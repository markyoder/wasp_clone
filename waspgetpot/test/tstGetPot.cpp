#include "waspgetpot/GetPotInterpreter.h"
#include "waspgetpot/GetPotNodeView.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>
using namespace wasp;

TEST(GetPotInterpreter, bad)

{
    std::stringstream input;
    input << R"INPUT([GlobalParams]
disp_x = disp_x
disp_y = disp_y
disp_z = disp_z
[../])INPUT";
    std::stringstream   error;
    GetPotInterpreter<> interpreter(error);
    ASSERT_FALSE(interpreter.parse(input));
    ASSERT_EQ(
        "stream input:5.1-5: syntax error, unexpected subblock terminator\n",
        error.str());
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
/GlobalParams/[../] ([../])
)INPUT";
    ASSERT_EQ(expected_tree.str(), tree_print.str());
}

TEST(GetPotInterpreter, simple)
{
    std::stringstream input;
    // Simple parse
    // document
    //  |_key
    //    |_ decl 'key'
    //    |_ = '='
    //    |_ value '3.421'
    input << "key =  3.421";
    GetPotInterpreter<> interpreter;
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

TEST(GetPotInterpreter, empty_object)
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
    GetPotInterpreter<> interpreter;
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
                                           "[]", "ted",  "document"};
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

TEST(GetPotInterpreter, simple_object)
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
    GetPotInterpreter<> interpreter;
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
        "[", "decl", "]", "decl", "=", "value", "key", "[]", "ted", "document"};
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

TEST(GetPotInterpreter, less_simple_object)
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
    GetPotInterpreter<> interpreter;
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
                                           "[]",
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

TEST(GetPotInterpreter, object_array)
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
    GetPotInterpreter<> interpreter;
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
                                           "[]",
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

TEST(GetPotInterpreter, object_array_commas)
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
    //      |_ , wasp_comma
    //      |_ value 201
    //      |_ , wasp_comma
    //      |_ value again
    //      |_ , wasp_comma
    //      |_ value here
    //      |_ , wasp_comma
    //      |_ value close
    //      |_ , wasp_comma
    //      |_ value far
    //      |_ value lu
    //      |_ ' '''
    //    |_ object_term '[]'

    input << "[ted]data='basic,201 , again,here,close , far lu'[]";
    GetPotInterpreter<> interpreter;
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
                                          wasp::WASP_COMMA,
                                          wasp::VALUE,
                                          wasp::WASP_COMMA,
                                          wasp::VALUE,
                                          wasp::WASP_COMMA,
                                          wasp::VALUE,
                                          wasp::WASP_COMMA,
                                          wasp::VALUE,
                                          wasp::WASP_COMMA,
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
                                           ","  // wasp_comma
                                           ,
                                           "value"  // 201
                                           ,
                                           ","  // wasp_comma
                                           ,
                                           "value"  // again
                                           ,
                                           ","  // wasp_comma
                                           ,
                                           "value"  // here
                                           ,
                                           ","  // wasp_comma
                                           ,
                                           "value"  // close
                                           ,
                                           ","  // wasp_comma
                                           ,
                                           "value"  // far
                                           ,
                                           "value"  // lu
                                           ,
                                           "'"  // terminator
                                           ,
                                           "data",
                                           "[]",
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

TEST(GetPotInterpreter, object_empty_subobject)
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
    //        |_ sub_object_term '[../]'
    //    |_ object_term '[]'

    input << "[ted][./fred][../][]";
    GetPotInterpreter<> interpreter;
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
                                          wasp::SUB_OBJECT_TERM,
                                          wasp::SUB_OBJECT,
                                          wasp::OBJECT_TERM,
                                          wasp::OBJECT,
                                          wasp::DOCUMENT_ROOT};
    std::vector<std::string> node_names = {"[",    "decl", "]",   "[",
                                           "./",   "decl", "]",   "[../]",
                                           "fred", "[]",   "ted", "document"};
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

TEST(GetPotInterpreter, object_subobject)
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
    //              |_ sub_object_term '[../]'
    //    |_ object_term '[]'

    input << "[ted][./fred]key=3.4321[../][]";
    GetPotInterpreter<> interpreter;
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
                                          wasp::SUB_OBJECT_TERM,
                                          wasp::SUB_OBJECT,
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
                                           "[../]",
                                           "fred",
                                           "[]",
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

TEST(GetPotInterpreter, simple_view)
{
    std::stringstream input;
    // Simple parse
    // document
    //  |_key
    //    |_ decl 'key'
    //    |_ = '='
    //    |_ value '3.421'
    input << "key =  3.421";
    GetPotInterpreter<> interpreter;
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

TEST(GetPotInterpreter, paths)
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
/Problem/child/[../] ([../])
/Problem/[] ([])
)INPUT";

    GetPotInterpreter<> interpreter;
    ASSERT_TRUE(interpreter.parse(input));
    ASSERT_EQ(16, interpreter.node_count());
    auto document = interpreter.root();
    ASSERT_EQ(1, document.child_count());
    std::stringstream paths;
    document.paths(paths);
    ASSERT_EQ(expected_paths, paths.str());
}

/**
 * @brief TEST getpot doesn't support expressions natively
 * It just grabs them as strings
 */
TEST(GetPotInterpreter, expression)
{
    std::stringstream input;
    input << R"INPUT(
function = 'A*c^2*(1-c)^2+B*(c^2+6*(1-c)*(gr0^2+gr1^2+gr2^2+gr3^2)
             -4*(2-c)*(gr0^3+gr1^3+gr2^3+gr3^3)
             +3*(gr0^2+gr1^2+gr2^2+gr3^2)^2)'
)INPUT";
    std::vector<std::string> data = {
        "function",
        "=",
        "'",
        "A*c^2*(1-c)^2+B*(c^2+6*(1-c)*(gr0^2+gr1^2+gr2^2+gr3^2)",
        "-4*(2-c)*(gr0^3+gr1^3+gr2^3+gr3^3)",
        "+3*(gr0^2+gr1^2+gr2^2+gr3^2)^2)",
        "'"};

    GetPotInterpreter<> interpreter;
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
TEST(GetPotInterpreter, comments)
{
    std::stringstream input;
    input << R"INPUT(#
# comment with content
#)INPUT";
    GetPotInterpreter<> interpreter;
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
 * @brief TEST GetPot has the unfortunate ability to terminate blocks via a new
 * block
 * Test to ensure this functions as expected.
 */
TEST(GetPotInterpreter, early_terminated_object)
{
    std::stringstream input;
    // The following file has the first_block
    // with a missing terminator, explicitly terminated by
    // the [new_block].
    // The new_block has a subblock2 with a missing terminator,
    // explicitly terminated by the new_block terminator
    input << R"INPUT([first_block]
  [./subblock]
    foo=bar
  [../]
 # block terminates others
[new_block]
    # comment in new block
    [./subblock1]
        bar=foo    [../]
    [./subblock2]
        f=b
[])INPUT";

    GetPotInterpreter<> interpreter;
    ASSERT_TRUE(interpreter.parse(input));
    ASSERT_EQ(41, interpreter.node_count());
    auto document = interpreter.root();
    ASSERT_EQ(2, document.child_count());
    {
        auto first_block = document.child_at(0);
        ASSERT_EQ(5, first_block.child_count());
        std::string name = first_block.name();
        ASSERT_EQ("first_block", name);
        std::vector<std::string> names = {"[", "decl", "]", "subblock",
                                          "comment"};
        std::vector<wasp::NODE> types = {wasp::LBRACKET, wasp::DECL,
                                         wasp::RBRACKET, wasp::SUB_OBJECT,
                                         wasp::COMMENT};
        std::vector<std::size_t> line   = {1, 1, 1, 2, 5};
        std::vector<std::size_t> column = {1, 2, 13, 3, 2};
        ASSERT_EQ(names.size(), types.size());
        ASSERT_EQ(names.size(), line.size());
        ASSERT_EQ(names.size(), column.size());
        for (std::size_t i = 0; i < first_block.child_count(); ++i)
        {
            {
                SCOPED_TRACE(i);
                auto child = first_block.child_at(i);
                ASSERT_EQ(names[i], child.name());
                ASSERT_EQ(types[i], child.type());
                ASSERT_EQ(line[i], child.line());
                ASSERT_EQ(column[i], child.column());
            }
        }
    }
    {
        auto new_block = document.child_at(1);
        ASSERT_EQ(7, new_block.child_count());
        std::string name = new_block.name();
        ASSERT_EQ("new_block", name);
        std::vector<std::string> names = {
            "[", "decl", "]", "comment", "subblock1", "subblock2", "[]"};
        std::vector<wasp::NODE> types = {
            wasp::LBRACKET,   wasp::DECL,       wasp::RBRACKET,   wasp::COMMENT,
            wasp::SUB_OBJECT, wasp::SUB_OBJECT, wasp::OBJECT_TERM};
        std::vector<std::size_t> line   = {6, 6, 6, 7, 8, 10, 12};
        std::vector<std::size_t> column = {1, 2, 11, 5, 5, 5, 1};
        ASSERT_EQ(names.size(), types.size());
        ASSERT_EQ(names.size(), line.size());
        ASSERT_EQ(names.size(), column.size());
        for (std::size_t i = 0; i < new_block.child_count(); ++i)
        {
            {
                SCOPED_TRACE(i);
                auto child = new_block.child_at(i);
                ASSERT_EQ(names[i], child.name());
                ASSERT_EQ(types[i], child.type());
                ASSERT_EQ(line[i], child.line());
                ASSERT_EQ(column[i], child.column());
            }
        }
    }
}

/**
 * @brief TEST nested subblocks (subblocks within subblocks)
 */
TEST(GetPotInterpreter, nested_subblocks)
{
    std::stringstream input;
    input << R"INPUT([block]
  [./subblock]
    [./nested_subblock]
    [../]
  [../]
[])INPUT";
    GetPotInterpreter<> interpreter;
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
    ASSERT_EQ(wasp::SUB_OBJECT, subblock.type());
    ASSERT_EQ(6, subblock.child_count());
    auto nestedsubblock = subblock.child_at(4);
    ASSERT_EQ("nested_subblock", std::string(nestedsubblock.name()));
    ASSERT_EQ(wasp::SUB_OBJECT, nestedsubblock.type());
    ASSERT_EQ(3, nestedsubblock.line());
    ASSERT_EQ(5, nestedsubblock.column());
}

TEST(GetPotInterpreter, multiple_objects)
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

    GetPotInterpreter<> interpreter;
    ASSERT_TRUE(interpreter.parse(input));
    ASSERT_EQ(55, interpreter.node_count());
    GetPotNodeView document = interpreter.root();
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
/Problem/[] ([])
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
/Mesh/[] ([])
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
/1/2/[../] ([../])
/1/[] ([])
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
 * @brief TEST getpot type promotion
 * When a block/subblock has a type field,
 * the block/subblock name becomes the type field's value
 * with "_type" appended.
 *
 * Test each scenario for block and subblock
 * 1. block with only type = value
 * 2. block with type = value and other stuff
 * 3. subblock with only type = value
 * 4. subblock with type = value and other stuff
 * 5. subblock with type = value but no subblock terminator
 * 6. block with type = value but no block terminator
 */
TEST(GetPotInterpreter, type_promotion)
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
[p2]
   type = t2
    [./s3]
        type = us3
[]
)INPUT";

    GetPotInterpreter<> interpreter;
    ASSERT_TRUE(interpreter.parse(input));
    ASSERT_EQ(61, interpreter.node_count());
    GetPotNodeView document = interpreter.root();
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
/ted_type/fred_type/[../] ([../])
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
/ted_type/x_type/[../] ([../])
/ted_type/[] ([])
/t1_type
/t1_type/[ ([)
/t1_type/decl (p1)
/t1_type/] (])
/t1_type/type
/t1_type/type/decl (type)
/t1_type/type/= (=)
/t1_type/type/value (t1)
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
/t2_type/[] ([])
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
