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
    {
    DataArray da;
    Value v( da );
    ASSERT_FALSE(v.is_string());
    ASSERT_TRUE(v.is_array());
    ASSERT_EQ( Value::TYPE_ARRAY, v.type() );
    }
    {
    DataObject obj;
    Value v( obj );
    ASSERT_FALSE(v.is_string());
    ASSERT_TRUE(v.is_object());
    ASSERT_EQ( Value::TYPE_OBJECT, v.type() );
    }
}

TEST(DataArray, methods)
{
    DataArray a;
    ASSERT_EQ(0, a.size() );
    ASSERT_TRUE(a.empty());
    ASSERT_TRUE( a.begin() == a.end() );
    a.push_back(Value(1));
    ASSERT_EQ(1,a.size());
    ASSERT_FALSE(a.empty());
    ASSERT_EQ(Value::TYPE_INTEGER, a.back().type());
    ASSERT_EQ(1, a.back().to_int());

    a.push_back("ted");
    ASSERT_EQ(Value::TYPE_STRING, a.back().type());
    ASSERT_EQ("ted", a.back().to_string());
    ASSERT_EQ(2, a.size() );

    const DataArray& b = a;
    ASSERT_EQ(Value::TYPE_NULL, b[a.size()+1].type() );
}
TEST(DataObject, methods)
{
    DataObject o;
    ASSERT_EQ(0, o.size() );
    ASSERT_TRUE(o.empty());
    ASSERT_TRUE( o.begin() == o.end() );
    ASSERT_FALSE( o.contains("fed") );
    ASSERT_TRUE( o.insert(std::make_pair("fed",Value("hi"))).second );
    ASSERT_FALSE( o.insert(std::make_pair("fed",Value("bye"))).second );
    ASSERT_EQ(1, o.size() );
    ASSERT_FALSE(o.empty());
    o["ted"] = 1;
    ASSERT_EQ(2, o.size() );
    ASSERT_TRUE( o.contains("ted") );
    ASSERT_EQ(Value::TYPE_INTEGER, o["ted"].type() );
    ASSERT_EQ(1, o["ted"].to_int());
    o["ted"] = 1.4;
    ASSERT_EQ(2, o.size() );
    ASSERT_TRUE( o.contains("ted") );
    ASSERT_EQ(Value::TYPE_DOUBLE, o["ted"].type() );
    ASSERT_EQ(1.4, o["ted"].to_double());

    {
    DataObject o2;
    o2["fred"] = "teds brother";
    o["ted"] = o2;
    }
    ASSERT_EQ(Value::TYPE_OBJECT, o["ted"].type());
    ASSERT_TRUE(o["ted"].to_object() != nullptr );
    ASSERT_TRUE(o["ted"].to_object()->contains("fred"));
    ASSERT_EQ(Value::TYPE_STRING, o["ted"]["fred"].type());
    ASSERT_EQ("teds brother", o["ted"]["fred"].to_string());
    {
        DataArray a;
        for( int i = 0; i < 10; ++i)
        {
            a.push_back(i);
        }
        o["ted"]["arabic numbers"] = a;
    }
    ASSERT_TRUE( o["ted"].to_object()->contains("arabic numbers") );
    DataArray * a = o["ted"]["arabic numbers"].to_array();
    ASSERT_TRUE( a != nullptr );
    ASSERT_EQ(10, a->size() );
    for( int i = 0; i < a->size(); ++i )
    {
        SCOPED_TRACE(i);
        ASSERT_EQ(i, a->at(i).to_int());
    }
}
