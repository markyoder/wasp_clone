#include "../ExprInterpreter.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>
using namespace wasp;

// TODO elaborate this test suite

TEST(ExprInterpreter,addition)
{
    std::stringstream input;
    input <<"8+9"<<std::endl;
    ExprInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(5, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ(1, document.child_count() );
}

TEST(ExprInterpreter,expression)
{
    std::stringstream input;
    input <<R"INPUT(
function = A*c^2*(1-c)^2+B*(c^2+6*(1-c)*(gr0^2+gr1^2+gr2^2+gr3^2)
             -4*(2-c)*(gr0^3+gr1^3+gr2^3+gr3^3)
             +3*(gr0^2+gr1^2+gr2^2+gr3^2)^2)
)INPUT";
    ExprInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(146, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ(1, document.child_count() );
}

