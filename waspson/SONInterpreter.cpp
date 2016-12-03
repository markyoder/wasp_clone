#include "waspson/SONInterpreter.h"
#include <fstream>
#include <sstream>
#include <ostream>

#include "SONLexer.h"
#include <waspson/son_config.h>
namespace wasp {

SONInterpreter::SONInterpreter()
    :Interpreter(),
    traceLexing(false),
    traceParsing(false),
    singleParse(false),
    mHasFile(false)
{
}
SONInterpreter::SONInterpreter(std::ostream & err)
    : Interpreter(err),
    traceLexing(false),
    traceParsing(false),    
    singleParse(false),
    mHasFile(false)
{
}
SONInterpreter::~SONInterpreter()
{
}

bool SONInterpreter::parse(std::istream& in, std::size_t startLine, std::size_t startColumn)
{
    return parseStream(in, hasFile() ? streamName : "stream input" , startLine,startColumn);
}

bool SONInterpreter::parseStream(std::istream& in
                                 , const std::string& sname
                                 , std::size_t start_line
                                 , std::size_t start_column)
{
    return parse_impl<SONLexerImpl
            ,SONParser
            ,SONInterpreter>(m_lexer
                ,in
                ,sname
                ,start_line
                ,start_column);
}

bool SONInterpreter::parseFile(const std::string &filename, std::size_t line)
{
    std::ifstream in(filename.c_str());
    if (!in.good()){
        error_stream()<<"file '"<<filename<<"' is either inaccessible or doesn't exist! Unable to read."<<std::endl;
        return false;
    }
    mHasFile = true;
    return parseStream(in, filename, line);
}

bool SONInterpreter::parseString(const std::string &input, const std::string& sname, std::size_t startLine, std::size_t startColumn)
{
    std::istringstream iss(input);
    return parseStream(iss, sname,startLine,startColumn);
}
} // namespace wasp
