#include "TestServer.h"

namespace wasp {
namespace lsp  {

bool TestServer::parseDocumentForDiagnostics(
                      DataArray & diagnosticsList )
{
    if (!this->is_initialized)
    {
        this->errors << m_error << "Server needs to be initialized" << std::endl;
        return false;
    }

    if (!this->is_document_open)
    {
        this->errors << m_error << "Server has no open document" << std::endl;
        return false;
    }

    bool pass = true;

    DataObject diagnostic;

    if (this->document_text == "test\ntext\n1\nstring\n")
    {
        pass &= buildDiagnosticObject( diagnostic         ,
                                       this->errors       ,
                                       20                 ,
                                       16                 ,
                                       20                 ,
                                       27                 ,
                                       1                  ,
                                       "test.code.11"     ,
                                       "test_source_11"   ,
                                       "Test message 11." );

        diagnosticsList.push_back(diagnostic);

        pass &= buildDiagnosticObject( diagnostic         ,
                                       this->errors       ,
                                       28                 ,
                                       56                 ,
                                       34                 ,
                                       27                 ,
                                       2                  ,
                                       "test.code.22"     ,
                                       "test_source_22"   ,
                                       "Test message 22." );

        diagnosticsList.push_back(diagnostic);

        pass &= buildDiagnosticObject( diagnostic         ,
                                       this->errors       ,
                                       47                 ,
                                       36                 ,
                                       47                 ,
                                       43                 ,
                                       3                  ,
                                       "test.code.33"     ,
                                       "test_source_33"   ,
                                       "Test message 33." );

        diagnosticsList.push_back(diagnostic);
    }

    else if (this->document_text == "test\ntext\n2\nstring\n")
    {
        pass &= buildDiagnosticObject( diagnostic         ,
                                       this->errors       ,
                                       67                 ,
                                       45                 ,
                                       68                 ,
                                       16                 ,
                                       4                  ,
                                       "test.code.44"     ,
                                       "test_source_44"   ,
                                       "Test message 44." );

        diagnosticsList.push_back(diagnostic);

        pass &= buildDiagnosticObject( diagnostic         ,
                                       this->errors       ,
                                       87                 ,
                                       17                 ,
                                       88                 ,
                                       12                 ,
                                       1                  ,
                                       "test.code.55"     ,
                                       "test_source_55"   ,
                                       "Test message 55." );

        diagnosticsList.push_back(diagnostic);
    }

    return pass;
}

bool TestServer::updateDocumentTextChanges(
                const std::string & replacement_text ,
                      int           start_line       ,
                      int           start_character  ,
                      int           end_line         ,
                      int           end_character    ,
                      int           range_length     )
{
    if (!this->is_initialized)
    {
        this->errors << m_error << "Server needs to be initialized" << std::endl;
        return false;
    }

    if (!this->is_document_open)
    {
        this->errors << m_error << "Server has no open document" << std::endl;
        return false;
    }

    bool pass = true;

    if ( start_line      == 0 &&
         start_character == 0 &&
         end_line        == 3 &&
         end_character   == 7 &&
         range_length    == 0 )
    {
        this->document_text = replacement_text;
    }

    return pass;
}

bool TestServer::gatherDocumentCompletionItems(
                      DataArray & completionItems  ,
                      bool      & is_incomplete    ,
                      int         line             ,
                      int         character        )
{
    if (!this->is_initialized)
    {
        this->errors << m_error << "Server needs to be initialized" << std::endl;
        return false;
    }

    if (!this->is_document_open)
    {
        this->errors << m_error << "Server has no open document" << std::endl;
        return false;
    }

    bool pass = true;

    DataObject completion_item;

    if ( line      == 4 &&
         character == 2 )
    {
        pass &= buildCompletionObject( completion_item        ,
                                       this->errors           ,
                                       "test-label-1"         ,
                                       11                     ,
                                       11                     ,
                                       11                     ,
                                       11                     ,
                                       "test-insert-text-1"   ,
                                       1                      ,
                                       "test type info 1"     ,
                                       "test documentation 1" ,
                                       false                  ,
                                       true                   );

        completionItems.push_back(completion_item);

        pass &= buildCompletionObject( completion_item        ,
                                       this->errors           ,
                                       "test-label-2"         ,
                                       22                     ,
                                       22                     ,
                                       22                     ,
                                       22                     ,
                                       "test-insert-text-2"   ,
                                       2                      ,
                                       "test type info 2"     ,
                                       "test documentation 2" ,
                                       false                  ,
                                       false                  );

        completionItems.push_back(completion_item);

        pass &= buildCompletionObject( completion_item        ,
                                       this->errors           ,
                                       "test-label-3"         ,
                                       33                     ,
                                       33                     ,
                                       33                     ,
                                       33                     ,
                                       "test-insert-text-3"   ,
                                       3                      ,
                                       "test type info 3"     ,
                                       "test documentation 3" ,
                                       false                  ,
                                       false                  );

        completionItems.push_back(completion_item);
    }

    is_incomplete = false;

    return pass;
}

bool TestServer::gatherDocumentDefinitionLocations(
                      DataArray & definitionLocations ,
                      int         line                ,
                      int         character           )
{
    if (!this->is_initialized)
    {
        this->errors << m_error << "Server needs to be initialized" << std::endl;
        return false;
    }

    if (!this->is_document_open)
    {
        this->errors << m_error << "Server has no open document" << std::endl;
        return false;
    }

    bool pass = true;

    DataObject location_object;

    if ( line      == 2 &&
         character == 5 )
    {
        pass &= buildLocationObject( location_object       ,
                                     this->errors          ,
                                     this->document_path   ,
                                     11                    ,
                                     11                    ,
                                     11                    ,
                                     11                    );

        definitionLocations.push_back(location_object);

        pass &= buildLocationObject( location_object       ,
                                     this->errors          ,
                                     this->document_path   ,
                                     22                    ,
                                     22                    ,
                                     22                    ,
                                     22                    );

        definitionLocations.push_back(location_object);

        pass &= buildLocationObject( location_object       ,
                                     this->errors          ,
                                     this->document_path   ,
                                     33                    ,
                                     33                    ,
                                     33                    ,
                                     33                    );

        definitionLocations.push_back(location_object);
    }

    return pass;
}

bool TestServer::gatherDocumentReferencesLocations(
                      DataArray & referencesLocations ,
                      int         line                ,
                      int         character           ,
                      bool        include_declaration )
{
    if (!this->is_initialized)
    {
        this->errors << m_error << "Server needs to be initialized" << std::endl;
        return false;
    }

    if (!this->is_document_open)
    {
        this->errors << m_error << "Server has no open document" << std::endl;
        return false;
    }

    bool pass = true;

    DataObject location_object;

    if ( line                == 1     &&
         character           == 3     &&
         include_declaration == false )
    {
        pass &= buildLocationObject( location_object       ,
                                     this->errors          ,
                                     this->document_path   ,
                                     44                    ,
                                     44                    ,
                                     44                    ,
                                     44                    );

        referencesLocations.push_back(location_object);

        pass &= buildLocationObject( location_object       ,
                                     this->errors          ,
                                     this->document_path   ,
                                     55                    ,
                                     55                    ,
                                     55                    ,
                                     55                    );

        referencesLocations.push_back(location_object);
    }

    return pass;
}

bool TestServer::gatherDocumentFormattingTextEdits(
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
        this->errors << m_error << "Server needs to be initialized" << std::endl;
        return false;
    }

    if (!this->is_document_open)
    {
        this->errors << m_error << "Server has no open document" << std::endl;
        return false;
    }

    bool pass = true;

    DataObject textedit_object;

    if ( start_line      == 2    &&
         start_character == 0    &&
         end_line        == 4    &&
         end_character   == 3    &&
         tab_size        == 4    &&
         insert_spaces   == true )
    {
        pass &= buildTextEditObject( textedit_object                      ,
                                     this->errors                         ,
                                     10                                   ,
                                     01                                   ,
                                     14                                   ,
                                     03                                   ,
                                     "test\n  new\n  text\n  format\n  1" );

        formattingTextEdits.push_back(textedit_object);

        pass &= buildTextEditObject( textedit_object                      ,
                                     this->errors                         ,
                                     20                                   ,
                                     01                                   ,
                                     24                                   ,
                                     03                                   ,
                                     "test\n  new\n  text\n  format\n  2" );

        formattingTextEdits.push_back(textedit_object);

        pass &= buildTextEditObject( textedit_object                      ,
                                     this->errors                         ,
                                     30                                   ,
                                     01                                   ,
                                     34                                   ,
                                     03                                   ,
                                     "test\n  new\n  text\n  format\n  3" );

        formattingTextEdits.push_back(textedit_object);
    }

    return pass;
}

bool TestServer::gatherDocumentSymbols(
                      DataArray & documentSymbols )
{
    if (!this->is_initialized)
    {
        this->errors << m_error << "Server needs to be initialized" << std::endl;
        return false;
    }

    if (!this->is_document_open)
    {
        this->errors << m_error << "Server has no open document" << std::endl;
        return false;
    }

    bool pass = true;

    DataObject parent_object;

    if (this->document_path == "test/document/uri/string")
    {
        std::string p0_name                      = "test_symbol_name_parent_0";
        std::string p0_detail                    = "test::symbol::detail::parent::0";
        int         p0_kind                      = 15;
        bool        p0_deprecated                = false;
        int         p0_start_line                = 10;
        int         p0_start_character           = 11;
        int         p0_end_line                  = 10;
        int         p0_end_character             = 17;
        int         p0_selection_start_line      = 10;
        int         p0_selection_start_character = 13;
        int         p0_selection_end_line        = 10;
        int         p0_selection_end_character   = 15;

        std::string c1_name                      = "test_symbol_name_child_1";
        std::string c1_detail                    = "test::symbol::detail::child::1";
        int         c1_kind                      = 20;
        bool        c1_deprecated                = false;
        int         c1_start_line                = 20;
        int         c1_start_character           = 21;
        int         c1_end_line                  = 20;
        int         c1_end_character             = 27;
        int         c1_selection_start_line      = 20;
        int         c1_selection_start_character = 23;
        int         c1_selection_end_line        = 20;
        int         c1_selection_end_character   = 25;

        std::string c2_name                      = "test_symbol_name_child_2";
        std::string c2_detail                    = "test::symbol::detail::child::2";
        int         c2_kind                      = 22;
        bool        c2_deprecated                = false;
        int         c2_start_line                = 30;
        int         c2_start_character           = 31;
        int         c2_end_line                  = 30;
        int         c2_end_character             = 37;
        int         c2_selection_start_line      = 30;
        int         c2_selection_start_character = 33;
        int         c2_selection_end_line        = 30;
        int         c2_selection_end_character   = 35;

        pass &= buildDocumentSymbolObject( parent_object                    ,
                                           errors                           ,
                                           p0_name                          ,
                                           p0_detail                        ,
                                           p0_kind                          ,
                                           p0_deprecated                    ,
                                           p0_start_line                    ,
                                           p0_start_character               ,
                                           p0_end_line                      ,
                                           p0_end_character                 ,
                                           p0_selection_start_line          ,
                                           p0_selection_start_character     ,
                                           p0_selection_end_line            ,
                                           p0_selection_end_character       );

        pass &= buildDocumentSymbolObject( addDocumentSymbolChild( parent_object ) ,
                                           errors                                  ,
                                           c1_name                                 ,
                                           c1_detail                               ,
                                           c1_kind                                 ,
                                           c1_deprecated                           ,
                                           c1_start_line                           ,
                                           c1_start_character                      ,
                                           c1_end_line                             ,
                                           c1_end_character                        ,
                                           c1_selection_start_line                 ,
                                           c1_selection_start_character            ,
                                           c1_selection_end_line                   ,
                                           c1_selection_end_character              );

        pass &= buildDocumentSymbolObject( addDocumentSymbolChild( parent_object ) ,
                                           errors                                  ,
                                           c2_name                                 ,
                                           c2_detail                               ,
                                           c2_kind                                 ,
                                           c2_deprecated                           ,
                                           c2_start_line                           ,
                                           c2_start_character                      ,
                                           c2_end_line                             ,
                                           c2_end_character                        ,
                                           c2_selection_start_line                 ,
                                           c2_selection_start_character            ,
                                           c2_selection_end_line                   ,
                                           c2_selection_end_character              );

        documentSymbols.push_back( parent_object );
    }

    return pass;
}

} // namespace lsp
} // namespace wasp
