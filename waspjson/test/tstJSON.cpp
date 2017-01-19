/*
 * File:   tstJSON.cpp
 * Author: raq
 *
 * Created on September 26, 2013, 11:43 AM
 */

#include <cstdlib>
#include <sstream>
#include <string>
#include <stdexcept>
#include <functional>
#include "waspjson/JSONInterpreter.h"

#include "gtest/gtest.h"
using namespace std;
using namespace wasp;



TEST( JJSON, DISABLED_simple )
{
    std::stringstream input;
    input<< R"INPUT(
{
 "key_string":"value",
 "key_int" :1,
 "key_double" : 1.03,
 "object": { },
 "array" : []
})INPUT";
    JSONInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(15, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ( 4, document.child_count() );
    std::stringstream printed_document;
    wasp::print(printed_document, document);
    ASSERT_EQ(input.str(), printed_document.str());
    ASSERT_EQ( input.str(), document.data() );
}

