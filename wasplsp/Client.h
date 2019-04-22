#ifndef WASPLSP_CLIENT_H
#define WASPLSP_CLIENT_H

#include "waspcore/decl.h"
#include "wasplsp/Connection.h"

namespace wasp {
namespace lsp  {

template <class T>
class WASP_PUBLIC Client
{
  public:
    Client(){}

    ~Client(){}

    bool connect( std::shared_ptr<Connection> connection )
    {
        return Impl.connect( connection );
    }

    bool initialize()
    {
        return Impl.initialize();
    }

    bool initialized()
    {
        return Impl.initialized();
    }

    bool opened( const std::string & document_path        ,
                 const std::string & document_language_id ,
                 const std::string & document_text        )
    {
        return Impl.opened( document_path        ,
                            document_language_id ,
                            document_text        );
    }

    bool changed( int                 start_line        ,
                  int                 start_character   ,
                  int                 end_line          ,
                  int                 end_character     ,
                  int                 range_length      ,
                  const std::string & new_document_text )
    {
        return Impl.changed( start_line        ,
                             start_character   ,
                             end_line          ,
                             end_character     ,
                             range_length ,
                             new_document_text );
    }

    bool completion( int line      ,
                     int character )
    {
        return Impl.completion( line      ,
                                character );
    }

    bool definition( int line      ,
                     int character )
    {
        return Impl.definition( line      ,
                                character );
    }

    bool references( int  line                ,
                     int  character           ,
                     bool include_declaration )
    {
        return Impl.references( line                ,
                                character           ,
                                include_declaration );
    }

    bool formatting( int  start_line      ,
                     int  start_character ,
                     int  end_line        ,
                     int  end_character   ,
                     int  tab_size        ,
                     bool insert_spaces   )
    {
        return Impl.formatting( start_line      ,
                                start_character ,
                                end_line        ,
                                end_character   ,
                                tab_size        ,
                                insert_spaces   );
    }

    bool closed()
    {
        return Impl.closed();
    }

    bool shutdown()
    {
        return Impl.shutdown();
    }

    bool exit()
    {
        return Impl.exit();
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
                                     end_character   );
    }

    bool isConnected()
    {
        return Impl.isConnected();
    }

    std::shared_ptr<Connection> getConnection()
    {
        return Impl.getConnection();
    }

    std::string getErrors()
    {
        return Impl.getErrors();
    }

    int getPreviousRequestID()
    {
        return Impl.getPreviousRequestID();
    }

    bool isDocumentOpen()
    {
        return Impl.isDocumentOpen();
    }

    int getCurrentDocumentVersion()
    {
        return Impl.getCurrentDocumentVersion();
    }

  private:

      T Impl;
};

} // namespace lsp
} // namespace wasp

#endif // WASPLSP_CLIENT_H
