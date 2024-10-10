#include <chrono>
#include <vector>

#include "OrderBook.hpp"

int main()
{
    OrderBook orderBook{"AAPL"};

    Order order1{1, 100, 100, OrderSide::Sell, OrderType::Limit};
    Order order2{2, 100, 100, OrderSide::Buy, OrderType::Limit};

    orderBook.AddOrder(order1);
    orderBook.AddOrder(order2);

    // auto start = std::chrono::high_resolution_clock::now();

    orderBook.MatchOrders();

    // auto end = std::chrono::high_resolution_clock::now();
    // auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
}
