# Copyright (c) 2009-2010 Daniel Pfeifer, University of Zurich

set(QT_USE_QTXML ON)
set(QT_USE_QTOPENGL ON)
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

find_package(Boost  REQUIRED)
find_package(OpenGL REQUIRED)

execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf
  ${CMAKE_CURRENT_SOURCE_DIR}/glew-1.5.5.tgz
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
configure_file(
  ${CMAKE_BINARY_DIR}/glew-1.5.5/include/GL/glew.h
  ${CMAKE_BINARY_DIR}/include/Maoni/glew.h
  COPYONLY)
install(FILES ${CMAKE_BINARY_DIR}/glew-1.5.5/include/GL/glew.h
  DESTINATION includeMaoni COMPONENT headers)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/include)
execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf
  ${CMAKE_CURRENT_SOURCE_DIR}/boost-la.tar.gz
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/include)

include_directories(
  ${Boost_INCLUDE_DIRS}
  ${OPENGL_INCLUDE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_BINARY_DIR}/include
  ${CMAKE_BINARY_DIR}/glew-1.5.5/include
  ${CMAKE_CURRENT_BINARY_DIR}/QGLViewer
  ${CMAKE_CURRENT_BINARY_DIR}/QPropertyBrowser
  )

add_definitions(
  -DGLEW_BUILD
  -DBOOST_ALL_NO_LIB
  -DQGLVIEWER_STATIC
  )

add_library(GLEW ${CMAKE_BINARY_DIR}/glew-1.5.5/src/glew.c)


find_package(Boost COMPONENTS serialization)
if(NOT Boost_SERIALIZATION_FOUND)
  message(STATUS "Boost.Serialization not found, I will built it.")
  set(BOOST_SERIALIZATION_FILE
    ${CMAKE_SOURCE_DIR}/externals/boost-serialization-1.40.0.tar.gz)
  set(BOOST_SERIALIZATION_SOURCE_DIR
    ${CMAKE_CURRENT_BINARY_DIR}/boost-serialization-1.40.0)
  file(MAKE_DIRECTORY ${BOOST_SERIALIZATION_SOURCE_DIR})
  execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${BOOST_SERIALIZATION_FILE}
    WORKING_DIRECTORY ${BOOST_SERIALIZATION_SOURCE_DIR})
  add_library(boost_serialization
    ${BOOST_SERIALIZATION_SOURCE_DIR}/basic_archive.cpp
    ${BOOST_SERIALIZATION_SOURCE_DIR}/basic_iarchive.cpp
    ${BOOST_SERIALIZATION_SOURCE_DIR}/basic_iserializer.cpp
    ${BOOST_SERIALIZATION_SOURCE_DIR}/basic_oarchive.cpp
    ${BOOST_SERIALIZATION_SOURCE_DIR}/basic_oserializer.cpp
    ${BOOST_SERIALIZATION_SOURCE_DIR}/basic_pointer_iserializer.cpp
    ${BOOST_SERIALIZATION_SOURCE_DIR}/basic_pointer_oserializer.cpp
    ${BOOST_SERIALIZATION_SOURCE_DIR}/basic_serializer_map.cpp
    ${BOOST_SERIALIZATION_SOURCE_DIR}/basic_text_iprimitive.cpp
    ${BOOST_SERIALIZATION_SOURCE_DIR}/basic_text_oprimitive.cpp
    ${BOOST_SERIALIZATION_SOURCE_DIR}/basic_xml_archive.cpp
    ${BOOST_SERIALIZATION_SOURCE_DIR}/binary_iarchive.cpp
    ${BOOST_SERIALIZATION_SOURCE_DIR}/binary_oarchive.cpp
    ${BOOST_SERIALIZATION_SOURCE_DIR}/extended_type_info.cpp
    ${BOOST_SERIALIZATION_SOURCE_DIR}/extended_type_info_typeid.cpp
    ${BOOST_SERIALIZATION_SOURCE_DIR}/extended_type_info_no_rtti.cpp
    ${BOOST_SERIALIZATION_SOURCE_DIR}/polymorphic_iarchive.cpp
    ${BOOST_SERIALIZATION_SOURCE_DIR}/polymorphic_oarchive.cpp
    ${BOOST_SERIALIZATION_SOURCE_DIR}/stl_port.cpp
    ${BOOST_SERIALIZATION_SOURCE_DIR}/text_iarchive.cpp
    ${BOOST_SERIALIZATION_SOURCE_DIR}/text_oarchive.cpp
    ${BOOST_SERIALIZATION_SOURCE_DIR}/void_cast.cpp
    ${BOOST_SERIALIZATION_SOURCE_DIR}/xml_grammar.cpp
    ${BOOST_SERIALIZATION_SOURCE_DIR}/xml_iarchive.cpp
    ${BOOST_SERIALIZATION_SOURCE_DIR}/xml_oarchive.cpp
    )
  set(Boost_LIBRARIES ${Boost_LIBRARIES} boost_serialization)
endif(NOT Boost_SERIALIZATION_FOUND)


add_subdirectory(Common)
add_subdirectory(Widgets)
add_subdirectory(QGLViewer)
add_subdirectory(QPropertyBrowser)

set(MAONI_LIBRARIES
  GLEW
  MaoniCommon
  MaoniWidgets
  QGLViewer
  QtPropertyBrowser
  ${QT_LIBRARIES}
  ${Boost_LIBRARIES}
  ${OPENGL_LIBRARIES}
  )

set(MAONI_SOURCE Simple/main.cpp)
if(MSVC)
  set(MAONI_SOURCE ${MAONI_SOURCE} version.rc)
endif(MSVC)

add_library(Maoni SHARED ${MAONI_SOURCE})
target_link_libraries(Maoni ${MAONI_LIBRARIES})


option(MAONI_SKIP_EQUALIZER "Do not build libMaoniEq" OFF)
if(NOT MAONI_SKIP_EQUALIZER)
  add_subdirectory(Equalizer)
endif(NOT MAONI_SKIP_EQUALIZER)

option(MAONI_SKIP_ICET "Do not build libMaoniIceT" OFF)
if(NOT MAONI_SKIP_ICET)
  add_subdirectory(IceT)
endif(NOT MAONI_SKIP_ICET)


add_library(MaoniMain STATIC main.cpp)

install(TARGETS Maoni MaoniMain
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  COMPONENT devlibs
  )

if(WIN32)
  install(TARGETS Maoni
    RUNTIME DESTINATION bin
    COMPONENT runlibs
    )
endif(WIN32)
