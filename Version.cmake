##---------------------------------------------------------------------------##
## wasp/Version.cmake
##---------------------------------------------------------------------------##
# Single file that needs to be changed on a release branch
# or on the development branch in order to configure wasp
# for release mode and set the version.

SET(${PROJECT_NAME}_NAME "wasp")
SET(${PROJECT_NAME}_VERSION 2.0.0)
SET(${PROJECT_NAME}_FULL_VERSION "Workbench Analysis Sequence Processor 2.0.0")
SET(${PROJECT_NAME}_VERSION_STRING "2.0.0")
SET(${PROJECT_NAME}_MAJOR_VERSION 02)
SET(${PROJECT_NAME}_MAJOR_MINOR_VERSION 020000)
SET(${PROJECT_NAME}_ENABLE_DEVELOPMENT_MODE_DEFAULT ON) # Change to 'OFF' for a release (beta or final)

##---------------------------------------------------------------------------##
##                    end of wasp/Version.cmake
##---------------------------------------------------------------------------##
