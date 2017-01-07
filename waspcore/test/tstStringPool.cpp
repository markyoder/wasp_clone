#include "waspcore/StringPool.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>
using namespace wasp;



TEST(StringPool,push_test)
{
    StringPool<> sp;
    sp.push("ted");
    sp.push("fred");
    ASSERT_EQ(2,sp.string_count());
}

TEST(StringPool,data_test)
{
    StringPool<> sp;
    {
        std::string s = "ted";
        sp.push(s.c_str());
        std::string es = sp.data(0);
        ASSERT_EQ(s,es);
    }
    {
        std::string s = "fred";
        sp.push(s.c_str());
        std::string es = sp.data(1);
        ASSERT_EQ(s,es);
    }
    ASSERT_EQ(2,sp.string_count());
}

TEST(StringPool,pop_test)
{
    StringPool<> sp;
    {
        std::string s = "ted";
        sp.push(s.c_str());
        std::string es = sp.data(0);
        ASSERT_EQ(s,es);
        ASSERT_EQ(4,sp.size()); // 'ted\0'
    }
    {
        std::string s = "fred";
        sp.push(s.c_str());
        std::string es = sp.data(1);
        ASSERT_EQ(s,es);
        ASSERT_EQ(9,sp.size()); // 'ted\0fred\0'
    }
    {
        sp.pop();
        ASSERT_EQ(4,sp.size());// 'ted\0'

        ASSERT_EQ(1,sp.string_count());
    }
    {
        sp.pop();
        // ''
        ASSERT_EQ(0,sp.size());
    }
    ASSERT_EQ(0,sp.string_count());
}

TEST(StringPool,copy_test)
{
    StringPool<> sp;
    {
        std::string s = "ted";
        sp.push(s.c_str());
        std::string es = sp.data(0);
        ASSERT_EQ(s,es);
    }
    {
        std::string s = "fred";
        sp.push(s.c_str());
        std::string es = sp.data(1);
        ASSERT_EQ(s,es);
    }
    ASSERT_EQ(2,sp.string_count());
    StringPool<> copy(sp);
    {
        std::string s = "ted";
        std::string es = copy.data(0);
        ASSERT_EQ(s,es);
    }
    {
        std::string s = "fred";
        std::string es = copy.data(1);
        ASSERT_EQ(s,es);
    }
    ASSERT_EQ(sp.string_count(),copy.string_count());
}
/**
 * @brief TEST pushing strings that originate in the pool
 * This tests the string pool's ability to recognize strings
 * originating from within the pool and to handle the
 * pool reallocations appropriately so as to avoid memory defects
 */
TEST(StringPool,self_copy_test)
{
    StringPool<> sp;
    {
        {
        std::string s(100,'1');
        sp.push(s.c_str());
        std::string es = sp.data(0);
        ASSERT_EQ(s,es);
        }
        {
        std::string s(200,'2');
        sp.push(s.c_str());
        std::string es = sp.data(1);
        ASSERT_EQ(s,es);
        }
    }
    // make 10 copies of the first string already in the pool
    for( size_t i = 0; i < 10; ++i )
    {
        const char * data = sp.data(0);
        sp.push(data);
        std::string es = sp.data(0);
        ASSERT_EQ(100, es.size() );
        std::string s = data;
        ASSERT_EQ(s,es);
    }
    // make 10 copies of a string already in the pool
    for( size_t i = 0; i < 10; ++i )
    {
        const char * data = sp.data(1);
        sp.push(data);
        std::string es = sp.data(sp.string_count()-1);
        std::string s = data;
        ASSERT_EQ(s,es);
        ASSERT_EQ(200, es.size() );
    }

}
