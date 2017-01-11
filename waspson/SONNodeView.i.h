#ifndef WASP_SONNODE_VIEW_I_H
#define WASP_SONNODE_VIEW_I_H

template<class TNV>
SONNodeView<TNV>::SONNodeView(std::size_t node_index
                        , const SONNodeView<TNV>::TreeNodePool_type & nodes)
    : m_tree_node_index(node_index)
    ,m_tree_data(&nodes)
{
    // TODO verify index is legal
}
template<class TNV>
SONNodeView<TNV>::SONNodeView(const SONNodeView & orig)
    : m_tree_node_index(orig.m_tree_node_index)
    ,m_tree_data(orig.m_tree_data)
{
}
template<class TNV>
SONNodeView<TNV>::SONNodeView(const TNV & orig)
    : m_tree_node_index(orig.tree_node_index())
    ,m_tree_data(orig.tree_node_pool())
{
}
template<class TNV>
SONNodeView<TNV>::~SONNodeView()
{
}
template<class TNV>
SONNodeView<TNV>& SONNodeView<TNV>::operator =( const SONNodeView& b)
{
    m_tree_node_index = b.tree_node_index();
    m_tree_data = b.tree_node_pool();
    return *this;
}
template<class TNV>
SONNodeView<TNV>& SONNodeView<TNV>::operator =( const TNV& b)
{
    m_tree_node_index = b.tree_node_index();
    m_tree_data = b.tree_node_pool();
    return *this;
}
template<class TNV>
bool SONNodeView<TNV>::operator ==(const SONNodeView& b)const
{
    return m_tree_data == b.m_tree_data
            && m_tree_node_index == b.m_tree_node_index;
}
template<class TNV>
SONNodeView<TNV> SONNodeView<TNV>::parent()const
{
    SONNodeView<TNV> view (m_tree_data->parent_node_index(m_tree_node_index)
                       ,*m_tree_data);
    return view;
}
template<class TNV>
bool SONNodeView<TNV>::has_parent()const
{
    return m_tree_data->has_parent(m_tree_node_index);
}
template<class TNV>
std::string SONNodeView<TNV>::id()const
{
    SONNodeView potential_id_child = id_child();
    if( potential_id_child.is_null () ) return "";
    return potential_id_child.data();
}
template<class TNV>
SONNodeView<TNV> SONNodeView<TNV>::id_child()const
{
    // id is the 3rd child
    if( child_count() > 2 )
    {
        const SONNodeView& child = child_at(2);
        std::string child_name = child.name();
        if( child_name == "id" ) return child;
    }
    return SONNodeView(); // null view
}
template<class TNV>
std::string SONNodeView<TNV>::data()const{
    std::stringstream str;
    m_tree_data->data(m_tree_node_index,str);
    return str.str();
}
template<class TNV>
std::string SONNodeView<TNV>::path()const{
    std::stringstream str;
    m_tree_data->node_path(m_tree_node_index,str);
    return str.str();
}
template<class TNV>
void SONNodeView<TNV>::paths(std::ostream& out)const{
    m_tree_data->node_paths(m_tree_node_index,out);
}
template<class TNV>
std::size_t SONNodeView<TNV>::child_count()const
{
    return m_tree_data->child_count(m_tree_node_index);
}
template<class TNV> // template type
std::size_t // return type
SONNodeView<TNV>::child_count_by_name(const std::string & name
                                                       , std::size_t limit)const
{
    TNV view (tree_node_index(),*tree_node_pool());
    return view.child_count_by_name(name, limit);
}
template<class TNV>
SONNodeView<TNV> SONNodeView<TNV>::child_at(std::size_t index)const
{

    auto child_node_pool_index = m_tree_data->child_at(m_tree_node_index
                                ,index);
    return SONNodeView<TNV>(child_node_pool_index,*m_tree_data);
}
template<class TNV> // template type
typename SONNodeView<TNV>::Collection // return type
SONNodeView<TNV>::child_by_name(const std::string & name
                                                       , std::size_t limit)const
{
    Collection results;
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
template<class TNV>
std::size_t SONNodeView<TNV>::type()const
{
    return m_tree_data->type(m_tree_node_index);
}
template<class TNV>
const char* SONNodeView<TNV>::name()const
{
    return m_tree_data->name(m_tree_node_index);
}
template<class TNV>
std::size_t SONNodeView<TNV>::line()const
{
    return m_tree_data->line(m_tree_node_index);
}
template<class TNV>
std::size_t SONNodeView<TNV>::column()const
{
    return m_tree_data->column(m_tree_node_index);
}
template<class TNV>
int SONNodeView<TNV>::to_int(bool * ok)const
{
    TNV view( tree_node_index(), *tree_node_pool() );
    return view.to_int(ok);
}
template<class TNV>
double SONNodeView<TNV>::to_double(bool * ok)const
{
    TNV view( tree_node_index(), *tree_node_pool() );
    return view.to_double(ok);
}
template<class TNV>
std::string SONNodeView<TNV>::to_string(bool * ok)const
{
    TNV view( tree_node_index(), *tree_node_pool() );
    return view.to_string(ok);
}

#endif
