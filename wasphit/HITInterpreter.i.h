#ifndef WASP_HITINTERPRETER_I_H
#define WASP_HITINTERPRETER_I_H
template<class S>
HITInterpreter<S>::HITInterpreter(std::ostream& err) : Interpreter<S>(err)
    , m_parent(nullptr)
{
}
template<class S>
HITInterpreter<S>::~HITInterpreter()
{
}

template<class S>
HITInterpreter<S>* HITInterpreter<S>::create_nested_interpreter(Interpreter<S>* parent)
{
    wasp_require(parent);
    auto* interp = new HITInterpreter<S>(parent->error_stream());
    wasp_insist(dynamic_cast<HITInterpreter<S>*>(parent) != nullptr, 
        "parent interpreter must be the same type");
    interp->m_parent = dynamic_cast<HITInterpreter<S>*>(parent);
    return interp;
}

template<class S>
bool HITInterpreter<S>::parse(std::istream& in,
                                 std::size_t   startLine,
                                 std::size_t   startColumn)
{
    return Interpreter<S>::template parse_impl<HITParser>(
        in, "stream input", startLine, startColumn);
}
template<class S>
bool HITInterpreter<S>::parseFile(const std::string& filename, size_t line)
{
    std::ifstream in(filename.c_str());
    if (!in.good())
    {
        Interpreter<S>::error_stream()
            << "file '" << filename
            << "' is either inaccessible or doesn't exist! Unable to read."
            << std::endl;
        return false;
    }
    return parse(in, line);
}
#endif
