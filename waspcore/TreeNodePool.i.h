#ifndef WASP_TREENODEPOOL_I_H
#define WASP_TREENODEPOOL_I_H

template<typename NTS, typename NIS
         ,typename TP>
TreeNodePool<NTS,NIS,TP>::TreeNodePool()
{
}
// copy constructor
template<typename NTS, typename NIS
         ,typename TP>
TreeNodePool<NTS,NIS,TP>::TreeNodePool(
        const TreeNodePool<NTS,NIS,TP>& orig)
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
         ,class TP>
TreeNodePool<NTS,NIS,TP>::~TreeNodePool()
{
}
// Create a parent node
template<typename NTS, typename NIS
         ,class TP>
void TreeNodePool<NTS,NIS,TP>::push_parent(
        NTS type, const char * name
        ,const std::vector<size_t> & child_indices)
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
template<typename NTS, typename NIS
         ,class TP>
void TreeNodePool<NTS,NIS,TP>::set_type(NIS node_index,
        NTS type)
{
    m_node_basic_data[node_index].m_node_type = type;
}
// Create a leaf node
template<typename NTS, typename NIS
         ,class TP>
void TreeNodePool<NTS,NIS,TP>::push_leaf(
        NTS node_type
       , const char * node_name
       , typename TP::token_type_size token_type
       , typename TP::file_offset_type_size token_offset
       , const char * token_data)
{
    // capture the token data index
    typename TP::token_index_type_size token_data_index = static_cast<typename TP::token_index_type_size>(m_token_data.size());
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
         ,class TP>
void TreeNodePool<NTS,NIS,TP>::push_leaf(
        NTS node_type
       , const char * node_name
       , typename TP::token_index_type_size token_data_index)
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
         ,class TP>
std::size_t TreeNodePool<NTS,NIS,TP>::parent_data_index(
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
         ,class TP>
std::size_t TreeNodePool<NTS,NIS,TP>::parent_node_index(
        NIS node_index) const
{
    // TODO check range    
    auto parent_index = m_node_basic_data[node_index].m_parent_node_index;
    if( parent_index == NIS(-1) )
    {
        return size();
    }
    return parent_index;
}
template<typename NTS, typename NIS
         ,class TP>
bool TreeNodePool<NTS,NIS,TP>::set_name(
        NIS node_index, const char * name)
{
    if( m_node_basic_data.empty() ) return false;
    if( node_index < m_node_basic_data.size()-1
            || node_index > m_node_basic_data.size()-1) return false;
    return m_node_names.set(node_index, name);
}
template<typename NTS, typename NIS
         ,class TP>
std::size_t TreeNodePool<NTS,NIS,TP>::child_count(
        NIS node_index) const
{
    // acquire the index into the parent meta data
    std::size_t parent_index = parent_data_index(node_index);
    if( parent_index == size() ) return 0;
    return m_node_parent_data[parent_index].m_child_count;
}
template<class TreeNodePool_T> // template type
std::size_t // return type
TreeNodeView<TreeNodePool_T>::child_count_by_name(const std::string & name
                                                       , std::size_t limit)const
{
    std::size_t matching_named_child_count = 0;

    for( std::size_t i = 0, count = child_count(); i < count; ++i )
    {
        auto child = child_at(i);
        std::string child_name = child.name();
        if( child_name == name )
        {
            ++matching_named_child_count;
        }
        // limit of 0 is reserved as no limit
        if( limit != 0 && matching_named_child_count == limit ) break;
    }
    return matching_named_child_count;
}
template<typename NTS, typename NIS
         ,class TP>
std::size_t TreeNodePool<NTS,NIS,TP>::child_at(
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
         ,class TP>
void TreeNodePool<NTS,NIS,TP>::node_path(
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
    else if( lineage.size() > 1 ){
        lineage.pop_back();
    }
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
         ,class TP>
void TreeNodePool<NTS,NIS,TP>::node_paths(
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
         ,class TP>
bool TreeNodePool<NTS,NIS,TP>::has_parent(
                    NIS node_index )const
{
    if( size() == 0 || node_index >= size()-1 ){
        return false;
    }
    std::size_t nodes_parent_index
            = parent_node_index(node_index);
    return nodes_parent_index != size();
}

// Obtain a nodes starting line
template<typename NTS, typename NIS
         ,class TP>
std::size_t TreeNodePool<NTS,NIS,TP>::line(
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
         ,class TP>
std::size_t TreeNodePool<NTS,NIS,TP>::column(
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
         ,class TP>
std::size_t TreeNodePool<NTS,NIS,TP>::leaf_index(
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
         ,class TP>
typename TP::token_type_size TreeNodePool<NTS,NIS,TP>::node_token_type(
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
         ,class TP>
std::string TreeNodePool<NTS,NIS,TP>::data(NIS node_index)const
{
    std::stringstream data_stream;
    data(node_index, data_stream);
    return data_stream.str();
}
// Obtain the node's data (string contents)
template<typename NTS, typename NIS
         ,class TP>
void TreeNodePool<NTS,NIS,TP>::data(NIS node_index
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
        TreeNodeView<TreeNodePool<NTS,NIS,TP>> view(node_index, *this);
        print(out,view);
    }
}

template<class TreeNodePool_T>
TreeNodeView<TreeNodePool_T>::TreeNodeView(std::size_t node_index
                        , const TreeNodePool_T & nodes)
    : m_tree_node_index(node_index)
    ,m_tree_data(&nodes)
{
    // TODO verify index is legal
}
template<class TreeNodePool_T>
TreeNodeView<TreeNodePool_T>::TreeNodeView(const TreeNodeView & orig)
    : m_tree_node_index(orig.m_tree_node_index)
    ,m_tree_data(orig.m_tree_data)
{
}
template<class TreeNodePool_T>
TreeNodeView<TreeNodePool_T>::~TreeNodeView()
{
}
template<class TreeNodePool_T>
TreeNodeView<TreeNodePool_T>& TreeNodeView<TreeNodePool_T>::operator =( const TreeNodeView& b)
{
    m_tree_node_index = b.m_tree_node_index;
    m_tree_data = b.m_tree_data;
    return *this;
}
template<class TreeNodePool_T>
bool TreeNodeView<TreeNodePool_T>::operator ==(const TreeNodeView& b)const
{
    return m_tree_data == b.m_tree_data
            && m_tree_node_index == b.m_tree_node_index;
}
template<class TreeNodePool_T>
TreeNodeView<TreeNodePool_T> TreeNodeView<TreeNodePool_T>::parent()const
{
    TreeNodeView<TreeNodePool_T> view (m_tree_data->parent_node_index(m_tree_node_index)
                       ,*m_tree_data);
    return view;
}
template<class TreeNodePool_T>
bool TreeNodeView<TreeNodePool_T>::has_parent()const
{
    return m_tree_data->has_parent(m_tree_node_index);
}
template<class TreeNodePool_T>
std::string TreeNodeView<TreeNodePool_T>::data()const{
    std::stringstream str;
    m_tree_data->data(m_tree_node_index,str);
    return str.str();
}
template<class TreeNodePool_T>
std::string TreeNodeView<TreeNodePool_T>::path()const{
    std::stringstream str;
    m_tree_data->node_path(m_tree_node_index,str);
    return str.str();
}
template<class TreeNodePool_T>
void TreeNodeView<TreeNodePool_T>::paths(std::ostream& out)const{
    m_tree_data->node_paths(m_tree_node_index,out);
}
template<class TreeNodePool_T>
std::size_t TreeNodeView<TreeNodePool_T>::child_count()const
{
    return m_tree_data->child_count(m_tree_node_index);
}
template<class TreeNodePool_T>
TreeNodeView<TreeNodePool_T> TreeNodeView<TreeNodePool_T>::child_at(std::size_t index)const
{

    auto child_node_pool_index = m_tree_data->child_at(m_tree_node_index
                                ,index);
    return TreeNodeView<TreeNodePool_T>(child_node_pool_index,*m_tree_data);
}
template<class TreeNodePool_T> // template type
typename TreeNodeView<TreeNodePool_T>::Collection // return type
TreeNodeView<TreeNodePool_T>::child_by_name(const std::string & name
                                                       , std::size_t limit)const
{
    TreeNodeView<TreeNodePool_T>::Collection results;

    for( std::size_t i = 0, count = child_count(); i < count; ++i )
    {
        auto child = child_at(i);
        std::string child_name = child.name();
        if( child_name == name )
        {
            results.push_back(child);
        }
        // limit of 0 is reserved as no limit
        if( limit != 0 && results.size() == limit ) break;
    }
    return results;
}
template<class TreeNodePool_T> // template type
TreeNodeView<TreeNodePool_T>
TreeNodeView<TreeNodePool_T>::first_child_by_name(const std::string & name)const
{
    for( std::size_t i = 0, count = child_count(); i < count; ++i )
    {
        auto child = child_at(i);
        if( name == child.name() ) return child;
    }
    return TreeNodeView<TreeNodePool_T>(); // null view
}
template<class TreeNodePool_T>
std::size_t TreeNodeView<TreeNodePool_T>::type()const
{
    return m_tree_data->type(m_tree_node_index);
}
template<class TreeNodePool_T>
std::size_t TreeNodeView<TreeNodePool_T>::token_type()const
{
    return m_tree_data->node_token_type(m_tree_node_index);
}
template<class TreeNodePool_T>
const char* TreeNodeView<TreeNodePool_T>::name()const
{
    return m_tree_data->name(m_tree_node_index);
}
template<class TreeNodePool_T>
std::size_t TreeNodeView<TreeNodePool_T>::line()const
{
    return m_tree_data->line(m_tree_node_index);
}
template<class TreeNodePool_T>
std::size_t TreeNodeView<TreeNodePool_T>::column()const
{
    return m_tree_data->column(m_tree_node_index);
}
template<class TreeNodePool_T>
bool TreeNodeView<TreeNodePool_T>::to_bool(bool * ok)const
{
    bool result = false;
    std::stringstream str;
    str<<std::boolalpha<< data();
    str>> result;
    if( ok ) *ok = !(str.bad() || str.fail());
    return result;
}
template<class TreeNodePool_T>
int TreeNodeView<TreeNodePool_T>::to_int(bool * ok)const
{
    int result = 0;
    to_type(result, data(), ok);
    return result;
}
template<class TreeNodePool_T>
double TreeNodeView<TreeNodePool_T>::to_double(bool * ok)const
{
    double result = 0.0;
    to_type(result, data(), ok);
    return result;
}
template<class TreeNodePool_T>
std::string TreeNodeView<TreeNodePool_T>::to_string(bool * ok)const
{
    std::string result;
    to_type(result, data(), ok);
    // trim front quotes
    result = wasp::strip_quotes(result);
    return result;
}


template<class TAdapter>
void print_from(std::ostream & stream, const TAdapter& tree_node, size_t& last_line, size_t& last_column)
{
    if( tree_node.child_count() == 0 )
    {
        //
        // determine distance from previous
        //
        size_t line = tree_node.line(); wasp_check(line > 0);
        size_t column = tree_node.column(); wasp_check(column > 0);
        size_t ldiff;
        if (line >= last_line) ldiff = line - last_line;
        else ldiff = 0;

        size_t cdiff;
        if (ldiff > 0) cdiff = column - 1;
        else if (column >= last_column) cdiff = column - last_column;
        else cdiff = 1;

//        if( cdiff <= column || cdiff <= lastColumn )
        // write preceeding newlines
        for( size_t i = 0; i < ldiff; i++) stream<<std::endl;
        //
        if( cdiff > 0 ) stream<<std::string(cdiff,' ');
        const std::string& data = tree_node.data();
        if( !(data.length() == 1 && data[0] == '\n') )stream<<data;

        int newLinePrintedCount = 0;
        if( !(data.length() == 1 && data[0] == '\n') ){
            newLinePrintedCount = std::count(data.begin(), data.end(), '\n');
        }
        last_line = line + newLinePrintedCount;
        // todo - data could span newlines making column some remainder
        last_column = column+data.size();
        return;
    }
    for(size_t i = 0, cc = tree_node.child_count(); i < cc; i++)
    {
        const TAdapter& child = tree_node.child_at(i);
        print_from(stream,child,last_line,last_column);
    }
}

#endif
