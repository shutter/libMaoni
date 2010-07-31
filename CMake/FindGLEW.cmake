# - Try to find GLEW
# Once done this will define
#  
#  GLEW_FOUND        - system has GLEW
#  GLEW_INCLUDE_DIRS - the GLEW include directory
#  GLEW_LIBRARIES    - Link these to use GLEW
#   

find_path(GLEW_INCLUDE_DIRS glew.h
  PATHS
    /usr/include
    /usr/local/include
    /opt/local/include
    c:/glew/include
  PATH_SUFFIXES
    gl/
    GL/
  )

find_library(GLEW_LIBRARIES
  NAMES
    glew
    glew32
    GLEW
  PATHS
    /usr/lib
    /usr/local/lib
    /opt/local/lib
    c:/glew/lib
  )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GLEW
  DEFAULT_MSG GLEW_LIBRARIES GLEW_INCLUDE_DIRS)

mark_as_advanced(GLEW_INCLUDE_DIRS GLEW_LIBRARIES)
