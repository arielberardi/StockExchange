#include "FASTEncoder.hpp"
#include "MarketFeedMessage.hpp"
#include "Trade.hpp"

[[nodiscard]] FASTMessage EncodeToFAST(MarketFeedMessage& message)
{
    FASTMessage buffer;

    buffer.push_back(static_cast<uint8_t>(message.GetSymbol().size()));
    buffer.insert(buffer.end(), message.GetSymbol().begin(), message.GetSymbol().end());

    int64_t epochTimestamp = message.GetTimestamp().time_since_epoch().count();
    for (int i = 7; i >= 0; --i)
    {
        buffer.push_back((epochTimestamp >> (i * 8)) & 0xFF);
    }

    for (int i = 3; i >= 0; --i)
    {
        buffer.push_back((message.GetTrade().price >> (i * 8)) & 0xFF);
    }

    for (int i = 3; i >= 0; --i)
    {
        buffer.push_back((message.GetTrade().quantity >> (i * 8)) & 0xFF);
    }

    buffer.push_back(static_cast<uint8_t>(message.GetTrade().side));

    return buffer;
}
