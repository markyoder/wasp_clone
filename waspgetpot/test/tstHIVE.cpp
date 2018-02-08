#include "waspson/SONInterpreter.h"
#include "waspson/SONNodeView.h"
#include "wasphive/HIVE.h"
#include "waspcore/TreeNodePool.h"
#include "waspgetpot/GetPotInterpreter.h"
#include "waspgetpot/GetPotNodeView.h"
#include "gtest/gtest.h"
#include <string>
#include <iostream>
#include <sstream>
#include <memory>

#include "waspgetpot/test/Paths.h"

std::string test_dir = TEST_DIR_ROOT;

using namespace wasp;

struct GetPotHIVETest
{
    std::string input_fail_path;
    std::shared_ptr<std::ifstream>
                                         input_fail;  // test failing input for schema to exercise
    std::shared_ptr<GetPotInterpreter<>> input_fail_interpreter;

    std::string input_pass_path;
    std::shared_ptr<std::ifstream>
                                         input_pass;  // test passing input for schema to exercise
    std::shared_ptr<GetPotInterpreter<>> input_pass_interpreter;

    std::string                       schema_path;
    std::shared_ptr<std::ifstream>    schema;  // schema to validate input
    std::shared_ptr<SONInterpreter<>> schema_interpreter;

    std::shared_ptr<std::stringstream> output_data;  // expected output
};

bool load_file_as_string(std::ifstream&                      f,
                         std::shared_ptr<std::stringstream>& s)
{
    bool first = true;
    while (!f.eof() && f.good())
    {
        std::string line;
        std::getline(f, line);
        if (!first)
        {
            *s << std::endl;
        }
        *s << line;
        first = false;
    }
    return f.eof() && !f.bad();
}

bool load_streams(GetPotHIVETest&    t,
                  const std::string& fname,
                  const std::string& pname,
                  const std::string& oname,
                  const std::string& sname)
{
    t.input_fail_path = test_dir + "/inputs/" + fname;
    t.input_fail      = std::make_shared<std::ifstream>(t.input_fail_path);
    bool file_bad     = t.input_fail->bad() || t.input_fail->fail();
    std::cout << " -Loaded fail input :: " << t.input_fail_path << std::endl;
    EXPECT_FALSE(file_bad);

    t.input_pass_path = test_dir + "/inputs/" + pname;
    t.input_pass      = std::make_shared<std::ifstream>(t.input_pass_path);
    file_bad          = t.input_pass->bad() || t.input_pass->fail();
    std::cout << " -Loaded pass input :: " << t.input_pass_path << std::endl;
    EXPECT_FALSE(file_bad);

    {
        std::string output_path = test_dir + "/outputs/" + oname;
        SCOPED_TRACE(output_path);
        std::ifstream output_file(output_path);
        t.output_data = std::make_shared<std::stringstream>();
        EXPECT_TRUE(load_file_as_string(output_file, t.output_data));
        file_bad = t.output_data->bad() || t.output_data->fail();
        std::cout << " -Loaded output (gold) :: " << output_path << std::endl;
        EXPECT_FALSE(file_bad);
    }
    t.schema_path = test_dir + "/schemas/" + sname;
    t.schema      = std::make_shared<std::ifstream>(t.schema_path);
    file_bad      = t.schema->bad() || t.schema->fail();
    std::cout << " -Loaded schema :: " << t.schema_path << std::endl;
    EXPECT_FALSE(file_bad);
    return !file_bad;
}
// load abstract syntax trees (dom)
bool load_ast(GetPotHIVETest& t)
{
    t.input_fail_interpreter = std::make_shared<GetPotInterpreter<>>();
    bool input_fail_good     = t.input_fail_interpreter->parse(*t.input_fail);

    EXPECT_TRUE(input_fail_good);

    t.input_pass_interpreter = std::make_shared<GetPotInterpreter<>>();
    bool input_pass_good     = t.input_pass_interpreter->parse(*t.input_pass);
    EXPECT_TRUE(input_pass_good);

    t.schema_interpreter = std::make_shared<SONInterpreter<>>();
    bool schema_good =
        t.schema_interpreter->parseStream(*t.schema, t.schema_path);
    EXPECT_TRUE(schema_good);

    return schema_good && input_fail_good && input_pass_good;
}

void do_test(const std::string& name)
{
    SCOPED_TRACE(name);
    HIVE           hive;
    GetPotHIVETest t;
    ASSERT_TRUE(load_streams(t, name + ".fail.gp", name + ".pass.gp",
                             name + ".fail.gld", name + ".sch"));
    ASSERT_TRUE(load_ast(t));
    std::vector<std::string>                            errors;
    SONNodeView schema_adapter = t.schema_interpreter->root();
    GetPotNodeView input_fail_adapter = t.input_fail_interpreter->root();
    GetPotNodeView input_pass_adapter = t.input_pass_interpreter->root();
    bool valid = hive.validate(schema_adapter, input_fail_adapter, errors);
    std::string msgs = HIVE::combine(errors);
    EXPECT_FALSE(valid);
    ASSERT_EQ(t.output_data->str(), msgs);
    errors.clear();
    valid = hive.validate(schema_adapter, input_pass_adapter, errors);
    msgs  = HIVE::combine(errors);
    if (!valid)
        std::cout << msgs << std::endl;
    EXPECT_TRUE(valid);
}

TEST(GetPotHIVE, MinOccurs)
{
    do_test("MinOccurs");
}
TEST(GetPotHIVE, MaxOccurs)
{
    do_test("MaxOccurs");
}

TEST(GetPotHIVE, ValEnums)
{
    do_test("ValEnums");
}

TEST(GetPotHIVE, ValType)
{
    do_test("ValType");
}
TEST(GetPotHIVE, MinValInc)
{
    do_test("MinValInc");
}
TEST(GetPotHIVE, MinValExc)
{
    do_test("MinValExc");
}
TEST(GetPotHIVE, MaxValInc)
{
    do_test("MaxValInc");
}
TEST(GetPotHIVE, MaxValExc)
{
    do_test("MaxValExc");
}
TEST(GetPotHIVE, ChildAtLeastOne)
{
    do_test("ChildAtLeastOne");
}
TEST(GetPotHIVE, ChildAtMostOne)
{
    do_test("ChildAtMostOne");
}
TEST(GetPotHIVE, ChildCountEqual)
{
    do_test("ChildCountEqual");
}
TEST(GetPotHIVE, ChildExactlyOne)
{
    do_test("ChildExactlyOne");
}
TEST(GetPotHIVE, ChildUniqueness)
{
    do_test("ChildUniqueness");
}
TEST(GetPotHIVE, DecreaseOver)
{
    do_test("DecreaseOver");
}
TEST(GetPotHIVE, ExistsIn)
{
    do_test("ExistsIn");
}
TEST(GetPotHIVE, Extras)
{
    do_test("Extras");
}
TEST(GetPotHIVE, IncreaseOver)
{
    do_test("IncreaseOver");
}
TEST(GetPotHIVE, NotExistsIn)
{
    do_test("NotExistsIn");
}
TEST(GetPotHIVE, SumOver)
{
    do_test("SumOver");
}
TEST(GetPotHIVE, SumOverGroup)
{
    do_test("SumOverGroup");
}
