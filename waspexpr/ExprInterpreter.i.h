#ifndef WASP_EXPRINTERPRETER_I_H
#define WASP_EXPRINTERPRETER_I_H
template<class S>
ExprInterpreter<S>::ExprInterpreter(std::ostream & err)
    : Interpreter<S>()
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
    return Interpreter<S>::template parse_impl<ExprParser>(in
                ,"input"
                ,startLine
                ,startColumn);
}
template<class S>
void ExprInterpreter<S>::Context::clear(){
    for( auto v: m_variables ) delete v.second;
    m_variables.clear();
    for( auto f: m_functions) delete f.second;
    m_functions.clear();
}

template<class S>
typename ExprInterpreter<S>::Context&
ExprInterpreter<S>::Context::add_default_variables()
{
    store("e",2.7182818284590452353602874713527);
    store("pi",3.14159265359);
    return *this;
}

template<class S>
typename ExprInterpreter<S>::Context&
ExprInterpreter<S>::Context::add_default_functions()
{
    wasp_check( function_exists("sin") == false );
    add_function("sin",new FSin() );
    return *this;
}
template<class S>
bool
ExprInterpreter<S>::Context::function_exists(const std::string & name) const
{
    return m_functions.find(name) != m_functions.end();
}

#endif
