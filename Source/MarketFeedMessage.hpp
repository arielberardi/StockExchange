#pragma once

#include <chrono>
#include <map>
#include <string>

#include "Order.hpp"
#include "OrderBook.hpp"
#include "Trade.hpp"

using Timestamp = std::chrono::_V2::system_clock::time_point;

class MarketFeedMessage
{
  public:
    MarketFeedMessage() = default;
    MarketFeedMessage(std::string_view symbol,
                      const Trade& trade,
                      const OrderBook::BidsMap& bids,
                      const OrderBook::AsksMap& asks)
        : m_Symbol{symbol}, m_Trade{trade}, m_Bids{bids}, m_Asks{asks}
    {
        m_Timestamp = std::chrono::high_resolution_clock::now();
    }

    std::string m_Symbol;
    Timestamp m_Timestamp;

    Trade m_Trade;

    OrderBook::BidsMap m_Bids;
    OrderBook::AsksMap m_Asks;
};
