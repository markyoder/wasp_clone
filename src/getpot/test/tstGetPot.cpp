#include "../GetPotInterpreter.h"
#include "wasp_harness.h"
#include <iostream>
#include <string>
using namespace wasp;


WASP_TESTS
TEST(GetPotInterpreter,simple)
{
    std::stringstream input;
    // Simple parse
    // document
    //  |_key
    //    |_ decl 'key'
    //    |_ = '='
    //    |_ value '3.421'
    input << "key =  3.421";
    GetPotInterpreter interpreter;
    W_ASSERT_EQ( true, interpreter.parse(input) );
    W_ASSERT_EQ(5, interpreter.node_count() );

    std::vector<std::string> token_data = {"key","=","3.421"};
    std::vector<std::string> leaf_node_names = {"decl","=","value"};
    std::vector<wasp::NODE> leaf_node_types = {wasp::DECL,wasp::ASSIGN
                                                ,wasp::VALUE};
    for( size_t i = 0; i < 3; ++i)
    {
        W_ASSERT_EQ(token_data[i], interpreter.m_tree_nodes.data(i));
        W_ASSERT_EQ(leaf_node_types[i], interpreter.m_tree_nodes.type(i));
        W_ASSERT_EQ(leaf_node_names[i], interpreter.m_tree_nodes.name(i))
    }
    std::vector<size_t> parent_indices = {3,3,3,4,5};
    std::vector<size_t> child_count = {0,0,0,3,1};
    std::vector<size_t> column = {1,5,8,1,1};
    std::vector<wasp::NODE> node_types = {wasp::DECL,wasp::ASSIGN
                                           ,wasp::VALUE,wasp::KEYED_VALUE
                                          ,wasp::DOCUMENT_ROOT};
    std::vector<std::string> node_names = {"decl","=","value"
                                           ,"key","document"};
    W_ASSERT_EQ( node_types.size(), node_names.size() );
    W_ASSERT_EQ( node_types.size(), parent_indices.size() );
    W_ASSERT_EQ( node_types.size(), child_count.size() );
    W_ASSERT_EQ( node_types.size(), column.size() );
    for( size_t i = 0; i < interpreter.node_count(); ++i )
    {
        W_ASSERT_EQ(node_types[i], interpreter.m_tree_nodes.type(i));
        W_ASSERT_EQ(node_names[i], interpreter.m_tree_nodes.name(i));
        W_ASSERT_EQ(parent_indices[i],interpreter.m_tree_nodes.parent_node_index(i));
        W_ASSERT_EQ(child_count[i], interpreter.m_tree_nodes.child_count(i));
        W_ASSERT_EQ(child_count[i], interpreter.m_tree_nodes.child_count(i));
        W_ASSERT_EQ( column[i], interpreter.m_tree_nodes.column(i));
        W_ASSERT_EQ( 1, interpreter.m_tree_nodes.line(i));
    }
}
TEST_END(GetPotInterpreter,simple)

TEST(GetPotInterpreter,empty_object)
{
    std::stringstream input;
    // Simple parse
    // document
    //  |_object
    //    |_ object_decl 'ted'
    //      |_ [ '['
    //      |_ string 'ted'
    //      |_ ] ']'
    //    |_ object_term '[]'

    input << "[ted][]";
    GetPotInterpreter interpreter;
    W_ASSERT_EQ( true, interpreter.parse(input) );
    W_ASSERT_EQ(7, interpreter.node_count() );

    std::vector<std::string> token_data = {"[","ted","]"};
    std::vector<std::string> leaf_node_names = {"[","string","]"};
    std::vector<wasp::NODE> leaf_node_types = {wasp::LBRACKET,wasp::STRING
                                           ,wasp::RBRACKET};
    for( size_t i = 0; i < 3; ++i)
    {
        W_ASSERT_EQ(token_data[i], interpreter.m_tree_nodes.data(i));
        W_ASSERT_EQ(leaf_node_types[i], interpreter.m_tree_nodes.type(i));
        W_ASSERT_EQ(leaf_node_names[i], interpreter.m_tree_nodes.name(i))
    }
    std::vector<wasp::NODE> node_types = {wasp::LBRACKET,wasp::STRING
                                           ,wasp::RBRACKET,wasp::OBJECT_DECL
                                           ,wasp::OBJECT_TERM
                                           ,wasp::OBJECT
                                          ,wasp::DOCUMENT_ROOT};
    std::vector<std::string> node_names = {"[","string","]","ted"
                                           ,"[]"
                                           ,"ted","document"};
    W_ASSERT_EQ( node_types.size(), node_names.size() );
    for( size_t i = 0; i < interpreter.node_count(); ++i )
    {
        W_ASSERT_EQ(node_types[i], interpreter.m_tree_nodes.type(i));
        W_ASSERT_EQ(node_names[i], interpreter.m_tree_nodes.name(i))
    }
}
TEST_END(GetPotInterpreter,empty_object)
TEST(GetPotInterpreter,simple_object)
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
    GetPotInterpreter interpreter;
    W_ASSERT_EQ( true, interpreter.parse(input) );
    W_ASSERT_EQ(11, interpreter.node_count() );

                                           // object decl
    std::vector<wasp::NODE> node_types = {wasp::LBRACKET,wasp::STRING
                                           ,wasp::RBRACKET,wasp::OBJECT_DECL
                                           // keyed value
                                           ,wasp::DECL,wasp::ASSIGN
                                           ,wasp::VALUE,wasp::KEYED_VALUE
                                           // object term
                                           ,wasp::OBJECT_TERM
                                           // object
                                           ,wasp::OBJECT
                                           // document root
                                          ,wasp::DOCUMENT_ROOT};
    std::vector<std::string> node_names = {"[","string","]","ted"
                                           ,"decl","=","value"
                                           ,"key"
                                           ,"[]"
                                           ,"ted","document"};
    W_ASSERT_EQ( node_types.size(), node_names.size() );
    for( size_t i = 0; i < interpreter.node_count(); ++i )
    {
        W_ASSERT_EQ(node_types[i], interpreter.m_tree_nodes.type(i));
        W_ASSERT_EQ(node_names[i], interpreter.m_tree_nodes.name(i))
    }
}
TEST_END(GetPotInterpreter,simple_object)

TEST(GetPotInterpreter,less_simple_object)
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

    input << "[ted]"<<std::endl;
    input << "    boo = foo # halloween "<<std::endl;
    input << "    fred = 1"<<std::endl;
    input << "    key = 3.421"<<std::endl;
    input << "[]";
    GetPotInterpreter interpreter;
    W_ASSERT_EQ( true, interpreter.parse(input) );
    W_ASSERT_EQ(20, interpreter.node_count() );

                                           // object decl
    std::vector<wasp::NODE> node_types = {wasp::LBRACKET,wasp::STRING
                                           ,wasp::RBRACKET,wasp::OBJECT_DECL
                                           // keyed value boo
                                           ,wasp::DECL,wasp::ASSIGN
                                           ,wasp::VALUE,wasp::KEYED_VALUE
                                           // comment
                                           ,wasp::COMMENT
                                           // keyed value fred
                                           ,wasp::DECL,wasp::ASSIGN
                                           ,wasp::VALUE,wasp::KEYED_VALUE
                                           // keyed value key
                                           ,wasp::DECL,wasp::ASSIGN
                                           ,wasp::VALUE,wasp::KEYED_VALUE
                                           // object term
                                           ,wasp::OBJECT_TERM
                                           // object
                                           ,wasp::OBJECT
                                           // document root
                                          ,wasp::DOCUMENT_ROOT};
    std::vector<std::string> node_names = {"[","string","]","ted"
                                           ,"decl","=","value" // boo
                                           ,"boo"
                                           ,"comment" // halloween
                                           ,"decl","=","value" // fred
                                           ,"fred"
                                           ,"decl","=","value" // key
                                           ,"key"
                                           ,"[]"
                                           ,"ted","document"};
    W_ASSERT_EQ( node_types.size(), node_names.size() );
    for( size_t i = 0; i < interpreter.node_count(); ++i )
    {
        W_ASSERT_EQ(node_types[i], interpreter.m_tree_nodes.type(i));
        W_ASSERT_EQ(node_names[i], interpreter.m_tree_nodes.name(i))
    }
}
TEST_END(GetPotInterpreter,less_simple_object)
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
    GetPotInterpreter interpreter;
    W_ASSERT_EQ( true, interpreter.parse(input) );
    W_ASSERT_EQ(15, interpreter.node_count() );

    std::vector<wasp::NODE> node_types = {wasp::LBRACKET,wasp::STRING
                                           ,wasp::RBRACKET,wasp::OBJECT_DECL
                                           // keyed value array data
                                           ,wasp::DECL,wasp::ASSIGN
                                           , wasp::QUOTE
                                           , wasp::VALUE
                                           , wasp::VALUE
                                           , wasp::VALUE
                                           , wasp::QUOTE
                                           , wasp::KEYED_VALUE
                                           ,wasp::OBJECT_TERM
                                           ,wasp::OBJECT
                                          ,wasp::DOCUMENT_ROOT};
    std::vector<std::string> node_names = {"[","string","]","ted"
                                           ,"decl","="// data array
                                           ,"'" // start
                                           ,"value" // basic
                                           ,"value" // 201
                                           ,"value" // lu
                                           ,"'" // terminator
                                           ,"data"
                                           ,"[]"
                                           ,"ted","document"};
    W_ASSERT_EQ( node_types.size(), node_names.size() );
    for( size_t i = 0; i < interpreter.node_count(); ++i )
    {
        W_ASSERT_EQ(node_types[i], interpreter.m_tree_nodes.type(i));
        W_ASSERT_EQ(node_names[i], interpreter.m_tree_nodes.name(i))
    }
}
TEST_END(GetPotInterpreter,object_array)
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
    GetPotInterpreter interpreter;
    W_ASSERT_EQ( true, interpreter.parse(input) );
    W_ASSERT_EQ(14, interpreter.node_count() );

    std::vector<wasp::NODE> node_types = {wasp::LBRACKET
                                          ,wasp::STRING
                                           ,wasp::RBRACKET
                                          ,wasp::OBJECT_DECL
                                           // sub object
                                           ,wasp::LBRACKET
                                          ,wasp::DOT_SLASH
                                          ,wasp::STRING
                                          ,wasp::RBRACKET
                                          ,wasp::SUB_OBJECT_DECL
                                           ,wasp::SUB_OBJECT_TERM
                                          ,wasp::SUB_OBJECT
                                           ,wasp::OBJECT_TERM
                                           ,wasp::OBJECT
                                          ,wasp::DOCUMENT_ROOT};
    std::vector<std::string> node_names = {"["
                                           ,"string"
                                           ,"]"
                                           ,"ted"
                                           ,"["
                                           ,"./"
                                           ,"string"
                                           ,"]"
                                           ,"fred"
                                           ,"[../]"
                                           ,"fred"
                                           ,"[]"
                                           ,"ted","document"};
    W_ASSERT_EQ( node_types.size(), node_names.size() );
    for( size_t i = 0; i < interpreter.node_count(); ++i )
    {
        W_ASSERT_EQ(node_types[i], interpreter.m_tree_nodes.type(i));
        W_ASSERT_EQ(node_names[i], interpreter.m_tree_nodes.name(i))
    }
}
TEST_END(GetPotInterpreter,object_empty_subobject)
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
    GetPotInterpreter interpreter;
    W_ASSERT_EQ( true, interpreter.parse(input) );
    W_ASSERT_EQ(18, interpreter.node_count() );

    std::vector<wasp::NODE> node_types = {wasp::LBRACKET
                                          ,wasp::STRING
                                           ,wasp::RBRACKET
                                          ,wasp::OBJECT_DECL
                                           // sub object
                                           ,wasp::LBRACKET
                                          ,wasp::DOT_SLASH
                                          ,wasp::STRING
                                          ,wasp::RBRACKET
                                          ,wasp::SUB_OBJECT_DECL
                                          // keyed value key
                                          ,wasp::DECL,wasp::ASSIGN
                                          ,wasp::VALUE,wasp::KEYED_VALUE
                                           ,wasp::SUB_OBJECT_TERM
                                          ,wasp::SUB_OBJECT
                                           ,wasp::OBJECT_TERM
                                           ,wasp::OBJECT
                                          ,wasp::DOCUMENT_ROOT};
    std::vector<std::string> node_names = {"["
                                           ,"string"
                                           ,"]"
                                           ,"ted"
                                           ,"["
                                           ,"./"
                                           ,"string"
                                           ,"]"
                                           ,"fred"
                                           ,"decl","=","value" // key
                                           ,"key"
                                           ,"[../]"
                                           ,"fred"
                                           ,"[]"
                                           ,"ted","document"};
    W_ASSERT_EQ( node_types.size(), node_names.size() );
    for( size_t i = 0; i < interpreter.node_count(); ++i )
    {
        W_ASSERT_EQ(node_types[i], interpreter.m_tree_nodes.type(i));
        W_ASSERT_EQ(node_names[i], interpreter.m_tree_nodes.name(i))
    }
}
TEST_END(GetPotInterpreter,object_subobject)

TEST(GetPotInterpreter,simple_view)
{
    std::stringstream input;
    // Simple parse
    // document
    //  |_key
    //    |_ decl 'key'
    //    |_ = '='
    //    |_ value '3.421'
    input << "key =  3.421";
    GetPotInterpreter interpreter;
    W_ASSERT_EQ( true, interpreter.parse(input) );
    W_ASSERT_EQ(5, interpreter.node_count() );

    std::vector<wasp::NODE> node_types = {wasp::DECL,wasp::ASSIGN
                                           ,wasp::VALUE,wasp::KEYED_VALUE
                                          ,wasp::DOCUMENT_ROOT};
    std::vector<std::string> node_names = {"decl","=","value"
                                           ,"key","document"};
    std::vector<std::string> node_paths = {"/key/decl","/key/=","/key/value"
                                           ,"/key","/"};
    std::vector<size_t> node_columns = {1,5,8,1,1};
    W_ASSERT_EQ(node_types.size(), node_names.size());
    W_ASSERT_EQ(node_types.size(), node_columns.size());
    W_ASSERT_EQ(node_types.size(), node_paths.size());
    TreeNodeView document = interpreter.root();
    // the root of the document
    W_ASSERT_EQ( 1, document.child_count() );
    W_ASSERT_EQ( node_names.back(), document.name() );
    W_ASSERT_EQ(wasp::DOCUMENT_ROOT, document.type());
    W_ASSERT_EQ( 1, document.line() );
    W_ASSERT_EQ( 1, document.column() );
    W_ASSERT_EQ( true, document.equal(document) );
    W_ASSERT_EQ( false, document.has_parent() );
    W_ASSERT_EQ( node_paths.back(), document.path() );
    TreeNodeView key = document.child_at(0);
    W_ASSERT_EQ(3, key.child_count() );
    W_ASSERT_EQ( true, key.has_parent() );
    W_ASSERT_EQ( true, document.equal(key.parent()) );
    W_ASSERT_EQ(wasp::KEYED_VALUE,key.type());
    W_ASSERT_EQ( node_names[3], key.name() );
    W_ASSERT_EQ( 1, key.line() );
    W_ASSERT_EQ( 1, key.column() );
    W_ASSERT_EQ( false, document.equal(key) )
    W_ASSERT_EQ( node_paths[3], key.path() );
    // TODO add test on data (type, line, col, etc).
    for( size_t i = 0, child_count = key.child_count(); i < child_count; ++i)
    {
        TreeNodeView child = key.child_at(i);
        W_ASSERT_EQ( node_types[i],child.type() );
        W_ASSERT_EQ( 0, child.child_count() );
        W_ASSERT_EQ( node_types[i],child.type() );
        W_ASSERT_EQ( node_names[i], child.name() );
        W_ASSERT_EQ( 1, child.line() );
        W_ASSERT_EQ( node_columns[i], child.column() );
        W_ASSERT_EQ( true, child.has_parent() );
        W_ASSERT_EQ( true, key.equal(child.parent()));
        W_ASSERT_EQ( node_paths[i],child.path() );
    }
    std::string expected_paths
            = "/\n/key\n/key/decl (key)\n/key/= (=)\n/key/value (3.421)\n";
    std::stringstream paths; document.paths(paths);
    W_ASSERT_EQ(expected_paths, paths.str() );
}
TEST_END(GetPotInterpreter,simple_view)

TEST(GetPotInterpreter,paths)
{
    std::stringstream input;
    input <<R"INPUT(
[Problem]
  coord_type = RZ
  [./child][../]
[])INPUT";
    GetPotInterpreter interpreter;
    W_ASSERT_EQ( true, interpreter.parse(input) );
    W_ASSERT_EQ(18, interpreter.node_count() );

    std::string expected_paths=
R"INPUT(/
/Problem
/Problem/Problem
/Problem/Problem/[ ([)
/Problem/Problem/string (Problem)
/Problem/Problem/] (])
/Problem/coord_type
/Problem/coord_type/decl (coord_type)
/Problem/coord_type/= (=)
/Problem/coord_type/value (RZ)
/Problem/child
/Problem/child/child
/Problem/child/child/[ ([)
/Problem/child/child/./ (./)
/Problem/child/child/string (child)
/Problem/child/child/] (])
/Problem/child/[../] ([../])
/Problem/[] ([])
)INPUT";

    TreeNodeView document = interpreter.root();
    W_ASSERT_EQ(1, document.child_count() );
    std::stringstream paths;
    document.paths(paths);
    W_ASSERT_EQ( expected_paths, paths.str() );
}
TEST_END(GetPotInterpreter,paths)

WASP_TESTS_END
