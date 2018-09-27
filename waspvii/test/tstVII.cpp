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
    block2.2
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
   block1.1 = block_data
 [erg]
 [block2]
)I" << std::endl;
    std::stringstream errors;
    VIInterpreter<>   vii(errors);
    vii.definition()->create("block1")->create("block1.1");
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
    {// acquire included block1

    auto b1node = viiroot.first_non_decorative_child_by_name("block1");
    ASSERT_EQ(1, b1node.line());
    ASSERT_EQ(2, b1node.last_line());
    ASSERT_EQ(1, b1node.column());
    ASSERT_EQ(11, b1node.last_column());
    }
    {
        ASSERT_EQ(2, viiroot.child_by_name("block1").size());
        ASSERT_EQ(2, viiroot.child_count_by_name("block1"));
        auto b1node = viiroot.child_by_name("block1")[1];
        ASSERT_EQ(2, b1node.line());
        ASSERT_EQ(6, b1node.last_line());
        ASSERT_EQ(3, b1node.column());
        ASSERT_EQ(13, b1node.last_column());
    }
    paths.str(""); // reset
    viiroot.paths(paths);
    std::stringstream expected_explicit;
    expected_explicit<<R"I(/
/incl
/block1
/block1/[ ([)
/block1/decl (block1)
/block1/] (])
/block1/block1.1
/block1/block1.1/decl (block_1.1)
/block1
/block1/[ ([)
/block1/decl (block1)
/block1/] (])
/block1/block1.1
/block1/block1.1/decl (block1.1)
/block1/incl
/block1/block1.2
/block1/block1.2/decl (block1.2)
/block1/block1.2/value (1)
/block1/block1.2
/block1/block1.2/decl (block1.2)
/block1/block1.2/value (2)
/block1/incl
/block1/block1.2
/block1/block1.2/decl (block1.2)
/block1/block1.2/value (3)
/block1/block1.2
/block1/block1.2/decl (block1.2)
/block1/block1.2/value (4)
/block1/comment (! trailing comment)
/block1/block1.3
/block1/block1.3/decl (block1.3)
)I";
    ASSERT_EQ(expected_explicit.str(), paths.str());
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

TEST(VIInterpreter, commas_semicolons)
{
    std::stringstream input;
    input << R"I(
 com 1,2; com_odd_even 6,7,8;
 com_index_aliased 8; com_named name 1,2;
 com_odd_even_named name 2,3,4;
 com_index_aliased_named  8
)I";
    DefaultVIInterpreter vii;
    vii.definition()->create("com");
    auto* odd_even = vii.definition()->create("com_odd_even");
    odd_even->create_aliased("_odd", odd_even->create("o"));
    odd_even->create_aliased("_even", odd_even->create("e"));

    auto* index_aliased = vii.definition()->create("com_index_aliased");
    index_aliased->create_aliased("_1", index_aliased->create("one"));

    vii.definition()->create("com_named")->create("_name");

    auto* odd_even_named = vii.definition()->create("com_odd_even_named");
    odd_even_named->create("_name");
    odd_even_named->create_aliased("_odd", odd_even_named->create("o"));
    odd_even_named->create_aliased("_even", odd_even_named->create("e"));

    auto* index_aliased_named = vii.definition()->create("com_index_aliased_named");
    index_aliased_named->create("_name");
    index_aliased_named->create_aliased("_1", index_aliased_named->create("named_one"));

    ASSERT_TRUE(vii.parse(input));
    ASSERT_EQ(6, vii.root().child_count());
    std::stringstream paths;
    vii.root().paths(paths);
    std::stringstream expected;
    expected<<R"I(/
/com
/com/decl (com)
/com/value (1)
/com/, (,)
/com/value (2)
/com/; (;)
/com_odd_even
/com_odd_even/decl (com_odd_even)
/com_odd_even/e (6)
/com_odd_even/, (,)
/com_odd_even/o (7)
/com_odd_even/, (,)
/com_odd_even/e (8)
/com_odd_even/; (;)
/com_index_aliased
/com_index_aliased/decl (com_index_aliased)
/com_index_aliased/one (8)
/com_index_aliased/; (;)
/com_named
/com_named/decl (com_named)
/com_named/_name (name)
/com_named/value (1)
/com_named/, (,)
/com_named/value (2)
/com_named/; (;)
/com_odd_even_named
/com_odd_even_named/decl (com_odd_even_named)
/com_odd_even_named/_name (name)
/com_odd_even_named/e (2)
/com_odd_even_named/, (,)
/com_odd_even_named/o (3)
/com_odd_even_named/, (,)
/com_odd_even_named/e (4)
/com_odd_even_named/; (;)
/com_index_aliased_named
/com_index_aliased_named/decl (com_index_aliased_named)
/com_index_aliased_named/_name (8)
)I";
    ASSERT_EQ(expected.str(), paths.str());

    VIINodeView viiroot = vii.root();
    VIINodeView com_odd_even_named = viiroot.first_child_by_name("com_odd_even_named");
    ASSERT_FALSE( com_odd_even_named.is_null() );
    ASSERT_EQ(8, com_odd_even_named.child_count());
    ASSERT_TRUE(com_odd_even_named.child_at(com_odd_even_named.child_count()-1).is_terminator());
    // _name and 3 values
    ASSERT_EQ(4, com_odd_even_named.non_decorative_children_count());
    const auto& non_decorative = com_odd_even_named.non_decorative_children();
    ASSERT_EQ(4, non_decorative.size());
    std::vector<std::string> names = {"_name", "e","o","e"};
    ASSERT_EQ(names.size(), non_decorative.size());
    for (size_t i = 0; i < names.size(); ++i)
    {
        SCOPED_TRACE(i);
        ASSERT_EQ(names[i], std::string(non_decorative[i].name()) );
    }
}

// TODO TEST
// commands containing the 'slash' construct
//
