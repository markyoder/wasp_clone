include_directories ("${PROJECT_SOURCE_DIR}/include")
include_directories ("${PROJECT_BINARY_DIR}/include") # Configured files, e.g. VERSION

# add the executable
add_executable(Test test.cpp)
# link the executable
target_link_libraries (Test wasp_core)
# install the executable
#INSTALL( TARGETS Test DESTINATION bin )
