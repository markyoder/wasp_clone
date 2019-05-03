#include "waspson/SONNodeView.h"

namespace wasp {
namespace lsp  {

template < class INPUT      ,
           class INPUTNV    ,
           class SCHEMA     ,
           class SCHEMANV   ,
           class VALIDATOR  ,
           class CONNECTION >
bool WaspServer<INPUT,INPUTNV,SCHEMA,SCHEMANV,VALIDATOR,CONNECTION>::
    setValidator(
                std::shared_ptr<VALIDATOR> & validator ,
                std::shared_ptr<SCHEMA>    & schema    )
{
    bool pass = true;

    this->validator = validator;

    this->schema = schema;

    return pass;
}

template < class INPUT      ,
           class INPUTNV    ,
           class SCHEMA     ,
           class SCHEMANV   ,
           class VALIDATOR  ,
           class CONNECTION >
bool WaspServer<INPUT,INPUTNV,SCHEMA,SCHEMANV,VALIDATOR,CONNECTION>::
    parseDocumentForDiagnostics(
                      DataArray & diagnosticsList )
{
    if (!this->is_initialized)
    {
        this->errors << m_error_prefix << "Server needs to be initialized" << std::endl;
        return false;
    }

    if (!this->is_document_open)
    {
        this->errors << m_error_prefix << "Server has no open document" << std::endl;
        return false;
    }

    bool pass = true;

    std::stringstream parse_errors;

    this->parser = std::make_shared<INPUT>(parse_errors);

    if ( !this->parser->parseString( this->document_text , "" ) )
    {
        while( parse_errors.good() )
        {
            std::string error;

            std::getline( parse_errors, error );

            if ( error.empty() ) continue;

            size_t dot   = error.find('.' , 1);

            size_t colon = error.find(':' , 1);

            std::string line_str = error.substr( 1, dot - 1 );

            int line;

            std::stringstream( line_str ) >> line;

            std::string column_str = error.substr( dot + 1, colon - dot - 1 );

            int column;

            std::stringstream( column_str ) >> column;

            std::string message  = error.substr( colon + 1 );

            message = trim( message, " " );

            wasp_check( line > 0 );

            wasp_check( column > 0 );

            wasp_check( !message.empty() );

            DataObject diagnostic;

            pass &= buildDiagnosticObject( diagnostic   ,
                                           this->errors ,
                                           line         ,
                                           column       ,
                                           line         ,
                                           column       ,
                                           1            ,
                                           "parse"      ,
                                           "parser"     ,
                                           message      );

            diagnosticsList.push_back(diagnostic);
        }
    }

    INPUTNV  schema_root = this->schema->root();

    SCHEMANV input_root  = this->parser->root();

    std::vector<std::string> validation_errors;

    if ( !this->validator->validate(schema_root, input_root, validation_errors) )
    {
        for (auto i : validation_errors)
        {
            std::size_t foundline   = i.find( "line:" );

            std::size_t foundcolumn = i.find( " column:" );

            std::size_t founddash   = i.find( " - " );

            std::string line_str = i.substr( foundline + 5, foundcolumn - (foundline + 5) );

            int line;

            std::stringstream( line_str ) >> line;

            std::string column_str = i.substr( foundcolumn + 8, founddash - (foundcolumn + 8) );

            int column;

            std::stringstream( column_str ) >> column;

            std::string message = i.substr( founddash + 3 );

            wasp_check( line > 0 );

            wasp_check( column > 0 );

            wasp_check( !message.empty() );

            DataObject diagnostic;

            pass &= buildDiagnosticObject( diagnostic   ,
                                           this->errors ,
                                           line         ,
                                           column       ,
                                           line         ,
                                           column       ,
                                           1            ,
                                           "validate"   ,
                                           "validator"  ,
                                           message      );

            diagnosticsList.push_back(diagnostic);
        }

    }

    return pass;
}

template < class INPUT      ,
           class INPUTNV    ,
           class SCHEMA     ,
           class SCHEMANV   ,
           class VALIDATOR  ,
           class CONNECTION >
bool WaspServer<INPUT,INPUTNV,SCHEMA,SCHEMANV,VALIDATOR,CONNECTION>::
    updateDocumentTextChanges(
                const std::string & replacement_text ,
                      int           start_line       ,
                      int           start_character  ,
                      int           end_line         ,
                      int           end_character    ,
                      int           range_length     )
{
    if (!this->is_initialized)
    {
        this->errors << m_error_prefix << "Server needs to be initialized" << std::endl;
        return false;
    }

    if (!this->is_document_open)
    {
        this->errors << m_error_prefix << "Server has no open document" << std::endl;
        return false;
    }

    bool pass = true;

    // TODO - replace text using line and column

    this->document_text = replacement_text;

    return pass;
}

template < class INPUT      ,
           class INPUTNV    ,
           class SCHEMA     ,
           class SCHEMANV   ,
           class VALIDATOR  ,
           class CONNECTION >
bool WaspServer<INPUT,INPUTNV,SCHEMA,SCHEMANV,VALIDATOR,CONNECTION>::
    gatherDocumentCompletionItems(
                      DataArray & completionItems  ,
                      bool      & is_incomplete    ,
                      int         line             ,
                      int         character        )
{
    if (!this->is_initialized)
    {
        this->errors << m_error_prefix << "Server needs to be initialized" << std::endl;
        return false;
    }

    if (!this->is_document_open)
    {
        this->errors << m_error_prefix << "Server has no open document" << std::endl;
        return false;
    }

    bool pass = true;

    // TODO

    is_incomplete = false;

    return pass;
}

template < class INPUT      ,
           class INPUTNV    ,
           class SCHEMA     ,
           class SCHEMANV   ,
           class VALIDATOR  ,
           class CONNECTION >
bool WaspServer<INPUT,INPUTNV,SCHEMA,SCHEMANV,VALIDATOR,CONNECTION>::
    gatherDocumentDefinitionLocations(
                      DataArray & definitionLocations ,
                      int         line                ,
                      int         character           )
{
    if (!this->is_initialized)
    {
        this->errors << m_error_prefix << "Server needs to be initialized" << std::endl;
        return false;
    }

    if (!this->is_document_open)
    {
        this->errors << m_error_prefix << "Server has no open document" << std::endl;
        return false;
    }

    bool pass = true;

    // TODO

    return pass;
}

template < class INPUT      ,
           class INPUTNV    ,
           class SCHEMA     ,
           class SCHEMANV   ,
           class VALIDATOR  ,
           class CONNECTION >
bool WaspServer<INPUT,INPUTNV,SCHEMA,SCHEMANV,VALIDATOR,CONNECTION>::
    gatherDocumentReferencesLocations(
                      DataArray & referencesLocations ,
                      int         line                ,
                      int         character           ,
                      bool        include_declaration )
{
    if (!this->is_initialized)
    {
        this->errors << m_error_prefix << "Server needs to be initialized" << std::endl;
        return false;
    }

    if (!this->is_document_open)
    {
        this->errors << m_error_prefix << "Server has no open document" << std::endl;
        return false;
    }

    bool pass = true;

    // TODO

    return pass;
}

template < class INPUT      ,
           class INPUTNV    ,
           class SCHEMA     ,
           class SCHEMANV   ,
           class VALIDATOR  ,
           class CONNECTION >
bool WaspServer<INPUT,INPUTNV,SCHEMA,SCHEMANV,VALIDATOR,CONNECTION>::
    gatherDocumentFormattingTextEdits(
                      DataArray & formattingTextEdits ,
                      int         start_line          ,
                      int         start_character     ,
                      int         end_line            ,
                      int         end_character       ,
                      int         tab_size            ,
                      bool        insert_spaces       )
{
    if (!this->is_initialized)
    {
        this->errors << m_error_prefix << "Server needs to be initialized" << std::endl;
        return false;
    }

    if (!this->is_document_open)
    {
        this->errors << m_error_prefix << "Server has no open document" << std::endl;
        return false;
    }

    bool pass = true;

    // TODO

    return pass;
}

template < class INPUT      ,
           class INPUTNV    ,
           class SCHEMA     ,
           class SCHEMANV   ,
           class VALIDATOR  ,
           class CONNECTION >
bool WaspServer<INPUT,INPUTNV,SCHEMA,SCHEMANV,VALIDATOR,CONNECTION>::
    gatherDocumentSymbols(
                      DataArray & documentSymbols )
{
    if (!this->is_initialized)
    {
        this->errors << m_error_prefix << "Server needs to be initialized" << std::endl;
        return false;
    }

    if (!this->is_document_open)
    {
        this->errors << m_error_prefix << "Server has no open document" << std::endl;
        return false;
    }

    bool pass = true;

    const auto & children = this->parser->root().non_decorative_children();

    for( size_t i = 0; i < children.size(); i++ )
    {
        std::string name   = children[i].name();
        int         line   = children[i].line();
        int         column = children[i].column();

        documentSymbols.push_back( DataObject() );

        DataObject * child = documentSymbols.back().to_object();

        pass &= buildDocumentSymbolObject( *child        ,
                                            this->errors ,
                                            name         ,
                                            name         ,
                                            1            ,
                                            false        ,
                                            line         ,
                                            column       ,
                                            line         ,
                                            column       ,
                                            line         ,
                                            column       ,
                                            line         ,
                                            column       );

      this->traverseParseTreeAndFillSymbols( children[i] , *child );
    }

    return pass;
}

template < class INPUT      ,
           class INPUTNV    ,
           class SCHEMA     ,
           class SCHEMANV   ,
           class VALIDATOR  ,
           class CONNECTION >
bool WaspServer<INPUT,INPUTNV,SCHEMA,SCHEMANV,VALIDATOR,CONNECTION>::
    traverseParseTreeAndFillSymbols(
                      INPUTNV      node   ,
                      DataObject & parent )
{
    bool pass = true;

    const auto & children = node.non_decorative_children();

    for( size_t i = 0; i < children.size(); i++ )
    {
        std::string name   = children[i].name();
        int         line   = children[i].line();
        int         column = children[i].column();

        DataObject & child = addDocumentSymbolChild( parent );

        pass &= buildDocumentSymbolObject( child        ,
                                           this->errors ,
                                           name         ,
                                           name         ,
                                           1            ,
                                           false        ,
                                           line         ,
                                           column       ,
                                           line         ,
                                           column       ,
                                           line         ,
                                           column       ,
                                           line         ,
                                           column       );

      this->traverseParseTreeAndFillSymbols( children[i] , child );
    }

    return pass;
}

} // namespace lsp
} // namespace wasp
