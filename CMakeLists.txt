# Copyright (c) 2009 Daniel Pfeifer, University of Zurich

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(Maoni)

#set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(MSVC)
  add_definitions(
    /D_CRT_SECURE_NO_WARNINGS /D_SCL_SECURE_NO_WARNINGS)
else(MSVC)
  # 64bit needs this
  add_definitions(-fPIC)
endif(MSVC)


list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CToolBox)


if(WIN32)
  set(QGLVIEWER_DIR ${CMAKE_BINARY_DIR}/QGLViewer)
  extract(${CMAKE_SOURCE_DIR}/win32/QGLViewer.zip ${QGLVIEWER_DIR})
  set(QGLVIEWER_INCLUDE_DIR ${QGLVIEWER_DIR}/include)
  set(QGLVIEWER_LIBRARY     ${QGLVIEWER_DIR}/lib/QGLViewer2.lib)
endif(WIN32)


include_directories(include)
install(DIRECTORY include/Maoni DESTINATION include COMPONENT headers)
install(FILES include/Maoni.hpp DESTINATION include COMPONENT headers)


add_subdirectory(src)
add_subdirectory(examples)


# Building of Documentation is tested on Linux only
if(CMAKE_SYSTEM_NAME STREQUAL Linux)
  set(THIS_PROJECT_NAME libMaoni)
  include(AddReference)
  include(AddDocumentation)
  add_subdirectory(doc EXCLUDE_FROM_ALL)
endif(CMAKE_SYSTEM_NAME STREQUAL Linux)

SET(CPACK_SOURCE_IGNORE_FILES "/[.][^/]*;${CMAKE_BINARY_DIR}/")

set(CPACK_PACKAGE_NAME "libMaoni")
set(CPACK_PACKAGE_VENDOR "http://github.com/purpleKarrot/libMaoni")
set(CPACK_PACKAGE_CONTACT "Daniel Pfeifer <daniel@pfeifer-mail.de>")
set(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_SOURCE_DIR}/README)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "common viewing framework")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "4")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "Maoni")

set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/COPYING)

set(CPACK_COMPONENTS_ALL headers devlibs runlibs)

set(CPACK_COMPONENT_HEADERS_GROUP dev)
set(CPACK_COMPONENT_HEADERS_DISPLAY_NAME "C++ Headers")
set(CPACK_COMPONENT_HEADERS_DESCRIPTION
  "C++ header files for use with Maoni")

set(CPACK_COMPONENT_DEVLIBS_DISPLAY_NAME "Developer Libraries")
set(CPACK_COMPONENT_DEVLIBS_DESCRIPTION
  "Libraries used to build programs with Maoni")

set(CPACK_COMPONENT_RUNLIBS_DISPLAY_NAME "Runtime Libraries")
set(CPACK_COMPONENT_RUNLIBS_DESCRIPTION
  "Libraries used to run Maoni based programs")

set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/src/Icons/stanford-bunny.ico")

set(CPACK_DPUT_HOST "ppa:purplekarrot/ppa")

set(CPACK_DEBIAN_BUILD_DEPENDS
  libqt4-dev
  libqglviewer-qt4-dev
  libboost1.40-dev
  libboost-serialization1.40-dev
  libglew1.5-dev
  libopenmpi-dev
  )

#todo: http://www.itk.org/Wiki/CMake:Component_Install_With_CPack

include(CPack)
