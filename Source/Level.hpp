#pragma once

#include <list>

#include "Order.hpp"

using OrdersList = std::list<Order>;
using OrdersListIterator = std::list<Order>::iterator;

class Level
{
  public:
    void RemoveOrder(OrdersListIterator iterator) noexcept;
    OrdersListIterator InsertOrder(Order& order);

    void ReduceVolumen(Quantity quantity);

    [[nodiscard]] OrdersList& GetOrders() noexcept;
    [[nodiscard]] OrdersList GetOrders() const noexcept;
    [[nodiscard]] Quantity GetVolume() const noexcept;

    [[nodiscard]] bool IsEmpty() const noexcept;

  private:
    OrdersList m_Orders{};
    Quantity m_Volumen{};
};
