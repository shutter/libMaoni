# Copyright (c) 2009, 2010 Daniel Pfeifer, University of Zurich

find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})


find_package(Boost COMPONENTS mpi)
if(NOT Boost_MPI_FOUND)
  message(STATUS "Boost.MPI not found, I will built it.")
  set(BOOST_MPI_FILE ${CMAKE_SOURCE_DIR}/externals/boost-mpi-1.40.0.tar.gz)
  set(BOOST_MPI_SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/boost-mpi-1.40.0)
  file(MAKE_DIRECTORY ${BOOST_MPI_SOURCE_DIR})
  execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${BOOST_MPI_FILE}
    WORKING_DIRECTORY ${BOOST_MPI_SOURCE_DIR})
  add_library(boost_mpi
    ${BOOST_MPI_SOURCE_DIR}/broadcast.cpp
    ${BOOST_MPI_SOURCE_DIR}/communicator.cpp
    ${BOOST_MPI_SOURCE_DIR}/computation_tree.cpp
    ${BOOST_MPI_SOURCE_DIR}/content_oarchive.cpp
    ${BOOST_MPI_SOURCE_DIR}/environment.cpp
    ${BOOST_MPI_SOURCE_DIR}/exception.cpp
    ${BOOST_MPI_SOURCE_DIR}/graph_communicator.cpp
    ${BOOST_MPI_SOURCE_DIR}/group.cpp
    ${BOOST_MPI_SOURCE_DIR}/intercommunicator.cpp
    ${BOOST_MPI_SOURCE_DIR}/mpi_datatype_cache.cpp
    ${BOOST_MPI_SOURCE_DIR}/mpi_datatype_oarchive.cpp
    ${BOOST_MPI_SOURCE_DIR}/packed_iarchive.cpp
    ${BOOST_MPI_SOURCE_DIR}/packed_oarchive.cpp
    ${BOOST_MPI_SOURCE_DIR}/packed_skeleton_iarchive.cpp
    ${BOOST_MPI_SOURCE_DIR}/packed_skeleton_oarchive.cpp
    ${BOOST_MPI_SOURCE_DIR}/point_to_point.cpp
    ${BOOST_MPI_SOURCE_DIR}/request.cpp
    ${BOOST_MPI_SOURCE_DIR}/text_skeleton_oarchive.cpp
    )
  set(Boost_LIBRARIES ${Boost_LIBRARIES} boost_mpi)
endif(NOT Boost_MPI_FOUND)


set(ICET_FILE ${CMAKE_SOURCE_DIR}/externals/IceT-1-0-0.tar.gz)
set(ICET_SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/IceT-1-0-0)
file(MAKE_DIRECTORY ${ICET_SOURCE_DIR})
execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${ICET_FILE}
  WORKING_DIRECTORY ${ICET_SOURCE_DIR})


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
  ${ICET_SOURCE_DIR}/include/GL/ice-t_config.h.in
  ${ICET_SOURCE_DIR}/include/GL/ice-t_config.h)

include_directories(${ICET_SOURCE_DIR}/include/)

add_subdirectory(${ICET_SOURCE_DIR} ${ICET_SOURCE_DIR}/build)

qt4_wrap_cpp(MAONI_ICET_MOC
  TilesWidget.hpp
  )

add_library(MaoniIceT SHARED
  FrameData.cpp
  main.cpp
  RenderWidget.cpp
  TilesWidget.cpp
  ${MAONI_ICET_MOC}
  )

target_link_libraries(MaoniIceT
  ${MAONI_LIBRARIES}
  ${MPI_LIBRARIES}
  boost_mpi
  icet icet_mpi icet_strategies
  )

install(TARGETS MaoniIceT
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  COMPONENT devlibs
  )

if(WIN32)
  install(TARGETS MaoniIceT
    RUNTIME DESTINATION bin
    COMPONENT runlibs
    )
endif(WIN32)
