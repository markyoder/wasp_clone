#include "GetPotInterpreter.h"

namespace wasp{

GetPotInterpreter::GetPotInterpreter(std::ostream & err)
    : Interpreter(err)
    ,m_lexer(nullptr)
{
}
GetPotInterpreter::~GetPotInterpreter()
{
}

bool GetPotInterpreter::parse(std::istream& in
                                        , size_t startLine
                                        , size_t startColumn)
{
    GetPotLexerImpl lexer(m_tree_nodes.token_data(),&in);
//    lexer.set_debug(m_trace_lexing);

//    lexer.set_debug(true);
    m_lexer = &lexer;
    m_start_line = startLine;
    m_start_column = startColumn;
    GetPotParser parser(*this);
//    parser.set_debug_level(true);


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
