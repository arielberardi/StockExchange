#pragma once

#include <functional>
#include <map>
#include <string>
#include <string_view>
#include <unordered_map>

#include "Level.hpp"
#include "Order.hpp"
#include "Trade.hpp"

class OrderBook
{
  public:
    using BidsMap = std::map<Price, Level, std::greater<Price>>;
    using AsksMap = std::map<Price, Level, std::less<Price>>;
    using TradeCallback = std::function<void(std::string_view symbol, const Trade& trade)>;

    OrderBook(std::string_view symbol) : m_Symbol{symbol} {};

    void AddOrder(Order& order);
    void CancelOrder(OrderId orderId);
    void MatchOrders();

    [[nodiscard]] const Level& GetLevelInfo(OrderSide side, Price price) const;
    [[nodiscard]] std::size_t GetOrdersCount() const noexcept;
    [[nodiscard]] const Order& GetLastOrder(OrderSide side) const;

    void SetTradeNotification(OrderBook::TradeCallback callback);

  private:
    std::unordered_map<OrderId, OrdersListIterator> m_Orders{};
    BidsMap m_Bids{};
    AsksMap m_Asks{};
    std::string m_Symbol;

    TradeCallback m_TradeCallback{};
};
