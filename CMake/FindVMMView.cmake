##############################################################
# Copyright (c) 2009 Daniel Pfeifer                          #
##############################################################

# This module defines
# VMMView_FOUND        - true if VMMView was found
# VMMView_INCLUDE_DIRS - where to find VMMView.hpp
# VMMView_LIBRARIES    - the libraries to link against to use VMMView

find_path(VMMView_INCLUDE_DIR VMMView.hpp
  ${VMMVIEW_ROOT}/include
  /usr/include
  /usr/local/include
  $ENV{ProgramFiles}/VMMView/include
)

if(VMMVIEW_USE_EQUALIZER)
  set(VMMView_LIB_NAME VMMView_eq)
else(VMMVIEW_USE_EQUALIZER)
  set(VMMView_LIB_NAME VMMView)
endif(VMMVIEW_USE_EQUALIZER)

find_library(VMMView_LIBRARY
  NAMES
    ${VMMView_LIB_NAME}
  PATHS
    ${VMMVIEW_ROOT}/lib
    /usr/lib
    /usr/local/lib
    $ENV{ProgramFiles}/VMMView/lib
)

find_library(QtPropertyBrowser_LIB
  NAMES
    QtPropertyBrowser
  PATHS
    ${VMMVIEW_ROOT}/lib
)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(VMMView
  DEFAULT_MSG VMMView_LIBRARY VMMView_INCLUDE_DIR)

set(QT_USE_QTOPENGL ON)
find_package(Qt4 REQUIRED)

find_package(FLTK)
find_package(Boost REQUIRED COMPONENTS thread)

set(VMMView_INCLUDE_DIRS
  ${VMMView_INCLUDE_DIR}
  ${Boost_INCLUDE_DIRS}
  )

set(VMMView_LIBRARIES
  ${VMMView_LIBRARY}
    ${FLTK_LIBRARIES}
    ${QT_LIBRARIES}
    qglviewer-qt4
#   ${Equalizer_LIBRARIES}
    ${QtPropertyBrowser_LIB}
  )

mark_as_advanced(VMMView_INCLUDE_DIRS VMMView_LIBRARIES)
