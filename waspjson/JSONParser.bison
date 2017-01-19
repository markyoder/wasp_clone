%{ /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>
%}

/*** yacc/bison Declarations ***/

%code requires{
#include <memory>
#include "waspcore/utils.h"
}

/* Require bison 3 or later */
%require "3"
%output "JSONParser.cpp"
/* add debug output code to generated parser. disable this for release
 * versions. */
 /*%debug*/

/* start symbol is named "start" */
%start start

/* write out a header file containing the token defines */
%defines

/* use newer C++ skeleton file */
%skeleton "lalr1.cc"

/* namespace to enclose parser in */
%name-prefix "wasp"

/* set the parser's class identifier */
%define parser_class_name {JSONParser}

/* keep track of the current position within the input */
%locations
%initial-action
{
    // initialize the initial location object
    @$.begin.filename = @$.end.filename = &interpreter.stream_name();
    @$.begin.line = @$.end.line = interpreter.start_line();
    @$.begin.column = @$.end.column = interpreter.start_column();
    lexer = std::make_shared<JSONLexerImpl>(interpreter,&input_stream);
};

/* The interpreter is passed by reference to the parser and to the JSONLexer. This
 * provides a simple but effective pure interface, not relying on global
 * variables. */
%parse-param { class AbstractInterpreter& interpreter }
             {std::istream &input_stream}
             {std::shared_ptr<class JSONLexerImpl> lexer}

/* verbose error messages */
%error-verbose

 /*** BEGIN EXAMPLE - Change the wasp grammar's tokens below ***/

%union {
        std::size_t token_index;
        std::size_t node_index;
        std::vector<size_t>* node_indices;
}

%token                  END          0  "end of file"
%token                  EOL             "end of line"
%token <token_index>   LBRACKET         "["
%token <token_index>   RBRACKET         "]"
%token <token_index>   LBRACE           "{"
%token <token_index>   RBRACE           "}"
%token <token_index>   COMMA            ","
%token <token_index>   COLON            ":"
%token <token_index>    INTEGER         "integer"
%token <token_index>    TOKEN_TRUE            "true"
%token <token_index>    TOKEN_FALSE            "false"
%token <token_index>    TOKEN_NULL            "null"
%token <token_index>    DOUBLE          "double"
%token <token_index>    QSTRING          "quoted string"


%type <token_index> PRIMITIVE ASSIGNMENT ANY_STRING
%type <token_index> BOOLEAN

%type <node_index>  assignment
%type <node_index>  lbracket rbracket
%type <node_index>  lbrace rbrace
%type <node_index>  decl
%type <node_index>  comma
%type <node_index>  primitive
%type <node_index>  array
%type <node_index>  object
%type <node_index>  keyed_primitive


%type <node_indices>  members declaration
%destructor { delete $$; } members declaration

%{

#include "JSONInterpreter.h"
#include "JSONLexer.h"

/* this "connects" the bison parser in the interpreter to the flex JSONLexer class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the interpreter context. */
#undef yylex
#define yylex lexer->lex

%}

%% /*** Grammar Rules ***/

 /*** BEGIN - Change the wasp grammar rules below ***/
comma : COMMA
    {
        auto token_index = ($1);
        $$ = interpreter.push_leaf(wasp::WASP_COMMA,",",token_index);
    }
BOOLEAN : TOKEN_TRUE | TOKEN_FALSE

lbrace  : LBRACE
    {
        auto token_index = ($1);
        $$ = interpreter.push_leaf(wasp::LBRACE,"{",token_index);
    }
rbrace  : RBRACE
    {
        auto token_index = ($1);
        $$ = interpreter.push_leaf(wasp::RBRACE,"}",token_index);
    }
lbracket  : LBRACKET
    {
        auto token_index = ($1);
        $$ = interpreter.push_leaf(wasp::LBRACKET,"[",token_index);
    }
rbracket  : RBRACKET
    {
        auto token_index = ($1);
        $$ = interpreter.push_leaf(wasp::RBRACKET,"]",token_index);
    }

ANY_STRING : QSTRING
PRIMITIVE : QSTRING | INTEGER | DOUBLE | BOOLEAN | TOKEN_NULL

primitive : PRIMITIVE
{
    size_t token_index = ($1);
    $$ = interpreter.push_leaf(wasp::VALUE,"value"
                     ,token_index);
}
decl : ANY_STRING
    {
        auto token_index = ($1);
        std::string quote_less_data = interpreter.token_data(token_index);
        quote_less_data = wasp::strip_quotes(quote_less_data);
        $$ = interpreter.push_leaf(wasp::DECL
                                   ,"decl"
                                   ,token_index);
    }
ASSIGNMENT : COLON
assignment : ASSIGNMENT {
             auto token_index = ($1);
             $$ = interpreter.push_leaf(wasp::ASSIGN,":",token_index);
            }
declaration : decl assignment
        {
            $$ = new std::vector<size_t>();
            $$->push_back($1);
            $$->push_back($2);
        }

array :
    declaration lbracket rbracket
    {
        $1->push_back($2);
        $1->push_back($3);
        $$ = interpreter.push_parent(wasp::ARRAY
                ,wasp::strip_quotes(interpreter.data($1->front())).c_str()
                ,*$1);
        delete $1;
    }
    | declaration lbracket END
    {
        $1->push_back($2);
        std::string name = interpreter.name($1->front());
        $$ = interpreter.push_parent(wasp::ARRAY
                                    , name.c_str()
                                        ,*$1);
        delete $1;
        error(@2, name+" has unmatched left bracket!");
        delete $1;
        YYERROR;
    }
    | declaration lbracket members END
    {
        std::string name = interpreter.name($1->front());
        auto last_component_type = interpreter.type($1->back());
        // TODO capture partial definition
        if( $3->size() ==0 ) error(@2, name+" has unmatched left bracket!");
        else if( last_component_type == wasp::ARRAY ) error(@2, name+" or one of its components has unmatched left bracket!");
        else error(@2, name+" has unmatched left bracket!");

        delete $1;
        YYERROR;
    }
    |declaration lbracket members rbracket
    {
        $1->push_back($2);
        for( std::size_t i = 0; i < $3->size(); ++i )
        {
            $1->push_back( $3->at( i ) );
        }
        $1->push_back($4);
        $$ = interpreter.push_parent(wasp::ARRAY
            ,wasp::strip_quotes(interpreter.data($1->front())).c_str()
            ,*$1);
        delete $1;
        delete $3;

    }
object : declaration lbrace rbrace
    {
        $1->push_back($2);
        $1->push_back($3);
        $$ = interpreter.push_parent(wasp::OBJECT
            ,wasp::strip_quotes(interpreter.data($1->front())).c_str()
            ,*$1);
        delete $1;
    }    
    | declaration lbrace END
    {
        $1->push_back($2);
        std::string name = interpreter.data($1->front());
        $$ = interpreter.push_parent(wasp::OBJECT
                                     , name.c_str()
                                     , *$1);
        delete $1;
        error(@2, name+" has unmatched left brace!");
        YYERROR;
    }
    | declaration lbrace members END
    {
        // TODO capture partial definition
        std::string name = interpreter.data($1->front());
        auto last_component_type = interpreter.type($1->back());
        if( $3->size() ==0 ) error(@2, name+" has unmatched left brace!");
        else if( last_component_type == wasp::OBJECT ) error(@2, name+" or one of its components has unmatched left brace!");
        else error(@2, name+" has unmatched left brace!");
        delete $3;
        delete $1;
        YYERROR;
    }    
    | declaration lbrace members rbrace
    {
        $1->push_back($2);
        for( std::size_t i = 0; i < $3->size(); ++i )
        {
            $1->push_back( $3->at( i ) );
        }
        $1->push_back($4);
        $$ = interpreter.push_parent(wasp::OBJECT
                                    ,wasp::strip_quotes(interpreter.data($1->front())).c_str()
                                        ,*$1);
        delete $1;
        delete $3;
    }


keyed_primitive : declaration primitive
    {
        $1->push_back($2);
        std::string quote_less_data = interpreter.data($1->front());
        quote_less_data = wasp::strip_quotes(quote_less_data);
        $$ = interpreter.push_parent(wasp::KEYED_VALUE
                                     // use the data instead of the name
                                     // this provides the following tree
                                     // data
                                     //  |_ decl (data)
                                     //  |_ : (:)
                                     //  |_ value (1.2..blah)
                                    ,quote_less_data.c_str()
                                    ,*$1);
        delete $1;
    }

members :object
        {
            $$ = new std::vector<size_t>();
            $$->push_back($1);
        }
        | members comma object
        {
            $$ = $1;
            $$->push_back($2);
            $$->push_back($3);
        }
        | array
        {
            $$ = new std::vector<size_t>();
            $$->push_back($1);
        }
        | members comma array
        {
            $$ = $1;
            $$->push_back($2);
            $$->push_back($3);
        }
        | keyed_primitive
        {
            $$ = new std::vector<size_t>();
            $$->push_back($1);

        }
        | members comma keyed_primitive
        {
            $$ = $1;
            $$->push_back($2);
            $$->push_back($3);
        }
        | primitive
        {
            $$ = new std::vector<size_t>();
            $$->push_back($1);
        }
        | members comma primitive
        {
            $$ = $1;
            $$->push_back($2);
            $$->push_back($3);
        }
     
start   : /** empty **/        
        | start object{interpreter.add_root_child_index(($2)); if(interpreter.single_parse() ) {lexer->rewind();YYACCEPT;}}        

 /*** END RULES - Change the wasp grammar rules above ***/

%% /*** Additional Code ***/

void wasp::JSONParser::error(const JSONParser::location_type& l,
                           const std::string& m)
{
    interpreter.error_stream()<<l<<": "<<m;
}
