#include "TestServer.h"

namespace wasp {
namespace lsp  {

bool TestServer::run()
{
    bool pass = true;

    while(1)
    {
        DataObject  input_object;
        std::string method_name;
        DataObject  output_object;

        pass &= this->connection->serverRead( input_object ,
                                              this->errors );

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
            pass &= this->handleRangeFormattingRequest( input_object  ,
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
            this->errors << m_error << "Message to server has no method name"
                               << std::endl;
        }
        else
        {
            pass = false;
            this->errors << m_error << "Message to server has bad method name: "
                               "\"" << method_name << "\"" << std::endl;
        }

        if ( !pass || method_name == m_method_exit ) break;

        if ( !output_object.empty() )
        {
            pass &= this->connection->serverWrite( output_object ,
                                                   this->errors  );
        }
    }

    return pass;
}

bool TestServer::handleInitializeRequest(
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

bool TestServer::handleInitializedNotification(
                const DataObject & initializedNotification )
{
    if (!this->is_initialized)
    {
        this->errors << m_error << "Server needs to be initialized" << std::endl;
        return false;
    }

    bool pass = true;

    pass &= dissectInitializedNotification( initializedNotification ,
                                            this->errors            );

    return pass;
}

bool TestServer::handleDidOpenNotification(
                const DataObject & didOpenNotification            ,
                      DataObject & publishDiagnosticsNotification )
{
    if (!this->is_initialized)
    {
        this->errors << m_error << "Server needs to be initialized" << std::endl;
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

bool TestServer::handleDidChangeNotification(
                const DataObject & didChangeNotification          ,
                      DataObject & publishDiagnosticsNotification )
{
    if (!this->is_initialized)
    {
        this->errors << m_error << "Server needs to be initialized" << std::endl;
        return false;
    }

    if (!this->is_document_open)
    {
        this->errors << m_error << "Server has no open document" << std::endl;
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
        this->errors << m_error << "Server has different document open" << std::endl;
        return false;
    }

    if (document_version <= this->document_version )
    {
        this->errors << m_error << "Server sent bad document version" << std::endl;
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

bool TestServer::handleCompletionRequest(
                const DataObject & completionRequest  ,
                      DataObject & completionResponse )
{
    if (!this->is_initialized)
    {
        this->errors << m_error << "Server needs to be initialized" << std::endl;
        return false;
    }

    if (!this->is_document_open)
    {
        this->errors << m_error << "Server has no open document" << std::endl;
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
        this->errors << m_error << "Server has different document open" << std::endl;
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

bool TestServer::handleDefinitionRequest(
                const DataObject & definitionRequest  ,
                      DataObject & definitionResponse )
{
    if (!this->is_initialized)
    {
        this->errors << m_error << "Server needs to be initialized" << std::endl;
        return false;
    }

    if (!this->is_document_open)
    {
        this->errors << m_error << "Server has no open document" << std::endl;
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
        this->errors << m_error << "Server has different document open" << std::endl;
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

bool TestServer::handleReferencesRequest(
                const DataObject & referencesRequest  ,
                      DataObject & referencesResponse )
{
    if (!this->is_initialized)
    {
        this->errors << m_error << "Server needs to be initialized" << std::endl;
        return false;
    }

    if (!this->is_document_open)
    {
        this->errors << m_error << "Server has no open document" << std::endl;
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
        this->errors << m_error << "Server has different document open" << std::endl;
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

bool TestServer::handleRangeFormattingRequest(
                const DataObject & rangeFormattingRequest  ,
                      DataObject & rangeFormattingResponse )
{
    if (!this->is_initialized)
    {
        this->errors << m_error << "Server needs to be initialized" << std::endl;
        return false;
    }

    if (!this->is_document_open)
    {
        this->errors << m_error << "Server has no open document" << std::endl;
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

    pass &= dissectRangeFormattingRequest( rangeFormattingRequest  ,
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
        this->errors << m_error << "Server has different document open" << std::endl;
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

    pass &= buildRangeFormattingResponse( rangeFormattingResponse ,
                                          this->errors            ,
                                          this->client_request_id ,
                                          formatting_textedits    );

    return pass;
}

bool TestServer::handleDidCloseNotification(
                const DataObject & didCloseNotification )
{
    if (!this->is_initialized)
    {
        this->errors << m_error << "Server needs to be initialized" << std::endl;
        return false;
    }

    if (!this->is_document_open)
    {
        this->errors << m_error << "Server has no open document" << std::endl;
        return false;
    }

    bool pass = true;

    std::string document_path;

    pass &= dissectDidCloseNotification( didCloseNotification ,
                                         this->errors         ,
                                         document_path        );

    if ( document_path != this->document_path )
    {
        this->errors << m_error << "Server has different document open" << std::endl;
        return false;
    }

    this->is_document_open = false;

    return pass;
}

bool TestServer::handleShutdownRequest(
                const DataObject & shutdownRequest  ,
                      DataObject & shutdownResponse )
{
    if (!this->is_initialized)
    {
        this->errors << m_error << "Server needs to be initialized" << std::endl;
        return false;
    }

    if (this->is_document_open)
    {
        this->errors << m_error << "Server document needs to be closed" << std::endl;
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

bool TestServer::handleExitNotification(
                const DataObject & exitNotification )
{
    if (this->is_initialized)
    {
        this->errors << m_error << "Server needs to be shutdown" << std::endl;
        return false;
    }

    bool pass = true;

    pass &= dissectExitNotification( exitNotification ,
                                     this->errors     );

    return pass;
}

bool TestServer::parseDocumentForDiagnostics(
                      DataArray & diagnosticsList )
{
    if (!this->is_initialized)
    {
        this->errors << m_error << "Server needs to be initialized" << std::endl;
        return false;
    }

    if (!this->is_document_open)
    {
        this->errors << m_error << "Server has no open document" << std::endl;
        return false;
    }

    bool pass = true;

    DataObject diagnostic;

    if (this->document_text == "test\ntext\n1\nstring\n")
    {
        pass &= buildDiagnosticObject( diagnostic         ,
                                       this->errors       ,
                                       20                 ,
                                       16                 ,
                                       20                 ,
                                       27                 ,
                                       1                  ,
                                       "test.code.11"     ,
                                       "test_source_11"   ,
                                       "Test message 11." );

        diagnosticsList.push_back(diagnostic);

        pass &= buildDiagnosticObject( diagnostic         ,
                                       this->errors       ,
                                       28                 ,
                                       56                 ,
                                       34                 ,
                                       27                 ,
                                       2                  ,
                                       "test.code.22"     ,
                                       "test_source_22"   ,
                                       "Test message 22." );

        diagnosticsList.push_back(diagnostic);

        pass &= buildDiagnosticObject( diagnostic         ,
                                       this->errors       ,
                                       47                 ,
                                       36                 ,
                                       47                 ,
                                       43                 ,
                                       3                  ,
                                       "test.code.33"     ,
                                       "test_source_33"   ,
                                       "Test message 33." );

        diagnosticsList.push_back(diagnostic);
    }

    else if (this->document_text == "test\ntext\n2\nstring\n")
    {
        pass &= buildDiagnosticObject( diagnostic         ,
                                       this->errors       ,
                                       67                 ,
                                       45                 ,
                                       68                 ,
                                       16                 ,
                                       4                  ,
                                       "test.code.44"     ,
                                       "test_source_44"   ,
                                       "Test message 44." );

        diagnosticsList.push_back(diagnostic);

        pass &= buildDiagnosticObject( diagnostic         ,
                                       this->errors       ,
                                       87                 ,
                                       17                 ,
                                       88                 ,
                                       12                 ,
                                       1                  ,
                                       "test.code.55"     ,
                                       "test_source_55"   ,
                                       "Test message 55." );

        diagnosticsList.push_back(diagnostic);
    }

    return pass;
}

bool TestServer::updateDocumentTextChanges(
                const std::string & replacement_text ,
                      int           start_line       ,
                      int           start_character  ,
                      int           end_line         ,
                      int           end_character    ,
                      int           range_length     )
{
    if (!this->is_initialized)
    {
        this->errors << m_error << "Server needs to be initialized" << std::endl;
        return false;
    }

    if (!this->is_document_open)
    {
        this->errors << m_error << "Server has no open document" << std::endl;
        return false;
    }

    bool pass = true;

    if ( start_line      == 0 &&
         start_character == 0 &&
         end_line        == 3 &&
         end_character   == 7 &&
         range_length    == 0 )
    {
        this->document_text = replacement_text;
    }

    return pass;
}

bool TestServer::gatherDocumentCompletionItems(
                      DataArray & completionItems  ,
                      bool      & is_incomplete    ,
                      int         line             ,
                      int         character        )
{
    if (!this->is_initialized)
    {
        this->errors << m_error << "Server needs to be initialized" << std::endl;
        return false;
    }

    if (!this->is_document_open)
    {
        this->errors << m_error << "Server has no open document" << std::endl;
        return false;
    }

    bool pass = true;

    DataObject completion_item;

    if ( line      == 4 &&
         character == 2 )
    {
        pass &= buildCompletionObject( completion_item        ,
                                       this->errors           ,
                                       "test-label-1"         ,
                                       11                     ,
                                       11                     ,
                                       11                     ,
                                       11                     ,
                                       "test-insert-text-1"   ,
                                       1                      ,
                                       "test type info 1"     ,
                                       "test documentation 1" ,
                                       false                  ,
                                       true                   );

        completionItems.push_back(completion_item);

        pass &= buildCompletionObject( completion_item        ,
                                       this->errors           ,
                                       "test-label-2"         ,
                                       22                     ,
                                       22                     ,
                                       22                     ,
                                       22                     ,
                                       "test-insert-text-2"   ,
                                       2                      ,
                                       "test type info 2"     ,
                                       "test documentation 2" ,
                                       false                  ,
                                       false                  );

        completionItems.push_back(completion_item);

        pass &= buildCompletionObject( completion_item        ,
                                       this->errors           ,
                                       "test-label-3"         ,
                                       33                     ,
                                       33                     ,
                                       33                     ,
                                       33                     ,
                                       "test-insert-text-3"   ,
                                       3                      ,
                                       "test type info 3"     ,
                                       "test documentation 3" ,
                                       false                  ,
                                       false                  );

        completionItems.push_back(completion_item);
    }

    is_incomplete = false;

    return pass;
}

bool TestServer::gatherDocumentDefinitionLocations(
                      DataArray & definitionLocations ,
                      int         line                ,
                      int         character           )
{
    if (!this->is_initialized)
    {
        this->errors << m_error << "Server needs to be initialized" << std::endl;
        return false;
    }

    if (!this->is_document_open)
    {
        this->errors << m_error << "Server has no open document" << std::endl;
        return false;
    }

    bool pass = true;

    DataObject location_object;

    if ( line      == 2 &&
         character == 5 )
    {
        pass &= buildLocationObject( location_object       ,
                                     this->errors          ,
                                     this->document_path   ,
                                     11                    ,
                                     11                    ,
                                     11                    ,
                                     11                    );

        definitionLocations.push_back(location_object);

        pass &= buildLocationObject( location_object       ,
                                     this->errors          ,
                                     this->document_path   ,
                                     22                    ,
                                     22                    ,
                                     22                    ,
                                     22                    );

        definitionLocations.push_back(location_object);

        pass &= buildLocationObject( location_object       ,
                                     this->errors          ,
                                     this->document_path   ,
                                     33                    ,
                                     33                    ,
                                     33                    ,
                                     33                    );

        definitionLocations.push_back(location_object);
    }

    return pass;
}

bool TestServer::gatherDocumentReferencesLocations(
                      DataArray & referencesLocations ,
                      int         line                ,
                      int         character           ,
                      bool        include_declaration )
{
    if (!this->is_initialized)
    {
        this->errors << m_error << "Server needs to be initialized" << std::endl;
        return false;
    }

    if (!this->is_document_open)
    {
        this->errors << m_error << "Server has no open document" << std::endl;
        return false;
    }

    bool pass = true;

    DataObject location_object;

    if ( line                == 1     &&
         character           == 3     &&
         include_declaration == false )
    {
        pass &= buildLocationObject( location_object       ,
                                     this->errors          ,
                                     this->document_path   ,
                                     44                    ,
                                     44                    ,
                                     44                    ,
                                     44                    );

        referencesLocations.push_back(location_object);

        pass &= buildLocationObject( location_object       ,
                                     this->errors          ,
                                     this->document_path   ,
                                     55                    ,
                                     55                    ,
                                     55                    ,
                                     55                    );

        referencesLocations.push_back(location_object);
    }

    return pass;
}

bool TestServer::gatherDocumentFormattingTextEdits(
                      DataArray & formattingTextEdits ,
                      int         start_line          ,
                      int         start_character     ,
                      int         end_line            ,
                      int         end_character       ,
                      int         tab_size            ,
                      bool        insert_spaces       )
{
    if (!this->is_initialized)
    {
        this->errors << m_error << "Server needs to be initialized" << std::endl;
        return false;
    }

    if (!this->is_document_open)
    {
        this->errors << m_error << "Server has no open document" << std::endl;
        return false;
    }

    bool pass = true;

    DataObject textedit_object;

    if ( start_line      == 2    &&
         start_character == 0    &&
         end_line        == 4    &&
         end_character   == 3    &&
         tab_size        == 4    &&
         insert_spaces   == true )
    {
        pass &= buildTextEditObject( textedit_object                      ,
                                     this->errors                         ,
                                     10                                   ,
                                     01                                   ,
                                     14                                   ,
                                     03                                   ,
                                     "test\n  new\n  text\n  format\n  1" );

        formattingTextEdits.push_back(textedit_object);

        pass &= buildTextEditObject( textedit_object                      ,
                                     this->errors                         ,
                                     20                                   ,
                                     01                                   ,
                                     24                                   ,
                                     03                                   ,
                                     "test\n  new\n  text\n  format\n  2" );

        formattingTextEdits.push_back(textedit_object);

        pass &= buildTextEditObject( textedit_object                      ,
                                     this->errors                         ,
                                     30                                   ,
                                     01                                   ,
                                     34                                   ,
                                     03                                   ,
                                     "test\n  new\n  text\n  format\n  3" );

        formattingTextEdits.push_back(textedit_object);
    }

    return pass;
}

} // namespace lsp
} // namespace wasp
