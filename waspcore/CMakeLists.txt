TRIBITS_SUBPACKAGE(core)

TRIBITS_CONFIGURE_FILE(version.h)

SET(SOURCE
Interpreter.cpp
StringPool.cpp
TokenPool.cpp
TreeNodePool.cpp
)

SET(HEADERS
FlexLexer.h
Interpreter.h
Interpreter.i.h
StringPool.h
StringPool.i.h
TokenPool.h
TokenPool.i.h
TreeNodePool.h
TreeNodePool.i.h
wasp_node.h
)

#
# Add library
TRIBITS_ADD_LIBRARY(waspcore
  SOURCES ${SOURCE}
  NOINSTALLHEADERS ${HEADERS}
)

#
# Add test directory
TRIBITS_ADD_TEST_DIRECTORIES(test)

INSTALL(FILES ${HEADERS} DESTINATION "include/waspcore/")
TRIBITS_SUBPACKAGE_POSTPROCESS()
