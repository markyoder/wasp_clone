#ifndef WASPLSP_SYMBOL_ITERATOR_H
#define WASPLSP_SYMBOL_ITERATOR_H

#include <vector>
#include <string>
#include <sstream>
#include <memory>
#include "waspcore/Object.h"
#include "waspcore/decl.h"
#include "wasplsp/LSP.h"

namespace wasp {
namespace lsp  {

class WASP_PUBLIC SymbolIterator
{
  public:

    SymbolIterator( DataObject::SP response )
    {
        this->symbols_lineage.push_back( &*response );

        m_response = response;

        this->recursiveSortByPosition();
    }

    ~SymbolIterator(){}

    typedef std::shared_ptr<SymbolIterator> SP;

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

    std::string getErrors() const { return this->errors.str(); }

  private:

      DataObject::SP m_response;

      std::vector<DataObject *> symbols_lineage;

      std::stringstream errors;

      bool recursiveSortByPosition();
};

} // namespace lsp
} // namespace wasp

#endif // WASPLSP_SYMBOL_ITERATOR_H
