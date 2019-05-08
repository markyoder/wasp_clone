#ifndef WASPLSP_CLIENT_H
#define WASPLSP_CLIENT_H

#include "waspcore/decl.h"
#include "wasplsp/Connection.h"
#include "wasplsp/SymbolIterator.h"
#include "waspcore/Object.h"

namespace wasp {
namespace lsp  {

template <class T>
class WASP_PUBLIC Client
{
  public:
    Client(){}

    ~Client(){}

    bool connect( Connection::SP connection )
    {
        return Impl.connect( connection );
    }

    bool doInitialize()
    {
        return Impl.doInitialize();
    }

    bool doInitialized()
    {
        return Impl.doInitialized();
    }

    bool doDocumentOpen( const std::string & document_path        ,
                         const std::string & document_language_id ,
                         const std::string & document_text        )
    {
        return Impl.doDocumentOpen( document_path        ,
                                    document_language_id ,
                                    document_text        );
    }

    bool doDocumentChange( int                 start_line        ,
                           int                 start_character   ,
                           int                 end_line          ,
                           int                 end_character     ,
                           int                 range_length      ,
                           const std::string & new_document_text )
    {
        return Impl.doDocumentChange( start_line        ,
                                      start_character   ,
                                      end_line          ,
                                      end_character     ,
                                      range_length      ,
                                      new_document_text );
    }

    bool doDocumentCompletion( int line      ,
                               int character )
    {
        return Impl.doDocumentCompletion( line      ,
                                          character );
    }

    bool doDocumentDefinition( int line      ,
                               int character )
    {
        return Impl.doDocumentDefinition( line      ,
                                          character );
    }

    bool doDocumentReferences( int  line                ,
                               int  character           ,
                               bool include_declaration )
    {
        return Impl.doDocumentReferences( line                ,
                                          character           ,
                                          include_declaration );
    }

    bool doDocumentFormatting( int  start_line      ,
                               int  start_character ,
                               int  end_line        ,
                               int  end_character   ,
                               int  tab_size        ,
                               bool insert_spaces   )
    {
        return Impl.doDocumentFormatting( start_line      ,
                                          start_character ,
                                          end_line        ,
                                          end_character   ,
                                          tab_size        ,
                                          insert_spaces   );
    }

    bool doDocumentSymbols()
    {
        return Impl.doDocumentSymbols();
    }

    bool doDocumentClose()
    {
        return Impl.doDocumentClose();
    }

    bool doShutdown()
    {
        return Impl.doShutdown();
    }

    bool doExit()
    {
        return Impl.doExit();
    }

    int getDiagnosticSize()
    {
        return Impl.getDiagnosticSize();
    }

    int getCompletionSize()
    {
        return Impl.getCompletionSize();
    }

    int getDefinitionSize()
    {
        return Impl.getDefinitionSize();
    }

    int getReferencesSize()
    {
        return Impl.getReferencesSize();
    }

    int getFormattingSize()
    {
        return Impl.getFormattingSize();
    }

    bool getDiagnosticAt( int           index           ,
                          int         & start_line      ,
                          int         & start_character ,
                          int         & end_line        ,
                          int         & end_character   ,
                          int         & severity        ,
                          std::string & code            ,
                          std::string & source          ,
                          std::string & message         )
    {
        return Impl.getDiagnosticAt( index           ,
                                     start_line      ,
                                     start_character ,
                                     end_line        ,
                                     end_character   ,
                                     severity        ,
                                     code            ,
                                     source          ,
                                     message         );
    }

    bool getCompletionAt( int           index           ,
                          std::string & label           ,
                          int         & start_line      ,
                          int         & start_character ,
                          int         & end_line        ,
                          int         & end_character   ,
                          std::string & new_text        ,
                          int         & kind            ,
                          std::string & detail          ,
                          std::string & documentation   ,
                          bool        & deprecated      ,
                          bool        & preselect       )
    {
        return Impl.getCompletionAt( index           ,
                                     label           ,
                                     start_line      ,
                                     start_character ,
                                     end_line        ,
                                     end_character   ,
                                     new_text        ,
                                     kind            ,
                                     detail          ,
                                     documentation   ,
                                     deprecated      ,
                                     preselect       );
    }

    bool getDefinitionAt( int           index           ,
                          int         & start_line      ,
                          int         & start_character ,
                          int         & end_line        ,
                          int         & end_character   )
    {
        return Impl.getDefinitionAt( index           ,
                                     start_line      ,
                                     start_character ,
                                     end_line        ,
                                     end_character   );
    }

    bool getReferencesAt( int           index           ,
                          int         & start_line      ,
                          int         & start_character ,
                          int         & end_line        ,
                          int         & end_character   )
    {
        return Impl.getReferencesAt( index           ,
                                     start_line      ,
                                     start_character ,
                                     end_line        ,
                                     end_character   );
    }

    bool getFormattingAt( int           index           ,
                          int         & start_line      ,
                          int         & start_character ,
                          int         & end_line        ,
                          int         & end_character   ,
                          std::string & new_text        )
    {
        return Impl.getFormattingAt( index           ,
                                     start_line      ,
                                     start_character ,
                                     end_line        ,
                                     end_character   ,
                                     new_text        );
    }

    bool isConnected()
    {
        return Impl.isConnected();
    }

    Connection::SP getConnection()
    {
        return Impl.getConnection();
    }

    std::string getErrors() const
    {
        return Impl.getErrors();
    }

    int getPreviousRequestID() const
    {
        return Impl.getPreviousRequestID();
    }

    bool isDocumentOpen() const
    {
        return Impl.isDocumentOpen();
    }

    int getCurrentDocumentVersion() const
    {
        return Impl.getCurrentDocumentVersion();
    }

    SymbolIterator::SP getSymbolIterator()
    {
        return Impl.getSymbolIterator();
    }

  private:

      T Impl;
};

} // namespace lsp
} // namespace wasp

#endif // WASPLSP_CLIENT_H
