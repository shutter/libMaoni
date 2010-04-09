# This module defines
# Equalizer_FOUND        - true if Equalizer was found
# Equalizer_INCLUDE_DIRS - where to find eq/eq.h
# Equalizer_LIBRARIES    - the libraries to link against to use Equalizer

# Look for Equalizer includes by searching for eq.h
find_path(Equalizer_INCLUDE_DIR eq/eq.h
  PATH_SUFFIXES
    include
  PATHS
    /usr/local
    /usr
    /opt
    $ENV{EQ_ROOT}
    $ENV{ProgramFiles}/Equalizer/include
  )

# Search for the Equalizer library by searching eq.so / Equalizer.lib
find_library(Equalizer_LIBRARY
  NAMES
    eq
    Equalizer
  PATH_SUFFIXES
    lib64
    lib
    libs64
    libs
    libs/Win32
    libs/Win64
  PATHS
    /usr/local
    /usr
    /opt
    $ENV{EQ_ROOT}
    $ENV{ProgramFiles}/Equalizer/lib
  )

# The variable Equalizer_LIBRARIES will contain all libraries which have to be
# linked when using Equalizer.
set(Equalizer_INCLUDE_DIRS ${Equalizer_INCLUDE_DIR})
set(Equalizer_LIBRARIES ${Equalizer_LIBRARY})

# Equalizer needs librt for clock_gettime, but only on Linux.
# Therefore search for librt and add it to Equalizer_LIBRARIES
IF("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
  FIND_LIBRARY(RT_LIBRARY NAMES rt)
  IF(NOT RT_LIBRARY)
    MESSAGE(FATAL_ERROR "librt was NOT found!")
  ELSE(NOT RT_LIBRARY)
    MESSAGE(STATUS "Found librt: Library at ${RT_LIBRARY}")
  ENDIF(NOT RT_LIBRARY)
  SET(Equalizer_LIBRARIES ${Equalizer_LIBRARIES} ${RT_LIBRARY})
ENDIF("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")

# Equalizer uses deprecated headers, ignore those errors
if(NOT WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated")
endif(NOT WIN32)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Equalizer
  DEFAULT_MSG Equalizer_LIBRARIES Equalizer_INCLUDE_DIRS)

mark_as_advanced(Equalizer_INCLUDE_DIRS Equalizer_LIBRARIES)
