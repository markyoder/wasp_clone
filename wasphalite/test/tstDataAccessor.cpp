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

TEST( Halite, data_accessor_parent_access)
{
    DataObject o;
    DataAccessor a(&o);
    DataAccessor l(nullptr, &a);
    ASSERT_TRUE( a.store("i",10) );
    ASSERT_EQ( Context::Type::INTEGER, l.type("i") );
    ASSERT_EQ( 10, l.integer("i") );

    ASSERT_TRUE( a.store("d",10.012) );
    ASSERT_EQ( Context::Type::REAL, l.type("d") );
    ASSERT_EQ( 10.012, l.real("d") );

    ASSERT_TRUE( a.store("b",true) );
    ASSERT_EQ( Context::Type::BOOLEAN, l.type("b") );
    ASSERT_TRUE( l.boolean("b") );

    // must wrap raw char* in std::string() to disambiguate implicit bool conversion
    ASSERT_TRUE( a.store("s",std::string("10aC")) );
    ASSERT_EQ( Context::Type::STRING, l.type("s") );
    ASSERT_EQ( "10aC", l.string("s") );

    o["i1"] = 11;
    o["d1"] = 10.014;
    o["b1"] = false;
    o["s1"] = "ten a C";
    o["a"]  = DataArray();
    o["a"][0] = 2;
    o["a"][1] = 3.14;
    o["a"][2] = true;
    o["a"][3] = std::string("ted");

    ASSERT_EQ( Context::Type::UNDEFINED, l.type("undefined"));

    // access variables via child layer
    ASSERT_EQ( Context::Type::INTEGER, l.type("i1") );
    ASSERT_EQ( Context::Type::INTEGER, l.type("a",0) );
    ASSERT_EQ( 11, l.integer("i1") );
    ASSERT_EQ( 2, l.integer("a",size_t(0)) );

    ASSERT_EQ( Context::Type::REAL, l.type("d1") );
    ASSERT_EQ( Context::Type::REAL, l.type("a",1) );
    ASSERT_EQ( 10.014, l.real("d1") );
    ASSERT_EQ( 3.14, l.real("a",1) );

    ASSERT_EQ( Context::Type::BOOLEAN, l.type("b1") );
    ASSERT_EQ( Context::Type::BOOLEAN, l.type("a",2) );
    ASSERT_FALSE( l.boolean("b1") );
    ASSERT_TRUE( l.boolean("a",2) );

    ASSERT_EQ( Context::Type::STRING, l.type("s1") );
    ASSERT_EQ( Context::Type::STRING, l.type("a",3) );
    ASSERT_EQ( "ten a C", l.string("s1") );
    ASSERT_EQ( "ted", l.string("a",3) );


}
