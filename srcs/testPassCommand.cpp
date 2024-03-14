#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TestableServer.hpp" // Assurez-vous d'inclure votre classe TestableServer
#include "MockClient.hpp" // Incluez votre MockClient si nécessaire




using ::testing::Return;
using ::testing::_;

class ServerPassTest : public ::testing::Test {
protected:
    TestableServer testServer; // Utilise TestableServer au lieu de Server
};

TEST_F(ServerPassTest, CorrectPassword) {
    MockClient mockClient;
    std::vector<std::string> params = {"correctPassword"}; // Assurez-vous que ceci est le bon mot de passe

    EXPECT_CALL(mockClient, has_mode(_))
        .WillOnce(Return(false));
    EXPECT_CALL(mockClient, set_mode(_))
        .Times(1);

    testServer._pass(mockClient, params); // Appel de _pass via TestableServer
}