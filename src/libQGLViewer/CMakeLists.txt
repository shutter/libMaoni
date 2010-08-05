# Copyright (c) 2010 Daniel Pfeifer, University of Zurich

execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf
  ${CMAKE_CURRENT_SOURCE_DIR}/libQGLViewer-2.3.6.tar.gz
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_definitions(-DNO_VECTORIAL_RENDER)

qt4_wrap_ui(QGLVIEWER_UI
  ${CMAKE_CURRENT_BINARY_DIR}/ImageInterface.ui
  )

qt4_wrap_cpp(QGLVIEWER_MOC
  ${CMAKE_CURRENT_BINARY_DIR}/qglviewer.h
  ${CMAKE_CURRENT_BINARY_DIR}/camera.h
  ${CMAKE_CURRENT_BINARY_DIR}/manipulatedFrame.h
  ${CMAKE_CURRENT_BINARY_DIR}/manipulatedCameraFrame.h
  ${CMAKE_CURRENT_BINARY_DIR}/frame.h
  ${CMAKE_CURRENT_BINARY_DIR}/keyFrameInterpolator.h
  )

add_library(QGLViewer
  ${QGLVIEWER_UI}
  ${QGLVIEWER_MOC}
  ${CMAKE_CURRENT_BINARY_DIR}/qglviewer.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/camera.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/manipulatedFrame.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/manipulatedCameraFrame.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/frame.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/saveSnapshot.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/constraint.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/keyFrameInterpolator.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/mouseGrabber.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/quaternion.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/vec.cpp
  )
