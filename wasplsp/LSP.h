#include <string>
#include <vector>
#include <iostream>
#include "waspcore/Object.h"

namespace wasp {
namespace lsp  {

bool checkRange( std::ostream & errors          ,
                 int            start_line      ,
                 int            start_character ,
                 int            end_line        ,
                 int            end_character   );

bool buildInitializeRequest( DataObject        & object              ,
                             std::ostream      & errors              ,
                             int                 process_id          ,
                             const std::string & root_uri            ,
                             const DataObject  & client_capabilities );

bool buildInitializedNotification( DataObject   & object ,
                                   std::ostream & errors );

bool buildShutdownRequest( DataObject   & object ,
                           std::ostream & errors );

bool buildExitNotification( DataObject   & object ,
                            std::ostream & errors );

bool buildDidOpenNotification( DataObject        & object      ,
                               std::ostream      & errors      ,
                               const std::string & uri         ,
                               const std::string & language_id ,
                               double              version     ,
                               const std::string & text        );

bool buildDidChangeNotification( DataObject        & object          ,
                                 std::ostream      & errors          ,
                                 const std::string & uri             ,
                                 double              version         ,
                                 int                 start_line      ,
                                 int                 start_character ,
                                 int                 end_line        ,
                                 int                 end_character   ,
                                 int                 range_length    ,
                                 const std::string & text            );

bool buildCompletionRequest( DataObject        & object    ,
                             std::ostream      & errors    ,
                             const std::string & uri       ,
                             int                 line      ,
                             int                 character );

bool buildDefinitionRequest( DataObject        & object    ,
                             std::ostream      & errors    ,
                             const std::string & uri       ,
                             int                 line      ,
                             int                 character );

bool buildReferencesRequest( DataObject        & object              ,
                             std::ostream      & errors              ,
                             const std::string & uri                 ,
                             int                 line                ,
                             int                 character           ,
                             bool                include_declaration );

bool buildRangeFormattingRequest( DataObject        & object          ,
                                  std::ostream      & errors          ,
                                  const std::string & uri             ,
                                  int                 start_line      ,
                                  int                 start_character ,
                                  int                 end_line        ,
                                  int                 end_character   ,
                                  int                 tab_size        ,
                                  bool                insert_spaces   );

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

bool buildPublishDiagnosticsNotification( DataObject        & object      ,
                                          std::ostream      & errors      ,
                                          const std::string & uri         ,
                                          const DataArray   & diagnostics );

bool buildInitializeResponse( DataObject        & object              ,
                              std::ostream      & errors              ,
                              const DataObject  & server_capabilities );

bool buildShutdownResponse( DataObject        & object ,
                            std::ostream      & errors );

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

bool buildCompletionResponse( DataObject        & object           ,
                              std::ostream      & errors           ,
                              bool                is_incomplete    ,
                              const DataArray   & completion_items );

bool buildLocationObject( DataObject        & object          ,
                          std::ostream      & errors          ,
                          const std::string & uri             ,
                          int                 start_line      ,
                          int                 start_character ,
                          int                 end_line        ,
                          int                 end_character   );

bool buildLocationsResponse( DataObject        & object           ,
                             std::ostream      & errors           ,
                             const DataArray   & location_objects );

bool buildTextEditObject( DataObject        & object          ,
                          std::ostream      & errors          ,
                          int                 start_line      ,
                          int                 start_character ,
                          int                 end_line        ,
                          int                 end_character   ,
                          const std::string & new_text        );

bool buildRangeFormattingResponse( DataObject        & object           ,
                                   std::ostream      & errors           ,
                                   const DataArray   & textedit_objects );

static const char _method[]              = "method";
static const char _params[]              = "params";
static const char _result[]              = "result";
static const char _process_id[]          = "processId";
static const char _root_uri[]            = "rootUri";
static const char _capabilities[]        = "capabilities";
static const char _text_document[]       = "textDocument";
static const char _uri[]                 = "uri";
static const char _language_id[]         = "languageId";
static const char _version[]             = "version";
static const char _text[]                = "text";
static const char _content_changes[]     = "contentChanges";
static const char _range[]               = "range";
static const char _start[]               = "start";
static const char _end[]                 = "end";
static const char _line[]                = "line";
static const char _character[]           = "character";
static const char _range_length[]        = "range_length";
static const char _position[]            = "position";
static const char _context[]             = "context";
static const char _include_declaration[] = "includeDeclaration";
static const char _options[]             = "options";
static const char _tab_size[]            = "tabSize";
static const char _insert_spaces[]       = "insertSpaces";
static const char _severity[]            = "severity";
static const char _code[]                = "code";
static const char _source[]              = "source";
static const char _message[]             = "message";
static const char _diagnostics[]         = "diagnostics";
static const char _label[]               = "label";
static const char _text_edit[]           = "textEdit";
static const char _new_text[]            = "newText";
static const char _kind[]                = "kind";
static const char _detail[]              = "detail";
static const char _documentation[]       = "documentation";
static const char _deprecated[]          = "deprecated";
static const char _preselect[]           = "preselect";
static const char _items[]               = "items";
static const char _is_incomplete[]       = "isIncomplete";

}
}
