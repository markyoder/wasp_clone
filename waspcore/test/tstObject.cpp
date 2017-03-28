#include "gtest/gtest.h"

#include "waspcore/Object.h"
using namespace wasp;

TEST( Object, constructors )
{
    {
    Value v;
    ASSERT_TRUE(v.is_null());
    ASSERT_EQ( Value::TYPE_NULL, v.type() );
    }
    {
    Value v(true);
    ASSERT_TRUE(v.is_bool());
    ASSERT_EQ( Value::TYPE_BOOLEAN, v.type() );
    }
    {
    Value v(1);
    ASSERT_TRUE(v.is_integer());
    ASSERT_TRUE(v.is_number());
    ASSERT_EQ( Value::TYPE_INTEGER, v.type() );
    }
    {
    Value v(1.0);
    ASSERT_FALSE(v.is_string());
    ASSERT_TRUE(v.is_double());
    ASSERT_TRUE(v.is_number());
    ASSERT_EQ( Value::TYPE_DOUBLE, v.type() );
    }
    {
    Value v("ted");
    ASSERT_TRUE(v.is_string());
    ASSERT_FALSE(v.is_number());
    ASSERT_EQ( Value::TYPE_STRING, v.type() );
    }
    {
    Value v(std::string("fred"));
    ASSERT_TRUE(v.is_string());
    ASSERT_EQ( Value::TYPE_STRING, v.type() );
    }
}
