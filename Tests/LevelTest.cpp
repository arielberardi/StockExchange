#include <gtest/gtest.h>

#include "Source/Level.hpp"

TEST(Level, InsertOrder)
{
    Order order{1, OrderAction::New, 100, 100, OrderSide::Buy, OrderType::Market};

    Level level{};
    level.InsertOrder(order);

    EXPECT_EQ(level.GetOrders().size(), 1);
    EXPECT_EQ(level.GetOrders().back().GetId(), 1);
    EXPECT_EQ(level.GetVolume(), 100);
}

TEST(Level, RemoveOrder)
{
    Order order{1, OrderAction::New, 100, 100, OrderSide::Buy, OrderType::Market};

    Level level{};
    OrdersListIterator orderIterator = level.InsertOrder(order);

    level.RemoveOrder(orderIterator);

    EXPECT_TRUE(level.GetOrders().empty());
    EXPECT_EQ(level.GetVolume(), 0);
}

TEST(Level, ReduceVolume)
{
    Order order{1, OrderAction::New, 100, 100, OrderSide::Buy, OrderType::Market};

    Level level{};
    level.InsertOrder(order);

    EXPECT_EQ(level.GetVolume(), 100);

    level.ReduceVolume(50);

    EXPECT_EQ(level.GetVolume(), 50);
}

TEST(Level, IsEmpty)
{
    Order order{1, OrderAction::New, 100, 100, OrderSide::Buy, OrderType::Market};
    Level level{};

    EXPECT_TRUE(level.IsEmpty());

    level.InsertOrder(order);

    EXPECT_FALSE(level.IsEmpty());
}
