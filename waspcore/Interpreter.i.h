
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
