#pragma once

#include <list>

#include "Order.hpp"

using OrdersList = std::list<Order>;
using OrdersListIterator = std::list<Order>::iterator;

class Level
{
  public:
    [[nodiscard]] bool IsEmpty() const noexcept
    {
        return m_Orders.empty();
    }

    void RemoveOrder(OrdersListIterator iterator) noexcept
    {
        assert(iterator != m_Orders.end());

        m_Orders.erase(iterator);
        m_Volumen -= iterator->GetRemainingQuantity();
    }

    OrdersListIterator InsertOrder(Order& order) noexcept
    {
        m_Orders.push_back(std::move(order));
        m_Volumen += order.GetRemainingQuantity();

        return std::prev(m_Orders.end());
    }

    void ReduceVolumen(Quantity quantity)
    {
        m_Volumen -= quantity;
    }

    [[nodiscard]] OrdersList& GetOrders() noexcept
    {
        return m_Orders;
    }

    [[nodiscard]] OrdersList GetOrders() const noexcept
    {
        return m_Orders;
    }

    [[nodiscard]] Quantity GetVolume() const noexcept
    {
        return m_Volumen;
    }

    // Level()
    // {
    //     std::cout << "Constructor" << std::endl;
    // }

    // ~Level() = default;

    // Level(const Level& level) : m_Orders{level.m_Orders}, m_Volumen{level.m_Volumen}
    // {
    //     std::cout << "Copy constructor" << std::endl;
    // }

    // Level(Level&& level) : m_Orders{std::move(level.m_Orders)}, m_Volumen{level.m_Volumen}
    // {
    //     std::cout << "Move constructor" << std::endl;
    // }

    // Level& operator=(const Level& other)
    // {
    //     std::cout << "Copy assignment" << std::endl;

    //     if (this == &other)
    //     {
    //         return *this;
    //     }

    //     m_Orders = other.m_Orders;
    //     m_Volumen = other.m_Volumen;
    //     return *this;
    // }

    // Level& operator=(Level&& other)
    // {
    //     std::cout << "Move assignment" << std::endl;

    //     if (this == &other)
    //     {
    //         return *this;
    //     }

    //     m_Orders = std::move(other.m_Orders);
    //     m_Volumen = other.m_Volumen;
    //     return *this;
    // }

  private:
    OrdersList m_Orders{};
    Quantity m_Volumen{};
};
