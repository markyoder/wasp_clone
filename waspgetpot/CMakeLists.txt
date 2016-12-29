INCLUDE(WaspAddCompilerFlags)

TRIBITS_SUBPACKAGE(getpot)

WASP_ADD_CXX_FLAGS(
  "-Wno-deprecated-register"
)


SET(SOURCE
GetPotLexer.cpp
GetPotParser.cpp
GetPotInterpreter.cpp
)

SET(HEADERS
GetPotLexer.h
GetPotParser.hpp
GetPotInterpreter.h
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

TRIBITS_ADD_EXECUTABLE(getpotls
  SOURCES ListGetPot.cpp
  NOEXEPREFIX
  NOEXESUFFIX
  INSTALLABLE
)

#
# Add test directory
TRIBITS_ADD_TEST_DIRECTORIES(test)

INSTALL(FILES ${HEADERS} DESTINATION "include/waspgetpot/")
TRIBITS_SUBPACKAGE_POSTPROCESS()
