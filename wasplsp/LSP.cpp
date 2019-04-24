#include "wasplsp/LSP.h"
#include "waspcore/wasp_bug.h"
#include <string>
#include <iostream>

namespace wasp {
namespace lsp  {

bool objectToRPCString( DataObject   & object ,
                        std::string  & rpcstr ,
                        std::ostream & errors )
{
    bool pass = true;

    object[m_rpc_jsonrpc_key] = m_rpc_jsonrpc_val;

    std::stringstream body;

    object.format_json(body);

    std::stringstream full_buffer;

    full_buffer << m_rpc_content_len_key
                << " "
                << body.str().size()
                << m_rpc_separator
                << body.str();

    rpcstr = full_buffer.str();

    return pass;
}

bool RPCStringToObject( const std::string  & rpcstr ,
                              DataObject   & object ,
                              std::ostream & errors )
{
    bool pass = true;

    std::stringstream full_buffer( rpcstr );

    std::string content_length_key;

    full_buffer >> content_length_key;

    wasp_check( content_length_key == m_rpc_content_len_key );

    int content_length_val;

    full_buffer >> content_length_val;

    content_length_val+=4;

    char * content_buffer = new char[ content_length_val ];

    full_buffer.read(content_buffer, content_length_val);

    std::istringstream packet(std::string(content_buffer,content_length_val));

    delete[] content_buffer;

    DataObject::SP json_ptr;

    JSONObjectParser generator(json_ptr, packet, errors, nullptr);

    pass &= (generator.parse() == 0);

    wasp_check( json_ptr != nullptr );

    object = *(json_ptr.get());

    wasp_check( object[m_rpc_jsonrpc_key].is_string() );

    wasp_check( object[m_rpc_jsonrpc_key].to_string() == m_rpc_jsonrpc_val );

    return pass;
}

bool checkPosition( std::ostream & errors    ,
                    int            line      ,
                    int            character )
{
    bool pass = true;

    if ( line < 0 )
    {
        errors << m_error << "Line number must be non-negative - received: "
               << line << std::endl;
        pass = false;
    }

    if ( character < 0 )
    {
        errors << m_error << "Column number must be non-negative - received: "
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
        errors << m_error << "Range start ( line:" << start_line << " column:"
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

    object[m_line]      = line;
    object[m_character] = character;

    return pass;
}

bool dissectPositionObject( const DataObject   & object    ,
                                  std::ostream & errors    ,
                                  int          & line      ,
                                  int          & character )
{
    bool pass = true;

    wasp_check( object[m_line].is_int() );

    line = object[m_line].to_int();

    wasp_check( object[m_character].is_int() );

    character = object[m_character].to_int();

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

    object[m_start] = start;
    object[m_end]   = end;

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

    wasp_check( object[m_start].is_object() );

    const DataObject& start = *(object[m_start].to_object());

    pass &= dissectPositionObject( start           ,
                                   errors          ,
                                   start_line      ,
                                   start_character );

    wasp_check( object[m_end].is_object() );

    const DataObject& end = *(object[m_end].to_object());

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
    params[m_process_id]   = process_id;
    params[m_root_uri]     = root_uri;
    params[m_capabilities] = client_capabilities;

    object[m_params] =  params;
    object[m_id]     =  request_id;
    object[m_method] = m_method_initialize;

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

    wasp_check( object[m_method].is_string() );

    wasp_check( object[m_method].to_string() == m_method_initialize );

    wasp_check( object[m_id].is_int() );

    request_id = object[m_id].to_int();

    wasp_check( object[m_params].is_object() );

    const DataObject& params = *(object[m_params].to_object());

    wasp_check( params[m_process_id].is_int() );

    process_id = params[m_process_id].to_int();

    wasp_check( params[m_root_uri].is_string() );

    root_uri = params[m_root_uri].to_string();

    wasp_check( params[m_capabilities].is_object() );

    client_capabilities = *(params[m_capabilities].to_object());

    return pass;
}

bool buildInitializedNotification( DataObject   & object ,
                                   std::ostream & errors )
{
    bool pass = true;

    DataObject params;

    object[m_params] =  params;
    object[m_method] = m_method_initialized;

    return pass;
}

bool dissectInitializedNotification( const DataObject   & object ,
                                           std::ostream & errors )
{
    bool pass = true;

    wasp_check( object[m_method].is_string() );

    wasp_check( object[m_method].to_string() == m_method_initialized );

    wasp_check( object[m_params].is_object() );

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
    text_document[m_uri]         = uri;
    text_document[m_language_id] = language_id;
    text_document[m_version]     = version;
    text_document[m_text]        = text;

    DataObject params;
    params[m_text_document] = text_document;

    object[m_params] =  params;
    object[m_method] = m_method_didopen;

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

    wasp_check( object[m_method].is_string() );

    wasp_check( object[m_method].to_string() == m_method_didopen );

    wasp_check( object[m_params].is_object() );

    const DataObject& params = *(object[m_params].to_object());

    wasp_check( params[m_text_document].is_object() );

    const DataObject& text_document = *(params[m_text_document].to_object());

    wasp_check( text_document[m_uri].is_string() );

    uri = text_document[m_uri].to_string();

    wasp_check( text_document[m_language_id].is_string() );

    language_id = text_document[m_language_id].to_string();

    wasp_check( text_document[m_version].is_int() );

    version = text_document[m_version].to_int();

    wasp_check( text_document[m_text].is_string() );

    text = text_document[m_text].to_string();

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

    DataObject content_changes;
    content_changes[m_range]        = DataObject();
    content_changes[m_range_length] = range_length;
    content_changes[m_text]         = text;

    pass &= buildRangeObject( *(content_changes[m_range].to_object()) ,
                                errors                                ,
                                start_line                            ,
                                start_character                       ,
                                end_line                              ,
                                end_character                         );

    DataObject text_document;
    text_document[m_uri]     = uri;
    text_document[m_version] = version;

    DataObject params;
    params[m_content_changes] = content_changes;
    params[m_text_document]   = text_document;

    object[m_params] =  params;
    object[m_method] = m_method_didchange;

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

    wasp_check( object[m_method].is_string() );

    wasp_check( object[m_method].to_string() == m_method_didchange );

    wasp_check( object[m_params].is_object() );

    const DataObject& params = *(object[m_params].to_object());

    wasp_check( params[m_text_document].is_object() );

    const DataObject& text_document = *(params[m_text_document].to_object());

    wasp_check( text_document[m_uri].is_string() );

    uri = text_document[m_uri].to_string();

    wasp_check( text_document[m_version].is_int() );

    version = text_document[m_version].to_int();

    wasp_check( params[m_content_changes].is_object() );

    const DataObject& content_changes = *(params[m_content_changes].to_object());

    wasp_check( content_changes[m_range].is_object() );

    const DataObject& range = *(content_changes[m_range].to_object());

    pass &= dissectRangeObject( range           ,
                                errors          ,
                                start_line      ,
                                start_character ,
                                end_line        ,
                                end_character   );

    wasp_check( content_changes[m_range_length].is_int() );

    range_length = content_changes[m_range_length].to_int();

    wasp_check( content_changes[m_text].is_string() );

    text = content_changes[m_text].to_string();

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
    text_document[m_uri] = uri;

    DataObject params;
    params[m_position]      = position;
    params[m_text_document] = text_document;

    object[m_params] =  params;
    object[m_id]     =  request_id;
    object[m_method] = m_method_completion;

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

    wasp_check( object[m_method].is_string() );

    wasp_check( object[m_method].to_string() == m_method_completion );

    wasp_check( object[m_id].is_int() );

    request_id = object[m_id].to_int();

    wasp_check( object[m_params].is_object() );

    const DataObject& params = *(object[m_params].to_object());

    wasp_check( params[m_text_document].is_object() );

    const DataObject& text_document = *(params[m_text_document].to_object());

    wasp_check( text_document[m_uri].is_string() );

    uri = text_document[m_uri].to_string();

    wasp_check( params[m_position].is_object() );

    const DataObject& position = *(params[m_position].to_object());

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
    text_document[m_uri] = uri;

    DataObject params;
    params[m_position]      = position;
    params[m_text_document] = text_document;

    object[m_params] =  params;
    object[m_id]     =  request_id;
    object[m_method] = m_method_definition;

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

    wasp_check( object[m_method].is_string() );

    wasp_check( object[m_method].to_string() == m_method_definition );

    wasp_check( object[m_id].is_int() );

    request_id = object[m_id].to_int();

    wasp_check( object[m_params].is_object() );

    const DataObject& params = *(object[m_params].to_object());

    wasp_check( params[m_text_document].is_object() );

    const DataObject& text_document = *(params[m_text_document].to_object());

    wasp_check( text_document[m_uri].is_string() );

    uri = text_document[m_uri].to_string();

    wasp_check( params[m_position].is_object() );

    const DataObject& position = *(params[m_position].to_object());

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
    text_document[m_uri] = uri;

    DataObject context;
    context[m_include_declaration] = include_declaration;

    DataObject params;
    params[m_position]      = position;
    params[m_text_document] = text_document;
    params[m_context]       = context;

    object[m_params] =  params;
    object[m_id]     =  request_id;
    object[m_method] = m_method_references;

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

    wasp_check( object[m_method].is_string() );

    wasp_check( object[m_method].to_string() == m_method_references );

    wasp_check( object[m_id].is_int() );

    request_id = object[m_id].to_int();

    wasp_check( object[m_params].is_object() );

    const DataObject& params = *(object[m_params].to_object());

    wasp_check( params[m_text_document].is_object() );

    const DataObject& text_document = *(params[m_text_document].to_object());

    wasp_check( text_document[m_uri].is_string() );

    uri = text_document[m_uri].to_string();

    wasp_check( params[m_position].is_object() );

    const DataObject& position = *(params[m_position].to_object());

    pass &= dissectPositionObject( position  ,
                                   errors    ,
                                   line      ,
                                   character );

    wasp_check( params[m_context].is_object() );

    const DataObject& context = *(params[m_context].to_object());

    wasp_check( context[m_include_declaration].is_bool() );

    include_declaration = context[m_include_declaration].to_bool();

    return pass;
}

bool buildFormattingRequest( DataObject        & object          ,
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

    DataObject options;
    options[m_tab_size]      = tab_size;
    options[m_insert_spaces] = insert_spaces;

    DataObject text_document;
    text_document[m_uri] = uri;

    DataObject params;
    params[m_range]         = DataObject();
    params[m_options]       = options;
    params[m_text_document] = text_document;

    pass &= buildRangeObject( *(params[m_range].to_object()) ,
                                errors                       ,
                                start_line                   ,
                                start_character              ,
                                end_line                     ,
                                end_character                );

    object[m_params] =  params;
    object[m_id]     =  request_id;
    object[m_method] = m_method_rangeformat;

    return pass;
}

bool dissectFormattingRequest( const DataObject   & object          ,
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

    wasp_check( object[m_method].is_string() );

    wasp_check( object[m_method].to_string() == m_method_rangeformat );

    wasp_check( object[m_id].is_int() );

    request_id = object[m_id].to_int();

    wasp_check( object[m_params].is_object() );

    const DataObject& params = *(object[m_params].to_object());

    wasp_check( params[m_text_document].is_object() );

    const DataObject& text_document = *(params[m_text_document].to_object());

    wasp_check( text_document[m_uri].is_string() );

    uri = text_document[m_uri].to_string();

    wasp_check( params[m_range].is_object() );

    const DataObject& range = *(params[m_range].to_object());

    pass &= dissectRangeObject( range           ,
                                errors          ,
                                start_line      ,
                                start_character ,
                                end_line        ,
                                end_character   );

    wasp_check( params[m_options].is_object() );

    const DataObject& options = *(params[m_options].to_object());

    wasp_check( options[m_tab_size].is_int() );

    tab_size = options[m_tab_size].to_int();

    wasp_check( options[m_insert_spaces].is_bool() );

    insert_spaces = options[m_insert_spaces].to_bool();

    return pass;
}

bool buildSymbolsRequest( DataObject        & object     ,
                          std::ostream      & errors     ,
                          int                 request_id ,
                          const std::string & uri        )
{
    bool pass = true;

    DataObject text_document;
    text_document[m_uri] = uri;

    DataObject params;
    params[m_text_document] = text_document;

    object[m_params] =  params;
    object[m_id]     =  request_id;
    object[m_method] = m_method_documentsymbol;

    return pass;
}

bool dissectSymbolsRequest( const DataObject   & object     ,
                                  std::ostream & errors     ,
                                  int          & request_id ,
                                  std::string  & uri        )
{
    bool pass = true;

    wasp_check( object[m_method].is_string() );

    wasp_check( object[m_method].to_string() == m_method_documentsymbol );

    wasp_check( object[m_id].is_int() );

    request_id = object[m_id].to_int();

    wasp_check( object[m_params].is_object() );

    const DataObject& params = *(object[m_params].to_object());

    wasp_check( params[m_text_document].is_object() );

    const DataObject& text_document = *(params[m_text_document].to_object());

    wasp_check( text_document[m_uri].is_string() );

    uri = text_document[m_uri].to_string();

    return pass;
}

bool buildDidCloseNotification( DataObject        & object ,
                                std::ostream      & errors ,
                                const std::string & uri    )
{
    bool pass = true;

    DataObject text_document;
    text_document[m_uri] = uri;

    DataObject params;
    params[m_text_document] = text_document;

    object[m_params] =  params;
    object[m_method] = m_method_didclose;

    return pass;
}

bool dissectDidCloseNotification( const DataObject   & object ,
                                        std::ostream & errors ,
                                        std::string  & uri    )
{
    bool pass = true;

    wasp_check( object[m_method].is_string() );

    wasp_check( object[m_method].to_string() == m_method_didclose );

    wasp_check( object[m_params].is_object() );

    const DataObject& params = *(object[m_params].to_object());

    wasp_check( params[m_text_document].is_object() );

    const DataObject& text_document = *(params[m_text_document].to_object());

    wasp_check( text_document[m_uri].is_string() );

    uri = text_document[m_uri].to_string();

    return pass;
}

bool buildShutdownRequest( DataObject   & object     ,
                           std::ostream & errors     ,
                           int            request_id )
{
    bool pass = true;

    DataObject params;

    object[m_params] =  params;
    object[m_id]     =  request_id;
    object[m_method] = m_method_shutdown;

    return pass;
}

bool dissectShutdownRequest( const DataObject   & object     ,
                                   std::ostream & errors     ,
                                   int          & request_id )
{
    bool pass = true;

    wasp_check( object[m_method].is_string() );

    wasp_check( object[m_method].to_string() == m_method_shutdown );

    wasp_check( object[m_id].is_int() );

    request_id = object[m_id].to_int();

    wasp_check( object[m_params].is_object() );

    return pass;
}

bool buildExitNotification( DataObject   & object ,
                            std::ostream & errors )
{
    bool pass = true;

    DataObject params;

    object[m_params] =  params;
    object[m_method] = m_method_exit;

    return pass;
}

bool dissectExitNotification( const DataObject   & object ,
                                    std::ostream & errors )
{
    bool pass = true;

    wasp_check( object[m_method].is_string() );

    wasp_check( object[m_method].to_string() == m_method_exit );

    wasp_check( object[m_params].is_object() );

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

    object[m_range]    = DataObject();
    object[m_severity] = severity;
    object[m_code]     = code;
    object[m_source]   = source;
    object[m_message]  = message;

    pass &= buildRangeObject( *(object[m_range].to_object()) ,
                                errors                       ,
                                start_line                   ,
                                start_character              ,
                                end_line                     ,
                                end_character                );

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

    wasp_check( object[m_range].is_object() );

    const DataObject& range = *(object[m_range].to_object());

    pass &= dissectRangeObject( range           ,
                                errors          ,
                                start_line      ,
                                start_character ,
                                end_line        ,
                                end_character   );

    wasp_check( object[m_severity].is_int() );

    severity = object[m_severity].to_int();

    wasp_check( object[m_code].is_string() );

    code = object[m_code].to_string();

    wasp_check( object[m_source].is_string() );

    source = object[m_source].to_string();

    wasp_check( object[m_message].is_string() );

    message = object[m_message].to_string();

    return pass;
}

bool buildPublishDiagnosticsNotification( DataObject        & object      ,
                                          std::ostream      & errors      ,
                                          const std::string & uri         ,
                                          const DataArray   & diagnostics )
{
    bool pass = true;

    DataObject params;
    params[m_uri]         = uri;
    params[m_diagnostics] = diagnostics;

    object[m_params] =  params;
    object[m_method] = m_method_pubdiagnostics;

    return pass;
}

bool dissectPublishDiagnosticsNotification( const DataObject   & object      ,
                                                  std::ostream & errors      ,
                                                  std::string  & uri         ,
                                                  DataArray    & diagnostics )
{
    bool pass = true;

    wasp_check( object[m_method].is_string() );

    wasp_check( object[m_method].to_string() == m_method_pubdiagnostics );

    wasp_check( object[m_params].is_object() );

    const DataObject& params = *(object[m_params].to_object());

    wasp_check( params[m_uri].is_string() );

    uri = params[m_uri].to_string();

    wasp_check( params[m_diagnostics].is_array() );

    diagnostics = *(params[m_diagnostics].to_array());

    return pass;
}

bool buildInitializeResponse( DataObject        & object              ,
                              std::ostream      & errors              ,
                              int                 request_id          ,
                              const DataObject  & server_capabilities )
{
    bool pass = true;

    DataObject result;
    result[m_capabilities] = server_capabilities;

    object[m_result] = result;
    object[m_id]     = request_id;

    return pass;
}

bool dissectInitializeResponse( const DataObject   & object              ,
                                      std::ostream & errors              ,
                                      int          & request_id          ,
                                      DataObject   & server_capabilities )
{
    bool pass = true;

    wasp_check( object[m_id].is_int() );

    request_id = object[m_id].to_int();

    wasp_check( object[m_result].is_object() );

    const DataObject& result = *(object[m_result].to_object());

    wasp_check( result[m_capabilities].is_object() );

    server_capabilities = *(result[m_capabilities].to_object());

    return pass;
}

bool buildShutdownResponse( DataObject        & object     ,
                            std::ostream      & errors     ,
                            int                 request_id )
{
    bool pass = true;

    DataObject result;

    object[m_result] = result;
    object[m_id]     = request_id;

    return pass;
}

bool dissectShutdownResponse( const DataObject   & object     ,
                                    std::ostream & errors     ,
                                    int          & request_id )
{
    bool pass = true;

    wasp_check( object[m_id].is_int() );

    request_id = object[m_id].to_int();

    wasp_check( object[m_result].is_object() );

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

    DataObject text_edit;
    text_edit[m_range]    = DataObject();
    text_edit[m_new_text] = new_text;

    pass &= buildRangeObject( *(text_edit[m_range].to_object()) ,
                                errors                          ,
                                start_line                      ,
                                start_character                 ,
                                end_line                        ,
                                end_character                   );

    object[m_text_edit]     = text_edit;
    object[m_label]         = label;
    object[m_kind]          = kind;
    object[m_detail]        = detail;
    object[m_documentation] = documentation;
    object[m_deprecated]    = deprecated;
    object[m_preselect]     = preselect;

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

    wasp_check( object[m_text_edit].is_object() );

    const DataObject& text_edit = *(object[m_text_edit].to_object());

    wasp_check( text_edit[m_range].is_object() );

    const DataObject& range = *(text_edit[m_range].to_object());

    pass &= dissectRangeObject( range           ,
                                errors          ,
                                start_line      ,
                                start_character ,
                                end_line        ,
                                end_character   );

    wasp_check( text_edit[m_new_text].is_string() );

    new_text = text_edit[m_new_text].to_string();

    wasp_check( object[m_label].is_string() );

    label = object[m_label].to_string();

    wasp_check( object[m_kind].is_int() );

    kind = object[m_kind].to_int();

    wasp_check( object[m_detail].is_string() );

    detail = object[m_detail].to_string();

    wasp_check( object[m_documentation].is_string() );

    documentation = object[m_documentation].to_string();

    wasp_check( object[m_deprecated].is_bool() );

    deprecated = object[m_deprecated].to_bool();

    wasp_check( object[m_preselect].is_bool() );

    preselect = object[m_preselect].to_bool();

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
    result[m_is_incomplete] = is_incomplete;
    result[m_items]         = completion_items;

    object[m_result] = result;
    object[m_id]     = request_id;

    return pass;
}

bool dissectCompletionResponse( const DataObject   & object           ,
                                      std::ostream & errors           ,
                                      int          & request_id       ,
                                      bool         & is_incomplete    ,
                                      DataArray    & completion_items )
{
    bool pass = true;

    wasp_check( object[m_id].is_int() );

    request_id = object[m_id].to_int();

    wasp_check( object[m_result].is_object() );

    const DataObject& result = *(object[m_result].to_object());

    wasp_check( result[m_is_incomplete].is_bool() );

    is_incomplete = result[m_is_incomplete].to_bool();

    wasp_check( result[m_items].is_array() );

    completion_items = *(result[m_items].to_array());

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

    object[m_range] = DataObject();
    object[m_uri]   = uri;

    pass &= buildRangeObject( *(object[m_range].to_object()) ,
                                errors                       ,
                                start_line                   ,
                                start_character              ,
                                end_line                     ,
                                end_character                );

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

    wasp_check( object[m_uri].is_string() );

    uri = object[m_uri].to_string();

    wasp_check( object[m_range].is_object() );

    const DataObject& range = *(object[m_range].to_object());

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

    object[m_result] = location_objects;
    object[m_id]     = request_id;

    return pass;
}

bool dissectLocationsResponse( const DataObject   & object           ,
                                     std::ostream & errors           ,
                                     int          & request_id       ,
                                     DataArray    & location_objects )
{
    bool pass = true;

    wasp_check( object[m_id].is_int() );

    request_id = object[m_id].to_int();

    wasp_check( object[m_result].is_array() );

    location_objects = *(object[m_result].to_array());

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

    object[m_range]    = DataObject();
    object[m_new_text] = new_text;

    pass &= buildRangeObject( *(object[m_range].to_object()) ,
                                errors                       ,
                                start_line                   ,
                                start_character              ,
                                end_line                     ,
                                end_character                );

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

    wasp_check( object[m_range].is_object() );

    const DataObject& range = *(object[m_range].to_object());

    pass &= dissectRangeObject( range           ,
                                errors          ,
                                start_line      ,
                                start_character ,
                                end_line        ,
                                end_character   );

    wasp_check( object[m_new_text].is_string() );

    new_text = object[m_new_text].to_string();

    return pass;
}

bool buildDocumentSymbolObject( DataObject        & object                    ,
                                std::ostream      & errors                    ,
                                const std::string & name                      ,
                                const std::string & detail                    ,
                                int                 kind                      ,
                                bool                deprecated                ,
                                int                 start_line                ,
                                int                 start_character           ,
                                int                 end_line                  ,
                                int                 end_character             ,
                                int                 selection_start_line      ,
                                int                 selection_start_character ,
                                int                 selection_end_line        ,
                                int                 selection_end_character   )
{
    bool pass = true;

    object[m_name]            = name;
    object[m_detail]          = detail;
    object[m_kind]            = kind;
    object[m_deprecated]      = deprecated;
    object[m_range]           = DataObject();
    object[m_selection_range] = DataObject();
    object[m_children]        = DataArray();

    pass &= buildRangeObject( *(object[m_range].to_object()) ,
                                errors                       ,
                                start_line                   ,
                                start_character              ,
                                end_line                     ,
                                end_character                );

    pass &= buildRangeObject( *(object[m_selection_range].to_object())  ,
                                errors                                  ,
                                selection_start_line                    ,
                                selection_start_character               ,
                                selection_end_line                      ,
                                selection_end_character                 );

    return pass;
}

bool dissectDocumentSymbolObject( const DataObject   & object                    ,
                                        std::ostream & errors                    ,
                                        std::string  & name                      ,
                                        std::string  & detail                    ,
                                        int          & kind                      ,
                                        bool         & deprecated                ,
                                        int          & start_line                ,
                                        int          & start_character           ,
                                        int          & end_line                  ,
                                        int          & end_character             ,
                                        int          & selection_start_line      ,
                                        int          & selection_start_character ,
                                        int          & selection_end_line        ,
                                        int          & selection_end_character   )
{
    bool pass = true;

    wasp_check( object[m_range].is_object() );

    const DataObject& range = *(object[m_range].to_object());

    pass &= dissectRangeObject( range           ,
                                errors          ,
                                start_line      ,
                                start_character ,
                                end_line        ,
                                end_character   );

    wasp_check( object[m_selection_range].is_object() );

    const DataObject& selection_range = *(object[m_selection_range].to_object());

    pass &= dissectRangeObject( selection_range           ,
                                errors                    ,
                                selection_start_line      ,
                                selection_start_character ,
                                selection_end_line        ,
                                selection_end_character   );

    wasp_check( object[m_name].is_string() );

    name = object[m_name].to_string();

    wasp_check( object[m_detail].is_string() );

    detail = object[m_detail].to_string();

    wasp_check( object[m_kind].is_int() );

    kind = object[m_kind].to_int();

    wasp_check( object[m_deprecated].is_bool() );

    deprecated = object[m_deprecated].to_bool();

    return pass;
}

DataObject & addDocumentSymbolChild( DataObject & parent )
{
    wasp_check( parent[m_children].is_array() );

    parent[m_children].to_array()->push_back( DataObject() );

    return *(parent[m_children].to_array()->back().to_object());
}

DataArray * getDocumentSymbolChildren( const DataObject & parent )
{
    wasp_check( parent[m_children].is_array() );

    return parent[m_children].to_array();
}

bool buildFormattingResponse( DataObject        & object           ,
                              std::ostream      & errors           ,
                              int                 request_id       ,
                              const DataArray   & textedit_objects )
{
    bool pass = true;

    DataObject result;

    object[m_result] = textedit_objects;
    object[m_id]     = request_id;

    return pass;
}

bool dissectFormattingResponse( const DataObject   & object           ,
                                      std::ostream & errors           ,
                                      int          & request_id       ,
                                      DataArray    & textedit_objects )
{
    bool pass = true;

    wasp_check( object[m_id].is_int() );

    request_id = object[m_id].to_int();

    wasp_check( object[m_result].is_array() );

    textedit_objects = *(object[m_result].to_array());

    return pass;
}
//make these bool - return false on each failure - and wrap the actual call in wasp_check
void verifyInitializeResponse( const DataObject & object )
{
    wasp_check( object[m_id].is_int() );

    wasp_check( object[m_result].is_object() );

    wasp_check( object[m_result][m_capabilities].is_object() );
}

void verifyDiagnosticResponse( const DataObject & object )
{
    wasp_check( object[m_method].is_string() );

    wasp_check( object[m_method].to_string() == m_method_pubdiagnostics );

    wasp_check( object[m_params].is_object() );

    wasp_check( object[m_params][m_uri].is_string() );

    wasp_check( object[m_params][m_diagnostics].is_array() );
}

void verifyCompletionResponse( const DataObject & object )
{
    wasp_check( object[m_id].is_int() );

    wasp_check( object[m_result].is_object() );

    wasp_check( object[m_result][m_is_incomplete].is_bool() );

    wasp_check( object[m_result][m_items].is_array() );
}

void verifyDefinitionResponse( const DataObject & object )
{
    wasp_check( object[m_id].is_int() );

    wasp_check( object[m_result].is_array() );
}

void verifyReferencesResponse( const DataObject & object )
{
    wasp_check( object[m_id].is_int() );

    wasp_check( object[m_result].is_array() );
}

void verifyFormattingResponse( const DataObject & object )
{
    wasp_check( object[m_id].is_int() );

    wasp_check( object[m_result].is_array() );
}

void verifyShutdownResponse( const DataObject & object )
{
    wasp_check( object[m_id].is_int() );

    wasp_check( object[m_result].is_object() );
}

DataArray * getDiagnosticResponseArray( const DataObject & object )
{
    wasp_check( object[m_params][m_diagnostics].is_array() );

    return object[m_params][m_diagnostics].to_array();
}

DataArray * getCompletionResponseArray( const DataObject & object )
{
    wasp_check(  object[m_result][m_items].is_array() );

    return object[m_result][m_items].to_array();
}

DataArray * getDefinitionResponseArray( const DataObject & object )
{
    wasp_check( object[m_result].is_array() );

    return object[m_result].to_array();
}

DataArray * getReferencesResponseArray( const DataObject & object )
{
    wasp_check( object[m_result].is_array() );

    return object[m_result].to_array();
}

DataArray * getFormattingResponseArray( const DataObject & object )
{
    wasp_check( object[m_result].is_array() );

    return object[m_result].to_array();
}

} // namespace lsp
} // namespace wasp
