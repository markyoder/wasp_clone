##---------------------------------------------------------------------------##
## Standard Object Notation (SON)/CMakeLists.txt
## Robert A. Lefebvre
## Wednesday September 25 12:41 2013
##---------------------------------------------------------------------------##
## Copyright (C) 2011 Oak Ridge National Laboratory, UT-Battelle, LLC.
##---------------------------------------------------------------------------##
## CMAKE for SON
##---------------------------------------------------------------------------##

INCLUDE(WaspAddCompilerFlags)


TRIBITS_SUBPACKAGE(son)
SET_DEFAULT(DBC 0)
SET_DEFAULT(TIMING 0)
SET_DEFAULT(DEBUG_OUTPUT 0)
TRIBITS_CONFIGURE_FILE(son_config.h)
##---------------------------------------------------------------------------##
## INCLUDES

##---------------------------------------------------------------------------##
## HEADER AND SOURCE FILES
##---------------------------------------------------------------------------##

WASP_ADD_CXX_FLAGS(
  "-Wno-deprecated-register"
)

# C/C++ headers
FILE(GLOB HEADERS *.h *.hh *.hpp *.lex *.bison
    "${CMAKE_CURRENT_BINARY_DIR}/*.h"
    )

# c++ files
SET(SOURCES
SONInterpreter.cpp
SONLexer.cpp
SONParser.cpp
)

##
## Introspection for flex and bison
##
FIND_PROGRAM(FLEX_PATH NAME flex HINTS ENV PATH)
IF(FLEX_PATH STREQUAL "FLEX_PATH-NOTFOUND")
   MESSAGE(WARNING "Flex not found. Generating/updating lexer disabled.")
ELSE()
   MESSAGE(STATUS "Found flex : '${FLEX_PATH}'")
   ADD_CUSTOM_TARGET(waspson_lexer
       COMMAND ${FLEX_PATH} -Ca -v ${CMAKE_CURRENT_SOURCE_DIR}/SONLexer.lex
       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
       DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/SONLexer.lex")
ENDIF()

FIND_PROGRAM(SED_EXE_PATH NAME sed HINTS ENV PATH)
IF(SED_EXE_PATH STREQUAL "SED_EXE_PATH-NOTFOUND")
   MESSAGE(WARNING "sed not found. Fixing lexer include disabled.")
ELSE()
   MESSAGE(STATUS "Found sed: '${SED_EXE_PATH}'")
   ADD_CUSTOM_TARGET(waspson_sed_lexer
       COMMAND ${SED_EXE_PATH} -i '' 's/\#include <FlexLexer.h>/\#include \"waspcore\/FlexLexer.h\"/' SONLexer.cpp
       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
       DEPENDS waspson_lexer "${CMAKE_CURRENT_SOURCE_DIR}/SONLexer.cpp"
   )
ENDIF()

FIND_PROGRAM(BISON_PATH NAME bison HINTS ENV PATH)
IF(BISON_PATH STREQUAL "BISON_PATH-NOTFOUND")
   MESSAGE(WARNING "Bison not found. Generating/updating parser disabled.")
ELSE()
   MESSAGE(STATUS "Found bison : '${BISON_PATH}'")
   ADD_CUSTOM_TARGET(waspson_parser
       COMMAND ${BISON_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/SONParser.bison --report=state --report=lookahead --report=solved -g
       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
       DEPENDS waspson_sed_lexer waspson_lexer "${CMAKE_CURRENT_SOURCE_DIR}/SONParser.bison")
ENDIF()
##---------------------------------------------------------------------------##
## PACKAGE TARGETS AND INSTALL
##---------------------------------------------------------------------------##

TRIBITS_ADD_LIBRARY(
  waspson
  SOURCES ${SOURCES}
  NOINSTALLHEADERS ${HEADERS})

INSTALL(FILES
  ${HEADERS}
  DESTINATION
  include/waspson)

TRIBITS_ADD_EXECUTABLE(sonls
  NOEXEPREFIX
  NOEXESUFFIX
  SOURCES ListSON.cpp
  INSTALLABLE
)
#
# Add test directory for this package
#
TRIBITS_ADD_TEST_DIRECTORIES(test)

##---------------------------------------------------------------------------##
##                   end of SON/CMakeLists.txt
##---------------------------------------------------------------------------##
TRIBITS_SUBPACKAGE_POSTPROCESS()
