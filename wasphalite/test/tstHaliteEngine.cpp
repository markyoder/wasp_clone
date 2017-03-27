/*
 * File:   tstHalite.cpp
 * Author: Robert A. Lefebvre
 */

#include <cstdlib>
#include <sstream>
#include <string>
#include <stdexcept>
#include <functional>
#include "wasphalite/HaliteInterpreter.h"

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
    ASSERT_TRUE( interpreter.evaluate(out) );
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
    ASSERT_TRUE( interpreter.evaluate(out) );
    ASSERT_EQ( expected.str(), out.str() );
}

TEST( Halite, DISABLED_static_text_fileimport)
{

    std::ofstream import("nested template.tmpl");
    std::stringstream expected;
    expected<<"this is "<<std::endl
         <<"nested files"<<std::endl
        <<std::endl // empty line
       <<"content"; // missing new line
    import<<expected.str();
    std::stringstream input;
    input<< R"INPUT(#import nested template.tmpl )INPUT";
    HaliteInterpreter<> interpreter;
    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    ASSERT_TRUE( interpreter.evaluate(out) );
    ASSERT_EQ( expected.str(), out.str() );
}
