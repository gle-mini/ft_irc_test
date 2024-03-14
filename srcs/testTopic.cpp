#include <gtest/gtest.h>
#include "class/specialized_string/Topic.hpp" // Update this include path to your Topic class file

// Define a struct for the test parameters
struct TopicTestParams {
    std::string topicString;
    bool expectedValidity;
};

// Define the test case class using the parameters
class TopicValidityTest : public ::testing::TestWithParam<TopicTestParams> {
protected:
    Topic topic;

    // Setup method to initialize topic with parameter value
    void SetUp() override {
        topic = Topic(GetParam().topicString);
    }
};

// Test whether Topic::is_valid works as expected
TEST_P(TopicValidityTest, ValidatesCorrectly) {
    EXPECT_EQ(topic.is_valid(), GetParam().expectedValidity);
}

// Instantiate the test suite with parameter values
INSTANTIATE_TEST_SUITE_P(
    TopicTests,
    TopicValidityTest,
    ::testing::Values(
        TopicTestParams{"ValidTopic", true}, // Valid topic with no newline or carriage return
        TopicTestParams{"Invalid\nTopic", false}, // Invalid topic with newline
        TopicTestParams{"Invalid\rTopic", false}, // Invalid topic with carriage return
        TopicTestParams{"Another ValidTopic", true}, // Another valid topic
        TopicTestParams{"Invalid\r\nTopic", false} // Invalid topic with both newline and carriage return
        // Add more test cases as needed
    )
);
