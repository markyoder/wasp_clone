#include "TestServer.h"
#include "wasplsp/Server.h"
#include "wasplsp/ClientImpl.h"
#include "wasplsp/Client.h"
#include "wasplsp/LSP.h"
#include "wasplsp/Connection.h"
#include "gtest/gtest.h"
#include <sstream>
#include <thread>

namespace wasp {
namespace lsp  {

// handles for client, server, and server thread

Client<ClientImpl> test_client;
Server<TestServer> test_server;
std::thread        server_thread;

TEST(client, launch_server_connnect_client)
{
    // launch server thread and connect test client to server's communication

    server_thread = std::thread( &Server<TestServer>::run , &test_server );

    ASSERT_FALSE( test_client.isConnected() );

    ASSERT_TRUE ( test_client.connect( test_server.getConnection() ) );

    ASSERT_TRUE ( test_client.isConnected() );
}

TEST(client, initialize)
{
    // initialize

    ASSERT_FALSE( test_client.getConnection()->isServerRunning() );

    ASSERT_TRUE ( test_client.initialize() );

    ASSERT_TRUE ( test_client.getConnection()->isServerRunning() );

    ASSERT_TRUE ( test_client.getConnection()->getServerErrors().empty() );

    ASSERT_TRUE ( test_client.getErrors().empty() );

    ASSERT_EQ   ( test_client.getPreviousRequestID() , 1 );
}

TEST(client, initialized)
{
    // initialized

    ASSERT_TRUE ( test_client.initialized() );

    ASSERT_TRUE ( test_client.getConnection()->getServerErrors().empty() );

    ASSERT_TRUE ( test_client.getErrors().empty() );

    ASSERT_EQ   ( test_client.getPreviousRequestID() , 1 );
}

TEST(client, opened_and_diagnostics)
{
    // opened

    std::string document_path        = "/test/document/path.inp";
    std::string document_language_id = "test-document-language-id";
    std::string document_text        = "test\ntext\n1\nstring\n";

    ASSERT_FALSE( test_client.isDocumentOpen() );

    ASSERT_TRUE ( test_client.opened( document_path        ,
                                      document_language_id ,
                                      document_text        ) );

    ASSERT_TRUE ( test_client.isDocumentOpen() );

    ASSERT_EQ   ( test_client.getCurrentDocumentVersion() , 1 );

    ASSERT_TRUE ( test_client.getConnection()->getServerErrors().empty() );

    ASSERT_TRUE ( test_client.getErrors().empty() );

    ASSERT_EQ   ( test_client.getPreviousRequestID() , 1 );

    // diagnostic response

    ASSERT_EQ   ( test_client.getDiagnosticSize(), 3 );

    for (int index = 0; index < test_client.getDiagnosticSize(); index++)
    {
        int         start_line;
        int         start_character;
        int         end_line;
        int         end_character;
        int         severity;
        std::string code;
        std::string source;
        std::string message;

        ASSERT_TRUE ( test_client.getDiagnosticAt( index           ,
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
            ASSERT_EQ ( start_line      , 20                 );
            ASSERT_EQ ( start_character , 16                 );
            ASSERT_EQ ( end_line        , 20                 );
            ASSERT_EQ ( end_character   , 27                 );
            ASSERT_EQ ( severity        , 1                  );
            ASSERT_EQ ( code            , "test.code.11"     );
            ASSERT_EQ ( source          , "test_source_11"   );
            ASSERT_EQ ( message         , "Test message 11." );
        }
        else if ( index == 1 )
        {
            ASSERT_EQ ( start_line      , 28                 );
            ASSERT_EQ ( start_character , 56                 );
            ASSERT_EQ ( end_line        , 34                 );
            ASSERT_EQ ( end_character   , 27                 );
            ASSERT_EQ ( severity        , 2                  );
            ASSERT_EQ ( code            , "test.code.22"     );
            ASSERT_EQ ( source          , "test_source_22"   );
            ASSERT_EQ ( message         , "Test message 22." );
        }
        else if ( index == 2 )
        {
            ASSERT_EQ ( start_line      , 47                 );
            ASSERT_EQ ( start_character , 36                 );
            ASSERT_EQ ( end_line        , 47                 );
            ASSERT_EQ ( end_character   , 43                 );
            ASSERT_EQ ( severity        , 3                  );
            ASSERT_EQ ( code            , "test.code.33"     );
            ASSERT_EQ ( source          , "test_source_33"   );
            ASSERT_EQ ( message         , "Test message 33." );
        }
    }
}

TEST(client, changed_and_diagnostics)
{
    // changed

    int         start_line        = 0;
    int         start_character   = 0;
    int         end_line          = 3;
    int         end_character     = 7;
    int         range_length      = 0;
    std::string new_document_text = "test\ntext\n2\nstring\n";

    ASSERT_EQ   ( test_client.getCurrentDocumentVersion() , 1 );

    ASSERT_TRUE ( test_client.changed( start_line        ,
                                       start_character   ,
                                       end_line          ,
                                       end_character     ,
                                       range_length      ,
                                       new_document_text ) );

    ASSERT_EQ   ( test_client.getCurrentDocumentVersion() , 2 );

    ASSERT_TRUE ( test_client.getConnection()->getServerErrors().empty() );

    ASSERT_TRUE ( test_client.getErrors().empty() );

    ASSERT_EQ   ( test_client.getPreviousRequestID() , 1 );

    // diagnostic response

    ASSERT_EQ   ( test_client.getDiagnosticSize(), 2 );

    for (int index = 0; index < test_client.getDiagnosticSize(); index++)
    {
        int         start_line;
        int         start_character;
        int         end_line;
        int         end_character;
        int         severity;
        std::string code;
        std::string source;
        std::string message;

        ASSERT_TRUE ( test_client.getDiagnosticAt( index           ,
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
            ASSERT_EQ ( start_line      , 67                 );
            ASSERT_EQ ( start_character , 45                 );
            ASSERT_EQ ( end_line        , 68                 );
            ASSERT_EQ ( end_character   , 16                 );
            ASSERT_EQ ( severity        , 4                  );
            ASSERT_EQ ( code            , "test.code.44"     );
            ASSERT_EQ ( source          , "test_source_44"   );
            ASSERT_EQ ( message         , "Test message 44." );
        }
        else if ( index == 1 )
        {
            ASSERT_EQ ( start_line      , 87                 );
            ASSERT_EQ ( start_character , 17                 );
            ASSERT_EQ ( end_line        , 88                 );
            ASSERT_EQ ( end_character   , 12                 );
            ASSERT_EQ ( severity        , 1                  );
            ASSERT_EQ ( code            , "test.code.55"     );
            ASSERT_EQ ( source          , "test_source_55"   );
            ASSERT_EQ ( message         , "Test message 55." );
        }
    }
}

TEST(client, completion_and_response)
{
    // completion

    int line        = 4;
    int character   = 2;

    ASSERT_TRUE ( test_client.completion( line      ,
                                          character ) );

    ASSERT_TRUE ( test_client.getConnection()->getServerErrors().empty() );

    ASSERT_TRUE ( test_client.getErrors().empty() );

    ASSERT_EQ   ( test_client.getPreviousRequestID() , 2 );

    // completion response

    ASSERT_EQ   ( test_client.getCompletionSize(), 3 );

    for (int index = 0; index < test_client.getCompletionSize(); index++)
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

        ASSERT_TRUE ( test_client.getCompletionAt( index           ,
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
            EXPECT_EQ ( label           , "test-label-1"         );
            EXPECT_EQ ( start_line      , 11                     );
            EXPECT_EQ ( start_character , 11                     );
            EXPECT_EQ ( end_line        , 11                     );
            EXPECT_EQ ( end_character   , 11                     );
            EXPECT_EQ ( new_text        , "test-insert-text-1"   );
            EXPECT_EQ ( kind            , 1                      );
            EXPECT_EQ ( detail          , "test type info 1"     );
            EXPECT_EQ ( documentation   , "test documentation 1" );
            EXPECT_EQ ( deprecated      , false                  );
            EXPECT_EQ ( preselect       , true                   );
        }
        else if ( index == 1 )
        {
            EXPECT_EQ ( label           , "test-label-2"         );
            EXPECT_EQ ( start_line      , 22                     );
            EXPECT_EQ ( start_character , 22                     );
            EXPECT_EQ ( end_line        , 22                     );
            EXPECT_EQ ( end_character   , 22                     );
            EXPECT_EQ ( new_text        , "test-insert-text-2"   );
            EXPECT_EQ ( kind            , 2                      );
            EXPECT_EQ ( detail          , "test type info 2"     );
            EXPECT_EQ ( documentation   , "test documentation 2" );
            EXPECT_EQ ( deprecated      , false                  );
            EXPECT_EQ ( preselect       , false                  );
        }
        else if ( index == 2 )
        {
            EXPECT_EQ ( label           , "test-label-3"         );
            EXPECT_EQ ( start_line      , 33                     );
            EXPECT_EQ ( start_character , 33                     );
            EXPECT_EQ ( end_line        , 33                     );
            EXPECT_EQ ( end_character   , 33                     );
            EXPECT_EQ ( new_text        , "test-insert-text-3"   );
            EXPECT_EQ ( kind            , 3                      );
            EXPECT_EQ ( detail          , "test type info 3"     );
            EXPECT_EQ ( documentation   , "test documentation 3" );
            EXPECT_EQ ( deprecated      , false                  );
            EXPECT_EQ ( preselect       , false                  );
        }
    }
}

TEST(client, definition_and_response)
{
    // todo : definition

    // todo : definition response
}

TEST(client, references_and_response)
{
    // todo : references

    // todo : references response
}

TEST(client, formatting_and_response)
{
    // todo : formatting

    // todo : formatting response
}

TEST(client, closed)
{
    // closed

    ASSERT_TRUE ( test_client.isDocumentOpen() );

    test_client.closed();

    ASSERT_FALSE( test_client.isDocumentOpen() );

    ASSERT_TRUE ( test_client.getErrors().empty() );

    ASSERT_TRUE ( test_client.getConnection()->getServerErrors().empty() );

    ASSERT_EQ   ( test_client.getPreviousRequestID() , 2 );
}

TEST(client, shutdown)
{
    // shutdown

    ASSERT_TRUE ( test_client.getConnection()->isServerRunning() );

    ASSERT_TRUE ( test_client.shutdown() );

    ASSERT_FALSE( test_client.getConnection()->isServerRunning() );

    ASSERT_TRUE ( test_client.getErrors().empty() );

    ASSERT_TRUE ( test_client.getConnection()->getServerErrors().empty() );

    ASSERT_EQ   ( test_client.getPreviousRequestID() , 3 );
}

TEST(client, exit)
{
    // exit

    ASSERT_TRUE ( test_client.exit() );

    ASSERT_TRUE ( test_client.getErrors().empty() );

    ASSERT_TRUE ( test_client.getConnection()->getServerErrors().empty() );

    ASSERT_EQ   ( test_client.getPreviousRequestID() , 3 );
}

TEST(client, server_thread_join)
{
    // make sure server thread finishes execution from the exit notification

    server_thread.join();
}

} // namespace lsp
} // namespace wasp
