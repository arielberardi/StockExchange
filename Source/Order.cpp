#include <iostream>

#include "Order.hpp"

void Order::Fill(Quantity quantity) noexcept
{
    m_RemainingQuantity -= quantity;
}

[[nodiscard]] bool Order::IsFilled() const noexcept
{
    return m_RemainingQuantity == 0;
}

[[nodiscard]] OrderId Order::GetId() const noexcept
{
    return m_Id;
}

[[nodiscard]] Quantity Order::GetRemainingQuantity() const noexcept
{
    return m_RemainingQuantity;
}

[[nodiscard]] OrderSide Order::GetSide() const noexcept
{
    return m_Side;
}

[[nodiscard]] Price Order::GetPrice() const noexcept
{
    return m_Price;
}

[[nodiscard]] Quantity Order::GetQuantity() const noexcept
{
    return m_Quantity;
}

[[nodiscard]] bool Order::IsBuy() const noexcept
{
    return m_Side == OrderSide::Buy;
}

[[nodiscard]] bool Order::IsSell() const noexcept
{
    return m_Side == OrderSide::Sell;
}

[[nodiscard]] bool Order::IsCancel() const noexcept
{
    return m_Type == OrderType::Cancel;
}

std::ostream& operator<<(std::ostream& os, const Order& order)
{
    std::string side = (order.m_Side == OrderSide::Buy) ? "Buy" : "Sell";
    os << order.m_Id << ", " << order.m_Price << ", " << order.m_Quantity << ", " << side;
    return os;
}
