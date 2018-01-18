#ifndef WASP_GETPOTINTERPRETER_I_H
#define WASP_GETPOTINTERPRETER_I_H
template<class S>
GetPotInterpreter<S>::GetPotInterpreter(std::ostream& err) : Interpreter<S>(err)
{
}
template<class S>
GetPotInterpreter<S>::~GetPotInterpreter()
{
}
template<class S>
bool GetPotInterpreter<S>::parse(std::istream& in,
                                 std::size_t   startLine,
                                 std::size_t   startColumn)
{
    return Interpreter<S>::template parse_impl<GetPotParser>(
        in, "stream input", startLine, startColumn);
}
template<class S>
bool GetPotInterpreter<S>::parseFile(const std::string& filename, size_t line)
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
