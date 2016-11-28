#include "waspsiren/SIRENInterpreter.h"
#include "waspcore/TreeNodePool.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

using namespace wasp;


TEST( SIREN, root_based_select_on_keyed_value )
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
    ASSERT_EQ( 1, document.child_count());
    TreeNodeView key = document.child_at(0);
    ASSERT_TRUE( key.has_parent() );
    ASSERT_EQ( 3, key.child_count() );
    {// select only the root
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
    {// select the key child
        SIRENInterpreter siren;
        ASSERT_TRUE( siren.parseString("/key") );
        {
            SIRENResultSet<TreeNodeView> set;
            ASSERT_EQ( 1, siren.evaluate<TreeNodeView>(document, set));
            ASSERT_EQ( 1, set.result_count() );
            ASSERT_TRUE( set.is_adapted(0) );
            std::string key = "key";
            ASSERT_EQ( key, set.adapted(0).name() );
            ASSERT_EQ( KEYED_VALUE, set.adapted(0).type() );
        }
    }
    {// select the key's value child
        SIRENInterpreter siren;
        ASSERT_TRUE( siren.parseString("/key/value") );
        {
            SIRENResultSet<TreeNodeView> set;
            ASSERT_EQ( 1, siren.evaluate<TreeNodeView>(document, set));
            ASSERT_EQ( 1, set.result_count() );
            ASSERT_TRUE( set.is_adapted(0) );
            std::string value = "value";
            ASSERT_EQ( value, set.adapted(0).name() );
            ASSERT_EQ( VALUE, set.adapted(0).type() );
        }
    }
    {// select the key's decl child
        SIRENInterpreter siren;
        ASSERT_TRUE( siren.parseString(" / key / decl ") );
        {
            SIRENResultSet<TreeNodeView> set;
            ASSERT_EQ( 1, siren.evaluate<TreeNodeView>(document, set));
            ASSERT_EQ( 1, set.result_count() );
            ASSERT_TRUE( set.is_adapted(0) );
            std::string decl = "decl";
            ASSERT_EQ( decl, set.adapted(0).name() );
            ASSERT_EQ( DECL, set.adapted(0).type() );
        }
    }
    {// select the key's decl child relative from document
        SIRENInterpreter siren;
        ASSERT_TRUE( siren.parseString("  key / decl ") );
        {
            SIRENResultSet<TreeNodeView> set;
            ASSERT_EQ( 1, siren.evaluate<TreeNodeView>(document, set));
            ASSERT_EQ( 1, set.result_count() );
            ASSERT_TRUE( set.is_adapted(0) );
            std::string decl = "decl";
            ASSERT_EQ( decl, set.adapted(0).name() );
            ASSERT_EQ( DECL, set.adapted(0).type() );
        }
    }
    {// select the key's decl child relative from key
        SIRENInterpreter siren;
        ASSERT_TRUE( siren.parseString(" decl ") );
        {
            SIRENResultSet<TreeNodeView> set;
            ASSERT_EQ( 1, siren.evaluate<TreeNodeView>(key, set));
            ASSERT_EQ( 1, set.result_count() );
            ASSERT_TRUE( set.is_adapted(0) );
            std::string decl = "decl";
            ASSERT_EQ( decl, set.adapted(0).name() );
            ASSERT_EQ( DECL, set.adapted(0).type() );
        }
    }
    {// test root-based selection with expected no results
        SIRENInterpreter siren;
        ASSERT_TRUE( siren.parseString(" /nothing/decl ") );
        {
            SIRENResultSet<TreeNodeView> set;
            ASSERT_EQ( 0, siren.evaluate<TreeNodeView>(key, set));
            ASSERT_EQ( 0, set.result_count() );
        }
    }
    {// test relative-based selection with expected no results
        SIRENInterpreter siren;
        ASSERT_TRUE( siren.parseString(" nothing/decl ") );
        {
            SIRENResultSet<TreeNodeView> set;
            ASSERT_EQ( 0, siren.evaluate<TreeNodeView>(key, set));
            ASSERT_EQ( 0, set.result_count() );
        }
    }
}

