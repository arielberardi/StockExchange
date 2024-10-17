#pragma once

#include <cstdint>
#include <iostream>

using OrderId = unsigned long;
using Price = int32_t;
using Quantity = int32_t;

enum class OrderAction
{
    New,
    Cancel,
    Update
};

enum class OrderType
{
    Market = 1,
    Limit,
    Stop,
    StopLimit
};

enum class OrderSide
{
    Buy,
    Sell
};

class Order
{
  public:
    Order(OrderId id,
          OrderAction action,
          Price price,
          Quantity quantity,
          OrderSide side,
          OrderType type)
        : m_Id{id}, m_Action{action}, m_Price{price}, m_Quantity{quantity},
          m_RemainingQuantity{quantity}, m_Side{side}, m_Type{type}
    {
    }

    void Fill(Quantity quantity) noexcept;

    [[nodiscard]] OrderId GetId() const noexcept;
    [[nodiscard]] Quantity GetRemainingQuantity() const noexcept;
    [[nodiscard]] OrderSide GetSide() const noexcept;
    [[nodiscard]] Price GetPrice() const noexcept;
    [[nodiscard]] Quantity GetQuantity() const noexcept;

    [[nodiscard]] bool IsFilled() const noexcept;
    [[nodiscard]] bool IsBuy() const noexcept;
    [[nodiscard]] bool IsSell() const noexcept;

    [[nodiscard]] bool IsNew() const noexcept;
    [[nodiscard]] bool IsUpdate() const noexcept;
    [[nodiscard]] bool IsCancel() const noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Order& order);

  private:
    OrderId m_Id;
    Price m_Price;
    Quantity m_Quantity;
    Quantity m_RemainingQuantity;
    OrderSide m_Side;
    OrderType m_Type;
    OrderAction m_Action;
};
