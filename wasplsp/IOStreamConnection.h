#ifndef WASPLSP_IOSTREAM_CONNECTION_H
#define WASPLSP_IOSTREAM_CONNECTION_H

#include <string>
#include <iostream>
#include <sstream>
#include "wasplsp/LSP.h"
#include "wasplsp/Connection.h"
#include "waspcore/decl.h"

namespace wasp {

class DataObject;

namespace lsp  {

template<class SERVER>
class WASP_PUBLIC IOStreamConnection : public Connection
{
  public:

    IOStreamConnection(SERVER * server){ this->server = server; }

    ~IOStreamConnection(){}

    typedef std::shared_ptr<Connection> SP;

    bool read( DataObject & object , std::stringstream & errors )
    {
        bool pass = true;

        std::string content_length_key;

        std::cin >> content_length_key;

        int content_length_val;

        std::cin >> content_length_val;

        std::string content( content_length_val+4 , ' ' );

        std::cin.read( &content[0] , content_length_val+4 );

        std::stringstream rpc_stream;

        rpc_stream << content_length_key << " " << content_length_val << content;

        pass &= RPCStringToObject( rpc_stream.str() , object , errors );

        return true;
    }

    bool write( DataObject & object , std::stringstream & errors )
    {
        bool pass = true;

        std::string rpc_string;

        pass &= objectToRPCString( object , rpc_string , errors );

        std::cout << rpc_string;

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

    SERVER *      server;
};

} // namespace lsp
} // namespace wasp

#endif // WASPLSP_IOSTREAM_CONNECTION_H
