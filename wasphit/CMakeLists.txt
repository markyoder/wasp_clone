INCLUDE(WaspAddCompilerFlags)
INCLUDE(WaspFlexAndBison)

TRIBITS_SUBPACKAGE(hit)

WASP_ADD_CXX_FLAGS(
  "-Wno-deprecated-register"
  "-wd4018"
)

WASP_FLEX_AND_BISON(
  FLEX_FILE HIT.lex
  FLEX_OPTIONS -Ca -v
  SED_OPTIONS 's@\#include <FlexLexer.h>@\#include \"waspcore/FlexLexer.h\"@' HITLexer.cpp
  BISON_FILE HIT.bison
  BISON_OPTIONS --report=state --report=lookahead
)

SET(SOURCE
HITLexer.cpp
HITParser.cpp
HITNodeView.cpp
)

SET(HEADERS
HITLexer.h
HITParser.hpp
HITInterpreter.h
HITInterpreter.i.h
HITNodeView.h
HITNodeView.i.h
HIT.lex
HIT.bison
)

#
# Add library
TRIBITS_ADD_LIBRARY(wasphit
  SOURCES ${SOURCE}
  NOINSTALLHEADERS ${HEADERS}
)
if(NOT DEFINED DISABLE_HIT_TYPE_PROMOTION)
  set(DISABLE_HIT_TYPE_PROMOTION 1)
endif()
target_compile_definitions(wasphit PRIVATE DISABLE_HIT_TYPE_PROMOTION=$<BOOL:${DISABLE_HIT_TYPE_PROMOTION}>)

#
# Add binary directory includes to wasphit target
#
target_include_directories(wasphit PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>  
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>  
    $<INSTALL_INTERFACE:include/wasphit>
)

#
# Add test directory
TRIBITS_ADD_TEST_DIRECTORIES(test)

INSTALL(FILES ${HEADERS} DESTINATION "include/wasphit/")
TRIBITS_SUBPACKAGE_POSTPROCESS()
