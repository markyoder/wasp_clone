configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/wasp/version.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/wasp/version.h"
  )
SET( INCLUDE_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/wasp/hello.h
    ${CMAKE_CURRENT_SOURCE_DIR}/wasp/core/StringPool.h
    ${CMAKE_CURRENT_SOURCE_DIR}/wasp/core/StringPool.i.h
    ${CMAKE_CURRENT_SOURCE_DIR}/wasp/core/TokenPool.h
    ${CMAKE_CURRENT_SOURCE_DIR}/wasp/core/TokenPool.i.h
    ${CMAKE_CURRENT_SOURCE_DIR}/wasp/core/TreeNodePool.h
    ${CMAKE_CURRENT_SOURCE_DIR}/wasp/core/TreeNodePool.i.h
    ${CMAKE_CURRENT_SOURCE_DIR}/wasp/flex/FlexLexer.h
    ${CMAKE_CURRENT_BINARY_DIR}/wasp/version.h
)
INSTALL(FILES ${INCLUDE_FILES} DESTINATION include)
