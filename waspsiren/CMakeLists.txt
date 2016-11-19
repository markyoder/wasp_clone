TRIBITS_SUBPACKAGE(siren)

SET(SOURCE
SIRENLexer.cpp
SIRENParser.cpp
SIRENInterpreter.cpp
)

# C/C++ headers
FILE(GLOB HEADERS *.h *.hh *.hpp *.lex *.bison
    "${CMAKE_CURRENT_BINARY_DIR}/*.h"
    )

#
# Add library
TRIBITS_ADD_LIBRARY(waspsiren
  SOURCES ${SOURCE}
  NOINSTALLHEADERS ${HEADERS}
)

#
# Add test directory
TRIBITS_ADD_TEST_DIRECTORIES(test)

INSTALL(FILES ${HEADERS} DESTINATION "include/waspsiren/")
TRIBITS_SUBPACKAGE_POSTPROCESS()
