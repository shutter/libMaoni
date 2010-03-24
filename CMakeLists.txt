# Copyright (c) 2009 Daniel Pfeifer, University of Zurich

cmake_minimum_required(VERSION 2.6.0 FATAL_ERROR)
project(Maoni)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(MSVC)
  add_definitions(/D_CRT_SECURE_NO_WARNINGS)
else(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -fPIC")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -fPIC")
endif(MSVC)

add_definitions(-DGL_GLEXT_PROTOTYPES)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake)


include_directories(include)
add_subdirectory(src)


option(MAONI_BUILD_DOCUMENTATION OFF)
if(MAONI_BUILD_DOCUMENTATION)
  set(THIS_PROJECT_NAME libMaoni)
  include(AddReference)
  include(AddDocumentation)
  add_subdirectory(doc)
endif(MAONI_BUILD_DOCUMENTATION)


option(MAONI_BUILD_EXAMPLES OFF)
if(MAONI_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif(MAONI_BUILD_EXAMPLES)


#install(DIRECTORY include/ DESTINATION include)
#install(TARGETS maoni ARCHIVE DESTINATION lib)
#
#set(CPACK_PACKAGE_CONTACT Daniel Pfeifer)
#include(CPack)
