#ifndef WASPLSP_SERVER_IMPL_H
#define WASPLSP_SERVER_IMPL_H

#include <string>
#include "wasplsp/LSP.h"
#include "wasplsp/ThreadConnection.h"
#include "waspcore/Object.h"
#include "waspcore/decl.h"

namespace wasp {
namespace lsp  {

class WASP_PUBLIC ServerImpl
{
  public:

    ServerImpl() : is_initialized(false) , is_document_open(false)
    {
        connection = std::make_shared<ThreadConnection<ServerImpl>>(this);
    }

    ~ServerImpl(){}

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

    bool handleFormattingRequest(
                    const DataObject & formattingRequest  ,
                          DataObject & formattingResponse );

    bool handleSymbolsRequest(
                    const DataObject & symbolsRequest  ,
                          DataObject & symbolsResponse );

    bool handleDidCloseNotification(
                    const DataObject & didCloseNotification );

    bool handleShutdownRequest(
                    const DataObject & shutdownRequest  ,
                          DataObject & shutdownResponse );

    bool handleExitNotification(
                    const DataObject & exitNotification );

    std::shared_ptr<ThreadConnection<ServerImpl>> getConnection()
    {
        return connection;
    }

    bool isRunning()
    {
        return this->is_initialized;
    }

    std::string getErrors()
    {
        return errors.str();
    }

  private:

    virtual bool parseDocumentForDiagnostics(
                          DataArray  & diagnosticsList ) = 0;

    virtual bool updateDocumentTextChanges(
                    const std::string & replacement_text ,
                          int           start_line       ,
                          int           start_character  ,
                          int           end_line         ,
                          int           end_character    ,
                          int           range_length     ) = 0;

    virtual bool gatherDocumentCompletionItems(
                          DataArray & completionItems  ,
                          bool      & is_incomplete    ,
                          int         line             ,
                          int         character        ) = 0;

    virtual bool gatherDocumentDefinitionLocations(
                          DataArray & definitionLocations ,
                          int         line                ,
                          int         character           ) = 0;

    virtual bool gatherDocumentReferencesLocations(
                          DataArray & referencesLocations ,
                          int         line                ,
                          int         character           ,
                          bool        include_declaration ) = 0;

    virtual bool gatherDocumentFormattingTextEdits(
                          DataArray & formattingTextEdits ,
                          int         start_line          ,
                          int         start_character     ,
                          int         end_line            ,
                          int         end_character       ,
                          int         tab_size            ,
                          bool        insert_spaces       ) = 0;

    virtual bool gatherDocumentSymbols(
                          DataArray & documentSymbols ) = 0;

  protected:

    std::shared_ptr<ThreadConnection<ServerImpl>> connection;
    std::stringstream                             errors;

    bool                                          is_initialized;
    bool                                          is_document_open;

    DataObject                                    server_capabilities;
    DataObject                                    client_capabilities;
    std::string                                   client_root_path;
    int                                           client_process_id;
    int                                           client_request_id;

    std::string                                   document_path;
    std::string                                   document_language_id;
    std::string                                   document_text;
    int                                           document_version;
};

} // namespace lsp
} // namespace wasp

#endif // WASPLSP_SERVER_IMPL_H
