#ifndef WASP_GETPOTINTERPRETER_H
#define WASP_GETPOTINTERPRETER_H
#include "waspcore/TreeNodePool.h"
#include "waspgetpot/GetPotLexer.h" // lexer definition must come before interpreter
#include "waspcore/Interpreter.h"

namespace wasp{

template<class S = TreeNodePool<> >
class GetPotInterpreter : public Interpreter<S>
{
public:
    GetPotInterpreter(std::ostream & error_stream=std::cerr);
    ~GetPotInterpreter();

    /**
     * @brief parse parser the given input stream
     * @param input the stream of the input data
     * @param startLine the first line of the input stream
     * @param startColumn the first column of the input stream
     * @return true, iff no input processing errors were encountered
     */
     bool parse(std::istream &input
                       , std::size_t m_start_line=1u
                       , std::size_t m_start_column=1u);

public: // variables
    /**
     * @brief lexer - current lexer instance
     */
    class GetPotLexerImpl* m_lexer;
    virtual class GetPotLexerImpl * lexer(){return m_lexer;}
};
#include "waspgetpot/GetPotInterpreter.i.h"
} // end of namespace
#endif
