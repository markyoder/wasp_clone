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
#line 1 "SONParser.bison" // lalr1.cc:404
 /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>

#line 43 "SONParser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "SONParser.hpp"

// User implementation prologue.
#line 135 "SONParser.bison" // lalr1.cc:412


#include "SONInterpreter.h"
#include "SONLexer.h"

/* this "connects" the bison parser in the interpreter to the flex SONLexer class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the interpreter context. */
#undef yylex
#define yylex lexer->lex


#line 69 "SONParser.cpp" // lalr1.cc:412


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

#line 34 "SONParser.bison" // lalr1.cc:479
namespace wasp {
#line 155 "SONParser.cpp" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  SONParser::yytnamerr_ (const char *yystr)
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
  SONParser::SONParser (class AbstractInterpreter& interpreter_yyarg, std::istream &input_stream_yyarg, std::shared_ptr<class SONLexerImpl> lexer_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      interpreter (interpreter_yyarg),
      input_stream (input_stream_yyarg),
      lexer (lexer_yyarg)
  {}

  SONParser::~SONParser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  SONParser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  SONParser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  SONParser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
    value = other.value;
  }


  template <typename Base>
  inline
  SONParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  SONParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  inline
  SONParser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  SONParser::basic_symbol<Base>::clear ()
  {
    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  SONParser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  SONParser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
    location = s.location;
  }

  // by_type.
  inline
  SONParser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  SONParser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  SONParser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  SONParser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  SONParser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  SONParser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  SONParser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  SONParser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  SONParser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  SONParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  SONParser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  SONParser::symbol_number_type
  SONParser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  SONParser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  SONParser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    value = that.value;
    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  SONParser::stack_symbol_type&
  SONParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  SONParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    switch (yysym.type_get ())
    {
            case 81: // key_declaration

#line 134 "SONParser.bison" // lalr1.cc:614
        { delete (yysym.value.node_indices); }
#line 410 "SONParser.cpp" // lalr1.cc:614
        break;

      case 82: // declaration

#line 134 "SONParser.bison" // lalr1.cc:614
        { delete (yysym.value.node_indices); }
#line 417 "SONParser.cpp" // lalr1.cc:614
        break;

      case 83: // tag

#line 133 "SONParser.bison" // lalr1.cc:614
        { delete (yysym.value.node_indices); }
#line 424 "SONParser.cpp" // lalr1.cc:614
        break;

      case 87: // members

#line 133 "SONParser.bison" // lalr1.cc:614
        { delete (yysym.value.node_indices); }
#line 431 "SONParser.cpp" // lalr1.cc:614
        break;

      case 88: // array_members

#line 133 "SONParser.bison" // lalr1.cc:614
        { delete (yysym.value.node_indices); }
#line 438 "SONParser.cpp" // lalr1.cc:614
        break;


      default:
        break;
    }
  }

#if YYDEBUG
  template <typename Base>
  void
  SONParser::yy_print_ (std::ostream& yyo,
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
  SONParser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  SONParser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  SONParser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  SONParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  SONParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  SONParser::debug_level_type
  SONParser::debug_level () const
  {
    return yydebug_;
  }

  void
  SONParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline SONParser::state_type
  SONParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  SONParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  SONParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  SONParser::parse ()
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
    #line 42 "SONParser.bison" // lalr1.cc:741
{
    // initialize the initial location object
    yyla.location.begin.filename = yyla.location.end.filename = &interpreter.stream_name();
    yyla.location.begin.line = yyla.location.end.line = interpreter.start_line();
    yyla.location.begin.column = yyla.location.end.column = interpreter.start_column();
    lexer = std::make_shared<SONLexerImpl>(interpreter,&input_stream);
}

#line 579 "SONParser.cpp" // lalr1.cc:741

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
#line 152 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::FILL_EXPR,"filler",token_index);
    }
#line 692 "SONParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 157 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::WASP_COMMA,",",token_index);
    }
#line 701 "SONParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 167 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::MULTIPLY,"*",token_index);
    }
#line 710 "SONParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 172 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::DIVIDE,"/",token_index);
    }
#line 719 "SONParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 178 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::PLUS,"+",token_index);
    }
#line 728 "SONParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 183 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::MINUS,"-",token_index);
    }
#line 737 "SONParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 189 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::EXPONENT,"^",token_index);
    }
#line 746 "SONParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 198 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::EQ,"==",token_index);
    }
#line 755 "SONParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 203 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::NEQ,"!=",token_index);
    }
#line 764 "SONParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 208 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::GTE,">=",token_index);
    }
#line 773 "SONParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 213 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::GT,">",token_index);
    }
#line 782 "SONParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 218 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::LTE,"<=",token_index);
    }
#line 791 "SONParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 223 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::LT,"<",token_index);
    }
#line 800 "SONParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 229 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::WASP_AND,"&&",token_index);
    }
#line 809 "SONParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 234 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::WASP_OR,"||",token_index);
    }
#line 818 "SONParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 240 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::UNARY_NOT,"!",token_index);
    }
#line 827 "SONParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 246 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::LPAREN,"(",token_index);
    }
#line 836 "SONParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 251 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::RPAREN,")",token_index);
    }
#line 845 "SONParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 256 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::LBRACE,"{",token_index);
    }
#line 854 "SONParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 261 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::RBRACE,"}",token_index);
    }
#line 863 "SONParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 266 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::LBRACKET,"[",token_index);
    }
#line 872 "SONParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 271 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::RBRACKET,"]",token_index);
    }
#line 881 "SONParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 280 "SONParser.bison" // lalr1.cc:859
    {
    size_t token_index = ((yystack_[0].value.token_index));
    (yylhs.value.node_index) = interpreter.push_leaf(wasp::VALUE,"value"
                     ,token_index);
}
#line 891 "SONParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 301 "SONParser.bison" // lalr1.cc:859
    {
          size_t left_i = ((yystack_[2].value.node_index));
          size_t op_i = ((yystack_[1].value.node_index));
          size_t right_i = ((yystack_[0].value.node_index));
          std::vector<size_t> child_indices = {left_i
                                                     ,op_i
                                                     ,right_i
                                                     };

          (yylhs.value.node_index) = interpreter.push_parent(interpreter.type(op_i)
                                          ,"value"
                                          ,child_indices);
    }
#line 909 "SONParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 315 "SONParser.bison" // lalr1.cc:859
    {
        size_t left_i = ((yystack_[2].value.node_index));
        size_t op_i = ((yystack_[1].value.node_index));
        size_t right_i = ((yystack_[0].value.node_index));
        std::vector<size_t> child_indices = {left_i
                                                   ,op_i
                                                   ,right_i
                                                   };

        (yylhs.value.node_index) = interpreter.push_parent(interpreter.type(op_i)
                                        ,"value"
                                        ,child_indices);
    }
#line 927 "SONParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 329 "SONParser.bison" // lalr1.cc:859
    {
        size_t left_i = ((yystack_[2].value.node_index));
        size_t op_i = ((yystack_[1].value.node_index));
        size_t right_i = ((yystack_[0].value.node_index));
        std::vector<size_t> child_indices = {left_i
                                                   ,op_i
                                                   ,right_i
                                                   };

        (yylhs.value.node_index) = interpreter.push_parent(interpreter.type(op_i)
                                        ,"value"
                                        ,child_indices);
    }
#line 945 "SONParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 343 "SONParser.bison" // lalr1.cc:859
    {
        size_t left_i = ((yystack_[2].value.node_index));
        size_t op_i = ((yystack_[1].value.node_index));
        size_t right_i = ((yystack_[0].value.node_index));
        std::vector<size_t> child_indices = {left_i
                                                   ,op_i
                                                   ,right_i
                                                   };

        (yylhs.value.node_index) = interpreter.push_parent(interpreter.type(op_i)
                                        ,"value"
                                        ,child_indices);
    }
#line 963 "SONParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 357 "SONParser.bison" // lalr1.cc:859
    {
        size_t left_i = ((yystack_[2].value.node_index));
        size_t op_i = ((yystack_[1].value.node_index));
        size_t right_i = ((yystack_[0].value.node_index));
        std::vector<size_t> child_indices = {left_i
                                                   ,op_i
                                                   ,right_i
                                                   };

        (yylhs.value.node_index) = interpreter.push_parent(interpreter.type(op_i)
                                        ,"value"
                                        ,child_indices);
    }
#line 981 "SONParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 372 "SONParser.bison" // lalr1.cc:859
    {
        size_t left_i = ((yystack_[2].value.node_index));
        size_t op_i = ((yystack_[1].value.node_index));
        size_t right_i = ((yystack_[0].value.node_index));
        std::vector<size_t> child_indices = {left_i
                                                   ,op_i
                                                   ,right_i
                                                   };

        (yylhs.value.node_index) = interpreter.push_parent(interpreter.type(op_i)
                                        ,"value"
                                        ,child_indices);
    }
#line 999 "SONParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 386 "SONParser.bison" // lalr1.cc:859
    {
        size_t left_i = ((yystack_[2].value.node_index));
        size_t center_i = ((yystack_[1].value.node_index));
        size_t right_i = ((yystack_[0].value.node_index));
        std::vector<size_t> child_indices = {left_i
                                                   ,center_i
                                                   ,right_i
                                                   };

        (yylhs.value.node_index) = interpreter.push_parent(wasp::PARENTHESIS
                                        ,"value"
                                        ,child_indices);
    }
#line 1017 "SONParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 400 "SONParser.bison" // lalr1.cc:859
    {
        size_t op_i = ((yystack_[1].value.node_index));
        size_t right_i = ((yystack_[0].value.node_index));
        std::vector<size_t> child_indices = {op_i
                                                   ,right_i
                                                   };

        (yylhs.value.node_index) = interpreter.push_parent(interpreter.type(op_i)
                                        ,"value"
                                        ,child_indices);
    }
#line 1033 "SONParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 412 "SONParser.bison" // lalr1.cc:859
    {
        size_t op_i = ((yystack_[1].value.node_index));
        size_t right_i = ((yystack_[0].value.node_index));
        std::vector<size_t> child_indices = {op_i
                                                   ,right_i
                                                   };

        (yylhs.value.node_index) = interpreter.push_parent(interpreter.type(op_i)
                                        ,"value"
                                        ,child_indices);
    }
#line 1049 "SONParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 425 "SONParser.bison" // lalr1.cc:859
    {
    auto token_index = ((yystack_[0].value.token_index));
    (yylhs.value.node_index) = interpreter.push_leaf(wasp::EXECUTION_UNIT_END,"uoe_end",token_index);
}
#line 1058 "SONParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 430 "SONParser.bison" // lalr1.cc:859
    {
    auto token_index = ((yystack_[0].value.token_index));
    (yylhs.value.node_index) = interpreter.push_leaf(wasp::EXECUTION_UNIT_START,"uoe_start",token_index);
}
#line 1067 "SONParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 436 "SONParser.bison" // lalr1.cc:859
    {
        interpreter.set_type((yystack_[0].value.node_index), wasp::IDENTIFIER);
        interpreter.set_name((yystack_[0].value.node_index), "id");
        (yylhs.value.node_index) = (yystack_[0].value.node_index);
    }
#line 1077 "SONParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 442 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        std::string quote_less_data = interpreter.token_data(token_index);
        quote_less_data = wasp::strip_quotes(quote_less_data);
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::DECL
                                   ,"decl"
                                   ,token_index);
    }
#line 1090 "SONParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 451 "SONParser.bison" // lalr1.cc:859
    {
             auto token_index = ((yystack_[0].value.token_index));
             (yylhs.value.node_index) = interpreter.push_leaf(wasp::ASSIGN,"=",token_index);
            }
#line 1099 "SONParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 456 "SONParser.bison" // lalr1.cc:859
    {
             (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
             (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));

        }
#line 1109 "SONParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 463 "SONParser.bison" // lalr1.cc:859
    {
             (yylhs.value.node_indices) = new std::vector<size_t>();
             (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1118 "SONParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 468 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<size_t>();
            (yylhs.value.node_indices)->push_back((yystack_[3].value.node_index));
            (yylhs.value.node_indices)->push_back((yystack_[2].value.node_index));
            (yylhs.value.node_indices)->push_back((yystack_[1].value.node_index));
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1130 "SONParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 477 "SONParser.bison" // lalr1.cc:859
    {
        (yystack_[2].value.node_indices)->push_back((yystack_[1].value.node_index));
        (yystack_[2].value.node_indices)->push_back((yystack_[0].value.node_index));
        (yylhs.value.node_index) = interpreter.push_parent(wasp::ARRAY
                ,wasp::strip_quotes(interpreter.data((yystack_[2].value.node_indices)->front())).c_str()
                ,*(yystack_[2].value.node_indices));
        delete (yystack_[2].value.node_indices);
    }
#line 1143 "SONParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 486 "SONParser.bison" // lalr1.cc:859
    {
        (yystack_[2].value.node_indices)->push_back((yystack_[1].value.node_index));
        std::string name = interpreter.name((yystack_[2].value.node_indices)->front());
        (yylhs.value.node_index) = interpreter.push_parent(wasp::ARRAY
                                    , name.c_str()
                                        ,*(yystack_[2].value.node_indices));
        delete (yystack_[2].value.node_indices);
        error(yystack_[1].location, name+" has unmatched left bracket!");
        YYERROR;
    }
#line 1158 "SONParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 497 "SONParser.bison" // lalr1.cc:859
    {
        std::string name = interpreter.name((yystack_[3].value.node_indices)->front());
        auto last_component_type = interpreter.type((yystack_[3].value.node_indices)->back());
        // TODO capture partial definition
        if( (yystack_[1].value.node_indices)->size() ==0 ) error(yystack_[2].location, name+" has unmatched left bracket!");
        else if( last_component_type == wasp::ARRAY ) error(yystack_[2].location, name+" or one of its components has unmatched left bracket!");
        else error(yystack_[2].location, name+" has unmatched left bracket!");

        delete (yystack_[3].value.node_indices);
        YYERROR;
    }
#line 1174 "SONParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 509 "SONParser.bison" // lalr1.cc:859
    {
        // TODO capture partial definition
        std::string name = interpreter.name((yystack_[2].value.node_indices)->front());
        error(yystack_[1].location, name+" has unmatched left bracket!");
        delete (yystack_[2].value.node_indices);
        YYERROR;
    }
#line 1186 "SONParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 517 "SONParser.bison" // lalr1.cc:859
    {
        std::string name = interpreter.name((yystack_[3].value.node_indices)->front());
        auto last_component_type = interpreter.type((yystack_[3].value.node_indices)->back());
        // TODO capture partial definition
        if( (yystack_[1].value.node_indices)->size() ==0 ) error(yystack_[2].location, name+" has unmatched left bracket!");
        else if( last_component_type == wasp::ARRAY ) error(yystack_[2].location, name+" or one of its components has unmatched left bracket!");
        else error(yystack_[2].location, name+" has unmatched left bracket!");

        delete (yystack_[1].value.node_indices);
        delete (yystack_[3].value.node_indices);
        YYERROR;
    }
#line 1203 "SONParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 530 "SONParser.bison" // lalr1.cc:859
    {
        (yystack_[3].value.node_indices)->push_back((yystack_[2].value.node_index));
        for( std::size_t i = 0; i < (yystack_[1].value.node_indices)->size(); ++i )
        {
            (yystack_[3].value.node_indices)->push_back( (yystack_[1].value.node_indices)->at( i ) );
        }
        (yystack_[3].value.node_indices)->push_back((yystack_[0].value.node_index));
        (yylhs.value.node_index) = interpreter.push_parent(wasp::ARRAY
            ,wasp::strip_quotes(interpreter.data((yystack_[3].value.node_indices)->front())).c_str()
            ,*(yystack_[3].value.node_indices));
        delete (yystack_[3].value.node_indices);
        delete (yystack_[1].value.node_indices);

    }
#line 1222 "SONParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 545 "SONParser.bison" // lalr1.cc:859
    {
        (yystack_[2].value.node_indices)->push_back((yystack_[1].value.node_index));
        (yystack_[2].value.node_indices)->push_back((yystack_[0].value.node_index));
        (yylhs.value.node_index) = interpreter.push_parent(wasp::OBJECT
            ,wasp::strip_quotes(interpreter.data((yystack_[2].value.node_indices)->front())).c_str()
            ,*(yystack_[2].value.node_indices));
        delete (yystack_[2].value.node_indices);
    }
#line 1235 "SONParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 554 "SONParser.bison" // lalr1.cc:859
    {
        (yystack_[2].value.node_indices)->push_back((yystack_[1].value.node_index));
        std::string name = interpreter.data((yystack_[2].value.node_indices)->front());
        (yylhs.value.node_index) = interpreter.push_parent(wasp::OBJECT
                                     , name.c_str()
                                     , *(yystack_[2].value.node_indices));
        delete (yystack_[2].value.node_indices);
        error(yystack_[1].location, name+" has unmatched left brace!");
        YYERROR;
    }
#line 1250 "SONParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 565 "SONParser.bison" // lalr1.cc:859
    {
        // TODO capture partial definition
        std::string name = interpreter.data((yystack_[3].value.node_indices)->front());
        auto last_component_type = interpreter.type((yystack_[3].value.node_indices)->back());
        if( (yystack_[1].value.node_indices)->size() ==0 ) error(yystack_[2].location, name+" has unmatched left brace!");
        else if( last_component_type == wasp::OBJECT ) error(yystack_[2].location, name+" or one of its components has unmatched left brace!");
        else error(yystack_[2].location, name+" has unmatched left brace!");
        delete (yystack_[1].value.node_indices);
        delete (yystack_[3].value.node_indices);
        YYERROR;
    }
#line 1266 "SONParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 577 "SONParser.bison" // lalr1.cc:859
    {
        (yystack_[2].value.node_indices)->push_back((yystack_[1].value.node_index));
        std::string name = interpreter.data((yystack_[2].value.node_indices)->front());
        (yylhs.value.node_index) = interpreter.push_parent( wasp::OBJECT
                                     , name.c_str()
                                     , *(yystack_[2].value.node_indices));
        error(yystack_[1].location, name+" has unmatched left brace!");
        delete (yystack_[2].value.node_indices);
        YYERROR;
    }
#line 1281 "SONParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 588 "SONParser.bison" // lalr1.cc:859
    {
        // TODO capture partial definition
        std::string name = interpreter.data((yystack_[3].value.node_indices)->front());
        auto last_component_type = interpreter.type((yystack_[3].value.node_indices)->back());
        if( (yystack_[1].value.node_indices)->size() ==0 ) error(yystack_[2].location, name+" has unmatched left brace!");
        else if( last_component_type == wasp::OBJECT ) error(yystack_[2].location, name+" or one of its components has unmatched left brace!");
        else error(yystack_[2].location, name+" has unmatched left brace!");

        delete (yystack_[1].value.node_indices);
        delete (yystack_[3].value.node_indices);
        YYERROR;
    }
#line 1298 "SONParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 601 "SONParser.bison" // lalr1.cc:859
    {
        (yystack_[3].value.node_indices)->push_back((yystack_[2].value.node_index));
        for( std::size_t i = 0; i < (yystack_[1].value.node_indices)->size(); ++i )
        {
            (yystack_[3].value.node_indices)->push_back( (yystack_[1].value.node_indices)->at( i ) );
        }
        (yystack_[3].value.node_indices)->push_back((yystack_[0].value.node_index));
        (yylhs.value.node_index) = interpreter.push_parent(wasp::OBJECT
                                    ,wasp::strip_quotes(interpreter.data((yystack_[3].value.node_indices)->front())).c_str()
                                        ,*(yystack_[3].value.node_indices));
        delete (yystack_[3].value.node_indices);
        delete (yystack_[1].value.node_indices);
    }
#line 1316 "SONParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 617 "SONParser.bison" // lalr1.cc:859
    {
        (yystack_[1].value.node_indices)->push_back((yystack_[0].value.node_index));
        std::string quote_less_data = interpreter.data((yystack_[1].value.node_indices)->front());
        quote_less_data = wasp::strip_quotes(quote_less_data);
        (yylhs.value.node_index) = interpreter.push_parent(wasp::KEYED_VALUE
                                     // use the data instead of the name
                                     // this provides the following tree
                                     // data
                                     //  |_ decl (data)
                                     //  |_ = (=)
                                     //  |_ value (1.2..blah)
                                    ,quote_less_data.c_str()
                                    ,*(yystack_[1].value.node_indices));
        delete (yystack_[1].value.node_indices);
    }
#line 1336 "SONParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 635 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<size_t>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1345 "SONParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 640 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1354 "SONParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 645 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<size_t>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1363 "SONParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 650 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1372 "SONParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 655 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<size_t>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1381 "SONParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 660 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1390 "SONParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 665 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<size_t>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1399 "SONParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 670 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1408 "SONParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 675 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<size_t>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1417 "SONParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 680 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1426 "SONParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 685 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1435 "SONParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 692 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<size_t>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1444 "SONParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 697 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1453 "SONParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 703 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<size_t>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1462 "SONParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 708 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1471 "SONParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 713 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<size_t>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1480 "SONParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 718 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1489 "SONParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 723 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<size_t>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1498 "SONParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 728 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1507 "SONParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 733 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<size_t>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1516 "SONParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 738 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1525 "SONParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 743 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<size_t>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1534 "SONParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 748 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1543 "SONParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 753 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1552 "SONParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 759 "SONParser.bison" // lalr1.cc:859
    {
            auto token_index = ((yystack_[0].value.token_index));
            (yylhs.value.node_index) = interpreter.push_leaf(wasp::COMMENT,"comment",token_index);
        }
#line 1561 "SONParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 764 "SONParser.bison" // lalr1.cc:859
    {
            auto token_index = ((yystack_[0].value.token_index));
            (yylhs.value.node_index) = interpreter.push_leaf(wasp::DECL,"name",token_index);
        }
#line 1570 "SONParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 769 "SONParser.bison" // lalr1.cc:859
    { // account for an empty execution unit
            size_t start_i = ((yystack_[2].value.node_index));
            size_t name_i = ((yystack_[1].value.node_index));
            size_t end_i = ((yystack_[0].value.node_index));
            std::vector<size_t> child_indices = {start_i
                                                       ,name_i
                                                       ,end_i
                                                       };

            (yylhs.value.node_index) = interpreter.push_parent(wasp::EXECUTION_UNIT
                        ,wasp::strip_quotes(interpreter.data(name_i)).c_str()
                        ,child_indices);
       }
#line 1588 "SONParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 783 "SONParser.bison" // lalr1.cc:859
    { // execution unit with members
            size_t start_i = ((yystack_[3].value.node_index));
            size_t name_i = ((yystack_[2].value.node_index));
            size_t end_i = ((yystack_[0].value.node_index));
            std::vector<size_t> child_indices = {start_i
                                                       ,name_i
                                                       };
            for( std::size_t i = 0; i < (yystack_[1].value.node_indices)->size(); ++ i )
            {
                child_indices.push_back( (yystack_[1].value.node_indices)->at(i) );
            }
            child_indices.push_back(end_i);
            delete (yystack_[1].value.node_indices);
            (yylhs.value.node_index) = interpreter.push_parent(wasp::EXECUTION_UNIT
                        ,wasp::strip_quotes(interpreter.data(name_i)).c_str()
                        ,child_indices);
       }
#line 1610 "SONParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 803 "SONParser.bison" // lalr1.cc:859
    {
          // Check for prior staged blocks that may need to be committed.
          // Because blocks are the only SON construct that are staged (in addition to the root)
          // the stage count should be 1, if it is greater, the additional stages should be closed
          if (interpreter.staged_count() > 1)
          {
              // blocks cannot be nested, so there should only be 1 additional stage
              // root+prior block = 2 stages
              wasp_check(interpreter.staged_count() == 2);
              interpreter.commit_staged(interpreter.staged_count()-1);
          }

          size_t start_i = ((yystack_[2].value.node_index));
          size_t name_i = ((yystack_[1].value.node_index));
          size_t end_i = ((yystack_[0].value.node_index));
          std::vector<size_t> child_indices = {start_i
                                                     ,name_i
                                                     ,end_i
                                                     };

          std::string quote_less_data = interpreter.data((yystack_[1].value.node_index));
          quote_less_data = wasp::strip_quotes(quote_less_data);
          (yylhs.value.node_index) = interpreter.push_staged(wasp::OBJECT
                                    ,quote_less_data.c_str()
                                    ,child_indices);

      }
#line 1642 "SONParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 831 "SONParser.bison" // lalr1.cc:859
    {interpreter.push_staged_child(((yystack_[0].value.node_index))); if(interpreter.single_parse() ) {lexer->rewind();YYACCEPT;}}
#line 1648 "SONParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 832 "SONParser.bison" // lalr1.cc:859
    {interpreter.push_staged_child(((yystack_[0].value.node_index))); if(interpreter.single_parse() ) {lexer->rewind();YYACCEPT;}}
#line 1654 "SONParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 833 "SONParser.bison" // lalr1.cc:859
    {interpreter.push_staged_child(((yystack_[0].value.node_index))); if(interpreter.single_parse() ) {lexer->rewind();YYACCEPT;}}
#line 1660 "SONParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 834 "SONParser.bison" // lalr1.cc:859
    {interpreter.push_staged_child(((yystack_[0].value.node_index))); if(interpreter.single_parse() ) {lexer->rewind();YYACCEPT;}}
#line 1666 "SONParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 835 "SONParser.bison" // lalr1.cc:859
    {interpreter.push_staged_child(((yystack_[0].value.node_index)));if(interpreter.single_parse() ) {YYACCEPT;}}
#line 1672 "SONParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 836 "SONParser.bison" // lalr1.cc:859
    { /*Node staging occurs in block rule*/;if(interpreter.single_parse() ) {YYACCEPT;}}
#line 1678 "SONParser.cpp" // lalr1.cc:859
    break;


#line 1682 "SONParser.cpp" // lalr1.cc:859
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
  SONParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  SONParser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
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


  const signed char SONParser::yypact_ninf_ = -56;

  const signed char SONParser::yytable_ninf_ = -59;

  const short int
  SONParser::yypact_[] =
  {
     -56,   190,   -56,   -56,   -56,   -56,   -56,   -56,   -56,   -56,
     -56,   -56,   -56,    48,   -56,   -27,    33,   205,    14,    13,
     -56,   -56,   -56,   -56,   -56,   -56,    41,   -56,   -56,   -56,
     -15,   -56,   205,   -56,   -56,   205,   205,   205,   -56,   -56,
     -56,   267,   -56,   169,   128,   -56,   -56,   -56,   -56,   -56,
     -56,   -56,   -56,   -56,   -56,   -56,   -56,   -56,   217,   -56,
     267,    44,    24,    24,   249,   -56,   -56,   -56,   -56,   -56,
     -56,   -56,   -56,   -56,   -56,   -56,   -56,   -56,   -56,   205,
     205,   205,   205,   205,   -56,   -56,   -56,   -56,   -56,   -56,
     205,   -56,   -56,   -56,   -56,   -56,   -56,   154,   -56,   -56,
     -56,    56,   267,   -56,   -56,   -56,   -56,   112,   -56,   -56,
     -56,   -56,   -56,   -56,   -56,   -56,   -56,   -56,   -56,   -56,
      24,    10,    10,    24,    29,   285,   -56,   -56,   -56,   -56,
     -56,   -56,   -56,   267,   -56,   -56,   -56,   -56,   -56
  };

  const unsigned char
  SONParser::yydefact_[] =
  {
     109,     0,     1,    34,    40,    11,    12,    41,    38,    39,
     104,    56,    42,     0,    58,     0,    65,    63,     0,    64,
     111,   113,   112,   110,   114,   115,     0,    36,    37,   105,
       0,    30,     0,     9,    29,     0,     0,     0,    43,    44,
      45,    79,    32,     0,     0,    59,    60,    61,    62,    35,
     108,     2,    55,    80,   106,    84,    82,    86,     0,    88,
      57,     0,    53,    54,     0,    21,    24,    22,    23,    20,
      19,    27,    28,     4,     5,     8,    10,     6,     7,     0,
       0,     0,     0,     0,    13,    14,    17,    15,    18,    16,
       0,    25,    26,    74,    33,    73,    76,     0,    68,    93,
      67,    43,    91,    70,    97,    95,    99,     0,   101,     3,
      81,    90,   107,    85,    83,    87,    89,    31,    66,    52,
      46,    47,    48,    49,    50,    51,    75,    78,    77,    69,
      94,   103,    72,    92,    71,    98,    96,   100,   102
  };

  const signed char
  SONParser::yypgoto_[] =
  {
     -56,   -31,   -55,   -56,   -56,   -56,   -56,   -32,   -56,   -56,
     -56,   -56,   -56,   -56,   -56,   -56,   -56,   -56,   -56,   -56,
     -56,    46,     7,   -56,   -25,    55,   -39,   -56,    -1,   -56,
     -56,     4,   -33,   -56,   -56,    62,   -56,   -56,   -56,   -56,
     -56,     0,     1,     2,    52,   -56,     3,   -56,   -56,   -56,
     -56
  };

  const signed char
  SONParser::yydefgoto_[] =
  {
      -1,    53,   111,    77,    78,    79,    80,    35,    82,    12,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      36,    37,   118,    43,    95,    13,    50,    29,    38,    39,
      40,    41,    54,    15,    61,    16,    47,    48,    17,    18,
      19,    55,    56,    57,    58,   107,    59,    30,    24,    25,
       1
  };

  const short int
  SONParser::yytable_[] =
  {
      14,    20,    21,    22,    23,   100,    27,    28,    51,    81,
      96,   103,    14,    99,     4,     5,     6,     7,     8,     9,
      10,     3,    52,    42,    45,   112,    46,   110,    81,    14,
      81,    81,    81,    33,    73,    74,    60,    76,    31,    62,
      63,    64,    14,   101,   104,   105,   106,   108,   102,    49,
     117,    76,   131,    73,    74,    75,    76,    14,   113,   114,
     115,   116,    32,   -58,   128,   -58,   110,   -58,   132,   -58,
      81,   119,   127,    44,   134,    26,   130,     4,     5,     6,
       7,     8,     9,   120,   121,   122,   123,   124,    81,    81,
      81,    81,    81,    81,   125,    97,    14,   113,   114,   115,
     116,    81,     0,     0,     0,     0,   101,   135,   136,   137,
     138,   133,   129,     0,     0,     0,    33,    31,     0,     0,
      49,     0,     0,     0,   109,     0,     0,     0,    98,     0,
       0,     0,    33,    31,    34,    51,    49,     0,     0,     0,
       0,     4,     5,     6,     7,     8,     9,    10,     0,    52,
      34,    51,     0,     0,   126,     0,     0,     4,     5,     6,
       7,     8,     9,    10,    94,    52,   109,     0,     0,    93,
       0,     0,     0,     0,     0,     0,     0,    51,     0,    94,
       0,     0,     0,     4,     5,     6,     7,     8,     9,    10,
       2,    52,    51,     0,     0,     0,     0,     3,     4,     5,
       6,     7,     8,     9,    10,     0,    52,     0,     0,    33,
      31,     0,     0,     0,     0,     0,     0,     0,     0,     4,
       5,     6,     7,     8,     9,    10,    11,    34,     0,   109,
       0,     0,     0,     0,     4,     5,     6,     7,     8,     9,
      51,     0,     0,     0,     0,     0,     4,     5,     6,     7,
       8,     9,    10,    33,    52,   117,     0,     0,     0,     0,
       0,     0,     0,    65,    66,    67,    68,    69,    70,    71,
      72,    33,     0,    73,    74,    75,    76,     0,     0,     0,
       0,    65,    66,    67,    68,    69,    70,    71,    72,    33,
       0,    73,    74,    75,    76,     0,     0,     0,     0,    65,
      66,    67,    68,    69,    70,     0,     0,     0,     0,    73,
      74,    75,    76
  };

  const short int
  SONParser::yycheck_[] =
  {
       1,     1,     1,     1,     1,    44,    33,    34,    23,    41,
      43,    44,    13,    44,    29,    30,    31,    32,    33,    34,
      35,     7,    37,     9,    11,    58,    13,    58,    60,    30,
      62,    63,    64,     4,    24,    25,    32,    27,     5,    35,
      36,    37,    43,    44,    44,    44,    44,    44,    44,     8,
       6,    27,   107,    24,    25,    26,    27,    58,    58,    58,
      58,    58,    16,     7,    97,     9,    97,    11,   107,    13,
     102,    64,    97,    18,   107,    13,   107,    29,    30,    31,
      32,    33,    34,    79,    80,    81,    82,    83,   120,   121,
     122,   123,   124,   125,    90,    43,    97,    97,    97,    97,
      97,   133,    -1,    -1,    -1,    -1,   107,   107,   107,   107,
     107,   107,     0,    -1,    -1,    -1,     4,     5,    -1,    -1,
       8,    -1,    -1,    -1,    12,    -1,    -1,    -1,     0,    -1,
      -1,    -1,     4,     5,    22,    23,     8,    -1,    -1,    -1,
      -1,    29,    30,    31,    32,    33,    34,    35,    -1,    37,
      22,    23,    -1,    -1,     0,    -1,    -1,    29,    30,    31,
      32,    33,    34,    35,    10,    37,    12,    -1,    -1,     0,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,    -1,    10,
      -1,    -1,    -1,    29,    30,    31,    32,    33,    34,    35,
       0,    37,    23,    -1,    -1,    -1,    -1,     7,    29,    30,
      31,    32,    33,    34,    35,    -1,    37,    -1,    -1,     4,
       5,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,
      30,    31,    32,    33,    34,    35,    36,    22,    -1,    12,
      -1,    -1,    -1,    -1,    29,    30,    31,    32,    33,    34,
      23,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,    32,
      33,    34,    35,     4,    37,     6,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    14,    15,    16,    17,    18,    19,    20,
      21,     4,    -1,    24,    25,    26,    27,    -1,    -1,    -1,
      -1,    14,    15,    16,    17,    18,    19,    20,    21,     4,
      -1,    24,    25,    26,    27,    -1,    -1,    -1,    -1,    14,
      15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,    24,
      25,    26,    27
  };

  const unsigned char
  SONParser::yystos_[] =
  {
       0,    93,     0,     7,    29,    30,    31,    32,    33,    34,
      35,    36,    52,    68,    71,    76,    78,    81,    82,    83,
      84,    85,    86,    89,    91,    92,    78,    33,    34,    70,
      90,     5,    64,     4,    22,    50,    63,    64,    71,    72,
      73,    74,     9,    66,    68,    11,    13,    79,    80,     8,
      69,    23,    37,    44,    75,    84,    85,    86,    87,    89,
      74,    77,    74,    74,    74,    14,    15,    16,    17,    18,
      19,    20,    21,    24,    25,    26,    27,    46,    47,    48,
      49,    50,    51,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,     0,    10,    67,    75,    87,     0,    44,
      69,    71,    74,    75,    84,    85,    86,    88,    89,    12,
      44,    45,    75,    84,    85,    86,    89,     6,    65,    65,
      74,    74,    74,    74,    74,    74,     0,    67,    75,     0,
      44,    45,    69,    74,    75,    84,    85,    86,    89
  };

  const unsigned char
  SONParser::yyr1_[] =
  {
       0,    43,    44,    45,    46,    47,    48,    48,    49,    50,
      51,    52,    52,    53,    53,    53,    53,    53,    53,    54,
      55,    56,    57,    58,    59,    60,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    70,    71,    71,
      71,    71,    71,    72,    73,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    75,    76,    77,    78,    79,
      79,    80,    81,    82,    82,    83,    83,    84,    84,    84,
      84,    84,    84,    85,    85,    85,    85,    85,    85,    86,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    89,    90,    91,    91,    92,    93,
      93,    93,    93,    93,    93,    93
  };

  const unsigned char
  SONParser::yyr2_[] =
  {
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     4,     3,     3,     4,
       3,     4,     4,     3,     3,     4,     3,     4,     4,     2,
       1,     2,     1,     2,     1,     2,     1,     2,     1,     2,
       2,     1,     2,     1,     2,     1,     2,     1,     2,     1,
       2,     1,     2,     2,     1,     1,     3,     4,     3,     0,
       2,     2,     2,     2,     2,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const SONParser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"end of line\"", "\"-\"",
  "\"(\"", "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\"=\"", "\",\"",
  "\":\"", "\">=\"", "\"<\"", "\">\"", "\"<=\"", "\"!=\"", "\"==\"",
  "\"&&\"", "\"||\"", "\"!\"", "\"filler\"", "\"*\"", "\"/\"", "\"+\"",
  "\"^\"", "\"&\"", "\"integer\"", "\"true\"", "\"false\"", "\"double\"",
  "\"string\"", "\"quoted string\"", "\"comment\"",
  "\"start of unit of execution\"", "\"end of unit of execution\"",
  "OBJECT", "ARRAY", "UMINUS", "UNOT", "\"exp\"", "$accept", "filler",
  "comma", "multiply", "divide", "multiply_divide", "plus", "minus",
  "exponent", "BOOLEAN", "boolean_numeric_op", "eq", "neq", "gte", "gt",
  "lte", "lt", "boolean_logic_op", "and", "or", "unary_not", "lparen",
  "rparen", "lbrace", "rbrace", "lbracket", "rbracket", "ANY_STRING",
  "PRIMITIVE", "value", "component", "exp", "execution_unit_end",
  "execution_unit_start", "identifier", "decl", "ASSIGNMENT", "assignment",
  "key_declaration", "declaration", "tag", "array", "object", "keyedvalue",
  "members", "array_members", "comment", "execution_unit_name",
  "execution_unit", "block", "start", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  SONParser::yyrline_[] =
  {
       0,   151,   151,   156,   166,   171,   176,   176,   177,   182,
     188,   193,   193,   195,   195,   195,   195,   195,   195,   197,
     202,   207,   212,   217,   222,   227,   227,   228,   233,   239,
     245,   250,   255,   260,   265,   270,   276,   276,   277,   277,
     277,   277,   277,   279,   297,   299,   300,   314,   328,   342,
     356,   371,   385,   399,   411,   424,   429,   435,   441,   450,
     450,   451,   455,   461,   461,   462,   467,   476,   485,   496,
     508,   516,   529,   544,   553,   564,   576,   587,   600,   616,
     634,   639,   644,   649,   654,   659,   664,   669,   674,   679,
     684,   691,   696,   702,   707,   712,   717,   722,   727,   732,
     737,   742,   747,   752,   758,   763,   768,   782,   802,   830,
     831,   832,   833,   834,   835,   836
  };

  // Print the state stack on the debug stream.
  void
  SONParser::yystack_print_ ()
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
  SONParser::yy_reduce_print_ (int yyrule)
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
  SONParser::token_number_type
  SONParser::yytranslate_ (int t)
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
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42
    };
    const unsigned int user_token_number_max_ = 297;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

#line 34 "SONParser.bison" // lalr1.cc:1167
} // wasp
#line 2254 "SONParser.cpp" // lalr1.cc:1167
#line 840 "SONParser.bison" // lalr1.cc:1168
 /*** Additional Code ***/

void wasp::SONParser::error(const SONParser::location_type& l,
                           const std::string& m)
{
    interpreter.error_stream()<<l<<": "<<m<<std::endl;
}
