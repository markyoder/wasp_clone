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

    virtual bool serverWrite( DataObject        & object ,
                              std::stringstream & errors ) = 0;

    virtual bool clientWrite( DataObject        & object ,
                              std::stringstream & errors ) = 0;

    virtual bool serverRead( DataObject        & object ,
                             std::stringstream & errors ) = 0;

    virtual bool clientRead( DataObject        & object ,
                             std::stringstream & errors ) = 0;

    virtual bool isServerRunning() = 0;

    virtual std::string getServerErrors() = 0;
};

} // namespace lsp
} // namespace wasp

#endif // WASPLSP_CONNECTION_H
