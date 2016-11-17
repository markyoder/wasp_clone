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
    TreeNodeView document = interpreter.root();
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
    for( size_t i = 0; i < types.size(); ++i )
    {
        ASSERT_EQ( types[i], interpreter.type(i) );
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
    TreeNodeView document = interpreter.root();
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
    for( size_t i = 0; i < types.size(); ++i )
    {
        ASSERT_EQ( types[i], interpreter.type(i) );
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
    TreeNodeView document = interpreter.root();
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
    for( size_t i = 0; i < types.size(); ++i )
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
    TreeNodeView document = interpreter.root();
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
    for( size_t i = 0; i < types.size(); ++i )
    {
        ASSERT_EQ( types[i], interpreter.type(i) );
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
    TreeNodeView document = interpreter.root();
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
    for( size_t i = 0; i < types.size(); ++i )
    {
        ASSERT_EQ( types[i], interpreter.type(i) );
    }
}
