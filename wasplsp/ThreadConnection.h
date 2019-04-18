#ifndef WASPLSP_THREAD_CONNECTION_H
#define WASPLSP_THREAD_CONNECTION_H

#include <string>
#include "wasplsp/Connection.h"
#include "wasplsp/StreamLock.h"
#include "waspcore/decl.h"

namespace wasp {
namespace lsp  {

class WASP_PUBLIC ThreadConnection : public Connection
{
  public:

    ThreadConnection(){}

    ~ThreadConnection(){}

    bool server_write( DataObject        & object ,
                       std::stringstream & errors )
    {
        bool pass = true;

        std::string rpc_string;

        pass &= objectToRPCString( object , rpc_string , errors );

        pass &= server_to_client.write( rpc_string );
//        server_to_client.str( rpc_string );

        return pass;
    }

    bool client_write( DataObject        & object ,
                       std::stringstream & errors )
    {
        bool pass = true;

        std::string rpc_string;

        pass &= objectToRPCString( object , rpc_string , errors );

        pass &= client_to_server.write( rpc_string );
//        client_to_server.str( rpc_string );

        return pass;
    }

    bool server_read( DataObject        & object ,
                      std::stringstream & errors )
    {
       bool pass = true;

       std::string rpc_string;

       pass &= client_to_server.read( rpc_string );
//       std::string rpc_string = client_to_server.str();

       pass &= RPCStringToObject( rpc_string , object , errors );

       return pass;
    }

    bool client_read( DataObject        & object ,
                      std::stringstream & errors )
    {
        bool pass = true;

        std::string rpc_string;

        pass &= server_to_client.read( rpc_string );
//        std::string rpc_string = server_to_client.str();

        pass &= RPCStringToObject( rpc_string , object , errors );

        return pass;
    }

  private:

    StreamLock client_to_server;

    StreamLock server_to_client;
};

} // namespace lsp
} // namespace wasp

#endif // WASPLSP_THREAD_CONNECTION_H
