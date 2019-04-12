#ifndef WASPLSP_SERVER_H
#define WASPLSP_SERVER_H

#include "wasplsp/LSP.h"
#include "waspcore/Object.h"
#include "waspcore/decl.h"
#include <iostream>

namespace wasp {
namespace lsp  {

template <class T>
class WASP_PUBLIC Server
{
  public:

    Server(){}

    ~Server(){}

    bool run( std::istream & input_stream  ,
              std::ostream & output_stream ,
              std::ostream & error_stream  )
    {
        return Impl.run( input_stream  ,
                         output_stream ,
                         error_stream  );
    }

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

  private:

      T Impl;
};

} // namespace lsp
} // namespace wasp

#endif // WASPLSP_SERVER_H
