#include "waspvii/VIINodeView.h"
#include "waspcore/utils.h"

namespace wasp
{
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
    VIINodeView view(m_pool->parent_node_index(m_node_index), *m_pool);
    return view;
}

bool VIINodeView::has_parent() const
{
    return m_pool->has_parent(m_node_index);
}

bool VIINodeView::is_leaf() const
{
    NodeView view(node_index(), *node_pool());
    return view.is_leaf();
}

bool VIINodeView::is_decorative() const
{
    auto t = type();
    switch (t)
    {
        case wasp::DECL:
        case wasp::ASSIGN:
        case wasp::COMMENT:
        case wasp::RBRACKET:  // [
        case wasp::LBRACKET:  // ]
        case wasp::DIVIDE:  // forward slash '/'
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

VIINodeView::Collection VIINodeView::non_decorative_children() const
{
    return wasp::non_decorative_children(*this);
}

VIINodeView
VIINodeView::first_non_decorative_child_by_name(const std::string& name) const
{
    return wasp::first_non_decorative_child_by_name(*this, name);
}

size_t VIINodeView::non_decorative_children_count() const
{
    return wasp::non_decorative_children_count(*this);
}

std::string VIINodeView::data() const
{
    std::stringstream str;
    m_pool->data(m_node_index, str);
    return str.str();
}

std::string VIINodeView::path() const
{
    std::stringstream str;
    m_pool->node_path(m_node_index, str);
    return str.str();
}

void VIINodeView::paths(std::ostream& out) const
{
    m_pool->node_paths(m_node_index, out);
}

std::size_t VIINodeView::child_count() const
{
    return m_pool->child_count(m_node_index);
}

std::size_t  // return type
    VIINodeView::child_count_by_name(const std::string& name,
                                     std::size_t        limit) const
{
    NodeView view(node_index(), *node_pool());
    return view.child_count_by_name(name, limit);
}

VIINodeView VIINodeView::child_at(std::size_t index) const
{
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
