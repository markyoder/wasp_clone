#include "waspson/SONNodeView.h"

namespace wasp{

SONNodeView::SONNodeView(std::size_t                node_index,
                         const AbstractInterpreter& pool)
    : m_node_index(node_index), m_pool(&pool)
{
    wasp_require(!this->is_null());
}

SONNodeView::SONNodeView(const SONNodeView& orig)
    : m_node_index(orig.m_node_index), m_pool(orig.m_pool)
{
}


SONNodeView::~SONNodeView()
{
}

SONNodeView& SONNodeView::operator=(const SONNodeView& b)
{
    m_node_index = b.node_index();
    m_pool       = b.node_pool();
    return *this;
}

bool SONNodeView::operator==(const SONNodeView& b) const
{
    return m_pool == b.m_pool && m_node_index == b.m_node_index;
}

bool SONNodeView::operator<(const SONNodeView& b) const
{
    return m_node_index < b.m_node_index;
}

SONNodeView SONNodeView::parent() const
{
    SONNodeView view(m_pool->parent_node_index(m_node_index), *m_pool);
    return view;
}

bool SONNodeView::has_parent() const
{
    return m_pool->has_parent(m_node_index);
}

std::string SONNodeView::id() const
{
    SONNodeView potential_id_child = id_child();
    if (potential_id_child.is_null())
        return "";
    return potential_id_child.to_string();
}

SONNodeView SONNodeView::id_child() const
{
    // id is the 3rd child
    if (child_count() > 2)
    {
        const SONNodeView& child      = child_at(2);
        std::string        child_name = child.name();
        if (child_name == "id")
            return child;
    }
    return SONNodeView();  // null view
}

bool SONNodeView::is_leaf() const
{
    NodeView view(node_index(), *node_pool());
    return view.is_leaf();
}

bool SONNodeView::is_decorative() const
{
    auto t = type();
    switch (t)
    {
        case wasp::DECL:
        case wasp::TERM:
        case wasp::ASSIGN:
        case wasp::COMMENT:
        case wasp::IDENTIFIER:
        case wasp::OBJECT_TERM:
        case wasp::WASP_COMMA:  // ,
        case wasp::COLON:
        case wasp::LPAREN:    // (
        case wasp::RPAREN:    // )
        case wasp::LBRACE:    // {
        case wasp::RBRACE:    // }
        case wasp::LBRACKET:  // [
        case wasp::RBRACKET:  // ]
        case wasp::EXECUTION_UNIT_START:
        case wasp::EXECUTION_UNIT_END:
            return true;
    }
    return false;
}

bool SONNodeView::is_declarator() const
{
    return type() == wasp::DECL;
}

bool SONNodeView::is_terminator() const
{
    switch (type())
    {
        case wasp::TERM:
        case wasp::RBRACE:    // }
        case wasp::RBRACKET:  // ]
        case wasp::EXECUTION_UNIT_END:
            return true;
        default:
            return false;
    }
}

SONNodeView::Collection SONNodeView::non_decorative_children() const
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

SONNodeView
SONNodeView::first_non_decorative_child_by_name(const std::string& name) const
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
    return SONNodeView();  // null node
}

size_t SONNodeView::non_decorative_children_count() const
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

std::string SONNodeView::data() const
{
    std::stringstream str;
    m_pool->data(m_node_index, str);
    return str.str();
}

std::string SONNodeView::path() const
{
    std::stringstream str;
    m_pool->node_path(m_node_index, str);
    return str.str();
}

void SONNodeView::paths(std::ostream& out) const
{
    m_pool->node_paths(m_node_index, out);
}

std::size_t SONNodeView::child_count() const
{
    return m_pool->child_count(m_node_index);
}
std::size_t  // return type
    SONNodeView::child_count_by_name(const std::string& name,
                                     std::size_t        limit) const
{
    NodeView view(node_index(), *node_pool());
    return view.child_count_by_name(name, limit);
}

SONNodeView SONNodeView::child_at(std::size_t index) const
{
    auto child_node_pool_index = m_pool->child_at(m_node_index, index);
    return SONNodeView(child_node_pool_index, *m_pool);
}
SONNodeView::Collection  // return type
    SONNodeView::child_by_name(const std::string& name, std::size_t limit) const
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
SONNodeView  // return type
    SONNodeView::first_child_by_name(const std::string& name) const
{
    NodeView view(node_index(), *node_pool());
    return view.first_child_by_name(name);
}

std::size_t SONNodeView::type() const
{
    return m_pool->type(m_node_index);
}

const char* SONNodeView::name() const
{
    return m_pool->name(m_node_index);
}

std::size_t SONNodeView::line() const
{
    return m_pool->line(m_node_index);
}

std::size_t SONNodeView::column() const
{
    return m_pool->column(m_node_index);
}

std::size_t SONNodeView::last_line() const
{
    return m_pool->last_line(m_node_index);
}

std::size_t SONNodeView::last_column() const
{
    return m_pool->last_column(m_node_index);
}

bool SONNodeView::to_bool(bool* ok) const
{
    NodeView view(value_node_index(), *node_pool());
    return view.to_bool(ok);
}

int SONNodeView::to_int(bool* ok) const
{
    NodeView view(value_node_index(), *node_pool());
    return view.to_int(ok);
}

double SONNodeView::to_double(bool* ok) const
{
    NodeView view(value_node_index(), *node_pool());
    return view.to_double(ok);
}

std::string SONNodeView::to_string(bool* ok) const
{
    NodeView view(value_node_index(), *node_pool());
    return view.to_string(ok);
}

std::string SONNodeView::last_as_string(bool* ok) const
{
    size_t count = child_count();
    if (count > 0)
    {
        return child_at(count - 1).last_as_string(ok);
    }
    return to_string(ok);
}

size_t SONNodeView::value_node_index() const
{
    /// TODO - could push this lower to NodeView ?
    if (type() == wasp::KEYED_VALUE && child_count() > 0)
    {
        return child_at(child_count() - 1).node_index();
    }
    return node_index();
}

} // end of namespace wasp
