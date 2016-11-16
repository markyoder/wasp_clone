%top{
/* This disables inclusion of unistd.h, which is not available under Visual C++
 * on Win32. The C++ scanner uses STL streams instead. */
#define YY_NO_UNISTD_H

}
%{ /*** C/C++ Declarations ***/

#include <string>
#include <sstream>
#include "GetPotLexer.h"

/* import the parser's token type into a local typedef */
typedef wasp::GetPotParser::token token;
typedef wasp::GetPotParser::token_type token_type;

/* By default yylex returns int, we use token_type. Unfortunately yyterminate
 * by default returns 0, which is not of token_type. */
#define yyterminate() return token::END

%}

 /*** Flex Declarations and Options ***/

 /* enable c++ scanner class generation */
%option c++

%option prefix="GetPot"
%option outfile="GetPotLexer.cpp"


 /* enable scanner to generate debug output. disable this for release
 * versions. */
 /*%option debug*/

 /* no support for include files is planned */
%option yywrap nounput

 /* enables the use of start condition stacks */
%option stack
%s execution_unit
 /* want to capture everthing except whitespace as the object's name
  * [ object_name ]
  */
%x object_decl
%s object
%s subobject
  /* want to capture everthing except whitespace and './' as the object's name
   * [ ./ object_name ]
   */
%x subobject_decl
 /*
  * When a declarator is pushed the following token must be a './'
  * This exclusive state should ensure this is present
  */
%x subobject_dot_slash

INT [0-9]+([eE]\+?[0-9]+)?
EXPONENT [eE][\+\-]?{INT}
REAL {INT}?\.{INT}{EXPONENT}?|{INT}\.({INT}{EXPONENT}?)?|{INT}\.?[eE]\-{INT}




 /* This string does not allow special characters '-','/'
 *  and should only occur in the context of reference
 */
LESSER_STRING [A-Za-z_][A-Za-z0-9_]*

DOUBLE_QUOTED_STRING \"([^\"\n])*\"
SINGLE_QUOTE '
COMMENT #[^\n]*

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
OBJECT_NAME [^" "\n\[\]]+
SUBOBJECT_NAME [^" ""./"\n\[\]]+
STRING [^" "\'\"\=\n\[\]\#]+
RBRACKET \]
COMMA ,
OBJECT_TERM \[" "*\]
SUB_OBJECT_TERM \[" "*\.?\.\/" "*\]
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
 /*** BEGIN EXAMPLE - Change the GetPot lexer rules below ***/

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
{COMMA} {
    capture_token(yylval,wasp::WASP_COMMA);
    return token::COMMA;
}
<subobject_dot_slash>{DOT_SLASH} {
    yy_pop_state();
    capture_token(yylval,wasp::DOT_SLASH);
    return token::DOT_SLASH;
}
{SUB_OBJECT_TERM} {
    capture_token(yylval,wasp::SUB_OBJECT_TERM);
    return token::SUB_OBJECT_TERM;
}
<object>{OBJECT_TERM} {
    yy_pop_state();
    capture_token(yylval,wasp::OBJECT_TERM);
    return token::OBJECT_TERM;
}
{SINGLE_QUOTE} {
    capture_token(yylval,wasp::QUOTE);
    return token::QUOTE;
}

<object>{LBRACKET} {
    yy_push_state(subobject_dot_slash);
    capture_token(yylval,wasp::LBRACKET);
    return token::LBRACKET;
}
<INITIAL>{LBRACKET} {
    yy_push_state(object_decl);
    capture_token(yylval,wasp::LBRACKET);
    return token::LBRACKET;
}
<object_decl,subobject_decl>{OBJECT_NAME} {
    capture_token(yylval,wasp::STRING);
    return token::STRING;
}
<object_decl>{RBRACKET} {
    yy_pop_state();
    yy_push_state(object);
    capture_token(yylval,wasp::RBRACKET);
    return token::RBRACKET;
}
<subobject_decl>{RBRACKET} {
    yy_pop_state();
    yy_push_state(subobject);
    capture_token(yylval,wasp::RBRACKET);
    return token::RBRACKET;
}
{RBRACKET} {
    capture_token(yylval,wasp::RBRACKET);
    return token::RBRACKET;
}
<INITIAL,execution_unit,object,subobject>{INT} {
    capture_token(yylval,wasp::INT);
    return token::INTEGER;
}

<INITIAL,execution_unit,object,subobject>{REAL} {
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
    m_token_data.push_line(file_offset-yyleng);
}
{COMMENT} {
    capture_token(yylval,wasp::COMMENT);
    return token::COMMENT;
}
 /* if we are expecting a './' and find a string
  * This is actually an early terminating object declaration*/
<subobject_dot_slash>{SUBOBJECT_NAME} {
  // pop subobject state and push object_decl
  yy_pop_state();
  yy_push_state(object_decl);
  capture_token(yylval,wasp::STRING);
  return token::STRING;
}
{STRING} {
    capture_token(yylval,wasp::STRING);
    return token::STRING;
}

 /* pass all other characters up to GetPot*/
. {
    return static_cast<token_type>(*yytext);
}

 /*** END EXAMPLE - Change the GetPot lexer rules above ***/

%% /*** Additional Code ***/

namespace wasp {

GetPotLexerImpl::GetPotLexerImpl(
                TokenPool<> & token_data,
                std::istream* in,
                std::ostream* out)
    : GetPotFlexLexer(in, out)
    , m_token_data(token_data)
    , file_offset(0)
{
}

GetPotLexerImpl::~GetPotLexerImpl()
{
}

void GetPotLexerImpl::set_debug(bool b)
{
    yy_flex_debug = b;
}
void GetPotLexerImpl::rewind()
{
    yyin->seekg(-yyleng,std::ios_base::cur);
    yyless(0);
}
void GetPotLexerImpl::capture_token(
        wasp::GetPotParser::semantic_type* yylval
        ,wasp::NODE type)
{
    size_t offset = file_offset - yyleng;
    yylval->node_index = m_token_data.size();
    m_token_data.push(yytext,type,offset);
}
} // end of namespace

/* This implementation of GetPotFlexLexer::yylex() is required to fill the
 * vtable of the class GetPotFlexLexer. We define the scanner's main yylex
 * function via YY_DECL to reside in the GetPotLexerImpl class instead. */

#ifdef yylex
#undef yylex
#endif

int GetPotFlexLexer::yylex()
{    
    return 0;
}

/* When the scanner receives an end-of-file indication from YY_INPUT, it then
 * checks the yywrap() function. If yywrap() returns false (zero), then it is
 * assumed that the function has gone ahead and set up `yyin' to point to
 * another input file, and scanning continues. If it returns true (non-zero),
 * then the scanner terminates, returning 0 to its caller. */

int GetPotFlexLexer::yywrap()
{
    return 1;
}
