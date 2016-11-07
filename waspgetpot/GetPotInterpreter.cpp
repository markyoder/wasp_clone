#include "GetPotInterpreter.h"
#include "GetPotLexer.h"
namespace wasp{


GetPotInterpreter::GetPotInterpreter(std::ostream & err)
    : m_lexer(nullptr)
    , m_start_column(1)
    , m_start_line(1)
    , m_stream_name("stream")
    , m_error_stream(err)
    , m_root_index(-1) // not set
{

}
GetPotInterpreter::~GetPotInterpreter()
{

}

void GetPotInterpreter::error(const class location& l,
                  const std::string& m)
{
    m_error_stream << l << ": " << m << std::endl;
}

TreeNodeView GetPotInterpreter::root()const
{
    // have any nodes?
    if( m_tree_nodes.size() == 0 )
    {
        return TreeNodeView(m_tree_nodes.size(),this->m_tree_nodes);
    }
    return TreeNodeView(m_root_index,this->m_tree_nodes);
}

bool GetPotInterpreter::parse(std::istream& in, size_t startLine, size_t startColumn)
{
    GetPotLexerImpl lexer(m_tree_nodes.token_data(),&in);
//    lexer.set_debug(m_trace_lexing);

//    lexer.set_debug(true);
    m_lexer = &lexer;
    m_start_line = startLine;
    m_start_column = startColumn;
    GetPotParser parser(*this);
//    parser.set_debug_level(m_trace_parsing);


    bool parsed = parser.parse() == 0;

    if( !m_root_child_indices.empty() )
    {
        m_root_index = push_parent(DOCUMENT_ROOT,"document",m_root_child_indices);
        m_root_child_indices.clear();
    }
    m_lexer = nullptr;
    return parsed;
}

size_t GetPotInterpreter::push_leaf(default_node_type_size node_type
                                    , const char *node_name
                                    , default_token_index_type_size token_index)
{
    size_t node_index = node_count();
    m_tree_nodes.push_leaf(node_type,node_name
                     ,token_index);
    return node_index;
}
size_t GetPotInterpreter::push_parent(default_node_type_size node_type
                                    , const char *node_name
                                    , const std::vector<default_node_index_size>&child_indices)
{
    size_t node_index = node_count();
    m_tree_nodes.push_parent(node_type,node_name
                     ,child_indices);
    return node_index;
}
}// end of namespace
