#include "waspeddi/EDDINodeView.h"
#include "waspcore/utils.h"

namespace wasp
{
template<size_t FileNodeType>
class NodeFileDeRef{
public:
    template<class T>
    T operator()(const T& node){
        if ( FileNodeType != node.type() )
        {
            return node;
        }
        wasp_check(node.node_pool());
        const auto* document = node.node_pool()->document(node.node_index());
        if (document)
        {
            T root = document->root();
            return root;
        }
        return T(); // null deref
    }
};
EDDINodeView::EDDINodeView(std::size_t                node_index,
                         const AbstractInterpreter& pool)
    : m_node_index(node_index), m_pool(&pool)
{
}

EDDINodeView::EDDINodeView(const EDDINodeView& orig)
    : m_node_index(orig.m_node_index), m_pool(orig.m_pool)
{
}

EDDINodeView::~EDDINodeView()
{
}

EDDINodeView& EDDINodeView::operator=(const EDDINodeView& b)
{
    m_node_index = b.node_index();
    m_pool       = b.node_pool();
    return *this;
}

bool EDDINodeView::operator==(const EDDINodeView& b) const
{
    return m_pool == b.m_pool && m_node_index == b.m_node_index;
}

bool EDDINodeView::operator<(const EDDINodeView& b) const
{
    return m_node_index < b.m_node_index;
}

EDDINodeView EDDINodeView::parent() const
{    
    EDDINodeView view;

    if( m_pool->document_parent() != nullptr )
    {
        if( type() != wasp::DOCUMENT_ROOT )
        {
            view = EDDINodeView(m_pool->parent_node_index(m_node_index), *m_pool);
            if ( view.type() == wasp::DOCUMENT_ROOT )
            {
                view = wasp::parent_document_node<EDDINodeView,
                                                    AbstractInterpreter>(m_pool);
            }
        }
    }
    else
    {
        view = EDDINodeView(m_pool->parent_node_index(m_node_index), *m_pool);
    }
    return view;
}

bool EDDINodeView::has_parent() const
{
    bool _has_parent = m_pool->has_parent(m_node_index);
    if (m_pool->document_parent() != nullptr)
    {
        return true;
    }
    return _has_parent;
}

bool EDDINodeView::is_leaf() const
{
    NodeView view(node_index(), *node_pool());
    return view.is_leaf();
}

bool EDDINodeView::is_decorative() const
{
    auto t = type();
    return is_type_decorative(t);
}
bool EDDINodeView::is_type_decorative(std::size_t t)
{
    switch (t)
    {
        case wasp::DECL:
        case wasp::ASSIGN:
        case wasp::COMMENT:
        case wasp::RBRACKET:  // [
        case wasp::LBRACKET:  // ]
        case wasp::WASP_COMMA:
        case wasp::DIVIDE:  // forward slash '/'
        case wasp::TERM:
            return true;
    }    
    return false;
}

bool EDDINodeView::is_declarator() const
{
    return type() == wasp::DECL;
}

bool EDDINodeView::is_terminator() const
{
    switch (type())
    {
        case wasp::TERM:
            return true;
        default:
            return false;
    }
}

std::string EDDINodeView::id() const {
     if(child_count() > 2 && child_at(1).type() == wasp::IDENTIFIER)
         return child_at(1).to_string();
     return "";
}
EDDINodeView EDDINodeView::id_child() const {
     if(child_count() > 2 && child_at(1).type() == wasp::IDENTIFIER)
         return child_at(1);
     return EDDINodeView();
}

EDDINodeView::Collection EDDINodeView::non_decorative_children() const
{    
    Collection results;

    for (std::size_t i = 0, count = child_count(); i < count; ++i)
    {
        const auto& child = child_at(i);
        if( child.type() == wasp::FILE )
        {
            auto * interp = m_pool->document(child.node_index());
            if ( interp != nullptr )
            {
                auto children = EDDINodeView(interp->root()).non_decorative_children();
                results.insert(results.end(), children.begin(),children.end());
            }
        }
        else if (!child.is_decorative())
            results.push_back(child);
    }
    return results;
}

EDDINodeView
EDDINodeView::first_non_decorative_child_by_name(const std::string& name) const
{
    for (std::size_t i = 0, count = child_count(); i < count; ++i)
    {
        const auto& child = child_at(i);

        if( child.type() == wasp::FILE )
        {
            auto * interp = m_pool->document(child.node_index());
            if ( interp != nullptr )
            {
                auto child = EDDINodeView(interp->root()).first_non_decorative_child_by_name(name);
                if (child.is_null() == false) return child;
            }
        }
        else if (!child.is_decorative())
        {
            if (name == child.name())
            {
                return child;
            }
        }
    }
    return EDDINodeView();  // null node
}

size_t EDDINodeView::non_decorative_children_count() const
{
    size_t result = 0;
    for (std::size_t i = 0, count = child_count(); i < count; ++i)
    {
        const auto& child = child_at(i);
        if( child.type() == wasp::FILE )
        {
            auto * interp = m_pool->document(child.node_index());
            if ( interp != nullptr )
            {
                result+=EDDINodeView(interp->root()).non_decorative_children_count();
            }
        }
        else if (!child.is_decorative())
        {
            ++result;
        }
    }
    return result;
}

std::string EDDINodeView::data() const
{
    std::stringstream str;
    m_pool->data(m_node_index, str);
    return str.str();
}

std::string EDDINodeView::path() const
{
    return wasp::node_path(*this);
}

void EDDINodeView::paths(std::ostream& out) const
{
    wasp::node_paths(*this, out);
}

std::size_t EDDINodeView::child_count() const
{
    if( type() == wasp::FILE )
    {
        auto * interp = m_pool->document(m_node_index);
        if ( interp != nullptr )
        {
            return EDDINodeView(interp->root()).child_count();
        }
    }
    return m_pool->child_count(m_node_index);
}

std::size_t  // return type
    EDDINodeView::child_count_by_name(const std::string& name,
                                     std::size_t        limit) const
{
    size_t result = 0;
    for (std::size_t i = 0, count = child_count(); i < count; ++i)
    {
        const auto& child = child_at(i);
        const std::string& child_name = child.name();
        if( child.type() == wasp::FILE )
        {
            auto * interp = m_pool->document(child.node_index());
            if ( interp != nullptr )
            {
                result+=EDDINodeView(interp->root()).child_count_by_name(name,
                                                    limit==0?limit:limit-result);
            }
        }
        else if (child_name == name)
        {
            ++result;
        }
    }
    return result;
}

EDDINodeView EDDINodeView::child_at(std::size_t index) const
{
    if( type() == wasp::FILE )
    {
        auto * interp = m_pool->document(m_node_index);
        if ( interp != nullptr )
        {
            EDDINodeView view = EDDINodeView(interp->root());
            wasp_check(view.is_null() == false);
            wasp_check(view.child_count() > index);
            return view.child_at(index);
        }
    }
    auto child_node_pool_index = m_pool->child_at(m_node_index, index);
    return EDDINodeView(child_node_pool_index, *m_pool);
}

EDDINodeView::Collection  // return type
    EDDINodeView::child_by_name(const std::string& name, std::size_t limit) const
{
    Collection results;
    for (std::size_t i = 0, count = child_count(); i < count; ++i)
    {
        auto        child      = child_at(i);
        std::string child_name = child.name();
        if( child.type() == wasp::FILE )
        {
            auto * interp = m_pool->document(child.node_index());
            if ( interp != nullptr )
            {
                auto children = EDDINodeView(interp->root()).child_by_name(name,limit);
                results.insert(results.end(), children.begin(), children.end());
            }
        }
        else if (child_name == name)
        {
            results.push_back(child);
        }
        // limit of 0 is reserved as no limit
        if (limit != 0 && results.size() == limit)
            break;
    }
    return results;
}
EDDINodeView  // return type
    EDDINodeView::first_child_by_name(const std::string& name) const
{
    if( type() == wasp::FILE )
    {
        auto * interp = m_pool->document(m_node_index);
        if ( interp != nullptr )
        {
            EDDINodeView view = EDDINodeView(interp->root());
            wasp_check(view.is_null() == false);
            return view.first_child_by_name(name);
        }
    }
    NodeView view(node_index(), *node_pool());
    return view.first_child_by_name(name);
}

std::size_t EDDINodeView::type() const
{
    return m_pool->type(m_node_index);
}

const char* EDDINodeView::name() const
{
    return m_pool->name(m_node_index);
}

std::size_t EDDINodeView::line() const
{
    return m_pool->line(m_node_index);
}

std::size_t EDDINodeView::column() const
{
    return m_pool->column(m_node_index);
}

std::size_t EDDINodeView::last_line() const
{
    return m_pool->last_line(m_node_index);
}

std::size_t EDDINodeView::last_column() const
{
    return m_pool->last_column(m_node_index);
}

bool EDDINodeView::to_bool(bool* ok) const
{
    NodeView view(value_node_index(), *node_pool());
    return view.to_bool(ok);
}

int EDDINodeView::to_int(bool* ok) const
{
    NodeView view(value_node_index(), *node_pool());
    return view.to_int(ok);
}

double EDDINodeView::to_double(bool* ok) const
{
    NodeView view(value_node_index(), *node_pool());
    return view.to_double(ok);
}

std::string EDDINodeView::to_string(bool* ok) const
{
    NodeView view(value_node_index(), *node_pool());
    return view.to_string(ok);
}

std::string EDDINodeView::last_as_string(bool* ok) const
{
    return wasp::last_as_string(*this, ok);
}

size_t EDDINodeView::value_node_index() const
{
    /// TODO - could push this lower to NodeView ?
    if (type() == wasp::KEYED_VALUE && child_count() > 0)
    {
        return child_at(child_count() - 1).node_index();
    }
    return node_index();
}
}  // end of namespace wasp
