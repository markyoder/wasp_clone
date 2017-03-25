/*
 * File:   tstHalite.cpp
 * Author: Robert A. Lefebvre
 */

#include <cstdlib>
#include <sstream>
#include <string>
#include <stdexcept>
#include <functional>
#include "wasphalite/HaliteInterpreter.h"

#include "gtest/gtest.h"
using namespace std;
using namespace wasp;

TEST( Halite, static_text)
{
    std::stringstream input;
    input<< R"INPUT(This is plain test
line2
 line3
   line
            )INPUT";
    HaliteInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(6, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ( 5, document.child_count() );
    std::string expected_paths = R"INPUT(/
/txt (This is plain test)
/txt (line2)
/txt ( line3)
/txt (   line)
/txt (            )
)INPUT";
        std::stringstream paths;
        document.paths(paths);
        ASSERT_EQ(expected_paths, paths.str());
        ASSERT_EQ(input.str(), document.data());
}


TEST( Halite, simple_parameterized_text)
{
    std::stringstream input;
    input<< R"INPUT(This is plain test
<attribute1><attr2><ted>
            )INPUT";
    HaliteInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(15, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ( 5, document.child_count() );
    std::string expected_paths = R"INPUT(/
/txt (This is plain test)
/attr
/attr/< (<)
/attr/txt (attribute1)
/attr/> (>)
/attr
/attr/< (<)
/attr/txt (attr2)
/attr/> (>)
/attr
/attr/< (<)
/attr/txt (ted)
/attr/> (>)
/txt (            )
)INPUT";
        std::stringstream paths;
        document.paths(paths);
        ASSERT_EQ(expected_paths, paths.str());
        ASSERT_EQ(input.str(), document.data());
}
/**
 * @brief TEST test attributes with whitespace separations
 */
TEST( Halite, simple_parameterized_text_wss)
{
    std::stringstream input;
    input<< R"INPUT(This is plain test
 <attribute1>  <attr2>   <ted>
            )INPUT";
    HaliteInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(18, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ( 8, document.child_count() );
    std::string expected_paths = R"INPUT(/
/txt (This is plain test)
/txt ( )
/attr
/attr/< (<)
/attr/txt (attribute1)
/attr/> (>)
/txt (  )
/attr
/attr/< (<)
/attr/txt (attr2)
/attr/> (>)
/txt (   )
/attr
/attr/< (<)
/attr/txt (ted)
/attr/> (>)
/txt (            )
)INPUT";
        std::stringstream paths;
        document.paths(paths);
        ASSERT_EQ(expected_paths, paths.str());
        ASSERT_EQ(input.str(), document.data());
}
/**
 * @brief TEST test nested empty attribute
 */
TEST( Halite, nested_attr_empty)
{
    std::stringstream input;
    input<<"<><<>><<<>>>";
    HaliteInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(19, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ( 3, document.child_count() );
    std::string expected_paths = R"INPUT(/
/attr
/attr/< (<)
/attr/> (>)
/attr
/attr/< (<)
/attr/attr
/attr/attr/< (<)
/attr/attr/> (>)
/attr/> (>)
/attr
/attr/< (<)
/attr/attr
/attr/attr/< (<)
/attr/attr/attr
/attr/attr/attr/< (<)
/attr/attr/attr/> (>)
/attr/attr/> (>)
/attr/> (>)
)INPUT";
        std::stringstream paths;
        document.paths(paths);
        ASSERT_EQ(expected_paths, paths.str());
        ASSERT_EQ(input.str(), document.data());
}
/**
 * @brief TEST test nested attribute, suffixed text
 */
TEST( Halite, nested_attr_suffix)
{
    std::stringstream input;
    input<<"<<a>b><<<c>d>e>";
    HaliteInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(21, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ( 2, document.child_count() );
    std::string expected_paths = R"INPUT(/
/attr
/attr/< (<)
/attr/attr
/attr/attr/< (<)
/attr/attr/txt (a)
/attr/attr/> (>)
/attr/txt (b)
/attr/> (>)
/attr
/attr/< (<)
/attr/attr
/attr/attr/< (<)
/attr/attr/attr
/attr/attr/attr/< (<)
/attr/attr/attr/txt (c)
/attr/attr/attr/> (>)
/attr/attr/txt (d)
/attr/attr/> (>)
/attr/txt (e)
/attr/> (>)
)INPUT";
        std::stringstream paths;
        document.paths(paths);
        ASSERT_EQ(expected_paths, paths.str());
        ASSERT_EQ(input.str(), document.data());
}

/**
 * @brief TEST test nested attribute, prefixed text
 */
TEST( Halite, nested_attr_prefix)
{
    std::stringstream input;
    input<<"<b<a>><e<d<c>>>";
    HaliteInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(21, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ( 2, document.child_count() );
    std::string expected_paths = R"INPUT(/
/attr
/attr/< (<)
/attr/txt (b)
/attr/attr
/attr/attr/< (<)
/attr/attr/txt (a)
/attr/attr/> (>)
/attr/> (>)
/attr
/attr/< (<)
/attr/txt (e)
/attr/attr
/attr/attr/< (<)
/attr/attr/txt (d)
/attr/attr/attr
/attr/attr/attr/< (<)
/attr/attr/attr/txt (c)
/attr/attr/attr/> (>)
/attr/attr/> (>)
/attr/> (>)
)INPUT";
        std::stringstream paths;
        document.paths(paths);
        ASSERT_EQ(expected_paths, paths.str());
        ASSERT_EQ(input.str(), document.data());
}
/**
 * @brief TEST test nested attribute, prefixed text
 */
TEST( Halite, nested_attr_infix)
{
    std::stringstream input;
    input<<"<b< a >b1><e<d<c>d1>e1>";
    HaliteInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(24, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ( 2, document.child_count() );
    std::string expected_paths = R"INPUT(/
/attr
/attr/< (<)
/attr/txt (b)
/attr/attr
/attr/attr/< (<)
/attr/attr/txt ( a )
/attr/attr/> (>)
/attr/txt (b1)
/attr/> (>)
/attr
/attr/< (<)
/attr/txt (e)
/attr/attr
/attr/attr/< (<)
/attr/attr/txt (d)
/attr/attr/attr
/attr/attr/attr/< (<)
/attr/attr/attr/txt (c)
/attr/attr/attr/> (>)
/attr/attr/txt (d1)
/attr/attr/> (>)
/attr/txt (e1)
/attr/> (>)
)INPUT";
        std::stringstream paths;
        document.paths(paths);
        ASSERT_EQ(expected_paths, paths.str());
        ASSERT_EQ(input.str(), document.data());
}

/**
 * @brief TEST test attribute with surrounding text
 */
TEST( Halite, nested_attr_surrounding)
{
    std::stringstream input;
    input<<"prefix <> suffix ";
    HaliteInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(6, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ( 3, document.child_count() );
    std::string expected_paths = R"INPUT(/
/txt (prefix )
/attr
/attr/< (<)
/attr/> (>)
/txt ( suffix )
)INPUT";
        std::stringstream paths;
        document.paths(paths);
        ASSERT_EQ(expected_paths, paths.str());
        ASSERT_EQ(input.str(), document.data());
}

/**
 * @brief TEST test import statement
 */
TEST( Halite, import_basic)
{
    std::stringstream input;
    input<<"#import some/path/to/some/file";
    HaliteInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(4, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ( 1, document.child_count() );
    std::string expected_paths = R"INPUT(/
/import
/import/decl (#import)
/import/txt ( some/path/to/some/file)
)INPUT";
        std::stringstream paths;
        document.paths(paths);
        ASSERT_EQ(expected_paths, paths.str());
        ASSERT_EQ(input.str(), document.data());
}

/**
 * @brief TEST test parameterized import statement
 */
TEST( Halite, import_parameterized)
{
    std::stringstream input;
    input<<"#import <ned>/<ted>/to/some/<fred>";
    HaliteInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(18, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ( 1, document.child_count() );
    std::string expected_paths = R"INPUT(/
/import
/import/decl (#import)
/import/txt ( )
/import/attr
/import/attr/< (<)
/import/attr/txt (ned)
/import/attr/> (>)
/import/txt (/)
/import/attr
/import/attr/< (<)
/import/attr/txt (ted)
/import/attr/> (>)
/import/txt (/to/some/)
/import/attr
/import/attr/< (<)
/import/attr/txt (fred)
/import/attr/> (>)
)INPUT";
        std::stringstream paths;
        document.paths(paths);
        ASSERT_EQ(expected_paths, paths.str());
        ASSERT_EQ(input.str(), document.data());
}

/**
 * @brief TEST test parameterized import statement
 */
TEST( Halite, import_parameterized_using)
{
    std::stringstream input;
    input<<"#import <ned>/<ted>/to/some/file using <zed>";
    HaliteInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(18, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ( 1, document.child_count() );
    std::string expected_paths = R"INPUT(/
/import
/import/decl (#import)
/import/txt ( )
/import/attr
/import/attr/< (<)
/import/attr/txt (ned)
/import/attr/> (>)
/import/txt (/)
/import/attr
/import/attr/< (<)
/import/attr/txt (ted)
/import/attr/> (>)
/import/txt (/to/some/file using )
/import/attr
/import/attr/< (<)
/import/attr/txt (zed)
/import/attr/> (>)
)INPUT";
        std::stringstream paths;
        document.paths(paths);
        ASSERT_EQ(expected_paths, paths.str());
        ASSERT_EQ(input.str(), document.data());
}
/**
 * @brief TEST test parameterized import statement
 */
TEST( Halite, multiple_import_parameterized_using)
{
    std::stringstream input;
    input<<"#import <ned>/<ted>/to/some/file using <zed>"<<std::endl
        <<"random text line"<<std::endl
       <<"#import some/other/import using <fred>";
    HaliteInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(26, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ( 3, document.child_count() );
    std::string expected_paths = R"INPUT(/
/import
/import/decl (#import)
/import/txt ( )
/import/attr
/import/attr/< (<)
/import/attr/txt (ned)
/import/attr/> (>)
/import/txt (/)
/import/attr
/import/attr/< (<)
/import/attr/txt (ted)
/import/attr/> (>)
/import/txt (/to/some/file using )
/import/attr
/import/attr/< (<)
/import/attr/txt (zed)
/import/attr/> (>)
/txt (random text line)
/import
/import/decl (#import)
/import/txt ( some/other/import using )
/import/attr
/import/attr/< (<)
/import/attr/txt (fred)
/import/attr/> (>)
)INPUT";
        std::stringstream paths;
        document.paths(paths);
        ASSERT_EQ(expected_paths, paths.str());
        ASSERT_EQ(input.str(), document.data());
}

/**
 * @brief TEST test ifdef
 */
TEST( Halite, ifdef)
{
    std::stringstream input;
    input<<"#ifdef something"<<std::endl
       <<"#endif";
    HaliteInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(5, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ( 1, document.child_count() );
    std::string expected_paths = R"INPUT(/
/ifdef
/ifdef/decl (#ifdef)
/ifdef/txt ( something)
/ifdef/endif (#endif)
)INPUT";
        std::stringstream paths;
        document.paths(paths);
        ASSERT_EQ(expected_paths, paths.str());
        ASSERT_EQ(input.str(), document.data());
}

/**
 * @brief TEST test ifdef with parameter and body
 */
TEST( Halite, ifdef_parameterized)
{
    std::stringstream input;
    input<<"#ifdef <x>"<<std::endl
       <<" intermediate text "<<std::endl
       <<"#endif";
    HaliteInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(10, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ( 1, document.child_count() );
    std::string expected_paths = R"INPUT(/
/ifdef
/ifdef/decl (#ifdef)
/ifdef/txt ( )
/ifdef/attr
/ifdef/attr/< (<)
/ifdef/attr/txt (x)
/ifdef/attr/> (>)
/ifdef/txt ( intermediate text )
/ifdef/endif (#endif)
)INPUT";
        std::stringstream paths;
        document.paths(paths);
        ASSERT_EQ(expected_paths, paths.str());
        ASSERT_EQ(input.str(), document.data());
}
/**
 * @brief TEST test ifndef with parameter and body
 */
TEST( Halite, ifndef_parameterized)
{
    std::stringstream input;
    input<<"#ifndef <x>"<<std::endl
       <<" intermediate text "<<std::endl
       <<"#endif";
    HaliteInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(10, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ( 1, document.child_count() );
    std::string expected_paths = R"INPUT(/
/ifndef
/ifndef/decl (#ifndef)
/ifndef/txt ( )
/ifndef/attr
/ifndef/attr/< (<)
/ifndef/attr/txt (x)
/ifndef/attr/> (>)
/ifndef/txt ( intermediate text )
/ifndef/endif (#endif)
)INPUT";
        std::stringstream paths;
        document.paths(paths);
        ASSERT_EQ(expected_paths, paths.str());
        ASSERT_EQ(input.str(), document.data());
}

/**
 * @brief TEST test if with parameter and body
 */
TEST( Halite, if_parameterized)
{
    std::stringstream input;
    input<<"#if <x> < <y>"<<std::endl
       <<" only if x is less than y "<<std::endl
       <<"#endif";
    HaliteInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(15, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ( 1, document.child_count() );
    std::string expected_paths = R"INPUT(/
/if
/if/decl (#if)
/if/txt ( )
/if/attr
/if/attr/< (<)
/if/attr/txt (x)
/if/attr/> (>)
/if/txt ( < )
/if/attr
/if/attr/< (<)
/if/attr/txt (y)
/if/attr/> (>)
/if/txt ( only if x is less than y )
/if/endif (#endif)
)INPUT";
        std::stringstream paths;
        document.paths(paths);
        ASSERT_EQ(expected_paths, paths.str());
        ASSERT_EQ(input.str(), document.data());
}

/**
 * @brief TEST test if elseif with parameter and body
 */
TEST( Halite, elseif_parameterized)
{
    std::stringstream input;
    input<<"#if <x> < <y>"<<std::endl
       <<" only if x is less than y "<<std::endl
        <<"#elseif condition "<<std::endl
        <<" only if x is not less than y and condition is true "<<std::endl
       <<"#endif";
    HaliteInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(19, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ( 2, document.child_count() );
    std::string expected_paths = R"INPUT(/
/if
/if/decl (#if)
/if/txt ( )
/if/attr
/if/attr/< (<)
/if/attr/txt (x)
/if/attr/> (>)
/if/txt ( < )
/if/attr
/if/attr/< (<)
/if/attr/txt (y)
/if/attr/> (>)
/if/txt ( only if x is less than y )
/elseif
/elseif/decl (#elseif)
/elseif/txt ( condition )
/elseif/txt ( only if x is not less than y and condition is true )
/elseif/endif (#endif)
)INPUT";
        std::stringstream paths;
        document.paths(paths);
        ASSERT_EQ(expected_paths, paths.str());
        ASSERT_EQ(input.str(), document.data());
}

/**
 * @brief TEST test if elseif with parameter and body
 */
TEST( Halite, else_parameterized)
{
    std::stringstream input;
    input<<"#if <x> < <y>"<<std::endl
       <<" only if x is less than y "<<std::endl
        <<"#else"<<std::endl
        <<" only if x is not less than y "<<std::endl
       <<"#endif";
    HaliteInterpreter<> interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(18, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ( 2, document.child_count() );
    std::string expected_paths = R"INPUT(/
/if
/if/decl (#if)
/if/txt ( )
/if/attr
/if/attr/< (<)
/if/attr/txt (x)
/if/attr/> (>)
/if/txt ( < )
/if/attr
/if/attr/< (<)
/if/attr/txt (y)
/if/attr/> (>)
/if/txt ( only if x is less than y )
/else
/else/decl (#else)
/else/txt ( only if x is not less than y )
/else/endif (#endif)
)INPUT";
        std::stringstream paths;
        document.paths(paths);
        ASSERT_EQ(expected_paths, paths.str());
        ASSERT_EQ(input.str(), document.data());
}
