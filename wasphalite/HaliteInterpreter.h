
#ifndef WASP_HALITEINTERPRETER_H
#define WASP_HALITEINTERPRETER_H

#include <string>
#include <fstream>
#include <istream>
#include <ostream>
#include <iostream>

#include "waspcore/Interpreter.h"
#include "wasphalite/SubStringIndexer.h"

namespace wasp {

    template<class S = TreeNodePool<unsigned short, unsigned short
                                    ,TokenPool<unsigned short,unsigned short, unsigned short>> >
    class HaliteInterpreter : public Interpreter<S> {
    public:
        typedef S Storage_type;
        typedef std::shared_ptr<HaliteInterpreter> SharedPtr;
        HaliteInterpreter();
        HaliteInterpreter(std::ostream & err);
        virtual ~HaliteInterpreter();

        /** Invoke the lexer and parser for a stream.
         * @param in        input stream
         * @param sname     stream name for error messages
         * @return          true if successfully parsed
         */
        bool parseStream(std::istream& in,
                const std::string& sname = "stream input", size_t startLine=1u, size_t startColumn=1u);
        bool parse(std::istream &input, size_t startLine=1u, size_t startColumn=1u);
        /** Invoke the lexer and parser on an input string.
         * @param input     input string
         * @param sname     stream name for error messages
         * @return          true if successfully parsed
         */
        bool parseString(const std::string& input,
                const std::string& sname = "string stream", size_t startLine=1u, size_t startColumn=1u);
        /** Invoke the lexer and parser on a file. Use parse_stream with a
         * std::ifstream if detection of file reading errors is required.
         * @param filename  input file name
         * @return          true if successfully parsed
         */
        bool parseFile(const std::string& filename, size_t startLine=1u);


    private:

        bool parse_content(std::istream& in);

        bool parse_line(const std::string & line );

        void capture_leaf(const std::string& node_name
                          , size_t node_type
                          , const std::string& data
                          , size_t token_type
                          , size_t file_offset);
    public: // public variables

        /**
         * @brief setStreamName sets the name of this stream and indicates whether the stream/name is a file[path]
         * @param name the name of the stream or file[path]
         * @param isFile [default=false] indicates whether the name is a file path
         */
        void setStreamName(const std::string & name, bool isFile=false)
        {Interpreter<S>::stream_name() = name; m_has_file = isFile;}


        /**
         * @brief hasFile indicates whether this parser's stream name is a file path
         * @return
         */
        bool hasFile()const{return m_has_file;}
    private: // private variables

        /**
         * @brief attribute_start_delim attribute substitution declarator
         */
        std::string m_attribute_start_delim;
        /**
         * @brief attribute_end_delim attribute substitution terminator
         */
        std::string m_attribute_end_delim;

        size_t m_current_line_count;
        size_t m_file_offset;
    private: // private methods

        /**
         * @brief mHasFile indicates whether this parser was instantiated via a file
         */
        bool m_has_file;
    }; // end of HaliteInterpreter class
#include "wasphalite/HaliteInterpreter.i.h"
} // namespace wasp
#endif // WASPHaliteIntERPRETER_H
