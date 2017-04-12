/*
 * File:   tstHalite.cpp
 * Author: Robert A. Lefebvre
 */

#include <cstdlib>
#include <cstdio> // std::remove(file_name)
#include <sstream>
#include <string>
#include <stdexcept>
#include <functional>
#include "wasphalite/HaliteInterpreter.h"
#include "wasphalite/DataAccessor.h"
#include "waspcore/Object.h"

#include "gtest/gtest.h"
using namespace std;
using namespace wasp;

TEST( Halite, single_attribute)
{
    std::stringstream input;
    input<< R"INPUT(<attribute>)INPUT";
    HaliteInterpreter<> interpreter;
    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataAccessor data;
    data.store("attribute",std::string("value")); // need explicit string type
    ASSERT_EQ( Context::Type::STRING, data.type("attribute") );
    ASSERT_TRUE( interpreter.evaluate(out,data) );
    ASSERT_EQ( "value", out.str() );
}
TEST( Halite, formatted_single_attribute)
{
    std::stringstream input;
    input<< R"INPUT(<pi:fmt=rounded=%12.8f>
<pi>)INPUT";
    HaliteInterpreter<> interpreter;
    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataAccessor data; data.add_default_variables();
    ASSERT_TRUE( interpreter.evaluate(out,data) );
    ASSERT_EQ( "rounded=  3.14159265\n3.14159", out.str() );
}
TEST( Halite, indirect_attribute)
{
    std::stringstream input;
    input<< R"INPUT(<<attr>> <<what>.<member>>)INPUT";
    HaliteInterpreter<> interpreter;
    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataObject o;
    DataAccessor data(&o);
    o["attr"]=std::string("what");
    o["what"]=std::string("obj");
    o["member"]=std::string("x");
    o["obj.x"]=3.14159;
    ASSERT_TRUE( interpreter.evaluate(out,data) );
    ASSERT_EQ( "obj 3.14159", out.str() );
}
TEST( Halite, static_text)
{
    std::stringstream input;
    input<< R"INPUT(This is plain test
line2
 line3
   line
            )INPUT";
    HaliteInterpreter<> interpreter;
    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataAccessor data;
    ASSERT_TRUE( interpreter.evaluate(out,data) );
    ASSERT_EQ( input.str(), out.str() );
}
TEST( Halite, parameterized_text )
{
    std::stringstream input;
    input<< R"INPUT(This is plain test
 < pi >  <pi>
 <pi>
   line
            )INPUT";
    std::stringstream expected;
    expected<< R"INPUT(This is plain test
 3.14159  3.14159
 3.14159
   line
            )INPUT";
    HaliteInterpreter<> interpreter;
    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataAccessor data; data.add_default_variables();
    ASSERT_TRUE( interpreter.evaluate(out,data) );
    ASSERT_EQ( expected.str(), out.str() );
}

/**
 * @brief test attribute acquisition using DataAccessor layer
 */
TEST( Halite, parameterized_text_data_accessed )
{
    std::stringstream input;
    input<< R"INPUT(This is plain test
 < ted >  <fred>
 <x>
   line
            )INPUT";
    std::stringstream expected;
    expected<< R"INPUT(This is plain test
 wombat  3.14159
 2
   line
            )INPUT";
    HaliteInterpreter<> interpreter;
    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataObject o;
    DataAccessor data(&o);
    o["ted"] = "wombat";
    o["fred"] = 3.14159;
    o["x"] = 2;
    ASSERT_TRUE( interpreter.evaluate(out,data) );
    ASSERT_EQ( expected.str(), out.str() );
}

/**
 * @brief test attribute usage from nested template
 * This ensures the data layer is properly propogated
 * to the nested halite engine
 */
TEST( Halite, attributed_text_fileimport)
{

    std::ofstream import("nested parameterized template.tmpl");
    std::stringstream content;
    content<<"this is"<<std::endl
         <<"nested files using <ted>"<<std::endl
        <<std::endl // empty line
       <<"and assigning fred to < fred = x >"; // missing new line
    import<<content.str();
    import.close();
    std::stringstream input;
    input<< R"INPUT(#import ./nested parameterized template.tmpl
<ted> has <fred> brothers)INPUT";
    HaliteInterpreter<> interpreter;

    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataObject o;
    DataAccessor data(&o);
    o["ted"] = "wombat";
    o["fred"] = 3.14159;
    ASSERT_EQ( Value::TYPE_STRING, o["ted"].type() );
    ASSERT_EQ( Value::TYPE_DOUBLE, o["fred"].type() );
    o["x"] = 2;
    ASSERT_TRUE( interpreter.evaluate(out,data) );

    std::stringstream expected;
    expected<< R"INPUT(this is
nested files using wombat

and assigning fred to 2
wombat has 2 brothers)INPUT";
    ASSERT_EQ( expected.str(), out.str() );
    std::remove("nested parameterized template.tmpl");
    ASSERT_EQ( Value::TYPE_INTEGER, o["fred"].type() );
    ASSERT_EQ( 2, o["fred"].to_int() );
}

/**
 * @brief test attribute usage from nested template where nested path is parameterized
 */
TEST( Halite, parameterized_fileimport)
{

    std::ofstream import("nested attr wombat.tmpl");
    std::stringstream content;
    content<<"this is"<<std::endl
         <<"nested files using <ted>"<<std::endl
        <<std::endl // empty line
       <<"and assigning fred to < fred = x >"; // missing new line
    import<<content.str();
    import.close();
    std::stringstream input;
    input<< R"INPUT(#import ./nested <x> <ted>.tmpl
<ted> has <fred> brothers)INPUT";
    HaliteInterpreter<> interpreter;

    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataObject o;
    DataAccessor data(&o);
    o["ted"] = "wombat";
    o["fred"] = 3.14159;
    ASSERT_EQ( Value::TYPE_STRING, o["ted"].type() );
    ASSERT_EQ( Value::TYPE_DOUBLE, o["fred"].type() );
    o["x"] = "attr";
    ASSERT_TRUE( interpreter.evaluate(out,data) );

    std::stringstream expected;
    expected<< R"INPUT(this is
nested files using wombat

and assigning fred to attr
wombat has attr brothers)INPUT";
    ASSERT_EQ( expected.str(), out.str() );
    std::remove("nested attr wombat.tmpl");
    ASSERT_EQ( Value::TYPE_STRING, o["fred"].type() );
    ASSERT_EQ( "attr", o["fred"].to_string() );
}

TEST( Halite, simple_conditional)
{
    std::stringstream input;
    input<< R"INPUT(#ifdef pi


<pi> is defined as pi math constant


#else

 some else statement


text



#endif
)INPUT";

    HaliteInterpreter<> interpreter;
    ASSERT_TRUE( interpreter.parse(input) );
    { // test defined path through template
        std::stringstream expected;
        expected<< R"INPUT(

3.14159 is defined as pi math constant

)INPUT";
        std::stringstream out;
        DataObject o;
        o["pi"] = 3.14159;
        DataAccessor data(&o);
        ASSERT_TRUE( interpreter.evaluate(out,data) );
        ASSERT_EQ( expected.str(), out.str() );
    }
    { // test defined path through template
        std::stringstream expected;
        expected<< R"INPUT(
 some else statement


text


)INPUT";
        std::stringstream out;
        DataObject o;
        DataAccessor data(&o);
        ASSERT_TRUE( interpreter.evaluate(out,data) );
        ASSERT_EQ( expected.str(), out.str() );
    }
}
TEST( Halite, nested_conditional)
{
    std::stringstream input;
    input<< R"INPUT(#ifdef pi

#if <<pi:fmt=%.0f>==3>
<pi> is defined as pi math constant
#endif

#else

 some else statement

#ifndef pi
text
#endif


#endif
)INPUT";

    HaliteInterpreter<> interpreter;
    ASSERT_TRUE( interpreter.parse(input) );
    { // test defined path through template
        std::stringstream expected;
        expected<< R"INPUT(
3.14159 is defined as pi math constant
)INPUT";
        std::stringstream out;
        DataObject o;
        o["pi"] = 3.14159;
        DataAccessor data(&o);
        ASSERT_TRUE( interpreter.evaluate(out,data) );
        ASSERT_EQ( expected.str(), out.str() );
    }
    { // test defined path through template
        std::stringstream expected;
        expected<< R"INPUT(
 some else statement

text

)INPUT";
        std::stringstream out;
        DataObject o;
        DataAccessor data(&o);
        ASSERT_TRUE( interpreter.evaluate(out,data) );
        ASSERT_EQ( expected.str(), out.str() );
    }
}

/**
 * @brief test conditional blocks
 */
TEST( Halite, conditional_text_data_accessed )
{
    std::stringstream input;
    input<< R"INPUT(#ifdef x
x is defined and has a value of <x>
#elseif    <defined(y)>
x is not defined,
 but y is defined with value as an int of <y:fmt=%.0f>
#else
x and y are not defined
#endif
   line
            )INPUT";
    HaliteInterpreter<> interpreter;
    ASSERT_TRUE( interpreter.parse(input) );
    { // test defined path through template
        std::stringstream expected;
        expected<< R"INPUT(x is defined and has a value of 3.14159
   line
            )INPUT";
        std::stringstream out;
        DataObject o;
        o["x"] = 3.14159;
        DataAccessor data(&o);
        ASSERT_TRUE( interpreter.evaluate(out,data) );
        ASSERT_EQ( expected.str(), out.str() );
    }

    { // test elseif  path through template
        std::stringstream expected;
        expected<< R"INPUT(x is not defined,
 but y is defined with value as an int of 7
   line
            )INPUT";
        std::stringstream out;
        DataObject o;
        o["y"] = 7.14159;
        DataAccessor data(&o);
        ASSERT_TRUE( interpreter.evaluate(out,data) );
        ASSERT_EQ( expected.str(), out.str() );
    }
    { // test undefined path through template
        std::stringstream expected;
        expected<< R"INPUT(x and y are not defined
   line
            )INPUT";
        std::stringstream out;
        DataObject o;
        DataAccessor data(&o);
        ASSERT_TRUE( interpreter.evaluate(out,data) );
        ASSERT_EQ( expected.str(), out.str() );
    }
}
