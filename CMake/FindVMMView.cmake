##############################################################
# Copyright (c) 2009 Daniel Pfeifer                          #
##############################################################

# This module defines
# VMMView_FOUND        - true if VMMView was found
# VMMView_INCLUDE_DIRS - where to find VMMView.hpp
# VMMView_LIBRARIES    - the libraries to link against to use VMMView
# VMMView_EXAMPLES     - example source files of VMMView

find_path(VMMView_INCLUDE_DIR VMMView.hpp
  /usr/include
  /usr/local/include
  $ENV{ProgramFiles}/VMMView/include
)

find_library(VMMView_LIBRARY
  NAMES
    VMMView
  PATHS
    /usr/lib
    /usr/local/lib
    $ENV{ProgramFiles}/VMMView/lib
)

set(VMMView_INCLUDE_DIRS ${VMMView_INCLUDE_DIR})
set(VMMView_LIBRARIES ${VMMView_LIBRARY})

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(VMMView
  DEFAULT_MSG VMMView_LIBRARIES VMMView_INCLUDE_DIRS)

mark_as_advanced(VMMView_INCLUDE_DIRS VMMView_LIBRARIES)
