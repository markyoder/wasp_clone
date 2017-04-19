# Requirements
* C/CXX compiler.
** GCC-4.8
** LLVM-7.0.2
* Git
* CMake-2.8.12.2.
* Python-2.7

# Getting Started
* You will need to save your ssh-key in [code-int.ornl.gov](https://code-int.ornl.gov/profile/keys).
* Clone wasp `git clone git@code-int.ornl.gov:lefebvre/wasp.git ~/wasp`
* Change directory into wasp `cd ~/wasp`
* Clone TriBITS `git clone https://github.com/lefebvre/TriBITS.git TriBITS` [TriBITS documentation](https://tribits.org/doc/TribitsDevelopersGuide.html)
* Clone extra repos `./TriBITS/tribits/ci_support/clone_extra_repos.py`
* Create a build directory `mkdir -p ~/build/wasp`
* Change into the build `cd ~/build/wasp`
* Create a configuration script in ~/build/. Lets call is ../configure.sh(linux)

```
#!/bin/bash
# Linux bash file example
rm -rf CMake*
cmake \
 -D CMAKE_BUILD_TYPE:STRING=RELEASE \
 -D wasp_ENABLE_ALL_PACKAGES:BOOL=ON \
 -D wasp_ENABLE_TESTS:BOOL=ON \
 -D CMAKE_INSTALL_PREFIX=`pwd`/install \
 -G "Unix Makefiles" \
 ~/wasp
```
E.g., to a script that will enable getpot
```
#!/bin/bash
# Linux bash file example
rm -rf CMake*
cmake \
 -D CMAKE_BUILD_TYPE:STRING=RELEASE \
 -D wasp_ENABLE_waspgetpot=ON \
 -D wasp_ENABLE_TESTS:BOOL=ON \
 -D CMAKE_INSTALL_PREFIX=`pwd`/install \
 -G "Unix Makefiles" \
 ~/wasp
```

* Invoke configure script in the build directory.
`../configure.sh or ..\configure.bat`
  * I place the configure script in the build directory as opposed to the build/wasp directory because it allows me to delete the build/wasp
directory without removing my script.



# Package Overview 
The Workbench Analysis Sequence Processor (WASP) is intended to streamline lexing, parsing, access, validation, and analysis of ascii text files.

The foundation of WASP resides on the parse tree data structure where each node in the tree represents syntax of the input document. Nodes can parent nodes with children. 
Nodes that have no children are known as terminal or leaf nodes and represent Tokens (string, number, delimiter, etc.) in the text file.

The fast lexical analyzer generator (flex - https://www.gnu.org/software/flex/) and GNU Bison parser generator (https://www.gnu.org/software/bison/) are extensively used for lexing and parsing.

## Components
WASP is composed of the following primary components:
1. __Core__ - the waspcore package contains most necessary data structures and interface classes needed to interact with text files. 
    * StringPool - a string storage optimization class where ascii data are stored in a contiguous memory block where each string is null terminated and indexed.
    * TokenPool - a token/word storage optimization class where Token information (string data via StringPool, file location) are stored. Line and column are calculated on-the-fly via token file offset and file line offset.
    * TreeNodePool - a TreeNode storage class where TreeNode information (token, name, parent, type, children, etc) are stored. 
    * Interpreter - an interface and highlevel implementation class which facilitates specific grammar lexer and parser state information and parse tree storage
    * wasp_node - enumerated token/node types used to aid in identifying context and intent. 
    * utils - contains utility functions useful for string processing and tree visiting.
    * wasp_bug - contains software quality assurance and development aids that can be preprocessed out of deployments.
        * design by contract - insist, require, ensure, assert, check, remember.
        * timing - 3 levels of timers for code performance monitoring. 1-3, highest to lowest.
        * debug lines - set of macros that allow printing debug information to screen.
2. __Expr__ - the waspexpr package contains lexer, parser, and evaluation logic for mathematical expressions.
    * Basic mathematical operators - multiplication '*', division '/', addition '+', subtraction '-', boolean ('<','<=','==','!=', etc), and exponentiation '\^'.
    * Scalar variable assignment, reference, and creation - known variable can be referenced and updated, or new variables created during expression evaluation.
    * Functions - _not yet implemented_. 
    * Vector and map assignment, reference, and creation - _not yet implemented_.
3. __GetPot__ - the waspgetpot package contains lexer, parser, and tree node view for the getpot grammar (http://getpot.sourceforge.net/) as needed by MOOSE 
4. [__HIVE__](/wasphive/README.md) - the Hierarchical Input Validation Engine contains algorithms for validating a parse tree using a document schema/definition file.
    * Flexible scalar and referential rules - supports element occurrence, value, child uniqueness and choice, existence, sum, predicated sum, etc.  
5. __JSON__ - the waspjson package contains lexer, and parser for the JSON grammar (http://www.json.org/) 
6. [__SIREN__](/waspsiren/README.md) - the Sequence Input Retrieval ENgine (SIREN) contains lexer, parser, and evaluation logic for tree node lookup.
    * Flexible tree node lookup mechanism - supports absolute and relative wild-carded named and value or index -predicated node path lookup.
7. [__SON__](/waspson/README.md) - the Standard Object Notation (SON) - waspson package contains the lexer, parser, and tree node view for the son grammar.
    * Flexible, structured, input entry mechanism - supports Objects, Arrays, and keyed values. Also supports identified objects, arrays, and keyed values.
8. [__HALITE__](/wasphalite/README.md) - the HierarchicAL Input Template Expansion engine provides a data-driven means of expanding patterned input.
    * Supports attribute and expression evaluations.
    * Supports template imports.
    * Supports conditional action blocks.
9. __Utils__ - the wasputils package contains executable utilities for listing/viewing, selecting, validating, and transforming WASP supported grammars.
    * List - lists paths to each file element.
    * Select - allows using SIREN expression to select pieces of input.
    * Valid - validates a given text file with a given document definition/schema.
    * XML - translates a given text file into XML with data and location information.
    * TODO - not all grammars support all utilities yet.
