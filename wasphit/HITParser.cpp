// A Bison parser, made by GNU Bison 3.8.2.

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
#line 1 "HIT.bison"
 /*** C/C++ Declarations ***/

#include <stdio.h>
#include <vector>
#include <cstring>

#line 48 "HITParser.cpp"


#include "HITParser.hpp"

// Second part of user prologue.
#line 116 "HIT.bison"


#include "HITInterpreter.h"
#include "HITLexer.h"
#include "HITConfig.h"

// Obtain the HIT name for an object_term
// I.e., 
// [name]
//     type=foo
//     ...
// has a rename occur equivalent to [foo_type].
// @return true, iff the name conversion occurs
bool hit_get_name(std::string& name,
                            size_t object_decl_i
                            , wasp::AbstractInterpreter & interpreter
                            , std::pair<size_t, std::vector<size_t>*>* object_members)
{
// if type promotion is disabled, then just return early before any checks
#if DISABLE_HIT_TYPE_PROMOTION
    return false;
#endif
    bool has_type = object_members->first != object_members->second->size();
    auto name_i = object_decl_i;
    if( has_type )
    { // update/promote
        // should be type = value
        name_i = object_members->second->at(object_members->first);
        // acquire the data from the value
        //TODO - conduct checks
        name_i = interpreter.child_index_at(name_i,interpreter.child_count(name_i)-1);
        name = interpreter.data(name_i) + "_type";
    }
    return has_type; 
}

size_t push_object(wasp::AbstractInterpreter & interpreter,
                   std::vector<size_t>& object_decl, 
                   std::pair<size_t, std::vector<size_t>*>* object_members,  
                   size_t object_term)
{
    std::vector<size_t> &child_indices = object_decl;
    size_t object_decl_i = child_indices.rbegin()[1];

    // Ensure object_decl is a wasp::DECL 
    // It may not be because of missing ]
    if (interpreter.type(object_decl_i) != wasp::DECL) object_decl_i = child_indices.rbegin()[0];

    std::string name = interpreter.data(object_decl_i).c_str();

    // handle 'x/y/z' names becoming tree hierarchy
    std::vector<std::string> names = wasp::split("/", name);
    if (object_members != nullptr && !object_members->second->empty())
    {
        for( size_t child_i: *object_members->second ) child_indices.push_back(child_i);

        // update name to <type>_type if type is present
        hit_get_name(names.back(), object_decl_i
                                  ,interpreter
                                  ,object_members);
    }
    // object_term of 0 indicates missing terminator. E.g., EOF reached
    if (object_term > 0) child_indices.push_back(object_term);

    
    size_t result_index = 0;

    // if '///' or some illegal mess, use the full name
    // so we still have a node on the tree
    if (names.empty() ) names.push_back(name);

    // push children first and add children
    // to new parent
    while( !names.empty() )
    {
        // skip empty names unless name was empty (an allowed error condition)
        if (names.back().empty() && !name.empty())
        {
            names.pop_back();
            continue;
        }
        result_index = interpreter.push_parent(wasp::OBJECT
                                    ,names.back().c_str()
                                    ,child_indices);        
        child_indices.clear();
        child_indices.push_back(result_index);
        names.pop_back();
    }
    
    return result_index;
}

size_t push_keyed_value_or_array(wasp::AbstractInterpreter & interpreter,
                                 std::vector<size_t>       & child_indices)
{
    // keyed values pass in three or less children and arrays pass in more

    wasp_check(!child_indices.empty());

    std::string name = interpreter.data(child_indices.front()).c_str();

    // split 'x/y/z' names into vector to iterate and build tree hierarchy

    std::vector<std::string> names = wasp::split("/", name);

    // for something illegal like '///', use full name so tree gets a node

    if (names.empty())
    {
        names.push_back(name);
    }

    // add keyed value or array then build hierarchy out of parent objects

    for(size_t result_index = 0; !names.empty(); names.pop_back())
    {
        // skip over empty levels in tree caused by consecutive delimiters

        if (names.back().empty())
        {
            continue;
        }

        // three or less children at the lowest level is for a keyed value

        if (result_index == 0 && child_indices.size() <= 3)
        {
            result_index = interpreter.push_parent(wasp::KEYED_VALUE    ,
                                                   names.back().c_str() ,
                                                   child_indices        );
        }

        // more than three children indicates an array at the lowest level

        else if (child_indices.size() > 3)
        {
            result_index = interpreter.push_parent(wasp::ARRAY          ,
                                                   names.back().c_str() ,
                                                   child_indices        );
        }

        // any other count (i.e., one) is for a higher level parent object

        else
        {
            wasp_check(child_indices.size() == 1);

            result_index = interpreter.push_parent(wasp::OBJECT         ,
                                                   names.back().c_str() ,
                                                   child_indices        );
        }

        // clear the vector of child indices and add only the result index

        child_indices.clear();

        child_indices.push_back(result_index);
    }

    // return result index from top level left in the child indices vector

    return child_indices.back();
}

/* this "connects" the HIT parser in the interpreter to the flex HITLexer class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the interpreter context. */
#undef yylex
#define yylex lexer->lex


#line 226 "HITParser.cpp"



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

#line 36 "HIT.bison"
namespace wasp {
#line 320 "HITParser.cpp"

  /// Build a parser object.
  HITParser::HITParser (class AbstractInterpreter& interpreter_yyarg, std::istream &input_stream_yyarg, std::shared_ptr<class HITLexerImpl> lexer_yyarg)
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

  HITParser::~HITParser ()
  {}

  HITParser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/

  // basic_symbol.
  template <typename Base>
  HITParser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
    , location (that.location)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  HITParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_MOVE_REF (location_type) l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  HITParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (value_type) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}


  template <typename Base>
  HITParser::symbol_kind_type
  HITParser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  HITParser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  HITParser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
    location = YY_MOVE (s.location);
  }

  // by_kind.
  HITParser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  HITParser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  HITParser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  HITParser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  void
  HITParser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  HITParser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  HITParser::symbol_kind_type
  HITParser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  HITParser::symbol_kind_type
  HITParser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }



  // by_state.
  HITParser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  HITParser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  HITParser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  HITParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  HITParser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  HITParser::symbol_kind_type
  HITParser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  HITParser::stack_symbol_type::stack_symbol_type ()
  {}

  HITParser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value), YY_MOVE (that.location))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  HITParser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value), YY_MOVE (that.location))
  {
    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  HITParser::stack_symbol_type&
  HITParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }

  HITParser::stack_symbol_type&
  HITParser::stack_symbol_type::operator= (stack_symbol_type& that)
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
  HITParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    switch (yysym.kind ())
    {
      case symbol_kind::S_object_decl: // object_decl
#line 113 "HIT.bison"
                    { delete (yysym.value.node_indices); }
#line 534 "HITParser.cpp"
        break;

      case symbol_kind::S_object_members: // object_members
#line 115 "HIT.bison"
                    { delete (yysym.value.object_children)->second; delete (yysym.value.object_children); }
#line 540 "HITParser.cpp"
        break;

      case symbol_kind::S_double_quoted_strings: // double_quoted_strings
#line 114 "HIT.bison"
                    { delete (yysym.value.node_indices); }
#line 546 "HITParser.cpp"
        break;

      case symbol_kind::S_array_members: // array_members
#line 114 "HIT.bison"
                    { delete (yysym.value.node_indices); }
#line 552 "HITParser.cpp"
        break;

      case symbol_kind::S_array: // array
#line 114 "HIT.bison"
                    { delete (yysym.value.node_indices); }
#line 558 "HITParser.cpp"
        break;

      default:
        break;
    }
  }

#if YYDEBUG
  template <typename Base>
  void
  HITParser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
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
  HITParser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  HITParser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  HITParser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  HITParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  HITParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  HITParser::debug_level_type
  HITParser::debug_level () const
  {
    return yydebug_;
  }

  void
  HITParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  HITParser::state_type
  HITParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  HITParser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  HITParser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  HITParser::operator() ()
  {
    return parse ();
  }

  int
  HITParser::parse ()
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
#line 44 "HIT.bison"
{
    // initialize the initial location object
    yyla.location.begin.filename = yyla.location.end.filename = &interpreter.stream_name();
    yyla.location.begin.line = yyla.location.end.line = interpreter.start_line();
    yyla.location.begin.column = yyla.location.end.column = interpreter.start_column();
    lexer = std::make_shared<HITLexerImpl>(interpreter,&input_stream);
    // lexer->set_debug(true); // Requires HIT.lex %option debug uncommented
    // this->set_debug_level(1); // Requires HIT.bison %debug option uncommented
}

#line 706 "HITParser.cpp"


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
  case 2: // semicolon: ";"
#line 293 "HIT.bison"
    {
        size_t token_index = ((yystack_[0].value.token_index));(yylhs.value.node_index) = interpreter.push_leaf(wasp::SEMICOLON,";",token_index);
    }
#line 846 "HITParser.cpp"
    break;

  case 3: // assign: "="
#line 297 "HIT.bison"
    {
        size_t assign_token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::ASSIGN,"="
                         ,assign_token_index);
    }
#line 856 "HITParser.cpp"
    break;

  case 4: // object_term: "block terminator"
#line 304 "HIT.bison"
    {
        size_t token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::OBJECT_TERM,"term"
                         ,token_index);
    }
#line 866 "HITParser.cpp"
    break;

  case 5: // lbracket: "["
#line 310 "HIT.bison"
    {
        size_t token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::LBRACKET,"["
                         ,token_index);
    }
#line 876 "HITParser.cpp"
    break;

  case 6: // rbracket: "]"
#line 316 "HIT.bison"
    {
        size_t token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::RBRACKET,"]"
                         ,token_index);
    }
#line 886 "HITParser.cpp"
    break;

  case 7: // dot_slash: "subblock indicator ./"
#line 322 "HIT.bison"
    {

        size_t token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::DOT_SLASH,"./"
                         ,token_index);
    }
#line 897 "HITParser.cpp"
    break;

  case 8: // include: "file include"
#line 329 "HIT.bison"
        {
            auto token_index = (yystack_[0].value.token_index);
            (yylhs.value.node_index) = interpreter.push_leaf(wasp::FILE,"decl",token_index);
        }
#line 906 "HITParser.cpp"
    break;

  case 9: // object_decl: lbracket section_name rbracket
#line 333 "HIT.bison"
                                             {
        size_t lbracket_index = ((yystack_[2].value.node_index));
        size_t decl_index = ((yystack_[1].value.node_index));
        size_t rbracket_index = ((yystack_[0].value.node_index));
        (yylhs.value.node_indices) = new std::vector<size_t>{lbracket_index
                                                   ,decl_index
                                                   ,rbracket_index};
    }
#line 919 "HITParser.cpp"
    break;

  case 10: // object_decl: lbracket section_name "end of line"
#line 341 "HIT.bison"
                                {
        size_t lbracket_index = ((yystack_[2].value.node_index));
        size_t decl_index = ((yystack_[1].value.node_index));
        (yylhs.value.node_indices) = new std::vector<size_t>{lbracket_index,decl_index};
        interpreter.set_failed(true);
        interpreter.error_stream() << yystack_[0].location.begin << ": syntax error, unexpected end of line, expecting ]" << std::endl;
    }
#line 931 "HITParser.cpp"
    break;

  case 11: // object_decl: lbracket "end of line"
#line 348 "HIT.bison"
                   {
        size_t lbracket_index = ((yystack_[1].value.node_index));
        
        // Manufacture empty token name 
        // data is zero bytes so byte offset will be the same as the opening bracket
        size_t byte_offset = interpreter.node_token_offset((yystack_[1].value.node_index));
        size_t decl_token_index =  interpreter.token_count();
        interpreter.push_token("", wasp::UNKNOWN, byte_offset);
        size_t decl_index = interpreter.push_leaf(wasp::DECL, "decl", decl_token_index);

        (yylhs.value.node_indices) = new std::vector<size_t>{lbracket_index,decl_index};
        interpreter.set_failed(true);
        interpreter.error_stream() << yystack_[0].location.begin << ": syntax error, unexpected end of line, expecting object name" << std::endl;
    }
#line 950 "HITParser.cpp"
    break;

  case 12: // object_decl: lbracket "end of file"
#line 362 "HIT.bison"
                   {
        size_t lbracket_index = ((yystack_[1].value.node_index));
        
        // Manufacture empty token name 
        // data is zero bytes so byte offset will be the same as the opening bracket
        size_t byte_offset = interpreter.node_token_offset((yystack_[1].value.node_index));
        size_t decl_token_index =  interpreter.token_count();
        interpreter.push_token("", wasp::UNKNOWN, byte_offset);
        size_t decl_index = interpreter.push_leaf(wasp::DECL, "decl", decl_token_index);

        (yylhs.value.node_indices) = new std::vector<size_t>{lbracket_index,decl_index};
        interpreter.set_failed(true);
        interpreter.error_stream() << yystack_[0].location.begin << ": syntax error, unexpected end of file, expecting object name" << std::endl;
    }
#line 969 "HITParser.cpp"
    break;

  case 13: // object_decl: lbracket section_name "end of file"
#line 376 "HIT.bison"
                                {
        size_t lbracket_index = ((yystack_[2].value.node_index));
        size_t decl_index = ((yystack_[1].value.node_index));
        (yylhs.value.node_indices) = new std::vector<size_t>{lbracket_index,decl_index};
        interpreter.set_failed(true);
        interpreter.error_stream() << yystack_[0].location.begin << ": syntax error, unexpected end of file, expecting ]" << std::endl;
    }
#line 981 "HITParser.cpp"
    break;

  case 14: // object_decl: lbracket section_name "invalid token"
#line 383 "HIT.bison"
                                    {
        size_t lbracket_index = ((yystack_[2].value.node_index));
        size_t decl_index = ((yystack_[1].value.node_index));
        (yylhs.value.node_indices) = new std::vector<size_t>{lbracket_index,decl_index};
        interpreter.set_failed(true);
        interpreter.error_stream() << yystack_[0].location.begin << ": syntax error, unexpected invalid token, expecting ]" << std::endl;
    }
#line 993 "HITParser.cpp"
    break;

  case 15: // object_decl: lbracket section_name "invalid token" rbracket
#line 390 "HIT.bison"
                                             {
        size_t lbracket_index = ((yystack_[3].value.node_index));
        size_t decl_index = ((yystack_[2].value.node_index));
        size_t rbracket_index = ((yystack_[0].value.node_index));
        (yylhs.value.node_indices) = new std::vector<size_t>{lbracket_index, decl_index, rbracket_index};
        interpreter.set_failed(true);
        interpreter.error_stream() << yystack_[1].location.begin << ": syntax error, unexpected invalid token, expecting ]" << std::endl;
    }
#line 1006 "HITParser.cpp"
    break;

  case 16: // object_decl: lbracket dot_slash section_name rbracket
#line 399 "HIT.bison"
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
#line 1023 "HITParser.cpp"
    break;

  case 17: // object_member: keyedvalue
#line 412 "HIT.bison"
                 { (yylhs.value.node_index) = (yystack_[0].value.node_index); }
#line 1029 "HITParser.cpp"
    break;

  case 18: // object_member: comment
#line 412 "HIT.bison"
                              { (yylhs.value.node_index) = (yystack_[0].value.node_index); }
#line 1035 "HITParser.cpp"
    break;

  case 19: // object_member: object
#line 413 "HIT.bison"
                  { (yylhs.value.node_index) = (yystack_[0].value.node_index); }
#line 1041 "HITParser.cpp"
    break;

  case 20: // object_member: include_file
#line 413 "HIT.bison"
                           { (yylhs.value.node_index) = (yystack_[0].value.node_index); }
#line 1047 "HITParser.cpp"
    break;

  case 21: // object_members: object_member
#line 416 "HIT.bison"
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
#line 1067 "HITParser.cpp"
    break;

  case 22: // object_members: object_members object_member
#line 431 "HIT.bison"
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
        (yylhs.value.object_children) = (yystack_[1].value.object_children);
    }
#line 1087 "HITParser.cpp"
    break;

  case 23: // object_members: object_members error
#line 447 "HIT.bison"
    {
        interpreter.set_failed(true);
        (yylhs.value.object_children) = (yystack_[1].value.object_children);
    }
#line 1096 "HITParser.cpp"
    break;

  case 24: // object: object_decl object_term
#line 454 "HIT.bison"
        { // empty object
            (yylhs.value.node_index) = push_object(interpreter, *(yystack_[1].value.node_indices), nullptr, (yystack_[0].value.node_index));
            delete (yystack_[1].value.node_indices);
        }
#line 1105 "HITParser.cpp"
    break;

  case 25: // object: object_decl "end of file"
#line 459 "HIT.bison"
        {
            (yylhs.value.node_index) = push_object(interpreter, *(yystack_[1].value.node_indices), nullptr, 0);
            delete (yystack_[1].value.node_indices);
            
            if (!interpreter.failed()) interpreter.error_stream() << yystack_[0].location.begin << ": syntax error, unexpected end of file" << std::endl;
            interpreter.set_failed(true);
        }
#line 1117 "HITParser.cpp"
    break;

  case 26: // object: object_decl error object_members object_term
#line 467 "HIT.bison"
        {
            (yylhs.value.node_index) = push_object(interpreter, *(yystack_[3].value.node_indices), (yystack_[1].value.object_children), (yystack_[0].value.node_index));
            delete (yystack_[3].value.node_indices);
            interpreter.set_failed(true);
        }
#line 1127 "HITParser.cpp"
    break;

  case 27: // object: object_decl object_members object_term
#line 473 "HIT.bison"
        {
            (yylhs.value.node_index) = push_object(interpreter, *(yystack_[2].value.node_indices), (yystack_[1].value.object_children), (yystack_[0].value.node_index));
            delete (yystack_[2].value.node_indices);
            delete (yystack_[1].value.object_children)->second;
            delete (yystack_[1].value.object_children);
        }
#line 1138 "HITParser.cpp"
    break;

  case 28: // object: object_decl object_members "end of file"
#line 480 "HIT.bison"
        {
            (yylhs.value.node_index) = push_object(interpreter, *(yystack_[2].value.node_indices), (yystack_[1].value.object_children), 0);
            delete (yystack_[2].value.node_indices);
            delete (yystack_[1].value.object_children)->second;
            delete (yystack_[1].value.object_children);
            interpreter.set_failed(true);
            interpreter.error_stream() << yystack_[2].location.begin << ": syntax error, unexpected end of file, expecting block terminator" << std::endl;
        }
#line 1151 "HITParser.cpp"
    break;

  case 29: // double_quoted_string: "quoted string"
#line 489 "HIT.bison"
    {
        size_t token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::VALUE, "value", token_index);
    }
#line 1160 "HITParser.cpp"
    break;

  case 30: // double_quoted_strings: double_quoted_string
#line 494 "HIT.bison"
    {
        size_t qstring_index = ((yystack_[0].value.node_index));
        (yylhs.value.node_indices) = new std::vector<size_t>();
        (yylhs.value.node_indices)->push_back(qstring_index);
    }
#line 1170 "HITParser.cpp"
    break;

  case 31: // double_quoted_strings: double_quoted_strings double_quoted_string
#line 500 "HIT.bison"
    {
        size_t qstring_index = ((yystack_[0].value.node_index));
        (yystack_[1].value.node_indices)->push_back(qstring_index);
        (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
    }
#line 1180 "HITParser.cpp"
    break;

  case 32: // VALUE: "integer"
#line 505 "HIT.bison"
        { (yylhs.value.token_index) = (yystack_[0].value.token_index); }
#line 1186 "HITParser.cpp"
    break;

  case 33: // VALUE: "real"
#line 505 "HIT.bison"
                  { (yylhs.value.token_index) = (yystack_[0].value.token_index); }
#line 1192 "HITParser.cpp"
    break;

  case 34: // VALUE: "value string"
#line 505 "HIT.bison"
                         { (yylhs.value.token_index) = (yystack_[0].value.token_index); }
#line 1198 "HITParser.cpp"
    break;

  case 35: // VALUE: "array string"
#line 505 "HIT.bison"
                                        { (yylhs.value.token_index) = (yystack_[0].value.token_index); }
#line 1204 "HITParser.cpp"
    break;

  case 36: // value: VALUE
#line 507 "HIT.bison"
    {
        size_t token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::VALUE,"value"
                         ,token_index);
    }
#line 1214 "HITParser.cpp"
    break;

  case 37: // SECTION_NAME: "object name"
#line 512 "HIT.bison"
               { (yylhs.value.token_index) = (yystack_[0].value.token_index); }
#line 1220 "HITParser.cpp"
    break;

  case 38: // SECTION_NAME: "integer"
#line 512 "HIT.bison"
                              { (yylhs.value.token_index) = (yystack_[0].value.token_index); }
#line 1226 "HITParser.cpp"
    break;

  case 39: // section_name: SECTION_NAME
#line 514 "HIT.bison"
    {
        size_t decl_token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::DECL,"decl"
                         ,decl_token_index);
    }
#line 1236 "HITParser.cpp"
    break;

  case 40: // field_name: "parameter name"
#line 520 "HIT.bison"
    {
        size_t decl_token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::DECL,"decl"
                         ,decl_token_index);
    }
#line 1246 "HITParser.cpp"
    break;

  case 41: // quote: "'"
#line 526 "HIT.bison"
    {
        size_t token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::QUOTE,"'"
                         ,token_index);
    }
#line 1256 "HITParser.cpp"
    break;

  case 42: // path: "string"
#line 533 "HIT.bison"
        {
            size_t token_index = ((yystack_[0].value.token_index));
            (yylhs.value.node_index) = interpreter.push_leaf(wasp::VALUE,"path"
                             ,token_index);
        }
#line 1266 "HITParser.cpp"
    break;

  case 43: // path: "quoted string"
#line 539 "HIT.bison"
        {
            size_t token_index = ((yystack_[0].value.token_index));
            (yylhs.value.node_index) = interpreter.push_leaf(wasp::VALUE,"path"
                             ,token_index);
        }
#line 1276 "HITParser.cpp"
    break;

  case 44: // include_file: include path
#line 546 "HIT.bison"
        {

            std::vector<size_t> child_indices = {(yystack_[1].value.node_index),(yystack_[0].value.node_index)};
            (yylhs.value.node_index) = interpreter.push_parent(wasp::FILE
                                         // include
                                         //  |_ decl (include)
                                         //  |_ value (path/to/file)
                                        ,"incl"
                                        ,child_indices);
            bool loaded = interpreter.load_document((yylhs.value.node_index), wasp::trim(interpreter.data((yystack_[0].value.node_index))," "));
            if (!loaded)
            {
                interpreter.set_failed(true);
            }
        }
#line 1296 "HITParser.cpp"
    break;

  case 45: // array_member: semicolon
#line 562 "HIT.bison"
               { (yylhs.value.node_index) = (yystack_[0].value.node_index); }
#line 1302 "HITParser.cpp"
    break;

  case 46: // array_member: value
#line 562 "HIT.bison"
                           { (yylhs.value.node_index) = (yystack_[0].value.node_index); }
#line 1308 "HITParser.cpp"
    break;

  case 47: // array_member: double_quoted_string
#line 562 "HIT.bison"
                                   { (yylhs.value.node_index) = (yystack_[0].value.node_index); }
#line 1314 "HITParser.cpp"
    break;

  case 48: // array_members: array_member
#line 565 "HIT.bison"
    {
        size_t offset = ((yystack_[0].value.node_index));
        (yylhs.value.node_indices) = new std::vector<size_t>();
        (yylhs.value.node_indices)->push_back(offset);
    }
#line 1324 "HITParser.cpp"
    break;

  case 49: // array_members: array_members array_member
#line 570 "HIT.bison"
    {
        (yystack_[1].value.node_indices)->push_back(((yystack_[0].value.node_index)));
        (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
    }
#line 1333 "HITParser.cpp"
    break;

  case 50: // array: quote array_members quote
#line 576 "HIT.bison"
    {
        (yystack_[1].value.node_indices)->insert((yystack_[1].value.node_indices)->begin(),(yystack_[2].value.node_index));
        (yystack_[1].value.node_indices)->push_back(((yystack_[0].value.node_index)));
        (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
    }
#line 1343 "HITParser.cpp"
    break;

  case 51: // array: quote quote
#line 582 "HIT.bison"
    {
        (yylhs.value.node_indices) = new std::vector<size_t>();
        (yylhs.value.node_indices)->push_back(((yystack_[1].value.node_index)));
        (yylhs.value.node_indices)->push_back(((yystack_[0].value.node_index)));
    }
#line 1353 "HITParser.cpp"
    break;

  case 52: // array: array array
#line 588 "HIT.bison"
    {
        (yylhs.value.node_indices) = (yystack_[1].value.node_indices);
        (yylhs.value.node_indices)->insert((yylhs.value.node_indices)->end(), (yystack_[0].value.node_indices)->begin(), (yystack_[0].value.node_indices)->end());
        delete (yystack_[0].value.node_indices);
    }
#line 1363 "HITParser.cpp"
    break;

  case 53: // keyedvalue: field_name assign value
#line 596 "HIT.bison"
    {
        size_t key_index = ((yystack_[2].value.node_index));
        size_t assign_index = ((yystack_[1].value.node_index));
        size_t value_index = ((yystack_[0].value.node_index));

        std::vector<size_t> child_indices = {key_index, assign_index,value_index};

        (yylhs.value.node_index) = push_keyed_value_or_array(interpreter, child_indices);
    }
#line 1377 "HITParser.cpp"
    break;

  case 54: // keyedvalue: field_name assign double_quoted_strings
#line 606 "HIT.bison"
    {
        size_t key_index = ((yystack_[2].value.node_index));
        size_t assign_index = ((yystack_[1].value.node_index));

        std::vector<size_t> child_indices = {key_index, assign_index};
        for( size_t child_i : *(yystack_[0].value.node_indices) ) child_indices.push_back(child_i);
        delete (yystack_[0].value.node_indices);

        (yylhs.value.node_index) = push_keyed_value_or_array(interpreter, child_indices);
    }
#line 1392 "HITParser.cpp"
    break;

  case 55: // keyedvalue: field_name assign array
#line 617 "HIT.bison"
    {

        size_t key_index = ((yystack_[2].value.node_index));
        size_t assign_index = ((yystack_[1].value.node_index));

        std::vector<size_t> child_indices = {key_index, assign_index};
        for( size_t child_i : *(yystack_[0].value.node_indices) ) child_indices.push_back(child_i);
        delete (yystack_[0].value.node_indices);

        (yylhs.value.node_index) = push_keyed_value_or_array(interpreter, child_indices);
    }
#line 1408 "HITParser.cpp"
    break;

  case 56: // keyedvalue: field_name assign error
#line 629 "HIT.bison"
    {
        size_t key_index = ((yystack_[2].value.node_index));
        size_t assign_index = ((yystack_[1].value.node_index));

        std::vector<size_t> child_indices = {key_index, assign_index};

        std::string key = interpreter.data(key_index);
        (yylhs.value.node_index) = push_keyed_value_or_array(interpreter, child_indices);
        interpreter.error_stream() << yystack_[1].location << ": syntax error, '" << key << "' has a missing or malformed value" << std::endl;
        interpreter.set_failed(true);
    }
#line 1424 "HITParser.cpp"
    break;

  case 57: // keyedvalue: field_name error
#line 641 "HIT.bison"
    {
        size_t key_index = ((yystack_[1].value.node_index));

        std::vector<size_t> child_indices = {key_index};

        std::string key = interpreter.data(key_index);
        (yylhs.value.node_index) = push_keyed_value_or_array(interpreter, child_indices);
        interpreter.set_failed(true);
    }
#line 1438 "HITParser.cpp"
    break;

  case 58: // comment: "comment"
#line 652 "HIT.bison"
    {
        size_t token_index = ((yystack_[0].value.token_index));
        (yylhs.value.node_index) = interpreter.push_leaf(wasp::COMMENT,"comment"
                         ,token_index);
    }
#line 1448 "HITParser.cpp"
    break;

  case 60: // start: start comment
#line 659 "HIT.bison"
                       {
            interpreter.push_staged_child((yystack_[0].value.node_index));
        }
#line 1456 "HITParser.cpp"
    break;

  case 61: // start: start keyedvalue
#line 662 "HIT.bison"
                          {
            interpreter.push_staged_child((yystack_[0].value.node_index));
        }
#line 1464 "HITParser.cpp"
    break;

  case 62: // start: start keyedvalue error
#line 665 "HIT.bison"
                                {
            interpreter.push_staged_child((yystack_[1].value.node_index));
            interpreter.set_failed(true);
        }
#line 1473 "HITParser.cpp"
    break;

  case 63: // start: start object
#line 669 "HIT.bison"
                      {
            interpreter.push_staged_child((yystack_[0].value.node_index));
        }
#line 1481 "HITParser.cpp"
    break;

  case 64: // start: start object error
#line 672 "HIT.bison"
                            {
            interpreter.push_staged_child((yystack_[1].value.node_index));
            interpreter.set_failed(true);
        }
#line 1490 "HITParser.cpp"
    break;

  case 65: // start: start include_file
#line 677 "HIT.bison"
        {
            // assume the included content will be a child of the existing
            // staged content.
            interpreter.push_staged_child((yystack_[0].value.node_index));
        }
#line 1500 "HITParser.cpp"
    break;


#line 1504 "HITParser.cpp"

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
  HITParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  HITParser::yytnamerr_ (const char *yystr)
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
  HITParser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // HITParser::context.
  HITParser::context::context (const HITParser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  HITParser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
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
  HITParser::yy_syntax_error_arguments_ (const context& yyctx,
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
  HITParser::yysyntax_error_ (const context& yyctx) const
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


  const signed char HITParser::yypact_ninf_ = -58;

  const signed char HITParser::yytable_ninf_ = -64;

  const signed char
  HITParser::yypact_[] =
  {
     -58,    33,   -58,   -58,   -58,   -58,   -58,    68,    54,     0,
       9,    55,   -58,    11,   -58,   -58,   -58,   -58,   -58,   -58,
      28,   -58,    39,   -58,   -58,   -58,   -58,    32,   -58,   -58,
     -58,     2,   -58,   -58,   -58,   -58,   -58,   -58,   -58,    47,
     -58,     7,   -58,   -58,     7,   -58,   -58,    30,   -58,   -58,
     -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,
      -5,   -58,   -58,    73,    51,   -58,   -58,   -58,   -58,   -58,
     -58,   -58,   -58,   -58,   -58,    73,    51,   -58,   -58
  };

  const signed char
  HITParser::yydefact_[] =
  {
      59,     0,     1,     5,    40,    58,     8,     0,     0,     0,
       0,     0,    65,     0,    60,    12,    11,     7,    38,    37,
       0,    39,     0,    42,    43,    44,    25,     0,     4,    24,
      21,     0,    19,    20,    17,    18,    64,    57,     3,     0,
      62,     0,    13,    10,    14,     6,     9,     0,    28,    23,
      27,    22,    56,    41,    32,    33,    34,    35,    29,    30,
      54,    36,    53,     0,    55,    16,    15,    26,    31,     2,
      45,    47,    46,    51,    48,     0,    52,    50,    49
  };

  const signed char
  HITParser::yypgoto_[] =
  {
     -58,   -58,   -58,   -27,   -58,    29,   -58,   -58,   -58,    15,
      13,    71,   -31,   -58,   -58,    36,   -58,    56,   -58,   -57,
     -58,    76,     3,   -58,    41,    81,    87,   -58
  };

  const signed char
  HITParser::yydefgoto_[] =
  {
       0,    70,    39,    29,     7,    46,    20,     8,     9,    30,
      31,    32,    71,    60,    61,    72,    21,    22,    11,    63,
      25,    33,    74,    75,    76,    34,    35,     1
  };

  const signed char
  HITParser::yytable_[] =
  {
      26,    27,    48,    49,    50,     3,    73,     3,    59,   -63,
      36,   -61,    40,    45,   -63,    58,   -61,     4,    77,     4,
      67,     5,    28,     5,    28,     6,   -63,     6,   -61,    68,
     -63,    49,   -61,     2,   -63,     3,   -61,     3,     3,    42,
      47,    18,    43,    44,    19,    45,    51,     4,    52,     4,
       4,     5,    28,     5,     5,     6,    37,     6,     6,    53,
      54,    55,    51,    53,    38,    56,    57,    58,    15,    23,
      65,    16,    10,    66,    24,    62,    41,    12,    78,    17,
      64,    18,    13,    69,    19,    53,    54,    55,    14,     0,
       0,    56,    57,    58
  };

  const signed char
  HITParser::yycheck_[] =
  {
       0,     1,     0,     1,    31,     5,    63,     5,    39,     0,
       1,     0,     1,     6,     5,    20,     5,    17,    75,    17,
      47,    21,    22,    21,    22,    25,    17,    25,    17,    60,
      21,     1,    21,     0,    25,     5,    25,     5,     5,     0,
      27,    13,     3,     4,    16,     6,    31,    17,     1,    17,
      17,    21,    22,    21,    21,    25,     1,    25,    25,    12,
      13,    14,    47,    12,     9,    18,    19,    20,     0,    15,
      41,     3,     1,    44,    20,    39,    20,     1,    75,    11,
      39,    13,     1,    10,    16,    12,    13,    14,     1,    -1,
      -1,    18,    19,    20
  };

  const signed char
  HITParser::yystos_[] =
  {
       0,    53,     0,     5,    17,    21,    25,    30,    33,    34,
      37,    44,    47,    51,    52,     0,     3,    11,    13,    16,
      32,    42,    43,    15,    20,    46,     0,     1,    22,    29,
      35,    36,    37,    47,    51,    52,     1,     1,     9,    28,
       1,    43,     0,     3,     4,     6,    31,    36,     0,     1,
      29,    35,     1,    12,    13,    14,    18,    19,    20,    38,
      39,    40,    41,    45,    50,    31,    31,    29,    38,    10,
      27,    38,    41,    45,    48,    49,    50,    45,    48
  };

  const signed char
  HITParser::yyr1_[] =
  {
       0,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      34,    34,    34,    34,    34,    34,    34,    35,    35,    35,
      35,    36,    36,    36,    37,    37,    37,    37,    37,    38,
      39,    39,    40,    40,    40,    40,    41,    42,    42,    43,
      44,    45,    46,    46,    47,    48,    48,    48,    49,    49,
      50,    50,    50,    51,    51,    51,    51,    51,    52,    53,
      53,    53,    53,    53,    53,    53
  };

  const signed char
  HITParser::yyr2_[] =
  {
       0,     2,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     2,     2,     3,     3,     4,     4,     1,     1,     1,
       1,     1,     2,     2,     2,     2,     4,     3,     3,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     2,
       3,     2,     2,     3,     3,     3,     3,     2,     1,     0,
       2,     2,     3,     2,     3,     2
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const HITParser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\"end of line\"",
  "\"invalid token\"", "\"[\"", "\"]\"", "'{'", "'}'", "\"=\"", "\";\"",
  "\"subblock indicator ./\"", "\"'\"", "\"integer\"", "\"real\"",
  "\"string\"", "\"object name\"", "\"parameter name\"",
  "\"value string\"", "\"array string\"", "\"quoted string\"",
  "\"comment\"", "\"block terminator\"", "\"section name\"", "\"value\"",
  "\"file include\"", "$accept", "semicolon", "assign", "object_term",
  "lbracket", "rbracket", "dot_slash", "include", "object_decl",
  "object_member", "object_members", "object", "double_quoted_string",
  "double_quoted_strings", "VALUE", "value", "SECTION_NAME",
  "section_name", "field_name", "quote", "path", "include_file",
  "array_member", "array_members", "array", "keyedvalue", "comment",
  "start", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  HITParser::yyrline_[] =
  {
       0,   292,   292,   296,   303,   309,   315,   321,   328,   333,
     341,   348,   362,   376,   383,   390,   398,   412,   412,   413,
     413,   415,   430,   446,   453,   458,   466,   472,   479,   488,
     493,   499,   505,   505,   505,   505,   506,   512,   512,   513,
     519,   525,   532,   538,   545,   562,   562,   562,   564,   569,
     575,   581,   587,   595,   605,   616,   628,   640,   651,   658,
     659,   662,   665,   669,   672,   676
  };

  void
  HITParser::yy_stack_print_ () const
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
  HITParser::yy_reduce_print_ (int yyrule) const
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

  HITParser::symbol_kind_type
  HITParser::yytranslate_ (int t) YY_NOEXCEPT
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
       2,     2,     2,     7,     2,     8,     2,     2,     2,     2,
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
       5,     6,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25
    };
    // Last valid token kind.
    const int code_max = 278;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 36 "HIT.bison"
} // wasp
#line 2084 "HITParser.cpp"

#line 686 "HIT.bison"
 /*** Additional Code ***/
namespace wasp{
void HITParser::error(const HITParser::location_type& l,
                           const std::string& m)
{
    interpreter.error_stream()<<l<<": "<<m<<std::endl;
}
} // end of namespace
