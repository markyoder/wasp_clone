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

