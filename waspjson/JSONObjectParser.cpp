// A Bison parser, made by GNU Bison 3.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018 Free Software Foundation, Inc.

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
#line 1 "JSONObjectParser.bison" // lalr1.cc:407
 /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>

#line 43 "JSONObjectParser.cpp" // lalr1.cc:407

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "JSONObjectParser.hpp"

// User implementation prologue.
#line 99 "JSONObjectParser.bison" // lalr1.cc:415


#include "JSONObjectLexer.h"

/* this "connects" the bison parser in the interpreter to the flex JSONObjectLexer class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the interpreter context. */
#undef yylex
#define yylex lexer->lex


#line 68 "JSONObjectParser.cpp" // lalr1.cc:415


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
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 36 "JSONObjectParser.bison" // lalr1.cc:491
namespace wasp {
#line 163 "JSONObjectParser.cpp" // lalr1.cc:491

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  JSONObjectParser::yytnamerr_ (const char *yystr)
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
  JSONObjectParser::JSONObjectParser (std::shared_ptr<wasp::DataObject>& root_yyarg, std::istream &input_stream_yyarg, std::ostream &error_stream_yyarg, std::shared_ptr<class JSONObjectLexerImpl> lexer_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      root (root_yyarg),
      input_stream (input_stream_yyarg),
      error_stream (error_stream_yyarg),
      lexer (lexer_yyarg)
  {}

  JSONObjectParser::~JSONObjectParser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  JSONObjectParser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  JSONObjectParser::basic_symbol<Base>::basic_symbol ()
    : value ()
    , location ()
  {}

  template <typename Base>
  JSONObjectParser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value (other.value)
    , location (other.location)
  {
  }

  template <typename Base>
  JSONObjectParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  JSONObjectParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  JSONObjectParser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  void
  JSONObjectParser::basic_symbol<Base>::clear ()
  {
    Base::clear ();
  }

  template <typename Base>
  bool
  JSONObjectParser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  void
  JSONObjectParser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = s.value;
    location = s.location;
  }

  // by_type.
  JSONObjectParser::by_type::by_type ()
    : type (empty_symbol)
  {}

  JSONObjectParser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  JSONObjectParser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  void
  JSONObjectParser::by_type::clear ()
  {
    type = empty_symbol;
  }

  void
  JSONObjectParser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  int
  JSONObjectParser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  JSONObjectParser::by_state::by_state ()
    : state (empty_state)
  {}

  JSONObjectParser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  void
  JSONObjectParser::by_state::clear ()
  {
    state = empty_state;
  }

  void
  JSONObjectParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  JSONObjectParser::by_state::by_state (state_type s)
    : state (s)
  {}

  JSONObjectParser::symbol_number_type
  JSONObjectParser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  JSONObjectParser::stack_symbol_type::stack_symbol_type ()
  {}

  JSONObjectParser::stack_symbol_type::stack_symbol_type (const stack_symbol_type& that)
    : super_type (that.state, that.location)
  {
    value = that.value;
  }

  JSONObjectParser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.value, that.location)
  {
    // that is emptied.
    that.type = empty_symbol;
  }

  JSONObjectParser::stack_symbol_type&
  JSONObjectParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }


  template <typename Base>
  void
  JSONObjectParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    switch (yysym.type_get ())
    {
            case 17: // primitive

#line 88 "JSONObjectParser.bison" // lalr1.cc:622
        { delete (yysym.value.value); }
#line 397 "JSONObjectParser.cpp" // lalr1.cc:622
        break;

      case 18: // decl

#line 88 "JSONObjectParser.bison" // lalr1.cc:622
        { delete (yysym.value.string); }
#line 404 "JSONObjectParser.cpp" // lalr1.cc:622
        break;

      case 19: // array

#line 88 "JSONObjectParser.bison" // lalr1.cc:622
        { delete (yysym.value.value); }
#line 411 "JSONObjectParser.cpp" // lalr1.cc:622
        break;

      case 20: // object

#line 88 "JSONObjectParser.bison" // lalr1.cc:622
        { delete (yysym.value.value); }
#line 418 "JSONObjectParser.cpp" // lalr1.cc:622
        break;

      case 21: // array_members

#line 89 "JSONObjectParser.bison" // lalr1.cc:622
        {
    for(size_t i = 0; i < (yysym.value.values)->size(); ++i)
        delete (*(yysym.value.values))[i];
    delete (yysym.value.values);
}
#line 429 "JSONObjectParser.cpp" // lalr1.cc:622
        break;

      case 22: // keyed_member

#line 94 "JSONObjectParser.bison" // lalr1.cc:622
        {
    for(size_t i = 0; i < (yysym.value.keyed_values)->size(); ++i)
        delete (*(yysym.value.keyed_values))[i].second;
    delete (yysym.value.keyed_values);
}
#line 440 "JSONObjectParser.cpp" // lalr1.cc:622
        break;

      case 23: // object_members

#line 94 "JSONObjectParser.bison" // lalr1.cc:622
        {
    for(size_t i = 0; i < (yysym.value.keyed_values)->size(); ++i)
        delete (*(yysym.value.keyed_values))[i].second;
    delete (yysym.value.keyed_values);
}
#line 451 "JSONObjectParser.cpp" // lalr1.cc:622
        break;


      default:
        break;
    }
  }

#if YYDEBUG
  template <typename Base>
  void
  JSONObjectParser::yy_print_ (std::ostream& yyo,
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

  void
  JSONObjectParser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  void
  JSONObjectParser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  void
  JSONObjectParser::yypop_ (unsigned n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  JSONObjectParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  JSONObjectParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  JSONObjectParser::debug_level_type
  JSONObjectParser::debug_level () const
  {
    return yydebug_;
  }

  void
  JSONObjectParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  JSONObjectParser::state_type
  JSONObjectParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  JSONObjectParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  JSONObjectParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  JSONObjectParser::parse ()
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

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    // User initialization code.
    #line 44 "JSONObjectParser.bison" // lalr1.cc:746
{
    // initialize the initial location object
    yyla.location.begin.line = yyla.location.end.line = 1;
    yyla.location.begin.column = yyla.location.end.column = 1;
    lexer = std::make_shared<JSONObjectLexerImpl>(&input_stream);
}

#line 588 "JSONObjectParser.cpp" // lalr1.cc:746

    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << '\n';

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
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
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
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
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
  case 2:
#line 116 "JSONObjectParser.bison" // lalr1.cc:870
    {
            (yylhs.value.value) = new Value();
            wasp_ensure((yylhs.value.value)->is_null());
        }
#line 707 "JSONObjectParser.cpp" // lalr1.cc:870
    break;

  case 3:
#line 120 "JSONObjectParser.bison" // lalr1.cc:870
    {
            (yylhs.value.value) = new Value((yystack_[0].value.boolean));
        }
#line 715 "JSONObjectParser.cpp" // lalr1.cc:870
    break;

  case 4:
#line 123 "JSONObjectParser.bison" // lalr1.cc:870
    {
            (yylhs.value.value) = new Value((yystack_[0].value.boolean));
        }
#line 723 "JSONObjectParser.cpp" // lalr1.cc:870
    break;

  case 5:
#line 126 "JSONObjectParser.bison" // lalr1.cc:870
    {
            (yylhs.value.value) = new Value((yystack_[0].value.integer));
        }
#line 731 "JSONObjectParser.cpp" // lalr1.cc:870
    break;

  case 6:
#line 129 "JSONObjectParser.bison" // lalr1.cc:870
    {
            (yylhs.value.value) = new Value((yystack_[0].value.real));
        }
#line 739 "JSONObjectParser.cpp" // lalr1.cc:870
    break;

  case 7:
#line 132 "JSONObjectParser.bison" // lalr1.cc:870
    {
            (yylhs.value.value) = new Value(wasp::json_unescape_string(wasp::strip_quotes(*(yystack_[0].value.string))));
            delete (yystack_[0].value.string);
        }
#line 748 "JSONObjectParser.cpp" // lalr1.cc:870
    break;

  case 9:
#line 141 "JSONObjectParser.bison" // lalr1.cc:870
    {
        (yylhs.value.value) = new Value(DataArray());
    }
#line 756 "JSONObjectParser.cpp" // lalr1.cc:870
    break;

  case 10:
#line 145 "JSONObjectParser.bison" // lalr1.cc:870
    {
        error(yystack_[0].location, "array has unmatched left bracket!");
        YYERROR;
        (yylhs.value.value) = nullptr;
    }
#line 766 "JSONObjectParser.cpp" // lalr1.cc:870
    break;

  case 11:
#line 151 "JSONObjectParser.bison" // lalr1.cc:870
    {
        error(yystack_[2].location, " is an unmatched left bracket!");
        for(size_t i = 0; i < (yystack_[1].value.values)->size(); ++i) delete (yystack_[1].value.values)->at(i);
        delete (yystack_[1].value.values);
        YYERROR;
        (yylhs.value.value) = nullptr;
    }
#line 778 "JSONObjectParser.cpp" // lalr1.cc:870
    break;

  case 12:
#line 159 "JSONObjectParser.bison" // lalr1.cc:870
    {
        (yylhs.value.value) = new Value();
        DataArray *array = new DataArray();
        array->resize((yystack_[1].value.values)->size());
        for( size_t i = 0; i < (yystack_[1].value.values)->size();++i)
        {
            // move resources
            (*array)[i] = std::move(*(yystack_[1].value.values)->at(i));
            delete (yystack_[1].value.values)->at(i); // deallocate empty Value
        }
        delete (yystack_[1].value.values);
        (yylhs.value.value)->assign(array);
    }
#line 796 "JSONObjectParser.cpp" // lalr1.cc:870
    break;

  case 13:
#line 173 "JSONObjectParser.bison" // lalr1.cc:870
    {
        (yylhs.value.value) = new Value(DataObject());
    }
#line 804 "JSONObjectParser.cpp" // lalr1.cc:870
    break;

  case 14:
#line 177 "JSONObjectParser.bison" // lalr1.cc:870
    {
        error(yystack_[0].location, "is an unmatched left brace!");
        YYERROR;
        (yylhs.value.value) = nullptr;
    }
#line 814 "JSONObjectParser.cpp" // lalr1.cc:870
    break;

  case 15:
#line 183 "JSONObjectParser.bison" // lalr1.cc:870
    {
        error(yystack_[2].location, "is an unmatched left brace!");
        for(size_t i = 0; i < (yystack_[1].value.keyed_values)->size(); ++i) delete (yystack_[1].value.keyed_values)->at(i).second;
        delete (yystack_[1].value.keyed_values);
        YYERROR;
        (yylhs.value.value) = nullptr;
    }
#line 826 "JSONObjectParser.cpp" // lalr1.cc:870
    break;

  case 16:
#line 191 "JSONObjectParser.bison" // lalr1.cc:870
    {
        (yylhs.value.value) = new Value();
        DataObject *object = new DataObject();
        (yylhs.value.value)->assign(object);
        for( size_t i = 0; i < (yystack_[1].value.keyed_values)->size();++i)
        {
            // move resources
            (*object)[(yystack_[1].value.keyed_values)->at(i).first] = std::move(*(yystack_[1].value.keyed_values)->at(i).second);
            delete (yystack_[1].value.keyed_values)->at(i).second; // deallocate empty Value
        }
        delete (yystack_[1].value.keyed_values);

    }
#line 844 "JSONObjectParser.cpp" // lalr1.cc:870
    break;

  case 17:
#line 206 "JSONObjectParser.bison" // lalr1.cc:870
    {
            (yylhs.value.values) = new std::vector<Value*>();
            (yylhs.value.values)->push_back((yystack_[0].value.value));
        }
#line 853 "JSONObjectParser.cpp" // lalr1.cc:870
    break;

  case 18:
#line 211 "JSONObjectParser.bison" // lalr1.cc:870
    {
            (yylhs.value.values) = (yystack_[2].value.values);
            (yylhs.value.values)->push_back((yystack_[0].value.value));
        }
#line 862 "JSONObjectParser.cpp" // lalr1.cc:870
    break;

  case 19:
#line 216 "JSONObjectParser.bison" // lalr1.cc:870
    {
            (yylhs.value.values) = new std::vector<Value*>();
            (yylhs.value.values)->push_back((yystack_[0].value.value));
        }
#line 871 "JSONObjectParser.cpp" // lalr1.cc:870
    break;

  case 20:
#line 221 "JSONObjectParser.bison" // lalr1.cc:870
    {
           (yylhs.value.values) = (yystack_[2].value.values);
           (yylhs.value.values)->push_back((yystack_[0].value.value));
        }
#line 880 "JSONObjectParser.cpp" // lalr1.cc:870
    break;

  case 21:
#line 226 "JSONObjectParser.bison" // lalr1.cc:870
    {
            (yylhs.value.values) = new std::vector<Value*>();
            (yylhs.value.values)->push_back((yystack_[0].value.value));
        }
#line 889 "JSONObjectParser.cpp" // lalr1.cc:870
    break;

  case 22:
#line 231 "JSONObjectParser.bison" // lalr1.cc:870
    {
            (yylhs.value.values) = (yystack_[2].value.values);
            (yylhs.value.values)->push_back((yystack_[0].value.value));
        }
#line 898 "JSONObjectParser.cpp" // lalr1.cc:870
    break;

  case 23:
#line 236 "JSONObjectParser.bison" // lalr1.cc:870
    {
            (yylhs.value.keyed_values) = new std::vector<std::pair<std::string,Value*>>();
            (yylhs.value.keyed_values)->push_back(std::make_pair(wasp::strip_quotes(*(yystack_[2].value.string)),(yystack_[0].value.value)));
            delete (yystack_[2].value.string);
        }
#line 908 "JSONObjectParser.cpp" // lalr1.cc:870
    break;

  case 24:
#line 241 "JSONObjectParser.bison" // lalr1.cc:870
    {
            (yylhs.value.keyed_values) = new std::vector<std::pair<std::string,Value*>>();
            (yylhs.value.keyed_values)->push_back(std::make_pair(wasp::strip_quotes(*(yystack_[2].value.string)),(yystack_[0].value.value)));
            delete (yystack_[2].value.string);
        }
#line 918 "JSONObjectParser.cpp" // lalr1.cc:870
    break;

  case 25:
#line 246 "JSONObjectParser.bison" // lalr1.cc:870
    {
            (yylhs.value.keyed_values) = new std::vector<std::pair<std::string,Value*>>();
            (yylhs.value.keyed_values)->push_back(std::make_pair(wasp::strip_quotes(*(yystack_[2].value.string)),(yystack_[0].value.value)));
            delete (yystack_[2].value.string);
        }
#line 928 "JSONObjectParser.cpp" // lalr1.cc:870
    break;

  case 27:
#line 253 "JSONObjectParser.bison" // lalr1.cc:870
    {
            (yylhs.value.keyed_values) = (yystack_[2].value.keyed_values);
            (yylhs.value.keyed_values)->push_back((yystack_[0].value.keyed_values)->front());
            delete (yystack_[0].value.keyed_values);
        }
#line 938 "JSONObjectParser.cpp" // lalr1.cc:870
    break;

  case 29:
#line 259 "JSONObjectParser.bison" // lalr1.cc:870
    {
            wasp_check( (yystack_[0].value.value)->is_object() );
            root.reset((yystack_[0].value.value)->to_object());
            (yystack_[0].value.value)->assign((DataObject*)nullptr);
            delete (yystack_[0].value.value);
        }
#line 949 "JSONObjectParser.cpp" // lalr1.cc:870
    break;


#line 953 "JSONObjectParser.cpp" // lalr1.cc:870
            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
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
  JSONObjectParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  JSONObjectParser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
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


  const signed char JSONObjectParser::yypact_ninf_ = -17;

  const signed char JSONObjectParser::yytable_ninf_ = -1;

  const signed char
  JSONObjectParser::yypact_[] =
  {
      -9,     8,   -17,     4,   -17,   -17,   -17,    -8,   -17,     1,
     -17,    29,   -17,   -17,     0,   -17,   -17,   -17,   -17,   -17,
     -17,    20,   -17,   -17,   -17,   -17,   -17,   -17,   -17,   -17,
     -17,     2,   -17,   -17,    29,   -17,   -17,   -17
  };

  const unsigned char
  JSONObjectParser::yydefact_[] =
  {
      28,     0,    29,     0,    14,     8,    13,     0,    26,     0,
       1,     0,    15,    16,     0,     5,     3,     4,     2,     6,
       7,     0,    23,    24,    25,    27,    10,     9,    21,    19,
      17,     0,    11,    12,     0,    22,    20,    18
  };

  const signed char
  JSONObjectParser::yypgoto_[] =
  {
     -17,   -16,   -17,   -15,   -11,   -17,    -3,   -17,   -17
  };

  const signed char
  JSONObjectParser::yydefgoto_[] =
  {
      -1,    22,     7,    23,     2,    31,     8,     9,     3
  };

  const unsigned char
  JSONObjectParser::yytable_[] =
  {
      24,    12,    32,     1,    10,    28,    29,    11,     4,     5,
      30,    25,     0,    33,    13,    14,    34,     5,    35,    36,
      26,     6,     0,    37,    15,    16,    17,    18,    19,    20,
      21,    27,     1,    15,    16,    17,    18,    19,    20,    21,
       0,     1
  };

  const signed char
  JSONObjectParser::yycheck_[] =
  {
      11,     0,     0,    12,     0,    21,    21,    15,     0,     9,
      21,    14,    -1,    11,    13,    14,    14,     9,    34,    34,
       0,    13,    -1,    34,     4,     5,     6,     7,     8,     9,
      10,    11,    12,     4,     5,     6,     7,     8,     9,    10,
      -1,    12
  };

  const unsigned char
  JSONObjectParser::yystos_[] =
  {
       0,    12,    20,    24,     0,     9,    13,    18,    22,    23,
       0,    15,     0,    13,    14,     4,     5,     6,     7,     8,
       9,    10,    17,    19,    20,    22,     0,    11,    17,    19,
      20,    21,     0,    11,    14,    17,    19,    20
  };

  const unsigned char
  JSONObjectParser::yyr1_[] =
  {
       0,    16,    17,    17,    17,    17,    17,    17,    18,    19,
      19,    19,    19,    20,    20,    20,    20,    21,    21,    21,
      21,    21,    21,    22,    22,    22,    23,    23,    24,    24
  };

  const unsigned char
  JSONObjectParser::yyr2_[] =
  {
       0,     2,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     3,     3,     2,     2,     3,     3,     1,     3,     1,
       3,     1,     3,     3,     3,     3,     1,     3,     0,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const JSONObjectParser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"end of line\"",
  "\"integer\"", "\"true\"", "\"false\"", "\"null\"", "\"double\"",
  "\"quoted string\"", "'['", "']'", "'{'", "'}'", "','", "':'", "$accept",
  "primitive", "decl", "array", "object", "array_members", "keyed_member",
  "object_members", "start", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short
  JSONObjectParser::yyrline_[] =
  {
       0,   115,   115,   119,   122,   125,   128,   131,   136,   140,
     144,   150,   158,   172,   176,   182,   190,   205,   210,   215,
     220,   225,   230,   235,   240,   245,   251,   252,   258,   259
  };

  // Print the state stack on the debug stream.
  void
  JSONObjectParser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  JSONObjectParser::yy_reduce_print_ (int yyrule)
  {
    unsigned yylno = yyrline_[yyrule];
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

  // Symbol number corresponding to token number t.
  JSONObjectParser::token_number_type
  JSONObjectParser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    14,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    15,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    10,     2,    11,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    12,     2,    13,     2,     2,     2,     2,
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
       5,     6,     7,     8,     9
    };
    const unsigned user_token_number_max_ = 264;
    const token_number_type undef_token_ = 2;

    if (static_cast<int> (t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

#line 36 "JSONObjectParser.bison" // lalr1.cc:1181
} // wasp
#line 1391 "JSONObjectParser.cpp" // lalr1.cc:1181
#line 268 "JSONObjectParser.bison" // lalr1.cc:1182
 /*** Additional Code ***/

void wasp::JSONObjectParser::error(const JSONObjectParser::location_type& l,
                           const std::string& m)
{
    error_stream<<l<<": "<<m<<std::endl;
}
