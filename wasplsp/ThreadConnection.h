#ifndef WASPLSP_THREAD_CONNECTION_H
#define WASPLSP_THREAD_CONNECTION_H

#include <string>
#include "wasplsp/Connection.h"
#include "wasplsp/StreamLock.h"
#include "waspcore/decl.h"

namespace wasp {
namespace lsp  {

template<class SERVER>
class WASP_PUBLIC ThreadConnection : public Connection
{
  public:

    ThreadConnection(SERVER * server){ this->server = server; }

    ~ThreadConnection(){}

    bool serverWrite( DataObject        & object ,
                      std::stringstream & errors )
    {
        bool pass = true;

        std::string rpc_string;

        pass &= objectToRPCString( object , rpc_string , errors );

        pass &= server_to_client.write( rpc_string );

        return pass;
    }

    bool clientWrite( DataObject        & object ,
                      std::stringstream & errors )
    {
        bool pass = true;

        std::string rpc_string;

        pass &= objectToRPCString( object , rpc_string , errors );

        pass &= client_to_server.write( rpc_string );

        return pass;
    }

    bool serverRead( DataObject        & object ,
                     std::stringstream & errors )
    {
       bool pass = true;

       std::string rpc_string;

       pass &= client_to_server.read( rpc_string );

       pass &= RPCStringToObject( rpc_string , object , errors );

       return pass;
    }

    bool clientRead( DataObject        & object ,
                     std::stringstream & errors )
    {
        bool pass = true;

        std::string rpc_string;

        pass &= server_to_client.read( rpc_string );

        pass &= RPCStringToObject( rpc_string , object , errors );

        return pass;
    }

    bool isServerRunning()
    {
        return ( server != nullptr && server->isRunning() );
    }

    std::string getServerErrors()
    {
        return server->getErrors();
    }

  private:

    SERVER * server;

    StreamLock client_to_server;

    StreamLock server_to_client;
};

} // namespace lsp
} // namespace wasp

#endif // WASPLSP_THREAD_CONNECTION_H
