#ifndef WASPLSP_LSP_H
#define WASPLSP_LSP_H

#include <string>
#include <iostream>
#include "waspcore/Object.h"
#include "waspcore/decl.h"

namespace wasp {
namespace lsp  {

WASP_PUBLIC
bool objectToStream( DataObject   & object ,
                     std::ostream & stream ,
                     std::ostream & errors );

WASP_PUBLIC
bool streamToObject( std::istream & stream ,
                     DataObject   & object ,
                     std::ostream & errors );

WASP_PUBLIC
bool checkPosition( std::ostream & errors    ,
                    int            line      ,
                    int            character );

WASP_PUBLIC
bool checkRange( std::ostream & errors          ,
                 int            start_line      ,
                 int            start_character ,
                 int            end_line        ,
                 int            end_character   );

WASP_PUBLIC
bool buildPositionObject( DataObject   & object    ,
                          std::ostream & errors    ,
                          int            line      ,
                          int            character );

WASP_PUBLIC
bool dissectPositionObject( const DataObject   & object    ,
                                  std::ostream & errors    ,
                                  int          & line      ,
                                  int          & character );

WASP_PUBLIC
bool buildRangeObject( DataObject   & object          ,
                       std::ostream & errors          ,
                       int            start_line      ,
                       int            start_character ,
                       int            end_line        ,
                       int            end_character   );

WASP_PUBLIC
bool dissectRangeObject( const DataObject      & object          ,
                               std::ostream    & errors          ,
                               int             & start_line      ,
                               int             & start_character ,
                               int             & end_line        ,
                               int             & end_character   );

WASP_PUBLIC
bool buildInitializeRequest( DataObject        & object              ,
                             std::ostream      & errors              ,
                             int                 request_id          ,
                             int                 process_id          ,
                             const std::string & root_uri            ,
                             const DataObject  & client_capabilities );

WASP_PUBLIC
bool dissectInitializeRequest( const DataObject        & object              ,
                                     std::ostream      & errors              ,
                                     int               & request_id          ,
                                     int               & process_id          ,
                                     std::string       & root_uri            ,
                                     DataObject        & client_capabilities );

WASP_PUBLIC
bool buildInitializedNotification( DataObject   & object ,
                                   std::ostream & errors );

WASP_PUBLIC
bool dissectInitializedNotification( const DataObject   & object ,
                                           std::ostream & errors );

WASP_PUBLIC
bool buildShutdownRequest( DataObject   & object     ,
                           std::ostream & errors     ,
                           int            request_id );

WASP_PUBLIC
bool dissectShutdownRequest( const DataObject   & object     ,
                                   std::ostream & errors     ,
                                   int          & request_id );

WASP_PUBLIC
bool buildExitNotification( DataObject   & object ,
                            std::ostream & errors );

WASP_PUBLIC
bool dissectExitNotification( const DataObject   & object ,
                                    std::ostream & errors );

WASP_PUBLIC
bool buildDidOpenNotification( DataObject        & object      ,
                               std::ostream      & errors      ,
                               const std::string & uri         ,
                               const std::string & language_id ,
                               int                 version     ,
                               const std::string & text        );

WASP_PUBLIC
bool dissectDidOpenNotification( const DataObject   & object      ,
                                       std::ostream & errors      ,
                                       std::string  & uri         ,
                                       std::string  & language_id ,
                                       int          & version     ,
                                       std::string  & text        );

WASP_PUBLIC
bool buildDidChangeNotification( DataObject        & object          ,
                                 std::ostream      & errors          ,
                                 const std::string & uri             ,
                                 int                 version         ,
                                 int                 start_line      ,
                                 int                 start_character ,
                                 int                 end_line        ,
                                 int                 end_character   ,
                                 int                 range_length    ,
                                 const std::string & text            );

WASP_PUBLIC
bool dissectDidChangeNotification( const DataObject   & object          ,
                                         std::ostream & errors          ,
                                         std::string  & uri             ,
                                         int          & version         ,
                                         int          & start_line      ,
                                         int          & start_character ,
                                         int          & end_line        ,
                                         int          & end_character   ,
                                         int          & range_length    ,
                                         std::string  & text            );

WASP_PUBLIC
bool buildCompletionRequest( DataObject        & object     ,
                             std::ostream      & errors     ,
                             int                 request_id ,
                             const std::string & uri        ,
                             int                 line       ,
                             int                 character  );

WASP_PUBLIC
bool dissectCompletionRequest( const DataObject   & object     ,
                                     std::ostream & errors     ,
                                     int          & request_id ,
                                     std::string  & uri        ,
                                     int          & line       ,
                                     int          & character  );

WASP_PUBLIC
bool buildDefinitionRequest( DataObject        & object     ,
                             std::ostream      & errors     ,
                             int                 request_id ,
                             const std::string & uri        ,
                             int                 line       ,
                             int                 character );

WASP_PUBLIC
bool dissectDefinitionRequest( const DataObject   & object     ,
                                     std::ostream & errors     ,
                                     int          & request_id ,
                                     std::string  & uri        ,
                                     int          & line       ,
                                     int          & character  );

WASP_PUBLIC
bool buildReferencesRequest( DataObject        & object              ,
                             std::ostream      & errors              ,
                             int                 request_id          ,
                             const std::string & uri                 ,
                             int                 line                ,
                             int                 character           ,
                             bool                include_declaration );

WASP_PUBLIC
bool dissectReferencesRequest( const DataObject   & object              ,
                                     std::ostream & errors              ,
                                     int          & request_id          ,
                                     std::string  & uri                 ,
                                     int          & line                ,
                                     int          & character           ,
                                     bool         & include_declaration );

WASP_PUBLIC
bool buildRangeFormattingRequest( DataObject        & object          ,
                                  std::ostream      & errors          ,
                                  int                 request_id      ,
                                  const std::string & uri             ,
                                  int                 start_line      ,
                                  int                 start_character ,
                                  int                 end_line        ,
                                  int                 end_character   ,
                                  int                 tab_size        ,
                                  bool                insert_spaces   );

WASP_PUBLIC
bool dissectRangeFormattingRequest( const DataObject   & object          ,
                                          std::ostream & errors          ,
                                          int          & request_id      ,
                                          std::string  & uri             ,
                                          int          & start_line      ,
                                          int          & start_character ,
                                          int          & end_line        ,
                                          int          & end_character   ,
                                          int          & tab_size        ,
                                          bool         & insert_spaces   );

WASP_PUBLIC
bool buildDiagnosticObject( DataObject        & object          ,
                            std::ostream      & errors          ,
                            int                 start_line      ,
                            int                 start_character ,
                            int                 end_line        ,
                            int                 end_character   ,
                            int                 severity        ,
                            const std::string & code            ,
                            const std::string & source          ,
                            const std::string & message         );

WASP_PUBLIC
bool dissectDiagnosticObject( const DataObject   & object          ,
                                    std::ostream & errors          ,
                                    int          & start_line      ,
                                    int          & start_character ,
                                    int          & end_line        ,
                                    int          & end_character   ,
                                    int          & severity        ,
                                    std::string  & code            ,
                                    std::string  & source          ,
                                    std::string  & message         );

WASP_PUBLIC
bool buildPublishDiagnosticsNotification( DataObject        & object      ,
                                          std::ostream      & errors      ,
                                          const std::string & uri         ,
                                          const DataArray   & diagnostics );

WASP_PUBLIC
bool dissectPublishDiagnosticsNotification( const DataObject   & object      ,
                                                  std::ostream & errors      ,
                                                  std::string  & uri         ,
                                                  DataArray    & diagnostics );

WASP_PUBLIC
bool buildInitializeResponse( DataObject        & object              ,
                              std::ostream      & errors              ,
                              int                 request_id          ,
                              const DataObject  & server_capabilities );

WASP_PUBLIC
bool dissectInitializeResponse( const DataObject   & object              ,
                                      std::ostream & errors              ,
                                      int          & request_id          ,
                                      DataObject   & server_capabilities );

WASP_PUBLIC
bool buildShutdownResponse( DataObject        & object     ,
                            std::ostream      & errors     ,
                            int                 request_id );

WASP_PUBLIC
bool dissectShutdownResponse( const DataObject   & object     ,
                                    std::ostream & errors     ,
                                    int          & request_id );

WASP_PUBLIC
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
                            bool                preselect       );

WASP_PUBLIC
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
                                    bool         & preselect       );

WASP_PUBLIC
bool buildCompletionResponse( DataObject        & object           ,
                              std::ostream      & errors           ,
                              int                 request_id       ,
                              bool                is_incomplete    ,
                              const DataArray   & completion_items );

WASP_PUBLIC
bool dissectCompletionResponse( const DataObject   & object           ,
                                      std::ostream & errors           ,
                                      int          & request_id       ,
                                      bool         & is_incomplete    ,
                                      DataArray    & completion_items );

WASP_PUBLIC
bool buildLocationObject( DataObject        & object          ,
                          std::ostream      & errors          ,
                          const std::string & uri             ,
                          int                 start_line      ,
                          int                 start_character ,
                          int                 end_line        ,
                          int                 end_character   );

WASP_PUBLIC
bool dissectLocationObject( const DataObject   & object          ,
                                  std::ostream & errors          ,
                                  std::string  & uri             ,
                                  int          & start_line      ,
                                  int          & start_character ,
                                  int          & end_line        ,
                                  int          & end_character   );

WASP_PUBLIC
bool buildLocationsResponse( DataObject        & object           ,
                             std::ostream      & errors           ,
                             int                 request_id       ,
                             const DataArray   & location_objects );

WASP_PUBLIC
bool dissectLocationsResponse( const DataObject   & object           ,
                                     std::ostream & errors           ,
                                     int          & request_id       ,
                                     DataArray    & location_objects );

WASP_PUBLIC
bool buildTextEditObject( DataObject        & object          ,
                          std::ostream      & errors          ,
                          int                 start_line      ,
                          int                 start_character ,
                          int                 end_line        ,
                          int                 end_character   ,
                          const std::string & new_text        );

WASP_PUBLIC
bool dissectTextEditObject( const DataObject   & object          ,
                                  std::ostream & errors          ,
                                  int          & start_line      ,
                                  int          & start_character ,
                                  int          & end_line        ,
                                  int          & end_character   ,
                                  std::string  & new_text        );

WASP_PUBLIC
bool buildRangeFormattingResponse( DataObject        & object           ,
                                   std::ostream      & errors           ,
                                   int                 request_id       ,
                                   const DataArray   & textedit_objects );

WASP_PUBLIC
bool dissectRangeFormattingResponse( const DataObject   & object           ,
                                           std::ostream & errors           ,
                                           int          & request_id       ,
                                           DataArray    & textedit_objects );

static const char m_rpc_content_len_key[]   = "Content-Length:";
static const char m_rpc_separator[]         = "\r\n\r\n";
static const char m_rpc_jsonrpc_key[]       = "jsonrpc";
static const char m_rpc_jsonrpc_val[]       = "2.0";
static const char m_error[]                 = "Error:: ";
static const char m_id[]                    = "id";
static const char m_method_initialize[]     = "initialize";
static const char m_method_initialized[]    = "initialized";
static const char m_method_shutdown[]       = "shutdown";
static const char m_method_exit[]           = "exit";
static const char m_method_didopen[]        = "textDocument/didOpen";
static const char m_method_didchange[]      = "textDocument/didChange";
static const char m_method_completion[]     = "textDocument/completion";
static const char m_method_definition[]     = "textDocument/definition";
static const char m_method_references[]     = "textDocument/references";
static const char m_method_rangeformat[]    = "textDocument/rangeFormatting";
static const char m_method_pubdiagnostics[] = "textDocument/publishDiagnostics";
static const char m_method[]                = "method";
static const char m_params[]                = "params";
static const char m_result[]                = "result";
static const char m_process_id[]            = "processId";
static const char m_root_uri[]              = "rootUri";
static const char m_capabilities[]          = "capabilities";
static const char m_text_document[]         = "textDocument";
static const char m_uri[]                   = "uri";
static const char m_language_id[]           = "languageId";
static const char m_version[]               = "version";
static const char m_text[]                  = "text";
static const char m_content_changes[]       = "contentChanges";
static const char m_range[]                 = "range";
static const char m_start[]                 = "start";
static const char m_end[]                   = "end";
static const char m_line[]                  = "line";
static const char m_character[]             = "character";
static const char m_range_length[]          = "range_length";
static const char m_position[]              = "position";
static const char m_context[]               = "context";
static const char m_include_declaration[]   = "includeDeclaration";
static const char m_options[]               = "options";
static const char m_tab_size[]              = "tabSize";
static const char m_insert_spaces[]         = "insertSpaces";
static const char m_severity[]              = "severity";
static const char m_code[]                  = "code";
static const char m_source[]                = "source";
static const char m_message[]               = "message";
static const char m_diagnostics[]           = "diagnostics";
static const char m_label[]                 = "label";
static const char m_text_edit[]             = "textEdit";
static const char m_new_text[]              = "newText";
static const char m_kind[]                  = "kind";
static const char m_detail[]                = "detail";
static const char m_documentation[]         = "documentation";
static const char m_deprecated[]            = "deprecated";
static const char m_preselect[]             = "preselect";
static const char m_items[]                 = "items";
static const char m_is_incomplete[]         = "isIncomplete";

} // namespace lsp
} // namespace wasp

#endif // WASPLSP_LSP_H
