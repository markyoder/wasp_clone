
#ifndef WASP_SONINTERPRETER_H
#define WASP_SONINTERPRETER_H

#include <string>
#include <fstream>
#include <istream>
#include <ostream>
#include <iostream>
#include <vector>
#include <map>
#include <memory>

#include "waspcore/Interpreter.h"
#include "waspcore/TreeNodePool.h"
/** The wasp namespace is used to encapsulate the three parser classes
 * wasp::SONParser, wasp::SONLexerImpl and wasp::SONInterpreter */
namespace wasp {

    /** The SONInterpreter class brings together all components. It creates an instance of
     * the SONParser and SONLexerImpl classes and connects them. Then the input stream is
     * fed into the lexer object and the parser gets it's token
     * sequence. Furthermore the driver object is available in the grammar rules as
     * a parameter. Therefore the driver class contains a reference to the
     * structure into which the parsed data is saved. 
     * 
     * @brief Parse a Standard Object Notation (SONInterpreter) file/stream
     * SONInterpreter currently supports the following grammar:
     * 
     * File : (object|array|keyedvalue)*
     * keyedvalue : primitive '=' primitive
     * object : tag ( '(' identifier ')' )? '{' members '}'
     * identifier : string | quoted_string
     * members : (object|array|keyedvalue)+
     * array : tag ( '(' identifier ')' )? '[' (objects|primitives|arrays)+ ']'
     * primitives : (integer|true|false|real|string|quoted_string)+
     * objects : object+
     */
    class SONInterpreter : public Interpreter<> {
    public:
        typedef std::shared_ptr<SONInterpreter> SharedPtr;
        SONInterpreter();
        SONInterpreter(std::ostream & err);
        virtual ~SONInterpreter();

        /** Invoke the lexer and parser for a stream.
         * @param in        input stream
         * @param sname     stream name for error messages
         * @return          true if successfully parsed
         */
        bool parseStream(std::istream& in,
                const std::string& sname = "stream input", std::size_t startLine=1u, std::size_t startColumn=1u);
        bool parse(std::istream &input, std::size_t startLine=1u, std::size_t startColumn=1u);
        /** Invoke the lexer and parser on an input string.
         * @param input     input string
         * @param sname     stream name for error messages
         * @return          true if successfully parsed
         */
        bool parseString(const std::string& input,
                const std::string& sname = "string stream", std::size_t startLine=1u, std::size_t startColumn=1u);
        /** Invoke the lexer and parser on a file. Use parse_stream with a
         * std::ifstream if detection of file reading errors is required.
         * @param filename  input file name
         * @return          true if successfully parsed
         */
        bool parseFile(const std::string& filename, std::size_t startLine=1u);

        void setSingleParse(bool s){singleParse = s;}
        bool isSingleParse()const{return singleParse;}

    public: // public variables
        /**
         * @brief lexer - current lexer instance
         */
        class SONLexerImpl* m_lexer;

        /**
         * @brief streamName - stream name (file or input stream) used for error messages.
         */
        std::string streamName;

        /**
         * @brief setStreamName sets the name of this stream and indicates whether the stream/name is a file[path]
         * @param name the name of the stream or file[path]
         * @param isFile [default=false] indicates whether the name is a file path
         */
        void setStreamName(const std::string & name, bool isFile=false)
        {streamName = name; mHasFile = isFile;}
        /**
         * @brief traceLexing - variable available for verbosely debugging lexing logic
         * @note '%debug' must be specified in the '.lex' grammar file
         */
        bool traceLexing;
        /**
         * @brief traceParsing - variable available for verbosely debugging parsing logic
         * @note '%debug' must be specified in the '.bison' grammar file
         */
        bool traceParsing;       

        /**
         * @brief hasFile indicates whether this parser's stream name is a file path
         * @return
         */
        bool hasFile()const{return mHasFile;}
    private: // private variables

        /**
         * @brief singleParse - indicates a single component is to be parsed
         * When true, only a single rule will be consumed
         * Default is false;
         */
        bool singleParse;

    private: // private methods

        /**
         * @brief mHasFile indicates whether this parser was instantiated via a file
         */
        bool mHasFile;
    }; // end of SONInterpreter class

} // namespace wasp
#endif // WASPSONINTERPRETER_H
