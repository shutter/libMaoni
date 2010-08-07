# Copyright (c) 2009-2010 Daniel Pfeifer, University of Zurich

execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf
  ${CMAKE_CURRENT_SOURCE_DIR}/glew-1.5.5.tgz
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  )

configure_file(
  ${CMAKE_CURRENT_BINARY_DIR}/glew-1.5.5/include/GL/glew.h
  ${CMAKE_BINARY_DIR}/include/Maoni/glew.h
  COPYONLY
  )

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/glew-1.5.5/include/GL/glew.h
  DESTINATION include/Maoni COMPONENT headers
  )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}/glew-1.5.5/include
  )

add_definitions(
  -DGLEW_BUILD
  )

qt4_wrap_cpp(COMMON_MOC
  AlgorithmWidget.hpp
  AnimationWidget.hpp
  LightWidget.hpp
  MainWindow.hpp
  RenderWidget.hpp
  TextOutput.hpp
  )

qt4_add_resources(COMMON_QRC
  Resources.qrc
  )

add_library(Common STATIC
  ${CMAKE_CURRENT_BINARY_DIR}/glew-1.5.5/src/glew.c
  ${COMMON_MOC}
  ${COMMON_QRC}
  AlgorithmWidget.cpp
  AnimationWidget.cpp
  Bunny.cpp
  FrameData.cpp
  LightWidget.cpp
  Logo.cpp
  MainWindow.cpp
  Path.cpp
  RenderWidget.cpp
  ShaderProgram.cpp
  Texture.cpp
  )

add_dependencies(Common QtPropertyBrowser)
