#ifndef WASP_GETPOTINTERPRETER_H
#define WASP_GETPOTINTERPRETER_H
#include <vector>
#include <string>
#include "wasp/core/TreeNodePool.h"
#include "GetPotParser.hpp"

namespace wasp{

class GetPotInterpreter{
public:
    GetPotInterpreter(std::ostream & error_stream=std::cerr);
    ~GetPotInterpreter();

    /**
     * @brief root acquire the root of the document
     * @return TreeNodeView view into the document parse tree
     */
    TreeNodeView root()const;

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
    bool parse(std::istream &input, size_t m_start_line=1u, size_t m_start_column=1u);

    /**
     * @brief push_leaf create a leaf node with the given type, name, and token reference
     * @param node_type the leaf node's type enumeration
     * @param node_name the leaf node's name
     * @param token_index the leaf node's token index
     * @return the new leaf node's index in the TreeNodePool
     */
    size_t push_leaf(default_node_type_size node_type
                     ,const char * node_name
                     ,default_token_index_type_size token_index);
    /**
     * @brief push_parent create a parent node with the given type, node, and child indices
     * @param node_type the node's enumerated type
     * @param node_name the node's name
     * @param child_indices the child indices for the node
     * @return the new parent node's index in the TreeNodePool
     */
    size_t push_parent(default_node_type_size node_type
                       , const char * node_name
                       , const std::vector<default_node_index_size>&child_indices );

    size_t node_count()const{return m_tree_nodes.size();}
    size_t leaf_node_count()const{return m_tree_nodes.leaf_node_count();}
    size_t parent_node_count()const{return m_tree_nodes.parent_node_count();}
    /**
     * @brief add_root_child_index method accumulates the root node's children
     * @param node_index child node index
     * TODO make private, friend the parser
     * This will be flushed at the conclusion of parsing.
     */
    void add_root_child_index(default_token_index_type_size node_index)
                {m_root_child_indices.push_back(node_index);}
public: // variables
    /**
     * @brief lexer - current lexer instance
     */
    class GetPotLexerImpl* m_lexer;
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

    std::vector<default_node_index_size> m_root_child_indices;
    size_t m_root_index;
public:
    TreeNodePool<> m_tree_nodes;
};
} // end of namespace
#endif
