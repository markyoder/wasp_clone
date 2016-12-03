#include "waspcore/TreeNodePool.h"
#include <sstream>

namespace wasp{
TreeNodeView::TreeNodeView(std::size_t node_index
                        , const TreeNodePool<> & nodes)
    : m_tree_node_index(node_index)
    ,m_tree_data(&nodes)
{
    // TODO verify index is legal
}
TreeNodeView::TreeNodeView(const TreeNodeView & orig)
    : m_tree_node_index(orig.m_tree_node_index)
    ,m_tree_data(orig.m_tree_data)
{
}
TreeNodeView::~TreeNodeView()
{
}
TreeNodeView& TreeNodeView::operator =( const TreeNodeView& b)
{
    m_tree_node_index = b.m_tree_node_index;
    m_tree_data = b.m_tree_data;
    return *this;
}
bool TreeNodeView::operator ==(const TreeNodeView& b)const
{
    return m_tree_data == b.m_tree_data
            && m_tree_node_index == b.m_tree_node_index;
}

TreeNodeView TreeNodeView::parent()const
{
    TreeNodeView view (m_tree_data->parent_node_index(m_tree_node_index)
                       ,*m_tree_data);
    return view;
}
bool TreeNodeView::has_parent()const
{
    return m_tree_data->has_parent(m_tree_node_index);
}
std::string TreeNodeView::data()const{
    std::stringstream str;
    m_tree_data->data(m_tree_node_index,str);
    return str.str();
}
std::string TreeNodeView::path()const{
    std::stringstream str;
    m_tree_data->node_path(m_tree_node_index,str);
    return str.str();
}
void TreeNodeView::paths(std::ostream& out)const{
    m_tree_data->node_paths(m_tree_node_index,out);
}
std::size_t TreeNodeView::child_count()const
{
    return m_tree_data->child_count(m_tree_node_index);
}
TreeNodeView TreeNodeView::child_at(std::size_t index)const
{

    auto child_node_pool_index = m_tree_data->child_at(m_tree_node_index
                                ,index);    
    return TreeNodeView(child_node_pool_index,*m_tree_data);
}
std::size_t TreeNodeView::type()const
{
    return m_tree_data->type(m_tree_node_index);
}
const char* TreeNodeView::name()const
{
    return m_tree_data->name(m_tree_node_index);
}
std::size_t TreeNodeView::line()const
{
    return m_tree_data->line(m_tree_node_index);
}
std::size_t TreeNodeView::column()const
{
    return m_tree_data->column(m_tree_node_index);
}

int TreeNodeView::to_int()const
{
    std::stringstream str;
    str<< data();
    int result = 0;
    str>> result;
    return result;
}

} // end of namespace

