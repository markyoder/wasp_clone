#include "wasplsp/ClientImpl.h"
#include <unistd.h>

namespace wasp {
namespace lsp  {

bool ClientImpl::connect( std::shared_ptr<Connection> connection )
{
    bool pass = true;

    if ( this->is_connected )
    {
        this->errors << m_error << "Client already connected" << std::endl;

        pass = false;
    }
    else
    {
        this->connection = connection;

        this->is_connected = true;
    }

    return pass;
}

bool ClientImpl::doInitialize()
{
    if ( !this->is_connected )
    {
        this->errors << m_error << "Client not connected" << std::endl;

        return false;
    }

    if ( this->is_initialized )
    {
        this->errors << m_error << "Connection already initialized" << std::endl;

        return false;
    }

    bool pass = true;

    this->incrementRequestID();

    DataObject client_object;
    DataObject client_capabilities;
    DataObject response_object;
    int        response_request_id;
    DataObject response_capabilities;

    pass &= buildInitializeRequest( client_object       ,
                                    this->errors        ,
                                    this->request_id    ,
                                    0000                ,
                                    "temp-root-uri"     ,
                                    client_capabilities );

    pass &= connection->write( client_object , this->errors );

    pass &= connection->read( response_object , this->errors );

    pass &= dissectInitializeResponse( response_object       ,
                                       this->errors          ,
                                       response_request_id   ,
                                       response_capabilities );

    if ( response_request_id != this->request_id )
    {
        this->errors << m_error << "Initialize response id mismatch" << std::endl;

        pass = false;
    }

    this->is_initialized = true;

    return pass;
}

bool ClientImpl::doInitialized()
{
    if ( !this->is_connected )
    {
        this->errors << m_error << "Client not connected" << std::endl;

        return false;
    }

    if ( !this->is_initialized )
    {
        this->errors << m_error << "Connection not initialized" << std::endl;

        return false;
    }

    bool pass = true;

    DataObject client_object;

    pass &= buildInitializedNotification( client_object ,
                                          this->errors  );

    pass &= connection->write( client_object , this->errors );

    return pass;
}

bool ClientImpl::doDocumentOpen( const std::string & document_path        ,
                                 const std::string & document_language_id ,
                                 const std::string & document_text        )
{
    if ( !this->is_connected )
    {
        this->errors << m_error << "Client not connected" << std::endl;

        return false;
    }

    if ( !this->is_initialized )
    {
        this->errors << m_error << "Connection not initialized" << std::endl;

        return false;
    }

    if ( this->is_document_open )
    {
        this->errors << m_error << "Document already open" << std::endl;

        return false;
    }

    bool pass = true;

    this->document_path = document_path;

    this->incrementDocumentVersion();

    DataObject  client_object;
    DataObject  response_object;
    std::string response_document_path;

    pass &= buildDidOpenNotification( client_object          ,
                                      this->errors           ,
                                      this->document_path    ,
                                      document_language_id   ,
                                      this->document_version ,
                                      document_text          );

    pass &= connection->write( client_object , this->errors );

    pass &= connection->read( response_object , this->errors );

    pass &= dissectPublishDiagnosticsNotification( response_object        ,
                                                   this->errors           ,
                                                   response_document_path ,
                                                   this->response_array   );

    if ( response_document_path != this->document_path )
    {
        this->errors << m_error << "Diagnositics path mismatch" << std::endl;

        pass = false;
    }

    this->response_array_type = DIAGNOSTIC;

    this->is_document_open = true;

    return pass;
}

bool ClientImpl::doDocumentChange( int                 start_line        ,
                                   int                 start_character   ,
                                   int                 end_line          ,
                                   int                 end_character     ,
                                   int                 range_length      ,
                                   const std::string & new_document_text )
{
    if ( !this->is_connected )
    {
        this->errors << m_error << "Client not connected" << std::endl;

        return false;
    }

    if ( !this->is_initialized )
    {
        this->errors << m_error << "Connection not initialized" << std::endl;

        return false;
    }

    if ( !this->is_document_open )
    {
        this->errors << m_error << "Document not open" << std::endl;

        return false;
    }

    bool pass = true;

    this->incrementDocumentVersion();

    DataObject  client_object;
    DataObject  response_object;
    std::string response_document_path;

    pass &= buildDidChangeNotification( client_object          ,
                                        this->errors           ,
                                        this->document_path    ,
                                        this->document_version ,
                                        start_line             ,
                                        start_character        ,
                                        end_line               ,
                                        end_character          ,
                                        range_length           ,
                                        new_document_text      );

    pass &= connection->write( client_object , this->errors );

    pass &= connection->read( response_object , this->errors );

    pass &= dissectPublishDiagnosticsNotification( response_object        ,
                                                   this->errors           ,
                                                   response_document_path ,
                                                   this->response_array   );

    if ( response_document_path != this->document_path )
    {
        this->errors << m_error << "Diagnositics path mismatch" << std::endl;

        pass = false;
    }

    this->response_array_type = DIAGNOSTIC;

    return pass;
}

bool ClientImpl::doDocumentCompletion( int line      ,
                                       int character )
{
    if ( !this->is_connected )
    {
        this->errors << m_error << "Client not connected" << std::endl;

        return false;
    }

    if ( !this->is_initialized )
    {
        this->errors << m_error << "Connection not initialized" << std::endl;

        return false;
    }

    if ( !this->is_document_open )
    {
        this->errors << m_error << "Document not open" << std::endl;

        return false;
    }

    bool pass = true;

    this->incrementRequestID();

    DataObject client_object;
    DataObject response_object;
    int        response_request_id;
    bool       response_is_incomplete;

    pass &= buildCompletionRequest( client_object       ,
                                    this->errors        ,
                                    this->request_id    ,
                                    this->document_path ,
                                    line                ,
                                    character           );

    pass &= connection->write( client_object , this->errors );

    pass &= connection->read( response_object , this->errors );

    pass &= dissectCompletionResponse( response_object        ,
                                       this->errors           ,
                                       response_request_id    ,
                                       response_is_incomplete ,
                                       this->response_array   );

    if ( response_request_id != this->request_id )
    {
        this->errors << m_error << "Completion response id mismatch" << std::endl;

        pass = false;
    }

    this->response_array_type = COMPLETION;

    return pass;
}

bool ClientImpl::doDocumentDefinition( int line      ,
                                       int character )
{
    if ( !this->is_connected )
    {
        this->errors << m_error << "Client not connected" << std::endl;

        return false;
    }

    if ( !this->is_initialized )
    {
        this->errors << m_error << "Connection not initialized" << std::endl;

        return false;
    }

    if ( !this->is_document_open )
    {
        this->errors << m_error << "Document not open" << std::endl;

        return false;
    }

    bool pass = true;

    this->incrementRequestID();

    DataObject client_object;
    DataObject response_object;
    int        response_request_id;

    pass &= buildDefinitionRequest( client_object       ,
                                    this->errors        ,
                                    this->request_id    ,
                                    this->document_path ,
                                    line                ,
                                    character           );

    pass &= connection->write( client_object , this->errors );

    pass &= connection->read( response_object , this->errors );

    pass &= dissectLocationsResponse( response_object      ,
                                      this->errors         ,
                                      response_request_id  ,
                                      this->response_array );

    if ( response_request_id != this->request_id )
    {
        this->errors << m_error << "Definition response id mismatch" << std::endl;

        pass = false;
    }

    this->response_array_type = DEFINITION;

    return pass;
}

bool ClientImpl::doDocumentReferences( int  line                ,
                                       int  character           ,
                                       bool include_declaration )
{
    if ( !this->is_connected )
    {
        this->errors << m_error << "Client not connected" << std::endl;

        return false;
    }

    if ( !this->is_initialized )
    {
        this->errors << m_error << "Connection not initialized" << std::endl;

        return false;
    }

    if ( !this->is_document_open )
    {
        this->errors << m_error << "Document not open" << std::endl;

        return false;
    }

    bool pass = true;

    this->incrementRequestID();

    DataObject client_object;
    DataObject response_object;
    int        response_request_id;

    pass &= buildReferencesRequest( client_object       ,
                                    this->errors        ,
                                    this->request_id    ,
                                    this->document_path ,
                                    line                ,
                                    character           ,
                                    include_declaration );

    pass &= connection->write( client_object , this->errors );

    pass &= connection->read( response_object , this->errors );

    pass &= dissectLocationsResponse( response_object      ,
                                      this->errors         ,
                                      response_request_id  ,
                                      this->response_array );

    if ( response_request_id != this->request_id )
    {
        this->errors << m_error << "References response id mismatch" << std::endl;

        pass = false;
    }

    this->response_array_type = REFERENCES;

    return pass;
}

bool ClientImpl::doDocumentFormatting( int  start_line      ,
                                       int  start_character ,
                                       int  end_line        ,
                                       int  end_character   ,
                                       int  tab_size        ,
                                       bool insert_spaces   )
{
    if ( !this->is_connected )
    {
        this->errors << m_error << "Client not connected" << std::endl;

        return false;
    }

    if ( !this->is_initialized )
    {
        this->errors << m_error << "Connection not initialized" << std::endl;

        return false;
    }

    if ( !this->is_document_open )
    {
        this->errors << m_error << "Document not open" << std::endl;

        return false;
    }

    bool pass = true;

    this->incrementRequestID();

    DataObject client_object;
    DataObject response_object;
    int        response_request_id;

    pass &= buildRangeFormattingRequest( client_object       ,
                                         this->errors        ,
                                         this->request_id    ,
                                         this->document_path ,
                                         start_line          ,
                                         start_character     ,
                                         end_line            ,
                                         end_character       ,
                                         tab_size            ,
                                         insert_spaces       );

    pass &= connection->write( client_object , this->errors );

    pass &= connection->read( response_object , this->errors );

    pass &= dissectRangeFormattingResponse( response_object      ,
                                            this->errors         ,
                                            response_request_id  ,
                                            this->response_array );

    if ( response_request_id != this->request_id )
    {
        this->errors << m_error << "Formatting response id mismatch" << std::endl;

        pass = false;
    }

    this->response_array_type = FORMATTING;

    return pass;
}

bool ClientImpl::doDocumentClose()
{
    if ( !this->is_connected )
    {
        this->errors << m_error << "Client not connected" << std::endl;

        return false;
    }

    if ( !this->is_initialized )
    {
        this->errors << m_error << "Connection not initialized" << std::endl;

        return false;
    }

    if ( !this->is_document_open )
    {
        this->errors << m_error << "Document not open" << std::endl;

        return false;
    }

    bool pass = true;

    DataObject client_object;

    pass &= buildDidCloseNotification( client_object       ,
                                       this->errors        ,
                                       this->document_path );

    pass &= connection->write( client_object , this->errors );

    this->is_document_open = false;

    return pass;
}

bool ClientImpl::doShutdown()
{
    if ( !this->is_connected )
    {
        this->errors << m_error << "Client not connected" << std::endl;

        return false;
    }

    if ( !this->is_initialized )
    {
        this->errors << m_error << "Connection needs to be initialized" << std::endl;

        return false;
    }

    if ( this->is_document_open )
    {
        this->errors << m_error << "Document needs to be closed" << std::endl;

        return false;
    }

    bool pass = true;

    this->incrementRequestID();

    DataObject client_object;
    DataObject response_object;
    int        response_request_id;

    pass &= buildShutdownRequest( client_object    ,
                                  this->errors     ,
                                  this->request_id );

    pass &= connection->write( client_object , this->errors );

    pass &= connection->read( response_object, this->errors );

    pass &= dissectShutdownResponse( response_object ,
                                     this->errors          ,
                                     response_request_id   );

    if ( response_request_id != this->request_id )
    {
        this->errors << m_error << "Shutdown response id mismatch" << std::endl;

        pass = false;
    }

    this->is_initialized = false;

    return pass;
}

bool ClientImpl::doExit()
{
    bool pass = true;

    if ( !this->is_connected )
    {
        this->errors << m_error << "Client not connected" << std::endl;

        return false;
    }

    if ( this->is_initialized )
    {
        this->errors << m_error << "Connection needs to be shutdown" << std::endl;

        return false;
    }

    DataObject client_object;

    pass &= buildExitNotification( client_object ,
                                   this->errors  );

    pass &= connection->write( client_object , this->errors );

    this->is_connected = false;

    return pass;
}

int ClientImpl::getDiagnosticSize()
{
    return response_array_type == DIAGNOSTIC ? response_array.size() : 0;
}

int ClientImpl::getCompletionSize()
{
    return response_array_type == COMPLETION ? response_array.size() : 0;
}

int ClientImpl::getDefinitionSize()
{
    return response_array_type == DEFINITION ? response_array.size() : 0;
}

int ClientImpl::getReferencesSize()
{
    return response_array_type == REFERENCES ? response_array.size() : 0;
}

int ClientImpl::getFormattingSize()
{
    return response_array_type == FORMATTING ? response_array.size() : 0;
}

bool ClientImpl::getDiagnosticAt( int           index           ,
                                  int         & start_line      ,
                                  int         & start_character ,
                                  int         & end_line        ,
                                  int         & end_character   ,
                                  int         & severity        ,
                                  std::string & code            ,
                                  std::string & source          ,
                                  std::string & message         )
{
    if ( response_array_type != DIAGNOSTIC )
    {
        this->errors << m_error << "No diagnostics currently stored" << std::endl;

        return false;
    }

    if ( index >= (int) response_array.size() )
    {
        this->errors << m_error << "Diagnostics index out of bounds" << std::endl;

        return false;
    }

    bool pass = true;

    pass &= dissectDiagnosticObject( *(response_array[index].to_object()) ,
                                       this->errors                       ,
                                       start_line                         ,
                                       start_character                    ,
                                       end_line                           ,
                                       end_character                      ,
                                       severity                           ,
                                       code                               ,
                                       source                             ,
                                       message                            );

    return pass;
}

bool ClientImpl::getCompletionAt( int           index           ,
                                  std::string & label           ,
                                  int         & start_line      ,
                                  int         & start_character ,
                                  int         & end_line        ,
                                  int         & end_character   ,
                                  std::string & new_text        ,
                                  int         & kind            ,
                                  std::string & detail          ,
                                  std::string & documentation   ,
                                  bool        & deprecated      ,
                                  bool        & preselect       )
{
    if ( response_array_type != COMPLETION )
    {
        this->errors << m_error << "No completions currently stored" << std::endl;

        return false;
    }

    if ( index >= (int) response_array.size() )
    {
        this->errors << m_error << "Completions index out of bounds" << std::endl;

        return false;
    }

    bool pass = true;

    pass &= dissectCompletionObject( *(response_array[index].to_object()) ,
                                       this->errors                       ,
                                       label                              ,
                                       start_line                         ,
                                       start_character                    ,
                                       end_line                           ,
                                       end_character                      ,
                                       new_text                           ,
                                       kind                               ,
                                       detail                             ,
                                       documentation                      ,
                                       deprecated                         ,
                                       preselect                          );





    return pass;
}

bool ClientImpl::getDefinitionAt( int           index           ,
                                  int         & start_line      ,
                                  int         & start_character ,
                                  int         & end_line        ,
                                  int         & end_character   )
{
    if ( response_array_type != DEFINITION )
    {
        this->errors << m_error << "No definitions currently stored" << std::endl;

        return false;
    }

    if ( index >= (int) response_array.size() )
    {
        this->errors << m_error << "Definitions index out of bounds" << std::endl;

        return false;
    }

    bool pass = true;

    std::string response_document_path;

    pass &= dissectLocationObject( *(response_array[index].to_object()) ,
                                     this->errors                       ,
                                     response_document_path             ,
                                     start_line                         ,
                                     start_character                    ,
                                     end_line                           ,
                                     end_character                      );

    if ( response_document_path != this->document_path )
    {
        this->errors << m_error << "Definition path mismatch" << std::endl;

        pass = false;
    }

    return pass;
}

bool ClientImpl::getReferencesAt( int           index           ,
                                  int         & start_line      ,
                                  int         & start_character ,
                                  int         & end_line        ,
                                  int         & end_character   )
{
    if ( response_array_type != REFERENCES )
    {
        this->errors << m_error << "No references currently stored" << std::endl;

        return false;
    }

    if ( index >= (int) response_array.size() )
    {
        this->errors << m_error << "References index out of bounds" << std::endl;

        return false;
    }

    bool pass = true;

    std::string response_document_path;

    pass &= dissectLocationObject( *(response_array[index].to_object()) ,
                                     this->errors                       ,
                                     response_document_path             ,
                                     start_line                         ,
                                     start_character                    ,
                                     end_line                           ,
                                     end_character                      );

    if ( response_document_path != this->document_path )
    {
        this->errors << m_error << "Refererences path mismatch" << std::endl;

        pass = false;
    }

    return pass;
}

bool ClientImpl::getFormattingAt( int           index           ,
                                  int         & start_line      ,
                                  int         & start_character ,
                                  int         & end_line        ,
                                  int         & end_character   ,
                                  std::string & new_text        )
{
    if ( response_array_type != FORMATTING )
    {
        this->errors << m_error << "No formattings currently stored" << std::endl;

        return false;
    }

    if ( index >= (int) response_array.size() )
    {
        this->errors << m_error << "Formattings index out of bounds" << std::endl;

        return false;
    }

    bool pass = true;

    pass &= dissectTextEditObject( *(response_array[index].to_object()) ,
                                     this->errors                       ,
                                     start_line                         ,
                                     start_character                    ,
                                     end_line                           ,
                                     end_character                      ,
                                     new_text                           );

    return pass;
}
} // namespace lsp
} // namespace wasp
