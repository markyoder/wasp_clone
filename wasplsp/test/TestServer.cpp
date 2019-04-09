#include "TestServer.h"

namespace wasp {
namespace lsp  {

bool TestServer::handleInitializeRequest(
                const DataObject   & initializeRequest  ,
                      DataObject   & initializeResponse ,
                      std::ostream & errors             )
{
    bool pass = true;

    pass &= dissectInitializeRequest( initializeRequest         ,
                                      errors                    ,
                                      this->client_request_id   ,
                                      this->client_process_id   ,
                                      this->client_root_path    ,
                                      this->client_capabilities );

    pass &= buildInitializeResponse( initializeResponse        ,
                                     errors                    ,
                                     this->client_request_id   ,
                                     this->server_capabilities );

    return pass;
}

bool TestServer::handleInitializedNotification(
                const DataObject   & initializedNotification ,
                      std::ostream & errors                  )
{
    bool pass = true;

    pass &= dissectInitializedNotification( initializedNotification ,
                                            errors                  );

    return pass;
}

bool TestServer::handleShutdownRequest(
                const DataObject   & shutdownRequest  ,
                      DataObject   & shutdownResponse ,
                      std::ostream & errors           )
{
    bool pass = true;

    pass &= dissectShutdownResponse( shutdownRequest         ,
                                     errors                  ,
                                     this->client_request_id );

    pass &= buildShutdownResponse( shutdownResponse        ,
                                   errors                  ,
                                   this->client_request_id );

    return pass;
}

bool TestServer::handleExitNotification(
                const DataObject   & exitNotification ,
                      std::ostream & errors           )
{
    bool pass = true;

    pass &= dissectExitNotification( exitNotification ,
                                     errors           );

    return pass;
}

bool TestServer::handleDidOpenNotification(
                const DataObject   & didOpenNotification            ,
                      DataObject   & publishDiagnosticsNotification ,
                      std::ostream & errors                         )
{
    bool pass = true;

    pass &= dissectDidOpenNotification( didOpenNotification        ,
                                        errors                     ,
                                        this->document_path        ,
                                        this->document_language_id ,
                                        this->document_version     ,
                                        this->document_text        );

    DataArray document_diagnostics;

    pass &= this->parseDocumentForDiagnostics( document_diagnostics ,
                                               errors               );

    pass &= buildPublishDiagnosticsNotification( publishDiagnosticsNotification ,
                                                 errors                         ,
                                                 this->document_path            ,
                                                 document_diagnostics           );

    return pass;
}

bool TestServer::handleDidChangeNotification(
                const DataObject   & didChangeNotification          ,
                      DataObject   & publishDiagnosticsNotification ,
                      std::ostream & errors                         )
{
    bool pass = true;

    int         start_line;
    int         start_character;
    int         end_line;
    int         end_character;
    int         range_length;
    std::string replacement_text;

    pass &= dissectDidChangeNotification( didChangeNotification  ,
                                          errors                 ,
                                          this->document_path    ,
                                          this->document_version ,
                                          start_line             ,
                                          start_character        ,
                                          end_line               ,
                                          end_character          ,
                                          range_length           ,
                                          replacement_text       );

    pass &= this->updateDocumentTextChanges( replacement_text ,
                                             start_line       ,
                                             start_character  ,
                                             end_line         ,
                                             end_character    ,
                                             range_length     ,
                                             errors           );

    DataArray document_diagnostics;

    pass &= this->parseDocumentForDiagnostics( document_diagnostics ,
                                               errors               );

    pass &= buildPublishDiagnosticsNotification( publishDiagnosticsNotification ,
                                                 errors                         ,
                                                 this->document_path            ,
                                                 document_diagnostics           );

    return pass;
}

bool TestServer::handleCompletionRequest(
                const DataObject   & completionRequest  ,
                      DataObject   & completionResponse ,
                      std::ostream & errors             )
{
    bool pass = true;

    int line;
    int character;

    pass &= dissectCompletionRequest( completionRequest       ,
                                      errors                  ,
                                      this->client_request_id ,
                                      this->document_path     ,
                                      line                    ,
                                      character               );

    DataArray completion_items;
    bool      is_incomplete;

    pass &= this->gatherDocumentCompletionItems( completion_items,
                                                 is_incomplete   ,
                                                 line            ,
                                                 character       ,
                                                 errors          );

    pass &= buildCompletionResponse( completionResponse      ,
                                     errors                  ,
                                     this->client_request_id ,
                                     is_incomplete           ,
                                     completion_items        );

    return pass;
}

bool TestServer::handleDefinitionRequest(
                const DataObject   & definitionRequest  ,
                      DataObject   & definitionResponse ,
                      std::ostream & errors             )
{
    bool pass = true;

    int line;
    int character;

    pass &= dissectDefinitionRequest( definitionRequest       ,
                                      errors                  ,
                                      this->client_request_id ,
                                      this->document_path     ,
                                      line                    ,
                                      character               );


    DataArray definition_locations;

    pass &= this->gatherDocumentDefinitionLocations( definition_locations ,
                                                     line                 ,
                                                     character            ,
                                                     errors               );


    pass &= buildLocationsResponse( definitionResponse      ,
                                    errors                  ,
                                    this->client_request_id ,
                                    definition_locations    );

    return pass;
}

bool TestServer::handleReferencesRequest(
                const DataObject   & referencesRequest  ,
                      DataObject   & referencesResponse ,
                      std::ostream & errors             )
{
    bool pass = true;

    int  line;
    int  character;
    bool include_declaration;

    pass &= dissectReferencesRequest( referencesRequest       ,
                                      errors                  ,
                                      this->client_request_id ,
                                      this->document_path     ,
                                      line                    ,
                                      character               ,
                                      include_declaration     );

    DataArray references_locations;

    pass &= this->gatherDocumentReferencesLocations( references_locations ,
                                                     line                 ,
                                                     character            ,
                                                     include_declaration  ,
                                                     errors               );

    pass &= buildLocationsResponse( referencesResponse      ,
                                    errors                  ,
                                    this->client_request_id ,
                                    references_locations    );

    return pass;
}

bool TestServer::handleRangeFormattingRequest(
                const DataObject   & rangeFormattingRequest  ,
                      DataObject   & rangeFormattingResponse ,
                      std::ostream & errors                  )
{
    bool pass = true;

    int  start_line;
    int  start_character;
    int  end_line;
    int  end_character;
    int  tab_size;
    bool insert_spaces;

    pass &= dissectRangeFormattingRequest( rangeFormattingRequest  ,
                                           errors                  ,
                                           this->client_request_id ,
                                           this->document_path     ,
                                           start_line              ,
                                           start_character         ,
                                           end_line                ,
                                           end_character           ,
                                           tab_size                ,
                                           insert_spaces           );

    DataArray formatting_textedits;

    pass &= this->gatherDocumentFormattingTextEdits( formatting_textedits ,
                                                     start_line           ,
                                                     start_character      ,
                                                     end_line             ,
                                                     end_character        ,
                                                     tab_size             ,
                                                     insert_spaces        ,
                                                     errors               );

    pass &= buildRangeFormattingResponse( rangeFormattingResponse ,
                                          errors                  ,
                                          this->client_request_id ,
                                          formatting_textedits    );

    return pass;
}

bool TestServer::parseDocumentForDiagnostics(
                      DataArray    & diagnosticsList ,
                      std::ostream & errors          )
{
    bool pass = true;

    DataObject diagnostic;

    if (this->document_text == "test\ntext\n1\nstring\n")
    {
        pass &= buildDiagnosticObject( diagnostic         ,
                                       errors             ,
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
                                       errors             ,
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
                                       errors             ,
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
                                       errors             ,
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
                                       errors             ,
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
                const std::string  & replacement_text ,
                      int            start_line       ,
                      int            start_character  ,
                      int            end_line         ,
                      int            end_character    ,
                      int            range_length     ,
                      std::ostream & errors           )
{
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
                      DataArray    & completionItems  ,
                      bool         & is_incomplete    ,
                      int            line             ,
                      int            character        ,
                      std::ostream & errors           )
{
    bool pass = true;

    DataObject completion_item;

    if ( line      == 4 &&
         character == 2 )
    {
        pass &= buildCompletionObject( completion_item        ,
                                       errors                 ,
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
                                       errors                 ,
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
                                       errors                 ,
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
                      DataArray    & definitionLocations ,
                      int            line                ,
                      int            character           ,
                      std::ostream & errors              )
{
    bool pass = true;

    DataObject location_object;

    if ( line      == 2 &&
         character == 5 )
    {
        pass &= buildLocationObject( location_object       ,
                                     errors                ,
                                     this->document_path   ,
                                     11                    ,
                                     11                    ,
                                     11                    ,
                                     11                    );

        definitionLocations.push_back(location_object);

        pass &= buildLocationObject( location_object       ,
                                     errors                ,
                                     this->document_path   ,
                                     22                    ,
                                     22                    ,
                                     22                    ,
                                     22                    );

        definitionLocations.push_back(location_object);

        pass &= buildLocationObject( location_object       ,
                                     errors                ,
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
                      DataArray    & referencesLocations ,
                      int            line                ,
                      int            character           ,
                      bool           include_declaration ,
                      std::ostream & errors              )
{
    bool pass = true;

    DataObject location_object;

    if ( line                == 1     &&
         character           == 3     &&
         include_declaration == false )
    {
        pass &= buildLocationObject( location_object       ,
                                     errors                ,
                                     this->document_path   ,
                                     44                    ,
                                     44                    ,
                                     44                    ,
                                     44                    );

        referencesLocations.push_back(location_object);

        pass &= buildLocationObject( location_object       ,
                                     errors                ,
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
                      DataArray    & formattingTextEdits ,
                      int            start_line          ,
                      int            start_character     ,
                      int            end_line            ,
                      int            end_character       ,
                      int            tab_size            ,
                      bool           insert_spaces       ,
                      std::ostream & errors              )
{
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
                                     errors                               ,
                                     10                                   ,
                                     01                                   ,
                                     14                                   ,
                                     03                                   ,
                                     "test\n  new\n  text\n  format\n  1" );

        formattingTextEdits.push_back(textedit_object);

        pass &= buildTextEditObject( textedit_object                      ,
                                     errors                               ,
                                     20                                   ,
                                     01                                   ,
                                     24                                   ,
                                     03                                   ,
                                     "test\n  new\n  text\n  format\n  2" );

        formattingTextEdits.push_back(textedit_object);

        pass &= buildTextEditObject( textedit_object                      ,
                                     errors                               ,
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
