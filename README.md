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

## Components
WASP is composed of the following primary components:
1. __Core__ - the waspcore package contains most necessary data structures and interface classes needed to interact with text files. 
    * StringPool - a string storage optimization class where ascii data are stored in a contiguous memory block where each string is null terminated and indexed.
    * TokenPool - a token/word storage optimization class where Token information (string data via StringPool, file location) are stored. Line and column are calculated on-the-fly via token file offset and file line offset.
    * TreeNodePool - a TreeNode
    * Interpreter - an interface and highlevel implementation class which facilitates specific grammar lexer and parser state information and parse tree storage
