#ifndef WASP_EXPRINTERPRETER_H
#define WASP_EXPRINTERPRETER_H
#include "waspcore/Interpreter.h"
#include "waspexpr/ExprParser.hpp"
#include "waspexpr/ExprLexer.h"
namespace wasp{

class ExprInterpreter : public Interpreter<default_node_type_size,default_node_index_size
                                            ,default_token_type_size,default_token_index_type_size
                                            ,default_file_offset_type_size>
{
public:
    ExprInterpreter(std::ostream & error_stream=std::cerr);
    ~ExprInterpreter();

    /**
     * @brief parse parser the given input stream
     * @param input the stream of the input data
     * @param startLine the first line of the input stream
     * @param startColumn the first column of the input stream
     * @return true, iff no input processing errors were encountered
     */
     bool parse(std::istream &input
                       , size_t m_start_line=1u
                       , size_t m_start_column=1u);

public: // variables
    /**
     * @brief lexer - current lexer instance
     */
    class ExprLexerImpl* m_lexer;
};
} // end of namespace

#endif
