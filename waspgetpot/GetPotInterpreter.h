#ifndef WASP_GETPOTINTERPRETER_H
#define WASP_GETPOTINTERPRETER_H
#include "waspcore/TreeNodePool.h"
#include "waspcore/Interpreter.h"

#include <cstdint>
#include <string>
#include <fstream>
#include <iostream>

#include "waspgetpot/GetPotParser.hpp"

namespace wasp
{
// How many input node type's (section, value, etc.) in a GetPot file
typedef std::uint8_t GetPotNodeType_t;

// How many input token type's (word, int, real, comma, etc.) in a GetPot file
typedef std::uint8_t GetPotTokenType_t;

// How many bytes in a file
typedef std::uint8_t  GetPotTinyFileSize_t;
typedef std::uint16_t GetPotMediumFileSize_t;
typedef std::uint32_t GetPotFileSize_t;
typedef std::uint64_t GetPotLargeFileSize_t;

// How many tokens in a file (5 reals, 100 ints, 50 words, etc.)
typedef std::uint8_t  GetPotTinyTokenSize_t;
typedef std::uint16_t GetPotMediumTokenSize_t;
typedef std::uint32_t GetPotTokenSize_t;
typedef std::uint64_t GetPotLargeTokenSize_t;

// Tiny file TokenPool (less than 256 bytes)
typedef TokenPool<
    // Token type
    GetPotTokenType_t,
    // Max number of token
    GetPotTinyTokenSize_t,
    // Max number of bytes in the file
    GetPotTinyFileSize_t>
    GetPotTinyTokenPool;

// Medium file TokenPool (less than 65k bytes)
typedef TokenPool<
    // Token type
    GetPotTokenType_t,
    // Max number of token
    GetPotMediumTokenSize_t,
    // Max number of bytes in the file
    GetPotMediumFileSize_t>
    GetPotMediumTokenPool;

// Regular file TokenPool (less than 4b bytes)
typedef TokenPool<
    // Token type
    GetPotTokenType_t,
    // Max number of token
    GetPotTokenSize_t,
    // Max number of bytes in the file
    GetPotFileSize_t>
    GetPotTokenPool;

// Large file TokenPool (greater than 4b bytes)
typedef TokenPool<
    // Token type
    GetPotTokenType_t,
    // Max number of token
    GetPotLargeTokenSize_t,
    // Max number of bytes in the file
    GetPotLargeFileSize_t>
    GetPotLargeTokenPool;

// Regular NodePool storage
typedef TreeNodePool<
    // Node type
    GetPotNodeType_t,
    // Max number of nodes in the file
    std::uint32_t,
    // Regular TokenPool
    GetPotTokenPool>
    GetPotNodePool;

template<class S = GetPotNodePool>
class GetPotInterpreter : public Interpreter<S>
{
  public:
    GetPotInterpreter(std::ostream& error_stream = std::cerr);
    ~GetPotInterpreter();

    /**
     * @brief parse parser the given input stream
     * @param input the stream of the input data
     * @param startLine the first line of the input stream
     * @param startColumn the first column of the input stream
     * @return true, iff no input processing errors were encountered
     */
    bool parse(std::istream& input,
               std::size_t   start_line   = 1u,
               std::size_t   start_column = 1u);
    bool parseStream(std::istream& input,
               const std::string& name,
               std::size_t   start_line   = 1u,
               std::size_t   start_column = 1u)
    {
        Interpreter<S>::stream_name() = name;
        return parse(input, start_line, start_column);
    }
    bool parseFile(const std::string& filename, size_t startLine = 1u);
};
#include "waspgetpot/GetPotInterpreter.i.h"
typedef GetPotInterpreter<> DefaultGetPotInterpreter;
}  // end of namespace
#endif
