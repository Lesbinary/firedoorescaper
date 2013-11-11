cmake_minimum_required(VERSION 2.4)
PROJECT(FireDoorEscaper)

###
### Main Variables
###
SET(PRJ ${PROJECT_NAME})         # Project name
SET(GCC_FLAGS "-ggdb -Wall")     # Compiler flags for gcc
SET(LIB_OUTDIR "../lib/")        # Output directory for compiled library
FILE(GLOB ${PRJ}_SOURCES *.cpp)  # Source files

###
### Compiler flags and information
###
SET(CMAKE_CXX_FLAGS ${GCC_FLAGS})          # Compilation flags
SET(LIBRARY_OUTPUT_PATH                    # Library output directory
        ${PROJECT_SOURCE_DIR}/${LIB_OUTDIR})
INCLUDE_DIRECTORIES(                       # Include directories 
        ${PROJECT_SOURCE_DIR}/../include/) 

###
### Creation of a Static Library
###
ADD_LIBRARY( ${PRJ} STATIC ${${PRJ}_SOURCES} )
TARGET_LINK_LIBRARIES( ${PRJ} m )
