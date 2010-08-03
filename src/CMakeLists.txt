# Copyright (c) 2009-2010 Daniel Pfeifer, University of Zurich

set(QT_USE_QTXML ON)
set(QT_USE_QTOPENGL ON)
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

find_package(Boost     REQUIRED)
find_package(GLEW      REQUIRED)
find_package(OpenGL    REQUIRED)
find_package(QGLViewer REQUIRED)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${Boost_INCLUDE_DIRS}
  ${GLEW_INCLUDE_DIR}
  ${QGLVIEWER_INCLUDE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}/QPropertyBrowser
  )


add_definitions(-DBOOST_ALL_NO_LIB)

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


file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/include)
execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${CMAKE_SOURCE_DIR}/externals/boost-la.tar.gz
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/include)
include_directories(${CMAKE_BINARY_DIR}/include)


add_subdirectory(Common)
add_subdirectory(Widgets)
add_subdirectory(QPropertyBrowser)

set(MAONI_LIBRARIES
  MaoniCommon
  MaoniWidgets
  ${QT_LIBRARIES}
  QtPropertyBrowser
  ${QGLVIEWER_LIBRARY}
  ${Boost_LIBRARIES}
  ${GLEW_LIBRARIES}
  ${OPENGL_LIBRARIES}
  )

set(MAONI_SOURCE Simple/main.cpp)
if(MSVC)
  set(MAONI_SOURCE ${MAONI_SOURCE} version.rc)
endif(MSVC)

add_library(Maoni SHARED ${MAONI_SOURCE})
target_link_libraries(Maoni ${MAONI_LIBRARIES})


add_subdirectory(Equalizer)
add_subdirectory(IceT)


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
