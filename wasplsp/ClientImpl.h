#ifndef WASPLSP_TEST_CLIENT_H
#define WASPLSP_TEST_CLIENT_H

#include <string>
#include "wasplsp/LSP.h"
#include "wasplsp/Connection.h"
#include "waspcore/Object.h"
#include "waspcore/decl.h"

namespace wasp {
namespace lsp  {

class WASP_PUBLIC ClientImpl
{
  public:

    ClientImpl() :
        is_connected(false)      ,
        is_initialized(false)    ,
        is_document_open(false)  ,
        request_id(0)            ,
        document_version(0)      ,
        response_array_type(NONE){}

    ~ClientImpl(){}

    bool connect( std::shared_ptr<Connection> connection );

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

    int getDiagnosticSize();

    int getCompletionSize();

    int getDefinitionSize();

    int getReferencesSize();

    int getFormattingSize();

    bool getDiagnosticAt( int           index           ,
                          int         & start_line      ,
                          int         & start_character ,
                          int         & end_line        ,
                          int         & end_character   ,
                          int         & severity        ,
                          std::string & code            ,
                          std::string & source          ,
                          std::string & message         );

    bool isConnected()
    {
        return this->is_connected;
    }

    std::shared_ptr<Connection> getConnection()
    {
        return this->connection;
    }

    std::string getErrors()
    {
        return this->errors.str();
    }

    int getPreviousRequestID()
    {
        return this->request_id;
    }

    bool isDocumentOpen()
    {
        return this->is_document_open;
    }

    int getCurrentDocumentVersion()
    {
        return this->document_version;
    }

  private:

      std::shared_ptr<Connection> connection;
      std::stringstream           errors;

      bool                        is_connected;
      bool                        is_initialized;
      bool                        is_document_open;
      int                         request_id;
      int                         document_version;
      std::string                 document_path;

      enum ResponseArrayType
      {
        DIAGNOSTIC,
        COMPLETION,
        DEFINITION,
        REFERENCES,
        FORMATTING,
        NONE
      } response_array_type;

      DataArray response_array;

      void incrementRequestID()
      {
          this->request_id++;
      }

      void incrementDocumentVersion()
      {
          this->document_version++;
      }
};

} // namespace lsp
} // namespace wasp

#endif // WASPLSP_TEST_CLIENT_H
