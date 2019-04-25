#include "TestServer.h"
#include "wasplsp/Server.h"
#include "wasplsp/LSP.h"
#include "wasplsp/Connection.h"
#include "waspcore/Object.h"
#include "gtest/gtest.h"
#include <sstream>
#include <thread>

namespace wasp {
namespace lsp  {

// handles for server, server-thread, and thread-safe communication

std::thread        server_thread;
Server<TestServer> test_server;
Connection::SP     test_connection;

TEST(integrate, server_thread_launch)
{
    // get handle to the server communication object and launch server thread

    test_connection = test_server.getConnection();

    server_thread = std::thread( &Server<TestServer>::run , &test_server );
}

TEST(integrate, test_initialize)
{
    // initialize - build object / stream to server / get response back / test

    DataObject  client_object;
    int         client_request_id =  1;
    int         client_process_id =  12345;
    std::string client_root_uri   = "test/root/uri/string";
    DataObject  client_capabilities;

    DataObject  response_object;
    int         response_request_id;
    DataObject  response_capabilities;

    std::stringstream  client_errors;

    ASSERT_TRUE( buildInitializeRequest( client_object       ,
                                         client_errors       ,
                                         client_request_id   ,
                                         client_process_id   ,
                                         client_root_uri     ,
                                         client_capabilities ) );

    ASSERT_TRUE( test_connection->write( client_object , client_errors ) );

    ASSERT_TRUE( test_connection->read( response_object , client_errors ) );

    ASSERT_TRUE( dissectInitializeResponse( response_object       ,
                                            client_errors         ,
                                            response_request_id   ,
                                            response_capabilities ) );

    ASSERT_EQ( response_request_id          , client_request_id );
    ASSERT_EQ( response_capabilities.size() , (size_t) 0        );
}

TEST(integrate, test_initialized)
{
    // initialized - build object / stream to server / no response expected

    DataObject client_object;

    std::stringstream  client_errors;

    ASSERT_TRUE( buildInitializedNotification( client_object ,
                                               client_errors ) );

    ASSERT_TRUE( test_connection->write( client_object , client_errors ) );
}

TEST(integrate, test_didopen)
{
    // didopen - build object / stream to server / get response back / test

    DataObject  client_object;
    std::string document_uri         = "test/document/uri/string";
    std::string document_language_id = "test_language_id_string";
    int         document_version     =  1;
    std::string document_text        = "test\ntext\n1\nstring\n";

    DataObject  response_object;
    std::string response_uri;
    DataArray   response_diagnostics;

    int         response_3_start_line;
    int         response_3_start_character;
    int         response_3_end_line;
    int         response_3_end_character;
    int         response_3_severity;
    std::string response_3_code;
    std::string response_3_source;
    std::string response_3_message;

    std::stringstream  client_errors;

    ASSERT_TRUE( buildDidOpenNotification( client_object        ,
                                           client_errors        ,
                                           document_uri         ,
                                           document_language_id ,
                                           document_version     ,
                                           document_text        ) );

    ASSERT_TRUE( test_connection->write( client_object ,  client_errors ) );

    ASSERT_TRUE( test_connection->read( response_object , client_errors ) );

    ASSERT_TRUE( dissectPublishDiagnosticsNotification( response_object      ,
                                                        client_errors        ,
                                                        response_uri         ,
                                                        response_diagnostics ) );

    ASSERT_EQ( response_uri                , document_uri );
    ASSERT_EQ( response_diagnostics.size() , (size_t) 3   );

    ASSERT_TRUE( dissectDiagnosticObject( *(response_diagnostics[2].to_object()) ,
                                            client_errors                        ,
                                            response_3_start_line                ,
                                            response_3_start_character           ,
                                            response_3_end_line                  ,
                                            response_3_end_character             ,
                                            response_3_severity                  ,
                                            response_3_code                      ,
                                            response_3_source                    ,
                                            response_3_message                   ) );

    ASSERT_EQ( response_3_start_line      , 47                 );
    ASSERT_EQ( response_3_start_character , 36                 );
    ASSERT_EQ( response_3_end_line        , 47                 );
    ASSERT_EQ( response_3_end_character   , 43                 );
    ASSERT_EQ( response_3_severity        , 3                  );
    ASSERT_EQ( response_3_code            , "test.code.33"     );
    ASSERT_EQ( response_3_source          , "test_source_33"   );
    ASSERT_EQ( response_3_message         , "Test message 33." );
}

TEST(integrate, test_didchange)
{
    // didchange - build object / stream to server / get response back / test

    DataObject  client_object;
    std::string document_uri     = "test/document/uri/string";
    int         document_version =  2;
    int         start_line       =  0;
    int         start_character  =  0;
    int         end_line         =  3;
    int         end_character    =  7;
    int         range_length     =  0;
    std::string document_text    = "test\ntext\n2\nstring\n";

    DataObject  response_object;
    std::string response_uri;
    DataArray   response_diagnostics;

    int         response_2_start_line;
    int         response_2_start_character;
    int         response_2_end_line;
    int         response_2_end_character;
    int         response_2_severity;
    std::string response_2_code;
    std::string response_2_source;
    std::string response_2_message;

    std::stringstream  client_errors;

    ASSERT_TRUE( buildDidChangeNotification( client_object    ,
                                             client_errors    ,
                                             document_uri     ,
                                             document_version ,
                                             start_line       ,
                                             start_character  ,
                                             end_line         ,
                                             end_character    ,
                                             range_length     ,
                                             document_text    ) );

    ASSERT_TRUE( test_connection->write( client_object , client_errors ) );

    ASSERT_TRUE( test_connection->read( response_object , client_errors ) );

    ASSERT_TRUE( dissectPublishDiagnosticsNotification( response_object      ,
                                                        client_errors        ,
                                                        response_uri         ,
                                                        response_diagnostics ) );

    ASSERT_EQ( response_uri                , document_uri );
    ASSERT_EQ( response_diagnostics.size() , (size_t) 2   );

    ASSERT_TRUE( dissectDiagnosticObject( *(response_diagnostics[1].to_object()) ,
                                            client_errors                        ,
                                            response_2_start_line                ,
                                            response_2_start_character           ,
                                            response_2_end_line                  ,
                                            response_2_end_character             ,
                                            response_2_severity                  ,
                                            response_2_code                      ,
                                            response_2_source                    ,
                                            response_2_message                   ) );

    ASSERT_EQ( response_2_start_line      , 87                 );
    ASSERT_EQ( response_2_start_character , 17                 );
    ASSERT_EQ( response_2_end_line        , 88                 );
    ASSERT_EQ( response_2_end_character   , 12                 );
    ASSERT_EQ( response_2_severity        , 1                  );
    ASSERT_EQ( response_2_code            , "test.code.55"     );
    ASSERT_EQ( response_2_source          , "test_source_55"   );
    ASSERT_EQ( response_2_message         , "Test message 55." );
}

TEST(integrate, test_completion)
{
    // completion - build object / stream to server / get response back / test

    DataObject  client_object;
    int         client_request_id =  3;
    std::string document_uri      = "test/document/uri/string";
    int         line              =  4;
    int         character         =  2;

    DataObject  response_object;
    int         response_request_id;
    bool        response_is_incomplete;
    DataArray   response_completions;

    std::string response_3_label;
    int         response_3_start_line;
    int         response_3_start_character;
    int         response_3_end_line;
    int         response_3_end_character;
    std::string response_3_new_text;
    int         response_3_kind;
    std::string response_3_detail;
    std::string response_3_documentation;
    bool        response_3_deprecated;
    bool        response_3_preselect;

    std::stringstream  client_errors;

    ASSERT_TRUE( buildCompletionRequest( client_object     ,
                                         client_errors     ,
                                         client_request_id ,
                                         document_uri      ,
                                         line              ,
                                         character         ) );

    ASSERT_TRUE( test_connection->write( client_object , client_errors ) );

    ASSERT_TRUE( test_connection->read( response_object , client_errors ) );

    ASSERT_TRUE( dissectCompletionResponse( response_object        ,
                                            client_errors          ,
                                            response_request_id    ,
                                            response_is_incomplete ,
                                            response_completions   ) );

    ASSERT_EQ( response_request_id         , client_request_id );
    ASSERT_EQ( response_is_incomplete      , false             );
    ASSERT_EQ( response_completions.size() , (size_t) 3        );

    ASSERT_TRUE( dissectCompletionObject( *(response_completions[2].to_object()) ,
                                            client_errors                        ,
                                            response_3_label                     ,
                                            response_3_start_line                ,
                                            response_3_start_character           ,
                                            response_3_end_line                  ,
                                            response_3_end_character             ,
                                            response_3_new_text                  ,
                                            response_3_kind                      ,
                                            response_3_detail                    ,
                                            response_3_documentation             ,
                                            response_3_deprecated                ,
                                            response_3_preselect                 ) );

    ASSERT_EQ( response_3_label           , "test-label-3"         );
    ASSERT_EQ( response_3_start_line      , 33                     );
    ASSERT_EQ( response_3_start_character , 33                     );
    ASSERT_EQ( response_3_end_line        , 33                     );
    ASSERT_EQ( response_3_end_character   , 33                     );
    ASSERT_EQ( response_3_new_text        , "test-insert-text-3"   );
    ASSERT_EQ( response_3_kind            , 3                      );
    ASSERT_EQ( response_3_detail          , "test type info 3"     );
    ASSERT_EQ( response_3_documentation   , "test documentation 3" );
    ASSERT_EQ( response_3_deprecated      , false                  );
    ASSERT_EQ( response_3_preselect       , false                  );
}

TEST(integrate, test_definition)
{
    // definition - build object / stream to server / get response back / test

    DataObject  client_object;
    int         client_request_id =  4;
    std::string document_uri      = "test/document/uri/string";
    int         line              =  2;
    int         character         =  5;

    DataObject  response_object;
    int         response_request_id;
    DataArray   response_locations;

    std::string response_3_uri;
    int         response_3_start_line;
    int         response_3_start_character;
    int         response_3_end_line;
    int         response_3_end_character;

    std::stringstream  client_errors;

    ASSERT_TRUE( buildDefinitionRequest( client_object     ,
                                         client_errors     ,
                                         client_request_id ,
                                         document_uri      ,
                                         line              ,
                                         character         ) );

    ASSERT_TRUE( test_connection->write( client_object , client_errors ) );

    ASSERT_TRUE( test_connection->read( response_object , client_errors ) );

    ASSERT_TRUE( dissectLocationsResponse( response_object      ,
                                           client_errors        ,
                                           response_request_id  ,
                                           response_locations   ) );

    ASSERT_EQ( response_request_id       , client_request_id );
    ASSERT_EQ( response_locations.size() , (size_t) 3        );

    ASSERT_TRUE( dissectLocationObject( *(response_locations[2].to_object()) ,
                                          client_errors                      ,
                                          response_3_uri                     ,
                                          response_3_start_line              ,
                                          response_3_start_character         ,
                                          response_3_end_line                ,
                                          response_3_end_character           ) );

    ASSERT_EQ( response_3_uri             , "test/document/uri/string" );
    ASSERT_EQ( response_3_start_line      ,  33                        );
    ASSERT_EQ( response_3_start_character ,  33                        );
    ASSERT_EQ( response_3_end_line        ,  33                        );
    ASSERT_EQ( response_3_end_character   ,  33                        );
}

TEST(integrate, test_references)
{
    // references - build object / stream to server / get response back / test

    DataObject  client_object;
    int         client_request_id   =  5;
    std::string document_uri        = "test/document/uri/string";
    int         line                =  1;
    int         character           =  3;
    bool        include_declaration = false;

    DataObject  response_object;
    int         response_request_id;
    DataArray   response_locations;

    std::string response_2_uri;
    int         response_2_start_line;
    int         response_2_start_character;
    int         response_2_end_line;
    int         response_2_end_character;

    std::stringstream  client_errors;

    ASSERT_TRUE( buildReferencesRequest( client_object       ,
                                         client_errors       ,
                                         client_request_id   ,
                                         document_uri        ,
                                         line                ,
                                         character           ,
                                         include_declaration ) );

    ASSERT_TRUE( test_connection->write( client_object , client_errors ) );

    ASSERT_TRUE( test_connection->read( response_object , client_errors ) );

    ASSERT_TRUE( dissectLocationsResponse( response_object      ,
                                           client_errors        ,
                                           response_request_id  ,
                                           response_locations   ) );

    ASSERT_EQ( response_request_id       , client_request_id );
    ASSERT_EQ( response_locations.size() , (size_t) 2        );

    ASSERT_TRUE( dissectLocationObject( *(response_locations[1].to_object()) ,
                                          client_errors                      ,
                                          response_2_uri                     ,
                                          response_2_start_line              ,
                                          response_2_start_character         ,
                                          response_2_end_line                ,
                                          response_2_end_character           ) );

    ASSERT_EQ( response_2_uri             , "test/document/uri/string" );
    ASSERT_EQ( response_2_start_line      ,  55                        );
    ASSERT_EQ( response_2_start_character ,  55                        );
    ASSERT_EQ( response_2_end_line        ,  55                        );
    ASSERT_EQ( response_2_end_character   ,  55                        );
}

TEST(integrate, test_formatting)
{
    // formatting - build object / stream to server / get response back / test

    DataObject  client_object;
    int         client_request_id =  6;
    std::string document_uri      = "test/document/uri/string";
    int         start_line        =  2;
    int         start_character   =  0;
    int         end_line          =  4;
    int         end_character     =  3;
    int         tab_size          =  4;
    bool        insert_spaces     =  true;

    DataObject  response_object;
    int         response_request_id;
    DataArray   response_textedits;

    int         response_3_start_line;
    int         response_3_start_character;
    int         response_3_end_line;
    int         response_3_end_character;
    std::string response_3_new_text;

    std::stringstream  client_errors;

    ASSERT_TRUE( buildFormattingRequest( client_object     ,
                                         client_errors     ,
                                         client_request_id ,
                                         document_uri      ,
                                         start_line        ,
                                         start_character   ,
                                         end_line          ,
                                         end_character     ,
                                         tab_size          ,
                                         insert_spaces     ) );

    ASSERT_TRUE( test_connection->write( client_object , client_errors ) );

    ASSERT_TRUE( test_connection->read( response_object , client_errors ) );

    ASSERT_TRUE( dissectFormattingResponse( response_object     ,
                                            client_errors       ,
                                            response_request_id ,
                                            response_textedits  ) );

    ASSERT_EQ( response_request_id       , client_request_id );
    ASSERT_EQ( response_textedits.size() , (size_t) 3        );

    ASSERT_TRUE( dissectTextEditObject( *(response_textedits[2].to_object()) ,
                                          client_errors                      ,
                                          response_3_start_line              ,
                                          response_3_start_character         ,
                                          response_3_end_line                ,
                                          response_3_end_character           ,
                                          response_3_new_text                ) );

    ASSERT_EQ( response_3_start_line      , 30                                   );
    ASSERT_EQ( response_3_start_character , 01                                   );
    ASSERT_EQ( response_3_end_line        , 34                                   );
    ASSERT_EQ( response_3_end_character   , 03                                   );
    ASSERT_EQ( response_3_new_text        , "test\n  new\n  text\n  format\n  3" );
}

TEST(integrate, test_symbols)
{
    // symbols - build object / stream to server / get response back / test

    DataObject  client_object;
    int         client_request_id =  7;
    std::string document_uri      = "test/document/uri/string";

    DataObject  response_object;
    int         response_request_id;
    DataArray   response_symbols;

    std::string response_parent_0_name;
    std::string response_parent_0_detail;
    int         response_parent_0_kind;
    bool        response_parent_0_deprecated;
    int         response_parent_0_start_line;
    int         response_parent_0_start_character;
    int         response_parent_0_end_line;
    int         response_parent_0_end_character;
    int         response_parent_0_selection_start_line;
    int         response_parent_0_selection_start_character;
    int         response_parent_0_selection_end_line;
    int         response_parent_0_selection_end_character;

    std::string response_child_1_name;
    std::string response_child_1_detail;
    int         response_child_1_kind;
    bool        response_child_1_deprecated;
    int         response_child_1_start_line;
    int         response_child_1_start_character;
    int         response_child_1_end_line;
    int         response_child_1_end_character;
    int         response_child_1_selection_start_line;
    int         response_child_1_selection_start_character;
    int         response_child_1_selection_end_line;
    int         response_child_1_selection_end_character;

    std::string response_child_2_name;
    std::string response_child_2_detail;
    int         response_child_2_kind;
    bool        response_child_2_deprecated;
    int         response_child_2_start_line;
    int         response_child_2_start_character;
    int         response_child_2_end_line;
    int         response_child_2_end_character;
    int         response_child_2_selection_start_line;
    int         response_child_2_selection_start_character;
    int         response_child_2_selection_end_line;
    int         response_child_2_selection_end_character;

    std::stringstream  client_errors;

    ASSERT_TRUE( buildSymbolsRequest( client_object     ,
                                      client_errors     ,
                                      client_request_id ,
                                      document_uri      ) );

    ASSERT_TRUE( test_connection->write( client_object , client_errors ) );

    ASSERT_TRUE( test_connection->read( response_object , client_errors ) );

    ASSERT_TRUE( dissectSymbolsResponse( response_object     ,
                                         client_errors       ,
                                         response_request_id ,
                                         response_symbols    ) );

    ASSERT_EQ( response_request_id     , client_request_id );

    ASSERT_EQ( response_symbols.size() , (size_t) 1        );

    const DataObject & parent_0 = *response_symbols[0].to_object();

    ASSERT_EQ ( getDocumentSymbolChildren( parent_0 )->size() , (size_t) 2 );

    const DataObject & child_1 =
                *(getDocumentSymbolChildren( parent_0 )->at(0).to_object());

    const DataObject & child_2 =
                *(getDocumentSymbolChildren( parent_0 )->at(1).to_object());

    ASSERT_TRUE( dissectDocumentSymbolObject( parent_0                                    ,
                                              client_errors                               ,
                                              response_parent_0_name                      ,
                                              response_parent_0_detail                    ,
                                              response_parent_0_kind                      ,
                                              response_parent_0_deprecated                ,
                                              response_parent_0_start_line                ,
                                              response_parent_0_start_character           ,
                                              response_parent_0_end_line                  ,
                                              response_parent_0_end_character             ,
                                              response_parent_0_selection_start_line      ,
                                              response_parent_0_selection_start_character ,
                                              response_parent_0_selection_end_line        ,
                                              response_parent_0_selection_end_character   ) );

    ASSERT_TRUE( dissectDocumentSymbolObject( child_1                                    ,
                                              client_errors                              ,
                                              response_child_1_name                      ,
                                              response_child_1_detail                    ,
                                              response_child_1_kind                      ,
                                              response_child_1_deprecated                ,
                                              response_child_1_start_line                ,
                                              response_child_1_start_character           ,
                                              response_child_1_end_line                  ,
                                              response_child_1_end_character             ,
                                              response_child_1_selection_start_line      ,
                                              response_child_1_selection_start_character ,
                                              response_child_1_selection_end_line        ,
                                              response_child_1_selection_end_character   ) );

    ASSERT_TRUE( dissectDocumentSymbolObject( child_2                                    ,
                                              client_errors                              ,
                                              response_child_2_name                      ,
                                              response_child_2_detail                    ,
                                              response_child_2_kind                      ,
                                              response_child_2_deprecated                ,
                                              response_child_2_start_line                ,
                                              response_child_2_start_character           ,
                                              response_child_2_end_line                  ,
                                              response_child_2_end_character             ,
                                              response_child_2_selection_start_line      ,
                                              response_child_2_selection_start_character ,
                                              response_child_2_selection_end_line        ,
                                              response_child_2_selection_end_character   ) );

    EXPECT_EQ( response_parent_0_name                      , "test_symbol_name_parent_0"       );
    EXPECT_EQ( response_parent_0_detail                    , "test::symbol::detail::parent::0" );
    EXPECT_EQ( response_parent_0_kind                      , 15                                );
    EXPECT_EQ( response_parent_0_deprecated                , false                             );
    EXPECT_EQ( response_parent_0_start_line                , 10                                );
    EXPECT_EQ( response_parent_0_start_character           , 11                                );
    EXPECT_EQ( response_parent_0_end_line                  , 10                                );
    EXPECT_EQ( response_parent_0_end_character             , 17                                );
    EXPECT_EQ( response_parent_0_selection_start_line      , 10                                );
    EXPECT_EQ( response_parent_0_selection_start_character , 13                                );
    EXPECT_EQ( response_parent_0_selection_end_line        , 10                                );
    EXPECT_EQ( response_parent_0_selection_end_character   , 15                                );

    EXPECT_EQ( response_child_1_name                      , "test_symbol_name_child_1"       );
    EXPECT_EQ( response_child_1_detail                    , "test::symbol::detail::child::1" );
    EXPECT_EQ( response_child_1_kind                      , 20                               );
    EXPECT_EQ( response_child_1_deprecated                , false                            );
    EXPECT_EQ( response_child_1_start_line                , 20                               );
    EXPECT_EQ( response_child_1_start_character           , 21                               );
    EXPECT_EQ( response_child_1_end_line                  , 20                               );
    EXPECT_EQ( response_child_1_end_character             , 27                               );
    EXPECT_EQ( response_child_1_selection_start_line      , 20                               );
    EXPECT_EQ( response_child_1_selection_start_character , 23                               );
    EXPECT_EQ( response_child_1_selection_end_line        , 20                               );
    EXPECT_EQ( response_child_1_selection_end_character   , 25                               );

    EXPECT_EQ( response_child_2_name                      , "test_symbol_name_child_2"       );
    EXPECT_EQ( response_child_2_detail                    , "test::symbol::detail::child::2" );
    EXPECT_EQ( response_child_2_kind                      , 22                               );
    EXPECT_EQ( response_child_2_deprecated                , false                            );
    EXPECT_EQ( response_child_2_start_line                , 30                               );
    EXPECT_EQ( response_child_2_start_character           , 31                               );
    EXPECT_EQ( response_child_2_end_line                  , 30                               );
    EXPECT_EQ( response_child_2_end_character             , 37                               );
    EXPECT_EQ( response_child_2_selection_start_line      , 30                               );
    EXPECT_EQ( response_child_2_selection_start_character , 33                               );
    EXPECT_EQ( response_child_2_selection_end_line        , 30                               );
    EXPECT_EQ( response_child_2_selection_end_character   , 35                               );
}

TEST(integrate, test_didclose)
{
    // didclose - build object / stream to server / no response expected

    DataObject  client_object;
    std::string document_uri = "test/document/uri/string";

    std::stringstream  client_errors;

    ASSERT_TRUE( buildDidCloseNotification( client_object ,
                                            client_errors ,
                                            document_uri  ) );

    ASSERT_TRUE( test_connection->write( client_object , client_errors ) );
}

TEST(integrate, test_shutdown)
{
    // shutdown - build object / stream to server / get response back / test

    DataObject  client_object;
    int         client_request_id = 8;

    DataObject  response_object;
    int         response_request_id;

    std::stringstream  client_errors;

    ASSERT_TRUE( buildShutdownRequest( client_object     ,
                                       client_errors     ,
                                       client_request_id ) );

    ASSERT_TRUE( test_connection->write( client_object , client_errors ) );

    ASSERT_TRUE( test_connection->read( response_object , client_errors ) );

    ASSERT_TRUE( dissectShutdownResponse( response_object     ,
                                          client_errors       ,
                                          response_request_id ) );

    ASSERT_EQ( response_request_id , client_request_id );
}

TEST(integrate, test_exit)
{
    // exit - build object / stream to server / no response expected

    DataObject client_object;

    std::stringstream  client_errors;

    ASSERT_TRUE( buildExitNotification( client_object ,
                                        client_errors ) );

    ASSERT_TRUE( test_connection->write( client_object , client_errors ) );
}

TEST(integrate, server_thread_join)
{
    // make sure server thread finishes execution from the exit notification

    server_thread.join();
}

} // namespace lsp
} // namespace wasp
