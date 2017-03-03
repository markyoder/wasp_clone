#include "waspddi/DDInterpreter.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>
using namespace wasp;

TEST(DDInterpreter,passing_flat)
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
    DDInterpreter<> ddi;
    ddi.definition()->create("sect1");
    ddi.definition()->create("sect2");
    ddi.definition()->create("sect3");
    ddi.definition()->create("sect4");
    ddi.definition()->create("sect5");
    ddi.definition()->create("sect6");
    ddi.definition()->create("sect7");
    ddi.definition()->create("sect8");
    ddi.definition()->create("sect9");
    ASSERT_TRUE( ddi.parse(input) );
    std::stringstream expected;
expected<<R"I(/
/sect1
/sect1/decl (sect1)
/sect2
/sect2/decl (sect2)
/sect2/value (1)
/sect3
/sect3/decl (sect3)
/sect3/= (=)
/sect3/value (1)
/sect4
/sect4/decl (sect4)
/sect4/value (1.1)
/sect5
/sect5/decl (sect5)
/sect5/= (=)
/sect5/value (1.1)
/sect6
/sect6/decl (sect6)
/sect6/value ("ted")
/sect7
/sect7/decl (sect7)
/sect7/= (=)
/sect7/value ("ted")
/sect8
/sect8/decl (sect8)
/sect8/= (=)
/sect8/value (1)
/sect8/value (2)
/sect8/value (3.4)
/sect8/value ("five")
/sect9
/sect9/decl (sect9)
/sect9/value (1)
/sect9/value (2)
/sect9/value (3.4)
/sect9/value ("five"))I";
    std::stringstream paths;
    ddi.root().paths(paths);
}


/**
 * @brief TEST ensures that an unknown section produces an expected error
 * Specifically tests unknown in 'decl values' logic
 */
TEST(DDInterpreter,failing_decl_values)
{
    std::stringstream input;
    input <<R"I( sect1
sect_eek 1
)I"<<std::endl;
    std::stringstream errors;
    DDInterpreter<> ddi(errors);
    ddi.definition()->create("sect1");

    EXPECT_FALSE( ddi.parse(input) );
    std::string msg = "stream input:2.1-8: 'sect_eek' is unknown.";
    ASSERT_EQ(msg, errors.str());

}
/**
 * @brief TEST ensures that an unknown section produces an expected error
 * Specifically tests unknown in 'decl' logic
 */
TEST(DDInterpreter,failing_decl)
{
    std::stringstream input;
    input <<R"I( sect1
 sect_eek
)I"<<std::endl;
    std::stringstream errors;
    DDInterpreter<> ddi(errors);
    ddi.definition()->create("sect1");

    EXPECT_FALSE( ddi.parse(input) );
    std::string msg = "stream input:2.2-9: 'sect_eek' is unknown.";
    ASSERT_EQ(msg, errors.str());

}
