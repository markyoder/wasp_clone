
#ifndef WASP_VIINTERPRETER_H
#define WASP_VIINTERPRETER_H

#include <cstddef>
#include <cstdint>
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

#include "waspvii/VIIParser.hpp"
#include "waspcore/Interpreter.h"
#include "waspcore/Definition.h"

#include "waspcore/decl.h"
#include "waspcore/location.hh"

/** The wasp namespace is used to encapsulate the three parser classes
 * wasp::VIIParser, wasp::VIILexerImpl and wasp::VIIInterpreter */
namespace wasp
{

// How many input node type's (section, value, etc.) in a VII file
typedef std::uint8_t VIINodeType_t;

// How many input token type's (word, int, real, comma, etc.) in a VII file
typedef std::uint8_t VIITokenType_t;

// How many bytes in a file
typedef std::uint8_t  VIITinyFileSize_t;
typedef std::uint16_t VIIMediumFileSize_t;
typedef std::uint32_t VIIFileSize_t;
typedef std::uint64_t VIILargeFileSize_t;

// How many tokens in a file (5 reals, 100 ints, 50 words, etc.)
typedef std::uint8_t  VIITinyTokenSize_t;
typedef std::uint16_t VIIMediumTokenSize_t;
typedef std::uint32_t VIITokenSize_t;
typedef std::uint64_t VIILargeTokenSize_t;

// Tiny file TokenPool (less than 256 bytes)
typedef TokenPool<
    // Token type
    VIITokenType_t,
    // Max number of token
    VIITinyTokenSize_t,
    // Max number of bytes in the file
    VIITinyFileSize_t>
    VIITinyTokenPool;

// Medium file TokenPool (less than 65k bytes)
typedef TokenPool<
    // Token type
    VIITokenType_t,
    // Max number of token
    VIIMediumTokenSize_t,
    // Max number of bytes in the file
    VIIMediumFileSize_t>
    VIIMediumTokenPool;

// Regular file TokenPool (less than 4b bytes)
typedef TokenPool<
    // Token type
    VIITokenType_t,
    // Max number of token
    VIITokenSize_t,
    // Max number of bytes in the file
    VIIFileSize_t>
    VIITokenPool;

// Large file TokenPool (greater than 4b bytes)
typedef TokenPool<
    // Token type
    VIITokenType_t,
    // Max number of token
    VIILargeTokenSize_t,
    // Max number of bytes in the file
    VIILargeFileSize_t>
    VIILargeTokenPool;

// Regular NodePool storage
typedef TreeNodePool<
    // Node type
    VIINodeType_t,
    // Max number of nodes in the file
    std::uint32_t,
    // Regular TokenPool
    VIITokenPool>
    VIINodePool;

template<class S = VIINodePool>
class WASP_PUBLIC VIInterpreter : public Interpreter<S>
{
  public:
    typedef S                              Storage_type;
    typedef std::shared_ptr<VIInterpreter> SharedPtr;
    typedef Interpreter<S>                 Super;
    VIInterpreter();
    VIInterpreter(std::ostream& err);
    virtual ~VIInterpreter();

    bool load_document(size_t node_index, const std::string& path);
    VIInterpreter* document_parent() const {return m_parent;}

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

    virtual bool process_staged_node(size_t& new_staged_index,
                                    const std::string& stage_name,
                                    size_t node_index,
                                    const location& loc,
                                    std::ostream& err);
    /**
     * Processes the document command statement
     * The command statement is composed of a document part
     * (value, forward slash, comment, declarator or keyed-balue, comma
     *  or semicolon). Depending on the state of the parse these parts
     * are captured into the parse-tree differently. 
     * If the part is aliased to an index or even-or-odd, etc, the 
     * resulting staged node is named appropriately as dictated by the 
     * definition.
     * @param new_staged_index the index of the newly staged node to be assigned
     * @param node_index the index of the part being processed
     *                  This enables access to name, type, etc. 
     * @param loc the location of the part being processed
     *                  This facilitates error reporting
     * @param err stream for reporting errors 
     * @return true, iff no error occurred
     */
    bool process_document_command(size_t& new_staged_index, 
                                size_t node_index, 
                                const location& loc,
                                std::ostream& err);
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

    const AbstractDefinition* definition() const;
    AbstractDefinition*       definition();
    virtual void set_current_definition(AbstractDefinition* current)
    {
        wasp_require(current);
        m_current = current;
    }

    AbstractDefinition::SP definition_store() { return m_definition; }
    void set_definition_store(AbstractDefinition::SP store)
    {
        m_definition = store;
        m_current    = store.get();
    }
    /**
     * Override from parent class in order to manage definition selection.
     * Pushes the new definition with the given node_name
     */
    virtual size_t push_staged(size_t                     node_type,
                               const std::string&         node_name,
                               const std::vector<size_t>& child_indices);
    /**
     * Override from parent class in order to manage non-decorative child counts
     * for the purpose of index'd aliasing
     */ 
    virtual size_t push_staged_child(size_t child_index);
    /**
     * Override from parent class in order to manage definition selection
     * Pops the existing definition
     */
    virtual size_t commit_staged(size_t stage_index);

  private:  // private variables
    /**
     * @brief singleParse - indicates a single component is to be parsed
     * When true, only a single rule will be consumed
     * Default is false;
     */
    bool singleParse;
    VIInterpreter* m_parent;

  private:  // private methods
    AbstractDefinition::SP m_definition;
    AbstractDefinition*    m_current;
    /**
     * @brief mHasFile indicates whether this parser was instantiated via a file
     */
    bool mHasFile;
};  // end of VIIInterpreter class
#include "waspvii/VIInterpreter.i.h"

typedef VIInterpreter<> DefaultVIInterpreter;
}  // namespace wasp
#endif  // WASPVIIINTERPRETER_H
