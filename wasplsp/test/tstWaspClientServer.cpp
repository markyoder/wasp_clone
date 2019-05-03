#include "wasplsp/WaspServer.h"
#include "wasplsp/Server.h"
#include "wasplsp/ClientImpl.h"
#include "wasplsp/Client.h"
#include "wasplsp/LSP.h"
#include "wasplsp/Connection.h"
#include "wasplsp/SymbolIterator.h"
#include "waspson/SONInterpreter.h"
#include "waspson/SONNodeView.h"
#include "wasphive/HIVE.h"
#include "gtest/gtest.h"
#include <thread>
#include <vector>
#include <sstream>

namespace wasp {
namespace lsp  {

// handles for client, server, and server thread

Client<ClientImpl> client;
std::thread server_thread;
Server<WaspServer<DefaultSONInterpreter,
                  SONNodeView,
                  DefaultSONInterpreter,
                  SONNodeView,
                  HIVE>> wasp_server;

TEST(client, launch_server_thread_and_connnect_client)
{
    // launch server thread and connect test client to server's communication

    std::string schema_text = R"INPUT(

object
{
    MinOccurs=3
    MaxOccurs=NoLimit

    key
    {
        MinOccurs=0
        MaxOccurs=1

        value
        {
            MinOccurs=1
            MaxOccurs=1
            ValType=Real
            MinValInc=0
            MaxValExc=NoLimit
        }
    }

    list
    {
        MinOccurs=1
        MaxOccurs=1

        value
        {
            MinOccurs=1
            MaxOccurs=5
            ValType=Int
            MinValInc=0
            MaxValExc=NoLimit
        }
    }
}

)INPUT";

    std::shared_ptr<DefaultSONInterpreter> schema =
            std::make_shared<DefaultSONInterpreter>();

    schema->parseString( schema_text );

    std::shared_ptr<HIVE> validator = std::make_shared<HIVE>();

    wasp_server.getImpl()->setValidator( validator , schema );

    server_thread = std::thread
    (
        &Server<WaspServer<DefaultSONInterpreter,
                           SONNodeView,
                           DefaultSONInterpreter,
                           SONNodeView,
                           HIVE>>::run ,
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
    list = [ 1 -2 4 5 9 8 ]
}

object
{
    key  = -4.6
    list = [ 5 6 7
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
            ASSERT_EQ ( start_line      , 14       );
            ASSERT_EQ ( start_character , 01       );
            ASSERT_EQ ( end_line        , 14       );
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
    list = [ 1 -2 4 5 9 ]
}

object
{
    key  = -4.6
    list = [ 5 6 7 ]
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

    ASSERT_EQ   ( client.getDiagnosticSize(), 3 );

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
            ASSERT_EQ ( start_line      , 11          );
            ASSERT_EQ ( start_character , 12          );
            ASSERT_EQ ( end_line        , 11          );
            ASSERT_EQ ( end_character   , 12          );
            ASSERT_EQ ( severity        , 01          );
            ASSERT_EQ ( code            , "validate"  );
            ASSERT_EQ ( source          , "validator" );
            ASSERT_EQ ( message         , "Validation Error: key value \"-4.6\" is less than the allowed minimum inclusive value of 0" );
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
/object/list/value (6:21)
/object/list/value (6:23)
/object (9:1)
/object/key (11:5)
/object/key/value (11:12)
/object/list (12:5)
/object/list/value (12:14)
/object/list/value (12:16)
/object/list/value (12:18)
)INPUT";

    ASSERT_EQ( paths.str() , expected_paths.str() );
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
