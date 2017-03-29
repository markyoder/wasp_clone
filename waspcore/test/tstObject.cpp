#include "gtest/gtest.h"

#include "waspcore/Object.h"
using namespace wasp;

TEST( Value, constructors )
{
    {
    Value v;
    ASSERT_TRUE(v.is_null());
    ASSERT_EQ(0, v.to_int());
    ASSERT_THROW(v.to_array(),std::runtime_error);
    ASSERT_THROW(v.to_object(),std::runtime_error);
    ASSERT_EQ( Value::TYPE_NULL, v.type() );
    }
    {
    Value v(true);
    ASSERT_TRUE(v.is_bool());
    ASSERT_EQ(1, v.to_int() );
    ASSERT_EQ(1.0, v.to_double() );
    ASSERT_TRUE(v.to_bool() );
    ASSERT_EQ( Value::TYPE_BOOLEAN, v.type() );
    }
    {
    Value v(1);
    ASSERT_TRUE(v.is_integer());
    ASSERT_TRUE(v.is_number());
    ASSERT_EQ(1, v.to_int() );
    ASSERT_EQ(1.0, v.to_double() );
    ASSERT_EQ( Value::TYPE_INTEGER, v.type() );
    }
    {
    Value v(1.1);
    ASSERT_FALSE(v.is_string());
    ASSERT_TRUE(v.is_double());
    ASSERT_TRUE(v.is_number());
    ASSERT_EQ(1, v.to_int() );
    ASSERT_EQ(1.1, v.to_double() );
    ASSERT_EQ( Value::TYPE_DOUBLE, v.type() );
    }
    {
    Value v("ted");
    ASSERT_TRUE(v.is_string());
    ASSERT_FALSE(v.is_number());
    ASSERT_EQ("ted",v.to_string());
    ASSERT_EQ( Value::TYPE_STRING, v.type() );
    }
    {
    Value v(std::string("fred"));
    ASSERT_TRUE(v.is_string());
    ASSERT_EQ("fred",v.to_string());
    std::string d = v.to_cstring();
    ASSERT_EQ("fred",d);
    ASSERT_EQ( Value::TYPE_STRING, v.type() );
    }
}
