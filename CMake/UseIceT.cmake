# Copyright (c) 2010 Daniel Pfeifer, University of Zurich

set(ICET_URL          http://www.cs.unm.edu/~kmorel/IceT/IceT-1-0-0.tar.gz)
set(ICET_FILE         ${CMAKE_BINARY_DIR}/IceT.tar.gz)
set(ICET_RELATIVE_DIR IceT-1-0-0/src)
set(ICET_ABSOLUTE_DIR ${CMAKE_BINARY_DIR}/${ICET_RELATIVE_DIR})


if(NOT EXISTS ${ICET_ABSOLUTE_DIR})
  message(STATUS "Downloading IceT")
  file(DOWNLOAD ${ICET_URL} ${ICET_FILE} TIMEOUT 60)
  execute_process(
    COMMAND tar -zxvf ${ICET_FILE} -C ${CMAKE_BINARY_DIR} ${ICET_RELATIVE_DIR}
    OUTPUT_QUIET)
  file(REMOVE ${ICET_FILE})
endif(NOT EXISTS ${ICET_ABSOLUTE_DIR})


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
  ${ICET_ABSOLUTE_DIR}/include/GL/ice-t_config.h.in
  ${ICET_ABSOLUTE_DIR}/include/GL/ice-t_config.h)

include_directories(${ICET_ABSOLUTE_DIR}/include/)

add_subdirectory(${ICET_ABSOLUTE_DIR})
