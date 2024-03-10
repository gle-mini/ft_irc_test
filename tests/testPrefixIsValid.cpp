#include "class/specialized_string/Prefix.hpp"
#include "gtest/gtest.h"

// Define a struct for test parameters
struct PrefixTestData
{
	std::string prefix;
	bool        expectedValidity;
};

class PrefixValidityTest : public ::testing::TestWithParam<PrefixTestData>
{
};

// Implement the test body
TEST_P(PrefixValidityTest, Validate)
{
	PrefixTestData data = GetParam();
	Prefix         prefix(data.prefix); // Assuming Prefix can be constructed from a std::string
	EXPECT_EQ(prefix.is_valid(), data.expectedValidity);
}

// Instantiate the test cases
INSTANTIATE_TEST_SUITE_P(
	PrefixTests,
	PrefixValidityTest,
	::testing::Values(
		// 0
		PrefixTestData{"", true}, // Empty prefix is valid
		// 1
		PrefixTestData{":user@host", false}, // Complexe false case
		// 2
		PrefixTestData{"user@host", false}, // Invalid, missing leading colon
		// 3
		PrefixTestData{":server.host.com", true}, // Valid server or host
		// 4
		PrefixTestData{":server..host.com", false}, // Invalid server or host with double dot
		// 5
		PrefixTestData{":Nick!User@Host", true}, // Valid nick!user@host format
		// 6
		PrefixTestData{":Nick!User@", false}, // Invalid, missing host
		// 7
		PrefixTestData{":!User@Host", false}, // Invalid, missing nick
		// 8
		PrefixTestData{":Nick!@Host", false}, // Invalid, missing user because user is empty
		// 9
		PrefixTestData{":N1ck-Name!U$er123@h0st-name.com", true}, // Complex valid case
		// 10
		PrefixTestData{":irc.example.com", true},
		// 11
		PrefixTestData{":johnDoe", true},
		// 12
		PrefixTestData{":janeDoe!user123@client.host.com", true},
		// 13
		PrefixTestData{":gurvan.server.example.com", true},
		// 14
		PrefixTestData{":userX!xYz@custom.host123.com", true},
		// 15
		PrefixTestData{":Bot42!bot@ai.server.net", true},
		// 16
		PrefixTestData{":nick!user@host", true}, // Complexe true case
		// 17
		PrefixTestData{":Nick!user@host", true}));
