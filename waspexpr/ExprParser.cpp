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
#line 1 "Expr.bison" // lalr1.cc:404
 /*** C/C++ Declarations ***/

#include <stdio.h>
#include <vector>


#line 45 "ExprParser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "ExprParser.hpp"

// User implementation prologue.
#line 113 "Expr.bison" // lalr1.cc:412


#include "ExprInterpreter.h"
#include "ExprLexer.h"

/* this "connects" the Expr parser in the interpreter to the flex ExprLexer class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the interpreter context. */
#undef yylex
#define yylex interpreter.m_lexer->lex


#line 71 "ExprParser.cpp" // lalr1.cc:412


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
#line 157 "ExprParser.cpp" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  ExprParser::yytnamerr_ (const char *yystr)
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
  ExprParser::ExprParser (class ExprInterpreter& interpreter_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      interpreter (interpreter_yyarg)
  {}

  ExprParser::~ExprParser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  ExprParser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  ExprParser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  ExprParser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
    value = other.value;
  }


  template <typename Base>
  inline
  ExprParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  ExprParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  inline
  ExprParser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  ExprParser::basic_symbol<Base>::clear ()
  {
    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  ExprParser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  ExprParser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
    location = s.location;
  }

  // by_type.
  inline
  ExprParser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  ExprParser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  ExprParser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  ExprParser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  ExprParser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  ExprParser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  ExprParser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  ExprParser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  ExprParser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  ExprParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  ExprParser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  ExprParser::symbol_number_type
  ExprParser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  ExprParser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  ExprParser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    value = that.value;
    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  ExprParser::stack_symbol_type&
  ExprParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  ExprParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YYUSE (yysym.type_get ());
  }

#if YYDEBUG
  template <typename Base>
  void
  ExprParser::yy_print_ (std::ostream& yyo,
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
  ExprParser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  ExprParser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  ExprParser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  ExprParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  ExprParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  ExprParser::debug_level_type
  ExprParser::debug_level () const
  {
    return yydebug_;
  }

  void
  ExprParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline ExprParser::state_type
  ExprParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  ExprParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  ExprParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  ExprParser::parse ()
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
    #line 40 "Expr.bison" // lalr1.cc:741
{
    // initialize the initial location object
    yyla.location.begin.filename = yyla.location.end.filename = &interpreter.m_stream_name;
    yyla.location.begin.line = yyla.location.end.line = interpreter.m_start_line;
    yyla.location.begin.column = yyla.location.end.column = interpreter.m_start_column;
}

#line 538 "ExprParser.cpp" // lalr1.cc:741

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
#line 130 "Expr.bison" // lalr1.cc:859
    {unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));(yylhs.value.node_index) = interpreter.push_leaf(wasp::BANG      ,"!",token_index);}
#line 648 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 131 "Expr.bison" // lalr1.cc:859
    {unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));(yylhs.value.node_index) = interpreter.push_leaf(wasp::GT      ,">",token_index);}
#line 654 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 132 "Expr.bison" // lalr1.cc:859
    {unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));(yylhs.value.node_index) = interpreter.push_leaf(wasp::LT      ,"<",token_index);}
#line 660 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 133 "Expr.bison" // lalr1.cc:859
    {unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));(yylhs.value.node_index) = interpreter.push_leaf(wasp::GTE      ,">=",token_index);}
#line 666 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 134 "Expr.bison" // lalr1.cc:859
    {unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));(yylhs.value.node_index) = interpreter.push_leaf(wasp::LTE      ,"<=",token_index);}
#line 672 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 135 "Expr.bison" // lalr1.cc:859
    {unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));(yylhs.value.node_index) = interpreter.push_leaf(wasp::NEQ      ,"!=",token_index);}
#line 678 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 136 "Expr.bison" // lalr1.cc:859
    {unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));(yylhs.value.node_index) = interpreter.push_leaf(wasp::EQ       ,"==",token_index);}
#line 684 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 137 "Expr.bison" // lalr1.cc:859
    {unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));(yylhs.value.node_index) = interpreter.push_leaf(wasp::AND      ,"&&",token_index);}
#line 690 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 138 "Expr.bison" // lalr1.cc:859
    {unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));(yylhs.value.node_index) = interpreter.push_leaf(wasp::OR       ,"||",token_index);}
#line 696 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 139 "Expr.bison" // lalr1.cc:859
    {unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));(yylhs.value.node_index) = interpreter.push_leaf(wasp::MULTIPLY , "*",token_index);}
#line 702 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 140 "Expr.bison" // lalr1.cc:859
    {unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));(yylhs.value.node_index) = interpreter.push_leaf(wasp::DIVIDE   ,"/" ,token_index);}
#line 708 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 141 "Expr.bison" // lalr1.cc:859
    {unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));(yylhs.value.node_index) = interpreter.push_leaf(wasp::PLUS     ,"+" ,token_index);}
#line 714 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 142 "Expr.bison" // lalr1.cc:859
    {unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));(yylhs.value.node_index) = interpreter.push_leaf(wasp::MINUS    ,"-" ,token_index);}
#line 720 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 143 "Expr.bison" // lalr1.cc:859
    {unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));(yylhs.value.node_index) = interpreter.push_leaf(wasp::EXPONENT ,"^" ,token_index);}
#line 726 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 144 "Expr.bison" // lalr1.cc:859
    {unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));(yylhs.value.node_index) = interpreter.push_leaf(wasp::LPAREN   ,"(" ,token_index);}
#line 732 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 145 "Expr.bison" // lalr1.cc:859
    {unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));(yylhs.value.node_index) = interpreter.push_leaf(wasp::RPAREN   ,")" ,token_index);}
#line 738 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 203 "Expr.bison" // lalr1.cc:859
    {
        unsigned int left_index = static_cast<unsigned int>((yystack_[1].value.node_index));
        unsigned int op_index = static_cast<unsigned int>((yystack_[0].value.node_index));
        std::vector<unsigned int> child_indices = {left_index
                                                   ,op_index};
        (yylhs.value.node_index) = interpreter.push_parent(wasp::UNARY_MINUS
                                        ,"exp"
                                        ,child_indices);
    }
#line 752 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 213 "Expr.bison" // lalr1.cc:859
    {
       unsigned int left_index = static_cast<unsigned int>((yystack_[1].value.node_index));
       unsigned int op_index = static_cast<unsigned int>((yystack_[0].value.node_index));
       std::vector<unsigned int> child_indices = {left_index
                                                  ,op_index};
       (yylhs.value.node_index) = interpreter.push_parent(wasp::UNARY_NOT
                                       ,"exp"
                                       ,child_indices);
    }
#line 766 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 223 "Expr.bison" // lalr1.cc:859
    {
        unsigned int left_index = static_cast<unsigned int>((yystack_[2].value.node_index));
        unsigned int op_index = static_cast<unsigned int>((yystack_[1].value.node_index));
        unsigned int right_index = static_cast<unsigned int>((yystack_[0].value.node_index));
        std::vector<unsigned int> child_indices = {left_index
                                                   ,op_index
                                                   ,right_index};
        (yylhs.value.node_index) = interpreter.push_parent(wasp::PARENTHESIS
                                        ,"exp"
                                        ,child_indices);
    }
#line 782 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 235 "Expr.bison" // lalr1.cc:859
    {
        unsigned int left_index = static_cast<unsigned int>((yystack_[2].value.node_index));
        unsigned int op_index = static_cast<unsigned int>((yystack_[1].value.node_index));
        unsigned int right_index = static_cast<unsigned int>((yystack_[0].value.node_index));
        std::vector<unsigned int> child_indices = {left_index
                                                   ,op_index
                                                   ,right_index};
        (yylhs.value.node_index) = interpreter.push_parent(wasp::MULTIPLY
                                        ,"exp"
                                        ,child_indices);
    }
#line 798 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 247 "Expr.bison" // lalr1.cc:859
    {
       unsigned int left_index = static_cast<unsigned int>((yystack_[2].value.node_index));
       unsigned int op_index = static_cast<unsigned int>((yystack_[1].value.node_index));
       unsigned int right_index = static_cast<unsigned int>((yystack_[0].value.node_index));
       std::vector<unsigned int> child_indices = {left_index
                                                  ,op_index
                                                  ,right_index};
       (yylhs.value.node_index) = interpreter.push_parent(wasp::DIVIDE
                                       ,"exp"
                                       ,child_indices);
   }
#line 814 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 259 "Expr.bison" // lalr1.cc:859
    {
      unsigned int left_index = static_cast<unsigned int>((yystack_[2].value.node_index));
      unsigned int op_index = static_cast<unsigned int>((yystack_[1].value.node_index));
      unsigned int right_index = static_cast<unsigned int>((yystack_[0].value.node_index));
      std::vector<unsigned int> child_indices = {left_index
                                                 ,op_index
                                                 ,right_index};
      (yylhs.value.node_index) = interpreter.push_parent(wasp::PLUS
                                      ,"exp"
                                      ,child_indices);
   }
#line 830 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 271 "Expr.bison" // lalr1.cc:859
    {
      unsigned int left_index = static_cast<unsigned int>((yystack_[2].value.node_index));
      unsigned int op_index = static_cast<unsigned int>((yystack_[1].value.node_index));
      unsigned int right_index = static_cast<unsigned int>((yystack_[0].value.node_index));
      std::vector<unsigned int> child_indices = {left_index
                                                 ,op_index
                                                 ,right_index};
      (yylhs.value.node_index) = interpreter.push_parent(wasp::MINUS
                                      ,"exp"
                                      ,child_indices);
   }
#line 846 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 283 "Expr.bison" // lalr1.cc:859
    {
      unsigned int left_index = static_cast<unsigned int>((yystack_[2].value.node_index));
      unsigned int op_index = static_cast<unsigned int>((yystack_[1].value.node_index));
      unsigned int right_index = static_cast<unsigned int>((yystack_[0].value.node_index));
      std::vector<unsigned int> child_indices = {left_index
                                                 ,op_index
                                                 ,right_index};
      (yylhs.value.node_index) = interpreter.push_parent(wasp::EXPONENT
                                      ,"exp"
                                      ,child_indices);
   }
#line 862 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 295 "Expr.bison" // lalr1.cc:859
    {
      unsigned int left_index = static_cast<unsigned int>((yystack_[2].value.node_index));
      unsigned int op_index = static_cast<unsigned int>((yystack_[1].value.node_index));
      unsigned int right_index = static_cast<unsigned int>((yystack_[0].value.node_index));
      std::vector<unsigned int> child_indices = {left_index
                                                 ,op_index
                                                 ,right_index};
      (yylhs.value.node_index) = interpreter.push_parent(wasp::EQ
                                      ,"exp"
                                      ,child_indices);
   }
#line 878 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 307 "Expr.bison" // lalr1.cc:859
    {
      unsigned int left_index = static_cast<unsigned int>((yystack_[2].value.node_index));
      unsigned int op_index = static_cast<unsigned int>((yystack_[1].value.node_index));
      unsigned int right_index = static_cast<unsigned int>((yystack_[0].value.node_index));
      std::vector<unsigned int> child_indices = {left_index
                                                 ,op_index
                                                 ,right_index};
      (yylhs.value.node_index) = interpreter.push_parent(wasp::NEQ
                                      ,"exp"
                                      ,child_indices);
   }
#line 894 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 319 "Expr.bison" // lalr1.cc:859
    {
      unsigned int left_index = static_cast<unsigned int>((yystack_[2].value.node_index));
      unsigned int op_index = static_cast<unsigned int>((yystack_[1].value.node_index));
      unsigned int right_index = static_cast<unsigned int>((yystack_[0].value.node_index));
      std::vector<unsigned int> child_indices = {left_index
                                                 ,op_index
                                                 ,right_index};
      (yylhs.value.node_index) = interpreter.push_parent(wasp::AND
                                      ,"exp"
                                      ,child_indices);
   }
#line 910 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 331 "Expr.bison" // lalr1.cc:859
    {
      unsigned int left_index = static_cast<unsigned int>((yystack_[2].value.node_index));
      unsigned int op_index = static_cast<unsigned int>((yystack_[1].value.node_index));
      unsigned int right_index = static_cast<unsigned int>((yystack_[0].value.node_index));
      std::vector<unsigned int> child_indices = {left_index
                                                 ,op_index
                                                 ,right_index};
      (yylhs.value.node_index) = interpreter.push_parent(wasp::OR
                                      ,"exp"
                                      ,child_indices);
   }
#line 926 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 343 "Expr.bison" // lalr1.cc:859
    {
      unsigned int left_index = static_cast<unsigned int>((yystack_[2].value.node_index));
      unsigned int op_index = static_cast<unsigned int>((yystack_[1].value.node_index));
      unsigned int right_index = static_cast<unsigned int>((yystack_[0].value.node_index));
      std::vector<unsigned int> child_indices = {left_index
                                                 ,op_index
                                                 ,right_index};
      (yylhs.value.node_index) = interpreter.push_parent(wasp::GTE
                                      ,"exp"
                                      ,child_indices);
   }
#line 942 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 355 "Expr.bison" // lalr1.cc:859
    {
      unsigned int left_index = static_cast<unsigned int>((yystack_[2].value.node_index));
      unsigned int op_index = static_cast<unsigned int>((yystack_[1].value.node_index));
      unsigned int right_index = static_cast<unsigned int>((yystack_[0].value.node_index));
      std::vector<unsigned int> child_indices = {left_index
                                                 ,op_index
                                                 ,right_index};
      (yylhs.value.node_index) = interpreter.push_parent(wasp::GT
                                      ,"exp"
                                      ,child_indices);
   }
#line 958 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 367 "Expr.bison" // lalr1.cc:859
    {
      unsigned int left_index = static_cast<unsigned int>((yystack_[2].value.node_index));
      unsigned int op_index = static_cast<unsigned int>((yystack_[1].value.node_index));
      unsigned int right_index = static_cast<unsigned int>((yystack_[0].value.node_index));
      std::vector<unsigned int> child_indices = {left_index
                                                 ,op_index
                                                 ,right_index};
      (yylhs.value.node_index) = interpreter.push_parent(wasp::LTE
                                      ,"exp"
                                      ,child_indices);
   }
#line 974 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 379 "Expr.bison" // lalr1.cc:859
    {
      unsigned int left_index = static_cast<unsigned int>((yystack_[2].value.node_index));
      unsigned int op_index = static_cast<unsigned int>((yystack_[1].value.node_index));
      unsigned int right_index = static_cast<unsigned int>((yystack_[0].value.node_index));
      std::vector<unsigned int> child_indices = {left_index
                                                 ,op_index
                                                 ,right_index};
      (yylhs.value.node_index) = interpreter.push_parent(wasp::LT
                                      ,"exp"
                                      ,child_indices);
   }
#line 990 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 391 "Expr.bison" // lalr1.cc:859
    {
        unsigned int assign_token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::ASSIGN,"="
                         ,assign_token_index);
    }
#line 1000 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 431 "Expr.bison" // lalr1.cc:859
    {
        unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::VALUE,"value"
                         ,token_index);
    }
#line 1010 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 438 "Expr.bison" // lalr1.cc:859
    {
        unsigned int decl_token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::DECL,"decl"
                         ,decl_token_index);
    }
#line 1020 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 446 "Expr.bison" // lalr1.cc:859
    {        

        unsigned int key_index = static_cast<unsigned int>((yystack_[2].value.node_index));
        unsigned int assign_index = static_cast<unsigned int>((yystack_[1].value.node_index));
        unsigned int value_index = static_cast<unsigned int>((yystack_[0].value.node_index));

        std::vector<unsigned int> child_indices = {key_index, assign_index,value_index};

        (yylhs.value.node_index) = interpreter.push_parent(wasp::KEYED_VALUE
                                        ,interpreter.m_tree_nodes.data(key_index).c_str()
                                        ,child_indices);
    }
#line 1037 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 461 "Expr.bison" // lalr1.cc:859
    {
        unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::COMMENT,"comment"
                         ,token_index);
    }
#line 1047 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 468 "Expr.bison" // lalr1.cc:859
    {
            interpreter.add_root_child_index(static_cast<unsigned int>((yystack_[0].value.node_index)));
        }
#line 1055 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 471 "Expr.bison" // lalr1.cc:859
    {
            interpreter.add_root_child_index(static_cast<unsigned int>((yystack_[0].value.node_index)));
        }
#line 1063 "ExprParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 474 "Expr.bison" // lalr1.cc:859
    {
            interpreter.add_root_child_index(static_cast<unsigned int>((yystack_[0].value.node_index)));
        }
#line 1071 "ExprParser.cpp" // lalr1.cc:859
    break;


#line 1075 "ExprParser.cpp" // lalr1.cc:859
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
  ExprParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  ExprParser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
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


  const signed char ExprParser::yypact_ninf_ = -18;

  const signed char ExprParser::yytable_ninf_ = -41;

  const signed char
  ExprParser::yypact_[] =
  {
     -18,    67,   -18,   -18,   -18,   -18,   -18,   -18,    -2,   -18,
      -7,    -7,    -7,    87,   -18,   -18,   -18,     2,   -18,   -18,
     -18,   -11,   -11,    65,   -18,   -18,   -18,   -18,   -18,   -18,
     -18,   -18,   -18,   -18,   -18,   -18,    -7,    -7,    -7,    -7,
      -7,    -7,    -7,    -7,    -7,    -7,    -7,    -7,    -7,   -18,
      -7,   -18,   -18,   -17,   -17,   -17,   -17,   -17,   -17,   100,
     100,   -11,   -11,     3,     3,   -11,    87
  };

  const unsigned char
  ExprParser::yydefact_[] =
  {
      44,     0,     1,     2,    14,    16,    36,    37,    38,    43,
       0,     0,     0,    47,    39,    18,    41,     0,    46,    45,
      38,    20,    19,     0,     5,     6,     4,     3,     7,     8,
       9,    10,    11,    12,    13,    15,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    35,
       0,    17,    21,    32,    34,    31,    33,    28,    27,    29,
      30,    22,    23,    24,    25,    26,    42
  };

  const signed char
  ExprParser::yypgoto_[] =
  {
     -18,   -18,   -18,   -18,   -18,   -18,   -18,   -18,   -18,   -18,
     -18,   -18,   -18,   -13,   -18,   -18,   -18,    18,   -18,   -18,
     -18,   -18,   -18,   -18,   -18,   -18
  };

  const signed char
  ExprParser::yydefgoto_[] =
  {
      -1,    10,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    11,    48,    12,    52,    13,    50,    14,
      15,    16,    17,    18,    19,     1
  };

  const signed char
  ExprParser::yytable_[] =
  {
      47,     3,    32,    33,    34,     4,    35,   -40,    47,    47,
      47,    49,    35,     0,     0,     4,     0,     5,     0,     6,
       7,    20,    32,    33,     0,     0,    35,     0,    21,    22,
      23,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,     2,    66,     0,
       0,     0,     0,     0,     0,     3,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,     4,    35,     4,
      51,     5,     0,     6,     7,     8,     0,     9,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,     4,
      35,    24,    25,    26,    27,    28,    29,     0,     0,    32,
      33,    34,     4,    35
  };

  const signed char
  ExprParser::yycheck_[] =
  {
      13,     8,    19,    20,    21,    22,    23,     9,    21,    22,
      23,     9,    23,    -1,    -1,    22,    -1,    24,    -1,    26,
      27,    28,    19,    20,    -1,    -1,    23,    -1,    10,    11,
      12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,     0,    50,    -1,
      -1,    -1,    -1,    -1,    -1,     8,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    22,
      25,    24,    -1,    26,    27,    28,    -1,    30,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    11,    12,    13,    14,    15,    16,    -1,    -1,    19,
      20,    21,    22,    23
  };

  const unsigned char
  ExprParser::yystos_[] =
  {
       0,    62,     0,     8,    22,    24,    26,    27,    28,    30,
      38,    50,    52,    54,    56,    57,    58,    59,    60,    61,
      28,    54,    54,    54,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    23,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,     9,
      55,    25,    53,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54
  };

  const unsigned char
  ExprParser::yyr1_[] =
  {
       0,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    55,    56,    56,    56,    57,
      58,    59,    60,    61,    62,    62,    62,    62
  };

  const unsigned char
  ExprParser::yyr2_[] =
  {
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     0,     2,     2,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const ExprParser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"end of line\"", "\"[\"",
  "\"]\"", "'{'", "'}'", "\"!\"", "\"=\"", "\",\"", "\">=\"", "\"<=\"",
  "\"<\"", "\">\"", "\"!=\"", "\"==\"", "\"&&\"", "\"||\"", "\"*\"",
  "\"/\"", "\"+\"", "\"-\"", "\"^\"", "\"(\"", "\")\"", "\"integer\"",
  "\"real\"", "\"string\"", "\"quoted string\"", "\"comment\"",
  "\"declarator\"", "\"value\"", "UMINUS", "UNOT", "\"constant\"",
  "\"name\"", "$accept", "bang", "gt", "lt", "gte", "lte", "neq", "eq",
  "and", "or", "multiply", "divide", "plus", "minus", "exponent", "lparen",
  "rparen", "math_exp", "assign", "VALUE", "value", "DECL", "decl",
  "keyedvalue", "comment", "start", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  ExprParser::yyrline_[] =
  {
       0,   130,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   201,   202,
     212,   222,   234,   246,   258,   270,   282,   294,   306,   318,
     330,   342,   354,   366,   378,   390,   429,   429,   429,   430,
     436,   437,   445,   460,   467,   468,   471,   474
  };

  // Print the state stack on the debug stream.
  void
  ExprParser::yystack_print_ ()
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
  ExprParser::yy_reduce_print_ (int yyrule)
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
  ExprParser::token_number_type
  ExprParser::yytranslate_ (int t)
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
       2,     2,     2,     6,     2,     7,     2,     2,     2,     2,
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
       5,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36
    };
    const unsigned int user_token_number_max_ = 289;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // wasp
#line 1553 "ExprParser.cpp" // lalr1.cc:1167
#line 482 "Expr.bison" // lalr1.cc:1168
 /*** Additional Code ***/
namespace wasp{
void ExprParser::error(const ExprParser::location_type& l,
                           const std::string& m)
{
    interpreter.error(l, m);
}
}; // end of namespace
