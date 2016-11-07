include_directories ("${PROJECT_SOURCE_DIR}/src")
include_directories ("${PROJECT_SOURCE_DIR}/include")
include_directories ("${PROJECT_BINARY_DIR}/include") # Configured files, e.g. VERSION
SET( SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/GetPotLexer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/GetPotParser.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/GetPotInterpreter.cpp"
)
ADD_LIBRARY(wasp_getpot SHARED
    ${SOURCES}
    )
target_link_libraries (wasp_getpot wasp_core)

INSTALL( TARGETS wasp_getpot
     RUNTIME DESTINATION bin
     LIBRARY DESTINATION lib)

# add the GetPot list executable
add_executable(ListGetPot ListGetPot.cpp)

# link the executable
target_link_libraries (ListGetPot wasp_getpot wasp_core)

# todo install
INSTALL( TARGETS ListGetPot DESTINATION bin )

IF(WASP_ENABLE_TESTS)
    ADD_SUBDIRECTORY(test)
ENDIF()
