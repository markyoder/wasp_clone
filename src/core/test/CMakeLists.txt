include_directories ("${CMAKE_CURRENT_SOURCE_DIR}")
SET( TESTS 
    tstStringPool.cpp
    tstTokenPool.cpp
    tstTreeNodePool.cpp
)
foreach( TEST ${TESTS} )
    message("Adding test ${TEST}")
    get_filename_component(name ${TEST} NAME_WE)
    message("Test name  ${name}")

    add_executable( ${name} ${TEST} )
    target_link_libraries( ${name} wasp_core )
    add_test( ${name} ${name} ) 
endforeach()
