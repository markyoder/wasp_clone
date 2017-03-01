#include "gtest/gtest.h"

#include "waspcore/utils.h"
using namespace wasp;
/**
 * @brief TEST tests wild card pattern matching
 *
 */
TEST( utils, string_wilds)
{
    EXPECT_TRUE(wildcard_string_match("ge?ks*", "geeksforgeeks")); // Yes
    EXPECT_FALSE(wildcard_string_match("g*k", "gee"));  // No because 'k' is not in second
    EXPECT_FALSE(wildcard_string_match("*pqrs", "pqrst")); // No because 't' is not in first
    EXPECT_TRUE(wildcard_string_match("abc*bcd", "abcdhghgbcd")); // Yes
    EXPECT_FALSE(wildcard_string_match("abc*c?d", "abcd")); // No because second must have 2
                                                           // instances of 'c'
    EXPECT_TRUE(wildcard_string_match("*c*d", "abcd")); // Yes
    EXPECT_TRUE(wildcard_string_match("*?c*d", "abcd")); // Yes
    EXPECT_TRUE(wildcard_string_match("*", "could_be_anything")); // Yes
}

