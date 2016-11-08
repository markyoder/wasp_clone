%top{
/* This disables inclusion of unistd.h, which is not available under Visual C++
 * on Win32. The C++ scanner uses STL streams instead. */
#define YY_NO_UNISTD_H

}
%{ /*** C/C++ Declarations ***/

#include <string>
#include <sstream>
#include "ExprLexer.h"

/* import the parser's token type into a local typedef */
typedef wasp::ExprParser::token token;
typedef wasp::ExprParser::token_type token_type;

/* By default yylex returns int, we use token_type. Unfortunately yyterminate
 * by default returns 0, which is not of token_type. */
#define yyterminate() return token::END

%}

 /*** Flex Declarations and Options ***/

 /* enable c++ scanner class generation */
%option c++

%option prefix="Expr"
%option outfile="ExprLexer.cpp"


 /* enable scanner to generate debug output. disable this for release
 * versions. */
 /*%option debug*/

 /* no support for include files is planned */
%option yywrap nounput

 /* enables the use of start condition stacks */

INT [0-9]+([eE]\+?[0-9]+)?
EXPONENT [eE][\+\-]?{INT}
REAL {INT}?\.{INT}{EXPONENT}?|{INT}\.({INT}{EXPONENT}?)?|{INT}\.?[eE]\-{INT}

STRING [A-Za-z_]((\-)?[A-Za-z0-9\._/])*



 /* This string does not allow special characters '-','/'
 *  and should only occur in the context of reference
 */
LESSER_STRING [A-Za-z_][A-Za-z0-9_]*

DOUBLE_QUOTED_STRING \"([^\"\n])*\"
COMMENT #[^\n]*|%[^\n]*

LTE <=
GTE >=
LT <
GT >
BANG !
EQ ==
EXPONENT_OP \^
ASSIGN =
NEQ \!=
AND &&
OR \|\|
LBRACKET \[
RBRACKET \]
COMMA ,


 /* The following paragraph suffices to track locations accurately. Each time
 * yylex is invoked, the begin position is moved onto the end position. */
%{
#define YY_USER_ACTION  yylloc->columns(yyleng); file_offset+=yyleng;
%}

%% /*** Regular Expressions Part ***/

 /* code to place at the beginning of yylex() */
%{
    // reset location
    yylloc->step();
%}
 /*** BEGIN EXAMPLE - Change the Expr lexer rules below ***/
{INT} {
    capture_token(yylval,token::INTEGER);
    return token::INTEGER;
}
{REAL} {
    capture_token(yylval,token::REAL);
    return token::REAL;
}
{LTE} {
    capture_token(yylval,token::LTE);
    return token::LTE;
}
{GTE}  {
    capture_token(yylval,token::GTE);
    return token::GTE;
}
{LT} {
    capture_token(yylval,token::LT);
    return token::LT;
}
{GT}  {
    capture_token(yylval,token::GT);
    return token::GT;
}
{EQ} {
    capture_token(yylval,token::EQ);
    return token::EQ;
}
{BANG} {
    capture_token(yylval,token::BANG);
    return token::BANG;
}
{ASSIGN} {
    capture_token(yylval,token::ASSIGN);
    return token::ASSIGN;
}
{NEQ} {
    capture_token(yylval,token::NEQ);
    return token::NEQ;
}
{AND} {
    capture_token(yylval,token::AND);
    return token::AND;
}
{OR} {
    capture_token(yylval,token::OR);
    return token::OR;
}
{LBRACKET} {
    capture_token(yylval,token::LBRACKET);
    return token::LBRACKET;
}
{RBRACKET} {
    capture_token(yylval,token::RBRACKET);
    return token::RBRACKET;
}
{EXPONENT_OP} {
    capture_token(yylval,token::EXPONENT);
    return token::EXPONENT;
}
\* {
    capture_token(yylval,token::MULTIPLY);
    return token::MULTIPLY;
}
\/ {
  capture_token(yylval,token::DIVIDE);
  return token::DIVIDE;
}
\+ {
  capture_token(yylval,token::PLUS);
  return token::PLUS;
}
- {
    capture_token(yylval,token::MINUS);
    return token::MINUS;
}
\( {
  capture_token(yylval,token::LPAREN);
  return token::LPAREN;
}
\) {
 capture_token(yylval,token::RPAREN);
 return token::RPAREN;
}
 /* gobble up white-spaces */
[ \t\r]+ {
    yylloc->step();
}

 /* gobble up end-of-lines */
\n {
    yylloc->lines(yyleng); yylloc->step();
    size_t offset = yyin->tellg();
    offset-=yyleng;
    m_token_data.push_line(offset);
}
{STRING} {
    capture_token(yylval,token::STRING);
//    yylval->stringVal = new std::string(yytext, yyleng);
    return token::STRING;
}

{COMMENT} {
//    yylval->stringVal = new std::string(yytext,yyleng);
    capture_token(yylval,token::COMMENT);
    return token::COMMENT;
}

 /* pass all other characters up to Expr*/
. {
    return static_cast<token_type>(*yytext);
}

 /*** END EXAMPLE - Change the Expr lexer rules above ***/

%% /*** Additional Code ***/

namespace wasp {

ExprLexerImpl::ExprLexerImpl(
                TokenPool<> & token_data,
                std::istream* in,
                std::ostream* out)
    : ExprFlexLexer(in, out)
    , m_token_data(token_data)
    , file_offset(0)
{
}

ExprLexerImpl::~ExprLexerImpl()
{
}

void ExprLexerImpl::set_debug(bool b)
{
    yy_flex_debug = b;
}
void ExprLexerImpl::rewind()
{
    yyin->seekg(-yyleng,std::ios_base::cur);
    yyless(0);
}
void ExprLexerImpl::capture_token(
        wasp::ExprParser::semantic_type* yylval
        ,token_type type)
{
    size_t offset = file_offset - yyleng;
    yylval->node_index = m_token_data.size();
    m_token_data.push(yytext,type,offset);
}
} // end of namespace

/* This implementation of ExprFlexLexer::yylex() is required to fill the
 * vtable of the class ExprFlexLexer. We define the scanner's main yylex
 * function via YY_DECL to reside in the ExprLexerImpl class instead. */

#ifdef yylex
#undef yylex
#endif

int ExprFlexLexer::yylex()
{    
    return 0;
}

/* When the scanner receives an end-of-file indication from YY_INPUT, it then
 * checks the yywrap() function. If yywrap() returns false (zero), then it is
 * assumed that the function has gone ahead and set up `yyin' to point to
 * another input file, and scanning continues. If it returns true (non-zero),
 * then the scanner terminates, returning 0 to its caller. */

int ExprFlexLexer::yywrap()
{
    return 1;
}
