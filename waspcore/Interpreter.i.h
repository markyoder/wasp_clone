
template<class TNS>
Interpreter<TNS>::Interpreter(std::ostream & err)
    : AbstractInterpreter()
    , m_start_column(1)
    , m_start_line(1)
    , m_stream_name("stream")
    , m_error_stream(err)
    , m_root_index(-1) // not set
    , m_root_type(wasp::DOCUMENT_ROOT)
{
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
    PARSER_IMPL parser(*this, in, nullptr);
//    parser.set_debug_level(true);


    bool parsed = parser.parse() == 0;

    if( !m_root_child_indices.empty() )
    {
        m_root_index = push_parent(m_root_type
                                   ,"document"
                                   ,m_root_child_indices);
        m_root_child_indices.clear();
    }
    return parsed;
}
