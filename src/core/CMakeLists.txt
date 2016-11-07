TRIBITS_SUBPACKAGE(core)


SET(SOURCE
StringPool.cpp
TokenPool.cpp
TreeNodePool.cpp
)

SET(HEADERS
FlexLexer.h
wasp_node.h
StringPool.h
StringPool.i.h
TokenPool.h
TokenPool.i.h
TreeNodePool.h
TreeNodePool.i.h
)

#
# Add library
TRIBITS_ADD_LIBRARY(core
  SOURCES ${SOURCE}
  NOINSTALLHEADERS ${HEADERS}
)

#
# Add test directory
TRIBITS_ADD_TEST_DIRECTORIES(test)

INSTALL(FILES ${HEADERS} DESTINATION "include/wasp/core/")
TRIBITS_SUBPACKAGE_POSTPROCESS()
