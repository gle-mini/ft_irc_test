#include "class/specialized_string/Password.hpp" // Ensure this path is correct
#include <gtest/gtest.h>

#define MAXIMUM_LENGTH_FOR_PASSWORD 50
// Define a struct to hold test parameters
struct PasswordTestParams
{
	std::string password;
	bool        expectedIsValid;
};

// Define the test case class, inheriting from testing::TestWithParam
class PasswordValidationTest : public ::testing::TestWithParam<PasswordTestParams>
{
protected:
	Password password_;

	// SetUp method to initialize the password before each test
	void SetUp() override { password_ = Password(GetParam().password); }
};

// Define the tests using TEST_P macro, which works with parameterized tests
TEST_P(PasswordValidationTest, Validate)
{
	const auto &params = GetParam();
	EXPECT_EQ(params.expectedIsValid, password_.is_valid());
}

// Instantiate the test suite with test case parameters
INSTANTIATE_TEST_SUITE_P(
	PasswordTests,
	PasswordValidationTest,
	::testing::Values(
		// 0
		PasswordTestParams{"", false}, // Empty password
		// 1
		PasswordTestParams{":-abc", false}, // Starts with invalid character
		// 2
		PasswordTestParams{"abc", true}, // Valid without colon
		// 3
		PasswordTestParams{"a:bc", true}, // Valid with colon
		// 4
		PasswordTestParams{"a:b\nc", false}, // Invalid character after colon
		// 5
		PasswordTestParams{std::string(MAXIMUM_LENGTH_FOR_PASSWORD, 'a'), true}, // Long valid password
		// 6
		PasswordTestParams{std::string(MAXIMUM_LENGTH_FOR_PASSWORD + 6, 'a'), false}, // Too long password
                                                                                      // 7
		PasswordTestParams{"a1=\tm", true},
		// 8
		PasswordTestParams{"p8d~a(yT", true},
		// 9
		PasswordTestParams{"14]i{d", true},
		// 10
		PasswordTestParams{"7.29_D:(l(", true},
		// 11
		PasswordTestParams{"%x8]bqx", true},
		// 12
		PasswordTestParams{"7^U}3:Uo", true},
		// 13
		PasswordTestParams{"8:K2'", true},
		// 14
		PasswordTestParams{"azws", true},
		// 15
		PasswordTestParams{"5!Ki:Gy", true},
		// 16
		PasswordTestParams{"7'0b", true},
		// 17
		PasswordTestParams{"\r\t\t\t\t\n", false}, // Entirely made of invalid characters (control characters, spaces,
                                                   // etc.) 18
		PasswordTestParams{"ValidPassword L", false}, // Contains a space, usually invalid
                                                      // 19
		PasswordTestParams{":nnnnn", false},   // Starts with a colon, which should be invalid without preceding valid
                                               // characters 20
		PasswordTestParams{"nnn\nppp", false}, // Contains newline characters, invalid
                                               // 21
		PasswordTestParams{"CCCCC:", true},    // Ends with a colon
                                               // 22
		PasswordTestParams{":", false},        // Just a invalid colon
                                               // 23
		PasswordTestParams{"\r\t\t\t\t\n", false}, // Entirely made of invalid characters (control characters, spaces,
                                                   // etc.) 24
		PasswordTestParams{"JJJ\raaa", false},     // Contains a carriage return, invalid
                                                   // 25
		PasswordTestParams{"<>\\ggg", true},       // Strange valid case
                                                   // 26
		PasswordTestParams{
			"foskfdku788&*T*G8984346425146245156g16452456525v4452v46v442^&^*(&)*(UH(J(*U%)))",
			false},                          // Too long
                                             // 27
		PasswordTestParams{"mlYjKN", true},  // Only letters, should be valid
                                             // 28
		PasswordTestParams{"156052", true},  // Only digits, should be valid
                                             // 29
		PasswordTestParams{"#/?}{;", true},  // Only special characters, should be valid
                                             // 30
		PasswordTestParams{"798o5y", true},  // Mix of letters and digits, should be valid
                                             // 31
		PasswordTestParams{"[:G:[:G", true}, // Valid characters with a colon in the middle, should be valid
                                             // 32
		PasswordTestParams{"~,*:><!", true}, // Special characters only, with a colon, should be valid
                                             // 33
		PasswordTestParams{"G9|$P~{~X^C'2o=8,<#r", true}, // Long valid password with a mix of characters, should be
                                                          // valid 34
		PasswordTestParams{"\ntsHXi", false}, // Starts with an invalid character (e.g., newline), should be invalid
                                              // 35
		PasswordTestParams{"SXnAL\n", false}, // Ends with an invalid character, should be invalid
											  // 36
		PasswordTestParams{
			"';p+4\n%79j?",
			false}, // Long password with an invalid character inserted in the middle, should be invalid
		// 37
		PasswordTestParams{":AAA", false}, // Invalid password starting by colon
		// 38
		PasswordTestParams{"A:AA", true} // Valid password with colon

		));