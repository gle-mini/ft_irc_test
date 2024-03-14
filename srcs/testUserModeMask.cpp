#include <gtest/gtest.h>
#include "class/specialized_string/UserModeMask.hpp"

// Define a struct for the test parameters
struct UserModeMaskTestParams {
    std::string modeMask;
    uint8_t umodes;
    bool expectedValidity;
};

// Define the test case class using the parameters
class UserModeMaskValidityTest : public ::testing::TestWithParam<UserModeMaskTestParams> {
protected:
    UserModeMask userModeMask;

    void SetUp() override {
        userModeMask = UserModeMask(GetParam().modeMask);
    }
};

// Test whether UserModeMask::is_valid works as expected
TEST_P(UserModeMaskValidityTest, ValidatesCorrectly) {
    const auto& params = GetParam();
    EXPECT_EQ(userModeMask.is_valid(params.umodes), params.expectedValidity);
}

// Instantiate the test suite with our parameter values
INSTANTIATE_TEST_SUITE_P(
    UserModeMaskTests,
    UserModeMaskValidityTest,
    ::testing::Values(
        UserModeMaskTestParams{"ab", 0, true}, // Valid: length is 2, umodes fits the mask
        UserModeMaskTestParams{"abc", 0, false}, // Invalid: length is more than 2
        UserModeMaskTestParams{"a", 13, false}, // Invalid: umodes does not fit the mask (13 & ~12 != 0)
        UserModeMaskTestParams{"", 8, true}, // Valid: empty string and umodes fits the mask
        UserModeMaskTestParams{"ab", 4, true} // Valid: length is 2, umodes fits the mask (4 & ~12 == 0)
        // Add more test cases as needed
    )
);
