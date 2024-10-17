#include <gtest/gtest.h>

#include "Source/MarketFeedMessage.hpp"
#include "Source/OrderBook.hpp"

TEST(OrderBook, AddOrder)
{
    OrderBook book{"AAPL"};
    Order order1{1, OrderAction::New, 100, 1, OrderSide::Buy, OrderType::Limit};

    book.AddOrder(order1);

    const Level& level{book.GetLevelInfo(OrderSide::Buy, 100)};
    EXPECT_EQ(level.GetOrders().size(), 1);

    const Order& bookOrder{book.GetLastOrder(OrderSide::Buy)};
    EXPECT_EQ(bookOrder.GetId(), 1);
}

TEST(OrderBook, CancelOrder)
{
    OrderBook book{"AAPL"};
    Order order1{1, OrderAction::New, 100, 1, OrderSide::Buy, OrderType::Limit};

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

TEST(OrderBook, NotificationCallbackOnTrade)
{
    OrderBook book{"AAPL"};

    MarketFeedMessage message;

    book.SetTradeNotification(
        [&](std::string_view symbol,
            const OrderBook::BidsMap& bids,
            const OrderBook::AsksMap& asks,
            const Trade& trade)
        {
            message.m_Symbol = symbol;
            message.m_Bids = bids;
            message.m_Asks = asks;
            message.m_Trade = trade;
        });

    Order order1{1, OrderAction::New, 100, 100, OrderSide::Buy, OrderType::Market};
    Order order2{2, OrderAction::New, 100, 100, OrderSide::Sell, OrderType::Market};

    book.AddOrder(order1);

    EXPECT_EQ(message.m_Symbol, "AAPL");
    EXPECT_EQ(message.m_Trade.price, 100);
    EXPECT_EQ(message.m_Trade.quantity, 100);
    EXPECT_EQ(message.m_Trade.side, OrderSide::Buy);
    EXPECT_TRUE(message.m_Bids.contains(100));
    EXPECT_TRUE(message.m_Asks.empty());

    book.AddOrder(order2);

    EXPECT_TRUE(message.m_Asks.contains(100));
    EXPECT_EQ(message.m_Trade.side, OrderSide::Sell);

    book.MatchOrders();

    EXPECT_EQ(message.m_Trade.price, 100);
    EXPECT_EQ(message.m_Trade.quantity, 100);
    EXPECT_EQ(message.m_Trade.side, OrderSide::Sell);
}
