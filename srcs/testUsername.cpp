#include <gtest/gtest.h>
#include "class/specialized_string/UserName.hpp"

// Define a struct for parameterized tests
struct UserNameTestParams {
    std::string username;
    bool expectedValidity;
};

// Define the test case class using our parameters
class UserNameValidityTest : public ::testing::TestWithParam<UserNameTestParams> {
protected:
    UserName user;

    UserNameValidityTest() : user(GetParam().username) {}

    void SetUp() override {
        // Initialization code here if necessary
    }
};

// Test whether UserName::is_valid works as expected
TEST_P(UserNameValidityTest, ValidatesCorrectly) {
    const auto& params = GetParam();
    EXPECT_EQ(user.is_valid(), params.expectedValidity);
}

// Instantiate the test suite with our parameter values
INSTANTIATE_TEST_SUITE_P(
    UserNameTests,
    UserNameValidityTest,
    ::testing::Values(
        // 0
        UserNameTestParams{"validUsername", true},
        // 1
        UserNameTestParams{"", false}, // Empty username
        // 2
        UserNameTestParams{"invalid@username", false}, // Username with '@'
        // 3
        UserNameTestParams{"another.valid_username", true}, // Another valid example
        // 4
        UserNameTestParams{"\x0cl\t^Lix15BN", true},
        // 5
        UserNameTestParams{"`R", true},
        // 6
        UserNameTestParams{"~\x12_gIq4oMNw#\x14u", true},
        // 7
        UserNameTestParams{"lAy2I\x06{d\x0e\\;`Kl\\t", true},
        // 8
        UserNameTestParams{"b0", true},
        // 9
        UserNameTestParams{" invalid_space_start", false},  // Starts with a space.
        // 10
        UserNameTestParams{"invalid@symbol", false},  // Contains '@' symbol.
        // 11
        UserNameTestParams{"\nnewline", false},  // Starts with a newline character.
        // 12
        UserNameTestParams{"carriage\rreturn", false},  // Contains a carriage return.
        // 13
        UserNameTestParams{"tab\tcharacter", false}  // Contains a tab character.
    )
);

