#include "Level.hpp"
#include "Order.hpp"
#include "OrderBook.hpp"

int main()
{
    OrderBook orderBook{"AAPL"};

    Order order1{1, 100, 100, OrderSide::Sell, OrderType::Limit};
    Order order2{2, 100, 100, OrderSide::Buy, OrderType::Limit};

    orderBook.AddOrder(order1);
    orderBook.AddOrder(order2);

    orderBook.MatchOrders();
}
