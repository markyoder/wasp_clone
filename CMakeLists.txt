##---------------------------------------------------------------------------##
## WASP/CMakeLists.txt
## Robert Alexander Lefebvre
## Saturday Oct 29 17:22:0 2016
##---------------------------------------------------------------------------##
## Copyright (C) 2016 Oak Ridge National Laboratory, UT-Battelle, LLC.
##---------------------------------------------------------------------------##
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12.2)

PROJECT(WASP)
# The version number.
set (WASP_VERSION_MAJOR 0)
set (WASP_VERSION_MINOR 0)
set (WASP_VERSION_MICRO 1)


ENABLE_TESTING()

OPTION(WASP_ENABLE_TESTS "Enable tests" ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wshadow")

##---------------------------------------------------------------------------##
## ADDITIONAL SUBDIRECTORIES AND INSTALLS
##---------------------------------------------------------------------------##
# Build the different applications
ADD_SUBDIRECTORY( src )

#install the includes
ADD_SUBDIRECTORY( include )
##---------------------------------------------------------------------------##
## end of WASP/CMakelists.txt
##---------------------------------------------------------------------------##
