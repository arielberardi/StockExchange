#pragma once

#include <cassert>
#include <iostream>
#include <list>
#include <map>
#include <optional>
#include <string>
#include <unordered_map>

#include "Level.hpp"
#include "Order.hpp"

class OrderBook
{
  public:
    OrderBook(std::string_view symbol) : m_Symbol{symbol} {};

    void AddOrder(Order& order);
    void CancelOrder(OrderId orderId);
    void MatchOrders();

    void Print() const noexcept;

    [[nodiscard]] const Level& GetLevelInfo(OrderSide side, Price price) const;
    [[nodiscard]] std::size_t GetOrdersCount() const noexcept;
    [[nodiscard]] const Order& GetLastOrder(OrderSide side) const;

  private:
    std::unordered_map<OrderId, OrdersListIterator> m_Orders{};
    std::map<Price, Level, std::greater<Price>> m_Bids{};
    std::map<Price, Level, std::less<Price>> m_Asks{};
    std::string m_Symbol;
};
