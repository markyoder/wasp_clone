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

    ASSERT_EQ   ( client.getCurrentDocumentVersion() , 1 );

    ASSERT_TRUE ( client.getConnection()->getServerErrors().empty() );

    ASSERT_TRUE ( client.getErrors().empty() );

    // diagnostic responses

    ASSERT_EQ   ( client.getDiagnosticSize(), 6 );

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
            ASSERT_EQ ( start_line      , 16       );
            ASSERT_EQ ( start_character , 01       );
            ASSERT_EQ ( end_line        , 16       );
            ASSERT_EQ ( end_character   , 01       );
            ASSERT_EQ ( severity        , 01       );
            ASSERT_EQ ( code            , "parse"  );
            ASSERT_EQ ( source          , "parser" );
            ASSERT_EQ ( message         , "syntax error, unexpected }" );
        }
        else if ( index == 1 )
        {
            ASSERT_EQ ( start_line      , 03          );
            ASSERT_EQ ( start_character , 01          );
            ASSERT_EQ ( end_line        , 03          );
            ASSERT_EQ ( end_character   , 01          );
            ASSERT_EQ ( severity        , 01          );
            ASSERT_EQ ( code            , "validate"  );
            ASSERT_EQ ( source          , "validator" );
            ASSERT_EQ ( message         , "Validation Error: document has 1 \"object\" occurrences - when there should be a minimum occurrence of 3" );
        }
        else if ( index == 2 )
        {
            ASSERT_EQ ( start_line      , 03          );
            ASSERT_EQ ( start_character , 01          );
            ASSERT_EQ ( end_line        , 03          );
            ASSERT_EQ ( end_character   , 01          );
            ASSERT_EQ ( severity        , 01          );
            ASSERT_EQ ( code            , "validate"  );
            ASSERT_EQ ( source          , "validator" );
            ASSERT_EQ ( message         , "Validation Error: object has 2 \"key\" occurrences - when there should be a maximum occurrence of 1" );
        }
        else if ( index == 3 )
        {
            ASSERT_EQ ( start_line      , 07          );
            ASSERT_EQ ( start_character , 05          );
            ASSERT_EQ ( end_line        , 07          );
            ASSERT_EQ ( end_character   , 05          );
            ASSERT_EQ ( severity        , 01          );
            ASSERT_EQ ( code            , "validate"  );
            ASSERT_EQ ( source          , "validator" );
            ASSERT_EQ ( message         , "Validation Error: list has 6 \"value\" occurrences - when there should be a maximum occurrence of 5" );
        }
        else if ( index == 4 )
        {
            ASSERT_EQ ( start_line      , 07          );
            ASSERT_EQ ( start_character , 16          );
            ASSERT_EQ ( end_line        , 07          );
            ASSERT_EQ ( end_character   , 16          );
            ASSERT_EQ ( severity        , 01          );
            ASSERT_EQ ( code            , "validate"  );
            ASSERT_EQ ( source          , "validator" );
            ASSERT_EQ ( message         , "Validation Error: list value \"-2\" is less than the allowed minimum inclusive value of 0" );
        }
        else if ( index == 5 )
        {
            ASSERT_EQ ( start_line      , 07          );
            ASSERT_EQ ( start_character , 19          );
            ASSERT_EQ ( end_line        , 07          );
            ASSERT_EQ ( end_character   , 19          );
            ASSERT_EQ ( severity        , 01          );
            ASSERT_EQ ( code            , "validate"  );
            ASSERT_EQ ( source          , "validator" );
            ASSERT_EQ ( message         , "Validation Error: list value \"-9\" is less than the allowed minimum inclusive value of 0" );
        }
    }
}

TEST(client, document_change_and_diagnostics)
{
    // document change

    int         start_line        = 0;
    int         start_character   = 0;
    int         end_line          = 0;
    int         end_character     = 0;
    int         range_length      = 0;
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

    ASSERT_EQ   ( client.getCurrentDocumentVersion() , 1 );

    ASSERT_TRUE ( client.doDocumentChange( start_line        ,
                                           start_character   ,
                                           end_line          ,
                                           end_character     ,
                                           range_length      ,
                                           new_document_text ) );

    ASSERT_EQ   ( client.getCurrentDocumentVersion() , 2 );

    ASSERT_TRUE ( client.getConnection()->getServerErrors().empty() );

    ASSERT_TRUE ( client.getErrors().empty() );

    // diagnostic responses

    ASSERT_EQ   ( client.getDiagnosticSize(), 5 );

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
            ASSERT_EQ ( start_line      , 03          );
            ASSERT_EQ ( start_character , 01          );
            ASSERT_EQ ( end_line        , 03          );
            ASSERT_EQ ( end_character   , 01          );
            ASSERT_EQ ( severity        , 01          );
            ASSERT_EQ ( code            , "validate"  );
            ASSERT_EQ ( source          , "validator" );
            ASSERT_EQ ( message         , "Validation Error: document has 2 \"object\" occurrences - when there should be a minimum occurrence of 3" );
        }
        else if ( index == 1 )
        {
            ASSERT_EQ ( start_line      , 06          );
            ASSERT_EQ ( start_character , 16          );
            ASSERT_EQ ( end_line        , 06          );
            ASSERT_EQ ( end_character   , 16          );
            ASSERT_EQ ( severity        , 01          );
            ASSERT_EQ ( code            , "validate"  );
            ASSERT_EQ ( source          , "validator" );
            ASSERT_EQ ( message         , "Validation Error: list value \"-2\" is less than the allowed minimum inclusive value of 0" );
        }
        else if ( index == 2 )
        {
            ASSERT_EQ ( start_line      , 06          );
            ASSERT_EQ ( start_character , 19          );
            ASSERT_EQ ( end_line        , 06          );
            ASSERT_EQ ( end_character   , 19          );
            ASSERT_EQ ( severity        , 01          );
            ASSERT_EQ ( code            , "validate"  );
            ASSERT_EQ ( source          , "validator" );
            ASSERT_EQ ( message         , "Validation Error: list value \"-9\" is less than the allowed minimum inclusive value of 0" );
        }
        else if ( index == 3 )
        {
            ASSERT_EQ ( start_line      , 12          );
            ASSERT_EQ ( start_character , 12          );
            ASSERT_EQ ( end_line        , 12          );
            ASSERT_EQ ( end_character   , 12          );
            ASSERT_EQ ( severity        , 01          );
            ASSERT_EQ ( code            , "validate"  );
            ASSERT_EQ ( source          , "validator" );
            ASSERT_EQ ( message         , "Validation Error: key value \"-4.6\" is less than the allowed minimum inclusive value of 0" );
        }
        else if ( index == 4 )
        {
            ASSERT_EQ ( start_line      , 15          );
            ASSERT_EQ ( start_character , 5           );
            ASSERT_EQ ( end_line        , 15          );
            ASSERT_EQ ( end_character   , 5           );
            ASSERT_EQ ( severity        , 01          );
            ASSERT_EQ ( code            , "validate"  );
            ASSERT_EQ ( source          , "validator" );
            ASSERT_EQ ( message         , "Validation Error: food value \"red\" is not one of the allowed values: [ \"apple\" \"kiwi\" \"orange\" \"potato\" \"tomato\" ]" );
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

    ASSERT_EQ( paths.str() , expected_paths.str() );
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

    ASSERT_EQ   ( client.getCompletionSize(), 5 );

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
            ASSERT_EQ ( label           , "-2"       );
            ASSERT_EQ ( start_line      , 07         );
            ASSERT_EQ ( start_character , 12         );
            ASSERT_EQ ( end_line        , 07         );
            ASSERT_EQ ( end_character   , 12         );
            ASSERT_EQ ( new_text        , "-2"       );
            ASSERT_EQ ( kind            , 1          );
            ASSERT_EQ ( detail          , "existsin" );
            ASSERT_EQ ( documentation   , "-2"       );
            ASSERT_EQ ( deprecated      , false      );
            ASSERT_EQ ( preselect       , false      );
        }
        if ( index == 1 )
        {
            ASSERT_EQ ( label           , "-9"       );
            ASSERT_EQ ( start_line      , 07         );
            ASSERT_EQ ( start_character , 12         );
            ASSERT_EQ ( end_line        , 07         );
            ASSERT_EQ ( end_character   , 12         );
            ASSERT_EQ ( new_text        , "-9"       );
            ASSERT_EQ ( kind            , 1          );
            ASSERT_EQ ( detail          , "existsin" );
            ASSERT_EQ ( documentation   , "-9"       );
            ASSERT_EQ ( deprecated      , false      );
            ASSERT_EQ ( preselect       , false      );
        }
        if ( index == 2 )
        {
            ASSERT_EQ ( label           , "009"      );
            ASSERT_EQ ( start_line      , 07         );
            ASSERT_EQ ( start_character , 12         );
            ASSERT_EQ ( end_line        , 07         );
            ASSERT_EQ ( end_character   , 12         );
            ASSERT_EQ ( new_text        , "009"      );
            ASSERT_EQ ( kind            , 1          );
            ASSERT_EQ ( detail          , "existsin" );
            ASSERT_EQ ( documentation   , "009"      );
            ASSERT_EQ ( deprecated      , false      );
            ASSERT_EQ ( preselect       , false      );
        }
        if ( index == 3 )
        {
            ASSERT_EQ ( label           , "5"        );
            ASSERT_EQ ( start_line      , 07         );
            ASSERT_EQ ( start_character , 12         );
            ASSERT_EQ ( end_line        , 07         );
            ASSERT_EQ ( end_character   , 12         );
            ASSERT_EQ ( new_text        , "5"        );
            ASSERT_EQ ( kind            , 1          );
            ASSERT_EQ ( detail          , "existsin" );
            ASSERT_EQ ( documentation   , "5"        );
            ASSERT_EQ ( deprecated      , false      );
            ASSERT_EQ ( preselect       , false      );
        }
        if ( index == 4 )
        {
            ASSERT_EQ ( label           , "9"        );
            ASSERT_EQ ( start_line      , 07         );
            ASSERT_EQ ( start_character , 12         );
            ASSERT_EQ ( end_line        , 07         );
            ASSERT_EQ ( end_character   , 12         );
            ASSERT_EQ ( new_text        , "9"        );
            ASSERT_EQ ( kind            , 1          );
            ASSERT_EQ ( detail          , "existsin" );
            ASSERT_EQ ( documentation   , "9"        );
            ASSERT_EQ ( deprecated      , false      );
            ASSERT_EQ ( preselect       , false      );
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

    ASSERT_EQ   ( client.getCompletionSize(), 5 );

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
            ASSERT_EQ ( label           , "apple"    );
            ASSERT_EQ ( start_line      , 15         );
            ASSERT_EQ ( start_character , 12         );
            ASSERT_EQ ( end_line        , 15         );
            ASSERT_EQ ( end_character   , 12         );
            ASSERT_EQ ( new_text        , "apple"    );
            ASSERT_EQ ( kind            , 1          );
            ASSERT_EQ ( detail          , "valenums" );
            ASSERT_EQ ( documentation   , "apple"    );
            ASSERT_EQ ( deprecated      , false      );
            ASSERT_EQ ( preselect       , false      );
        }
        if ( index == 1 )
        {
            ASSERT_EQ ( label           , "orange"   );
            ASSERT_EQ ( start_line      , 15         );
            ASSERT_EQ ( start_character , 12         );
            ASSERT_EQ ( end_line        , 15         );
            ASSERT_EQ ( end_character   , 12         );
            ASSERT_EQ ( new_text        , "orange"   );
            ASSERT_EQ ( kind            , 1          );
            ASSERT_EQ ( detail          , "valenums" );
            ASSERT_EQ ( documentation   , "orange"   );
            ASSERT_EQ ( deprecated      , false      );
            ASSERT_EQ ( preselect       , false      );
        }
        if ( index == 2 )
        {
            ASSERT_EQ ( label           , "kiwi"     );
            ASSERT_EQ ( start_line      , 15         );
            ASSERT_EQ ( start_character , 12         );
            ASSERT_EQ ( end_line        , 15         );
            ASSERT_EQ ( end_character   , 12         );
            ASSERT_EQ ( new_text        , "kiwi"     );
            ASSERT_EQ ( kind            , 1          );
            ASSERT_EQ ( detail          , "valenums" );
            ASSERT_EQ ( documentation   , "kiwi"     );
            ASSERT_EQ ( deprecated      , false      );
            ASSERT_EQ ( preselect       , false      );
        }
        if ( index == 3 )
        {
            ASSERT_EQ ( label           , "potato"   );
            ASSERT_EQ ( start_line      , 15         );
            ASSERT_EQ ( start_character , 12         );
            ASSERT_EQ ( end_line        , 15         );
            ASSERT_EQ ( end_character   , 12         );
            ASSERT_EQ ( new_text        , "potato"   );
            ASSERT_EQ ( kind            , 1          );
            ASSERT_EQ ( detail          , "valenums" );
            ASSERT_EQ ( documentation   , "potato"   );
            ASSERT_EQ ( deprecated      , false      );
            ASSERT_EQ ( preselect       , false      );
        }
        if ( index == 4 )
        {
            ASSERT_EQ ( label           , "tomato"   );
            ASSERT_EQ ( start_line      , 15         );
            ASSERT_EQ ( start_character , 12         );
            ASSERT_EQ ( end_line        , 15         );
            ASSERT_EQ ( end_character   , 12         );
            ASSERT_EQ ( new_text        , "tomato"   );
            ASSERT_EQ ( kind            , 1          );
            ASSERT_EQ ( detail          , "valenums" );
            ASSERT_EQ ( documentation   , "tomato"   );
            ASSERT_EQ ( deprecated      , false      );
            ASSERT_EQ ( preselect       , false      );
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

    ASSERT_EQ   ( client.getCompletionSize(), 5 );

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
            ASSERT_EQ ( label           , "key_string"                            );
            ASSERT_EQ ( start_line      , line                                    );
            ASSERT_EQ ( start_character , character                               );
            ASSERT_EQ ( end_line        , line                                    );
            ASSERT_EQ ( end_character   , character                               );
            ASSERT_EQ ( new_text        , "key_string = \"insert_string_here\"\n" );
            ASSERT_EQ ( kind            , 1                                       );
            ASSERT_EQ ( detail          , "inputtmpl"                             );
            ASSERT_EQ ( documentation   , "Key_string description here for test"  );
            ASSERT_EQ ( deprecated      , false                                   );
            ASSERT_EQ ( preselect       , false                                   );
        }
        if ( index == 1 )
        {
            ASSERT_EQ ( label           , "array_overwrite"                     );
            ASSERT_EQ ( start_line      , line                                  );
            ASSERT_EQ ( start_character , character                             );
            ASSERT_EQ ( end_line        , line                                  );
            ASSERT_EQ ( end_character   , character                             );
            ASSERT_EQ ( new_text        , "array_overwrite = [ 9.9 9.9 9.9 ]\n" );
            ASSERT_EQ ( kind            , 1                                     );
            ASSERT_EQ ( detail          , "inputtmpl"                           );
            ASSERT_EQ ( documentation   , "Key_list description here for test"  );
            ASSERT_EQ ( deprecated      , false                                 );
            ASSERT_EQ ( preselect       , false                                 );
        }
        if ( index == 2 )
        {
            ASSERT_EQ ( label           , "object - variant 1"               );
            ASSERT_EQ ( start_line      , line                               );
            ASSERT_EQ ( start_character , character                          );
            ASSERT_EQ ( end_line        , line                               );
            ASSERT_EQ ( end_character   , character                          );
            ASSERT_EQ ( new_text        , "object\n{\n    key  =   1.0\n    list = [ 11 12 13 14 15 ]\n    use  =   11\n}\n" );
            ASSERT_EQ ( kind            , 1                                  );
            ASSERT_EQ ( detail          , "inputvariants"                    );
            ASSERT_EQ ( documentation   , "Object description here For test" );
            ASSERT_EQ ( deprecated      , false                              );
            ASSERT_EQ ( preselect       , false                              );
        }
        if ( index == 3 )
        {
            ASSERT_EQ ( label           , "object - variant 2"               );
            ASSERT_EQ ( start_line      , line                               );
            ASSERT_EQ ( start_character , character                          );
            ASSERT_EQ ( end_line        , line                               );
            ASSERT_EQ ( end_character   , character                          );
            ASSERT_EQ ( new_text        ,"object\n{\n    key  =   2.0\n    list = [ 21 22 23 24 25 ]\n    use  =   21\n}\n" );
            ASSERT_EQ ( kind            , 1                                  );
            ASSERT_EQ ( detail          , "inputvariants"                    );
            ASSERT_EQ ( documentation   , "Object description here For test" );
            ASSERT_EQ ( deprecated      , false                              );
            ASSERT_EQ ( preselect       , false                              );
        }
        if ( index == 4 )
        {
            ASSERT_EQ ( label           , "object - variant 3"               );
            ASSERT_EQ ( start_line      , line                               );
            ASSERT_EQ ( start_character , character                          );
            ASSERT_EQ ( end_line        , line                               );
            ASSERT_EQ ( end_character   , character                          );
            ASSERT_EQ ( new_text        , "object\n{\n    key  =   3.0\n    list = [ 31 32 33 34 35 ]\n    use  =   31\n}\n" );
            ASSERT_EQ ( kind            , 1                                  );
            ASSERT_EQ ( detail          , "inputvariants"                    );
            ASSERT_EQ ( documentation   , "Object description here For test" );
            ASSERT_EQ ( deprecated      , false                              );
            ASSERT_EQ ( preselect       , false                              );
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

    ASSERT_EQ   ( client.getDefinitionSize(), 3 );

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
            ASSERT_EQ ( start_line      , 06 );
            ASSERT_EQ ( start_character , 14 );
            ASSERT_EQ ( end_line        , 06 );
            ASSERT_EQ ( end_character   , 14 );
        }
        else if ( index == 1 )
        {
            ASSERT_EQ ( start_line      , 06 );
            ASSERT_EQ ( start_character , 19 );
            ASSERT_EQ ( end_line        , 06 );
            ASSERT_EQ ( end_character   , 20 );
        }
        else if ( index == 2 )
        {
            ASSERT_EQ ( start_line      , 06 );
            ASSERT_EQ ( start_character , 24 );
            ASSERT_EQ ( end_line        , 06 );
            ASSERT_EQ ( end_character   , 26 );
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
