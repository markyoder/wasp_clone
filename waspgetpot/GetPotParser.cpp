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
#line 1 "GetPot.bison" // lalr1.cc:404
 /*** C/C++ Declarations ***/

#include <stdio.h>
#include <vector>
#include <cstring>

#line 43 "GetPotParser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "GetPotParser.hpp"

// User implementation prologue.
#line 114 "GetPot.bison" // lalr1.cc:412


#include "GetPotInterpreter.h"
#include "GetPotLexer.h"
std::string getpot_get_name(size_t object_decl_i
                            , wasp::AbstractInterpreter & interpreter
                            , std::pair<size_t, std::vector<size_t>*>* object_members)
{
    bool has_type = object_members->first != object_members->second->size();
    auto name_i = object_decl_i;
    std::string name;
    if( has_type )
    { // update/promote
        // should be type = value
        name_i = object_members->second->at(object_members->first);
        // acquire the data from the value
        //TODO - conduct checks
        name_i = interpreter.child_index_at(name_i,interpreter.child_count(name_i)-1);
        name = interpreter.data(name_i) + "_type";
    }else{
        name = interpreter.data(name_i);
    }
    return name;
}

/* this "connects" the GetPot parser in the interpreter to the flex GetPotLexer class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the interpreter context. */
#undef yylex
#define yylex lexer->lex


#line 89 "GetPotParser.cpp" // lalr1.cc:412


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
//#define YYUSE(E) ((void) (E))

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

#line 35 "GetPot.bison" // lalr1.cc:479
namespace wasp {
#line 175 "GetPotParser.cpp" // lalr1.cc:479

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
  GetPotParser::GetPotParser (class AbstractInterpreter& interpreter_yyarg, std::istream &input_stream_yyarg, std::shared_ptr<class GetPotLexerImpl> lexer_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      interpreter (interpreter_yyarg),
      input_stream (input_stream_yyarg),
      lexer (lexer_yyarg)
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
    switch (yysym.type_get ())
    {
            case 32: // sub_object_members

#line 113 "GetPot.bison" // lalr1.cc:614
        { delete (yysym.value.object_children)->second; delete (yysym.value.object_children); }
#line 430 "GetPotParser.cpp" // lalr1.cc:614
        break;

      case 33: // sub_object_decl

#line 111 "GetPot.bison" // lalr1.cc:614
        { delete (yysym.value.node_indices); }
#line 437 "GetPotParser.cpp" // lalr1.cc:614
        break;

      case 35: // object_decl

#line 111 "GetPot.bison" // lalr1.cc:614
        { delete (yysym.value.node_indices); }
#line 444 "GetPotParser.cpp" // lalr1.cc:614
        break;

      case 37: // object_members

#line 113 "GetPot.bison" // lalr1.cc:614
        { delete (yysym.value.object_children)->second; delete (yysym.value.object_children); }
#line 451 "GetPotParser.cpp" // lalr1.cc:614
        break;

      case 50: // array_members

#line 112 "GetPot.bison" // lalr1.cc:614
        { delete (yysym.value.node_indices); }
#line 458 "GetPotParser.cpp" // lalr1.cc:614
        break;

      case 51: // array

#line 112 "GetPot.bison" // lalr1.cc:614
        { delete (yysym.value.node_indices); }
#line 465 "GetPotParser.cpp" // lalr1.cc:614
        break;


      default:
        break;
    }
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
    #line 43 "GetPot.bison" // lalr1.cc:741
{
    // initialize the initial location object
    yyla.location.begin.filename = yyla.location.end.filename = &interpreter.stream_name();
    yyla.location.begin.line = yyla.location.end.line = interpreter.start_line();
    yyla.location.begin.column = yyla.location.end.column = interpreter.start_column();
    lexer = std::make_shared<GetPotLexerImpl>(interpreter,&input_stream);
}

#line 606 "GetPotParser.cpp" // lalr1.cc:741

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
#line 152 "GetPot.bison" // lalr1.cc:859
    {
        size_t token_index = ((yystack_[0].value.token_index));(yylhs.value.node_index) = interpreter.push_leaf(wasp::WASP_COMMA,",",token_index);
    }
#line 718 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 156 "GetPot.bison" // lalr1.cc:859
    {
        size_t assign_token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::ASSIGN,"="
                         ,assign_token_index);
    }
#line 728 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 163 "GetPot.bison" // lalr1.cc:859
    {
        size_t token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::OBJECT_TERM,"[]"
                         ,token_index);
    }
#line 738 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 169 "GetPot.bison" // lalr1.cc:859
    {
        size_t token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::SUB_OBJECT_TERM,"[../]"
                         ,token_index);
    }
#line 748 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 175 "GetPot.bison" // lalr1.cc:859
    {
        size_t token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::LBRACKET,"["
                         ,token_index);
    }
#line 758 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 181 "GetPot.bison" // lalr1.cc:859
    {

        size_t token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::RBRACKET,"]"
                         ,token_index);
    }
#line 769 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 188 "GetPot.bison" // lalr1.cc:859
    {

        size_t token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::DOT_SLASH,"./"
                         ,token_index);
    }
#line 780 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 198 "GetPot.bison" // lalr1.cc:859
    {
        size_t node_index = ((yystack_[0].value.node_index));
        auto indices = new std::vector<size_t>();
        indices->push_back(node_index);
        if( std::strcmp("type",interpreter.name(node_index)) == 0 )
        {
            // -1 because we just pushed the 'type' node
            (yylhs.value.object_children) = new std::pair<size_t,std::vector<size_t>*>
                    (indices->size()-1, indices);
        }
        else{
            (yylhs.value.object_children) = new std::pair<size_t,std::vector<size_t>*>
                    (indices->size(), indices);
        }
    }
#line 800 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 213 "GetPot.bison" // lalr1.cc:859
    {
        // only if the type has not already be assigned
        // and the new object is named type
        bool type_not_present = (yystack_[1].value.object_children)->first == (yystack_[1].value.object_children)->second->size();
        if( type_not_present
            && std::strcmp("type",interpreter.name((yystack_[0].value.node_index))) == 0 )
        {
            (yystack_[1].value.object_children)->first = (yystack_[1].value.object_children)->second->size();
        }else if( type_not_present ){
            (yystack_[1].value.object_children)->first = (yystack_[1].value.object_children)->second->size() + 1;
        }
        (yystack_[1].value.object_children)->second->push_back(((yystack_[0].value.node_index)));
    }
#line 818 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 227 "GetPot.bison" // lalr1.cc:859
    {
        size_t lbracket_index = ((yystack_[3].value.node_index));
        size_t dot_slash_index = ((yystack_[2].value.node_index));
        size_t decl_index = ((yystack_[1].value.node_index));
        size_t rbracket_index = ((yystack_[0].value.node_index));


        (yylhs.value.node_indices) = new std::vector<size_t>{lbracket_index
                ,dot_slash_index
                ,decl_index
                ,rbracket_index};
    }
#line 835 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 240 "GetPot.bison" // lalr1.cc:859
    {// empty object
        std::vector<size_t> &child_indices = *(yystack_[1].value.node_indices);
        size_t object_decl_i = child_indices.at(2);
        child_indices.push_back((yystack_[0].value.node_index));

        (yylhs.value.node_index) = interpreter.push_parent(wasp::SUB_OBJECT
                                        ,interpreter.data(object_decl_i).c_str()
                                        ,child_indices);
        delete (yystack_[1].value.node_indices);

    }
#line 851 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 251 "GetPot.bison" // lalr1.cc:859
    {   std::vector<size_t> & children = *(yystack_[2].value.node_indices);
        size_t object_decl_i = children.at(2);
        for( size_t child_i: *(yystack_[1].value.object_children)->second ) children.push_back(child_i);
        children.push_back(((yystack_[0].value.node_index)));
        const std::string& name
                = getpot_get_name(object_decl_i
                                  ,interpreter
                                  ,(yystack_[1].value.object_children));
        delete (yystack_[1].value.object_children)->second;
        delete (yystack_[1].value.object_children);
        (yylhs.value.node_index) = interpreter.push_parent(wasp::SUB_OBJECT
                                    ,name.c_str()
                                    ,children);
        delete (yystack_[2].value.node_indices);
    }
#line 871 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 267 "GetPot.bison" // lalr1.cc:859
    {   std::vector<size_t> & children = *(yystack_[1].value.node_indices);
        size_t object_decl_i = children.at(2);
        for( size_t child_i: *(yystack_[0].value.object_children)->second ) children.push_back(child_i);
        const std::string & name
                = getpot_get_name(object_decl_i
                                   ,interpreter
                                   ,(yystack_[0].value.object_children));
        delete (yystack_[0].value.object_children)->second;
        delete (yystack_[0].value.object_children);
        (yylhs.value.node_index) = interpreter.push_parent(wasp::SUB_OBJECT
                                    ,name.c_str()
                                    ,children);
        delete (yystack_[1].value.node_indices);
    }
#line 890 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 281 "GetPot.bison" // lalr1.cc:859
    {
        size_t lbracket_index = ((yystack_[2].value.node_index));
        size_t decl_index = ((yystack_[1].value.node_index));
        size_t rbracket_index = ((yystack_[0].value.node_index));
        (yylhs.value.node_indices) = new std::vector<size_t>{lbracket_index
                                                   ,decl_index
                                                   ,rbracket_index};
    }
#line 903 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 293 "GetPot.bison" // lalr1.cc:859
    {
        size_t node_index = ((yystack_[0].value.node_index));
        auto indices = new std::vector<size_t>();
        indices->push_back(node_index);
        if( std::strcmp("type",interpreter.name(node_index)) == 0 )
        {
            // -1 because we just pushed the 'type' node
            (yylhs.value.object_children) = new std::pair<size_t,std::vector<size_t>*>
                    (indices->size()-1, indices);
        }
        else{
            (yylhs.value.object_children) = new std::pair<size_t,std::vector<size_t>*>
                    (indices->size(), indices);
        }
    }
#line 923 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 308 "GetPot.bison" // lalr1.cc:859
    {

        // only if the type has not already be assigned
        // and the new object is named type
        bool type_not_present = (yystack_[1].value.object_children)->first == (yystack_[1].value.object_children)->second->size();
        if( type_not_present
            && std::strcmp("type",interpreter.name((yystack_[0].value.node_index))) == 0 )
        {
            (yystack_[1].value.object_children)->first = (yystack_[1].value.object_children)->second->size();
        }else if (type_not_present){
            (yystack_[1].value.object_children)->first = (yystack_[1].value.object_children)->second->size()+1;
        }
        (yystack_[1].value.object_children)->second->push_back(((yystack_[0].value.node_index)));
    }
#line 942 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 325 "GetPot.bison" // lalr1.cc:859
    { // empty object
        std::vector<size_t> &child_indices = *(yystack_[1].value.node_indices);
        size_t object_decl_i = child_indices.at(1);
        size_t object_term_i = ((yystack_[0].value.node_index));
        child_indices.push_back(object_term_i);

        (yylhs.value.node_index) = interpreter.push_parent(wasp::OBJECT
                                        ,interpreter.data(object_decl_i).c_str()
                                        ,child_indices);
        delete (yystack_[1].value.node_indices);
        }
#line 958 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 337 "GetPot.bison" // lalr1.cc:859
    {
        std::vector<size_t> & children = *(yystack_[2].value.node_indices);
        size_t object_decl_i = children.at(1);
        for( size_t child_i: *(yystack_[1].value.object_children)->second ) children.push_back(child_i);
        children.push_back(((yystack_[0].value.node_index)));
        const std::string& name
                = getpot_get_name(object_decl_i
                                  ,interpreter
                                  ,(yystack_[1].value.object_children));
        delete (yystack_[1].value.object_children)->second;
        delete (yystack_[1].value.object_children);
        (yylhs.value.node_index) = interpreter.push_parent(wasp::OBJECT
                                        ,name.c_str()
                                        ,children);
        delete (yystack_[2].value.node_indices);
        }
#line 979 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 354 "GetPot.bison" // lalr1.cc:859
    {
        std::vector<size_t> & children = *(yystack_[2].value.node_indices);
        size_t object_decl_i = children.at(1);
        for( size_t child_i: *(yystack_[1].value.object_children)->second ) children.push_back(child_i);
        children.push_back(((yystack_[0].value.node_index)));
        const std::string& name
                = getpot_get_name(object_decl_i
                                  ,interpreter
                                  ,(yystack_[1].value.object_children));
        delete (yystack_[1].value.object_children)->second;
        delete (yystack_[1].value.object_children);
        (yylhs.value.node_index) = interpreter.push_parent(wasp::OBJECT
                                        ,name.c_str()
                                        ,children);
        delete (yystack_[2].value.node_indices);
        error(yystack_[0].location,"syntax error, unexpected subblock terminator");
        YYERROR;
        }
#line 1002 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 373 "GetPot.bison" // lalr1.cc:859
    {
        size_t token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::INT,"int"
                         ,token_index);
    }
#line 1012 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 379 "GetPot.bison" // lalr1.cc:859
    {
        size_t token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::REAL,"real"
                         ,token_index);
    }
#line 1022 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 385 "GetPot.bison" // lalr1.cc:859
    {
        size_t token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::STRING,"string"
                         ,token_index);
    }
#line 1032 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 392 "GetPot.bison" // lalr1.cc:859
    {
        size_t token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::VALUE,"value"
                         ,token_index);
    }
#line 1042 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 399 "GetPot.bison" // lalr1.cc:859
    {
        size_t decl_token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::DECL,"decl"
                         ,decl_token_index);
    }
#line 1052 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 405 "GetPot.bison" // lalr1.cc:859
    {
        size_t token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::QUOTE,"'"
                         ,token_index);
    }
#line 1062 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 419 "GetPot.bison" // lalr1.cc:859
    {
        size_t offset = ((yystack_[0].value.node_index));
        (yylhs.value.node_indices) = new std::vector<size_t>();
        (yylhs.value.node_indices)->push_back(offset);
    }
#line 1072 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 424 "GetPot.bison" // lalr1.cc:859
    {
        (yystack_[1].value.node_indices)->push_back(((yystack_[0].value.node_index)));
    }
#line 1080 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 429 "GetPot.bison" // lalr1.cc:859
    {
        (yystack_[1].value.node_indices)->insert((yystack_[1].value.node_indices)->begin(),(yystack_[2].value.node_index));
        (yystack_[1].value.node_indices)->push_back(((yystack_[0].value.node_index)));
        (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
    }
#line 1090 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 435 "GetPot.bison" // lalr1.cc:859
    {
        (yylhs.value.node_indices) = new std::vector<size_t>();
        (yylhs.value.node_indices)->push_back(((yystack_[1].value.node_index)));
        (yylhs.value.node_indices)->push_back(((yystack_[0].value.node_index)));
    }
#line 1100 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 443 "GetPot.bison" // lalr1.cc:859
    {
        size_t key_index = ((yystack_[2].value.node_index));
        size_t assign_index = ((yystack_[1].value.node_index));
        size_t value_index = ((yystack_[0].value.node_index));

        std::vector<size_t> child_indices = {key_index, assign_index,value_index};

        (yylhs.value.node_index) = interpreter.push_parent(wasp::KEYED_VALUE
                                        ,interpreter.data(key_index).c_str()
                                        ,child_indices);
    }
#line 1116 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 455 "GetPot.bison" // lalr1.cc:859
    {

        size_t key_index = ((yystack_[2].value.node_index));
        size_t assign_index = ((yystack_[1].value.node_index));

        std::vector<size_t> child_indices = {key_index, assign_index};
        for( size_t child_i : *(yystack_[0].value.node_indices) ) child_indices.push_back(child_i);
        delete (yystack_[0].value.node_indices);
        (yylhs.value.node_index) = interpreter.push_parent(wasp::ARRAY
                                        ,interpreter.data(key_index).c_str()
                                        ,child_indices);
    }
#line 1133 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 470 "GetPot.bison" // lalr1.cc:859
    {
        size_t token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::COMMENT,"comment"
                         ,token_index);
    }
#line 1143 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 477 "GetPot.bison" // lalr1.cc:859
    {
            interpreter.push_staged_child(((yystack_[0].value.node_index)));
        }
#line 1151 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 480 "GetPot.bison" // lalr1.cc:859
    {
            interpreter.push_staged_child(((yystack_[0].value.node_index)));
        }
#line 1159 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 483 "GetPot.bison" // lalr1.cc:859
    {
            interpreter.push_staged_child(((yystack_[0].value.node_index)));
        }
#line 1167 "GetPotParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 487 "GetPot.bison" // lalr1.cc:859
    {
            std::vector<size_t> & children = *(yystack_[2].value.node_indices);
            // [0] = '[', [1] = 'name', [2] = ']'
            size_t object_decl_i = children[1];
            for( size_t child_i: *(yystack_[1].value.object_children)->second ) children.push_back(child_i);
            const std::string& name
                    = getpot_get_name(object_decl_i
                                      ,interpreter
                                      ,(yystack_[1].value.object_children));
            delete (yystack_[1].value.object_children)->second;
            delete (yystack_[1].value.object_children);

            size_t object_i = interpreter.push_parent(wasp::OBJECT
                                            ,name.c_str()
                                            ,children);
            interpreter.push_staged_child(object_i);
            interpreter.push_staged_child(((yystack_[0].value.node_index)));
            delete (yystack_[2].value.node_indices);
        }
#line 1191 "GetPotParser.cpp" // lalr1.cc:859
    break;


#line 1195 "GetPotParser.cpp" // lalr1.cc:859
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


  const signed char GetPotParser::yypact_ninf_ = -52;

  const signed char GetPotParser::yytable_ninf_ = -38;

  const signed char
  GetPotParser::yypact_[] =
  {
     -52,    20,   -52,   -52,   -52,   -52,   -52,    49,    55,   -52,
     -52,     6,   -52,   -52,     5,    13,   -52,    17,   -52,   -52,
      28,    44,   -52,   -52,    33,   -52,   -52,   -52,   -52,   -52,
     -52,   -52,   -52,    64,   -52,   -52,   -52,    49,   -52,   -52,
     -52,    44,   -52,   -52,   -52,   -52,   -52,   -52,    21,    55,
     -52,   -52,   -52,   -52,   -52,   -52,   -52,   -52,     4,   -52,
       5,   -52,   -52,    33,   -52,   -52,   -52,   -52,   -52,   -52,
       4,   -52,   -52,   -52
  };

  const unsigned char
  GetPotParser::yydefact_[] =
  {
      54,     0,     1,     6,    37,    36,    53,     0,     0,    57,
      38,     0,    56,    55,     0,    29,    30,    31,     4,    26,
       0,     0,    23,    24,     0,    41,    42,    40,    43,    20,
      21,    22,     3,     0,     7,    19,     8,     0,     5,    16,
      13,    18,    12,     9,    10,    11,    27,    28,     0,     0,
      25,    58,    39,    32,    33,    34,    35,    51,     0,    52,
       0,    17,    14,     0,     2,    44,    46,    45,    50,    47,
       0,    15,    49,    48
  };

  const signed char
  GetPotParser::yypgoto_[] =
  {
     -52,   -52,     0,   -23,   -15,     3,   -21,   -52,     9,   -52,
     -52,   -13,    27,   -19,    16,    30,   -52,   -52,   -52,   -52,
      22,   -52,    -7,   -51,   -52,   -12,    -8,   -52,   -52,     1,
       2,   -52
  };

  const signed char
  GetPotParser::yydefgoto_[] =
  {
      -1,    65,    66,    19,    47,    20,    35,    37,    40,    41,
      21,    22,     8,    23,    24,     9,    25,    26,    27,    56,
      67,    10,    11,    58,    28,    29,    69,    70,    59,    30,
      31,     1
  };

  const signed char
  GetPotParser::yytable_[] =
  {
      14,    46,    12,    13,     7,    50,    39,    68,    42,    43,
      34,    33,    32,    64,    32,    52,    53,    54,    55,    72,
       2,   -37,    44,    45,     3,   -36,    61,    48,    42,    43,
      60,    36,     4,     4,     5,     5,     6,     3,    36,    71,
      46,    14,    44,    45,    50,    15,    16,    17,     3,     6,
      62,    49,    18,    38,    51,    57,    15,    16,    17,     3,
       6,     4,    73,     5,    38,    63,     0,    15,    16,    17,
       0,     6,     0,     0,    18,    52,    53,    54,    55
  };

  const signed char
  GetPotParser::yycheck_[] =
  {
       7,    24,     1,     1,     1,    24,    21,    58,    21,    21,
       5,    11,     8,     9,     8,    11,    12,    13,    14,    70,
       0,     8,    21,    21,     4,     8,    41,    24,    41,    41,
      37,    10,    12,    12,    14,    14,    16,     4,    10,    60,
      63,    48,    41,    41,    63,    12,    13,    14,     4,    16,
      41,    24,    19,    20,    24,    33,    12,    13,    14,     4,
      16,    12,    70,    14,    20,    49,    -1,    12,    13,    14,
      -1,    16,    -1,    -1,    19,    11,    12,    13,    14
  };

  const unsigned char
  GetPotParser::yystos_[] =
  {
       0,    54,     0,     4,    12,    14,    16,    28,    35,    38,
      44,    45,    52,    53,    45,    12,    13,    14,    19,    26,
      28,    33,    34,    36,    37,    39,    40,    41,    47,    48,
      52,    53,     8,    25,     5,    29,    10,    30,    20,    27,
      31,    32,    34,    48,    52,    53,    26,    27,    28,    35,
      36,    38,    11,    12,    13,    14,    42,    43,    46,    51,
      45,    27,    31,    37,     9,    24,    25,    43,    46,    49,
      50,    29,    46,    49
  };

  const unsigned char
  GetPotParser::yyr1_[] =
  {
       0,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      31,    31,    31,    32,    32,    33,    34,    34,    34,    35,
      36,    36,    36,    36,    37,    37,    38,    38,    38,    39,
      40,    41,    42,    42,    42,    43,    44,    44,    45,    46,
      47,    48,    48,    48,    49,    49,    49,    50,    50,    51,
      51,    52,    52,    53,    54,    54,    54,    54,    54
  };

  const unsigned char
  GetPotParser::yyr2_[] =
  {
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     4,     2,     3,     2,     3,
       1,     1,     1,     1,     1,     2,     2,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     3,
       2,     3,     3,     1,     0,     2,     2,     2,     4
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const GetPotParser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"end of line\"", "\"[\"",
  "\"]\"", "'{'", "'}'", "\"=\"", "\",\"", "\"subblock indicator ./\"",
  "\"'\"", "\"integer\"", "\"real\"", "\"string\"", "\"quoted string\"",
  "\"comment\"", "\"start of unit of execution\"",
  "\"end of unit of execution\"", "\"block terminator\"",
  "\"subblock terminator\"", "\"declarator\"", "\"value\"", "$accept",
  "comma", "assign", "object_term", "sub_object_term", "lbracket",
  "rbracket", "dot_slash", "sub_object_member", "sub_object_members",
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
       0,   151,   151,   155,   162,   168,   174,   180,   187,   194,
     194,   194,   194,   197,   212,   226,   239,   250,   266,   281,
     289,   289,   289,   290,   292,   307,   324,   336,   353,   372,
     378,   384,   390,   390,   390,   391,   397,   397,   398,   404,
     410,   412,   413,   414,   416,   416,   416,   418,   423,   428,
     434,   442,   454,   469,   476,   477,   480,   483,   486
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
      17,    18,    19,    20,    21,    22
    };
    const unsigned int user_token_number_max_ = 275;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

#line 35 "GetPot.bison" // lalr1.cc:1167
} // wasp
#line 1673 "GetPotParser.cpp" // lalr1.cc:1167
#line 510 "GetPot.bison" // lalr1.cc:1168
 /*** Additional Code ***/
namespace wasp{
void GetPotParser::error(const GetPotParser::location_type& l,
                           const std::string& m)
{
    interpreter.error_stream()<<l<<": "<<m<<std::endl;
}
} // end of namespace
