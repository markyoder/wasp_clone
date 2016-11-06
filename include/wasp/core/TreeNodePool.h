#ifndef WASP_TREENODEPOOL_H
#define WASP_TREENODEPOOL_H
#include <unordered_map>
#include <string>
#include <sstream>
#include <ostream>
#include "wasp/core/StringPool.h"
#include "wasp/core/TokenPool.h"
namespace wasp{
typedef unsigned short default_node_type_size;
typedef unsigned int default_node_index_size;
/**
 * @class TreeNodePool class for managing Tree Nodes in a memory efficient manner
 */
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
class TreeNodePool{
public:
    TreeNodePool();
    TreeNodePool(const TreeNodePool<
                 node_type_size
                 ,node_index_size
                 ,token_type_size
                 ,token_index_type_size
                 ,file_offset_type_size> & orig);
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
              ,const std::vector<node_index_size> & child_indices);
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
                   , token_type_size token_type
                   , file_offset_type_size token_offset
                   , const char * token_data);
    /**
     * @brief push_leaf create a leaf node with the given attributes and existing token
     * @param node_type the type of the leaf node (value, decl, term, etc.)
     * @param node_name the name of the leaf node
     * @param token_index the index of the existing token
     */
    void push_leaf(node_type_size node_type
                   , const char * node_name
                   , token_index_type_size token_index);
    /**
     * @brief size acquire the number of nodes (leaf and parent)
     * @return node count
     */
    size_t size()const{return m_node_basic_data.size();}
    /**
     * @brief parent_node_count acquire the number of parent nodes
     * @return parent node count
     * Parent nodes reference leaf and other parent nodes
     */
    size_t parent_node_count()const{return m_node_parent_data.size();}

    /**
     * @brief parent_data_index acquires the given node's parent data index
     * @param node_index the child node's index for which to retrieve the parent node data index
     * @return the parent node's data index
     */
    size_t parent_data_index(node_index_size node_index)const;
    /**
     * @brief parent_node_index acquires the index of the given node's parent node
     * @param node_index the node's index for which the parent's index is requested
     * @return the parent node's index into the TreeNodePool, or size() if no parent exists
     */
    size_t parent_node_index(node_index_size node_index)const;
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
    size_t child_at(node_index_size node_index
                    , node_index_size child_index)const;
    /**
     * @brief leaf_node_count acquire the number of leaf nodes
     * @return leaf node count
     * Leaf nodes reference a token
     */
    size_t leaf_node_count()const{return m_leaf_token_lookup.size();}

    /**
     * @brief child_count acquire the number of child nodes for the given node index
     * @param node_index the index of the node from which to determine child count
     * @return child count, or zero if no children exist
     */
    size_t child_count(node_index_size node_index)const;
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
    size_t line(node_index_size node_index)const;
    /**
     * @brief column acquire the column the node starts on
     * @param node_index the index of the node to acquire the column
     * @return the node's starting column
     */
    size_t column(node_index_size node_index)const;

    /**
     * @brief leaf acquire the node index of the first leaf node at/under node_index
     * @param node_index parent or leaf node index
     * @return the first leaf node index at or under the given node_index
     * If the node at node_index is a leaf node return=node_index.
     * If the node at node_index is a parent node, the depth-first
     * leaf node index will be returned
     */
    size_t leaf_index( node_index_size node_index)const;
    /**
     * @brief push_line add a new line into the underlying token pool
     * @param line_offset the byte offset of the line
     */
    void push_line(file_offset_type_size line_offset){m_token_data.push_line(line_offset);}

    /**
     * @brief token_data acquires the token pool that backs this TreeNodePool
     * @return
     */
    TokenPool<token_type_size,token_index_type_size,file_offset_type_size>&
        token_data(){return m_token_data;}

    const TokenPool<token_type_size,token_index_type_size,file_offset_type_size>&
        token_data()const{return m_token_data;}
private:
    /**
     * @brief m_token_data Leaf node's token data
     * All leaf nodes will have a corresponding token
     */
    TokenPool<token_type_size,token_index_type_size,file_offset_type_size> m_token_data; //
    /**
     * @brief m_node_names all node names are stored here
     */
    StringPool<token_index_type_size> m_node_names;
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
    std::unordered_map<node_index_size,token_index_type_size> m_leaf_token_lookup;

};

/**
 * @brief The TreeNodeView class provies light weight interface to TreeNodes
 * Allows traversing child nodes and parent as well as acquire node information *
 */
class TreeNodeView{
public:

    TreeNodeView(size_t node_index, const TreeNodePool<> & nodes);
    TreeNodeView(const TreeNodeView& orig);
    ~TreeNodeView();


    bool operator==(const TreeNodeView& b)const;
    /**
     * @brief equal determines if this is equal to the provides TreeNodeView
     * @return true, iff and only if the nodes are the same
     */
    bool equal(const TreeNodeView& b)const{return *this==b;}

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
    size_t child_count()const;

    /**
     * @brief child_at acquire the child node view at the given index
     * @param index the index of the child [0-child_count())
     * @return TreeNodeView describing the child node
     */
    TreeNodeView child_at(size_t index)const;

    /**
     * @brief type acquire the type of the node
     * @return the node's type
     */
    size_t type()const;
    /**
     * @brief name acquire the name of the node
     * @return the node's name
     */
    const char * name()const;

    /**
     * @brief line acquire the node's starting line
     * @return the starting line of the node
     */
    size_t line()const;
    /**
     * @brief column acquire the node's starting column
     * @return the starting column of the node
     */
    size_t column()const;
    /**
     * @brief tree_node_index acquire the index into the tree node data pool
     * @return the index into the data pool
     */
    size_t tree_node_index()const{return m_tree_node_index;}
private:
    size_t m_tree_node_index;
    const TreeNodePool<> & m_tree_data;
};
#include "wasp/core/TreeNodePool.i.h"
} // end of namespace
#endif
