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
    std::shared_ptr<std::istringstream> input;  // test input for schema to exercise
    std::shared_ptr<SONInterpreter<>> input_interpreter;
    std::shared_ptr<std::istringstream> output; // expected output
    std::shared_ptr<std::istringstream> schema; // schema to validate input
    std::shared_ptr<SONInterpreter<>> schema_interpreter;
};


bool load_streams(HIVETest& t
                   , const std::string& iname
                   , const std::string& oname
                   , const std::string& sname)
{
    std::string input_path = test_dir+"/inputs/"+iname;
    t.input = std::make_shared<std::istringstream>(input_path);
    bool file_bad = t.input->bad() || t.input->fail();
    EXPECT_FALSE( file_bad );

    std::string output_path = test_dir+"/outputs/"+oname;
    t.output = std::make_shared<std::istringstream>(output_path);
    file_bad = t.output->bad() || t.output->fail();
    EXPECT_FALSE( file_bad );

    std::string schema_path = test_dir+"/schemas/"+sname;
    t.schema = std::make_shared<std::istringstream>(schema_path);
    file_bad = t.schema->bad() || t.schema->fail();
    EXPECT_FALSE( file_bad );

    return !file_bad;
}
// load abstract syntax trees (dom)
bool load_ast(HIVETest& t)
{
    t.input_interpreter = std::make_shared<SONInterpreter<>>();
    bool interpret_bad = t.input_interpreter->parse(*t.input);
    EXPECT_FALSE( interpret_bad );

    t.schema_interpreter = std::make_shared<SONInterpreter<>>();
    interpret_bad = t.schema_interpreter->parse(*t.input);
    EXPECT_FALSE( interpret_bad );

    return !interpret_bad;
}


TEST(HIVE,minoccurs)
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
    ASSERT_EQ( t.output->str(), msgs );

}
