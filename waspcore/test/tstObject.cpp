#include "gtest/gtest.h"

#include "waspcore/Object.h"
using namespace wasp;

TEST( Object, constructors )
{
    {
    Value v;
    ASSERT_EQ( Value::TYPE_NULL, v.type() );
    }
    {
    Value v(true);
    ASSERT_EQ( Value::TYPE_BOOLEAN, v.type() );
    }
    {
    Value v(1);
    ASSERT_EQ( Value::TYPE_INTEGER, v.type() );
    }
    {
    Value v(1.0);
    ASSERT_EQ( Value::TYPE_DOUBLE, v.type() );
    }
    {
    Value v("ted");
    ASSERT_EQ( Value::TYPE_STRING, v.type() );
    }
    {
    Value v(std::string("fred"));
    ASSERT_EQ( Value::TYPE_STRING, v.type() );
    }
}
