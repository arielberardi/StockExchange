#include <gtest/gtest.h>

#include "Source/FixParser.hpp"
#include "Source/Order.hpp"

TEST(FixParser, FixMessageToOrder)
{
    std::string message = "8=FIX.4.2|35=D|49=CLIENT12|56=SERVER|34=1|52=20231015-15:30:00.000|11=1|"
                          "21=1|55=AAPL|54=1|38=100|40=1|44=10|59=0|10=128|";

    Order order = FixMessageToOrder(message);

    EXPECT_EQ(order.GetId(), 1);
    EXPECT_EQ(order.GetSide(), OrderSide::Buy);
    EXPECT_EQ(order.GetPrice(), 10);
    EXPECT_EQ(order.GetQuantity(), 100);
}
