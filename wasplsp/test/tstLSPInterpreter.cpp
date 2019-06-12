#include "wasplsp/LSPInterpreter.h"
#include "wasplsp/WaspServer.h"
#include "waspson/SONInterpreter.h"
#include "waspson/SONNodeView.h"
#include "wasphive/HIVE.h"
#include "wasplsp/ThreadConnection.h"
#include "wasplsp/test/Paths.h"
#include "gtest/gtest.h"
#include <sstream>
#include <string>

namespace wasp {
namespace lsp  {

TEST(LSP, wasp_server_son)
{
    std::stringstream input;

    input << R"INPUT(

object
{
   key  = 19.6
   key  = 12.6
   list = [ 9 -2 -9 5 009 8 ]
   use  = -09
}

object
{
   key  = -4.6
   list = [ 5 6 7
   use  = 6
}

)INPUT";

    std::shared_ptr<HIVE> validator = std::make_shared<HIVE>();

    std::shared_ptr<DefaultSONInterpreter> schema =
            std::make_shared<DefaultSONInterpreter>();

    ASSERT_TRUE ( schema->parseFile( TEST_SCHEMA_DIR + "/schema.sch" ) );

    std::string template_dir = TEST_TMPL_DIR;

    WaspServer< DefaultSONInterpreter ,
                SONNodeView           ,
                DefaultSONInterpreter ,
                SONNodeView           ,
                HIVE                  ,
                ThreadConnection      > server;

    ASSERT_TRUE ( server.setup( validator , schema , template_dir ) );

    std::stringstream parse_errors;

    parse_errors << std::endl;

    DefaultLSPInterpreter lsp_interpreter( parse_errors );

    ASSERT_TRUE ( lsp_interpreter.setupServer( &server ) );

    ASSERT_FALSE( lsp_interpreter.parse( input ) );

    std::string expected_errors = R"INPUT(
 line: 16 column: 1 - syntax error, unexpected }
 line: 3 column: 1 - Validation Error: document has 1 "object" occurrences - when there should be a minimum occurrence of 3
 line: 3 column: 1 - Validation Error: object has 2 "key" occurrences - when there should be a maximum occurrence of 1
 line: 7 column: 4 - Validation Error: list has 6 "value" occurrences - when there should be a maximum occurrence of 5
 line: 7 column: 15 - Validation Error: list value "-2" is less than the allowed minimum inclusive value of 0
 line: 7 column: 18 - Validation Error: list value "-9" is less than the allowed minimum inclusive value of 0
)INPUT";

    ASSERT_EQ   ( expected_errors, parse_errors.str() );
}

} // namespace lsp
} // namespace wasp
