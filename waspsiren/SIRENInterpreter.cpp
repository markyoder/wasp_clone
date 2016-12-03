#include "waspsiren/SIRENInterpreter.h"
#include <fstream>
#include <sstream>
#include <ostream>

#include "SIRENLexer.h"
namespace wasp {

SIRENInterpreter::SIRENInterpreter()
    :Interpreter(),
    traceLexing(false),
    traceParsing(false)
{
}
SIRENInterpreter::SIRENInterpreter(std::ostream & err)
    : Interpreter(err),
    traceLexing(false),
    traceParsing(false)
{
}
SIRENInterpreter::~SIRENInterpreter()
{
}

bool SIRENInterpreter::parse(std::istream& in, std::size_t startLine, std::size_t startColumn)
{
    return parseStream(in, "selection statement" , startLine,startColumn);
}

bool SIRENInterpreter::parseStream(std::istream& in
                                 , const std::string& sname
                                 , std::size_t start_line
                                 , std::size_t start_column)
{
    return parse_impl<SIRENLexerImpl
            ,SIRENParser
            ,SIRENInterpreter>(m_lexer
                ,in
                ,sname
                ,start_line
                ,start_column);
}

bool SIRENInterpreter::parseString(const std::string &input, const std::string& sname, std::size_t startLine, std::size_t startColumn)
{
    std::istringstream iss(input);
    return parseStream(iss, sname,startLine,startColumn);
}
} // namespace wasp
