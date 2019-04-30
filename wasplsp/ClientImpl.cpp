
#include "waspcore/Object.h"
#include "wasplsp/ClientImpl.h"

namespace wasp {
namespace lsp  {

bool ClientImpl::connect( Connection::SP connection )
{
    bool pass = true;

    if ( this->is_connected )
    {
        this->errors << m_error_prefix << "Client already connected" << std::endl;

        pass = false;
    }

    if ( pass )
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
        this->errors << m_error_prefix << "Client not connected" << std::endl;

        return false;
    }

    if ( this->is_initialized )
    {
        this->errors << m_error_prefix << "Connection already initialized" << std::endl;

        return false;
    }

    bool pass = true;

    this->incrementRequestID();

    DataObject client_object;
    DataObject client_capabilities;

    this->response = std::make_shared<DataObject>();

    pass &= buildInitializeRequest( client_object       ,
                                    this->errors        ,
                                    this->request_id    ,
                                    0000                ,
                                    "temp-root-uri"     ,
                                    client_capabilities );

    pass &= connection->write( client_object , this->errors );

    pass &= connection->read( *(this->response) , this->errors );

    pass &= checkErrorResponse( *(this->response) , this->errors );

    wasp_check( verifyInitializeResponse( *(this->response) ) );

    if ( pass )
    {
        this->response_type = INITIALIZE;

        this->is_initialized = true;
    }

    return pass;
}

bool ClientImpl::doInitialized()
{
    if ( !this->is_connected )
    {
        this->errors << m_error_prefix << "Client not connected" << std::endl;

        return false;
    }

    if ( !this->is_initialized )
    {
        this->errors << m_error_prefix << "Connection not initialized" << std::endl;

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
        this->errors << m_error_prefix << "Client not connected" << std::endl;

        return false;
    }

    if ( !this->is_initialized )
    {
        this->errors << m_error_prefix << "Connection not initialized" << std::endl;

        return false;
    }

    if ( this->is_document_open )
    {
        this->errors << m_error_prefix << "Document already open" << std::endl;

        return false;
    }

    bool pass = true;

    this->document_path = document_path;

    this->incrementDocumentVersion();

    DataObject  client_object;
    this->response = std::make_shared<DataObject>();
    std::string response_document_path;

    pass &= buildDidOpenNotification( client_object          ,
                                      this->errors           ,
                                      this->document_path    ,
                                      document_language_id   ,
                                      this->document_version ,
                                      document_text          );

    pass &= connection->write( client_object , this->errors );

    pass &= connection->read( *(this->response) , this->errors );

    pass &= checkErrorResponse( *(this->response) , this->errors );

    wasp_check( verifyDiagnosticResponse( *(this->response) ) );

    if ( pass )
    {
        this->response_type = DIAGNOSTIC;

        this->is_document_open = true;
    }

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
        this->errors << m_error_prefix << "Client not connected" << std::endl;

        return false;
    }

    if ( !this->is_initialized )
    {
        this->errors << m_error_prefix << "Connection not initialized" << std::endl;

        return false;
    }

    if ( !this->is_document_open )
    {
        this->errors << m_error_prefix << "Document not open" << std::endl;

        return false;
    }

    bool pass = true;

    this->incrementDocumentVersion();

    DataObject  client_object;
    this->response = std::make_shared<DataObject>();
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

    pass &= connection->read( *(this->response) , this->errors );

    pass &= checkErrorResponse( *(this->response) , this->errors );

    wasp_check( verifyDiagnosticResponse( *(this->response) ) );

    if ( pass )
    {
        this->response_type = DIAGNOSTIC;
    }

    return pass;
}

bool ClientImpl::doDocumentCompletion( int line      ,
                                       int character )
{
    if ( !this->is_connected )
    {
        this->errors << m_error_prefix << "Client not connected" << std::endl;

        return false;
    }

    if ( !this->is_initialized )
    {
        this->errors << m_error_prefix << "Connection not initialized" << std::endl;

        return false;
    }

    if ( !this->is_document_open )
    {
        this->errors << m_error_prefix << "Document not open" << std::endl;

        return false;
    }

    bool pass = true;

    this->incrementRequestID();

    DataObject client_object;

    this->response = std::make_shared<DataObject>();

    pass &= buildCompletionRequest( client_object       ,
                                    this->errors        ,
                                    this->request_id    ,
                                    this->document_path ,
                                    line                ,
                                    character           );

    pass &= connection->write( client_object , this->errors );

    pass &= connection->read( *(this->response) , this->errors );

    pass &= checkErrorResponse( *(this->response) , this->errors );

    wasp_check( verifyCompletionResponse( *(this->response) ) );

    if ( pass )
    {
        this->response_type = COMPLETION;
    }

    return pass;
}

bool ClientImpl::doDocumentDefinition( int line      ,
                                       int character )
{
    if ( !this->is_connected )
    {
        this->errors << m_error_prefix << "Client not connected" << std::endl;

        return false;
    }

    if ( !this->is_initialized )
    {
        this->errors << m_error_prefix << "Connection not initialized" << std::endl;

        return false;
    }

    if ( !this->is_document_open )
    {
        this->errors << m_error_prefix << "Document not open" << std::endl;

        return false;
    }

    bool pass = true;

    this->incrementRequestID();

    DataObject client_object;

    this->response = std::make_shared<DataObject>();

    pass &= buildDefinitionRequest( client_object       ,
                                    this->errors        ,
                                    this->request_id    ,
                                    this->document_path ,
                                    line                ,
                                    character           );

    pass &= connection->write( client_object , this->errors );

    pass &= connection->read( *(this->response) , this->errors );

    pass &= checkErrorResponse( *(this->response) , this->errors );

    wasp_check( verifyDefinitionResponse( *(this->response) ) );

    if ( pass )
    {
        this->response_type = DEFINITION;
    }

    return pass;
}

bool ClientImpl::doDocumentReferences( int  line                ,
                                       int  character           ,
                                       bool include_declaration )
{
    if ( !this->is_connected )
    {
        this->errors << m_error_prefix << "Client not connected" << std::endl;

        return false;
    }

    if ( !this->is_initialized )
    {
        this->errors << m_error_prefix << "Connection not initialized" << std::endl;

        return false;
    }

    if ( !this->is_document_open )
    {
        this->errors << m_error_prefix << "Document not open" << std::endl;

        return false;
    }

    bool pass = true;

    this->incrementRequestID();

    DataObject client_object;

    this->response = std::make_shared<DataObject>();

    pass &= buildReferencesRequest( client_object       ,
                                    this->errors        ,
                                    this->request_id    ,
                                    this->document_path ,
                                    line                ,
                                    character           ,
                                    include_declaration );

    pass &= connection->write( client_object , this->errors );

    pass &= connection->read( *(this->response) , this->errors );

    pass &= checkErrorResponse( *(this->response) , this->errors );

    wasp_check( verifyReferencesResponse( *(this->response) ) );

    if ( pass )
    {
        this->response_type = REFERENCES;
    }

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
        this->errors << m_error_prefix << "Client not connected" << std::endl;

        return false;
    }

    if ( !this->is_initialized )
    {
        this->errors << m_error_prefix << "Connection not initialized" << std::endl;

        return false;
    }

    if ( !this->is_document_open )
    {
        this->errors << m_error_prefix << "Document not open" << std::endl;

        return false;
    }

    bool pass = true;

    this->incrementRequestID();

    DataObject client_object;

    this->response = std::make_shared<DataObject>();

    pass &= buildFormattingRequest( client_object       ,
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

    pass &= connection->read( *(this->response) , this->errors );

    pass &= checkErrorResponse( *(this->response) , this->errors );

    wasp_check( verifyFormattingResponse( *(this->response) ) );

    if ( pass )
    {
        this->response_type = FORMATTING;
    }

    return pass;
}

bool ClientImpl::doDocumentSymbols()
{
    if ( !this->is_connected )
    {
        this->errors << m_error_prefix << "Client not connected" << std::endl;

        return false;
    }

    if ( !this->is_initialized )
    {
        this->errors << m_error_prefix << "Connection not initialized" << std::endl;

        return false;
    }

    if ( !this->is_document_open )
    {
        this->errors << m_error_prefix << "Document not open" << std::endl;

        return false;
    }

    bool pass = true;

    this->incrementRequestID();

    DataObject client_object;

    this->response = std::make_shared<DataObject>();

    pass &= buildSymbolsRequest( client_object       ,
                                 this->errors        ,
                                 this->request_id    ,
                                 this->document_path );

    pass &= connection->write( client_object , this->errors );

    pass &= connection->read( *(this->response) , this->errors );

    pass &= checkErrorResponse( *(this->response) , this->errors );

    wasp_check( verifySymbolsResponse( *(this->response) ) );

    if ( pass )
    {
        this->response_type = SYMBOLS;
    }

    return pass;
}

bool ClientImpl::doDocumentClose()
{
    if ( !this->is_connected )
    {
        this->errors << m_error_prefix << "Client not connected" << std::endl;

        return false;
    }

    if ( !this->is_initialized )
    {
        this->errors << m_error_prefix << "Connection not initialized" << std::endl;

        return false;
    }

    if ( !this->is_document_open )
    {
        this->errors << m_error_prefix << "Document not open" << std::endl;

        return false;
    }

    bool pass = true;

    DataObject client_object;

    pass &= buildDidCloseNotification( client_object       ,
                                       this->errors        ,
                                       this->document_path );

    pass &= connection->write( client_object , this->errors );

    if ( pass )
    {
        this->is_document_open = false;
    }

    return pass;
}

bool ClientImpl::doShutdown()
{
    if ( !this->is_connected )
    {
        this->errors << m_error_prefix << "Client not connected" << std::endl;

        return false;
    }

    if ( !this->is_initialized )
    {
        this->errors << m_error_prefix << "Connection needs to be initialized" << std::endl;

        return false;
    }

    if ( this->is_document_open )
    {
        this->errors << m_error_prefix << "Document needs to be closed" << std::endl;

        return false;
    }

    bool pass = true;

    this->incrementRequestID();

    DataObject client_object;

    this->response = std::make_shared<DataObject>();

    pass &= buildShutdownRequest( client_object    ,
                                  this->errors     ,
                                  this->request_id );

    pass &= connection->write( client_object , this->errors );

    pass &= connection->read( *(this->response) , this->errors );

    pass &= checkErrorResponse( *(this->response) , this->errors );

    wasp_check( verifyShutdownResponse( *(this->response) ) );

    if ( pass )
    {
        this->response_type = SHUTDOWN;

        this->is_initialized = false;
    }

    return pass;
}

bool ClientImpl::doExit()
{
    bool pass = true;

    if ( !this->is_connected )
    {
        this->errors << m_error_prefix << "Client not connected" << std::endl;

        return false;
    }

    if ( this->is_initialized )
    {
        this->errors << m_error_prefix << "Connection needs to be shutdown" << std::endl;

        return false;
    }

    DataObject client_object;

    pass &= buildExitNotification( client_object ,
                                   this->errors  );

    pass &= connection->write( client_object , this->errors );

    if ( pass )
    {
        this->is_connected = false;
    }

    return pass;
}

int ClientImpl::getDiagnosticSize()
{
    int size = 0;

    if ( this->response_type == DIAGNOSTIC )
    {
        size = getDiagnosticResponseArray(*this->response)->size();
    }

    return size;
}

int ClientImpl::getCompletionSize()
{
    int size = 0;

    if ( this->response_type == COMPLETION )
    {
        size = getCompletionResponseArray(*this->response)->size();
    }

    return size;
}

int ClientImpl::getDefinitionSize()
{
    int size = 0;

    if ( this->response_type == DEFINITION )
    {
        size = getDefinitionResponseArray(*this->response)->size();
    }

    return size;
}

int ClientImpl::getReferencesSize()
{
    int size = 0;

    if ( this->response_type == REFERENCES )
    {
        size = getReferencesResponseArray(*this->response)->size();
    }

    return size;
}

int ClientImpl::getFormattingSize()
{
    int size = 0;

    if ( this->response_type == FORMATTING )
    {
        size = getFormattingResponseArray(*this->response)->size();
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
    if ( this->response_type != DIAGNOSTIC )
    {
        this->errors << m_error_prefix << "No diagnostics currently stored" << std::endl;

        return false;
    }

    if ( index >= this->getDiagnosticSize() )
    {
        this->errors << m_error_prefix << "Diagnostics index out of bounds" << std::endl;

        return false;
    }

    bool pass = true;

    const DataObject & diagnosticObject =
            *getDiagnosticResponseArray(*this->response)->at(index).to_object();

    pass &= dissectDiagnosticObject( diagnosticObject ,
                                     this->errors     ,
                                     start_line       ,
                                     start_character  ,
                                     end_line         ,
                                     end_character    ,
                                     severity         ,
                                     code             ,
                                     source           ,
                                     message          );

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
    if ( this->response_type != COMPLETION )
    {
        this->errors << m_error_prefix << "No completions currently stored" << std::endl;

        return false;
    }

    if ( index >= this->getCompletionSize() )
    {
        this->errors << m_error_prefix << "Completions index out of bounds" << std::endl;

        return false;
    }

    bool pass = true;

    const DataObject & completionObject =
            *getCompletionResponseArray(*this->response)->at(index).to_object();

    pass &= dissectCompletionObject( completionObject ,
                                     this->errors     ,
                                     label            ,
                                     start_line       ,
                                     start_character  ,
                                     end_line         ,
                                     end_character    ,
                                     new_text         ,
                                     kind             ,
                                     detail           ,
                                     documentation    ,
                                     deprecated       ,
                                     preselect        );

    return pass;
}

bool ClientImpl::getDefinitionAt( int   index           ,
                                  int & start_line      ,
                                  int & start_character ,
                                  int & end_line        ,
                                  int & end_character   )
{
    if ( this->response_type != DEFINITION )
    {
        this->errors << m_error_prefix << "No definitions currently stored" << std::endl;

        return false;
    }

    if ( index >= this->getDefinitionSize() )
    {
        this->errors << m_error_prefix << "Definitions index out of bounds" << std::endl;

        return false;
    }

    bool pass = true;

    std::string response_document_path;

    const DataObject & locationObject =
            *getDefinitionResponseArray(*this->response)->at(index).to_object();

    pass &= dissectLocationObject( locationObject         ,
                                   this->errors           ,
                                   response_document_path ,
                                   start_line             ,
                                   start_character        ,
                                   end_line               ,
                                   end_character          );

    if ( response_document_path != this->document_path )
    {
        this->errors << m_error_prefix << "Definition path mismatch" << std::endl;

        pass = false;
    }

    return pass;
}

bool ClientImpl::getReferencesAt( int   index           ,
                                  int & start_line      ,
                                  int & start_character ,
                                  int & end_line        ,
                                  int & end_character   )
{
    if ( this->response_type != REFERENCES )
    {
        this->errors << m_error_prefix << "No references currently stored" << std::endl;

        return false;
    }

    if ( index >= this->getReferencesSize() )
    {
        this->errors << m_error_prefix << "References index out of bounds" << std::endl;

        return false;
    }

    bool pass = true;

    std::string response_document_path;

    const DataObject & locationObject =
            *getReferencesResponseArray(*this->response)->at(index).to_object();

    pass &= dissectLocationObject( locationObject         ,
                                   this->errors           ,
                                   response_document_path ,
                                   start_line             ,
                                   start_character        ,
                                   end_line               ,
                                   end_character          );

    if ( response_document_path != this->document_path )
    {
        this->errors << m_error_prefix << "Refererences path mismatch" << std::endl;

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
    if ( this->response_type != FORMATTING )
    {
        this->errors << m_error_prefix << "No formattings currently stored" << std::endl;

        return false;
    }

    if ( index >= this->getFormattingSize() )
    {
        this->errors << m_error_prefix << "Formattings index out of bounds" << std::endl;

        return false;
    }

    bool pass = true;

    const DataObject & textEditObject =
            *getFormattingResponseArray(*this->response)->at(index).to_object();

    pass &= dissectTextEditObject( textEditObject  ,
                                   this->errors    ,
                                   start_line      ,
                                   start_character ,
                                   end_line        ,
                                   end_character   ,
                                   new_text        );

    return pass;
}

} // namespace lsp
} // namespace wasp
