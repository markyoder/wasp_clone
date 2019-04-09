#ifndef WASPLSP_LSP_H
#define WASPLSP_LSP_H

#include <string>
#include <vector>
#include <iostream>
#include "waspcore/Object.h"
#include "waspcore/decl.h"

namespace wasp {
namespace lsp  {

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

static const char _id[]                    = "id";
static const char _method_initialize[]     = "initialize";
static const char _method_initialized[]    = "initialized";
static const char _method_shutdown[]       = "shutdown";
static const char _method_exit[]           = "exit";
static const char _method_didopen[]        = "textDocument/didOpen";
static const char _method_didchange[]      = "textDocument/didChange";
static const char _method_completion[]     = "textDocument/completion";
static const char _method_definition[]     = "textDocument/definition";
static const char _method_references[]     = "textDocument/references";
static const char _method_rangeformat[]    = "textDocument/rangeFormatting";
static const char _method_pubdiagnostics[] = "textDocument/publishDiagnostics";
static const char _method[]                = "method";
static const char _params[]                = "params";
static const char _result[]                = "result";
static const char _process_id[]            = "processId";
static const char _root_uri[]              = "rootUri";
static const char _capabilities[]          = "capabilities";
static const char _text_document[]         = "textDocument";
static const char _uri[]                   = "uri";
static const char _language_id[]           = "languageId";
static const char _version[]               = "version";
static const char _text[]                  = "text";
static const char _content_changes[]       = "contentChanges";
static const char _range[]                 = "range";
static const char _start[]                 = "start";
static const char _end[]                   = "end";
static const char _line[]                  = "line";
static const char _character[]             = "character";
static const char _range_length[]          = "range_length";
static const char _position[]              = "position";
static const char _context[]               = "context";
static const char _include_declaration[]   = "includeDeclaration";
static const char _options[]               = "options";
static const char _tab_size[]              = "tabSize";
static const char _insert_spaces[]         = "insertSpaces";
static const char _severity[]              = "severity";
static const char _code[]                  = "code";
static const char _source[]                = "source";
static const char _message[]               = "message";
static const char _diagnostics[]           = "diagnostics";
static const char _label[]                 = "label";
static const char _text_edit[]             = "textEdit";
static const char _new_text[]              = "newText";
static const char _kind[]                  = "kind";
static const char _detail[]                = "detail";
static const char _documentation[]         = "documentation";
static const char _deprecated[]            = "deprecated";
static const char _preselect[]             = "preselect";
static const char _items[]                 = "items";
static const char _is_incomplete[]         = "isIncomplete";

} // namespace lsp
} // namespace wasp

#endif // WASPLSP_LSP_H
