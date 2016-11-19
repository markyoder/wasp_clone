
#ifndef WASP_SIRENINTERPRETER_H
#define WASP_SIRENINTERPRETER_H

#include <string>
#include <fstream>
#include <istream>
#include <ostream>
#include <iostream>
#include <vector>
#include <map>
#include <memory>

#include "waspcore/Interpreter.h"

/** The wasp namespace is used to encapsulate the three parser classes
 * wasp::SIRENParser, wasp::SIRENLexerImpl and wasp::SIRENInterpreter */
namespace wasp {

    class SIRENInterpreter : public Interpreter<default_node_type_size,default_node_index_size
            ,default_token_type_size,default_token_index_type_size
            ,default_file_offset_type_size> {
    public:
        typedef std::shared_ptr<SIRENInterpreter> SharedPtr;
        SIRENInterpreter();
        SIRENInterpreter(std::ostream & err);
        virtual ~SIRENInterpreter();

        /** Invoke the lexer and parser for a stream.
         * @param in        input stream
         * @param sname     stream name for error messages
         * @return          true if successfully parsed
         */
        bool parseStream(std::istream& in,
                const std::string& sname = "selection statement", size_t startLine=1u, size_t startColumn=1u);
        bool parse(std::istream &input, size_t startLine=1u, size_t startColumn=1u);
        /** Invoke the lexer and parser on an input string.
         * @param input     input string
         * @param sname     stream name for error messages
         * @return          true if successfully parsed
         */
        bool parseString(const std::string& input,
                const std::string& sname = "selection statement", size_t startLine=1u, size_t startColumn=1u);

    public: // public variables
        /**
         * @brief lexer - current lexer instance
         */
        class SIRENLexerImpl* m_lexer;

        /**
         * @brief streamName - stream name (file or input stream) used for error messages.
         */
        std::string streamName;

        /**
         * @brief traceLexing - variable available for verbosely debugging lexing logic
         * @note '%debug' must be specified in the '.lex' grammar file
         */
        bool traceLexing;
        /**
         * @brief traceParsing - variable available for verbosely debugging parsing logic
         * @note '%debug' must be specified in the '.biSIREN' grammar file
         */
        bool traceParsing;       


    }; // end of SIRENInterpreter class

} // namespace wasp
#endif // WASPSIRENINTERPRETER_H
