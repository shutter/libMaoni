# Copyright (c) 2009, 2010 Daniel Pfeifer, University of Zurich

include(UseIceT)

qt4_wrap_cpp(MAONI_ICET_MOC IceTWidget.hpp)

add_library(maoni_parallel SHARED
  main.cpp
  IceTWidget.cpp
  ${MAONI_ICET_MOC}
  )

target_link_libraries(maoni_parallel
  ${MAONI_LIBRARIES}
  ${MPI_LIBRARIES}
  icet icet_mpi
  )
