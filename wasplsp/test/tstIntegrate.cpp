#include "TestServer.h"
#include "wasplsp/Server.h"
#include "wasplsp/LSP.h"
#include "waspcore/Object.h"
#include "gtest/gtest.h"
#include <sstream>
#include <thread>
#include <chrono>

namespace wasp {
namespace lsp  {

// client to server stream / server to client stream / errors stream

std::stringstream  client_to_server_stream;
std::stringstream  server_to_client_stream;
std::stringstream  errors_stream;

Server<TestServer> test_server;

TEST(integrate, launch_server_thread)
{
    // start server on separate detached thread with the provided streams
        
    std::thread ( & Server<TestServer>::run         ,
                  & test_server                     ,
                  std::ref( client_to_server_stream ) ,
                  std::ref( server_to_client_stream ) ,
                  std::ref( errors_stream           ) ).detach();
}

TEST(integrate, test_initialize)
{
    // initialize - build object / stream to server / get response back / test

    server_to_client_stream.str("");
    client_to_server_stream.str("");
    errors_stream.str("");
    
    DataObject  client_object;
    int         client_request_id =  1;
    int         client_process_id =  12345;
    std::string client_root_uri   = "test/root/uri/string";
    DataObject  client_capabilities;

    DataObject  response_object;
    int         response_request_id;
    DataObject  response_capabilities;

    ASSERT_TRUE( buildInitializeRequest( client_object       ,
                                         errors_stream       ,
                                         client_request_id   ,
                                         client_process_id   ,
                                         client_root_uri     ,
                                         client_capabilities ) );

    ASSERT_TRUE( objectToStream( client_object           ,
                                 client_to_server_stream ,
                                 errors_stream           ) );

    ASSERT_TRUE( streamToObject( server_to_client_stream ,
                                 response_object         ,
                                 errors_stream           ) );

    ASSERT_TRUE( dissectInitializeResponse( response_object       ,
                                            errors_stream         ,
                                            response_request_id   ,
                                            response_capabilities ) );

    ASSERT_EQ( response_request_id          , client_request_id );
    ASSERT_EQ( response_capabilities.size() , (size_t) 0        );
}

TEST(integrate, test_initialized)
{
    // initialized - build object / stream to server / no response expected

    server_to_client_stream.str("");
    client_to_server_stream.str("");
    errors_stream.str("");
    
    DataObject client_object;

    ASSERT_TRUE(buildInitializedNotification( client_object ,
                                              errors_stream ));

    ASSERT_TRUE(objectToStream( client_object           ,
                                client_to_server_stream ,
                                errors_stream           ));
}

TEST(integrate, test_didopen)
{
    // didopen - build object / stream to server / get response back / test

    server_to_client_stream.str("");
    client_to_server_stream.str("");
    errors_stream.str("");
    
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

    ASSERT_TRUE( buildDidOpenNotification( client_object        ,
                                           errors_stream        ,
                                           document_uri         ,
                                           document_language_id ,
                                           document_version     ,
                                           document_text        ) );

    ASSERT_TRUE( objectToStream( client_object           ,
                                 client_to_server_stream ,
                                 errors_stream           ) );

    std::this_thread::sleep_for( std::chrono::milliseconds(500) );
    
    ASSERT_TRUE( streamToObject( server_to_client_stream ,
                                 response_object         ,
                                 errors_stream           ) );

    ASSERT_TRUE( dissectPublishDiagnosticsNotification( response_object      ,
                                                        errors_stream        ,
                                                        response_uri         ,
                                                        response_diagnostics ) );

    ASSERT_EQ( response_uri                , document_uri );
    ASSERT_EQ( response_diagnostics.size() , (size_t) 3   );

    ASSERT_TRUE( dissectDiagnosticObject( *(response_diagnostics[2].to_object()) ,
                                            errors_stream                        ,
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

//TEST(integrate, test_didchange)
//{
//    // didchange - build object / stream to server / get response back / test
//
//    /* * * TODO * * */
//}
//
//TEST(integrate, test_completion)
//{
//    // completion - build object / stream to server / get response back / test
//
//    /* * * TODO * * */
//}
//
//TEST(integrate, test_definition)
//{
//    // definition - build object / stream to server / get response back / test
//
//    /* * * TODO * * */
//}
//
//TEST(integrate, test_references)
//{
//    // references - build object / stream to server / get response back / test
//
//    /* * * TODO * * */
//}
//
//TEST(integrate, test_formatting)
//{
//    // formatting - build object / stream to server / get response back / test
//
//    /* * * TODO * * */
//}

TEST(integrate, test_shutdown)
{
    // shutdown - build object / stream to server / get response back / test

    server_to_client_stream.str("");
    client_to_server_stream.str("");
    errors_stream.str("");
    
    DataObject  client_object;
    int         client_request_id = 6;

    DataObject  response_object;
    int         response_request_id;

    ASSERT_TRUE( buildShutdownRequest( client_object       ,
                                       errors_stream       ,
                                       client_request_id   ) );

    ASSERT_TRUE( objectToStream( client_object           ,
                                 client_to_server_stream ,
                                 errors_stream           ) );

    ASSERT_TRUE( streamToObject( server_to_client_stream ,
                                 response_object         ,
                                 errors_stream           ) );

    ASSERT_TRUE( dissectShutdownResponse( response_object       ,
                                          errors_stream         ,
                                          response_request_id   ) );

    ASSERT_EQ( response_request_id , client_request_id );
}

TEST(integrate, test_exit)
{
    // exit - build object / stream to server / no response expected

    server_to_client_stream.str("");
    client_to_server_stream.str("");
    errors_stream.str("");
    
    DataObject client_object;

    ASSERT_TRUE(buildExitNotification( client_object ,
                                       errors_stream ));

    ASSERT_TRUE(objectToStream( client_object           ,
                                client_to_server_stream ,
                                errors_stream           ));
}

} // namespace lsp
} // namespace wasp
