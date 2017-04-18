/*
 * File:   tstHalite.cpp
 * Author: Robert A. Lefebvre
 */

#include <cstdlib>
#include <sstream>
#include <string>
#include <stdexcept>

#include <utility>
#include "waspcore/Object.h"
#include "wasphalite/DataAccessor.h"

#include "gtest/gtest.h"
using namespace std;
using namespace wasp;

/**
 * @brief TEST data accessor with default data store
 */
TEST( Halite, data_accessor_store)
{
    DataAccessor a;
    ASSERT_TRUE( a.store("i",10) );
    ASSERT_EQ( Context::Type::INTEGER, a.type("i") );
    ASSERT_EQ( 10, a.integer("i") );

    ASSERT_TRUE( a.store("d",10.012) );
    ASSERT_EQ( Context::Type::REAL, a.type("d") );
    ASSERT_EQ( 10.012, a.real("d") );

    ASSERT_TRUE( a.store("b",true) );
    ASSERT_EQ( Context::Type::BOOLEAN, a.type("b") );
    ASSERT_TRUE( a.boolean("b") );

    // must wrap raw char* in std::string() to disambiguate implicit bool conversion
    ASSERT_TRUE( a.store("s",std::string("10aC")) );
    ASSERT_EQ( Context::Type::STRING, a.type("s") );
    ASSERT_EQ( "10aC", a.string("s") );
}

TEST( Halite, data_accessor_store_object)
{
    DataObject o;
    DataAccessor a(&o);
    ASSERT_TRUE( a.store("i",10) );
    ASSERT_EQ( Context::Type::INTEGER, a.type("i") );
    ASSERT_EQ( 10, a.integer("i") );

    ASSERT_TRUE( a.store("d",10.012) );
    ASSERT_EQ( Context::Type::REAL, a.type("d") );
    ASSERT_EQ( 10.012, a.real("d") );

    ASSERT_TRUE( a.store("b",true) );
    ASSERT_EQ( Context::Type::BOOLEAN, a.type("b") );
    ASSERT_TRUE( a.boolean("b") );

    // must wrap raw char* in std::string() to disambiguate implicit bool conversion
    ASSERT_TRUE( a.store("s",std::string("10aC")) );
    ASSERT_EQ( Context::Type::STRING, a.type("s") );
    ASSERT_EQ( "10aC", a.string("s") );
}


TEST( Halite, data_accessor_dataobject_backed)
{
    DataObject o;
    DataAccessor a(&o);
    ASSERT_TRUE( a.store("i",10) );
    ASSERT_EQ( Context::Type::INTEGER, a.type("i") );
    ASSERT_EQ( 10, a.integer("i") );

    ASSERT_TRUE( a.store("d",10.012) );
    ASSERT_EQ( Context::Type::REAL, a.type("d") );
    ASSERT_EQ( 10.012, a.real("d") );

    ASSERT_TRUE( a.store("b",true) );
    ASSERT_EQ( Context::Type::BOOLEAN, a.type("b") );
    ASSERT_TRUE( a.boolean("b") );

    // must wrap raw char* in std::string() to disambiguate implicit bool conversion
    ASSERT_TRUE( a.store("s",std::string("10aC")) );
    ASSERT_EQ( Context::Type::STRING, a.type("s") );
    ASSERT_EQ( "10aC", a.string("s") );

    o["i1"] = 11;
    o["d1"] = 10.014;
    o["b1"] = false;
    o["s1"] = "ten a C";


    ASSERT_EQ( Context::Type::UNDEFINED, a.type("undefined"));

    ASSERT_EQ( Context::Type::INTEGER, a.type("i1") );
    ASSERT_EQ( 11, a.integer("i1") );

    ASSERT_EQ( Context::Type::REAL, a.type("d1") );
    ASSERT_EQ( 10.014, a.real("d1") );

    ASSERT_EQ( Context::Type::BOOLEAN, a.type("b1") );
    ASSERT_FALSE( a.boolean("b1") );

    ASSERT_EQ( Context::Type::STRING, a.type("s1") );
    ASSERT_EQ( "ten a C", a.string("s1") );
}
