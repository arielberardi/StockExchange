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
    MarketFeedMessage(std::string_view symbol, const Trade& trade)
        : m_Symbol{symbol}, m_Trade{trade}
    {
        m_Timestamp = std::chrono::high_resolution_clock::now();
    }

    [[nodiscard]] const std::string& GetSymbol() const noexcept
    {
        return m_Symbol;
    };

    [[nodiscard]] Timestamp GetTimestamp() const noexcept
    {
        return m_Timestamp;
    }

    [[nodiscard]] const Trade& GetTrade() const noexcept
    {
        return m_Trade;
    }

  private:
    std::string m_Symbol;
    Timestamp m_Timestamp;

    Trade m_Trade;
};
