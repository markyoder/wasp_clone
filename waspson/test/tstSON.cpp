/*
 * File:   tstSON.cpp
 * Author: raq
 *
 * Created on September 26, 2013, 11:43 AM
 */

#include <cstdlib>
#include <sstream>
#include <string>
#include <stdexcept>
#include <functional>
#include "waspson/SONInterpreter.h"
#include <waspson/son_config.h>

#include "gtest/gtest.h"
using namespace std;
using namespace wasp;

TEST( SON, keyed_value)
{
    std::stringstream input;
    input<< R"INPUT(string = val
                    qstring="quoted string"
                    qstr='quoted string'
                    integer = 10323
                    real = 1.1232
                    "qkey" = str
                    'quoted key' = ' 1 12 '
                    tag ( "the id" ) = valu
                    tag ( an_id ) = vl
            )INPUT";
    SONInterpreter interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(43, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ( 9, document.child_count() );
    std::string expected_paths = R"INPUT(/
/string
/string/decl (string)
/string/= (=)
/string/value (val)
/qstring
/qstring/decl (qstring)
/qstring/= (=)
/qstring/value ("quoted string")
/qstr
/qstr/decl (qstr)
/qstr/= (=)
/qstr/value ('quoted string')
/integer
/integer/decl (integer)
/integer/= (=)
/integer/value (10323)
/real
/real/decl (real)
/real/= (=)
/real/value (1.1232)
/qkey
/qkey/decl ("qkey")
/qkey/= (=)
/qkey/value (str)
/quoted key
/quoted key/decl ('quoted key')
/quoted key/= (=)
/quoted key/value (' 1 12 ')
/tag
/tag/decl (tag)
/tag/( (()
/tag/id ("the id")
/tag/) ())
/tag/= (=)
/tag/value (valu)
/tag
/tag/decl (tag)
/tag/( (()
/tag/id (an_id)
/tag/) ())
/tag/= (=)
/tag/value (vl)
)INPUT";
        std::stringstream paths;
        document.paths(paths);
        ASSERT_EQ( expected_paths, paths.str() );
        std::vector<wasp::NODE> types = {
            wasp::DECL
            ,wasp::ASSIGN
            ,wasp::VALUE
            ,wasp::KEYED_VALUE
            ,wasp::DECL
            ,wasp::ASSIGN
            ,wasp::VALUE
            ,wasp::KEYED_VALUE
            ,wasp::DECL
            ,wasp::ASSIGN
            ,wasp::VALUE
            ,wasp::KEYED_VALUE
            ,wasp::DECL
            ,wasp::ASSIGN
            ,wasp::VALUE
            ,wasp::KEYED_VALUE
            ,wasp::DECL
            ,wasp::ASSIGN
            ,wasp::VALUE
            ,wasp::KEYED_VALUE
            ,wasp::DECL
            ,wasp::ASSIGN
            ,wasp::VALUE
            ,wasp::KEYED_VALUE
            ,wasp::DECL
            ,wasp::ASSIGN
            ,wasp::VALUE
            ,wasp::KEYED_VALUE
            ,wasp::DECL
            ,wasp::LPAREN
            ,wasp::IDENTIFIER
            ,wasp::RPAREN
            ,wasp::ASSIGN
            ,wasp::VALUE
            ,wasp::KEYED_VALUE
            ,wasp::DECL
            ,wasp::LPAREN
            ,wasp::IDENTIFIER
            ,wasp::RPAREN
            ,wasp::ASSIGN
            ,wasp::VALUE
            ,wasp::KEYED_VALUE
            ,wasp::DOCUMENT_ROOT
        };
    ASSERT_EQ( types.size(), interpreter.node_count() );
    for( std::size_t i = 0; i < types.size(); ++i )
    {
        {
        SCOPED_TRACE(i);
        ASSERT_EQ( types[i], interpreter.type(i) );
        }
    }
}
TEST( SON, empty_object)
{
    std::stringstream input;
    input<< R"INPUT(e1 {}
            e2{
            }
            e3 = { }
            'e4' : {}
            e5(id1) = { }
            'e6'("id 2") : {}
            )INPUT";
    SONInterpreter interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(35, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ( 6, document.child_count() );
    std::string expected_paths = R"INPUT(/
/e1
/e1/decl (e1)
/e1/{ ({)
/e1/} (})
/e2
/e2/decl (e2)
/e2/{ ({)
/e2/} (})
/e3
/e3/decl (e3)
/e3/= (=)
/e3/{ ({)
/e3/} (})
/e4
/e4/decl ('e4')
/e4/= (:)
/e4/{ ({)
/e4/} (})
/e5
/e5/decl (e5)
/e5/( (()
/e5/id (id1)
/e5/) ())
/e5/= (=)
/e5/{ ({)
/e5/} (})
/e6
/e6/decl ('e6')
/e6/( (()
/e6/id ("id 2")
/e6/) ())
/e6/= (:)
/e6/{ ({)
/e6/} (})
)INPUT";
        std::stringstream paths;
        document.paths(paths);
        ASSERT_EQ( expected_paths, paths.str() );
        std::vector<wasp::NODE> types = {
            wasp::DECL
            ,wasp::LBRACE
            ,wasp::RBRACE
            ,wasp::OBJECT
            ,wasp::DECL
            ,wasp::LBRACE
            ,wasp::RBRACE
            ,wasp::OBJECT
            ,wasp::DECL
            ,wasp::ASSIGN
            ,wasp::LBRACE
            ,wasp::RBRACE
            ,wasp::OBJECT
            ,wasp::DECL
            ,wasp::ASSIGN
            ,wasp::LBRACE
            ,wasp::RBRACE
            ,wasp::OBJECT
            ,wasp::DECL
            ,wasp::LPAREN
            ,wasp::IDENTIFIER
            ,wasp::RPAREN
            ,wasp::ASSIGN
            ,wasp::LBRACE
            ,wasp::RBRACE
            ,wasp::OBJECT
            ,wasp::DECL
            ,wasp::LPAREN
            ,wasp::IDENTIFIER
            ,wasp::RPAREN
            ,wasp::ASSIGN
            ,wasp::LBRACE
            ,wasp::RBRACE
            ,wasp::OBJECT
            ,wasp::DOCUMENT_ROOT
        };
    ASSERT_EQ( types.size(), interpreter.node_count() );
    for( std::size_t i = 0; i < types.size(); ++i )
    {
        {
        SCOPED_TRACE(i);
        ASSERT_EQ( types[i], interpreter.type(i) );
        }
    }
}

TEST( SON, empty_array )
{
    std::stringstream input;
    input<< R"INPUT(e1 []
            e2[
            ]
            e3 = [ ]
            'e4' : []
            e5(id1) = [ ]
            'e6'("id 2") : []
            )INPUT";
    SONInterpreter interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(35, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ( 6, document.child_count() );
    std::string expected_paths = R"INPUT(/
/e1
/e1/decl (e1)
/e1/[ ([)
/e1/] (])
/e2
/e2/decl (e2)
/e2/[ ([)
/e2/] (])
/e3
/e3/decl (e3)
/e3/= (=)
/e3/[ ([)
/e3/] (])
/e4
/e4/decl ('e4')
/e4/= (:)
/e4/[ ([)
/e4/] (])
/e5
/e5/decl (e5)
/e5/( (()
/e5/id (id1)
/e5/) ())
/e5/= (=)
/e5/[ ([)
/e5/] (])
/e6
/e6/decl ('e6')
/e6/( (()
/e6/id ("id 2")
/e6/) ())
/e6/= (:)
/e6/[ ([)
/e6/] (])
)INPUT";
        std::stringstream paths;
        document.paths(paths);
        ASSERT_EQ( expected_paths, paths.str() );
        std::vector<wasp::NODE> types = {
            wasp::DECL
            ,wasp::LBRACKET
            ,wasp::RBRACKET
            ,wasp::ARRAY
            ,wasp::DECL
            ,wasp::LBRACKET
            ,wasp::RBRACKET
            ,wasp::ARRAY
            ,wasp::DECL
            ,wasp::ASSIGN
            ,wasp::LBRACKET
            ,wasp::RBRACKET
            ,wasp::ARRAY
            ,wasp::DECL
            ,wasp::ASSIGN
            ,wasp::LBRACKET
            ,wasp::RBRACKET
            ,wasp::ARRAY
            ,wasp::DECL
            ,wasp::LPAREN
            ,wasp::IDENTIFIER
            ,wasp::RPAREN
            ,wasp::ASSIGN
            ,wasp::LBRACKET
            ,wasp::RBRACKET
            ,wasp::ARRAY
            ,wasp::DECL
            ,wasp::LPAREN
            ,wasp::IDENTIFIER
            ,wasp::RPAREN
            ,wasp::ASSIGN
            ,wasp::LBRACKET
            ,wasp::RBRACKET
            ,wasp::ARRAY
            ,wasp::DOCUMENT_ROOT
        };
    ASSERT_EQ( types.size(), interpreter.node_count() );
    for( std::size_t i = 0; i < types.size(); ++i )
    {
        ASSERT_EQ( types[i], interpreter.type(i) );
    }
}

TEST( SON, empty_execution_unit)
{
    std::stringstream input;
    input<< R"INPUT(=code
end)INPUT";
    SONInterpreter interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(5, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ( 1, document.child_count() );
    std::string expected_paths = R"INPUT(/
/code
/code/uoe_start (=)
/code/name (code)
/code/uoe_end (end)
)INPUT";
        std::stringstream paths;
        document.paths(paths);
        ASSERT_EQ( expected_paths, paths.str() );
        std::vector<wasp::NODE> types = {
            wasp::EXECUTION_UNIT_START
            ,wasp::DECL
            ,EXECUTION_UNIT_END
            ,EXECUTION_UNIT
            ,wasp::DOCUMENT_ROOT
        };
    ASSERT_EQ( types.size(), interpreter.node_count() );
    for( std::size_t i = 0; i < types.size(); ++i )
    {
        {
        SCOPED_TRACE(i);
        ASSERT_EQ( types[i], interpreter.type(i) );
        }
    }
}
TEST( SON, execution_unit)
{
    std::stringstream input;
    input<< R"INPUT(=code string = val
                    qstring="quoted string"
                    qstr='quoted string'
                    integer = 10323
                    real = 1.1232
                    "qkey" = str
                    'quoted key' = ' 1 12 '
                    tag ( "the id" ) = valu
                    tag ( an_id ) = vl
end)INPUT";
    SONInterpreter interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(47, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ( 1, document.child_count() );
    std::string expected_paths = R"INPUT(/
/code
/code/uoe_start (=)
/code/name (code)
/code/string
/code/string/decl (string)
/code/string/= (=)
/code/string/value (val)
/code/qstring
/code/qstring/decl (qstring)
/code/qstring/= (=)
/code/qstring/value ("quoted string")
/code/qstr
/code/qstr/decl (qstr)
/code/qstr/= (=)
/code/qstr/value ('quoted string')
/code/integer
/code/integer/decl (integer)
/code/integer/= (=)
/code/integer/value (10323)
/code/real
/code/real/decl (real)
/code/real/= (=)
/code/real/value (1.1232)
/code/qkey
/code/qkey/decl ("qkey")
/code/qkey/= (=)
/code/qkey/value (str)
/code/quoted key
/code/quoted key/decl ('quoted key')
/code/quoted key/= (=)
/code/quoted key/value (' 1 12 ')
/code/tag
/code/tag/decl (tag)
/code/tag/( (()
/code/tag/id ("the id")
/code/tag/) ())
/code/tag/= (=)
/code/tag/value (valu)
/code/tag
/code/tag/decl (tag)
/code/tag/( (()
/code/tag/id (an_id)
/code/tag/) ())
/code/tag/= (=)
/code/tag/value (vl)
/code/uoe_end (end)
)INPUT";
        std::stringstream paths;
        document.paths(paths);
        ASSERT_EQ( expected_paths, paths.str() );
        std::vector<wasp::NODE> types = {
            wasp::EXECUTION_UNIT_START
            ,wasp::DECL
            ,wasp::DECL
            ,wasp::ASSIGN
            ,wasp::VALUE
            ,wasp::KEYED_VALUE
            ,wasp::DECL
            ,wasp::ASSIGN
            ,wasp::VALUE
            ,wasp::KEYED_VALUE
            ,wasp::DECL
            ,wasp::ASSIGN
            ,wasp::VALUE
            ,wasp::KEYED_VALUE
            ,wasp::DECL
            ,wasp::ASSIGN
            ,wasp::VALUE
            ,wasp::KEYED_VALUE
            ,wasp::DECL
            ,wasp::ASSIGN
            ,wasp::VALUE
            ,wasp::KEYED_VALUE
            ,wasp::DECL
            ,wasp::ASSIGN
            ,wasp::VALUE
            ,wasp::KEYED_VALUE
            ,wasp::DECL
            ,wasp::ASSIGN
            ,wasp::VALUE
            ,wasp::KEYED_VALUE
            ,wasp::DECL
            ,wasp::LPAREN
            ,wasp::IDENTIFIER
            ,wasp::RPAREN
            ,wasp::ASSIGN
            ,wasp::VALUE
            ,wasp::KEYED_VALUE
            ,wasp::DECL
            ,wasp::LPAREN
            ,wasp::IDENTIFIER
            ,wasp::RPAREN
            ,wasp::ASSIGN
            ,wasp::VALUE
            ,wasp::KEYED_VALUE
            ,EXECUTION_UNIT_END
            ,EXECUTION_UNIT
            ,wasp::DOCUMENT_ROOT
        };
    ASSERT_EQ( types.size(), interpreter.node_count() );
    for( std::size_t i = 0; i < types.size(); ++i )
    {
        {
        SCOPED_TRACE(i);
        ASSERT_EQ( types[i], interpreter.type(i) );
        }
    }
}

TEST( SON, int_array)
{
    std::stringstream input;
    input<< R"INPUT(
            ints=[1]
            integers =
                    [
                        4 5 6 7
                    ]
            "2darray"
                     [ 4 5
                       6 7 ]
            )INPUT";
    SONInterpreter interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(24, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ( 3, document.child_count() );
    std::string expected_paths = R"INPUT(/
/ints
/ints/decl (ints)
/ints/= (=)
/ints/[ ([)
/ints/value (1)
/ints/] (])
/integers
/integers/decl (integers)
/integers/= (=)
/integers/[ ([)
/integers/value (4)
/integers/value (5)
/integers/value (6)
/integers/value (7)
/integers/] (])
/2darray
/2darray/decl ("2darray")
/2darray/[ ([)
/2darray/value (4)
/2darray/value (5)
/2darray/value (6)
/2darray/value (7)
/2darray/] (])
)INPUT";
        std::stringstream paths;
        document.paths(paths);
        ASSERT_EQ( expected_paths, paths.str() );
        std::vector<wasp::NODE> types = {
            wasp::DECL
            ,wasp::ASSIGN
            ,wasp::LBRACKET
            ,wasp::VALUE
            ,wasp::RBRACKET
            ,wasp::ARRAY
            ,wasp::DECL
            ,wasp::ASSIGN
            ,wasp::LBRACKET
            ,wasp::VALUE
            ,wasp::VALUE
            ,wasp::VALUE
            ,wasp::VALUE
            ,wasp::RBRACKET
            ,wasp::ARRAY
            ,wasp::DECL
            ,wasp::LBRACKET
            ,wasp::VALUE
            ,wasp::VALUE
            ,wasp::VALUE
            ,wasp::VALUE
            ,wasp::RBRACKET
            ,wasp::ARRAY
            ,wasp::DOCUMENT_ROOT
        };
        std::vector<wasp::NODE> token = {
            wasp::STRING
            ,wasp::ASSIGN
            ,wasp::LBRACKET
            ,wasp::INT
            ,wasp::RBRACKET
            ,wasp::UNKNOWN
            ,wasp::STRING
            ,wasp::ASSIGN
            ,wasp::LBRACKET
            ,wasp::INT
            ,wasp::INT
            ,wasp::INT
            ,wasp::INT
            ,wasp::RBRACKET
            ,wasp::UNKNOWN
            ,wasp::QUOTED_STRING
            ,wasp::LBRACKET
            ,wasp::INT
            ,wasp::INT
            ,wasp::INT
            ,wasp::INT
            ,wasp::RBRACKET
            ,wasp::UNKNOWN
            ,wasp::UNKNOWN
        };
    ASSERT_EQ( types.size(), interpreter.node_count() );
    ASSERT_EQ( token.size(), interpreter.node_count() );
    for( std::size_t i = 0; i < types.size(); ++i )
    {
        {
        SCOPED_TRACE(i);
        ASSERT_EQ( types[i], interpreter.type(i) );
        ASSERT_EQ( token[i], interpreter.node_token_type(i) );
        }
    }
}
TEST( SON, real_array)
{
    std::stringstream input;
    input<< R"INPUT(
            1=[1.0]
            real =
                    [
                        4.0 5.2 1.0e6 1e-7
                    ]
            3.14
                     [ 4.3 5.4
                       6.1 7.0 ]
            )INPUT";
    SONInterpreter interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(24, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ( 3, document.child_count() );
    std::string expected_paths = R"INPUT(/
/1
/1/decl (1)
/1/= (=)
/1/[ ([)
/1/value (1.0)
/1/] (])
/real
/real/decl (real)
/real/= (=)
/real/[ ([)
/real/value (4.0)
/real/value (5.2)
/real/value (1.0e6)
/real/value (1e-7)
/real/] (])
/3.14
/3.14/decl (3.14)
/3.14/[ ([)
/3.14/value (4.3)
/3.14/value (5.4)
/3.14/value (6.1)
/3.14/value (7.0)
/3.14/] (])
)INPUT";
        std::stringstream paths;
        document.paths(paths);
        ASSERT_EQ( expected_paths, paths.str() );
        std::vector<wasp::NODE> types = {
            wasp::DECL
            ,wasp::ASSIGN
            ,wasp::LBRACKET
            ,wasp::VALUE
            ,wasp::RBRACKET
            ,wasp::ARRAY
            ,wasp::DECL
            ,wasp::ASSIGN
            ,wasp::LBRACKET
            ,wasp::VALUE
            ,wasp::VALUE
            ,wasp::VALUE
            ,wasp::VALUE
            ,wasp::RBRACKET
            ,wasp::ARRAY
            ,wasp::DECL
            ,wasp::LBRACKET
            ,wasp::VALUE
            ,wasp::VALUE
            ,wasp::VALUE
            ,wasp::VALUE
            ,wasp::RBRACKET
            ,wasp::ARRAY
            ,wasp::DOCUMENT_ROOT
        };
        std::vector<wasp::NODE> token = {
            wasp::INT // decl
            ,wasp::ASSIGN
            ,wasp::LBRACKET
            ,wasp::REAL
            ,wasp::RBRACKET
            ,wasp::UNKNOWN
            ,wasp::STRING
            ,wasp::ASSIGN
            ,wasp::LBRACKET
            ,wasp::REAL
            ,wasp::REAL
            ,wasp::REAL
            ,wasp::REAL
            ,wasp::RBRACKET
            ,wasp::UNKNOWN
            ,wasp::REAL // decl
            ,wasp::LBRACKET
            ,wasp::REAL
            ,wasp::REAL
            ,wasp::REAL
            ,wasp::REAL
            ,wasp::RBRACKET
            ,wasp::UNKNOWN
            ,wasp::UNKNOWN
        };
    ASSERT_EQ( types.size(), interpreter.node_count() );
    ASSERT_EQ( token.size(), interpreter.node_count() );
    for( std::size_t i = 0; i < types.size(); ++i )
    {
        {
        SCOPED_TRACE(i);
        ASSERT_EQ( types[i], interpreter.type(i) );
        ASSERT_EQ( token[i], interpreter.node_token_type(i) );
        }
    }
}

TEST( SON, comments )
{
    std::stringstream input;
    input<< R"INPUT(
% start of line
   k=1 % trailing line
            )INPUT";
    SONInterpreter interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(7, interpreter.node_count() );
    auto document = interpreter.root();
    ASSERT_EQ( 3, document.child_count() );
    std::string expected_paths = R"INPUT(/
/comment (% start of line)
/k
/k/decl (k)
/k/= (=)
/k/value (1)
/comment (% trailing line)
)INPUT";
        std::stringstream paths;
        document.paths(paths);
        ASSERT_EQ( expected_paths, paths.str() );
        std::vector<wasp::NODE> types = {
            wasp::COMMENT
            ,wasp::DECL
            ,wasp::ASSIGN
            ,wasp::VALUE
            ,wasp::KEYED_VALUE
            ,wasp::COMMENT
            ,wasp::DOCUMENT_ROOT
        };
    ASSERT_EQ( types.size(), interpreter.node_count() );
    for( std::size_t i = 0; i < types.size(); ++i )
    {
        {
        SCOPED_TRACE(i);
        ASSERT_EQ( types[i], interpreter.type(i) );
        }
    }
}

/**
 * @brief TEST the following permutations
 * Objects with comments, keys (w/expression), arrays, and objects
 * Arrays with comments, scalars, keys, arrays, and objects
 * Execution units with comments, keys, arrays and objects
 */
TEST( SON, SON )
{
    std::stringstream input;
    input<< R"INPUT( var = 3.14 % global variable
 g_obj { k=v a[ 1 ] g{x=y} }
=eu
    obj { e=-5  % unary minus of 5
            r[ 1.0 ] n { g=d } }
    arr [ r=5.3
            % A array has a 2 elements, 1) subtraction expression followed by
            % and 2) an unary minus expression
            A[ 1.0-5 -4 ] O { g=d } ]
end % conclusion of unit of execution
)INPUT";
    SONInterpreter interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(85, interpreter.node_count() );
    auto document = interpreter.root();
    // var, comment, global_obj, execution unit, comment
    ASSERT_EQ( 5, document.child_count() );
    std::string expected_paths = R"INPUT(/
/var
/var/decl (var)
/var/= (=)
/var/value (3.14)
/comment (% global variable)
/g_obj
/g_obj/decl (g_obj)
/g_obj/{ ({)
/g_obj/k
/g_obj/k/decl (k)
/g_obj/k/= (=)
/g_obj/k/value (v)
/g_obj/a
/g_obj/a/decl (a)
/g_obj/a/[ ([)
/g_obj/a/value (1)
/g_obj/a/] (])
/g_obj/g
/g_obj/g/decl (g)
/g_obj/g/{ ({)
/g_obj/g/x
/g_obj/g/x/decl (x)
/g_obj/g/x/= (=)
/g_obj/g/x/value (y)
/g_obj/g/} (})
/g_obj/} (})
/eu
/eu/uoe_start (=)
/eu/name (eu)
/eu/obj
/eu/obj/decl (obj)
/eu/obj/{ ({)
/eu/obj/e
/eu/obj/e/decl (e)
/eu/obj/e/= (=)
/eu/obj/e/value
/eu/obj/e/value/- (-)
/eu/obj/e/value/value (5)
/eu/obj/comment (% unary minus of 5)
/eu/obj/r
/eu/obj/r/decl (r)
/eu/obj/r/[ ([)
/eu/obj/r/value (1.0)
/eu/obj/r/] (])
/eu/obj/n
/eu/obj/n/decl (n)
/eu/obj/n/{ ({)
/eu/obj/n/g
/eu/obj/n/g/decl (g)
/eu/obj/n/g/= (=)
/eu/obj/n/g/value (d)
/eu/obj/n/} (})
/eu/obj/} (})
/eu/arr
/eu/arr/decl (arr)
/eu/arr/[ ([)
/eu/arr/r
/eu/arr/r/decl (r)
/eu/arr/r/= (=)
/eu/arr/r/value (5.3)
/eu/arr/comment (% A array has a 2 elements, 1) subtraction expression followed by)
/eu/arr/comment (% and 2) an unary minus expression)
/eu/arr/A
/eu/arr/A/decl (A)
/eu/arr/A/[ ([)
/eu/arr/A/value
/eu/arr/A/value/value
/eu/arr/A/value/value/value (1.0)
/eu/arr/A/value/value/- (-)
/eu/arr/A/value/value/value (5)
/eu/arr/A/value/- (-)
/eu/arr/A/value/value (4)
/eu/arr/A/] (])
/eu/arr/O
/eu/arr/O/decl (O)
/eu/arr/O/{ ({)
/eu/arr/O/g
/eu/arr/O/g/decl (g)
/eu/arr/O/g/= (=)
/eu/arr/O/g/value (d)
/eu/arr/O/} (})
/eu/arr/] (])
/eu/uoe_end (end)
/comment (% conclusion of unit of execution)
)INPUT";
        std::stringstream paths;
        document.paths(paths);
        ASSERT_EQ( expected_paths, paths.str() );
        std::vector<wasp::NODE> types = {
             wasp::DECL           // /var/decl (var)
            ,wasp::ASSIGN         // /var/= (=)
            ,wasp::VALUE          // /var/value (3.14)
            ,wasp::KEYED_VALUE    // /var
            ,wasp::COMMENT        // /comment (% global variable)
            ,wasp::DECL           // /g_obj/decl (g_obj)
            ,wasp::LBRACE         // /g_obj/{ ({)
            ,wasp::DECL           // /g_obj/k/decl (k)
            ,wasp::ASSIGN         // /g_obj/k/= (=)
            ,wasp::VALUE          // /g_obj/k/value (v)
            ,wasp::KEYED_VALUE    // /g_obj/k
            ,wasp::DECL           // /g_obj/a/decl (a)
            ,wasp::LBRACKET       // /g_obj/a/[ ([)
            ,wasp::VALUE          // /g_obj/a/value (1)
            ,wasp::RBRACKET       // /g_obj/a/] (])
            ,wasp::ARRAY          // /g_obj/a
            ,wasp::DECL           // /g_obj/g/decl (g)
            ,wasp::LBRACE         // /g_obj/g/{ ({)
            ,wasp::DECL           // /g_obj/g/x/decl (x)
            ,wasp::ASSIGN         // /g_obj/g/x/= (=)
            ,wasp::VALUE          // /g_obj/g/x/value (y)
            ,wasp::KEYED_VALUE    // /g_obj/g/x
            ,wasp::RBRACE         // /g_obj/g/} (})
            ,wasp::OBJECT         // /g_obj/g
            ,wasp::RBRACE         // /g_obj/} (})
            ,wasp::OBJECT         // /g_obj
            ,wasp::EXECUTION_UNIT_START   // /eu/uoe_start (=)
            ,wasp::DECL           // /eu/name (eu)
            ,wasp::DECL           // /eu/obj/decl (obj)
            ,wasp::LBRACE         // /eu/obj/{ ({)
            ,wasp::DECL           // /eu/obj/e/decl (e)
            ,wasp::ASSIGN         // /eu/obj/e/= (=)
            ,wasp::MINUS          // /eu/obj/e/value/- (-)
            ,wasp::VALUE          // /eu/obj/e/value/value (5)
            ,wasp::MINUS          // /eu/obj/e/value
            ,wasp::KEYED_VALUE    // /eu/obj/e
            ,wasp::COMMENT        // /eu/obj/comment (% unary minus of 5)
            ,wasp::DECL           // /eu/obj/r/decl (r)
            ,wasp::LBRACKET       // /eu/obj/r/[ ([)
            ,wasp::VALUE          // /eu/obj/r/value (1.0)
            ,wasp::RBRACKET       // /eu/obj/r/] (])
            ,wasp::ARRAY          // /eu/obj/r
            ,wasp::DECL           // /eu/obj/n/decl (n)
            ,wasp::LBRACE         // /eu/obj/n/{ ({)
            ,wasp::DECL           // /eu/obj/n/g/decl (g)
            ,wasp::ASSIGN         // /eu/obj/n/g/= (=)
            ,wasp::VALUE          // /eu/obj/n/g/value (d)
            ,wasp::KEYED_VALUE    // /eu/obj/n/g
            ,wasp::RBRACE         // /eu/obj/n/} (})
            ,wasp::OBJECT         // /eu/obj/n
            ,wasp::RBRACE         // /eu/obj/} (})
            ,wasp::OBJECT         // /eu/obj
            ,wasp::DECL           // /eu/arr/decl (arr)
            ,wasp::LBRACKET       // /eu/arr/[ ([)
            ,wasp::DECL           // /eu/arr/r/decl (r)
            ,wasp::ASSIGN         // /eu/arr/r/= (=)
            ,wasp::VALUE          // /eu/arr/r/value (5.3)
            ,wasp::KEYED_VALUE    // /eu/arr/r
            ,wasp::COMMENT        // /eu/arr/comment (% A array has a 2 elements, 1) subtraction expression followed by)
            ,wasp::COMMENT        // /eu/arr/comment (% and 2) an unary minus expression)
            ,wasp::DECL           // /eu/arr/A/decl (A)
            ,wasp::LBRACKET       // /eu/arr/A/[ ([)
            ,wasp::VALUE          // /eu/arr/A/value/value (1.0)
            ,wasp::MINUS          // /eu/arr/A/value/- (-)
            ,wasp::VALUE          // /eu/arr/A/value/value (5)
            ,wasp::MINUS          // /eu/arr/A/value
            ,wasp::MINUS          // /eu/arr/A/value/- (-)
            ,wasp::VALUE          // /eu/arr/A/value/value (4)
            ,wasp::MINUS          // /eu/arr/A/value
            ,wasp::RBRACKET       // /eu/arr/A/] (])
            ,wasp::ARRAY          // /eu/arr/A
            ,wasp::DECL           // /eu/arr/O/decl (O)
            ,wasp::LBRACE         // /eu/arr/O/{ ({)
            ,wasp::DECL           // /eu/arr/O/g/decl (g)
            ,wasp::ASSIGN         // /eu/arr/O/g/= (=)
            ,wasp::VALUE          // /eu/arr/O/g/value (d)
            ,wasp::KEYED_VALUE    // /eu/arr/O/g
            ,wasp::RBRACE         // /eu/arr/O/} (})
            ,wasp::OBJECT         // /eu/arr/O
            ,wasp::RBRACKET       // /eu/arr/] (])
            ,wasp::ARRAY          // /eu/arr
            ,wasp::EXECUTION_UNIT_END    // /eu/uoe_end (end)
            ,wasp::EXECUTION_UNIT // /eu
            ,wasp::COMMENT         // /comment (% conclusion of unit of execution)
            ,wasp::DOCUMENT_ROOT   // /
        };
    ASSERT_EQ( types.size(), interpreter.node_count() );
    for( std::size_t i = 0; i < types.size(); ++i )
    {
        {
        SCOPED_TRACE(i);
        ASSERT_EQ( types[i], interpreter.type(i) );
        }
    }
}

/**
 * @brief TEST the supported expressions
 */
TEST( SON, expressions )
{
    std::stringstream input;
    input<< R"INPUT( e[
            a+b  a+2  a+1.2  b+a  2+a  1.2+a
            a-b  a-2  a-1.2  b-a  2-a  1.2-a
            a*b  a*2  a*1.2  b*a  2*a  1.2*a
            a/b  a/2  a/1.2  b/a  2/a  1.2/a
            a^b  a^2  a^1.2  b^a  2^a  1.2^a
            a<b  a<2  a<1.2  b<a  2<a  1.2<a
            a>b  a>2  a>1.2  b>a  2>a  1.2>a
            a<=b a<=2 a<=1.2 b<=a 2<=a 1.2<=a
            a>=b a>=2 a>=1.2 b>=a 2>=a 1.2>=a
            a==b a==2 a==1.2 b==a 2==a 1.2==a
            a!=b a!=2 a!=1.2 b!=a 2!=a 1.2!=a
            a&&b a&&2 a&&1.2 b&&a 2&&a 1.2&&a
            a||b a||2 a||1.2 b||a 2||a 1.2||a
            ]
)INPUT";
    SONInterpreter interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(312+5, interpreter.node_count() );
    auto document = interpreter.root();
    // var, comment, global_obj, execution unit, comment
    ASSERT_EQ( 1, document.child_count() );

    std::vector<wasp::NODE> types = {
        DECL,LBRACKET
        ,VALUE,PLUS,VALUE,PLUS
        ,VALUE,PLUS,VALUE,PLUS
        ,VALUE,PLUS,VALUE,PLUS
        ,VALUE,PLUS,VALUE,PLUS
        ,VALUE,PLUS,VALUE,PLUS
        ,VALUE,PLUS,VALUE,PLUS

        ,VALUE,MINUS,VALUE,MINUS
        ,VALUE,MINUS,VALUE,MINUS
        ,VALUE,MINUS,VALUE,MINUS
        ,VALUE,MINUS,VALUE,MINUS
        ,VALUE,MINUS,VALUE,MINUS
        ,VALUE,MINUS,VALUE,MINUS

        ,VALUE,MULTIPLY,VALUE,MULTIPLY
        ,VALUE,MULTIPLY,VALUE,MULTIPLY
        ,VALUE,MULTIPLY,VALUE,MULTIPLY
        ,VALUE,MULTIPLY,VALUE,MULTIPLY
        ,VALUE,MULTIPLY,VALUE,MULTIPLY
        ,VALUE,MULTIPLY,VALUE,MULTIPLY

        ,VALUE,DIVIDE,VALUE,DIVIDE
        ,VALUE,DIVIDE,VALUE,DIVIDE
        ,VALUE,DIVIDE,VALUE,DIVIDE
        ,VALUE,DIVIDE,VALUE,DIVIDE
        ,VALUE,DIVIDE,VALUE,DIVIDE
        ,VALUE,DIVIDE,VALUE,DIVIDE

        ,VALUE,EXPONENT,VALUE,EXPONENT
        ,VALUE,EXPONENT,VALUE,EXPONENT
        ,VALUE,EXPONENT,VALUE,EXPONENT
        ,VALUE,EXPONENT,VALUE,EXPONENT
        ,VALUE,EXPONENT,VALUE,EXPONENT
        ,VALUE,EXPONENT,VALUE,EXPONENT

        ,VALUE,LT,VALUE,LT
        ,VALUE,LT,VALUE,LT
        ,VALUE,LT,VALUE,LT
        ,VALUE,LT,VALUE,LT
        ,VALUE,LT,VALUE,LT
        ,VALUE,LT,VALUE,LT

        ,VALUE,GT,VALUE,GT
        ,VALUE,GT,VALUE,GT
        ,VALUE,GT,VALUE,GT
        ,VALUE,GT,VALUE,GT
        ,VALUE,GT,VALUE,GT
        ,VALUE,GT,VALUE,GT

        ,VALUE,LTE,VALUE,LTE
        ,VALUE,LTE,VALUE,LTE
        ,VALUE,LTE,VALUE,LTE
        ,VALUE,LTE,VALUE,LTE
        ,VALUE,LTE,VALUE,LTE
        ,VALUE,LTE,VALUE,LTE

        ,VALUE,GTE,VALUE,GTE
        ,VALUE,GTE,VALUE,GTE
        ,VALUE,GTE,VALUE,GTE
        ,VALUE,GTE,VALUE,GTE
        ,VALUE,GTE,VALUE,GTE
        ,VALUE,GTE,VALUE,GTE

        ,VALUE,EQ,VALUE,EQ
        ,VALUE,EQ,VALUE,EQ
        ,VALUE,EQ,VALUE,EQ
        ,VALUE,EQ,VALUE,EQ
        ,VALUE,EQ,VALUE,EQ
        ,VALUE,EQ,VALUE,EQ

        ,VALUE,NEQ,VALUE,NEQ
        ,VALUE,NEQ,VALUE,NEQ
        ,VALUE,NEQ,VALUE,NEQ
        ,VALUE,NEQ,VALUE,NEQ
        ,VALUE,NEQ,VALUE,NEQ
        ,VALUE,NEQ,VALUE,NEQ

        ,VALUE,WASP_AND,VALUE,WASP_AND
        ,VALUE,WASP_AND,VALUE,WASP_AND
        ,VALUE,WASP_AND,VALUE,WASP_AND
        ,VALUE,WASP_AND,VALUE,WASP_AND
        ,VALUE,WASP_AND,VALUE,WASP_AND
        ,VALUE,WASP_AND,VALUE,WASP_AND

        ,VALUE,WASP_OR,VALUE,WASP_OR
        ,VALUE,WASP_OR,VALUE,WASP_OR
        ,VALUE,WASP_OR,VALUE,WASP_OR
        ,VALUE,WASP_OR,VALUE,WASP_OR
        ,VALUE,WASP_OR,VALUE,WASP_OR
        ,VALUE,WASP_OR,VALUE,WASP_OR
        ,RBRACKET
        ,ARRAY
        ,wasp::DOCUMENT_ROOT   // /
    };
    ASSERT_EQ( types.size(), interpreter.node_count() );
    for( std::size_t i = 0; i < types.size(); ++i )
    {
        {
        SCOPED_TRACE(i);
        ASSERT_EQ( types[i], interpreter.type(i) );
        }
    }
}
