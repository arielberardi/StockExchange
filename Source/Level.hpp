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

  private:
    OrdersList m_Orders{};
    Quantity m_Volumen{};
};
