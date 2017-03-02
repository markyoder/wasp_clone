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

