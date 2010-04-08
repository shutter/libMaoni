# Copyright (c) 2009 Daniel Pfeifer, University of Zurich

##############################################################
find_package(Boost REQUIRED)
find_package(GLEW  REQUIRED)
include_directories(${Boost_INCLUDE_DIRS} ${GLEW_INCLUDE_DIR})

##############################################################
# example without source

set(EMPTY_SOURCE_FILE ${CMAKE_CURRENT_BINARY_DIR}/empty.c)
file(WRITE ${EMPTY_SOURCE_FILE} "")
add_executable(example_nothing ${EMPTY_SOURCE_FILE})
target_link_libraries(example_nothing maoni maoni_main)

if(MAONI_BUILD_LIB_ICET)
  add_executable(example_nothing_icet ${EMPTY_SOURCE_FILE})
  target_link_libraries(example_nothing_icet
    maoni_icet maoni_main)
endif(MAONI_BUILD_LIB_ICET)

##############################################################
# example with algorithms

file(GLOB RENDER_ALGO_SOURCE Algorithms/*.cpp)
add_executable(example_algorithms ${RENDER_ALGO_SOURCE})
target_link_libraries(example_algorithms maoni maoni_main)

##############################################################
# example with loaders

set(MESH_LOADER_SOURCE
  Loaders/PLY/ply.cpp
  Loaders/PLY/plyfile.cpp
  Loaders/STL/stl.cpp
  Loaders/STL/stla_io.cpp
  )

set(LIBRARIES maoni maoni_main)

find_package(lib3ds)
if(lib3ds_LIBRARIES)
  set(MESH_LOADER_SOURCE
    ${MESH_LOADER_SOURCE}
    Loaders/3DS/3ds.cpp
    )
  set(LIBRARIES ${LIBRARIES} ${lib3ds_LIBRARIES})
endif(lib3ds_LIBRARIES)

add_executable(example_loaders ${MESH_LOADER_SOURCE})
target_link_libraries(example_loaders ${LIBRARIES})

##############################################################
# example with both algorithms and loaders

add_executable(example_full ${RENDER_ALGO_SOURCE} ${MESH_LOADER_SOURCE})
target_link_libraries(example_full ${LIBRARIES})

##############################################################

file(GLOB MODEL_FILES
   RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/Models 
   ${CMAKE_CURRENT_SOURCE_DIR}/Models/?*.*)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Models)

foreach(MODEL_FILE ${MODEL_FILES})
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Models/${MODEL_FILE}
    ${CMAKE_CURRENT_BINARY_DIR}/Models/${MODEL_FILE} COPYONLY)
endforeach(MODEL_FILE ${MODEL_FILES})
