#include <gtest/gtest.h>
#include "class/specialized_string/Key.hpp" // Make sure to provide the correct path to your Key class

// Define a struct for the test parameters
struct KeyTestParams {
    std::string keyString;
    bool expectedValidity;
};

// Define the test case class using the parameters
class KeyValidityTest : public ::testing::TestWithParam<KeyTestParams> {
protected:
    Key key;

    // Setup method to initialize key with parameter value
    void SetUp() override {
        key = Key(GetParam().keyString);
    }
};

// Test whether Key::is_valid works as expected
TEST_P(KeyValidityTest, ValidatesCorrectly) {
    EXPECT_EQ(key.is_valid(), GetParam().expectedValidity);
}

// Instantiate the test suite with parameter values
INSTANTIATE_TEST_SUITE_P(
    KeyTests,
    KeyValidityTest,
    ::testing::Values(
        KeyTestParams{"ValidKey", true},
        KeyTestParams{"", false}, // Empty string, below minimum length
        KeyTestParams{"TooLongKeyIsInvalidBecauseItExceedsTheMaximumLength", false}, // Exceeds maximum length
        KeyTestParams{"Valid_Key", true}, // Valid key, assuming '_' is not in the excluded characters
        KeyTestParams{"In valid", false}, // Contains a space, assuming it's in the excluded characters
        KeyTestParams{"Invalid\tKey", false}, // Contains a tab character, explicitly in excluded characters
        KeyTestParams{"Invalid\nKey", false}, // Contains a newline character, explicitly in excluded characters
        KeyTestParams{"ValidKey123", true} // Valid key with digits
        // Add more test cases as needed
    )
);
