#include <chrono>
#include <iostream>
#include <mutex>
#include <queue>
#include <random>
#include <thread>

#include "FASTEncoder.hpp"
#include "FixParser.hpp"
#include "Level.hpp"
#include "MarketFeedMessage.hpp"
#include "Order.hpp"
#include "OrderBook.hpp"
#include "TCPServer.hpp"
#include "Trade.hpp"
#include "UDPMulticast.hpp"

constexpr char kMulticastIP[] = "172.19.15.255";
constexpr int kFIXPort = 10000;
constexpr int kFASTPort = 10001;

static std::mutex ordersQueueMutex;
static std::mutex marketFeedQueueMutex;

void OrderBookThread(std::queue<Order>& queue, std::queue<MarketFeedMessage>& marketFeed)
{
    OrderBook orderBook{"AAPL"};

    orderBook.SetTradeNotification(
        [&marketFeed](std::string_view symbol, const Trade& trade)
        {
            marketFeed.emplace(symbol, trade);
        });

    while (true)
    {
        if (!queue.empty())
        {
            std::scoped_lock lock(ordersQueueMutex);
            Order order = std::move(queue.front());

            if (order.IsCancel())
            {
                orderBook.CancelOrder(order.GetId());
            }
            else
            {
                orderBook.AddOrder(order);
            }

            queue.pop();
        }

        orderBook.MatchOrders();
    }
}

void RequestsThread(std::queue<Order>& queue)
{
    boost::asio::io_context context;

    try
    {
        TCPClient::Callback dataReceivedCallback = [&](const char* data, const std::size_t length)
        {
            const std::string message(data, length);
            Order order = FixMessageToOrder(message);

            {
                std::scoped_lock lock(ordersQueueMutex);
                queue.push(order);
            }
        };

        TCPServer server(context, kFIXPort, dataReceivedCallback);
        context.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    context.stop();
}

void MarketFeedThread(std::queue<MarketFeedMessage>& queue)
{
    boost::asio::io_context context;
    UDPMulticast udpClient{context, kMulticastIP, kFASTPort};

    try
    {
        while (true)
        {
            MarketFeedMessage message{};

            if (!queue.empty())
            {
                std::scoped_lock lock(marketFeedQueueMutex);
                message = std::move(queue.front());
                queue.pop();
            }

            std::vector<uint8_t> buffer = EncodeToFAST(message);
            udpClient.Send(buffer);

            context.run();
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    context.stop();
}

int main()
{
    std::queue<Order> requestQueue;
    std::queue<MarketFeedMessage> marketFeedQueue;

    std::jthread requestsThread(RequestsThread, std::ref(requestQueue));
    std::jthread marketFeedThread(MarketFeedThread, std::ref(marketFeedQueue));
    std::jthread orderBookThread(OrderBookThread,
                                 std::ref(requestQueue),
                                 std::ref(marketFeedQueue));
}
