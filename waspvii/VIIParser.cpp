// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.
#line 1 "VIIParser.bison" // lalr1.cc:404
 /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>


#line 44 "VIIParser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "VIIParser.hpp"

// User implementation prologue.
#line 92 "VIIParser.bison" // lalr1.cc:412


#include "VIInterpreter.h"
#include "VIINodeView.h"
#include "VIILexer.h"

#include "waspcore/wasp_bug.h"

/* this "connects" the bison parser in the interpreter to the flex VIILexer class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the interpreter context. */
#undef yylex
#define yylex lexer->lex


#line 73 "VIIParser.cpp" // lalr1.cc:412


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 35 "VIIParser.bison" // lalr1.cc:479
namespace wasp {
#line 159 "VIIParser.cpp" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  VIIParser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  VIIParser::VIIParser (class AbstractInterpreter& interpreter_yyarg, std::istream &input_stream_yyarg, std::shared_ptr<class VIILexerImpl> lexer_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      interpreter (interpreter_yyarg),
      input_stream (input_stream_yyarg),
      lexer (lexer_yyarg)
  {}

  VIIParser::~VIIParser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  VIIParser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  VIIParser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  VIIParser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
    value = other.value;
  }


  template <typename Base>
  inline
  VIIParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  VIIParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  inline
  VIIParser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  VIIParser::basic_symbol<Base>::clear ()
  {
    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  VIIParser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  VIIParser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
    location = s.location;
  }

  // by_type.
  inline
  VIIParser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  VIIParser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  VIIParser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  VIIParser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  VIIParser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  VIIParser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  VIIParser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  VIIParser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  VIIParser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  VIIParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  VIIParser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  VIIParser::symbol_number_type
  VIIParser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  VIIParser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  VIIParser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    value = that.value;
    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  VIIParser::stack_symbol_type&
  VIIParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  VIIParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YYUSE (yysym.type_get ());
  }

#if YYDEBUG
  template <typename Base>
  void
  VIIParser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  VIIParser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  VIIParser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  VIIParser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  VIIParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  VIIParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  VIIParser::debug_level_type
  VIIParser::debug_level () const
  {
    return yydebug_;
  }

  void
  VIIParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline VIIParser::state_type
  VIIParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  VIIParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  VIIParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  VIIParser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    // User initialization code.
    #line 43 "VIIParser.bison" // lalr1.cc:741
{
    // initialize the initial location object
    yyla.location.begin.filename = yyla.location.end.filename = &interpreter.stream_name();
    yyla.location.begin.line = yyla.location.end.line = interpreter.start_line();
    yyla.location.begin.column = yyla.location.end.column = interpreter.start_column();
    lexer = std::make_shared<VIILexerImpl>(interpreter,&input_stream);
}

#line 543 "VIIParser.cpp" // lalr1.cc:741

    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 112 "VIIParser.bison" // lalr1.cc:859
    {
            auto token_index = (yystack_[0].value.token_index);
            (yylhs.value.node_index) = interpreter.push_leaf(wasp::FILE,"decl",token_index);
        }
#line 656 "VIIParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 117 "VIIParser.bison" // lalr1.cc:859
    {
            auto token_index = (yystack_[0].value.token_index);
            (yylhs.value.node_index) = interpreter.push_leaf(wasp::ASSIGN,"=",token_index);
        }
#line 665 "VIIParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 123 "VIIParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::DIVIDE,"/",token_index);
    }
#line 674 "VIIParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 128 "VIIParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::RBRACKET,"]",token_index);
    }
#line 683 "VIIParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 133 "VIIParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::LBRACKET,"[",token_index);
    }
#line 692 "VIIParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 141 "VIIParser.bison" // lalr1.cc:859
    {
    size_t token_index = ((yystack_[0].value.token_index));
    (yylhs.value.node_index) = interpreter.push_leaf(wasp::VALUE,"value"
                     ,token_index);
}
#line 702 "VIIParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 148 "VIIParser.bison" // lalr1.cc:859
    {
    size_t token_index = ((yystack_[0].value.token_index));
    (yylhs.value.node_index) = interpreter.push_leaf(wasp::VALUE,"value"
                     ,token_index);
}
#line 712 "VIIParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 155 "VIIParser.bison" // lalr1.cc:859
    {
            size_t token_index = ((yystack_[0].value.token_index));
            (yylhs.value.node_index) = interpreter.push_leaf(wasp::VALUE,"path"
                             ,token_index);
        }
#line 722 "VIIParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 161 "VIIParser.bison" // lalr1.cc:859
    {
            size_t token_index = ((yystack_[0].value.token_index));
            (yylhs.value.node_index) = interpreter.push_leaf(wasp::VALUE,"path"
                             ,token_index);
        }
#line 732 "VIIParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 168 "VIIParser.bison" // lalr1.cc:859
    {

            std::vector<size_t> child_indices = {(yystack_[1].value.node_index),(yystack_[0].value.node_index)};
            (yylhs.value.node_index) = interpreter.push_parent(wasp::FILE
                                         // include
                                         //  |_ decl (include)
                                         //  |_ value (path/to/file)
                                        ,"incl"
                                        ,child_indices);
            interpreter.load_document((yylhs.value.node_index), wasp::trim(interpreter.data((yystack_[0].value.node_index))," "));
        }
#line 748 "VIIParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 182 "VIIParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        std::string quote_less_data = interpreter.token_data(token_index);
        quote_less_data = wasp::strip_quotes(quote_less_data);
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::DECL
                                   ,"decl"
                                   ,token_index);
    }
#line 761 "VIIParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 191 "VIIParser.bison" // lalr1.cc:859
    {
            std::string quote_less_data = interpreter.data((yystack_[2].value.node_index));
            quote_less_data = wasp::strip_quotes(quote_less_data);
            std::vector<size_t> child_indices = {(yystack_[2].value.node_index),(yystack_[1].value.node_index),(yystack_[0].value.node_index)};
            (yylhs.value.node_index) = interpreter.push_parent(wasp::KEYED_VALUE
                                         // use the data instead of the name
                                         // this provides the following tree
                                         // data
                                         //  |_ decl (data)
                                         //  |_ = (=)
                                         //  |_ value (1.2..blah)
                                        ,quote_less_data.c_str()
                                        ,child_indices);
        }
#line 780 "VIIParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 208 "VIIParser.bison" // lalr1.cc:859
    {

        auto token_type = interpreter.node_token_type((yystack_[0].value.node_index));
        // If this is a potential start of a new command
        std::string data = interpreter.data((yystack_[0].value.node_index));
        wasp_check(interpreter.definition());
        const auto& child_indices = interpreter.staged_child_indices(interpreter.staged_count()-1);

        // Accumumate non-decorative staged child count
        // This cannot be done with the node view because the node is staged and
        // has not been committed to the tree, yet.
        size_t staged_child_count = 0;
        for ( const auto&  c_index : child_indices)
        {
            if ( wasp::COMMENT != interpreter.type(c_index) )
            {
                ++staged_child_count;
            }
        }
        bool is_named = interpreter.definition()->has("_name");

        std::string index_name = is_named ? "_"+std::to_string(staged_child_count-1)
                                          : "_"+std::to_string(staged_child_count);
        std::string even_odd_name = (is_named?staged_child_count:staged_child_count-1)%2 == 0
                                    ? "_even" : "_odd";

        if ( wasp::COMMENT == token_type )
        {
            (yylhs.value.stage_index) = interpreter.push_staged_child((yystack_[0].value.node_index));
        }
        // if there are stages, and the existing stage only contains
        // the declarator (child_count==1), and the block/command is named
        // we need to consume/recast the first child as the '_name' node
        else if ( interpreter.staged_count() > 1
             && staged_child_count == 1
             && is_named )
        {
            interpreter.set_type((yystack_[0].value.node_index), wasp::IDENTIFIER);
            bool name_set_success = interpreter.set_name((yystack_[0].value.node_index), "_name");
            wasp_check(name_set_success);
            (yylhs.value.stage_index) = interpreter.push_staged_child((yystack_[0].value.node_index));
        }
        // If staged child index is aliased to a named component
        // we need to capture it appropriately
        else if (interpreter.staged_count() > 1
                && staged_child_count >= 1
                && interpreter.definition()->has(index_name) )
        {
           interpreter.definition()->delta(index_name, index_name);
           interpreter.set_type((yystack_[0].value.node_index), wasp::VALUE);
           bool name_set_success = interpreter.set_name((yystack_[0].value.node_index), index_name.c_str());
           wasp_check(name_set_success);
           (yylhs.value.stage_index) = interpreter.push_staged_child((yystack_[0].value.node_index));
        }
        else if ( token_type == wasp::STRING || token_type == wasp::QUOTED_STRING)
        {
            int delta = interpreter.definition()->delta(data, data);
            if( -1 == delta ) // no adjustment, not a command
            {
                // TODO cleanup duplicate code
                if (interpreter.staged_count() > 1
                        && staged_child_count >= 1
                        && interpreter.definition()->has(even_odd_name) )
                {
                   interpreter.definition()->delta(even_odd_name, even_odd_name);
                   interpreter.set_type((yystack_[0].value.node_index), wasp::VALUE);
                   bool name_set_success = interpreter.set_name((yystack_[0].value.node_index), even_odd_name.c_str());
                   wasp_check(name_set_success);
                   (yylhs.value.stage_index) = interpreter.push_staged_child((yystack_[0].value.node_index));
                }
                // the string is not a new command, capture as a value
                // correct part name and type to be decl
                // must occur prior to prior stage commital
                else{
                    interpreter.set_type((yystack_[0].value.node_index), wasp::VALUE);
                    bool name_set_success = interpreter.set_name((yystack_[0].value.node_index), "value");
                    wasp_check(name_set_success);
                    (yylhs.value.stage_index) = interpreter.push_staged_child((yystack_[0].value.node_index));
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
                            error(yystack_[0].location, "'"+data+"' has been identified, but belongs to a different scope.");
                            interpreter.set_failed(true);

                        }
                        else
                        {
                            interpreter.commit_staged(interpreter.staged_count()-1);
                        }
                        --delta;
                    }
                }
                std::vector<size_t> child_indices = {(yystack_[0].value.node_index)};
                (yylhs.value.stage_index) = interpreter.push_staged(wasp::ARRAY // commands are
                                        ,data.c_str()
                                        ,child_indices);
            }
        }
        // if staged index
        else if (interpreter.staged_count() > 1
                && staged_child_count >= 1
                && interpreter.definition()->has(even_odd_name) )
        {
           interpreter.definition()->delta(even_odd_name, even_odd_name);
           interpreter.set_type((yystack_[0].value.node_index), wasp::VALUE);
           bool name_set_success = interpreter.set_name((yystack_[0].value.node_index), even_odd_name.c_str());
           wasp_check(name_set_success);
           (yylhs.value.stage_index) = interpreter.push_staged_child((yystack_[0].value.node_index));
        }
        // This is a part of a command, stage in existing stage
        else
        {
            (yylhs.value.stage_index) = interpreter.push_staged_child((yystack_[0].value.node_index));
        }
    }
#line 922 "VIIParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 346 "VIIParser.bison" // lalr1.cc:859
    {
        // assume the included content will be a child of the existing
        // staged content.
        (yylhs.value.stage_index) = interpreter.push_staged_child((yystack_[0].value.node_index));
    }
#line 932 "VIIParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 353 "VIIParser.bison" // lalr1.cc:859
    {
            auto token_index = ((yystack_[0].value.token_index));
            (yylhs.value.node_index) = interpreter.push_leaf(wasp::COMMENT,"comment",token_index);
        }
#line 941 "VIIParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 358 "VIIParser.bison" // lalr1.cc:859
    {
        // Block is top level parse construct
        // It closes/commits existing stages
        while (interpreter.staged_count() > 1)
        {
            interpreter.commit_staged(interpreter.staged_count() - 1);
        }
        std::string data = interpreter.data((yystack_[1].value.node_index));
        int delta = interpreter.definition()->delta(data, data);
        if( -1 == delta ) // no adjustment, not a command
        {
            error(yystack_[1].location, "'"+data+"' is unknown.");
            interpreter.set_failed(true);
        }
        else
        {
            std::vector<size_t> child_indices = {(yystack_[2].value.node_index), (yystack_[1].value.node_index), (yystack_[0].value.node_index)};
            // top level blocks are objects
            (yylhs.value.stage_index) = interpreter.push_staged(wasp::OBJECT
                                        ,data.c_str()
                                        ,child_indices);
        }
    }
#line 969 "VIIParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 383 "VIIParser.bison" // lalr1.cc:859
    {
           if(interpreter.single_parse() )
           {
               lexer->rewind();
               YYACCEPT;
           }
       }
#line 981 "VIIParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 390 "VIIParser.bison" // lalr1.cc:859
    {
            if(interpreter.single_parse() )
            {
                lexer->rewind();
                YYACCEPT;
            }
        }
#line 993 "VIIParser.cpp" // lalr1.cc:859
    break;


#line 997 "VIIParser.cpp" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  VIIParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  VIIParser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char VIIParser::yypact_ninf_ = -14;

  const signed char VIIParser::yytable_ninf_ = -1;

  const signed char
  VIIParser::yypact_[] =
  {
     -14,     0,   -14,   -14,   -14,   -14,   -14,   -14,   -14,   -14,
     -14,   -14,    -7,   -14,    -5,   -14,   -14,   -14,     6,   -14,
     -14,   -14,   -14,   -14,   -14,   -14,   -14,    -6,   -14,    11,
     -14,   -14,   -14,   -14,   -14
  };

  const unsigned char
  VIIParser::yydefact_[] =
  {
      28,     0,     1,    10,     8,     9,    17,     7,    26,     6,
       4,     2,     0,    21,     0,    11,    20,    25,    19,    23,
      24,    30,    22,    29,    14,    15,    16,     0,     3,     0,
       5,    27,    13,    12,    18
  };

  const signed char
  VIIParser::yypgoto_[] =
  {
     -14,   -14,   -14,   -14,   -14,   -14,   -14,   -13,   -14,   -14,
     -14,     7,   -14,   -14,   -14,   -14,   -14,   -14
  };

  const signed char
  VIIParser::yydefgoto_[] =
  {
      -1,    12,    29,    13,    31,    14,    15,    16,    34,    26,
      17,    18,    19,    20,    21,    22,    23,     1
  };

  const unsigned char
  VIIParser::yytable_[] =
  {
       2,    24,    25,     6,     3,    30,     4,     5,     6,     7,
       8,    28,     9,    10,    11,     3,    33,     4,     5,    32,
       7,    27
  };

  const unsigned char
  VIIParser::yycheck_[] =
  {
       0,     8,     9,     8,     4,    11,     6,     7,     8,     9,
      10,     5,    12,    13,    14,     4,    29,     6,     7,     8,
       9,    14
  };

  const unsigned char
  VIIParser::yystos_[] =
  {
       0,    32,     0,     4,     6,     7,     8,     9,    10,    12,
      13,    14,    16,    18,    20,    21,    22,    25,    26,    27,
      28,    29,    30,    31,     8,     9,    24,    26,     5,    17,
      11,    19,     8,    22,    23
  };

  const unsigned char
  VIIParser::yyr1_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    21,    21,
      21,    22,    23,    23,    24,    24,    25,    26,    27,    27,
      28,    28,    28,    28,    29,    29,    30,    31,    32,    32,
      32
  };

  const unsigned char
  VIIParser::yyr2_[] =
  {
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     0,     2,
       2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const VIIParser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"end of line\"", "\"-\"",
  "\"=\"", "\"integer\"", "\"double\"", "\"string\"", "\"quoted string\"",
  "\"comment\"", "\"right bracket\"", "\"left bracket\"",
  "\"forward slash\"", "\"file include\"", "$accept", "include", "assign",
  "fslash", "rbracket", "lbracket", "PRIMITIVE", "value", "key_value",
  "path", "include_file", "decl", "decl_or_key_value", "part",
  "command_part", "comment", "block", "start", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  VIIParser::yyrline_[] =
  {
       0,   111,   111,   116,   122,   127,   132,   138,   138,   138,
     138,   140,   146,   147,   154,   160,   167,   181,   190,   204,
     205,   205,   205,   206,   208,   345,   352,   357,   382,   383,
     390
  };

  // Print the state stack on the debug stream.
  void
  VIIParser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  VIIParser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
  VIIParser::token_number_type
  VIIParser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14
    };
    const unsigned int user_token_number_max_ = 269;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

#line 35 "VIIParser.bison" // lalr1.cc:1167
} // wasp
#line 1436 "VIIParser.cpp" // lalr1.cc:1167
#line 402 "VIIParser.bison" // lalr1.cc:1168
 /*** Additional Code ***/

void wasp::VIIParser::error(const VIIParser::location_type& l,
                           const std::string& m)
{
    interpreter.error_stream()<<l<<": "<<m<<std::endl;
}
