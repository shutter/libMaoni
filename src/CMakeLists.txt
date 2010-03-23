# Copyright (c) 2009-2010 Daniel Pfeifer, University of Zurich

set(QT_USE_QTXML ON)
set(QT_USE_QTOPENGL ON)
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

find_package(Boost     REQUIRED)
find_package(GLEW      REQUIRED)
find_package(QGLViewer REQUIRED)
include(UseQtPropertyBrowser)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${Boost_INCLUDE_DIRS}
  ${GLEW_INCLUDE_DIR}
  ${QGLVIEWER_INCLUDE_DIR}
  )

add_subdirectory(Common)
add_subdirectory(Widgets)

set(MAONI_LIBRARIES
  maoni_common
  maoni_widgets
  ${QT_LIBRARIES}
  QtPropertyBrowser
  ${QGLVIEWER_LIBRARY}
  ${Boost_LIBRARIES}
  ${GLEW_LIBRARY}
  )

add_library(maoni SHARED Simple/main.cpp)
target_link_libraries(maoni ${MAONI_LIBRARIES})

option(MAONI_BUILD_PARALLEL_LIB OFF)
if(MAONI_BUILD_PARALLEL_LIB)
  add_subdirectory(IceT)
endif(MAONI_BUILD_PARALLEL_LIB)

add_library(maoni_main STATIC main.cpp)
