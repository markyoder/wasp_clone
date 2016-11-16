#ifndef WASP_WASP_NODE_H
#define WASP_WASP_NODE_H
namespace wasp{
    /**
     * @brief The NODE enum core node types used by wasp support processors
     */
    enum NODE : char {
          UNKNOWN
        , DOCUMENT_ROOT
        , DECL
        , TERM
        , INT
        , REAL
        , KEY
        , ASSIGN
        , QUOTE
        , STRING
        , QUOTED_STRING
        , VALUE
        , COMMENT
        , KEYED_VALUE
        , OBJECT_DECL
        , OBJECT_TERM
        , OBJECT
        , WASP_COMMA // ,
        , PLUS  // +
        , MINUS // -
        , MULTIPLY // *
        , DIVIDE // /
        , GTE    // >=
        , GT     // >
        , LTE    // <=
        , LT     // >
        , NEQ    // !=
        , EQ     // ==
        , WASP_AND    // && // disambiguated for cross-platform macro avoidance
        , WASP_OR     // || // disambiguated for cross-platform macro avoidance
        , BANG // !
        , UNARY_MINUS // -x
        , UNARY_NOT   // !x
        , EXPONENT    // ^
        , LPAREN      // (
        , RPAREN      // )
        , LBRACE      // {
        , RBRACE      // }
        , PARENTHESIS
        , FUNCTION
        , MATH_EXPRESSION
        , SUB_OBJECT_DECL
        , LBRACKET    // [
        , RBRACKET    // ]
        , SUB_OBJECT_TERM
        , SUB_OBJECT
        , DOT_SLASH
        , WASP_TRUE  // disambiguated for cross-platform macro avoidance
        , WASP_FALSE // disambiguated for cross-platform macro avoidance
        , FILL_EXPR
        , WASP_TICK // `
        , IDENTIFIER
        , ARRAY // sequence of data
        , EXECUTION_UNIT_END
        , EXECUTION_UNIT_START
        , EXECUTION_UNIT
     };
}
#endif
