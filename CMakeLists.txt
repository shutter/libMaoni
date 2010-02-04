# Copyright (c) 2009 Daniel Pfeifer, University of Zurich

cmake_minimum_required(VERSION 2.6.0 FATAL_ERROR)
project(VMMView)

set(CMAKE_BUILD_TYPE Debug)

if(NOT MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
endif(NOT MSVC)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

add_definitions(-DGL_GLEXT_PROTOTYPES)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

##############################################################

set(QT_USE_QTOPENGL ON) #
set(QT_USE_QTXML ON)    # required for property browser
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

add_subdirectory(contrib/QtPropertyBrowser)
include_directories(contrib/QtPropertyBrowser/include)

##############################################################

include(CMake/AddDocumentation.cmake)

file(GLOB VMMVIEW_DOC_HEADER include/VMMView/*.hpp)

add_documentation(VMMView ${VMMVIEW_DOC_HEADER}
  ${CMAKE_SOURCE_DIR}/include/VMMView.hpp)

##############################################################

find_package(Boost REQUIRED)
find_package(QGLViewer REQUIRED)

include_directories(
  include
  src
  ${Boost_INCLUDE_DIRS}
  ${Equalizer_INCLUDE_DIRS}
  ${QGLVIEWER_INCLUDE_DIR}
  )

file(GLOB_RECURSE VMMVIEW_HEADER 
  ${CMAKE_SOURCE_DIR}/VMMView/include/VMMView/*.hpp)

file(GLOB VMMVIEW_WIDGETS_HPP src/Widgets/*.hpp)
file(GLOB VMMVIEW_WIDGETS_SRC src/Widgets/*.cpp)
qt4_wrap_cpp(VMMVIEW_WIDGETS_MOC ${VMMVIEW_WIDGETS_HPP})

file(GLOB VMMVIEW_COMMON_SOURCE src/Common/*.c*)
set(VMMVIEW_COMMON_SOURCE
  ${VMMVIEW_COMMON_SOURCE}
  ${VMMVIEW_WIDGETS_SRC}
  ${VMMVIEW_WIDGETS_MOC}
  )

file(GLOB VMMVIEW_SIMPLE_SOURCE src/Simple/*.c*)

add_library(VMMView STATIC ${VMMVIEW_COMMON_SOURCE} ${VMMVIEW_SIMPLE_SOURCE})

##############################################################

option(VMMVIEW_BUILD_EQUALIZER_LIB OFF)
if(VMMVIEW_BUILD_EQUALIZER_LIB)
  include(VMMViewEqualizer)
endif(VMMVIEW_BUILD_EQUALIZER_LIB)

##############################################################

option(VMMVIEW_BUILD_ICET_LIB OFF)
if(VMMVIEW_BUILD_ICET_LIB)
  include(VMMViewIceT)
endif(VMMVIEW_BUILD_ICET_LIB)

##############################################################

install(FILES ${VMMVIEW_HEADER} DESTINATION include/VMMView)
install(TARGETS VMMView ARCHIVE DESTINATION lib)

set(CPACK_PACKAGE_CONTACT Daniel Pfeifer)
include(CPack)
