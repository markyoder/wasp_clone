#ifndef WASP_TREENODEPOOL_I_H
#define WASP_TREENODEPOOL_I_H

template<typename NTS, typename NIS
         ,typename TTS,typename TITS, typename FOTS>
TreeNodePool<NTS,NIS,TTS,TITS,FOTS>::TreeNodePool()
{
}
// copy constructor
template<typename NTS, typename NIS
         ,typename TTS, typename TITS, typename FOTS>
TreeNodePool<NTS,NIS,TTS,TITS,FOTS>::TreeNodePool(
        const TreeNodePool<NTS,NIS,TTS,TITS,FOTS>& orig)
    : m_token_data(orig.m_token_data)
    , m_node_names(orig.m_node_names)
    , m_node_basic_data(orig.m_node_basic_data)
    , m_node_parent_data(orig.m_node_parent_data)
    , m_node_child_indices(orig.m_node_child_indices)
    , m_basic_parent_data_lookup(orig.m_basic_parent_data_lookup)
    , m_leaf_token_lookup(orig.m_leaf_token_lookup)
{
}
// default destructor
template<typename NTS, typename NIS
         ,typename TTS, typename TITS,typename FOTS>
TreeNodePool<NTS,NIS,TTS,TITS,FOTS>::~TreeNodePool()
{
}
// Create a parent node
template<typename NTS, typename NIS
         ,typename TTS, typename TITS,typename FOTS>
void TreeNodePool<NTS,NIS,TTS,TITS,FOTS>::push_parent(
        NTS type, const char * name
        ,const std::vector<NIS> & child_indices)
{
    // Capture node's basic information
    m_node_names.push(name);
    NIS basic_data_index = static_cast<NIS>(m_node_basic_data.size());
    // capture type - parent index is unknown
    m_node_basic_data.push_back(BasicNodeData(type,-1));

    // capture node's parental info
    NIS parent_data_index = static_cast<NIS>(m_node_parent_data.size());
    NIS first_child_index = static_cast<NIS>(m_node_child_indices.size());
    NIS child_count = static_cast<NIS>(child_indices.size());
    m_node_parent_data.push_back(ParentNodeData(first_child_index,child_count));

    // capture index association between basic and parent data
    // basic data is type, and parent index
    // parent data is only present when the node has children
    m_basic_parent_data_lookup[basic_data_index] = parent_data_index;

    // update the children's parent index
    // TODO check children range for valid indices
    // TODO check children for lack of parent
    std::size_t last_child_index = first_child_index+child_count;
    for( std::size_t c = 0, i = first_child_index; i < last_child_index; ++i, ++c)
    {
        // assign parent
        std::size_t child_index = child_indices[c];
        m_node_basic_data[child_index].m_parent_node_index = basic_data_index;
        // assign lookup index mapping parent to list
        // of arbitrary indices into basic node data
        // describing the children of this parent node
        m_node_child_indices.push_back(child_index);
    }
}

// Create a leaf node
template<typename NTS, typename NIS
         ,typename TTS, typename TITS,typename FOTS>
void TreeNodePool<NTS,NIS,TTS,TITS,FOTS>::push_leaf(
        NTS node_type
       , const char * node_name
       , TTS token_type
       , FOTS token_offset
       , const char * token_data)
{
    // capture the token data index
    TITS token_data_index = static_cast<TITS>(m_token_data.size());
    m_token_data.push(token_data,token_type,token_offset);

    // Capture node's basic information
    m_node_names.push(node_name);
    NIS basic_data_index = static_cast<NIS>(m_node_basic_data.size());

    // capture type - parent index is unknown
    m_node_basic_data.push_back(BasicNodeData(node_type,-1));

    // make the leaf node to token index association
    m_leaf_token_lookup[basic_data_index] = token_data_index;
}
// Create a leaf node for a given token
template<typename NTS, typename NIS
         ,typename TTS, typename TITS,typename FOTS>
void TreeNodePool<NTS,NIS,TTS,TITS,FOTS>::push_leaf(
        NTS node_type
       , const char * node_name
       , TITS token_data_index)
{
    // TODO - check the token_data_index is legit

    // Capture node's basic information
    m_node_names.push(node_name);
    NIS basic_data_index = static_cast<NIS>(m_node_basic_data.size());

    // capture type - parent index is unknown
    m_node_basic_data.push_back(BasicNodeData(node_type,-1));

    // make the leaf node to token index association
    m_leaf_token_lookup[basic_data_index] = token_data_index;
}
// Acquire the given token's parent meta data (child indices, count) index
template<typename NTS, typename NIS
         ,typename TTS, typename TITS,typename FOTS>
std::size_t TreeNodePool<NTS,NIS,TTS,TITS,FOTS>::parent_data_index(
        NIS node_index) const
{    
    auto itr = m_basic_parent_data_lookup.find(node_index);
    if( itr == m_basic_parent_data_lookup.end() )
    {
        return size(); // when root, return size of nodes
    }

    // TODO - could check parent children for consistency

    // return the index of the
    return itr->second;
}

template<typename NTS, typename NIS
         ,typename TTS, typename TITS,typename FOTS>
std::size_t TreeNodePool<NTS,NIS,TTS,TITS,FOTS>::parent_node_index(
        NIS node_index) const
{
    // TODO check range    
    auto parent_index = m_node_basic_data[node_index].m_parent_node_index;
    if( parent_index == -1 )
    {
        return size();
    }
    return parent_index;
}

template<typename NTS, typename NIS
         ,typename TTS, typename TITS,typename FOTS>
std::size_t TreeNodePool<NTS,NIS,TTS,TITS,FOTS>::child_count(
        NIS node_index) const
{
    // acquire the index into the parent meta data
    std::size_t parent_index = parent_data_index(node_index);
    if( parent_index == size() ) return 0;
    return m_node_parent_data[parent_index].m_child_count;
}

template<typename NTS, typename NIS
         ,typename TTS, typename TITS,typename FOTS>
std::size_t TreeNodePool<NTS,NIS,TTS,TITS,FOTS>::child_at(
        NIS node_index, NIS child_relative_index) const
{
    // TODO conduct range check on relative index to child count

    // acquire the index into the parent meta data
    std::size_t parent_index = parent_data_index(node_index);
    auto child_indices_index
            = m_node_parent_data[parent_index].m_first_child_index
            + child_relative_index;
    auto child_basic_data_index = m_node_child_indices[child_indices_index];
    return child_basic_data_index;
}
template<typename NTS, typename NIS
         ,typename TTS, typename TITS,typename FOTS>
void TreeNodePool<NTS,NIS,TTS,TITS,FOTS>::node_path(
                    NIS node_index
                    ,std::ostream & out)const
{
    // TODO range check node index
    std::vector<NIS> lineage(1,node_index);
    // while there are parents available
    // accrue the lineage
    while( has_parent(node_index) )
    {
        node_index = parent_node_index(node_index);
        lineage.push_back(node_index);
    }
    // describe the root
    if( lineage.size() == 1)
    {
        out<<"/";
        lineage.pop_back();
    }
    // remove the root 'document'
    else if( lineage.size() > 1 ) lineage.pop_back();
    // with the lineage accrued
    // walk in reverse order parent->child
    while( !lineage.empty() )
    {
        node_index = lineage.back();
        out<< "/" << name(node_index);
        lineage.pop_back();
    }
}
template<typename NTS, typename NIS
         ,typename TTS, typename TITS,typename FOTS>
void TreeNodePool<NTS,NIS,TTS,TITS,FOTS>::node_paths(
                    NIS node_index
                    ,std::ostream & out)const
{
    // TODO conduct node index range check
    std::size_t node_child_count = child_count(node_index);
    node_path(node_index,out);
    if( node_child_count == 0 ){
        out<<" ("<<data(node_index)<<")"<<std::endl;
    }
    else{
        out<<std::endl;
    }

    for( std::size_t i = 0; i < node_child_count; ++i){
        node_paths( child_at( node_index, i ), out );
    }
}


// determine if the given node has a parent
template<typename NTS, typename NIS
         ,typename TTS, typename TITS,typename FOTS>
bool TreeNodePool<NTS,NIS,TTS,TITS,FOTS>::has_parent(
                    NIS node_index )const
{
    if( node_index >= size() ) return false;

    std::size_t nodes_parent_index
            = parent_node_index(node_index);
    return nodes_parent_index != size();
}

// Obtain a nodes starting line
template<typename NTS, typename NIS
         ,typename TTS, typename TITS,typename FOTS>
std::size_t TreeNodePool<NTS,NIS,TTS,TITS,FOTS>::line(
                    NIS node_index )const
{
    auto leaf_node_index = leaf_index(node_index);
    auto leaf_itr = m_leaf_token_lookup.find(leaf_node_index);
    // obtain the token's column
    if( leaf_itr != m_leaf_token_lookup.end() )
    {
        auto token_index = leaf_itr->second;
        return m_token_data.line(token_index);
    }
    // neither a leaf node or a parent node
    // TODO - catch error condition
    return -1;
}
// Obtain a nodes starting column
template<typename NTS, typename NIS
         ,typename TTS, typename TITS,typename FOTS>
std::size_t TreeNodePool<NTS,NIS,TTS,TITS,FOTS>::column(
                    NIS node_index )const
{
    auto leaf_node_index = leaf_index(node_index);
    auto leaf_itr = m_leaf_token_lookup.find(leaf_node_index);
    // obtain the token's column
    if( leaf_itr != m_leaf_token_lookup.end() )
    {
        auto token_index = leaf_itr->second;
        return m_token_data.column(token_index);
    }
    // neither a leaf node or a parent node
    // TODO - catch error condition
    return -1;
}
// Obtain a node's first leaf node index
template<typename NTS, typename NIS
         ,typename TTS, typename TITS,typename FOTS>
std::size_t TreeNodePool<NTS,NIS,TTS,TITS,FOTS>::leaf_index(
                    NIS node_index )const
{
    auto leaf_itr = m_leaf_token_lookup.find(node_index);
    // obtain the token's column
    if( leaf_itr != m_leaf_token_lookup.end() )
    {
        return node_index;
    }
    // node must be a parent, need first child
    auto parent_itr = m_basic_parent_data_lookup.find(node_index);
    if( parent_itr != m_basic_parent_data_lookup.end() )
    {
        auto parent_data_index = parent_itr->second;
        auto first_child_lookup_index
                = m_node_parent_data[parent_data_index].m_first_child_index;
        auto first_child_basic_data_index
                = m_node_child_indices[first_child_lookup_index];
        return leaf_index(first_child_basic_data_index);
    }
    // neither a leaf node or a parent node
    // TODO - catch error condition
    return -1;
}
// Obtain a leaf node's token type
template<typename NTS, typename NIS
         ,typename TTS, typename TITS,typename FOTS>
TTS TreeNodePool<NTS,NIS,TTS,TITS,FOTS>::node_token_type(
                    NIS node_index )const
{
    auto leaf_itr = m_leaf_token_lookup.find(node_index);
    // obtain the token's column
    if( leaf_itr != m_leaf_token_lookup.end() )
    {
        return m_token_data.type(leaf_itr->second);
    }
    return wasp::UNKNOWN;
}
// Obtain the node's data (string contents)
template<typename NTS, typename NIS
         ,typename TTS, typename TITS,typename FOTS>
std::string TreeNodePool<NTS,NIS,TTS,TITS,FOTS>::data(NIS node_index)const
{
    std::stringstream data_stream;
    data(node_index, data_stream);
    return data_stream.str();
}
// Obtain the node's data (string contents)
template<typename NTS, typename NIS
         ,typename TTS, typename TITS,typename FOTS>
void TreeNodePool<NTS,NIS,TTS,TITS,FOTS>::data(NIS node_index
                                               ,std::ostream& out)const
{
    // two scenarios - 1 leaf node, 2 parent node
    // 1. obtain the leaf node's token data
    auto leaf_itr = m_leaf_token_lookup.find(node_index);
    // obtain the token's column
    if( leaf_itr != m_leaf_token_lookup.end() )
    {
        out<<m_token_data.str(leaf_itr->second);
    }
    // 2. accumulate the parent
    else{

    }
}
#endif
