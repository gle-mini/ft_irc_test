#include "gtest/gtest.h"

TEST(HelloTest, ReturnsZero) {
    EXPECT_EQ(hello(), 0);
}
