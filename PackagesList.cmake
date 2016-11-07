##---------------------------------------------------------------------------##
## wasp/PackagesList.cmake
## Robert A. Lefebvre, lefebvrera@ornl.gov
## Monday November 7 2016
##---------------------------------------------------------------------------##
#
# See documentation in TriBITS https://tribits.org


##---------------------------------------------------------------------------##
## PACKAGES PROVIDED
##---------------------------------------------------------------------------##

TRIBITS_REPOSITORY_DEFINE_PACKAGES(
  googletest googletest/googletest PT
  testframework testframework PT
  wasp  . PT
)

TRIBITS_ALLOW_MISSING_EXTERNAL_PACKAGES(
   googletest
   testframework
)

##---------------------------------------------------------------------------##
##                     end of wasp/PackagesList.cmake
##---------------------------------------------------------------------------##
