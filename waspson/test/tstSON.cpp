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
