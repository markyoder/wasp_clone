/*
 * File:   tstHalite.cpp
 * Author: Robert A. Lefebvre
 */

#include <cstdlib>
#include <sstream>
#include <string>
#include <stdexcept>
#include <functional>
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

TEST( Halite, sub_string_multichar_index)
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
