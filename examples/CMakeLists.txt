# Copyright (c) 2009 Daniel Pfeifer, University of Zurich

find_package(lib3ds REQUIRED)

file(GLOB_RECURSE RENDER_ALGO_SOURCE Algorithms/*.cpp)
file(GLOB_RECURSE MESH_LOADER_SOURCE Loaders/*.cpp)

add_executable(maoni_example
  ${RENDER_ALGO_SOURCE}
  ${MESH_LOADER_SOURCE}
  )

target_link_libraries(maoni_example
  maoni
  ${QT_LIBRARIES}
  QtPropertyBrowser
  ${QGLVIEWER_LIBRARY}
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
