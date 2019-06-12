#ifndef WASPLSP_LSPINTERPRETER_H
#define WASPLSP_LSPINTERPRETER_H

#include <string>
#include <iostream>
#include <fstream>
#include <thread>
#include "wasplsp/ServerImpl.h"
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
        , server_running ( false ) {}

    LSPInterpreter( std::ostream & error )
        : Interpreter<S> ( error )
        , server_running ( false ) {}

    ~LSPInterpreter()
    {
        if ( client.isDocumentOpen() )
        {
            client.doDocumentClose();
        }

        if ( server->isRunning() )
        {
            client.doShutdown();

            client.doExit();
        }

        this->checkClientServerErrors();

        if ( server_running )
        {
            server_thread.join();
        }
    }

    bool setupServer( ServerImpl * server )
    {
        if ( server_running )
        {
            Interpreter<S>::error_stream() << m_error_prefix
                                           << "Server already setup and running"
                                           << std::endl;
            return false;
        }

        bool pass = true;

        this->server = server;

        server_thread = std::thread( &ServerImpl::run , this->server );

        pass &= client.connect( this->server->getConnection() );

        pass &= client.doInitialize();

        pass &= client.doInitialized();

        this->checkClientServerErrors();

        server_running = pass;

        return pass;
    }

    bool parse( std::istream & inp_stream     ,
                size_t         startLine = 1u ,
                size_t         startCol  = 1u )
    {
        std::ostringstream oss;

        oss << inp_stream.rdbuf();

        return parseString( oss.str() , "stream input" , startLine , startCol );
    }

    bool parseStream( std::istream       & inp_stream                 ,
                      const std::string  & sname     = "stream input" ,
                      size_t               startLine = 1u             ,
                      size_t               startCol  = 1u             )
    {
        std::ostringstream oss;

        oss << inp_stream.rdbuf();

        return parseString( oss.str() , sname , startLine , startCol );
    }

    bool parseFile( const std::string & filename       ,
                    size_t              startLine = 1u )
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

        return parseString( oss.str() , filename , startLine );
    }

    bool parseString( const std::string & input                       ,
                      const std::string & sname     = "string stream" ,
                      size_t              startLine = 1u              ,
                      size_t              startCol  = 1u              )
    {
        bool pass = true;

        if ( !server_running )
        {
            Interpreter<S>::error_stream() << m_error_prefix
                                           << "Server is not setup and running"
                                           << std::endl;
            return false;
        }

        pass &= client.doDocumentOpen( sname     ,
                                       "wasplsp" ,
                                       input     );

        size_t diagnostics_size = client.getDiagnosticSize();

        for ( size_t index = 0 ; index < diagnostics_size ; index++ )
        {
            int         start_line;
            int         start_character;
            int         end_line;
            int         end_character;
            int         severity;
            std::string code;
            std::string source;
            std::string message;

            client.getDiagnosticAt( index           ,
                                    start_line      ,
                                    start_character ,
                                    end_line        ,
                                    end_character   ,
                                    severity        ,
                                    code            ,
                                    source          ,
                                    message         );

            Interpreter<S>::error_stream() << " line: "   << start_line
                                           << " column: " << start_character
                                           << " - "      << message
                                           << std::endl;
        }

        this->checkClientServerErrors();

        pass &= ( diagnostics_size == 0 );

        return pass;
    }

  private:

    bool server_running;

    ServerImpl * server;

    std::thread server_thread;

    ClientImpl client;

    void checkClientServerErrors()
    {
        if ( !client.getErrors().empty() )
        {
            Interpreter<S>::error_stream() << "lsp client-side errors:"
                                           << std::endl
                                           << client.getErrors()
                                           << std::endl;
        }

        if ( !server->getErrors().empty() )
        {
            Interpreter<S>::error_stream() << "lsp server-side errors:"
                                           << std::endl
                                           << server->getErrors()
                                           << std::endl;
        }
    }
};

typedef LSPInterpreter<> DefaultLSPInterpreter;

} // namespace lsp
} // namespace wasp

#endif  // WASPLSP_LSPINTERPRETER_H
