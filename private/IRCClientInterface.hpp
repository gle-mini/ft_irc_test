#include "gtest/gtest.h"
#include <string>

// IRCClientInterface.hpp

class IRCClientInterface {
public:
    virtual ~IRCClientInterface() {}
    virtual void connect(const std::string& server, int port) = 0;
    virtual std::string sendCommand(const std::string& command) = 0;
};
