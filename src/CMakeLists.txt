# Copyright (c) 2009-2010 Daniel Pfeifer, University of Zurich

set(QT_USE_QTXML ON)
set(QT_USE_QTOPENGL ON)
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

if(WIN32)
  set(Boost_USE_STATIC_LIBS ON)
endif(WIN32)

find_package(Boost  REQUIRED COMPONENTS serialization)
find_package(OpenGL REQUIRED)


file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/include)
execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf
  ${CMAKE_CURRENT_SOURCE_DIR}/boost-la.tar.gz
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/include)

include_directories(
  ${Boost_INCLUDE_DIRS}
  ${OPENGL_INCLUDE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_BINARY_DIR}/include
  ${CMAKE_CURRENT_BINARY_DIR}/QGLViewer
  ${CMAKE_CURRENT_BINARY_DIR}/QPropertyBrowser
  )

add_definitions(
  -DBOOST_ALL_NO_LIB
  -DQGLVIEWER_STATIC
  )


add_subdirectory(Common)
add_subdirectory(QGLViewer)
add_subdirectory(QPropertyBrowser)

set(MAONI_LIBRARIES
  Common
  QGLViewer
  QtPropertyBrowser
  ${QT_LIBRARIES}
  ${Boost_LIBRARIES}
  ${OPENGL_LIBRARIES}
  )

if(MSVC)
  set(MAONI_VERSION_RC ${CMAKE_CURRENT_SOURCE_DIR}/version.rc)
endif(MSVC)


#add_subdirectory(Equalizer)
add_subdirectory(IceT)


add_library(Maoni SHARED Maoni.cpp ${MAONI_VERSION_RC})
target_link_libraries(Maoni ${MAONI_LIBRARIES})

add_library(MaoniMain STATIC main.cpp)

install(TARGETS Maoni MaoniMain
  RUNTIME DESTINATION bin COMPONENT runlibs
  LIBRARY DESTINATION lib COMPONENT devlibs
  ARCHIVE DESTINATION lib COMPONENT devlibs
  )
