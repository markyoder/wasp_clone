#ifndef WASP_DDINODE_VIEW_I_H
#define WASP_DDINODE_VIEW_I_H

template<class TNV>
DDINodeView<TNV>::DDINodeView(
    std::size_t                                         node_index,
    const typename DDINodeView<TNV>::TreeNodePool_type& nodes)
    : m_tree_node_index(node_index), m_tree_data(&nodes)
{
    wasp_require(!this->is_null());
}
template<class TNV>
DDINodeView<TNV>::DDINodeView(const DDINodeView& orig)
    : m_tree_node_index(orig.m_tree_node_index), m_tree_data(orig.m_tree_data)
{
}
template<class TNV>
DDINodeView<TNV>::DDINodeView(const TNV& orig)
    : m_tree_node_index(orig.tree_node_index())
    , m_tree_data(orig.tree_node_pool())
{
}
template<class TNV>
DDINodeView<TNV>::~DDINodeView()
{
}
template<class TNV>
DDINodeView<TNV>& DDINodeView<TNV>::operator=(const DDINodeView& b)
{
    m_tree_node_index = b.tree_node_index();
    m_tree_data       = b.tree_node_pool();
    return *this;
}
template<class TNV>
DDINodeView<TNV>& DDINodeView<TNV>::operator=(const TNV& b)
{
    m_tree_node_index = b.tree_node_index();
    m_tree_data       = b.tree_node_pool();
    return *this;
}
template<class TNV>
bool DDINodeView<TNV>::operator==(const DDINodeView& b) const
{
    return m_tree_data == b.m_tree_data &&
           m_tree_node_index == b.m_tree_node_index;
}
template<class TNV>
bool DDINodeView<TNV>::operator<(const DDINodeView& b) const
{
    return m_tree_node_index < b.m_tree_node_index;
}
template<class TNV>
DDINodeView<TNV> DDINodeView<TNV>::parent() const
{
    DDINodeView<TNV> view(m_tree_data->parent_node_index(m_tree_node_index),
                          *m_tree_data);
    return view;
}
template<class TNV>
bool DDINodeView<TNV>::has_parent() const
{
    return m_tree_data->has_parent(m_tree_node_index);
}
template<class TNV>
bool DDINodeView<TNV>::is_leaf() const
{
    TNV view(tree_node_index(), *tree_node_pool());
    return view.is_leaf();
}
template<class TNV>
bool DDINodeView<TNV>::is_decorative() const
{
    auto t = type();
    switch (t)
    {
        case wasp::DECL:
        case wasp::ASSIGN:
        case wasp::COMMENT:
        case wasp::WASP_COMMA:  // ,
            return true;
    }
    return false;
}

template<class TNV>
bool DDINodeView<TNV>::is_declarator() const
{
    return type() == wasp::DECL;
}

template<class TNV>
bool DDINodeView<TNV>::is_terminator() const
{
    switch (type())
    {
        case wasp::TERM:
            return true;
        default:
            return false;
    }
}

template<class TNV>
typename DDINodeView<TNV>::Collection
DDINodeView<TNV>::non_decorative_children() const
{
    Collection results;
    for (std::size_t i = 0, count = child_count(); i < count; ++i)
    {
        const auto& child = child_at(i);
        if (!child.is_decorative())
            results.push_back(child);
    }
    return results;
}
template<class TNV>
DDINodeView<TNV> DDINodeView<TNV>::first_non_decorative_child_by_name(
    const std::string& name) const
{
    for (std::size_t i = 0, count = child_count(); i < count; ++i)
    {
        const auto& child = child_at(i);
        if (!child.is_decorative())
        {
            if (name == child.name())
            {
                return child;
            }
        }
    }
    return DDINodeView<TNV>();  // null node
}
template<class TNV>
size_t DDINodeView<TNV>::non_decorative_children_count() const
{
    size_t result = 0;
    for (std::size_t i = 0, count = child_count(); i < count; ++i)
    {
        const auto& child = child_at(i);
        if (!child.is_decorative())
            ++result;
    }
    return result;
}
template<class TNV>
std::string DDINodeView<TNV>::data() const
{
    std::stringstream str;
    m_tree_data->data(m_tree_node_index, str);
    return str.str();
}
template<class TNV>
std::string DDINodeView<TNV>::path() const
{
    std::stringstream str;
    m_tree_data->node_path(m_tree_node_index, str);
    return str.str();
}
template<class TNV>
void DDINodeView<TNV>::paths(std::ostream& out) const
{
    m_tree_data->node_paths(m_tree_node_index, out);
}
template<class TNV>
std::size_t DDINodeView<TNV>::child_count() const
{
    return m_tree_data->child_count(m_tree_node_index);
}
template<class TNV>  // template type
std::size_t          // return type
    DDINodeView<TNV>::child_count_by_name(const std::string& name,
                                          std::size_t        limit) const
{
    TNV view(tree_node_index(), *tree_node_pool());
    return view.child_count_by_name(name, limit);
}
template<class TNV>
DDINodeView<TNV> DDINodeView<TNV>::child_at(std::size_t index) const
{
    auto child_node_pool_index =
        m_tree_data->child_at(m_tree_node_index, index);
    return DDINodeView<TNV>(child_node_pool_index, *m_tree_data);
}
template<class TNV>                    // template type
typename DDINodeView<TNV>::Collection  // return type
    DDINodeView<TNV>::child_by_name(const std::string& name,
                                    std::size_t        limit) const
{
    Collection results;
    for (std::size_t i = 0, count = child_count(); i < count; ++i)
    {
        auto        child      = child_at(i);
        std::string child_name = child.name();
        if (child_name == name)
        {
            results.push_back(child);
        }
        // limit of 0 is reserved as no limit
        if (limit != 0 && results.size() == limit)
            break;
    }
    return results;
}
template<class TNV>  // template type
DDINodeView<TNV>     // return type
    DDINodeView<TNV>::first_child_by_name(const std::string& name) const
{
    TNV view(tree_node_index(), *tree_node_pool());
    return view.first_child_by_name(name);
}
template<class TNV>
std::size_t DDINodeView<TNV>::type() const
{
    return m_tree_data->type(m_tree_node_index);
}
template<class TNV>
const char* DDINodeView<TNV>::name() const
{
    return m_tree_data->name(m_tree_node_index);
}
template<class TNV>
std::size_t DDINodeView<TNV>::line() const
{
    return m_tree_data->line(m_tree_node_index);
}
template<class TNV>
std::size_t DDINodeView<TNV>::column() const
{
    return m_tree_data->column(m_tree_node_index);
}

template<class TNV>
std::size_t DDINodeView<TNV>::last_line() const
{
    return m_tree_data->last_line(m_tree_node_index);
}

template<class TNV>
std::size_t DDINodeView<TNV>::last_column() const
{
    return m_tree_data->last_column(m_tree_node_index);
}

template<class TNV>
bool DDINodeView<TNV>::to_bool(bool* ok) const
{
    TNV view(value_tree_node_index(), *tree_node_pool());
    return view.to_bool(ok);
}

template<class TNV>
int DDINodeView<TNV>::to_int(bool* ok) const
{
    TNV view(value_tree_node_index(), *tree_node_pool());
    return view.to_int(ok);
}
template<class TNV>
double DDINodeView<TNV>::to_double(bool* ok) const
{
    TNV view(value_tree_node_index(), *tree_node_pool());
    return view.to_double(ok);
}
template<class TNV>
std::string DDINodeView<TNV>::to_string(bool* ok) const
{
    TNV view(value_tree_node_index(), *tree_node_pool());
    return view.to_string(ok);
}
template<class TNV>
std::string DDINodeView<TNV>::last_as_string(bool* ok) const
{
    size_t count = child_count();
    if (count > 0)
    {
        return child_at(count - 1).last_as_string(ok);
    }
    return to_string(ok);
}
template<class TNV>
size_t DDINodeView<TNV>::value_tree_node_index() const
{
    /// TODO - could push this lower to TNV ?
    if (type() == wasp::KEYED_VALUE && child_count() > 0)
    {
        return child_at(child_count() - 1).tree_node_index();
    }
    return tree_node_index();
}
#endif
