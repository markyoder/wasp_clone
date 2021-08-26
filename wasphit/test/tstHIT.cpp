#include "wasphit/HITInterpreter.h"
#include "wasphit/HITNodeView.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>
using namespace wasp;

TEST(HITInterpreter, bad)

{
    std::stringstream input;
    input << R"INPUT([GlobalParams]
disp_x = disp_x
disp_y = disp_y
disp_z = disp_z
[../])INPUT";
    std::stringstream        error;
    DefaultHITInterpreter interpreter(error);
    ASSERT_TRUE(interpreter.parse(input));
    std::stringstream tree_print;
    auto              root_view = interpreter.root();
    ASSERT_FALSE(root_view.is_null());
    root_view.paths(tree_print);
    std::stringstream expected_tree;
    expected_tree <<
        R"INPUT(/
/GlobalParams
/GlobalParams/[ ([)
/GlobalParams/decl (GlobalParams)
/GlobalParams/] (])
/GlobalParams/disp_x
/GlobalParams/disp_x/decl (disp_x)
/GlobalParams/disp_x/= (=)
/GlobalParams/disp_x/value (disp_x)
/GlobalParams/disp_y
/GlobalParams/disp_y/decl (disp_y)
/GlobalParams/disp_y/= (=)
/GlobalParams/disp_y/value (disp_y)
/GlobalParams/disp_z
/GlobalParams/disp_z/decl (disp_z)
/GlobalParams/disp_z/= (=)
/GlobalParams/disp_z/value (disp_z)
/GlobalParams/term ([../])
)INPUT";
    ASSERT_EQ(expected_tree.str(), tree_print.str());
}

TEST(HITInterpreter, simple)
{
    std::stringstream input;
    // Simple parse
    // document
    //  |_key
    //    |_ decl 'key'
    //    |_ = '='
    //    |_ value '3.421'
    input << "key =  3.421";
    DefaultHITInterpreter interpreter;
    ASSERT_TRUE(interpreter.parse(input));
    ASSERT_EQ(5, interpreter.node_count());

    std::vector<std::string> token_data      = {"key", "=", "3.421"};
    std::vector<std::string> leaf_node_names = {"decl", "=", "value"};
    std::vector<wasp::NODE>  leaf_node_types = {wasp::DECL, wasp::ASSIGN,
                                               wasp::VALUE};
    for (std::size_t i = 0; i < 3; ++i)
    {
        {
            SCOPED_TRACE(i);
            ASSERT_EQ(token_data[i], interpreter.data(i));
            ASSERT_EQ(leaf_node_types[i], interpreter.type(i));
            ASSERT_EQ(leaf_node_names[i], interpreter.name(i));
        }
    }
    std::vector<std::size_t> parent_indices = {3, 3, 3, 4, 5};
    std::vector<std::size_t> child_count    = {0, 0, 0, 3, 1};
    std::vector<std::size_t> column         = {1, 5, 8, 1, 1};
    std::vector<wasp::NODE> node_types = {wasp::DECL, wasp::ASSIGN, wasp::VALUE,
                                          wasp::KEYED_VALUE,
                                          wasp::DOCUMENT_ROOT};
    std::vector<std::string> node_names = {"decl", "=", "value", "key",
                                           "document"};
    ASSERT_EQ(node_types.size(), node_names.size());
    ASSERT_EQ(node_types.size(), parent_indices.size());
    ASSERT_EQ(node_types.size(), child_count.size());
    ASSERT_EQ(node_types.size(), column.size());
    for (std::size_t i = 0; i < interpreter.node_count(); ++i)
    {
        {
            SCOPED_TRACE(i);
            ASSERT_EQ(node_types[i], interpreter.type(i));
            ASSERT_EQ(node_names[i], interpreter.name(i));
            ASSERT_EQ(parent_indices[i], interpreter.parent_node_index(i));
            ASSERT_EQ(child_count[i], interpreter.child_count(i));
            ASSERT_EQ(child_count[i], interpreter.child_count(i));
            ASSERT_EQ(column[i], interpreter.column(i));
            ASSERT_EQ(1, interpreter.line(i));
        }
    }
}

TEST(HITInterpreter, empty_object)
{
    std::stringstream input;
    // Simple parse
    // document
    //  |_object
    //    |_ decl 'ted'
    //      |_ [ '['
    //      |_ string 'ted'
    //      |_ ] ']'
    //    |_ object_term '[]'

    input << "[ted][]";
    DefaultHITInterpreter interpreter;
    ASSERT_TRUE(interpreter.parse(input));
    ASSERT_EQ(6, interpreter.node_count());

    std::vector<std::string> token_data      = {"[", "ted", "]"};
    std::vector<std::string> leaf_node_names = {"[", "decl", "]"};
    std::vector<wasp::NODE>  leaf_node_types = {wasp::LBRACKET, wasp::DECL,
                                               wasp::RBRACKET};
    for (std::size_t i = 0; i < 3; ++i)
    {
        {
            SCOPED_TRACE(i);
            ASSERT_EQ(token_data[i], interpreter.data(i));
            ASSERT_EQ(leaf_node_types[i], interpreter.type(i));
            ASSERT_EQ(leaf_node_names[i], interpreter.name(i));
        }
    }
    std::vector<wasp::NODE> node_types = {wasp::LBRACKET, wasp::DECL,
                                          wasp::RBRACKET, wasp::OBJECT_TERM,
                                          wasp::OBJECT,   wasp::DOCUMENT_ROOT};
    std::vector<std::string> node_names = {"[",  "decl", "]",
                                           "term", "ted",  "document"};
    ASSERT_EQ(node_types.size(), node_names.size());
    for (std::size_t i = 0; i < interpreter.node_count(); ++i)
    {
        {
            SCOPED_TRACE(i);
            ASSERT_EQ(node_types[i], interpreter.type(i));
            ASSERT_EQ(node_names[i], interpreter.name(i));
        }
    }
}

TEST(HITInterpreter, simple_object)
{
    std::stringstream input;
    // Simple parse
    // document
    //  |_object
    //    |_ object_decl 'ted'
    //      |_ [ '['
    //      |_ string 'ted'
    //      |_ ] ']'
    //    |_key
    //      |_ decl 'key'
    //      |_ = '='
    //      |_ value '3.421'
    //    |_ object_term '[]'

    input << "[ted]key = 3.421[]";
    DefaultHITInterpreter interpreter;
    ASSERT_TRUE(interpreter.parse(input));
    ASSERT_EQ(10, interpreter.node_count());

    // object decl
    std::vector<wasp::NODE> node_types = {wasp::LBRACKET,
                                          wasp::DECL,
                                          wasp::RBRACKET
                                          // keyed value
                                          ,
                                          wasp::DECL,
                                          wasp::ASSIGN,
                                          wasp::VALUE,
                                          wasp::KEYED_VALUE
                                          // object term
                                          ,
                                          wasp::OBJECT_TERM
                                          // object
                                          ,
                                          wasp::OBJECT
                                          // document root
                                          ,
                                          wasp::DOCUMENT_ROOT};
    std::vector<std::string> node_names = {
        "[", "decl", "]", "decl", "=", "value", "key", "term", "ted", "document"};
    ASSERT_EQ(node_types.size(), node_names.size());
    for (std::size_t i = 0; i < interpreter.node_count(); ++i)
    {
        {
            SCOPED_TRACE(i);
            ASSERT_EQ(node_types[i], interpreter.type(i));
            ASSERT_EQ(node_names[i], interpreter.name(i));
        }
    }
}

TEST(HITInterpreter, less_simple_object)
{
    std::stringstream input;
    // Simple parse
    // document
    //  |_object
    //    |_ object_decl 'ted'
    //      |_ [ '['
    //      |_ string 'ted'
    //      |_ ] ']'
    //    |_boo
    //      |_ decl 'boo'
    //      |_ = '='
    //      |_ value 'foo'
    //    |_comment
    //    |_fred
    //      |_ decl 'fred'
    //      |_ = '='
    //      |_ value '1'
    //    |_key
    //      |_ decl 'key'
    //      |_ = '='
    //      |_ value '3.421'
    //    |_ object_term '[]'

    input << R"INPUT([ted]
     boo = foo # halloween
     fred = 1
     key = 3.421
 [])INPUT";
    DefaultHITInterpreter interpreter;
    ASSERT_TRUE(interpreter.parse(input));
    ASSERT_EQ(19, interpreter.node_count());

    // object decl
    std::vector<wasp::NODE> node_types = {wasp::LBRACKET,
                                          wasp::DECL,
                                          wasp::RBRACKET
                                          // keyed value boo
                                          ,
                                          wasp::DECL,
                                          wasp::ASSIGN,
                                          wasp::VALUE,
                                          wasp::KEYED_VALUE
                                          // comment
                                          ,
                                          wasp::COMMENT
                                          // keyed value fred
                                          ,
                                          wasp::DECL,
                                          wasp::ASSIGN,
                                          wasp::VALUE,
                                          wasp::KEYED_VALUE
                                          // keyed value key
                                          ,
                                          wasp::DECL,
                                          wasp::ASSIGN,
                                          wasp::VALUE,
                                          wasp::KEYED_VALUE
                                          // object term
                                          ,
                                          wasp::OBJECT_TERM
                                          // object
                                          ,
                                          wasp::OBJECT
                                          // document root
                                          ,
                                          wasp::DOCUMENT_ROOT};
    std::vector<std::string> node_names = {"[",
                                           "decl",
                                           "]",
                                           "decl",
                                           "=",
                                           "value"  // boo
                                           ,
                                           "boo",
                                           "comment"  // halloween
                                           ,
                                           "decl",
                                           "=",
                                           "value"  // fred
                                           ,
                                           "fred",
                                           "decl",
                                           "=",
                                           "value"  // key
                                           ,
                                           "key",
                                           "term",
                                           "ted",
                                           "document"};
    ASSERT_EQ(node_types.size(), node_names.size());
    for (std::size_t i = 0; i < interpreter.node_count(); ++i)
    {
        {
            SCOPED_TRACE(i);
            ASSERT_EQ(node_types[i], interpreter.type(i));
            ASSERT_EQ(node_names[i], interpreter.name(i));
        }
    }
}

TEST(HITInterpreter, object_array)
{
    std::stringstream input;
    // Simple parse
    // document
    //  |_object
    //    |_ object_decl 'ted'
    //      |_ [ '['
    //      |_ string 'ted'
    //      |_ ] ']'
    //    |_array 'data'
    //      |_ decl 'data'
    //      |_ = '='
    //      |_ ' '''
    //      |_ value 'basic'
    //      |_ value '201'
    //      |_ value 'lu'
    //      |_ ' '''
    //    |_ object_term '[]'

    input << "[ted]data='basic 201 lu'[]";
    DefaultHITInterpreter interpreter;
    ASSERT_TRUE(interpreter.parse(input));
    ASSERT_EQ(14, interpreter.node_count());

    std::vector<wasp::NODE> node_types = {wasp::LBRACKET,
                                          wasp::DECL,
                                          wasp::RBRACKET
                                          // keyed value array data
                                          ,
                                          wasp::DECL,
                                          wasp::ASSIGN,
                                          wasp::QUOTE,
                                          wasp::VALUE,
                                          wasp::VALUE,
                                          wasp::VALUE,
                                          wasp::QUOTE,
                                          wasp::ARRAY,
                                          wasp::OBJECT_TERM,
                                          wasp::OBJECT,
                                          wasp::DOCUMENT_ROOT};
    std::vector<std::string> node_names = {"[",
                                           "decl",
                                           "]",
                                           "decl",
                                           "="  // data array
                                           ,
                                           "'"  // start
                                           ,
                                           "value"  // basic
                                           ,
                                           "value"  // 201
                                           ,
                                           "value"  // lu
                                           ,
                                           "'"  // terminator
                                           ,
                                           "data",
                                           "term",
                                           "ted",
                                           "document"};
    ASSERT_EQ(node_types.size(), node_names.size());
    for (std::size_t i = 0; i < interpreter.node_count(); ++i)
    {
        {
            SCOPED_TRACE(i);
            ASSERT_EQ(node_types[i], interpreter.type(i));
            ASSERT_EQ(node_names[i], interpreter.name(i));
        }
    }
}

TEST(HITInterpreter, double_quoted_value)
{
    std::stringstream input;
    // Simple parse
    // document
    //  |_object
    //    |_ object_decl 'ted'
    //      |_ [ '['
    //      |_ string 'ted'
    //      |_ ] ']'
    //    |_key
    //      |_ decl 'key'
    //      |_ = '='
    //      |_ value '"quotedvalue"'
    //    |_ object_term '[]'

    input << "[ted]key = \"quotedvalue\"[]";
    DefaultHITInterpreter interpreter;
    ASSERT_TRUE(interpreter.parse(input));
    ASSERT_EQ(10, interpreter.node_count());

    // object decl
    std::vector<wasp::NODE> node_types = {wasp::LBRACKET,
                                          wasp::DECL,
                                          wasp::RBRACKET
                                          // keyed value
                                          ,
                                          wasp::DECL,
                                          wasp::ASSIGN,
                                          wasp::VALUE,
                                          wasp::KEYED_VALUE
                                          // object term
                                          ,
                                          wasp::OBJECT_TERM
                                          // object
                                          ,
                                          wasp::OBJECT
                                          // document root
                                          ,
                                          wasp::DOCUMENT_ROOT};
    std::vector<std::string> node_names = {
        "[", "decl", "]", "decl", "=", "value", "key", "term", "ted", "document"};
    ASSERT_EQ(node_types.size(), node_names.size());
    for (std::size_t i = 0; i < interpreter.node_count(); ++i)
    {
        {
            SCOPED_TRACE(i);
            ASSERT_EQ(node_types[i], interpreter.type(i));
            ASSERT_EQ(node_names[i], interpreter.name(i));
        }
    }
}

TEST(HITInterpreter, object_array_semicolons)
{
    std::stringstream input;
    // Simple parse
    // document
    //  |_object
    //    |_ object_decl 'ted'
    //      |_ [ '['
    //      |_ string 'ted'
    //      |_ ] ']'
    //    |_array 'data'
    //      |_ decl 'data'
    //      |_ = '='
    //      |_ ' '''
    //      |_ value basic
    //      |_ , semicolon
    //      |_ value 201
    //      |_ , semicolon
    //      |_ value again
    //      |_ , semicolon
    //      |_ value here
    //      |_ , semicolon
    //      |_ value close
    //      |_ , semicolon
    //      |_ value far
    //      |_ value lu
    //      |_ ' '''
    //    |_ object_term '[]'

    input << "[ted]data='basic;201 ; again;here;close ; far lu'[]";
    DefaultHITInterpreter interpreter;
    ASSERT_TRUE(interpreter.parse(input));
    ASSERT_EQ(23, interpreter.node_count());

    std::vector<wasp::NODE> node_types = {wasp::LBRACKET,
                                          wasp::DECL,
                                          wasp::RBRACKET
                                          // keyed value array data
                                          ,
                                          wasp::DECL,
                                          wasp::ASSIGN,
                                          wasp::QUOTE,
                                          wasp::VALUE,
                                          wasp::SEMICOLON,
                                          wasp::VALUE,
                                          wasp::SEMICOLON,
                                          wasp::VALUE,
                                          wasp::SEMICOLON,
                                          wasp::VALUE,
                                          wasp::SEMICOLON,
                                          wasp::VALUE,
                                          wasp::SEMICOLON,
                                          wasp::VALUE,
                                          wasp::VALUE,
                                          wasp::QUOTE,
                                          wasp::ARRAY,
                                          wasp::OBJECT_TERM,
                                          wasp::OBJECT,
                                          wasp::DOCUMENT_ROOT};
    std::vector<std::string> node_names = {"[",
                                           "decl",
                                           "]",
                                           "decl",
                                           "="  // data array
                                           ,
                                           "'"  // start
                                           ,
                                           "value"  // basic
                                           ,
                                           ";"  // semicolon
                                           ,
                                           "value"  // 201
                                           ,
                                           ";"  // semicolon
                                           ,
                                           "value"  // again
                                           ,
                                           ";"  // semicolon
                                           ,
                                           "value"  // here
                                           ,
                                           ";"  // semicolon
                                           ,
                                           "value"  // close
                                           ,
                                           ";"  // semicolon
                                           ,
                                           "value"  // far
                                           ,
                                           "value"  // lu
                                           ,
                                           "'"  // terminator
                                           ,
                                           "data",
                                           "term",
                                           "ted",
                                           "document"};
    ASSERT_EQ(node_types.size(), node_names.size());
    for (std::size_t i = 0; i < interpreter.node_count(); ++i)
    {
        {
            SCOPED_TRACE(i);
            ASSERT_EQ(node_types[i], interpreter.type(i));
            ASSERT_EQ(node_names[i], interpreter.name(i));
        }
    }
}

TEST(HITInterpreter, object_empty_subobject)
{
    std::stringstream input;
    // Simple parse
    // document
    //  |_object
    //    |_ object_decl 'ted'
    //      |_ [ '['
    //      |_ string 'ted'
    //      |_ ] ']'
    //      |_ sub_object 'fred'
    //        |_ sub_object_decl 'fred'
    //          |_ [ '['
    //          |_ ./ './'
    //          |_ string 'fred'
    //          |_ ] ']'
    //        |_ object_term '[../]'
    //    |_ object_term '[]'

    input << "[ted][./fred][../][]";
    DefaultHITInterpreter interpreter;
    ASSERT_TRUE(interpreter.parse(input));
    ASSERT_EQ(12, interpreter.node_count());

    std::vector<wasp::NODE> node_types = {wasp::LBRACKET,
                                          wasp::DECL,
                                          wasp::RBRACKET
                                          // sub object
                                          ,
                                          wasp::LBRACKET,
                                          wasp::DOT_SLASH,
                                          wasp::DECL,
                                          wasp::RBRACKET,
                                          wasp::OBJECT_TERM,
                                          wasp::OBJECT,
                                          wasp::OBJECT_TERM,
                                          wasp::OBJECT,
                                          wasp::DOCUMENT_ROOT};
    std::vector<std::string> node_names = {"[",    "decl", "]",   "[",
                                           "./",   "decl", "]",   "term",
                                           "fred", "term",   "ted", "document"};
    ASSERT_EQ(node_types.size(), node_names.size());
    for (std::size_t i = 0; i < interpreter.node_count(); ++i)
    {
        {
            SCOPED_TRACE(i);
            ASSERT_EQ(node_types[i], interpreter.type(i));
            ASSERT_EQ(node_names[i], interpreter.name(i));
        }
    }
}

TEST(HITInterpreter, object_subobject)
{
    std::stringstream input;
    // Simple parse
    // document
    //  |_object
    //    |_ object_decl 'ted'
    //      |_ [ '['
    //      |_ string 'ted'
    //      |_ ] ']'
    //      |_ sub_object 'fred'
    //        |_ sub_object_decl 'fred'
    //          |_ [ '['
    //          |_ ./ './'
    //          |_ string 'fred'
    //          |_ ] ']'
    //          |_key
    //            |_ decl 'key'
    //            |_ = '='
    //            |_ value '3.421'
    //              |_ object_term '[../]'
    //    |_ object_term '[]'

    input << "[ted][./fred]key=3.4321[../][]";
    DefaultHITInterpreter interpreter;
    ASSERT_TRUE(interpreter.parse(input));
    ASSERT_EQ(16, interpreter.node_count());

    std::vector<wasp::NODE> node_types = {wasp::LBRACKET,
                                          wasp::DECL,
                                          wasp::RBRACKET
                                          // sub object
                                          ,
                                          wasp::LBRACKET,
                                          wasp::DOT_SLASH,
                                          wasp::DECL,
                                          wasp::RBRACKET
                                          // keyed value key
                                          ,
                                          wasp::DECL,
                                          wasp::ASSIGN,
                                          wasp::VALUE,
                                          wasp::KEYED_VALUE,
                                          wasp::OBJECT_TERM,
                                          wasp::OBJECT,
                                          wasp::OBJECT_TERM,
                                          wasp::OBJECT,
                                          wasp::DOCUMENT_ROOT};
    std::vector<std::string> node_names = {"[",
                                           "decl",
                                           "]",
                                           "[",
                                           "./",
                                           "decl",
                                           "]",
                                           "decl",
                                           "=",
                                           "value"  // key
                                           ,
                                           "key",
                                           "term",
                                           "fred",
                                           "term",
                                           "ted",
                                           "document"};
    ASSERT_EQ(node_types.size(), node_names.size());
    for (std::size_t i = 0; i < interpreter.node_count(); ++i)
    {
        {
            SCOPED_TRACE(i);
            ASSERT_EQ(node_types[i], interpreter.type(i));
            ASSERT_EQ(node_names[i], interpreter.name(i));
        }
    }
}

TEST(HITInterpreter, simple_view)
{
    std::stringstream input;
    // Simple parse
    // document
    //  |_key
    //    |_ decl 'key'
    //    |_ = '='
    //    |_ value '3.421'
    input << "key =  3.421";
    DefaultHITInterpreter interpreter;
    ASSERT_TRUE(interpreter.parse(input));
    ASSERT_EQ(5, interpreter.node_count());

    std::vector<wasp::NODE> node_types = {wasp::DECL, wasp::ASSIGN, wasp::VALUE,
                                          wasp::KEYED_VALUE,
                                          wasp::DOCUMENT_ROOT};
    std::vector<std::string> node_names = {"decl", "=", "value", "key",
                                           "document"};
    std::vector<std::string> node_paths = {"/key/decl", "/key/=", "/key/value",
                                           "/key", "/"};
    std::vector<std::size_t> node_columns = {1, 5, 8, 1, 1};
    ASSERT_EQ(node_types.size(), node_names.size());
    ASSERT_EQ(node_types.size(), node_columns.size());
    ASSERT_EQ(node_types.size(), node_paths.size());
    auto document = interpreter.root();
    // the root of the document
    ASSERT_EQ(1, document.child_count());
    ASSERT_EQ(node_names.back(), document.name());
    ASSERT_EQ(wasp::DOCUMENT_ROOT, document.type());
    ASSERT_EQ(1, document.line());
    ASSERT_EQ(1, document.column());
    ASSERT_TRUE(document.equal(document));
    ASSERT_TRUE(false == document.has_parent());
    ASSERT_EQ(node_paths.back(), document.path());
    auto key = document.child_at(0);
    ASSERT_EQ(3, key.child_count());
    ASSERT_TRUE(key.has_parent());
    ASSERT_TRUE(document.equal(key.parent()));
    ASSERT_EQ(wasp::KEYED_VALUE, key.type());
    ASSERT_EQ(node_names[3], key.name());
    ASSERT_EQ(1, key.line());
    ASSERT_EQ(1, key.column());
    ASSERT_FALSE(document.equal(key));
    ASSERT_EQ(node_paths[3], key.path());
    // TODO add test on data (type, line, col, etc).
    for (std::size_t i = 0, child_count = key.child_count(); i < child_count;
         ++i)
    {
        {
            SCOPED_TRACE(i);
            auto child = key.child_at(i);
            ASSERT_EQ(node_types[i], child.type());
            ASSERT_EQ(0, child.child_count());
            ASSERT_EQ(node_types[i], child.type());
            ASSERT_EQ(node_names[i], child.name());
            ASSERT_EQ(1, child.line());
            ASSERT_EQ(node_columns[i], child.column());
            ASSERT_TRUE(child.has_parent());
            ASSERT_TRUE(key.equal(child.parent()));
            ASSERT_EQ(node_paths[i], child.path());
        }
    }
    std::string expected_paths =
        "/\n/key\n/key/decl (key)\n/key/= (=)\n/key/value (3.421)\n";
    std::stringstream paths;
    document.paths(paths);
    ASSERT_EQ(expected_paths, paths.str());
}

TEST(HITInterpreter, paths)
{
    std::stringstream input;
    input << R"INPUT([Problem]
  coord_type = RZ
  [./child][../]
[])INPUT";

    std::string expected_paths =
        R"INPUT(/
/Problem
/Problem/[ ([)
/Problem/decl (Problem)
/Problem/] (])
/Problem/coord_type
/Problem/coord_type/decl (coord_type)
/Problem/coord_type/= (=)
/Problem/coord_type/value (RZ)
/Problem/child
/Problem/child/[ ([)
/Problem/child/./ (./)
/Problem/child/decl (child)
/Problem/child/] (])
/Problem/child/term ([../])
/Problem/term ([])
)INPUT";

    DefaultHITInterpreter interpreter;
    ASSERT_TRUE(interpreter.parse(input));
    ASSERT_EQ(16, interpreter.node_count());
    auto document = interpreter.root();
    ASSERT_EQ(1, document.child_count());
    std::stringstream paths;
    document.paths(paths);
    ASSERT_EQ(expected_paths, paths.str());
}

/**
 * @brief TEST hit doesn't support expressions natively
 * It just grabs them as strings
 */
TEST(HITInterpreter, expression)
{
    std::stringstream input;
    input << R"INPUT(
function = 'A*c^2*(1-c)^2+B*(c^2+6*(1-c),(gr0^2+gr1^2+gr2^2+gr3^2)
             -4*(2-c)*(gr0^3+gr1^3+gr2^3+gr3^3)
             +3*(gr0^2+gr1^2,gr2^2+gr3^2)^2)'
)INPUT";
    std::vector<std::string> data = {
        "function",
        "=",
        "'",
        "A*c^2*(1-c)^2+B*(c^2+6*(1-c),(gr0^2+gr1^2+gr2^2+gr3^2)",
        "-4*(2-c)*(gr0^3+gr1^3+gr2^3+gr3^3)",
        "+3*(gr0^2+gr1^2,gr2^2+gr3^2)^2)",
        "'"};

    DefaultHITInterpreter interpreter;
    ASSERT_TRUE(interpreter.parse(input));
    ASSERT_EQ(9, interpreter.node_count());
    auto document = interpreter.root();
    ASSERT_EQ(1, document.child_count());
    auto fnode = document.child_at(0);
    ASSERT_EQ(data.size(), fnode.child_count());
    for (std::size_t i = 0; i < fnode.child_count(); ++i)
    {
        {
            SCOPED_TRACE(i);
            ASSERT_EQ(data[i], fnode.child_at(i).data());
        }
    }
}
/**
 *  @brief TEST comments that are empty and with content
 */
TEST(HITInterpreter, comments)
{
    std::stringstream input;
    input << R"INPUT(#
# comment with content
#)INPUT";
    DefaultHITInterpreter interpreter;
    ASSERT_TRUE(interpreter.parse(input));
    ASSERT_EQ(4, interpreter.node_count());
    auto document = interpreter.root();
    ASSERT_EQ(3, document.child_count());
    std::vector<std::string> data = {"#", "# comment with content", "#"};
    ASSERT_EQ(data.size(), document.child_count());
    for (std::size_t i = 0; i < document.child_count(); ++i)
    {
        {
            SCOPED_TRACE(i);
            ASSERT_EQ(data[i], document.child_at(i).data());
        }
    }
}

/**
 * @brief TEST nested subblocks (subblocks within subblocks)
 */
TEST(HITInterpreter, nested_subblocks)
{
    std::stringstream input;
    input << R"INPUT([block]
  [./subblock]
    [./nested_subblock]
    [../]
  [../]
[])INPUT";
    DefaultHITInterpreter interpreter;
    ASSERT_TRUE(interpreter.parse(input));
    ASSERT_EQ(18, interpreter.node_count());
    auto document = interpreter.root();
    ASSERT_EQ(1, document.child_count());
    auto block = document.child_at(0);
    ASSERT_EQ("block", std::string(block.name()));
    ASSERT_EQ(wasp::OBJECT, block.type());
    ASSERT_EQ(5, block.child_count());
    auto subblock = block.child_at(3);
    ASSERT_EQ("subblock", std::string(subblock.name()));
    ASSERT_EQ(wasp::OBJECT, subblock.type());
    ASSERT_EQ(6, subblock.child_count());
    auto nestedsubblock = subblock.child_at(4);
    ASSERT_EQ("nested_subblock", std::string(nestedsubblock.name()));
    ASSERT_EQ(wasp::OBJECT, nestedsubblock.type());
    ASSERT_EQ(3, nestedsubblock.line());
    ASSERT_EQ(5, nestedsubblock.column());
}

TEST(HITInterpreter, multiple_objects)
{
    std::stringstream input;
    input << R"INPUT([Problem]
    # Specify coordinate system type
    coord_type = RZ
[]

[Mesh]
    file = pelletcladmergedfine10_rz.e
    displacements = 'disp_x disp_y'
    patch_size = 1000 # For contact algorithm
[]
[1]
    some = thing
    [./2]
        another=value
        sliceheight = ${/ ${fuelheight} ${numslices}}
    [../]
[])INPUT";

    DefaultHITInterpreter interpreter;
    ASSERT_TRUE(interpreter.parse(input));
    ASSERT_EQ(55, interpreter.node_count());
    HITNodeView document = interpreter.root();
    ASSERT_EQ(3, document.child_count());  // problem and mesh
    ASSERT_EQ(3, interpreter.child_count(document.node_index()));
    ASSERT_EQ(document.child_at(0).node_index(),
              interpreter.child_index_at(document.node_index(), 0));
    std::string       expected_paths = R"INPUT(/
/Problem
/Problem/[ ([)
/Problem/decl (Problem)
/Problem/] (])
/Problem/comment (# Specify coordinate system type)
/Problem/coord_type
/Problem/coord_type/decl (coord_type)
/Problem/coord_type/= (=)
/Problem/coord_type/value (RZ)
/Problem/term ([])
/Mesh
/Mesh/[ ([)
/Mesh/decl (Mesh)
/Mesh/] (])
/Mesh/file
/Mesh/file/decl (file)
/Mesh/file/= (=)
/Mesh/file/value (pelletcladmergedfine10_rz.e)
/Mesh/displacements
/Mesh/displacements/decl (displacements)
/Mesh/displacements/= (=)
/Mesh/displacements/' (')
/Mesh/displacements/value (disp_x)
/Mesh/displacements/value (disp_y)
/Mesh/displacements/' (')
/Mesh/patch_size
/Mesh/patch_size/decl (patch_size)
/Mesh/patch_size/= (=)
/Mesh/patch_size/value (1000)
/Mesh/comment (# For contact algorithm)
/Mesh/term ([])
/1
/1/[ ([)
/1/decl (1)
/1/] (])
/1/some
/1/some/decl (some)
/1/some/= (=)
/1/some/value (thing)
/1/2
/1/2/[ ([)
/1/2/./ (./)
/1/2/decl (2)
/1/2/] (])
/1/2/another
/1/2/another/decl (another)
/1/2/another/= (=)
/1/2/another/value (value)
/1/2/sliceheight
/1/2/sliceheight/decl (sliceheight)
/1/2/sliceheight/= (=)
/1/2/sliceheight/value (${/ ${fuelheight} ${numslices}})
/1/2/term ([../])
/1/term ([])
)INPUT";
    std::stringstream paths;
    document.paths(paths);
    ASSERT_EQ(expected_paths, paths.str());
    auto mesh_view = document.first_child_by_name("Mesh");
    ASSERT_FALSE(mesh_view.is_null());
    ASSERT_FALSE(mesh_view.is_decorative());
    ASSERT_EQ(wasp::OBJECT, mesh_view.type());
    ASSERT_EQ(8, mesh_view.child_count());
    ASSERT_EQ(3, mesh_view.non_decorative_children_count());
    auto disp_view = mesh_view.first_child_by_name("displacements");
    ASSERT_FALSE(disp_view.is_null());
    ASSERT_EQ(wasp::ARRAY, disp_view.type());
    ASSERT_EQ(2, disp_view.non_decorative_children_count());
    auto values = disp_view.non_decorative_children();
    ASSERT_EQ(2, values.size());
    for (auto v : values)
    {
        ASSERT_EQ("value", std::string(v.name()));
        ASSERT_EQ("disp", v.to_string().substr(0, 4));
    }
}

/**
 * @brief TEST hit type promotion
 * When a block/subblock has a type field,
 * the block/subblock name becomes the type field's value
 * with "_type" appended.
 *
 * Test each scenario for block and subblock
 * 1. block with only type = value
 * 2. block with type = value and other stuff
 * 3. subblock with only type = value
 * 4. subblock with type = value and other stuff
 * 5. subblock with type = value
 * 6. block with type = value
 */
TEST(HITInterpreter, type_promotion)
{
    std::stringstream input;
    input << R"INPUT([Problem]
    # Specify coordinate system type
    type = ted
    [./s1] type = fred [../]
    [./s2] type = x  y=1 [../]
[]
[p1]
    type = t1
[]
[p2]
   type = t2
    [./s3]
        type = us3
    [../]
[]
)INPUT";

    DefaultHITInterpreter interpreter;
    ASSERT_TRUE(interpreter.parse(input));
    ASSERT_EQ(63, interpreter.node_count());
    HITNodeView document = interpreter.root();
    ASSERT_EQ(3, document.child_count());  // problem and mesh
    ASSERT_EQ(3, interpreter.child_count(document.node_index()));
    std::string       expected_paths = R"INPUT(/
/ted_type
/ted_type/[ ([)
/ted_type/decl (Problem)
/ted_type/] (])
/ted_type/comment (# Specify coordinate system type)
/ted_type/type
/ted_type/type/decl (type)
/ted_type/type/= (=)
/ted_type/type/value (ted)
/ted_type/fred_type
/ted_type/fred_type/[ ([)
/ted_type/fred_type/./ (./)
/ted_type/fred_type/decl (s1)
/ted_type/fred_type/] (])
/ted_type/fred_type/type
/ted_type/fred_type/type/decl (type)
/ted_type/fred_type/type/= (=)
/ted_type/fred_type/type/value (fred)
/ted_type/fred_type/term ([../])
/ted_type/x_type
/ted_type/x_type/[ ([)
/ted_type/x_type/./ (./)
/ted_type/x_type/decl (s2)
/ted_type/x_type/] (])
/ted_type/x_type/type
/ted_type/x_type/type/decl (type)
/ted_type/x_type/type/= (=)
/ted_type/x_type/type/value (x)
/ted_type/x_type/y
/ted_type/x_type/y/decl (y)
/ted_type/x_type/y/= (=)
/ted_type/x_type/y/value (1)
/ted_type/x_type/term ([../])
/ted_type/term ([])
/t1_type
/t1_type/[ ([)
/t1_type/decl (p1)
/t1_type/] (])
/t1_type/type
/t1_type/type/decl (type)
/t1_type/type/= (=)
/t1_type/type/value (t1)
/t1_type/term ([])
/t2_type
/t2_type/[ ([)
/t2_type/decl (p2)
/t2_type/] (])
/t2_type/type
/t2_type/type/decl (type)
/t2_type/type/= (=)
/t2_type/type/value (t2)
/t2_type/us3_type
/t2_type/us3_type/[ ([)
/t2_type/us3_type/./ (./)
/t2_type/us3_type/decl (s3)
/t2_type/us3_type/] (])
/t2_type/us3_type/type
/t2_type/us3_type/type/decl (type)
/t2_type/us3_type/type/= (=)
/t2_type/us3_type/type/value (us3)
/t2_type/us3_type/term ([../])
/t2_type/term ([])
)INPUT";
    std::stringstream paths;
    document.paths(paths);
    ASSERT_EQ(expected_paths, paths.str());
    auto ted_view = document.first_child_by_name("ted_type");
    ASSERT_FALSE(ted_view.is_null());
    ASSERT_FALSE(ted_view.is_decorative());
    ASSERT_EQ(wasp::OBJECT, ted_view.type());
    ASSERT_EQ(8, ted_view.child_count());
    // ted/type and ted/fred
    ASSERT_EQ(3, ted_view.non_decorative_children_count());
}

/**
 * @brief Test HIT syntax
 *
 * MOOSE's new HIT parser relaxes the declarator and terminator syntax
 * for blocks and subblocks and all blocks are considered the same type
 *
 * Blocks and subblocks may be started with:
 *  - Block declarator syntax    ( i.e. "[blockname]")
 *  - Subblock declarator syntax ( i.e. "[./blockname]")
 *
 * Blocks and subblocks may be terminated with:
 *  - Block terminator syntax    ( i.e. "[]")
 *  - Subblock terminator syntax ( i.e. "[../]")
 */
TEST(HITInterpreter, hit_syntax)
{
    std::stringstream input;
    input << R"INPUT(
[TopLevelBlock]

  [./sub-decl-sub-term-no-type]
    flag01  = 1.1
    array01 = name11 name12 name13
  [../]

  [./sub-decl-top-term-no-type]
    flag02  = 2.2
    array02 = name21 name22 name23
  []

  [top-decl-sub-term-no-type]
    flag03  = 3.3
    array03 = name31 name32 name33
  [../]

  [top-decl-top-term-no-type]
    flag04  = 4.4
    array04 = name41 name42 name43
  []

  [./sub-decl-sub-term-wt-type]
    type    = SubDeclSubTerm
    flag05  = 5.5
    array05 = name51 name42 name53
  [../]

  [./sub-decl-top-term-wt-type]
    type    = SubDeclTopTerm
    flag06  = 6.6
    array06 = name61 name62 name63
  []

  [top-decl-sub-term-wt-type]
    type    = TopDeclSubTerm
    flag07  = 7.7
    array07 = name71 name72 name73
  [../]

  [top-decl-top-term-wt-type]
    type    = TopDeclTopTerm
    flag08  = 8.8
    array08 = name81 name82 name83
  []

[]
)INPUT";

    DefaultHITInterpreter interpreter;
    ASSERT_TRUE(interpreter.parse(input));
    ASSERT_EQ(146, interpreter.node_count());
    HITNodeView document = interpreter.root();
    ASSERT_EQ(1, document.child_count());
    ASSERT_EQ(1, interpreter.child_count(document.node_index()));
    ASSERT_EQ(document.child_at(0).node_index(),
              interpreter.child_index_at(document.node_index(), 0));

    std::string expected_paths = R"INPUT(/
/TopLevelBlock
/TopLevelBlock/[ ([)
/TopLevelBlock/decl (TopLevelBlock)
/TopLevelBlock/] (])
/TopLevelBlock/sub-decl-sub-term-no-type
/TopLevelBlock/sub-decl-sub-term-no-type/[ ([)
/TopLevelBlock/sub-decl-sub-term-no-type/./ (./)
/TopLevelBlock/sub-decl-sub-term-no-type/decl (sub-decl-sub-term-no-type)
/TopLevelBlock/sub-decl-sub-term-no-type/] (])
/TopLevelBlock/sub-decl-sub-term-no-type/flag01
/TopLevelBlock/sub-decl-sub-term-no-type/flag01/decl (flag01)
/TopLevelBlock/sub-decl-sub-term-no-type/flag01/= (=)
/TopLevelBlock/sub-decl-sub-term-no-type/flag01/value (1.1)
/TopLevelBlock/sub-decl-sub-term-no-type/array01
/TopLevelBlock/sub-decl-sub-term-no-type/array01/decl (array01)
/TopLevelBlock/sub-decl-sub-term-no-type/array01/= (=)
/TopLevelBlock/sub-decl-sub-term-no-type/array01/value (name11)
/TopLevelBlock/sub-decl-sub-term-no-type/string (name12)
/TopLevelBlock/sub-decl-sub-term-no-type/string (name13)
/TopLevelBlock/sub-decl-sub-term-no-type/term ([../])
/TopLevelBlock/sub-decl-top-term-no-type
/TopLevelBlock/sub-decl-top-term-no-type/[ ([)
/TopLevelBlock/sub-decl-top-term-no-type/./ (./)
/TopLevelBlock/sub-decl-top-term-no-type/decl (sub-decl-top-term-no-type)
/TopLevelBlock/sub-decl-top-term-no-type/] (])
/TopLevelBlock/sub-decl-top-term-no-type/flag02
/TopLevelBlock/sub-decl-top-term-no-type/flag02/decl (flag02)
/TopLevelBlock/sub-decl-top-term-no-type/flag02/= (=)
/TopLevelBlock/sub-decl-top-term-no-type/flag02/value (2.2)
/TopLevelBlock/sub-decl-top-term-no-type/array02
/TopLevelBlock/sub-decl-top-term-no-type/array02/decl (array02)
/TopLevelBlock/sub-decl-top-term-no-type/array02/= (=)
/TopLevelBlock/sub-decl-top-term-no-type/array02/value (name21)
/TopLevelBlock/sub-decl-top-term-no-type/string (name22)
/TopLevelBlock/sub-decl-top-term-no-type/string (name23)
/TopLevelBlock/sub-decl-top-term-no-type/term ([])
/TopLevelBlock/top-decl-sub-term-no-type
/TopLevelBlock/top-decl-sub-term-no-type/[ ([)
/TopLevelBlock/top-decl-sub-term-no-type/decl (top-decl-sub-term-no-type)
/TopLevelBlock/top-decl-sub-term-no-type/] (])
/TopLevelBlock/top-decl-sub-term-no-type/flag03
/TopLevelBlock/top-decl-sub-term-no-type/flag03/decl (flag03)
/TopLevelBlock/top-decl-sub-term-no-type/flag03/= (=)
/TopLevelBlock/top-decl-sub-term-no-type/flag03/value (3.3)
/TopLevelBlock/top-decl-sub-term-no-type/array03
/TopLevelBlock/top-decl-sub-term-no-type/array03/decl (array03)
/TopLevelBlock/top-decl-sub-term-no-type/array03/= (=)
/TopLevelBlock/top-decl-sub-term-no-type/array03/value (name31)
/TopLevelBlock/top-decl-sub-term-no-type/string (name32)
/TopLevelBlock/top-decl-sub-term-no-type/string (name33)
/TopLevelBlock/top-decl-sub-term-no-type/term ([../])
/TopLevelBlock/top-decl-top-term-no-type
/TopLevelBlock/top-decl-top-term-no-type/[ ([)
/TopLevelBlock/top-decl-top-term-no-type/decl (top-decl-top-term-no-type)
/TopLevelBlock/top-decl-top-term-no-type/] (])
/TopLevelBlock/top-decl-top-term-no-type/flag04
/TopLevelBlock/top-decl-top-term-no-type/flag04/decl (flag04)
/TopLevelBlock/top-decl-top-term-no-type/flag04/= (=)
/TopLevelBlock/top-decl-top-term-no-type/flag04/value (4.4)
/TopLevelBlock/top-decl-top-term-no-type/array04
/TopLevelBlock/top-decl-top-term-no-type/array04/decl (array04)
/TopLevelBlock/top-decl-top-term-no-type/array04/= (=)
/TopLevelBlock/top-decl-top-term-no-type/array04/value (name41)
/TopLevelBlock/top-decl-top-term-no-type/string (name42)
/TopLevelBlock/top-decl-top-term-no-type/string (name43)
/TopLevelBlock/top-decl-top-term-no-type/term ([])
/TopLevelBlock/SubDeclSubTerm_type
/TopLevelBlock/SubDeclSubTerm_type/[ ([)
/TopLevelBlock/SubDeclSubTerm_type/./ (./)
/TopLevelBlock/SubDeclSubTerm_type/decl (sub-decl-sub-term-wt-type)
/TopLevelBlock/SubDeclSubTerm_type/] (])
/TopLevelBlock/SubDeclSubTerm_type/type
/TopLevelBlock/SubDeclSubTerm_type/type/decl (type)
/TopLevelBlock/SubDeclSubTerm_type/type/= (=)
/TopLevelBlock/SubDeclSubTerm_type/type/value (SubDeclSubTerm)
/TopLevelBlock/SubDeclSubTerm_type/flag05
/TopLevelBlock/SubDeclSubTerm_type/flag05/decl (flag05)
/TopLevelBlock/SubDeclSubTerm_type/flag05/= (=)
/TopLevelBlock/SubDeclSubTerm_type/flag05/value (5.5)
/TopLevelBlock/SubDeclSubTerm_type/array05
/TopLevelBlock/SubDeclSubTerm_type/array05/decl (array05)
/TopLevelBlock/SubDeclSubTerm_type/array05/= (=)
/TopLevelBlock/SubDeclSubTerm_type/array05/value (name51)
/TopLevelBlock/SubDeclSubTerm_type/string (name42)
/TopLevelBlock/SubDeclSubTerm_type/string (name53)
/TopLevelBlock/SubDeclSubTerm_type/term ([../])
/TopLevelBlock/SubDeclTopTerm_type
/TopLevelBlock/SubDeclTopTerm_type/[ ([)
/TopLevelBlock/SubDeclTopTerm_type/./ (./)
/TopLevelBlock/SubDeclTopTerm_type/decl (sub-decl-top-term-wt-type)
/TopLevelBlock/SubDeclTopTerm_type/] (])
/TopLevelBlock/SubDeclTopTerm_type/type
/TopLevelBlock/SubDeclTopTerm_type/type/decl (type)
/TopLevelBlock/SubDeclTopTerm_type/type/= (=)
/TopLevelBlock/SubDeclTopTerm_type/type/value (SubDeclTopTerm)
/TopLevelBlock/SubDeclTopTerm_type/flag06
/TopLevelBlock/SubDeclTopTerm_type/flag06/decl (flag06)
/TopLevelBlock/SubDeclTopTerm_type/flag06/= (=)
/TopLevelBlock/SubDeclTopTerm_type/flag06/value (6.6)
/TopLevelBlock/SubDeclTopTerm_type/array06
/TopLevelBlock/SubDeclTopTerm_type/array06/decl (array06)
/TopLevelBlock/SubDeclTopTerm_type/array06/= (=)
/TopLevelBlock/SubDeclTopTerm_type/array06/value (name61)
/TopLevelBlock/SubDeclTopTerm_type/string (name62)
/TopLevelBlock/SubDeclTopTerm_type/string (name63)
/TopLevelBlock/SubDeclTopTerm_type/term ([])
/TopLevelBlock/TopDeclSubTerm_type
/TopLevelBlock/TopDeclSubTerm_type/[ ([)
/TopLevelBlock/TopDeclSubTerm_type/decl (top-decl-sub-term-wt-type)
/TopLevelBlock/TopDeclSubTerm_type/] (])
/TopLevelBlock/TopDeclSubTerm_type/type
/TopLevelBlock/TopDeclSubTerm_type/type/decl (type)
/TopLevelBlock/TopDeclSubTerm_type/type/= (=)
/TopLevelBlock/TopDeclSubTerm_type/type/value (TopDeclSubTerm)
/TopLevelBlock/TopDeclSubTerm_type/flag07
/TopLevelBlock/TopDeclSubTerm_type/flag07/decl (flag07)
/TopLevelBlock/TopDeclSubTerm_type/flag07/= (=)
/TopLevelBlock/TopDeclSubTerm_type/flag07/value (7.7)
/TopLevelBlock/TopDeclSubTerm_type/array07
/TopLevelBlock/TopDeclSubTerm_type/array07/decl (array07)
/TopLevelBlock/TopDeclSubTerm_type/array07/= (=)
/TopLevelBlock/TopDeclSubTerm_type/array07/value (name71)
/TopLevelBlock/TopDeclSubTerm_type/string (name72)
/TopLevelBlock/TopDeclSubTerm_type/string (name73)
/TopLevelBlock/TopDeclSubTerm_type/term ([../])
/TopLevelBlock/TopDeclTopTerm_type
/TopLevelBlock/TopDeclTopTerm_type/[ ([)
/TopLevelBlock/TopDeclTopTerm_type/decl (top-decl-top-term-wt-type)
/TopLevelBlock/TopDeclTopTerm_type/] (])
/TopLevelBlock/TopDeclTopTerm_type/type
/TopLevelBlock/TopDeclTopTerm_type/type/decl (type)
/TopLevelBlock/TopDeclTopTerm_type/type/= (=)
/TopLevelBlock/TopDeclTopTerm_type/type/value (TopDeclTopTerm)
/TopLevelBlock/TopDeclTopTerm_type/flag08
/TopLevelBlock/TopDeclTopTerm_type/flag08/decl (flag08)
/TopLevelBlock/TopDeclTopTerm_type/flag08/= (=)
/TopLevelBlock/TopDeclTopTerm_type/flag08/value (8.8)
/TopLevelBlock/TopDeclTopTerm_type/array08
/TopLevelBlock/TopDeclTopTerm_type/array08/decl (array08)
/TopLevelBlock/TopDeclTopTerm_type/array08/= (=)
/TopLevelBlock/TopDeclTopTerm_type/array08/value (name81)
/TopLevelBlock/TopDeclTopTerm_type/string (name82)
/TopLevelBlock/TopDeclTopTerm_type/string (name83)
/TopLevelBlock/TopDeclTopTerm_type/term ([])
/TopLevelBlock/term ([])
)INPUT";

    std::stringstream paths;
    document.paths(paths);
    ASSERT_EQ(expected_paths, paths.str());
}

/**
 * @brief Test HIT syntax - period in block declarators
 */
TEST(HITInterpreter, period_in_block_declarators)
{
    std::stringstream input;
    input << R"INPUT(
[TopBlock]
  [child.01.period.wt.type]
    type = Type01
    var01 = val01
  []
  [./child.02.period.wt.type]
    type = Type02
    var02 = val02
  [../]
  [child.03.period.no.type]
    var03 = val03
  [../]
  [./child.04.period.no.type]
    var04 = val04
  []
[]
)INPUT";

    DefaultHITInterpreter interpreter;
    ASSERT_TRUE(interpreter.parse(input));
    ASSERT_EQ(52, interpreter.node_count());
    HITNodeView document = interpreter.root();
    ASSERT_EQ(1, document.child_count());
    ASSERT_EQ(1, interpreter.child_count(document.node_index()));
    ASSERT_EQ(document.child_at(0).node_index(),
              interpreter.child_index_at(document.node_index(), 0));

    std::string expected_paths = R"INPUT(/
/TopBlock
/TopBlock/[ ([)
/TopBlock/decl (TopBlock)
/TopBlock/] (])
/TopBlock/Type01_type
/TopBlock/Type01_type/[ ([)
/TopBlock/Type01_type/decl (child.01.period.wt.type)
/TopBlock/Type01_type/] (])
/TopBlock/Type01_type/type
/TopBlock/Type01_type/type/decl (type)
/TopBlock/Type01_type/type/= (=)
/TopBlock/Type01_type/type/value (Type01)
/TopBlock/Type01_type/var01
/TopBlock/Type01_type/var01/decl (var01)
/TopBlock/Type01_type/var01/= (=)
/TopBlock/Type01_type/var01/value (val01)
/TopBlock/Type01_type/term ([])
/TopBlock/Type02_type
/TopBlock/Type02_type/[ ([)
/TopBlock/Type02_type/./ (./)
/TopBlock/Type02_type/decl (child.02.period.wt.type)
/TopBlock/Type02_type/] (])
/TopBlock/Type02_type/type
/TopBlock/Type02_type/type/decl (type)
/TopBlock/Type02_type/type/= (=)
/TopBlock/Type02_type/type/value (Type02)
/TopBlock/Type02_type/var02
/TopBlock/Type02_type/var02/decl (var02)
/TopBlock/Type02_type/var02/= (=)
/TopBlock/Type02_type/var02/value (val02)
/TopBlock/Type02_type/term ([../])
/TopBlock/child.03.period.no.type
/TopBlock/child.03.period.no.type/[ ([)
/TopBlock/child.03.period.no.type/decl (child.03.period.no.type)
/TopBlock/child.03.period.no.type/] (])
/TopBlock/child.03.period.no.type/var03
/TopBlock/child.03.period.no.type/var03/decl (var03)
/TopBlock/child.03.period.no.type/var03/= (=)
/TopBlock/child.03.period.no.type/var03/value (val03)
/TopBlock/child.03.period.no.type/term ([../])
/TopBlock/child.04.period.no.type
/TopBlock/child.04.period.no.type/[ ([)
/TopBlock/child.04.period.no.type/./ (./)
/TopBlock/child.04.period.no.type/decl (child.04.period.no.type)
/TopBlock/child.04.period.no.type/] (])
/TopBlock/child.04.period.no.type/var04
/TopBlock/child.04.period.no.type/var04/decl (var04)
/TopBlock/child.04.period.no.type/var04/= (=)
/TopBlock/child.04.period.no.type/var04/value (val04)
/TopBlock/child.04.period.no.type/term ([])
/TopBlock/term ([])
)INPUT";

    std::stringstream actual_paths;
    document.paths(actual_paths);
    ASSERT_EQ(expected_paths, actual_paths.str());
}

/**
 * @brief Test HIT syntax - equals and brackets in arrays
 */
TEST(HITInterpreter, equals_and_brackets_in_arrays)
{
    std::stringstream input;
    input << R"INPUT(
array01 = 'd2F1:=D[F1,eta1,eta1] d2F2:=D[F2,eta1,eta1]'
[BlockContainer]
  array02 = ' 08.4;; ; -5;;123;abc:=t[e_x]t;;-02.85;  '
[]
)INPUT";

    DefaultHITInterpreter interpreter;
    ASSERT_TRUE(interpreter.parse(input));
    ASSERT_EQ(32, interpreter.node_count());
    HITNodeView document = interpreter.root();
    ASSERT_EQ(2, document.child_count());
    ASSERT_EQ(2, interpreter.child_count(document.node_index()));
    ASSERT_EQ(document.child_at(0).node_index(),
              interpreter.child_index_at(document.node_index(), 0));

    std::string expected_paths = R"INPUT(/
/array01
/array01/decl (array01)
/array01/= (=)
/array01/' (')
/array01/value (d2F1:=D[F1,eta1,eta1])
/array01/value (d2F2:=D[F2,eta1,eta1])
/array01/' (')
/BlockContainer
/BlockContainer/[ ([)
/BlockContainer/decl (BlockContainer)
/BlockContainer/] (])
/BlockContainer/array02
/BlockContainer/array02/decl (array02)
/BlockContainer/array02/= (=)
/BlockContainer/array02/' (')
/BlockContainer/array02/value (08.4)
/BlockContainer/array02/; (;)
/BlockContainer/array02/; (;)
/BlockContainer/array02/; (;)
/BlockContainer/array02/value (-5)
/BlockContainer/array02/; (;)
/BlockContainer/array02/; (;)
/BlockContainer/array02/value (123)
/BlockContainer/array02/; (;)
/BlockContainer/array02/value (abc:=t[e_x]t)
/BlockContainer/array02/; (;)
/BlockContainer/array02/; (;)
/BlockContainer/array02/value (-02.85)
/BlockContainer/array02/; (;)
/BlockContainer/array02/' (')
/BlockContainer/term ([])
)INPUT";

    std::stringstream actual_paths;
    document.paths(actual_paths);
    ASSERT_EQ(expected_paths, actual_paths.str());
}
