%{ /*** C/C++ Declarations ***/

#include <stdio.h>
#include <vector>

%}

/*** yacc/bison Declarations ***/

%code requires{
#include "waspcore/TreeNodePool.h"
#include "waspcore/wasp_node.h"
}

/* Require biGetPot 3 or later */
%require "3"
%output "GetPotParser.cpp"
/* add debug output code to generated parser. disable this for release
 * versions. */
 // %debug

/* start symbol is named "start" */
%start start

/* write out a header file containing the token defines */
%defines

/* use newer C++ skeleton file */
%skeleton "lalr1.cc"

/* namespace to enclose parser in */
%name-prefix "wasp"

/* set the parser's class identifier */
%define parser_class_name {GetPotParser}

/* keep track of the current position within the input */
%locations
%initial-action
{
    // initialize the initial location object
    @$.begin.filename = @$.end.filename = &interpreter.stream_name();
    @$.begin.line = @$.end.line = interpreter.start_line();
    @$.begin.column = @$.end.column = interpreter.start_column();
};

/* The interpreter is passed by reference to the parser and to the GetPotLexer. This
 * provides a simple but effective pure interface, not relying on global
 * variables. */
%parse-param { class AbstractInterpreter& interpreter }

/* verbose error messages */
%error-verbose

 /*** BEGIN EXAMPLE - Change the GetPot grammar's tokens below ***/

//%define api.value.type {struct YYSTYPE}
%union{
    std::size_t token_index;
    std::size_t node_index;
    std::vector<size_t>* node_indices;
}


%token                  END          0  "end of file"
%token                  EOL             "end of line"
%token <token_index>   LBRACKET         "["
%token <token_index>   RBRACKET         "]"
%token                 '{'
%token                 '}'
%token <token_index>   ASSIGN           "="
%token <token_index>   COMMA            ","


%token <token_index>   DOT_SLASH        "subblock indicator ./"
%token <token_index>   QUOTE            "'"
%token <token_index>   INTEGER         "integer"
%token <token_index>   REAL          "real"
%token <token_index>   STRING          "string"
%token <token_index>   QSTRING          "quoted string"
%token <token_index>   COMMENT           "comment"
%token <token_index>   EXECUTION_UNIT_START  "start of unit of execution"
%token <token_index>   EXECUTION_UNIT_END  "end of unit of execution"
%token <token_index>   OBJECT_TERM  "block terminator"
%token <token_index>   SUB_OBJECT_TERM  "subblock terminator"

%type <token_index>   DECL "declarator"
%type <token_index>   VALUE "value"
%type <node_index>  integer real string lbracket rbracket quote assign comma
%type <node_index>  object_decl object_term
%type <node_index>  sub_object_decl sub_object_term
%type <node_index>  object sub_object
%type <node_index>  unquoted_string
%type <node_index>  keyedvalue dot_slash
%type <node_index>  comment value decl primitive
%type <node_index> object_member array_member sub_object_member
%type <node_indices> object_members array_members array sub_object_members
 //%type <node_indices> last_object

%{

#include "GetPotInterpreter.h"
#include "GetPotLexer.h"

/* this "connects" the GetPot parser in the interpreter to the flex GetPotLexer class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the interpreter context. */
#undef yylex
#define yylex dynamic_cast<GetPotLexerImpl*>(interpreter.lexer())->lex

%}

%% /*** Grammar Rules ***/

 /*** BEGIN - Change the GetPot grammar rules below ***/

comma : COMMA
    {
        size_t token_index = ($1);$$ = interpreter.push_leaf(wasp::WASP_COMMA,",",token_index);
    }
assign : ASSIGN
    {
        size_t assign_token_index = ($1);
        $$ = interpreter.push_leaf(wasp::ASSIGN,"="
                         ,assign_token_index);
    }

object_term : OBJECT_TERM
    {
        size_t token_index = ($1);
        $$ = interpreter.push_leaf(wasp::OBJECT_TERM,"[]"
                         ,token_index);
    }
sub_object_term : SUB_OBJECT_TERM
    {
        size_t token_index = ($1);
        $$ = interpreter.push_leaf(wasp::SUB_OBJECT_TERM,"[../]"
                         ,token_index);
    }
lbracket : LBRACKET
    {
        size_t token_index = ($1);
        $$ = interpreter.push_leaf(wasp::LBRACKET,"["
                         ,token_index);
    }
rbracket : RBRACKET
    {

        size_t token_index = ($1);
        $$ = interpreter.push_leaf(wasp::RBRACKET,"]"
                         ,token_index);
    }
dot_slash : DOT_SLASH
    {

        size_t token_index = ($1);
        $$ = interpreter.push_leaf(wasp::DOT_SLASH,"./"
                         ,token_index);
    }
sub_object_member : primitive | keyedvalue | comment | sub_object


sub_object_members : sub_object_member
    {
        size_t node_index = ($1);
        $$ = new std::vector<size_t>();
        $$->push_back(node_index);
    }| sub_object_members sub_object_member
    {
        $1->push_back(($sub_object_member));
    }
sub_object_decl : lbracket  dot_slash decl rbracket
    {
        size_t lbracket_index = ($lbracket);
        size_t dot_slash_index = ($dot_slash);
        size_t decl_index = ($decl);
        size_t rbracket_index = ($rbracket);
        std::vector<size_t> child_indices = {lbracket_index
                                                   ,dot_slash_index
                                                   ,decl_index
                                                   ,rbracket_index};

        $$ = interpreter.push_parent(wasp::SUB_OBJECT_DECL
                                        ,interpreter.data(decl_index).c_str()
                                        ,child_indices);
    }
sub_object : sub_object_decl sub_object_term
    {// empty object
        size_t object_decl_i = ($sub_object_decl);
        size_t object_term_i = ($sub_object_term);
        std::vector<size_t> child_indices = {object_decl_i
                                                   ,object_term_i};

        $$ = interpreter.push_parent(wasp::SUB_OBJECT
                                        ,interpreter.name(object_decl_i)
                                        ,child_indices);

    }| sub_object_decl sub_object_members sub_object_term
    {   std::vector<size_t> children; children.reserve(2+$2->size());
        size_t object_decl_i = ($sub_object_decl);
        children.push_back(object_decl_i);
        for( size_t child_i: *$2 ) children.push_back(child_i);
        children.push_back(($sub_object_term));
        delete $2;

        $$ = interpreter.push_parent(wasp::SUB_OBJECT
                                    ,interpreter.name(object_decl_i)
                                    ,children);
    }
    | sub_object_decl sub_object_members
    {   std::vector<size_t> children; children.reserve(1+$2->size());
        size_t object_decl_i = ($sub_object_decl);
        children.push_back(object_decl_i);
        for( size_t child_i: *$2 ) children.push_back(child_i);
        delete $2;

        $$ = interpreter.push_parent(wasp::SUB_OBJECT
                                    ,interpreter.name(object_decl_i)
                                    ,children);
    }
object_decl : lbracket decl rbracket {
        size_t lbracket_index = ($lbracket);
        size_t decl_index = ($decl);
        size_t rbracket_index = ($rbracket);
        std::vector<size_t> child_indices = {lbracket_index
                                                   ,decl_index
                                                   ,rbracket_index};

        $$ = interpreter.push_parent(wasp::OBJECT_DECL
                                        ,interpreter.data(decl_index).c_str()
                                        ,child_indices);
    }
object_member : primitive | keyedvalue | comment
                | sub_object

object_members : object_member
    {
        size_t node_index = ($1);
        $$ = new std::vector<size_t>();
        $$->push_back(node_index);
    }| object_members object_member
    {
        $1->push_back(($object_member));
    }


object : object_decl object_term
        { // empty object
        size_t object_decl_i = ($object_decl);
        size_t object_term_i = ($object_term);
        std::vector<size_t> child_indices = {object_decl_i
                                                   ,object_term_i};

        $$ = interpreter.push_parent(wasp::OBJECT
                                        ,interpreter.name(object_decl_i)
                                        ,child_indices);
        }
        | object_decl object_members object_term
        {
        std::vector<size_t> children; children.reserve(2+$object_members->size());
        size_t object_decl_i = ($object_decl);
        children.push_back(object_decl_i);
        for( size_t child_i: *$object_members ) children.push_back(child_i);
        children.push_back(($object_term));
        delete $object_members;

        $$ = interpreter.push_parent(wasp::OBJECT
                                        ,interpreter.name(object_decl_i)
                                        ,children);
        }
integer : INTEGER
    {
        size_t token_index = ($1);
        $$ = interpreter.push_leaf(wasp::INT,"int"
                         ,token_index);
    }
real : REAL
    {        
        size_t token_index = ($1);
        $$ = interpreter.push_leaf(wasp::REAL,"real"
                         ,token_index);
    }
unquoted_string : STRING
    {        
        size_t token_index = ($1);
        $$ = interpreter.push_leaf(wasp::STRING,"string"
                         ,token_index);
    }
VALUE : INTEGER | REAL | STRING
value : VALUE
    {
        size_t token_index = ($1);
        $$ = interpreter.push_leaf(wasp::VALUE,"value"
                         ,token_index);
    }
DECL : STRING
decl : DECL
    {
        size_t decl_token_index = ($1);
        $$ = interpreter.push_leaf(wasp::DECL,"decl"
                         ,decl_token_index);
    }
quote : QUOTE
    {
        size_t token_index = ($1);
        $$ = interpreter.push_leaf(wasp::QUOTE,"'"
                         ,token_index);
    }
string : unquoted_string

primitive : integer           
           | real
           | string

array_member : comma | value | assign

array_members : array_member
    {
        size_t offset = ($1);
        $$ = new std::vector<size_t>();
        $$->push_back(offset);
    }| array_members array_member
    {
        $1->push_back(($array_member));
    }

array : quote array_members quote
    {
        $array_members->insert($array_members->begin(),$1);
        $array_members->push_back(($3));
        $$ = $array_members;
    }
    |quote  quote
    {
        $$ = new std::vector<size_t>();
        $$->push_back(($1));
        $$->push_back(($2));
    }


keyedvalue : decl assign value
    {        

        size_t key_index = ($1);
        size_t assign_index = ($2);
        size_t value_index = ($3);

        std::vector<size_t> child_indices = {key_index, assign_index,value_index};

        $$ = interpreter.push_parent(wasp::KEYED_VALUE
                                        ,interpreter.data(key_index).c_str()
                                        ,child_indices);
    }
    | decl assign array
    {

        size_t key_index = ($1);
        size_t assign_index = ($2);

        std::vector<size_t> child_indices = {key_index, assign_index};
        for( size_t child_i : *$array ) child_indices.push_back(child_i);
        delete $array;
        $$ = interpreter.push_parent(wasp::KEYED_VALUE
                                        ,interpreter.data(key_index).c_str()
                                        ,child_indices);
    }


comment : COMMENT
    {
        size_t token_index = ($1);
        $$ = interpreter.push_leaf(wasp::COMMENT,"comment"
                         ,token_index);
    }

start   : /** empty **/
        | start comment{
            interpreter.add_root_child_index(($2));
        }
        | start keyedvalue{
            interpreter.add_root_child_index(($2));
        }
        | start object{
            interpreter.add_root_child_index(($2));
        }
        | start object_decl object_members object
        {
            std::vector<size_t> children; children.reserve(1+$object_members->size());
            size_t object_decl_i = ($object_decl);
            children.push_back(object_decl_i);
            for( size_t child_i: *$object_members ) children.push_back(child_i);
            delete $object_members;

            size_t object_i = interpreter.push_parent(wasp::OBJECT
                                            ,interpreter.name(object_decl_i)
                                            ,children);
            interpreter.add_root_child_index(object_i);
            interpreter.add_root_child_index(($object));
        }


 /*** END RULES - Change the GetPot grammar rules above ***/

%% /*** Additional Code ***/
namespace wasp{
void GetPotParser::error(const GetPotParser::location_type& l,
                           const std::string& m)
{
    interpreter.error_stream()<<l<<": "<<m;
}
}; // end of namespace
