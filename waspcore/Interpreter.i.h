
template<typename node_type_size
         ,typename node_index_size
         ,typename token_type_size
         ,typename token_index_type_size
         ,typename file_offset_type_size>
Interpreter<node_type_size,node_index_size
        ,token_type_size,token_index_type_size
        ,file_offset_type_size>::Interpreter(std::ostream & err)
    : m_start_column(1)
    , m_start_line(1)
    , m_stream_name("stream")
    , m_error_stream(err)
    , m_root_index(-1) // not set
{
}
template<typename node_type_size
         ,typename node_index_size
         ,typename token_type_size
         ,typename token_index_type_size
         ,typename file_offset_type_size>
Interpreter<node_type_size,node_index_size
        ,token_type_size,token_index_type_size
        ,file_offset_type_size>::~Interpreter()
{
}
template<typename node_type_size
         ,typename node_index_size
         ,typename token_type_size
         ,typename token_index_type_size
         ,typename file_offset_type_size>
void Interpreter<node_type_size,node_index_size
        ,token_type_size,token_index_type_size
        ,file_offset_type_size>::error(const class location& l,
                  const std::string& m)
{
    m_error_stream << l << ": " << m << std::endl;
}
template<typename node_type_size
         ,typename node_index_size
         ,typename token_type_size
         ,typename token_index_type_size
         ,typename file_offset_type_size>
TreeNodeView Interpreter<node_type_size,node_index_size
        ,token_type_size,token_index_type_size
        ,file_offset_type_size>::root()const
{
    // have any nodes?
    if( m_tree_nodes.size() == 0 )
    {
        return TreeNodeView(m_tree_nodes.size(),this->m_tree_nodes);
    }
    return TreeNodeView(m_root_index,this->m_tree_nodes);
}
template<typename node_type_size
         ,typename node_index_size
         ,typename token_type_size
         ,typename token_index_type_size
         ,typename file_offset_type_size>
TreeNodeView Interpreter<node_type_size,node_index_size
        ,token_type_size,token_index_type_size
        ,file_offset_type_size>::node_at(node_index_size index )const
{
    // have any nodes?
    if( m_tree_nodes.size() == 0 )
    {
        return TreeNodeView(m_tree_nodes.size(),this->m_tree_nodes);
    }
    return TreeNodeView(index,this->m_tree_nodes);
}
template<typename node_type_size
         ,typename node_index_size
         ,typename token_type_size
         ,typename token_index_type_size
         ,typename file_offset_type_size>
size_t Interpreter<node_type_size,node_index_size
        ,token_type_size,token_index_type_size
        ,file_offset_type_size>::push_leaf(node_type_size node_type
                                    , const char *node_name
                                    , token_index_type_size token_index)
{
    size_t node_index = node_count();
    m_tree_nodes.push_leaf(node_type,node_name
                     ,token_index);
    return node_index;
}
template<typename node_type_size
         ,typename node_index_size
         ,typename token_type_size
         ,typename token_index_type_size
         ,typename file_offset_type_size>
size_t Interpreter<node_type_size,node_index_size
        ,token_type_size,token_index_type_size
        ,file_offset_type_size>::push_parent(node_type_size node_type
                                    , const char *node_name
                                    , const std::vector<node_index_size>&child_indices)
{
    size_t node_index = node_count();
    m_tree_nodes.push_parent(node_type,node_name
                     ,child_indices);
    return node_index;
}
template<typename node_type_size
         ,typename node_index_size
         ,typename token_type_size
         ,typename token_index_type_size
         ,typename file_offset_type_size>
node_type_size Interpreter<node_type_size,node_index_size
        ,token_type_size,token_index_type_size
        ,file_offset_type_size>::type(node_index_size index )const
{
    // have any nodes?
    if( m_tree_nodes.size() == 0 )
    {
        return wasp::UNKNOWN;
    }
    return this->m_tree_nodes.type( index );
}
template<typename node_type_size
         ,typename node_index_size
         ,typename token_type_size
         ,typename token_index_type_size
         ,typename file_offset_type_size>
token_type_size Interpreter<node_type_size,node_index_size
        ,token_type_size,token_index_type_size
        ,file_offset_type_size>::node_token_type(node_index_size index )const
{
    // have any nodes?
    if( m_tree_nodes.size() == 0 )
    {
        return wasp::UNKNOWN;
    }
    return this->m_tree_nodes.node_token_type( index );
}
template<typename node_type_size
         ,typename node_index_size
         ,typename token_type_size
         ,typename token_index_type_size
         ,typename file_offset_type_size>
const char * Interpreter<node_type_size,node_index_size
        ,token_type_size,token_index_type_size
        ,file_offset_type_size>::name(node_index_size index )const
{
    // have any nodes?
    if( m_tree_nodes.size() == 0 )
    {
        return nullptr;
    }
    return this->m_tree_nodes.name( index );
}
template<typename node_type_size
         ,typename node_index_size
         ,typename token_type_size
         ,typename token_index_type_size
         ,typename file_offset_type_size>
std::string Interpreter<node_type_size,node_index_size
        ,token_type_size,token_index_type_size
        ,file_offset_type_size>::data(node_index_size index )const
{
    // have any nodes?
    if( m_tree_nodes.size() == 0 )
    {
        return "";
    }
    return this->m_tree_nodes.data( index );
}
template<typename node_type_size
         ,typename node_index_size
         ,typename token_type_size
         ,typename token_index_type_size
         ,typename file_offset_type_size>
const char * Interpreter<node_type_size,node_index_size
        ,token_type_size,token_index_type_size
        ,file_offset_type_size>::token_data(token_index_type_size index )const
{
    // have any tokens?
    const auto& token_pool = m_tree_nodes.token_data();
    if( token_pool.size() == 0 )
    {
        return nullptr;
    }
    return token_pool.str( index );
}

template<typename node_type_size
          ,typename node_index_size
          ,typename token_type_size
          ,typename token_index_type_size
          ,typename file_offset_type_size>
template<class LEXER_IMPL
         ,class PARSER_IMPL
         ,class INTERPRETER_IMPL>
bool Interpreter<node_type_size,node_index_size
,token_type_size,token_index_type_size
,file_offset_type_size>::parse_impl( LEXER_IMPL *& m_lexer
        , std::istream &in
        , const std::string& stream_name
        , size_t start_line
        , size_t start_column)
{
    m_stream_name = stream_name;
    LEXER_IMPL lexer(m_tree_nodes.token_data(),&in);
//    lexer.set_debug(m_trace_lexing);

//    lexer.set_debug(true);
    m_lexer = &lexer;
    m_start_line = start_line;
    m_start_column = start_column;
    PARSER_IMPL parser(dynamic_cast<INTERPRETER_IMPL&>(*this));
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
