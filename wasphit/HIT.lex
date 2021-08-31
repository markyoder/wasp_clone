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
%s execution_unit
%s object
%s array
%x lbracket

INTEGER [0-9]+([eE]\+?[0-9]+)?
EXPONENT [eE][\+\-]?{INTEGER}
REAL {INTEGER}?\.{INTEGER}{EXPONENT}?|{INTEGER}\.({INTEGER}{EXPONENT}?)?|{INTEGER}\.?[eE]\-{INTEGER}




 /* This string does not allow special characters '-','/'
 *  and should only occur in the context of reference
 */
LESSER_STRING [A-Za-z_][A-Za-z0-9_]*

DOUBLE_QUOTED_STRING \"([^\"\n])*\"
SINGLE_QUOTE '
UNICODE [^\x00-\x7F]+
COMMENT #([^\n]|{UNICODE})*

 /*
 * The 'execution unit' is a rebranded SCALE sequence construct
 * where the sequence started with the unit_start rule below
 * and terminated with unit_end rule below.
 * We reproduce it here to account for the input construct                                                                                                                        
 * while in transition...
 */
EXECUTION_UNIT_START ^=
EXECUTION_UNIT_END ^[Ee][Nn][Dd]
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
OBJECT_NAME [^" ""."\n\[\]][^" "\n\[\]]*
STRING (\$\{([^\"\n\t\r])*\})|([^" "\'\"\=\n\t\r\[\]\#\;]+)
ARRAY_STRING (\$\{([^\"\n\t\r])*\})|([^ \'\n\t\r\#\;]+)
RBRACKET \]
SEMICOLON ;
TOP_OBJECT_TERM \[" "*\]
SUB_OBJECT_TERM \[" "*\.?\.\/" "*\]
OBJECT_TERM {TOP_OBJECT_TERM}|{SUB_OBJECT_TERM}
DOT_SLASH \.\/


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

{EXECUTION_UNIT_START} {
    yy_push_state(execution_unit); // enter the 'unit' of execution
    capture_token(yylval,wasp::EXECUTION_UNIT_START);
    return token::EXECUTION_UNIT_START;
}
<execution_unit>{EXECUTION_UNIT_END} {
    yy_pop_state(); // pop the execution state
    capture_token(yylval,wasp::EXECUTION_UNIT_END);
    return token::EXECUTION_UNIT_END;
}
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
<INITIAL,execution_unit,object>{SINGLE_QUOTE} {
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
<INITIAL,execution_unit,object,array>{INTEGER} {
    capture_token(yylval,wasp::INTEGER);
    return token::INTEGER;
}

<INITIAL,execution_unit,object,array>{REAL} {
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
<INITIAL,execution_unit,object>{STRING} {
    capture_token(yylval,wasp::STRING);
    return token::STRING;
}
<INITIAL,execution_unit,object>{DOUBLE_QUOTED_STRING} {
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
