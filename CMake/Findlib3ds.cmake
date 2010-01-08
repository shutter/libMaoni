# This module defines
# lib3ds_FOUND        - true if lib3ds was found
# lib3ds_INCLUDE_DIRS - where to find lib3ds/*.h
# lib3ds_LIBRARIES    - the libraries to link against to use lib3ds

find_path(lib3ds_INCLUDE_DIRS lib3ds/file.h)

find_library(lib3ds_LIBRARIES 3ds)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(lib3ds
  DEFAULT_MSG lib3ds_LIBRARIES lib3ds_INCLUDE_DIRS)

mark_as_advanced(lib3ds_INCLUDE_DIRS lib3ds_LIBRARIES)
