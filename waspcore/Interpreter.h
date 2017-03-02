#ifndef WASP_INTERPRETER_H
#define WASP_INTERPRETER_H
#include <vector>
#include <string>
#include <cstddef> // size_t
#include <iostream>
#include "waspcore/TreeNodePool.h"
#include "waspcore/wasp_node.h" // for UNKNOWN, DOCUMENT_ROOT NODE types
#include "waspcore/wasp_bug.h"
#include "waspcore/Definition.h"

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

    virtual bool set_name(size_t node_index, const char * name)=0;
    virtual void set_type(size_t node_index, size_t node_type)=0;
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
     * @brief child_count determines the number of children for the node
     * @param node_index index of the node of which children count are requested
     * @return the number of children nodes
     */
    virtual size_t child_count(size_t node_index)const=0;
    /**
     * @brief child_index_at acquire the index of the given child
     * @param node_index the index of the parent node from which child_index is relative
     * @param child_index the relative child index
     * @return the index of the child at the requested index
     */
    virtual size_t child_index_at( size_t node_index, size_t child_index)const=0;
    /**
     * @brief push_staged stages the given node for child accrual and later commitment
     * @param node_type the type of the node, i.e., WASP::DOCUMENT_ROOT
     * @param node_name the name of the node, i.e., "document"
     * @param child_indices the indices of any known children in the tree node pool
     * @return the number of stages
     * This method is used for managing tree creation. This most frequently
     * is associated with creating the root document node once all children
     * have been processed and are staged.
     */
    virtual size_t push_staged(size_t node_type
                     , const std::string& node_name
                     , const std::vector<size_t>&child_indices )=0;
    /**
     * @brief push_staged_child adds the given child index to the currently staged node
     * @param child_index the index of the adopted child
     * @return the number of children for the current stage
     */
    virtual size_t push_staged_child(size_t child_index)=0;
    virtual size_t push_staged_child(const std::vector<size_t>& child_indices) = 0;
    /**
     * @brief commit_staged commits the staged tree node
     * @param stage_index the stage at which to commit to the tree
     * @return the new tree node's index into the tree node pool
     * The new tree node is added to the parent stage's list of
     * children
     */
    virtual size_t commit_staged(size_t stage_index)=0;

    virtual const size_t& staged_type(size_t staged_index)const = 0;
    virtual size_t& staged_type(size_t staged_index) = 0;

    virtual const std::string& staged_name(size_t staged_index)const = 0;
    virtual std::string& staged_name(size_t staged_index) = 0;

    virtual size_t staged_count()const = 0;

    virtual size_t start_column()const=0;
    virtual size_t start_line()const=0;
    virtual const std::string& stream_name()const=0;
    virtual std::string& stream_name()=0;
    virtual std::ostream & error_stream()=0;    

    virtual const Definition::SP& definition()const{wasp_not_implemented("definition");}
    virtual Definition::SP& definition(){wasp_not_implemented("definition");}

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
    bool set_name(size_t node_index, const char * name);
    void set_type(size_t node_index, size_t node_type);
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
    /**
     * @brief child_count determines the number of children for the node
     * @param node_index index of the node of which children count are requested
     * @return the number of children nodes
     */
    size_t child_count(size_t node_index) const;
    /**
     * @brief child_index_at acquire the index of the given child
     * @param node_index the index of the parent node from which child_index is relative
     * @param child_index the relative child index
     * @return the index of the child at the requested index
     */
    size_t child_index_at( size_t node_index, size_t child_index)const;
    size_t node_count()const{return m_tree_nodes.size();}
    size_t leaf_node_count()const{return m_tree_nodes.leaf_node_count();}
    size_t parent_node_count()const{return m_tree_nodes.parent_node_count();}

    /**
     * @brief push_staged stages the given node for child accrual and later commitment
     * @param node_type the type of the node, i.e., WASP::DOCUMENT_ROOT
     * @param node_name the name of the node, i.e., "document"
     * @param child_indices the indices of any known children in the tree node pool
     * @return the number of stages
     * This method is used for managing tree creation. This most frequently
     * is associated with creating the root document node once all children
     * have been processed and are staged.
     */
    size_t push_staged(size_t node_type
                     , const std::string& node_name
                     , const std::vector<size_t>&child_indices );

    /**
     * @brief push_staged_child adds the given child index to the currently staged node
     * @param child_index the index of the adopted child
     * @return the number of children for the current stage
     */
    size_t push_staged_child(size_t child_index);
    size_t push_staged_child(const std::vector<size_t>& child_indices)
    {
        wasp_require( m_staged.empty() == false );
        size_t child_count = 0;
        for( size_t child_index : child_indices) {
            child_count = push_staged_child(child_index);
        }
        return child_count;
    }
    virtual const std::string& staged_name(size_t staged_index)const
    {
        wasp_require( staged_index < m_staged.size() )
        return m_staged[staged_index].m_name;
    }
    virtual std::string& staged_name(size_t staged_index)
    {

        wasp_require( staged_index < m_staged.size() )
        return m_staged[staged_index].m_name;
    }

    /**
     * @brief commit_staged commits the staged tree node
     * @param stage_index the stage at which to commit to the tree
     * @return the new tree node's index into the tree node pool
     * The new tree node is added to the parent stage's list of
     * children
     */
    size_t commit_staged(size_t stage_index);

    const size_t& staged_type(size_t staged_index)const;
    size_t& staged_type(size_t staged_index);

    size_t staged_count()const{ return m_staged.size(); }
    virtual bool single_parse()const{return false;}
protected:
    template<class PARSER_IMPL>
    bool parse_impl( std::istream &input
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
    struct Stage{

        Stage() : m_type(wasp::UNKNOWN){}
        Stage(const Stage& orig)
            :m_type(orig.m_type),m_name(orig.m_name)
        , m_child_indices(orig.m_child_indices){}

        size_t m_type;
        std::string m_name;
        std::vector<size_t> m_child_indices;
    };
    std::vector<Stage> m_staged;
    size_t m_root_index;
public:
    // TODO protect/privatize this.
    TreeNodePool_type m_tree_nodes;

};

#include "waspcore/Interpreter.i.h"
} // end of namespace
#endif
