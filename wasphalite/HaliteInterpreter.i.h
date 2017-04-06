#ifndef WASP_HALITEINTERPRETER_I_H
#define WASP_HALITEINTERPRETER_I_H

template<class S>
HaliteInterpreter<S>::HaliteInterpreter()
    :Interpreter<S>(),        
    m_attribute_start_delim("<"),
    m_attribute_end_delim(">"),
    m_attribute_options_delim(":"),
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
    m_attribute_options_delim(":"),
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
bool HaliteInterpreter<S>::parse(std::istream& in
                                 , size_t startLine, size_t startColumn)
{
    return parseStream(in,
                       hasFile()
                       ? Interpreter<S>::stream_name()
                       : "stream input" , startLine,startColumn);
}
template<class S>
bool HaliteInterpreter<S>::parseStream(std::istream& in
                                 , const std::string& sname
                                 , size_t start_line
                                 , size_t start_column)
{
    Interpreter<S>::stream_name() = sname;
    Interpreter<S>::start_line() = start_line;
    Interpreter<S>::start_column() = start_column;

    bool parsed = parse_content(in);

    Interpreter<S>::commit_stages();

    return parsed;
}
template<class S>
bool HaliteInterpreter<S>::parseFile(const std::string &filename, size_t line)
{
    std::ifstream in(filename.c_str());
    if (!in.good()){
        Interpreter<S>::error_stream()
                <<"file '"<<filename<<"' is either inaccessible or doesn't exist!"
                                      " Unable to read."<<std::endl;
        return false;
    }
    m_has_file = true;
    return parseStream(in, filename, line);
}
template<class S>
bool HaliteInterpreter<S>::parseString(const std::string &input
                                       , const std::string& sname
                                       , size_t startLine, size_t startColumn)
{
    std::istringstream iss(input);
    return parseStream(iss, sname,startLine,startColumn);
}
template<class S>
bool HaliteInterpreter<S>::parse_content(std::istream& in)
{

    // process all lines of the file
    for(std::string line; std::getline(in,line); )
    {
        ++m_current_line_count;
        bool line_processed = parse_line(line);

        if( line_processed == false ) return false;

        ++m_file_offset; // increment past newline
    }
    if( !in.eof() && in.fail() )
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
    size_t node_i
            = Interpreter<S>::push_leaf(node_type, node_name.c_str(), token_i);

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
    size_t current_column_index = 0;
    // check for file import statement
    bool is_directive = line.compare(0,1,"#") == 0;
    static std::string import_stmt = "#import";
    bool is_import = false;
    static std::string ifdef_stmt = "#ifdef";
    bool is_ifdef = false; // assume false
    static std::string ifndef_stmt = "#ifndef";
    bool is_ifndef = false; // assume false
    static std::string if_stmt = "#if";
    bool is_if = false; // assume false
    static std::string elseif_stmt = "#elseif";
    bool is_elseif = false; // assume false
    static std::string else_stmt = "#else";
    bool is_else = false; // assume false
    static std::string endif_stmt = "#endif";
    bool is_endif = false; // assume false

    if( is_directive && (is_import
                         = line.compare(0, import_stmt.size(), import_stmt) == 0) )
    { // capture import declarator
        Interpreter<S>::push_staged(wasp::FILE, "import",{});
        size_t offset = m_file_offset + current_column_index;
        capture_leaf("decl", wasp::DECL
                     ,line.substr(current_column_index,import_stmt.size())
                     , wasp::STRING, offset );
        current_column_index += import_stmt.size();
    }
    else if(is_directive &&  (is_ifdef
                              = line.compare(0,ifdef_stmt.size(),ifdef_stmt) == 0) )
    {
        Interpreter<S>::push_staged(wasp::CONDITIONAL, "ifdef",{});
        size_t offset = m_file_offset + current_column_index;
        capture_leaf("decl", wasp::DECL
                     ,line.substr(current_column_index,ifdef_stmt.size())
                     , wasp::STRING, offset );
        current_column_index += ifdef_stmt.size();
    }
    else if(is_directive &&  (is_ifndef
                              = line.compare(0,ifndef_stmt.size(),ifndef_stmt) == 0) )
    {
        Interpreter<S>::push_staged(wasp::CONDITIONAL, "ifndef",{});
        size_t offset = m_file_offset + current_column_index;
        capture_leaf("decl", wasp::DECL
                     ,line.substr(current_column_index,ifndef_stmt.size())
                     , wasp::STRING, offset );
        current_column_index += ifndef_stmt.size();
    }
    else if(is_directive &&  (is_if
                              = line.compare(0,if_stmt.size(),if_stmt) == 0) )
    {
        Interpreter<S>::push_staged(wasp::CONDITIONAL, "if",{});
        size_t offset = m_file_offset + current_column_index;
        capture_leaf("decl", wasp::DECL
                     ,line.substr(current_column_index,if_stmt.size())
                     , wasp::STRING, offset );
        current_column_index += if_stmt.size();
    }
    else if(is_directive &&  (is_elseif
                              = line.compare(0,elseif_stmt.size(),elseif_stmt) == 0) )
    {
        // check for required condition to be open
        wasp_check( Interpreter<S>::staged_count() > 0 );
        size_t staged_type = Interpreter<S>::staged_type(Interpreter<S>::staged_count()-1);
        if( staged_type != wasp::CONDITIONAL  )
        {
            Interpreter<S>::error_stream()<<"***Error : line "
                         <<Interpreter<S>::line_count()+1
                        <<" is an unmatched conditional elseif."
                       <<" The matching #if, #ifdef, #ifndef, or #elseif"
                        <<" is missing."<<std::endl;
            return false;
        }
        // commit/close the current staged conditional to the parse tree
        Interpreter<S>::commit_staged(Interpreter<S>::staged_count()-1);
        // push new elseif staged conditional
        Interpreter<S>::push_staged(wasp::CONDITIONAL, "elseif",{});
        size_t offset = m_file_offset + current_column_index;
        capture_leaf("decl", wasp::DECL
                     ,line.substr(current_column_index,elseif_stmt.size())
                     , wasp::STRING, offset );
        current_column_index += elseif_stmt.size();
    }
    else if(is_directive &&  (is_else
                              = line.compare(0,else_stmt.size(),else_stmt) == 0) )
    {
        // check for required condition to be open
        wasp_check( Interpreter<S>::staged_count() > 0 );
        size_t staged_type = Interpreter<S>::staged_type(Interpreter<S>::staged_count()-1);
        if( staged_type != wasp::CONDITIONAL  )
        {
            Interpreter<S>::error_stream()<<"***Error : line "
                         <<Interpreter<S>::line_count()+1
                        <<" is an unmatched conditional else."
                       <<" The matching #if, #ifdef, #ifndef, or #elseif"
                        <<" is missing."<<std::endl;
            return false;
        }
        // commit/close the current staged conditional to the parse tree
        Interpreter<S>::commit_staged(Interpreter<S>::staged_count()-1);
        // push new elseif staged conditional
        Interpreter<S>::push_staged(wasp::CONDITIONAL, "else",{});
        size_t offset = m_file_offset + current_column_index;
        capture_leaf("decl", wasp::DECL
                     ,line.substr(current_column_index,else_stmt.size())
                     , wasp::STRING, offset );
        current_column_index += else_stmt.size();
    }
    else if(is_directive &&  (is_endif = line.compare(0,endif_stmt.size(),endif_stmt) == 0) )
    {
        wasp_check( Interpreter<S>::staged_count() > 0 );
        size_t staged_type = Interpreter<S>::staged_type(Interpreter<S>::staged_count()-1);
        if( staged_type != wasp::CONDITIONAL  )
        {
            Interpreter<S>::error_stream()<<"***Error : line "
                         <<Interpreter<S>::line_count()+1
                        <<" is an unmatched conditional terminator - '"
                       <<line<<"'."
                       <<" The matching #if, #ifdef, #ifndef, #elseif,"
                        <<" or #else is missing."<<std::endl;
            return false;
        }
        // capture the terminator as a leaf of the current stage
        size_t offset = m_file_offset + current_column_index;
        capture_leaf("endif", wasp::TERM
                     ,line.substr(current_column_index,endif_stmt.size())
                     , wasp::STRING, offset );

        // commit/close the current staged conditional to the parse tree
        Interpreter<S>::commit_staged(Interpreter<S>::staged_count()-1);
        // update the current column
        current_column_index += endif_stmt.size();
    }

    if( attribute_indices.empty() == false )
    { // in addition to the attributes, capture the components before, between, and after
        size_t current_attribute_index = 0;
        size_t limit = attribute_indices.size();
        // capture up to the conclusion of the attributes
        capture(line
                ,current_column_index
                ,current_attribute_index
                ,attribute_indices
                ,limit);        
    }
    // if line is plain text, capture
    if( is_import == false
            && is_ifdef == false
            && is_ifndef == false
            && is_if == false
            && is_elseif == false
            && is_else == false
            && is_endif == false
            && attribute_indices.empty() )
    {
        // only capture lines with content
        if( line.empty() == false )
        {
            capture_leaf("txt", wasp::STRING, line, wasp::STRING, m_file_offset );
        }
    }
    // capture potential trailing text
    else
    {
        // current_column index has been updated by capture(), etc.
        size_t offset = m_file_offset + current_column_index;
        size_t remaining_length = line.size() - current_column_index;
        wasp_check( current_column_index+remaining_length <= line.size() );
        if( remaining_length > 0 )
        {            
            capture_attribute_text(
                        line.substr(current_column_index,remaining_length)
                        ,offset);
        }

        // when closing import statement, commit the tree
        if( is_import )
        {
            Interpreter<S>::commit_staged(Interpreter<S>::staged_count()-1);
        }
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

    std::vector<size_t> depths = SubStringIndexer::depths(attribute_indices);
    wasp_check( depths.size() == attribute_indices.size() );

    if( limit == 0 ) limit = attribute_indices.size();

    std::vector<SubStringIndexer::IndexPair_type> open_tree;

    for( size_t i = current_attribute_index; i < limit; ++i )
    {
        const SubStringIndexer::IndexPair_type& attribute_index
                = attribute_indices[i];
        // check for preceding text/name that needs to be put into tree
        if( attribute_index.first > current_column_index )
        {
            size_t length = attribute_index.first - current_column_index;
            size_t file_offset = m_file_offset + current_column_index;
            const std::string & prefixed
                    = data.substr(current_column_index,length);
            capture_attribute_text(prefixed,file_offset);
        }
        Interpreter<S>::push_staged(wasp::IDENTIFIER, "attr",{});
        { // capture declarative delimiter
            size_t file_offset = m_file_offset + attribute_index.first;
            capture_leaf(m_attribute_start_delim,wasp::DECL
                     ,m_attribute_start_delim,wasp::STRING
                     ,file_offset);
        }

        // increment current column to next potential block of text
        current_column_index = attribute_index.first
                +m_attribute_start_delim.size();
        // initial assumed depth to worst scenario, no more attributes
        // in this situation, all open trees must be closed/committed
        int depth_delta = open_tree.size()*-1;
        // acquire the
        if( i+1 < attribute_indices.size() )
        {
            depth_delta = depths[i+1]-depths[i];
        }

        // The next attribute should be a sibling or uncle in the tree.
        // Capture the current attribute's text, terminator,
        // commit open sub tree and update current column index
        // to next potential block of text.
        if( depth_delta <= 0 )
        {
            capture_attribute_delim(data, current_column_index, attribute_index.second);

        } // end of depth == 0
        // The next attribute is an uncle/great/great uncle etc.
        // Capture the appropriate open ancestral subtrees
        if ( depth_delta < 0 )
        {
            while( depth_delta != 0 ){
                const auto & prev = open_tree.back();
                capture_attribute_delim(data,current_column_index, prev.second);
                ++depth_delta;
                open_tree.pop_back();
            }
        }
        // The next attribute is a child.
        // Push onto the open tree stack for future closure.
        else if( depth_delta > 0){
            open_tree.push_back(attribute_index);
        }
    } // end of attribute loop
}
template<class S>
bool HaliteInterpreter<S>::evaluate(std::ostream & out
                                    ,DataAccessor & data
                                    , std::ostream * activity_log)
{
    auto root_view = Interpreter<S>::root();
    size_t current_line = 1, current_column = 1;

    for( size_t i = 0; i < root_view.child_count(); ++i)
    {
        const auto & child_view = root_view.child_at(i);
        auto child_type = child_view.type();
        switch( child_type )
        {
        case  wasp::STRING:

//            if( activity_log ) *activity_log<<Interpreter<S>::stream_name()<<": line "<<current_line<<std::endl;
            // print the text and update the current line and column
            wasp::print_from(out, child_view, current_line, current_column);
        break;
        case wasp::IDENTIFIER:
        {
            std::stringstream substitution;
            if( !print_attribute(data, child_view, substitution
                               , current_line, current_column) )
            {
                return false;
            }
            out<<substitution.str();
        }
        break;
        case wasp::FILE:
            if( !import_file(data, child_view, out, current_line, current_column) ) return false;
        break;
        default:
            wasp_not_implemented("template construct at line "
                                 +std::to_string(current_line));
        break;
        } // end of switch
    }
    return true;
}
template<class S>
bool HaliteInterpreter<S>::print_attribute(DataAccessor & data
                                           ,const TreeNodeView<S>& attr_view
                                           ,std::ostream& out
                                           ,size_t & line
                                           ,size_t & column)
{
    wasp_tagged_line("printing attribute "<<attr_view.data());
    // attributes must have '<' txt? '>'
    // e.g., < txt> or <>
    wasp_require( attr_view.child_count() > 1);
    std::stringstream attr_str;
    size_t start_column = column; // todo ensure column is propogated appropriately
    SubstitutionOptions options;
    // accumulate an attribute string
    for( size_t i = 1, count = attr_view.child_count()-1; i < count; ++i )
    {
        auto child_view = attr_view.child_at(i);
        auto type = child_view.type();
        switch( type )
        {
            // plain text to be printed for variable substitution
            case wasp::STRING:
            wasp::print(attr_str, child_view);
            break;
            // nested attribute, recurse
            case wasp::IDENTIFIER:
            if( !print_attribute(data, child_view, attr_str, line, column) )
            {
                return false;
            }
            // indicates the attribute has options for substitution
            case wasp::FUNCTION:
                attribute_options(options, child_view.data());
            break;
            default:
            wasp_not_implemented("nested attribute printing");
        }
    }

    // TODO - add optimization to check if above loop only encounters STRING
    // and optionally FUNCTION in which indicate a variable can be directly substituted
    // and formatted and no expression evaluation is needed

    // attribute string contains the full attribute name
    ExprInterpreter<> expr(Interpreter<S>::error_stream());
    if( false == expr.parse(attr_str, line, start_column + m_attribute_start_delim.size()) )
    {
        return false;
    }
    wasp_tagged_line("evaluating statement '"<<attr_str.str()<<"'");
    auto result = expr.evaluate(data);
    if( result.is_error() )
    {
        wasp_tagged_line(result.string());
        return false;
    }

    if( options.has_format() )
    {
        if( !result.format(  out, options.format(), Interpreter<S>::error_stream()) )
        {
            return false;
        }
    }
    else {
       if( !result.format( out ) ) return false;
    }
    column = attr_view.child_at(attr_view.child_count()-1).column() + m_attribute_end_delim.size();
    return true;
}

template<class S>
bool HaliteInterpreter<S>::import_file(DataAccessor & data
                                       ,const TreeNodeView<S>& import_view
                                           ,std::ostream& out
                                           ,size_t & line
                                           ,size_t & column)
{

    // attributes must have '#import txt'
    // e.g., #import txt or #import txt<a1>txt<a2>...
    wasp_require( import_view.child_count() > 1);
    std::stringstream import_str;
    // accumulate an attribute string
    for( size_t i = 1, count = import_view.child_count(); i < count; ++i )
    {
        const auto& child_view = import_view.child_at(i);
        auto type = child_view.type();
        switch( type )
        {
            case wasp::STRING:
                wasp::print(import_str, child_view);
            break;
            case wasp::IDENTIFIER:
                print_attribute(data,child_view, import_str, line, column);
            break;
            default:
                wasp_not_implemented("parameterized file import");
        }
    }
    std::string path = import_str.str();
    path = wasp::trim(path," \t");
    wasp_tagged_line("importing '"<<path<<"' relative to '"
                     <<Interpreter<S>::stream_name()<<"'");
    std::ifstream relative_to_working_dir(path.c_str());
    std::string relative_to_current_path = Interpreter<S>::stream_name()+"/"+path;
    std::ifstream relative_to_current(relative_to_current_path.c_str());
    HaliteInterpreter<S> nested_interp(Interpreter<S>::error_stream());
    if( !relative_to_working_dir.good() )
    {
        if( !relative_to_current.good() )
        {
            Interpreter<S>::error_stream()<<"***Error : unable to open '"
                                         <<path<<".'"<<std::endl;
            return false;
        }
        nested_interp.setStreamName(relative_to_current_path,true);
        bool parsed = nested_interp.parse(relative_to_current);
        if( parsed == false )
        {
            return false;
        }
        return nested_interp.evaluate(out,data);
    }

    nested_interp.setStreamName(path,true);
    bool parsed = nested_interp.parse(relative_to_working_dir);
    if( parsed == false )
    {
        return false;
    }
    bool import = nested_interp.evaluate(out,data);
    ++line; // we know imports take 1 line
    out<<std::endl;
    return import;
}
template<class S>
void HaliteInterpreter<S>::capture_attribute_text(const std::string& text
                                                  ,size_t offset)
{
    size_t options_index = text.find(m_attribute_options_delim);
    bool contains_options = options_index != std::string::npos;
    if( !contains_options ) options_index = text.size();

    // capture text
    capture_leaf("txt",wasp::STRING, text.substr(0,options_index)
                 ,wasp::STRING,offset);
    size_t options_text_size = text.size() - options_index;
    // capture attribute options
    if( options_text_size > 0 )
    {
        capture_leaf("opt",wasp::FUNCTION, text.substr(options_index,options_text_size)
                     ,wasp::STRING,offset+options_index);
    }
}


template<class S>
void HaliteInterpreter<S>::capture_attribute_delim(const std::string& data
                                                   , size_t & current_column_index
                                                  ,size_t attribute_end_index)
{
    wasp_require(attribute_end_index >= current_column_index);
    size_t remaining_length
            = attribute_end_index - current_column_index;
    // capture text, if any
    if( remaining_length > 0 ){
        size_t file_offset = m_file_offset + current_column_index;
        capture_attribute_text(
                    data.substr(current_column_index,remaining_length)
                    ,file_offset);
    }
    // capture attribute terminator
    size_t file_offset = m_file_offset + attribute_end_index;
    capture_leaf(m_attribute_end_delim,wasp::TERM
             ,m_attribute_end_delim,wasp::STRING
             ,file_offset);
    // close/commit the subtree
    wasp_check( Interpreter<S>::staged_count() > 1 );
    Interpreter<S>::commit_staged(Interpreter<S>::staged_count()-1);
    // update current column to end of delimiter
    current_column_index = attribute_end_index
            + m_attribute_end_delim.size();
}
template<class S>
void HaliteInterpreter<S>::attribute_options(SubstitutionOptions & options
        ,const std::string& data)const
{
    static std::string fmt = "fmt=";
    size_t format_index = data.find(fmt);
    if( format_index != std::string::npos )
    {
        options.format() = data.substr(format_index+fmt.size());
        wasp_tagged_line("Format of '"<<options.format()<<"' captured");
    }
}
#endif
