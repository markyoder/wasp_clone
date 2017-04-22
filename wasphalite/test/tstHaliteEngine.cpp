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

TEST( Halite, single_attribute)
{
    std::stringstream input;
    input<< R"INPUT(<attribute>)INPUT";
    HaliteInterpreter<> interpreter;
    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataAccessor data;
    data.store("attribute",std::string("value")); // need explicit string type
    ASSERT_EQ( Context::Type::STRING, data.type("attribute") );
    ASSERT_TRUE( interpreter.evaluate(out,data) );
    ASSERT_EQ( "value", out.str() );
}
TEST( Halite, single_quoted_attribute)
{
    std::stringstream input;
    input<< R"INPUT(<'attr with space( )'>)INPUT";
    HaliteInterpreter<> interpreter;
    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataAccessor data;
    data.store("attr with space( )",std::string("value")); // need explicit string type
    ASSERT_EQ( Context::Type::STRING, data.type("attr with space( )") );
    ASSERT_TRUE( interpreter.evaluate(out,data) );
    ASSERT_EQ( "value", out.str() );
}
TEST( Halite, single_abscent_optional_attribute)
{
    std::stringstream input;
    input<< R"INPUT(b<attribute:?>a)INPUT";
    HaliteInterpreter<> interpreter;
    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataAccessor data;
    ASSERT_TRUE( interpreter.evaluate(out,data) );
    ASSERT_EQ( "ba", out.str() );
}
TEST( Halite, single_present_optional_attribute)
{
    std::stringstream input;
    input<< R"INPUT(b<attribute:?>a)INPUT";
    HaliteInterpreter<> interpreter;
    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataAccessor data;
    data.store("attribute",3.14159);
    ASSERT_TRUE( interpreter.evaluate(out,data) );
    ASSERT_EQ( "b3.14159a", out.str() );
}
TEST( Halite, single_silent_attribute)
{
    std::stringstream input;
    input<< R"INPUT(b<attribute=4:|>a)INPUT";
    HaliteInterpreter<> interpreter;
    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataAccessor data;

    ASSERT_TRUE( interpreter.evaluate(out,data) );
    ASSERT_EQ( Context::Type::INTEGER, data.type("attribute"));
    ASSERT_EQ( 4, data.integer("attribute") );
    ASSERT_EQ( "ba", out.str() );
}
TEST( Halite, single_present_formatted_optional_attribute)
{
    std::stringstream input;
    input<< R"INPUT(b<attribute:?fmt=%6.2f>a)INPUT";
    HaliteInterpreter<> interpreter;
    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataAccessor data;
    data.store("attribute",3.14159);
    ASSERT_TRUE( interpreter.evaluate(out,data) );
    ASSERT_EQ( "b  3.14a", out.str() );
}
TEST( Halite, formatted_single_attribute)
{
    std::stringstream input;
    input<< R"INPUT(<pi:fmt=rounded=%12.8f>
<pi>)INPUT";
    HaliteInterpreter<> interpreter;
    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataAccessor data; data.add_default_variables();
    ASSERT_TRUE( interpreter.evaluate(out,data) );
    ASSERT_EQ( "rounded=  3.14159265\n3.14159", out.str() );
}
TEST( Halite, iterative_formatted_attribute_only_start)
{
    std::stringstream input;
    input<< R"INPUT(<i:fmt=rounded=%3d; i=1>)INPUT";
    HaliteInterpreter<> interpreter;
    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataAccessor data;
    ASSERT_TRUE( interpreter.evaluate(out,data) );
    ASSERT_EQ( "rounded=  1", out.str() );
}
TEST( Halite, iterative_formatted_attribute_embedded)
{
    std::stringstream input;
    input<< R"INPUT(<i:fmt=%3d; i=<start>,<end>>)INPUT";
    HaliteInterpreter<> interpreter;
    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataAccessor data;
    data.store("start",1);
    data.store("end",2);
    ASSERT_TRUE( interpreter.evaluate(out,data) );
    ASSERT_EQ( "  1   2", out.str() );
}
TEST( Halite, iterative_formatted_attribute_only_start_end)
{
    std::stringstream input;
    // default separator is a whitespace making %2 behave like %3
    input<< R"INPUT(<i:fmt=%2d; i=1,3>)INPUT";
    HaliteInterpreter<> interpreter;
    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataAccessor data;
    ASSERT_TRUE( interpreter.evaluate(out,data) );
    ASSERT_EQ( " 1  2  3", out.str() );
}
TEST( Halite, iterative_formatted_attribute)
{
    std::stringstream input;
    // default separator is a whitespace making %2 behave like %3
    input<< R"INPUT(<i:fmt=%2d; i=1,3,2>)INPUT";
    HaliteInterpreter<> interpreter;
    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataAccessor data;
    ASSERT_TRUE( interpreter.evaluate(out,data) );
    ASSERT_EQ( " 1  3", out.str() );
}
TEST( Halite, iterative_formatted_attribute_sep)
{
    std::stringstream input;
    // default separator is a whitespace making %2 behave like %3
    input<< R"INPUT(<i:fmt=%2d;i=1,3,2;sep=,>)INPUT";
    HaliteInterpreter<> interpreter;
    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataAccessor data;
    ASSERT_TRUE( interpreter.evaluate(out,data) );
    ASSERT_EQ( " 1, 3", out.str() );
}
TEST( Halite, iterative_formatted_sep_attribute)
{
    std::stringstream input;
    // default separator is a whitespace making %2 behave like %3
    input<< R"INPUT(<i:fmt=%2d;sep=s;i=1,3,2;>)INPUT";
    HaliteInterpreter<> interpreter;
    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataAccessor data;
    ASSERT_TRUE( interpreter.evaluate(out,data) );
    ASSERT_EQ( " 1s 3", out.str() );
}
TEST( Halite, iterative_formatted_sep_first_attribute)
{
    std::stringstream input;
    // default separator is a whitespace making %2 behave like %3
    input<< R"INPUT(<i:sep=*;fmt=%2d;i=1,3,2;>)INPUT";
    HaliteInterpreter<> interpreter;
    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataAccessor data;
    ASSERT_TRUE( interpreter.evaluate(out,data) );
    ASSERT_EQ( " 1* 3", out.str() );
}
TEST( Halite, iterative_formatted_attribute_multi_only_start)
{
    std::stringstream input;
    // default separator is a whitespace making %2 behave like %3
    input<< R"INPUT(<i*j:j=3; fmt=%2d; i=1,3,2>)INPUT";
    HaliteInterpreter<> interpreter;
    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataAccessor data;
    ASSERT_TRUE( interpreter.evaluate(out,data) );
    ASSERT_EQ( " 3  9", out.str() );
}
TEST( Halite, iterative_formatted_attribute_multi_only_start_end)
{
    std::stringstream input;
    // default separator is a whitespace making %2 behave like %3
    input<< R"INPUT(<i*j: j=3,5; i=1,3,2; fmt=%2d; >)INPUT";
    HaliteInterpreter<> interpreter;
    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataAccessor data;
    ASSERT_TRUE( interpreter.evaluate(out,data) );

    ASSERT_EQ( " 3  9  4 12  5 15", out.str() );
}
TEST( Halite, indirect_attribute)
{
    std::stringstream input;
    input<< R"INPUT(<<attr>> <<what>.<member>>)INPUT";
    HaliteInterpreter<> interpreter;
    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataObject o;
    DataAccessor data(&o);
    o["attr"]=std::string("what");
    o["what"]=std::string("obj");
    o["member"]=std::string("x");
    o["obj.x"]=3.14159;
    ASSERT_TRUE( interpreter.evaluate(out,data) );
    ASSERT_EQ( "obj 3.14159", out.str() );
}
TEST( Halite, static_text)
{
    std::stringstream input;
    input<< R"INPUT(This is plain test
line2

 line3
   line
            )INPUT";
    HaliteInterpreter<> interpreter;
    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataAccessor data;
    ASSERT_TRUE( interpreter.evaluate(out,data) );
    ASSERT_EQ( input.str(), out.str() );
}
TEST( Halite, parameterized_text )
{
    std::stringstream input;
    input<< R"INPUT(This is plain test
 < pi >  <pi>
 <pi>
   line
            )INPUT";
    std::stringstream expected;
    expected<< R"INPUT(This is plain test
 3.14159  3.14159
 3.14159
   line
            )INPUT";
    HaliteInterpreter<> interpreter;
    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataAccessor data; data.add_default_variables();
    ASSERT_TRUE( interpreter.evaluate(out,data) );
    ASSERT_EQ( expected.str(), out.str() );
}

TEST( Halite, array_access )
{
    std::stringstream input;
    input<< R"INPUT( <var> "<str[0]>" <str[1]>
<int[0]> <int[1]>
 <double[0]> <double[1]>
<bool[0]> <bool[1]>

<mixed[0]> <mixed[1]> <mixed[2]:fmt=%.6f> <mixed[3]>
<mixed[i]:i=0,<size(mixed)-1>>
)INPUT";
    std::stringstream expected;
    expected<< R"INPUT( 1 "ted" fed
10 20
 1.1 3.14159
0 1

0 19 500.123123 dead ted
0 19 500.123 dead ted)INPUT";
    HaliteInterpreter<> interpreter;
    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataObject o;
    DataAccessor data(&o);
    o["var"] = true;
    o["str"] = DataArray();
    o["str"][0] = "ted";
    o["str"][1] = "fed";
    o["int"] = DataArray();
    o["int"][0] = 10;
    o["int"][1] = 20;
    o["double"] = DataArray();
    o["double"][0] = 1.1;
    o["double"][1] = 3.14159;
    o["bool"] = DataArray();
    o["bool"][0] = false;
    o["bool"][1] = true;

    o["mixed"] = DataArray();
    o["mixed"][0] = false;
    o["mixed"][1] = 19;
    o["mixed"][2] = 500.123123;
    o["mixed"][3] = std::string("dead ted");
    ASSERT_TRUE( interpreter.evaluate(out,data) );
    ASSERT_EQ( expected.str(), out.str() );
}
/**
 * @brief test attribute acquisition using DataAccessor layer
 */
TEST( Halite, parameterized_text_data_accessed )
{
    std::stringstream input;
    input<< R"INPUT(This is plain test
 < ted >  <fred>
 <x>
   line
            )INPUT";
    std::stringstream expected;
    expected<< R"INPUT(This is plain test
 wombat  3.14159
 2
   line
            )INPUT";
    HaliteInterpreter<> interpreter;
    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataObject o;
    DataAccessor data(&o);
    o["ted"] = "wombat";
    o["fred"] = 3.14159;
    o["x"] = 2;
    ASSERT_TRUE( interpreter.evaluate(out,data) );
    ASSERT_EQ( expected.str(), out.str() );
}

/**
 * @brief test attribute usage from nested template
 * This ensures the data layer is properly propogated
 * to the nested halite engine
 */
TEST( Halite, attributed_text_fileimport)
{

    std::ofstream import("nested parameterized template.tmpl");
    std::stringstream content;
    content<<"this is"<<std::endl
         <<"nested files using <ted>"<<std::endl
        <<std::endl // empty line
       <<"and assigning fred to < fred = x >"; // missing new line
    import<<content.str();
    import.close();
    std::stringstream input;
    input<< R"INPUT(#import ./nested parameterized template.tmpl
<ted> has <fred> brothers)INPUT";
    HaliteInterpreter<> interpreter;

    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataObject o;
    DataAccessor data(&o);
    o["ted"] = "wombat";
    o["fred"] = 3.14159;
    ASSERT_EQ( Value::TYPE_STRING, o["ted"].type() );
    ASSERT_EQ( Value::TYPE_DOUBLE, o["fred"].type() );
    o["x"] = 2;
    ASSERT_TRUE( interpreter.evaluate(out,data) );

    std::stringstream expected;
    expected<< R"INPUT(this is
nested files using wombat

and assigning fred to 2
wombat has 2 brothers)INPUT";
    ASSERT_EQ( expected.str(), out.str() );
    std::remove("nested parameterized template.tmpl");
    ASSERT_EQ( Value::TYPE_INTEGER, o["fred"].type() );
    ASSERT_EQ( 2, o["fred"].to_int() );
}

/**
 * @brief test file repeat (single) iteration
 */
TEST( Halite, repeat_fileimport)
{

    std::ofstream import("nested template.tmpl");
    std::stringstream content;
    content<<"this is"<<std::endl
         <<"nested files using nothing"<<std::endl
        <<std::endl // empty line
       <<"and assigning fred to < fred = 3.14159 >";
    import<<content.str();
    import.close();
    std::stringstream input;
    input<< R"INPUT(
            Some preceeding text
#repeat ./nested template.tmpl
no iteration. Fred = <fred>)INPUT";
    HaliteInterpreter<> interpreter;

    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataObject o;
    DataAccessor data(&o);
    ASSERT_TRUE( interpreter.evaluate(out,data) );

    std::stringstream expected;
    expected<< R"INPUT(
            Some preceeding text
this is
nested files using nothing

and assigning fred to 3.14159
no iteration. Fred = 3.14159)INPUT";
    ASSERT_EQ( expected.str(), out.str() );
    std::remove("nested template.tmpl");
    ASSERT_EQ( Value::TYPE_DOUBLE, o["fred"].type() );
    ASSERT_EQ( 3.14159, o["fred"].to_double() );
}
TEST(Halite, range)
{
    std::vector<HaliteInterpreter<>::Range> expected_imports =
    {
        {"x",1,1,1}
        ,{"x",1,1,1}
        ,{"x",1,2,1}
        ,{"x",1,2,1}
        ,{"x",1,3,2}
        ,{"x",6,6,1}
    };
    std::vector<std::string> ranges =
    {
        " x=1"
        ,"x = 1"
        ," x=1,2"
        ," x = 1 , 2 "
        ," x = 1 , 3, 2 "
        ," x = 6"
    };
    ASSERT_EQ( expected_imports.size(), ranges.size() );
    for( size_t i = 0; i < expected_imports.size(); ++i ){
        SCOPED_TRACE(i);
        SCOPED_TRACE(ranges[i]);
        std::vector<HaliteInterpreter<>::Range> imports;
        std::string range = ranges[i];
        std::string error;
        EXPECT_TRUE( HaliteInterpreter<>::extract_ranges(range,imports, error));
        std::cout<<error<<std::endl;
        ASSERT_FALSE( imports.empty() );
        EXPECT_EQ( expected_imports[i].name, imports.front().name );
        EXPECT_EQ( expected_imports[i].start, imports.front().start );
        EXPECT_EQ( expected_imports[i].end, imports.front().end);
        EXPECT_EQ( expected_imports[i].stride, imports.front().stride);
    }

}
TEST(Halite, multi_range)
{
    std::vector<std::vector<HaliteInterpreter<>::Range>> expected_imports =
    {
        {{"x",1,1,1},{"y",1,1,1}}
        ,{{"x",1,2,1},{"y",2,2,1}}
        ,{{"x",1,2,3},{"y",3,3,1}}
        ,{{"x",1,2,1},{"y",4,5,1}}
        ,{{"x",1,3,2},{"y",6,12,3}}
        ,{{"x",1,3,2},{"y",7,7,1},{"z",3,3,1}}
    };
    std::vector<std::string> ranges =
    {
        " x=1;y=1"
        ,"x = 1,2;y=2"
        ," x=1,2,3;y=3"
        ," x = 1 , 2 ; y = 4, 5"
        ," x = 1 , 3, 2 ; y= 6, 12, 3"
        ," x = 1 , 3, 2 ; y = 7; z=3"
    };
    ASSERT_EQ( expected_imports.size(), ranges.size() );
    for( size_t i = 0; i < expected_imports.size(); ++i ){
        SCOPED_TRACE(i);
        SCOPED_TRACE(ranges[i]);
        std::vector<HaliteInterpreter<>::Range> imports;
        std::string range = ranges[i];
        std::string error;
        EXPECT_TRUE( HaliteInterpreter<>::extract_ranges(range,imports, error));
        std::cout<<error<<std::endl;
        ASSERT_FALSE( imports.empty() );
        ASSERT_EQ( expected_imports[i].size(), imports.size() );

        for( size_t j = 0; j < expected_imports[i].size(); ++j )
        {
        EXPECT_EQ( expected_imports[i][j].name, imports[j].name );
        EXPECT_EQ( expected_imports[i][j].start, imports[j].start );
        EXPECT_EQ( expected_imports[i][j].end, imports[j].end);
        EXPECT_EQ( expected_imports[i][j].stride, imports[j].stride);
        }
    }
}
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

/**
 * @brief test file repeat (single) iteration
 */
TEST( Halite, repeat_fileimport_using_single_range)
{

    std::ofstream import("nested repeated template.tmpl");
    std::stringstream content;
    content<<"i=<i>";
    import<<content.str();
    import.close();
    std::stringstream input;
    input<< R"INPUT(
            Some preceeding text
#repeat ./nested repeated template.tmpl using i=1,3

text that follows)INPUT";
    HaliteInterpreter<> interpreter;

    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataObject o;
    DataAccessor data(&o);
    ASSERT_TRUE( interpreter.evaluate(out,data) );

    std::stringstream expected;
    expected<< R"INPUT(
            Some preceeding text
i=1
i=2
i=3

text that follows)INPUT";
    ASSERT_EQ( expected.str(), out.str() );
    std::remove("nested repeated template.tmpl");
}
/**
 * @brief test file repeat (single) iteration
 */
TEST( Halite, repeat_fileimport_using_multiple_range)
{

    std::ofstream import("nested repeated template.tmpl");
    std::stringstream content;
    content<<"i=<i> j=<j> k=<k>";
    import<<content.str();
    import.close();
    std::stringstream input;
    input<< R"INPUT(
            Some preceeding text
#repeat ./nested repeated template.tmpl using i=1,3; j=1,1; k=0,2,2

text that follows)INPUT";
    HaliteInterpreter<> interpreter;

    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataObject o;
    DataAccessor data(&o);
    ASSERT_TRUE( interpreter.evaluate(out,data) );

    std::stringstream expected;
    expected<< R"INPUT(
            Some preceeding text
i=1 j=1 k=0
i=1 j=1 k=2
i=2 j=1 k=0
i=2 j=1 k=2
i=3 j=1 k=0
i=3 j=1 k=2

text that follows)INPUT";
    ASSERT_EQ( expected.str(), out.str() );
    std::remove("nested repeated template.tmpl");
}
TEST( Halite, file_import_using_object_by_name)
{

    std::ofstream import("import_by_name_template.tmpl");
    std::stringstream content;
    content<<"this is"<<std::endl
         <<"nested files using ted's foo (<foo>)"<<std::endl
        <<std::endl // empty line
       <<"and assigning foo to < foo = 9 > and p (<p>) to <p=4>";
    import<<content.str();
    import.close();
    std::stringstream input;
    input<< R"INPUT(
    text prior
#import ./import_by_name_template.tmpl using ted
 text after
)INPUT";
    HaliteInterpreter<> interpreter;

    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataObject o;
    DataAccessor data(&o);
    o["p"] = 3;
    o["ted"] = DataObject();
    o["ted"]["foo"] = std::string("bar");
    ASSERT_EQ( Value::TYPE_OBJECT, o["ted"].type() );
    ASSERT_EQ( Value::TYPE_STRING, o["ted"]["foo"].type() );
    ASSERT_TRUE( interpreter.evaluate(out,data) );

    std::stringstream expected;
    expected<< R"INPUT(
    text prior
this is
nested files using ted's foo (bar)

and assigning foo to 9 and p (3) to 4
 text after)INPUT";
    ASSERT_EQ( expected.str(), out.str() );
    std::remove("import_by_name_template.tmpl");
    ASSERT_EQ( Value::TYPE_INTEGER, o["p"].type() );
    ASSERT_EQ( 3, o["p"].to_int() ); // didnt change!!!
    // ensure the child was passed by reference (can be changed)
    ASSERT_EQ( Value::TYPE_INTEGER, o["ted"]["foo"].type() );
    ASSERT_EQ( 9, o["ted"]["foo"].to_int() );
}
TEST( Halite, file_import_using_object_by_copy)
{

    std::ofstream import("import_by_name_template.tmpl");
    std::stringstream content;
    content<<"this is"<<std::endl
         <<"nested files using ted's foo (<foo>)"<<std::endl
        <<std::endl // empty line
       <<"and assigning foo to < foo = 9 >"<<std::endl;
    import<<content.str();
    import.close();
    std::stringstream input;
    input<< R"INPUT(
    text prior
#import ./import_by_name_template.tmpl using <ted>
 text after
)INPUT";
    HaliteInterpreter<> interpreter;

    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataObject o;
    DataAccessor data(&o);
    o["ted"] = DataObject();
    o["ted"]["foo"] = std::string("bar");
    ASSERT_EQ( Value::TYPE_OBJECT, o["ted"].type() );
    ASSERT_EQ( Value::TYPE_STRING, o["ted"]["foo"].type() );
    ASSERT_TRUE( interpreter.evaluate(out,data) );

    std::stringstream expected;
    expected<< R"INPUT(
    text prior
this is
nested files using ted's foo (bar)

and assigning foo to 9
 text after)INPUT";
    ASSERT_EQ( expected.str(), out.str() );
    std::remove("import_by_name_template.tmpl");
    // ensure the child was passed by copy (cannot be changed)
    ASSERT_EQ( Value::TYPE_STRING, o["ted"]["foo"].type() );
    ASSERT_EQ( "bar", o["ted"]["foo"].to_string() );
}
TEST( Halite, file_import_using_inline)
{

    std::ofstream import("import_by_name_inline.tmpl");
    std::stringstream content;
    content<<"this is"<<std::endl
         <<"nested files using ted's foo (<foo>)"<<std::endl
        <<std::endl // empty line
       <<"and assigning foo to < foo = 9 >"<<std::endl;
    import<<content.str();
    import.close();
    std::stringstream input;
    input<< R"INPUT(
    text prior
#import ./import_by_name_inline.tmpl using {"foo":"bar"}
 text after
)INPUT";
    HaliteInterpreter<> interpreter;

    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataObject o;
    DataAccessor data(&o);
    ASSERT_TRUE( interpreter.evaluate(out,data) );

    std::stringstream expected;
    expected<< R"INPUT(
    text prior
this is
nested files using ted's foo (bar)

and assigning foo to 9
 text after)INPUT";
    ASSERT_EQ( expected.str(), out.str() );
    std::remove("import_by_name_inline.tmpl");
    // ensure the variable is not present
    ASSERT_FALSE( data.exists("foo") );
}
TEST( Halite, file_import_using_array_by_name)
{

    std::ofstream import("import_by_name_iterative.tmpl");
    std::stringstream content;
    content<<"nested template"<<std::endl
         <<"using parameter <name>"<<std::endl
        <<"with value <value>"<<std::endl
       <<"and assigning value its own name <value=name>"<<std::endl;
    import<<content.str();
    import.close();
    std::stringstream input;
    input<< R"INPUT(
    text prior
#import ./import_by_name_iterative.tmpl using my_array
 text after
)INPUT";
    HaliteInterpreter<> interpreter;

    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataObject o;
    DataAccessor data(&o);
    o["my_array"] = DataArray();
    o["my_array"][0] = DataObject();
    o["my_array"][0]["name"] = "ted1";
    o["my_array"][0]["value"] = 1;

    o["my_array"][1] = DataObject();
    o["my_array"][1]["name"] = "ted2";
    o["my_array"][1]["value"] = 2.2;

    o["my_array"][2] = DataObject();
    o["my_array"][2]["name"] = "ted3";
    o["my_array"][2]["value"] = "fred";
    ASSERT_TRUE( interpreter.evaluate(out,data) );

    std::stringstream expected;
    expected<< R"INPUT(
    text prior
nested template
using parameter ted1
with value 1
and assigning value its own name ted1nested template
using parameter ted2
with value 2.2
and assigning value its own name ted2nested template
using parameter ted3
with value fred
and assigning value its own name ted3
 text after)INPUT";
    ASSERT_EQ( expected.str(), out.str() );
    std::remove("import_by_name_iterative.tmpl");
    // ensure the child was passed by reference (can be changed)
    ASSERT_EQ( Value::TYPE_STRING, o["my_array"][0]["value"].type() );
    ASSERT_EQ( "ted1", o["my_array"][0]["value"].to_string() );
}

/**
 * @brief test attribute usage from nested template where nested path is parameterized
 */
TEST( Halite, parameterized_fileimport)
{

    std::ofstream import("nested attr wombat.tmpl");
    std::stringstream content;
    content<<"this is"<<std::endl
         <<"nested files using <ted>"<<std::endl
        <<std::endl // empty line
       <<"and assigning fred to < fred = x >"; // missing new line
    import<<content.str();
    import.close();
    std::stringstream input;
    input<< R"INPUT(#import ./nested <x> <ted>.tmpl
<ted> has <fred> brothers)INPUT";
    HaliteInterpreter<> interpreter;

    ASSERT_TRUE( interpreter.parse(input) );
    std::stringstream out;
    DataObject o;
    DataAccessor data(&o);
    o["ted"] = "wombat";
    o["fred"] = 3.14159;
    ASSERT_EQ( Value::TYPE_STRING, o["ted"].type() );
    ASSERT_EQ( Value::TYPE_DOUBLE, o["fred"].type() );
    o["x"] = "attr";
    ASSERT_TRUE( interpreter.evaluate(out,data) );

    std::stringstream expected;
    expected<< R"INPUT(this is
nested files using wombat

and assigning fred to attr
wombat has attr brothers)INPUT";
    ASSERT_EQ( expected.str(), out.str() );
    std::remove("nested attr wombat.tmpl");
    ASSERT_EQ( Value::TYPE_STRING, o["fred"].type() );
    ASSERT_EQ( "attr", o["fred"].to_string() );
}

TEST( Halite, simple_conditional)
{
    std::stringstream input;
    input<< R"INPUT(#ifdef pi


<pi> is defined as pi math constant


#else

 some else statement


text



#endif
)INPUT";

    HaliteInterpreter<> interpreter;
    ASSERT_TRUE( interpreter.parse(input) );
    { // test defined path through template
        std::stringstream expected;
        expected<< R"INPUT(

3.14159 is defined as pi math constant

)INPUT";
        std::stringstream out;
        DataObject o;
        o["pi"] = 3.14159;
        DataAccessor data(&o);
        ASSERT_TRUE( interpreter.evaluate(out,data) );
        ASSERT_EQ( expected.str(), out.str() );
    }
    { // test defined path through template
        std::stringstream expected;
        expected<< R"INPUT(
 some else statement


text


)INPUT";
        std::stringstream out;
        DataObject o;
        DataAccessor data(&o);
        ASSERT_TRUE( interpreter.evaluate(out,data) );
        ASSERT_EQ( expected.str(), out.str() );
    }
}
TEST( Halite, nested_conditional)
{
    std::stringstream input;
    input<< R"INPUT(#ifdef pi

#if <<pi:fmt=%.0f>==3>
<pi> is defined as pi math constant
#endif

#else

 some else statement

#ifndef pi
text
#endif


#endif
)INPUT";

    HaliteInterpreter<> interpreter;
    ASSERT_TRUE( interpreter.parse(input) );
    { // test defined path through template
        std::stringstream expected;
        expected<< R"INPUT(
3.14159 is defined as pi math constant
)INPUT";
        std::stringstream out;
        DataObject o;
        o["pi"] = 3.14159;
        DataAccessor data(&o);
        ASSERT_TRUE( interpreter.evaluate(out,data) );
        ASSERT_EQ( expected.str(), out.str() );
    }
    { // test defined path through template
        std::stringstream expected;
        expected<< R"INPUT(
 some else statement

text

)INPUT";
        std::stringstream out;
        DataObject o;
        DataAccessor data(&o);
        ASSERT_TRUE( interpreter.evaluate(out,data) );
        ASSERT_EQ( expected.str(), out.str() );
    }
}

/**
 * @brief test conditional blocks
 */
TEST( Halite, conditional_text_data_accessed )
{
    std::stringstream input;
    input<< R"INPUT(#ifdef x
x is defined and has a value of <x>
#elseif    <defined(y)>
x is not defined,
 but y is defined with value as an int of <y:fmt=%.0f>
#else
x and y are not defined
#endif
   line
            )INPUT";
    HaliteInterpreter<> interpreter;
    ASSERT_TRUE( interpreter.parse(input) );
    { // test defined path through template
        std::stringstream expected;
        expected<< R"INPUT(x is defined and has a value of 3.14159
   line
            )INPUT";
        std::stringstream out;
        DataObject o;
        o["x"] = 3.14159;
        DataAccessor data(&o);
        ASSERT_TRUE( interpreter.evaluate(out,data) );
        ASSERT_EQ( expected.str(), out.str() );
    }

    { // test elseif  path through template
        std::stringstream expected;
        expected<< R"INPUT(x is not defined,
 but y is defined with value as an int of 7
   line
            )INPUT";
        std::stringstream out;
        DataObject o;
        o["y"] = 7.14159;
        DataAccessor data(&o);
        ASSERT_TRUE( interpreter.evaluate(out,data) );
        ASSERT_EQ( expected.str(), out.str() );
    }
    { // test undefined path through template
        std::stringstream expected;
        expected<< R"INPUT(x and y are not defined
   line
            )INPUT";
        std::stringstream out;
        DataObject o;
        DataAccessor data(&o);
        ASSERT_TRUE( interpreter.evaluate(out,data) );
        ASSERT_EQ( expected.str(), out.str() );
    }
}
