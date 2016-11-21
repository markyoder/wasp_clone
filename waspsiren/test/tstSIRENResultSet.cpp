#include "waspsiren/SIRENResultSet.h"
#include "waspcore/TreeNodePool.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

using namespace wasp;

class FakeAdapter{
public:
    FakeAdapter(const std::string & name="fake",const std::string & data="adapter")
        :name(name),data(data){}
    FakeAdapter(const FakeAdapter & orig)
        : name(orig.name),data(orig.data),children(orig.children){}
    ~FakeAdapter(){}
    std::string name;
    std::string data;
    std::vector<FakeAdapter> children;
};

TEST( SIREN, result )
{
    SIRENResultSet<FakeAdapter> set;
    ASSERT_EQ( 0, set.result_count() );

    set.push(FakeAdapter("fake","adapter"));
    ASSERT_EQ( 1, set.result_count() );
    ASSERT_TRUE( set.is_adapted(0) );
    ASSERT_EQ("fake", set.adapted(0).name);
    ASSERT_EQ("adapter", set.adapted(0).data);

}
