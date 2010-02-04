# Copyright (c) 2009 Daniel Pfeifer, University of Zurich

cmake_minimum_required(VERSION 2.6.0 FATAL_ERROR)
project(VMMView)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
add_definitions(-DGL_GLEXT_PROTOTYPES)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/../VMMLFramework/CMake)

##############################################################

#option(VMMVIEW_USE_INSTALLED_LIB "Whether the installed VMMView library should be used" OFF)
set(VMMVIEW_ROOT ${CMAKE_SOURCE_DIR}/../Maoni)

option(VMMVIEW_USE_EQUALIZER "If VmmView should use Equalizer for rendering" OFF)

find_package(VMMView)

include_directories(include ${VMMView_INCLUDE_DIRS})

##############################################################

find_package(lib3ds REQUIRED)

file(GLOB_RECURSE RENDER_ALGO_SOURCE RenderAlgorithms/*.cpp)
file(GLOB_RECURSE MESH_LOADER_SOURCE MeshLoaders/*.cpp)

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
