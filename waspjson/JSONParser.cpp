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
#line 1 "JSONParser.bison"  // lalr1.cc:404
                            /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>

#line 43 "JSONParser.cpp"  // lalr1.cc:404

#ifndef YY_NULLPTR
#if defined __cplusplus && 201103L <= __cplusplus
#define YY_NULLPTR nullptr
#else
#define YY_NULLPTR 0
#endif
#endif

#include "JSONParser.hpp"

// User implementation prologue.
#line 99 "JSONParser.bison"  // lalr1.cc:412

#include "JSONInterpreter.h"
#include "JSONLexer.h"

/* this "connects" the bison parser in the interpreter to the flex JSONLexer
 * class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the interpreter context. */
#undef yylex
#define yylex lexer->lex

#line 69 "JSONParser.cpp"  // lalr1.cc:412

#ifndef YY_
#if defined YYENABLE_NLS && YYENABLE_NLS
#if ENABLE_NLS
#include <libintl.h>  // FIXME: INFRINGES ON USER NAME SPACE.
#define YY_(msgid) dgettext("bison-runtime", msgid)
#endif
#endif
#ifndef YY_
#define YY_(msgid) msgid
#endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
#define YYLLOC_DEFAULT(Current, Rhs, N)                             \
    do                                                              \
        if (N)                                                      \
        {                                                           \
            (Current).begin = YYRHSLOC(Rhs, 1).begin;               \
            (Current).end   = YYRHSLOC(Rhs, N).end;                 \
        }                                                           \
        else                                                        \
        {                                                           \
            (Current).begin = (Current).end = YYRHSLOC(Rhs, 0).end; \
        }                                                           \
    while (/*CONSTCOND*/ false)
#endif

// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void)(E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
#define YYCDEBUG  \
    if (yydebug_) \
    (*yycdebug_)

#define YY_SYMBOL_PRINT(Title, Symbol)     \
    do                                     \
    {                                      \
        if (yydebug_)                      \
        {                                  \
            *yycdebug_ << Title << ' ';    \
            yy_print_(*yycdebug_, Symbol); \
            *yycdebug_ << std::endl;       \
        }                                  \
    } while (false)

#define YY_REDUCE_PRINT(Rule)       \
    do                              \
    {                               \
        if (yydebug_)               \
            yy_reduce_print_(Rule); \
    } while (false)

#define YY_STACK_PRINT()      \
    do                        \
    {                         \
        if (yydebug_)         \
            yystack_print_(); \
    } while (false)

#else  // !YYDEBUG

#define YYCDEBUG \
    if (false)   \
    std::cerr
#define YY_SYMBOL_PRINT(Title, Symbol) YYUSE(Symbol)
#define YY_REDUCE_PRINT(Rule) static_cast<void>(0)
#define YY_STACK_PRINT() static_cast<void>(0)

#endif  // !YYDEBUG

#define yyerrok (yyerrstatus_ = 0)
#define yyclearin (yyla.clear())

#define YYACCEPT goto yyacceptlab
#define YYABORT goto yyabortlab
#define YYERROR goto yyerrorlab
#define YYRECOVERING() (!!yyerrstatus_)

#line 33 "JSONParser.bison"  // lalr1.cc:479
namespace wasp
{
#line 155 "JSONParser.cpp"  // lalr1.cc:479

/* Return YYSTR after stripping away unnecessary quotes and
   backslashes, so that it's suitable for yyerror.  The heuristic is
   that double-quoting is unnecessary unless the string contains an
   apostrophe, a comma, or backslash (other than backslash-backslash).
   YYSTR is taken from yytname.  */
std::string JSONParser::yytnamerr_(const char *yystr)
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
    do_not_strip_quotes:;
    }

    return yystr;
}

/// Build a parser object.
JSONParser::JSONParser(class AbstractInterpreter &          interpreter_yyarg,
                       std::istream &                       input_stream_yyarg,
                       std::shared_ptr<class JSONLexerImpl> lexer_yyarg)
    :
#if YYDEBUG
    yydebug_(false)
    , yycdebug_(&std::cerr)
    ,
#endif
    interpreter(interpreter_yyarg)
    , input_stream(input_stream_yyarg)
    , lexer(lexer_yyarg)
{
}

JSONParser::~JSONParser()
{
}

/*---------------.
| Symbol types.  |
`---------------*/

inline JSONParser::syntax_error::syntax_error(const location_type &l,
                                              const std::string &  m)
    : std::runtime_error(m), location(l)
{
}

// basic_symbol.
template<typename Base>
inline JSONParser::basic_symbol<Base>::basic_symbol() : value()
{
}

template<typename Base>
inline JSONParser::basic_symbol<Base>::basic_symbol(const basic_symbol &other)
    : Base(other), value(), location(other.location)
{
    value = other.value;
}

template<typename Base>
inline JSONParser::basic_symbol<Base>::basic_symbol(typename Base::kind_type t,
                                                    const semantic_type &    v,
                                                    const location_type &    l)
    : Base(t), value(v), location(l)
{
}

/// Constructor for valueless symbols.
template<typename Base>
inline JSONParser::basic_symbol<Base>::basic_symbol(typename Base::kind_type t,
                                                    const location_type &    l)
    : Base(t), value(), location(l)
{
}

template<typename Base>
inline JSONParser::basic_symbol<Base>::~basic_symbol()
{
    clear();
}

template<typename Base>
inline void JSONParser::basic_symbol<Base>::clear()
{
    Base::clear();
}

template<typename Base>
inline bool JSONParser::basic_symbol<Base>::empty() const
{
    return Base::type_get() == empty_symbol;
}

template<typename Base>
inline void JSONParser::basic_symbol<Base>::move(basic_symbol &s)
{
    super_type::move(s);
    value    = s.value;
    location = s.location;
}

// by_type.
inline JSONParser::by_type::by_type() : type(empty_symbol)
{
}

inline JSONParser::by_type::by_type(const by_type &other) : type(other.type)
{
}

inline JSONParser::by_type::by_type(token_type t) : type(yytranslate_(t))
{
}

inline void JSONParser::by_type::clear()
{
    type = empty_symbol;
}

inline void JSONParser::by_type::move(by_type &that)
{
    type = that.type;
    that.clear();
}

inline int JSONParser::by_type::type_get() const
{
    return type;
}

// by_state.
inline JSONParser::by_state::by_state() : state(empty_state)
{
}

inline JSONParser::by_state::by_state(const by_state &other)
    : state(other.state)
{
}

inline void JSONParser::by_state::clear()
{
    state = empty_state;
}

inline void JSONParser::by_state::move(by_state &that)
{
    state = that.state;
    that.clear();
}

inline JSONParser::by_state::by_state(state_type s) : state(s)
{
}

inline JSONParser::symbol_number_type JSONParser::by_state::type_get() const
{
    if (state == empty_state)
        return empty_symbol;
    else
        return yystos_[state];
}

inline JSONParser::stack_symbol_type::stack_symbol_type()
{
}

inline JSONParser::stack_symbol_type::stack_symbol_type(state_type   s,
                                                        symbol_type &that)
    : super_type(s, that.location)
{
    value = that.value;
    // that is emptied.
    that.type = empty_symbol;
}

inline JSONParser::stack_symbol_type &JSONParser::stack_symbol_type::
operator=(const stack_symbol_type &that)
{
    state    = that.state;
    value    = that.value;
    location = that.location;
    return *this;
}

template<typename Base>
inline void JSONParser::yy_destroy_(const char *        yymsg,
                                    basic_symbol<Base> &yysym) const
{
    if (yymsg)
        YY_SYMBOL_PRINT(yymsg, yysym);

    // User destructor.
    switch (yysym.type_get())
    {
        case 29:  // declaration

#line 97 "JSONParser.bison"  // lalr1.cc:614
        {
            delete (yysym.value.node_indices);
        }
#line 410 "JSONParser.cpp"  // lalr1.cc:614
        break;

        case 30:  // array

#line 97 "JSONParser.bison"  // lalr1.cc:614
        {
            delete (yysym.value.node_indices);
        }
#line 417 "JSONParser.cpp"  // lalr1.cc:614
        break;

        case 31:  // object

#line 97 "JSONParser.bison"  // lalr1.cc:614
        {
            delete (yysym.value.node_indices);
        }
#line 424 "JSONParser.cpp"  // lalr1.cc:614
        break;

        case 35:  // array_members

#line 97 "JSONParser.bison"  // lalr1.cc:614
        {
            delete (yysym.value.node_indices);
        }
#line 431 "JSONParser.cpp"  // lalr1.cc:614
        break;

        case 36:  // object_members

#line 97 "JSONParser.bison"  // lalr1.cc:614
        {
            delete (yysym.value.node_indices);
        }
#line 438 "JSONParser.cpp"  // lalr1.cc:614
        break;

        default:
            break;
    }
}

#if YYDEBUG
template<typename Base>
void JSONParser::yy_print_(std::ostream &            yyo,
                           const basic_symbol<Base> &yysym) const
{
    std::ostream &yyoutput = yyo;
    YYUSE(yyoutput);
    symbol_number_type yytype = yysym.type_get();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty())
        std::abort();
    yyo << (yytype < yyntokens_ ? "token" : "nterm") << ' ' << yytname_[yytype]
        << " (" << yysym.location << ": ";
    YYUSE(yytype);
    yyo << ')';
}
#endif

inline void JSONParser::yypush_(const char *m, state_type s, symbol_type &sym)
{
    stack_symbol_type t(s, sym);
    yypush_(m, t);
}

inline void JSONParser::yypush_(const char *m, stack_symbol_type &s)
{
    if (m)
        YY_SYMBOL_PRINT(m, s);
    yystack_.push(s);
}

inline void JSONParser::yypop_(unsigned int n)
{
    yystack_.pop(n);
}

#if YYDEBUG
std::ostream &JSONParser::debug_stream() const
{
    return *yycdebug_;
}

void JSONParser::set_debug_stream(std::ostream &o)
{
    yycdebug_ = &o;
}

JSONParser::debug_level_type JSONParser::debug_level() const
{
    return yydebug_;
}

void JSONParser::set_debug_level(debug_level_type l)
{
    yydebug_ = l;
}
#endif  // YYDEBUG

inline JSONParser::state_type JSONParser::yy_lr_goto_state_(state_type yystate,
                                                            int        yysym)
{
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
        return yytable_[yyr];
    else
        return yydefgoto_[yysym - yyntokens_];
}

inline bool JSONParser::yy_pact_value_is_default_(int yyvalue)
{
    return yyvalue == yypact_ninf_;
}

inline bool JSONParser::yy_table_value_is_error_(int yyvalue)
{
    return yyvalue == yytable_ninf_;
}

int JSONParser::parse()
{
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_     = 0;
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
#line 42 "JSONParser.bison"  // lalr1.cc:741
        {
            // initialize the initial location object
            yyla.location.begin.filename = yyla.location.end.filename =
                &interpreter.stream_name();
            yyla.location.begin.line = yyla.location.end.line =
                interpreter.start_line();
            yyla.location.begin.column = yyla.location.end.column =
                interpreter.start_column();
            lexer = std::make_shared<JSONLexerImpl>(interpreter, &input_stream);
        }

#line 579 "JSONParser.cpp"  // lalr1.cc:741

        /* Initialize the stack.  The initial state will be set in
           yynewstate, since the latter expects the semantical and the
           location values to have been already stored, initialize these
           stacks with a primary value.  */
        yystack_.clear();
        yypush_(YY_NULLPTR, 0, yyla);

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
        if (yy_pact_value_is_default_(yyn))
            goto yydefault;

        // Read a lookahead token.
        if (yyla.empty())
        {
            YYCDEBUG << "Reading a token: ";
            try
            {
                yyla.type = yytranslate_(yylex(&yyla.value, &yyla.location));
            }
            catch (const syntax_error &yyexc)
            {
                error(yyexc);
                goto yyerrlab1;
            }
        }
        YY_SYMBOL_PRINT("Next token is", yyla);

        /* If the proper action on seeing token YYLA.TYPE is to reduce or
           to detect an error, take that action.  */
        yyn += yyla.type_get();
        if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get())
            goto yydefault;

        // Reduce or error.
        yyn = yytable_[yyn];
        if (yyn <= 0)
        {
            if (yy_table_value_is_error_(yyn))
                goto yyerrlab;
            yyn = -yyn;
            goto yyreduce;
        }

        // Count tokens shifted since error; after three, turn off error status.
        if (yyerrstatus_)
            --yyerrstatus_;

        // Shift the lookahead token.
        yypush_("Shifting", yyn, yyla);
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
                slice<stack_symbol_type, stack_type> slice(yystack_, yylen);
                YYLLOC_DEFAULT(yylhs.location, slice, yylen);
            }

            // Perform the reduction.
            YY_REDUCE_PRINT(yyn);
            try
            {
                switch (yyn)
                {
                    case 2:
#line 116 "JSONParser.bison"  // lalr1.cc:859
                    {
                        auto token_index = ((yystack_[0].value.token_index));
                        (yylhs.value.node_index) = interpreter.push_leaf(
                            wasp::WASP_COMMA, ",", token_index);
                    }
#line 692 "JSONParser.cpp"  // lalr1.cc:859
                    break;

                    case 5:
#line 123 "JSONParser.bison"  // lalr1.cc:859
                    {
                        auto token_index = ((yystack_[0].value.token_index));
                        (yylhs.value.node_index) = interpreter.push_leaf(
                            wasp::LBRACE, "{", token_index);
                    }
#line 701 "JSONParser.cpp"  // lalr1.cc:859
                    break;

                    case 6:
#line 128 "JSONParser.bison"  // lalr1.cc:859
                    {
                        auto token_index = ((yystack_[0].value.token_index));
                        (yylhs.value.node_index) = interpreter.push_leaf(
                            wasp::RBRACE, "}", token_index);
                    }
#line 710 "JSONParser.cpp"  // lalr1.cc:859
                    break;

                    case 7:
#line 133 "JSONParser.bison"  // lalr1.cc:859
                    {
                        auto token_index = ((yystack_[0].value.token_index));
                        (yylhs.value.node_index) = interpreter.push_leaf(
                            wasp::LBRACKET, "[", token_index);
                    }
#line 719 "JSONParser.cpp"  // lalr1.cc:859
                    break;

                    case 8:
#line 138 "JSONParser.bison"  // lalr1.cc:859
                    {
                        auto token_index = ((yystack_[0].value.token_index));
                        (yylhs.value.node_index) = interpreter.push_leaf(
                            wasp::RBRACKET, "]", token_index);
                    }
#line 728 "JSONParser.cpp"  // lalr1.cc:859
                    break;

                    case 15:
#line 147 "JSONParser.bison"  // lalr1.cc:859
                    {
                        size_t token_index = ((yystack_[0].value.token_index));
                        (yylhs.value.node_index) = interpreter.push_leaf(
                            wasp::VALUE, "value", token_index);
                    }
#line 738 "JSONParser.cpp"  // lalr1.cc:859
                    break;

                    case 16:
#line 153 "JSONParser.bison"  // lalr1.cc:859
                    {
                        auto token_index = ((yystack_[0].value.token_index));
                        std::string quote_less_data =
                            interpreter.token_data(token_index);
                        quote_less_data = wasp::strip_quotes(quote_less_data);
                        (yylhs.value.node_index) = interpreter.push_leaf(
                            wasp::DECL, "decl", token_index);
                    }
#line 751 "JSONParser.cpp"  // lalr1.cc:859
                    break;

                    case 18:
#line 162 "JSONParser.bison"  // lalr1.cc:859
                    {
                        auto token_index = ((yystack_[0].value.token_index));
                        (yylhs.value.node_index) = interpreter.push_leaf(
                            wasp::ASSIGN, ":", token_index);
                    }
#line 760 "JSONParser.cpp"  // lalr1.cc:859
                    break;

                    case 19:
#line 167 "JSONParser.bison"  // lalr1.cc:859
                    {
                        (yylhs.value.node_indices) = new std::vector<size_t>();
                        (yylhs.value.node_indices)
                            ->push_back((yystack_[1].value.node_index));
                        (yylhs.value.node_indices)
                            ->push_back((yystack_[0].value.node_index));
                    }
#line 770 "JSONParser.cpp"  // lalr1.cc:859
                    break;

                    case 20:
#line 175 "JSONParser.bison"  // lalr1.cc:859
                    {
                        (yylhs.value.node_indices) = new std::vector<size_t>();
                        (yylhs.value.node_indices)
                            ->push_back((yystack_[1].value.node_index));
                        (yylhs.value.node_indices)
                            ->push_back((yystack_[0].value.node_index));
                    }
#line 780 "JSONParser.cpp"  // lalr1.cc:859
                    break;

                    case 21:
#line 181 "JSONParser.bison"  // lalr1.cc:859
                    {
                        error(yystack_[0].location,
                              "array has unmatched left bracket!");
                        YYERROR;
                        (yylhs.value.node_indices) = nullptr;
                    }
#line 790 "JSONParser.cpp"  // lalr1.cc:859
                    break;

                    case 22:
#line 187 "JSONParser.bison"  // lalr1.cc:859
                    {
                        std::string name                = "object";
                        auto        last_component_type = interpreter.type(
                            (yystack_[1].value.node_indices)->back());
                        if ((yystack_[1].value.node_indices)->size() == 0)
                            error(yystack_[2].location,
                                  name + " has unmatched left bracket!");
                        else if (last_component_type == wasp::OBJECT)
                            error(yystack_[2].location,
                                  name + " or one of its components has "
                                         "unmatched left bracket!");
                        else
                            error(yystack_[2].location,
                                  name + " has unmatched left bracket!");
                        delete (yystack_[1].value.node_indices);
                        YYERROR;
                        (yylhs.value.node_indices) = nullptr;
                    }
#line 805 "JSONParser.cpp"  // lalr1.cc:859
                    break;

                    case 23:
#line 198 "JSONParser.bison"  // lalr1.cc:859
                    {
                        (yystack_[1].value.node_indices)
                            ->insert((yystack_[1].value.node_indices)->begin(),
                                     (yystack_[2].value.node_index));
                        (yystack_[1].value.node_indices)
                            ->push_back((yystack_[0].value.node_index));
                        (yylhs.value.node_indices) =
                            (yystack_[1].value.node_indices);
                    }
#line 815 "JSONParser.cpp"  // lalr1.cc:859
                    break;

                    case 24:
#line 204 "JSONParser.bison"  // lalr1.cc:859
                    {
                        (yylhs.value.node_indices) = new std::vector<size_t>();
                        (yylhs.value.node_indices)
                            ->push_back((yystack_[1].value.node_index));
                        (yylhs.value.node_indices)
                            ->push_back((yystack_[0].value.node_index));
                    }
#line 825 "JSONParser.cpp"  // lalr1.cc:859
                    break;

                    case 25:
#line 210 "JSONParser.bison"  // lalr1.cc:859
                    {
                        error(yystack_[0].location,
                              "object has unmatched left brace!");
                        YYERROR;
                        (yylhs.value.node_indices) = nullptr;
                    }
#line 835 "JSONParser.cpp"  // lalr1.cc:859
                    break;

                    case 26:
#line 216 "JSONParser.bison"  // lalr1.cc:859
                    {
                        // TODO capture partial definition
                        std::string name                = "object";
                        auto        last_component_type = interpreter.type(
                            (yystack_[1].value.node_indices)->back());
                        if ((yystack_[1].value.node_indices)->size() == 0)
                            error(yystack_[2].location,
                                  name + " has unmatched left brace!");
                        else if (last_component_type == wasp::OBJECT)
                            error(yystack_[2].location,
                                  name + " or one of its components has "
                                         "unmatched left brace!");
                        else
                            error(yystack_[2].location,
                                  name + " has unmatched left brace!");
                        delete (yystack_[1].value.node_indices);
                        YYERROR;
                        (yylhs.value.node_indices) = nullptr;
                    }
#line 851 "JSONParser.cpp"  // lalr1.cc:859
                    break;

                    case 27:
#line 228 "JSONParser.bison"  // lalr1.cc:859
                    {
                        (yystack_[1].value.node_indices)
                            ->insert((yystack_[1].value.node_indices)->begin(),
                                     (yystack_[2].value.node_index));
                        (yystack_[1].value.node_indices)
                            ->push_back((yystack_[0].value.node_index));
                        (yylhs.value.node_indices) =
                            (yystack_[1].value.node_indices);
                    }
#line 861 "JSONParser.cpp"  // lalr1.cc:859
                    break;

                    case 28:
#line 236 "JSONParser.bison"  // lalr1.cc:859
                    {
                        (yystack_[1].value.node_indices)
                            ->push_back((yystack_[0].value.node_index));
                        std::string quote_less_data = interpreter.data(
                            (yystack_[1].value.node_indices)->front());
                        quote_less_data = wasp::strip_quotes(quote_less_data);
                        (yylhs.value.node_index) = interpreter.push_parent(
                            wasp::KEYED_VALUE, quote_less_data.c_str(),
                            *(yystack_[1].value.node_indices));
                        delete (yystack_[1].value.node_indices);
                    }
#line 875 "JSONParser.cpp"  // lalr1.cc:859
                    break;

                    case 29:
#line 246 "JSONParser.bison"  // lalr1.cc:859
                    {
                        for (size_t i = 0;
                             i < (yystack_[0].value.node_indices)->size(); ++i)
                        {
                            (yystack_[1].value.node_indices)
                                ->push_back(
                                    (yystack_[0].value.node_indices)->at(i));
                        }
                        std::string quote_less_data = interpreter.data(
                            (yystack_[1].value.node_indices)->front());
                        quote_less_data = wasp::strip_quotes(quote_less_data);
                        (yylhs.value.node_index) = interpreter.push_parent(
                            wasp::OBJECT, quote_less_data.c_str(),
                            *(yystack_[1].value.node_indices));
                        delete (yystack_[1].value.node_indices);
                        delete (yystack_[0].value.node_indices);
                    }
#line 893 "JSONParser.cpp"  // lalr1.cc:859
                    break;

                    case 30:
#line 260 "JSONParser.bison"  // lalr1.cc:859
                    {
                        for (size_t i = 0;
                             i < (yystack_[0].value.node_indices)->size(); ++i)
                        {
                            (yystack_[1].value.node_indices)
                                ->push_back(
                                    (yystack_[0].value.node_indices)->at(i));
                        }
                        std::string quote_less_data = interpreter.data(
                            (yystack_[1].value.node_indices)->front());
                        quote_less_data = wasp::strip_quotes(quote_less_data);
                        (yylhs.value.node_index) = interpreter.push_parent(
                            wasp::ARRAY, quote_less_data.c_str(),
                            *(yystack_[1].value.node_indices));
                        delete (yystack_[1].value.node_indices);
                        delete (yystack_[0].value.node_indices);
                    }
#line 911 "JSONParser.cpp"  // lalr1.cc:859
                    break;

                    case 31:
#line 274 "JSONParser.bison"  // lalr1.cc:859
                    {
                        (yylhs.value.node_indices) = new std::vector<size_t>();
                        size_t obj_i               = interpreter.push_parent(
                            wasp::OBJECT, "value",
                            *(yystack_[0].value.node_indices));
                        (yylhs.value.node_indices)->push_back(obj_i);
                        delete (yystack_[0].value.node_indices);
                    }
#line 924 "JSONParser.cpp"  // lalr1.cc:859
                    break;

                    case 32:
#line 283 "JSONParser.bison"  // lalr1.cc:859
                    {
                        (yylhs.value.node_indices) =
                            (yystack_[2].value.node_indices);
                        (yylhs.value.node_indices)
                            ->push_back((yystack_[1].value.node_index));
                        size_t obj_i = interpreter.push_parent(
                            wasp::OBJECT, "value",
                            *(yystack_[0].value.node_indices));
                        (yylhs.value.node_indices)->push_back(obj_i);
                        delete (yystack_[0].value.node_indices);
                    }
#line 938 "JSONParser.cpp"  // lalr1.cc:859
                    break;

                    case 33:
#line 293 "JSONParser.bison"  // lalr1.cc:859
                    {
                        (yylhs.value.node_indices) = new std::vector<size_t>();
                        size_t arr_i               = interpreter.push_parent(
                            wasp::ARRAY, "value",
                            *(yystack_[0].value.node_indices));
                        (yylhs.value.node_indices)->push_back(arr_i);
                        delete (yystack_[0].value.node_indices);
                    }
#line 951 "JSONParser.cpp"  // lalr1.cc:859
                    break;

                    case 34:
#line 302 "JSONParser.bison"  // lalr1.cc:859
                    {
                        (yylhs.value.node_indices) =
                            (yystack_[2].value.node_indices);
                        (yylhs.value.node_indices)
                            ->push_back((yystack_[1].value.node_index));
                        size_t arr_i = interpreter.push_parent(
                            wasp::ARRAY, "value",
                            *(yystack_[0].value.node_indices));
                        (yylhs.value.node_indices)->push_back(arr_i);
                        delete (yystack_[0].value.node_indices);
                    }
#line 965 "JSONParser.cpp"  // lalr1.cc:859
                    break;

                    case 35:
#line 312 "JSONParser.bison"  // lalr1.cc:859
                    {
                        (yylhs.value.node_indices) = new std::vector<size_t>();
                        (yylhs.value.node_indices)
                            ->push_back((yystack_[0].value.node_index));
                    }
#line 974 "JSONParser.cpp"  // lalr1.cc:859
                    break;

                    case 36:
#line 317 "JSONParser.bison"  // lalr1.cc:859
                    {
                        (yylhs.value.node_indices) =
                            (yystack_[2].value.node_indices);
                        (yylhs.value.node_indices)
                            ->push_back((yystack_[1].value.node_index));
                        (yylhs.value.node_indices)
                            ->push_back((yystack_[0].value.node_index));
                    }
#line 984 "JSONParser.cpp"  // lalr1.cc:859
                    break;

                    case 37:
#line 323 "JSONParser.bison"  // lalr1.cc:859
                    {
                        (yylhs.value.node_indices) = new std::vector<size_t>();
                        (yylhs.value.node_indices)
                            ->push_back((yystack_[0].value.node_index));
                    }
#line 993 "JSONParser.cpp"  // lalr1.cc:859
                    break;

                    case 38:
#line 328 "JSONParser.bison"  // lalr1.cc:859
                    {
                        (yylhs.value.node_indices) =
                            (yystack_[2].value.node_indices);
                        (yylhs.value.node_indices)
                            ->push_back((yystack_[1].value.node_index));
                        (yylhs.value.node_indices)
                            ->push_back((yystack_[0].value.node_index));
                    }
#line 1003 "JSONParser.cpp"  // lalr1.cc:859
                    break;

                    case 39:
#line 334 "JSONParser.bison"  // lalr1.cc:859
                    {
                        (yylhs.value.node_indices) = new std::vector<size_t>();
                        (yylhs.value.node_indices)
                            ->push_back((yystack_[0].value.node_index));
                    }
#line 1012 "JSONParser.cpp"  // lalr1.cc:859
                    break;

                    case 40:
#line 339 "JSONParser.bison"  // lalr1.cc:859
                    {
                        (yylhs.value.node_indices) =
                            (yystack_[2].value.node_indices);
                        (yylhs.value.node_indices)
                            ->push_back((yystack_[1].value.node_index));
                        (yylhs.value.node_indices)
                            ->push_back((yystack_[0].value.node_index));
                    }
#line 1022 "JSONParser.cpp"  // lalr1.cc:859
                    break;

                    case 41:
#line 345 "JSONParser.bison"  // lalr1.cc:859
                    {
                        (yylhs.value.node_indices) = new std::vector<size_t>();
                        (yylhs.value.node_indices)
                            ->push_back((yystack_[0].value.node_index));
                    }
#line 1031 "JSONParser.cpp"  // lalr1.cc:859
                    break;

                    case 42:
#line 350 "JSONParser.bison"  // lalr1.cc:859
                    {
                        (yylhs.value.node_indices) =
                            (yystack_[2].value.node_indices);
                        (yylhs.value.node_indices)
                            ->push_back((yystack_[1].value.node_index));
                        (yylhs.value.node_indices)
                            ->push_back((yystack_[0].value.node_index));
                    }
#line 1041 "JSONParser.cpp"  // lalr1.cc:859
                    break;

                    case 44:
#line 356 "JSONParser.bison"  // lalr1.cc:859
                    {
                        interpreter.staged_type(0) = wasp::OBJECT;
                        interpreter.push_staged_child(
                            *(yystack_[0].value.node_indices));
                        delete (yystack_[0].value.node_indices);
                        if (interpreter.single_parse())
                        {
                            lexer->rewind();
                            YYACCEPT;
                        }
                    }
#line 1052 "JSONParser.cpp"  // lalr1.cc:859
                    break;

                    case 45:
#line 362 "JSONParser.bison"  // lalr1.cc:859
                    {
                        interpreter.staged_type(0) = wasp::ARRAY;
                        interpreter.push_staged_child(
                            *(yystack_[0].value.node_indices));
                        delete (yystack_[0].value.node_indices);
                        if (interpreter.single_parse())
                        {
                            lexer->rewind();
                            YYACCEPT;
                        }
                    }
#line 1063 "JSONParser.cpp"  // lalr1.cc:859
                    break;

#line 1067 "JSONParser.cpp"  // lalr1.cc:859
                    default:
                        break;
                }
            }
            catch (const syntax_error &yyexc)
            {
                error(yyexc);
                YYERROR;
            }
            YY_SYMBOL_PRINT("-> $$ =", yylhs);
            yypop_(yylen);
            yylen = 0;
            YY_STACK_PRINT();

            // Shift the result of the reduction.
            yypush_(YY_NULLPTR, yylhs);
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
            error(yyla.location, yysyntax_error_(yystack_[0].state, yyla));
        }

        yyerror_range[1].location = yyla.location;
        if (yyerrstatus_ == 3)
        {
            /* If just tried and failed to reuse lookahead token after an
               error, discard it.  */

            // Return failure if at end of input.
            if (yyla.type_get() == yyeof_)
                YYABORT;
            else if (!yyla.empty())
            {
                yy_destroy_("Error: discarding", yyla);
                yyla.clear();
            }
        }

        // Else will try to reuse lookahead token after shifting the error
        // token.
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
        yypop_(yylen);
        yylen = 0;
        goto yyerrlab1;

    /*-------------------------------------------------------------.
    | yyerrlab1 -- common code for both syntax error and YYERROR.  |
    `-------------------------------------------------------------*/
    yyerrlab1:
        yyerrstatus_ = 3;  // Each real token shifted decrements this.
        {
            stack_symbol_type error_token;
            for (;;)
            {
                yyn = yypact_[yystack_[0].state];
                if (!yy_pact_value_is_default_(yyn))
                {
                    yyn += yyterror_;
                    if (0 <= yyn && yyn <= yylast_ &&
                        yycheck_[yyn] == yyterror_)
                    {
                        yyn = yytable_[yyn];
                        if (0 < yyn)
                            break;
                    }
                }

                // Pop the current state because it cannot handle the error
                // token.
                if (yystack_.size() == 1)
                    YYABORT;

                yyerror_range[1].location = yystack_[0].location;
                yy_destroy_("Error: popping", yystack_[0]);
                yypop_();
                YY_STACK_PRINT();
            }

            yyerror_range[2].location = yyla.location;
            YYLLOC_DEFAULT(error_token.location, yyerror_range, 2);

            // Shift the error token.
            error_token.state = yyn;
            yypush_("Shifting", error_token);
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
        if (!yyla.empty())
            yy_destroy_("Cleanup: discarding lookahead", yyla);

        /* Do not reclaim the symbols of the rule whose action triggered
           this YYABORT or YYACCEPT.  */
        yypop_(yylen);
        while (1 < yystack_.size())
        {
            yy_destroy_("Cleanup: popping", yystack_[0]);
            yypop_();
        }

        return yyresult;
    }
    catch (...)
    {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty())
            yy_destroy_(YY_NULLPTR, yyla);

        while (1 < yystack_.size())
        {
            yy_destroy_(YY_NULLPTR, yystack_[0]);
            yypop_();
        }
        throw;
    }
}

void JSONParser::error(const syntax_error &yyexc)
{
    error(yyexc.location, yyexc.what());
}

// Generate an error message.
std::string JSONParser::yysyntax_error_(state_type         yystate,
                                        const symbol_type &yyla) const
{
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum
    {
        YYERROR_VERBOSE_ARGS_MAXIMUM = 5
    };
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
    if (!yyla.empty())
    {
        int yytoken      = yyla.type_get();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn          = yypact_[yystate];
        if (!yy_pact_value_is_default_(yyn))
        {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend     = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
                if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_ &&
                    !yy_table_value_is_error_(yytable_[yyx + yyn]))
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

    char const *yyformat = YY_NULLPTR;
    switch (yycount)
    {
#define YYCASE_(N, S) \
    case N:           \
        yyformat = S; \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4,
                YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(
            5,
            YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const *yyp = yyformat; *yyp; ++yyp)
        if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
            yyres += yytnamerr_(yyarg[yyi++]);
            ++yyp;
        }
        else
            yyres += *yyp;
    return yyres;
}

const signed char JSONParser::yypact_ninf_ = -13;

const signed char JSONParser::yytable_ninf_ = -1;

const signed char JSONParser::yypact_[] = {
    0,   -13, -13, 5,   3,   -13, -13, 22,  -13, -13, -13, -13, -13, 14,
    15,  -13, -13, -13, 24,  -13, -13, -13, -13, -13, -13, -13, -13, -13,
    -13, -13, -13, -13, -13, 33,  -13, -13, -13, -13, -13, -13, -13, -13,
    -13, 20,  -13, -13, 15,  -13, -13, -13, -13, -13, -13, -13};

const unsigned char JSONParser::yydefact_[] = {
    43, 7,  5,  0,  0,  45, 44, 0,  25, 6,  9,  24, 16, 0,  0,  41, 37, 39,
    0,  21, 8,  11, 3,  4,  14, 12, 10, 13, 20, 15, 35, 33, 31, 0,  1,  17,
    18, 19, 28, 30, 29, 26, 2,  0,  27, 22, 0,  23, 42, 38, 40, 36, 34, 32};

const signed char JSONParser::yypgoto_[] = {
    -13, 4,   -13, -13, 18, -13, 6, -13, -13, -12, -13,
    -13, -13, -13, -4,  -3, 1,   2, 7,   -13, -13, -13};

const signed char JSONParser::yydefgoto_[] = {-1, 43, 27, 3,  11, 4,  28, 12,
                                              29, 30, 13, 36, 37, 14, 5,  6,
                                              15, 16, 17, 33, 18, 7};

const unsigned char JSONParser::yytable_[] = {
    31, 32, 38, 19, 1,  8,  2,  1,  20, 2,  39, 40, 9,  21, 22, 23, 24,
    25, 26, 1,  10, 2,  34, 35, 41, 21, 22, 23, 24, 25, 26, 9,  42, 45,
    51, 10, 44, 46, 20, 47, 0,  42, 52, 53, 48, 49, 0,  0,  0,  0,  50};

const signed char JSONParser::yycheck_[] = {
    4,  4,  14, 0,  4, 0,  6,  4, 5,  6,  14, 14, 7,  10, 11, 12, 13,
    14, 15, 4,  15, 6, 0,  9,  0, 10, 11, 12, 13, 14, 15, 7,  8,  0,
    46, 15, 18, 33, 5, 33, -1, 8, 46, 46, 43, 43, -1, -1, -1, -1, 43};

const unsigned char JSONParser::yystos_[] = {
    0,  4,  6,  19, 21, 30, 31, 37, 0,  7,  15, 20, 23, 26, 29, 32, 33, 34,
    36, 0,  5,  10, 11, 12, 13, 14, 15, 18, 22, 24, 25, 30, 31, 35, 0,  9,
    27, 28, 25, 30, 31, 0,  8,  17, 20, 0,  17, 22, 32, 33, 34, 25, 30, 31};

const unsigned char JSONParser::yyr1_[] = {
    0,  16, 17, 18, 18, 19, 20, 21, 22, 23, 24, 24, 24, 24, 24, 25,
    26, 27, 28, 29, 30, 30, 30, 30, 31, 31, 31, 31, 32, 33, 34, 35,
    35, 35, 35, 35, 35, 36, 36, 36, 36, 36, 36, 37, 37, 37};

const unsigned char JSONParser::yyr2_[] = {
    0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 3,
    3, 2, 2, 3, 3, 2, 2, 2, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 0, 1, 1};

// YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
// First, the terminals, then, starting at \a yyntokens_, nonterminals.
const char *const JSONParser::yytname_[] = {
    "\"end of file\"", "error",        "$undefined",  "\"end of line\"",
    "\"[\"",           "\"]\"",        "\"{\"",       "\"}\"",
    "\",\"",           "\":\"",        "\"integer\"", "\"true\"",
    "\"false\"",       "\"null\"",     "\"double\"",  "\"quoted string\"",
    "$accept",         "comma",        "BOOLEAN",     "lbrace",
    "rbrace",          "lbracket",     "rbracket",    "ANY_STRING",
    "PRIMITIVE",       "primitive",    "decl",        "ASSIGNMENT",
    "assignment",      "declaration",  "array",       "object",
    "keyed_primitive", "keyed_object", "keyed_array", "array_members",
    "object_members",  "start",        YY_NULLPTR};

#if YYDEBUG
const unsigned short int JSONParser::yyrline_[] = {
    0,   115, 115, 120, 120, 122, 127, 132, 137, 143, 144, 144,
    144, 144, 144, 146, 152, 161, 162, 166, 174, 180, 186, 197,
    203, 209, 215, 227, 235, 245, 259, 273, 282, 292, 301, 311,
    316, 322, 327, 333, 338, 344, 349, 355, 356, 362};

// Print the state stack on the debug stream.
void JSONParser::yystack_print_()
{
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator i     = yystack_.begin(),
                                    i_end = yystack_.end();
         i != i_end; ++i)
        *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
}

// Report on the debug stream that the rule \a yyrule is going to be reduced.
void JSONParser::yy_reduce_print_(int yyrule)
{
    unsigned int yylno  = yyrline_[yyrule];
    int          yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1 << " (line " << yylno
               << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
        YY_SYMBOL_PRINT("   $" << yyi + 1 << " =",
                        yystack_[(yynrhs) - (yyi + 1)]);
}
#endif  // YYDEBUG

// Symbol number corresponding to token number t.
inline JSONParser::token_number_type JSONParser::yytranslate_(int t)
{
    static const token_number_type translate_table[] = {
        0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,  2,  2,  2,  2,  2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,  2,  2,  2,  2,  2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,  2,  2,  2,  2,  2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,  2,  2,  2,  2,  2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,  2,  2,  2,  2,  2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,  2,  2,  2,  2,  2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,  2,  2,  2,  2,  2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,  2,  2,  2,  2,  2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,  2,  2,  2,  2,  2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,  2,  2,  2,  2,  2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,  2,  2,  2,  2,  2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,  2,  2,  2,  2,  2, 2, 2,
        2, 2, 2, 2, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    const unsigned int      user_token_number_max_ = 270;
    const token_number_type undef_token_           = 2;

    if (static_cast<int>(t) <= yyeof_)
        return yyeof_;
    else if (static_cast<unsigned int>(t) <= user_token_number_max_)
        return translate_table[t];
    else
        return undef_token_;
}

#line 33 "JSONParser.bison"  // lalr1.cc:1167
}  // wasp
#line 1525 "JSONParser.cpp"   // lalr1.cc:1167
#line 371 "JSONParser.bison"  // lalr1.cc:1168
                              /*** Additional Code ***/

void wasp::JSONParser::error(const JSONParser::location_type &l,
                             const std::string &              m)
{
    interpreter.error_stream() << l << ": " << m << std::endl;
}
