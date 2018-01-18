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

IF ( wasp_ENABLE_wasphalite  AND wasp_ENABLE_waspjson  )
    TRIBITS_ADD_EXECUTABLE(halite
      SOURCES halite.cpp
      NOEXEPREFIX
      NOEXESUFFIX
      INSTALLABLE
    )
    TRIBITS_ADD_EXECUTABLE(halitelist
      SOURCES halitelist.cpp
      NOEXEPREFIX
      NOEXESUFFIX
      INSTALLABLE
    )
ENDIF()

IF ( wasp_ENABLE_waspddi )
    TRIBITS_ADD_EXECUTABLE(ddilist
      SOURCES ddilist.cpp
      NOEXEPREFIX
      NOEXESUFFIX
      INSTALLABLE
    )
    TRIBITS_ADD_EXECUTABLE(ddixml
      SOURCES ddixml.cpp
      NOEXEPREFIX
      NOEXESUFFIX
      INSTALLABLE
    )
    TRIBITS_ADD_EXECUTABLE(ddivalid
      SOURCES ddivalid.cpp
      NOEXEPREFIX
      NOEXESUFFIX
      INSTALLABLE
    )
    TRIBITS_ADD_EXECUTABLE(ddiselect
      SOURCES ddiselect.cpp
      NOEXEPREFIX
      NOEXESUFFIX
      INSTALLABLE
    )
ENDIF()
IF ( wasp_ENABLE_waspgetpot )
    TRIBITS_ADD_EXECUTABLE(getpotlist
      SOURCES getpotlist.cpp
      NOEXEPREFIX
      NOEXESUFFIX
      INSTALLABLE
    )
    TRIBITS_ADD_EXECUTABLE(getpotxml
      SOURCES getpotxml.cpp
      NOEXEPREFIX
      NOEXESUFFIX
      INSTALLABLE
    )
    TRIBITS_ADD_EXECUTABLE(getpotvalid
      SOURCES getpotvalid.cpp
      NOEXEPREFIX
      NOEXESUFFIX
      INSTALLABLE
    )
    TRIBITS_ADD_EXECUTABLE(getpotselect
      SOURCES getpotselect.cpp
      NOEXEPREFIX
      NOEXESUFFIX
      INSTALLABLE
    )
ENDIF()
IF ( wasp_ENABLE_waspson )
    TRIBITS_ADD_EXECUTABLE(sonlist
      SOURCES sonlist.cpp
      NOEXEPREFIX
      NOEXESUFFIX
      INSTALLABLE
    )
    TRIBITS_ADD_EXECUTABLE(sonvalid
      SOURCES sonvalid.cpp
      NOEXEPREFIX
      NOEXESUFFIX
      INSTALLABLE
    )
    TRIBITS_ADD_EXECUTABLE(sonselect
      SOURCES sonselect.cpp
      NOEXEPREFIX
      NOEXESUFFIX
      INSTALLABLE
    )
    TRIBITS_ADD_EXECUTABLE(sonxml
      SOURCES sonxml.cpp
      NOEXEPREFIX
      NOEXESUFFIX
      INSTALLABLE
    )
    TRIBITS_ADD_EXECUTABLE(sonvalidxml
      SOURCES sonvalidxml.cpp
      NOEXEPREFIX
      NOEXESUFFIX
      INSTALLABLE
    )
    TRIBITS_ADD_EXECUTABLE(sonschemaskel
      SOURCES sonschemaskel.cpp
      NOEXEPREFIX
      NOEXESUFFIX
      INSTALLABLE
    )
ENDIF()
IF ( wasp_ENABLE_waspjson )
    TRIBITS_ADD_EXECUTABLE(jsonlist
      SOURCES jsonlist.cpp
      NOEXEPREFIX
      NOEXESUFFIX
      INSTALLABLE
    )
    TRIBITS_ADD_EXECUTABLE(jsonxml
      SOURCES jsonxml.cpp
      NOEXEPREFIX
      NOEXESUFFIX
      INSTALLABLE
    )
    TRIBITS_ADD_EXECUTABLE(jsonselect
      SOURCES jsonselect.cpp
      NOEXEPREFIX
      NOEXESUFFIX
      INSTALLABLE
    )
    TRIBITS_ADD_EXECUTABLE(sonjson
      SOURCES sonjson.cpp
      NOEXEPREFIX
      NOEXESUFFIX
      INSTALLABLE
    )
    TRIBITS_ADD_EXECUTABLE(sonvalidjson
      SOURCES sonvalidjson.cpp
      NOEXEPREFIX
      NOEXESUFFIX
      INSTALLABLE
    )
ENDIF()
##---------------------------------------------------------------------------##
##                   end of utils/CMakeLists.txt
##---------------------------------------------------------------------------##
TRIBITS_SUBPACKAGE_POSTPROCESS()
