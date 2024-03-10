#include "gtest/gtest.h"

// MockIRCClient.hpp

#include <gmock/gmock.h>
#include "IRCClientInterface.hpp"

class MockIRCClient : public IRCClientInterface {
public:
    MOCK_METHOD(void, connect, (const std::string& server, int port), (override));
    MOCK_METHOD(std::string, sendCommand, (const std::string& command), (override));
};
