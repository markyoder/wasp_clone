##---------------------------------------------------------------------------##
## wasp/Version.cmake
##---------------------------------------------------------------------------##
# Single file that needs to be changed on a release branch
# or on the development branch in order to configure wasp
# for release mode and set the version.

SET(WASP_NAME "wasp")
SET(WASP_VERSION 0.1)
SET(WASP_FULL_VERSION "alpha 0.1")
SET(WASP_VERSION_STRING "0.1 (aplha)")
SET(WASP_MAJOR_VERSION 00)
SET(WASP_MAJOR_MINOR_VERSION 001000)
SET(WASP_ENABLE_DEVELOPMENT_MODE_DEFAULT ON) # Change to 'OFF' for a release (beta or final)

##---------------------------------------------------------------------------##
##                    end of wasp/Version.cmake
##---------------------------------------------------------------------------##
