#ifndef WASP_DDILEXER_H
#define WASP_DDILEXER_H

// Flex expects the signature of yylex to be defined in the macro YY_DECL, and
// the C++ parser expects it to be declared. We can factor both as follows.

#ifndef YY_DECL

#define YY_DECL      wasp::DDIParser::token_type   wasp::DDILexerImpl::lex( \
      wasp::DDIParser::semantic_type* yylval,         \
             wasp::DDIParser::location_type* yylloc          \
                 )
#endif

#ifndef __FLEX_LEXER_H
#define yyFlexLexer DDIFlexLexer
#include "waspcore/FlexLexer.h"
#undef yyFlexLexer
#endif

#include "DDIParser.hpp"
#include "waspcore/wasp_node.h"
namespace wasp {

/** DDILexerImpl is a derived class to add some extra function to the scanner
 * class. Flex itself creates a class named yyFlexLexer, which is renamed using
 * macros to DDILexer. However we change the context of the generated
 * yylex() function to be contained within the DDILexerImpl class. This is required
 * because the yylex() defined in DDILexer has no parameters. */
class DDILexerImpl : public DDIFlexLexer
{
public:
    /** Create a new scanner object. The streams arg_yyin and arg_yyout default
     * to cin and cout, but that assignment is only made when initializing in
     * yylex(). */
    DDILexerImpl(class AbstractInterpreter& interpreter,
                 std::istream* arg_yyin = 0,
           std::ostream* arg_yyout = 0);

    /** Required for virtual functions */
    virtual ~DDILexerImpl();

    /** This is the main lexing function. It is generated by flex according to
     * the macro declaration YY_DECL above. The generated bison parser then
     * calls this virtual function to fetch new tokens. */
    virtual DDIParser::token_type lex(
       DDIParser::semantic_type* yylval,
       DDIParser::location_type* yylloc
       );
    
    /** Enable debug output (via arg_yyout) if compiled into the scanner. */
    void set_debug(bool b);
    /**
     * @brief rewind - rewind the last token (yyless(0))
     */
    void rewind();

    void capture_token(wasp::DDIParser::semantic_type* yylval,
                       wasp::NODE type);
private:
    class AbstractInterpreter & interpreter;
    std::size_t file_offset;
};

} // namespace wasp

#endif // WASP_DDILEXER_H

