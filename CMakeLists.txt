################################################################################
#                                                                              #
#             WASP   TriBITS Project and Package CMakeLists.txt File           #
#             Workbench Analysis Sequence Processor                            #
################################################################################
IF(NOT DEFINED WASP_DEBUG_OUTPUT)
   SET(WASP_DEBUG_OUTPUT 0 CACHE STRING "Display debug output.")
ENDIF()
IF(WASP_DEBUG_OUTPUT)
   ADD_DEFINITIONS("-DWASP_DEBUG_OUTPUT=${WASP_DEBUG_OUTPUT}")
ENDIF()

IF(NOT DEFINED WASP_TIMING)
   SET(WASP_TIMING 0 CACHE STRING "Timing setting.")
ENDIF()
IF(WASP_TIMING)
   ADD_DEFINITIONS("-DWASP_TIMING=${WASP_TIMING}")
ENDIF()

IF(NOT DEFINED WASP_DBC)
   SET(WASP_DBC 0 CACHE STRING "DBC setting.")
ENDIF()
IF(WASP_DBC)
   ADD_DEFINITIONS("-DWASP_DBC=${WASP_DBC}")
ENDIF()

IF (NOT TRIBITS_PROCESSING_PACKAGE)
  # This CMakeLists.txt file is being processed as the wasp TriBITS projects's base
  # CMakeLists.txt file!  (See comments at bottom of this file.)
  CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12.2 FATAL_ERROR)
  INCLUDE("${CMAKE_CURRENT_SOURCE_DIR}/ProjectName.cmake")
  PROJECT(${PROJECT_NAME} NONE)
  # enable C++11 by default
  SET(wasp_ENABLE_CXX11 ON CACHE BOOL "Compile using the C++11 standard" FORCE)
  # disable generating HTML dependencies webpage and xml files
  SET(${PROJECT_NAME}_DEPS_XML_OUTPUT_FILE OFF CACHE BOOL "")
  # disable TriBITS export system to save time configuring
  SET(${PROJECT_NAME}_ENABLE_INSTALL_CMAKE_CONFIG_FILES OFF CACHE BOOL "")
  SET(${PROJECT_NAME}_ENABLE_EXPORT_MAKEFILES OFF CACHE BOOL "")
  SET(${PROJECT_NAME}_TRIBITS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/TriBITS/tribits" CACHE PATH "")
  INCLUDE("${${PROJECT_NAME}_TRIBITS_DIR}/TriBITS.cmake")
  SET(${PROJECT_NAME}_ENABLE_TESTS ON CACHE BOOL "Enable tests by default.")
  # default fortran support off
  IF(NOT ${PROJECT_NAME}_ENABLE_Fortran)
     SET(${PROJECT_NAME}_ENABLE_Fortran OFF CACHE BOOL "Enable fortran support")
  ENDIF()
  # default MPI support off
  IF(NOT TPL_ENABLE_MPI)
    SET(TPL_ENABLE_MPI OFF CACHE BOOL "Enable MPI support")
  ENDIF()

  TRIBITS_PROJECT_ENABLE_ALL()
ELSE()
  # This CMakeLists.txt file is being processed as the TriBITS package file.
  INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
  # include binary directory for configured includes
  INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
  TRIBITS_PACKAGE_DECL(wasp)
  #
  # Process subpackages
  #
  TRIBITS_PROCESS_SUBPACKAGES()
  TRIBITS_PACKAGE_POSTPROCESS()
ENDIF()

# NOTE: In order to allow the `wasp/` directory to be both a TriBITS
# package (for inclusion in other TriBITS projects) and to be a TriBITS
# project itself, you only have to put in a simple if statement in this
# top-level CMakeLists.txt file.  That is all!
