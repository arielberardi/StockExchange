#include <cassert>

#include "Level.hpp"
#include "Order.hpp"
#include "OrderBook.hpp"

void OrderBook::AddOrder(Order& order)
{
    OrderId id = order.GetId();
    Price price = order.GetPrice();

    if (order.IsBuy())
    {
        m_Orders[id] = m_Bids[price].InsertOrder(order);
    }
    else
    {
        m_Orders[id] = m_Asks[price].InsertOrder(order);
    }
}

void OrderBook::CancelOrder(OrderId orderId)
{
    assert(m_Orders.contains(orderId));

    OrdersListIterator orderIterator = m_Orders.at(orderId);
    Price price = orderIterator->GetPrice();

    m_Orders.erase(orderId);

    if (orderIterator->IsBuy())
    {
        Level& level = m_Bids.at(price);
        level.RemoveOrder(orderIterator);

        if (level.IsEmpty())
        {
            m_Bids.erase(price);
        }
    }
    else
    {
        Level& level = m_Asks.at(price);
        level.RemoveOrder(orderIterator);

        if (level.IsEmpty())
        {
            m_Asks.erase(price);
        }
    }
}

void OrderBook::MatchOrders()
{
    if (m_Asks.empty() || m_Bids.empty())
    {
        return;
    }

    auto& [bidPrice, bidLevel] = *m_Bids.begin();
    auto& [askPrice, askLevel] = *m_Asks.begin();

    if (bidPrice < askPrice)
    {
        return;
    }

    OrdersList& bidOrders = bidLevel.GetOrders();
    OrdersList& askOrders = askLevel.GetOrders();

    while (!bidLevel.IsEmpty() && !askLevel.IsEmpty())
    {
        Order& bid = bidOrders.front();
        Order& ask = askOrders.front();
        Quantity quantity = std::min(bid.GetRemainingQuantity(), ask.GetRemainingQuantity());

        bid.Fill(quantity);
        ask.Fill(quantity);

        bidLevel.ReduceVolume(quantity);
        askLevel.ReduceVolume(quantity);

        if (bid.IsFilled())
        {
            m_Orders.erase(bid.GetId());
            bidOrders.pop_front();
        }

        if (ask.IsFilled())
        {
            m_Orders.erase(ask.GetId());
            askOrders.pop_front();
        }
    }

    if (bidLevel.IsEmpty())
    {
        m_Bids.erase(bidPrice);
    }

    if (askLevel.IsEmpty())
    {
        m_Asks.erase(askPrice);
    }
}

const Level& OrderBook::GetLevelInfo(OrderSide side, Price price) const
{
    assert(side == OrderSide::Buy ? m_Bids.contains(price) : m_Asks.contains(price));
    return side == OrderSide::Buy ? m_Bids.at(price) : m_Asks.at(price);
}

[[nodiscard]] std::size_t OrderBook::GetOrdersCount() const noexcept
{
    return m_Orders.size();
}

const Order& OrderBook::GetLastOrder(OrderSide side) const
{
    assert(side == OrderSide::Buy ? !m_Bids.empty() : !m_Asks.empty());

    auto& [_, level] = side == OrderSide::Buy ? *m_Bids.begin() : *m_Asks.begin();
    return level.GetOrders().back();
}
