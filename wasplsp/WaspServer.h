#ifndef WASPLSP_WASP_SERVER_H
#define WASPLSP_WASP_SERVER_H

#include <string>
#include "wasplsp/LSP.h"
#include "wasplsp/ServerImpl.h"
#include "wasplsp/ThreadConnection.h"
#include "waspcore/Object.h"
#include "waspcore/Interpreter.h"
#include "waspcore/decl.h"

namespace wasp {
namespace lsp  {

template < class INPUT                                     ,
           class INPUTNV                                   ,
           class SCHEMA                                    ,
           class SCHEMANV                                  ,
           class VALIDATOR                                 ,
           class CONNECTION = ThreadConnection<ServerImpl> >

class WASP_PUBLIC WaspServer : public ServerImpl
{
  public:

    WaspServer()
    {
        connection = std::make_shared<CONNECTION>(this);
    }

    std::shared_ptr<CONNECTION> getConnection()
    {
        return connection;
    }

    bool setValidator( std::shared_ptr<VALIDATOR> & validator ,
                       std::shared_ptr<SCHEMA>    & schema    );

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

    bool traverseParseTreeAndFillSymbols(
                          INPUTNV      node   ,
                          DataObject & parent );

    bool connectionRead( DataObject & object )
    {
       return this->connection->read( object , this->errors );
    }

    bool connectionWrite( DataObject & object )
    {
       return this->connection->write( object , this->errors );
    }

    std::shared_ptr<INPUT>      parser;

    std::shared_ptr<VALIDATOR>  validator;

    std::shared_ptr<SCHEMA>     schema;

    std::shared_ptr<CONNECTION> connection;
};

} // namespace lsp
} // namespace wasp

#include "wasplsp/WaspServer.i.h"

#endif // WASPLSP_WASP_SERVER_H
