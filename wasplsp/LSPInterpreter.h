#ifndef WASPLSP_LSPINTERPRETER_H
#define WASPLSP_LSPINTERPRETER_H

#include <string>
#include <iostream>
#include <fstream>
#include "wasplsp/Connection.h"
#include "wasplsp/ClientImpl.h"
#include "waspcore/Interpreter.h"
#include "waspcore/TreeNodePool.h"
#include "waspcore/decl.h"

namespace wasp {
namespace lsp  {

template<class S = TreeNodePool<>>
class WASP_PUBLIC LSPInterpreter : public Interpreter<S>
{
  public:

    LSPInterpreter()
        : Interpreter<S> (       )
        , is_connected   ( false ) {}

    LSPInterpreter( std::ostream & error )
        : Interpreter<S> ( error )
        , is_connected   ( false ) {}

    ~LSPInterpreter() {}

    bool connect( std::shared_ptr<Connection> connection )
    {
        if ( is_connected )
        {
            Interpreter<S>::error_stream() << m_error_prefix
                                           << "LSPInterpreter already connected"
                                           << std::endl;
            return false;
        }

        bool pass = true;

        this->connection = connection;

        pass &= client.connect( connection );

        pass &= client.doInitialize();

        pass &= client.doInitialized();

        checkClientServerErrors();

        is_connected = pass;

        return pass;
    }

    bool disconnect()
    {
        bool pass = true;

        if ( client.isDocumentOpen() )
        {
            pass &= client.doDocumentClose();
        }

        if ( connection->isServerRunning() )
        {
            pass &= client.doShutdown();

            pass &= client.doExit();
        }

        checkClientServerErrors();

        return pass;
    }

    bool parse( std::istream & inp_stream      ,
                size_t         start_line = 1u ,
                size_t         start_col  = 1u )
    {
        std::ostringstream oss;

        oss << inp_stream.rdbuf();

        return parseImpl( oss.str() , "stream input" , start_line , start_col );
    }

    bool parseStream( std::istream       & inp_stream                  ,
                      const std::string  & sname      = "stream input" ,
                      size_t               start_line = 1u             ,
                      size_t               start_col  = 1u             )
    {
        std::ostringstream oss;

        oss << inp_stream.rdbuf();

        return parseImpl( oss.str() , sname , start_line , start_col );
    }

    bool parseFile( const std::string & filename        ,
                    size_t              start_line = 1u )
    {
        std::ifstream ifs( filename.c_str() );

        if ( !ifs.good() )
        {
            Interpreter<S>::error_stream() << m_error_prefix
                                           << "Cannot open file: " << filename
                                           << std::endl;
            return false;
        }

        std::ostringstream oss;

        oss << ifs.rdbuf();

        return parseImpl( oss.str() , filename , start_line );
    }

    bool parseString( const std::string & input                        ,
                      const std::string & sname      = "string stream" ,
                      size_t              start_line = 1u              ,
                      size_t              start_col  = 1u              )
    {
        return parseImpl( input , sname , start_line , start_col );
    }

  private:

    bool parseImpl( const std::string & input                          ,
                    const std::string & stream_name = "string stream" ,
                    size_t              start_line  = 1u              ,
                    size_t              start_col   = 1u              )
    {
        Interpreter<S>::m_stream_name = stream_name;

        Interpreter<S>::set_start_line( start_line );

        Interpreter<S>::set_start_column( start_col );

        bool parsed = parseLSP( input , stream_name );

        Interpreter<S>::commit_stages();

        Interpreter<S>::set_failed( parsed );

        return parsed;
    }

    bool parseLSP( const std::string & input                         ,
                   const std::string & stream_name = "string stream" )
    {
        bool pass = true;

        if ( !is_connected )
        {
            Interpreter<S>::error_stream() << m_error_prefix
                                           << "LSPInterpreter not yet connected"
                                           << std::endl;
            return false;
        }

        if ( !connection->isServerRunning() )
        {
            Interpreter<S>::error_stream() << m_error_prefix
                                           << "Connection server is not running"
                                           << std::endl;
            return false;
        }

        pass &= client.doDocumentOpen( stream_name ,
                                       "wasplsp"   ,
                                       input       );

        size_t diagnostics_size = client.getDiagnosticSize();

        for ( size_t index = 0 ; index < diagnostics_size ; index++ )
        {
            int         start_line;
            int         start_char;
            int         end_line;
            int         end_char;
            int         severity;
            std::string code;
            std::string source;
            std::string message;

            client.getDiagnosticAt( index      ,
                                    start_line ,
                                    start_char ,
                                    end_line   ,
                                    end_char   ,
                                    severity   ,
                                    code       ,
                                    source     ,
                                    message    );

            int report_line = start_line + Interpreter<S>::m_start_line - 1;

            int report_col = start_char + Interpreter<S>::m_start_column - 1;

            Interpreter<S>::error_stream() << " line: "   << report_line
                                           << " column: " << report_col
                                           << " - "       << message
                                           << std::endl;
        }

        checkClientServerErrors();

        pass &= ( diagnostics_size == 0 );

        return pass;
    }

    void checkClientServerErrors()
    {
        if ( !client.getErrors().empty() )
        {
            Interpreter<S>::error_stream() << "lsp client-side errors:"
                                           << std::endl
                                           << client.getErrors()
                                           << std::endl;
        }

        if ( !connection->getServerErrors().empty() )
        {
            Interpreter<S>::error_stream() << "lsp server-side errors:"
                                           << std::endl
                                           << connection->getServerErrors()
                                           << std::endl;
        }
    }

    bool is_connected;

    std::shared_ptr<Connection> connection;

    ClientImpl client;
};

typedef LSPInterpreter<> DefaultLSPInterpreter;

} // namespace lsp
} // namespace wasp

#endif  // WASPLSP_LSPINTERPRETER_H
