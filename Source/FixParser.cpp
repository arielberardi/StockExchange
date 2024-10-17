#include <algorithm>
#include <iostream>
#include <ranges>
#include <unordered_map>

#include "FixParser.hpp"
#include "Order.hpp"

using FixHashMap = std::unordered_map<int, std::string>;

[[nodiscard]] static FixHashMap FixMessageToHashMap(std::string_view message)
{
    FixHashMap map;

    for (const auto& keyvalue : std::views::split(message, '|'))
    {
        std::string keyvalueStr(keyvalue.begin(), keyvalue.end());

        // Final delimiter
        if (keyvalueStr.length() <= 1)
        {
            break;
        }

        std::size_t delimiter = keyvalueStr.find('=');

        if (delimiter == std::string::npos)
        {
            throw std::runtime_error("FixParser: message is invalid.");
        }

        std::string key = keyvalueStr.substr(0, delimiter);
        std::string value = keyvalueStr.substr(delimiter + 1);

        int keyIndex = std::stoi(key);
        map[keyIndex] = value;
    }

    return map;
}

[[nodiscard]] static OrderType FixOrderTypeToEnum(std::string_view value)
{
    if (value == "1")
        return OrderType::Market;
    if (value == "2")
        return OrderType::Limit;
    if (value == "3")
        return OrderType::Stop;
    if (value == "4")
        return OrderType::StopLimit;

    return static_cast<OrderType>(0);
}

[[nodiscard]] Order FixMessageToOrder(std::string_view message)
{
    FixHashMap messageHash = FixMessageToHashMap(message);

    OrderId id = std::stoul(messageHash.at(11));
    Price price = std::stoi(messageHash.at(44));
    Quantity quantity = std::stoi(messageHash.at(38));
    OrderSide side = messageHash.at(54) == "1" ? OrderSide::Buy : OrderSide::Sell;
    OrderType type = FixOrderTypeToEnum(messageHash.at(40));
    OrderAction action = messageHash.at(35) == "F" ? OrderAction::New : OrderAction::Cancel;

    Order order{id, action, price, quantity, side, type};
    return order;
}
