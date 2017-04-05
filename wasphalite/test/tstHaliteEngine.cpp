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
    input<< R"INPUT(#import ./nested parameterized template.tmpl )INPUT";
    HaliteInterpreter<> interpreter;

    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataObject o;
    DataAccessor data(&o);
    o["ted"] = "wombat";
    o["fred"] = 3.14159;
    ASSERT_EQ( Value::TYPE_DOUBLE, o["fred"].type() );
    o["x"] = 2;
    ASSERT_TRUE( interpreter.evaluate(out,data) );

    std::stringstream expected;
    expected<< R"INPUT(this is
nested files using wombat

and assigning fred to 2)INPUT";
    ASSERT_EQ( expected.str(), out.str() );
    std::remove("nested parameterized template.tmpl");
    ASSERT_EQ( Value::TYPE_INTEGER, o["fred"].type() );
    ASSERT_EQ( 2, o["fred"].to_int() );
}

