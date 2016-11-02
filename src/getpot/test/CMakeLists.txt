include_directories ("${CMAKE_CURRENT_SOURCE_DIR}")
include_directories ("${PROJECT_SOURCE_DIR}/src/core/test") # test harness
SET( TESTS 
    tstGetPot.cpp
)
foreach( TEST ${TESTS} )
    message("Adding test ${TEST}")
    get_filename_component(name ${TEST} NAME_WE)
    message("Test name  ${name}")

    add_executable( ${name} ${TEST} )
    target_link_libraries( ${name} wasp_getpot wasp_core )
    add_test( ${name} ${name} ) 
endforeach()
