# Copyright (c) 2009-2010 Daniel Pfeifer, University of Zurich

set(QT_USE_QTXML ON)
set(QT_USE_QTOPENGL ON)
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

find_package(Boost     REQUIRED)
find_package(GLEW      REQUIRED)
find_package(OpenGL    REQUIRED)
find_package(QGLViewer REQUIRED)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${Boost_INCLUDE_DIRS}
  ${GLEW_INCLUDE_DIR}
  ${QGLVIEWER_INCLUDE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}/QPropertyBrowser
  )

add_subdirectory(Common)
add_subdirectory(Widgets)
add_subdirectory(QPropertyBrowser)

set(MAONI_LIBRARIES
  MaoniCommon
  MaoniWidgets
  ${QT_LIBRARIES}
  QtPropertyBrowser
  ${QGLVIEWER_LIBRARY}
  ${Boost_LIBRARIES}
  ${GLEW_LIBRARY}
  ${OPENGL_LIBRARIES}
  )

set(MAONI_SOURCE Simple/main.cpp)
if(MSVC)
  set(MAONI_SOURCE ${MAONI_SOURCE} version.rc)
endif(MSVC)

add_library(Maoni SHARED ${MAONI_SOURCE})
target_link_libraries(Maoni ${MAONI_LIBRARIES})


add_subdirectory(Equalizer)
add_subdirectory(IceT)


add_library(MaoniMain STATIC main.cpp)

install(TARGETS Maoni MaoniMain
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  COMPONENT devlibs
  )

if(WIN32)
  install(TARGETS Maoni
    RUNTIME DESTINATION bin
    COMPONENT runlibs
    )
endif(WIN32)
