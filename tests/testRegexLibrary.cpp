#include "gtest/gtest.h"
#include "regex.hpp"
#include "irc.hpp"

// Define a struct to hold test parameters
struct RegexTestParams {
    const char* pattern;
    const char* text;
    const char* expected;
};

// Declare the regex_test function
int regex_test(const char* pattern, const char* sampleString, const char* trueAnswer);

// Define the test fixture class
class RegexDebugTest : public ::testing::TestWithParam<RegexTestParams> {};

// Implement the test cases
TEST_P(RegexDebugTest, MatchesExpectedOutput) {
    RegexTestParams params = GetParam();
    // Convert std::string to const char* and call regex_test
    int result = regex_test(params.pattern, params.text, params.expected);
    
	if (result == 1)
		std::cout << "TTTTTTTTTTTESSSSSSSSSSSSSTTTTTTTTTTTTTTTTT" << std::endl;
    // Check if the result matches the expected value
    // Assuming that the 'expected' field in RegexTestParams indicates whether an error is expected or not.
    // For example, if 'expected' is "true", we expect regex_test to return 0, and if 'expected' is "false", we expect regex_test to return 1.
    bool expectedResult = (result == 0) ? 0 : 1;
    EXPECT_EQ(result, expectedResult);
}

// Instantiate the test cases
INSTANTIATE_TEST_SUITE_P(
    Default, RegexDebugTest,
    ::testing::Values(
        // Add all your test cases here
        RegexTestParams{"(\\(*.\\[)[qQ]", "((a[Q]", "((a[Q]"},
        RegexTestParams{"((b)c)", "abc", "bc"},
		RegexTestParams{"(a)((b)c)?", "abc","abc"},
		RegexTestParams{"(a)(((b))c)(d)?", "abc","abc"},
		RegexTestParams{"ba*(ac)?", "baaa","baaa"},
		RegexTestParams{"a{1,2}c?q?", "aaa","aa"},
		RegexTestParams{"a{3,}c?q?", "aaacq","aaacq"},
		RegexTestParams{"a{2}v", "aaav","aav"},
		RegexTestParams{"a*b*c*", "",""},
		RegexTestParams{"a*","zb",""},   
		RegexTestParams{"a*b*c*q", "","@NO"},
		RegexTestParams{"ba*", "baaa","baaa"},
		RegexTestParams{"ba*(ac)+", "baaac","baaac"},
		RegexTestParams{"ba+", "baaa","baaa"},
		RegexTestParams{"ba{0,3}", "baaa","baaa"},
		RegexTestParams{"ba{1,2}c?q?", "baaa","baa"},
		RegexTestParams{"[0-3]*(22a)", "12222a","12222a"},
		RegexTestParams{"b[0-9]+", "abc123xyz","@NO"},
		RegexTestParams{"ac?.[0-2]*", "abc123xyz","ab"},
		RegexTestParams{"ac?b[q-z]*c{0,4}.[0-2]*(22a)", "abc12222a","abc12222a"},
		RegexTestParams{"(6(0|4|5)_)+", "61_60_64_65_A","60_64_65_"},
		RegexTestParams{"(6(0|4|5)_)*", "61_60_64_65_A","60_64_65_"},
		RegexTestParams{"(6(011|44|5)_)*", "6012_6011_644_65_6541_","6011_644_65_"},
		RegexTestParams{"^a[ \t\r\n\v\f]*", "za \n ","@NO"},							// Test spaces
		RegexTestParams{"a[ \t\r\n\v\f]*b", "ga \tbv","a \tb"},
		RegexTestParams{"a[ \t\r\n\v\f]*", "za \t\t \f\n ","a \t\t \f\n "},
		RegexTestParams{"f..k","zfolky","folk"},
		RegexTestParams{"va*b","kkvaaaab","vaaaab"},
		RegexTestParams{".*b","ababc","abab"},
		RegexTestParams{"z.*b","xyzababc","zabab"},
		RegexTestParams{".*b","bc","b"},
		RegexTestParams{"[abc]1{2}(cat|pup+y|dog).{2}","_a11puppy11_","a11puppy11"},   
		RegexTestParams{"[abc]*\\|","zab|","ab|"},   
		RegexTestParams{"[abc]*\\|[AC-Z]*","zab|ACDB","ab|ACD"},   
		RegexTestParams{"[abc]*\\|[ABCK]*","zab|ACKvv","ab|ACK"},   
		RegexTestParams{"[ABCK\\+UZ0-9]*","AAZ+BUB","AAZ+BUB"},   
		RegexTestParams{"[ABCKUZ0-9\\-]*","AAZ-BUB","AAZ-BUB"},			
		RegexTestParams{"[ABCK\\-UZ0-9]*","AAZ-BUB","AAZ-BUB"},							
		RegexTestParams{"[abc]*\\|[A\\?B-Z]*","zab|A?BCD","ab|A?BCD"},   
		RegexTestParams{"[^xyz]","zab","a"},   
		RegexTestParams{"[^xyc]+","zab","zab"},   
		RegexTestParams{"([0-9]+a{2,4})+q","1aa23aaa445aaaaq","1aa23aaa445aaaaq"},   
		RegexTestParams{"([abc]?[01]?)*","a1b00aab","a1b00aab"},   
		RegexTestParams{"[a-c]+(x{2,4})*","cxxxxxxxx","cxxxxxxxx"},   
		RegexTestParams{"([a-c]+(x{1,2})?)+x","cxccxxccxxx","cxccxxccxxx"},   
		RegexTestParams{"a[0-9]+b",   "za789b","a789b"},
		RegexTestParams{"[^A-Za-z]*","abc12..","12.."},
		RegexTestParams{"^a\\+{3}\\*\\?b","a+++*?bc","a+++*?b"},
		RegexTestParams{"\\[\\[","a[?][[1","[["},
		RegexTestParams{"(V\\.?A\\.?T\\.?|TAX|TVA)( *[^A-Z]? +)?[A-_\\. ]*([0-9]+([\\.,][0-9]{1,2})?%?[0-9]+([\\.,][0-9]{1,2})?%_? +)?([A-_\\. ]*)?([0-9]+[\\.,][0-9]{1,2} +)?[A-_]? *[\\-\\+]?[0-9]+(,[0-9]{3})*[\\.,][0-9]{1,2} *.? *\n","         VAT                      3.93\n","VAT                      3.93\n"},
		RegexTestParams{"\\[\\]","a[?][]1","[]1"},										
		RegexTestParams{"(\\[\\?\\])*\\|(\\*)+","a[?][?]|**1","[?][?]|**"},				
		RegexTestParams{"(.+)(.+)","AB","AB"},
		RegexTestParams{"((.*A)BABA)Z","ZABABABABAZQ","ZABABABABAZ"}
    )
);
