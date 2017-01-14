#include "waspson/SONInterpreter.h"
#include "wasphive/HIVE.h"
#include "waspcore/TreeNodePool.h"
#include "waspson/SONNodeView.h"
#include "gtest/gtest.h"
#include <string>
#include <iostream>
#include <sstream>
#include <memory>

#include "wasphive/test/Paths.h"

std::string test_dir = TEST_DIR_ROOT;


using namespace wasp;

struct HIVETest{
    std::string input_path;
    std::shared_ptr<std::ifstream> input;  // test input for schema to exercise
    std::shared_ptr<SONInterpreter<>> input_interpreter;

    std::string schema_path;
    std::shared_ptr<std::ifstream> schema; // schema to validate input
    std::shared_ptr<SONInterpreter<>> schema_interpreter;

    std::shared_ptr<std::stringstream> output_data; // expected output
};

bool load_file_as_string(std::ifstream & f
                         ,std::shared_ptr<std::stringstream>&s)
{
    bool first = true;
    while( !f.eof() && f.good() )
    {

        std::string line;
        std::getline(f,line);
        if( !first ){ *s<<std::endl;
        }
        *s << line;
        first = false;
    }
    return f.eof() && !f.bad();
}

bool load_streams(HIVETest& t
                   , const std::string& iname
                   , const std::string& oname
                   , const std::string& sname)
{

    t.input_path = test_dir+"/inputs/"+iname;
    t.input = std::make_shared<std::ifstream>(t.input_path);
    bool file_bad = t.input->bad() || t.input->fail();
    std::cout<<" -Loaded input :: "<<t.input_path<<std::endl;
    EXPECT_FALSE( file_bad );

    {
    std::string output_path = test_dir+"/outputs/"+oname;
    SCOPED_TRACE(output_path);
    std::ifstream output_file(output_path);
    t.output_data = std::make_shared<std::stringstream>();
    EXPECT_TRUE( load_file_as_string(output_file,t.output_data) );
    file_bad = t.output_data->bad() || t.output_data->fail();
    std::cout<<" -Loaded output (gold) :: "<<output_path<<std::endl;
    EXPECT_FALSE( file_bad );
    }
    t.schema_path = test_dir+"/schemas/"+sname;
    t.schema = std::make_shared<std::ifstream>(t.schema_path);
    file_bad = t.schema->bad() || t.schema->fail();
    std::cout<<" -Loaded schema :: "<<t.schema_path<<std::endl;
    EXPECT_FALSE( file_bad );    
    return !file_bad;
}
// load abstract syntax trees (dom)
bool load_ast(HIVETest& t)
{
    t.input_interpreter = std::make_shared<SONInterpreter<>>();
    bool input_good =
            t.input_interpreter->parseStream(*t.input,t.input_path);
    EXPECT_TRUE( input_good );

    t.schema_interpreter = std::make_shared<SONInterpreter<>>();
    bool schema_good =
            t.schema_interpreter->parseStream(*t.schema
                                                ,t.schema_path);
    EXPECT_TRUE( schema_good );

    return schema_good && input_good;
}


TEST(HIVE, MinOccurs)
{
    HIVE hive;
    HIVETest t;
    ASSERT_TRUE( load_streams(t,"MinOccurs.son","MinOccurs.gld","MinOccurs.sch") );
    ASSERT_TRUE( load_ast(t) );
    std::vector<std::string> errors;
    SONNodeView<decltype(t.schema_interpreter->root())> schema_adapter = t.schema_interpreter->root();
    SONNodeView<decltype(t.input_interpreter->root())> input_adapter = t.input_interpreter->root();
    bool valid = hive.validate(schema_adapter
                             , input_adapter
                             , errors);
    std::string msgs = HIVE::combine(errors);
    EXPECT_FALSE( valid );
    ASSERT_EQ( t.output_data->str(), msgs );
}
TEST(HIVE, MaxOccurs)
{
    HIVE hive;
    HIVETest t;
    ASSERT_TRUE( load_streams(t,"MaxOccurs.son","MaxOccurs.gld","MaxOccurs.sch") );
    ASSERT_TRUE( load_ast(t) );
    std::vector<std::string> errors;
    SONNodeView<decltype(t.schema_interpreter->root())> schema_adapter = t.schema_interpreter->root();
    SONNodeView<decltype(t.input_interpreter->root())> input_adapter = t.input_interpreter->root();
    bool valid = hive.validate(schema_adapter
                             , input_adapter
                             , errors);
    std::string msgs = HIVE::combine(errors);
    EXPECT_FALSE( valid );
    ASSERT_EQ( t.output_data->str(), msgs );
}
TEST(HIVE, ValEnums)
{
    HIVE hive;
    HIVETest t;
    ASSERT_TRUE( load_streams(t,"ValEnums.son","ValEnums.gld","ValEnums.sch") );
    ASSERT_TRUE( load_ast(t) );
    std::vector<std::string> errors;
    SONNodeView<decltype(t.schema_interpreter->root())> schema_adapter = t.schema_interpreter->root();
    SONNodeView<decltype(t.input_interpreter->root())> input_adapter = t.input_interpreter->root();
    bool valid = hive.validate(schema_adapter
                             , input_adapter
                             , errors);
    std::string msgs = HIVE::combine(errors);
    EXPECT_FALSE( valid );
    ASSERT_EQ( t.output_data->str(), msgs );
}

TEST(HIVE, ValType)
{
    HIVE hive;
    HIVETest t;
    ASSERT_TRUE( load_streams(t,"ValType.son","ValType.gld","ValType.sch") );
    ASSERT_TRUE( load_ast(t) );
    std::vector<std::string> errors;
    SONNodeView<decltype(t.schema_interpreter->root())> schema_adapter = t.schema_interpreter->root();
    SONNodeView<decltype(t.input_interpreter->root())> input_adapter = t.input_interpreter->root();
    bool valid = hive.validate(schema_adapter
                             , input_adapter
                             , errors);
    std::string msgs = HIVE::combine(errors);
    EXPECT_FALSE( valid );
    ASSERT_EQ( t.output_data->str(), msgs );
}
