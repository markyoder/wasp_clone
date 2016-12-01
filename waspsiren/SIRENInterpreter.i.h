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
        case DECL: // named child search
            search_child_name(context, stage);
        break;
        case PARENT : // select parent of current nodes '..'
        {
            size_t count = stage.size();
            for( size_t i = 0; i < count; ++i)
            {
                const TAdapter& node = stage[i];
                if( node.has_parent() ) stage.push_back( node.parent() );
            }
            stage.erase(stage.begin(),stage.begin()+count);
        }break;
        case OBJECT : // selection / selection
        {
            TreeNodeView left_selection = context.child_at(0);
            // TODO - ensure selections are legit
            if( evaluate(left_selection,result,stage) > 0 ){
                TreeNodeView right_selection = context.child_at(2);
                evaluate(right_selection,result,stage);
            }
        }break;
        case PREDICATED_CHILD: // obj[id=value] or obj[1:3:2]
        {
            // 'obj' = [0]
            // '['   = [1]
            // 'id=value' | '1:3:2' = [2]
            TreeNodeView predicate_node = context.child_at(2);
            if( predicate_node.type() == KEYED_VALUE )
            {
                search_conditional_predicated_child(context,stage);
            }
            else if( predicate_node.type() == INDEX )
            {
                search_index_predicated_child(context,stage);
            }
        }break;
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
template<typename TAdapter>
void SIRENInterpreter::search_conditional_predicated_child(
        const TreeNodeView & context,
        std::vector<TAdapter> & stage)const
{
    // context should be something like
    // obj [ id=value ]
    // obj = [0]
    // '[' = [1]
    // 'id=value' = [2]
    // ']' = [3]
    // TODO - ensure context fulfills expectations
    TreeNodeView child_name_context = context.child_at(0);
    // predicate context should be something like
    // id = value
    // id = [0]
    // '=' = [1]
    // value = [2]
    TreeNodeView predicate_context = context.child_at(2);
    // TODO - ensure predicate context fulfills expectations
    TreeNodeView predicate_name_context = predicate_context.child_at(0);
    TreeNodeView predicate_value_context = predicate_context.child_at(2);

    // the names for which to search
    const char * name = child_name_context.name();
    const char * predicate_name = predicate_name_context.name();
    const std::string& predicate_value = predicate_value_context.data();
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
                // prior to pushing, must determine if the
                // predicate passes
                // TODO - added expression evaluator
                // for proper robustness.
                // string compare fails quickly '1' == '1.0' fails, but should
                // not considering user is expecting it is a numeric comparison.
                bool predicate_accepted = false; // assume predicate fails
                for( size_t gc = 0, gc_count = child_node.child_count();
                     gc < gc_count; ++gc)
                {
                    const TAdapter & g_child_node = child_node.child_at(gc);
                    // if grand child name is a match, need to determine
                    // if value matches
                    if( strcmp( predicate_name, g_child_node.name() ) == 0 )
                    {
                        const std::string & g_child_node_value = g_child_node.data();
                        predicate_accepted = predicate_value == g_child_node_value;
                        if( predicate_accepted )
                        {
                            break; // break from grandchild loop
                        }
                    }
                }
                if( predicate_accepted ) stage.push_back( child_node );
            }
        }
    }
    stage.erase(stage.begin(),stage.begin()+stage_size);
}
template<typename TAdapter>
void SIRENInterpreter::search_index_predicated_child(
        const TreeNodeView & context,
        std::vector<TAdapter> & stage)const
{
    // context should be something like
    // obj [ 1 ] | obj [ 1:10 ] | obj [ 1:10:2 ]
    // obj = [0]
    // '[' = [1]
    // index '1' | '1:10' | '1:10:2' = [2]
    // ']' = [3]
    // TODO - ensure context fulfills expectations
    TreeNodeView child_name_context = context.child_at(0);
    // predicate context should be something like
    // index  - 1 child
    // start : end - 3 children
    // start : end : stride - 5 children
    TreeNodeView predicate_context = context.child_at(2);
    // TODO - ensure predicate context fulfills expectations
    size_t start_i = 0, end_i = 0, stride = 1;
    size_t incident_count = 0;

    // the names for which to search
    const char * name = child_name_context.name();

    // single index selection - start = end, stride =1
    if( predicate_context.child_count() == 1 )
    {   // TODO check type
        TreeNodeView index = predicate_context.child_at(0);
        end_i = start_i = index.to_int();
    }

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
                ++incident_count; // increment prior to comparison - 1 based indices
                if( incident_count >= start_i  //
                        && incident_count <= end_i
                        && incident_count % stride == 0)
                {
                    stage.push_back(child_node);
                }
            }
            // early terminate when our range has been exhausted
            else if( incident_count > end_i ) {
                break;
            }
        }
    }
    stage.erase(stage.begin(),stage.begin()+stage_size);
}
#endif
