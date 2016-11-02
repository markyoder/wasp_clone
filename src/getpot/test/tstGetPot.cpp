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
    std::vector<wasp::NODE> node_types = {wasp::DECL,wasp::ASSIGN
                                           ,wasp::VALUE,wasp::KEYED_VALUE
                                          ,wasp::DOCUMENT_ROOT};
    std::vector<std::string> node_names = {"decl","=","value"
                                           ,"key","document"};
    for( size_t i = 0; i < interpreter.node_count(); ++i )
    {
        W_ASSERT_EQ(node_types[i], interpreter.m_tree_nodes.type(i));
        W_ASSERT_EQ(node_names[i], interpreter.m_tree_nodes.name(i))
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
    for( size_t i = 0; i < interpreter.node_count(); ++i )
    {
        W_ASSERT_EQ(node_types[i], interpreter.m_tree_nodes.type(i));
        W_ASSERT_EQ(node_names[i], interpreter.m_tree_nodes.name(i))
    }
}
TEST_END(GetPotInterpreter,object_array)
WASP_TESTS_END
