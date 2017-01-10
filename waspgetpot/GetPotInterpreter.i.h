#ifndef WASP_GETPOTINTERPRETER_I_H
#define WASP_GETPOTINTERPRETER_I_H
template<class S>
GetPotInterpreter<S>::GetPotInterpreter(std::ostream & err)
    : Interpreter<S>(err)
    , m_lexer(nullptr)
{
}
template<class S>
GetPotInterpreter<S>::~GetPotInterpreter()
{
}
template<class S>
bool GetPotInterpreter<S>::parse(std::istream& in
                                        , std::size_t startLine
                                        , std::size_t startColumn)
{
    return Interpreter<S>::template parse_impl<GetPotLexerImpl
            ,GetPotParser
            ,GetPotInterpreter>(m_lexer
                ,in
                ,"input"
                ,startLine
                ,startColumn);
}
#endif
