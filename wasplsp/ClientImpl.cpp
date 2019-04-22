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

bool ClientImpl::initialize()
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

    DataObject client_object;
    DataObject client_capabilities;
    DataObject response_object;
    int        response_request_id;
    DataObject response_capabilities;

    this->incrementRequestID();

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

bool ClientImpl::initialized()
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

bool ClientImpl::opened( const std::string & document_path        ,
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

    DataObject  client_object;
    DataObject  response_object;
    std::string response_uri;

    this->document_path = document_path;

    this->incrementDocumentVersion();

    pass &= buildDidOpenNotification( client_object          ,
                                      this->errors           ,
                                      this->document_path    ,
                                      document_language_id   ,
                                      this->document_version ,
                                      document_text          );

    pass &= connection->write( client_object , this->errors );

    pass &= connection->read( response_object , this->errors );

    pass &= dissectPublishDiagnosticsNotification( response_object      ,
                                                   this->errors         ,
                                                   response_uri         ,
                                                   this->response_array );

    if ( response_uri != this->document_path )
    {
        this->errors << m_error << "Diagnositics uri mismatch" << std::endl;

        pass = false;
    }

    this->response_array_type = DIAGNOSTIC;

    this->is_document_open = true;

    return pass;
}

bool ClientImpl::changed( int                 start_line        ,
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

    DataObject  client_object;
    DataObject  response_object;
    std::string response_uri;

    this->incrementDocumentVersion();

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

    pass &= dissectPublishDiagnosticsNotification( response_object      ,
                                                   this->errors         ,
                                                   response_uri         ,
                                                   this->response_array );

    if ( response_uri != this->document_path )
    {
        this->errors << m_error << "Diagnositics uri mismatch" << std::endl;

        pass = false;
    }

    this->response_array_type = DIAGNOSTIC;

    return pass;
}

bool ClientImpl::completion( int line      ,
                             int character )
{
    bool pass = true;

    /* * * TODO * * */

    return pass;
}

bool ClientImpl::definition( int line      ,
                             int character )
{
    bool pass = true;

    /* * * TODO * * */

    return pass;
}

bool ClientImpl::references( int  line                ,
                             int  character           ,
                             bool include_declaration )
{
    bool pass = true;

    /* * * TODO * * */

    return pass;
}

bool ClientImpl::formatting( int  start_line      ,
                             int  start_character ,
                             int  end_line        ,
                             int  end_character   ,
                             int  tab_size        ,
                             bool insert_spaces   )
{
    bool pass = true;

    /* * * TODO * * */

    return pass;
}

bool ClientImpl::closed()
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

bool ClientImpl::shutdown()
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

    DataObject client_object;
    DataObject response_object;
    int        response_request_id;

    this->incrementRequestID();

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

bool ClientImpl::exit()
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
    int size = 0;

    if ( response_array_type == DIAGNOSTIC )
    {
        size = response_array.size();
    }

    return size;
}

int ClientImpl::getCompletionSize()
{
    int size = 0;

    if ( response_array_type == COMPLETION )
    {
        size = response_array.size();
    }

    return size;
}

int ClientImpl::getDefinitionSize()
{
    int size = 0;

    if ( response_array_type == DEFINITION )
    {
        size = response_array.size();
    }

    return size;
}

int ClientImpl::getReferencesSize()
{
    int size = 0;

    if ( response_array_type == REFERENCES )
    {
        size = response_array.size();
    }

    return size;
}

int ClientImpl::getFormattingSize()
{
    int size = 0;

    if ( response_array_type == FORMATTING )
    {
        size = response_array.size();
    }

    return size;
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

} // namespace lsp
} // namespace wasp
