#ifndef WASPLSP_SYMBOLS_INTERROGATOR_H
#define WASPLSP_SYMBOLS_INTERROGATOR_H

#include <vector>
#include <string>
#include <sstream>
#include "waspcore/Object.h"
#include "waspcore/decl.h"
#include "wasplsp/LSP.h"

namespace wasp {
namespace lsp  {

class WASP_PUBLIC SymbolsInterrogator
{
  public:

    SymbolsInterrogator( DataObject::SP response )
    {
        this->symbols_lineage.push_back( &*response );
    }

    ~SymbolsInterrogator(){}

    typedef std::shared_ptr<SymbolsInterrogator> SP;

    size_t getChildSize() const;

    std::string getPath() const;

    bool moveToChildAt( size_t index );

    bool moveToParent();

    bool dissectCurrentSymbol( std::string  & name                      ,
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
                               int          & selection_end_character   );

  private:

      std::vector<DataObject *> symbols_lineage;

      std::stringstream errors;
};

} // namespace lsp
} // namespace wasp

#endif // WASPLSP_SYMBOLS_INTERROGATOR_H
