#ifndef WASPLSP_WASP_SERVER_H
#define WASPLSP_WASP_SERVER_H

#include <string>
#include "wasplsp/LSP.h"
#include "wasplsp/ServerImpl.h"
#include "waspcore/Object.h"
#include "waspcore/Interpreter.h"
#include "waspcore/decl.h"

namespace wasp {
namespace lsp  {

template <class INPUT , class INPUTNV, class SCHEMA , class SCHEMANV, class VALIDATOR>
class WASP_PUBLIC WaspServer : public ServerImpl
{
  public:

    bool setValidator( std::shared_ptr<VALIDATOR> validator ,
                       std::shared_ptr<SCHEMA>    schema    );

  private:

    bool parseDocumentForDiagnostics(
                          DataArray  & diagnosticsList );

    bool updateDocumentTextChanges(
                    const std::string & replacement_text ,
                          int           start_line       ,
                          int           start_character  ,
                          int           end_line         ,
                          int           end_character    ,
                          int           range_length     );

    bool gatherDocumentCompletionItems(
                          DataArray & completionItems  ,
                          bool      & is_incomplete    ,
                          int         line             ,
                          int         character        );

    bool gatherDocumentDefinitionLocations(
                          DataArray & definitionLocations ,
                          int         line                ,
                          int         character           );

    bool gatherDocumentReferencesLocations(
                          DataArray & referencesLocations ,
                          int         line                ,
                          int         character           ,
                          bool        include_declaration );

    bool gatherDocumentFormattingTextEdits(
                          DataArray & formattingTextEdits ,
                          int         start_line          ,
                          int         start_character     ,
                          int         end_line            ,
                          int         end_character       ,
                          int         tab_size            ,
                          bool        insert_spaces       );

    bool gatherDocumentSymbols(
                          DataArray & documentSymbols );

    std::shared_ptr<INPUT>     parser;

    std::shared_ptr<VALIDATOR> validator;

    std::shared_ptr<SCHEMA>    schema;
};

} // namespace lsp
} // namespace wasp

#include "wasplsp/WaspServer.i.h"

#endif // WASPLSP_WASP_SERVER_H
