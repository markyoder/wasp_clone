#include "wasp/core/TreeNodePool.h"

namespace wasp{
TreeNodeView::TreeNodeView(size_t node_index
                        , const TreeNodePool<> & nodes)
    : m_tree_node_index(node_index)
    ,m_tree_data(nodes)
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

bool TreeNodeView::operator ==(const TreeNodeView& b)const
{
    return &m_tree_data == &b.m_tree_data
            && m_tree_node_index == b.m_tree_node_index;
}

TreeNodeView TreeNodeView::parent()const
{
    TreeNodeView view (m_tree_data.parent_node_index(m_tree_node_index)
                       ,m_tree_data);
    return view;
}
bool TreeNodeView::has_parent()const
{
    size_t parent_node_index
            = m_tree_data.parent_node_index(m_tree_node_index);
    return parent_node_index != m_tree_data.size();
}
size_t TreeNodeView::child_count()const
{
    return m_tree_data.child_count(m_tree_node_index);
}
TreeNodeView TreeNodeView::child_at(size_t index)const
{

    auto child_node_pool_index = m_tree_data.child_at(m_tree_node_index
                                ,index);
    return TreeNodeView(child_node_pool_index,m_tree_data);
}
size_t TreeNodeView::type()const
{
    return m_tree_data.type(m_tree_node_index);
}
const char* TreeNodeView::name()const
{
    return m_tree_data.name(m_tree_node_index);
}
size_t TreeNodeView::line()const
{
    return m_tree_data.line(m_tree_node_index);
}
size_t TreeNodeView::column()const
{
    return m_tree_data.column(m_tree_node_index);
}
} // end of namespace
