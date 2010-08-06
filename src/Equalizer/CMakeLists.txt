# Copyright (c) 2009, 2010 Daniel Pfeifer, University of Zurich

find_package(Equalizer REQUIRED)
include_directories(${Equalizer_INCLUDE_DIRS})

set(MAONI_EQ_SRC
  main.cpp
  RenderWidget.cpp
  FrameDataEq.cpp
  )

if(MSVC)
  set(MAONI_EQ_SRC ${MAONI_EQ_SRC}
  EqInclude.hpp
  FrameDataEq.hpp
  Node.hpp
  RenderWidget.hpp
  )
endif(MSVC)

add_library(MaoniEq SHARED ${MAONI_EQ_SRC})

target_link_libraries(MaoniEq
  ${MAONI_LIBRARIES}
  ${Equalizer_LIBRARIES}
  )
