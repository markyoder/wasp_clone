#include "wasplsp/StreamLock.h"

namespace wasp {
namespace lsp  {

std::string StreamLock::str()
{
    std::unique_lock<std::mutex> unique_lock( mutex_lock );

    while( this->stream.str().empty() )
    {
        ready_to_read.wait( unique_lock );
    }

    std::string value = this->stream.str();

    this->stream.str( std::string() );

    this->stream.clear();

    if ( this->stream.str().empty() )
    {
        ready_to_write.notify_all();
    }

    return value;
}

void StreamLock::str( const std::string & value )
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
}

bool StreamLock::fail()
{
    return this->stream.fail();
}

} // namespace lsp
} // namespace wasp
