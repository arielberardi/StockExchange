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
        std::cout << "Order Constructor" << this << std::endl;
    }

    ~Order()
    {
        std::cout << "Order Deleted" << this << std::endl;
    };

    Order(const Order& order)
        : m_Id{order.m_Id}, m_Price{order.m_Price}, m_Quantity{order.m_Quantity},
          m_RemainingQuantity{order.m_RemainingQuantity}, m_Side{order.m_Side}, m_Type{order.m_Type}
    {
        std::cout << "Order Copy constructor" << this << std::endl;
    }

    Order(Order&& order)
        : m_Id{order.m_Id}, m_Price{order.m_Price}, m_Quantity{order.m_Quantity},
          m_RemainingQuantity{order.m_RemainingQuantity}, m_Side{order.m_Side}, m_Type{order.m_Type}
    {
        std::cout << "Order Move constructor" << this << std::endl;
    }

    Order& operator=(Order& other)
    {
        std::cout << "Order Copy assignment" << this << std::endl;

        if (this == &other)
        {
            return *this;
        }

        m_Id = other.m_Id;
        m_Price = other.m_Price;
        m_Quantity = other.m_Quantity;
        m_RemainingQuantity = other.m_RemainingQuantity;
        m_Side = other.m_Side;
        m_Type = other.m_Type;

        return *this;
    }

    Order& operator=(Order&& other)
    {
        std::cout << "Order Move assignment" << std::endl;

        if (this == &other)
        {
            return *this;
        }

        m_Id = other.m_Id;
        m_Price = other.m_Price;
        m_Quantity = other.m_Quantity;
        m_RemainingQuantity = other.m_RemainingQuantity;
        m_Side = other.m_Side;
        m_Type = other.m_Type;

        return *this;
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
