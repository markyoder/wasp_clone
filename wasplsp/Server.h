#ifndef WASPLSP_SERVER_H
#define WASPLSP_SERVER_H

#include "wasplsp/LSP.h"

namespace wasp {
namespace lsp  {

template <class T>
class WASP_PUBLIC Server
{
  public:

    Server(){}

    ~Server(){}

    bool handleInitializeRequest(
                    const DataObject   & initializeRequest  ,
                          DataObject   & initializeResponse ,
                          std::ostream & errors             )
    {
        return Impl.handleInitializeRequest( initializeRequest  ,
                                             initializeResponse ,
                                             errors             );
    }

    bool handleInitializedNotification(
                    const DataObject   & initializedNotification ,
                          std::ostream & errors                  )
    {
        return Impl.handleInitializedNotification( initializedNotification ,
                                                   errors                  );
    }

    bool handleShutdownRequest(
                    const DataObject   & shutdownRequest  ,
                          DataObject   & shutdownResponse ,
                          std::ostream & errors           )
    {
        return Impl.handleShutdownRequest( shutdownRequest  ,
                                           shutdownResponse ,
                                           errors           );
    }

    bool handleExitNotification(
                    const DataObject   & exitNotification ,
                          std::ostream & errors           )
    {
        return Impl.handleExitNotification( exitNotification  ,
                                            errors            );
    }

    bool handleDidOpenNotification(
                    const DataObject   & didOpenNotification            ,
                          DataObject   & publishDiagnosticsNotification ,
                          std::ostream & errors                         )
    {
        return Impl.handleDidOpenNotification( didOpenNotification            ,
                                               publishDiagnosticsNotification ,
                                               errors                         );
    }

    bool handleDidChangeNotification(
                    const DataObject   & didChangeNotification          ,
                          DataObject   & publishDiagnosticsNotification ,
                          std::ostream & errors                         )
    {
        return Impl.handleDidChangeNotification( didChangeNotification          ,
                                                 publishDiagnosticsNotification ,
                                                 errors                         );
    }

    bool handleCompletionRequest(
                    const DataObject   & completionRequest  ,
                          DataObject   & completionResponse ,
                          std::ostream & errors             )
    {
        return Impl.handleCompletionRequest( completionRequest  ,
                                             completionResponse ,
                                             errors             );
    }

    bool handleDefinitionRequest(
                    const DataObject   & definitionRequest  ,
                          DataObject   & definitionResponse ,
                          std::ostream & errors             )
    {
        return Impl.handleDefinitionRequest( definitionRequest  ,
                                             definitionResponse ,
                                             errors             );
    }

    bool handleReferencesRequest(
                    const DataObject   & referencesRequest  ,
                          DataObject   & referencesResponse ,
                          std::ostream & errors             )
    {
        return Impl.handleReferencesRequest( referencesRequest  ,
                                             referencesResponse ,
                                             errors             );
    }

    bool handleRangeFormattingRequest(
                    const DataObject   & rangeFormattingRequest  ,
                          DataObject   & rangeFormattingResponse ,
                          std::ostream & errors                  )
    {
        return Impl.handleRangeFormattingRequest( rangeFormattingRequest  ,
                                                  rangeFormattingResponse ,
                                                  errors             );
    }

    bool parseDocumentForDiagnostics(
                          DataArray    & diagnosticsList ,
                          std::ostream & errors          )
    {
        return Impl.parseDocumentForDiagnostics( diagnosticsList ,
                                                 errors          );
    }

    bool updateDocumentTextChanges(
                    const std::string  & replacement_text ,
                          int            start_line       ,
                          int            start_character  ,
                          int            end_line         ,
                          int            end_character    ,
                          int            range_length     ,
                          std::ostream & errors           )
    {
        return Impl.updateDocumentTextChanges( replacement_text ,
                                               start_line       ,
                                               start_character  ,
                                               end_line         ,
                                               end_character    ,
                                               range_length     ,
                                               errors           );
    }

    bool gatherDocumentCompletionItems(
                          DataArray    & completionItems ,
                          bool         & is_incomplete   ,
                          int            line            ,
                          int            character       ,
                          std::ostream & errors          )
    {
        return Impl.gatherDocumentCompletionItems( completionItems ,
                                                   is_incomplete   ,
                                                   line            ,
                                                   character       ,
                                                   errors          );
    }

    bool gatherDocumentDefinitionLocations(
                          DataArray    & definitionLocations ,
                          int            line                ,
                          int            character           ,
                          std::ostream & errors              )
    {
        return Impl.gatherDocumentDefinitionLocations( definitionLocations ,
                                                       line                ,
                                                       character           ,
                                                       errors              );
    }

  private:

      T Impl;
};

} // namespace lsp
} // namespace wasp

#endif // WASPLSP_SERVER_H
