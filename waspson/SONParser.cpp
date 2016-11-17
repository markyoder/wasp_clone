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
#line 135 "SONParser.bison" // lalr1.cc:412


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
            case 81: // key_declaration

#line 134 "SONParser.bison" // lalr1.cc:614
        { delete (yysym.value.node_indices); }
#line 411 "SONParser.cpp" // lalr1.cc:614
        break;

      case 82: // declaration

#line 134 "SONParser.bison" // lalr1.cc:614
        { delete (yysym.value.node_indices); }
#line 418 "SONParser.cpp" // lalr1.cc:614
        break;

      case 83: // tag

#line 133 "SONParser.bison" // lalr1.cc:614
        { delete (yysym.value.node_indices); }
#line 425 "SONParser.cpp" // lalr1.cc:614
        break;

      case 87: // members

#line 133 "SONParser.bison" // lalr1.cc:614
        { delete (yysym.value.node_indices); }
#line 432 "SONParser.cpp" // lalr1.cc:614
        break;

      case 88: // array_members

#line 133 "SONParser.bison" // lalr1.cc:614
        { delete (yysym.value.node_indices); }
#line 439 "SONParser.cpp" // lalr1.cc:614
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
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::FILL_EXPR,"filler",token_index);
    }
#line 692 "SONParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 157 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::WASP_COMMA,",",token_index);
    }
#line 701 "SONParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 177 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::MULTIPLY,"*",token_index);
    }
#line 710 "SONParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 182 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::DIVIDE,"/",token_index);
    }
#line 719 "SONParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 188 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::PLUS,"+",token_index);
    }
#line 728 "SONParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 193 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::MINUS,"-",token_index);
    }
#line 737 "SONParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 199 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::EXPONENT,"^",token_index);
    }
#line 746 "SONParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 217 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::EQ,"=",token_index);
    }
#line 755 "SONParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 222 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::NEQ,"!=",token_index);
    }
#line 764 "SONParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 227 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::GTE,">=",token_index);
    }
#line 773 "SONParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 232 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::GT,">",token_index);
    }
#line 782 "SONParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 237 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::LTE,"<=",token_index);
    }
#line 791 "SONParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 242 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::LT,"<",token_index);
    }
#line 800 "SONParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 248 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::WASP_AND,"&&",token_index);
    }
#line 809 "SONParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 253 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::WASP_OR,"||",token_index);
    }
#line 818 "SONParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 259 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::UNARY_NOT,"!",token_index);
    }
#line 827 "SONParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 265 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::LPAREN,"(",token_index);
    }
#line 836 "SONParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 270 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::RPAREN,")",token_index);
    }
#line 845 "SONParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 275 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::LBRACE,"{",token_index);
    }
#line 854 "SONParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 280 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::RBRACE,"}",token_index);
    }
#line 863 "SONParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 285 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::LBRACKET,"[",token_index);
    }
#line 872 "SONParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 290 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::RBRACKET,"]",token_index);
    }
#line 881 "SONParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 310 "SONParser.bison" // lalr1.cc:859
    {
    unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
    (yylhs.value.node_index) = interpreter.push_leaf(wasp::VALUE,"value"
                     ,token_index);
}
#line 891 "SONParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 331 "SONParser.bison" // lalr1.cc:859
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
#line 909 "SONParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 345 "SONParser.bison" // lalr1.cc:859
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
#line 927 "SONParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 359 "SONParser.bison" // lalr1.cc:859
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
#line 945 "SONParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 373 "SONParser.bison" // lalr1.cc:859
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
#line 963 "SONParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 387 "SONParser.bison" // lalr1.cc:859
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
#line 981 "SONParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 402 "SONParser.bison" // lalr1.cc:859
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
#line 999 "SONParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 416 "SONParser.bison" // lalr1.cc:859
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
#line 1017 "SONParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 430 "SONParser.bison" // lalr1.cc:859
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
#line 1033 "SONParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 442 "SONParser.bison" // lalr1.cc:859
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
#line 1049 "SONParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 455 "SONParser.bison" // lalr1.cc:859
    {
    auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
    (yylhs.value.node_index) = interpreter.push_leaf(wasp::EXECUTION_UNIT_END,"uoe_end",token_index);
}
#line 1058 "SONParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 460 "SONParser.bison" // lalr1.cc:859
    {
    auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
    (yylhs.value.node_index) = interpreter.push_leaf(wasp::EXECUTION_UNIT_START,"uoe_start",token_index);
}
#line 1067 "SONParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 465 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::IDENTIFIER,"id",token_index);
    }
#line 1076 "SONParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 470 "SONParser.bison" // lalr1.cc:859
    {
        auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        std::string quote_less_data = interpreter.token_data(token_index);
        quote_less_data = wasp::strip_quotes(quote_less_data);
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::DECL
                                   ,"decl"
                                   ,token_index);
    }
#line 1089 "SONParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 479 "SONParser.bison" // lalr1.cc:859
    {
             auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
             (yylhs.value.node_index) = interpreter.push_leaf(wasp::ASSIGN,"=",token_index);
            }
#line 1098 "SONParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 484 "SONParser.bison" // lalr1.cc:859
    {
             (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
             (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));

        }
#line 1108 "SONParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 491 "SONParser.bison" // lalr1.cc:859
    {
             (yylhs.value.node_indices) = new std::vector<unsigned int>();
             (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1117 "SONParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 496 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<unsigned int>();
            (yylhs.value.node_indices)->push_back((yystack_[3].value.node_index));
            (yylhs.value.node_indices)->push_back((yystack_[2].value.node_index));
            (yylhs.value.node_indices)->push_back((yystack_[1].value.node_index));
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1129 "SONParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 505 "SONParser.bison" // lalr1.cc:859
    {
        (yystack_[2].value.node_indices)->push_back((yystack_[1].value.node_index));
        (yystack_[2].value.node_indices)->push_back((yystack_[0].value.node_index));
        (yylhs.value.node_index) = interpreter.push_parent(wasp::ARRAY
                ,wasp::strip_quotes(interpreter.data((yystack_[2].value.node_indices)->front())).c_str()
                ,*(yystack_[2].value.node_indices));
        delete (yystack_[2].value.node_indices);
    }
#line 1142 "SONParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 514 "SONParser.bison" // lalr1.cc:859
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
#line 1158 "SONParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 526 "SONParser.bison" // lalr1.cc:859
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

  case 64:
#line 538 "SONParser.bison" // lalr1.cc:859
    {
        // TODO capture partial definition
        std::string name = interpreter.name((yystack_[2].value.node_indices)->front());
        error(yystack_[1].location, name+" has unmatched left bracket!");
        delete (yystack_[2].value.node_indices);
        YYERROR;
    }
#line 1186 "SONParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 546 "SONParser.bison" // lalr1.cc:859
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

  case 66:
#line 559 "SONParser.bison" // lalr1.cc:859
    {
        (yystack_[3].value.node_indices)->push_back((yystack_[2].value.node_index));
        for( size_t i = 0; i < (yystack_[1].value.node_indices)->size(); ++i )
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

  case 67:
#line 574 "SONParser.bison" // lalr1.cc:859
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

  case 68:
#line 583 "SONParser.bison" // lalr1.cc:859
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

  case 69:
#line 594 "SONParser.bison" // lalr1.cc:859
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

  case 70:
#line 606 "SONParser.bison" // lalr1.cc:859
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

  case 71:
#line 617 "SONParser.bison" // lalr1.cc:859
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

  case 72:
#line 630 "SONParser.bison" // lalr1.cc:859
    {
        (yystack_[3].value.node_indices)->push_back((yystack_[2].value.node_index));
        for( size_t i = 0; i < (yystack_[1].value.node_indices)->size(); ++i )
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

  case 73:
#line 646 "SONParser.bison" // lalr1.cc:859
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

  case 74:
#line 664 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<unsigned int>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1345 "SONParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 669 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1354 "SONParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 674 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<unsigned int>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1363 "SONParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 679 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1372 "SONParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 684 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<unsigned int>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1381 "SONParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 689 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1390 "SONParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 694 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<unsigned int>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1399 "SONParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 699 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1408 "SONParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 704 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<unsigned int>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1417 "SONParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 709 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1426 "SONParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 714 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1435 "SONParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 721 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<unsigned int>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1444 "SONParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 726 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1453 "SONParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 732 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<unsigned int>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1462 "SONParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 737 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1471 "SONParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 742 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<unsigned int>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1480 "SONParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 747 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1489 "SONParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 752 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<unsigned int>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1498 "SONParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 757 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1507 "SONParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 762 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<unsigned int>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1516 "SONParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 767 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1525 "SONParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 772 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<unsigned int>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1534 "SONParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 777 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1543 "SONParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 782 "SONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1552 "SONParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 788 "SONParser.bison" // lalr1.cc:859
    {
            auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
            (yylhs.value.node_index) = interpreter.push_leaf(wasp::COMMENT,"comment",token_index);
        }
#line 1561 "SONParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 793 "SONParser.bison" // lalr1.cc:859
    {
            auto token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
            (yylhs.value.node_index) = interpreter.push_leaf(wasp::DECL,"name",token_index);
        }
#line 1570 "SONParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 798 "SONParser.bison" // lalr1.cc:859
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
#line 1588 "SONParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 812 "SONParser.bison" // lalr1.cc:859
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
#line 1610 "SONParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 830 "SONParser.bison" // lalr1.cc:859
    {interpreter.add_root_child_index(static_cast<unsigned int>((yystack_[0].value.node_index))); if(interpreter.isSingleParse() ) {interpreter.m_lexer->rewind();YYACCEPT;}}
#line 1616 "SONParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 831 "SONParser.bison" // lalr1.cc:859
    {interpreter.add_root_child_index(static_cast<unsigned int>((yystack_[0].value.node_index))); if(interpreter.isSingleParse() ) {interpreter.m_lexer->rewind();YYACCEPT;}}
#line 1622 "SONParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 832 "SONParser.bison" // lalr1.cc:859
    {interpreter.add_root_child_index(static_cast<unsigned int>((yystack_[0].value.node_index))); if(interpreter.isSingleParse() ) {interpreter.m_lexer->rewind();YYACCEPT;}}
#line 1628 "SONParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 833 "SONParser.bison" // lalr1.cc:859
    {interpreter.add_root_child_index(static_cast<unsigned int>((yystack_[0].value.node_index))); if(interpreter.isSingleParse() ) {interpreter.m_lexer->rewind();YYACCEPT;}}
#line 1634 "SONParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 834 "SONParser.bison" // lalr1.cc:859
    {interpreter.add_root_child_index(static_cast<unsigned int>((yystack_[0].value.node_index)));if(interpreter.isSingleParse() ) {YYACCEPT;}}
#line 1640 "SONParser.cpp" // lalr1.cc:859
    break;


#line 1644 "SONParser.cpp" // lalr1.cc:859
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


  const signed char SONParser::yypact_ninf_ = -35;

  const signed char SONParser::yytable_ninf_ = -53;

  const short int
  SONParser::yypact_[] =
  {
     -35,   155,   -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,
     -35,   -35,   -35,    -2,    13,   188,    14,    11,   -35,   -35,
     -35,   -35,   -35,   -35,   -35,   -35,   229,   -35,    30,   -35,
     -35,   188,   188,   188,   -35,   -35,   -35,   220,   -35,   -35,
     172,   130,   -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,
     -35,   -35,   -35,   200,   -35,   -35,    20,   -22,   -22,    10,
     -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,   188,   188,
     188,   188,   188,    15,   188,    17,   -35,   -35,   -35,   -35,
     146,   -35,   -35,   -35,   -35,     4,   220,   -35,   -35,   -35,
     -35,   110,   -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,
     -35,   -35,   -35,   -35,   -22,   -15,   -15,   -22,    47,   -35,
      29,   224,   -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,
     -35,   220,   -35,   -35,   -35,   -35,   -35,   -35,    50,   -35,
      55,   -35,    53,   -35,   -35
  };

  const unsigned char
  SONParser::yydefact_[] =
  {
     102,     0,     1,    34,    11,    12,    35,    32,    33,    98,
      50,    36,    52,     0,    59,    57,     0,    58,   104,   106,
     105,   103,   107,    30,    31,    99,     0,    24,     0,     9,
      23,     0,     0,     0,    37,    38,    39,    73,    28,    26,
       0,     0,    53,    54,    55,    56,     2,    49,    74,   100,
      78,    76,    80,     0,    82,    51,     0,    47,    48,     0,
      14,    21,     4,     5,     8,    10,     6,     7,     0,     0,
       0,     0,     0,     0,     0,     0,    68,    27,    67,    70,
       0,    62,    29,    87,    61,    37,    85,    64,    91,    89,
      93,     0,    95,     3,    75,    84,   101,    79,    77,    81,
      83,    25,    60,    46,    40,    41,    42,    43,    44,    15,
       0,    45,    22,    20,    69,    72,    71,    63,    88,    97,
      66,    86,    65,    92,    90,    94,    96,    17,     0,    19,
       0,    16,     0,    18,    13
  };

  const signed char
  SONParser::yypgoto_[] =
  {
     -35,   -33,   -16,   -35,   -35,   -35,   -35,    -9,   -35,   -35,
     -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,
     -35,    64,    25,   -35,     5,   -35,    -5,   -35,    -1,   -35,
     -35,    35,   -34,   -35,   -35,   -35,   -35,   -35,   -35,   -35,
     -35,     0,     1,     2,    48,   -35,     3,   -35,   -35,   -35
  };

  const short int
  SONParser::yydefgoto_[] =
  {
      -1,    48,    95,    66,    67,    68,    69,    31,    71,    11,
      72,    73,   110,   132,   128,   134,   130,    74,    75,   113,
      32,    33,   102,    40,    78,    41,    84,    25,    34,    35,
      36,    37,    49,    13,    56,    14,    44,    45,    15,    16,
      17,    50,    51,    52,    53,    91,    54,    26,    22,     1
  };

  const short int
  SONParser::yytable_[] =
  {
      12,    18,    19,    20,    21,    65,    79,    87,    83,    62,
      63,   -52,    65,   -52,    29,   -52,   101,   -52,    27,    96,
      94,    38,    42,    39,    43,    12,   101,    55,    70,    60,
      61,    23,    24,   109,    62,    63,    64,    65,   112,    12,
      85,    88,    89,    90,    92,   127,   116,    94,    70,    70,
      70,    29,    12,    97,    98,    99,   100,   122,   118,     3,
       4,     5,     6,     7,     8,   129,    57,    58,    59,   131,
     133,    62,    63,    64,    65,   119,    86,    70,    28,    12,
      97,    98,    99,   100,   103,   115,   120,     0,    80,     0,
      85,   123,   124,   125,   126,    70,    70,    70,    70,    70,
       0,     0,    70,   104,   105,   106,   107,   108,     0,   111,
     117,     0,    70,     0,    29,    27,     0,     0,    82,     0,
       0,     0,    93,     0,     0,     0,   121,     0,     0,     0,
      81,     0,    30,    46,    29,    27,     0,     0,    82,     3,
       4,     5,     6,     7,     8,     9,   114,    47,     0,     0,
       0,     0,    30,    46,     0,     2,    77,     0,    93,     3,
       4,     5,     6,     7,     8,     9,     0,    47,     0,    46,
       0,     0,    76,     0,     0,     3,     4,     5,     6,     7,
       8,     9,    77,    47,     3,     4,     5,     6,     7,     8,
       9,    10,    29,    27,     0,    46,     0,     0,     0,     0,
       0,     3,     4,     5,     6,     7,     8,     9,     0,    47,
      30,     0,    93,     0,     0,     0,     0,     3,     4,     5,
       6,     7,     8,    46,    29,     0,     0,     0,    29,     3,
       4,     5,     6,     7,     8,     9,     0,    47,     0,    60,
      61,     0,     0,    60,    62,    63,    64,    65,    62,    63,
      64,    65,    46,     0,     0,     0,     0,     0,     3,     4,
       5,     6,     7,     8,     9,     0,    47
  };

  const signed char
  SONParser::yycheck_[] =
  {
       1,     1,     1,     1,     1,    27,    40,    41,    41,    24,
      25,     7,    27,     9,     4,    11,     6,    13,     5,    53,
      53,     7,    11,     9,    13,    26,     6,    28,    37,    19,
      20,    33,    34,    18,    24,    25,    26,    27,    21,    40,
      41,    41,    41,    41,    41,    16,    80,    80,    57,    58,
      59,     4,    53,    53,    53,    53,    53,    91,    91,    29,
      30,    31,    32,    33,    34,    15,    31,    32,    33,    14,
      17,    24,    25,    26,    27,    91,    41,    86,    14,    80,
      80,    80,    80,    80,    59,    80,    91,    -1,    40,    -1,
      91,    91,    91,    91,    91,   104,   105,   106,   107,   108,
      -1,    -1,   111,    68,    69,    70,    71,    72,    -1,    74,
       0,    -1,   121,    -1,     4,     5,    -1,    -1,     8,    -1,
      -1,    -1,    12,    -1,    -1,    -1,    91,    -1,    -1,    -1,
       0,    -1,    22,    23,     4,     5,    -1,    -1,     8,    29,
      30,    31,    32,    33,    34,    35,     0,    37,    -1,    -1,
      -1,    -1,    22,    23,    -1,     0,    10,    -1,    12,    29,
      30,    31,    32,    33,    34,    35,    -1,    37,    -1,    23,
      -1,    -1,     0,    -1,    -1,    29,    30,    31,    32,    33,
      34,    35,    10,    37,    29,    30,    31,    32,    33,    34,
      35,    36,     4,     5,    -1,    23,    -1,    -1,    -1,    -1,
      -1,    29,    30,    31,    32,    33,    34,    35,    -1,    37,
      22,    -1,    12,    -1,    -1,    -1,    -1,    29,    30,    31,
      32,    33,    34,    23,     4,    -1,    -1,    -1,     4,    29,
      30,    31,    32,    33,    34,    35,    -1,    37,    -1,    19,
      20,    -1,    -1,    19,    24,    25,    26,    27,    24,    25,
      26,    27,    23,    -1,    -1,    -1,    -1,    -1,    29,    30,
      31,    32,    33,    34,    35,    -1,    37
  };

  const unsigned char
  SONParser::yystos_[] =
  {
       0,    92,     0,    29,    30,    31,    32,    33,    34,    35,
      36,    52,    71,    76,    78,    81,    82,    83,    84,    85,
      86,    89,    91,    33,    34,    70,    90,     5,    64,     4,
      22,    50,    63,    64,    71,    72,    73,    74,     7,     9,
      66,    68,    11,    13,    79,    80,    23,    37,    44,    75,
      84,    85,    86,    87,    89,    71,    77,    74,    74,    74,
      19,    20,    24,    25,    26,    27,    46,    47,    48,    49,
      50,    51,    53,    54,    60,    61,     0,    10,    67,    75,
      87,     0,     8,    44,    69,    71,    74,    75,    84,    85,
      86,    88,    89,    12,    44,    45,    75,    84,    85,    86,
      89,     6,    65,    65,    74,    74,    74,    74,    74,    18,
      55,    74,    21,    62,     0,    67,    75,     0,    44,    45,
      69,    74,    75,    84,    85,    86,    89,    16,    57,    15,
      59,    14,    56,    17,    58
  };

  const unsigned char
  SONParser::yyr1_[] =
  {
       0,    43,    44,    45,    46,    47,    48,    48,    49,    50,
      51,    52,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    70,    71,    71,    71,    71,    71,    72,    73,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    75,
      76,    77,    78,    79,    79,    80,    81,    82,    82,    83,
      83,    84,    84,    84,    84,    84,    84,    85,    85,    85,
      85,    85,    85,    86,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    89,    90,
      91,    91,    92,    92,    92,    92,    92,    92
  };

  const unsigned char
  SONParser::yyr2_[] =
  {
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     6,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     1,
       4,     3,     3,     4,     3,     4,     4,     3,     3,     4,
       3,     4,     4,     2,     1,     2,     1,     2,     1,     2,
       1,     2,     1,     2,     2,     1,     2,     1,     2,     1,
       2,     1,     2,     1,     2,     1,     2,     2,     1,     1,
       3,     4,     0,     2,     2,     2,     2,     2
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
  "execution_unit", "start", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  SONParser::yyrline_[] =
  {
       0,   151,   151,   156,   176,   181,   186,   186,   187,   192,
     198,   203,   203,   214,   216,   221,   226,   231,   236,   241,
     246,   247,   252,   258,   264,   269,   274,   279,   284,   289,
     306,   306,   307,   307,   307,   307,   307,   309,   327,   329,
     330,   344,   358,   372,   386,   401,   415,   429,   441,   454,
     459,   464,   469,   478,   478,   479,   483,   489,   489,   490,
     495,   504,   513,   525,   537,   545,   558,   573,   582,   593,
     605,   616,   629,   645,   663,   668,   673,   678,   683,   688,
     693,   698,   703,   708,   713,   720,   725,   731,   736,   741,
     746,   751,   756,   761,   766,   771,   776,   781,   787,   792,
     797,   811,   829,   830,   831,   832,   833,   834
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


} // wasp
#line 2201 "SONParser.cpp" // lalr1.cc:1167
#line 838 "SONParser.bison" // lalr1.cc:1168
 /*** Additional Code ***/

void wasp::SONParser::error(const SONParser::location_type& l,
                           const std::string& m)
{
    interpreter.error(l, m);
}
