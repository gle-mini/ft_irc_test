#include "gtest/gtest.h"
#include "irc.hpp"

TEST(HelloTest, ReturnsZero) {
    EXPECT_EQ(hello(), 0);
}
