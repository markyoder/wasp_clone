#include "waspddi/DDInterpreter.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>
using namespace wasp;

TEST(DDInterpreter,flat)
{
    std::stringstream input;
    input <<R"I( sect1
sect2 1
sect3 = 1
sect4 1.1
sect5 = 1.1
sect6 "ted"
sect7 = "ted"
sect8 = 1 2 3.4 "five"
sect9  1 2 3.4 "five"
)I"<<std::endl;
    DDIInterpreter<> ddi;
    ASSERT_TRUE( ddi.parse(input) );
    ddi.root().paths(std::cout);
}
