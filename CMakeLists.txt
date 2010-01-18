# Copyright (c) 2009 Daniel Pfeifer, University of Zurich

cmake_minimum_required(VERSION 2.6.0 FATAL_ERROR)
project(VMMView)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

add_definitions(-DGL_GLEXT_PROTOTYPES)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

##############################################################

find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

set(ICET_INSTALL_NO_DEVELOPMENT ON)
set(ICET_INSTALL_NO_LIBRARIES   ON)

# Set the current ICE-T version.
SET(ICET_MAJOR_VERSION 1)
SET(ICET_MINOR_VERSION 0)
SET(ICET_PATCH_VERSION 0)
SET(ICET_VERSION "${ICET_MAJOR_VERSION}.${ICET_MINOR_VERSION}.${ICET_PATCH_VERSION}")

# Configure data type sizes.
INCLUDE (CheckTypeSize)
CHECK_TYPE_SIZE(char        ICET_SIZEOF_CHAR)
CHECK_TYPE_SIZE(short       ICET_SIZEOF_SHORT)
CHECK_TYPE_SIZE(int         ICET_SIZEOF_INT)
CHECK_TYPE_SIZE(long        ICET_SIZEOF_LONG)
CHECK_TYPE_SIZE("long long" ICET_SIZEOF_LONG_LONG)
CHECK_TYPE_SIZE(__int64     ICET_SIZEOF___INT64)
CHECK_TYPE_SIZE(float       ICET_SIZEOF_FLOAT)
CHECK_TYPE_SIZE(double      ICET_SIZEOF_DOUBLE)
CHECK_TYPE_SIZE("void*"     ICET_SIZEOF_VOID_P)

CONFIGURE_FILE(
  ${CMAKE_SOURCE_DIR}/contrib/IceT/include/GL/ice-t_config.h.in
  ${CMAKE_BINARY_DIR}/contrib/IceT/include/GL/ice-t_config.h)

include_directories(
  ${CMAKE_SOURCE_DIR}/contrib/IceT/include/
  ${CMAKE_BINARY_DIR}/contrib/IceT/include/)

add_subdirectory(contrib/IceT)

##############################################################

set(QT_USE_QTOPENGL ON) #
set(QT_USE_QTXML ON)    # required for property browser
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

message(STATUS ${QT_CONFIG})

add_subdirectory(contrib/QtPropertyBrowser)
include_directories(contrib/QtPropertyBrowser/include)

##############################################################

include(CMake/AddDocumentation.cmake)

file(GLOB VMMVIEW_DOC_HEADER include/VMMView/*.hpp)

add_documentation(VMMView ${VMMVIEW_DOC_HEADER}
  ${CMAKE_SOURCE_DIR}/include/VMMView.hpp)

##############################################################

find_package(FLTK)
find_package(Boost REQUIRED)
find_package(Equalizer REQUIRED)

include_directories(
  include
  src
  ${FLTK_INCLUDE_DIR}
  ${Boost_INCLUDE_DIRS}
  ${Equalizer_INCLUDE_DIRS}
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
file(GLOB VMMVIEW_EQ_SOURCE src/Equalizer/*.c*)

add_library(VMMView STATIC ${VMMVIEW_COMMON_SOURCE} ${VMMVIEW_SIMPLE_SOURCE})
add_library(VMMView_eq STATIC ${VMMVIEW_COMMON_SOURCE} ${VMMVIEW_EQ_SOURCE})

##############################################################

add_executable(IceTexample src/IceT/main.cpp)
target_link_libraries(IceTexample
  ${MPI_LIBRARIES}
  ${OPENGL_LIBRARIES}
  icet icet_mpi
  )

##############################################################

install(FILES ${VMMVIEW_HEADER} DESTINATION include/VMMView)
install(TARGETS VMMView VMMView_eq ARCHIVE DESTINATION lib)

set(CPACK_PACKAGE_CONTACT Daniel Pfeifer)
include(CPack)
