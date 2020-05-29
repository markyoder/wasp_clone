#include "waspgetpot/GetPotNodeView.h"
#include "waspcore/utils.h"

namespace wasp
{
GetPotNodeView::GetPotNodeView(std::size_t                node_index,
                               const AbstractInterpreter& data)
    : m_node_index(node_index), m_pool(&data)
{
}
GetPotNodeView::GetPotNodeView(const GetPotNodeView& orig)
    : m_node_index(orig.m_node_index), m_pool(orig.m_pool)
{
}

GetPotNodeView::~GetPotNodeView()
{
}

GetPotNodeView& GetPotNodeView::operator=(const GetPotNodeView& b)
{
    m_node_index = b.node_index();
    m_pool       = b.node_pool();
    return *this;
}

bool GetPotNodeView::operator==(const GetPotNodeView& b) const
{
    return m_pool == b.m_pool && m_node_index == b.m_node_index;
}

bool GetPotNodeView::operator<(const GetPotNodeView& b) const
{
    return m_node_index < b.m_node_index;
}

GetPotNodeView GetPotNodeView::parent() const
{
    GetPotNodeView view(m_pool->parent_node_index(m_node_index), *m_pool);
    return view;
}

bool GetPotNodeView::has_parent() const
{
    return m_pool->has_parent(m_node_index);
}

bool GetPotNodeView::is_leaf() const
{
    NodeView view(node_index(), *node_pool());
    return view.is_leaf();
}

bool GetPotNodeView::is_decorative() const
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
        case wasp::WASP_COMMA:       // ,
        case wasp::COLON:
        case wasp::QUOTE:     // delimits arrays, e.g., ' 1 2 3 '
        case wasp::LBRACKET:  // [
        case wasp::RBRACKET:  // ]
            return true;
    }
    return false;
}

bool GetPotNodeView::is_declarator() const
{
    return type() == wasp::DECL;
}

bool GetPotNodeView::is_terminator() const
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

GetPotNodeView::Collection GetPotNodeView::non_decorative_children() const
{
    return wasp::non_decorative_children(*this);
}

GetPotNodeView GetPotNodeView::first_non_decorative_child_by_name(
    const std::string& name) const
{
    return wasp::first_non_decorative_child_by_name(*this, name);
}

size_t GetPotNodeView::non_decorative_children_count() const
{
    return wasp::non_decorative_children_count(*this);
}

std::string GetPotNodeView::data() const
{
    std::stringstream str;
    m_pool->data(m_node_index, str);
    return str.str();
}

std::string GetPotNodeView::path() const
{
    std::stringstream str;
    m_pool->node_path(m_node_index, str);
    return str.str();
}

void GetPotNodeView::paths(std::ostream& out) const
{
    m_pool->node_paths(m_node_index, out);
}

std::size_t GetPotNodeView::child_count() const
{
    return m_pool->child_count(m_node_index);
}
std::size_t  // return type
    GetPotNodeView::child_count_by_name(const std::string& name,
                                        std::size_t        limit) const
{
    NodeView view(node_index(), *node_pool());
    return view.child_count_by_name(name, limit);
}

GetPotNodeView GetPotNodeView::child_at(std::size_t index) const
{
    auto child_node_pool_index = m_pool->child_at(m_node_index, index);
    return GetPotNodeView(child_node_pool_index, *m_pool);
}
GetPotNodeView::Collection  // return type
    GetPotNodeView::child_by_name(const std::string& name,
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
GetPotNodeView  // return type
    GetPotNodeView::first_child_by_name(const std::string& name) const
{
    NodeView view(node_index(), *node_pool());
    return view.first_child_by_name(name);
}

std::size_t GetPotNodeView::type() const
{
    return m_pool->type(m_node_index);
}

const char* GetPotNodeView::name() const
{
    return m_pool->name(m_node_index);
}

std::size_t GetPotNodeView::line() const
{
    return m_pool->line(m_node_index);
}

std::size_t GetPotNodeView::column() const
{
    return m_pool->column(m_node_index);
}

std::size_t GetPotNodeView::last_line() const
{
    return m_pool->last_line(m_node_index);
}

std::size_t GetPotNodeView::last_column() const
{
    return m_pool->last_column(m_node_index);
}

bool GetPotNodeView::to_bool(bool* ok) const
{
    NodeView view(value_node_index(), *node_pool());
    return view.to_bool(ok);
}

int GetPotNodeView::to_int(bool* ok) const
{
    NodeView view(value_node_index(), *node_pool());
    return view.to_int(ok);
}

double GetPotNodeView::to_double(bool* ok) const
{
    NodeView view(value_node_index(), *node_pool());
    return view.to_double(ok);
}

std::string GetPotNodeView::to_string(bool* ok) const
{
    NodeView view(value_node_index(), *node_pool());
    return view.to_string(ok);
}

std::string GetPotNodeView::last_as_string(bool* ok) const
{
    return wasp::last_as_string(*this, ok);
}

size_t GetPotNodeView::value_node_index() const
{
    /// TODO - could push this lower to NodeView ?
    if (type() == wasp::KEYED_VALUE && child_count() > 0)
    {
        return child_at(child_count() - 1).node_index();
    }
    return node_index();
}
}  // end of namespace wasp
