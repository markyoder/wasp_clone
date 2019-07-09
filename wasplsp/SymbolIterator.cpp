#include "SymbolIterator.h"

namespace wasp {
namespace lsp  {

size_t SymbolIterator::getChildSize() const
{
    // get array of children at the currently set lineage level and return size

    DataArray * children = getSymbolChildrenArray( *this->symbols_lineage.back() );

    if ( children == nullptr ) return 0;

    return children->size();
}

std::string SymbolIterator::getPath() const
{
    std::string path;

    // walk through the current symbol lineage walking from root to leaf

    for ( size_t i = 1 ; i < this->symbols_lineage.size() ; i++ )
    {
        wasp_check( (*this->symbols_lineage[i]).contains(m_name) &&
                    (*this->symbols_lineage[i])[m_name].is_string() );

        // append '/' + name to the path - building it as we go

        path += "/" + (*this->symbols_lineage[i])[m_name].to_string();

        // if this is the leaf node then add the line and column to the end

        if ( i+1 == this->symbols_lineage.size() )
        {
            DataObject * leaf = this->symbols_lineage[i];

            wasp_check( leaf->contains(m_range) && (*leaf)[m_range].is_object() );

            const DataObject& range = *(*leaf)[m_range].to_object();

            wasp_check( range.contains(m_start) && range[m_start].is_object() );

            const DataObject& start = *(range[m_start].to_object());

            wasp_check( start.contains(m_line) && start[m_line].is_int() );

            int line = start[m_line].to_int();

            wasp_check( start.contains(m_character) && start[m_character].is_int() );

            int character = start[m_character].to_int();

            path += std::string(" (")         +
                    std::to_string(line)      +
                    std::string(":")          +
                    std::to_string(character) +
                    std::string(")");
        }
    }

    // return the built path for the current symbol from root to leaf

    return path;
}

bool SymbolIterator::moveToChildAt( size_t index )
{
    bool pass = true;

    // check that the index is not more than the size of the current children

    if ( index >= this->getChildSize() )
    {
        this->errors << m_error_prefix << "Index out of bounds" << std::endl;

        return false;
    }

    // get the children of the current document symbol

    DataArray * children = getSymbolChildrenArray( *this->symbols_lineage.back() );

    wasp_check( children != nullptr );

    // convert the child at the given index to a DataObject

    DataObject * object = children->at(index).to_object();

    wasp_check( object != nullptr );

    // push a pointer to the child object at the given index onto the lineage

    this->symbols_lineage.push_back( object );

    return pass;
}

bool SymbolIterator::moveToParent()
{
    bool pass = true;

    // check that we are not currently at the root object in the lineage

    if ( this->symbols_lineage.size() == 1 )
    {
        this->errors << m_error_prefix << "Already at root" << std::endl;

        return false;
    }

    // pop the end of the symbol lineage making the new end the parent object

    this->symbols_lineage.pop_back();

    return pass;
}

bool SymbolIterator::dissectCurrentSymbol( std::string  & name  ,
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

    // dissect the document symbol that is currently at the end of the lineage

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

bool positionChildSort( const Value & lv , const Value & rv )
{
    // convert the left Value to a DataObject

    DataObject * lo = lv.to_object();

    std::stringstream lo_errors;
    std::string       lo_name;
    std::string       lo_detail;
    int               lo_kind;
    bool              lo_deprecated;
    int               lo_start_line;
    int               lo_start_character;
    int               lo_end_line;
    int               lo_end_character;
    int               lo_selection_start_line;
    int               lo_selection_start_character;
    int               lo_selection_end_line;
    int               lo_selection_end_character;

    // dissect the left DataObject to get the start_line and start_character

    dissectDocumentSymbolObject( *lo                           ,
                                  lo_errors                    ,
                                  lo_name                      ,
                                  lo_detail                    ,
                                  lo_kind                      ,
                                  lo_deprecated                ,
                                  lo_start_line                ,
                                  lo_start_character           ,
                                  lo_end_line                  ,
                                  lo_end_character             ,
                                  lo_selection_start_line      ,
                                  lo_selection_start_character ,
                                  lo_selection_end_line        ,
                                  lo_selection_end_character   );

    // convert the right Value to a DataObject

    DataObject * ro = rv.to_object();

    std::stringstream ro_errors;
    std::string       ro_name;
    std::string       ro_detail;
    int               ro_kind;
    bool              ro_deprecated;
    int               ro_start_line;
    int               ro_start_character;
    int               ro_end_line;
    int               ro_end_character;
    int               ro_selection_start_line;
    int               ro_selection_start_character;
    int               ro_selection_end_line;
    int               ro_selection_end_character;

    // dissect the right DataObject to get the start_line and start_character

    dissectDocumentSymbolObject( *ro                           ,
                                  ro_errors                    ,
                                  ro_name                      ,
                                  ro_detail                    ,
                                  ro_kind                      ,
                                  ro_deprecated                ,
                                  ro_start_line                ,
                                  ro_start_character           ,
                                  ro_end_line                  ,
                                  ro_end_character             ,
                                  ro_selection_start_line      ,
                                  ro_selection_start_character ,
                                  ro_selection_end_line        ,
                                  ro_selection_end_character   );

    // return true if left object comes before right object in the document

    return ( lo_start_line      <  ro_start_line      ||
           ( lo_start_line      == ro_start_line      &&
             lo_start_character <  ro_start_character ));
}

bool SymbolIterator::recursiveSortByPosition()
{
    bool pass = true;

    // get the size of the children of the current symbol lineage object

    size_t child_size = this->getChildSize();

    // if there is more than one child - then sort them by line and column

    if ( child_size > 1 )
    {
        DataArray * children = getSymbolChildrenArray( *this->symbols_lineage.back() );

        // if there is not a range object but there is a location object in the
        // first child - bail out now because these are not hierarchical symbols

        if ( !children->at(0).is_object()                           ||
           ( !children->at(0).to_object()->contains(m_range)        &&
              children->at(0).to_object()->contains(m_location)     &&
           ( *children->at(0).to_object() )[m_location].is_object() ) )
        {
            this->errors << m_error_prefix << "Not sorting non-hierarchical symbols"
                          << std::endl;
            return false;
        }

        std::sort( children->begin() , children->end() , positionChildSort );
    }

    // recursively call this method to sort all children levels

    for( size_t i = 0 ; i < child_size ; i++ )
    {
        pass &= this->moveToChildAt( i );

        pass &= this->recursiveSortByPosition();

        pass &= this->moveToParent();
    }

    return pass;
}

} // namespace lsp
} // namespace wasp
