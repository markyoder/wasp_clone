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
#line 1 "SIRENParser.bison" // lalr1.cc:404
 /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>

#line 43 "SIRENParser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "SIRENParser.hpp"

// User implementation prologue.
#line 119 "SIRENParser.bison" // lalr1.cc:412


#include "SIRENInterpreter.h"
#include "SIRENLexer.h"

/* this "connects" the BISON parser in the interpreter to the flex SIRENLexer class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the interpreter context. */
#undef yylex
#define yylex lexer->lex


#line 69 "SIRENParser.cpp" // lalr1.cc:412


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

#line 32 "SIRENParser.bison" // lalr1.cc:479
namespace wasp {
#line 155 "SIRENParser.cpp" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  SIRENParser::yytnamerr_ (const char *yystr)
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
  SIRENParser::SIRENParser (class AbstractInterpreter& interpreter_yyarg, std::istream &input_stream_yyarg, std::shared_ptr<class SIRENLexerImpl> lexer_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      interpreter (interpreter_yyarg),
      input_stream (input_stream_yyarg),
      lexer (lexer_yyarg)
  {}

  SIRENParser::~SIRENParser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  SIRENParser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  SIRENParser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  SIRENParser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
    value = other.value;
  }


  template <typename Base>
  inline
  SIRENParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  SIRENParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  inline
  SIRENParser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  SIRENParser::basic_symbol<Base>::clear ()
  {
    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  SIRENParser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  SIRENParser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
    location = s.location;
  }

  // by_type.
  inline
  SIRENParser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  SIRENParser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  SIRENParser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  SIRENParser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  SIRENParser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  SIRENParser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  SIRENParser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  SIRENParser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  SIRENParser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  SIRENParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  SIRENParser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  SIRENParser::symbol_number_type
  SIRENParser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  SIRENParser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  SIRENParser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    value = that.value;
    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  SIRENParser::stack_symbol_type&
  SIRENParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  SIRENParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    switch (yysym.type_get ())
    {
            case 70: // key_declaration

#line 118 "SIRENParser.bison" // lalr1.cc:614
        { delete (yysym.value.node_indices); }
#line 410 "SIRENParser.cpp" // lalr1.cc:614
        break;

      case 71: // tag

#line 118 "SIRENParser.bison" // lalr1.cc:614
        { delete (yysym.value.node_indices); }
#line 417 "SIRENParser.cpp" // lalr1.cc:614
        break;


      default:
        break;
    }
  }

#if YYDEBUG
  template <typename Base>
  void
  SIRENParser::yy_print_ (std::ostream& yyo,
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
  SIRENParser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  SIRENParser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  SIRENParser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  SIRENParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  SIRENParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  SIRENParser::debug_level_type
  SIRENParser::debug_level () const
  {
    return yydebug_;
  }

  void
  SIRENParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline SIRENParser::state_type
  SIRENParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  SIRENParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  SIRENParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  SIRENParser::parse ()
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
    #line 41 "SIRENParser.bison" // lalr1.cc:741
{
    // initialize the initial location object
    yyla.location.begin.filename = yyla.location.end.filename = &interpreter.stream_name();
    yyla.location.begin.line = yyla.location.end.line = interpreter.start_line();
    yyla.location.begin.column = yyla.location.end.column = interpreter.start_column();
    lexer = std::make_shared<SIRENLexerImpl>(interpreter,&input_stream);
}

#line 558 "SIRENParser.cpp" // lalr1.cc:741

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
#line 136 "SIRENParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::ANY,"A",token_index);
    }
#line 671 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 141 "SIRENParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        // P - parent
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::PARENT,"P",token_index);
    }
#line 681 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 152 "SIRENParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::COLON,":",token_index);
    }
#line 690 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 157 "SIRENParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::MULTIPLY,"*",token_index);
    }
#line 699 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 162 "SIRENParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::DIVIDE,"/",token_index);
    }
#line 708 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 169 "SIRENParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::SEPARATOR,"/",token_index);
    }
#line 717 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 175 "SIRENParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::PLUS,"+",token_index);
    }
#line 726 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 180 "SIRENParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::MINUS,"-",token_index);
    }
#line 735 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 186 "SIRENParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::EXPONENT,"^",token_index);
    }
#line 744 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 194 "SIRENParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::EQ,"==",token_index);
    }
#line 753 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 199 "SIRENParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::NEQ,"!=",token_index);
    }
#line 762 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 204 "SIRENParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::GTE,">=",token_index);
    }
#line 771 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 209 "SIRENParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::GT,">",token_index);
    }
#line 780 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 214 "SIRENParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::LTE,"<=",token_index);
    }
#line 789 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 219 "SIRENParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::LT,"<",token_index);
    }
#line 798 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 225 "SIRENParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::WASP_AND,"&&",token_index);
    }
#line 807 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 230 "SIRENParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::WASP_OR,"||",token_index);
    }
#line 816 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 236 "SIRENParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::UNARY_NOT,"!",token_index);
    }
#line 825 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 242 "SIRENParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::LPAREN,"(",token_index);
    }
#line 834 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 247 "SIRENParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::RPAREN,")",token_index);
    }
#line 843 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 262 "SIRENParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::LBRACKET,"[",token_index);
    }
#line 852 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 267 "SIRENParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::RBRACKET,"]",token_index);
    }
#line 861 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 274 "SIRENParser.bison" // lalr1.cc:859
    {
        size_t token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::INT,"int"
                         ,token_index);
    }
#line 871 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 280 "SIRENParser.bison" // lalr1.cc:859
    {
    size_t token_index = ((yystack_[0].value.token_index));
    (yylhs.value.node_index) = interpreter.push_leaf(wasp::VALUE,"value"
                     ,token_index);
}
#line 881 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 300 "SIRENParser.bison" // lalr1.cc:859
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
#line 899 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 314 "SIRENParser.bison" // lalr1.cc:859
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
#line 917 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 328 "SIRENParser.bison" // lalr1.cc:859
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
#line 935 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 342 "SIRENParser.bison" // lalr1.cc:859
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
#line 953 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 356 "SIRENParser.bison" // lalr1.cc:859
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
#line 971 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 371 "SIRENParser.bison" // lalr1.cc:859
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
#line 989 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 385 "SIRENParser.bison" // lalr1.cc:859
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
#line 1007 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 399 "SIRENParser.bison" // lalr1.cc:859
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
#line 1023 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 411 "SIRENParser.bison" // lalr1.cc:859
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
#line 1039 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 423 "SIRENParser.bison" // lalr1.cc:859
    {
        auto token_index = ((yystack_[0].value.token_index));
        std::string quote_less_data = interpreter.token_data(token_index);
        quote_less_data = wasp::strip_quotes(quote_less_data);
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::DECL
                                   ,quote_less_data.c_str()
                                   ,token_index);
    }
#line 1052 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 433 "SIRENParser.bison" // lalr1.cc:859
    {
             (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
             (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));

        }
#line 1062 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 440 "SIRENParser.bison" // lalr1.cc:859
    {
             (yylhs.value.node_indices) = new std::vector<size_t>();
             (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1071 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 447 "SIRENParser.bison" // lalr1.cc:859
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
#line 1091 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 463 "SIRENParser.bison" // lalr1.cc:859
    {
                // capture integer index
                size_t i_i = ((yystack_[0].value.node_index));
                std::vector<size_t> child_indices = {i_i
                                                           };

                (yylhs.value.node_index) = interpreter.push_parent(wasp::INDEX
                             ,"I" // I - index
                             ,child_indices);
            }
#line 1106 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 474 "SIRENParser.bison" // lalr1.cc:859
    {
                // capture index range
                size_t si_i = ((yystack_[2].value.node_index));
                size_t c_i = ((yystack_[1].value.node_index));
                size_t ei_i = ((yystack_[0].value.node_index));
                std::vector<size_t> child_indices = {si_i
                                                           ,c_i
                                                           ,ei_i
                                                           };

                (yylhs.value.node_index) = interpreter.push_parent(wasp::INDEX
                            ,"I" // I - index
                            ,child_indices);
            }
#line 1125 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 489 "SIRENParser.bison" // lalr1.cc:859
    {
                // capture strided index range
                size_t si_i = ((yystack_[4].value.node_index));
                size_t c1_i = ((yystack_[3].value.node_index));
                size_t ei_i = ((yystack_[2].value.node_index));
                size_t c2_i = ((yystack_[1].value.node_index));
                size_t stride_i = ((yystack_[2].value.node_index));
                std::vector<size_t> child_indices = {si_i
                                                           ,c1_i
                                                           ,ei_i
                                                           ,c2_i
                                                           ,stride_i
                                                           };

                (yylhs.value.node_index) = interpreter.push_parent(wasp::INDEX
                            ,"I" // I - index
                            ,child_indices);
            }
#line 1148 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 509 "SIRENParser.bison" // lalr1.cc:859
    {
                 // capture condition predicated child selection
                 // obj[name = 'ted']
                 // obj[value <= 5]
                 size_t decl_i = ((yystack_[3].value.node_index));
                 size_t lb_i = ((yystack_[2].value.node_index));
                 size_t exp_i = ((yystack_[1].value.node_index));
                 size_t rb_i = ((yystack_[0].value.node_index));
                 std::vector<size_t> child_indices = {decl_i
                                                            ,lb_i
                                                            ,exp_i
                                                            ,rb_i
                                                            };

                 (yylhs.value.node_index) = interpreter.push_parent(wasp::PREDICATED_CHILD
                             ,"cpcs" // condition predicated child selection
                             ,child_indices);
             }
#line 1171 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 528 "SIRENParser.bison" // lalr1.cc:859
    {
                 // capture index predicated child selection
                 // obj[1]
                 // obj[1:3]
                 // obj[1:10:2]
                 size_t decl_i = ((yystack_[3].value.node_index));
                 size_t lb_i = ((yystack_[2].value.node_index));
                 size_t indices_i = ((yystack_[1].value.node_index));
                 size_t rb_i = ((yystack_[0].value.node_index));
                 std::vector<size_t> child_indices = {decl_i
                                                            ,lb_i
                                                            ,indices_i
                                                            ,rb_i
                                                            };

                 (yylhs.value.node_index) = interpreter.push_parent(wasp::PREDICATED_CHILD
                             ,"ipcs" // index predicated child selection
                             ,child_indices);
             }
#line 1195 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 548 "SIRENParser.bison" // lalr1.cc:859
    {
                 // capture parent selection
                 // obj/..
                 (yylhs.value.node_index) = (yystack_[0].value.node_index);
             }
#line 1205 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 554 "SIRENParser.bison" // lalr1.cc:859
    {
                // capture consecutive selections
                // obj/child
                // obj[name='ted']/child
                // obj[name='ted']/.[1]
                 size_t left_i = ((yystack_[2].value.node_index));
                 size_t sep_i = ((yystack_[1].value.node_index));
                 size_t right_i = ((yystack_[0].value.node_index));
                 std::vector<size_t> child_indices = {left_i
                                                            ,sep_i
                                                            ,right_i
                                                            };

                 (yylhs.value.node_index) = interpreter.push_parent(wasp::OBJECT
                             ,"O" // O - object
                             ,child_indices);
             }
#line 1227 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 572 "SIRENParser.bison" // lalr1.cc:859
    {
                // capture named child selection
                // parent//child
                // obj[name='ted']//child
                // obj[name='ted']//.[1]
                 size_t left_i = ((yystack_[2].value.node_index));
                 size_t any_i = ((yystack_[1].value.node_index));
                 size_t right_i = ((yystack_[0].value.node_index));
                 std::vector<size_t> child_indices = {left_i
                                                            ,any_i
                                                            ,right_i
                                                            };

                 (yylhs.value.node_index) = interpreter.push_parent(wasp::ANY
                             ,"A" // A - any child
                             ,child_indices);
             }
#line 1249 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 590 "SIRENParser.bison" // lalr1.cc:859
    {
                // capture named node's descendants
                // parent//
                // obj[name='ted']//
                // obj[1]//
                 size_t left_i = ((yystack_[1].value.node_index));
                 size_t any_i = ((yystack_[0].value.node_index));
                 std::vector<size_t> child_indices = {left_i
                                                            ,any_i
                                                            };

                 (yylhs.value.node_index) = interpreter.push_parent(wasp::ANY
                             ,"A" // A - any child
                             ,child_indices);
             }
#line 1269 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 611 "SIRENParser.bison" // lalr1.cc:859
    {
         // capture root only selection
         size_t s_i = ((yystack_[0].value.node_index));
         std::vector<size_t> child_indices = {s_i};
         (yylhs.value.node_index) = interpreter.push_parent(wasp::DOCUMENT_ROOT
                                         ,"R" // R - root
                                         ,child_indices);
     }
#line 1282 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 620 "SIRENParser.bison" // lalr1.cc:859
    {
         // capture root based child selection
         size_t root_i = ((yystack_[1].value.node_index));
         size_t child_i = ((yystack_[0].value.node_index));
         std::vector<size_t> child_indices = {root_i
                                                    ,child_i
                                                    };

         (yylhs.value.node_index) = interpreter.push_parent(wasp::DOCUMENT_ROOT
                                         ,"R" // R - root
                                         ,child_indices);
     }
#line 1299 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 634 "SIRENParser.bison" // lalr1.cc:859
    {
         // capture any child of the root
         size_t any_i = ((yystack_[1].value.node_index));
         size_t child_i = ((yystack_[0].value.node_index));
         std::vector<size_t> child_indices = {any_i
                                                    ,child_i
                                                    };

         (yylhs.value.node_index) = interpreter.push_parent(wasp::ANY
                                         ,"A" // A - any
                                         ,child_indices);
     }
#line 1316 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 646 "SIRENParser.bison" // lalr1.cc:859
    {interpreter.push_staged_child(((yystack_[0].value.node_index))); }
#line 1322 "SIRENParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 647 "SIRENParser.bison" // lalr1.cc:859
    {interpreter.push_staged_child(((yystack_[0].value.node_index))); }
#line 1328 "SIRENParser.cpp" // lalr1.cc:859
    break;


#line 1332 "SIRENParser.cpp" // lalr1.cc:859
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
  SIRENParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  SIRENParser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
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


  const signed char SIRENParser::yypact_ninf_ = -45;

  const signed char SIRENParser::yytable_ninf_ = -1;

  const signed char
  SIRENParser::yypact_[] =
  {
       4,   -45,   -45,   -45,   -45,   -45,   -14,   -45,   -14,   -45,
      -6,     0,   -45,     6,     0,     0,   -45,   -20,   -14,   -14,
     -45,   -45,    14,   -45,     8,   101,     1,     1,     0,     0,
     -45,    -1,   -45,   -45,   -45,   -45,   -45,   -45,   -45,     8,
       8,     8,   -45,   -45,   -45,    65,   -45,   -45,   -45,   -45,
     -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45,
     -45,   -45,    14,     5,     5,    49,   -45,   -45,   -45,   -45,
     -45,   -45,   -45,   -45,     8,     8,     8,     8,     8,     8,
     -45,   -45,    -1,   -45,   -45,     5,    24,    24,     5,    86,
      81,   -45
  };

  const unsigned char
  SIRENParser::yydefact_[] =
  {
       0,     2,     3,     7,    34,    35,    69,    63,    67,    53,
      60,    72,    71,     0,    70,    68,    32,     0,    66,     0,
       1,    40,    57,    55,     0,     0,     0,     0,    65,    64,
       4,     0,    11,    30,    29,    38,    39,    36,    37,     0,
       0,     0,    41,    42,    43,    56,    21,    24,    22,    23,
      20,    19,    54,    13,    14,    17,    15,    18,    16,    33,
      61,    62,    58,    51,    52,     0,    27,    28,     5,     6,
      10,    12,     8,     9,     0,     0,     0,     0,     0,     0,
      25,    26,     0,    31,    50,    44,    45,    46,    47,    48,
      49,    59
  };

  const signed char
  SIRENParser::yypgoto_[] =
  {
     -45,    29,   -45,   -30,   -45,   -45,    34,   -45,   -45,   -44,
     -45,    22,   -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45,
     -45,   -45,   -45,   -45,   -45,    23,   -45,   -45,   -31,   -45,
     -45,   -17,    36,   -45,   -45,   -45,   -45,    -3,   -45,   -45
  };

  const signed char
  SIRENParser::yydefgoto_[] =
  {
      -1,    18,     7,    31,    72,    73,    19,    74,    75,    39,
      77,    78,    53,    54,    55,    56,    57,    58,    79,    80,
      81,    40,    41,    84,    17,    60,     9,    42,    22,    43,
      44,    45,    10,    24,    25,    26,    27,    11,    12,    13
  };

  const unsigned char
  SIRENParser::yytable_[] =
  {
      62,    76,    16,    14,     1,    15,    20,     2,     1,    21,
      59,     4,     5,    32,    33,    28,    29,     4,     5,    76,
      76,    76,    63,    64,    65,     2,     3,    30,    21,     6,
       3,    34,    82,    71,     8,     4,     5,    35,    36,    37,
      38,    76,    76,    76,    76,    76,    76,    52,    68,    69,
      61,    91,    71,    23,    32,     0,    83,    85,    86,    87,
      88,    89,    90,    46,    47,    48,    49,    50,    51,    66,
      32,    67,     0,    68,    69,     0,    70,    71,     0,    46,
      47,    48,    49,    50,    51,    66,    32,    67,     0,    68,
      69,    32,    70,    71,     0,    46,    47,    48,    49,    50,
      51,     0,     0,     0,     0,    68,    69,     0,    70,    71,
      68,    69,     0,    70,    71,    46,    47,    48,    49,    50,
      51
  };

  const signed char
  SIRENParser::yycheck_[] =
  {
      31,    45,     8,     6,     4,     8,     0,    21,     4,    29,
       9,    31,    32,     5,     6,    18,    19,    31,    32,    63,
      64,    65,    39,    40,    41,    21,    26,    13,    29,     0,
      26,    23,    62,    28,     0,    31,    32,    29,    30,    31,
      32,    85,    86,    87,    88,    89,    90,    25,    24,    25,
      27,    82,    28,    17,     5,    -1,     7,    74,    75,    76,
      77,    78,    79,    14,    15,    16,    17,    18,    19,    20,
       5,    22,    -1,    24,    25,    -1,    27,    28,    -1,    14,
      15,    16,    17,    18,    19,    20,     5,    22,    -1,    24,
      25,     5,    27,    28,    -1,    14,    15,    16,    17,    18,
      19,    -1,    -1,    -1,    -1,    24,    25,    -1,    27,    28,
      24,    25,    -1,    27,    28,    14,    15,    16,    17,    18,
      19
  };

  const unsigned char
  SIRENParser::yystos_[] =
  {
       0,     4,    21,    26,    31,    32,    38,    39,    43,    63,
      69,    74,    75,    76,    74,    74,     8,    61,    38,    43,
       0,    29,    65,    69,    70,    71,    72,    73,    74,    74,
      13,    40,     5,     6,    23,    29,    30,    31,    32,    46,
      58,    59,    64,    66,    67,    68,    14,    15,    16,    17,
      18,    19,    48,    49,    50,    51,    52,    53,    54,     9,
      62,    62,    65,    68,    68,    68,    20,    22,    24,    25,
      27,    28,    41,    42,    44,    45,    46,    47,    48,    55,
      56,    57,    40,     7,    60,    68,    68,    68,    68,    68,
      68,    65
  };

  const unsigned char
  SIRENParser::yyr1_[] =
  {
       0,    37,    38,    39,    40,    41,    42,    43,    44,    44,
      45,    46,    47,    48,    48,    48,    48,    48,    48,    49,
      50,    51,    52,    53,    54,    55,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    63,    64,    64,    64,    64,
      65,    66,    67,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    69,    70,    71,    72,    73,    73,    73,
      74,    74,    74,    74,    74,    74,    74,    75,    75,    75,
      75,    76,    76
  };

  const unsigned char
  SIRENParser::yyr2_[] =
  {
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     1,     2,     1,     2,     1,     3,     5,
       1,     4,     4,     1,     3,     3,     2,     1,     2,     1,
       2,     1,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const SIRENParser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"end of line\"", "\"//\"",
  "\"-\"", "\"(\"", "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\",\"",
  "\":\"", "\">=\"", "\"<\"", "\">\"", "\"<=\"", "\"!=\"", "\"=\"",
  "\"&&\"", "\"..\"", "\"||\"", "\"!\"", "\"*\"", "\"division operator\"",
  "\"path separator\"", "\"+\"", "\"^\"", "\"integer\"", "\"double\"",
  "\"decl\"", "\"quoted string\"", "ASSIGN", "UMINUS", "UNOT", "\"exp\"",
  "$accept", "any_selection", "parent_selection", "colon", "multiply",
  "divide", "separator", "multiply_divide", "plus", "minus", "exponent",
  "boolean_numeric_op", "eq", "neq", "gte", "gt", "lte", "lt",
  "boolean_logic_op", "and", "or", "unary_not", "lparen", "rparen",
  "lbracket", "rbracket", "ANY_STRING", "PRIMITIVE", "integer", "value",
  "component", "exp", "decl", "key_declaration", "tag", "keyedvalue",
  "indices_selection", "relative_selection", "root_based_selection",
  "start", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  SIRENParser::yyrline_[] =
  {
       0,   135,   135,   140,   151,   156,   161,   168,   173,   173,
     174,   179,   185,   191,   191,   191,   191,   191,   191,   193,
     198,   203,   208,   213,   218,   223,   223,   224,   229,   235,
     241,   246,   261,   266,   272,   272,   273,   273,   273,   273,
     274,   279,   296,   298,   299,   313,   327,   341,   355,   370,
     384,   398,   410,   422,   432,   439,   446,   462,   473,   488,
     507,   508,   527,   547,   553,   571,   589,   610,   619,   632,
     633,   646,   647
  };

  // Print the state stack on the debug stream.
  void
  SIRENParser::yystack_print_ ()
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
  SIRENParser::yy_reduce_print_ (int yyrule)
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
  SIRENParser::token_number_type
  SIRENParser::yytranslate_ (int t)
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
      35,    36
    };
    const unsigned int user_token_number_max_ = 291;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

#line 32 "SIRENParser.bison" // lalr1.cc:1167
} // wasp
#line 1835 "SIRENParser.cpp" // lalr1.cc:1167
#line 652 "SIRENParser.bison" // lalr1.cc:1168
 /*** Additional Code ***/

void wasp::SIRENParser::error(const SIRENParser::location_type& l,
                           const std::string& m)
{
    interpreter.error_stream()<<l<<": "<<m<<std::endl;
}
