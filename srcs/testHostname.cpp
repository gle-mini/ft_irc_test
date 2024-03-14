#include <gtest/gtest.h>
#include "class/specialized_string/HostName.hpp" // Make sure to provide the correct path to your HostName class

// Define a struct for the test parameters
struct HostNameTestParams {
    std::string hostname;
    bool expectedValidity;
};

// Define the test case class using the parameters
class HostNameValidityTest : public ::testing::TestWithParam<HostNameTestParams> {
protected:
    HostName hostname;

    // Setup method to initialize hostname with parameter value
    void SetUp() override {
        hostname = HostName(GetParam().hostname);
    }
};

// Test whether HostName::is_valid works as expected
TEST_P(HostNameValidityTest, ValidatesCorrectly) {
    EXPECT_EQ(hostname.is_valid(), GetParam().expectedValidity);
}

// Instantiate the test suite with parameter values
INSTANTIATE_TEST_SUITE_P(
    HostNameTests,
    HostNameValidityTest,
    ::testing::Values(
        // 0
        HostNameTestParams{"valid-hostname.com", true},
        // 1
        HostNameTestParams{"-invalidhostname.com", false}, // Invalid because it starts with a dash
        // 2
        HostNameTestParams{"invalidhostname-.com", true}, // Invalid because segment ends with a dash
        // 3
        HostNameTestParams{"invalid..hostname.com", false}, // Invalid because of empty segment
        // 4
        HostNameTestParams{"1valid-hostname.com", true}, // Valid starting with a digit
        // 5
        HostNameTestParams{"validhostname", true}, // Valid single segment
        // 6
        HostNameTestParams{"valid_hostname.com", false}, // Invalid due to underscore
        // 7
        HostNameTestParams{"127.0.0.1", true} // Assuming numeric hostnames are allowed
        // Add more test cases as needed
    )
);
