#include <chrono>
#include <iostream>
#include <mutex>
#include <queue>
#include <random>
#include <thread>

#include "FixParser.hpp"
#include "Level.hpp"
#include "Order.hpp"
#include "OrderBook.hpp"
#include "TCPServer.hpp"

std::mutex ordersQueueMutex;

void OrderBookThread(std::queue<Order>& queue)
{
    OrderBook orderBook{"AAPL"};

    while (true)
    {
        {
            if (!queue.empty())
            {
                std::scoped_lock lock(ordersQueueMutex);
                Order& order = queue.front();

                std::cout << "Order received: " << order << std::endl;

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
        }

        orderBook.MatchOrders();
    }
}

void RequestsThread(std::queue<Order>& queue, boost::asio::io_context& context)
{
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

        TCPServer server(context, 8142, dataReceivedCallback);
        context.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

int main()
{
    std::queue<Order> requestQueue;
    boost::asio::io_context context;

    {
        // We keep threads in separated scope so they can be joined before calling context.stop()
        // Isn't clear from the Docs to me if destructor of io_context would have same effect as
        // stop

        std::jthread orderBookThread(OrderBookThread, std::ref(requestQueue));
        std::jthread requestsThread(RequestsThread, std::ref(requestQueue), std::ref(context));
    }

    context.stop();
}
