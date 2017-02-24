#include "waspexpr/ExprInterpreter.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>
using namespace wasp;

template<typename T>
struct ScalarExprTest{
    std::string tst;
    T expected;
    ScalarExprTest(const std::string & tst, T expected)
        :tst(tst),expected(expected){}
};
template<typename V,typename T>
struct VariableExprTest{
    std::string tst;
    V var;
    T expected;
    VariableExprTest(const std::string & tst, V var, T expected)
        :tst(tst),var(var),expected(expected){}
};
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
