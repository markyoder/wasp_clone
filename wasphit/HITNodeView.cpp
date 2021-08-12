#include "wasphit/HITNodeView.h"
#include "waspcore/utils.h"

namespace wasp
{
HITNodeView::HITNodeView(std::size_t                node_index,
                               const AbstractInterpreter& data)
    : m_node_index(node_index), m_pool(&data)
{
}
HITNodeView::HITNodeView(const HITNodeView& orig)
    : m_node_index(orig.m_node_index), m_pool(orig.m_pool)
{
}

HITNodeView::~HITNodeView()
{
}

HITNodeView& HITNodeView::operator=(const HITNodeView& b)
{
    m_node_index = b.node_index();
    m_pool       = b.node_pool();
    return *this;
}

bool HITNodeView::operator==(const HITNodeView& b) const
{
    return m_pool == b.m_pool && m_node_index == b.m_node_index;
}

bool HITNodeView::operator<(const HITNodeView& b) const
{
    return m_node_index < b.m_node_index;
}

HITNodeView HITNodeView::parent() const
{
    HITNodeView view(m_pool->parent_node_index(m_node_index), *m_pool);
    return view;
}

bool HITNodeView::has_parent() const
{
    return m_pool->has_parent(m_node_index);
}

bool HITNodeView::is_leaf() const
{
    NodeView view(node_index(), *node_pool());
    return view.is_leaf();
}

bool HITNodeView::is_decorative() const
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
        case wasp::DOT_SLASH:        // sub block component '[./subblock]'
        case wasp::SEMICOLON:        // ;
        case wasp::COLON:
        case wasp::QUOTE:     // delimits arrays, e.g., ' 1 2 3 '
        case wasp::LBRACKET:  // [
        case wasp::RBRACKET:  // ]
            return true;
    }
    return false;
}

bool HITNodeView::is_declarator() const
{
    return type() == wasp::DECL;
}

bool HITNodeView::is_terminator() const
{
    switch (type())
    {
        case wasp::TERM:
        case wasp::OBJECT_TERM:
            return true;
        default:
            return false;
    }
}

HITNodeView::Collection HITNodeView::non_decorative_children() const
{
    return wasp::non_decorative_children(*this);
}

HITNodeView HITNodeView::first_non_decorative_child_by_name(
    const std::string& name) const
{
    return wasp::first_non_decorative_child_by_name(*this, name);
}

size_t HITNodeView::non_decorative_children_count() const
{
    return wasp::non_decorative_children_count(*this);
}

std::string HITNodeView::data() const
{
    std::stringstream str;
    m_pool->data(m_node_index, str);
    return str.str();
}

std::string HITNodeView::path() const
{
    std::stringstream str;
    m_pool->node_path(m_node_index, str);
    return str.str();
}

void HITNodeView::paths(std::ostream& out) const
{
    m_pool->node_paths(m_node_index, out);
}

std::size_t HITNodeView::child_count() const
{
    return m_pool->child_count(m_node_index);
}
std::size_t  // return type
    HITNodeView::child_count_by_name(const std::string& name,
                                        std::size_t        limit) const
{
    NodeView view(node_index(), *node_pool());
    return view.child_count_by_name(name, limit);
}

HITNodeView HITNodeView::child_at(std::size_t index) const
{
    auto child_node_pool_index = m_pool->child_at(m_node_index, index);
    return HITNodeView(child_node_pool_index, *m_pool);
}
HITNodeView::Collection  // return type
    HITNodeView::child_by_name(const std::string& name,
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
HITNodeView  // return type
    HITNodeView::first_child_by_name(const std::string& name) const
{
    NodeView view(node_index(), *node_pool());
    return view.first_child_by_name(name);
}

std::size_t HITNodeView::type() const
{
    return m_pool->type(m_node_index);
}

const char* HITNodeView::name() const
{
    return m_pool->name(m_node_index);
}

std::size_t HITNodeView::line() const
{
    return m_pool->line(m_node_index);
}

std::size_t HITNodeView::column() const
{
    return m_pool->column(m_node_index);
}

std::size_t HITNodeView::last_line() const
{
    return m_pool->last_line(m_node_index);
}

std::size_t HITNodeView::last_column() const
{
    return m_pool->last_column(m_node_index);
}

bool HITNodeView::to_bool(bool* ok) const
{
    NodeView view(value_node_index(), *node_pool());
    return view.to_bool(ok);
}

int HITNodeView::to_int(bool* ok) const
{
    NodeView view(value_node_index(), *node_pool());
    return view.to_int(ok);
}

double HITNodeView::to_double(bool* ok) const
{
    NodeView view(value_node_index(), *node_pool());
    return view.to_double(ok);
}

std::string HITNodeView::to_string(bool* ok) const
{
    NodeView view(value_node_index(), *node_pool());
    return view.to_string(ok);
}

std::string HITNodeView::last_as_string(bool* ok) const
{
    return wasp::last_as_string(*this, ok);
}

size_t HITNodeView::value_node_index() const
{
    /// TODO - could push this lower to NodeView ?
    if (type() == wasp::KEYED_VALUE && child_count() > 0)
    {
        return child_at(child_count() - 1).node_index();
    }
    return node_index();
}
}  // end of namespace wasp
