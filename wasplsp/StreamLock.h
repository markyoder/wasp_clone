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

    std::string str();

    void str( const std::string & value );

    bool fail();

  private:

      std::mutex              mutex_lock;

      std::condition_variable ready_to_read;

      std::condition_variable ready_to_write;

      std::stringstream       stream;
};

} // namespace lsp
} // namespace wasp

#endif // WASPLSP_STREAM_LOCK_H
