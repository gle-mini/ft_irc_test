#include "gtest/gtest.h"
#include "class/Message.hpp"
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

TEST_P(MessageParsingTest, ParsesCorrectly) {
    MessageTestParam const& param = GetParam();
    Message message(param.input);

    EXPECT_EQ(message.get_prefix(), param.expectedPrefix);
    EXPECT_EQ(message.get_command(), param.expectedCommand);
    EXPECT_EQ(message.get_parameters().size(), param.expectedParams.size());
    for (size_t i = 0; i < param.expectedParams.size(); ++i) {
        EXPECT_EQ(message.get_parameters()[i], param.expectedParams[i]);
    }
}

// Instantiate the test case
INSTANTIATE_TEST_SUITE_P(
    Default, MessageParsingTest,
    ::testing::Values(
        // 0
        MessageTestParam{":Nick!user@host PRIVMSG #channel :Hello, world!", "Nick!user@host", "PRIVMSG", {"#channel", ":Hello, world!"}},
        // 1
        MessageTestParam{"PING :server", "", "PING", {":server"}},
        // 2
        MessageTestParam{"PING:server", "", "PING:server", {}},
        // 3
        MessageTestParam{"ERROR :Network Unreachable", "", "ERROR", {":Network Unreachable"}},
        // 4
        MessageTestParam{"PING :server last param heyhey", "", "PING", {":server last param heyhey"}},
        // 5
        MessageTestParam{"PING server last :param heyhey", "", "PING", {"server","last",":param heyhey"}},
        // 6
        MessageTestParam{":Nickname!user@host PRIVMSG #channel :Salut tout le monde, comment ça va ?", "Nickname!user@host", "PRIVMSG", {"#channel", ":Salut tout le monde, comment ça va ?"}},
        // 7
        MessageTestParam{":Nickname!user@host PRIVMSG #channel :@membre1 @membre2, pouvez-vous jeter un œil à http://exemple.com ? Aussi, /join #autreCanal pour notre réunion.", "Nickname!user@host", "PRIVMSG", {"#channel",":@membre1 @membre2, pouvez-vous jeter un œil à http://exemple.com ? Aussi, /join #autreCanal pour notre réunion."}},
        // 8
        MessageTestParam{":Nickname!user@host MODE #channel +o utilisateur", "Nickname!user@host", "MODE", {"#channel", "+o", "utilisateur"}}
    )
);