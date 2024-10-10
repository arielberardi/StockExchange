#include <gtest/gtest.h>
#include <optional>

#include "Source/OrderBook.hpp"

TEST(OrderBook, AddOrder)
{
    OrderBook book{"AAPL"};
    Order order1{1, 100, 1, OrderSide::Buy, OrderType::Limit};

    book.AddOrder(order1);

    const Level& level{book.GetLevelInfo(OrderSide::Buy, 100)};
    EXPECT_EQ(level.GetOrders().size(), 1);

    const Order& bookOrder{book.GetLastOrder(OrderSide::Buy)};
    EXPECT_EQ(bookOrder.GetId(), 1);
}

TEST(OrderBook, CancelOrder)
{
    OrderBook book{"AAPL"};
    Order order1{1, 100, 1, OrderSide::Buy, OrderType::Limit};

    book.AddOrder(order1);
    book.CancelOrder(1);

    EXPECT_EQ(book.GetOrdersCount(), 0);
    EXPECT_DEATH(auto& level = book.GetLevelInfo(OrderSide::Buy, 100), ".*");
    EXPECT_DEATH(auto& order = book.GetLastOrder(OrderSide::Buy), ".*");
}

TEST(OrderBook, CancelNonExistingOrder)
{
    OrderBook book{"AAPL"};
    EXPECT_DEATH(book.CancelOrder(1), ".*");
}
