# Copyright (c) 2009 Daniel Pfeifer, University of Zurich

cmake_minimum_required(VERSION 2.6.0 FATAL_ERROR)
project(VMMView)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
add_definitions(-DGL_GLEXT_PROTOTYPES)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

##############################################################

set(QT_USE_QTOPENGL ON)
set(QT_USE_QTXML ON)
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

message(STATUS ${QT_CONFIG})

add_subdirectory(QtPropertyBrowser)
include_directories(QtPropertyBrowser/include)

##############################################################

add_subdirectory(VMMView)

include(CMake/AddDocumentation.cmake)

option(VMMVIEW_USE_INSTALLED_LIB "Whether the installed VMMView library should be used" OFF)
if(VMMVIEW_USE_INSTALLED_LIB)
  find_package(VMMView)
else(VMMVIEW_USE_INSTALLED_LIB)
  find_package(FLTK)
  find_package(Boost REQUIRED COMPONENTS thread)
  
  set(VMMView_INCLUDE_DIRS VMMView/include ${FLTK_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})

  option(VMMVIEW_USE_EQUALIZER "If VmmView should use Equalizer for rendering" OFF)
  if(VMMVIEW_USE_EQUALIZER)
    find_package(Equalizer REQUIRED)
    add_definitions(-DVMMVIEW_USE_EQUALIZER)
    set(VMMView_INCLUDE_DIRS ${VMMView_INCLUDE_DIRS} ${Equalizer_INCLUDE_DIRS})
    set(VMMView_LIBRARIES VMMView_eq ${Equalizer_LIBRARIES})    
  else(VMMVIEW_USE_EQUALIZER)
    set(VMMView_LIBRARIES VMMView)    
  endif(VMMVIEW_USE_EQUALIZER)

  set(VMMView_LIBRARIES
    ${VMMView_LIBRARIES}
    ${FLTK_LIBRARIES}
    ${QT_LIBRARIES}
    qglviewer-qt4
    QtPropertyBrowser
    )

endif(VMMVIEW_USE_INSTALLED_LIB)

include_directories(include ${VMMView_INCLUDE_DIRS})

##############################################################

find_package(lib3ds REQUIRED)

file(GLOB_RECURSE RENDER_ALGO_SOURCE RenderAlgorithm/*.cpp)
file(GLOB_RECURSE MESH_LOADER_SOURCE MeshLoader/*.cpp)

add_executable(view
  ${RENDER_ALGO_SOURCE}
  ${MESH_LOADER_SOURCE}
  )

target_link_libraries(view
  ${VMMView_LIBRARIES}
  ${lib3ds_LIBRARIES}
  ${Boost_LIBRARIES}
  )

##############################################################

file(GLOB MODEL_FILES
   RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/Models 
   ${CMAKE_CURRENT_SOURCE_DIR}/Models/?*.*)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Models)

foreach(MODEL_FILE ${MODEL_FILES})
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Models/${MODEL_FILE}
    ${CMAKE_CURRENT_BINARY_DIR}/Models/${MODEL_FILE} COPYONLY)
endforeach(MODEL_FILE ${MODEL_FILES})
