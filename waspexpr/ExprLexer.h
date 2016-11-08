#ifndef WASP_EXPRLEXER_H
#define WASP_EXPRLEXER_H


// Flex expects the signature of yylex to be defined in the macro YY_DECL, and
// the C++ parser expects it to be declared. We can factor both as follows.

#ifndef YY_DECL

#define YY_DECL      wasp::ExprParser::token_type   wasp::ExprLexerImpl::lex( \
      wasp::ExprParser::semantic_type* yylval,         \
             wasp::ExprParser::location_type* yylloc          \
                 )
#endif

#ifndef __FLEX_LEXER_H
#define yyFlexLexer ExprFlexLexer
#include "waspcore/FlexLexer.h"
#undef yyFlexLexer
#endif

#include "ExprParser.hpp"
#include "waspcore/TokenPool.h"
namespace wasp {

/** ExprLexerImpl is a derived class to add some extra function to the scanner
 * class. Flex itself creates a class named yyFlexLexer, which is renamed using
 * macros to ExprLexer. However we change the context of the generated
 * yylex() function to be contained within the ExprLexerImpl class. This is required
 * because the yylex() defined in ExprLexer has no parameters. */
class ExprLexerImpl : public ExprFlexLexer
{
public:
    /** Create a new scanner object. The streams arg_yyin and arg_yyout default
     * to cin and cout, but that assignment is only made when initializing in
     * yylex().
     * The token pool is the storage class
    */
    ExprLexerImpl(TokenPool<> & token_data,
            std::istream* arg_yyin = 0,
           std::ostream* arg_yyout = 0);

    /** Required for virtual functions */
    virtual ~ExprLexerImpl();

    /** This is the main lexing function. It is generated by flex according to
     * the macro declaration YY_DECL above. The generated biExpr parser then
     * calls this virtual function to fetch new tokens. */
    virtual ExprParser::token_type lex(
       ExprParser::semantic_type* yylval,
       ExprParser::location_type* yylloc
       );
    
    /** Enable debug output (via arg_yyout) if compiled into the scanner. */
    void set_debug(bool b);
    /**
     * @brief rewind - rewind the last token (yyless(0))
     */
    void rewind();    
    /* import the parser's token type into a local typedef */
    typedef wasp::ExprParser::token_type token_type;
    void capture_token(wasp::ExprParser::semantic_type* yylval,
                       token_type type);

    TokenPool<> & m_token_data;
private:
    size_t file_offset;

};

} // namespace wasp

#endif // WASP_EXPRLEXER_H

