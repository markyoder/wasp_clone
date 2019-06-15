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

        if ( !pass ) checkClientServerErrors();

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

        if ( !pass ) checkClientServerErrors();

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

        pass &= ( diagnostics_size == 0 );

        pass &= createParseTree();

        if ( !pass ) checkClientServerErrors();

        return pass;
    }

    bool createParseTree()
    {
        // make the document symbols lsp call to the server

        if ( !client.doDocumentSymbols() )
        {
            Interpreter<S>::error_stream() << m_error_prefix
                                           << "Document symbol creation failed"
                                           << std::endl;
            return false;
        }

        bool pass = true;

        // initialize the global_node_index / global_byte_offset / location info

        global_node_index = 0;

        global_byte_offset = 0;

        previous_symbol_end_line = 1;

        previous_symbol_end_char = 0;

        // get the root document symbol iterator

        SymbolIterator::SP si = client.getSymbolIterator();

        // traverse further into root children and pushing as staged children

        for( size_t i = 0 ; i < si->getChildSize() ; i++ )
        {
            pass &= si->moveToChildAt( i );

            pass &= addSymbolsToTree( si );

            this->push_staged_child( global_node_index-1 );

            pass &= si->moveToParent();
        }

        return pass;
    }

    bool addSymbolsToTree( SymbolIterator::SP & si )
    {
        bool pass = true;

        // dissect current document symbol so the info can be used for insertion

        std::string symbol_name;
        std::string symbol_detail;
        int         symbol_kind;
        bool        symbol_deprecated;
        int         symbol_start_line;
        int         symbol_start_char;
        int         symbol_end_line;
        int         symbol_end_char;
        int         symbol_selection_start_line;
        int         symbol_selection_start_char;
        int         symbol_selection_end_line;
        int         symbol_selection_end_char;

        pass &= si->dissectCurrentSymbol( symbol_name                 ,
                                          symbol_detail               ,
                                          symbol_kind                 ,
                                          symbol_deprecated           ,
                                          symbol_start_line           ,
                                          symbol_start_char           ,
                                          symbol_end_line             ,
                                          symbol_end_char             ,
                                          symbol_selection_start_line ,
                                          symbol_selection_start_char ,
                                          symbol_selection_end_line   ,
                                          symbol_selection_end_char   );

        // if this is a leaf node with no children - push_token and push_leaf

        if ( si->getChildSize() == 0 )
        {
            // check that this leaf token does not span multiple lines

            wasp_check( symbol_start_line == symbol_end_line );

            // check that this leaf token end column is not before start column

            wasp_check( symbol_end_char >= symbol_start_char );

            // number of newlines that needs to be added since last token

            size_t additional_new_lines = symbol_start_line - previous_symbol_end_line;

            // add calculated number of newlines and increase global_byte_offset

            for(int i = 0 ; i < additional_new_lines ; i++ )
            {
                global_byte_offset++;

                this->push_line_offset( global_byte_offset );
            }

            // increase global_byte_offset to the starting character of token

            global_byte_offset += symbol_start_char;

            // if the same line as last token - adjust based on previous token

            if ( additional_new_lines == 0 )
            {
                global_byte_offset -= previous_symbol_end_char + 1;
            }

            // calculate the token length based on start and end character

            size_t token_length = symbol_end_char - symbol_start_char + 1;

            // since lsp doesn't give data - make dummy data of correct length

            std::string token_data = std::string(token_length , ' ');

            // push correct length dummy token data at calculated byte offset

            this->push_token( token_data.c_str() , wasp::UNKNOWN , global_byte_offset );

            // push leaf with the symbol name and the previous token push index

            this->push_leaf( wasp::VALUE , symbol_name.c_str() , this->token_count() - 1 );

            // increase global_byte_offset to point to the end of inserted token

            global_byte_offset += token_length;

            // save the inserted token's end line as previous_symbol_end_line

            previous_symbol_end_line = symbol_end_line;

            // save the inserted token's end column as previous_symbol_end_char

            previous_symbol_end_char = symbol_end_char;

            // increase the global_node_index since we inserted a node

            global_node_index++;

            // this was a leaf node - so we can return and not traverse further

            return pass;
        }

        // this is not a leaf - so traverse further but cache child node indices

        std::vector<size_t> child_indices;

        for( size_t i = 0 ; i < si->getChildSize() ; i++ )
        {
            pass &= si->moveToChildAt( i );

            pass &= addSymbolsToTree( si );

            child_indices.push_back( global_node_index-1 );

            pass &= si->moveToParent();
        }

        // push parent with the symbol name and its cached child node indices

        this->push_parent( wasp::UNKNOWN , symbol_name.c_str() , child_indices );

        // increase the global_node_index since we inserted a node

        global_node_index++;

        // return to parent caller

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

    size_t global_node_index;

    size_t global_byte_offset;

    size_t previous_symbol_end_line;

    size_t previous_symbol_end_char;
};

typedef LSPInterpreter<> DefaultLSPInterpreter;

} // namespace lsp
} // namespace wasp

#endif  // WASPLSP_LSPINTERPRETER_H
