#include "wasp/core/StringPool.h"
#include "wasp_harness.h"
#include <iostream>
#include <string>
using namespace wasp;


WASP_TESTS
TEST(StringPool,push_test)
{
    StringPool<> sp;
    sp.push("ted");
    sp.push("fred");
    W_ASSERT_EQ(2,sp.string_count());
}
TEST_END(StringPool,push_test)
TEST(StringPool,data_test)
{
    StringPool<> sp;
    {
        std::string s = "ted";
        sp.push(s.c_str());
        std::string es = sp.data(0);
        W_ASSERT_EQ(s,es);
    }
    {
        std::string s = "fred";
        sp.push(s.c_str());
        std::string es = sp.data(1);
        W_ASSERT_EQ(s,es);
    }
    W_ASSERT_EQ(2,sp.string_count());
}
TEST_END(StringPool,data_test)
TEST(StringPool,pop_test)
{
    StringPool<> sp;
    {
        std::string s = "ted";
        sp.push(s.c_str());
        std::string es = sp.data(0);
        W_ASSERT_EQ(s,es);
        W_ASSERT_EQ(4,sp.size()); // 'ted\0'
    }
    {
        std::string s = "fred";
        sp.push(s.c_str());
        std::string es = sp.data(1);
        W_ASSERT_EQ(s,es);
        W_ASSERT_EQ(9,sp.size()); // 'ted\0fred\0'
    }
    {
        sp.pop();
        W_ASSERT_EQ(4,sp.size());// 'ted\0'

        W_ASSERT_EQ(1,sp.string_count());
    }
    {
        sp.pop();
        // ''
        W_ASSERT_EQ(0,sp.size());
    }
    W_ASSERT_EQ(0,sp.string_count());
}
TEST_END(StringPool,pop_test)
TEST(StringPool,copy_test)
{
    StringPool<> sp;
    {
        std::string s = "ted";
        sp.push(s.c_str());
        std::string es = sp.data(0);
        W_ASSERT_EQ(s,es);
    }
    {
        std::string s = "fred";
        sp.push(s.c_str());
        std::string es = sp.data(1);
        W_ASSERT_EQ(s,es);
    }
    W_ASSERT_EQ(2,sp.string_count());
    StringPool<> copy(sp);
    {
        std::string s = "ted";
        std::string es = copy.data(0);
        W_ASSERT_EQ(s,es);
    }
    {
        std::string s = "fred";
        std::string es = copy.data(1);
        W_ASSERT_EQ(s,es);
    }
    W_ASSERT_EQ(sp.string_count(),copy.string_count());
}
TEST_END(StringPool,copy_test)
WASP_TESTS_END
