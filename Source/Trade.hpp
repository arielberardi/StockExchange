#pragma once

#include "Order.hpp"

struct Trade
{
    Price price;
    Quantity quantity;
    OrderSide side;
};
