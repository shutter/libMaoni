# Copyright (c) 2009 Daniel Pfeifer, University of Zurich

file(GLOB RENDER_ALGO_SOURCE Algorithms/*.cpp)

set(MESH_LOADER_SOURCE
  Loaders/PLY/ply.cpp
  Loaders/PLY/plyfile.cpp
  Loaders/STL/stl.cpp
  Loaders/STL/stla_io.cpp
  )

set(LIBRARIES
  maoni
  ${QT_LIBRARIES}
  QtPropertyBrowser
  ${QGLVIEWER_LIBRARY}
  ${Boost_LIBRARIES}
  ${GLEW_LIBRARY}
  )

##############################################################

find_package(lib3ds)
if(lib3ds_LIBRARIES)
  set(MESH_LOADER_SOURCE
    ${MESH_LOADER_SOURCE}
    Loaders/3DS/3ds.cpp
    )
  set(LIBRARIES ${LIBRARIES} ${lib3ds_LIBRARIES})
endif(lib3ds_LIBRARIES)


##############################################################

add_executable(maoni_example
  ${RENDER_ALGO_SOURCE}
  ${MESH_LOADER_SOURCE}
  )

target_link_libraries(maoni_example ${LIBRARIES})

##############################################################

file(GLOB MODEL_FILES
   RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/Models 
   ${CMAKE_CURRENT_SOURCE_DIR}/Models/?*.*)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Models)

foreach(MODEL_FILE ${MODEL_FILES})
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Models/${MODEL_FILE}
    ${CMAKE_CURRENT_BINARY_DIR}/Models/${MODEL_FILE} COPYONLY)
endforeach(MODEL_FILE ${MODEL_FILES})
