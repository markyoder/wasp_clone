#include "TestServer.h"
#include "wasplsp/Server.h"
#include "wasplsp/ClientImpl.h"
#include "wasplsp/Client.h"
#include "wasplsp/LSP.h"
#include "wasplsp/Connection.h"
#include "gtest/gtest.h"
#include <thread>

namespace wasp {
namespace lsp  {

// handles for client, server, and server thread

Client<ClientImpl> test_client;
Server<TestServer> test_server;
std::thread        server_thread;

TEST(client, launch_server_thread_and_connnect_client)
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

    ASSERT_TRUE ( test_client.doInitialize() );

    ASSERT_TRUE ( test_client.getConnection()->isServerRunning() );

    ASSERT_TRUE ( test_client.getConnection()->getServerErrors().empty() );

    ASSERT_TRUE ( test_client.getErrors().empty() );

    ASSERT_EQ   ( test_client.getPreviousRequestID() , 1 );
}

TEST(client, initialized)
{
    // initialized

    ASSERT_TRUE ( test_client.doInitialized() );

    ASSERT_TRUE ( test_client.getConnection()->getServerErrors().empty() );

    ASSERT_TRUE ( test_client.getErrors().empty() );

    ASSERT_EQ   ( test_client.getPreviousRequestID() , 1 );
}

TEST(client, document_open_and_diagnostics)
{
    // document open

    std::string document_path        = "test/document/uri/string";
    std::string document_language_id = "test-document-language-id";
    std::string document_text        = "test\ntext\n1\nstring\n";

    ASSERT_FALSE( test_client.isDocumentOpen() );

    ASSERT_TRUE ( test_client.doDocumentOpen( document_path        ,
                                              document_language_id ,
                                              document_text        ) );

    ASSERT_TRUE ( test_client.isDocumentOpen() );

    ASSERT_EQ   ( test_client.getCurrentDocumentVersion() , 1 );

    ASSERT_TRUE ( test_client.getConnection()->getServerErrors().empty() );

    ASSERT_TRUE ( test_client.getErrors().empty() );

    ASSERT_EQ   ( test_client.getPreviousRequestID() , 1 );

    // diagnostic responses

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

TEST(client, document_change_and_diagnostics)
{
    // document change

    int         start_line        = 0;
    int         start_character   = 0;
    int         end_line          = 3;
    int         end_character     = 7;
    int         range_length      = 0;
    std::string new_document_text = "test\ntext\n2\nstring\n";

    ASSERT_EQ   ( test_client.getCurrentDocumentVersion() , 1 );

    ASSERT_TRUE ( test_client.doDocumentChange( start_line        ,
                                                start_character   ,
                                                end_line          ,
                                                end_character     ,
                                                range_length      ,
                                                new_document_text ) );

    ASSERT_EQ   ( test_client.getCurrentDocumentVersion() , 2 );

    ASSERT_TRUE ( test_client.getConnection()->getServerErrors().empty() );

    ASSERT_TRUE ( test_client.getErrors().empty() );

    ASSERT_EQ   ( test_client.getPreviousRequestID() , 1 );

    // diagnostic responses

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

TEST(client, document_completion_and_responses)
{
    // document completion

    int line        = 4;
    int character   = 2;

    ASSERT_TRUE ( test_client.doDocumentCompletion( line      ,
                                                    character ) );

    ASSERT_TRUE ( test_client.getConnection()->getServerErrors().empty() );

    ASSERT_TRUE ( test_client.getErrors().empty() );

    ASSERT_EQ   ( test_client.getPreviousRequestID() , 2 );

    // completion responses

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
            ASSERT_EQ ( label           , "test-label-1"         );
            ASSERT_EQ ( start_line      , 11                     );
            ASSERT_EQ ( start_character , 11                     );
            ASSERT_EQ ( end_line        , 11                     );
            ASSERT_EQ ( end_character   , 11                     );
            ASSERT_EQ ( new_text        , "test-insert-text-1"   );
            ASSERT_EQ ( kind            , 1                      );
            ASSERT_EQ ( detail          , "test type info 1"     );
            ASSERT_EQ ( documentation   , "test documentation 1" );
            ASSERT_EQ ( deprecated      , false                  );
            ASSERT_EQ ( preselect       , true                   );
        }
        else if ( index == 1 )
        {
            ASSERT_EQ ( label           , "test-label-2"         );
            ASSERT_EQ ( start_line      , 22                     );
            ASSERT_EQ ( start_character , 22                     );
            ASSERT_EQ ( end_line        , 22                     );
            ASSERT_EQ ( end_character   , 22                     );
            ASSERT_EQ ( new_text        , "test-insert-text-2"   );
            ASSERT_EQ ( kind            , 2                      );
            ASSERT_EQ ( detail          , "test type info 2"     );
            ASSERT_EQ ( documentation   , "test documentation 2" );
            ASSERT_EQ ( deprecated      , false                  );
            ASSERT_EQ ( preselect       , false                  );
        }
        else if ( index == 2 )
        {
            ASSERT_EQ ( label           , "test-label-3"         );
            ASSERT_EQ ( start_line      , 33                     );
            ASSERT_EQ ( start_character , 33                     );
            ASSERT_EQ ( end_line        , 33                     );
            ASSERT_EQ ( end_character   , 33                     );
            ASSERT_EQ ( new_text        , "test-insert-text-3"   );
            ASSERT_EQ ( kind            , 3                      );
            ASSERT_EQ ( detail          , "test type info 3"     );
            ASSERT_EQ ( documentation   , "test documentation 3" );
            ASSERT_EQ ( deprecated      , false                  );
            ASSERT_EQ ( preselect       , false                  );
        }
    }
}

TEST(client, document_definition_and_responses)
{
    // document definition

    int line        = 2;
    int character   = 5;

    ASSERT_TRUE ( test_client.doDocumentDefinition( line      ,
                                                    character ) );

    ASSERT_TRUE ( test_client.getConnection()->getServerErrors().empty() );

    ASSERT_TRUE ( test_client.getErrors().empty() );

    ASSERT_EQ   ( test_client.getPreviousRequestID() , 3 );

    // definition responses

    ASSERT_EQ   ( test_client.getDefinitionSize(), 3 );

    for (int index = 0; index < test_client.getDefinitionSize(); index++)
    {
        int         start_line;
        int         start_character;
        int         end_line;
        int         end_character;

        ASSERT_TRUE ( test_client.getDefinitionAt( index           ,
                                                   start_line      ,
                                                   start_character ,
                                                   end_line        ,
                                                   end_character   ) );
        if ( index == 0 )
        {
            ASSERT_EQ ( start_line      , 11 );
            ASSERT_EQ ( start_character , 11 );
            ASSERT_EQ ( end_line        , 11 );
            ASSERT_EQ ( end_character   , 11 );
        }
        else if ( index == 1 )
        {
            ASSERT_EQ ( start_line      , 22 );
            ASSERT_EQ ( start_character , 22 );
            ASSERT_EQ ( end_line        , 22 );
            ASSERT_EQ ( end_character   , 22 );
        }
        else if ( index == 2 )
        {
            ASSERT_EQ ( start_line      , 33 );
            ASSERT_EQ ( start_character , 33 );
            ASSERT_EQ ( end_line        , 33 );
            ASSERT_EQ ( end_character   , 33 );
        }
    }
}

TEST(client, document_references_and_responses)
{
    // document references

    int  line                = 1;
    int  character           = 3;
    bool include_declaration = false;

    ASSERT_TRUE ( test_client.doDocumentReferences( line                ,
                                                    character           ,
                                                    include_declaration ) );

    ASSERT_TRUE ( test_client.getConnection()->getServerErrors().empty() );

    ASSERT_TRUE ( test_client.getErrors().empty() );

    ASSERT_EQ   ( test_client.getPreviousRequestID() , 4 );

    // references responses

    ASSERT_EQ   ( test_client.getReferencesSize(), 2 );

    for (int index = 0; index < test_client.getReferencesSize(); index++)
    {
        int         start_line;
        int         start_character;
        int         end_line;
        int         end_character;

        ASSERT_TRUE ( test_client.getReferencesAt( index           ,
                                                   start_line      ,
                                                   start_character ,
                                                   end_line        ,
                                                   end_character   ) );
        if ( index == 0 )
        {
            ASSERT_EQ ( start_line      , 44 );
            ASSERT_EQ ( start_character , 44 );
            ASSERT_EQ ( end_line        , 44 );
            ASSERT_EQ ( end_character   , 44 );
        }
        else if ( index == 1 )
        {
            ASSERT_EQ ( start_line      , 55 );
            ASSERT_EQ ( start_character , 55 );
            ASSERT_EQ ( end_line        , 55 );
            ASSERT_EQ ( end_character   , 55 );
        }
    }
}

TEST(client, document_formatting_and_responses)
{
    // document formatting

    int         start_line        =  2;
    int         start_character   =  0;
    int         end_line          =  4;
    int         end_character     =  3;
    int         tab_size          =  4;
    bool        insert_spaces     =  true;

    ASSERT_TRUE ( test_client.doDocumentFormatting( start_line      ,
                                                    start_character ,
                                                    end_line        ,
                                                    end_character   ,
                                                    tab_size        ,
                                                    insert_spaces   ) );

    ASSERT_TRUE ( test_client.getConnection()->getServerErrors().empty() );

    ASSERT_TRUE ( test_client.getErrors().empty() );

    ASSERT_EQ   ( test_client.getPreviousRequestID() , 5 );

    // formatting responses

    ASSERT_EQ   ( test_client.getFormattingSize(), 3 );

    for (int index = 0; index < test_client.getFormattingSize(); index++)
    {
        int         start_line;
        int         start_character;
        int         end_line;
        int         end_character;
        std::string new_text;

        ASSERT_TRUE ( test_client.getFormattingAt( index           ,
                                                   start_line      ,
                                                   start_character ,
                                                   end_line        ,
                                                   end_character   ,
                                                   new_text        ) );
        if ( index == 0 )
        {
            ASSERT_EQ ( start_line      , 10                                   );
            ASSERT_EQ ( start_character , 01                                   );
            ASSERT_EQ ( end_line        , 14                                   );
            ASSERT_EQ ( end_character   , 03                                   );
            ASSERT_EQ ( new_text        , "test\n  new\n  text\n  format\n  1" );
        }
        else if ( index == 1 )
        {
            ASSERT_EQ ( start_line      , 20                                   );
            ASSERT_EQ ( start_character , 01                                   );
            ASSERT_EQ ( end_line        , 24                                   );
            ASSERT_EQ ( end_character   , 03                                   );
            ASSERT_EQ ( new_text        , "test\n  new\n  text\n  format\n  2" );
        }
        else if ( index == 2 )
        {
            ASSERT_EQ ( start_line      , 30                                   );
            ASSERT_EQ ( start_character , 01                                   );
            ASSERT_EQ ( end_line        , 34                                   );
            ASSERT_EQ ( end_character   , 03                                   );
            ASSERT_EQ ( new_text        , "test\n  new\n  text\n  format\n  3" );
        }
    }
}

TEST(client, document_symbols_and_responses)
{
    // document symbols

    ASSERT_TRUE ( test_client.doDocumentSymbols() );

    ASSERT_TRUE ( test_client.getConnection()->getServerErrors().empty() );

    ASSERT_TRUE ( test_client.getErrors().empty() );

    ASSERT_EQ   ( test_client.getPreviousRequestID() , 6 );

    // symbols responses

    ASSERT_EQ   ( test_client.getSymbolRootSize(), 1 );

    for (int index = 0; index < test_client.getSymbolRootSize(); index++)
    {
        std::string parent_0_name;
        std::string parent_0_detail;
        int         parent_0_kind;
        bool        parent_0_deprecated;
        int         parent_0_start_line;
        int         parent_0_start_character;
        int         parent_0_end_line;
        int         parent_0_end_character;
        int         parent_0_selection_start_line;
        int         parent_0_selection_start_character;
        int         parent_0_selection_end_line;
        int         parent_0_selection_end_character;

//        std::string child_1_name;
//        std::string child_1_detail;
//        int         child_1_kind;
//        bool        child_1_deprecated;
//        int         child_1_start_line;
//        int         child_1_start_character;
//        int         child_1_end_line;
//        int         child_1_end_character;
//        int         child_1_selection_start_line;
//        int         child_1_selection_start_character;
//        int         child_1_selection_end_line;
//        int         child_1_selection_end_character;
//
//        std::string child_2_name;
//        std::string child_2_detail;
//        int         child_2_kind;
//        bool        child_2_deprecated;
//        int         child_2_start_line;
//        int         child_2_start_character;
//        int         child_2_end_line;
//        int         child_2_end_character;
//        int         child_2_selection_start_line;
//        int         child_2_selection_start_character;
//        int         child_2_selection_end_line;
//        int         child_2_selection_end_character;

        ASSERT_TRUE ( test_client.getSymbolRootAt( index                              ,
                                                   parent_0_name                      ,
                                                   parent_0_detail                    ,
                                                   parent_0_kind                      ,
                                                   parent_0_deprecated                ,
                                                   parent_0_start_line                ,
                                                   parent_0_start_character           ,
                                                   parent_0_end_line                  ,
                                                   parent_0_end_character             ,
                                                   parent_0_selection_start_line      ,
                                                   parent_0_selection_start_character ,
                                                   parent_0_selection_end_line        ,
                                                   parent_0_selection_end_character   ) );
        if ( index == 0 )
        {
            ASSERT_EQ ( parent_0_name                      , "test_symbol_name_parent_0"       );
            ASSERT_EQ ( parent_0_detail                    , "test::symbol::detail::parent::0" );
            ASSERT_EQ ( parent_0_kind                      , 15                                );
            ASSERT_EQ ( parent_0_deprecated                , false                             );
            ASSERT_EQ ( parent_0_start_line                , 10                                );
            ASSERT_EQ ( parent_0_start_character           , 11                                );
            ASSERT_EQ ( parent_0_end_line                  , 10                                );
            ASSERT_EQ ( parent_0_end_character             , 17                                );
            ASSERT_EQ ( parent_0_selection_start_line      , 10                                );
            ASSERT_EQ ( parent_0_selection_start_character , 13                                );
            ASSERT_EQ ( parent_0_selection_end_line        , 10                                );
            ASSERT_EQ ( parent_0_selection_end_character   , 15                                );

            // TODO - ADD CLIENT TREE ITERATOR PATTERN FOR TRAVERSING CHILDREN OF EACH SYMBOL
        }
    }
}

TEST(client, document_close)
{
    // document close

    ASSERT_TRUE ( test_client.isDocumentOpen() );

    ASSERT_TRUE ( test_client.doDocumentClose() );

    ASSERT_FALSE( test_client.isDocumentOpen() );

    ASSERT_TRUE ( test_client.getErrors().empty() );

    ASSERT_TRUE ( test_client.getConnection()->getServerErrors().empty() );

    ASSERT_EQ   ( test_client.getPreviousRequestID() , 6 );
}

TEST(client, shutdown)
{
    // shutdown

    ASSERT_TRUE ( test_client.getConnection()->isServerRunning() );

    ASSERT_TRUE ( test_client.doShutdown() );

    ASSERT_FALSE( test_client.getConnection()->isServerRunning() );

    ASSERT_TRUE ( test_client.getErrors().empty() );

    ASSERT_TRUE ( test_client.getConnection()->getServerErrors().empty() );

    ASSERT_EQ   ( test_client.getPreviousRequestID() , 7 );
}

TEST(client, exit)
{
    // exit

    ASSERT_TRUE ( test_client.doExit() );

    ASSERT_TRUE ( test_client.getErrors().empty() );

    ASSERT_TRUE ( test_client.getConnection()->getServerErrors().empty() );

    ASSERT_EQ   ( test_client.getPreviousRequestID() , 7 );
}

TEST(client, server_thread_join)
{
    // make sure server thread finishes execution from the exit notification

    server_thread.join();
}

} // namespace lsp
} // namespace wasp
