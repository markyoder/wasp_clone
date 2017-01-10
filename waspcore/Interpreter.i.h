
template<class TNS>
Interpreter<TNS>::Interpreter(std::ostream & err)
    : m_start_column(1)
    , m_start_line(1)
    , m_stream_name("stream")
    , m_error_stream(err)
    , m_root_index(-1) // not set
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
        return TreeNodeView<decltype(m_tree_nodes)>(m_tree_nodes.size(),this->m_tree_nodes);
    }
    return TreeNodeView<decltype(m_tree_nodes)>(m_root_index,this->m_tree_nodes);
}
template<class TNS>
TreeNodeView< TNS >
Interpreter<TNS>::node_at(node_index_size index )const
{
    // have any nodes?
    if( m_tree_nodes.size() == 0 )
    {
        return TreeNodeView<decltype(m_tree_nodes)>(m_tree_nodes.size(),this->m_tree_nodes);
    }
    return TreeNodeView<decltype(m_tree_nodes)>(index,this->m_tree_nodes);
}
template<class TNS>
std::size_t Interpreter<TNS>::push_leaf(node_type_size node_type
                                    , const char *node_name
                                    , token_index_type_size token_index)
{
    std::size_t node_index = node_count();
    m_tree_nodes.push_leaf(node_type,node_name
                     ,token_index);
    return node_index;
}
template<class TNS>
std::size_t Interpreter<TNS>::push_parent(node_type_size node_type
                                    , const char *node_name
                                    , const std::vector<node_index_size>&child_indices)
{
    std::size_t node_index = node_count();
    m_tree_nodes.push_parent(node_type,node_name
                     ,child_indices);
    return node_index;
}
template<class TNS>
typename Interpreter<TNS>::node_type_size
Interpreter<TNS>::type(node_index_size index )const
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
Interpreter<TNS>::node_token_type(node_index_size index )const
{
    // have any nodes?
    if( m_tree_nodes.size() == 0 )
    {
        return wasp::UNKNOWN;
    }
    return this->m_tree_nodes.node_token_type( index );
}
template<class TNS>
const char * Interpreter<TNS>::name(node_index_size index )const
{
    // have any nodes?
    if( m_tree_nodes.size() == 0 )
    {
        return nullptr;
    }
    return this->m_tree_nodes.name( index );
}
template<class TNS>
std::string Interpreter<TNS>::data(node_index_size index )const
{
    // have any nodes?
    if( m_tree_nodes.size() == 0 )
    {
        return "";
    }
    return this->m_tree_nodes.data( index );
}
template<class TNS>
const char * Interpreter<TNS>::token_data(token_index_type_size index )const
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
template<class LEXER_IMPL
         ,class PARSER_IMPL
         ,class INTERPRETER_IMPL>
bool Interpreter<TNS>::parse_impl( LEXER_IMPL *& m_lexer
        , std::istream &in
        , const std::string& stream_name
        , std::size_t start_line
        , std::size_t start_column)
{
    m_stream_name = stream_name;
    INTERPRETER_IMPL & interp_impl = dynamic_cast<INTERPRETER_IMPL&>(*this);
    LEXER_IMPL lexer(interp_impl,&in);
//    lexer.set_debug(m_trace_lexing);

//    lexer.set_debug(true);
    m_lexer = &lexer;
    m_start_line = start_line;
    m_start_column = start_column;
    PARSER_IMPL parser(interp_impl);
//    parser.set_debug_level(true);


    bool parsed = parser.parse() == 0;

    if( !m_root_child_indices.empty() )
    {
        m_root_index = push_parent(wasp::DOCUMENT_ROOT
                                   ,"document"
                                   ,m_root_child_indices);
        m_root_child_indices.clear();
    }
    m_lexer = nullptr;
    return parsed;
}
