#ifndef WASP_EXPRINTERPRETER_I_H
#define WASP_EXPRINTERPRETER_I_H
template<class S>
ExprInterpreter<S>::ExprInterpreter(std::ostream & err)
    : Interpreter<S>(), m_lexer(nullptr)
{
}
template<class S>
ExprInterpreter<S>::~ExprInterpreter()
{
}
template<class S>
bool ExprInterpreter<S>::parse(std::istream& in
                                        , std::size_t startLine
                                        , std::size_t startColumn)
{
    return Interpreter<S>::template parse_impl<ExprLexerImpl
            ,ExprParser
            ,ExprInterpreter>(m_lexer
                ,in
                ,"input"
                ,startLine
                ,startColumn);
}

#endif
