/*
 * File:   tstHalite.cpp
 * Author: Robert A. Lefebvre
 */

#include <cstdlib>
#include <cstdio> // std::remove(file_name)
#include <sstream>
#include <string>
#include <stdexcept>
#include <functional>
#include "wasphalite/HaliteInterpreter.h"
#include "wasphalite/DataAccessor.h"
#include "waspcore/Object.h"

#include "gtest/gtest.h"
using namespace std;
using namespace wasp;


TEST(Halite, range_errors)
{
    std::vector<std::string> expected_error =
    {
      "no range start was specified for 'x'"
        ,"unable to extract range start for 'x'" // no ',' or ';'
        ,"unable to extract delimited range start for 'x'" // delimited by ',' or ';'
        ,"unable to extract delimited range start for 'x'" // delimited by ',' or ';'
        ,"no range end was specified for 'x'"
        ,"unable to extract range end for 'x'" // no ',' or ';'
        ,"unable to extract delimited range end for 'x'" // nothing between ',' or ';'
        ,"unable to extract delimited range end for 'x'" // nothing between ',' or ';'
        ,"no range stride was specified for 'x'"
        ,"unable to extract range stride for 'x'" // no ',' or ';'
        ,"unable to extract delimited range stride for 'x'" // delimited by ';'
    };
    std::vector<std::string> ranges =
    {
        " x="
        ,"x = "
        ,"x = ,"
        ,"x = ;"
        ,"x = 1,"
        ,"x = 1, "
        ,"x = 1, ,"
        ,"x = 1, ;"
        ,"x = 1, 2,"
        ,"x = 1, 2, ,"
        ,"x = 1, 3,;"
    };
    ASSERT_EQ( expected_error.size(), ranges.size() );
    for( size_t i = 0; i < expected_error.size(); ++i ){
        SCOPED_TRACE(expected_error[i]);
        SCOPED_TRACE(ranges[i]);
        std::vector<HaliteInterpreter<>::Range> imports;
        std::string range = ranges[i];
        std::string error;
        EXPECT_FALSE( HaliteInterpreter<>::extract_ranges(range,imports, error));
        std::cout<<error<<std::endl;
        ASSERT_EQ(expected_error[i], error);
    }
}

TEST( Halite,attribute_range_errors)
{
    std::vector<std::string> ranges =
    {
        "<x:x=>"
        ,"<x:x = >"
        ,"\n\n<x:x = ,>"
        ,"<x:x = ;>"
        ,"<x:x = 1,>"
        ,"<x:x = 1, >"
        ,"<x:x = 1, ,>"
        ,"<x:x = 1, ;>"
        ,"<x:x = 1, 2,>"
        ,"<x:x = 1, 2, ,>"
        ,"<x:x = 1, 3,;>"
    };
    std::vector<std::string> expected_error =
    {
      "no range start was specified for 'x'."
        ,"no range start was specified for 'x'."
        ,"unable to extract delimited range start for 'x'." // delimited by ',' or ';'
        ,"unable to extract delimited range start for 'x'." // delimited by ',' or ';'
        ,"no range end was specified for 'x'."
        ,"no range end was specified for 'x'." // no ',' or ';'
        ,"unable to extract delimited range end for 'x'." // nothing between ',' or ';'
        ,"unable to extract delimited range end for 'x'." // nothing between ',' or ';'
        ,"no range stride was specified for 'x'."
        ,"unable to extract range stride for 'x'." // no ',' or ';'
        ,"unable to extract delimited range stride for 'x'." // delimited by ';'
    };
    ASSERT_EQ(expected_error.size(), ranges.size());
    for(size_t i = 0; i < ranges.size(); ++i)
    {
        const std::string & t = ranges[i];
        const std::string & e = expected_error[i];
        SCOPED_TRACE(t);
        SCOPED_TRACE(e);
        std::stringstream input;
        input<<t;
        std::stringstream errors;
        HaliteInterpreter<> interpreter(errors);
        // TODO - these should really be parse errors
        ASSERT_TRUE( interpreter.parse(input) );

        std::stringstream out;
        DataAccessor data;
        ASSERT_FALSE( interpreter.evaluate(out,data) );
        ASSERT_EQ("***Error: unable to acquire attribute options on line 1; "+e+"\n", errors.str() );
    }
}
