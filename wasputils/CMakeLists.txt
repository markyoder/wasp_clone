##---------------------------------------------------------------------------##
## Utilities/CMakeLists.txt
## Robert A. Lefebvre
## Monday February 6 2017
##---------------------------------------------------------------------------##
## Copyright (C) 2017 Oak Ridge National Laboratory, UT-Battelle, LLC.
##---------------------------------------------------------------------------##
## CMAKE for utils 
##---------------------------------------------------------------------------##


TRIBITS_SUBPACKAGE(utils)
SET_DEFAULT(DBC 0)
SET_DEFAULT(TIMING 0)
SET_DEFAULT(DEBUG_OUTPUT 0)
##---------------------------------------------------------------------------##
## INCLUDES

##---------------------------------------------------------------------------##
## HEADER AND SOURCE FILES
##---------------------------------------------------------------------------##

# C/C++ headers
FILE(GLOB HEADERS *.h *.hh *.hpp 
    "${CMAKE_CURRENT_BINARY_DIR}/*.h"
    )

##---------------------------------------------------------------------------##
## PACKAGE TARGETS AND INSTALL
##---------------------------------------------------------------------------##

TRIBITS_ADD_EXECUTABLE(getpotlist
  SOURCES getpotlist.cpp
  NOEXEPREFIX
  NOEXESUFFIX
  INSTALLABLE
)
##---------------------------------------------------------------------------##
##                   end of utils/CMakeLists.txt
##---------------------------------------------------------------------------##
TRIBITS_SUBPACKAGE_POSTPROCESS()
