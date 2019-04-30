#include "ServerImpl.h"

namespace wasp {
namespace lsp  {

bool ServerImpl::run()
{
    bool pass = true;

    while(1)
    {
        DataObject  input_object;
        std::string method_name;
        DataObject  output_object;

        pass &= this->connection->read( input_object , this->errors );

        if ( input_object[m_method].is_string() )
        {
            method_name = input_object[m_method].to_string();
        }

        if ( method_name == m_method_initialize )
        {
            pass &= this->handleInitializeRequest( input_object  ,
                                                   output_object );
        }
        else if ( method_name == m_method_initialized )
        {
            pass &= this->handleInitializedNotification( input_object );
        }
        else if ( method_name == m_method_didopen )
        {
            pass &= this->handleDidOpenNotification( input_object  ,
                                                     output_object );
        }
        else if ( method_name == m_method_didchange)
        {
            pass &= this->handleDidChangeNotification( input_object  ,
                                                       output_object );
        }
        else if ( method_name == m_method_completion )
        {
            pass &= this->handleCompletionRequest( input_object  ,
                                                   output_object );
        }
        else if ( method_name == m_method_definition )
        {
            pass &= this->handleDefinitionRequest( input_object  ,
                                                   output_object );;
        }
        else if ( method_name == m_method_references )
        {
            pass &= this->handleReferencesRequest( input_object  ,
                                                   output_object );
        }
        else if ( method_name == m_method_rangeformat )
        {
            pass &= this->handleFormattingRequest( input_object  ,
                                                   output_object );
        }
        else if ( method_name == m_method_documentsymbol )
        {
            pass &= this->handleSymbolsRequest( input_object  ,
                                                output_object );
        }
        else if ( method_name == m_method_didclose )
        {
            pass &= this->handleDidCloseNotification( input_object );
        }
        else if ( method_name == m_method_shutdown )
        {
            pass &= this->handleShutdownRequest( input_object  ,
                                                 output_object );
        }
        else if ( method_name == m_method_exit )
        {
            pass &= this->handleExitNotification( input_object );
        }
        else if ( method_name.empty() )
        {
            pass = false;
            this->errors << m_error_prefix << "Message to server has no method name"
                               << std::endl;
        }
        else
        {
            pass = false;
            this->errors << m_error_prefix << "Message to server has bad method name: "
                               "\"" << method_name << "\"" << std::endl;
        }

        if ( !pass )
        {
            buildErrorResponse( output_object      ,
                                m_internal_error   ,
                                this->errors.str() );
        }

        if ( !output_object.empty() )
        {
            pass &= this->connection->write( output_object , this->errors );
        }

        if ( !pass || method_name == m_method_exit ) break;
    }

    return pass;
}

bool ServerImpl::handleInitializeRequest(
                const DataObject & initializeRequest  ,
                      DataObject & initializeResponse )
{
    bool pass = true;

    pass &= dissectInitializeRequest( initializeRequest         ,
                                      this->errors              ,
                                      this->client_request_id   ,
                                      this->client_process_id   ,
                                      this->client_root_path    ,
                                      this->client_capabilities );

    this->is_initialized = true;

    pass &= buildInitializeResponse( initializeResponse        ,
                                     this->errors              ,
                                     this->client_request_id   ,
                                     this->server_capabilities );

    return pass;
}

bool ServerImpl::handleInitializedNotification(
                const DataObject & initializedNotification )
{
    if (!this->is_initialized)
    {
        this->errors << m_error_prefix << "Server needs to be initialized" << std::endl;
        return false;
    }

    bool pass = true;

    pass &= dissectInitializedNotification( initializedNotification ,
                                            this->errors            );

    return pass;
}

bool ServerImpl::handleDidOpenNotification(
                const DataObject & didOpenNotification            ,
                      DataObject & publishDiagnosticsNotification )
{
    if (!this->is_initialized)
    {
        this->errors << m_error_prefix << "Server needs to be initialized" << std::endl;
        return false;
    }

    bool pass = true;

    pass &= dissectDidOpenNotification( didOpenNotification        ,
                                        this->errors               ,
                                        this->document_path        ,
                                        this->document_language_id ,
                                        this->document_version     ,
                                        this->document_text        );

    this->is_document_open = true;

    DataArray document_diagnostics;

    pass &= this->parseDocumentForDiagnostics( document_diagnostics );

    pass &= buildPublishDiagnosticsNotification( publishDiagnosticsNotification ,
                                                 this->errors                   ,
                                                 this->document_path            ,
                                                 document_diagnostics           );

    return pass;
}

bool ServerImpl::handleDidChangeNotification(
                const DataObject & didChangeNotification          ,
                      DataObject & publishDiagnosticsNotification )
{
    if (!this->is_initialized)
    {
        this->errors << m_error_prefix << "Server needs to be initialized" << std::endl;
        return false;
    }

    if (!this->is_document_open)
    {
        this->errors << m_error_prefix << "Server has no open document" << std::endl;
        return false;
    }

    bool pass = true;

    std::string document_path;
    int         document_version;
    int         start_line;
    int         start_character;
    int         end_line;
    int         end_character;
    int         range_length;
    std::string replacement_text;

    pass &= dissectDidChangeNotification( didChangeNotification  ,
                                          this->errors           ,
                                          document_path          ,
                                          document_version       ,
                                          start_line             ,
                                          start_character        ,
                                          end_line               ,
                                          end_character          ,
                                          range_length           ,
                                          replacement_text       );

    if ( document_path != this->document_path )
    {
        this->errors << m_error_prefix << "Server has different document open" << std::endl;
        return false;
    }

    if (document_version <= this->document_version )
    {
        this->errors << m_error_prefix << "Server sent bad document version" << std::endl;
        return false;
    }

    this->document_version = document_version;

    pass &= this->updateDocumentTextChanges( replacement_text ,
                                             start_line       ,
                                             start_character  ,
                                             end_line         ,
                                             end_character    ,
                                             range_length     );

    DataArray document_diagnostics;

    pass &= this->parseDocumentForDiagnostics( document_diagnostics );

    pass &= buildPublishDiagnosticsNotification( publishDiagnosticsNotification ,
                                                 this->errors                   ,
                                                 this->document_path            ,
                                                 document_diagnostics           );

    return pass;
}

bool ServerImpl::handleCompletionRequest(
                const DataObject & completionRequest  ,
                      DataObject & completionResponse )
{
    if (!this->is_initialized)
    {
        this->errors << m_error_prefix << "Server needs to be initialized" << std::endl;
        return false;
    }

    if (!this->is_document_open)
    {
        this->errors << m_error_prefix << "Server has no open document" << std::endl;
        return false;
    }

    bool pass = true;

    std::string document_path;
    int         line;
    int         character;

    pass &= dissectCompletionRequest( completionRequest       ,
                                      this->errors            ,
                                      this->client_request_id ,
                                      document_path           ,
                                      line                    ,
                                      character               );

    if ( document_path != this->document_path )
    {
        this->errors << m_error_prefix << "Server has different document open" << std::endl;
        return false;
    }

    DataArray completion_items;
    bool      is_incomplete;

    pass &= this->gatherDocumentCompletionItems( completion_items,
                                                 is_incomplete   ,
                                                 line            ,
                                                 character       );

    pass &= buildCompletionResponse( completionResponse      ,
                                     this->errors            ,
                                     this->client_request_id ,
                                     is_incomplete           ,
                                     completion_items        );

    return pass;
}

bool ServerImpl::handleDefinitionRequest(
                const DataObject & definitionRequest  ,
                      DataObject & definitionResponse )
{
    if (!this->is_initialized)
    {
        this->errors << m_error_prefix << "Server needs to be initialized" << std::endl;
        return false;
    }

    if (!this->is_document_open)
    {
        this->errors << m_error_prefix << "Server has no open document" << std::endl;
        return false;
    }

    bool pass = true;

    std::string document_path;
    int         line;
    int         character;

    pass &= dissectDefinitionRequest( definitionRequest       ,
                                      this->errors            ,
                                      this->client_request_id ,
                                      document_path           ,
                                      line                    ,
                                      character               );

    if ( document_path != this->document_path )
    {
        this->errors << m_error_prefix << "Server has different document open" << std::endl;
        return false;
    }

    DataArray definition_locations;

    pass &= this->gatherDocumentDefinitionLocations( definition_locations ,
                                                     line                 ,
                                                     character            );


    pass &= buildLocationsResponse( definitionResponse      ,
                                    this->errors            ,
                                    this->client_request_id ,
                                    definition_locations    );

    return pass;
}

bool ServerImpl::handleReferencesRequest(
                const DataObject & referencesRequest  ,
                      DataObject & referencesResponse )
{
    if (!this->is_initialized)
    {
        this->errors << m_error_prefix << "Server needs to be initialized" << std::endl;
        return false;
    }

    if (!this->is_document_open)
    {
        this->errors << m_error_prefix << "Server has no open document" << std::endl;
        return false;
    }

    bool pass = true;

    std::string document_path;
    int         line;
    int         character;
    bool        include_declaration;

    pass &= dissectReferencesRequest( referencesRequest       ,
                                      this->errors            ,
                                      this->client_request_id ,
                                      document_path           ,
                                      line                    ,
                                      character               ,
                                      include_declaration     );

    if ( document_path != this->document_path )
    {
        this->errors << m_error_prefix << "Server has different document open" << std::endl;
        return false;
    }

    DataArray references_locations;

    pass &= this->gatherDocumentReferencesLocations( references_locations ,
                                                     line                 ,
                                                     character            ,
                                                     include_declaration  );

    pass &= buildLocationsResponse( referencesResponse      ,
                                    this->errors            ,
                                    this->client_request_id ,
                                    references_locations    );

    return pass;
}

bool ServerImpl::handleFormattingRequest(
                const DataObject & formattingRequest  ,
                      DataObject & formattingResponse )
{
    if (!this->is_initialized)
    {
        this->errors << m_error_prefix << "Server needs to be initialized" << std::endl;
        return false;
    }

    if (!this->is_document_open)
    {
        this->errors << m_error_prefix << "Server has no open document" << std::endl;
        return false;
    }

    bool pass = true;

    std::string document_path;
    int         start_line;
    int         start_character;
    int         end_line;
    int         end_character;
    int         tab_size;
    bool        insert_spaces;

    pass &= dissectFormattingRequest( formattingRequest       ,
                                      this->errors            ,
                                      this->client_request_id ,
                                      document_path           ,
                                      start_line              ,
                                      start_character         ,
                                      end_line                ,
                                      end_character           ,
                                      tab_size                ,
                                      insert_spaces           );

    if ( document_path != this->document_path )
    {
        this->errors << m_error_prefix << "Server has different document open" << std::endl;
        return false;
    }

    DataArray formatting_textedits;

    pass &= this->gatherDocumentFormattingTextEdits( formatting_textedits ,
                                                     start_line           ,
                                                     start_character      ,
                                                     end_line             ,
                                                     end_character        ,
                                                     tab_size             ,
                                                     insert_spaces        );

    pass &= buildFormattingResponse( formattingResponse      ,
                                     this->errors            ,
                                     this->client_request_id ,
                                     formatting_textedits    );

    return pass;
}

bool ServerImpl::handleSymbolsRequest(
                const DataObject & symbolsRequest  ,
                      DataObject & symbolsResponse )
{
    if (!this->is_initialized)
    {
        this->errors << m_error_prefix << "Server needs to be initialized" << std::endl;
        return false;
    }

    if (!this->is_document_open)
    {
        this->errors << m_error_prefix << "Server has no open document" << std::endl;
        return false;
    }

    bool pass = true;

    std::string document_path;

    pass &= dissectSymbolsRequest( symbolsRequest          ,
                                   this->errors            ,
                                   this->client_request_id ,
                                   document_path           );

    if ( document_path != this->document_path )
    {
        this->errors << m_error_prefix << "Server has different document open" << std::endl;
        return false;
    }

    DataArray document_symbols;

    pass &= this->gatherDocumentSymbols( document_symbols );

    pass &= buildSymbolsResponse( symbolsResponse         ,
                                  this->errors            ,
                                  this->client_request_id ,
                                  document_symbols        );

    return pass;
}

bool ServerImpl::handleDidCloseNotification(
                const DataObject & didCloseNotification )
{
    if (!this->is_initialized)
    {
        this->errors << m_error_prefix << "Server needs to be initialized" << std::endl;
        return false;
    }

    if (!this->is_document_open)
    {
        this->errors << m_error_prefix << "Server has no open document" << std::endl;
        return false;
    }

    bool pass = true;

    std::string document_path;

    pass &= dissectDidCloseNotification( didCloseNotification ,
                                         this->errors         ,
                                         document_path        );

    if ( document_path != this->document_path )
    {
        this->errors << m_error_prefix << "Server has different document open" << std::endl;
        return false;
    }

    this->is_document_open = false;

    return pass;
}

bool ServerImpl::handleShutdownRequest(
                const DataObject & shutdownRequest  ,
                      DataObject & shutdownResponse )
{
    if (!this->is_initialized)
    {
        this->errors << m_error_prefix << "Server needs to be initialized" << std::endl;
        return false;
    }

    if (this->is_document_open)
    {
        this->errors << m_error_prefix << "Server document needs to be closed" << std::endl;
        return false;
    }

    bool pass = true;

    pass &= dissectShutdownRequest( shutdownRequest         ,
                                    this->errors            ,
                                    this->client_request_id );

    this->is_initialized = false;

    pass &= buildShutdownResponse( shutdownResponse        ,
                                   this->errors            ,
                                   this->client_request_id );

    return pass;
}

bool ServerImpl::handleExitNotification(
                const DataObject & exitNotification )
{
    if (this->is_initialized)
    {
        this->errors << m_error_prefix << "Server needs to be shutdown" << std::endl;
        return false;
    }

    bool pass = true;

    pass &= dissectExitNotification( exitNotification ,
                                     this->errors     );

    return pass;
}

} // namespace lsp
} // namespace wasp
