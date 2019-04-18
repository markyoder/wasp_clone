#ifndef WASPLSP_TEST_SERVER_H
#define WASPLSP_TEST_SERVER_H

#include <string>
#include "wasplsp/LSP.h"
#include "wasplsp/ThreadConnection.h"
#include "waspcore/Object.h"
#include "waspcore/decl.h"

namespace wasp {
namespace lsp  {

class WASP_PUBLIC TestServer
{
  public:

    TestServer() : is_initialized(false) , is_document_open(false)
    {
        connection = std::make_shared<ThreadConnection>();
    }

    ~TestServer(){}

    bool run();

    bool handleInitializeRequest(
                    const DataObject & initializeRequest  ,
                          DataObject & initializeResponse );

    bool handleInitializedNotification(
                    const DataObject & initializedNotification );

    bool handleDidOpenNotification(
                    const DataObject & didOpenNotification            ,
                          DataObject & publishDiagnosticsNotification );

    bool handleDidChangeNotification(
                    const DataObject & didChangeNotification          ,
                          DataObject & publishDiagnosticsNotification );

    bool handleCompletionRequest(
                    const DataObject & completionRequest  ,
                          DataObject & completionResponse );

    bool handleDefinitionRequest(
                    const DataObject & definitionRequest  ,
                          DataObject & definitionResponse );

    bool handleReferencesRequest(
                    const DataObject & referencesRequest  ,
                          DataObject & referencesResponse );

    bool handleRangeFormattingRequest(
                    const DataObject & rangeFormattingRequest  ,
                          DataObject & rangeFormattingResponse );

    bool handleDidCloseNotification(
                    const DataObject & didCloseNotification );

    bool handleShutdownRequest(
                    const DataObject & shutdownRequest  ,
                          DataObject & shutdownResponse );

    bool handleExitNotification(
                    const DataObject & exitNotification );

    bool parseDocumentForDiagnostics(
                          DataArray  & diagnosticsList );

    bool updateDocumentTextChanges(
                    const std::string & replacement_text ,
                          int           start_line       ,
                          int           start_character  ,
                          int           end_line         ,
                          int           end_character    ,
                          int           range_length     );

    bool gatherDocumentCompletionItems(
                          DataArray & completionItems  ,
                          bool      & is_incomplete    ,
                          int           line             ,
                          int           character        );

    bool gatherDocumentDefinitionLocations(
                          DataArray & definitionLocations ,
                          int           line                ,
                          int           character           );

    bool gatherDocumentReferencesLocations(
                          DataArray & referencesLocations ,
                          int           line                ,
                          int           character           ,
                          bool          include_declaration );

    bool gatherDocumentFormattingTextEdits(
                          DataArray & formattingTextEdits ,
                          int           start_line          ,
                          int           start_character     ,
                          int           end_line            ,
                          int           end_character       ,
                          int           tab_size            ,
                          bool          insert_spaces       );

    std::shared_ptr<ThreadConnection> getConnection()
    {
        return connection;
    }

  private:

      std::shared_ptr<ThreadConnection>  connection;
      std::stringstream                  errors;

      bool                               is_initialized;
      bool                               is_document_open;

      DataObject                         server_capabilities;
      DataObject                         client_capabilities;
      std::string                        client_root_path;
      int                                client_process_id;
      int                                client_request_id;

      std::string                        document_path;
      std::string                        document_language_id;
      std::string                        document_text;
      int                                document_version;
};

//#include "TestServer.i.h"

} // namespace lsp
} // namespace wasp

#endif // WASPLSP_TEST_SERVER_H
