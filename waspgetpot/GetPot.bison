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
%define parser_class_name {GetPotParser}

/* keep track of the current position within the input */
%locations
%initial-action
{
    // initialize the initial location object
    @$.begin.filename = @$.end.filename = &interpreter.m_stream_name;
    @$.begin.line = @$.end.line = interpreter.m_start_line;
    @$.begin.column = @$.end.column = interpreter.m_start_column;
};

/* The interpreter is passed by reference to the parser and to the GetPotLexer. This
 * provides a simple but effective pure interface, not relying on global
 * variables. */
%parse-param { class GetPotInterpreter& interpreter }

/* verbose error messages */
%error-verbose

 /*** BEGIN EXAMPLE - Change the GetPot grammar's tokens below ***/

//%define api.value.type {struct YYSTYPE}
%union{
    size_t token_index;
    size_t node_index;
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

%token <token_index>   DOT_SLASH
%token <token_index>   QUOTE
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
%type <node_index>  gt lt gte lte neq eq and or multiply divide plus minus
%type <node_index>  exponent lparen rparen bang
%type <node_index>  function function_name
//%type <token_index>   NUMERIC_VALUE "numeric value"
//%type <node_index>  numeric_value string_value
%type <node_index>  object_decl object_term
%type <node_index>  sub_object_decl sub_object_term
%type <node_index>  object sub_object
%type <node_index>  unquoted_string
%type <node_index>  primitive math_exp
%type <node_index>  keyedvalue dot_slash
%type <node_index>  comment value decl
%type <node_index> object_member array_member
%type <node_indices> object_members array_members array
%type <node_indices> function_args



%{

#include "GetPotInterpreter.h"
#include "GetPotLexer.h"

/* this "connects" the GetPot parser in the interpreter to the flex GetPotLexer class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the interpreter context. */
#undef yylex
#define yylex interpreter.m_lexer->lex

%}

%% /*** Grammar Rules ***/

 /*** BEGIN - Change the GetPot grammar rules below ***/

bang     : BANG     {unsigned int token_index = static_cast<unsigned int>($1);$$ = interpreter.push_leaf(wasp::BANG      ,"!",token_index);}
gt       : GT       {unsigned int token_index = static_cast<unsigned int>($1);$$ = interpreter.push_leaf(wasp::GT      ,">",token_index);}
lt       : LT       {unsigned int token_index = static_cast<unsigned int>($1);$$ = interpreter.push_leaf(wasp::LT      ,"<",token_index);}
gte      : GTE      {unsigned int token_index = static_cast<unsigned int>($1);$$ = interpreter.push_leaf(wasp::GTE      ,">=",token_index);}
lte      : LTE      {unsigned int token_index = static_cast<unsigned int>($1);$$ = interpreter.push_leaf(wasp::LTE      ,"<=",token_index);}
neq      : NEQ      {unsigned int token_index = static_cast<unsigned int>($1);$$ = interpreter.push_leaf(wasp::NEQ      ,"!=",token_index);}
eq       : EQ       {unsigned int token_index = static_cast<unsigned int>($1);$$ = interpreter.push_leaf(wasp::EQ       ,"==",token_index);}
and      : AND      {unsigned int token_index = static_cast<unsigned int>($1);$$ = interpreter.push_leaf(wasp::AND      ,"&&",token_index);}
or       : OR       {unsigned int token_index = static_cast<unsigned int>($1);$$ = interpreter.push_leaf(wasp::OR       ,"||",token_index);}
multiply : MULTIPLY {unsigned int token_index = static_cast<unsigned int>($1);$$ = interpreter.push_leaf(wasp::MULTIPLY , "*",token_index);}
divide   : DIVIDE   {unsigned int token_index = static_cast<unsigned int>($1);$$ = interpreter.push_leaf(wasp::DIVIDE   ,"/" ,token_index);}
plus     : PLUS     {unsigned int token_index = static_cast<unsigned int>($1);$$ = interpreter.push_leaf(wasp::PLUS     ,"+" ,token_index);}
minus    : MINUS    {unsigned int token_index = static_cast<unsigned int>($1);$$ = interpreter.push_leaf(wasp::MINUS    ,"-" ,token_index);}
exponent : EXPONENT {unsigned int token_index = static_cast<unsigned int>($1);$$ = interpreter.push_leaf(wasp::EXPONENT ,"^" ,token_index);}
lparen   : LPAREN   {unsigned int token_index = static_cast<unsigned int>($1);$$ = interpreter.push_leaf(wasp::LPAREN   ,"(" ,token_index);}
rparen   : RPAREN   {unsigned int token_index = static_cast<unsigned int>($1);$$ = interpreter.push_leaf(wasp::RPAREN   ,")" ,token_index);}

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
//string_value : STRING
//    {
//        unsigned int token_index = static_cast<unsigned int>($1);
//        $$ = interpreter.push_leaf(wasp::VALUE,"value"
//                         ,token_index);
//    }
//NUMERIC_VALUE : REAL | INTEGER
//numeric_value : NUMERIC_VALUE
//   {
//       unsigned int token_index = static_cast<unsigned int>($1);
//       $$ = interpreter.push_leaf(wasp::VALUE,"value"
//                        ,token_index);
//   }

%nonassoc "constant" "name";

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
            for( size_t i = 0; i < $function_args->size(); ++i)
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
math_exp : function // constant value or function( cos(), sin())
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
      $$ = interpreter.push_parent(wasp::AND
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
      $$ = interpreter.push_parent(wasp::OR
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
comma : COMMA
    {
        unsigned int token_index = static_cast<unsigned int>($1);$$ = interpreter.push_leaf(wasp::COMMA,",",token_index);
    }
assign : ASSIGN
    {
        unsigned int assign_token_index = static_cast<unsigned int>($1);
        $$ = interpreter.push_leaf(wasp::ASSIGN,"="
                         ,assign_token_index);
    }

object_term : OBJECT_TERM
    {
        unsigned int token_index = static_cast<unsigned int>($1);
        $$ = interpreter.push_leaf(wasp::OBJECT_TERM,"[]"
                         ,token_index);
    }
sub_object_term : SUB_OBJECT_TERM
    {
        unsigned int token_index = static_cast<unsigned int>($1);
        $$ = interpreter.push_leaf(wasp::SUB_OBJECT_TERM,"[../]"
                         ,token_index);
    }
lbracket : LBRACKET
    {
        unsigned int token_index = static_cast<unsigned int>($1);
        $$ = interpreter.push_leaf(wasp::LBRACKET,"["
                         ,token_index);
    }
rbracket : RBRACKET
    {

        unsigned int token_index = static_cast<unsigned int>($1);
        $$ = interpreter.push_leaf(wasp::RBRACKET,"]"
                         ,token_index);
    }
dot_slash : DOT_SLASH
    {

        unsigned int token_index = static_cast<unsigned int>($1);
        $$ = interpreter.push_leaf(wasp::DOT_SLASH,"./"
                         ,token_index);
    }
sub_object_decl : lbracket  dot_slash string rbracket
    {
        unsigned int lbracket_index = static_cast<unsigned int>($lbracket);
        unsigned int dot_slash_index = static_cast<unsigned int>($dot_slash);
        unsigned int string_index = static_cast<unsigned int>($string);
        unsigned int rbracket_index = static_cast<unsigned int>($rbracket);
        std::vector<unsigned int> child_indices = {lbracket_index
                                                   ,dot_slash_index
                                                   ,string_index
                                                   ,rbracket_index};

        $$ = interpreter.push_parent(wasp::SUB_OBJECT_DECL
                                        ,interpreter.m_tree_nodes.data($string).c_str()
                                        ,child_indices);
    }
sub_object : sub_object_decl sub_object_term
    {// empty object
        unsigned int object_decl_i = static_cast<unsigned int>($sub_object_decl);
        unsigned int object_term_i = static_cast<unsigned int>($sub_object_term);
        std::vector<unsigned int> child_indices = {object_decl_i
                                                   ,object_term_i};

        $$ = interpreter.push_parent(wasp::SUB_OBJECT
                                        ,interpreter.m_tree_nodes.name(object_decl_i)
                                        ,child_indices);

    }| sub_object_decl object_members sub_object_term
    {   std::vector<unsigned int> children; children.reserve(2+$object_members->size());
        unsigned int object_decl_i = static_cast<unsigned int>($sub_object_decl);
        children.push_back(object_decl_i);
        for( unsigned int child_i: *$object_members ) children.push_back(child_i);
        children.push_back(static_cast<unsigned int>($sub_object_term));
        delete $object_members;

        $$ = interpreter.push_parent(wasp::SUB_OBJECT
                                    ,interpreter.m_tree_nodes.name(object_decl_i)
                                    ,children);
    }
object_decl : lbracket string rbracket {
        unsigned int lbracket_index = static_cast<unsigned int>($lbracket);
        unsigned int string_index = static_cast<unsigned int>($string);
        unsigned int rbracket_index = static_cast<unsigned int>($rbracket);
        std::vector<unsigned int> child_indices = {lbracket_index
                                                   ,string_index
                                                   ,rbracket_index};

        $$ = interpreter.push_parent(wasp::OBJECT_DECL
                                        ,interpreter.m_tree_nodes.data($string).c_str()
                                        ,child_indices);
    }
object_member : primitive | keyedvalue | comment
                | sub_object

object_members : object_member
    {
        unsigned int node_index = static_cast<unsigned int>($1);
        $$ = new std::vector<unsigned int>();
        $$->push_back(node_index);
    }| object_members object_member
    {
        $1->push_back(static_cast<unsigned int>($object_member));
    }

object : object_decl object_term
        { // empty object
        unsigned int object_decl_i = static_cast<unsigned int>($object_decl);
        unsigned int object_term_i = static_cast<unsigned int>($object_term);
        std::vector<unsigned int> child_indices = {object_decl_i
                                                   ,object_term_i};

        $$ = interpreter.push_parent(wasp::OBJECT
                                        ,interpreter.m_tree_nodes.name(object_decl_i)
                                        ,child_indices);
        }
        | object_decl object_members object_term
        {
        std::vector<unsigned int> children; children.reserve(2+$object_members->size());
        unsigned int object_decl_i = static_cast<unsigned int>($object_decl);
        children.push_back(object_decl_i);
        for( unsigned int child_i: *$object_members ) children.push_back(child_i);
        children.push_back(static_cast<unsigned int>($object_term));
        delete $object_members;

        $$ = interpreter.push_parent(wasp::OBJECT
                                        ,interpreter.m_tree_nodes.name(object_decl_i)
                                        ,children);
        }
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
quote : QUOTE
    {
        unsigned int token_index = static_cast<unsigned int>($1);
        $$ = interpreter.push_leaf(wasp::QUOTE,"'"
                         ,token_index);
    }
string : unquoted_string

primitive : integer           
           | real
           | string

array_member : comma | math_exp

array_members : array_member
    {
        unsigned int offset = static_cast<unsigned int>($1);
        $$ = new std::vector<unsigned int>();
        $$->push_back(offset);
    }| array_members array_member
    {
        $1->push_back(static_cast<unsigned int>($array_member));
    }

array : quote array_members quote
    {
        $array_members->insert($array_members->begin(),$1);
        $array_members->push_back(static_cast<unsigned int>($3));
        $$ = $array_members;
    }
    |quote  quote
    {
        $$ = new std::vector<unsigned int>();
        $$->push_back(static_cast<unsigned int>($1));
        $$->push_back(static_cast<unsigned int>($2));
    }


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
    | decl assign array
    {

        unsigned int key_index = static_cast<unsigned int>($1);
        unsigned int assign_index = static_cast<unsigned int>($2);

        std::vector<unsigned int> child_indices = {key_index, assign_index};
        for( unsigned int child_i : *$array ) child_indices.push_back(child_i);
        delete $array;
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
        | start object{
            interpreter.add_root_child_index(static_cast<unsigned int>($2));
        }



 /*** END RULES - Change the GetPot grammar rules above ***/

%% /*** Additional Code ***/
namespace wasp{
void GetPotParser::error(const GetPotParser::location_type& l,
                           const std::string& m)
{
    interpreter.error(l, m);
}
}; // end of namespace
