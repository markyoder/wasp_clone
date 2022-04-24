#ifndef WASP_HITINTERPRETER_I_H
#define WASP_HITINTERPRETER_I_H
template<class S>
HITInterpreter<S>::HITInterpreter(std::ostream& err) : Interpreter<S>(err)
{
}
template<class S>
HITInterpreter<S>::~HITInterpreter()
{
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
