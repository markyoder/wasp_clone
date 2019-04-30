#include "SymbolsInterrogator.h"

namespace wasp {
namespace lsp  {

size_t SymbolsInterrogator::getChildSize() const
{
    DataArray * children = getSymbolChildrenArray( *this->symbols_lineage.back() );

    wasp_check( children != nullptr );

    return children->size();
}

std::string SymbolsInterrogator::getPath() const
{
    std::string path;

    for ( size_t i = 1 ; i < this->symbols_lineage.size() ; i++ )
    {
        path += "/" + (*this->symbols_lineage[i])[m_name].to_string();
    }

    return path;
}

bool SymbolsInterrogator::moveToChildAt( size_t index )
{
    bool pass = true;

    if ( index >= this->getChildSize() )
    {
        this->errors << m_error_prefix << "Index out of bounds" << std::endl;

        return false;
    }

    DataArray * children = getSymbolChildrenArray( *this->symbols_lineage.back() );

    DataObject * object = children->at(index).to_object();

    this->symbols_lineage.push_back( object );

    return pass;
}

bool SymbolsInterrogator::moveToParent()
{
    bool pass = true;

    if ( this->symbols_lineage.size() == 1 )
    {
        this->errors << m_error_prefix << "Already at root" << std::endl;

        return false;
    }

    this->symbols_lineage.pop_back();

    return pass;
}

bool SymbolsInterrogator::dissectCurrentSymbol( std::string  & name  ,
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
                           int          & selection_end_character   )
{
    bool pass = true;

    pass = dissectDocumentSymbolObject( *this->symbols_lineage.back() ,
                                         this->errors                 ,
                                         name                         ,
                                         detail                       ,
                                         kind                         ,
                                         deprecated                   ,
                                         start_line                   ,
                                         start_character              ,
                                         end_line                     ,
                                         end_character                ,
                                         selection_start_line         ,
                                         selection_start_character    ,
                                         selection_end_line           ,
                                         selection_end_character      );

    return pass;
}

} // namespace lsp
} // namespace wasp
