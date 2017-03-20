/*
 * File:   tstHalite.cpp
 * Author: Robert A. Lefebvre
 */

#include <cstdlib>
#include <sstream>
#include <string>
#include <stdexcept>

#include <utility>
#include "wasphalite/SubStringIndexer.h"

#include "gtest/gtest.h"
using namespace std;
using namespace wasp;

TEST( Halite, sub_string_index)
{
    std::string str = " sssss";
    std::string substr = "s";
    SubStringIndexer indicies;
    ASSERT_TRUE( indicies.index(str,substr) );
    const SubStringIndexer::Index_type & index = indicies.data();
    ASSERT_TRUE( index.empty() == false );
    SubStringIndexer::Index_type expected = {1,2,3,4,5};
    ASSERT_EQ( expected, index );
}

TEST( Halite, multichar_sub_string_index)
{
    std::string str = " sssss";
    std::string substr = "ss";
    SubStringIndexer indicies;
    ASSERT_TRUE( indicies.index(str,substr) );
    const SubStringIndexer::Index_type & index = indicies.data();
    ASSERT_TRUE( index.empty() == false );
    SubStringIndexer::Index_type expected = {1,3};
    ASSERT_EQ( expected, index );
}
/**
 * @brief TEST test matching indices
 */
TEST( Halite, sub_string_merge_simple)
{
    std::string str = " foo <ted> bar";
    SubStringIndexer start_indices;
    {
        std::string startstr = "<";
        ASSERT_TRUE( start_indices.index(str,startstr) );
        const SubStringIndexer::Index_type & index = start_indices.data();
        ASSERT_TRUE( index.empty() == false );
        SubStringIndexer::Index_type expected = {5};
        ASSERT_EQ( expected, index );
    }
    SubStringIndexer end_indices;
    {
        std::string endstr = ">";
        ASSERT_TRUE( end_indices.index(str,endstr) );
        const SubStringIndexer::Index_type & index = end_indices.data();
        ASSERT_TRUE( index.empty() == false );
        SubStringIndexer::Index_type expected = {9};
        ASSERT_EQ( expected, index );
    }

    SubStringIndexer::IndexPairs_type results = start_indices.merge(end_indices);

    {
        ASSERT_EQ(1, results.size() );
        SubStringIndexer::IndexPairs_type expected = {{5,9}};
        ASSERT_EQ( expected, results );
    }

}

/**
 * @brief TEST test matching indices with nested matches
 */
TEST( Halite, sub_string_merge_nested)
{
    std::string str = " foo <<ted> bar>";
    SubStringIndexer start_indices;
    {
        std::string startstr = "<";
        ASSERT_TRUE( start_indices.index(str,startstr) );
        const SubStringIndexer::Index_type & index = start_indices.data();
        ASSERT_TRUE( index.empty() == false );
        SubStringIndexer::Index_type expected = {5,6};
        ASSERT_EQ( expected, index );
    }
    SubStringIndexer end_indices;
    {
        std::string endstr = ">";
        ASSERT_TRUE( end_indices.index(str,endstr) );
        const SubStringIndexer::Index_type & index = end_indices.data();
        ASSERT_TRUE( index.empty() == false );
        SubStringIndexer::Index_type expected = {10,15};
        ASSERT_EQ( expected, index );
    }

    SubStringIndexer::IndexPairs_type results = start_indices.merge(end_indices);

    {
        ASSERT_EQ(2, results.size() );
        SubStringIndexer::IndexPairs_type expected = {{6,10},{5,15}};
        ASSERT_EQ( expected, results );
    }

}

/**
 * @brief TEST test matching indices with nested matches
 */
TEST( Halite, sub_string_merge_nested_unmatched)
{
    std::string str = "< foo <<ted> bar>";
    SubStringIndexer start_indices;
    {
        std::string startstr = "<";
        ASSERT_TRUE( start_indices.index(str,startstr) );
        const SubStringIndexer::Index_type & index = start_indices.data();
        ASSERT_TRUE( index.empty() == false );
        SubStringIndexer::Index_type expected = {0,6,7};
        ASSERT_EQ( expected, index );
    }
    SubStringIndexer end_indices;
    {
        std::string endstr = ">";
        ASSERT_TRUE( end_indices.index(str,endstr) );
        const SubStringIndexer::Index_type & index = end_indices.data();
        ASSERT_TRUE( index.empty() == false );
        SubStringIndexer::Index_type expected = {11,16};
        ASSERT_EQ( expected, index );
    }

    SubStringIndexer::IndexPairs_type results = start_indices.merge(end_indices);

    {
        ASSERT_EQ(2, results.size() );
        SubStringIndexer::IndexPairs_type expected = {{7,11},{6,16}};
        ASSERT_EQ( expected, results );
    }

}

/**
 * @brief TEST test indices involving unmatched/hanging indices
 */
TEST( Halite, sub_string_merge_hanging)
{
    std::string str = " foo ><ted>< bar";
    SubStringIndexer start_indices;
    {
        std::string startstr = "<";
        ASSERT_TRUE( start_indices.index(str,startstr) );
        const SubStringIndexer::Index_type & index = start_indices.data();
        ASSERT_TRUE( index.empty() == false );
        SubStringIndexer::Index_type expected = {6,11};
        ASSERT_EQ( expected, index );
    }
    SubStringIndexer end_indices;
    {
        std::string endstr = ">";
        ASSERT_TRUE( end_indices.index(str,endstr) );
        const SubStringIndexer::Index_type & index = end_indices.data();
        ASSERT_TRUE( index.empty() == false );
        SubStringIndexer::Index_type expected = {5,10};
        ASSERT_EQ( expected, index );
    }

    SubStringIndexer::IndexPairs_type results = start_indices.merge(end_indices);

    {
        ASSERT_EQ(1, results.size() );
        SubStringIndexer::IndexPairs_type expected = {{6,10}};
        ASSERT_EQ( expected, results );
    }

}

/**
 * @brief TEST test multiple indices involving unmatched/hanging indices
 */
TEST( Halite, sub_string_merge_multiple)
{
    std::string str = "> foo ><ted>< <bar>";
    SubStringIndexer start_indices;
    {
        std::string startstr = "<";
        ASSERT_TRUE( start_indices.index(str,startstr) );
        const SubStringIndexer::Index_type & index = start_indices.data();
        ASSERT_TRUE( index.empty() == false );
        SubStringIndexer::Index_type expected = {7,12,14};
        ASSERT_EQ( expected, index );
    }
    SubStringIndexer end_indices;
    {
        std::string endstr = ">";
        ASSERT_TRUE( end_indices.index(str,endstr) );
        const SubStringIndexer::Index_type & index = end_indices.data();
        ASSERT_TRUE( index.empty() == false );
        SubStringIndexer::Index_type expected = {0,6,11,18};
        ASSERT_EQ( expected, index );
    }

    SubStringIndexer::IndexPairs_type results = start_indices.merge(end_indices);

    {
        ASSERT_EQ(2, results.size() );
        SubStringIndexer::IndexPairs_type expected = {{7,11},{14,18}};
        ASSERT_EQ( expected, results );
    }
}

/**
 * @brief TEST test multiple indices involving unmatched/hanging indices
 */
TEST( Halite, multichar_sub_string_merge_multiple)
{
    std::string str = "}} foo }}{{ted}}{{ {{bar}}";
    SubStringIndexer start_indices;
    {
        std::string startstr = "{{";
        ASSERT_TRUE( start_indices.index(str,startstr) );
        const SubStringIndexer::Index_type & index = start_indices.data();
        ASSERT_TRUE( index.empty() == false );
        SubStringIndexer::Index_type expected = {9,16,19};
        ASSERT_EQ( expected, index );
    }
    SubStringIndexer end_indices;
    {
        std::string endstr = "}}";
        ASSERT_TRUE( end_indices.index(str,endstr) );
        const SubStringIndexer::Index_type & index = end_indices.data();
        ASSERT_TRUE( index.empty() == false );
        SubStringIndexer::Index_type expected = {0,7,14,24};
        ASSERT_EQ( expected, index );
    }

    SubStringIndexer::IndexPairs_type results = start_indices.merge(end_indices);

    {
        ASSERT_EQ(2, results.size() );
        SubStringIndexer::IndexPairs_type expected = {{9,14},{19,24}};
        ASSERT_EQ( expected, results );
    }
}
