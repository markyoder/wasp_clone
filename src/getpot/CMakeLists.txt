TRIBITS_SUBPACKAGE(getpot)


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
TRIBITS_ADD_LIBRARY(getpot
  SOURCES ${SOURCE}
  NOINSTALLHEADERS ${HEADERS}
)

#
# Add test directory
TRIBITS_ADD_TEST_DIRECTORIES(test)

INSTALL(FILES ${HEADERS} DESTINATION "include/getpot/")
TRIBITS_SUBPACKAGE_POSTPROCESS()
