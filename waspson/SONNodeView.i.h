#ifndef WASP_SONNODE_VIEW_I_H
#define WASP_SONNODE_VIEW_I_H

template<class TreeNodePool_T, class TreeNodeView_T>
SONNodeView<TreeNodePool_T,TreeNodeView_T>::SONNodeView(std::size_t node_index
                        , const TreeNodePool_T & nodes)
    : m_tree_node_index(node_index)
    ,m_tree_data(&nodes)
{
    // TODO verify index is legal
}
template<class TreeNodePool_T, class TreeNodeView_T>
SONNodeView<TreeNodePool_T,TreeNodeView_T>::SONNodeView(const SONNodeView & orig)
    : m_tree_node_index(orig.m_tree_node_index)
    ,m_tree_data(orig.m_tree_data)
{
}
template<class TreeNodePool_T, class TreeNodeView_T>
SONNodeView<TreeNodePool_T,TreeNodeView_T>::~SONNodeView()
{
}
template<class TreeNodePool_T, class TreeNodeView_T>
SONNodeView<TreeNodePool_T,TreeNodeView_T>& SONNodeView<TreeNodePool_T,TreeNodeView_T>::operator =( const SONNodeView& b)
{
    m_tree_node_index = b.m_tree_node_index;
    m_tree_data = b.m_tree_data;
    return *this;
}
template<class TreeNodePool_T, class TreeNodeView_T>
bool SONNodeView<TreeNodePool_T,TreeNodeView_T>::operator ==(const SONNodeView& b)const
{
    return m_tree_data == b.m_tree_data
            && m_tree_node_index == b.m_tree_node_index;
}
template<class TreeNodePool_T, class TreeNodeView_T>
SONNodeView<TreeNodePool_T,TreeNodeView_T> SONNodeView<TreeNodePool_T,TreeNodeView_T>::parent()const
{
    SONNodeView<TreeNodePool_T,TreeNodeView_T> view (m_tree_data->parent_node_index(m_tree_node_index)
                       ,*m_tree_data);
    return view;
}
template<class TreeNodePool_T, class TreeNodeView_T>
bool SONNodeView<TreeNodePool_T,TreeNodeView_T>::has_parent()const
{
    return m_tree_data->has_parent(m_tree_node_index);
}
template<class TreeNodePool_T, class TreeNodeView_T>
std::string SONNodeView<TreeNodePool_T,TreeNodeView_T>::data()const{
    std::stringstream str;
    m_tree_data->data(m_tree_node_index,str);
    return str.str();
}
template<class TreeNodePool_T, class TreeNodeView_T>
std::string SONNodeView<TreeNodePool_T,TreeNodeView_T>::path()const{
    std::stringstream str;
    m_tree_data->node_path(m_tree_node_index,str);
    return str.str();
}
template<class TreeNodePool_T, class TreeNodeView_T>
void SONNodeView<TreeNodePool_T,TreeNodeView_T>::paths(std::ostream& out)const{
    m_tree_data->node_paths(m_tree_node_index,out);
}
template<class TreeNodePool_T, class TreeNodeView_T>
std::size_t SONNodeView<TreeNodePool_T,TreeNodeView_T>::child_count()const
{
    return m_tree_data->child_count(m_tree_node_index);
}
template<class TreeNodePool_T, class TreeNodeView_T>
SONNodeView<TreeNodePool_T,TreeNodeView_T> SONNodeView<TreeNodePool_T,TreeNodeView_T>::child_at(std::size_t index)const
{

    auto child_node_pool_index = m_tree_data->child_at(m_tree_node_index
                                ,index);
    return SONNodeView<TreeNodePool_T,TreeNodeView_T>(child_node_pool_index,*m_tree_data);
}
template<class TreeNodePool_T, class TreeNodeView_T> // template type
typename SONNodeView<TreeNodePool_T,TreeNodeView_T>::Collection // return type
SONNodeView<TreeNodePool_T,TreeNodeView_T>::child_by_name(const std::string & name
                                                       , std::size_t limit)const
{
    SONNodeView<TreeNodePool_T,TreeNodeView_T>::Collection results;

    for( std::size_t i = 0, count = child_count(); i < count; ++i )
    {
        auto child = child_at(i);
        std::string child_name = child.name();
        if( child_name == name )
        {
            results.push_back(child);
        }
        // limit of 0 is reserved as no limit
        if( limit != 0 && results.size() == limit ) break;
    }
    return results;
}
template<class TreeNodePool_T, class TreeNodeView_T>
std::size_t SONNodeView<TreeNodePool_T,TreeNodeView_T>::type()const
{
    return m_tree_data->type(m_tree_node_index);
}
template<class TreeNodePool_T, class TreeNodeView_T>
const char* SONNodeView<TreeNodePool_T,TreeNodeView_T>::name()const
{
    return m_tree_data->name(m_tree_node_index);
}
template<class TreeNodePool_T, class TreeNodeView_T>
std::size_t SONNodeView<TreeNodePool_T,TreeNodeView_T>::line()const
{
    return m_tree_data->line(m_tree_node_index);
}
template<class TreeNodePool_T, class TreeNodeView_T>
std::size_t SONNodeView<TreeNodePool_T,TreeNodeView_T>::column()const
{
    return m_tree_data->column(m_tree_node_index);
}
template<class TreeNodePool_T, class TreeNodeView_T>
int SONNodeView<TreeNodePool_T,TreeNodeView_T>::to_int(bool * ok)const
{
    TreeNodeView_T view( tree_node_index(), *tree_node_pool() );
    return view.to_int(ok);
}
template<class TreeNodePool_T, class TreeNodeView_T>
double SONNodeView<TreeNodePool_T,TreeNodeView_T>::to_double(bool * ok)const
{
    TreeNodeView_T view( tree_node_index(), *tree_node_pool() );
    return view.to_double(ok);
}
template<class TreeNodePool_T, class TreeNodeView_T>
std::string SONNodeView<TreeNodePool_T,TreeNodeView_T>::to_string(bool * ok)const
{
    TreeNodeView_T view( tree_node_index(), *tree_node_pool() );
    return view.to_String(ok);
}

#endif
