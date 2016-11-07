#ifndef WASP_WASP_NODE_H
#define WASP_WASP_NODE_H
namespace wasp{
    /**
     * @brief The NODE enum core node types used by wasp support processors
     */
    enum NODE : char {
        DOCUMENT_ROOT
        , DECL
        , TERM
        , INT
        , REAL
        , KEY
        , ASSIGN
        , QUOTE
        , STRING
        , VALUE
        , COMMENT
        , KEYED_VALUE
        , OBJECT_DECL
        , OBJECT_TERM
        , OBJECT
        , COMMA
        , PLUS
        , MINUS
        , MULTIPLY
        , DIVIDE
        , GTE
        , GT
        , LTE
        , LT
        , NEQ
        , EQ
        , AND
        , OR
        , BANG // !
        , UNARY_MINUS
        , UNARY_NOT
        , EXPONENT
        , LPAREN
        , RPAREN
        , PARENTHESIS
        , FUNCTION
        , SUB_OBJECT_DECL
        , LBRACKET
        , RBRACKET
        , SUB_OBJECT_TERM
        , SUB_OBJECT
        , DOT_SLASH
     };
}
#endif
