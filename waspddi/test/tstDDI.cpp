#include "waspddi/DDInterpreter.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>
using namespace wasp;

TEST(DDInterpreter,flat)
{
    std::stringstream input;
    input <<R"I( section1
section2 1
section3 = 1
section4 1.1
section4 = 1.1
section5 "ted"
section5 = "ted"
sectionx = 1 2 3.4 "five"
sectionx  1 2 3.4 "five"
)I"<<std::endl;
    DDIInterpreter<> ddi;
    ASSERT_TRUE( ddi.parse(input) );
    ddi.root().paths(std::cout);
}
