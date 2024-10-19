#include <gtest/gtest.h>
#include <vector>

#include "Source/FASTEncoder.hpp"
#include "Source/Order.hpp"

TEST(FASTEncoder, EncodeToFAST)
{
    Trade trade{.price = 100, .quantity = 100, .side = OrderSide::Sell};
    MarketFeedMessage message{"AAPL", trade};

    std::vector<uint8_t> encodedMessage = EncodeToFAST(message);

    std::vector<uint8_t> symbolEncoded{0x04, 0x41, 0x41, 0x50, 0x4C};
    EXPECT_TRUE(
        std::equal(encodedMessage.begin(), encodedMessage.begin() + 5, symbolEncoded.begin()));

    std::vector<uint8_t> priceEncoded{0x00, 0x00, 0x00, 0x64};
    EXPECT_TRUE(
        std::equal(encodedMessage.begin() + 13, encodedMessage.begin() + 16, priceEncoded.begin()));

    std::vector<uint8_t> quantityEncoded{0x00, 0x00, 0x00, 0x64};
    EXPECT_TRUE(std::equal(encodedMessage.begin() + 17,
                           encodedMessage.begin() + 20,
                           quantityEncoded.begin()));

    EXPECT_EQ(encodedMessage.back(), 0x01);
}
