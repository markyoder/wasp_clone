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
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(6, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ( 5, document.child_count() );
    std::string expected_paths = R"INPUT(/
/txt (This is plain test)
/txt (line2)
/txt ( line3)
/txt (   line)
/txt (            )
)INPUT";
        std::stringstream paths;
        document.paths(paths);
        ASSERT_EQ(expected_paths, paths.str());
        ASSERT_EQ(input.str(), document.data());
}


TEST( Halite, simple_parameterized_text)
{
    std::stringstream input;
    input<< R"INPUT(This is plain test
<attribute1><attr2><ted>
            )INPUT";
    HaliteInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(15, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ( 5, document.child_count() );
    std::string expected_paths = R"INPUT(/
/txt (This is plain test)
/attr
/attr/< (<)
/attr/txt (attribute1)
/attr/> (>)
/attr
/attr/< (<)
/attr/txt (attr2)
/attr/> (>)
/attr
/attr/< (<)
/attr/txt (ted)
/attr/> (>)
/txt (            )
)INPUT";
        std::stringstream paths;
        document.paths(paths);
        ASSERT_EQ(expected_paths, paths.str());
        ASSERT_EQ(input.str(), document.data());
}
