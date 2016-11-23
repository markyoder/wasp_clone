#ifndef SIREN_SIRENINTERPRETER_I_H
#define SIREN_SIRENINTERPRETER_I_H
template<typename TAdapter>
size_t SIRENInterpreter::evaluate(
        TAdapter & node, SIRENResultSet<TAdapter> & result)const
{

    // the first selection
    // is either a document root-based selection
    // or a node-relative selection
    TreeNodeView selection_root = root();

    if( selection_root.child_count() == 0 ) return 0;

    TreeNodeView first_selection = selection_root.child_at(0);

    // if root-based, need to select the root of the document
    // relative to the node given
    // When first selection is '/', the user wants to only select the root
    bool is_only_root_oriented = first_selection.type() == wasp::DOCUMENT_ROOT
            && first_selection.child_count() == 0 ; // is it only '/', or '/', 'child'

    if( is_only_root_oriented )
    {
        TAdapter anode( node );
        while( anode.has_parent() )
        {
            anode = anode.parent();
        }
        // the root of the document
        result.push(anode);
        return result.result_count();
    }

    return 0;
}

#endif
