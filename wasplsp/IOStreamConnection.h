#ifndef WASPLSP_IOSTREAM_CONNECTION_H
#define WASPLSP_IOSTREAM_CONNECTION_H

#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include "wasplsp/LSP.h"
#include "wasplsp/Connection.h"
#include "wasplsp/ServerImpl.h"
#include "waspcore/decl.h"

namespace wasp {

class DataObject;

namespace lsp  {

class WASP_PUBLIC IOStreamConnection : public Connection
{
  public:

    IOStreamConnection(ServerImpl * server){ this->server = server; }

    ~IOStreamConnection(){}

    typedef std::shared_ptr<Connection> SP;

    bool read( DataObject & object , std::stringstream & errors )
    {
        bool pass = true;

        std::string content_length_key;

        std::cin >> content_length_key;

        wasp_check( content_length_key == m_rpc_content_len_key );

        int content_length_val;

        std::cin >> content_length_val;

        wasp_check( content_length_val > 0 );

        std::cin >> std::ws;

        std::string content( content_length_val , ' ' );

        std::cin.read( &content[0] , content_length_val );

        std::stringstream rpc_stream;

        rpc_stream << content_length_key
                   << " "
                   << content_length_val
                   << m_rpc_separator
                   << content;

        pass &= RPCStringToObject( rpc_stream.str() , object , errors );

        return true;
    }

    bool write( DataObject & object , std::stringstream & errors )
    {
        bool pass = true;

        std::string rpc_string;

        pass &= objectToRPCString( object , rpc_string , errors );

        std::cout << rpc_string;

        std::cout.flush();

        return true;
    }

    bool isServerRunning() const
    {
        return ( server != nullptr && server->isRunning() );
    }

    std::string getServerErrors() const
    {
        return server->getErrors();
    }

  private:

    ServerImpl * server;
};

} // namespace lsp
} // namespace wasp

#endif // WASPLSP_IOSTREAM_CONNECTION_H
