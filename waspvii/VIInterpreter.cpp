
#include "waspvii/VIInterpreter.h"
#include "waspvii/VIINodeView.h"
#include "waspcore/Definition.h"
#include "waspcore/wasp_bug.h"
#include "waspcore/wasp_node.h"
namespace wasp
{


AbstractDefinition* get_definition(size_t node_index,
                                    AbstractInterpreter *interp)
{
    wasp_require(interp);
    wasp_require(interp->definition());
    wasp_require(node_index < interp->size());

    VIINodeView nv(node_index,*interp);

    auto node_lineage = wasp::lineage(nv);

    auto* definition = interp->definition();

    while (definition->parent() != nullptr )
    {
        definition = definition->parent();
    }
    // lineage is from node to ancestor (front to back)
    // traverse from ancestor to node definition
    while( !node_lineage.empty() )
    {
        const std::string& name = node_lineage.back().name();
        wasp_check(definition->has(name));
        definition = definition->get(name);
        node_lineage.pop_back();
    }
    return definition;
}
}
