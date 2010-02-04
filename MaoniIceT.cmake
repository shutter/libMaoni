# Copyright (c) 2009 Daniel Pfeifer, University of Zurich

find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

set(ICET_INSTALL_NO_DEVELOPMENT ON)
set(ICET_INSTALL_NO_LIBRARIES   ON)

# Set the current ICE-T version.
SET(ICET_MAJOR_VERSION 1)
SET(ICET_MINOR_VERSION 0)
SET(ICET_PATCH_VERSION 0)
SET(ICET_VERSION "${ICET_MAJOR_VERSION}.${ICET_MINOR_VERSION}.${ICET_PATCH_VERSION}")

# Configure data type sizes.
INCLUDE (CheckTypeSize)
CHECK_TYPE_SIZE(char        ICET_SIZEOF_CHAR)
CHECK_TYPE_SIZE(short       ICET_SIZEOF_SHORT)
CHECK_TYPE_SIZE(int         ICET_SIZEOF_INT)
CHECK_TYPE_SIZE(long        ICET_SIZEOF_LONG)
CHECK_TYPE_SIZE("long long" ICET_SIZEOF_LONG_LONG)
CHECK_TYPE_SIZE(__int64     ICET_SIZEOF___INT64)
CHECK_TYPE_SIZE(float       ICET_SIZEOF_FLOAT)
CHECK_TYPE_SIZE(double      ICET_SIZEOF_DOUBLE)
CHECK_TYPE_SIZE("void*"     ICET_SIZEOF_VOID_P)

CONFIGURE_FILE(
  ${CMAKE_SOURCE_DIR}/contrib/IceT/include/GL/ice-t_config.h.in
  ${CMAKE_BINARY_DIR}/contrib/IceT/include/GL/ice-t_config.h)

include_directories(
  ${CMAKE_SOURCE_DIR}/contrib/IceT/include/
  ${CMAKE_BINARY_DIR}/contrib/IceT/include/)

add_subdirectory(contrib/IceT)

##############################################################

add_executable(IceTexample src/IceT/main.cpp)
target_link_libraries(IceTexample
  ${MPI_LIBRARIES}
  ${OPENGL_LIBRARIES}
  icet icet_mpi
  )
