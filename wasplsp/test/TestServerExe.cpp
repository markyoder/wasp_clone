#include "TestServer.h"
#include "wasplsp/Server.h"

using namespace wasp;
using namespace lsp;

int main(int argc, char* argv[])
{
    bool pass;

    Server<TestServer> test_server;

    std::cin.sync_with_stdio(false);
     
    pass = test_server.run(std::cin , std::cout , std::cerr);

    return ( pass ? 0 : 1 );
}
