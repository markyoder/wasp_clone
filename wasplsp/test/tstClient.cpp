#include "TestServer.h"
#include "wasplsp/Server.h"
#include "TestClient.h"
#include "wasplsp/Client.h"
#include "wasplsp/LSP.h"
#include "wasplsp/Connection.h"
#include "gtest/gtest.h"
#include <sstream>
#include <thread>

namespace wasp {
namespace lsp  {

TEST(client, script)
{
    // handles for test client and test server

    Client<TestClient> test_client;

    Server<TestServer> test_server;

    // setup test client with server's communication and launch server thread

    test_client.setup( test_server.getConnection() );

    std::thread server_thread = std::thread( & Server<TestServer>::run ,
                                             & test_server             );

    // script

    ASSERT_TRUE( test_client.initialize() );

        ASSERT_TRUE( test_client.getErrors().empty() );

        ASSERT_TRUE( test_server.getErrors().empty() );

        ASSERT_EQ  ( test_client.getPreviousRequestID() , 1 );

    ASSERT_TRUE( test_client.initialized() );

        ASSERT_TRUE( test_client.getErrors().empty() );

        ASSERT_TRUE( test_server.getErrors().empty() );

        ASSERT_EQ  ( test_client.getPreviousRequestID() , 1 );

    /* * * TODO - OTHER METHODS * * */

    ASSERT_TRUE( test_client.shutdown() );

        ASSERT_TRUE( test_client.getErrors().empty() );

        ASSERT_TRUE( test_server.getErrors().empty() );

        ASSERT_EQ  ( test_client.getPreviousRequestID() , 2 );

    ASSERT_TRUE( test_client.exit() );

        ASSERT_TRUE( test_client.getErrors().empty() );

        ASSERT_TRUE( test_server.getErrors().empty() );

        ASSERT_EQ  ( test_client.getPreviousRequestID() , 2 );

    // make sure server thread finishes execution from the exit notification

    server_thread.join();
}

} // namespace lsp
} // namespace wasp
