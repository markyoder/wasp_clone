#include "waspvii/VIINodeView.h"
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
VIINodeView::VIINodeView(std::size_t                node_index,
                         const AbstractInterpreter& pool)
    : m_node_index(node_index), m_pool(&pool)
{
    wasp_require(!this->is_null());
}

VIINodeView::VIINodeView(const VIINodeView& orig)
    : m_node_index(orig.m_node_index), m_pool(orig.m_pool)
{
}

VIINodeView::~VIINodeView()
{
}

VIINodeView& VIINodeView::operator=(const VIINodeView& b)
{
    m_node_index = b.node_index();
    m_pool       = b.node_pool();
    return *this;
}

bool VIINodeView::operator==(const VIINodeView& b) const
{
    return m_pool == b.m_pool && m_node_index == b.m_node_index;
}

bool VIINodeView::operator<(const VIINodeView& b) const
{
    return m_node_index < b.m_node_index;
}

VIINodeView VIINodeView::parent() const
{    
    VIINodeView view;

    if( m_pool->document_parent() != nullptr )
    {
        if( type() != wasp::DOCUMENT_ROOT )
        {
            view = VIINodeView(m_pool->parent_node_index(m_node_index), *m_pool);
            if ( view.type() == wasp::DOCUMENT_ROOT )
            {
                view = wasp::parent_document_node<VIINodeView,
                                                    AbstractInterpreter>(m_pool);
            }
        }
    }
    else
    {
        view = VIINodeView(m_pool->parent_node_index(m_node_index), *m_pool);
    }
    return view;
}

bool VIINodeView::has_parent() const
{
    bool _has_parent = m_pool->has_parent(m_node_index);
    if (m_pool->document_parent() != nullptr)
    {
        return true;
    }
    return _has_parent;
}

bool VIINodeView::is_leaf() const
{
    NodeView view(node_index(), *node_pool());
    return view.is_leaf();
}

bool VIINodeView::is_decorative() const
{
    auto t = type();
    return is_type_decorative(t);
}
bool VIINodeView::is_type_decorative(std::size_t t)
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

bool VIINodeView::is_declarator() const
{
    return type() == wasp::DECL;
}

bool VIINodeView::is_terminator() const
{
    switch (type())
    {
        case wasp::TERM:
            return true;
        default:
            return false;
    }
}

std::string VIINodeView::id() const {
     if(child_count() > 2 && child_at(1).type() == wasp::IDENTIFIER)
         return child_at(1).to_string();
     return "";
}
VIINodeView VIINodeView::id_child() const {
     if(child_count() > 2 && child_at(1).type() == wasp::IDENTIFIER)
         return child_at(1);
     return VIINodeView();
}

VIINodeView::Collection VIINodeView::non_decorative_children() const
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
                auto children = VIINodeView(interp->root()).non_decorative_children();
                results.insert(results.end(), children.begin(),children.end());
            }
        }
        else if (!child.is_decorative())
            results.push_back(child);
    }
    return results;
}

VIINodeView
VIINodeView::first_non_decorative_child_by_name(const std::string& name) const
{
    for (std::size_t i = 0, count = child_count(); i < count; ++i)
    {
        const auto& child = child_at(i);

        if( child.type() == wasp::FILE )
        {
            auto * interp = m_pool->document(child.node_index());
            if ( interp != nullptr )
            {
                auto child = VIINodeView(interp->root()).first_non_decorative_child_by_name(name);
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
    return VIINodeView();  // null node
}

size_t VIINodeView::non_decorative_children_count() const
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
                result+=VIINodeView(interp->root()).non_decorative_children_count();
            }
        }
        else if (!child.is_decorative())
        {
            ++result;
        }
    }
    return result;
}

std::string VIINodeView::data() const
{
    std::stringstream str;
    m_pool->data(m_node_index, str);
    return str.str();
}

std::string VIINodeView::path() const
{
    return wasp::node_path(*this);
}

void VIINodeView::paths(std::ostream& out) const
{
    wasp::node_paths(*this, out);
}

std::size_t VIINodeView::child_count() const
{
    if( type() == wasp::FILE )
    {
        auto * interp = m_pool->document(m_node_index);
        if ( interp != nullptr )
        {
            return VIINodeView(interp->root()).child_count();
        }
    }
    return m_pool->child_count(m_node_index);
}

std::size_t  // return type
    VIINodeView::child_count_by_name(const std::string& name,
                                     std::size_t        limit) const
{
    if( type() == wasp::FILE )
    {
        auto * interp = m_pool->document(m_node_index);
        if ( interp != nullptr )
        {
            return VIINodeView(interp->root()).child_count_by_name(name,limit);
        }
    }
    NodeView view(node_index(), *node_pool());
    return view.child_count_by_name(name, limit);
}

VIINodeView VIINodeView::child_at(std::size_t index) const
{
    if( type() == wasp::FILE )
    {
        auto * interp = m_pool->document(m_node_index);
        if ( interp != nullptr )
        {
            VIINodeView view = VIINodeView(interp->root());
            wasp_check(view.is_null() == false);
            wasp_check(view.child_count() > index);
            return view.child_at(index);
        }
    }
    auto child_node_pool_index = m_pool->child_at(m_node_index, index);
    return VIINodeView(child_node_pool_index, *m_pool);
}

VIINodeView::Collection  // return type
    VIINodeView::child_by_name(const std::string& name, std::size_t limit) const
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
VIINodeView  // return type
    VIINodeView::first_child_by_name(const std::string& name) const
{
    if( type() == wasp::FILE )
    {
        auto * interp = m_pool->document(m_node_index);
        if ( interp != nullptr )
        {
            VIINodeView view = VIINodeView(interp->root());
            wasp_check(view.is_null() == false);
            return view.first_child_by_name(name);
        }
    }
    NodeView view(node_index(), *node_pool());
    return view.first_child_by_name(name);
}

std::size_t VIINodeView::type() const
{
    return m_pool->type(m_node_index);
}

const char* VIINodeView::name() const
{
    return m_pool->name(m_node_index);
}

std::size_t VIINodeView::line() const
{
    return m_pool->line(m_node_index);
}

std::size_t VIINodeView::column() const
{
    return m_pool->column(m_node_index);
}

std::size_t VIINodeView::last_line() const
{
    return m_pool->last_line(m_node_index);
}

std::size_t VIINodeView::last_column() const
{
    return m_pool->last_column(m_node_index);
}

bool VIINodeView::to_bool(bool* ok) const
{
    NodeView view(value_node_index(), *node_pool());
    return view.to_bool(ok);
}

int VIINodeView::to_int(bool* ok) const
{
    NodeView view(value_node_index(), *node_pool());
    return view.to_int(ok);
}

double VIINodeView::to_double(bool* ok) const
{
    NodeView view(value_node_index(), *node_pool());
    return view.to_double(ok);
}

std::string VIINodeView::to_string(bool* ok) const
{
    NodeView view(value_node_index(), *node_pool());
    return view.to_string(ok);
}

std::string VIINodeView::last_as_string(bool* ok) const
{
    return wasp::last_as_string(*this, ok);
}

size_t VIINodeView::value_node_index() const
{
    /// TODO - could push this lower to NodeView ?
    if (type() == wasp::KEYED_VALUE && child_count() > 0)
    {
        return child_at(child_count() - 1).node_index();
    }
    return node_index();
}
}  // end of namespace wasp
