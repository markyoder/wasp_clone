// A Bison parser, made by GNU Bison 3.7.6.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

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

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.



// First part of user prologue.
#line 1 "SONParser.bison"
 /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>

#line 48 "SONParser.cpp"


#include "SONParser.hpp"

// Second part of user prologue.
#line 134 "SONParser.bison"


#include "SONInterpreter.h"
#include "SONLexer.h"

/* this "connects" the bison parser in the interpreter to the flex SONLexer class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the interpreter context. */
#undef yylex
#define yylex lexer->lex


#line 67 "SONParser.cpp"



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


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
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
    while (false)
# endif


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
      *yycdebug_ << '\n';                       \
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
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 32 "SONParser.bison"
namespace wasp {
#line 161 "SONParser.cpp"

  /// Build a parser object.
  SONParser::SONParser (class AbstractInterpreter& interpreter_yyarg, std::istream &input_stream_yyarg, std::shared_ptr<class SONLexerImpl> lexer_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      interpreter (interpreter_yyarg),
      input_stream (input_stream_yyarg),
      lexer (lexer_yyarg)
  {}

  SONParser::~SONParser ()
  {}

  SONParser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/

  // basic_symbol.
  template <typename Base>
  SONParser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
    , location (that.location)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  SONParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_MOVE_REF (location_type) l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  SONParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (semantic_type) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  SONParser::symbol_kind_type
  SONParser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

  template <typename Base>
  bool
  SONParser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  SONParser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
    location = YY_MOVE (s.location);
  }

  // by_kind.
  SONParser::by_kind::by_kind ()
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  SONParser::by_kind::by_kind (by_kind&& that)
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  SONParser::by_kind::by_kind (const by_kind& that)
    : kind_ (that.kind_)
  {}

  SONParser::by_kind::by_kind (token_kind_type t)
    : kind_ (yytranslate_ (t))
  {}

  void
  SONParser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  SONParser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  SONParser::symbol_kind_type
  SONParser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }

  SONParser::symbol_kind_type
  SONParser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  // by_state.
  SONParser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  SONParser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  SONParser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  SONParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  SONParser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  SONParser::symbol_kind_type
  SONParser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  SONParser::stack_symbol_type::stack_symbol_type ()
  {}

  SONParser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value), YY_MOVE (that.location))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  SONParser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value), YY_MOVE (that.location))
  {
    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  SONParser::stack_symbol_type&
  SONParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }

  SONParser::stack_symbol_type&
  SONParser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  SONParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    switch (yysym.kind ())
    {
      case symbol_kind::S_key_declaration: // key_declaration
#line 133 "SONParser.bison"
                    { delete (yysym.value.node_indices); }
#line 369 "SONParser.cpp"
        break;

      case symbol_kind::S_declaration: // declaration
#line 133 "SONParser.bison"
                    { delete (yysym.value.node_indices); }
#line 375 "SONParser.cpp"
        break;

      case symbol_kind::S_tag: // tag
#line 132 "SONParser.bison"
                    { delete (yysym.value.node_indices); }
#line 381 "SONParser.cpp"
        break;

      case symbol_kind::S_members: // members
#line 132 "SONParser.bison"
                    { delete (yysym.value.node_indices); }
#line 387 "SONParser.cpp"
        break;

      case symbol_kind::S_array_members: // array_members
#line 132 "SONParser.bison"
                    { delete (yysym.value.node_indices); }
#line 393 "SONParser.cpp"
        break;

      default:
        break;
    }
  }

#if YYDEBUG
  template <typename Base>
  void
  SONParser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  SONParser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  SONParser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  SONParser::yypop_ (int n)
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

  SONParser::state_type
  SONParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  SONParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  SONParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  SONParser::operator() ()
  {
    return parse ();
  }

  int
  SONParser::parse ()
  {
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

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    // User initialization code.
#line 41 "SONParser.bison"
{
    // initialize the initial location object
    yyla.location.begin.filename = yyla.location.end.filename = &interpreter.stream_name();
    yyla.location.begin.line = yyla.location.end.line = interpreter.start_line();
    yyla.location.begin.column = yyla.location.end.column = interpreter.start_column();
    lexer = std::make_shared<SONLexerImpl>(interpreter,&input_stream);
}

#line 539 "SONParser.cpp"


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

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
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // filler: "filler"
#line 151 "SONParser.bison"
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::FILL_EXPR,"filler",token_index);
    }
#line 680 "SONParser.cpp"
    break;

  case 3: // comma: ","
#line 156 "SONParser.bison"
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::WASP_COMMA,",",token_index);
    }
#line 689 "SONParser.cpp"
    break;

  case 4: // multiply: "*"
#line 166 "SONParser.bison"
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::MULTIPLY,"*",token_index);
    }
#line 698 "SONParser.cpp"
    break;

  case 5: // divide: "/"
#line 171 "SONParser.bison"
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::DIVIDE,"/",token_index);
    }
#line 707 "SONParser.cpp"
    break;

  case 6: // multiply_divide: multiply
#line 175 "SONParser.bison"
                  { (yylhs.value.node_index) = (yystack_[0].value.node_index); }
#line 713 "SONParser.cpp"
    break;

  case 7: // multiply_divide: divide
#line 175 "SONParser.bison"
                             { (yylhs.value.node_index) = (yystack_[0].value.node_index); }
#line 719 "SONParser.cpp"
    break;

  case 8: // plus: "+"
#line 177 "SONParser.bison"
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::PLUS,"+",token_index);
    }
#line 728 "SONParser.cpp"
    break;

  case 9: // minus: "-"
#line 182 "SONParser.bison"
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::MINUS,"-",token_index);
    }
#line 737 "SONParser.cpp"
    break;

  case 10: // exponent: "^"
#line 188 "SONParser.bison"
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::EXPONENT,"^",token_index);
    }
#line 746 "SONParser.cpp"
    break;

  case 11: // BOOLEAN: "true"
#line 192 "SONParser.bison"
          { (yylhs.value.token_index) = (yystack_[0].value.token_index); }
#line 752 "SONParser.cpp"
    break;

  case 12: // BOOLEAN: "false"
#line 192 "SONParser.bison"
                       { (yylhs.value.token_index) = (yystack_[0].value.token_index); }
#line 758 "SONParser.cpp"
    break;

  case 13: // boolean_numeric_op: eq
#line 194 "SONParser.bison"
                     { (yylhs.value.node_index) = (yystack_[0].value.node_index); }
#line 764 "SONParser.cpp"
    break;

  case 14: // boolean_numeric_op: neq
#line 194 "SONParser.bison"
                          { (yylhs.value.node_index) = (yystack_[0].value.node_index); }
#line 770 "SONParser.cpp"
    break;

  case 15: // boolean_numeric_op: gt
#line 194 "SONParser.bison"
                                { (yylhs.value.node_index) = (yystack_[0].value.node_index); }
#line 776 "SONParser.cpp"
    break;

  case 16: // boolean_numeric_op: lt
#line 194 "SONParser.bison"
                                     { (yylhs.value.node_index) = (yystack_[0].value.node_index); }
#line 782 "SONParser.cpp"
    break;

  case 17: // boolean_numeric_op: gte
#line 194 "SONParser.bison"
                                          { (yylhs.value.node_index) = (yystack_[0].value.node_index); }
#line 788 "SONParser.cpp"
    break;

  case 18: // boolean_numeric_op: lte
#line 194 "SONParser.bison"
                                                { (yylhs.value.node_index) = (yystack_[0].value.node_index); }
#line 794 "SONParser.cpp"
    break;

  case 19: // eq: "=="
#line 197 "SONParser.bison"
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::EQ,"==",token_index);
    }
#line 803 "SONParser.cpp"
    break;

  case 20: // neq: "!="
#line 202 "SONParser.bison"
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::NEQ,"!=",token_index);
    }
#line 812 "SONParser.cpp"
    break;

  case 21: // gte: ">="
#line 207 "SONParser.bison"
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::GTE,">=",token_index);
    }
#line 821 "SONParser.cpp"
    break;

  case 22: // gt: ">"
#line 212 "SONParser.bison"
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::GT,">",token_index);
    }
#line 830 "SONParser.cpp"
    break;

  case 23: // lte: "<="
#line 217 "SONParser.bison"
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::LTE,"<=",token_index);
    }
#line 839 "SONParser.cpp"
    break;

  case 24: // lt: "<"
#line 222 "SONParser.bison"
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::LT,"<",token_index);
    }
#line 848 "SONParser.cpp"
    break;

  case 25: // boolean_logic_op: and
#line 226 "SONParser.bison"
                   { (yylhs.value.node_index) = (yystack_[0].value.node_index); }
#line 854 "SONParser.cpp"
    break;

  case 26: // boolean_logic_op: or
#line 226 "SONParser.bison"
                         { (yylhs.value.node_index) = (yystack_[0].value.node_index); }
#line 860 "SONParser.cpp"
    break;

  case 27: // and: "&&"
#line 228 "SONParser.bison"
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::WASP_AND,"&&",token_index);
    }
#line 869 "SONParser.cpp"
    break;

  case 28: // or: "||"
#line 233 "SONParser.bison"
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::WASP_OR,"||",token_index);
    }
#line 878 "SONParser.cpp"
    break;

  case 29: // unary_not: "!"
#line 239 "SONParser.bison"
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::UNARY_NOT,"!",token_index);
    }
#line 887 "SONParser.cpp"
    break;

  case 30: // lparen: "("
#line 245 "SONParser.bison"
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::LPAREN,"(",token_index);
    }
#line 896 "SONParser.cpp"
    break;

  case 31: // rparen: ")"
#line 250 "SONParser.bison"
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::RPAREN,")",token_index);
    }
#line 905 "SONParser.cpp"
    break;

  case 32: // lbrace: "{"
#line 255 "SONParser.bison"
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::LBRACE,"{",token_index);
    }
#line 914 "SONParser.cpp"
    break;

  case 33: // rbrace: "}"
#line 260 "SONParser.bison"
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::RBRACE,"}",token_index);
    }
#line 923 "SONParser.cpp"
    break;

  case 34: // lbracket: "["
#line 265 "SONParser.bison"
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::LBRACKET,"[",token_index);
    }
#line 932 "SONParser.cpp"
    break;

  case 35: // rbracket: "]"
#line 270 "SONParser.bison"
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::RBRACKET,"]",token_index);
    }
#line 941 "SONParser.cpp"
    break;

  case 36: // ANY_STRING: "string"
#line 275 "SONParser.bison"
             { (yylhs.value.token_index) = (yystack_[0].value.token_index); }
#line 947 "SONParser.cpp"
    break;

  case 37: // ANY_STRING: "quoted string"
#line 275 "SONParser.bison"
                      { (yylhs.value.token_index) = (yystack_[0].value.token_index); }
#line 953 "SONParser.cpp"
    break;

  case 38: // PRIMITIVE: "string"
#line 276 "SONParser.bison"
            { (yylhs.value.token_index) = (yystack_[0].value.token_index); }
#line 959 "SONParser.cpp"
    break;

  case 39: // PRIMITIVE: "quoted string"
#line 276 "SONParser.bison"
                     { (yylhs.value.token_index) = (yystack_[0].value.token_index); }
#line 965 "SONParser.cpp"
    break;

  case 40: // PRIMITIVE: "integer"
#line 276 "SONParser.bison"
                               { (yylhs.value.token_index) = (yystack_[0].value.token_index); }
#line 971 "SONParser.cpp"
    break;

  case 41: // PRIMITIVE: "double"
#line 276 "SONParser.bison"
                                         { (yylhs.value.token_index) = (yystack_[0].value.token_index); }
#line 977 "SONParser.cpp"
    break;

  case 42: // PRIMITIVE: BOOLEAN
#line 276 "SONParser.bison"
                                                  { (yylhs.value.token_index) = (yystack_[0].value.token_index); }
#line 983 "SONParser.cpp"
    break;

  case 43: // value: PRIMITIVE
#line 279 "SONParser.bison"
{
    size_t token_index = ((yystack_[0].value.token_index));
    (yylhs.value.node_index) = interpreter.push_leaf(wasp::VALUE,"value"
                     ,token_index);
}
#line 993 "SONParser.cpp"
    break;

  case 44: // component: value
#line 296 "SONParser.bison"
            { (yylhs.value.node_index) = (yystack_[0].value.node_index); }
#line 999 "SONParser.cpp"
    break;

  case 45: // exp: component
#line 298 "SONParser.bison"
      { (yylhs.value.node_index) = (yystack_[0].value.node_index); }
#line 1005 "SONParser.cpp"
    break;

  case 46: // exp: exp multiply_divide exp
#line 300 "SONParser.bison"
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
#line 1023 "SONParser.cpp"
    break;

  case 47: // exp: exp plus exp
#line 314 "SONParser.bison"
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
#line 1041 "SONParser.cpp"
    break;

  case 48: // exp: exp minus exp
#line 328 "SONParser.bison"
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
#line 1059 "SONParser.cpp"
    break;

  case 49: // exp: exp exponent exp
#line 342 "SONParser.bison"
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
#line 1077 "SONParser.cpp"
    break;

  case 50: // exp: exp boolean_numeric_op exp
#line 356 "SONParser.bison"
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
#line 1095 "SONParser.cpp"
    break;

  case 51: // exp: exp boolean_logic_op exp
#line 371 "SONParser.bison"
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
#line 1113 "SONParser.cpp"
    break;

  case 52: // exp: lparen exp rparen
#line 385 "SONParser.bison"
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
#line 1131 "SONParser.cpp"
    break;

  case 53: // exp: minus exp
#line 399 "SONParser.bison"
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
#line 1147 "SONParser.cpp"
    break;

  case 54: // exp: unary_not exp
#line 411 "SONParser.bison"
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
#line 1163 "SONParser.cpp"
    break;

  case 55: // execution_unit_end: "end of unit of execution"
#line 424 "SONParser.bison"
{
    auto token_index = ((yystack_[0].value.token_index));
    (yylhs.value.node_index) = interpreter.push_leaf(wasp::EXECUTION_UNIT_END,"uoe_end",token_index);
}
#line 1172 "SONParser.cpp"
    break;

  case 56: // execution_unit_start: "start of unit of execution"
#line 429 "SONParser.bison"
{
    auto token_index = ((yystack_[0].value.token_index));
    (yylhs.value.node_index) = interpreter.push_leaf(wasp::EXECUTION_UNIT_START,"uoe_start",token_index);
}
#line 1181 "SONParser.cpp"
    break;

  case 57: // identifier: exp
#line 435 "SONParser.bison"
    {
        interpreter.set_type((yystack_[0].value.node_index), wasp::IDENTIFIER);
        interpreter.set_name((yystack_[0].value.node_index), "id");
        (yylhs.value.node_index) = (yystack_[0].value.node_index);
    }
#line 1191 "SONParser.cpp"
    break;

  case 58: // decl: PRIMITIVE
#line 441 "SONParser.bison"
    {
        auto token_index = ((yystack_[0].value.token_index));
        std::string quote_less_data = interpreter.token_data(token_index);
        quote_less_data = wasp::strip_quotes(quote_less_data);
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::DECL
                                   ,"decl"
                                   ,token_index);
    }
#line 1204 "SONParser.cpp"
    break;

  case 59: // ASSIGNMENT: "="
#line 449 "SONParser.bison"
             { (yylhs.value.token_index) = (yystack_[0].value.token_index); }
#line 1210 "SONParser.cpp"
    break;

  case 60: // ASSIGNMENT: ":"
#line 449 "SONParser.bison"
                      { (yylhs.value.token_index) = (yystack_[0].value.token_index); }
#line 1216 "SONParser.cpp"
    break;

  case 61: // assignment: ASSIGNMENT
#line 450 "SONParser.bison"
                        {
             auto token_index = ((yystack_[0].value.token_index));
             (yylhs.value.node_index) = interpreter.push_leaf(wasp::ASSIGN,"=",token_index);
            }
#line 1225 "SONParser.cpp"
    break;

  case 62: // key_declaration: tag assignment
#line 455 "SONParser.bison"
        {
             (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
             (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));

        }
#line 1235 "SONParser.cpp"
    break;

  case 63: // declaration: key_declaration
#line 460 "SONParser.bison"
              { (yylhs.value.node_indices) = (yystack_[0].value.node_indices); }
#line 1241 "SONParser.cpp"
    break;

  case 64: // declaration: tag
#line 460 "SONParser.bison"
                                { (yylhs.value.node_indices) = (yystack_[0].value.node_indices); }
#line 1247 "SONParser.cpp"
    break;

  case 65: // tag: decl
#line 462 "SONParser.bison"
        {
             (yylhs.value.node_indices) = new std::vector<size_t>();
             (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1256 "SONParser.cpp"
    break;

  case 66: // tag: decl lparen identifier rparen
#line 467 "SONParser.bison"
        {
            (yylhs.value.node_indices) = new std::vector<size_t>();
            (yylhs.value.node_indices)->push_back((yystack_[3].value.node_index));
            (yylhs.value.node_indices)->push_back((yystack_[2].value.node_index));
            (yylhs.value.node_indices)->push_back((yystack_[1].value.node_index));
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1268 "SONParser.cpp"
    break;

  case 67: // array: declaration lbracket rbracket
#line 476 "SONParser.bison"
    {
        (yystack_[2].value.node_indices)->push_back((yystack_[1].value.node_index));
        (yystack_[2].value.node_indices)->push_back((yystack_[0].value.node_index));
        (yylhs.value.node_index) = interpreter.push_parent(wasp::ARRAY
                ,wasp::strip_quotes(interpreter.data((yystack_[2].value.node_indices)->front())).c_str()
                ,*(yystack_[2].value.node_indices));
        delete (yystack_[2].value.node_indices);
    }
#line 1281 "SONParser.cpp"
    break;

  case 68: // array: declaration lbracket "end of file"
#line 485 "SONParser.bison"
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
#line 1296 "SONParser.cpp"
    break;

  case 69: // array: declaration lbracket array_members "end of file"
#line 496 "SONParser.bison"
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
#line 1312 "SONParser.cpp"
    break;

  case 70: // array: declaration lbracket execution_unit_end
#line 508 "SONParser.bison"
    {
        // TODO capture partial definition
        std::string name = interpreter.name((yystack_[2].value.node_indices)->front());
        error(yystack_[1].location, name+" has unmatched left bracket!");
        delete (yystack_[2].value.node_indices);
        YYERROR;
    }
#line 1324 "SONParser.cpp"
    break;

  case 71: // array: declaration lbracket array_members execution_unit_end
#line 516 "SONParser.bison"
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
#line 1341 "SONParser.cpp"
    break;

  case 72: // array: declaration lbracket array_members rbracket
#line 529 "SONParser.bison"
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
#line 1360 "SONParser.cpp"
    break;

  case 73: // object: declaration lbrace rbrace
#line 544 "SONParser.bison"
    {
        (yystack_[2].value.node_indices)->push_back((yystack_[1].value.node_index));
        (yystack_[2].value.node_indices)->push_back((yystack_[0].value.node_index));
        (yylhs.value.node_index) = interpreter.push_parent(wasp::OBJECT
            ,wasp::strip_quotes(interpreter.data((yystack_[2].value.node_indices)->front())).c_str()
            ,*(yystack_[2].value.node_indices));
        delete (yystack_[2].value.node_indices);
    }
#line 1373 "SONParser.cpp"
    break;

  case 74: // object: declaration lbrace "end of file"
#line 553 "SONParser.bison"
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
#line 1388 "SONParser.cpp"
    break;

  case 75: // object: declaration lbrace members "end of file"
#line 564 "SONParser.bison"
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
#line 1404 "SONParser.cpp"
    break;

  case 76: // object: declaration lbrace execution_unit_end
#line 576 "SONParser.bison"
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
#line 1419 "SONParser.cpp"
    break;

  case 77: // object: declaration lbrace members execution_unit_end
#line 587 "SONParser.bison"
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
#line 1436 "SONParser.cpp"
    break;

  case 78: // object: declaration lbrace members rbrace
#line 600 "SONParser.bison"
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
#line 1454 "SONParser.cpp"
    break;

  case 79: // keyedvalue: key_declaration exp
#line 616 "SONParser.bison"
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
#line 1474 "SONParser.cpp"
    break;

  case 80: // members: filler
#line 634 "SONParser.bison"
        {
            (yylhs.value.node_indices) = new std::vector<size_t>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1483 "SONParser.cpp"
    break;

  case 81: // members: members filler
#line 639 "SONParser.bison"
        {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1492 "SONParser.cpp"
    break;

  case 82: // members: object
#line 644 "SONParser.bison"
        {
            (yylhs.value.node_indices) = new std::vector<size_t>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1501 "SONParser.cpp"
    break;

  case 83: // members: members object
#line 649 "SONParser.bison"
        {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1510 "SONParser.cpp"
    break;

  case 84: // members: array
#line 654 "SONParser.bison"
        {
            (yylhs.value.node_indices) = new std::vector<size_t>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1519 "SONParser.cpp"
    break;

  case 85: // members: members array
#line 659 "SONParser.bison"
        {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1528 "SONParser.cpp"
    break;

  case 86: // members: keyedvalue
#line 664 "SONParser.bison"
        {
            (yylhs.value.node_indices) = new std::vector<size_t>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1537 "SONParser.cpp"
    break;

  case 87: // members: members keyedvalue
#line 669 "SONParser.bison"
        {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1546 "SONParser.cpp"
    break;

  case 88: // members: comment
#line 674 "SONParser.bison"
        {
            (yylhs.value.node_indices) = new std::vector<size_t>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1555 "SONParser.cpp"
    break;

  case 89: // members: members comment
#line 679 "SONParser.bison"
        {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1564 "SONParser.cpp"
    break;

  case 90: // members: members comma
#line 684 "SONParser.bison"
        {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1573 "SONParser.cpp"
    break;

  case 91: // array_members: exp
#line 691 "SONParser.bison"
        {
            (yylhs.value.node_indices) = new std::vector<size_t>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1582 "SONParser.cpp"
    break;

  case 92: // array_members: array_members exp
#line 696 "SONParser.bison"
        {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1591 "SONParser.cpp"
    break;

  case 93: // array_members: filler
#line 702 "SONParser.bison"
        {
            (yylhs.value.node_indices) = new std::vector<size_t>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1600 "SONParser.cpp"
    break;

  case 94: // array_members: array_members filler
#line 707 "SONParser.bison"
        {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1609 "SONParser.cpp"
    break;

  case 95: // array_members: object
#line 712 "SONParser.bison"
        {
            (yylhs.value.node_indices) = new std::vector<size_t>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1618 "SONParser.cpp"
    break;

  case 96: // array_members: array_members object
#line 717 "SONParser.bison"
        {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1627 "SONParser.cpp"
    break;

  case 97: // array_members: array
#line 722 "SONParser.bison"
        {
            (yylhs.value.node_indices) = new std::vector<size_t>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1636 "SONParser.cpp"
    break;

  case 98: // array_members: array_members array
#line 727 "SONParser.bison"
        {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1645 "SONParser.cpp"
    break;

  case 99: // array_members: keyedvalue
#line 732 "SONParser.bison"
        {
            (yylhs.value.node_indices) = new std::vector<size_t>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1654 "SONParser.cpp"
    break;

  case 100: // array_members: array_members keyedvalue
#line 737 "SONParser.bison"
        {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1663 "SONParser.cpp"
    break;

  case 101: // array_members: comment
#line 742 "SONParser.bison"
        {
            (yylhs.value.node_indices) = new std::vector<size_t>();
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1672 "SONParser.cpp"
    break;

  case 102: // array_members: array_members comment
#line 747 "SONParser.bison"
        {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1681 "SONParser.cpp"
    break;

  case 103: // array_members: array_members comma
#line 752 "SONParser.bison"
        {
            (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
            (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
        }
#line 1690 "SONParser.cpp"
    break;

  case 104: // comment: "comment"
#line 758 "SONParser.bison"
        {
            auto token_index = ((yystack_[0].value.token_index));
            (yylhs.value.node_index) = interpreter.push_leaf(wasp::COMMENT,"comment",token_index);
        }
#line 1699 "SONParser.cpp"
    break;

  case 105: // execution_unit_name: ANY_STRING
#line 763 "SONParser.bison"
        {
            auto token_index = ((yystack_[0].value.token_index));
            (yylhs.value.node_index) = interpreter.push_leaf(wasp::DECL,"name",token_index);
        }
#line 1708 "SONParser.cpp"
    break;

  case 106: // execution_unit: execution_unit_start execution_unit_name execution_unit_end
#line 768 "SONParser.bison"
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
#line 1726 "SONParser.cpp"
    break;

  case 107: // execution_unit: execution_unit_start execution_unit_name members execution_unit_end
#line 782 "SONParser.bison"
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
#line 1748 "SONParser.cpp"
    break;

  case 108: // block: lbracket decl rbracket
#line 802 "SONParser.bison"
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
#line 1780 "SONParser.cpp"
    break;

  case 110: // start: start comment
#line 830 "SONParser.bison"
                       {interpreter.push_staged_child(((yystack_[0].value.node_index))); if(interpreter.single_parse() ) {lexer->rewind();YYACCEPT;}}
#line 1786 "SONParser.cpp"
    break;

  case 111: // start: start array
#line 831 "SONParser.bison"
                     {interpreter.push_staged_child(((yystack_[0].value.node_index))); if(interpreter.single_parse() ) {lexer->rewind();YYACCEPT;}}
#line 1792 "SONParser.cpp"
    break;

  case 112: // start: start keyedvalue
#line 832 "SONParser.bison"
                          {interpreter.push_staged_child(((yystack_[0].value.node_index))); if(interpreter.single_parse() ) {lexer->rewind();YYACCEPT;}}
#line 1798 "SONParser.cpp"
    break;

  case 113: // start: start object
#line 833 "SONParser.bison"
                      {interpreter.push_staged_child(((yystack_[0].value.node_index))); if(interpreter.single_parse() ) {lexer->rewind();YYACCEPT;}}
#line 1804 "SONParser.cpp"
    break;

  case 114: // start: start execution_unit
#line 834 "SONParser.bison"
                              {interpreter.push_staged_child(((yystack_[0].value.node_index)));if(interpreter.single_parse() ) {YYACCEPT;}}
#line 1810 "SONParser.cpp"
    break;

  case 115: // start: start block
#line 835 "SONParser.bison"
                     { /*Node staging occurs in block rule*/;if(interpreter.single_parse() ) {YYACCEPT;}}
#line 1816 "SONParser.cpp"
    break;


#line 1820 "SONParser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
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
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
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
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
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
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  SONParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

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
        std::string yyr;
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
              else
                goto append;

            append:
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

  std::string
  SONParser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // SONParser::context.
  SONParser::context::context (const SONParser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  SONParser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        int yychecklim = yylast_ - yyn + 1;
        int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }



  int
  SONParser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
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
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  SONParser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char SONParser::yypact_ninf_ = -56;

  const signed char SONParser::yytable_ninf_ = -59;

  const short
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

  const signed char
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
       0,    53,   111,    77,    78,    79,    80,    35,    82,    12,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      36,    37,   118,    43,    95,    13,    50,    29,    38,    39,
      40,    41,    54,    15,    61,    16,    47,    48,    17,    18,
      19,    55,    56,    57,    58,   107,    59,    30,    24,    25,
       1
  };

  const short
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

  const short
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

  const signed char
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

  const signed char
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

  const signed char
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


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const SONParser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\"end of line\"",
  "\"-\"", "\"(\"", "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\"=\"",
  "\",\"", "\":\"", "\">=\"", "\"<\"", "\">\"", "\"<=\"", "\"!=\"",
  "\"==\"", "\"&&\"", "\"||\"", "\"!\"", "\"filler\"", "\"*\"", "\"/\"",
  "\"+\"", "\"^\"", "\"&\"", "\"integer\"", "\"true\"", "\"false\"",
  "\"double\"", "\"string\"", "\"quoted string\"", "\"comment\"",
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
#endif


#if YYDEBUG
  const short
  SONParser::yyrline_[] =
  {
       0,   150,   150,   155,   165,   170,   175,   175,   176,   181,
     187,   192,   192,   194,   194,   194,   194,   194,   194,   196,
     201,   206,   211,   216,   221,   226,   226,   227,   232,   238,
     244,   249,   254,   259,   264,   269,   275,   275,   276,   276,
     276,   276,   276,   278,   296,   298,   299,   313,   327,   341,
     355,   370,   384,   398,   410,   423,   428,   434,   440,   449,
     449,   450,   454,   460,   460,   461,   466,   475,   484,   495,
     507,   515,   528,   543,   552,   563,   575,   586,   599,   615,
     633,   638,   643,   648,   653,   658,   663,   668,   673,   678,
     683,   690,   695,   701,   706,   711,   716,   721,   726,   731,
     736,   741,   746,   751,   757,   762,   767,   781,   801,   829,
     830,   831,   832,   833,   834,   835
  };

  void
  SONParser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  SONParser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  SONParser::symbol_kind_type
  SONParser::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
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
    // Last valid token kind.
    const int code_max = 297;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return YY_CAST (symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 32 "SONParser.bison"
} // wasp
#line 2486 "SONParser.cpp"

#line 839 "SONParser.bison"
 /*** Additional Code ***/

void wasp::SONParser::error(const SONParser::location_type& l,
                           const std::string& m)
{
    interpreter.error_stream()<<l<<": "<<m<<std::endl;
}
