#ifndef WASPLSP_TEST_CLIENT_H
#define WASPLSP_TEST_CLIENT_H

#include <string>
#include "wasplsp/LSP.h"
#include "wasplsp/ThreadConnection.h"
#include "waspcore/Object.h"
#include "waspcore/decl.h"

namespace wasp {
namespace lsp  {

class WASP_PUBLIC TestClient
{
  public:

    TestClient() : is_setup(false) {}

    ~TestClient(){}

    bool setup( std::shared_ptr<Connection> connection );

    bool initialize();

    bool initialized();

    bool opened( const std::string & document_path        ,
                 const std::string & document_language_id ,
                 const std::string & document_text        );

    bool changed( int                 start_line        ,
                  int                 start_character   ,
                  int                 end_line          ,
                  int                 end_character     ,
                  int                 range_length      ,
                  const std::string & new_document_text );

    bool completion( int line      ,
                     int character );

    bool definition( int line      ,
                     int character );

    bool references( int  line                ,
                     int  character           ,
                     bool include_declaration );

    bool formatting( int  start_line      ,
                     int  start_character ,
                     int  end_line        ,
                     int  end_character   ,
                     int  tab_size        ,
                     bool insert_spaces   );

    bool closed();

    bool shutdown();

    bool exit();

    std::string getErrors()
    {
        return errors.str();
    }

    int getPreviousRequestID()
    {
        return request_id;
    }

    int getCurrentDocumentVersion()
    {
        return document_version;
    }

  private:

      std::shared_ptr<Connection> connection;
      std::stringstream           errors;


      bool                        is_setup;

      bool                        is_initialized;
      bool                        is_document_open;

      int                         request_id;
      int                         document_version;
};

//#include "TestClientx.i.h"

} // namespace lsp
} // namespace wasp

#endif // WASPLSP_TEST_CLIENT_H
