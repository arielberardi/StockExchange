#pragma once

using OrderId = int64_t;
using Price = int32_t;
using Quantity = int32_t;

enum class OrderType
{
    Market,
    Limit,
    Stop,
    StopLimit,
    FillAndKill,
    FillOrKill,
    GoodTillTime,
    GoodTillDate,
};

enum class OrderSide
{
    Buy,
    Sell
};

class Order
{
  public:
    Order(OrderId id, Price price, Quantity quantity, OrderSide side, OrderType type)
        : m_Id{id}, m_Price{price}, m_Quantity{quantity}, m_RemainingQuantity{quantity},
          m_Side{side}, m_Type{type}
    {
    }

    void Fill(Quantity quantity) noexcept
    {
        m_RemainingQuantity -= quantity;
    }

    [[nodiscard]] bool IsFilled() const noexcept
    {
        return m_RemainingQuantity == 0;
    }

    [[nodiscard]] OrderId GetId() const noexcept
    {
        return m_Id;
    }

    [[nodiscard]] Quantity GetRemainingQuantity() const noexcept
    {
        return m_RemainingQuantity;
    }

    [[nodiscard]] OrderSide GetSide() const noexcept
    {
        return m_Side;
    }

    [[nodiscard]] Price GetPrice() const noexcept
    {
        return m_Price;
    }

    [[nodiscard]] Quantity GetQuantity() const noexcept
    {
        return m_Quantity;
    }

    [[nodiscard]] bool IsBuy() const noexcept
    {
        return m_Side == OrderSide::Buy;
    }

    [[nodiscard]] bool IsSell() const noexcept
    {
        return m_Side == OrderSide::Sell;
    }

  private:
    OrderId m_Id;
    Price m_Price;
    Quantity m_Quantity;
    Quantity m_RemainingQuantity;
    OrderSide m_Side;
    OrderType m_Type;
};
