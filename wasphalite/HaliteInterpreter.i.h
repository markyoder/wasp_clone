#ifndef WASP_HALITEINTERPRETER_I_H
#define WASP_HALITEINTERPRETER_I_H

template<class S>
HaliteInterpreter<S>::HaliteInterpreter()
    :Interpreter<S>(),        
    m_attribute_start_delim("<"),
    m_attribute_end_delim(">"),
    m_current_line_count(0),
    m_file_offset(0),
    m_has_file(false)
{
}
template<class S>
HaliteInterpreter<S>::HaliteInterpreter(std::ostream & err)
    : Interpreter<S>(err),    
    m_attribute_start_delim("<"),
    m_attribute_end_delim(">"),
    m_current_line_count(0),
    m_file_offset(0),
    m_has_file(false)
{
}
template<class S>
HaliteInterpreter<S>::~HaliteInterpreter()
{
}
template<class S>
bool HaliteInterpreter<S>::parse(std::istream& in, size_t startLine, size_t startColumn)
{
    return parseStream(in, hasFile() ? Interpreter<S>::stream_name() : "stream input" , startLine,startColumn);
}
template<class S>
bool HaliteInterpreter<S>::parseStream(std::istream& in
                                 , const std::string& sname
                                 , size_t start_line
                                 , size_t start_column)
{
    Interpreter<S>::template stream_name() = sname;
    Interpreter<S>::template start_line() = start_line;
    Interpreter<S>::template start_column() = start_column;

    bool parsed = parse_content(in);

    Interpreter<S>::commit_stages();

    return parsed;
}
template<class S>
bool HaliteInterpreter<S>::parseFile(const std::string &filename, size_t line)
{
    std::ifstream in(filename.c_str());
    if (!in.good()){
        Interpreter<S>::error_stream()<<"file '"<<filename<<"' is either inaccessible or doesn't exist! Unable to read."<<std::endl;
        return false;
    }
    m_has_file = true;
    return parseStream(in, filename, line);
}
template<class S>
bool HaliteInterpreter<S>::parseString(const std::string &input, const std::string& sname, size_t startLine, size_t startColumn)
{
    std::istringstream iss(input);
    return parseStream(iss, sname,startLine,startColumn);
}
template<class S>
bool HaliteInterpreter<S>::parse_content(std::istream& in)
{

    // process all lines of the file
    while( in.good() )
    {
        ++m_current_line_count;
        std::string line;
        // acquire the line from the template
        std::getline(in, line);

        // acquire the soon-to-be-fullfilled token index
        size_t token_i = Interpreter<S>::token_count();
        // push the token text
        Interpreter<S>::push_token(line.c_str(), wasp::STRING, m_file_offset);
        // push the leaf node representing the token
        size_t node_i = Interpreter<S>::push_leaf(wasp::STRING, "text", token_i);

        // stage the leaf for committal as a child of the document
        // templates are very flat; nearly all nodes are a child
        // of the document root
        Interpreter<S>::push_staged_child(node_i);

        // compute the new offset
        m_file_offset+= line.size();

        Interpreter<S>::push_line_offset(m_file_offset);
        ++m_file_offset; // increment past newline
    }
    if( in.fail() )
    {
        Interpreter<S>::error_stream()
                <<Interpreter<S>::stream_name()
               << " - error while reading"<<std::endl;
        return false;
    }
    return true;
}
template<class S>
bool HaliteInterpreter<S>::parse_line(const std::string& line)
{
    // a line could contain the following constructs with given priority
    // 1. zero or more attribute/expression substitution
    // 1.1 attribute substitution '<' name '>'
    // 1.2 expression substutution '<(' expression ')>'
    // 1.3 silent evaluation '<-' name '>' or '<-(' expression ')>'
    // 1.4 each evaluation/substitution can have optional format
    //    e.g., '<' name [: fmt="format"] '>'
    //    i.e., < pi : fmt=%2.8f >

    //
    // identify all attribute
    //
    SubStringIndexer attribute_declarators;

    if( attribute_declarators.index(line, m_attribute_start_delim) )
    {
        SubStringIndexer attribute_terminators(line, m_attribute_end_delim);

    }

    return true;
}

#endif
