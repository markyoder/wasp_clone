#include "waspsiren/SIRENInterpreter.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

using namespace wasp;

TEST( SIREN, parse_only_root )
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
TEST( SIREN, parse_simple_root )
{
    std::stringstream input;
    input<< R"INPUT(/child)INPUT";
    SIRENInterpreter interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(4, interpreter.node_count() );
    TreeNodeView document = interpreter.root();
    ASSERT_EQ( DOCUMENT_ROOT, document.type() );
    ASSERT_EQ( 1, document.child_count() );
    TreeNodeView root_selection = document.child_at(0);
    // when there exists a root selection
    // with a child selection the node type is a declaration
    ASSERT_EQ( DECL, root_selection.type() );
    // '/' 'child'
    ASSERT_EQ( 2, root_selection.child_count() );
    ASSERT_EQ( SEPARATOR, root_selection.child_at(0).type() );
    ASSERT_EQ( DECL, root_selection.child_at(1).type() );
    std::string decl = "child";
    ASSERT_EQ( decl, root_selection.child_at(1).name() );
}

TEST( SIREN, parse_simple_root_w_conditionally_predicated_child )
{
    std::stringstream input;
    input<< R"INPUT(/child/gchild[id=1]/ggchild)INPUT";
    SIRENInterpreter interpreter;
    ASSERT_EQ( true, interpreter.parse(input) );
    ASSERT_EQ(17, interpreter.node_count() );
    TreeNodeView document = interpreter.root();
    ASSERT_EQ( DOCUMENT_ROOT, document.type() );
    ASSERT_EQ( 1, document.child_count() );
//    document.paths(std::cout);
    std::vector<std::pair<std::string,NODE>> expected={
        {"/",SEPARATOR}
        ,{"child",DECL}

        ,{"/",SEPARATOR}
        ,{"gchild",DECL}
        ,{"[",LBRACKET}

        ,{"id",DECL}
        ,{"==",EQ}
        ,{"value",VALUE}
        ,{"id",KEYED_VALUE}

        ,{"]",RBRACKET}
        ,{"cpcs",PREDICATED_CHILD}

        ,{"/",SEPARATOR}
        ,{"ggchild",DECL}
        ,{"O",OBJECT}

        ,{"O",OBJECT}
        ,{"R",DECL}
        ,{"document", DOCUMENT_ROOT}
    };
    ASSERT_EQ( expected.size(), interpreter.node_count() );
    for( size_t i = 0; i < expected.size(); ++i)
    {
        {
        SCOPED_TRACE(i);
        ASSERT_EQ( expected[i].first, interpreter.name(i) );
        ASSERT_EQ( expected[i].second, interpreter.type(i) );
        }
    }
}
