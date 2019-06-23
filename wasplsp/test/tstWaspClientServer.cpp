#include "wasplsp/WaspServer.h"
#include "wasplsp/Server.h"
#include "wasplsp/ServerImpl.h"
#include "wasplsp/Client.h"
#include "wasplsp/ClientImpl.h"
#include "wasplsp/LSP.h"
#include "wasplsp/Connection.h"
#include "wasplsp/ThreadConnection.h"
#include "wasplsp/SymbolIterator.h"
#include "wasplsp/test/Paths.h"
#include "waspson/SONInterpreter.h"
#include "waspson/SONNodeView.h"
#include "wasphive/HIVE.h"
#include "gtest/gtest.h"
#include <thread>
#include <vector>
#include <sstream>
#include <memory>

namespace wasp {
namespace lsp  {

// handles for client, server, and server thread

Client<ClientImpl> client;
std::thread server_thread;
Server<WaspServer< DefaultSONInterpreter ,
                   SONNodeView           ,
                   DefaultSONInterpreter ,
                   SONNodeView           ,
                   HIVE                  ,
                   ThreadConnection      > > wasp_server;

TEST(client, launch_server_thread_and_connnect_client)
{
    // launch server thread and connect test client to server's communication

    std::shared_ptr<DefaultSONInterpreter> schema =
            std::make_shared<DefaultSONInterpreter>();

    ASSERT_TRUE( schema->parseFile( TEST_SCHEMA_DIR + "/schema.sch" ) );

    std::shared_ptr<HIVE> validator = std::make_shared<HIVE>();

    std::string template_dir = TEST_TMPL_DIR;

    ASSERT_TRUE ( wasp_server.getImpl()->setup( validator    ,
                                                schema       ,
                                                template_dir ) );

    server_thread = std::thread
    (
        &Server<WaspServer< DefaultSONInterpreter ,
                            SONNodeView           ,
                            DefaultSONInterpreter ,
                            SONNodeView           ,
                            HIVE                  ,
                            ThreadConnection      > >::run ,
        &wasp_server
    );

    ASSERT_FALSE( client.isConnected() );

    ASSERT_TRUE ( client.connect( wasp_server.getConnection() ) );

    ASSERT_TRUE ( client.isConnected() );
}

TEST(client, initialize)
{
    // initialize

    ASSERT_FALSE( client.getConnection()->isServerRunning() );

    ASSERT_TRUE ( client.doInitialize() );

    ASSERT_TRUE ( client.getConnection()->isServerRunning() );

    ASSERT_TRUE ( client.getConnection()->getServerErrors().empty() );

    ASSERT_TRUE ( client.getErrors().empty() );
}

TEST(client, initialized)
{
    // initialized

    ASSERT_TRUE ( client.doInitialized() );

    ASSERT_TRUE ( client.getConnection()->getServerErrors().empty() );

    ASSERT_TRUE ( client.getErrors().empty() );
}

TEST(client, document_open_and_diagnostics)
{
    // document open

    std::string document_path        = "test/document/uri/string";
    std::string document_language_id = "test-document-language-id";
    std::string document_text = R"INPUT(

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

    ASSERT_FALSE( client.isDocumentOpen() );

    ASSERT_TRUE ( client.doDocumentOpen( document_path        ,
                                         document_language_id ,
                                         document_text        ) );

    ASSERT_TRUE ( client.isDocumentOpen() );

    ASSERT_EQ   ( 1 , client.getCurrentDocumentVersion() );

    ASSERT_TRUE ( client.getConnection()->getServerErrors().empty() );

    ASSERT_TRUE ( client.getErrors().empty() );

    // diagnostic responses

    ASSERT_EQ   ( 6 , client.getDiagnosticSize() );

    for (int index = 0; index < client.getDiagnosticSize(); index++)
    {
        int         start_line;
        int         start_character;
        int         end_line;
        int         end_character;
        int         severity;
        std::string code;
        std::string source;
        std::string message;

        ASSERT_TRUE ( client.getDiagnosticAt( index           ,
                                              start_line      ,
                                              start_character ,
                                              end_line        ,
                                              end_character   ,
                                              severity        ,
                                              code            ,
                                              source          ,
                                              message         ) );
        if ( index == 0 )
        {
            ASSERT_EQ ( 15       , start_line      );
            ASSERT_EQ ( 00       , start_character );
            ASSERT_EQ ( 15       , end_line        );
            ASSERT_EQ ( 00       , end_character   );
            ASSERT_EQ ( 01       , severity        );
            ASSERT_EQ ( "parse"  , code            );
            ASSERT_EQ ( "parser" , source          );
            ASSERT_EQ ( "syntax error, unexpected }" , message         );
        }
        else if ( index == 1 )
        {
            ASSERT_EQ ( 02          , start_line      );
            ASSERT_EQ ( 00          , start_character );
            ASSERT_EQ ( 02          , end_line        );
            ASSERT_EQ ( 00          , end_character   );
            ASSERT_EQ ( 01          , severity        );
            ASSERT_EQ ( "validate"  , code            );
            ASSERT_EQ ( "validator" , source          );
            ASSERT_EQ ( "Validation Error: document has 1 \"object\" occurrences - when there should be a minimum occurrence of 3" , message         );
        }
        else if ( index == 2 )
        {
            ASSERT_EQ ( 02          , start_line      );
            ASSERT_EQ ( 00          , start_character );
            ASSERT_EQ ( 02          , end_line        );
            ASSERT_EQ ( 00          , end_character   );
            ASSERT_EQ ( 01          , severity        );
            ASSERT_EQ ( "validate"  , code            );
            ASSERT_EQ ( "validator" , source          );
            ASSERT_EQ ( "Validation Error: object has 2 \"key\" occurrences - when there should be a maximum occurrence of 1" , message         );
        }
        else if ( index == 3 )
        {
            ASSERT_EQ ( 06          , start_line      );
            ASSERT_EQ ( 04          , start_character );
            ASSERT_EQ ( 06          , end_line        );
            ASSERT_EQ ( 04          , end_character   );
            ASSERT_EQ ( 01          , severity        );
            ASSERT_EQ ( "validate"  , code            );
            ASSERT_EQ ( "validator" , source          );
            ASSERT_EQ ( "Validation Error: list has 6 \"value\" occurrences - when there should be a maximum occurrence of 5" , message         );
        }
        else if ( index == 4 )
        {
            ASSERT_EQ ( 06          , start_line      );
            ASSERT_EQ ( 15          , start_character );
            ASSERT_EQ ( 06          , end_line        );
            ASSERT_EQ ( 15          , end_character   );
            ASSERT_EQ ( 01          , severity        );
            ASSERT_EQ ( "validate"  , code            );
            ASSERT_EQ ( "validator" , source          );
            ASSERT_EQ ( "Validation Error: list value \"-2\" is less than the allowed minimum inclusive value of 0" , message         );
        }
        else if ( index == 5 )
        {
            ASSERT_EQ ( 06          , start_line      );
            ASSERT_EQ ( 18          , start_character );
            ASSERT_EQ ( 06          , end_line        );
            ASSERT_EQ ( 18          , end_character   );
            ASSERT_EQ ( 01          , severity        );
            ASSERT_EQ ( "validate"  , code            );
            ASSERT_EQ ( "validator" , source          );
            ASSERT_EQ ( "Validation Error: list value \"-9\" is less than the allowed minimum inclusive value of 0" , message         );
        }
    }
}

TEST(client, document_change_and_diagnostics)
{
    // document change

    int         start_line        = -1;
    int         start_character   = -1;
    int         end_line          = -1;
    int         end_character     = -1;
    int         range_length      = -1;
    std::string new_document_text = R"INPUT(

object
{
    key  = 19.6
    list = [ 9 -2 -9 5 009 ]
    use  = -09
}

object
{
    key  = -4.6
    list = [ 5 6 7 ]
    use  = 6
    food = red
}

)INPUT";

    ASSERT_EQ   ( 1 , client.getCurrentDocumentVersion() );

    ASSERT_TRUE ( client.doDocumentChange( start_line        ,
                                           start_character   ,
                                           end_line          ,
                                           end_character     ,
                                           range_length      ,
                                           new_document_text ) );

    ASSERT_EQ   ( 2 , client.getCurrentDocumentVersion() );

    ASSERT_TRUE ( client.getConnection()->getServerErrors().empty() );

    ASSERT_TRUE ( client.getErrors().empty() );

    // diagnostic responses

    ASSERT_EQ   ( 5 , client.getDiagnosticSize() );

    for (int index = 0; index < client.getDiagnosticSize(); index++)
    {
        int         start_line;
        int         start_character;
        int         end_line;
        int         end_character;
        int         severity;
        std::string code;
        std::string source;
        std::string message;

        ASSERT_TRUE ( client.getDiagnosticAt( index           ,
                                              start_line      ,
                                              start_character ,
                                              end_line        ,
                                              end_character   ,
                                              severity        ,
                                              code            ,
                                              source          ,
                                              message         ) );
        if ( index == 0 )
        {
            ASSERT_EQ ( 02          , start_line      );
            ASSERT_EQ ( 00          , start_character );
            ASSERT_EQ ( 02          , end_line        );
            ASSERT_EQ ( 00          , end_character   );
            ASSERT_EQ ( 01          , severity        );
            ASSERT_EQ ( "validate"  , code            );
            ASSERT_EQ ( "validator" , source          );
            ASSERT_EQ ( "Validation Error: document has 2 \"object\" occurrences - when there should be a minimum occurrence of 3" , message         );
        }
        else if ( index == 1 )
        {
            ASSERT_EQ ( 05          , start_line      );
            ASSERT_EQ ( 15          , start_character );
            ASSERT_EQ ( 05          , end_line        );
            ASSERT_EQ ( 15          , end_character   );
            ASSERT_EQ ( 01          , severity        );
            ASSERT_EQ ( "validate"  , code            );
            ASSERT_EQ ( "validator" , source          );
            ASSERT_EQ ( "Validation Error: list value \"-2\" is less than the allowed minimum inclusive value of 0" , message         );
        }
        else if ( index == 2 )
        {
            ASSERT_EQ ( 05          , start_line      );
            ASSERT_EQ ( 18          , start_character );
            ASSERT_EQ ( 05          , end_line        );
            ASSERT_EQ ( 18          , end_character   );
            ASSERT_EQ ( 01          , severity        );
            ASSERT_EQ ( "validate"  , code            );
            ASSERT_EQ ( "validator" , source          );
            ASSERT_EQ ( "Validation Error: list value \"-9\" is less than the allowed minimum inclusive value of 0" , message         );
        }
        else if ( index == 3 )
        {
            ASSERT_EQ ( 11          , start_line      );
            ASSERT_EQ ( 11          , start_character );
            ASSERT_EQ ( 11          , end_line        );
            ASSERT_EQ ( 11          , end_character   );
            ASSERT_EQ ( 01          , severity        );
            ASSERT_EQ ( "validate"  , code            );
            ASSERT_EQ ( "validator" , source          );
            ASSERT_EQ ( "Validation Error: key value \"-4.6\" is less than the allowed minimum inclusive value of 0" , message         );
        }
        else if ( index == 4 )
        {
            ASSERT_EQ ( 14          , start_line      );
            ASSERT_EQ ( 04          , start_character );
            ASSERT_EQ ( 14          , end_line        );
            ASSERT_EQ ( 04          , end_character   );
            ASSERT_EQ ( 01          , severity        );
            ASSERT_EQ ( "validate"  , code            );
            ASSERT_EQ ( "validator" , source          );
            ASSERT_EQ ( "Validation Error: food value \"red\" is not one of the allowed values: [ \"apple\" \"kiwi\" \"orange\" \"potato\" \"tomato\" ]" , message         );
        }
    }
}

TEST(client, document_symbols_and_responses)
{
    // document symbols

    ASSERT_TRUE ( client.doDocumentSymbols() );

    ASSERT_TRUE ( client.getConnection()->getServerErrors().empty() );

    ASSERT_TRUE ( client.getErrors().empty() );

    // symbols responses

    SymbolIterator::SP si = client.getSymbolIterator();

    std::stringstream paths;

    paths << std::endl;

    for( std::vector<int> indices{ 0 } ; indices.back() < (int) si->getChildSize() ; indices.back()++ )
    {
        si->moveToChildAt( indices.back() );

        indices.push_back( -1 );

        paths << si->getPath() << std::endl;

        if ( si->getChildSize() == 0 )
        {
            while ( indices.back()+1 == (int) si->getChildSize() && si->moveToParent() )
            {
                indices.pop_back();
            }
        }
    }

    std::stringstream expected_paths;
    expected_paths << R"INPUT(
/object (3:1)
/object/key (5:5)
/object/key/value (5:12)
/object/list (6:5)
/object/list/value (6:14)
/object/list/value (6:16)
/object/list/value (6:19)
/object/list/value (6:22)
/object/list/value (6:24)
/object/use (7:5)
/object/use/value (7:12)
/object (10:1)
/object/key (12:5)
/object/key/value (12:12)
/object/list (13:5)
/object/list/value (13:14)
/object/list/value (13:16)
/object/list/value (13:18)
/object/use (14:5)
/object/use/value (14:12)
/object/food (15:5)
/object/food/value (15:12)
)INPUT";

    ASSERT_EQ ( expected_paths.str() , paths.str() );
}

TEST(client, document_completion_existsin)
{
    // document completion

    int line       = 07;
    int character  = 12;

    ASSERT_TRUE ( client.doDocumentCompletion( line     ,
                                               character) );

    ASSERT_TRUE ( client.getConnection()->getServerErrors().empty() );

    ASSERT_TRUE ( client.getErrors().empty() );

    // completion responses

    ASSERT_EQ   ( 5 , client.getCompletionSize() );

    for (int index = 0; index < client.getCompletionSize(); index++)
    {
        std::string label;
        int         start_line;
        int         start_character;
        int         end_line;
        int         end_character;
        std::string new_text;
        int         kind;
        std::string detail;
        std::string documentation;
        bool        deprecated;
        bool        preselect;

        ASSERT_TRUE ( client.getCompletionAt( index           ,
                                              label           ,
                                              start_line      ,
                                              start_character ,
                                              end_line        ,
                                              end_character   ,
                                              new_text        ,
                                              kind            ,
                                              detail          ,
                                              documentation   ,
                                              deprecated      ,
                                              preselect       ) );
        if ( index == 0 )
        {
            ASSERT_EQ ( "-2"       , label           );
            ASSERT_EQ ( 07         , start_line      );
            ASSERT_EQ ( 12         , start_character );
            ASSERT_EQ ( 07         , end_line        );
            ASSERT_EQ ( 12         , end_character   );
            ASSERT_EQ ( "-2"       , new_text        );
            ASSERT_EQ ( 1          , kind            );
            ASSERT_EQ ( "existsin" , detail          );
            ASSERT_EQ ( "-2"       , documentation   );
            ASSERT_EQ ( false      , deprecated      );
            ASSERT_EQ ( false      , preselect       );
        }
        if ( index == 1 )
        {
            ASSERT_EQ ( "-9"       , label           );
            ASSERT_EQ ( 07         , start_line      );
            ASSERT_EQ ( 12         , start_character );
            ASSERT_EQ ( 07         , end_line        );
            ASSERT_EQ ( 12         , end_character   );
            ASSERT_EQ ( "-9"       , new_text        );
            ASSERT_EQ ( 1          , kind            );
            ASSERT_EQ ( "existsin" , detail          );
            ASSERT_EQ ( "-9"       , documentation   );
            ASSERT_EQ ( false      , deprecated      );
            ASSERT_EQ ( false      , preselect       );
        }
        if ( index == 2 )
        {
            ASSERT_EQ ( "009"      , label           );
            ASSERT_EQ ( 07         , start_line      );
            ASSERT_EQ ( 12         , start_character );
            ASSERT_EQ ( 07         , end_line        );
            ASSERT_EQ ( 12         , end_character   );
            ASSERT_EQ ( "009"      , new_text        );
            ASSERT_EQ ( 1          , kind            );
            ASSERT_EQ ( "existsin" , detail          );
            ASSERT_EQ ( "009"      , documentation   );
            ASSERT_EQ ( false      , deprecated      );
            ASSERT_EQ ( false      , preselect       );
        }
        if ( index == 3 )
        {
            ASSERT_EQ ( "5"        , label           );
            ASSERT_EQ ( 07         , start_line      );
            ASSERT_EQ ( 12         , start_character );
            ASSERT_EQ ( 07         , end_line        );
            ASSERT_EQ ( 12         , end_character   );
            ASSERT_EQ ( "5"        , new_text        );
            ASSERT_EQ ( 1          , kind            );
            ASSERT_EQ ( "existsin" , detail          );
            ASSERT_EQ ( "5"        , documentation   );
            ASSERT_EQ ( false      , deprecated      );
            ASSERT_EQ ( false      , preselect       );
        }
        if ( index == 4 )
        {
            ASSERT_EQ ( "9"        , label           );
            ASSERT_EQ ( 07         , start_line      );
            ASSERT_EQ ( 12         , start_character );
            ASSERT_EQ ( 07         , end_line        );
            ASSERT_EQ ( 12         , end_character   );
            ASSERT_EQ ( "9"        , new_text        );
            ASSERT_EQ ( 1          , kind            );
            ASSERT_EQ ( "existsin" , detail          );
            ASSERT_EQ ( "9"        , documentation   );
            ASSERT_EQ ( false      , deprecated      );
            ASSERT_EQ ( false      , preselect       );
        }
    }
}

TEST(client, document_completion_valenums)
{
    // document completion

    int line       = 15;
    int character  = 12;

    ASSERT_TRUE ( client.doDocumentCompletion( line     ,
                                               character) );

    ASSERT_TRUE ( client.getConnection()->getServerErrors().empty() );

    ASSERT_TRUE ( client.getErrors().empty() );

    // completion responses

    ASSERT_EQ   ( 5 , client.getCompletionSize() );

    for (int index = 0; index < client.getCompletionSize(); index++)
    {
        std::string label;
        int         start_line;
        int         start_character;
        int         end_line;
        int         end_character;
        std::string new_text;
        int         kind;
        std::string detail;
        std::string documentation;
        bool        deprecated;
        bool        preselect;

        ASSERT_TRUE ( client.getCompletionAt( index           ,
                                              label           ,
                                              start_line      ,
                                              start_character ,
                                              end_line        ,
                                              end_character   ,
                                              new_text        ,
                                              kind            ,
                                              detail          ,
                                              documentation   ,
                                              deprecated      ,
                                              preselect       ) );
        if ( index == 0 )
        {
            ASSERT_EQ ( "apple"    , label           );
            ASSERT_EQ ( 15         , start_line      );
            ASSERT_EQ ( 12         , start_character );
            ASSERT_EQ ( 15         , end_line        );
            ASSERT_EQ ( 12         , end_character   );
            ASSERT_EQ ( "apple"    , new_text        );
            ASSERT_EQ ( 1          , kind            );
            ASSERT_EQ ( "valenums" , detail          );
            ASSERT_EQ ( "apple"    , documentation   );
            ASSERT_EQ ( false      , deprecated      );
            ASSERT_EQ ( false      , preselect       );
        }
        if ( index == 1 )
        {
            ASSERT_EQ ( "orange"   , label           );
            ASSERT_EQ ( 15         , start_line      );
            ASSERT_EQ ( 12         , start_character );
            ASSERT_EQ ( 15         , end_line        );
            ASSERT_EQ ( 12         , end_character   );
            ASSERT_EQ ( "orange"   , new_text        );
            ASSERT_EQ ( 1          , kind            );
            ASSERT_EQ ( "valenums" , detail          );
            ASSERT_EQ ( "orange"   , documentation   );
            ASSERT_EQ ( false      , deprecated      );
            ASSERT_EQ ( false      , preselect       );
        }
        if ( index == 2 )
        {
            ASSERT_EQ ( "kiwi"     , label           );
            ASSERT_EQ ( 15         , start_line      );
            ASSERT_EQ ( 12         , start_character );
            ASSERT_EQ ( 15         , end_line        );
            ASSERT_EQ ( 12         , end_character   );
            ASSERT_EQ ( "kiwi"     , new_text        );
            ASSERT_EQ ( 1          , kind            );
            ASSERT_EQ ( "valenums" , detail          );
            ASSERT_EQ ( "kiwi"     , documentation   );
            ASSERT_EQ ( false      , deprecated      );
            ASSERT_EQ ( false      , preselect       );
        }
        if ( index == 3 )
        {
            ASSERT_EQ ( "potato"   , label           );
            ASSERT_EQ ( 15         , start_line      );
            ASSERT_EQ ( 12         , start_character );
            ASSERT_EQ ( 15         , end_line        );
            ASSERT_EQ ( 12         , end_character   );
            ASSERT_EQ ( "potato"   , new_text        );
            ASSERT_EQ ( 1          , kind            );
            ASSERT_EQ ( "valenums" , detail          );
            ASSERT_EQ ( "potato"   , documentation   );
            ASSERT_EQ ( false      , deprecated      );
            ASSERT_EQ ( false      , preselect       );
        }
        if ( index == 4 )
        {
            ASSERT_EQ ( "tomato"   , label           );
            ASSERT_EQ ( 15         , start_line      );
            ASSERT_EQ ( 12         , start_character );
            ASSERT_EQ ( 15         , end_line        );
            ASSERT_EQ ( 12         , end_character   );
            ASSERT_EQ ( "tomato"   , new_text        );
            ASSERT_EQ ( 1          , kind            );
            ASSERT_EQ ( "valenums" , detail          );
            ASSERT_EQ ( "tomato"   , documentation   );
            ASSERT_EQ ( false      , deprecated      );
            ASSERT_EQ ( false      , preselect       );
        }
    }
}

TEST(client, document_completion_templates)
{
    // document completion

    int line       = 2;
    int character  = 1;

    ASSERT_TRUE ( client.doDocumentCompletion( line     ,
                                               character) );

    ASSERT_TRUE ( client.getConnection()->getServerErrors().empty() );

    ASSERT_TRUE ( client.getErrors().empty() );

    // completion responses

    ASSERT_EQ   ( 5 , client.getCompletionSize() );

    for (int index = 0; index < client.getCompletionSize(); index++)
    {
        std::string label;
        int         start_line;
        int         start_character;
        int         end_line;
        int         end_character;
        std::string new_text;
        int         kind;
        std::string detail;
        std::string documentation;
        bool        deprecated;
        bool        preselect;

        ASSERT_TRUE ( client.getCompletionAt( index           ,
                                              label           ,
                                              start_line      ,
                                              start_character ,
                                              end_line        ,
                                              end_character   ,
                                              new_text        ,
                                              kind            ,
                                              detail          ,
                                              documentation   ,
                                              deprecated      ,
                                              preselect       ) );
        if ( index == 0 )
        {
            ASSERT_EQ ( "key_string"                            , label           );
            ASSERT_EQ ( line                                    , start_line      );
            ASSERT_EQ ( character                               , start_character );
            ASSERT_EQ ( line                                    , end_line        );
            ASSERT_EQ ( character                               , end_character   );
            ASSERT_EQ ( "key_string = \"insert_string_here\"\n" , new_text        );
            ASSERT_EQ ( 1                                       , kind            );
            ASSERT_EQ ( "inputtmpl"                             , detail          );
            ASSERT_EQ ( "Key_string description here for test"  , documentation   );
            ASSERT_EQ ( false                                   , deprecated      );
            ASSERT_EQ ( false                                   , preselect       );
        }
        if ( index == 1 )
        {
            ASSERT_EQ ( "array_overwrite"                     , label           );
            ASSERT_EQ ( line                                  , start_line      );
            ASSERT_EQ ( character                             , start_character );
            ASSERT_EQ ( line                                  , end_line        );
            ASSERT_EQ ( character                             , end_character   );
            ASSERT_EQ ( "array_overwrite = [ 9.9 9.9 9.9 ]\n" , new_text        );
            ASSERT_EQ ( 1                                     , kind            );
            ASSERT_EQ ( "inputtmpl"                           , detail          );
            ASSERT_EQ ( "Key_list description here for test"  , documentation   );
            ASSERT_EQ ( false                                 , deprecated      );
            ASSERT_EQ ( false                                 , preselect       );
        }
        if ( index == 2 )
        {
            ASSERT_EQ ( "object - variant 1"               , label           );
            ASSERT_EQ ( line                               , start_line      );
            ASSERT_EQ ( character                          , start_character );
            ASSERT_EQ ( line                               , end_line        );
            ASSERT_EQ ( character                          , end_character   );
            ASSERT_EQ ( "object\n{\n    key  =   1.0\n    list = [ 11 12 13 14 15 ]\n    use  =   11\n}\n" , new_text        );
            ASSERT_EQ ( 1                                  , kind            );
            ASSERT_EQ ( "inputvariants"                    , detail          );
            ASSERT_EQ ( "Object description here For test" , documentation   );
            ASSERT_EQ ( false                              , deprecated      );
            ASSERT_EQ ( false                              , preselect       );
        }
        if ( index == 3 )
        {
            ASSERT_EQ ( "object - variant 2"               , label           );
            ASSERT_EQ ( line                               , start_line      );
            ASSERT_EQ ( character                          , start_character );
            ASSERT_EQ ( line                               , end_line        );
            ASSERT_EQ ( character                          , end_character   );
            ASSERT_EQ ( "object\n{\n    key  =   2.0\n    list = [ 21 22 23 24 25 ]\n    use  =   21\n}\n" ,new_text        );
            ASSERT_EQ ( 1                                  , kind            );
            ASSERT_EQ ( "inputvariants"                    , detail          );
            ASSERT_EQ ( "Object description here For test" , documentation   );
            ASSERT_EQ ( false                              , deprecated      );
            ASSERT_EQ ( false                              , preselect       );
        }
        if ( index == 4 )
        {
            ASSERT_EQ ( "object - variant 3"               , label           );
            ASSERT_EQ ( line                               , start_line      );
            ASSERT_EQ ( character                          , start_character );
            ASSERT_EQ ( line                               , end_line        );
            ASSERT_EQ ( character                          , end_character   );
            ASSERT_EQ ( "object\n{\n    key  =   3.0\n    list = [ 31 32 33 34 35 ]\n    use  =   31\n}\n" , new_text        );
            ASSERT_EQ ( 1                                  , kind            );
            ASSERT_EQ ( "inputvariants"                    , detail          );
            ASSERT_EQ ( "Object description here For test" , documentation   );
            ASSERT_EQ ( false                              , deprecated      );
            ASSERT_EQ ( false                              , preselect       );
        }
    }
}

TEST(client, document_definition)
{
    // document definition

    int line       = 07;
    int character  = 12;

    ASSERT_TRUE ( client.doDocumentDefinition( line     ,
                                               character) );

    ASSERT_TRUE ( client.getConnection()->getServerErrors().empty() );

    ASSERT_TRUE ( client.getErrors().empty() );

    // definition responses

    ASSERT_EQ   ( 3 , client.getDefinitionSize() );

    for (int index = 0; index < client.getDefinitionSize(); index++)
    {
        int         start_line;
        int         start_character;
        int         end_line;
        int         end_character;

        ASSERT_TRUE ( client.getDefinitionAt( index           ,
                                              start_line      ,
                                              start_character ,
                                              end_line        ,
                                              end_character   ) );
        if ( index == 0 )
        {
            ASSERT_EQ ( 06 , start_line      );
            ASSERT_EQ ( 14 , start_character );
            ASSERT_EQ ( 06 , end_line        );
            ASSERT_EQ ( 14 , end_character   );
        }
        else if ( index == 1 )
        {
            ASSERT_EQ ( 06 , start_line      );
            ASSERT_EQ ( 19 , start_character );
            ASSERT_EQ ( 06 , end_line        );
            ASSERT_EQ ( 20 , end_character   );
        }
        else if ( index == 2 )
        {
            ASSERT_EQ ( 06 , start_line      );
            ASSERT_EQ ( 24 , start_character );
            ASSERT_EQ ( 06 , end_line        );
            ASSERT_EQ ( 26 , end_character   );
        }
    }
}

TEST(client, document_close)
{
    // document close

    ASSERT_TRUE ( client.isDocumentOpen() );

    ASSERT_TRUE ( client.doDocumentClose() );

    ASSERT_FALSE( client.isDocumentOpen() );

    ASSERT_TRUE ( client.getErrors().empty() );

    ASSERT_TRUE ( client.getConnection()->getServerErrors().empty() );
}

TEST(client, shutdown)
{
    // shutdown

    ASSERT_TRUE ( client.getConnection()->isServerRunning() );

    ASSERT_TRUE ( client.doShutdown() );

    ASSERT_FALSE( client.getConnection()->isServerRunning() );

    ASSERT_TRUE ( client.getErrors().empty() );

    ASSERT_TRUE ( client.getConnection()->getServerErrors().empty() );
}

TEST(client, exit)
{
    // exit

    ASSERT_TRUE ( client.doExit() );

    ASSERT_TRUE ( client.getErrors().empty() );

    ASSERT_TRUE ( client.getConnection()->getServerErrors().empty() );;
}

TEST(client, server_thread_join)
{
    // make sure server thread finishes execution from the exit notification

    server_thread.join();
}

} // namespace lsp
} // namespace wasp
