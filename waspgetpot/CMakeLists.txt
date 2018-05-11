INCLUDE(WaspAddCompilerFlags)
INCLUDE(WaspFlexAndBison)

TRIBITS_SUBPACKAGE(getpot)

WASP_ADD_CXX_FLAGS(
  "-Wno-deprecated-register"
  "-wd4018"
)

WASP_FLEX_AND_BISON(
  FLEX_FILE GetPot.lex
  FLEX_OPTIONS -Ca -v
  SED_OPTIONS 's@\#include <FlexLexer.h>@\#include \"waspcore/FlexLexer.h\"@' GetPotLexer.cpp
  BISON_FILE GetPot.bison
  BISON_OPTIONS --report=state --report=lookahead
)

SET(SOURCE
GetPotLexer.cpp
GetPotParser.cpp
GetPotNodeView.cpp
)

SET(HEADERS
GetPotLexer.h
GetPotParser.hpp
GetPotInterpreter.h
GetPotInterpreter.i.h
GetPotNodeView.h
GetPotNodeView.i.h
location.hh
position.hh
stack.hh
GetPot.lex
GetPot.bison
)

#
# Add library
TRIBITS_ADD_LIBRARY(waspgetpot
  SOURCES ${SOURCE}
  NOINSTALLHEADERS ${HEADERS}
)

#
# Add test directory
TRIBITS_ADD_TEST_DIRECTORIES(test)

INSTALL(FILES ${HEADERS} DESTINATION "include/waspgetpot/")
TRIBITS_SUBPACKAGE_POSTPROCESS()
