# Core Package
The core package of WASP provides the foundation for text processing.

A primary mission of WASP is to capture information in a manner that facilitate reconstituting a users' text file. 

This information is captured in two primary stages which are the lexing and parsing of the text files. 
Lexical analysis processes the text file by recognizing patterns of text and producing a `token` that encapsulates information pertaining to this pattern.

The parser recognizes patterns of tokens and constructs a parse tree for future examination. 


Typically, all whitespace are not captured in the parse tree as they can be deduced and reconstituted upon request. 

## Core Parts
The primary parts of wasp core are:

1. StringPool - provides contiguous string storage. All strings are stored, null-terminated, in a single data container.
2. TokenPool - provides contiguous token storage. Tokens consist of string data, a token type, and a file byte offset. 
    * An index is used that identifies the location in the StringPool at which the data resides. 
    * The token pool stores new line offsets.
    * The file byte offset is used to compute line and column with the assistance of the new line offset.
3. TreeNodePool - manages TreeNodes which consist of a node name, type, and child indicates. 
    * Uses StringPool for contiguous node name storage.
    * Uses TokenPool to store all leaf node token information.
4. Interpreter - base class providing boilerplate lex and parse logic
    * Contains core token and node construction logic for lexer and parser to use.
5. Format - utility methods for formatting values - safe printf to facilitate [expression engine](/waspexpr/README.md) and [halite](/wasphalite/README.md).
6. wasp_node - central location for node and token type enumeration.
7. Object - generic type data structure to facilitate typed-data access to hierarchical data. 
    * Facilitates Halite data-driven capabilities.
    
## String Pool
The string pool consists of two members, 1) a vector of chars, 2) a vector of indices indicating string starts.

In this way, the string data that is consumed from a text file is reasonable maintained and size not inflated. 

In a benchmark of one application's input where the token's mathematical mode was 3 characters, with a mean of 4, 
using std::string produces on average ~28+ byte overhead per token. Using the StringPool facilitated the memory consolidation. 

