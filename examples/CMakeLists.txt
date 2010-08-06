# Copyright (c) 2009 Daniel Pfeifer, University of Zurich

##############################################################
find_package(Boost REQUIRED)
include_directories(
  ${Boost_INCLUDE_DIRS}
  ${CMAKE_BINARY_DIR}/include
  )

add_custom_target(examples)

macro(add_example NAME)
  add_executable(${NAME} EXCLUDE_FROM_ALL ${ARGN})
  add_dependencies(examples ${NAME})
endmacro(add_example NAME)

##############################################################
# example without source

set(EMPTY_SOURCE_FILE ${CMAKE_CURRENT_BINARY_DIR}/empty.c)
file(WRITE ${EMPTY_SOURCE_FILE} "")
add_example(example_nothing ${EMPTY_SOURCE_FILE})
target_link_libraries(example_nothing Maoni MaoniMain)

##############################################################
# example with algorithms

set(VBO_MODEL_SOURCE
  Loaders/VBOModel.cpp
  )
file(GLOB RENDER_ALGO_SOURCE Algorithms/*.c*)
add_example(example_algorithms ${RENDER_ALGO_SOURCE} ${VBO_MODEL_SOURCE})
target_link_libraries(example_algorithms Maoni MaoniMain)

##############################################################
# example with loaders

set(MESH_LOADER_SOURCE
  Loaders/VBOModel.cpp
  Loaders/PLY/ply.cpp Loaders/PLY/plyfile.cpp
  Loaders/STL/stl.cpp Loaders/STL/stla_io.cpp
  )

set(LIBRARIES MaoniMain)

find_package(lib3ds)
if(lib3ds_LIBRARIES)
  set(MESH_LOADER_SOURCE ${MESH_LOADER_SOURCE} Loaders/3DS/3ds.cpp)
  set(LIBRARIES ${LIBRARIES} ${lib3ds_LIBRARIES})
endif(lib3ds_LIBRARIES)

add_example(example_loaders ${MESH_LOADER_SOURCE})
target_link_libraries(example_loaders ${LIBRARIES} Maoni)

##############################################################
# example with both algorithms and loaders

add_example(example_full ${RENDER_ALGO_SOURCE} ${MESH_LOADER_SOURCE})
target_link_libraries(example_full ${LIBRARIES} Maoni)

##############################################################
# example with both algorithms and loaders, using Equalizer

add_example(example_eq ${RENDER_ALGO_SOURCE} ${MESH_LOADER_SOURCE})
target_link_libraries(example_eq ${LIBRARIES} MaoniEq)

##############################################################
# example with both algorithms and loaders, using IceT

add_example(example_icet ${RENDER_ALGO_SOURCE} ${MESH_LOADER_SOURCE})
target_link_libraries(example_icet ${LIBRARIES} MaoniIceT)

##############################################################

file(GLOB MODEL_FILES
   RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/Models 
   ${CMAKE_CURRENT_SOURCE_DIR}/Models/?*.*)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Models)

foreach(MODEL_FILE ${MODEL_FILES})
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Models/${MODEL_FILE}
    ${CMAKE_CURRENT_BINARY_DIR}/Models/${MODEL_FILE} COPYONLY)
endforeach(MODEL_FILE ${MODEL_FILES})
