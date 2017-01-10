#ifndef WASP_SONNODE_VIEW_H
#define WASP_SONNODE_VIEW_H

#include <string>
#include <sstream>
#include <ostream>
#include <iostream>
#include "waspcore/TreeNodePool.h" // for Default TreeNodeView
namespace wasp{

/**
 * @brief The SONNodeView class provides light weight interface to SON Nodes
 * Allows traversing child nodes and parent as well as acquire node information *
 */
template< class TNV = TreeNodeView<> >
class SONNodeView{
public:
    using Collection = std::vector<SONNodeView>;
    typedef TNV TreeNodeView_type;
    typedef typename TNV::TreeNodePool_type TreeNodePool_type;
    SONNodeView():m_tree_node_index(-1),m_tree_data(nullptr){}
    SONNodeView(std::size_t node_index, const TreeNodePool_type & nodes);
    SONNodeView(const TNV& orig);
    SONNodeView(const SONNodeView& orig);

    ~SONNodeView();

    SONNodeView& operator=(const SONNodeView& b);

    bool operator==(const SONNodeView& b)const;
    bool operator!=(const SONNodeView& b)const{return !(*this==b);}
    /**
     * @brief equal determines if this is equal to the provides SONNodeView
     * @return true, iff and only if the nodes are the same
     */
    bool equal(const SONNodeView& b)const{return *this==b;}

    /**
     * @brief data acquire the node's data
     * @return the node's data
     */
    std::string data()const;
    /**
     * @brief parent acquire the parent view of the current node
     * @return
     */
    SONNodeView parent()const;
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
     * @return SONNodeView describing the child node
     */
    SONNodeView<TNV> child_at(std::size_t index)const;

    /**
     * @brief child_by_name acquire child nodes by the given name
     * @param name the name of the children to be retrieved
     * @param limit the limit on the number of children ( 0 := no limit )
     * @return A collection of views. Empty if no match occurrs
     */
    SONNodeView::Collection child_by_name(const std::string & name, size_t limit=0)const;
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
    const TNV * tree_node_pool()const{return m_tree_data;}

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
    friend std::ostream& operator<< (std::ostream& str, const wasp::SONNodeView<TNV> & view){
        str<<"SONNodeView(tree_node_index="<<view.m_tree_node_index<<", &pool="<<view.m_tree_data<<")";
        return str;
    }

private:
    size_t m_tree_node_index;
    const TreeNodePool_type * m_tree_data;

};
#include "waspson/SONNodeView.i.h"
} // end of namespace

#endif
