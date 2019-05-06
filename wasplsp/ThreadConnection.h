#ifndef WASPLSP_THREAD_CONNECTION_H
#define WASPLSP_THREAD_CONNECTION_H

#include <string>
#include <sstream>
#include <mutex>
#include <condition_variable>
#include "wasplsp/LSP.h"
#include "wasplsp/Connection.h"
#include "wasplsp/ServerImpl.h"
#include "waspcore/decl.h"

namespace wasp {

class DataObject;

namespace lsp  {

class WASP_PUBLIC ThreadConnection : public Connection
{
  public:

    ThreadConnection(ServerImpl * server){ this->server = server; }

    ~ThreadConnection(){}

    typedef std::shared_ptr<Connection> SP;

    bool read( DataObject & object , std::stringstream & errors )
    {
        bool pass = true;

        std::unique_lock<std::mutex> unique_lock( mutex_lock );

        if( this->packet.empty() )
        {
            ready_to_read.wait( unique_lock );
        }

        std::string rpc_string = this->packet;

        this->packet.clear();

        ready_to_write.notify_all();

        pass &= RPCStringToObject( rpc_string , object , errors );

        return true;
    }

    bool write( DataObject & object , std::stringstream & errors )
    {
        bool pass = true;

        std::unique_lock<std::mutex> unique_lock( mutex_lock );

        std::string rpc_string;

        pass &= objectToRPCString( object , rpc_string , errors );

        this->packet = rpc_string;

        ready_to_read.notify_all();

        ready_to_write.wait( unique_lock );

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

    std::mutex              mutex_lock;

    std::condition_variable ready_to_read;

    std::condition_variable ready_to_write;

    std::string             packet;

};

} // namespace lsp
} // namespace wasp

#endif // WASPLSP_THREAD_CONNECTION_H
