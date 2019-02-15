%{ /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>

%}

/*** yacc/bison Declarations ***/

%code requires{
#include <memory>
#include "waspcore/utils.h"
#include "waspcore/decl.h"
}

/* Require bison 3 or later */
%require "3"
%output "VIIParser.cpp"
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
/* %name-prefix "wasp" */
%define api.namespace {wasp}

/* set the parser's class identifier */
%define parser_class_name {VIIParser}

/* keep track of the current position within the input */
%locations
%initial-action
{
    // initialize the initial location object
    @$.begin.filename = @$.end.filename = &interpreter.stream_name();
    @$.begin.line = @$.end.line = interpreter.start_line();
    @$.begin.column = @$.end.column = interpreter.start_column();
    lexer = std::make_shared<VIILexerImpl>(interpreter,&input_stream);
};

/* The interpreter is passed by reference to the parser and to the VIILexer. This
 * provides a simple but effective pure interface, not relying on global
 * variables. */
%parse-param { class AbstractInterpreter& interpreter }
             {std::istream &input_stream}
             {std::shared_ptr<class VIILexerImpl> lexer}

/* verbose error messages */
%error-verbose

 /*** BEGIN EXAMPLE - Change the wasp grammar's tokens below ***/

%union {
        std::size_t token_index;
        std::size_t node_index;
        std::size_t stage_index;
}

%token                  END          0  "end of file"
%token                  EOL             "end of line"

%token <token_index>   MINUS            "-"
%token <token_index>   ASSIGN           "="
%token <token_index>   WASP_COMMA           ","
%token <token_index>   SEMICOLON            ";"

%token <token_index>    INTEGER         "integer"
%token <token_index>    DOUBLE          "double"
%token <token_index>    STRING          "string"
%token <token_index>    QSTRING          "quoted string"
%token <token_index>    COMMENT           "comment"
%token <token_index>    RBRACKET           "right bracket"
%token <token_index>    LBRACKET           "left bracket"
%token <token_index>    FSLASH             "forward slash"
%token <token_index>    FILE              "file include"

%type <token_index> PRIMITIVE

%type <node_index>  decl lbracket rbracket fslash assign
%type <node_index>  comma semicolon
%type <node_index>  value key_value part path decl_or_key_value
%type <stage_index>  command_part block
%type <node_index>  comment include include_file

%{

#include "VIInterpreter.h"
#include "VIINodeView.h"
#include "VIILexer.h"

#include "waspcore/wasp_bug.h"

/* this "connects" the bison parser in the interpreter to the flex VIILexer class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the interpreter context. */
#undef yylex
#define yylex lexer->lex

%}

%% /*** Grammar Rules ***/

 /*** BEGIN - Change the wasp grammar rules below ***/
include : FILE
        {
            auto token_index = $1;
            $$ = interpreter.push_leaf(wasp::FILE,"decl",token_index);
        }
comma : WASP_COMMA
        {
            auto token_index = $1;
            $$ = interpreter.push_leaf(wasp::WASP_COMMA,",",token_index);
        }
semicolon : SEMICOLON
        {
            auto token_index = $1;
            $$ = interpreter.push_leaf(wasp::TERM,";",token_index);
        }
assign : ASSIGN
        {
            auto token_index = $1;
            $$ = interpreter.push_leaf(wasp::ASSIGN,"=",token_index);
        }

fslash : FSLASH
    {
        auto token_index = ($1);
        $$ = interpreter.push_leaf(wasp::DIVIDE,"/",token_index);
    }
rbracket : RBRACKET
    {
        auto token_index = ($1);
        $$ = interpreter.push_leaf(wasp::RBRACKET,"]",token_index);
    }
lbracket : LBRACKET
    {
        auto token_index = ($1);
        $$ = interpreter.push_leaf(wasp::LBRACKET,"[",token_index);
    }

PRIMITIVE : QSTRING | INTEGER | DOUBLE | MINUS

value : PRIMITIVE
{
    size_t token_index = ($1);
    $$ = interpreter.push_leaf(wasp::VALUE,"value"
                     ,token_index);
}
key_value : value
        | STRING
{
    size_t token_index = ($1);
    $$ = interpreter.push_leaf(wasp::VALUE,"value"
                     ,token_index);
}

path : STRING
        {
            size_t token_index = ($1);
            $$ = interpreter.push_leaf(wasp::VALUE,"path"
                             ,token_index);
        }
        | QSTRING
        {
            size_t token_index = ($1);
            $$ = interpreter.push_leaf(wasp::VALUE,"path"
                             ,token_index);
        }

include_file : include path
        {

            std::vector<size_t> child_indices = {$1,$2};
            $$ = interpreter.push_parent(wasp::FILE
                                         // include
                                         //  |_ decl (include)
                                         //  |_ value (path/to/file)
                                        ,"incl"
                                        ,child_indices);
            interpreter.load_document($$, wasp::trim(interpreter.data($2)," "));
        }


decl : STRING
    {
        auto token_index = ($1);
        std::string quote_less_data = interpreter.token_data(token_index);
        quote_less_data = wasp::strip_quotes(quote_less_data);
        $$ = interpreter.push_leaf(wasp::DECL
                                   ,"decl"
                                   ,token_index);
    }
decl_or_key_value :  decl assign key_value
        {
            std::string quote_less_data = interpreter.data($1);
            quote_less_data = wasp::strip_quotes(quote_less_data);
            std::vector<size_t> child_indices = {$1,$2,$3};
            $$ = interpreter.push_parent(wasp::KEYED_VALUE
                                         // use the data instead of the name
                                         // this provides the following tree
                                         // data
                                         //  |_ decl (data)
                                         //  |_ = (=)
                                         //  |_ value (1.2..blah)
                                        ,quote_less_data.c_str()
                                        ,child_indices);
        } | decl
part : value | fslash | comment
        | decl_or_key_value | comma | semicolon

command_part : part {

        auto token_type = interpreter.node_token_type($1);
        auto node_type = interpreter.type($1);
        auto staged_type = interpreter.staged_type(interpreter.staged_count()-1);

        bool is_key_value = node_type == wasp::KEYED_VALUE;
        // If this is a potential start of a new command        
        wasp_check(interpreter.definition());
        const auto& child_indices = interpreter.staged_child_indices(interpreter.staged_count()-1);

        // Accumulate non-decorative staged child count
        // This cannot be done with the node view because the node is staged and
        // has not been committed to the tree, yet.
        size_t staged_child_count = 0;
        for ( const auto&  c_index : child_indices)
        {
            auto child_node_type = interpreter.type(c_index);
            if ( child_node_type != wasp::COMMENT
                    && child_node_type != wasp::WASP_COMMA
                    && child_node_type != wasp::TERM)
            {
                ++staged_child_count;
            }
        }
        auto prev_part_line = @1.end.line;  // initialize to current line
        if (!child_indices.empty())
        {
            prev_part_line = interpreter.node_token_line(child_indices.back());
        }
        bool is_named = interpreter.definition()->has("_name");

        std::string index_name = is_named ? "_"+std::to_string(staged_child_count-1)
                                          : "_"+std::to_string(staged_child_count);
        std::string even_odd_name = (is_named?staged_child_count:staged_child_count-1)%2 == 0
                                    ? "_even" : "_odd";

        // Check for scenario where comment is trailing on a different line
        if ( wasp::COMMENT == token_type
                && @1.end.line !=  prev_part_line
                && staged_type  != wasp::OBJECT
                && interpreter.staged_count() > 1)
        {
            // this comment belongs to parent scope
            // terminate the current staged data
            interpreter.commit_staged(interpreter.staged_count()-1);

            // Stage
            $$ = interpreter.push_staged_child($1);
        }
        else if ( wasp::COMMENT == token_type
                || wasp::WASP_COMMA == token_type
                || wasp::TERM == token_type)
        {
            $$ = interpreter.push_staged_child($1);
            // terminator ';' commits the current stage
            if ( wasp::TERM == token_type && staged_child_count > 0
                 && interpreter.staged_count() > 1)
            {
                interpreter.commit_staged(interpreter.staged_count()-1);
            }
        }
        // if there are stages, and the existing stage only contains
        // the declarator (child_count==1), and the block/command is named
        // we need to consume/recast the first child as the '_name' node
        else if ( interpreter.staged_count() > 1
             && staged_child_count == 1
             && is_named )
        {
            interpreter.set_type($1, wasp::IDENTIFIER);
            bool name_set_success = interpreter.set_name($1, "_name");
            wasp_check(name_set_success);
            $$ = interpreter.push_staged_child($1);
        }
        // If staged child index is aliased to a named component
        // we need to capture it appropriately
        else if (interpreter.staged_count() > 1
                && staged_child_count >= 1
                && interpreter.definition()->has(index_name) )
        {
           interpreter.definition()->delta(index_name, index_name);
           interpreter.set_type($1, wasp::VALUE);
           bool name_set_success = interpreter.set_name($1, index_name.c_str());
           wasp_check(name_set_success);
           $$ = interpreter.push_staged_child($1);
        }
        else if ( is_key_value ||
                  token_type == wasp::STRING ||
                  token_type == wasp::QUOTED_STRING)
        {
            std::string data = is_key_value ? interpreter.name($1)
                                            : interpreter.data($1);
            int delta = interpreter.definition()->delta(data, data);
            if( -1 == delta ) // no adjustment, not a command
            {
                // TODO cleanup duplicate code
                if (interpreter.staged_count() > 1
                        && staged_child_count >= 1
                        && interpreter.definition()->has(even_odd_name) )
                {
                   interpreter.definition()->delta(even_odd_name, even_odd_name);
                   interpreter.set_type($1, wasp::VALUE);
                   bool name_set_success = interpreter.set_name($1, even_odd_name.c_str());
                   wasp_check(name_set_success);
                   $$ = interpreter.push_staged_child($1);
                }
                // the string is not a new command, capture as a value
                // correct part name and type to be decl
                // must occur prior to prior stage commital
                else{
                    interpreter.set_type($1, wasp::VALUE);
                    bool name_set_success = interpreter.set_name($1, "value");
                    wasp_check(name_set_success);
                    $$ = interpreter.push_staged_child($1);
                }
            }
            else{
                // if nothing has been staged and we are a nested document
                // we need to update definition
                if( staged_child_count == 0 && interpreter.staged_count() == 1
                        && interpreter.document_parent() != nullptr)
                {
                    auto* parent_doc = interpreter.document_parent();
                    while (delta > 0)
                    {
                        auto* parent_definition = interpreter.definition()->parent();
                        interpreter.set_current_definition(parent_definition);
                        wasp_check(static_cast<int>(parent_doc->staged_count()) > delta);
                        parent_doc->commit_staged(parent_doc->staged_count()-1);
                        --delta;
                    }
                }
                else
                {
                    wasp_ensure( delta < static_cast<int>(interpreter.staged_count()) );
                    // commit prior stages
                    while( delta > 0 ){
                        if ( interpreter.staged_count() == 0 ) // user error
                        {
                            error(@1, "'"+data+"' has been identified, but belongs to a different scope.");
                            interpreter.set_failed(true);
                        }
                        else
                        {
                            interpreter.commit_staged(interpreter.staged_count()-1);
                        }
                        --delta;
                    }
                }

                if ( is_key_value )
                {
                    $$ = interpreter.push_staged_child($1);
                }
                else
                {
                    std::vector<size_t> child_indices = {$1};
                    $$ = interpreter.push_staged(wasp::ARRAY // commands are
                                            ,data.c_str()
                                            ,child_indices);
                }
            }
        }
        // if staged index
        else if (interpreter.staged_count() > 1
                && staged_child_count >= 1
                && interpreter.definition()->has(even_odd_name) )
        {
           interpreter.definition()->delta(even_odd_name, even_odd_name);
           interpreter.set_type($1, wasp::VALUE);
           bool name_set_success = interpreter.set_name($1, even_odd_name.c_str());
           wasp_check(name_set_success);
           $$ = interpreter.push_staged_child($1);
        }
        // This is a part of a command, stage in existing stage
        else
        {
            $$ = interpreter.push_staged_child($1);
        }
    }
    | include_file
    {
        // assume the included content will be a child of the existing
        // staged content.
        $$ = interpreter.push_staged_child($1);
    }

comment : COMMENT
        {
            auto token_index = ($1);
            $$ = interpreter.push_leaf(wasp::COMMENT,"comment",token_index);
        }
block : lbracket decl rbracket
    {
        // Block is top level parse construct
        // It closes/commits existing stages
        while (interpreter.staged_count() > 1)
        {
            interpreter.commit_staged(interpreter.staged_count() - 1);
        }
        std::string data = interpreter.data($2);
        int delta = interpreter.definition()->delta(data, data);
        if( -1 == delta ) // no adjustment, not a command
        {
            error(@2, "'"+data+"' is unknown.");
            interpreter.set_failed(true);
        }
        else
        {
            std::vector<size_t> child_indices = {$lbracket, $decl, $rbracket};
            // top level blocks are objects
            $$ = interpreter.push_staged(wasp::OBJECT
                                        ,data.c_str()
                                        ,child_indices);
        }
    }

start   : /** empty files are not syntax errors **/
       | start block{
           if(interpreter.single_parse() )
           {
               lexer->rewind();
               YYACCEPT;
           }
       }
        | start command_part{
            if(interpreter.single_parse() )
            {
                lexer->rewind();
                YYACCEPT;
            }
        }



 /*** END RULES - Change the wasp grammar rules above ***/

%% /*** Additional Code ***/

void wasp::VIIParser::error(const VIIParser::location_type& l,
                           const std::string& m)
{
    interpreter.error_stream()<<l<<": "<<m<<std::endl;
}
