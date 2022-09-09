%top{
/* This disables inclusion of unistd.h, which is not available under Visual C++
 * on Win32. The C++ scanner uses STL streams instead. */
#define YY_NO_UNISTD_H

}
%{ /*** C/C++ Declarations ***/

#include <string>
#include <sstream>
#include "HITLexer.h"
#include "HITInterpreter.h"

/* import the parser's token type into a local typedef */
typedef wasp::HITParser::token token;
typedef wasp::HITParser::token_type token_type;

/* By default yylex returns int, we use token_type. Unfortunately yyterminate
 * by default returns 0, which is not of token_type. */
#define yyterminate() return token::END

%}

 /*** Flex Declarations and Options ***/

 /* enable c++ scanner class generation */
%option c++

%option prefix="HIT"
%option outfile="HITLexer.cpp"


 /* enable scanner to generate debug output. disable this for release
 * versions. */
 /*%option debug*/

 /* no support for include files is planned */
%option yywrap nounput

 /* enables the use of start condition stacks */
%option stack
%s object
%s array
%x lbracket
%x file_include

INTEGER [0-9]+([eE]\+?[0-9]+)?
EXPONENT [eE][\+\-]?{INTEGER}
REAL {INTEGER}?\.{INTEGER}{EXPONENT}?|{INTEGER}\.({INTEGER}{EXPONENT}?)?|{INTEGER}\.?[eE]\-{INTEGER}

DOUBLE_QUOTED_STRING \"([^\"\n])*\"
SINGLE_QUOTE '
UNICODE [^\x00-\x7F]+
COMMENT #([^\n]|{UNICODE})*

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
OBJECT_NAME [^" ""."\n\[\]][^" "\n\[\]\=\#\&]*
SUBSTITUTION_STRING \$\{[^\"\=]*\}
CONVENTIONAL_STRING [^ \'\"\=\n\t\r\[\]\#\&\;]+
ARRAY_MEMBER_STRING [^ \'\"\=\n\t\r\#\&\;]+
STRING       {SUBSTITUTION_STRING}|{CONVENTIONAL_STRING}
ARRAY_STRING {SUBSTITUTION_STRING}|{ARRAY_MEMBER_STRING}
RBRACKET \]
SEMICOLON ;
TOP_OBJECT_TERM \[" "*\]
SUB_OBJECT_TERM \[" "*\.\.\/" "*\]
OBJECT_TERM {TOP_OBJECT_TERM}|{SUB_OBJECT_TERM}
DOT_SLASH \.\/
INCLUDE_PATH [^ \t\n][^\n#\[]*


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
 /*** BEGIN EXAMPLE - Change the HIT lexer rules below ***/


{ASSIGN} {
    capture_token(yylval,wasp::ASSIGN);
    return token::ASSIGN;
}
<array>{SEMICOLON} {
    capture_token(yylval,wasp::SEMICOLON);
    return token::SEMICOLON;
}
<object>{OBJECT_TERM} {
    yy_pop_state();
    capture_token(yylval,wasp::OBJECT_TERM);
    return token::OBJECT_TERM;
}
<INITIAL,object>{SINGLE_QUOTE} {
    yy_push_state(array);
    capture_token(yylval,wasp::QUOTE);
    return token::QUOTE;
}
<array>{SINGLE_QUOTE} {
    yy_pop_state();
    capture_token(yylval,wasp::QUOTE);
    return token::QUOTE;
}
<INITIAL,object>{LBRACKET} {
    yy_push_state(lbracket);
    capture_token(yylval,wasp::LBRACKET);
    return token::LBRACKET;
}
<lbracket>{DOT_SLASH} {
    capture_token(yylval,wasp::DOT_SLASH);
    return token::DOT_SLASH;
}
<lbracket>{OBJECT_NAME} {
    capture_token(yylval,wasp::STRING);
    return token::STRING;
}
<lbracket>{RBRACKET} {
    yy_pop_state();
    yy_push_state(object);
    capture_token(yylval,wasp::RBRACKET);
    return token::RBRACKET;
}
<INITIAL,object,array>{INTEGER} {
    capture_token(yylval,wasp::INTEGER);
    return token::INTEGER;
}

<INITIAL,object,array>{REAL} {
    capture_token(yylval,wasp::REAL);
    return token::REAL;
}
 /* gobble up white-spaces */
<*>[ \t\r]+ {
    yylloc->step();
}

 /* gobble up end-of-lines */
\n {
    yylloc->lines(yyleng); yylloc->step();
    interpreter.push_line_offset(file_offset-yyleng);
}
{COMMENT} {
    capture_token(yylval,wasp::COMMENT);
    return token::COMMENT;
}
!include {
    yy_push_state(file_include);
    capture_token(yylval,wasp::FILE);
    return token::FILE;
}
<file_include>{INCLUDE_PATH} {
    // file includes grab everyting starting after '!include' to
    // either a newline '\n' or a comment '#'
    yy_pop_state();
    capture_token(yylval,wasp::STRING);
    return token::STRING;
}
<INITIAL,object>{STRING} {
    capture_token(yylval,wasp::STRING);
    return token::STRING;
}
<INITIAL,object,array>{DOUBLE_QUOTED_STRING} {
    capture_token(yylval,wasp::QUOTED_STRING);
    return token::QSTRING;
}
<array>{ARRAY_STRING} {
    capture_token(yylval,wasp::STRING);
    return token::STRING;
}

 /* pass all other characters up to HIT*/
<*>. {
    return static_cast<token_type>(*yytext);
}

 /*** END EXAMPLE - Change the HIT lexer rules above ***/

%% /*** Additional Code ***/

namespace wasp {

HITLexerImpl::HITLexerImpl(
                AbstractInterpreter & interpreter,
                std::istream* in,
                std::ostream* out)
    : HITFlexLexer(in, out)
    , interpreter(interpreter)
    , file_offset(0)
{
}

HITLexerImpl::~HITLexerImpl()
{
}

void HITLexerImpl::set_debug(bool b)
{
    yy_flex_debug = b;
}
void HITLexerImpl::rewind()
{
    yyin.seekg(-yyleng,std::ios_base::cur);
    yyless(0);
}
void HITLexerImpl::capture_token(
        wasp::HITParser::semantic_type* yylval
        ,wasp::NODE type)
{
    std::size_t offset = file_offset - yyleng;
    yylval->token_index = interpreter.token_count();
    interpreter.push_token(yytext,type,offset);
}
} // end of namespace

/* This implementation of HITFlexLexer::yylex() is required to fill the
 * vtable of the class HITFlexLexer. We define the scanner's main yylex
 * function via YY_DECL to reside in the HITLexerImpl class instead. */

#ifdef yylex
#undef yylex
#endif

int HITFlexLexer::yylex()
{    
    return 0;
}

/* When the scanner receives an end-of-file indication from YY_INPUT, it then
 * checks the yywrap() function. If yywrap() returns false (zero), then it is
 * assumed that the function has gone ahead and set up `yyin' to point to
 * another input file, and scanning continues. If it returns true (non-zero),
 * then the scanner terminates, returning 0 to its caller. */

int HITFlexLexer::yywrap()
{
    return 1;
}
