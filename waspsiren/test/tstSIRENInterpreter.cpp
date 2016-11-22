#include "waspsiren/SIRENInterpreter.h"
#include "waspcore/TreeNodePool.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

using namespace wasp;


TEST( SIREN, root_only_select )
{    
    TreeNodePool<> tree;
    // decl = value
    // key = 3.14
    // document
    // |_keyedvalue
    //   |_ decl (key)
    //   |_ =  (=)
    //   |_ value (3.14)
    //

    auto token_i = tree.token_data().size();
    tree.token_data().push("key",wasp::STRING,0);
    tree.push_leaf(wasp::DECL,"decl"
                   , token_i ); // node 0
    token_i = tree.token_data().size();
    tree.token_data().push("=",wasp::ASSIGN,5);
    tree.push_leaf(wasp::ASSIGN,"="
                   , token_i ); // node 1
    token_i = tree.token_data().size();
    tree.token_data().push("3.14",wasp::REAL,7);
    tree.push_leaf(wasp::VALUE,"value"
                   , token_i ); // node 2
    tree.push_parent(wasp::KEYED_VALUE,"key",{0,1,2}); // node 3
    tree.push_parent(wasp::DOCUMENT_ROOT, "document", {3} ); // node 4
    TreeNodeView document(4, tree);
    SIRENInterpreter siren;
    ASSERT_TRUE( siren.parseString("/") );
    {
        SIRENResultSet<TreeNodeView> set;
        ASSERT_EQ( 1, siren.evaluate<TreeNodeView>(document, set));
        ASSERT_EQ( 1, set.result_count() );
        ASSERT_TRUE( set.is_adapted(0) );
        std::string document = "document";
        ASSERT_EQ( document, set.adapted(0).name() );
        ASSERT_EQ( DOCUMENT_ROOT, set.adapted(0).type() );
    }
}
