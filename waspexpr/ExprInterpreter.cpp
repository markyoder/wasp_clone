#include "ExprInterpreter.h"

namespace wasp{
ExprInterpreter::ExprInterpreter(std::ostream & err)
    : m_lexer(nullptr)
{
}
ExprInterpreter::~ExprInterpreter()
{
}
bool ExprInterpreter::parse(std::istream& in
                                        , size_t startLine
                                        , size_t startColumn)
{
    ExprLexerImpl lexer(m_tree_nodes.token_data(),&in);
//    lexer.set_debug(m_trace_lexing);

//    lexer.set_debug(true);
    m_lexer = &lexer;
    m_start_line = startLine;
    m_start_column = startColumn;
    ExprParser parser(*this);
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

} // end of namespace
