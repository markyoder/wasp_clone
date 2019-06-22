#include "wasplsp/LSPInterpreter.h"

namespace wasp {
namespace lsp  {

/** Invoke the lexer and parser for a stream
 * @param in         - input stream
 * @param start_line - optional start line for offset if not entire document
 * @param start_col  - optional start col for offset if not entire document
 * @return           - true if successfully parsed with no diagnostic errors
 */
bool LSPInterpreter::parse( std::istream & inp_stream ,
                            size_t         start_line ,
                            size_t         start_col  )
{
    std::ostringstream oss;

    oss << inp_stream.rdbuf();

    return parseImpl( oss.str() , "stream input" , start_line , start_col );
}

/** Invoke the lexer and parser for a stream
 * @param in         - input stream
 * @param sname      - optional stream name for error messages
 * @param start_line - optional start line for offset if not entire document
 * @param start_col  - optional start col for offset if not entire document
 * @return           - true if successfully parsed with no diagnostic errors
 */
bool LSPInterpreter::parseStream( std::istream       & inp_stream ,
                                  const std::string  & sname      ,
                                  size_t               start_line ,
                                  size_t               start_col  )
{
    std::ostringstream oss;

    oss << inp_stream.rdbuf();

    return parseImpl( oss.str() , sname , start_line , start_col );
}

/** Invoke the lexer and parser on a file. Use parse_stream with a
 * std::ifstream if detection of file reading errors is required
 * @param filename   - input file name
 * @param start_line - optional start line for offset if not entire document
 * @return           - true if successfully parsed with no diagnostic errors
 */
bool LSPInterpreter::parseFile( const std::string & filename   ,
                                size_t              start_line )
{
    std::ifstream ifs( filename.c_str() );

    if ( !ifs.good() )
    {
        Interpreter::error_stream() << m_error_prefix
                                       << "Cannot open file: " << filename
                                       << std::endl;
        return false;
    }

    std::ostringstream oss;

    oss << ifs.rdbuf();

    return parseImpl( oss.str() , filename , start_line );
}

/** Invoke the lexer and parser on an input string
 * @param input      - input string
 * @param sname      - optional stream name for error messages
 * @param start_line - optional start line for offset if not entire document
 * @param start_col  - optional start col for offset if not entire document
 * @return           - true if successfully parsed with no diagnostic errors
 */
bool LSPInterpreter::parseString( const std::string & input      ,
                                  const std::string & sname      ,
                                  size_t              start_line ,
                                  size_t              start_col  )
{
    return parseImpl( input , sname , start_line , start_col );
}

/** Wraps the parseLSP implementation method with Interpreter methods
 * (1) Sets the base Interpreter's m_stream_name
 * (2) Sets the base Interpreter's start_line
 * (3) Sets the base Interpreter's start_column
 * (4) Calls parseLSP to actually parse the document
 * (5) Calls commit_stages after the parse to finish
 * (6) Sets the failed bool on the base Interpreter
 * @param input      - input string
 * @param sname      - optional stream name for error messages
 * @param start_line - optional start line for offset if not entire document
 * @param start_col  - optional start col for offset if not entire document
 * @return           - true if successfully parsed with no diagnostic errors
 */
bool LSPInterpreter::parseImpl( const std::string & input       ,
                                const std::string & stream_name ,
                                size_t              start_line  ,
                                size_t              start_col   )
{
    Interpreter::m_stream_name = stream_name;

    Interpreter::set_start_line( start_line );

    Interpreter::set_start_column( start_col );

    bool parsed = parseLSP( input , stream_name );

    Interpreter::commit_stages();

    Interpreter::set_failed( parsed );

    return parsed;
}

/** Wraps the parseLSP implementation method with Interpreter methods
 * (1) Calls DOCUMENT_OPEN on the server with the INPUT
 * (2) Gets any DIAGNOSTICS from server and adds each to the error_stream
 * (3) Gets DOCUMENT_SYMBOLS from server and traverses creating parse tree
 * @param input - input string
 * @param sname - optional stream name for error messages
 * @return      - true if successfully parsed with no diagnostic errors
 */
bool LSPInterpreter::parseLSP( const std::string & input       ,
                               const std::string & stream_name )
{
    bool pass = true;

    // check that the LSPInterpreter has bveen successfully connected

    if ( !client )
    {
        Interpreter::error_stream() << m_error_prefix
                                    << "LSPInterpreter client not yet set"
                                    << std::endl;
        return false;
    }

    // get temporary file path from the client (if already open) or create new

    this->temp_input_file_path = client->isDocumentOpen()  ?
                                 client->getDocumentPath() :
                                 tempnam("","") + std::string(m_extension);

    // write contents to parse to the temporary input file that the server uses

    std::ofstream temp_input_file;

    temp_input_file.open( this->temp_input_file_path );

    temp_input_file << input;

    temp_input_file.close();

    // if the document is not yet open - first parse so call DOCUMENT_OPEN

    if ( !client->isDocumentOpen() )
    {
        pass &= client->doDocumentOpen( this->temp_input_file_path ,
                                        "wasplsp"                  ,
                                        input                      );
    }

    // if the document is already open - not first parse so call DOCUMENT_CHANGE
    // the -1s for range values indicate that the input is the entire document

    else
    {
        pass &= client->doDocumentChange( -1 , -1 , -1 , -1 , -1 , input );
    }

    // get the DIAGNOSTICS size from the server after the open and parse

    size_t diagnostics_size = client->getDiagnosticSize();

    // if there are DIAGNOSTICS - add each to error_stream with line and column

    for ( size_t index = 0 ; index < diagnostics_size ; index++ )
    {
        // dissect each diagnostic to get the line / column / message info

        int         start_line;
        int         start_char;
        int         end_line;
        int         end_char;
        int         severity;
        std::string code;
        std::string source;
        std::string message;

        client->getDiagnosticAt( index      ,
                                 start_line ,
                                 start_char ,
                                 end_line   ,
                                 end_char   ,
                                 severity   ,
                                 code       ,
                                 source     ,
                                 message    );

        // calculate report line / column using the start_line / start_column                        

        int report_line = start_line + Interpreter::m_start_line - 1;

        int report_col = start_char + Interpreter::m_start_column - 1;

        // add each message with line / column to error_stream in correct format

        Interpreter::error_stream() << Interpreter::stream_name()
                                    << ":"
                                    << report_line << "." << report_col
                                    << ": "
                                    << message
                                    << std::endl;
    }

    // update the pass boolean based on if there were any diagnostics

    pass &= ( diagnostics_size == 0 );

    // call the top level method for DOCUMENT_SYMBOLS to PARSE_TREE conversion

    pass &= createParseTree();

    // if anything failed along the way - check the client and server for errors

    if ( !pass ) checkClientServerErrors();

    return pass;
}

/** Top level call for doing the DOCUMENT_SYMBOLS to PARSE_TREE conversion
 * (1) Calls addSymbolsToTree recursive method for each child of the root
 * (2) Calls base Interpreter's push_staged_child for each child of the root
 * @return - true if parse tree successfully built from DOCUMENT_SYMBOLS
 */
bool LSPInterpreter::createParseTree()
{
    // make the document symbols lsp call to the server

    if ( !client->doDocumentSymbols() )
    {
        Interpreter::error_stream() << m_error_prefix
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

    SymbolIterator::SP si = client->getSymbolIterator();

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

/** Interior recursive method for DOCUMENT_SYMBOLS to PARSE_TREE conversion
 * (1) For every LEAF - pushes a token and a leaf node to the Interpreter
 * (2) For every PARENT - pushes a parent node with a list of child indices
 * @param si - reference to a SymbolIterator shared_ptr
 * @return   - true if parse tree successfully built from DOCUMENT_SYMBOLS
 */
bool LSPInterpreter::addSymbolsToTree( SymbolIterator::SP & si )
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

        for( size_t i = 0 ; i < additional_new_lines ; i++ )
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

/** For any failure - this is called to check for any client / server errors
 * (1) if the client has any errors stored - add them to the error_stream
 * (2) if the server has any errors stored - add them to the error_stream
 */
void LSPInterpreter::checkClientServerErrors()
{
    // if the client has any errors - add to the base Interpreter::error_stream

    if ( client && !client->getErrors().empty() )
    {
        Interpreter::error_stream() << "lsp client-side errors:"
                                    << std::endl
                                    << client->getErrors()
                                    << std::endl;
    }

    // if the server has any errors - add to the base Interpreter::error_stream

    if ( client && !client->getConnection()->getServerErrors().empty() )
    {
        Interpreter::error_stream() << "lsp server-side errors:"
                                    << std::endl
                                    << client->getConnection()->getServerErrors()
                                    << std::endl;
    }
}

} // namespace lsp
} // namespace wasp
