%{ /*** C/C++ Declarations ***/

#include <stdio.h>
#include <vector>

%}

/*** yacc/bison Declarations ***/

%code requires{
#include "waspcore/TreeNodePool.h"
#include "waspcore/wasp_node.h"
}

/* Require biExpr 3 or later */
%require "3"
%output "ExprParser.cpp"
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
%define parser_class_name {ExprParser}

/* keep track of the current position within the input */
%locations
%initial-action
{
    // initialize the initial location object
    @$.begin.filename = @$.end.filename = &interpreter.m_stream_name;
    @$.begin.line = @$.end.line = interpreter.m_start_line;
    @$.begin.column = @$.end.column = interpreter.m_start_column;
};

/* The interpreter is passed by reference to the parser and to the ExprLexer. This
 * provides a simple but effective pure interface, not relying on global
 * variables. */
%parse-param { class ExprInterpreter& interpreter }

/* verbose error messages */
%error-verbose

 /*** BEGIN EXAMPLE - Change the Expr grammar's tokens below ***/

//%define api.value.type {struct YYSTYPE}
%union{
    std::size_t token_index;
    std::size_t node_index;
    std::vector<unsigned int>* node_indices;
}


%token                  END          0  "end of file"
%token                  EOL             "end of line"
%token <token_index>   LBRACKET         "["
%token <token_index>   RBRACKET         "]"
%token                 '{'
%token                 '}'
%token <token_index>   BANG             "!"
%token <token_index>   ASSIGN           "="
%token <token_index>   COMMA            ","
%token <token_index>    GTE             ">="
%token <token_index>    LTE             "<="
%token <token_index>    LT             "<"
%token <token_index>    GT             ">"
%token <token_index>    NEQ             "!="
%token <token_index>    EQ              "=="
%token <token_index>    AND             "&&"
%token <token_index>    OR              "||"
%token <token_index>   MULTIPLY          "*"
%token <token_index>   DIVIDE           "/"
%token <token_index>   PLUS             "+"
%token <token_index>   MINUS            "-"
%token <token_index>   EXPONENT         "^"
%token <token_index>   LPAREN           "("
%token <token_index>   RPAREN           ")"
%token <token_index>   INTEGER         "integer"
%token <token_index>   REAL          "real"
%token <token_index>   STRING          "string"
%token <token_index>   QSTRING          "quoted string"
%token <token_index>   COMMENT           "comment"

%type <token_index>   DECL "declarator"
%type <token_index>   VALUE "value"
%type <node_index>  integer real string
//%type <node_index>  lbracket rbracket
%type <node_index>  assign comma
%type <node_index>  gt lt gte lte neq eq and or multiply divide plus minus
%type <node_index>  exponent lparen rparen bang
%type <node_index>  function function_name
//%type <token_index>   NUMERIC_VALUE "numeric value"
//%type <node_index>  numeric_value string_value
%type <node_index>  unquoted_string
%type <node_index>  primitive math_exp
%type <node_index>  keyedvalue 
%type <node_index>  comment value decl
%type <node_indices> function_args



%{

#include "ExprInterpreter.h"
#include "ExprLexer.h"

/* this "connects" the Expr parser in the interpreter to the flex ExprLexer class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the interpreter context. */
#undef yylex
#define yylex interpreter.m_lexer->lex

%}

%% /*** Grammar Rules ***/

 /*** BEGIN - Change the Expr grammar rules below ***/

bang     : BANG     {unsigned int token_index = static_cast<unsigned int>($1);$$ = interpreter.push_leaf(wasp::BANG      ,"!",token_index);}
gt       : GT       {unsigned int token_index = static_cast<unsigned int>($1);$$ = interpreter.push_leaf(wasp::GT      ,">",token_index);}
lt       : LT       {unsigned int token_index = static_cast<unsigned int>($1);$$ = interpreter.push_leaf(wasp::LT      ,"<",token_index);}
gte      : GTE      {unsigned int token_index = static_cast<unsigned int>($1);$$ = interpreter.push_leaf(wasp::GTE      ,">=",token_index);}
lte      : LTE      {unsigned int token_index = static_cast<unsigned int>($1);$$ = interpreter.push_leaf(wasp::LTE      ,"<=",token_index);}
neq      : NEQ      {unsigned int token_index = static_cast<unsigned int>($1);$$ = interpreter.push_leaf(wasp::NEQ      ,"!=",token_index);}
eq       : EQ       {unsigned int token_index = static_cast<unsigned int>($1);$$ = interpreter.push_leaf(wasp::EQ       ,"==",token_index);}
and      : AND      {unsigned int token_index = static_cast<unsigned int>($1);$$ = interpreter.push_leaf(wasp::WASP_AND      ,"&&",token_index);}
or       : OR       {unsigned int token_index = static_cast<unsigned int>($1);$$ = interpreter.push_leaf(wasp::WASP_OR       ,"||",token_index);}
multiply : MULTIPLY {unsigned int token_index = static_cast<unsigned int>($1);$$ = interpreter.push_leaf(wasp::MULTIPLY , "*",token_index);}
divide   : DIVIDE   {unsigned int token_index = static_cast<unsigned int>($1);$$ = interpreter.push_leaf(wasp::DIVIDE   ,"/" ,token_index);}
plus     : PLUS     {unsigned int token_index = static_cast<unsigned int>($1);$$ = interpreter.push_leaf(wasp::PLUS     ,"+" ,token_index);}
minus    : MINUS    {unsigned int token_index = static_cast<unsigned int>($1);$$ = interpreter.push_leaf(wasp::MINUS    ,"-" ,token_index);}
exponent : EXPONENT {unsigned int token_index = static_cast<unsigned int>($1);$$ = interpreter.push_leaf(wasp::EXPONENT ,"^" ,token_index);}
lparen   : LPAREN   {unsigned int token_index = static_cast<unsigned int>($1);$$ = interpreter.push_leaf(wasp::LPAREN   ,"(" ,token_index);}
rparen   : RPAREN   {unsigned int token_index = static_cast<unsigned int>($1);$$ = interpreter.push_leaf(wasp::RPAREN   ,")" ,token_index);}
comma    : COMMA    {unsigned int token_index = static_cast<unsigned int>($1);$$ = interpreter.push_leaf(wasp::COMMA    ,"," ,token_index);}

%left AND OR ;
%left LT GT LTE GTE EQ NEQ ;
%left PLUS MINUS;
%left MULTIPLY DIVIDE;
%left UMINUS UNOT ;
%right EXPONENT;

function_name : STRING {
        unsigned int token_index = static_cast<unsigned int>($1);
        $$ = interpreter.push_leaf(wasp::VALUE,"name"
                         ,token_index);
    }
function_args : /*EMPTY*/ { $$ = nullptr;}
    | math_exp
    {
        unsigned int node_index = static_cast<unsigned int>($1);
        $$ = new std::vector<unsigned int>();
        $$->push_back(node_index);
    }
    | function_args comma math_exp
    {
        if( $1 == nullptr )
        {
            $$ = new std::vector<unsigned int>();
        }
        $$->push_back($2);
        $$->push_back($3);
    }

%nonassoc "constant" "name";
// TODO add array indices
function : value %prec "constant"
    |  function_name lparen function_args rparen %prec "name"
    {
        unsigned int name_index = static_cast<unsigned int>($1);
        unsigned int left_index = static_cast<unsigned int>($2);
        unsigned int right_index = static_cast<unsigned int>($4);
        std::vector<unsigned int> child_indices = {name_index
                                                   ,left_index};
        if( $function_args != nullptr )
        {
            child_indices.reserve(child_indices.size()+$function_args->size());
            for( std::size_t i = 0; i < $function_args->size(); ++i)
            {
                child_indices.push_back($function_args->at(i));
            }
            delete $function_args;
        }
        child_indices.push_back(right_index);
        $$ = interpreter.push_parent(wasp::FUNCTION
                                        ,"exp"
                                        ,child_indices);
     }
math_exp : value // constant value or function( cos(), sin())
    | minus math_exp  %prec UMINUS
    {
        unsigned int left_index = static_cast<unsigned int>($1);
        unsigned int op_index = static_cast<unsigned int>($2);
        std::vector<unsigned int> child_indices = {left_index
                                                   ,op_index};
        $$ = interpreter.push_parent(wasp::UNARY_MINUS
                                        ,"exp"
                                        ,child_indices);
    }
   | bang math_exp %prec UNOT
   {
       unsigned int left_index = static_cast<unsigned int>($1);
       unsigned int op_index = static_cast<unsigned int>($2);
       std::vector<unsigned int> child_indices = {left_index
                                                  ,op_index};
       $$ = interpreter.push_parent(wasp::UNARY_NOT
                                       ,"exp"
                                       ,child_indices);
    }
    | lparen math_exp rparen
    {
        unsigned int left_index = static_cast<unsigned int>($1);
        unsigned int op_index = static_cast<unsigned int>($2);
        unsigned int right_index = static_cast<unsigned int>($3);
        std::vector<unsigned int> child_indices = {left_index
                                                   ,op_index
                                                   ,right_index};
        $$ = interpreter.push_parent(wasp::PARENTHESIS
                                        ,"exp"
                                        ,child_indices);
    }
    | math_exp multiply math_exp %prec MULTIPLY
    {
        unsigned int left_index = static_cast<unsigned int>($1);
        unsigned int op_index = static_cast<unsigned int>($2);
        unsigned int right_index = static_cast<unsigned int>($3);
        std::vector<unsigned int> child_indices = {left_index
                                                   ,op_index
                                                   ,right_index};
        $$ = interpreter.push_parent(wasp::MULTIPLY
                                        ,"exp"
                                        ,child_indices);
    }
   | math_exp divide math_exp %prec DIVIDE
   {
       unsigned int left_index = static_cast<unsigned int>($1);
       unsigned int op_index = static_cast<unsigned int>($2);
       unsigned int right_index = static_cast<unsigned int>($3);
       std::vector<unsigned int> child_indices = {left_index
                                                  ,op_index
                                                  ,right_index};
       $$ = interpreter.push_parent(wasp::DIVIDE
                                       ,"exp"
                                       ,child_indices);
   }
   | math_exp plus math_exp %prec PLUS
   {
      unsigned int left_index = static_cast<unsigned int>($1);
      unsigned int op_index = static_cast<unsigned int>($2);
      unsigned int right_index = static_cast<unsigned int>($3);
      std::vector<unsigned int> child_indices = {left_index
                                                 ,op_index
                                                 ,right_index};
      $$ = interpreter.push_parent(wasp::PLUS
                                      ,"exp"
                                      ,child_indices);
   }
   | math_exp minus math_exp %prec MINUS
   {
      unsigned int left_index = static_cast<unsigned int>($1);
      unsigned int op_index = static_cast<unsigned int>($2);
      unsigned int right_index = static_cast<unsigned int>($3);
      std::vector<unsigned int> child_indices = {left_index
                                                 ,op_index
                                                 ,right_index};
      $$ = interpreter.push_parent(wasp::MINUS
                                      ,"exp"
                                      ,child_indices);
   }
   | math_exp exponent math_exp %prec EXPONENT
   {
      unsigned int left_index = static_cast<unsigned int>($1);
      unsigned int op_index = static_cast<unsigned int>($2);
      unsigned int right_index = static_cast<unsigned int>($3);
      std::vector<unsigned int> child_indices = {left_index
                                                 ,op_index
                                                 ,right_index};
      $$ = interpreter.push_parent(wasp::EXPONENT
                                      ,"exp"
                                      ,child_indices);
   }
   | math_exp eq math_exp %prec EQ
   {
      unsigned int left_index = static_cast<unsigned int>($1);
      unsigned int op_index = static_cast<unsigned int>($2);
      unsigned int right_index = static_cast<unsigned int>($3);
      std::vector<unsigned int> child_indices = {left_index
                                                 ,op_index
                                                 ,right_index};
      $$ = interpreter.push_parent(wasp::EQ
                                      ,"exp"
                                      ,child_indices);
   }
   | math_exp neq math_exp %prec NEQ
   {
      unsigned int left_index = static_cast<unsigned int>($1);
      unsigned int op_index = static_cast<unsigned int>($2);
      unsigned int right_index = static_cast<unsigned int>($3);
      std::vector<unsigned int> child_indices = {left_index
                                                 ,op_index
                                                 ,right_index};
      $$ = interpreter.push_parent(wasp::NEQ
                                      ,"exp"
                                      ,child_indices);
   }
   | math_exp and math_exp %prec AND
   {
      unsigned int left_index = static_cast<unsigned int>($1);
      unsigned int op_index = static_cast<unsigned int>($2);
      unsigned int right_index = static_cast<unsigned int>($3);
      std::vector<unsigned int> child_indices = {left_index
                                                 ,op_index
                                                 ,right_index};
      $$ = interpreter.push_parent(wasp::WASP_AND
                                      ,"exp"
                                      ,child_indices);
   }
   | math_exp or math_exp %prec OR
   {
      unsigned int left_index = static_cast<unsigned int>($1);
      unsigned int op_index = static_cast<unsigned int>($2);
      unsigned int right_index = static_cast<unsigned int>($3);
      std::vector<unsigned int> child_indices = {left_index
                                                 ,op_index
                                                 ,right_index};
      $$ = interpreter.push_parent(wasp::WASP_OR
                                      ,"exp"
                                      ,child_indices);
   }
   | math_exp gte math_exp %prec GTE
   {
      unsigned int left_index = static_cast<unsigned int>($1);
      unsigned int op_index = static_cast<unsigned int>($2);
      unsigned int right_index = static_cast<unsigned int>($3);
      std::vector<unsigned int> child_indices = {left_index
                                                 ,op_index
                                                 ,right_index};
      $$ = interpreter.push_parent(wasp::GTE
                                      ,"exp"
                                      ,child_indices);
   }
   | math_exp gt math_exp %prec GT
   {
      unsigned int left_index = static_cast<unsigned int>($1);
      unsigned int op_index = static_cast<unsigned int>($2);
      unsigned int right_index = static_cast<unsigned int>($3);
      std::vector<unsigned int> child_indices = {left_index
                                                 ,op_index
                                                 ,right_index};
      $$ = interpreter.push_parent(wasp::GT
                                      ,"exp"
                                      ,child_indices);
   }
   | math_exp lte math_exp %prec LTE
   {
      unsigned int left_index = static_cast<unsigned int>($1);
      unsigned int op_index = static_cast<unsigned int>($2);
      unsigned int right_index = static_cast<unsigned int>($3);
      std::vector<unsigned int> child_indices = {left_index
                                                 ,op_index
                                                 ,right_index};
      $$ = interpreter.push_parent(wasp::LTE
                                      ,"exp"
                                      ,child_indices);
   }
   | math_exp lt math_exp %prec LT
   {
      unsigned int left_index = static_cast<unsigned int>($1);
      unsigned int op_index = static_cast<unsigned int>($2);
      unsigned int right_index = static_cast<unsigned int>($3);
      std::vector<unsigned int> child_indices = {left_index
                                                 ,op_index
                                                 ,right_index};
      $$ = interpreter.push_parent(wasp::LT
                                      ,"exp"
                                      ,child_indices);
   }
assign : ASSIGN
    {
        unsigned int assign_token_index = static_cast<unsigned int>($1);
        $$ = interpreter.push_leaf(wasp::ASSIGN,"="
                         ,assign_token_index);
    }

//lbracket : LBRACKET
//    {
//        unsigned int token_index = static_cast<unsigned int>($1);
//        $$ = interpreter.push_leaf(wasp::LBRACKET,"["
//                         ,token_index);
//    }
//rbracket : RBRACKET
//    {

//        unsigned int token_index = static_cast<unsigned int>($1);
//        $$ = interpreter.push_leaf(wasp::RBRACKET,"]"
//                         ,token_index);
//    }

integer : INTEGER
    {
        unsigned int token_index = static_cast<unsigned int>($1);
        $$ = interpreter.push_leaf(wasp::INT,"int"
                         ,token_index);
    }
real : REAL
    {        
        unsigned int token_index = static_cast<unsigned int>($1);
        $$ = interpreter.push_leaf(wasp::REAL,"real"
                         ,token_index);
    }
unquoted_string : STRING
    {        
        unsigned int token_index = static_cast<unsigned int>($1);
        $$ = interpreter.push_leaf(wasp::STRING,"string"
                         ,token_index);
    }
VALUE : INTEGER | REAL | STRING
value : VALUE
    {
        unsigned int token_index = static_cast<unsigned int>($1);
        $$ = interpreter.push_leaf(wasp::VALUE,"value"
                         ,token_index);
    }
DECL : STRING
decl : DECL
    {
        unsigned int decl_token_index = static_cast<unsigned int>($1);
        $$ = interpreter.push_leaf(wasp::DECL,"decl"
                         ,decl_token_index);
    }
string : unquoted_string

keyedvalue : decl assign math_exp
    {        

        unsigned int key_index = static_cast<unsigned int>($1);
        unsigned int assign_index = static_cast<unsigned int>($2);
        unsigned int value_index = static_cast<unsigned int>($3);

        std::vector<unsigned int> child_indices = {key_index, assign_index,value_index};

        $$ = interpreter.push_parent(wasp::KEYED_VALUE
                                        ,interpreter.m_tree_nodes.data(key_index).c_str()
                                        ,child_indices);
    }


comment : COMMENT
    {
        unsigned int token_index = static_cast<unsigned int>($1);
        $$ = interpreter.push_leaf(wasp::COMMENT,"comment"
                         ,token_index);
    }

start   : /** empty **/
        | start comment{
            interpreter.add_root_child_index(static_cast<unsigned int>($2));
        }
        | start keyedvalue{
            interpreter.add_root_child_index(static_cast<unsigned int>($2));
        }
        | start math_exp{
            interpreter.add_root_child_index(static_cast<unsigned int>($2));
        }



 /*** END RULES - Change the Expr grammar rules above ***/

%% /*** Additional Code ***/
namespace wasp{
void ExprParser::error(const ExprParser::location_type& l,
                           const std::string& m)
{
    interpreter.error_stream()<<l<<": "<<m;
}
}; // end of namespace
