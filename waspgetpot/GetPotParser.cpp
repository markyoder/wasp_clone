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
#line 1 "GetPot.bison" // lalr1.cc:404
 /*** C/C++ Declarations ***/

#include <stdio.h>
#include <vector>


#line 45 "GetPotParser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "GetPotParser.hpp"

// User implementation prologue.
#line 123 "GetPot.bison" // lalr1.cc:412


#include "GetPotInterpreter.h"
#include "GetPotLexer.h"

/* this "connects" the GetPot parser in the interpreter to the flex GetPotLexer class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the interpreter context. */
#undef yylex
#define yylex interpreter.m_lexer->lex


#line 71 "GetPotParser.cpp" // lalr1.cc:412


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
#line 157 "GetPotParser.cpp" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  GetPotParser::yytnamerr_ (const char *yystr)
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
  GetPotParser::GetPotParser (class GetPotInterpreter& interpreter_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      interpreter (interpreter_yyarg)
  {}

  GetPotParser::~GetPotParser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  GetPotParser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  GetPotParser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  GetPotParser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
    value = other.value;
  }


  template <typename Base>
  inline
  GetPotParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  GetPotParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  inline
  GetPotParser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  GetPotParser::basic_symbol<Base>::clear ()
  {
    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  GetPotParser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  GetPotParser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
    location = s.location;
  }

  // by_type.
  inline
  GetPotParser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  GetPotParser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  GetPotParser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  GetPotParser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  GetPotParser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  GetPotParser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  GetPotParser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  GetPotParser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  GetPotParser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  GetPotParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  GetPotParser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  GetPotParser::symbol_number_type
  GetPotParser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  GetPotParser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  GetPotParser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    value = that.value;
    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  GetPotParser::stack_symbol_type&
  GetPotParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  GetPotParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YYUSE (yysym.type_get ());
  }

#if YYDEBUG
  template <typename Base>
  void
  GetPotParser::yy_print_ (std::ostream& yyo,
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
  GetPotParser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  GetPotParser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  GetPotParser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  GetPotParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  GetPotParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  GetPotParser::debug_level_type
  GetPotParser::debug_level () const
  {
    return yydebug_;
  }

  void
  GetPotParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline GetPotParser::state_type
  GetPotParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  GetPotParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  GetPotParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  GetPotParser::parse ()
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
    #line 40 "GetPot.bison" // lalr1.cc:741
{
    // initialize the initial location object
    yyla.location.begin.filename = yyla.location.end.filename = &interpreter.m_stream_name;
    yyla.location.begin.line = yyla.location.end.line = interpreter.m_start_line;
    yyla.location.begin.column = yyla.location.end.column = interpreter.m_start_column;
}

#line 538 "GetPotParser.cpp" // lalr1.cc:741

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
#line 140 "GetPot.bison" // lalr1.cc:859
    {unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));(yylhs.value.node_index) = interpreter.push_leaf(wasp::BANG      ,"!",token_index);}
#line 648 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 141 "GetPot.bison" // lalr1.cc:859
    {unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));(yylhs.value.node_index) = interpreter.push_leaf(wasp::GT      ,">",token_index);}
#line 654 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 142 "GetPot.bison" // lalr1.cc:859
    {unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));(yylhs.value.node_index) = interpreter.push_leaf(wasp::LT      ,"<",token_index);}
#line 660 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 143 "GetPot.bison" // lalr1.cc:859
    {unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));(yylhs.value.node_index) = interpreter.push_leaf(wasp::GTE      ,">=",token_index);}
#line 666 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 144 "GetPot.bison" // lalr1.cc:859
    {unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));(yylhs.value.node_index) = interpreter.push_leaf(wasp::LTE      ,"<=",token_index);}
#line 672 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 145 "GetPot.bison" // lalr1.cc:859
    {unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));(yylhs.value.node_index) = interpreter.push_leaf(wasp::NEQ      ,"!=",token_index);}
#line 678 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 146 "GetPot.bison" // lalr1.cc:859
    {unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));(yylhs.value.node_index) = interpreter.push_leaf(wasp::EQ       ,"==",token_index);}
#line 684 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 147 "GetPot.bison" // lalr1.cc:859
    {unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));(yylhs.value.node_index) = interpreter.push_leaf(wasp::AND      ,"&&",token_index);}
#line 690 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 148 "GetPot.bison" // lalr1.cc:859
    {unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));(yylhs.value.node_index) = interpreter.push_leaf(wasp::OR       ,"||",token_index);}
#line 696 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 149 "GetPot.bison" // lalr1.cc:859
    {unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));(yylhs.value.node_index) = interpreter.push_leaf(wasp::MULTIPLY , "*",token_index);}
#line 702 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 150 "GetPot.bison" // lalr1.cc:859
    {unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));(yylhs.value.node_index) = interpreter.push_leaf(wasp::DIVIDE   ,"/" ,token_index);}
#line 708 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 151 "GetPot.bison" // lalr1.cc:859
    {unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));(yylhs.value.node_index) = interpreter.push_leaf(wasp::PLUS     ,"+" ,token_index);}
#line 714 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 152 "GetPot.bison" // lalr1.cc:859
    {unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));(yylhs.value.node_index) = interpreter.push_leaf(wasp::MINUS    ,"-" ,token_index);}
#line 720 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 153 "GetPot.bison" // lalr1.cc:859
    {unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));(yylhs.value.node_index) = interpreter.push_leaf(wasp::EXPONENT ,"^" ,token_index);}
#line 726 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 154 "GetPot.bison" // lalr1.cc:859
    {unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));(yylhs.value.node_index) = interpreter.push_leaf(wasp::LPAREN   ,"(" ,token_index);}
#line 732 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 155 "GetPot.bison" // lalr1.cc:859
    {unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));(yylhs.value.node_index) = interpreter.push_leaf(wasp::RPAREN   ,")" ,token_index);}
#line 738 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 164 "GetPot.bison" // lalr1.cc:859
    {
        unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::VALUE,"name"
                         ,token_index);
    }
#line 748 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 169 "GetPot.bison" // lalr1.cc:859
    { (yylhs.value.node_indices) = nullptr;}
#line 754 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 171 "GetPot.bison" // lalr1.cc:859
    {
        unsigned int node_index = static_cast<unsigned int>((yystack_[0].value.node_index));
        (yylhs.value.node_indices) = new std::vector<unsigned int>();
        (yylhs.value.node_indices)->push_back(node_index);
    }
#line 764 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 177 "GetPot.bison" // lalr1.cc:859
    {
        if( (yystack_[2].value.node_indices) == nullptr )
        {
            (yylhs.value.node_indices) = new std::vector<unsigned int>();
        }
        (yylhs.value.node_indices)->push_back((yystack_[1].value.node_index));
        (yylhs.value.node_indices)->push_back((yystack_[0].value.node_index));
    }
#line 777 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 203 "GetPot.bison" // lalr1.cc:859
    {
        unsigned int name_index = static_cast<unsigned int>((yystack_[3].value.node_index));
        unsigned int left_index = static_cast<unsigned int>((yystack_[2].value.node_index));
        unsigned int right_index = static_cast<unsigned int>((yystack_[0].value.node_index));
        std::vector<unsigned int> child_indices = {name_index
                                                   ,left_index};
        if( (yystack_[1].value.node_indices) != nullptr )
        {
            child_indices.reserve(child_indices.size()+(yystack_[1].value.node_indices)->size());
            for( size_t i = 0; i < (yystack_[1].value.node_indices)->size(); ++i)
            {
                child_indices.push_back((yystack_[1].value.node_indices)->at(i));
            }
            delete (yystack_[1].value.node_indices);
        }
        child_indices.push_back(right_index);
        (yylhs.value.node_index) = interpreter.push_parent(wasp::FUNCTION
                                        ,"exp"
                                        ,child_indices);
     }
#line 802 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 225 "GetPot.bison" // lalr1.cc:859
    {
        unsigned int left_index = static_cast<unsigned int>((yystack_[1].value.node_index));
        unsigned int op_index = static_cast<unsigned int>((yystack_[0].value.node_index));
        std::vector<unsigned int> child_indices = {left_index
                                                   ,op_index};
        (yylhs.value.node_index) = interpreter.push_parent(wasp::UNARY_MINUS
                                        ,"exp"
                                        ,child_indices);
    }
#line 816 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 235 "GetPot.bison" // lalr1.cc:859
    {
       unsigned int left_index = static_cast<unsigned int>((yystack_[1].value.node_index));
       unsigned int op_index = static_cast<unsigned int>((yystack_[0].value.node_index));
       std::vector<unsigned int> child_indices = {left_index
                                                  ,op_index};
       (yylhs.value.node_index) = interpreter.push_parent(wasp::UNARY_NOT
                                       ,"exp"
                                       ,child_indices);
    }
#line 830 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 245 "GetPot.bison" // lalr1.cc:859
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
#line 846 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 257 "GetPot.bison" // lalr1.cc:859
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
#line 862 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 269 "GetPot.bison" // lalr1.cc:859
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
#line 878 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 281 "GetPot.bison" // lalr1.cc:859
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
#line 894 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 293 "GetPot.bison" // lalr1.cc:859
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
#line 910 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 305 "GetPot.bison" // lalr1.cc:859
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
#line 926 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 317 "GetPot.bison" // lalr1.cc:859
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
#line 942 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 329 "GetPot.bison" // lalr1.cc:859
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
#line 958 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 341 "GetPot.bison" // lalr1.cc:859
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
#line 974 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 353 "GetPot.bison" // lalr1.cc:859
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
#line 990 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 365 "GetPot.bison" // lalr1.cc:859
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
#line 1006 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 377 "GetPot.bison" // lalr1.cc:859
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
#line 1022 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 389 "GetPot.bison" // lalr1.cc:859
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
#line 1038 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 401 "GetPot.bison" // lalr1.cc:859
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
#line 1054 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 413 "GetPot.bison" // lalr1.cc:859
    {
        unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));(yylhs.value.node_index) = interpreter.push_leaf(wasp::COMMA,",",token_index);
    }
#line 1062 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 417 "GetPot.bison" // lalr1.cc:859
    {
        unsigned int assign_token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::ASSIGN,"="
                         ,assign_token_index);
    }
#line 1072 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 424 "GetPot.bison" // lalr1.cc:859
    {
        unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::OBJECT_TERM,"[]"
                         ,token_index);
    }
#line 1082 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 430 "GetPot.bison" // lalr1.cc:859
    {
        unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::SUB_OBJECT_TERM,"[../]"
                         ,token_index);
    }
#line 1092 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 436 "GetPot.bison" // lalr1.cc:859
    {
        unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::LBRACKET,"["
                         ,token_index);
    }
#line 1102 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 442 "GetPot.bison" // lalr1.cc:859
    {

        unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::RBRACKET,"]"
                         ,token_index);
    }
#line 1113 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 449 "GetPot.bison" // lalr1.cc:859
    {

        unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::DOT_SLASH,"./"
                         ,token_index);
    }
#line 1124 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 456 "GetPot.bison" // lalr1.cc:859
    {
        unsigned int lbracket_index = static_cast<unsigned int>((yystack_[3].value.node_index));
        unsigned int dot_slash_index = static_cast<unsigned int>((yystack_[2].value.node_index));
        unsigned int string_index = static_cast<unsigned int>((yystack_[1].value.node_index));
        unsigned int rbracket_index = static_cast<unsigned int>((yystack_[0].value.node_index));
        std::vector<unsigned int> child_indices = {lbracket_index
                                                   ,dot_slash_index
                                                   ,string_index
                                                   ,rbracket_index};

        (yylhs.value.node_index) = interpreter.push_parent(wasp::SUB_OBJECT_DECL
                                        ,interpreter.m_tree_nodes.data((yystack_[1].value.node_index)).c_str()
                                        ,child_indices);
    }
#line 1143 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 471 "GetPot.bison" // lalr1.cc:859
    {// empty object
        unsigned int object_decl_i = static_cast<unsigned int>((yystack_[1].value.node_index));
        unsigned int object_term_i = static_cast<unsigned int>((yystack_[0].value.node_index));
        std::vector<unsigned int> child_indices = {object_decl_i
                                                   ,object_term_i};

        (yylhs.value.node_index) = interpreter.push_parent(wasp::SUB_OBJECT
                                        ,interpreter.m_tree_nodes.name(object_decl_i)
                                        ,child_indices);

    }
#line 1159 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 482 "GetPot.bison" // lalr1.cc:859
    {   std::vector<unsigned int> children; children.reserve(2+(yystack_[1].value.node_indices)->size());
        unsigned int object_decl_i = static_cast<unsigned int>((yystack_[2].value.node_index));
        children.push_back(object_decl_i);
        for( unsigned int child_i: *(yystack_[1].value.node_indices) ) children.push_back(child_i);
        children.push_back(static_cast<unsigned int>((yystack_[0].value.node_index)));
        delete (yystack_[1].value.node_indices);

        (yylhs.value.node_index) = interpreter.push_parent(wasp::SUB_OBJECT
                                    ,interpreter.m_tree_nodes.name(object_decl_i)
                                    ,children);
    }
#line 1175 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 493 "GetPot.bison" // lalr1.cc:859
    {
        unsigned int lbracket_index = static_cast<unsigned int>((yystack_[2].value.node_index));
        unsigned int string_index = static_cast<unsigned int>((yystack_[1].value.node_index));
        unsigned int rbracket_index = static_cast<unsigned int>((yystack_[0].value.node_index));
        std::vector<unsigned int> child_indices = {lbracket_index
                                                   ,string_index
                                                   ,rbracket_index};

        (yylhs.value.node_index) = interpreter.push_parent(wasp::OBJECT_DECL
                                        ,interpreter.m_tree_nodes.data((yystack_[1].value.node_index)).c_str()
                                        ,child_indices);
    }
#line 1192 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 509 "GetPot.bison" // lalr1.cc:859
    {
        unsigned int node_index = static_cast<unsigned int>((yystack_[0].value.node_index));
        (yylhs.value.node_indices) = new std::vector<unsigned int>();
        (yylhs.value.node_indices)->push_back(node_index);
    }
#line 1202 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 514 "GetPot.bison" // lalr1.cc:859
    {
        (yystack_[1].value.node_indices)->push_back(static_cast<unsigned int>((yystack_[0].value.node_index)));
    }
#line 1210 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 519 "GetPot.bison" // lalr1.cc:859
    { // empty object
        unsigned int object_decl_i = static_cast<unsigned int>((yystack_[1].value.node_index));
        unsigned int object_term_i = static_cast<unsigned int>((yystack_[0].value.node_index));
        std::vector<unsigned int> child_indices = {object_decl_i
                                                   ,object_term_i};

        (yylhs.value.node_index) = interpreter.push_parent(wasp::OBJECT
                                        ,interpreter.m_tree_nodes.name(object_decl_i)
                                        ,child_indices);
        }
#line 1225 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 530 "GetPot.bison" // lalr1.cc:859
    {
        std::vector<unsigned int> children; children.reserve(2+(yystack_[1].value.node_indices)->size());
        unsigned int object_decl_i = static_cast<unsigned int>((yystack_[2].value.node_index));
        children.push_back(object_decl_i);
        for( unsigned int child_i: *(yystack_[1].value.node_indices) ) children.push_back(child_i);
        children.push_back(static_cast<unsigned int>((yystack_[0].value.node_index)));
        delete (yystack_[1].value.node_indices);

        (yylhs.value.node_index) = interpreter.push_parent(wasp::OBJECT
                                        ,interpreter.m_tree_nodes.name(object_decl_i)
                                        ,children);
        }
#line 1242 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 543 "GetPot.bison" // lalr1.cc:859
    {
        unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::INT,"int"
                         ,token_index);
    }
#line 1252 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 549 "GetPot.bison" // lalr1.cc:859
    {        
        unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::REAL,"real"
                         ,token_index);
    }
#line 1262 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 555 "GetPot.bison" // lalr1.cc:859
    {        
        unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::STRING,"string"
                         ,token_index);
    }
#line 1272 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 562 "GetPot.bison" // lalr1.cc:859
    {
        unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::VALUE,"value"
                         ,token_index);
    }
#line 1282 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 569 "GetPot.bison" // lalr1.cc:859
    {
        unsigned int decl_token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::DECL,"decl"
                         ,decl_token_index);
    }
#line 1292 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 575 "GetPot.bison" // lalr1.cc:859
    {
        unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::QUOTE,"'"
                         ,token_index);
    }
#line 1302 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 589 "GetPot.bison" // lalr1.cc:859
    {
        unsigned int offset = static_cast<unsigned int>((yystack_[0].value.node_index));
        (yylhs.value.node_indices) = new std::vector<unsigned int>();
        (yylhs.value.node_indices)->push_back(offset);
    }
#line 1312 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 594 "GetPot.bison" // lalr1.cc:859
    {
        (yystack_[1].value.node_indices)->push_back(static_cast<unsigned int>((yystack_[0].value.node_index)));
    }
#line 1320 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 599 "GetPot.bison" // lalr1.cc:859
    {
        (yystack_[1].value.node_indices)->insert((yystack_[1].value.node_indices)->begin(),(yystack_[2].value.node_index));
        (yystack_[1].value.node_indices)->push_back(static_cast<unsigned int>((yystack_[0].value.node_index)));
        (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
    }
#line 1330 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 605 "GetPot.bison" // lalr1.cc:859
    {
        (yylhs.value.node_indices) = new std::vector<unsigned int>();
        (yylhs.value.node_indices)->push_back(static_cast<unsigned int>((yystack_[1].value.node_index)));
        (yylhs.value.node_indices)->push_back(static_cast<unsigned int>((yystack_[0].value.node_index)));
    }
#line 1340 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 613 "GetPot.bison" // lalr1.cc:859
    {        

        unsigned int key_index = static_cast<unsigned int>((yystack_[2].value.node_index));
        unsigned int assign_index = static_cast<unsigned int>((yystack_[1].value.node_index));
        unsigned int value_index = static_cast<unsigned int>((yystack_[0].value.node_index));

        std::vector<unsigned int> child_indices = {key_index, assign_index,value_index};

        (yylhs.value.node_index) = interpreter.push_parent(wasp::KEYED_VALUE
                                        ,interpreter.m_tree_nodes.data(key_index).c_str()
                                        ,child_indices);
    }
#line 1357 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 626 "GetPot.bison" // lalr1.cc:859
    {

        unsigned int key_index = static_cast<unsigned int>((yystack_[2].value.node_index));
        unsigned int assign_index = static_cast<unsigned int>((yystack_[1].value.node_index));

        std::vector<unsigned int> child_indices = {key_index, assign_index};
        for( unsigned int child_i : *(yystack_[0].value.node_indices) ) child_indices.push_back(child_i);
        delete (yystack_[0].value.node_indices);
        (yylhs.value.node_index) = interpreter.push_parent(wasp::KEYED_VALUE
                                        ,interpreter.m_tree_nodes.data(key_index).c_str()
                                        ,child_indices);
    }
#line 1374 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 641 "GetPot.bison" // lalr1.cc:859
    {
        unsigned int token_index = static_cast<unsigned int>((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::COMMENT,"comment"
                         ,token_index);
    }
#line 1384 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 648 "GetPot.bison" // lalr1.cc:859
    {
            interpreter.add_root_child_index(static_cast<unsigned int>((yystack_[0].value.node_index)));
        }
#line 1392 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 651 "GetPot.bison" // lalr1.cc:859
    {
            interpreter.add_root_child_index(static_cast<unsigned int>((yystack_[0].value.node_index)));
        }
#line 1400 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 654 "GetPot.bison" // lalr1.cc:859
    {
            interpreter.add_root_child_index(static_cast<unsigned int>((yystack_[0].value.node_index)));
        }
#line 1408 "GetPotParser.cpp" // lalr1.cc:859
    break;


#line 1412 "GetPotParser.cpp" // lalr1.cc:859
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
  GetPotParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  GetPotParser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
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


  const signed char GetPotParser::yypact_ninf_ = -72;

  const signed char GetPotParser::yytable_ninf_ = -68;

  const short int
  GetPotParser::yypact_[] =
  {
     -72,     5,   -72,   -72,   -72,   -72,   -27,    40,   -72,   -72,
      -5,   -72,   -72,   -72,   -72,    10,   -72,   -72,     7,   -72,
     -72,    -6,    -2,   -72,   -72,    40,   -72,   -72,   -72,   -72,
     -72,   -72,   -72,    69,   -72,   -72,   -72,   -27,   -72,   -72,
      -2,   -72,   -72,   -72,   -72,   -72,   -72,   -72,   -72,     0,
     110,   110,   110,     9,   -72,   145,   -72,   -72,    52,   -72,
      10,   -72,    -1,    -1,   130,   110,   -72,   -72,   -72,   -72,
     -72,   -72,   -72,   -72,   -72,   -72,   -72,   -72,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   -72,   145,   -72,   -72,   -72,    52,   -72,   -72,   -72,
      -4,   145,    -9,    -9,    -9,    -9,    -9,    -9,   158,   158,
      -1,    -1,    64,    64,    -1,   -72,   -72,   -72,   110,   145
  };

  const unsigned char
  GetPotParser::yydefact_[] =
  {
      83,     0,     1,    45,    67,    82,     0,     0,    86,    68,
       0,    85,    84,    62,    70,     0,    60,    61,    62,    43,
      58,     0,     0,    55,    56,     0,    71,    72,    73,    52,
      53,    54,    42,     0,    46,    51,    47,     0,    44,    49,
       0,    59,    57,     2,    14,    16,    69,    63,    64,    65,
       0,     0,     0,     0,    24,    80,    66,    22,     0,    81,
       0,    50,    26,    25,     0,    19,     5,     6,     4,     3,
       7,     8,     9,    10,    11,    12,    13,    15,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    41,    75,    74,    79,    76,     0,    48,    17,    27,
       0,    20,    38,    40,    37,    39,    34,    33,    35,    36,
      28,    29,    30,    31,    32,    78,    77,    23,     0,    21
  };

  const signed char
  GetPotParser::yypgoto_[] =
  {
     -72,   -72,   -72,   -72,   -72,   -72,   -72,   -72,   -72,   -72,
     -72,   -72,   -72,     3,   -72,   -28,   -71,   -72,   -72,   -72,
     -33,   -69,   -72,    11,     2,    39,   -19,   -72,   -72,   -72,
     -72,   -17,    21,   -72,   -72,   -72,   -72,   -72,   -72,   -72,
     -72,   -57,     1,   -72,   -37,   -72,   -72,    60,    62,   -72
  };

  const signed char
  GetPotParser::yydefgoto_[] =
  {
      -1,    50,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    51,    90,    52,    99,    53,   100,    54,
      92,    93,    33,    20,    39,    21,    35,    37,    22,    23,
       7,    24,    25,     8,    26,    27,    14,    56,    57,     9,
      10,    58,    28,    29,    95,    96,    59,    30,    31,     1
  };

  const signed char
  GetPotParser::yytable_[] =
  {
      55,    94,     3,    13,    32,     2,    91,    15,    42,     3,
      74,    75,    76,    44,    77,    34,   -67,    62,    63,    64,
      36,    98,    77,    42,   -18,    65,    16,    17,    18,   117,
       5,   118,   101,    45,    38,     4,    41,     5,    60,   115,
       6,    97,    61,    40,     3,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,    89,   116,
      43,    11,    91,    12,     0,    89,    89,    89,    16,    17,
      18,     0,     5,     0,    44,    19,    45,    43,     0,    46,
      47,    48,    49,    74,    75,   119,     0,    77,     0,     0,
       0,    44,     0,    45,     0,    89,    46,    47,    48,    49,
       0,     0,     0,     0,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    43,     0,
       0,     0,    89,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    44,     0,    45,     0,     0,     0,    47,    48,
      49,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    44,    77,     0,    98,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    44,    77,    66,
      67,    68,    69,    70,    71,     0,     0,    74,    75,    76,
      44,    77
  };

  const signed char
  GetPotParser::yycheck_[] =
  {
      33,    58,     4,    30,     9,     0,    10,     6,    25,     4,
      19,    20,    21,    22,    23,     5,     9,    50,    51,    52,
      26,    25,    23,    40,    24,    53,    28,    29,    30,   100,
      32,   100,    65,    24,    36,    30,    25,    32,    37,    96,
       1,    60,    40,    22,     4,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    55,    96,
       8,     1,    10,     1,    -1,    62,    63,    64,    28,    29,
      30,    -1,    32,    -1,    22,    35,    24,     8,    -1,    27,
      28,    29,    30,    19,    20,   118,    -1,    23,    -1,    -1,
      -1,    22,    -1,    24,    -1,    92,    27,    28,    29,    30,
      -1,    -1,    -1,    -1,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,     8,    -1,
      -1,    -1,   119,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    22,    -1,    24,    -1,    -1,    -1,    28,    29,
      30,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    -1,    25,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    11,
      12,    13,    14,    15,    16,    -1,    -1,    19,    20,    21,
      22,    23
  };

  const unsigned char
  GetPotParser::yystos_[] =
  {
       0,    92,     0,     4,    30,    32,    68,    73,    76,    82,
      83,    90,    91,    30,    79,    85,    28,    29,    30,    35,
      66,    68,    71,    72,    74,    75,    77,    78,    85,    86,
      90,    91,     9,    65,     5,    69,    26,    70,    36,    67,
      75,    66,    74,     8,    22,    24,    27,    28,    29,    30,
      44,    56,    58,    60,    62,    63,    80,    81,    84,    89,
      85,    67,    63,    63,    63,    58,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    23,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    10,    63,    64,    84,    87,    88,    69,    25,    59,
      61,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    84,    87,    59,    64,    63
  };

  const unsigned char
  GetPotParser::yyr1_[] =
  {
       0,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      61,    61,    62,    62,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      72,    73,    74,    74,    74,    74,    75,    75,    76,    76,
      77,    78,    79,    80,    80,    80,    81,    82,    83,    84,
      85,    86,    86,    86,    87,    87,    88,    88,    89,    89,
      90,    90,    91,    92,    92,    92,    92
  };

  const unsigned char
  GetPotParser::yyr2_[] =
  {
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       1,     3,     1,     4,     1,     2,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     4,     2,
       3,     3,     1,     1,     1,     1,     1,     2,     2,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     3,     2,
       3,     3,     1,     0,     2,     2,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const GetPotParser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"end of line\"", "\"[\"",
  "\"]\"", "'{'", "'}'", "\"!\"", "\"=\"", "\",\"", "\">=\"", "\"<=\"",
  "\"<\"", "\">\"", "\"!=\"", "\"==\"", "\"&&\"", "\"||\"", "\"*\"",
  "\"/\"", "\"+\"", "\"-\"", "\"^\"", "\"(\"", "\")\"", "DOT_SLASH",
  "QUOTE", "\"integer\"", "\"real\"", "\"string\"", "\"quoted string\"",
  "\"comment\"", "\"start of unit of execution\"",
  "\"end of unit of execution\"", "\"block terminator\"",
  "\"subblock terminator\"", "\"declarator\"", "\"value\"", "UMINUS",
  "UNOT", "\"constant\"", "\"name\"", "$accept", "bang", "gt", "lt", "gte",
  "lte", "neq", "eq", "and", "or", "multiply", "divide", "plus", "minus",
  "exponent", "lparen", "rparen", "function_name", "function_args",
  "function", "math_exp", "comma", "assign", "object_term",
  "sub_object_term", "lbracket", "rbracket", "dot_slash",
  "sub_object_decl", "sub_object", "object_decl", "object_member",
  "object_members", "object", "integer", "real", "unquoted_string",
  "VALUE", "value", "DECL", "decl", "quote", "string", "primitive",
  "array_member", "array_members", "array", "keyedvalue", "comment",
  "start", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  GetPotParser::yyrline_[] =
  {
       0,   140,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   164,   169,
     170,   176,   201,   202,   223,   224,   234,   244,   256,   268,
     280,   292,   304,   316,   328,   340,   352,   364,   376,   388,
     400,   412,   416,   423,   429,   435,   441,   448,   455,   470,
     481,   493,   505,   505,   505,   506,   508,   513,   518,   529,
     542,   548,   554,   560,   560,   560,   561,   567,   568,   574,
     580,   582,   583,   584,   586,   586,   588,   593,   598,   604,
     612,   625,   640,   647,   648,   651,   654
  };

  // Print the state stack on the debug stream.
  void
  GetPotParser::yystack_print_ ()
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
  GetPotParser::yy_reduce_print_ (int yyrule)
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
  GetPotParser::token_number_type
  GetPotParser::yytranslate_ (int t)
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
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42
    };
    const unsigned int user_token_number_max_ = 295;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // wasp
#line 1942 "GetPotParser.cpp" // lalr1.cc:1167
#line 662 "GetPot.bison" // lalr1.cc:1168
 /*** Additional Code ***/
namespace wasp{
void GetPotParser::error(const GetPotParser::location_type& l,
                           const std::string& m)
{
    interpreter.error(l, m);
}
}; // end of namespace
