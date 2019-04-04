#include "LSP.h"

namespace wasp {
namespace lsp  {

bool buildPositionObject( DataObject   & object    ,
                          std::ostream & errors    ,
                          int            line      ,
                          int            character )
{
    bool pass = true;

    if ( line < 0 )
    {
        errors << "Error:: Line number must be non-negative - received: "
               << line << std::endl;
        pass = false;
    }

    if ( character < 0 )
    {
        errors << "Error:: Column number must be non-negative - received: "
               << character << std::endl;
        pass = false;
    }

    object[_line]      = line;
    object[_character] = character;

    return pass;
}

bool buildRangeObject( DataObject   & object          ,
                       std::ostream & errors          ,
                       int            start_line      ,
                       int            start_character ,
                       int            end_line        ,
                       int            end_character   )
{
    bool pass = true;

    if (( start_line  > end_line ) ||
        ( start_line == end_line && start_character > end_character ))
    {
        errors << "Error:: Range start ( line:" << start_line << " column:"
               << start_character << " ) must be less than range end ( line:"
               << end_line << " column:" << end_character << " )" << std::endl;
        pass = false;
    }

    DataObject start;
    pass &= buildPositionObject( start           ,
                                 errors          ,
                                 start_line      ,
                                 start_character );

    DataObject end;
    pass &= buildPositionObject( end           ,
                                 errors        ,
                                 end_line      ,
                                 end_character );

    object[_start] = start;
    object[_end]   = end;

    return pass;
}

bool buildInitializeRequest( DataObject        & object              ,
                             std::ostream      & errors              ,
                             int                 process_id          ,
                             const std::string & root_uri            ,
                             const DataObject  & client_capabilities )
{
    bool pass = true;

    DataObject params;
    params[_process_id]   = process_id;
    params[_root_uri]     = root_uri;
    params[_capabilities] = client_capabilities;

    object[_params] =  params;
    object[_method] = _method_initialize;

    return pass;
}

bool buildInitializedNotification( DataObject   & object ,
                                   std::ostream & errors )
{
    bool pass = true;

    DataObject params;

    object[_params] =  params;
    object[_method] = _method_initialized;

    return pass;
}

bool buildShutdownRequest( DataObject   & object ,
                           std::ostream & errors )
{
    bool pass = true;

    DataObject params;

    object[_params] =  params;
    object[_method] = _method_shutdown;

    return pass;
}

bool buildExitNotification( DataObject   & object ,
                            std::ostream & errors )
{
    bool pass = true;

    DataObject params;

    object[_params] =  params;
    object[_method] = _method_exit;

    return pass;
}

bool buildDidOpenNotification( DataObject        & object      ,
                               std::ostream      & errors      ,
                               const std::string & uri         ,
                               const std::string & language_id ,
                               double              version     ,
                               const std::string & text        )
{
    bool pass = true;

    DataObject text_document;
    text_document[_uri]         = uri;
    text_document[_language_id] = language_id;
    text_document[_version]     = version;
    text_document[_text]        = text;

    DataObject params;
    params[_text_document] = text_document;

    object[_params] =  params;
    object[_method] = _method_didopen;

    return pass;
}

bool buildDidChangeNotification( DataObject        & object          ,
                                 std::ostream      & errors          ,
                                 const std::string & uri             ,
                                 double              version         ,
                                 int                 start_line      ,
                                 int                 start_character ,
                                 int                 end_line        ,
                                 int                 end_character   ,
                                 int                 range_length    ,
                                 const std::string & text            )
{
    bool pass = true;

    DataObject range;
    pass &= buildRangeObject( range           ,
                              errors          ,
                              start_line      ,
                              start_character ,
                              end_line        ,
                              end_character   );

    DataObject content_changes;
    content_changes[_range]        = range;
    content_changes[_range_length] = range_length;
    content_changes[_text]         = text;

    DataObject text_document;
    text_document[_uri]     = uri;
    text_document[_version] = version;

    DataObject params;
    params[_content_changes] = content_changes;
    params[_text_document]   = text_document;

    object[_params] =  params;
    object[_method] = _method_didchange;

    return pass;
}

bool buildCompletionRequest( DataObject        & object    ,
                             std::ostream      & errors    ,
                             const std::string & uri       ,
                             int                 line      ,
                             int                 character )
{
    bool pass = true;

    DataObject position;
    pass &= buildPositionObject( position  ,
                                 errors    ,
                                 line      ,
                                 character );

    DataObject text_document;
    text_document[_uri] = uri;

    DataObject params;
    params[_position]      = position;
    params[_text_document] = text_document;

    object[_params] =  params;
    object[_method] = _method_completion;

    return pass;
}

bool buildDefinitionRequest( DataObject        & object    ,
                             std::ostream      & errors    ,
                             const std::string & uri       ,
                             int                 line      ,
                             int                 character )
{
    bool pass = true;

    DataObject position;
    pass &= buildPositionObject( position  ,
                                 errors    ,
                                 line      ,
                                 character );

    DataObject text_document;
    text_document[_uri] = uri;

    DataObject params;
    params[_position]      = position;
    params[_text_document] = text_document;

    object[_params] =  params;
    object[_method] = _method_definition;

    return pass;
}

bool buildReferencesRequest( DataObject        & object              ,
                             std::ostream      & errors              ,
                             const std::string & uri                 ,
                             int                 line                ,
                             int                 character           ,
                             bool                include_declaration )
{
    bool pass = true;

    DataObject position;
    pass &= buildPositionObject( position  ,
                                 errors    ,
                                 line      ,
                                 character );

    DataObject text_document;
    text_document[_uri] = uri;

    DataObject context;
    context[_include_declaration] = include_declaration;

    DataObject params;
    params[_position]      = position;
    params[_text_document] = text_document;
    params[_context]       = context;

    object[_params] =  params;
    object[_method] = _method_references;

    return pass;
}

bool buildRangeFormattingRequest( DataObject        & object          ,
                                  std::ostream      & errors          ,
                                  const std::string & uri             ,
                                  int                 start_line      ,
                                  int                 start_character ,
                                  int                 end_line        ,
                                  int                 end_character   ,
                                  int                 tab_size        ,
                                  bool                insert_spaces   )
{
    bool pass = true;

    DataObject range;
    pass &= buildRangeObject( range           ,
                              errors          ,
                              start_line      ,
                              start_character ,
                              end_line        ,
                              end_character   );

    DataObject options;
    options[_tab_size]      = tab_size;
    options[_insert_spaces] = insert_spaces;

    DataObject text_document;
    text_document[_uri] = uri;

    DataObject params;
    params[_range]         = range;
    params[_options]       = options;
    params[_text_document] = text_document;

    object[_params] =  params;
    object[_method] = _method_rangeformat;

    return pass;
}

bool buildDiagnosticObject( DataObject        & object          ,
                            std::ostream      & errors          ,
                            int                 start_line      ,
                            int                 start_character ,
                            int                 end_line        ,
                            int                 end_character   ,
                            int                 severity        ,
                            const std::string & code            ,
                            const std::string & source          ,
                            const std::string & message         )
{
    bool pass = true;

    DataObject range;
    pass &= buildRangeObject( range           ,
                              errors          ,
                              start_line      ,
                              start_character ,
                              end_line        ,
                              end_character   );

    object[_range]    = range;
    object[_severity] = severity;
    object[_code]     = code;
    object[_source]   = source;
    object[_message]  = message;

    return pass;
}

bool buildPublishDiagnosticsNotification( DataObject        & object      ,
                                          std::ostream      & errors      ,
                                          const std::string & uri         ,
                                          const DataArray   & diagnostics )
{
    bool pass = true;

    DataObject params;
    params[_uri]         = uri;
    params[_diagnostics] = diagnostics;

    object[_params] =  params;
    object[_method] = _method_pubdiagnostics;

    return pass;
}

bool buildInitializeResponse( DataObject        & object              ,
                              std::ostream      & errors              ,
                              const DataObject  & server_capabilities )
{
    bool pass = true;

    DataObject result;
    result[_capabilities] = server_capabilities;

    object[_result] = result;

    return pass;
}

bool buildShutdownResponse( DataObject   & object ,
                            std::ostream & errors )
{
    bool pass = true;

    DataObject result;

    object[_result] = result;

    return pass;
}

bool buildCompletionObject( DataObject        & object          ,
                            std::ostream      & errors          ,
                            const std::string & label           ,
                            int                 start_line      ,
                            int                 start_character ,
                            int                 end_line        ,
                            int                 end_character   ,
                            const std::string & new_text        ,
                            int                 kind            ,
                            const std::string & detail          ,
                            const std::string & documentation   ,
                            bool                deprecated      ,
                            bool                preselect       )
{
    bool pass = true;

    DataObject range;
    pass &= buildRangeObject( range           ,
                              errors          ,
                              start_line      ,
                              start_character ,
                              end_line        ,
                              end_character   );

    DataObject text_edit;
    text_edit[_range]    = range;
    text_edit[_new_text] = new_text;

    object[_text_edit]     = text_edit;
    object[_label]         = label;
    object[_kind]          = kind;
    object[_detail]        = detail;
    object[_documentation] = documentation;
    object[_deprecated]    = deprecated;
    object[_preselect]     = preselect;

    return pass;
}

bool buildCompletionResponse( DataObject        & object           ,
                              std::ostream      & errors           ,
                              bool                is_incomplete    ,
                              const DataArray   & completion_items )
{
    bool pass = true;

    DataObject result;
    result[_is_incomplete] = is_incomplete;
    result[_items]         = completion_items;

    object[_result] = result;

    return pass;
}

bool buildLocationObject( DataObject        & object          ,
                          std::ostream      & errors          ,
                          const std::string & uri             ,
                          int                 start_line      ,
                          int                 start_character ,
                          int                 end_line        ,
                          int                 end_character   )
{
    bool pass = true;

    DataObject range;
    pass &= buildRangeObject( range           ,
                              errors          ,
                              start_line      ,
                              start_character ,
                              end_line        ,
                              end_character   );

    object[_range] = range;
    object[_uri]   = uri;

    return pass;
}

bool buildLocationsResponse( DataObject        & object           ,
                             std::ostream      & errors           ,
                             const DataArray   & location_objects )
{
    bool pass = true;

    DataObject result;

    object[_result] = location_objects;

    return pass;
}

bool buildTextEditObject( DataObject        & object          ,
                          std::ostream      & errors          ,
                          int                 start_line      ,
                          int                 start_character ,
                          int                 end_line        ,
                          int                 end_character   ,
                          const std::string & new_text        )
{
    bool pass = true;

    DataObject range;
    pass &= buildRangeObject( range           ,
                              errors          ,
                              start_line      ,
                              start_character ,
                              end_line        ,
                              end_character   );

    object[_range]    = range;
    object[_new_text] = new_text;

    return pass;
}

bool buildRangeFormattingResponse( DataObject        & object           ,
                                   std::ostream      & errors           ,
                                   const DataArray   & textedit_objects )
{
    bool pass = true;

    DataObject result;

    object[_result] = textedit_objects;

    return pass;
}

}
}
