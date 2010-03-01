# Copyright (c) 2009 Daniel Pfeifer, University of Zurich

include(UseIceT)
find_package(OpenGL REQUIRED)

##############################################################

add_executable(IceTexample src/IceT/main.cpp)
target_link_libraries(IceTexample
  ${MPI_LIBRARIES}
  ${OPENGL_LIBRARIES}
  icet icet_mpi
  )
