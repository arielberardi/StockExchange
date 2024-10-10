#include <cassert>

#include "Level.hpp"
#include "Order.hpp"

[[nodiscard]] bool Level::IsEmpty() const noexcept
{
    return m_Orders.empty();
}

void Level::RemoveOrder(OrdersListIterator iterator) noexcept
{
    assert(iterator != m_Orders.end());

    m_Orders.erase(iterator);
    m_Volumen -= iterator->GetRemainingQuantity();
}

OrdersListIterator Level::InsertOrder(Order& order)
{
    m_Orders.push_back(std::move(order));
    m_Volumen += order.GetRemainingQuantity();

    return std::prev(m_Orders.end());
}

void Level::ReduceVolumen(Quantity quantity)
{
    m_Volumen -= quantity;
}

[[nodiscard]] OrdersList& Level::GetOrders() noexcept
{
    return m_Orders;
}

[[nodiscard]] OrdersList Level::GetOrders() const noexcept
{
    return m_Orders;
}

[[nodiscard]] Quantity Level::GetVolume() const noexcept
{
    return m_Volumen;
}
