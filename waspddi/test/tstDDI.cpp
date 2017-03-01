#include "waspddi/DDInterpreter.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>
using namespace wasp;

TEST(DDInterpreter,simple)
{
    std::stringstream input;
    input <<"level1 level1.1"<<std::endl;
    DDIInterpreter<> ddi;
    ASSERT_TRUE( ddi.parse(input) );
    ddi.root().paths(std::cout);
}
