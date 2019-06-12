#ifndef WASPLSP_TEST_SERVER_H
#define WASPLSP_TEST_SERVER_H

#include <string>
#include <memory>
#include "wasplsp/LSP.h"
#include "wasplsp/ServerImpl.h"
#include "wasplsp/Connection.h"
#include "wasplsp/ThreadConnection.h"
#include "waspcore/Object.h"
#include "waspcore/decl.h"

namespace wasp {
namespace lsp  {

class WASP_PUBLIC TestServer : public ServerImpl
{
  public:

    TestServer()
    {
        connection = std::make_shared<ThreadConnection>(this);
    }

    std::shared_ptr<Connection> getConnection()
    {
        return connection;
    }

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

    bool connectionRead( DataObject & object )
    {
       return this->connection->read( object , this->errors );
    }

    bool connectionWrite( DataObject & object )
    {
       return this->connection->write( object , this->errors );
    }

    std::shared_ptr<ThreadConnection> connection;
};

} // namespace lsp
} // namespace wasp

#endif // WASPLSP_TEST_SERVER_H
