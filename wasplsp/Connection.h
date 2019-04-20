#ifndef WASPLSP_CONNECTION_H
#define WASPLSP_CONNECTION_H

#include <string>
#include "waspcore/decl.h"

namespace wasp {
namespace lsp  {

class WASP_PUBLIC Connection
{
  public:

    Connection(){}

    ~Connection(){}

    virtual bool write( DataObject & object , std::stringstream & errors ) = 0;

    virtual bool read ( DataObject & object , std::stringstream & errors ) = 0;

    virtual bool isServerRunning() = 0;

    virtual std::string getServerErrors() = 0;
};

} // namespace lsp
} // namespace wasp

#endif // WASPLSP_CONNECTION_H
