include_directories ("${PROJECT_SOURCE_DIR}/include")
include_directories ("${PROJECT_BINARY_DIR}/include") # Configured files, e.g. VERSION
SET( SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/StringPool.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/TokenPool.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/TreeNodePool.cpp"
)
ADD_LIBRARY(wasp_core SHARED  
    ${SOURCES}
    )


# Set library's runtime search path on OSX
IF(APPLE)
    SET_TARGET_PROPERTIES( wasp_core PROPERTIES INSTALL_RPATH "@loader_path/." )
ENDIF()
# todo install

INSTALL( TARGETS wasp_core
     RUNTIME DESTINATION bin
     LIBRARY DESTINATION lib)

IF(WASP_ENABLE_TESTS)
    ADD_SUBDIRECTORY(test)
ENDIF()

