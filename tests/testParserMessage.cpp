#include "gtest/gtest.h"
#include "Message.hpp"
#include "irc.hpp"

#include "gtest/gtest.h"
#include "regex.hpp"
#include "irc.hpp"

#include "Message.hpp"
#include <gtest/gtest.h>
#include <vector>
#include <string>

// Define a struct for test parameters
struct MessageTestParam {
    std::string input; // Input IRC message
    std::string expectedPrefix; // Expected prefix after parsing
    std::string expectedCommand; // Expected command after parsing
    std::vector<std::string> expectedParams; // Expected parameters after parsing
};

// Define the test case class
class MessageParsingTest : public ::testing::TestWithParam<MessageTestParam> {};

=TEST_P(MessageParsingTest, ParsesCorrectly) {
    MessageTestParam const& param = GetParam();
    Message message(param.input);

    EXPECT_EQ(message.get_prefix(), param.expectedPrefix);
    EXPECT_EQ(message.get_command(), param.expectedCommand);
    ASSERT_EQ(message.get_params().size(), param.expectedParams.size());
    for (size_t i = 0; i < param.expectedParams.size(); ++i) {
        EXPECT_EQ(message.get_params()[i], param.expectedParams[i]);
    }
}

// Instantiate the test case
INSTANTIATE_TEST_CASE_P(Default, MessageParsingTest, ::testing::Values(
    MessageTestParam{":Nick!user@host PRIVMSG #channel :Hello, world!", "Nick!user@host", "PRIVMSG", {"#channel", "Hello, world!"}},
    MessageTestParam{"PING :server", "", "PING", {"server"}},
    MessageTestParam{"ERROR :Network Unreachable", "", "ERROR", {"Network Unreachable"}}
));