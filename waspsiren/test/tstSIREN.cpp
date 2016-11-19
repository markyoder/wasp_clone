#include "waspsiren/SIRENInterpreter.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

using namespace wasp;

TEST( SIREN, parse_root )
{
    std::stringstream input;
    input<< R"INPUT(/)INPUT";
    SIRENInterpreter interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(2, interpreter.node_count() );
    TreeNodeView document = interpreter.root();
    ASSERT_EQ( DOCUMENT_ROOT, document.type() );
    ASSERT_EQ( 1, document.child_count() );
    TreeNodeView root_selection = document.child_at(0);
    // when there exists only the root selection
    // the node type is a separator
    ASSERT_EQ( SEPARATOR, root_selection.type() );
}
