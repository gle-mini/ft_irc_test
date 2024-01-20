#include "gtest/gtest.h"
#include "irc.hpp"

TEST(MainProgramTest, ReturnsZero) {
    EXPECT_EQ(mainProgram(), 0);
}
