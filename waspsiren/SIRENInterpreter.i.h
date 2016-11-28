#ifndef SIREN_SIRENINTERPRETER_I_H
#define SIREN_SIRENINTERPRETER_I_H
#include <cstring> // strcmp
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
    bool is_root_oriented = first_selection.type() == wasp::DOCUMENT_ROOT
            // first selection of 'any' is a root oriented selection
                                || first_selection.type() ==  wasp::ANY ;
    bool is_only_root_oriented = is_root_oriented
            && first_selection.child_count() <= 1 ; // is it only '/', not '/' and 'child'

    std::vector<TAdapter> stage;
    if( is_root_oriented )
    {
        TAdapter anode( node );
        while( anode.has_parent() )
        {
            anode = anode.parent();
        }
        // the root of the document
        if( is_only_root_oriented ) {
            result.push(anode);
            return result.result_count();
        }
        stage.push_back(anode);
    }else{
        stage.push_back(node);
    }

    evaluate(first_selection, result, stage);
    for( size_t i = 0; i < stage.size(); ++i )
    {
        result.push(stage[i]);
    }
    return result.result_count();
}
template<typename TAdapter>
size_t SIRENInterpreter::evaluate(
        const TreeNodeView & context
        ,SIRENResultSet<TAdapter> & result
        ,std::vector<TAdapter> & stage )const
{
    switch( context.type() )
    {
        default:
            return -1; // ERROR - unsupported type (underflow)
        break;
        case DOCUMENT_ROOT:
            if( context.child_count() > 0 ){ // '/' relative_selection
                TreeNodeView child_context = context.child_at(1);
                evaluate(child_context,result, stage);
            }
            break;
        case SEPARATOR:
        break;

//        case ANY:
//        select_any( context, node, result );
        case DECL: // named child search
            search_child_name(context, stage);
        break;
        case OBJECT : // selection / selection
            TreeNodeView left_selection = context.child_at(0);
            // TODO - ensure selections are legit
            if( evaluate(left_selection,result,stage) > 0 ){
                TreeNodeView right_selection = context.child_at(2);
                evaluate(right_selection,result,stage);
            }
        break;
    } // end of switch on context type

    return stage.size();
}
template<typename TAdapter>
void SIRENInterpreter::search_child_name(
        const TreeNodeView & context,
        std::vector<TAdapter> & stage)const
{
    // the name for which to search
    const char * name = context.name();
    size_t stage_size = stage.size();
    for( size_t i = stage.size(); i > 0; --i )
    {
        size_t index = i-1;
        const TAdapter & node = stage[index];
        for( size_t c = 0; c < node.child_count(); ++c )
        {
            const TAdapter & child_node = node.child_at(c);
            // if child is a match, push back onto stage
            if( strcmp( name, child_node.name() ) == 0 )
            {
                stage.push_back( child_node );
            }
        }
    }
    stage.erase(stage.begin(),stage.begin()+stage_size);
}
#endif
