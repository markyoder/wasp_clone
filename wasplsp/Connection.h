#ifndef WASPLSP_CONNECTION_H
#define WASPLSP_CONNECTION_H

#include <string>
#include <sstream>
#include <memory>
#include "waspcore/decl.h"

namespace wasp {

class DataObject;

namespace lsp  {

class WASP_PUBLIC Connection
{
  public:

    Connection(){}

    ~Connection(){}

    typedef std::shared_ptr<Connection> SP;

    virtual bool write( DataObject & object , std::stringstream & errors ) = 0;

    virtual bool read ( DataObject & object , std::stringstream & errors ) = 0;

    virtual bool isServerRunning() const = 0;

    virtual std::string getServerErrors() const = 0;
};

} // namespace lsp
} // namespace wasp

#endif // WASPLSP_CONNECTION_H
