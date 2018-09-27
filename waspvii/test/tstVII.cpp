#include "waspvii/VIInterpreter.h"
#include "waspvii/VIINodeView.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>
using namespace wasp;

TEST(VIInterpreter, comments)
{
    std::stringstream input;
    input << R"I( ! comments
 !comments here
 !comments there

 ! comments everywhere
)I" << std::endl;
    DefaultVIInterpreter vii;
    ASSERT_TRUE(vii.parse(input));
    ASSERT_EQ(4, vii.root().child_count());

}

TEST(VIInterpreter, named)
{
    std::stringstream input;
    input << R"I( [block]
 command1 name1 2 3
 command2 3 4
 command3 1 4.3
)I" << std::endl;
    DefaultVIInterpreter vii;
    auto*                block1   = vii.definition()->create("block");
    auto*                command1 = block1->create("command1");
    command1->create("_name");
    block1->create("command2");
    block1->create("command3")->create("_name");
    EXPECT_TRUE(vii.parse(input));
    std::stringstream paths;
    vii.root().paths(paths);
    std::stringstream expected;
    expected << R"I(/
/block
/block/[ ([)
/block/decl (block)
/block/] (])
/block/command1
/block/command1/decl (command1)
/block/command1/_name (name1)
/block/command1/value (2)
/block/command1/value (3)
/block/command2
/block/command2/decl (command2)
/block/command2/value (3)
/block/command2/value (4)
/block/command3
/block/command3/decl (command3)
/block/command3/_name (1)
/block/command3/value (4.3)
)I";

    ASSERT_EQ(expected.str(), paths.str());
}

// TEST that named-index aliased list parameters work as expected
TEST(VIInterpreter, indexed)
{
    std::stringstream input;
    input << R"I( [block]
 command1 2 3
 command2 3 4
 command3 1 4.3
)I" << std::endl;
    DefaultVIInterpreter vii;
    auto*                block1   = vii.definition()->create("block");
    auto*                command1 = block1->create("command1");
    auto* b = command1->create("b");
    command1->create_aliased("_2",b);
    auto* command2 = block1->create("command2");
    auto * x = command2->create("x");
    // create named index at 1st
    command2->create_aliased("_1", x);
    auto* command3 = block1->create("command3");
    command3->create("_name");
    // create named index at 2nd child of named
    auto* y = command3->create("y");
    command3->create_aliased("_1", y);
    EXPECT_TRUE(vii.parse(input));
    std::stringstream paths;
    vii.root().paths(paths);
    std::stringstream expected;
    expected << R"I(/
/block
/block/[ ([)
/block/decl (block)
/block/] (])
/block/command1
/block/command1/decl (command1)
/block/command1/value (2)
/block/command1/b (3)
/block/command2
/block/command2/decl (command2)
/block/command2/x (3)
/block/command2/value (4)
/block/command3
/block/command3/decl (command3)
/block/command3/_name (1)
/block/command3/y (4.3)
)I";

    ASSERT_EQ(expected.str(), paths.str());
    VIINodeView root = vii.root();
    EXPECT_EQ(3,root.first_child_by_name("block")
              .first_child_by_name("command1")
              .first_child_by_name("b").to_int());
    EXPECT_EQ(4.3,root.first_child_by_name("block")
              .first_child_by_name("command3")
              .first_child_by_name("y").to_double());
    EXPECT_EQ("1",root.first_child_by_name("block")
              .first_child_by_name("command3").id());
    EXPECT_EQ("1",root.first_child_by_name("block")
              .first_child_by_name("command3").id_child().to_string());
    EXPECT_EQ(wasp::OBJECT,root.first_child_by_name("block").type());
    EXPECT_EQ("",root.first_child_by_name("block").id());
    EXPECT_EQ("",root.first_child_by_name("block").id());
    EXPECT_TRUE(root.first_child_by_name("block").id_child().is_null());
    EXPECT_EQ(3,root.first_child_by_name("block").non_decorative_children().size());
}

// TEST that named-odd-even-index aliased list parameters work as expected
TEST(VIInterpreter, even_odd)
{
    std::stringstream input;
    input << R"I([block]
 command1 0 ! comment
          one 2
 command2 name 4 5 ! comment
          six
)I" << std::endl;
    DefaultVIInterpreter vii;
    auto*                block1   = vii.definition()->create("block");

    // Create regular command (no named node)
    auto*                command1 = block1->create("command1");
    auto* c1o = command1->create("odd");
    command1->create_aliased("_odd",c1o);
    auto* c1e = command1->create("even");
    command1->create_aliased("_even",c1e);

    // Create named command with even-odd
    auto* command2 = block1->create("command2");
    command2->create("_name");
    auto* c2o = command2->create("odd");
    command2->create_aliased("_odd",c2o);
    auto* c2e = command2->create("even");
    command2->create_aliased("_even",c2e);
    EXPECT_TRUE(vii.parse(input));
    std::stringstream paths;
    vii.root().paths(paths);
    std::stringstream expected;
    expected << R"I(/
/block
/block/[ ([)
/block/decl (block)
/block/] (])
/block/command1
/block/command1/decl (command1)
/block/command1/even (0)
/block/command1/comment (! comment)
/block/command1/odd (one)
/block/command1/even (2)
/block/command2
/block/command2/decl (command2)
/block/command2/_name (name)
/block/command2/even (4)
/block/command2/odd (5)
/block/command2/comment (! comment)
/block/command2/even (six)
)I";

    ASSERT_EQ(expected.str(), paths.str());
}
TEST(VIInterpreter, comment_placement)
{
    std::stringstream input;
    input << R"I( ! comment of document
 block1 "a"
    ! comment for blockion 1
    block1.1
        block1.1.1 ! comment for block 1.1.1
        !comment still 1.1.1
        block1.1.2
            !comment for 1.1.2
    block1.2
        ! comment of 1.2
        block1.2.1
! block 1.2.1
        block1.2.2
        block1.2.3 "value"
    !block 1.2.3
    block1.3
 block2
)I" << std::endl;
    DefaultVIInterpreter vii;
    auto*                block1   = vii.definition()->create("block1");
    auto*                block1_1 = block1->create("block1.1");
    block1_1->create("block1.1.1");
    block1_1->create("block1.1.2");
    auto* block1_2 = block1->create("block1.2");
    block1_2->create("block1.2.1");
    block1_2->create("block1.2.2");
    block1_2->create("block1.2.3");
    block1->create("block1.3");
    vii.definition()->create("block2");
    EXPECT_TRUE(vii.parse(input));
    std::stringstream paths;
    vii.root().paths(paths);
    std::stringstream expected;
    expected << R"I(/
/comment (! comment of document)
/block1
/block1/decl (block1)
/block1/value ("a")
/block1/comment (! comment for blockion 1)
/block1/block1.1
/block1/block1.1/decl (block1.1)
/block1/block1.1/block1.1.1
/block1/block1.1/block1.1.1/decl (block1.1.1)
/block1/block1.1/block1.1.1/comment (! comment for block 1.1.1)
/block1/block1.1/block1.1.1/comment (!comment still 1.1.1)
/block1/block1.1/block1.1.2
/block1/block1.1/block1.1.2/decl (block1.1.2)
/block1/block1.1/block1.1.2/comment (!comment for 1.1.2)
/block1/block1.2
/block1/block1.2/decl (block1.2)
/block1/block1.2/comment (! comment of 1.2)
/block1/block1.2/block1.2.1
/block1/block1.2/block1.2.1/decl (block1.2.1)
/block1/block1.2/block1.2.1/comment (! block 1.2.1)
/block1/block1.2/block1.2.2
/block1/block1.2/block1.2.2/decl (block1.2.2)
/block1/block1.2/block1.2.3
/block1/block1.2/block1.2.3/decl (block1.2.3)
/block1/block1.2/block1.2.3/value ("value")
/block1/block1.2/block1.2.3/comment (!block 1.2.3)
/block1/block1.3
/block1/block1.3/decl (block1.3)
/block2
/block2/decl (block2)
)I";

    ASSERT_EQ(expected.str(), paths.str());
}
TEST(VIInterpreter, passing_flat)
{
    std::stringstream input;
    input << R"I( block1
2block 1
block3 1
block4 1.1
block5 1.e29
block6 "ted"
block7 "ted"
block8 1 2       ! comment about block8 list line 1
        3.4       ! comment about block8 list line 2
        "five"   ! comment about block8 list line 3
block9  1 2        ! comment about block9 list line 1
       3.4 "five" ! comment about block9 list line 2
)I" << std::endl;
    DefaultVIInterpreter vii;
    vii.definition()->create("block1");
    vii.definition()->create("2block");
    vii.definition()->create("block3");
    vii.definition()->create("block4");
    vii.definition()->create("block5");
    vii.definition()->create("block6");
    vii.definition()->create("block7");
    vii.definition()->create("block8");
    vii.definition()->create("block9");
    ASSERT_TRUE(vii.parse(input));
    std::stringstream expected;
    expected << R"I(/
/block1
/block1/decl (block1)
/2block
/2block/decl (2block)
/2block/value (1)
/block3
/block3/decl (block3)
/block3/value (1)
/block4
/block4/decl (block4)
/block4/value (1.1)
/block5
/block5/decl (block5)
/block5/value (1.e29)
/block6
/block6/decl (block6)
/block6/value ("ted")
/block7
/block7/decl (block7)
/block7/value ("ted")
/block8
/block8/decl (block8)
/block8/value (1)
/block8/value (2)
/block8/comment (! comment about block8 list line 1)
/block8/value (3.4)
/block8/comment (! comment about block8 list line 2)
/block8/value ("five")
/block8/comment (! comment about block8 list line 3)
/block9
/block9/decl (block9)
/block9/value (1)
/block9/value (2)
/block9/comment (! comment about block9 list line 1)
/block9/value (3.4)
/block9/value ("five")
/block9/comment (! comment about block9 list line 2)
)I";
    std::stringstream paths;
    VIINodeView       root = vii.root();
    root.paths(paths);
    ASSERT_EQ(expected.str(), paths.str());

    ASSERT_EQ(1,
              root.child_at(1)  // block2
                  .child_at(1) // value
                  .to_int());
}

TEST(VIInterpreter, passing_simple_blocks)
{
    std::stringstream input;
    input << R"I( block1 1
block2 2
    block2.2=2.2

)I" << std::endl;
    DefaultVIInterpreter vii;
    vii.definition()->create("block1")->create("block1.1");
    vii.definition()->create("block2")->create("block2.2");
    ASSERT_TRUE(vii.parse(input));
    std::stringstream expected;
    expected << R"I(/
/block1
/block1/decl (block1)
/block1/value (1)
/block2
/block2/decl (block2)
/block2/value (2)
/block2/block2.2
/block2/block2.2/decl (block2.2)
/block2/block2.2/= (=)
/block2/block2.2/value (2.2)
)I";
    std::stringstream paths;
    vii.root().paths(paths);
    ASSERT_EQ(expected.str(), paths.str());
}

TEST(VIInterpreter, passing_blocks_aliased)
{
    std::stringstream input;
    input << R"I( block1 1 blurgity_blarg
blergity_blerg 2
    block2.2 2.2
)I" << std::endl;
    DefaultVIInterpreter vii;
    auto block = vii.definition()->create("block1")->create("block1.1");
    block->parent()->create_aliased("blurgity_blarg", block);
    vii.definition()->create("block2")->create("block2.2");
    vii.definition()->create_aliased("blergity_blerg",
                                     vii.definition()->get("block2"));
    ASSERT_TRUE(vii.parse(input));
    std::stringstream expected;
    expected << R"I(/
/block1
/block1/decl (block1)
/block1/value (1)
/block1/block1.1
/block1/block1.1/decl (blurgity_blarg)
/block2
/block2/decl (blergity_blerg)
/block2/value (2)
/block2/block2.2
/block2/block2.2/decl (block2.2)
/block2/block2.2/value (2.2)
)I";
    std::stringstream paths;
    vii.root().paths(paths);
    ASSERT_EQ(expected.str(), paths.str());
}


/**
 * @brief TEST
 */
TEST(VIInterpreter, test_simple_blocks)
{
    std::stringstream input;
    input << R"I( [block1]

 [block1]
   block1.1
 [block2]
)I" << std::endl;
    std::stringstream errors;
    VIInterpreter<>   vii(errors);
    vii.definition()->create("block1")->create("block1.1");
    vii.definition()->create("block2");

    EXPECT_TRUE(vii.parse(input));

    const auto& root = vii.root();
    ASSERT_EQ(3, root.child_count());
    ASSERT_EQ("block1", std::string(root.child_at(0).name()));
    ASSERT_EQ("block1", std::string(root.child_at(1).name()));
    // [, decl, ],  block1.1
    ASSERT_EQ(4, root.child_at(1).child_count());
    ASSERT_EQ("block1.1", std::string(root.child_at(1).child_at(3).name()));
    ASSERT_EQ("block2", std::string(root.child_at(2).name()));
}
/**
 * @brief TEST
 */
TEST(VIInterpreter, test_unknown_blocks)
{
    std::stringstream input;
    input << R"I( [unknown]

 [block1]
   block1.1
 [erg]
 [block2]
)I" << std::endl;
    std::stringstream errors;
    VIInterpreter<>   vii(errors);
    auto* b11 = vii.definition()->create("block1")->create("block1.1");
    vii.definition()->create("block2");

    EXPECT_FALSE(vii.parse(input));
    std::stringstream expected_errors;
    expected_errors<<"stream input:1.3-9: 'unknown' is unknown."<<std::endl
                  <<"stream input:5.3-5: 'erg' is unknown."<<std::endl;
    ASSERT_EQ(expected_errors.str(), errors.str());

    const auto& root = vii.root();
    ASSERT_EQ(2, root.child_count());
    ASSERT_EQ("block1", std::string(root.child_at(0).name()));
    // [, decl, ],  block1.1
    ASSERT_EQ(4, root.child_at(0).child_count());
    ASSERT_EQ("block1.1", std::string(root.child_at(0).child_at(3).name()));
    ASSERT_EQ("block2", std::string(root.child_at(1).name()));

    auto lineage = wasp::lineage(root.child_at(0) // block1
                                     .child_at(3)); // block1.1
    EXPECT_EQ(2, lineage.size());
    ASSERT_EQ("block1.1", std::string(lineage[0].name()));
    ASSERT_EQ("block1", std::string(lineage[1].name()));
    auto* def = wasp::get_definition(root.child_at(0).child_at(3).node_index(),
                                   &vii);
    ASSERT_EQ(b11, def);
}

TEST(VIInterpreter, includes)
{
    {
    std::ofstream block_file("block.txt");
    block_file << "[block1] " <<std::endl
               << "  block_1.1"<<std::endl;
    block_file.close();
    }
    {
    std::ofstream block_file("block1.2.txt");
    block_file << "  block1.2 1 " <<std::endl
               << "  block1.2 2"<<std::endl;
    block_file.close();
    }
    {
    std::ofstream block_file("_block1.2.txt");
    block_file << "block1.2 3 " <<std::endl
               << "  block1.2 4"<<std::endl;
    block_file.close();
    }
    std::stringstream input;
    input << R"I( include block.txt
 [block1]
     block1.1
     include block1.2.txt
     include _block1.2.txt ! trailing comment
     block1.3
)I" << std::endl;

    DefaultVIInterpreter vii;
    auto b1 = vii.definition()->create("block1");
    b1->create_aliased("block_1.1",b1->create("block1.1"));
    b1->create("block1.2");
    b1->create("block1.3");

    ASSERT_TRUE(vii.parseStream(input, "./"));
    ASSERT_EQ(3, vii.document_count());
    std::stringstream paths;
    vii.root().paths(paths);
    std::stringstream expected;
    expected<<R"I(/
/incl
/incl/decl (include)
/incl/path (block.txt)
/block1
/block1/[ ([)
/block1/decl (block1)
/block1/] (])
/block1/block1.1
/block1/block1.1/decl (block1.1)
/block1/incl
/block1/incl/decl (include)
/block1/incl/path (block1.2.txt)
/block1/incl
/block1/incl/decl (include)
/block1/incl/path (_block1.2.txt )
/block1/comment (! trailing comment)
/block1/block1.3
/block1/block1.3/decl (block1.3)
)I";

    ASSERT_EQ(expected.str(), paths.str());

    VIINodeView blocktxt_incl_node = vii.root().child_at(0); 
    ASSERT_EQ(wasp::FILE, blocktxt_incl_node.type());
    // should have an associated document
    ASSERT_NE(nullptr, vii.document(blocktxt_incl_node.node_index()));


    ASSERT_EQ(1, blocktxt_incl_node.non_decorative_children().size());
    // block_1.1 aliased to 'block1.1'    
    ASSERT_EQ(1, blocktxt_incl_node.non_decorative_children()[0].non_decorative_children().size());
    ASSERT_EQ("block1.1", std::string(blocktxt_incl_node.non_decorative_children()[0].non_decorative_children()[0].name()));

    VIINodeView viiroot = vii.root();
    VIINodeView blocktxt_root = viiroot.child_at(0);
    ASSERT_EQ(wasp::FILE, blocktxt_root.type());
    ASSERT_EQ(1, blocktxt_root.child_count()); // dereferences
    auto block1 = blocktxt_root.child_at(0); // dereferences
    ASSERT_EQ("/block1", block1.path());

    // [ decl ] block_1.1
    ASSERT_EQ(4, block1.child_count());
    auto block_11 = block1.child_at(3);
    ASSERT_EQ("block_1.1", block_11.data());
    ASSERT_EQ("/block1/block1.1", block_11.path());

    { // cleanup test files
    std::remove("block.txt");
    std::remove("block1.2.txt");
    std::remove("_block1.2.txt");
    }
}


// TODO TEST
// commands containing the 'slash' construct
//
