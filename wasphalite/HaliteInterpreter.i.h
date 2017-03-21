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

        bool line_processed = parse_line(line);

        if( line_processed == false ) return false;

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
void HaliteInterpreter<S>::capture_leaf(const std::string& node_name
                                        , size_t node_type
                                        , const std::string& data
                                        , size_t token_type
                                        , size_t file_offset)
{
    // acquire the soon-to-be-fullfilled token index
    size_t token_i = Interpreter<S>::token_count();

    // push the token text
    Interpreter<S>::push_token(data.c_str(), token_type, file_offset);
    // push the leaf node representing the token
    size_t node_i = Interpreter<S>::push_leaf(node_type, node_name.c_str(), token_i);

    // stage the leaf for committal as a child of the document
    // templates are very flat; nearly all nodes are a child
    // of the document root
    Interpreter<S>::push_staged_child(node_i);
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
    // identify all attribute locations
    //
    SubStringIndexer attribute_declarators;
    SubStringIndexer::IndexPairs_type attribute_indices;
    if( attribute_declarators.index(line, m_attribute_start_delim) )
    {
        SubStringIndexer attribute_terminators(line, m_attribute_end_delim);
        attribute_indices = attribute_declarators.merge(attribute_terminators);
    }

    if( attribute_indices.empty() == false )
    { // in addition to the attributes, capture the components before, between, and after
        size_t current_column_index = 0;
        size_t current_attribute_index = 0;
        size_t limit = attribute_indices.size();
        capture(line
                ,current_column_index
                ,current_attribute_index
                ,attribute_indices
                ,limit);
    }
    // if line is plain text, capture
    else
    {
        capture_leaf("txt", wasp::STRING, line, wasp::STRING, m_file_offset );
    }
    // compute the new offset
    m_file_offset+= line.size();
    Interpreter<S>::push_line_offset(m_file_offset);
    return true;
}
template<class S>
void HaliteInterpreter<S>::capture(const std::string& data
                   ,size_t& current_column_index
                   ,size_t& current_attribute_index
                   ,const SubStringIndexer::IndexPairs_type& attribute_indices
                   ,size_t limit)
{
    wasp_require( limit <= attribute_indices.size() );
    if( limit == 0 ) limit = attribute_indices.size();
    for( size_t i = current_attribute_index; i < limit; ++i )
    {
        const SubStringIndexer::IndexPair_type& attribute_index
                = attribute_indices[i];
        // check for preceeding text/name that needs to be put into tree
        if( attribute_index.first > current_column_index )
        {
            size_t length = attribute_index.first - current_column_index;
            size_t file_offset = m_file_offset + current_column_index;
            const std::string & prefixed
                    = data.substr(current_column_index,length);
            capture_leaf("txt",wasp::STRING, prefixed.c_str()
                         ,wasp::STRING,file_offset);
        }
        size_t stage = Interpreter<S>::push_staged(wasp::IDENTIFIER, "attr",{});
        { // capture declarator
            size_t file_offset = m_file_offset + attribute_index.first;
            capture_leaf(m_attribute_start_delim,wasp::DECL
                     ,m_attribute_start_delim,wasp::STRING
                     ,file_offset);
        }

        size_t look_ahead_i = i+1;
        while( look_ahead_i < limit && attribute_indices[look_ahead_i].first
               < attribute_index.second) ++ look_ahead_i;
        look_ahead_i -= 1;
        current_column_index = attribute_index.first
                +m_attribute_start_delim.size();
        // check if we need to capture nested
        if( look_ahead_i != i )
        {
            capture(data,current_column_index
                    ,i,attribute_indices
                    ,look_ahead_i);
        }
        // nothing is nested, just capture the txt
        else
        {
            size_t file_offset = m_file_offset + current_column_index;
            size_t length = attribute_index.second - current_column_index;
            const std::string & txt
                    = data.substr(current_column_index,length);
            capture_leaf("txt",wasp::STRING, txt.c_str()
                         ,wasp::STRING,file_offset);
        }
        { // capture terminator
            size_t file_offset = m_file_offset + attribute_index.second;
            capture_leaf(m_attribute_end_delim,wasp::TERM
                     ,m_attribute_end_delim,wasp::STRING
                     ,file_offset);
        }
        Interpreter<S>::commit_staged(stage);

        // update the current column index to be past delimiter
        current_column_index=attribute_indices[i].second
                + m_attribute_end_delim.size();
    }
}

#endif
