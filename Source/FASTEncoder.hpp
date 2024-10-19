#pragma once

#include <vector>

#include "MarketFeedMessage.hpp"
#include "Trade.hpp"

using FASTMessage = std::vector<uint8_t>;

[[nodiscard]] FASTMessage EncodeToFAST(MarketFeedMessage& message);
