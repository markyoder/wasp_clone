#include "waspexpr/ExprInterpreter.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <cmath>
using namespace wasp;

template<typename T>
struct ScalarExprTest{
    std::string tst;
    T expected;
    ScalarExprTest(const std::string & tst, T expected)
        :tst(tst),expected(expected){}
};
template<typename V1, typename V2, typename T>
struct VariableExprTest{
    std::string tst;
    V1 v1;
    V2 v2;
    T expected;
    VariableExprTest(const std::string & tst, V1 v1, V2 v2, T expected)
        :tst(tst),v1(v1),v2(v2),expected(expected){}
};

TEST(ExprInterpreter, default_variables)
{
    std::vector<ScalarExprTest<double>> tests={
        {"pi",3.14159265359},
        {"e",2.718281828459}
    };
    ASSERT_FALSE( tests.empty() );
    for( auto & t : tests )
    {
        SCOPED_TRACE( t.tst );
        std::stringstream input;
        input <<t.tst;
        ExprInterpreter<> interpreter;
        interpreter.context().add_default_variables();
        ASSERT_TRUE(interpreter.parse(input) );

        auto result = interpreter.evaluate();
        ASSERT_FALSE(result.is_integer());
        ASSERT_TRUE(result.is_number());
        ASSERT_TRUE(result.is_real());
        ASSERT_FALSE(result.is_string());
        ASSERT_FALSE(result.is_bool());
        ASSERT_NEAR(t.expected, result.real(),1e-8);
    }
}
TEST(ExprInterpreter, default_functions)
{
    std::vector<ScalarExprTest<double>> tests={
        {"sin(pi)",0.0},
        {"sin(1.0)",0.8414709848},
        {"sin(1)",0.8414709848},
    };
    ASSERT_FALSE( tests.empty() );
    for( auto & t : tests )
    {
        SCOPED_TRACE( t.tst );
        std::stringstream input;
        input <<t.tst;
        ExprInterpreter<> interpreter;
        interpreter.context().add_default_functions();
        interpreter.context().add_default_variables();
        ASSERT_TRUE(interpreter.parse(input) );

        auto result = interpreter.evaluate();
        ASSERT_FALSE(result.is_integer());
        ASSERT_TRUE(result.is_number());
        ASSERT_TRUE(result.is_real());
        ASSERT_FALSE(result.is_string());
        ASSERT_FALSE(result.is_bool());
        ASSERT_NEAR(t.expected, result.real(),1e-8);
    }
}

TEST(ExprInterpreter,scalar_boolean)
{
    std::vector<ScalarExprTest<bool>> tests={

        // same negative numbers
         {"-1000000 <  -1000000", false}
        ,{"-1000000 <= -1000000", true}
        ,{"-1000000 >  -1000000", false}
        ,{"-1000000 >= -1000000", true}
        ,{"-1000000 == -1000000", true}
        ,{"-1000000 != -1000000", false}
        ,{"-1000000 || -1000000", true}
        ,{"-1000000 && -1000000", true}

        // same zero integer
        ,{"0 <  0", false}
        ,{"0 <= 0", true}
        ,{"0 >  0", false}
        ,{"0 >= 0", true}
        ,{"0 == 0", true}
        ,{"0 != 0", false}
        ,{"0 || 0", false}
        ,{"0 && 0", false}

        // same positive integer
       ,{"1000000 <  1000000", false}
       ,{"1000000 <= 1000000", true}
       ,{"1000000 >  1000000", false}
       ,{"1000000 >= 1000000", true}
       ,{"1000000 == 1000000", true}
       ,{"1000000 != 1000000", false}

        // positive different integers
        ,{"2 >  3", false}
        ,{"2 >= 3", false}
        ,{"2 <  3", true}
        ,{"2 <= 3", true}
        ,{"2 == 3", false}
        ,{"2 != 3", true}
        ,{"2 || 3", true}
        ,{"2 && 3", true}

        // negative different integers
        ,{"-2 >  -3", true}
        ,{"-2 >= -3", true}
        ,{"-2 <  -3", false}
        ,{"-2 <= -3", false}
        ,{"-2 == -3", false}
        ,{"-2 != -3", true}
        ,{"-2 || -3", true}
        ,{"-2 && -3", true}

        // mixed sign different integer
        ,{"2 >  -3", true}
        ,{"2 >= -3", true}
        ,{"2 <  -3", false}
        ,{"2 <= -3", false}
        ,{"2 == -3", false}
        ,{"2 != -3", true}
        ,{"2 || -3", true}
        ,{"2 && -3", true}

        // same zero real number
        ,{"0.0 <  0.0", false}
        ,{"0.0 <= 0.0", true}
        ,{"0.0 >  0.0", false}
        ,{"0.0 >= 0.0", true}
        ,{"0.0 == 0.0", true}
        ,{"0.0 != 0.0", false}
        ,{"0.0 || 0.0", false}
        ,{"0.0 && 0.0", false}

        // positive same reals
        ,{"3.33 <  3.33", false}
        ,{"3.33 <= 3.33", true}
        ,{"3.33 >  3.33", false}
        ,{"3.33 >= 3.33", true}
        ,{"3.33 == 3.33", true}
        ,{"3.33 != 3.33", false}
        ,{"3.33 || 3.33", true}
        ,{"3.33 && 3.33", true}

        // positive different reals
        ,{"0.33 <  3.33", true}
        ,{"0.33 <= 3.33", true}
        ,{"0.33 >  3.33", false}
        ,{"0.33 >= 3.33", false}
        ,{"0.33 == 3.33", false}
        ,{"0.33 != 3.33", true}
        ,{"0.33 || 3.33", true}
        ,{"0.33 && 3.33", true}

        // negative same reals
        ,{"-3.33 <  -3.33", false}
        ,{"-3.33 <= -3.33", true}
        ,{"-3.33 >  -3.33", false}
        ,{"-3.33 >= -3.33", true}
        ,{"-3.33 == -3.33", true}
        ,{"-3.33 != -3.33", false}
        ,{"-3.33 || -3.33", true}
        ,{"-3.33 && -3.33", true}

        // negative different reals
        ,{"-0.33 <  -3.33", false}
        ,{"-0.33 <= -3.33", false}
        ,{"-0.33 >  -3.33", true}
        ,{"-0.33 >= -3.33", true}
        ,{"-0.33 == -3.33", false}
        ,{"-0.33 != -3.33", true}
        ,{"-0.33 || -3.33", true}
        ,{"-0.33 && -3.33", true}

        // boolean algebra tables
        ,{"1==1 && 2==2",true} // true && true
        ,{"1==1 && 2==1",false} // true && false
        ,{"1==2 && 0==2",false} // false && false
        ,{"1==2 && 2==2",false} // false and true

        // cont'd
        ,{"1==1 || 2==2",true}
        ,{"1==1 || 2==1",true}
        ,{"1==2 || 0==2",false}
        ,{"1==2 || 2==2",true}

    };

    ASSERT_FALSE( tests.empty() );
    for( auto & t : tests )
    {
        SCOPED_TRACE( t.tst );
        std::stringstream input;
        input <<t.tst;
        ExprInterpreter<> interpreter;
        ASSERT_EQ( true, interpreter.parse(input) );

        auto result = interpreter.evaluate();
        ASSERT_FALSE(result.is_integer());
        ASSERT_FALSE(result.is_number());
        ASSERT_FALSE(result.is_real());
        ASSERT_FALSE(result.is_string());
        ASSERT_TRUE(result.is_bool());
        ASSERT_EQ(t.expected, result.boolean());
    }
}
TEST(ExprInterpreter,integer_variable_boolean)
{
    std::vector<VariableExprTest<int,int,bool>> tests={

        // same negative numbers
         {"x < y",-1000000,-1000000, false}
        ,{"x <= y",-1000000,-1000000, true}
        ,{"x >  y",-1000000,-1000000, false}
        ,{"x >= y",-1000000,-1000000, true}
        ,{"x == y",-1000000,-1000000, true}
        ,{"x != y",-1000000,-1000000, false}
        ,{"x || y",-1000000,-1000000, true}
        ,{"x && y",-1000000,-1000000, true}

        // same zero integer
        ,{"x <  y",0, 0,false}
        ,{"x <= y",0, 0,true}
        ,{"x >  y",0, 0,false}
        ,{"x >= y",0, 0,true}
        ,{"x == y",0, 0,true}
        ,{"x != y",0, 0,false}
        ,{"x || y",0, 0,false}
        ,{"x && y",0, 0,false}

        // same positive integer
       ,{"x <  y",1000000,1000000, false}
       ,{"x <= y",1000000,1000000, true}
       ,{"x >  y",1000000,1000000, false}
       ,{"x >= y",1000000,1000000, true}
       ,{"x == y",1000000,1000000, true}
       ,{"x != y",1000000,1000000, false}

        // positive different integers
        ,{"x >  y",2,3, false}
        ,{"x >= y",2,3, false}
        ,{"x <  y",2,3, true}
        ,{"x <= y",2,3, true}
        ,{"x == y",2,3, false}
        ,{"x != y",2,3, true}
        ,{"x || y",2,3, true}
        ,{"x && y",2,3, true}

        // negative different integers
        ,{"x >  y",-2,-3, true}
        ,{"x >= y",-2,-3, true}
        ,{"x <  y",-2,-3, false}
        ,{"x <= y",-2,-3, false}
        ,{"x == y",-2,-3, false}
        ,{"x != y",-2,-3, true}
        ,{"x || y",-2,-3, true}
        ,{"x && y",-2,-3, true}

        // mixed sign different integer
        ,{"x >  y",2, -3, true}
        ,{"x >= y",2, -3, true}
        ,{"x <  y",2, -3, false}
        ,{"x <= y",2, -3, false}
        ,{"x == y",2, -3, false}
        ,{"x != y",2, -3, true}
        ,{"x || y",2, -3, true}
        ,{"x && y",2, -3, true}

        // boolean algebra tables
        ,{"x==x && y==y",1,2,true} // true && true
        ,{"x==x && y==x",1,2,false} // true && false
        ,{"x==y && 0==y",1,2,false} // false && false
        ,{"x==y && y==y",1,2,false} // false and true

        // cont'd
        ,{"x==x || y==y",1,2,true}
        ,{"x==x || y==x",1,2,true}
        ,{"x==y || 0==y",1,2,false}
        ,{"x==y || y==y",1,2,true}
    };

    ASSERT_FALSE( tests.empty() );
    for( auto & t : tests )
    {
        SCOPED_TRACE( t.tst );
        std::stringstream input;
        input <<t.tst;
        ExprInterpreter<> interpreter;

        interpreter.context().store("x",t.v1);
        interpreter.context().store("y",t.v2);
        ASSERT_EQ( true, interpreter.parse(input) );

        auto result = interpreter.evaluate();
        ASSERT_FALSE(result.is_integer());
        ASSERT_FALSE(result.is_number());
        ASSERT_FALSE(result.is_real());
        ASSERT_FALSE(result.is_string());
        ASSERT_TRUE(result.is_bool());
        ASSERT_EQ(t.expected, result.boolean());
    }
}

TEST(ExprInterpreter,real_variable_boolean)
{
    std::vector<VariableExprTest<double,double,bool>> tests={
        // same zero real number
         {"x <  y",0.0,0.0, false}
        ,{"x <= y",0.0,0.0, true}
        ,{"x >  y",0.0,0.0, false}
        ,{"x >= y",0.0,0.0, true}
        ,{"x == y",0.0,0.0, true}
        ,{"x != y",0.0,0.0, false}
        ,{"x || y",0.0,0.0, false}
        ,{"x && y",0.0,0.0, false}

        // positive same reals
        ,{"x <  y",3.33,3.33, false}
        ,{"x <= y",3.33,3.33, true}
        ,{"x >  y",3.33,3.33, false}
        ,{"x >= y",3.33,3.33, true}
        ,{"x == y",3.33,3.33, true}
        ,{"x != y",3.33,3.33, false}
        ,{"x || y",3.33,3.33, true}
        ,{"x && y",3.33,3.33, true}

        // positive different reals
        ,{"x <  y",0.33,3.33, true}
        ,{"x <= y",0.33,3.33, true}
        ,{"x >  y",0.33,3.33, false}
        ,{"x >= y",0.33,3.33, false}
        ,{"x == y",0.33,3.33, false}
        ,{"x != y",0.33,3.33, true}
        ,{"x || y",0.33,3.33, true}
        ,{"x && y",0.33,3.33, true}

        // negative same reals
        ,{"x <  y",-3.33,-3.33, false}
        ,{"x <= y",-3.33,-3.33, true}
        ,{"x >  y",-3.33,-3.33, false}
        ,{"x >= y",-3.33,-3.33, true}
        ,{"x == y",-3.33,-3.33, true}
        ,{"x != y",-3.33,-3.33, false}
        ,{"x || y",-3.33,-3.33, true}
        ,{"x && y",-3.33,-3.33, true}

        // negative different reals
        ,{"x <  y",-0.33,-3.33, false}
        ,{"x <= y",-0.33,-3.33, false}
        ,{"x >  y",-0.33,-3.33, true}
        ,{"x >= y",-0.33,-3.33, true}
        ,{"x == y",-0.33,-3.33, false}
        ,{"x != y",-0.33,-3.33, true}
        ,{"x || y",-0.33,-3.33, true}
        ,{"x && y",-0.33,-3.33, true}
    };
    ASSERT_FALSE( tests.empty() );
    for( auto & t : tests )
    {
        SCOPED_TRACE( t.tst );
        std::stringstream input;
        input <<t.tst;
        ExprInterpreter<> interpreter;

        interpreter.context().store("x",t.v1);
        interpreter.context().store("y",t.v2);
        ASSERT_EQ( true, interpreter.parse(input) );

        auto result = interpreter.evaluate();
        ASSERT_FALSE(result.is_integer());
        ASSERT_FALSE(result.is_number());
        ASSERT_FALSE(result.is_real());
        ASSERT_FALSE(result.is_string());
        ASSERT_TRUE(result.is_bool());
        ASSERT_EQ(t.expected, result.boolean());
    }
}
TEST(ExprInterpreter,mixed_numeric_variable_boolean)
{
    std::vector<VariableExprTest<int,double,bool>> tests={
        // same zero number
         {"x <  y",0,0.0, false}
        ,{"x <= y",0,0.0, true}
        ,{"x >  y",0,0.0, false}
        ,{"x >= y",0,0.0, true}
        ,{"x == y",0,0.0, true}
        ,{"x != y",0,0.0, false}
        ,{"x || y",0,0.0, false}
        ,{"x  && y",0,0.0, false}

        // positive same number
        ,{"x <  y",3,3.00, false}
        ,{"x <= y",3,3.00, true}
        ,{"x >  y",3,3.00, false}
        ,{"x >= y",3,3.00, true}
        ,{"x == y",3,3.00, true}
        ,{"x != y",3,3.00, false}
        ,{"x || y",3,3.00, true}
        ,{"x &&  y",3,3.00, true}

        // positive different numbers
        ,{"x <  y",0,3.33, true}
        ,{"x <= y",0,3.33, true}
        ,{"x >  y",0,3.33, false}
        ,{"x >= y",0,3.33, false}
        ,{"x == y",0,3.33, false}
        ,{"x != y",0,3.33, true}
        ,{"x || y",0,3.33, true}
        ,{"x  &&  y",0,3.33, false}

        // negative same number
        ,{"x <  y",-3,-3.00, false}
        ,{"x <= y",-3,-3.00, true}
        ,{"x >  y",-3,-3.00, false}
        ,{"x >= y",-3,-3.00, true}
        ,{"x == y",-3,-3.00, true}
        ,{"x != y",-3,-3.00, false}
        ,{"x || y",-3,-3.00, true}
        ,{"x&&y",-3,-3.00, true}

        // negative different numbers
        ,{"x <  y",-0,-3.33, false}
        ,{"x <= y",-0,-3.33, false}
        ,{"x >  y",-0,-3.33, true}
        ,{"x >= y",-0,-3.33, true}
        ,{"x == y",-0,-3.33, false}
        ,{"x != y",-0,-3.33, true}
        ,{"x || y",-0,-3.33, true}
        ,{"x && y",-0,-3.33, false}
    };
    ASSERT_FALSE( tests.empty() );
    for( auto & t : tests )
    {
        SCOPED_TRACE( t.tst );
        std::stringstream input;
        input <<t.tst;
        ExprInterpreter<> interpreter;

        interpreter.context().store("x",t.v1);
        interpreter.context().store("y",t.v2);
        ASSERT_EQ( true, interpreter.parse(input) );

        auto result = interpreter.evaluate();
        ASSERT_FALSE(result.is_integer());
        ASSERT_FALSE(result.is_number());
        ASSERT_FALSE(result.is_real());
        ASSERT_FALSE(result.is_string());
        ASSERT_TRUE(result.is_bool());
        ASSERT_EQ(t.expected, result.boolean());
    }
}
TEST(ExprInterpreter,scalar_integer)
{

    for( int i = -2500, count = 0; count < 5000; ++count,i=-2500+count  )
    {
        SCOPED_TRACE( i );
        std::stringstream input;
        input <<"result="<<i<<"^2"; // exponentiation is higher precendence than unary minus
        ExprInterpreter<> interpreter;
        ASSERT_EQ( true, interpreter.parse(input) );

        auto result = interpreter.evaluate();
        ASSERT_TRUE(result.is_integer());
        ASSERT_TRUE(result.is_number());
        ASSERT_FALSE(result.is_real());
        ASSERT_FALSE(result.is_string());
        ASSERT_FALSE(result.is_bool());
        int expected = i > 0 ? std::pow(i,2) : -std::pow(i,2);
        ASSERT_EQ(expected, result.integer());
        ASSERT_EQ(expected, interpreter.context().variable("result")->integer());
    }
}

TEST(ExprInterpreter,DISABLED_scalar_real)
{

    for( double i = -50.1, count = 0; count < 100; ++count,i=-50.1+count  )
    {
        SCOPED_TRACE( i );
        std::stringstream input;
        input <<"result=("<<i<<"-15)*3"; // exponentiation is higher precendence than unary minus
        ExprInterpreter<> interpreter;
        std::cout<<input.str()<<std::endl;
        ASSERT_EQ( true, interpreter.parse(input) );

        auto result = interpreter.evaluate();
        ASSERT_FALSE(result.is_integer());
        ASSERT_TRUE(result.is_number());
        ASSERT_TRUE(result.is_real());
        ASSERT_FALSE(result.is_string());
        ASSERT_FALSE(result.is_bool());
        float expected = (i-15.0)*3;
        ASSERT_NEAR(expected, result.real(),1e-10);
        ASSERT_NEAR(expected, interpreter.context().variable("result")->real()
                    ,1e-10);
    }
}

TEST(ExprInterpreter,string_concat)
{

    std::vector<ScalarExprTest<std::string>> tests={
        {"'x'+'y'","xy"}
        ,{"\"x\"+\"y\"","xy"}
        ,{"'x'+'y'+' z '","xy z "}
        ,{"'x'+'y'+(' z ')","xy z "}
        ,{"3+'y'+' z '","3y z "}
        ,{"'y'+3+' z '","y3 z "}
        ,{"3/'y'+' z '","3/y z "}
        ,{"'y'+3/' z '","y3/ z "}
        ,{"3 - 'y' +' z '","3-y z "}
        ,{"'y' + 3 - ' z '","y3- z "}
    };
    for( auto t : tests )
    {
        SCOPED_TRACE( t.tst );
        std::stringstream input;
        input <<t.tst;
        ExprInterpreter<> interpreter;
        ASSERT_EQ( true, interpreter.parse(input) );

        auto result = interpreter.evaluate();
        ASSERT_FALSE(result.is_integer());
        ASSERT_FALSE(result.is_number());
        ASSERT_FALSE(result.is_real());
        ASSERT_TRUE(result.is_string());
        ASSERT_FALSE(result.is_bool());
        ASSERT_EQ(t.expected, result.string());
    }
}
