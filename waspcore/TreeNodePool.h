#ifndef WASP_TREENODEPOOL_H
#define WASP_TREENODEPOOL_H
#include <unordered_map>
#include <string>
#include <sstream>
#include <ostream>
#include <iostream>
#include "waspcore/StringPool.h"
#include "waspcore/TokenPool.h"
#include "waspcore/wasp_node.h" // for UNKNOWN node/token types
namespace wasp{
typedef unsigned short default_node_type_size;
typedef unsigned int default_node_index_size;
/**
 * @class TreeNodePool class for managing Tree Nodes in a memory efficient manner
 */
template<
    // size type describing node type maximum
    typename nts =  default_node_type_size
    // size type describing node occurrence maximum
    ,typename nis = default_node_index_size
    // Token Pool storage type
    ,class TP = TokenPool<>
>
class TreeNodePool{
public:
    typedef nts node_type_size;
    typedef nis node_index_size;
    typedef TP TokenPool_type;
    TreeNodePool();
    TreeNodePool(const TreeNodePool<
                 node_type_size
                 ,node_index_size
                 ,TP> & orig);
    ~TreeNodePool();

    /**
     * @brief push_parent create a parent node with given name and child
     * @param type the node's type
     * @param name the node's name
     * @param first_child_index the pool index of the node's first child
     * @param child_count
     */
    void push_parent(node_type_size type
                , const char * name
              ,const std::vector<size_t> & child_indices);
    /**
     * @brief push_leaf create a leaf node with the given attributes
     * @param node_type the type of the leaf node (value, decl, term, etc.)
     * @param node_name the name of the leaf node
     * @param token_type the type of the token (float, int, word, etc.)
     * @param token_offset the offset of the token in the file/stream
     * @param token_data the token's string data (1.234, 10, ted, etc.)
     */
    void push_leaf(node_type_size node_type
                   , const char * node_name
                   , typename TP::token_type_size token_type
                   , typename TP::file_offset_type_size token_offset
                   , const char * token_data);
    /**
     * @brief push_leaf create a leaf node with the given attributes and existing token
     * @param node_type the type of the leaf node (value, decl, term, etc.)
     * @param node_name the name of the leaf node
     * @param token_index the index of the existing token
     */
    void push_leaf(node_type_size node_type
                   , const char * node_name
                   , typename TP::token_index_type_size token_index);


    /**
     * @brief size acquire the number of nodes (leaf and parent)
     * @return node count
     */
    std::size_t size()const{return m_node_basic_data.size();}
    /**
     * @brief parent_node_count acquire the number of parent nodes
     * @return parent node count
     * Parent nodes reference leaf and other parent nodes
     */
    std::size_t parent_node_count()const{return m_node_parent_data.size();}

    /**
     * @brief token_count acquire the number of tokens needed for all TreeNodes
     * @return the number of tokens backing all tree nodes
     */
    std::size_t token_count()const{return m_token_data.size();}

    /**
     * @brief push appends a token
     * @param str the token's string data
     * @param type the token's type (enumeration)
     * @param token_file_offset the token's offset into the file/stream
     */
    void push_token(const char * str, typename TP::token_type_size type
              , size_t token_file_offset )
        {m_token_data.push(str,type,token_file_offset);}
    /**
     * @brief parent_data_index acquires the given node's parent data index
     * @param node_index the child node's index for which to retrieve the parent node data index
     * @return the parent node's data index
     */
    std::size_t parent_data_index(node_index_size node_index)const;
    /**
     * @brief parent_node_index acquires the index of the given node's parent node
     * @param node_index the node's index for which the parent's index is requested
     * @return the parent node's index into the TreeNodePool, or size() if no parent exists
     */
    std::size_t parent_node_index(node_index_size node_index)const;
    /**
     * @brief has_parent determine if the given node has a parent
     * @return true, iff the node at the given index has a parent
     */
    bool has_parent(node_index_size node_index)const;
    /**
    * @brief child_at acquire the child node index at the given relative index
    * @param index the index of the child [0-child_count())
    * @return the absolute node index of the parent relative child index
    */
    std::size_t child_at(node_index_size node_index
                    , node_index_size child_index)const;

    /**
     * @brief leaf_node_count acquire the number of leaf nodes
     * @return leaf node count
     * Leaf nodes reference a token
     */
    std::size_t leaf_node_count()const{return m_leaf_token_lookup.size();}

    /**
     * @brief child_count acquire the number of child nodes for the given node index
     * @param node_index the index of the node from which to determine child count
     * @return child count, or zero if no children exist
     */
    std::size_t child_count(node_index_size node_index)const;
    /**
     * @brief node_path acquires the path of the node at the given index
     * @param node_index the index of the node for which the path is requested
     * @param out the output stream in which to capture the path
     */
    void node_path(node_index_size node_index, std::ostream & out)const;
    /**
     * @brief node_paths acquires the paths of the given node and its children
     * @param node_index the node for which it and its descendents' paths are desired
     * @param out the output stream in which to capture the paths
     */
    void node_paths(node_index_size node_index, std::ostream & out)const;
    /**
     * @brief name acquire the name of the node
     * @param node_index the index of the node to acquire the name
     * @return the node's name
     */
    const char * name(node_index_size node_index)const
                            {return m_node_names.data(node_index);}
    node_type_size type(node_index_size node_index)const
                            {return m_node_basic_data[node_index].m_node_type;}    
    /**
     * @brief node_token_type acquire the type of the toke backing the node at the given index
     * @param node_index the node for which the token type is requested.
     * @return the token type of the leaf node at the given index.
     * If the node index is out of range, wasp::UNKNOWN is returned.
     * If the node at the given index is not a leaf node, wasp::UNKNOWN is returned
     */
    typename TP::token_type_size node_token_type( node_index_size node_index)const;
    /**
     * @brief data acquire the string data of the node
     * @param node_index the index of the node to acquire the data
     * @return the node's data
     */
    std::string data(node_index_size node_index)const;
    void data(node_index_size node_index,std::ostream& out)const;

    /**
     * @brief line acquire the line the node starts on
     * @param node_index the index of the node to acquire the line
     * @return the node's starting line
     */
    std::size_t line(node_index_size node_index)const;
    /**
     * @brief column acquire the column the node starts on
     * @param node_index the index of the node to acquire the column
     * @return the node's starting column
     */
    std::size_t column(node_index_size node_index)const;

    /**
     * @brief leaf acquire the node index of the first leaf node at/under node_index
     * @param node_index parent or leaf node index
     * @return the first leaf node index at or under the given node_index
     * If the node at node_index is a leaf node return=node_index.
     * If the node at node_index is a parent node, the depth-first
     * leaf node index will be returned
     */
    std::size_t leaf_index( node_index_size node_index)const;
    /**
     * @brief push_line add a new line into the underlying token pool
     * @param line_offset the byte offset of the line
     */
    void push_line(typename TP::file_offset_type_size line_offset){m_token_data.push_line(line_offset);}

    /**
     * @brief token_data acquires the token pool that backs this TreeNodePool
     * @return
     */
    TokenPool<typename TP::token_type_size,typename TP::token_index_type_size,typename TP::file_offset_type_size>&
        token_data(){return m_token_data;}

    const TokenPool<typename TP::token_type_size,typename TP::token_index_type_size,typename TP::file_offset_type_size>&
        token_data()const{return m_token_data;}
private:
    /**
     * @brief m_token_data Leaf node's token data
     * All leaf nodes will have a corresponding token
     */
    TP m_token_data; //
    /**
     * @brief m_node_names all node names are stored here
     */
    StringPool<typename TP::token_index_type_size> m_node_names;
    /**
     * @brief The BasicNodeData struct describes all node's basic data
     */
    struct BasicNodeData{
        BasicNodeData():m_node_type(-1),m_parent_node_index(-1){}
        BasicNodeData(node_type_size type
                      ,node_index_size parent_index)
            :m_node_type(type),m_parent_node_index(parent_index){}
        /**
         * @brief m_type the node type
         */
        node_type_size m_node_type;
        /**
         * @brief m_parent_node_index the node's parent index into m_node_basic_data
         */
        node_index_size m_parent_node_index;
    };
    /**
     * @brief m_node_basic_data basic data for all nodes
     */
    std::vector<BasicNodeData> m_node_basic_data;
    /**
     * @brief The ParentNodeData struct describes parent node's data
     */
    struct ParentNodeData{
        ParentNodeData():m_first_child_index(-1),m_child_count(0){}
        ParentNodeData(node_index_size first_child_index
                       ,node_index_size child_count)
            :m_first_child_index(first_child_index)
            ,m_child_count(child_count){}
        /**
         * @brief m_first_child_index node's first child index into m_node_child_indices indicating
         */
        node_index_size m_first_child_index;
        /**
         * @brief m_child_count node's child count, relative from first child index
         */
        node_index_size m_child_count;
    };
    /**
     * @brief m_node_parent_data parent data for parent nodes
     */
    std::vector<ParentNodeData> m_node_parent_data;

    /**
     * @brief m_node_child_indices indices of children of a given parent node
     * This vector should be O(#nodes-1) as each node except the root has a parent
     */
    std::vector<node_index_size> m_node_child_indices;
    /**
     * @brief m_basic_parent_data_lookup index of basic node to parent node
     * An entry will only exist when a basic node is also a parent node
     */
    std::unordered_map<node_index_size,node_index_size> m_basic_parent_data_lookup;
    /**
     * @brief m_leaf_token_lookup basic node index to token data index in pool
     * An entry will only exist when a basic node is also a leaf node
     */
    std::unordered_map<node_index_size,typename TP::token_index_type_size> m_leaf_token_lookup;

};

/**
 * @brief The TreeNodeView class provies light weight interface to TreeNodes
 * Allows traversing child nodes and parent as well as acquire node information *
 */
template<class TreeNodePool_T = TreeNodePool<> >
class TreeNodeView{
public:
    using Collection = std::vector<TreeNodeView>;
    typedef TreeNodePool_T TreeNodePool_type;
    TreeNodeView():m_tree_node_index(-1),m_tree_data(nullptr){}
    TreeNodeView(std::size_t node_index, const TreeNodePool_T & nodes);
    TreeNodeView(const TreeNodeView& orig);
    ~TreeNodeView();


    TreeNodeView& operator=(const TreeNodeView& b);

    bool operator==(const TreeNodeView& b)const;
    bool operator!=(const TreeNodeView& b)const{return !(*this==b);}
    /**
     * @brief equal determines if this is equal to the provides TreeNodeView
     * @return true, iff and only if the nodes are the same
     */
    bool equal(const TreeNodeView& b)const{return *this==b;}

    /**
     * @brief data acquire the node's data
     * @return the node's data
     */
    std::string data()const;
    /**
     * @brief parent acquire the parent view of the current node
     * @return
     */
    TreeNodeView parent()const;
    /**
     * @brief has_parent determine if this node has a parent
     * @return true, iff this node has a parent
     */
    bool has_parent()const;

    /**
     * @brief is_null determines if this view is backed by a storage pool
     * @return true, iff the view has no storage backing
     */
    bool is_null()const{ return m_tree_data == nullptr; }

    /**
     * @brief path acquire the path of this node from the document root
     * @return path to node, e.g., '/object/key/value'
     */
    std::string path()const;
    /**
     * @brief paths acquire the paths of this node and its children
     * @param out the output stream to capture the node paths
     * The node paths are written, new line delimited
     */
    void paths(std::ostream & out)const;
    /**
     * @brief child_count acquire the number of nodes for which this node is a parent
     * @return child count
     */
    std::size_t child_count()const;
    /**
     * @brief child_count_by_name determines the number of children with the given name
     * @param name the name of the child nodes to count
     * @param limit the limit (0 reserved as no limit) which can be used to optimize determination of named children
     * @return the number of children with the given name
     */
    std::size_t child_count_by_name(const std::string & name, size_t limit=0)const;

    /**
     * @brief child_at acquire the child node view at the given index
     * @param index the index of the child [0-child_count())
     * @return TreeNodeView describing the child node
     */
    TreeNodeView child_at(std::size_t index)const;

    /**
     * @brief child_by_name acquire child nodes by the given name
     * @param name the name of the children to be retrieved
     * @param limit the limit on the number of children ( 0 := no limit )
     * @return A collection of views. Empty if no match occurrs
     */
    TreeNodeView::Collection child_by_name(const std::string & name, size_t limit=0)const;
    TreeNodeView first_child_by_name(const std::string & name)const;
    /**
     * @brief type acquire the type of the node
     * @return the node's type
     */
    std::size_t type()const;
    /**
     * @brief name acquire the name of the node
     * @return the node's name
     */
    const char * name()const;

    /**
     * @brief line acquire the node's starting line
     * @return the starting line of the node
     */
    std::size_t line()const;
    /**
     * @brief column acquire the node's starting column
     * @return the starting column of the node
     */
    std::size_t column()const;
    /**
     * @brief tree_node_index acquire the index into the tree node data pool
     * @return the index into the data pool
     */
    std::size_t tree_node_index()const{return m_tree_node_index;}

    /**
     * @brief tree_node_pool acquire the pointer to the backend storage
     * @return the TreeNodePool that backs this view
     */
    const TreeNodePool_T * tree_node_pool()const{return m_tree_data;}

    // !> Type operators
    /**
     * @brief to_int converts the data to an integer
     * @return the data as an integer
     */
    int to_int(bool * ok = nullptr) const;

    /**
     * @brief to_double converts the data to a double
     * @return the data as a double
     */
    double to_double(bool * ok = nullptr) const;

    /**
     * @brief to_string converts the data to a string
     * @return the data as a string (single and double quotes are removed from front and back).
     */
    std::string to_string(bool * ok = nullptr) const;

    // Friendly stream operator
    friend std::ostream& operator<< (std::ostream& str, const wasp::TreeNodeView<TreeNodePool_T> & view){
        str<<"TreeNodeView(tree_node_index="<<view.m_tree_node_index<<", &pool="<<view.m_tree_data<<")";
        return str;
    }

private:
    std::size_t m_tree_node_index;
    const TreeNodePool_T * m_tree_data;

    /**
     * @brief to_type acquire the data typed as the requested type
     * @param result the typed result
     * @param ok optional boolean return value indicating if conversion was successful.
     */
    template<typename T>
    void to_type(T & result, bool * ok=nullptr)const;
};
#include "waspcore/TreeNodePool.i.h"
} // end of namespace

#endif
