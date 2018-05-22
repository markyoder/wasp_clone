TRIBITS_SUBPACKAGE(py)

file(GLOB MODULE  ${CMAKE_CURRENT_SOURCE_DIR}/*.py )

# Copy module and test directory into build tree for python testing
file(COPY ${MODULE} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY "test"  DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY "drive"  DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


IF(PYTHON_EXECUTABLE)
  ADD_TEST( tstWaspPy python -m unittest discover -v )
ENDIF()

#
# Add test directory
TRIBITS_ADD_TEST_DIRECTORIES(test)

# Install the python module
install(DIRECTORY .
        DESTINATION "wasppy"
        PATTERN "./*.py"
)
TRIBITS_SUBPACKAGE_POSTPROCESS()
