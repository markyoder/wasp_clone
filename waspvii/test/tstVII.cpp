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

TEST(VIInterpreter, passing_simple_blockions)
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
/block2/value (1)
/block2
/block2/decl (block2)
/block2/value (2)
/block2/sec2.2
/block2/block2.2/decl (block2.2)
/block2/block2.2/= (=)
/block2/block2.2/value (2.2)
)I";
    std::stringstream paths;
    vii.root().paths(paths);
}

TEST(VIInterpreter, passing_blockions_aliased)
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
/block2/value (1)
/block2
/block2/decl (block2)
/block2/value (2)
/block2/sec2.2
/block2/block2.2/decl (block2.2)
/block2/block2.2/value (2.2)
)I";
    std::stringstream paths;
    vii.root().paths(paths);
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

// TODO TEST
// Named commands
// commands containing the 'slash' construct
//
