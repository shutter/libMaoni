# Copyright (c) 2009 Daniel Pfeifer, University of Zurich

cmake_minimum_required(VERSION 2.6.0 FATAL_ERROR)
project(Maoni)

set(CMAKE_BUILD_TYPE Debug)

if(NOT MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -fPIC")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -fPIC")
endif(NOT MSVC)

add_definitions(-DGL_GLEXT_PROTOTYPES)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake)

##############################################################

set(QT_USE_QTOPENGL ON) #
set(QT_USE_QTXML ON)    # required for property browser
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

include(UseQtPropertyBrowser)

##############################################################

add_library(maoni_main STATIC src/main.cpp)

##############################################################

find_package(Boost     REQUIRED)
find_package(GLEW      REQUIRED)
find_package(QGLViewer REQUIRED)

include_directories(
  include
  src
  ${Boost_INCLUDE_DIRS}
  ${Equalizer_INCLUDE_DIRS}
  ${GLEW_INCLUDE_DIR}
  ${QGLVIEWER_INCLUDE_DIR}
  )

file(GLOB MAONI_WIDGETS_HPP src/Widgets/*.hpp)
file(GLOB MAONI_WIDGETS_SRC src/Widgets/*.cpp)
qt4_wrap_cpp(MAONI_WIDGETS_MOC ${MAONI_WIDGETS_HPP})
add_library(maoni_widgets STATIC ${MAONI_WIDGETS_SRC} ${MAONI_WIDGETS_MOC})

file(GLOB MAONI_COMMON_SOURCE src/Common/*.c*)
add_library(maoni_common STATIC ${MAONI_COMMON_SOURCE})

set(MAONI_LIBRARIES
  maoni_common
  maoni_widgets
  ${QT_LIBRARIES}
  QtPropertyBrowser
  ${QGLVIEWER_LIBRARY}
  ${Boost_LIBRARIES}
  ${GLEW_LIBRARY}
  )

add_library(maoni SHARED src/Simple/main.cpp)
target_link_libraries(maoni ${MAONI_LIBRARIES})

##############################################################

option(MAONI_BUILD_PARALLEL_LIB OFF)
if(MAONI_BUILD_PARALLEL_LIB)
  include(UseIceT)
  qt4_wrap_cpp(MAONI_ICET_MOC src/IceT/IceTWidget.hpp)
  add_library(maoni_parallel SHARED
    src/IceT/main.cpp
    src/IceT/IceTWidget.cpp
    ${MAONI_ICET_MOC}
    )
  target_link_libraries(maoni_parallel
    ${MAONI_LIBRARIES}
    ${MPI_LIBRARIES}
    icet icet_mpi
    )
endif(MAONI_BUILD_PARALLEL_LIB)

##############################################################

option(MAONI_BUILD_DOCUMENTATION OFF)
if(MAONI_BUILD_DOCUMENTATION)
  set(THIS_PROJECT_NAME libMaoni)
  include(AddReference)
  include(AddDocumentation)
  add_subdirectory(doc)
endif(MAONI_BUILD_DOCUMENTATION)

##############################################################

option(MAONI_BUILD_EXAMPLES OFF)
if(MAONI_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif(MAONI_BUILD_EXAMPLES)

##############################################################

#install(DIRECTORY include/ DESTINATION include)
#install(TARGETS maoni ARCHIVE DESTINATION lib)
#
#set(CPACK_PACKAGE_CONTACT Daniel Pfeifer)
#include(CPack)
