#ifndef WASP_INTERPRETER_H
#define WASP_INTERPRETER_H
#include <vector>
#include <string>
#include <cstddef> // size_t
#include <iostream>
#include "waspcore/TreeNodePool.h"
#include "waspcore/wasp_node.h" // for UNKNOWN, DOCUMENT_ROOT NODE types

namespace wasp{


/**
 * @brief The AbstractInterpreter class to fulfill design req for parser interaction
 */
class AbstractInterpreter{
public:
    /**
     * @brief token_count acquires the number of tokens so far interpreted
     * @return the number of tokens
     */
    virtual size_t token_count()const=0;
    /**
     * @brief push appends a token
     * @param str the token's string data
     * @param type the token's type (enumeration)
     * @param token_file_offset the token's offset into the file/stream
     */
    virtual void push_token(const char * str, size_t type
              , size_t token_file_offset )=0;
    /**
     * @brief push_line appends a line to the new line buffer
     * @param line_file_offset byte offset into the file/stream for the newline
     */
    virtual void push_line_offset(size_t line_file_offset)=0;
    /**
     * @brief push_leaf create a leaf node with the given type, name, and token reference
     * @param node_type the leaf node's type enumeration
     * @param node_name the leaf node's name
     * @param token_index the leaf node's token index
     * @return the new leaf node's index in the TreeNodePool
     */
    virtual size_t push_leaf(size_t node_type
                     ,const char * node_name
                     ,size_t token_index)=0;
    /**
     * @brief push_parent create a parent node with the given type, node, and child indices
     * @param node_type the node's enumerated type
     * @param node_name the node's name
     * @param child_indices the child indices for the node
     * @return the new parent node's index in the TreeNodePool
     */
    virtual size_t push_parent(size_t node_type
                       , const char * node_name
                       , const std::vector<size_t>&child_indices )=0;
    /**
     * @brief type acquire the type of the node at the given index
     * @param node_index the node index
     * @return the type of the node from the wasp_node.h collection
     */
    virtual size_t type(size_t node_index)const=0;
    /**
     * @brief name acquire the name of the node at the given index
     * @param node_index the node index
     * @return the name of the node
     */
    virtual const char * name(size_t node_index)const=0;
    /**
     * @brief data acquire the data of the node at the given index
     * @param node_index
     * @return
     */
    virtual std::string data(size_t node_index)const=0;
    /**
     * @brief token_data acquires the data for the token at the given index
     * @param token_index the index of the token for which the data is requested
     * @return the data of the token
     */
    virtual const char * token_data( size_t token_index )const=0;

    /**
     * @brief add_root_child_index method accumulates the root node's children
     * @param node_index child node index
     * This will be flushed at the conclusion of parsing.
     */
    virtual void add_root_child_index(size_t node_index)=0;

    virtual size_t start_column()const=0;
    virtual size_t start_line()const=0;
    virtual const std::string& stream_name()const=0;
    virtual std::string& stream_name()=0;
    virtual std::ostream & error_stream()=0;
    virtual class ::FlexLexer * lexer()=0;

    virtual bool single_parse()const=0;
};

template< class TNS = TreeNodePool<> >
class Interpreter : public AbstractInterpreter {
public:
    typedef TNS TreeNodePool_type;
    typedef typename TNS::node_index_size node_index_size;
    typedef typename TNS::node_type_size node_type_size;
    typedef typename TNS::TokenPool_type::token_index_type_size token_index_type_size;
    typedef typename TNS::TokenPool_type::token_type_size token_type_size;
    typedef typename TNS::TokenPool_type::file_offset_type_size file_offset_type_size;
    Interpreter(std::ostream & error_stream=std::cerr);
    virtual ~Interpreter();

    /**
     * @brief root acquire the root of the document
     * @return TreeNodeView view into the document parse tree
     */
    TreeNodeView< TreeNodePool_type > root()const;

    /**
     * @brief node_at acquire the node at the given index in the pool
     * @param node_pool_index the index at which to acquire the node
     * @return the TreeNodeView from which data (name, type, data, children) can be conventienty acquired
     */
    TreeNodeView< TreeNodePool_type > node_at(node_index_size node_pool_index)const;


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
     * @brief token_count acquires the number of tokens so far interpreted
     * @return the number of tokens
     */
    size_t token_count()const{ return m_tree_nodes.token_data().size();}
    /**
     * @brief push appends a token
     * @param str the token's string data
     * @param type the token's type (enumeration)
     * @param token_file_offset the token's offset into the file/stream
     */
    void push_token(const char * str, size_t type
              , size_t token_file_offset )
        {m_tree_nodes.push_token(str,type,token_file_offset);}
    /**
     * @brief push_line appends a line to the new line buffer
     * @param line_file_offset byte offset into the file/stream for the newline
     */
    void push_line_offset(size_t line_file_offset)
        {m_tree_nodes.token_data().push_line(line_file_offset);}
    /**
     * @brief push_leaf create a leaf node with the given type, name, and token reference
     * @param node_type the leaf node's type enumeration
     * @param node_name the leaf node's name
     * @param token_index the leaf node's token index
     * @return the new leaf node's index in the TreeNodePool
     */
    size_t push_leaf(size_t node_type
                     ,const char * node_name
                     ,size_t token_index);
    /**
     * @brief push_parent create a parent node with the given type, node, and child indices
     * @param node_type the node's enumerated type
     * @param node_name the node's name
     * @param child_indices the child indices for the node
     * @return the new parent node's index in the TreeNodePool
     */
    size_t push_parent(size_t node_type
                       , const char * node_name
                       , const std::vector<size_t>&child_indices );
    /**
     * @brief type acquire the type of the node at the given index
     * @param node_index the node index
     * @return the type of the node from the wasp_node.h collection
     */
    size_t type(size_t node_index)const;

    /**
     * @brief node_token_type acquire the type of the toke backing the node at the given index
     * @param node_index the node for which the token type is requested.
     * @return the token type of the leaf node at the given index.
     * If the node index is out of range, wasp::UNKNOWN is returned.
     * If the node at the given index is not a leaf node, wasp::UNKNOWN is returned
     */
    token_type_size node_token_type( size_t node_index)const;
    /**
     * @brief name acquire the name of the node at the given index
     * @param node_index the node index
     * @return the name of the node
     */
    const char * name(size_t node_index)const;
    /**
     * @brief data acquire the data of the node at the given index
     * @param node_index
     * @return
     */
    std::string data(size_t node_index)const;
    /**
     * @brief token_data acquires the data for the token at the given index
     * @param token_index the index of the token for which the data is requested
     * @return the data of the token
     */
    const char * token_data( size_t token_index )const;

    size_t node_count()const{return m_tree_nodes.size();}
    size_t leaf_node_count()const{return m_tree_nodes.leaf_node_count();}
    size_t parent_node_count()const{return m_tree_nodes.parent_node_count();}
    /**
     * @brief add_root_child_index method accumulates the root node's children
     * @param node_index child node index
     * TODO make private, friend the parser
     * This will be flushed at the conclusion of parsing.
     */
    void add_root_child_index(size_t node_index)
                {m_root_child_indices.push_back(node_index);}

    virtual class ::FlexLexer * lexer()=0;
    virtual bool single_parse()const{return false;}
protected:
    template<class LEXER_IMPL
             ,class PARSER_IMPL
             ,class INTERPRETER_IMPL>
    bool parse_impl( LEXER_IMPL *& lexer
            , std::istream &input
            , const std::string& stream_name
            , size_t m_start_line
            , size_t m_start_column);

public: // variables
    /**
     * @brief m_start_column - the starting colum to start parsing at (default 1)
     */
    size_t m_start_column;
    size_t start_column()const{return m_start_column;}
    /**
     * @brief m_start_line - the starting line to start parsing at (default 1)
     */
    size_t m_start_line;
    size_t start_line()const{return m_start_line;}
    /**
     * @brief m_stream_name - stream name (file or input stream) used for error messages.
     */
    std::string m_stream_name;
    const std::string& stream_name()const{return m_stream_name;}
    std::string& stream_name(){return m_stream_name;}
    std::ostream & error_stream(){return m_error_stream;}
private:
    /**
     * @brief err - the error stream to report on
     */
    std::ostream & m_error_stream;
protected:
    std::vector<size_t> m_root_child_indices;
    size_t m_root_index;
public:
    TreeNodePool_type m_tree_nodes;
};

#include "waspcore/Interpreter.i.h"
} // end of namespace
#endif
