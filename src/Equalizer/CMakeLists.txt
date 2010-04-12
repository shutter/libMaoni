# Copyright (c) 2009, 2010 Daniel Pfeifer, University of Zurich

if(WIN32)
  include(Extract)
  set(EQUALIZER_DIR ${CMAKE_CURRENT_BINARY_DIR}/Eq)
  extract(${CMAKE_SOURCE_DIR}/win32/Equalizer.zip ${EQUALIZER_DIR})
  set(Equalizer_INCLUDE_DIR ${EQUALIZER_DIR}/Headers)
  set(Equalizer_LIBRARY     ${EQUALIZER_DIR}/Equalizer.lib)
endif(WIN32)

find_package(Equalizer REQUIRED)
include_directories(${Equalizer_INCLUDE_DIRS})

set(MAONI_EQ_SRC
  Channel.cpp
  main.cpp
  )

if(MSVC)
  set(MAONI_EQ_SRC ${MAONI_EQ_SRC}
  Channel.hpp
  ColoredOutput.hpp
  EqInclude.hpp
  FrameDataEq.hpp
  Pipe.hpp
  Window.hpp
  )
endif(MSVC)

add_library(MaoniEq SHARED ${MAONI_EQ_SRC})

target_link_libraries(MaoniEq
  ${MAONI_LIBRARIES}
  ${Equalizer_LIBRARIES}
  )
