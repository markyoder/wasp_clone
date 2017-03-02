#include "gtest/gtest.h"

#include "waspcore/Definition.h"
using namespace wasp;
/**
 * @brief TEST definition match at existing section
 *
 */
TEST( Definition, current_section)
{
    Definition definition;
    ASSERT_FALSE( definition.has( "child" ) );
    ASSERT_EQ(-1, definition.delta( "child" ) );

    Definition * child = definition.create("child");

    ASSERT_TRUE( definition.has( "child" ) );
    ASSERT_EQ(0, definition.delta( "child" ) );

    Definition * clone = definition.clone();

    ASSERT_TRUE( clone->has( "child" ) );
    ASSERT_EQ(0, clone->delta( "child" ) );
}


TEST( Definition, parent_section)
{
    Definition definition;
    Definition * child = definition.create("child");
    Definition * grandchild1 = child->create("grandchild1");
    Definition * grandchild2 = child->create("grandchild2");

    ASSERT_TRUE( child->has( "grandchild1" ) );
    ASSERT_EQ(0, child->delta( "grandchild1" ) );

    ASSERT_TRUE( child->has( "grandchild2" ) );
    ASSERT_EQ(0, child->delta( "grandchild2" ) );

    ASSERT_EQ(1, grandchild1->delta("grandchild1") );
    ASSERT_EQ(1, grandchild1->delta("grandchild2") );

    ASSERT_EQ(1, grandchild2->delta("grandchild1") );
    ASSERT_EQ(1, grandchild2->delta("grandchild2") );

    ASSERT_EQ(2, grandchild1->delta("child") );
    ASSERT_EQ(2, grandchild2->delta("child") );
}
