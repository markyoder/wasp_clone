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
#line 1 "VIIParser.bison"
 /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>


#line 49 "VIIParser.cpp"


#include "VIIParser.hpp"

// Second part of user prologue.
#line 93 "VIIParser.bison"


#include "VIInterpreter.h"
#include "VIINodeView.h"
#include "VIILexer.h"

#include "waspcore/wasp_bug.h"

/* this "connects" the bison parser in the interpreter to the flex VIILexer class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the interpreter context. */
#undef yylex
#define yylex lexer->lex


#line 71 "VIIParser.cpp"



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

#line 33 "VIIParser.bison"
namespace wasp {
#line 165 "VIIParser.cpp"

  /// Build a parser object.
  VIIParser::VIIParser (class AbstractInterpreter& interpreter_yyarg, std::istream &input_stream_yyarg, std::shared_ptr<class VIILexerImpl> lexer_yyarg)
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

  VIIParser::~VIIParser ()
  {}

  VIIParser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/

  // basic_symbol.
  template <typename Base>
  VIIParser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
    , location (that.location)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  VIIParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_MOVE_REF (location_type) l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  VIIParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (semantic_type) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  VIIParser::symbol_kind_type
  VIIParser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

  template <typename Base>
  bool
  VIIParser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  VIIParser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
    location = YY_MOVE (s.location);
  }

  // by_kind.
  VIIParser::by_kind::by_kind ()
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  VIIParser::by_kind::by_kind (by_kind&& that)
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  VIIParser::by_kind::by_kind (const by_kind& that)
    : kind_ (that.kind_)
  {}

  VIIParser::by_kind::by_kind (token_kind_type t)
    : kind_ (yytranslate_ (t))
  {}

  void
  VIIParser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  VIIParser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  VIIParser::symbol_kind_type
  VIIParser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }

  VIIParser::symbol_kind_type
  VIIParser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  // by_state.
  VIIParser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  VIIParser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  VIIParser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  VIIParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  VIIParser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  VIIParser::symbol_kind_type
  VIIParser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  VIIParser::stack_symbol_type::stack_symbol_type ()
  {}

  VIIParser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value), YY_MOVE (that.location))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  VIIParser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value), YY_MOVE (that.location))
  {
    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  VIIParser::stack_symbol_type&
  VIIParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }

  VIIParser::stack_symbol_type&
  VIIParser::stack_symbol_type::operator= (stack_symbol_type& that)
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
  VIIParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YY_USE (yysym.kind ());
  }

#if YYDEBUG
  template <typename Base>
  void
  VIIParser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
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
  VIIParser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  VIIParser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  VIIParser::yypop_ (int n)
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

  VIIParser::state_type
  VIIParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  VIIParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  VIIParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  VIIParser::operator() ()
  {
    return parse ();
  }

  int
  VIIParser::parse ()
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
#line 41 "VIIParser.bison"
{
    // initialize the initial location object
    yyla.location.begin.filename = yyla.location.end.filename = &interpreter.stream_name();
    yyla.location.begin.line = yyla.location.end.line = interpreter.start_line();
    yyla.location.begin.column = yyla.location.end.column = interpreter.start_column();
    lexer = std::make_shared<VIILexerImpl>(interpreter,&input_stream);
}

#line 509 "VIIParser.cpp"


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
  case 2: // include: "file include"
#line 113 "VIIParser.bison"
        {
            auto token_index = (yystack_[0].value.token_index);
            (yylhs.value.node_index) = interpreter.push_leaf(wasp::FILE,"decl",token_index);
        }
#line 650 "VIIParser.cpp"
    break;

  case 3: // comma: ","
#line 118 "VIIParser.bison"
        {
            auto token_index = (yystack_[0].value.token_index);
            (yylhs.value.node_index) = interpreter.push_leaf(wasp::WASP_COMMA,",",token_index);
        }
#line 659 "VIIParser.cpp"
    break;

  case 4: // semicolon: ";"
#line 123 "VIIParser.bison"
        {
            auto token_index = (yystack_[0].value.token_index);
            (yylhs.value.node_index) = interpreter.push_leaf(wasp::TERM,";",token_index);
        }
#line 668 "VIIParser.cpp"
    break;

  case 5: // assign: "="
#line 128 "VIIParser.bison"
        {
            auto token_index = (yystack_[0].value.token_index);
            (yylhs.value.node_index) = interpreter.push_leaf(wasp::ASSIGN,"=",token_index);
        }
#line 677 "VIIParser.cpp"
    break;

  case 6: // fslash: "forward slash"
#line 134 "VIIParser.bison"
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::DIVIDE,"/",token_index);
    }
#line 686 "VIIParser.cpp"
    break;

  case 7: // rbracket: "right bracket"
#line 139 "VIIParser.bison"
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::RBRACKET,"]",token_index);
    }
#line 695 "VIIParser.cpp"
    break;

  case 8: // lbracket: "left bracket"
#line 144 "VIIParser.bison"
    {
        auto token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::LBRACKET,"[",token_index);
    }
#line 704 "VIIParser.cpp"
    break;

  case 9: // PRIMITIVE: "quoted string"
#line 149 "VIIParser.bison"
            { (yylhs.value.token_index) = (yystack_[0].value.token_index); }
#line 710 "VIIParser.cpp"
    break;

  case 10: // PRIMITIVE: "integer"
#line 149 "VIIParser.bison"
                      { (yylhs.value.token_index) = (yystack_[0].value.token_index); }
#line 716 "VIIParser.cpp"
    break;

  case 11: // PRIMITIVE: "double"
#line 149 "VIIParser.bison"
                                { (yylhs.value.token_index) = (yystack_[0].value.token_index); }
#line 722 "VIIParser.cpp"
    break;

  case 12: // PRIMITIVE: "-"
#line 149 "VIIParser.bison"
                                         { (yylhs.value.token_index) = (yystack_[0].value.token_index); }
#line 728 "VIIParser.cpp"
    break;

  case 13: // value: PRIMITIVE
#line 152 "VIIParser.bison"
{
    size_t token_index = ((yystack_[0].value.token_index));
    (yylhs.value.node_index) = interpreter.push_leaf(wasp::VALUE,"value"
                     ,token_index);
}
#line 738 "VIIParser.cpp"
    break;

  case 14: // key_value: value
#line 157 "VIIParser.bison"
            { (yylhs.value.node_index) = (yystack_[0].value.node_index); }
#line 744 "VIIParser.cpp"
    break;

  case 15: // key_value: "string"
#line 159 "VIIParser.bison"
{
    size_t token_index = ((yystack_[0].value.token_index));
    (yylhs.value.node_index) = interpreter.push_leaf(wasp::VALUE,"value"
                     ,token_index);
}
#line 754 "VIIParser.cpp"
    break;

  case 16: // path: "string"
#line 166 "VIIParser.bison"
        {
            size_t token_index = ((yystack_[0].value.token_index));
            (yylhs.value.node_index) = interpreter.push_leaf(wasp::VALUE,"path"
                             ,token_index);
        }
#line 764 "VIIParser.cpp"
    break;

  case 17: // path: "quoted string"
#line 172 "VIIParser.bison"
        {
            size_t token_index = ((yystack_[0].value.token_index));
            (yylhs.value.node_index) = interpreter.push_leaf(wasp::VALUE,"path"
                             ,token_index);
        }
#line 774 "VIIParser.cpp"
    break;

  case 18: // include_file: include path
#line 179 "VIIParser.bison"
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
#line 790 "VIIParser.cpp"
    break;

  case 19: // decl: "string"
#line 193 "VIIParser.bison"
    {
        auto token_index = ((yystack_[0].value.token_index));
        std::string quote_less_data = interpreter.token_data(token_index);
        quote_less_data = wasp::strip_quotes(quote_less_data);
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::DECL
                                   ,"decl"
                                   ,token_index);
    }
#line 803 "VIIParser.cpp"
    break;

  case 20: // decl_or_key_value: decl assign key_value
#line 202 "VIIParser.bison"
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
#line 822 "VIIParser.cpp"
    break;

  case 21: // decl_or_key_value: decl
#line 215 "VIIParser.bison"
            { (yylhs.value.node_index) = (yystack_[0].value.node_index); }
#line 828 "VIIParser.cpp"
    break;

  case 22: // part: value
#line 216 "VIIParser.bison"
       { (yylhs.value.node_index) = (yystack_[0].value.node_index); }
#line 834 "VIIParser.cpp"
    break;

  case 23: // part: fslash
#line 216 "VIIParser.bison"
               { (yylhs.value.node_index) = (yystack_[0].value.node_index); }
#line 840 "VIIParser.cpp"
    break;

  case 24: // part: comment
#line 216 "VIIParser.bison"
                        { (yylhs.value.node_index) = (yystack_[0].value.node_index); }
#line 846 "VIIParser.cpp"
    break;

  case 25: // part: decl_or_key_value
#line 217 "VIIParser.bison"
          { (yylhs.value.node_index) = (yystack_[0].value.node_index); }
#line 852 "VIIParser.cpp"
    break;

  case 26: // part: comma
#line 217 "VIIParser.bison"
                              { (yylhs.value.node_index) = (yystack_[0].value.node_index); }
#line 858 "VIIParser.cpp"
    break;

  case 27: // part: semicolon
#line 217 "VIIParser.bison"
                                      { (yylhs.value.node_index) = (yystack_[0].value.node_index); }
#line 864 "VIIParser.cpp"
    break;

  case 28: // command_part: part
#line 219 "VIIParser.bison"
                    {

        auto token_type = interpreter.node_token_type((yystack_[0].value.node_index));
        auto node_type = interpreter.type((yystack_[0].value.node_index));
        auto staged_type = interpreter.staged_type(interpreter.staged_count()-1);

        bool is_key_value = node_type == wasp::KEYED_VALUE;
        // If this is a potential start of a new command        
        wasp_check(interpreter.definition());
        auto staged_index = interpreter.staged_count()-1;
        const auto& child_indices = interpreter.staged_child_indices(staged_index);

        // Accumulate non-decorative staged child count
        // This cannot be done with the node view because the node is staged and
        // has not been committed to the tree, yet.
        size_t staged_child_count = interpreter.staged_non_decorative_child_count(staged_index);
        
        auto prev_part_line = yystack_[0].location.end.line;  // initialize to current line
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
                && yystack_[0].location.end.line !=  prev_part_line
                && staged_type  != wasp::OBJECT
                && interpreter.staged_count() > 1)
        {
            // this comment belongs to parent scope
            // terminate the current staged data
            interpreter.commit_staged(staged_index);

            // Stage
            (yylhs.value.stage_index) = interpreter.push_staged_child((yystack_[0].value.node_index));
        }
        else if ( wasp::COMMENT == token_type
                || wasp::WASP_COMMA == token_type
                || wasp::TERM == token_type)
        {
            (yylhs.value.stage_index) = interpreter.push_staged_child((yystack_[0].value.node_index));
            // terminator ';' commits the current stage
            if ( wasp::TERM == token_type && staged_child_count > 0
                 && interpreter.staged_count() > 1)
            {
                interpreter.commit_staged(staged_index);
            }
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
        else if ( is_key_value ||
                  token_type == wasp::STRING ||
                  token_type == wasp::QUOTED_STRING)
        {
            std::string data = is_key_value ? interpreter.name((yystack_[0].value.node_index))
                                            : interpreter.data((yystack_[0].value.node_index));
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

                if ( is_key_value )
                {
                    (yylhs.value.stage_index) = interpreter.push_staged_child((yystack_[0].value.node_index));
                }
                else
                {
                    std::vector<size_t> child_indices = {(yystack_[0].value.node_index)};
                    (yylhs.value.stage_index) = interpreter.push_staged(wasp::ARRAY // commands are
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
#line 1041 "VIIParser.cpp"
    break;

  case 29: // command_part: include_file
#line 392 "VIIParser.bison"
    {
        // assume the included content will be a child of the existing
        // staged content.
        (yylhs.value.stage_index) = interpreter.push_staged_child((yystack_[0].value.node_index));
    }
#line 1051 "VIIParser.cpp"
    break;

  case 30: // comment: "comment"
#line 399 "VIIParser.bison"
        {
            auto token_index = ((yystack_[0].value.token_index));
            (yylhs.value.node_index) = interpreter.push_leaf(wasp::COMMENT,"comment",token_index);
        }
#line 1060 "VIIParser.cpp"
    break;

  case 31: // block: lbracket decl rbracket
#line 404 "VIIParser.bison"
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
#line 1088 "VIIParser.cpp"
    break;

  case 33: // start: start block
#line 429 "VIIParser.bison"
                    {
           if(interpreter.single_parse() )
           {
               lexer->rewind();
               YYACCEPT;
           }
       }
#line 1100 "VIIParser.cpp"
    break;

  case 34: // start: start command_part
#line 436 "VIIParser.bison"
                            {
            if(interpreter.single_parse() )
            {
                lexer->rewind();
                YYACCEPT;
            }
        }
#line 1112 "VIIParser.cpp"
    break;


#line 1116 "VIIParser.cpp"

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
  VIIParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

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
  VIIParser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // VIIParser::context.
  VIIParser::context::context (const VIIParser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  VIIParser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
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
  VIIParser::yy_syntax_error_arguments_ (const context& yyctx,
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
  VIIParser::yysyntax_error_ (const context& yyctx) const
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


  const signed char VIIParser::yypact_ninf_ = -12;

  const signed char VIIParser::yytable_ninf_ = -1;

  const signed char
  VIIParser::yypact_[] =
  {
     -12,     0,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,
     -12,   -12,   -12,   -12,    -9,   -12,   -12,   -12,    -7,   -12,
     -12,   -12,    16,   -12,   -12,   -12,   -12,   -12,   -12,   -12,
     -12,    -8,   -12,     9,   -12,   -12,   -12,   -12,   -12
  };

  const signed char
  VIIParser::yydefact_[] =
  {
      32,     0,     1,    12,     3,     4,    10,    11,    19,     9,
      30,     8,     6,     2,     0,    26,    27,    23,     0,    13,
      22,    29,    21,    25,    28,    34,    24,    33,    16,    17,
      18,     0,     5,     0,     7,    31,    15,    14,    20
  };

  const signed char
  VIIParser::yypgoto_[] =
  {
     -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -11,
     -12,   -12,   -12,     5,   -12,   -12,   -12,   -12,   -12,   -12
  };

  const signed char
  VIIParser::yydefgoto_[] =
  {
       0,    14,    15,    16,    33,    17,    35,    18,    19,    20,
      38,    30,    21,    22,    23,    24,    25,    26,    27,     1
  };

  const signed char
  VIIParser::yytable_[] =
  {
       2,    28,    29,     8,     3,    34,     4,     5,     6,     7,
       8,     9,    10,     3,    11,    12,    13,     6,     7,    36,
       9,    32,    37,    31
  };

  const signed char
  VIIParser::yycheck_[] =
  {
       0,    10,    11,    10,     4,    13,     6,     7,     8,     9,
      10,    11,    12,     4,    14,    15,    16,     8,     9,    10,
      11,     5,    33,    18
  };

  const signed char
  VIIParser::yystos_[] =
  {
       0,    36,     0,     4,     6,     7,     8,     9,    10,    11,
      12,    14,    15,    16,    18,    19,    20,    22,    24,    25,
      26,    29,    30,    31,    32,    33,    34,    35,    10,    11,
      28,    30,     5,    21,    13,    23,    10,    26,    27
  };

  const signed char
  VIIParser::yyr1_[] =
  {
       0,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      25,    25,    25,    26,    27,    27,    28,    28,    29,    30,
      31,    31,    32,    32,    32,    32,    32,    32,    33,    33,
      34,    35,    36,    36,    36
  };

  const signed char
  VIIParser::yyr2_[] =
  {
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     2,     2
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const VIIParser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\"end of line\"",
  "\"-\"", "\"=\"", "\",\"", "\";\"", "\"integer\"", "\"double\"",
  "\"string\"", "\"quoted string\"", "\"comment\"", "\"right bracket\"",
  "\"left bracket\"", "\"forward slash\"", "\"file include\"", "$accept",
  "include", "comma", "semicolon", "assign", "fslash", "rbracket",
  "lbracket", "PRIMITIVE", "value", "key_value", "path", "include_file",
  "decl", "decl_or_key_value", "part", "command_part", "comment", "block",
  "start", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  VIIParser::yyrline_[] =
  {
       0,   112,   112,   117,   122,   127,   133,   138,   143,   149,
     149,   149,   149,   151,   157,   158,   165,   171,   178,   192,
     201,   215,   216,   216,   216,   217,   217,   217,   219,   391,
     398,   403,   428,   429,   436
  };

  void
  VIIParser::yy_stack_print_ () const
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
  VIIParser::yy_reduce_print_ (int yyrule) const
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

  VIIParser::symbol_kind_type
  VIIParser::yytranslate_ (int t)
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
      15,    16
    };
    // Last valid token kind.
    const int code_max = 271;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return YY_CAST (symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 33 "VIIParser.bison"
} // wasp
#line 1651 "VIIParser.cpp"

#line 448 "VIIParser.bison"
 /*** Additional Code ***/

void wasp::VIIParser::error(const VIIParser::location_type& l,
                           const std::string& m)
{
    interpreter.error_stream()<<l<<": "<<m<<std::endl;
}
