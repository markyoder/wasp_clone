#ifndef WASPLSP_STREAM_LOCK_H
#define WASPLSP_STREAM_LOCK_H

#include <sstream>
#include <string>
#include <mutex>
#include <condition_variable>
#include "waspcore/decl.h"

namespace wasp {
namespace lsp  {

class WASP_PUBLIC StreamLock
{
  public:

    StreamLock(){}

    ~StreamLock(){}

    bool write( const std::string & value )
    {
        std::unique_lock<std::mutex> unique_lock( mutex_lock );

        while( !this->stream.str().empty() )
        {
            ready_to_write.wait( unique_lock );
        }

        this->stream.clear();

        this->stream.str( value );

        if ( !this->stream.str().empty() )
        {
            ready_to_read.notify_all();
        }

        return true;
    }

    bool read ( std::string & value )
    {
        std::unique_lock<std::mutex> unique_lock( mutex_lock );

        while( this->stream.str().empty() )
        {
            ready_to_read.wait( unique_lock );
        }

        value = this->stream.str();

        this->stream.str( std::string() );

        this->stream.clear();

        if ( this->stream.str().empty() )
        {
            ready_to_write.notify_all();
        }

        return true;
    }

  private:

      std::mutex              mutex_lock;

      std::condition_variable ready_to_read;

      std::condition_variable ready_to_write;

      std::stringstream       stream;
};

} // namespace lsp
} // namespace wasp

#endif // WASPLSP_STREAM_LOCK_H
