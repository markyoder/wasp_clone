
#ifndef WASP_JSONINTERPRETER_H
#define WASP_JSONINTERPRETER_H

#include <cstddef>
#include <string>
#include <fstream>
#include <istream>
#include <ostream>
#include <iostream>
#include <vector>
#include <map>
#include <memory>

#include "waspcore/TreeNodePool.h"
#include "waspcore/TokenPool.h"
#include "waspcore/Object.h"
#include "waspjson/JSONParser.hpp"
#include "waspcore/Interpreter.h"
#include "waspcore/wasp_node.h"
#include "waspcore/decl.h"

/** The wasp namespace is used to encapsulate the three parser classes
 * wasp::JSONParser, wasp::JSONLexerImpl and wasp::JSONInterpreter */
namespace wasp
{
/** The JSONInterpreter class brings together all components. It creates an
 * instance of
 * the JSONParser and JSONLexerImpl classes and connects them. Then the input
 * stream is
 * fed into the lexer object and the parser gets it's token
 * sequence. Furthermore the driver object is available in the grammar rules as
 * a parameter. Therefore the driver class contains a reference to the
 * structure into which the parsed data is saved.
 *
 * @brief Parse a Standard Object Notation (JSONInterpreter) file/stream
 * www.json.org for specications
 */
template<class S = TreeNodePool<
             unsigned short,
             unsigned short,
             TokenPool<unsigned short, unsigned short, unsigned short>>>
class WASP_PUBLIC JSONInterpreter : public Interpreter<S>
{
  public:
    typedef S                                Storage_type;
    typedef std::shared_ptr<JSONInterpreter> SharedPtr;
    JSONInterpreter();
    JSONInterpreter(std::ostream& err);
    virtual ~JSONInterpreter();

    /** Invoke the lexer and parser for a stream.
     * @param in        input stream
     * @param sname     stream name for error messages
     * @return          true if successfully parsed
     */
    bool parseStream(std::istream&      in,
                     const std::string& sname       = "stream input",
                     size_t             startLine   = 1u,
                     size_t             startColumn = 1u);
    bool
    parse(std::istream& input, size_t startLine = 1u, size_t startColumn = 1u);
    /** Invoke the lexer and parser on an input string.
     * @param input     input string
     * @param sname     stream name for error messages
     * @return          true if successfully parsed
     */
    bool parseString(const std::string& input,
                     const std::string& sname       = "string stream",
                     size_t             startLine   = 1u,
                     size_t             startColumn = 1u);
    /** Invoke the lexer and parser on a file. Use parse_stream with a
     * std::ifstream if detection of file reading errors is required.
     * @param filename  input file name
     * @return          true if successfully parsed
     */
    bool parseFile(const std::string& filename, size_t startLine = 1u);

    void setSingleParse(bool s) { singleParse = s; }
    bool                     single_parse() const { return singleParse; }

    bool generate_object(DataObject& obj, std::ostream& err) const;

  public:  // public variables
    /**
     * @brief setStreamName sets the name of this stream and indicates whether
     * the stream/name is a file[path]
     * @param name the name of the stream or file[path]
     * @param isFile [default=false] indicates whether the name is a file path
     */
    void setStreamName(const std::string& name, bool isFile = false)
    {
        Interpreter<S>::stream_name() = name;
        mHasFile                      = isFile;
    }
    /**
     * @brief traceLexing - variable available for verbosely debugging lexing
     * logic
     * @note '%debug' must be specified in the '.lex' grammar file
     */
    bool traceLexing;
    /**
     * @brief traceParsing - variable available for verbosely debugging parsing
     * logic
     * @note '%debug' must be specified in the '.bison' grammar file
     */
    bool traceParsing;

    /**
     * @brief hasFile indicates whether this parser's stream name is a file path
     * @return
     */
    bool hasFile() const { return mHasFile; }

  private:  // private variables
    /**
     * @brief singleParse - indicates a single component is to be parsed
     * When true, only a single rule will be consumed
     * Default is false;
     */
    bool singleParse;
    /**
     * @brief mHasFile indicates whether this parser was instantiated via a file
     */
    bool mHasFile;

  private:  // private methods
    // TODO these generate methods do not need to live in the interpreter class

    bool generate_object_internal(const NodeView& view,
                                  DataObject&            obj,
                                  std::ostream&          err) const;
    bool generate_array_internal(const NodeView& view,
                                 DataArray&             obj,
                                 std::ostream&          err) const;
    bool generate_value_internal(const NodeView& value_view,
                                 wasp::Value&           value,
                                 std::ostream&          err) const;
};  // end of JSONInterpreter class
#include "waspjson/JSONInterpreter.i.h"
}  // namespace wasp
#endif  // WASPJSONINTERPRETER_H
