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
    auto op = document.child_at(0);
    ASSERT_EQ(wasp::PLUS, op.type());
    ASSERT_EQ(3, op.child_count());
    ASSERT_EQ(wasp::VALUE, op.child_at(0).type());
    ASSERT_EQ(wasp::PLUS, op.child_at(1).type());
    ASSERT_EQ(wasp::VALUE, op.child_at(2).type());
    auto result = interpreter.evaluate();
    ASSERT_TRUE(result.is_integer());
    ASSERT_TRUE(result.is_number());
    ASSERT_FALSE(result.is_real());
    ASSERT_FALSE(result.is_string());
    ASSERT_FALSE(result.is_error());
    ASSERT_EQ(17, result.integer());
}
TEST(ExprInterpreter,substraction)
{
    std::stringstream input;
    input <<"8 - 3"<<std::endl;
    ExprInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(5, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ(1, document.child_count() );
    auto op = document.child_at(0);
    ASSERT_EQ(wasp::MINUS, op.type());
    ASSERT_EQ(3, op.child_count());
    ASSERT_EQ(wasp::VALUE, op.child_at(0).type());
    ASSERT_EQ(wasp::MINUS, op.child_at(1).type());
    ASSERT_EQ(wasp::VALUE, op.child_at(2).type());
    auto result = interpreter.evaluate();
    ASSERT_TRUE(result.is_integer());
    ASSERT_TRUE(result.is_number());
    ASSERT_FALSE(result.is_real());
    ASSERT_FALSE(result.is_string());
    ASSERT_FALSE(result.is_error());
    ASSERT_EQ(5, result.integer());
}
TEST(ExprInterpreter,assign)
{
    std::stringstream input;
    input <<"x=2"<<std::endl;
    ExprInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(5, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ(1, document.child_count() );
    auto op = document.child_at(0);
    ASSERT_EQ(wasp::KEYED_VALUE, op.type());
    ASSERT_EQ(3, op.child_count());
    ASSERT_EQ(wasp::DECL, op.child_at(0).type());
    ASSERT_EQ(wasp::ASSIGN, op.child_at(1).type());
    ASSERT_EQ(wasp::VALUE, op.child_at(2).type());
}
TEST(ExprInterpreter,exponent)
{
    std::stringstream input;
    input <<"3^2"<<std::endl;
    ExprInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(5, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ(1, document.child_count() );
    auto op = document.child_at(0);
    ASSERT_EQ(wasp::EXPONENT, op.type());
    ASSERT_EQ(3, op.child_count());
    ASSERT_EQ(wasp::VALUE, op.child_at(0).type());
    ASSERT_EQ(wasp::EXPONENT, op.child_at(1).type());
    ASSERT_EQ(wasp::VALUE, op.child_at(2).type());
    auto result = interpreter.evaluate();
    ASSERT_TRUE(result.is_integer());
    ASSERT_TRUE(result.is_number());
    ASSERT_FALSE(result.is_real());
    ASSERT_FALSE(result.is_string());
    ASSERT_FALSE(result.is_error());
    ASSERT_EQ(9, result.integer());
}
TEST(ExprInterpreter,mult)
{
    std::stringstream input;
    input <<"8 * 3"<<std::endl;
    ExprInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(5, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ(1, document.child_count() );
    auto op = document.child_at(0);
    ASSERT_EQ(wasp::MULTIPLY, op.type());
    ASSERT_EQ(3, op.child_count());
    ASSERT_EQ(wasp::VALUE, op.child_at(0).type());
    ASSERT_EQ(wasp::MULTIPLY, op.child_at(1).type());
    ASSERT_EQ(wasp::VALUE, op.child_at(2).type());
    auto result = interpreter.evaluate();
    ASSERT_TRUE(result.is_integer());
    ASSERT_TRUE(result.is_number());
    ASSERT_FALSE(result.is_real());
    ASSERT_FALSE(result.is_string());
    ASSERT_FALSE(result.is_error());
    ASSERT_EQ(24, result.integer());
}
TEST(ExprInterpreter,div)
{
    std::stringstream input;
    input <<"8 / 3"<<std::endl;
    ExprInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(5, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ(1, document.child_count() );
    auto op = document.child_at(0);
    ASSERT_EQ(wasp::DIVIDE, op.type());
    ASSERT_EQ(3, op.child_count());
    ASSERT_EQ(wasp::VALUE, op.child_at(0).type());
    ASSERT_EQ(wasp::DIVIDE, op.child_at(1).type());
    ASSERT_EQ(wasp::VALUE, op.child_at(2).type());
    auto result = interpreter.evaluate();
    ASSERT_TRUE(result.is_integer());
    ASSERT_TRUE(result.is_number());
    ASSERT_FALSE(result.is_real());
    ASSERT_FALSE(result.is_string());
    ASSERT_FALSE(result.is_error());
    ASSERT_EQ(2, result.integer());
}
TEST(ExprInterpreter,equal)
{
    std::stringstream input;
    input <<"8 == 3"<<std::endl;
    ExprInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(5, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ(1, document.child_count() );
    auto op = document.child_at(0);
    ASSERT_EQ(wasp::EQ, op.type());
    ASSERT_EQ(3, op.child_count());
    ASSERT_EQ(wasp::VALUE, op.child_at(0).type());
    ASSERT_EQ(wasp::EQ, op.child_at(1).type());
    ASSERT_EQ(wasp::VALUE, op.child_at(2).type());
}
TEST(ExprInterpreter,not_equal)
{
    std::stringstream input;
    input <<"8 != 3"<<std::endl;
    ExprInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(5, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ(1, document.child_count() );
    auto op = document.child_at(0);
    ASSERT_EQ(wasp::NEQ, op.type());
    ASSERT_EQ(3, op.child_count());
    ASSERT_EQ(wasp::VALUE, op.child_at(0).type());
    ASSERT_EQ(wasp::NEQ, op.child_at(1).type());
    ASSERT_EQ(wasp::VALUE, op.child_at(2).type());
}
TEST(ExprInterpreter,less_than)
{
    std::stringstream input;
    input <<"8 < 3"<<std::endl;
    ExprInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(5, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ(1, document.child_count() );
    auto op = document.child_at(0);
    ASSERT_EQ(wasp::LT, op.type());
    ASSERT_EQ(3, op.child_count());
    ASSERT_EQ(wasp::VALUE, op.child_at(0).type());
    ASSERT_EQ(wasp::LT, op.child_at(1).type());
    ASSERT_EQ(wasp::VALUE, op.child_at(2).type());
}
TEST(ExprInterpreter,less_than_eq)
{
    std::stringstream input;
    input <<"8 <= 3"<<std::endl;
    ExprInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(5, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ(1, document.child_count() );
    auto op = document.child_at(0);
    ASSERT_EQ(wasp::LTE, op.type());
    ASSERT_EQ(3, op.child_count());
    ASSERT_EQ(wasp::VALUE, op.child_at(0).type());
    ASSERT_EQ(wasp::LTE, op.child_at(1).type());
    ASSERT_EQ(wasp::VALUE, op.child_at(2).type());
}
TEST(ExprInterpreter,greater_than)
{
    std::stringstream input;
    input <<"8 > 3"<<std::endl;
    ExprInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(5, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ(1, document.child_count() );
    auto op = document.child_at(0);
    ASSERT_EQ(wasp::GT, op.type());
    ASSERT_EQ(3, op.child_count());
    ASSERT_EQ(wasp::VALUE, op.child_at(0).type());
    ASSERT_EQ(wasp::GT, op.child_at(1).type());
    ASSERT_EQ(wasp::VALUE, op.child_at(2).type());
}
TEST(ExprInterpreter,greater_than_eq)
{
    std::stringstream input;
    input <<"8 >= 3"<<std::endl;
    ExprInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(5, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ(1, document.child_count() );
    auto op = document.child_at(0);
    ASSERT_EQ(wasp::GTE, op.type());
    ASSERT_EQ(3, op.child_count());
    ASSERT_EQ(wasp::VALUE, op.child_at(0).type());
    ASSERT_EQ(wasp::GTE, op.child_at(1).type());
    ASSERT_EQ(wasp::VALUE, op.child_at(2).type());
}
TEST(ExprInterpreter,parenthesis)
{
    std::stringstream input;
    input <<" (8 > 3) "<<std::endl;
    ExprInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(8, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ(1, document.child_count() );
    auto op = document.child_at(0);
    ASSERT_EQ(wasp::PARENTHESIS, op.type());
    ASSERT_EQ(3, op.child_count());
    ASSERT_EQ(wasp::LPAREN, op.child_at(0).type());
    ASSERT_EQ(wasp::GT, op.child_at(1).type());
    ASSERT_EQ(wasp::RPAREN, op.child_at(2).type());
}
TEST(ExprInterpreter,unary_not)
{
    std::stringstream input;
    input <<" !(8 > 3) "<<std::endl;
    ExprInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(10, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ(1, document.child_count() );
    auto op = document.child_at(0);
    ASSERT_EQ(wasp::UNARY_NOT, op.type());
    ASSERT_EQ(2, op.child_count());
    ASSERT_EQ(wasp::BANG, op.child_at(0).type());
    ASSERT_EQ(wasp::PARENTHESIS, op.child_at(1).type());
}
TEST(ExprInterpreter,unary_minus)
{
    std::stringstream input;
    input <<" -(8 > 3) "<<std::endl;
    ExprInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(10, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ(1, document.child_count() );
    auto op = document.child_at(0);
    ASSERT_EQ(wasp::UNARY_MINUS, op.type());
    ASSERT_EQ(2, op.child_count());
    ASSERT_EQ(wasp::MINUS, op.child_at(0).type());
    ASSERT_EQ(wasp::PARENTHESIS, op.child_at(1).type());
}
TEST(ExprInterpreter,pos_scalar)
{
    std::stringstream input;
    input <<" 9 "<<std::endl;
    ExprInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(2, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ(1, document.child_count() );
    auto op = document.child_at(0);
    ASSERT_EQ(wasp::VALUE, op.type());
    ASSERT_EQ(0, op.child_count());
}
TEST(ExprInterpreter,neg_scalar)
{
    std::stringstream input;
    input <<" -9 "<<std::endl;
    ExprInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(4, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ(1, document.child_count() );
    auto op = document.child_at(0);
    ASSERT_EQ(wasp::UNARY_MINUS, op.type());
    ASSERT_EQ(2, op.child_count());
    ASSERT_EQ(wasp::MINUS, op.child_at(0).type());
    ASSERT_EQ(wasp::VALUE, op.child_at(1).type());
}
TEST(ExprInterpreter,combined)
{
    std::stringstream input;
    input <<" y = !(1+2 > -3*4/5^6)  "<<std::endl;
    ExprInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(27, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ(1, document.child_count() );
    auto op = document.child_at(0);
    ASSERT_EQ(wasp::KEYED_VALUE, op.type());
    ASSERT_EQ(3, op.child_count());
    ASSERT_EQ(wasp::DECL, op.child_at(0).type());
    ASSERT_EQ(wasp::ASSIGN, op.child_at(1).type());
    ASSERT_EQ(wasp::UNARY_NOT, op.child_at(2).type());
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

