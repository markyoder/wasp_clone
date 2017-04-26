
template<class TNS>
Interpreter<TNS>::Interpreter(std::ostream & err)
    : AbstractInterpreter()
    , m_start_column(1)
    , m_start_line(1)
    , m_stream_name("stream")
    , m_error_stream(err)
    , m_root_index(-1)
{
    // All documents have a root.
    // However, if no elements are parsed
    // this staged root will not be committed.
    push_staged(wasp::DOCUMENT_ROOT, "document", {});
}
template<class TNS>
Interpreter<TNS>::~Interpreter()
{
}

template<class TNS>
TreeNodeView< TNS >
Interpreter<TNS>::root()const
{
    // have any nodes?
    if( m_tree_nodes.size() == 0 )
    {
        return TreeNodeView<TNS>(m_tree_nodes.size(),this->m_tree_nodes);
    }
    return TreeNodeView<TNS>(m_root_index,this->m_tree_nodes);
}
template<class TNS>
TreeNodeView< TNS >
Interpreter<TNS>::node_at(node_index_size index )const
{
    // have any nodes?
    if( m_tree_nodes.size() == 0 )
    {
        return TreeNodeView<TNS>(m_tree_nodes.size(),this->m_tree_nodes);
    }
    return TreeNodeView<TNS>(index,this->m_tree_nodes);
}
template<class TNS>
size_t Interpreter<TNS>::child_count( size_t node_index )const
{
    return this->m_tree_nodes.child_count(node_index);
}
template<class TNS>
size_t Interpreter<TNS>::column( size_t node_index )const
{
    return this->m_tree_nodes.column(node_index);
}
template<class TNS>
size_t Interpreter<TNS>::line( size_t node_index )const
{
    return this->m_tree_nodes.line(node_index);
}
template<class TNS>
size_t Interpreter<TNS>::parent_node_index( size_t node_index )const
{
    return this->m_tree_nodes.parent_node_index(node_index);
}
template<class TNS>
size_t Interpreter<TNS>::child_index_at( size_t node_index
                                         ,size_t child_index)const
{
    return this->m_tree_nodes.child_at(node_index, child_index);
}
template<class TNS>
size_t Interpreter<TNS>::push_leaf(size_t node_type
                                    , const char *node_name
                                    , size_t token_index)
{
    size_t node_index = node_count();
    m_tree_nodes.push_leaf(node_type,node_name
                     ,token_index);
    return node_index;
}
template<class TNS>
size_t Interpreter<TNS>::push_parent(size_t node_type
                                    , const char *node_name
                                    , const std::vector<size_t>&child_indices)
{
    size_t node_index = node_count();
    m_tree_nodes.push_parent(node_type,node_name
                     ,child_indices);
    return node_index;
}
template<class TNS>
size_t
Interpreter<TNS>::type(size_t index )const
{
    // have any nodes?
    if( m_tree_nodes.size() == 0 )
    {
        return wasp::UNKNOWN;
    }
    return this->m_tree_nodes.type( index );
}
template<class TNS>
typename Interpreter<TNS>::token_type_size
Interpreter<TNS>::node_token_type(size_t index )const
{
    // have any nodes?
    if( m_tree_nodes.size() == 0 )
    {
        return wasp::UNKNOWN;
    }
    return this->m_tree_nodes.node_token_type( index );
}
template<class TNS>
const char * Interpreter<TNS>::name(size_t index )const
{
    // have any nodes?
    if( m_tree_nodes.size() == 0 )
    {
        return nullptr;
    }
    return this->m_tree_nodes.name( index );
}
template<class TNS>
bool Interpreter<TNS>::set_name(size_t node_index
                                    , const char *node_name)
{
    return this->m_tree_nodes.set_name(node_index, node_name);
}
template<class TNS>
void Interpreter<TNS>::set_type(size_t node_index
                                    , size_t node_type)
{
    return this->m_tree_nodes.set_type(node_index, node_type);
}
template<class TNS>
std::string Interpreter<TNS>::data(size_t index )const
{
    // have any nodes?
    if( m_tree_nodes.size() == 0 )
    {
        return "";
    }
    return this->m_tree_nodes.data( index );
}
template<class TNS>
const char * Interpreter<TNS>::token_data(size_t index )const
{
    // have any tokens?
    const auto& token_pool = m_tree_nodes.token_data();
    if( token_pool.size() == 0 )
    {
        return nullptr;
    }
    return token_pool.str( index );
}

template<class TNS>
template<class PARSER_IMPL>
bool Interpreter<TNS>::parse_impl(std::istream &in
        , const std::string& stream_name
        , size_t start_line
        , size_t start_column)
{
//    lexer.set_debug(m_trace_lexing);
//    lexer.set_debug(true);

    m_stream_name = stream_name;
    m_start_line = start_line;
    m_start_column = start_column;
    m_tree_nodes.set_start_line(start_line);
    m_tree_nodes.set_start_column(start_column);
    wasp_tagged_line("parsing '"<<stream_name<<"' starting from line "
                     <<start_line<<" and column "<<start_column);
    PARSER_IMPL parser(*this, in, nullptr);
//    parser.set_debug_level(true);


    bool parsed = parser.parse() == 0;

    commit_stages();

    return parsed;
}

template<class TNS>
const size_t& Interpreter<TNS>::staged_type(size_t staged_index)const
{
    wasp_require( staged_index < m_staged.size() );
    return m_staged[staged_index].m_type;
}
template<class TNS>
size_t& Interpreter<TNS>::staged_type(size_t staged_index)
{
    wasp_require( staged_index < m_staged.size() );
    return m_staged[staged_index].m_type;
}
template<class TNS>
size_t Interpreter<TNS>::push_staged(size_t node_type
                               , const std::string& node_name
                               , const std::vector<size_t>&child_indices)
{
    m_staged.push_back(Stage());
    auto & back = m_staged.back();
    back.m_type = node_type;
    back.m_name = node_name;
    back.m_child_indices = child_indices;
    return m_staged.size()-1;
}

template<class TNS>
size_t Interpreter<TNS>::push_staged_child(size_t child_index)
{
    wasp_require( m_staged.empty() == false );
    auto & back = m_staged.back();
    back.m_child_indices.push_back(child_index);
    return back.m_child_indices.size();
}
template<class TNS>
size_t Interpreter<TNS>::commit_staged(size_t stage_index)
{
    wasp_require( m_staged.empty() == false );
    wasp_require( stage_index < m_staged.size() );

    Stage& stage = m_staged[stage_index];
    size_t node_index = push_parent( stage.m_type
                                   ,stage.m_name.c_str()
                                   ,stage.m_child_indices);

    wasp_ensure( node_index >= 0 && node_index < m_tree_nodes.size() );
    m_staged.pop_back();
    // make sure to add newly realized tree node
    // to existing staged parent
    if( !m_staged.empty() ) push_staged_child(node_index);
    return node_index;
}
