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

// Take the name prefix into account.
#define yylex   wasplex

// First part of user declarations.
#line 1 "SONParser.bison" // lalr1.cc:404
 /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>


#line 46 "SONParser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "SONParser.hpp"

// User implementation prologue.
#line 134 "SONParser.bison" // lalr1.cc:412


#include "SONInterpreter.h"
#include "SONLexer.h"

/* this "connects" the bison parser in the interpreter to the flex SONLexer class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the interpreter context. */
#undef yylex
#define yylex interpreter.m_lexer->lex


#line 72 "SONParser.cpp" // lalr1.cc:412


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


namespace wasp {
#line 158 "SONParser.cpp" // lalr1.cc:479

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
  SONParser::SONParser (class SONInterpreter& interpreter_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      interpreter (interpreter_yyarg)
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
            case 99: // declaration

#line 133 "SONParser.bison" // lalr1.cc:614
        { delete (yysym.value.node_indices); }
#line 411 "SONParser.cpp" // lalr1.cc:614
        break;

      case 100: // tag

#line 133 "SONParser.bison" // lalr1.cc:614
        { delete (yysym.value.node_indices); }
#line 418 "SONParser.cpp" // lalr1.cc:614
        break;

      case 104: // members

#line 133 "SONParser.bison" // lalr1.cc:614
        { delete (yysym.value.node_indices); }
#line 425 "SONParser.cpp" // lalr1.cc:614
        break;

      case 105: // array_members

#line 133 "SONParser.bison" // lalr1.cc:614
        { delete (yysym.value.node_indices); }
#line 432 "SONParser.cpp" // lalr1.cc:614
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
    #line 40 "SONParser.bison" // lalr1.cc:741
{
    // initialize the initial location object
    yyla.location.begin.filename = yyla.location.end.filename = &interpreter.m_stream_name;
    yyla.location.begin.line = yyla.location.end.line = interpreter.m_start_line;
    yyla.location.begin.column = yyla.location.end.column = interpreter.m_start_column;
}

#line 572 "SONParser.cpp" // lalr1.cc:741

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
#line 151 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::FILL_EXPR,"filler",token_index);
    }
#line 685 "SONParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 156 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::WASP_COMMA,",",token_index);
    }
#line 694 "SONParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 176 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::MULTIPLY,"*",token_index);
    }
#line 703 "SONParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 181 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::DIVIDE,"/",token_index);
    }
#line 712 "SONParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 187 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::PLUS,"+",token_index);
    }
#line 721 "SONParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 192 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::MINUS,"-",token_index);
    }
#line 730 "SONParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 198 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::EXPONENT,"^",token_index);
    }
#line 739 "SONParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 216 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::EQ,"=",token_index);
    }
#line 748 "SONParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 221 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::NEQ,"!=",token_index);
    }
#line 757 "SONParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 226 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::GTE,">=",token_index);
    }
#line 766 "SONParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 231 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::GT,">",token_index);
    }
#line 775 "SONParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 236 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::LTE,"<=",token_index);
    }
#line 784 "SONParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 241 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::LT,"<",token_index);
    }
#line 793 "SONParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 247 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::WASP_AND,"&&",token_index);
    }
#line 802 "SONParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 252 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::WASP_OR,"||",token_index);
    }
#line 811 "SONParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 258 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::UNARY_NOT,"!",token_index);
    }
#line 820 "SONParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 264 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::LPAREN,"(",token_index);
    }
#line 829 "SONParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 269 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::RPAREN,")",token_index);
    }
#line 838 "SONParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 274 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::LBRACE,"{",token_index);
    }
#line 847 "SONParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 279 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::RBRACE,"}",token_index);
    }
#line 856 "SONParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 284 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::LBRACKET,"]",token_index);
    }
#line 865 "SONParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 289 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::RBRACKET,"]",token_index);
    }
#line 874 "SONParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 309 "SONParser.bison" // lalr1.cc:859
    {
    unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
    (yylhs.value.node_index) = interpreter.push_leaf(wasp::VALUE,"value"
                     ,token_index);
}
#line 884 "SONParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 330 "SONParser.bison" // lalr1.cc:859
    {
          unsigned int left_i = static_cast<unsigned int>((yystack_[2].value.node_index));
          unsigned int op_i = static_cast<unsigned int>((yystack_[1].value.node_index));
          unsigned int right_i = static_cast<unsigned int>((yystack_[0].value.node_index));
          std::vector<unsigned int> child_indices = {left_i
                                                     ,op_i
                                                     ,right_i
                                                     };

          (yylhs.value.node_index) = interpreter.push_parent(interpreter.type(op_i)
                                          ,"expr"
                                          ,child_indices);
    }
#line 902 "SONParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 344 "SONParser.bison" // lalr1.cc:859
    {
        unsigned int left_i = static_cast<unsigned int>((yystack_[2].value.node_index));
        unsigned int op_i = static_cast<unsigned int>((yystack_[1].value.node_index));
        unsigned int right_i = static_cast<unsigned int>((yystack_[0].value.node_index));
        std::vector<unsigned int> child_indices = {left_i
                                                   ,op_i
                                                   ,right_i
                                                   };

        (yylhs.value.node_index) = interpreter.push_parent(interpreter.type(op_i)
                                        ,"expr"
                                        ,child_indices);
    }
#line 920 "SONParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 358 "SONParser.bison" // lalr1.cc:859
    {
        unsigned int left_i = static_cast<unsigned int>((yystack_[2].value.node_index));
        unsigned int op_i = static_cast<unsigned int>((yystack_[1].value.node_index));
        unsigned int right_i = static_cast<unsigned int>((yystack_[0].value.node_index));
        std::vector<unsigned int> child_indices = {left_i
                                                   ,op_i
                                                   ,right_i
                                                   };

        (yylhs.value.node_index) = interpreter.push_parent(interpreter.type(op_i)
                                        ,"expr"
                                        ,child_indices);
    }
#line 938 "SONParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 372 "SONParser.bison" // lalr1.cc:859
    {
        unsigned int left_i = static_cast<unsigned int>((yystack_[2].value.node_index));
        unsigned int op_i = static_cast<unsigned int>((yystack_[1].value.node_index));
        unsigned int right_i = static_cast<unsigned int>((yystack_[0].value.node_index));
        std::vector<unsigned int> child_indices = {left_i
                                                   ,op_i
                                                   ,right_i
                                                   };

        (yylhs.value.node_index) = interpreter.push_parent(interpreter.type(op_i)
                                        ,"expr"
                                        ,child_indices);
    }
#line 956 "SONParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 386 "SONParser.bison" // lalr1.cc:859
    {
        unsigned int left_i = static_cast<unsigned int>((yystack_[2].value.node_index));
        unsigned int op_i = static_cast<unsigned int>((yystack_[1].value.node_index));
        unsigned int right_i = static_cast<unsigned int>((yystack_[0].value.node_index));
        std::vector<unsigned int> child_indices = {left_i
                                                   ,op_i
                                                   ,right_i
                                                   };

        (yylhs.value.node_index) = interpreter.push_parent(interpreter.type(op_i)
                                        ,"expr"
                                        ,child_indices);
    }
#line 974 "SONParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 401 "SONParser.bison" // lalr1.cc:859
    {
        unsigned int left_i = static_cast<unsigned int>((yystack_[2].value.node_index));
        unsigned int op_i = static_cast<unsigned int>((yystack_[1].value.node_index));
        unsigned int right_i = static_cast<unsigned int>((yystack_[0].value.node_index));
        std::vector<unsigned int> child_indices = {left_i
                                                   ,op_i
                                                   ,right_i
                                                   };

        (yylhs.value.node_index) = interpreter.push_parent(interpreter.type(op_i)
                                        ,"expr"
                                        ,child_indices);
    }
#line 992 "SONParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 415 "SONParser.bison" // lalr1.cc:859
    {
        unsigned int left_i = static_cast<unsigned int>((yystack_[2].value.node_index));
        unsigned int center_i = static_cast<unsigned int>((yystack_[1].value.node_index));
        unsigned int right_i = static_cast<unsigned int>((yystack_[0].value.node_index));
        std::vector<unsigned int> child_indices = {left_i
                                                   ,center_i
                                                   ,right_i
                                                   };

        (yylhs.value.node_index) = interpreter.push_parent(wasp::PARENTHESIS
                                        ,"expr"
                                        ,child_indices);
    }
#line 1010 "SONParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 429 "SONParser.bison" // lalr1.cc:859
    {
        unsigned int op_i = static_cast<unsigned int>((yystack_[1].value.node_index));
        unsigned int right_i = static_cast<unsigned int>((yystack_[0].value.node_index));
        std::vector<unsigned int> child_indices = {op_i
                                                   ,right_i
                                                   };

        (yylhs.value.node_index) = interpreter.push_parent(interpreter.type(op_i)
                                        ,"expr"
                                        ,child_indices);
    }
#line 1026 "SONParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 441 "SONParser.bison" // lalr1.cc:859
    {
        unsigned int op_i = static_cast<unsigned int>((yystack_[1].value.node_index));
        unsigned int right_i = static_cast<unsigned int>((yystack_[0].value.node_index));
        std::vector<unsigned int> child_indices = {op_i
                                                   ,right_i
                                                   };

        (yylhs.value.node_index) = interpreter.push_parent(interpreter.type(op_i)
                                        ,"expr"
                                        ,child_indices);
    }
#line 1042 "SONParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 454 "SONParser.bison" // lalr1.cc:859
    {
    auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
    (yylhs.value.node_index) = interpreter.push_leaf(wasp::EXECUTION_UNIT_END,"uoe_end",token_index);
}
#line 1051 "SONParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 459 "SONParser.bison" // lalr1.cc:859
    {
    auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
    (yylhs.value.node_index) = interpreter.push_leaf(wasp::EXECUTION_UNIT_START,"uoe_start",token_index);
}
#line 1060 "SONParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 464 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::IDENTIFIER,"id",token_index);
    }
#line 1069 "SONParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 469 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        std::string quote_less_data = interpreter.token_data(token_index);
        quote_less_data = wasp::strip_quotes(quote_less_data);
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::DECL
                                   ,"decl"
                                   ,token_index);
    }
#line 1082 "SONParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 478 "SONParser.bison" // lalr1.cc:859
    {
             auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
             (yylhs.value.node_index) = interpreter.push_leaf(wasp::ASSIGN,"=",token_index);
            }
#line 1091 "SONParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 483 "SONParser.bison" // lalr1.cc:859
    {
             (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
             (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));

        }
#line 1101 "SONParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 489 "SONParser.bison" // lalr1.cc:859
    {
             (yylhs.value.node_indices) = new std::vector<unsigned int>();
             (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1110 "SONParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 494 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<unsigned int>();
            (yylhs.value.node_indices)->push_back((yystack_[3].value.node_index));
            (yylhs.value.node_indices)->push_back((yystack_[2].value.node_index));
            (yylhs.value.node_indices)->push_back((yystack_[1].value.node_index));
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1122 "SONParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 503 "SONParser.bison" // lalr1.cc:859
    {
        (yystack_[2].value.node_indices)->push_back((yystack_[1].value.node_index));
        (yystack_[2].value.node_indices)->push_back((yystack_[0].value.node_index));
        (yylhs.value.node_index) = interpreter.push_parent(wasp::ARRAY
                                    ,interpreter.name((yystack_[2].value.node_indices)->front())
                                        ,*(yystack_[2].value.node_indices));
        delete (yystack_[2].value.node_indices);
    }
#line 1135 "SONParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 512 "SONParser.bison" // lalr1.cc:859
    {
        (yystack_[2].value.node_indices)->push_back((yystack_[1].value.node_index));
        std::string name = interpreter.name((yystack_[2].value.node_indices)->front());
        (yylhs.value.node_index) = interpreter.push_parent(wasp::ARRAY
                                    , name.c_str()
                                        ,*(yystack_[2].value.node_indices));
        delete (yystack_[2].value.node_indices);
        error(yystack_[1].location, name+" has unmatched left bracket!");
        delete (yystack_[2].value.node_indices);
        YYERROR;
    }
#line 1151 "SONParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 524 "SONParser.bison" // lalr1.cc:859
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
#line 1167 "SONParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 536 "SONParser.bison" // lalr1.cc:859
    {
        // TODO capture partial definition
        std::string name = interpreter.name((yystack_[2].value.node_indices)->front());
        error(yystack_[1].location, name+" has unmatched left bracket!");
        delete (yystack_[2].value.node_indices);
        YYERROR;
    }
#line 1179 "SONParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 544 "SONParser.bison" // lalr1.cc:859
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
#line 1196 "SONParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 557 "SONParser.bison" // lalr1.cc:859
    {
        (yystack_[3].value.node_indices)->push_back((yystack_[2].value.node_index));
        for( size_t i = 0; i < (yystack_[1].value.node_indices)->size(); ++i )
        {
            (yystack_[3].value.node_indices)->push_back( (yystack_[1].value.node_indices)->at( i ) );
        }
        (yystack_[3].value.node_indices)->push_back((yystack_[0].value.node_index));
        (yylhs.value.node_index) = interpreter.push_parent(wasp::ARRAY
                                    ,interpreter.name((yystack_[3].value.node_indices)->front())
                                        ,*(yystack_[3].value.node_indices));
        delete (yystack_[3].value.node_indices);
        delete (yystack_[1].value.node_indices);

    }
#line 1215 "SONParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 572 "SONParser.bison" // lalr1.cc:859
    {
        (yystack_[2].value.node_indices)->push_back((yystack_[1].value.node_index));
        (yystack_[2].value.node_indices)->push_back((yystack_[0].value.node_index));
        const char * name = interpreter.name((yystack_[2].value.node_indices)->front());
        (yylhs.value.node_index) = interpreter.push_parent(wasp::OBJECT
                                    ,name
                                    ,*(yystack_[2].value.node_indices));
        delete (yystack_[2].value.node_indices);
    }
#line 1229 "SONParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 582 "SONParser.bison" // lalr1.cc:859
    {
        (yystack_[2].value.node_indices)->push_back((yystack_[1].value.node_index));
        std::string name = interpreter.name((yystack_[2].value.node_indices)->front());
        (yylhs.value.node_index) = interpreter.push_parent(wasp::OBJECT
                                     , name.c_str()
                                     , *(yystack_[2].value.node_indices));
        delete (yystack_[2].value.node_indices);
        error(yystack_[1].location, name+" has unmatched left brace!");
        YYERROR;
    }
#line 1244 "SONParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 593 "SONParser.bison" // lalr1.cc:859
    {
        // TODO capture partial definition
        std::string name = interpreter.name((yystack_[3].value.node_indices)->front());
        auto last_component_type = interpreter.type((yystack_[3].value.node_indices)->back());
        if( (yystack_[1].value.node_indices)->size() ==0 ) error(yystack_[2].location, name+" has unmatched left brace!");
        else if( last_component_type == wasp::OBJECT ) error(yystack_[2].location, name+" or one of its components has unmatched left brace!");
        else error(yystack_[2].location, name+" has unmatched left brace!");
        delete (yystack_[1].value.node_indices);
        delete (yystack_[3].value.node_indices);
        YYERROR;
    }
#line 1260 "SONParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 605 "SONParser.bison" // lalr1.cc:859
    {
        (yystack_[2].value.node_indices)->push_back((yystack_[1].value.node_index));
        std::string name = interpreter.name((yystack_[2].value.node_indices)->front());
        (yylhs.value.node_index) = interpreter.push_parent( wasp::OBJECT
                                     , name.c_str()
                                     , *(yystack_[2].value.node_indices));
        error(yystack_[1].location, name+" has unmatched left brace!");
        delete (yystack_[2].value.node_indices);
        YYERROR;
    }
#line 1275 "SONParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 616 "SONParser.bison" // lalr1.cc:859
    {
        // TODO capture partial definition
        std::string name = interpreter.name((yystack_[3].value.node_indices)->front());
        auto last_component_type = interpreter.type((yystack_[3].value.node_indices)->back());
        if( (yystack_[1].value.node_indices)->size() ==0 ) error(yystack_[2].location, name+" has unmatched left brace!");
        else if( last_component_type == wasp::OBJECT ) error(yystack_[2].location, name+" or one of its components has unmatched left brace!");
        else error(yystack_[2].location, name+" has unmatched left brace!");

        delete (yystack_[1].value.node_indices);
        delete (yystack_[3].value.node_indices);
        YYERROR;
    }
#line 1292 "SONParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 629 "SONParser.bison" // lalr1.cc:859
    {
        (yystack_[3].value.node_indices)->push_back((yystack_[2].value.node_index));
        for( size_t i = 0; i < (yystack_[1].value.node_indices)->size(); ++i )
        {
            (yystack_[3].value.node_indices)->push_back( (yystack_[1].value.node_indices)->at( i ) );
        }
        (yystack_[3].value.node_indices)->push_back((yystack_[0].value.node_index));
        (yylhs.value.node_index) = interpreter.push_parent(wasp::OBJECT
                                    ,interpreter.name((yystack_[3].value.node_indices)->front())
                                        ,*(yystack_[3].value.node_indices));
        delete (yystack_[3].value.node_indices);
        delete (yystack_[1].value.node_indices);
    }
#line 1310 "SONParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 645 "SONParser.bison" // lalr1.cc:859
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
#line 1330 "SONParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 663 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<unsigned int>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1339 "SONParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 668 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1348 "SONParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 673 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<unsigned int>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1357 "SONParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 678 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1366 "SONParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 683 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<unsigned int>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1375 "SONParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 688 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1384 "SONParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 693 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<unsigned int>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1393 "SONParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 698 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1402 "SONParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 703 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<unsigned int>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1411 "SONParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 708 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1420 "SONParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 713 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1429 "SONParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 720 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<unsigned int>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1438 "SONParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 725 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1447 "SONParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 731 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<unsigned int>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1456 "SONParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 736 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1465 "SONParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 741 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<unsigned int>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1474 "SONParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 746 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1483 "SONParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 751 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<unsigned int>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1492 "SONParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 756 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1501 "SONParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 761 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<unsigned int>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1510 "SONParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 766 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1519 "SONParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 771 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<unsigned int>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1528 "SONParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 776 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1537 "SONParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 781 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1546 "SONParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 787 "SONParser.bison" // lalr1.cc:859
    {
            auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
            (yylhs.value.node_index) = interpreter.push_leaf(wasp::COMMENT,"comment",token_index);
        }
#line 1555 "SONParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 792 "SONParser.bison" // lalr1.cc:859
    {
            auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
            (yylhs.value.node_index) = interpreter.push_leaf(wasp::DECL,"name",token_index);
        }
#line 1564 "SONParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 797 "SONParser.bison" // lalr1.cc:859
    { // account for an empty execution unit
            unsigned int start_i = static_cast<unsigned int>((yystack_[2].value.node_index));
            unsigned int name_i = static_cast<unsigned int>((yystack_[1].value.node_index));
            unsigned int end_i = static_cast<unsigned int>((yystack_[0].value.node_index));
            std::vector<unsigned int> child_indices = {start_i
                                                       ,name_i
                                                       ,end_i
                                                       };

            (yylhs.value.node_index) = interpreter.push_parent(wasp::EXECUTION_UNIT
                                            ,interpreter.name(name_i)
                                            ,child_indices);
       }
#line 1582 "SONParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 811 "SONParser.bison" // lalr1.cc:859
    { // execution unit with members
            unsigned int start_i = static_cast<unsigned int>((yystack_[3].value.node_index));
            unsigned int name_i = static_cast<unsigned int>((yystack_[2].value.node_index));
            unsigned int end_i = static_cast<unsigned int>((yystack_[0].value.node_index));
            std::vector<unsigned int> child_indices = {start_i
                                                       ,name_i
                                                       };
            for( size_t i = 0; i < (yystack_[1].value.node_indices)->size(); ++ i )
            {
                child_indices.push_back( (yystack_[1].value.node_indices)->at(i) );
            }
            child_indices.push_back(end_i);
            delete (yystack_[1].value.node_indices);
            (yylhs.value.node_index) = interpreter.push_parent(wasp::EXECUTION_UNIT
                                            ,interpreter.name(name_i)
                                            ,child_indices);
       }
#line 1604 "SONParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 829 "SONParser.bison" // lalr1.cc:859
    {interpreter.add_root_child_index(static_cast<unsigned int>((yystack_[0].value.node_index))); if(interpreter.isSingleParse() ) {interpreter.m_lexer->rewind();YYACCEPT;}}
#line 1610 "SONParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 830 "SONParser.bison" // lalr1.cc:859
    {interpreter.add_root_child_index(static_cast<unsigned int>((yystack_[0].value.node_index))); if(interpreter.isSingleParse() ) {interpreter.m_lexer->rewind();YYACCEPT;}}
#line 1616 "SONParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 831 "SONParser.bison" // lalr1.cc:859
    {interpreter.add_root_child_index(static_cast<unsigned int>((yystack_[0].value.node_index))); if(interpreter.isSingleParse() ) {interpreter.m_lexer->rewind();YYACCEPT;}}
#line 1622 "SONParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 832 "SONParser.bison" // lalr1.cc:859
    {interpreter.add_root_child_index(static_cast<unsigned int>((yystack_[0].value.node_index))); if(interpreter.isSingleParse() ) {interpreter.m_lexer->rewind();YYACCEPT;}}
#line 1628 "SONParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 833 "SONParser.bison" // lalr1.cc:859
    {interpreter.add_root_child_index(static_cast<unsigned int>((yystack_[0].value.node_index)));if(interpreter.isSingleParse() ) {YYACCEPT;}}
#line 1634 "SONParser.cpp" // lalr1.cc:859
    break;


#line 1638 "SONParser.cpp" // lalr1.cc:859
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


  const signed char SONParser::yypact_ninf_ = -41;

  const signed char SONParser::yytable_ninf_ = -53;

  const short int
  SONParser::yypact_[] =
  {
     -41,   129,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,
     -41,   -41,   -41,   -38,     2,   189,   -12,   -41,   -41,   -41,
     -41,   -41,   -41,   -41,   -41,   227,   -41,   183,   -41,   -41,
     -41,   -41,    62,    62,    62,   115,    94,   -41,   -41,   -41,
     181,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,
     -41,   -41,   209,   -41,   -41,    13,   -20,   -20,   165,   -41,
     -41,   -41,   -41,   139,   -41,   -41,   -41,   -41,    -3,   181,
     -41,   -41,   -41,   -41,    85,   -41,   -41,   -41,   -41,   -41,
     -41,   -41,   -41,   -41,    62,    62,    62,    62,    62,    -6,
      62,    -2,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,
     -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,
     181,   -41,   -41,   -41,   -41,   -41,   -20,   -17,   -17,   -20,
      83,   -41,     5,   211,   -41,   -41,   -41,     9,   -41,    14,
     -41,     4,   -41,   -41
  };

  const unsigned char
  SONParser::yydefact_[] =
  {
     100,     0,     1,    34,    11,    12,    35,    32,    33,    96,
      50,    36,    52,     0,    57,     0,     0,   102,   104,   103,
     101,   105,    30,    31,    97,     0,    24,     0,     9,    28,
      26,    23,     0,     0,     0,     0,     0,    37,    38,    39,
      71,    53,    54,    55,    56,     2,    49,    72,    98,    76,
      74,    78,     0,    80,    51,     0,    47,    48,     0,    66,
      27,    65,    68,     0,    60,    29,    85,    59,    37,    83,
      62,    89,    87,    91,     0,    93,    14,    21,     4,     5,
       8,    10,     6,     7,     0,     0,     0,     0,     0,     0,
       0,     0,     3,    73,    82,    99,    77,    75,    79,    81,
      25,    58,    46,    67,    70,    69,    61,    86,    95,    64,
      84,    63,    90,    88,    92,    94,    40,    41,    42,    43,
      44,    15,     0,    45,    22,    20,    17,     0,    19,     0,
      16,     0,    18,    13
  };

  const short int
  SONParser::yypgoto_[] =
  {
     -41,   -24,   -34,   -41,   -41,   -41,   -41,   -40,   -41,   -41,
     -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,
     -41,    27,   -16,   -41,   -15,   -41,   -31,   -41,     0,   -41,
     -41,   -29,   192,   -41,   -41,   -41,   -41,   -41,   -41,   -41,
       1,     8,    10,    12,   -41,    29,   -41,   -41,   -41
  };

  const short int
  SONParser::yydefgoto_[] =
  {
      -1,    47,    94,    82,    83,    84,    85,    32,    87,    11,
      88,    89,   122,   131,   127,   133,   129,    90,    91,   125,
      33,    34,   101,    35,    61,    36,    67,    24,    37,    38,
      39,    40,    48,    13,    55,    14,    43,    44,    15,    16,
      49,    50,    51,    52,    74,    53,    25,    21,     1
  };

  const short int
  SONParser::yytable_[] =
  {
      86,    12,    17,    56,    57,    58,    41,    69,    26,    18,
      42,    19,    66,    22,    23,   -52,    86,    86,    86,   -52,
      78,   100,    79,    81,   121,    12,    81,    54,    93,    86,
      20,   124,   126,   132,   128,    12,    68,    71,   130,    93,
     108,    27,   102,   109,    72,   110,    73,    63,   104,     0,
     107,     0,    12,    96,     0,   116,   117,   118,   119,   120,
      97,   123,    98,    12,    96,    75,    28,     0,    26,     0,
      86,    97,     0,    98,    68,   112,    86,    86,    86,    86,
      86,    99,   113,    86,   114,   106,     0,    28,     0,    28,
       0,    26,    99,     0,    64,     0,    31,    65,    28,     0,
      26,     0,     0,   115,     0,    92,    65,     0,     0,     3,
       4,     5,     6,     7,     8,    59,     0,     0,     0,    31,
      78,    45,    79,     0,    80,     0,    81,     0,    31,     2,
      45,    60,     3,     4,     5,     6,     7,     8,     9,   103,
      46,     3,     4,     5,     6,     7,     8,     9,     0,    46,
       0,    45,     0,     0,     0,    60,     0,     0,     0,    92,
       0,     0,     3,     4,     5,     6,     7,     8,     9,    28,
      46,     0,     0,   100,     0,    45,     3,     4,     5,     6,
       7,     8,     9,    10,     0,    28,     3,     4,     5,     6,
       7,     8,     9,    28,    46,    26,    76,    77,     0,    29,
       0,     0,    78,    30,    79,     0,    80,     0,    81,     0,
       0,     0,    76,    77,     0,    28,     0,     0,    78,     0,
      79,     0,    80,    31,    81,     0,     0,    62,    70,    92,
       3,     4,     5,     6,     7,     8,     3,     4,     5,     6,
       7,     8,    76,     0,    95,    45,     0,     0,    78,     0,
      79,     0,    80,     0,    81,   105,     3,     4,     5,     6,
       7,     8,     9,    45,    46,     0,   111,     0,     0,     0,
       0,     0,     0,     0,     3,     4,     5,     6,     7,     8,
       9,     0,    46
  };

  const signed char
  SONParser::yycheck_[] =
  {
      40,     1,     1,    32,    33,    34,    18,    36,     6,     1,
      22,     1,    36,    51,    52,    18,    56,    57,    58,    22,
      37,     8,    39,    43,    30,    25,    43,    27,    52,    69,
       1,    33,    27,    29,    25,    35,    36,    36,    24,    63,
      74,    14,    58,    74,    36,    74,    36,    35,    63,    -1,
      74,    -1,    52,    52,    -1,    84,    85,    86,    87,    88,
      52,    90,    52,    63,    63,    36,     4,    -1,     6,    -1,
     110,    63,    -1,    63,    74,    74,   116,   117,   118,   119,
     120,    52,    74,   123,    74,     0,    -1,     4,    -1,     4,
      -1,     6,    63,    -1,     0,    -1,    34,    12,     4,    -1,
       6,    -1,    -1,    74,    -1,    20,    12,    -1,    -1,    47,
      48,    49,    50,    51,    52,     0,    -1,    -1,    -1,    34,
      37,    36,    39,    -1,    41,    -1,    43,    -1,    34,     0,
      36,    16,    47,    48,    49,    50,    51,    52,    53,     0,
      55,    47,    48,    49,    50,    51,    52,    53,    -1,    55,
      -1,    36,    -1,    -1,    -1,    16,    -1,    -1,    -1,    20,
      -1,    -1,    47,    48,    49,    50,    51,    52,    53,     4,
      55,    -1,    -1,     8,    -1,    36,    47,    48,    49,    50,
      51,    52,    53,    54,    -1,     4,    47,    48,    49,    50,
      51,    52,    53,     4,    55,     6,    31,    32,    -1,    10,
      -1,    -1,    37,    14,    39,    -1,    41,    -1,    43,    -1,
      -1,    -1,    31,    32,    -1,     4,    -1,    -1,    37,    -1,
      39,    -1,    41,    34,    43,    -1,    -1,    35,    36,    20,
      47,    48,    49,    50,    51,    52,    47,    48,    49,    50,
      51,    52,    31,    -1,    52,    36,    -1,    -1,    37,    -1,
      39,    -1,    41,    -1,    43,    63,    47,    48,    49,    50,
      51,    52,    53,    36,    55,    -1,    74,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    48,    49,    50,    51,    52,
      53,    -1,    55
  };

  const unsigned char
  SONParser::yystos_[] =
  {
       0,   109,     0,    47,    48,    49,    50,    51,    52,    53,
      54,    70,    89,    94,    96,    99,   100,   101,   102,   103,
     106,   108,    51,    52,    88,   107,     6,    82,     4,    10,
      14,    34,    68,    81,    82,    84,    86,    89,    90,    91,
      92,    18,    22,    97,    98,    36,    55,    62,    93,   101,
     102,   103,   104,   106,    89,    95,    92,    92,    92,     0,
      16,    85,    93,   104,     0,    12,    62,    87,    89,    92,
      93,   101,   102,   103,   105,   106,    31,    32,    37,    39,
      41,    43,    64,    65,    66,    67,    68,    69,    71,    72,
      78,    79,    20,    62,    63,    93,   101,   102,   103,   106,
       8,    83,    83,     0,    85,    93,     0,    62,    63,    87,
      92,    93,   101,   102,   103,   106,    92,    92,    92,    92,
      92,    30,    73,    92,    33,    80,    27,    75,    25,    77,
      24,    74,    29,    76
  };

  const unsigned char
  SONParser::yyr1_[] =
  {
       0,    61,    62,    63,    64,    65,    66,    66,    67,    68,
      69,    70,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    88,    89,    89,    89,    89,    89,    90,    91,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    93,
      94,    95,    96,    97,    97,    98,    99,   100,   100,   101,
     101,   101,   101,   101,   101,   102,   102,   102,   102,   102,
     102,   103,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   106,   107,   108,   108,
     109,   109,   109,   109,   109,   109
  };

  const unsigned char
  SONParser::yyr2_[] =
  {
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     6,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     4,     3,
       3,     4,     3,     4,     4,     3,     3,     4,     3,     4,
       4,     2,     1,     2,     1,     2,     1,     2,     1,     2,
       1,     2,     2,     1,     2,     1,     2,     1,     2,     1,
       2,     1,     2,     1,     2,     2,     1,     1,     3,     4,
       0,     2,     2,     2,     2,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const SONParser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"end of line\"", "MINUS",
  "'-'", "LPAREN", "'('", "RPAREN", "')'", "LBRACKET", "'['", "RBRACKET",
  "']'", "LBRACE", "'{'", "RBRACE", "'}'", "ASSIGN", "'='", "COMMA", "','",
  "COLON", "':'", "\">=\"", "LT", "'<'", "GT", "'>'", "\"<=\"", "\"!=\"",
  "\"==\"", "\"&&\"", "\"||\"", "BANG", "'!'", "\"filler\"", "MULTIPLY",
  "'*'", "DIVIDE", "'/'", "PLUS", "'+'", "EXPONENT", "'^'", "AMPERSAND",
  "'&'", "\"integer\"", "\"true\"", "\"false\"", "\"double\"",
  "\"string\"", "\"quoted string\"", "\"comment\"",
  "\"start of unit of execution\"", "\"end of unit of execution\"",
  "OBJECT", "ARRAY", "UMINUS", "UNOT", "\"exp\"", "$accept", "filler",
  "comma", "multiply", "divide", "multiply_divide", "plus", "minus",
  "exponent", "BOOLEAN", "boolean_numeric_op", "eq", "neq", "gte", "gt",
  "lte", "lt", "boolean_logic_op", "and", "or", "unary_not", "lparen",
  "rparen", "lbrace", "rbrace", "lbracket", "rbracket", "ANY_STRING",
  "PRIMITIVE", "value", "component", "exp", "execution_unit_end",
  "execution_unit_start", "identifier", "decl", "ASSIGNMENT", "assignment",
  "declaration", "tag", "array", "object", "keyedvalue", "members",
  "array_members", "comment", "execution_unit_name", "execution_unit",
  "start", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  SONParser::yyrline_[] =
  {
       0,   150,   150,   155,   175,   180,   185,   185,   186,   191,
     197,   202,   202,   213,   215,   220,   225,   230,   235,   240,
     245,   246,   251,   257,   263,   268,   273,   278,   283,   288,
     305,   305,   306,   306,   306,   306,   306,   308,   326,   328,
     329,   343,   357,   371,   385,   400,   414,   428,   440,   453,
     458,   463,   468,   477,   477,   478,   482,   488,   493,   502,
     511,   523,   535,   543,   556,   571,   581,   592,   604,   615,
     628,   644,   662,   667,   672,   677,   682,   687,   692,   697,
     702,   707,   712,   719,   724,   730,   735,   740,   745,   750,
     755,   760,   765,   770,   775,   780,   786,   791,   796,   810,
     828,   829,   830,   831,   832,   833
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
       2,     2,     2,    35,     2,     2,     2,     2,    46,     2,
       7,     9,    38,    42,    21,     5,     2,    40,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    23,     2,
      26,    19,    28,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    11,     2,    13,    44,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    15,     2,    17,     2,     2,     2,     2,
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
       6,     8,    10,    12,    14,    16,    18,    20,    22,    24,
      25,    27,    29,    30,    31,    32,    33,    34,    36,    37,
      39,    41,    43,    45,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60
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


} // wasp
#line 2201 "SONParser.cpp" // lalr1.cc:1167
#line 837 "SONParser.bison" // lalr1.cc:1168
 /*** Additional Code ***/

void wasp::SONParser::error(const SONParser::location_type& l,
                           const std::string& m)
{
    interpreter.error(l, m);
}
