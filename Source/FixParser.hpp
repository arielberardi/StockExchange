#pragma once

#include "Order.hpp"
#include <iostream>

[[nodiscard]] Order FixMessageToOrder(std::string_view message);
