#ifndef WASP_VIINTERPRETER_I_H
#define WASP_VIINTERPRETER_I_H

template<class S>
VIInterpreter<S>::VIInterpreter()
    : Interpreter<S>()
    , traceLexing(false)
    , traceParsing(false)
    , singleParse(false)
    , m_parent(nullptr)
    , m_current(nullptr)
    , mHasFile(false)
{
    definition();  // create empty definition needed by interpreter
}
template<class S>
VIInterpreter<S>::VIInterpreter(std::ostream& err)
    : Interpreter<S>(err)
    , traceLexing(false)
    , traceParsing(false)
    , singleParse(false)
    , m_parent(nullptr)
    , m_current(nullptr)
    , mHasFile(false)
{
    definition();  // create empty definition needed by interpreter
}
template<class S>
VIInterpreter<S>::~VIInterpreter()
{
    m_current = nullptr;
    // TODO delete node interpreters
}
template<class S>
bool VIInterpreter<S>::parse(std::istream& in,
                             size_t        startLine,
                             size_t        startColumn)
{
    return parseStream(
        in, hasFile() ? Interpreter<S>::stream_name() : "stream input",
        startLine, startColumn);
}
template<class S>
bool VIInterpreter<S>::parseStream(std::istream&      in,
                                   const std::string& sname,
                                   size_t             start_line,
                                   size_t             start_column)
{
    return Interpreter<S>::template parse_impl<VIIParser>(in, sname, start_line,
                                                          start_column);
}
template<class S>
bool VIInterpreter<S>::parseFile(const std::string& filename, size_t line)
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
    mHasFile = true;
    return parseStream(in, filename, line);
}
template<class S>
bool VIInterpreter<S>::parseString(const std::string& input,
                                   const std::string& sname,
                                   size_t             startLine,
                                   size_t             startColumn)
{
    std::istringstream iss(input);
    return parseStream(iss, sname, startLine, startColumn);
}

template<class S>
const AbstractDefinition* VIInterpreter<S>::definition() const
{
    wasp_require(m_current != nullptr);
    return m_current;
}
template<class S>
AbstractDefinition* VIInterpreter<S>::definition()
{
    if (m_current == nullptr)
    {
        m_definition = std::make_shared<Definition>();
        m_current    = &(*m_definition);
    }

    return m_current;
}
template<class S>
size_t VIInterpreter<S>::push_staged(size_t                     node_type,
                                     const std::string&         node_name,
                                     const std::vector<size_t>& child_indices)
{
    auto stage_count =
        Interpreter<S>::push_staged(node_type, node_name, child_indices);
    wasp_check(m_current->has(node_name));
    m_current = m_current->get(node_name);  // push new definition
    return stage_count;
}
template<class S>
size_t VIInterpreter<S>::commit_staged(size_t stage_index)
{
    auto node_index = Interpreter<S>::commit_staged(stage_index);
    wasp_check(m_current);
    if ( m_current->parent() ) m_current = m_current->parent();  // pops current definition
    return node_index;
}
template<class S>
bool VIInterpreter<S>::load_document(std::ostream& document_errors)
{
    bool passed = true;

    for ( auto node_path: Interpreter<S>::m_node_interp_path )
    {
        auto node_index = node_path.first;

        std::stringstream err_msgs;

        auto document_relative_path  = wasp::dir_name(Interpreter<S>::stream_name())
                                      +"/"+node_path.second;
        if ( wasp::file_exists(document_relative_path) )
        {
            auto * interp = new VIInterpreter<S>(err_msgs);
            interp->m_parent = this;
            interp->set_definition_store(this->definition_store());

            auto parent_node_index = Interpreter<S>::parent_node_index(node_index);
            interp->m_current = get_definition(parent_node_index, this);
            wasp_check (interp->m_current);
            if ( !interp->parseFile(document_relative_path) )
            {
                Interpreter<S>::error_stream()<<err_msgs.str()<<std::endl;
                passed &= false;
            }
            else
            {
                wasp_check(Interpreter<S>::m_node_interp.find(node_index)
                           == Interpreter<S>::m_node_interp.end());
                wasp_check(Interpreter<S>::m_interp_node.find(interp)
                           == Interpreter<S>::m_interp_node.end());
                Interpreter<S>::m_node_interp[node_index] = interp;
                Interpreter<S>::m_interp_node[interp] = node_index;
            }
        }
        else
        {
            Interpreter<S>::error_stream()<<Interpreter<S>::stream_name()
                                          <<" line:"
                                          <<Interpreter<S>::line(node_index)
                                          <<" column:"
                                          <<Interpreter<S>::column(node_index)
                                          <<" : could not find '"
                                          <<document_relative_path<<"'"
                                          <<std::endl;
            passed &= false;
        }
    }
    return passed;
}
#endif
