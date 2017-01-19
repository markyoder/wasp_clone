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
#line 1 "JSONParser.bison" // lalr1.cc:404
 /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>

#line 45 "JSONParser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "JSONParser.hpp"

// User implementation prologue.
#line 132 "JSONParser.bison" // lalr1.cc:412


#include "JSONInterpreter.h"
#include "JSONLexer.h"

/* this "connects" the bison parser in the interpreter to the flex JSONLexer class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the interpreter context. */
#undef yylex
#define yylex lexer->lex


#line 71 "JSONParser.cpp" // lalr1.cc:412


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
#line 157 "JSONParser.cpp" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  JSONParser::yytnamerr_ (const char *yystr)
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
  JSONParser::JSONParser (class AbstractInterpreter& interpreter_yyarg, std::istream &input_stream_yyarg, std::shared_ptr<class JSONLexerImpl> lexer_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      interpreter (interpreter_yyarg),
      input_stream (input_stream_yyarg),
      lexer (lexer_yyarg)
  {}

  JSONParser::~JSONParser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  JSONParser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  JSONParser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  JSONParser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
    value = other.value;
  }


  template <typename Base>
  inline
  JSONParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  JSONParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  inline
  JSONParser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  JSONParser::basic_symbol<Base>::clear ()
  {
    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  JSONParser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  JSONParser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
    location = s.location;
  }

  // by_type.
  inline
  JSONParser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  JSONParser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  JSONParser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  JSONParser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  JSONParser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  JSONParser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  JSONParser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  JSONParser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  JSONParser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  JSONParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  JSONParser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  JSONParser::symbol_number_type
  JSONParser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  JSONParser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  JSONParser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    value = that.value;
    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  JSONParser::stack_symbol_type&
  JSONParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  JSONParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    switch (yysym.type_get ())
    {
            case 81: // key_declaration

#line 131 "JSONParser.bison" // lalr1.cc:614
        { delete (yysym.value.node_indices); }
#line 412 "JSONParser.cpp" // lalr1.cc:614
        break;

      case 82: // declaration

#line 131 "JSONParser.bison" // lalr1.cc:614
        { delete (yysym.value.node_indices); }
#line 419 "JSONParser.cpp" // lalr1.cc:614
        break;

      case 83: // tag

#line 130 "JSONParser.bison" // lalr1.cc:614
        { delete (yysym.value.node_indices); }
#line 426 "JSONParser.cpp" // lalr1.cc:614
        break;

      case 87: // members

#line 130 "JSONParser.bison" // lalr1.cc:614
        { delete (yysym.value.node_indices); }
#line 433 "JSONParser.cpp" // lalr1.cc:614
        break;

      case 88: // array_members

#line 130 "JSONParser.bison" // lalr1.cc:614
        { delete (yysym.value.node_indices); }
#line 440 "JSONParser.cpp" // lalr1.cc:614
        break;


      default:
        break;
    }
  }

#if YYDEBUG
  template <typename Base>
  void
  JSONParser::yy_print_ (std::ostream& yyo,
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
  JSONParser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  JSONParser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  JSONParser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  JSONParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  JSONParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  JSONParser::debug_level_type
  JSONParser::debug_level () const
  {
    return yydebug_;
  }

  void
  JSONParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline JSONParser::state_type
  JSONParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  JSONParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  JSONParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  JSONParser::parse ()
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
    #line 40 "JSONParser.bison" // lalr1.cc:741
{
    // initialize the initial location object
    yyla.location.begin.filename = yyla.location.end.filename = &interpreter.stream_name();
    yyla.location.begin.line = yyla.location.end.line = interpreter.start_line();
    yyla.location.begin.column = yyla.location.end.column = interpreter.start_column();
    lexer = std::make_shared<JSONLexerImpl>(interpreter,&input_stream);
}

#line 581 "JSONParser.cpp" // lalr1.cc:741

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
#line 149 "JSONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::FILL_EXPR,"filler",token_index);
    }
#line 694 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 154 "JSONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::WASP_COMMA,",",token_index);
    }
#line 703 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 164 "JSONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::MULTIPLY,"*",token_index);
    }
#line 712 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 169 "JSONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::DIVIDE,"/",token_index);
    }
#line 721 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 175 "JSONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::PLUS,"+",token_index);
    }
#line 730 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 180 "JSONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::MINUS,"-",token_index);
    }
#line 739 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 186 "JSONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::EXPONENT,"^",token_index);
    }
#line 748 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 195 "JSONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::EQ,"==",token_index);
    }
#line 757 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 200 "JSONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::NEQ,"!=",token_index);
    }
#line 766 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 205 "JSONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::GTE,">=",token_index);
    }
#line 775 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 210 "JSONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::GT,">",token_index);
    }
#line 784 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 215 "JSONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::LTE,"<=",token_index);
    }
#line 793 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 220 "JSONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::LT,"<",token_index);
    }
#line 802 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 226 "JSONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::WASP_AND,"&&",token_index);
    }
#line 811 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 231 "JSONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::WASP_OR,"||",token_index);
    }
#line 820 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 237 "JSONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::UNARY_NOT,"!",token_index);
    }
#line 829 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 243 "JSONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::LPAREN,"(",token_index);
    }
#line 838 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 248 "JSONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::RPAREN,")",token_index);
    }
#line 847 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 253 "JSONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::LBRACE,"{",token_index);
    }
#line 856 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 258 "JSONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::RBRACE,"}",token_index);
    }
#line 865 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 263 "JSONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::LBRACKET,"[",token_index);
    }
#line 874 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 268 "JSONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::RBRACKET,"]",token_index);
    }
#line 883 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 277 "JSONParser.bison" // lalr1.cc:859
    {
    size_t token_index = ((yystack_[0].value.token_index));
    (yylhs.value.node_index) = interpreter.push_leaf(wasp::VALUE,"value"
                     ,token_index);
}
#line 893 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 298 "JSONParser.bison" // lalr1.cc:859
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
#line 911 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 312 "JSONParser.bison" // lalr1.cc:859
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
#line 929 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 326 "JSONParser.bison" // lalr1.cc:859
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
#line 947 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 340 "JSONParser.bison" // lalr1.cc:859
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
#line 965 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 354 "JSONParser.bison" // lalr1.cc:859
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
#line 983 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 369 "JSONParser.bison" // lalr1.cc:859
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
#line 1001 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 383 "JSONParser.bison" // lalr1.cc:859
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
#line 1019 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 397 "JSONParser.bison" // lalr1.cc:859
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
#line 1035 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 409 "JSONParser.bison" // lalr1.cc:859
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
#line 1051 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 422 "JSONParser.bison" // lalr1.cc:859
    {
    auto token_index = ((yystack_[0].value.token_index));
    (yylhs.value.node_index) = interpreter.push_leaf(wasp::EXECUTION_UNIT_END,"uoe_end",token_index);
}
#line 1060 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 427 "JSONParser.bison" // lalr1.cc:859
    {
    auto token_index = ((yystack_[0].value.token_index));
    (yylhs.value.node_index) = interpreter.push_leaf(wasp::EXECUTION_UNIT_START,"uoe_start",token_index);
}
#line 1069 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 432 "JSONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::IDENTIFIER,"id",token_index);
    }
#line 1078 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 437 "JSONParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        std::string quote_less_data = interpreter.token_data(token_index);
        quote_less_data = wasp::strip_quotes(quote_less_data);
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::DECL
                                   ,"decl"
                                   ,token_index);
    }
#line 1091 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 446 "JSONParser.bison" // lalr1.cc:859
    {
             auto token_index = ((yystack_[0].value.token_index));
             (yylhs.value.node_index) = interpreter.push_leaf(wasp::ASSIGN,"=",token_index);
            }
#line 1100 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 451 "JSONParser.bison" // lalr1.cc:859
    {
             (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
             (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));

        }
#line 1110 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 458 "JSONParser.bison" // lalr1.cc:859
    {
             (yylhs.value.node_indices) = new std::vector<size_t>();
             (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1119 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 463 "JSONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<size_t>();
            (yylhs.value.node_indices)->push_back((yystack_[3].value.node_index));
            (yylhs.value.node_indices)->push_back((yystack_[2].value.node_index));
            (yylhs.value.node_indices)->push_back((yystack_[1].value.node_index));
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1131 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 472 "JSONParser.bison" // lalr1.cc:859
    {
        (yystack_[2].value.node_indices)->push_back((yystack_[1].value.node_index));
        (yystack_[2].value.node_indices)->push_back((yystack_[0].value.node_index));
        (yylhs.value.node_index) = interpreter.push_parent(wasp::ARRAY
                ,wasp::strip_quotes(interpreter.data((yystack_[2].value.node_indices)->front())).c_str()
                ,*(yystack_[2].value.node_indices));
        delete (yystack_[2].value.node_indices);
    }
#line 1144 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 481 "JSONParser.bison" // lalr1.cc:859
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
#line 1160 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 493 "JSONParser.bison" // lalr1.cc:859
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
#line 1176 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 505 "JSONParser.bison" // lalr1.cc:859
    {
        // TODO capture partial definition
        std::string name = interpreter.name((yystack_[2].value.node_indices)->front());
        error(yystack_[1].location, name+" has unmatched left bracket!");
        delete (yystack_[2].value.node_indices);
        YYERROR;
    }
#line 1188 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 513 "JSONParser.bison" // lalr1.cc:859
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
#line 1205 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 526 "JSONParser.bison" // lalr1.cc:859
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
#line 1224 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 541 "JSONParser.bison" // lalr1.cc:859
    {
        (yystack_[2].value.node_indices)->push_back((yystack_[1].value.node_index));
        (yystack_[2].value.node_indices)->push_back((yystack_[0].value.node_index));
        (yylhs.value.node_index) = interpreter.push_parent(wasp::OBJECT
            ,wasp::strip_quotes(interpreter.data((yystack_[2].value.node_indices)->front())).c_str()
            ,*(yystack_[2].value.node_indices));
        delete (yystack_[2].value.node_indices);
    }
#line 1237 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 550 "JSONParser.bison" // lalr1.cc:859
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
#line 1252 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 561 "JSONParser.bison" // lalr1.cc:859
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
#line 1268 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 573 "JSONParser.bison" // lalr1.cc:859
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
#line 1283 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 584 "JSONParser.bison" // lalr1.cc:859
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
#line 1300 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 597 "JSONParser.bison" // lalr1.cc:859
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
#line 1318 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 613 "JSONParser.bison" // lalr1.cc:859
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
#line 1338 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 631 "JSONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<size_t>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1347 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 636 "JSONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1356 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 641 "JSONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<size_t>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1365 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 646 "JSONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1374 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 651 "JSONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<size_t>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1383 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 656 "JSONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1392 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 661 "JSONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<size_t>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1401 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 666 "JSONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1410 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 671 "JSONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<size_t>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1419 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 676 "JSONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1428 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 681 "JSONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1437 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 688 "JSONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<size_t>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1446 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 693 "JSONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1455 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 699 "JSONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<size_t>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1464 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 704 "JSONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1473 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 709 "JSONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<size_t>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1482 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 714 "JSONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1491 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 719 "JSONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<size_t>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1500 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 724 "JSONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1509 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 729 "JSONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<size_t>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1518 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 734 "JSONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1527 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 739 "JSONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = new std::vector<size_t>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1536 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 744 "JSONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1545 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 749 "JSONParser.bison" // lalr1.cc:859
    {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1554 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 755 "JSONParser.bison" // lalr1.cc:859
    {
            auto token_index = ((yystack_[0].value.token_index));
            (yylhs.value.node_index) = interpreter.push_leaf(wasp::COMMENT,"comment",token_index);
        }
#line 1563 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 760 "JSONParser.bison" // lalr1.cc:859
    {
            auto token_index = ((yystack_[0].value.token_index));
            (yylhs.value.node_index) = interpreter.push_leaf(wasp::DECL,"name",token_index);
        }
#line 1572 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 765 "JSONParser.bison" // lalr1.cc:859
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
#line 1590 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 779 "JSONParser.bison" // lalr1.cc:859
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
#line 1612 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 797 "JSONParser.bison" // lalr1.cc:859
    {interpreter.add_root_child_index(((yystack_[0].value.node_index))); if(interpreter.single_parse() ) {lexer->rewind();YYACCEPT;}}
#line 1618 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 798 "JSONParser.bison" // lalr1.cc:859
    {interpreter.add_root_child_index(((yystack_[0].value.node_index))); if(interpreter.single_parse() ) {lexer->rewind();YYACCEPT;}}
#line 1624 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 799 "JSONParser.bison" // lalr1.cc:859
    {interpreter.add_root_child_index(((yystack_[0].value.node_index))); if(interpreter.single_parse() ) {lexer->rewind();YYACCEPT;}}
#line 1630 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 800 "JSONParser.bison" // lalr1.cc:859
    {interpreter.add_root_child_index(((yystack_[0].value.node_index))); if(interpreter.single_parse() ) {lexer->rewind();YYACCEPT;}}
#line 1636 "JSONParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 801 "JSONParser.bison" // lalr1.cc:859
    {interpreter.add_root_child_index(((yystack_[0].value.node_index)));if(interpreter.single_parse() ) {YYACCEPT;}}
#line 1642 "JSONParser.cpp" // lalr1.cc:859
    break;


#line 1646 "JSONParser.cpp" // lalr1.cc:859
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
  JSONParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  JSONParser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
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


  const signed char JSONParser::yypact_ninf_ = -98;

  const signed char JSONParser::yytable_ninf_ = -59;

  const short int
  JSONParser::yypact_[] =
  {
     -98,   179,   -98,   -98,   -98,   -98,   -98,   -98,   -98,   -98,
     -98,   -98,   -98,   -21,    12,     4,    -2,    18,   -98,   -98,
     -98,   -98,   -98,   -98,   -98,   -98,   261,   -98,   142,   -98,
     -98,     4,     4,     4,   -98,   -98,   -98,   244,   -98,   -98,
     170,   129,   -98,   -98,   -98,   -98,   -98,   -98,   -98,   -98,
     -98,   -98,   -98,   194,   -98,   -98,    15,     5,     5,   226,
     -98,   -98,   -98,   -98,   -98,   -98,   -98,   -98,   -98,   -98,
     -98,   -98,   -98,   -98,     4,     4,     4,     4,     4,   -98,
     -98,   -98,   -98,   -98,   -98,     4,   -98,   -98,   -98,   -98,
     -98,   -98,   155,   -98,   -98,   -98,   -98,    68,   244,   -98,
     -98,   -98,   -98,   113,   -98,   -98,   -98,   -98,   -98,   -98,
     -98,   -98,   -98,   -98,   -98,   -98,     5,    -5,    -5,     5,
      72,   262,   -98,   -98,   -98,   -98,   -98,   -98,   -98,   244,
     -98,   -98,   -98,   -98,   -98
  };

  const unsigned char
  JSONParser::yydefact_[] =
  {
     108,     0,     1,    40,    11,    12,    41,    38,    39,   104,
      56,    42,    58,     0,    65,    63,     0,    64,   110,   112,
     111,   109,   113,    36,    37,   105,     0,    30,     0,     9,
      29,     0,     0,     0,    43,    44,    45,    79,    34,    32,
       0,     0,    59,    60,    61,    62,     2,    55,    80,   106,
      84,    82,    86,     0,    88,    57,     0,    53,    54,     0,
      21,    24,    22,    23,    20,    19,    27,    28,     4,     5,
       8,    10,     6,     7,     0,     0,     0,     0,     0,    13,
      14,    17,    15,    18,    16,     0,    25,    26,    74,    33,
      73,    76,     0,    68,    35,    93,    67,    43,    91,    70,
      97,    95,    99,     0,   101,     3,    81,    90,   107,    85,
      83,    87,    89,    31,    66,    52,    46,    47,    48,    49,
      50,    51,    75,    78,    77,    69,    94,   103,    72,    92,
      71,    98,    96,   100,   102
  };

  const signed char
  JSONParser::yypgoto_[] =
  {
     -98,   -23,   -97,   -98,   -98,   -98,   -98,    -9,   -98,   -98,
     -98,   -98,   -98,   -98,   -98,   -98,   -98,   -98,   -98,   -98,
     -98,    31,   -13,   -98,   -45,   -98,   -52,   -98,    -1,   -98,
     -98,   -17,   -30,   -98,   -98,   -98,   -98,   -98,   -98,   -98,
     -98,     0,     1,     2,    23,   -98,     3,   -98,   -98,   -98
  };

  const signed char
  JSONParser::yydefgoto_[] =
  {
      -1,    48,   107,    72,    73,    74,    75,    31,    77,    11,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      32,    33,   114,    40,    90,    41,    96,    25,    34,    35,
      36,    37,    49,    13,    56,    14,    44,    45,    15,    16,
      17,    50,    51,    52,    53,   103,    54,    26,    22,     1
  };

  const short int
  JSONParser::yytable_[] =
  {
      12,    18,    19,    20,    21,    38,   127,    39,    29,    27,
      91,    99,    23,    24,    57,    58,    59,    27,    95,    68,
      69,   113,    71,   108,    98,    12,    30,    55,    76,    42,
     106,    43,    71,     3,     4,     5,     6,     7,     8,    12,
      97,   100,   101,   102,   104,    28,   115,   123,    76,    76,
      76,   128,    12,   109,   110,   111,   112,   116,   117,   118,
     119,   120,   124,    92,     0,     0,     0,     0,   121,   106,
       0,     0,     0,   130,     0,   -58,    29,   -58,     0,   -58,
     126,   -58,     0,     0,     0,     0,   129,     0,     0,    76,
       0,    12,   109,   110,   111,   112,    68,    69,    70,    71,
       0,     0,    97,   131,   132,   133,   134,    76,    76,    76,
      76,    76,    76,   125,     0,     0,     0,    29,    27,     0,
      76,    94,     0,     0,     0,   105,     0,     0,     0,    93,
       0,     0,     0,    29,    27,    30,    46,    94,     0,     0,
       0,     0,     3,     4,     5,     6,     7,     8,     9,     0,
      47,    30,    46,     0,     0,   122,     0,     0,     3,     4,
       5,     6,     7,     8,     9,    89,    47,   105,     0,     0,
      88,     3,     4,     5,     6,     7,     8,     0,    46,     2,
      89,     0,     0,     0,     3,     4,     5,     6,     7,     8,
       9,     0,    47,    46,     0,     0,     0,     0,     0,     3,
       4,     5,     6,     7,     8,     9,   105,    47,     3,     4,
       5,     6,     7,     8,     9,    10,     0,    46,     0,     0,
       0,     0,     0,     3,     4,     5,     6,     7,     8,     9,
      29,    47,   113,     0,     0,     0,     0,     0,     0,     0,
      60,    61,    62,    63,    64,    65,    66,    67,    29,     0,
      68,    69,    70,    71,     0,     0,     0,     0,    60,    61,
      62,    63,    64,    65,    66,    67,    29,     0,    68,    69,
      70,    71,     0,     0,     0,     0,    60,    61,    62,    63,
      64,    65,     0,     0,    46,     0,    68,    69,    70,    71,
       3,     4,     5,     6,     7,     8,     9,     0,    47
  };

  const short int
  JSONParser::yycheck_[] =
  {
       1,     1,     1,     1,     1,     7,   103,     9,     4,     5,
      40,    41,    33,    34,    31,    32,    33,     5,    41,    24,
      25,     6,    27,    53,    41,    26,    22,    28,    37,    11,
      53,    13,    27,    29,    30,    31,    32,    33,    34,    40,
      41,    41,    41,    41,    41,    14,    59,    92,    57,    58,
      59,   103,    53,    53,    53,    53,    53,    74,    75,    76,
      77,    78,    92,    40,    -1,    -1,    -1,    -1,    85,    92,
      -1,    -1,    -1,   103,    -1,     7,     4,     9,    -1,    11,
     103,    13,    -1,    -1,    -1,    -1,   103,    -1,    -1,    98,
      -1,    92,    92,    92,    92,    92,    24,    25,    26,    27,
      -1,    -1,   103,   103,   103,   103,   103,   116,   117,   118,
     119,   120,   121,     0,    -1,    -1,    -1,     4,     5,    -1,
     129,     8,    -1,    -1,    -1,    12,    -1,    -1,    -1,     0,
      -1,    -1,    -1,     4,     5,    22,    23,     8,    -1,    -1,
      -1,    -1,    29,    30,    31,    32,    33,    34,    35,    -1,
      37,    22,    23,    -1,    -1,     0,    -1,    -1,    29,    30,
      31,    32,    33,    34,    35,    10,    37,    12,    -1,    -1,
       0,    29,    30,    31,    32,    33,    34,    -1,    23,     0,
      10,    -1,    -1,    -1,    29,    30,    31,    32,    33,    34,
      35,    -1,    37,    23,    -1,    -1,    -1,    -1,    -1,    29,
      30,    31,    32,    33,    34,    35,    12,    37,    29,    30,
      31,    32,    33,    34,    35,    36,    -1,    23,    -1,    -1,
      -1,    -1,    -1,    29,    30,    31,    32,    33,    34,    35,
       4,    37,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      14,    15,    16,    17,    18,    19,    20,    21,     4,    -1,
      24,    25,    26,    27,    -1,    -1,    -1,    -1,    14,    15,
      16,    17,    18,    19,    20,    21,     4,    -1,    24,    25,
      26,    27,    -1,    -1,    -1,    -1,    14,    15,    16,    17,
      18,    19,    -1,    -1,    23,    -1,    24,    25,    26,    27,
      29,    30,    31,    32,    33,    34,    35,    -1,    37
  };

  const unsigned char
  JSONParser::yystos_[] =
  {
       0,    92,     0,    29,    30,    31,    32,    33,    34,    35,
      36,    52,    71,    76,    78,    81,    82,    83,    84,    85,
      86,    89,    91,    33,    34,    70,    90,     5,    64,     4,
      22,    50,    63,    64,    71,    72,    73,    74,     7,     9,
      66,    68,    11,    13,    79,    80,    23,    37,    44,    75,
      84,    85,    86,    87,    89,    71,    77,    74,    74,    74,
      14,    15,    16,    17,    18,    19,    20,    21,    24,    25,
      26,    27,    46,    47,    48,    49,    50,    51,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,     0,    10,
      67,    75,    87,     0,     8,    44,    69,    71,    74,    75,
      84,    85,    86,    88,    89,    12,    44,    45,    75,    84,
      85,    86,    89,     6,    65,    65,    74,    74,    74,    74,
      74,    74,     0,    67,    75,     0,    44,    45,    69,    74,
      75,    84,    85,    86,    89
  };

  const unsigned char
  JSONParser::yyr1_[] =
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
      88,    88,    88,    88,    89,    90,    91,    91,    92,    92,
      92,    92,    92,    92
  };

  const unsigned char
  JSONParser::yyr2_[] =
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
       2,     1,     2,     2,     1,     1,     3,     4,     0,     2,
       2,     2,     2,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const JSONParser::yytname_[] =
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
  JSONParser::yyrline_[] =
  {
       0,   148,   148,   153,   163,   168,   173,   173,   174,   179,
     185,   190,   190,   192,   192,   192,   192,   192,   192,   194,
     199,   204,   209,   214,   219,   224,   224,   225,   230,   236,
     242,   247,   252,   257,   262,   267,   273,   273,   274,   274,
     274,   274,   274,   276,   294,   296,   297,   311,   325,   339,
     353,   368,   382,   396,   408,   421,   426,   431,   436,   445,
     445,   446,   450,   456,   456,   457,   462,   471,   480,   492,
     504,   512,   525,   540,   549,   560,   572,   583,   596,   612,
     630,   635,   640,   645,   650,   655,   660,   665,   670,   675,
     680,   687,   692,   698,   703,   708,   713,   718,   723,   728,
     733,   738,   743,   748,   754,   759,   764,   778,   796,   797,
     798,   799,   800,   801
  };

  // Print the state stack on the debug stream.
  void
  JSONParser::yystack_print_ ()
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
  JSONParser::yy_reduce_print_ (int yyrule)
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
  JSONParser::token_number_type
  JSONParser::yytranslate_ (int t)
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
#line 2212 "JSONParser.cpp" // lalr1.cc:1167
#line 805 "JSONParser.bison" // lalr1.cc:1168
 /*** Additional Code ***/

void wasp::JSONParser::error(const JSONParser::location_type& l,
                           const std::string& m)
{
    interpreter.error_stream()<<l<<": "<<m;
}
