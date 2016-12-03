#ifndef WASP_TOKENPOOL_H
#define WASP_TOKENPOOL_H
#include <algorithm>
#include <vector>
#include "waspcore/StringPool.h"
namespace wasp{

/**
 * @brief default_token_type_size
 */
typedef unsigned short default_token_type_size;

/**
 * @brief file_offset_type_size
 */
typedef unsigned int default_file_offset_type_size;

/**
 * @class TokenPool Memory pool and data accessor for token data
 * This data consists of the token string, type, line, and column,
 * and file offset data
 */
template<
    // size type describing token type maximum token type count
     typename token_type_size = default_token_type_size
    // size type describing maximum number of tokens
    ,typename token_index_type_size = default_token_index_type_size
    // size type describing the maximum byte file offset
    ,typename file_offset_type_size = default_file_offset_type_size
>
struct TokenPool{
public:
    TokenPool();
    TokenPool(const TokenPool<token_type_size
                    ,token_index_type_size
                    ,file_offset_type_size> & orig);
    ~TokenPool();
    /**
     * @brief str acquires the string data for the token at the given index
     * @param index the token's index for which to acquire the string data
     * @return char * of the token's string data
     */
    const char * str(token_index_type_size index)const;
    /**
     * @brief line acquires the line for the token at the given index
     * @return std::size_t the line number for which the token exists
     */
    std::size_t line(token_index_type_size token_index)const;
    /**
     * @brief column acquires the column for the token at the given index
     * @return std::size_t the column number for which the token exists
     */
    std::size_t column(token_index_type_size token_index)const;
    /**
     * @brief offset acquires byte offset for the token at the given index
     * @return file_offset_type_size the byte offset of the token
     */
    file_offset_type_size offset(token_index_type_size token_index)const;
    /**
     * @brief push appends a token to the token pool
     * @param str the token's string data
     * @param type the token's type (enumeration)
     * @param token_file_offset the token's offset into the file/stream
     */
    void push(const char * str, token_type_size type
              , file_offset_type_size token_file_offset );
    /**
     * @brief push_line appends a line to the new line buffer
     * @param line_file_offset byte offset into the file/stream for the newline
     */
    void push_line(file_offset_type_size line_file_offset);
    /**
     * @brief pop_token removes the last token
     */
    void pop_token(){m_tokens.pop_back();}
    /**
     * @brief pop_line removes the last line
     */
    void pop_line(){m_line_offsets.pop_back();}

    // TODO - add pop(file_offset_type_size) to allow
    // popping both line and token info together

    /**
     * @brief size the number of tokens in this token pool
     * @return std::size_t the token count
     */
    std::size_t size()const{return m_tokens.size();}

    /**
     * @brief type acquire the type of the token at the given index
     * @return the type of the token at the given index
     */
    token_type_size type(token_index_type_size token_index)const;

    /**
     * @brief line_count the number of new lines stored in this pool
     * @return the new line count
     */
    std::size_t line_count()const{return m_line_offsets.size();}
    /**
     * @brief line_offset acquire the byte offset of the line at the given index
     * @param line_index the index of the line for which the offset is desired
     * @return the byte offset of the line
     */
    file_offset_type_size line_offset(token_index_type_size line_index)const;
private:
    /**
     * @brief m_strings the token string data pool
     */
    StringPool<token_index_type_size> m_strings;
    /**
     * @brief The Token struct convenience data structure
     */
    struct Token{
        Token(token_type_size type
              ,file_offset_type_size offset)
            :m_token_type(type),m_token_file_offset(offset){}
        // E..g, float, int, string...
        token_type_size m_token_type;
        // token byte offset into file
        file_offset_type_size m_token_file_offset;
        // new line byte offset into file
        // NOT NEEDED AS IT CAN BE COMPUTED
//        file_offset_type_size m_new_line_file_offset;
    };
    /**
     * @brief m_tokens all accumulated tokens
     */
    std::vector<Token> m_tokens;
    /**
     * @brief m_line_offsets byte offsets of a line
     */
    std::vector<file_offset_type_size> m_line_offsets;

};
#include "waspcore/TokenPool.i.h"
} // end of namespace
#endif
