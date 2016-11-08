#ifndef WASP_INTERPRETER_H
#define WASP_INTERPRETER_H
#include <vector>
#include <string>
#include <iostream>
#include "waspcore/TreeNodePool.h"

namespace wasp{

template<
         // size type describing node type maximum
         typename node_type_size =  default_node_type_size
         // size type describing node occurrence maximum
         ,typename node_index_size = default_node_index_size
         // size type describing token type maximum token type count
         ,typename token_type_size = default_token_type_size
         // size type describing maximum number of tokens
         ,typename token_index_type_size = default_token_index_type_size
         // size type describing the maximum byte file offset
         ,typename file_offset_type_size = default_file_offset_type_size
     >
class Interpreter{
public:
    Interpreter(std::ostream & error_stream=std::cerr);
    virtual ~Interpreter();

    /**
     * @brief root acquire the root of the document
     * @return TreeNodeView view into the document parse tree
     */
    TreeNodeView root()const;

    /**
     * @brief node_at acquire the node at the given index in the pool
     * @param node_pool_index the index at which to acquire the node
     * @return the TreeNodeView from which data (name, type, data, children) can be conventienty acquired
     */
    TreeNodeView node_at(node_index_size node_pool_index)const;
    /**
     * @brief child_count acquire the number of child nodes for the current node
     * @return child node count
     */
    size_t child_count()const;

    /**
     * @brief parse parser the given input stream
     * @param input the stream of the input data
     * @param startLine the first line of the input stream
     * @param startColumn the first column of the input stream
     * @return true, iff no input processing errors were encountered
     */
    virtual bool parse(std::istream &input
                       , size_t m_start_line=1u
                       , size_t m_start_column=1u)=0;

    /**
     * @brief push_leaf create a leaf node with the given type, name, and token reference
     * @param node_type the leaf node's type enumeration
     * @param node_name the leaf node's name
     * @param token_index the leaf node's token index
     * @return the new leaf node's index in the TreeNodePool
     */
    size_t push_leaf(node_type_size node_type
                     ,const char * node_name
                     ,token_index_type_size token_index);
    /**
     * @brief push_parent create a parent node with the given type, node, and child indices
     * @param node_type the node's enumerated type
     * @param node_name the node's name
     * @param child_indices the child indices for the node
     * @return the new parent node's index in the TreeNodePool
     */
    size_t push_parent(node_type_size node_type
                       , const char * node_name
                       , const std::vector<node_index_size>&child_indices );

    size_t node_count()const{return m_tree_nodes.size();}
    size_t leaf_node_count()const{return m_tree_nodes.leaf_node_count();}
    size_t parent_node_count()const{return m_tree_nodes.parent_node_count();}
    /**
     * @brief add_root_child_index method accumulates the root node's children
     * @param node_index child node index
     * TODO make private, friend the parser
     * This will be flushed at the conclusion of parsing.
     */
    void add_root_child_index(token_index_type_size node_index)
                {m_root_child_indices.push_back(node_index);}
public: // variables
    /**
     * @brief m_start_column - the starting colum to start parsing at (default 1)
     */
    size_t m_start_column;
    /**
     * @brief m_start_line - the starting line to start parsing at (default 1)
     */
    size_t m_start_line;
    /**
     * @brief m_stream_name - stream name (file or input stream) used for error messages.
     */
    std::string m_stream_name;
    /**
     * @brief error - Error handling with associated line number. This can be modified to
     * @param l - the location of the error
     * @param m - the error message
     */
    void error(const class location& l, const std::string& m);
private:
    /**
     * @brief err - the error stream to report on
     */
    std::ostream & m_error_stream;
protected:
    std::vector<node_index_size> m_root_child_indices;
    size_t m_root_index;
public:
    TreeNodePool<node_type_size,node_index_size
        ,token_type_size,token_index_type_size
        ,file_offset_type_size> m_tree_nodes;
};
#include "waspcore/Interpreter.i.h"
} // end of namespace
#endif
