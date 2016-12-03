#include "waspcore/TreeNodePool.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

using namespace wasp;

// fake type enumerations
char decl = 0;
char term = 1;
char integer = 2;
char real = 3;
char word = 4;
char paren = 5;
char value = 6;
char id = 7;
char array = 8;
char assign = 9;
char root = 10;
/**
 * @brief TEST push test
 * 'root'
 *  |_ 'data'
 *    |_ 'array'
 *    |_ '('
 *    |_ 'foo'
 *    |_ ')'
 *    |_ '234'
 *    |_ '1.2343'
 *    |_ 'end'
 *  |_ 'attr'
 *    |_ 'key'
 *    |_ '='
 *    |_ '1.23'
 */
TEST(TreeNodePool,push_test)
{
    //'array (foo) 234 1.2343 end\n' // data
    // 0     67  1011  15     22     // offsets
    //'key = 1.23'                   // data
    //'26  3032                      // offsets
    TreeNodePool<char,char,char,char,default_file_offset_type_size> tp;
    std::vector<char> root_child_indices;
    { // push first line's contents
        std::vector<std::string> token_data=
        {"array","(","foo",")","234","1.2343","end"};
        std::vector<std::string> node_name=
        {"decl","op","id","cp","value","value","term"};
        std::vector<char> node_type =
        {decl,paren,id,paren,value,value,term};
        std::vector<char> token_type =
        {word,paren,word,paren,integer,real,term};
        std::vector<default_file_offset_type_size> token_offset=
        {0,6,7,10,11,15,22};

        ASSERT_EQ(token_data.size(),node_name.size());
        ASSERT_EQ(token_data.size(),node_type.size());
        ASSERT_EQ(token_data.size(),token_type.size());
        ASSERT_EQ(token_data.size(),token_offset.size());
        std::vector<char> child_indices;
        for(std::size_t i = 0; i < token_data.size(); ++i)
        {
            {
            SCOPED_TRACE(i);
            // capture index of new leaf node
            child_indices.push_back(static_cast<char>(i));
            tp.push_leaf(node_type[i],node_name[i].c_str()
                         ,token_type[i],token_offset[i]
                         ,token_data[i].c_str());
            ASSERT_EQ(i, tp.leaf_index(i)); // already leaf, so same index
            ASSERT_EQ(1, tp.line(i));
            ASSERT_EQ(node_type[i],tp.type(i));
            ASSERT_EQ(node_name[i],tp.name(i));
            ASSERT_EQ(token_offset[i]+1, tp.column(i));
            ASSERT_EQ(i+1, tp.size());
            ASSERT_EQ( token_type[i], tp.node_token_type(i) );
            }
        }
        // add parent node
        std::string parent_name = "data";
        char parent_type = array;
        // create parent node with type, name, and children
        root_child_indices.push_back(tp.size()); // capture
        tp.push_parent(parent_type,parent_name.c_str(),child_indices);
        ASSERT_EQ(7+1, tp.size());
        ASSERT_EQ(0, tp.leaf_index(tp.size()-1)); // parent of first leaf node
        ASSERT_EQ(1,tp.line(tp.size()-1));
        ASSERT_EQ(1,tp.column(tp.size()-1));
        default_file_offset_type_size line_offset
                = token_offset.back()+token_data.back().size();
        ASSERT_EQ(25, line_offset);
        tp.push_line(line_offset);
    } // done with first line
    { // push second line
        //'key = 1.23'      // data
        //'26  3032         // offsets
        std::vector<std::string> token_data=
        {"key","=","1.23"};
        std::vector<std::string> node_name=
        {"decl","assign","value"};
        std::vector<char> node_type =
        {decl,assign,value};
        std::vector<char> token_type =
        {word,assign,real};
        std::vector<default_file_offset_type_size> token_offset=
        {26,30,32};

        ASSERT_EQ(token_data.size(),node_name.size());
        ASSERT_EQ(token_data.size(),node_type.size());
        ASSERT_EQ(token_data.size(),token_type.size());
        ASSERT_EQ(token_data.size(),token_offset.size());
        std::vector<char> child_indices;
        for(std::size_t i = 0; i < token_data.size(); ++i)
        {
            {
            SCOPED_TRACE(i);
            std::size_t node_index = tp.size();
            // capture index of new leaf node
            child_indices.push_back(static_cast<char>(node_index));
            tp.push_leaf(node_type[i],node_name[i].c_str()
                         ,token_type[i],token_offset[i]
                         ,token_data[i].c_str());
            ASSERT_EQ(node_index, tp.leaf_index(node_index)); // already leaf, so same index
            ASSERT_EQ(2, tp.line(node_index));
            ASSERT_EQ(token_offset[i]-token_offset.front()+1
                        , tp.column(node_index));
            ASSERT_EQ(node_index+1, tp.size());
            ASSERT_EQ( token_type[i], tp.node_token_type(node_index) );
            }
        }
        // add parent node
        std::string parent_name = "data";
        char parent_type = array;
        // create parent node with type, name, and children
        root_child_indices.push_back(tp.size()); // capture
        tp.push_parent(parent_type,parent_name.c_str(),child_indices);
        ASSERT_EQ(7+1+3+1, tp.size());
        ASSERT_EQ(8, tp.leaf_index(tp.size()-1)); // parent of first leaf node
        ASSERT_EQ(2,tp.line(tp.size()-1));
        ASSERT_EQ(1,tp.column(tp.size()-1));
    }
    std::string root_name = "root";
    tp.push_parent(root,root_name.c_str(),root_child_indices);
    ASSERT_EQ(root_name,tp.name(tp.size()-1));
    ASSERT_EQ(root, tp.type(tp.size()-1));
}

