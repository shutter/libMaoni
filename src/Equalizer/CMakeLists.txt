# Copyright (c) 2009, 2010 Daniel Pfeifer, University of Zurich

find_package(Equalizer REQUIRED)
include_directories(${Equalizer_INCLUDE_DIRS})

add_library(maoni_eq SHARED
  Channel.cpp
  main.cpp
  )

target_link_libraries(maoni_eq
  ${MAONI_LIBRARIES}
  ${Equalizer_LIBRARIES}
  )

