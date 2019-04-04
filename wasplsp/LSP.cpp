#include "LSP.h"

namespace wasp {
namespace lsp  {

bool checkRange( std::ostream & errors          ,
                 int            start_line      ,
                 int            start_character ,
                 int            end_line        ,
                 int            end_character   )
{
    if (( start_line  > end_line ) ||
        ( start_line == end_line && start_character > end_character ))
    {
        errors << "Error:: Range start ( line:" << start_line << " column:"
               << start_character << " ) must be less than range end ( line:"
               << end_line << " column:" << end_character << " )" << std::endl;
        return false;
    }

    return true;
}

bool buildInitializeRequest( DataObject        & object              ,
                             std::ostream      & errors              ,
                             int                 process_id          ,
                             const std::string & root_uri            ,
                             const DataObject  & client_capabilities )
{
    DataObject params;

    object[_method]                = "initialize";
    object[_params]                =  params;
    object[_params][_process_id]   =  process_id;
    object[_params][_root_uri]     =  root_uri;
    object[_params][_capabilities] =  client_capabilities;

    return true;
}

bool buildInitializedNotification( DataObject   & object ,
                                   std::ostream & errors )
{
    DataObject params;

    object[_method] = "initialized";
    object[_params] =  params;

    return true;
}

bool buildShutdownRequest( DataObject   & object ,
                           std::ostream & errors )
{
    DataObject params;

    object[_method] = "shutdown";
    object[_params] =  params;

    return true;
}

bool buildExitNotification( DataObject   & object ,
                            std::ostream & errors )
{
    DataObject params;

    object[_method] = "exit";
    object[_params] =  params;

    return true;
}

bool buildDidOpenNotification( DataObject        & object      ,
                               std::ostream      & errors      ,
                               const std::string & uri         ,
                               const std::string & language_id ,
                               double              version     ,
                               const std::string & text        )
{
    DataObject params;
    DataObject text_document;

    object[_method]                               = "textDocument/didOpen";
    object[_params]                               =  params;
    object[_params][_text_document]               =  text_document;
    object[_params][_text_document][_uri]         =  uri;
    object[_params][_text_document][_language_id] =  language_id;
    object[_params][_text_document][_version]     =  version;
    object[_params][_text_document][_text]        =  text;

    return true;
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
    if ( !checkRange( errors          ,
                      start_line      ,
                      start_character ,
                      end_line        ,
                      end_character   )) return false;

    DataObject params;
    DataObject text_document;
    DataObject content_changes;
    DataObject range;
    DataObject start;
    DataObject end;

    object[_method]                                               = "textDocument/didChange";
    object[_params]                                               =  params;
    object[_params][_text_document]                               =  text_document;
    object[_params][_text_document][_uri]                         =  uri;
    object[_params][_text_document][_version]                     =  version;
    object[_params][_content_changes]                             =  content_changes;
    object[_params][_content_changes][_range]                     =  range;
    object[_params][_content_changes][_range][_start]             =  start;
    object[_params][_content_changes][_range][_start][_line]      =  start_line;
    object[_params][_content_changes][_range][_start][_character] =  start_character;
    object[_params][_content_changes][_range][_end]               =  end;
    object[_params][_content_changes][_range][_end][_line]        =  end_line;
    object[_params][_content_changes][_range][_end][_character]   =  end_character;
    object[_params][_content_changes][_range_length]              =  range_length;
    object[_params][_content_changes][_text]                      =  text;

    return true;
}

bool buildCompletionRequest( DataObject        & object    ,
                             std::ostream      & errors    ,
                             const std::string & uri       ,
                             int                 line      ,
                             int                 character )
{
    DataObject params;
    DataObject text_document;
    DataObject position;

    object[_method]                        = "textDocument/completion";
    object[_params]                        =  params;
    object[_params][_text_document]        =  text_document;
    object[_params][_text_document][_uri]  =  uri;
    object[_params][_position]             =  position;
    object[_params][_position][_line]      =  line;
    object[_params][_position][_character] =  character;

    return true;
}

bool buildDefinitionRequest( DataObject        & object    ,
                             std::ostream      & errors    ,
                             const std::string & uri       ,
                             int                 line      ,
                             int                 character )
{
    DataObject params;
    DataObject text_document;
    DataObject position;

    object[_method]                        = "textDocument/definition";
    object[_params]                        =  params;
    object[_params][_text_document]        =  text_document;
    object[_params][_text_document][_uri]  =  uri;
    object[_params][_position]             =  position;
    object[_params][_position][_line]      =  line;
    object[_params][_position][_character] =  character;

    return true;
}

bool buildReferencesRequest( DataObject        & object              ,
                             std::ostream      & errors              ,
                             const std::string & uri                 ,
                             int                 line                ,
                             int                 character           ,
                             bool                include_declaration )
{
    DataObject params;
    DataObject text_document;
    DataObject position;
    DataObject context;

    object[_method]                                 = "textDocument/references";
    object[_params]                                 =  params;
    object[_params][_text_document]                 =  text_document;
    object[_params][_text_document][_uri]           =  uri;
    object[_params][_position]                      =  position;
    object[_params][_position][_line]               =  line;
    object[_params][_position][_character]          =  character;
    object[_params][_context]                       =  context;
    object[_params][_context][_include_declaration] =  include_declaration;

    return true;
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
    if ( !checkRange( errors          ,
                      start_line      ,
                      start_character ,
                      end_line        ,
                      end_character   )) return false;

    DataObject params;
    DataObject text_document;
    DataObject content_changes;
    DataObject range;
    DataObject start;
    DataObject end;
    DataObject options;

    object[_method]                             = "textDocument/rangeFormatting";
    object[_params]                             =  params;
    object[_params][_text_document]             =  text_document;
    object[_params][_text_document][_uri]       =  uri;
    object[_params][_range]                     =  range;
    object[_params][_range][_start]             =  start;
    object[_params][_range][_start][_line]      =  start_line;
    object[_params][_range][_start][_character] =  start_character;
    object[_params][_range][_end]               =  end;
    object[_params][_range][_end][_line]        =  end_line;
    object[_params][_range][_end][_character]   =  end_character;
    object[_params][_options]                   =  options;
    object[_params][_options][_tab_size]        =  tab_size;
    object[_params][_options][_insert_spaces]   =  insert_spaces;

    return true;
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
    if ( !checkRange( errors          ,
                      start_line      ,
                      start_character ,
                      end_line        ,
                      end_character   )) return false;

    DataObject range;
    DataObject start;
    DataObject end;

    object[_range]                     =  range;
    object[_range][_start]             =  start;
    object[_range][_start][_line]      =  start_line;
    object[_range][_start][_character] =  start_character;
    object[_range][_end]               =  end;
    object[_range][_end][_line]        =  end_line;
    object[_range][_end][_character]   =  end_character;
    object[_severity]                  =  severity;
    object[_code]                      =  code;
    object[_source]                    =  source;
    object[_message]                   =  message;

    return true;
}

bool buildPublishDiagnosticsNotification( DataObject        & object      ,
                                          std::ostream      & errors      ,
                                          const std::string & uri         ,
                                          const DataArray   & diagnostics )
{
    DataObject params;

    object[_method]               = "textDocument/publishDiagnostics";
    object[_params]               =  params;
    object[_params][_uri]         =  uri;
    object[_params][_diagnostics] =  diagnostics;

    return true;
}

bool buildInitializeResponse( DataObject        & object              ,
                              std::ostream      & errors              ,
                              const DataObject  & server_capabilities )
{
    DataObject result;

    object[_result]                = result;
    object[_result][_capabilities] = server_capabilities;

    return true;
}

bool buildShutdownResponse( DataObject   & object ,
                            std::ostream & errors )
{
    DataObject result;

    object[_result] = result;

    return true;
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
    if ( !checkRange( errors          ,
                      start_line      ,
                      start_character ,
                      end_line        ,
                      end_character   )) return false;

    DataObject text_edit;
    DataObject range;
    DataObject start;
    DataObject end;

    object[_label]                                 = label;
    object[_text_edit]                             = text_edit;
    object[_text_edit][_range]                     = range;
    object[_text_edit][_range][_start]             = start;
    object[_text_edit][_range][_start][_line]      = start_line;
    object[_text_edit][_range][_start][_character] = start_character;
    object[_text_edit][_range][_end]               = end;
    object[_text_edit][_range][_end][_line]        = end_line;
    object[_text_edit][_range][_end][_character]   = end_character;
    object[_text_edit][_new_text]                  = new_text;
    object[_kind]                                  = kind;
    object[_detail]                                = detail;
    object[_documentation]                         = documentation;
    object[_deprecated]                            = deprecated;
    object[_preselect]                             = preselect;

    return true;
}

bool buildCompletionResponse( DataObject        & object           ,
                              std::ostream      & errors           ,
                              bool                is_incomplete    ,
                              const DataArray   & completion_items )
{
    DataObject result;

    object[_result]                 = result;
    object[_result][_is_incomplete] = is_incomplete;
    object[_result][_items]         = completion_items;

    return true;
}

bool buildLocationObject( DataObject        & object          ,
                          std::ostream      & errors          ,
                          const std::string & uri             ,
                          int                 start_line      ,
                          int                 start_character ,
                          int                 end_line        ,
                          int                 end_character   )
{
    if ( !checkRange( errors          ,
                      start_line      ,
                      start_character ,
                      end_line        ,
                      end_character   )) return false;

    DataObject range;
    DataObject start;
    DataObject end;

    object[_uri]                       = uri;
    object[_range]                     = range;
    object[_range][_start]             = start;
    object[_range][_start][_line]      = start_line;
    object[_range][_start][_character] = start_character;
    object[_range][_end]               = end;
    object[_range][_end][_line]        = end_line;
    object[_range][_end][_character]   = end_character;

    return true;
}

bool buildLocationsResponse( DataObject        & object           ,
                             std::ostream      & errors           ,
                             const DataArray   & location_objects )
{
    DataObject result;

    object[_result] = location_objects;

    return true;
}

bool buildTextEditObject( DataObject        & object          ,
                          std::ostream      & errors          ,
                          int                 start_line      ,
                          int                 start_character ,
                          int                 end_line        ,
                          int                 end_character   ,
                          const std::string & new_text        )
{
    if ( !checkRange( errors          ,
                      start_line      ,
                      start_character ,
                      end_line        ,
                      end_character   )) return false;

    DataObject range;
    DataObject start;
    DataObject end;

    object[_range]                     = range;
    object[_range][_start]             = start;
    object[_range][_start][_line]      = start_line;
    object[_range][_start][_character] = start_character;
    object[_range][_end]               = end;
    object[_range][_end][_line]        = end_line;
    object[_range][_end][_character]   = end_character;
    object[_new_text]                  = new_text;

    return true;
}

bool buildRangeFormattingResponse( DataObject        & object           ,
                                   std::ostream      & errors           ,
                                   const DataArray   & textedit_objects )
{
    DataObject result;

    object[_result] = textedit_objects;

    return true;
}

}
}
