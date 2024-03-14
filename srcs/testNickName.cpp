#include <gtest/gtest.h>
#include "abnf_components.hpp" // Ensure this path is correct
#include "class/specialized_string/NickName.hpp" // Ensure this path is correct

// Define a struct for the test parameters
struct NickNameTestParams {
    std::string nickname;
    bool expectedValidity;
};

// Define the test case class using the parameters
class NickNameValidityTest : public ::testing::TestWithParam<NickNameTestParams> {
protected:
    NickName nickname;

    // Setup method to initialize nickname with parameter value
    void SetUp() override {
        nickname = NickName(GetParam().nickname);
    }
};

// Test whether NickName::is_valid works as expected
TEST_P(NickNameValidityTest, ValidatesCorrectly) {
    EXPECT_EQ(nickname.is_valid(), GetParam().expectedValidity);
}

// Instantiate the test suite with parameter values
INSTANTIATE_TEST_SUITE_P(
    NickNameTests,
    NickNameValidityTest,
    ::testing::Values(
        // 0
        NickNameTestParams{"ValidNick", true},
        // 1
        NickNameTestParams{"", false}, // Empty nickname
        // 2
        NickNameTestParams{"TooLongNickName", false}, // Nickname exceeding maximum length
        // 3
        NickNameTestParams{"1Invalid", false}, // Invalid because it starts with a digit
        // 4
        NickNameTestParams{"Good-Nick", true}, // Valid with dash
        // 5
        NickNameTestParams{"John_75", true}, // Assuming '_' is within `special` characters
        // 6
        NickNameTestParams{"Invalid?", false}, // Contains a character not in any valid category
        // 7
        NickNameTestParams{"-Nickname", false} // Contains a character not in any valid category
        // Add more test cases as needed
    )
);
