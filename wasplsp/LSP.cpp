#include "wasplsp/LSP.h"
#include "waspcore/wasp_bug.h"

namespace wasp {
namespace lsp  {

bool checkPosition( std::ostream & errors    ,
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

    return pass;
}

bool checkRange( std::ostream & errors          ,
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

    return pass;
}

bool buildPositionObject( DataObject   & object    ,
                          std::ostream & errors    ,
                          int            line      ,
                          int            character )
{
    bool pass = true;

    pass &= checkPosition( errors    ,
                           line      ,
                           character );

    object[_line]      = line;
    object[_character] = character;

    return pass;
}

bool dissectPositionObject( const DataObject   & object    ,
                                  std::ostream & errors    ,
                                  int          & line      ,
                                  int          & character )
{
    bool pass = true;

    wasp_check( object[_line].is_int() );

    line = object[_line].to_int();

    wasp_check( object[_character].is_int() );

    character = object[_character].to_int();

    pass &= checkPosition( errors    ,
                           line      ,
                           character );

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

    pass &= checkRange( errors          ,
                        start_line      ,
                        start_character ,
                        end_line        ,
                        end_character   );

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

bool dissectRangeObject( const DataObject      & object          ,
                               std::ostream    & errors          ,
                               int             & start_line      ,
                               int             & start_character ,
                               int             & end_line        ,
                               int             & end_character   )
{
    bool pass = true;

    wasp_check( object[_start].is_object() );

    DataObject start = *(object[_start].to_object());

    pass &= dissectPositionObject( start           ,
                                   errors          ,
                                   start_line      ,
                                   start_character );

    wasp_check( object[_end].is_object() );

    DataObject end = *(object[_end].to_object());

    pass &= dissectPositionObject( end           ,
                                   errors        ,
                                   end_line      ,
                                   end_character );

    pass &= checkRange( errors          ,
                        start_line      ,
                        start_character ,
                        end_line        ,
                        end_character   );

    return pass;
}

bool buildInitializeRequest( DataObject        & object              ,
                             std::ostream      & errors              ,
                             int                 request_id          ,
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
    object[_id]     =  request_id;
    object[_method] = _method_initialize;

    return pass;
}

bool dissectInitializeRequest( const DataObject        & object              ,
                                     std::ostream      & errors              ,
                                     int               & request_id          ,
                                     int               & process_id          ,
                                     std::string       & root_uri            ,
                                     DataObject        & client_capabilities )
{
    bool pass = true;

    wasp_check( object[_method].is_string() );

    wasp_check( object[_method].to_string() == _method_initialize );

    wasp_check( object[_id].is_int() );

    request_id = object[_id].to_int();

    wasp_check( object[_params].is_object() );

    DataObject params = *(object[_params].to_object());

    wasp_check( params[_process_id].is_int() );

    process_id = params[_process_id].to_int();

    wasp_check( params[_root_uri].is_string() );

    root_uri = params[_root_uri].to_string();

    wasp_check( params[_capabilities].is_object() );

    client_capabilities = *(params[_capabilities].to_object());

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

bool dissectInitializedNotification( const DataObject   & object ,
                                           std::ostream & errors )
{
    bool pass = true;

    wasp_check( object[_method].is_string() );

    wasp_check( object[_method].to_string() == _method_initialized );

    wasp_check( object[_params].is_object() );

    return pass;
}

bool buildShutdownRequest( DataObject   & object     ,
                           std::ostream & errors     ,
                           int            request_id )
{
    bool pass = true;

    DataObject params;

    object[_params] =  params;
    object[_id]     =  request_id;
    object[_method] = _method_shutdown;

    return pass;
}

bool dissectShutdownRequest( const DataObject   & object     ,
                                   std::ostream & errors     ,
                                   int          & request_id )
{
    bool pass = true;

    wasp_check( object[_method].is_string() );

    wasp_check( object[_method].to_string() == _method_shutdown );

    wasp_check( object[_id].is_int() );

    request_id = object[_id].to_int();

    wasp_check( object[_params].is_object() );

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

bool dissectExitNotification( const DataObject   & object ,
                                    std::ostream & errors )
{
    bool pass = true;

    wasp_check( object[_method].is_string() );

    wasp_check( object[_method].to_string() == _method_exit );

    wasp_check( object[_params].is_object() );

    return pass;
}

bool buildDidOpenNotification( DataObject        & object      ,
                               std::ostream      & errors      ,
                               const std::string & uri         ,
                               const std::string & language_id ,
                               int                 version     ,
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

bool dissectDidOpenNotification( const DataObject   & object      ,
                                       std::ostream & errors      ,
                                       std::string  & uri         ,
                                       std::string  & language_id ,
                                       int          & version     ,
                                       std::string  & text        )
{
    bool pass = true;

    wasp_check( object[_method].is_string() );

    wasp_check( object[_method].to_string() == _method_didopen );

    wasp_check( object[_params].is_object() );

    DataObject params = *(object[_params].to_object());

    wasp_check( params[_text_document].is_object() );

    DataObject text_document = *(params[_text_document].to_object());

    wasp_check( text_document[_uri].is_string() );

    uri = text_document[_uri].to_string();

    wasp_check( text_document[_language_id].is_string() );

    language_id = text_document[_language_id].to_string();

    wasp_check( text_document[_version].is_int() );

    version = text_document[_version].to_int();

    wasp_check( text_document[_text].is_string() );

    text = text_document[_text].to_string();

    return pass;
}

bool buildDidChangeNotification( DataObject        & object          ,
                                 std::ostream      & errors          ,
                                 const std::string & uri             ,
                                 int                 version         ,
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

bool dissectDidChangeNotification( const DataObject   & object          ,
                                         std::ostream & errors          ,
                                         std::string  & uri             ,
                                         int          & version         ,
                                         int          & start_line      ,
                                         int          & start_character ,
                                         int          & end_line        ,
                                         int          & end_character   ,
                                         int          & range_length    ,
                                         std::string  & text            )
{
    bool pass = true;

    wasp_check( object[_method].is_string() );

    wasp_check( object[_method].to_string() == _method_didchange );

    wasp_check( object[_params].is_object() );

    DataObject params = *(object[_params].to_object());

    wasp_check( params[_text_document].is_object() );

    DataObject text_document = *(params[_text_document].to_object());

    wasp_check( text_document[_uri].is_string() );

    uri = text_document[_uri].to_string();

    wasp_check( text_document[_version].is_int() );

    version = text_document[_version].to_int();

    wasp_check( params[_content_changes].is_object() );

    DataObject content_changes = *(params[_content_changes].to_object());

    wasp_check( content_changes[_range].is_object() );

    DataObject range = *(content_changes[_range].to_object());

    pass &= dissectRangeObject( range           ,
                                errors          ,
                                start_line      ,
                                start_character ,
                                end_line        ,
                                end_character   );

    wasp_check( content_changes[_range_length].is_int() );

    range_length = content_changes[_range_length].to_int();

    wasp_check( content_changes[_text].is_string() );

    text = content_changes[_text].to_string();

    return pass;
}

bool buildCompletionRequest( DataObject        & object     ,
                             std::ostream      & errors     ,
                             int                 request_id ,
                             const std::string & uri        ,
                             int                 line       ,
                             int                 character  )
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
    object[_id]     =  request_id;
    object[_method] = _method_completion;

    return pass;
}

bool dissectCompletionRequest( const DataObject   & object     ,
                                     std::ostream & errors     ,
                                     int          & request_id ,
                                     std::string  & uri        ,
                                     int          & line       ,
                                     int          & character  )
{
    bool pass = true;

    wasp_check( object[_method].is_string() );

    wasp_check( object[_method].to_string() == _method_completion );

    wasp_check( object[_id].is_int() );

    request_id = object[_id].to_int();

    wasp_check( object[_params].is_object() );

    DataObject params = *(object[_params].to_object());

    wasp_check( params[_text_document].is_object() );

    DataObject text_document = *(params[_text_document].to_object());

    wasp_check( text_document[_uri].is_string() );

    uri = text_document[_uri].to_string();

    wasp_check( params[_position].is_object() );

    DataObject position = *(params[_position].to_object());

    pass &= dissectPositionObject( position  ,
                                   errors    ,
                                   line      ,
                                   character );

    return pass;
}

bool buildDefinitionRequest( DataObject        & object     ,
                             std::ostream      & errors     ,
                             int                 request_id ,
                             const std::string & uri        ,
                             int                 line       ,
                             int                 character  )
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
    object[_id]     =  request_id;
    object[_method] = _method_definition;

    return pass;
}

bool dissectDefinitionRequest( const DataObject   & object     ,
                                     std::ostream & errors     ,
                                     int          & request_id ,
                                     std::string  & uri        ,
                                     int          & line       ,
                                     int          & character  )
{
    bool pass = true;

    wasp_check( object[_method].is_string() );

    wasp_check( object[_method].to_string() == _method_definition );

    wasp_check( object[_id].is_int() );

    request_id = object[_id].to_int();

    wasp_check( object[_params].is_object() );

    DataObject params = *(object[_params].to_object());

    wasp_check( params[_text_document].is_object() );

    DataObject text_document = *(params[_text_document].to_object());

    wasp_check( text_document[_uri].is_string() );

    uri = text_document[_uri].to_string();

    wasp_check( params[_position].is_object() );

    DataObject position = *(params[_position].to_object());

    pass &= dissectPositionObject( position  ,
                                   errors    ,
                                   line      ,
                                   character );

    return pass;
}

bool buildReferencesRequest( DataObject        & object              ,
                             std::ostream      & errors              ,
                             int                 request_id          ,
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
    object[_id]     =  request_id;
    object[_method] = _method_references;

    return pass;
}

bool dissectReferencesRequest( const DataObject   & object              ,
                                     std::ostream & errors              ,
                                     int          & request_id          ,
                                     std::string  & uri                 ,
                                     int          & line                ,
                                     int          & character           ,
                                     bool         & include_declaration )
{
    bool pass = true;

    wasp_check( object[_method].is_string() );

    wasp_check( object[_method].to_string() == _method_references );

    wasp_check( object[_id].is_int() );

    request_id = object[_id].to_int();

    wasp_check( object[_params].is_object() );

    DataObject params = *(object[_params].to_object());

    wasp_check( params[_text_document].is_object() );

    DataObject text_document = *(params[_text_document].to_object());

    wasp_check( text_document[_uri].is_string() );

    uri = text_document[_uri].to_string();

    wasp_check( params[_position].is_object() );

    DataObject position = *(params[_position].to_object());

    pass &= dissectPositionObject( position  ,
                                   errors    ,
                                   line      ,
                                   character );

    wasp_check( params[_context].is_object() );

    DataObject context = *(params[_context].to_object());

    wasp_check( context[_include_declaration].is_bool() );

    include_declaration = context[_include_declaration].to_bool();

    return pass;
}

bool buildRangeFormattingRequest( DataObject        & object          ,
                                  std::ostream      & errors          ,
                                  int                 request_id      ,
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
    object[_id]     =  request_id;
    object[_method] = _method_rangeformat;

    return pass;
}

bool dissectRangeFormattingRequest( const DataObject   & object          ,
                                          std::ostream & errors          ,
                                          int          & request_id      ,
                                          std::string  & uri             ,
                                          int          & start_line      ,
                                          int          & start_character ,
                                          int          & end_line        ,
                                          int          & end_character   ,
                                          int          & tab_size        ,
                                          bool         & insert_spaces   )
{
    bool pass = true;

    wasp_check( object[_method].is_string() );

    wasp_check( object[_method].to_string() == _method_rangeformat );

    wasp_check( object[_id].is_int() );

    request_id = object[_id].to_int();

    wasp_check( object[_params].is_object() );

    DataObject params = *(object[_params].to_object());

    wasp_check( params[_text_document].is_object() );

    DataObject text_document = *(params[_text_document].to_object());

    wasp_check( text_document[_uri].is_string() );

    uri = text_document[_uri].to_string();

    wasp_check( params[_range].is_object() );

    DataObject range = *(params[_range].to_object());

    pass &= dissectRangeObject( range           ,
                                errors          ,
                                start_line      ,
                                start_character ,
                                end_line        ,
                                end_character   );

    wasp_check( params[_options].is_object() );

    DataObject options = *(params[_options].to_object());

    wasp_check( options[_tab_size].is_int() );

    tab_size = options[_tab_size].to_int();

    wasp_check( options[_insert_spaces].is_bool() );

    insert_spaces = options[_insert_spaces].to_bool();

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

bool dissectDiagnosticObject( const DataObject   & object          ,
                                    std::ostream & errors          ,
                                    int          & start_line      ,
                                    int          & start_character ,
                                    int          & end_line        ,
                                    int          & end_character   ,
                                    int          & severity        ,
                                    std::string  & code            ,
                                    std::string  & source          ,
                                    std::string  & message         )
{
    bool pass = true;

    wasp_check( object[_range].is_object() );

    DataObject range = *(object[_range].to_object());

    pass &= dissectRangeObject( range           ,
                                errors          ,
                                start_line      ,
                                start_character ,
                                end_line        ,
                                end_character   );

    wasp_check( object[_severity].is_int() );

    severity = object[_severity].to_int();

    wasp_check( object[_code].is_string() );

    code = object[_code].to_string();

    wasp_check( object[_source].is_string() );

    source = object[_source].to_string();

    wasp_check( object[_message].is_string() );

    message = object[_message].to_string();

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

bool dissectPublishDiagnosticsNotification( const DataObject   & object      ,
                                                  std::ostream & errors      ,
                                                  std::string  & uri         ,
                                                  DataArray    & diagnostics )
{
    bool pass = true;

    wasp_check( object[_method].is_string() );

    wasp_check( object[_method].to_string() == _method_pubdiagnostics );

    wasp_check( object[_params].is_object() );

    DataObject params = *(object[_params].to_object());

    wasp_check( params[_uri].is_string() );

    uri = params[_uri].to_string();

    wasp_check( params[_diagnostics].is_array() );

    diagnostics = *(params[_diagnostics].to_array());

    return pass;
}

bool buildInitializeResponse( DataObject        & object              ,
                              std::ostream      & errors              ,
                              int                 request_id          ,
                              const DataObject  & server_capabilities )
{
    bool pass = true;

    DataObject result;
    result[_capabilities] = server_capabilities;

    object[_result] = result;
    object[_id]     = request_id;

    return pass;
}

bool dissectInitializeResponse( const DataObject   & object              ,
                                      std::ostream & errors              ,
                                      int          & request_id          ,
                                      DataObject   & server_capabilities )
{
    bool pass = true;

    wasp_check( object[_id].is_int() );

    request_id = object[_id].to_int();

    wasp_check( object[_result].is_object() );

    DataObject result = *(object[_result].to_object());

    wasp_check( result[_capabilities].is_object() );

    server_capabilities = *(result[_capabilities].to_object());

    return pass;
}

bool buildShutdownResponse( DataObject        & object     ,
                            std::ostream      & errors     ,
                            int                 request_id )
{
    bool pass = true;

    DataObject result;

    object[_result] = result;
    object[_id]     = request_id;

    return pass;
}

bool dissectShutdownResponse( const DataObject   & object     ,
                                    std::ostream & errors     ,
                                    int          & request_id )
{
    bool pass = true;

    wasp_check( object[_id].is_int() );

    request_id = object[_id].to_int();

    wasp_check( object[_result].is_object() );

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

bool dissectCompletionObject( const DataObject   & object          ,
                                    std::ostream & errors          ,
                                    std::string  & label           ,
                                    int          & start_line      ,
                                    int          & start_character ,
                                    int          & end_line        ,
                                    int          & end_character   ,
                                    std::string  & new_text        ,
                                    int          & kind            ,
                                    std::string  & detail          ,
                                    std::string  & documentation   ,
                                    bool         & deprecated      ,
                                    bool         & preselect       )
{
    bool pass = true;

    wasp_check( object[_text_edit].is_object() );

    DataObject text_edit = *(object[_text_edit].to_object());

    wasp_check( text_edit[_range].is_object() );

    DataObject range = *(text_edit[_range].to_object());

    pass &= dissectRangeObject( range           ,
                                errors          ,
                                start_line      ,
                                start_character ,
                                end_line        ,
                                end_character   );

    wasp_check( text_edit[_new_text].is_string() );

    new_text = text_edit[_new_text].to_string();

    wasp_check( object[_label].is_string() );

    label = object[_label].to_string();

    wasp_check( object[_kind].is_int() );

    kind = object[_kind].to_int();

    wasp_check( object[_detail].is_string() );

    detail = object[_detail].to_string();

    wasp_check( object[_documentation].is_string() );

    documentation = object[_documentation].to_string();

    wasp_check( object[_deprecated].is_bool() );

    deprecated = object[_deprecated].to_bool();

    wasp_check( object[_preselect].is_bool() );

    preselect = object[_preselect].to_bool();

    return pass;
}

bool buildCompletionResponse( DataObject        & object           ,
                              std::ostream      & errors           ,
                              int                 request_id       ,
                              bool                is_incomplete    ,
                              const DataArray   & completion_items )
{
    bool pass = true;

    DataObject result;
    result[_is_incomplete] = is_incomplete;
    result[_items]         = completion_items;

    object[_result] = result;
    object[_id]     = request_id;

    return pass;
}

bool dissectCompletionResponse( const DataObject   & object           ,
                                      std::ostream & errors           ,
                                      int          & request_id       ,
                                      bool         & is_incomplete    ,
                                      DataArray    & completion_items )
{
    bool pass = true;

    wasp_check( object[_id].is_int() );

    request_id = object[_id].to_int();

    wasp_check( object[_result].is_object() );

    DataObject result = *(object[_result].to_object());

    wasp_check( result[_is_incomplete].is_bool() );

    is_incomplete = result[_is_incomplete].to_bool();

    wasp_check( result[_items].is_array() );

    completion_items = *(result[_items].to_array());

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

bool dissectLocationObject( const DataObject   & object          ,
                                  std::ostream & errors          ,
                                  std::string  & uri             ,
                                  int          & start_line      ,
                                  int          & start_character ,
                                  int          & end_line        ,
                                  int          & end_character   )
{
    bool pass = true;

    wasp_check( object[_uri].is_string() );

    uri = object[_uri].to_string();

    wasp_check( object[_range].is_object() );

    DataObject range = *(object[_range].to_object());

    pass &= dissectRangeObject( range           ,
                                errors          ,
                                start_line      ,
                                start_character ,
                                end_line        ,
                                end_character   );

    return pass;
}

bool buildLocationsResponse( DataObject        & object           ,
                             std::ostream      & errors           ,
                             int                 request_id       ,
                             const DataArray   & location_objects )
{
    bool pass = true;

    DataObject result;

    object[_result] = location_objects;
    object[_id]     = request_id;

    return pass;
}

bool dissectLocationsResponse( const DataObject   & object           ,
                                     std::ostream & errors           ,
                                     int          & request_id       ,
                                     DataArray    & location_objects )
{
    bool pass = true;

    wasp_check( object[_id].is_int() );

    request_id = object[_id].to_int();

    wasp_check( object[_result].is_array() );

    location_objects = *(object[_result].to_array());

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

bool dissectTextEditObject( const DataObject   & object          ,
                                  std::ostream & errors          ,
                                  int          & start_line      ,
                                  int          & start_character ,
                                  int          & end_line        ,
                                  int          & end_character   ,
                                  std::string  & new_text        )
{
    bool pass = true;

    wasp_check( object[_range].is_object() );

    DataObject range = *(object[_range].to_object());

    pass &= dissectRangeObject( range           ,
                                errors          ,
                                start_line      ,
                                start_character ,
                                end_line        ,
                                end_character   );

    wasp_check( object[_new_text].is_string() );

    new_text = object[_new_text].to_string();

    return pass;
}

bool buildRangeFormattingResponse( DataObject        & object           ,
                                   std::ostream      & errors           ,
                                   int                 request_id       ,
                                   const DataArray   & textedit_objects )
{
    bool pass = true;

    DataObject result;

    object[_result] = textedit_objects;
    object[_id]     = request_id;

    return pass;
}

bool dissectRangeFormattingResponse( const DataObject   & object           ,
                                           std::ostream & errors           ,
                                           int          & request_id       ,
                                           DataArray    & textedit_objects )
{
    bool pass = true;

    wasp_check( object[_id].is_int() );

    request_id = object[_id].to_int();

    wasp_check( object[_result].is_array() );

    textedit_objects = *(object[_result].to_array());

    return pass;
}

} // namespace lsp
} // namespace wasp
