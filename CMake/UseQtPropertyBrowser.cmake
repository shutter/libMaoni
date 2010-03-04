# Copyright (c) 2010 Daniel Pfeifer, University of Zurich

set(QTPB_URL          http://get.qt.nokia.com/qt/solutions/lgpl/qtpropertybrowser-2.5_1-opensource.tar.gz)
set(QTPB_FILE         ${CMAKE_BINARY_DIR}/qtpropertybrowser-2.5_1-opensource.tar.gz)
set(QTPB_RELATIVE_DIR qtpropertybrowser-2.5_1-opensource/src/)
set(QTPB_ABSOLUTE_DIR ${CMAKE_BINARY_DIR}/${QTPB_RELATIVE_DIR})

if(NOT EXISTS ${QTPB_ABSOLUTE_DIR})
  message(STATUS "Downloading QtPropertyBrowser")
  file(DOWNLOAD ${QTPB_URL} ${QTPB_FILE} TIMEOUT 60)
  execute_process(
    COMMAND tar -zxvf ${QTPB_FILE} -C ${CMAKE_BINARY_DIR} ${QTPB_RELATIVE_DIR}
    OUTPUT_QUIET)
  file(REMOVE ${QTPB_FILE})
endif(NOT EXISTS ${QTPB_ABSOLUTE_DIR})


set(QTPBE_URL          http://doc.trolltech.com/qq/qq18-propertybrowser-code.zip)
set(QTPBE_FILE         ${CMAKE_BINARY_DIR}/qq18-propertybrowser-code.zip)
set(QTPBE_RELATIVE_DIR qq18-propertybrowser/extension)
set(QTPBE_ABSOLUTE_DIR ${CMAKE_BINARY_DIR}/${QTPBE_RELATIVE_DIR})

if(NOT EXISTS ${QTPBE_ABSOLUTE_DIR})
  message(STATUS "Downloading QtPropertyBrowser Extension")
  file(DOWNLOAD ${QTPBE_URL} ${QTPBE_FILE} TIMEOUT 60)
  execute_process(
    COMMAND unzip ${QTPBE_FILE} ${QTPBE_RELATIVE_DIR}/* -d ${CMAKE_BINARY_DIR}
    OUTPUT_QUIET)
  file(REMOVE ${QTPB_FILE})
endif(NOT EXISTS ${QTPBE_ABSOLUTE_DIR})


include_directories(${QTPB_ABSOLUTE_DIR} ${QTPBE_ABSOLUTE_DIR})


file(GLOB QT_PROPERTY_BROWSER_SRC
  ${QTPB_ABSOLUTE_DIR}/qtbuttonpropertybrowser.cpp
  ${QTPB_ABSOLUTE_DIR}/qteditorfactory.cpp
  ${QTPB_ABSOLUTE_DIR}/qtgroupboxpropertybrowser.cpp
  ${QTPB_ABSOLUTE_DIR}/qtpropertybrowser.cpp
  ${QTPB_ABSOLUTE_DIR}/qtpropertybrowserutils.cpp
  ${QTPB_ABSOLUTE_DIR}/qtpropertymanager.cpp
  ${QTPB_ABSOLUTE_DIR}/qttreepropertybrowser.cpp
  ${QTPB_ABSOLUTE_DIR}/qtvariantproperty.cpp
  ${QTPBE_ABSOLUTE_DIR}/fileedit.cpp
  ${QTPBE_ABSOLUTE_DIR}/fileeditfactory.cpp
  ${QTPBE_ABSOLUTE_DIR}/filepathmanager.cpp
  )

qt4_wrap_cpp(QT_PROPERTY_BROWSER_MOC
  ${QTPB_ABSOLUTE_DIR}/qtpropertybrowserutils_p.h
  ${QTPBE_ABSOLUTE_DIR}/fileedit.h
  ${QTPBE_ABSOLUTE_DIR}/fileeditfactory.h
  ${QTPBE_ABSOLUTE_DIR}/filepathmanager.h
  )

qt4_add_resources(QT_PROPERTY_BROWSER_RCC
  ${QTPB_ABSOLUTE_DIR}/qtpropertybrowser.qrc
  )

add_library(QtPropertyBrowser STATIC
  ${QT_PROPERTY_BROWSER_SRC}
  ${QT_PROPERTY_BROWSER_RCC}
  ${QT_PROPERTY_BROWSER_MOC}
  )

##############################################################

MACRO(QT4_MOC infile outfile)
  set(input  ${QTPB_ABSOLUTE_DIR}/${infile})
  set(output ${QTPB_ABSOLUTE_DIR}/${outfile})
  ADD_CUSTOM_COMMAND(OUTPUT ${output}
    COMMAND ${QT_MOC_EXECUTABLE}
   ARGS -o ${output} ${input}
    DEPENDS ${input})
  ADD_CUSTOM_TARGET(${outfile} DEPENDS ${output})
ENDMACRO(QT4_MOC)

QT4_MOC(qtbuttonpropertybrowser.h   moc_qtbuttonpropertybrowser.cpp)
QT4_MOC(qteditorfactory.h           moc_qteditorfactory.cpp)
QT4_MOC(qteditorfactory.cpp         qteditorfactory.moc)
QT4_MOC(qtgroupboxpropertybrowser.h moc_qtgroupboxpropertybrowser.cpp)
QT4_MOC(qtpropertybrowser.h         moc_qtpropertybrowser.cpp)
QT4_MOC(qtpropertymanager.h         moc_qtpropertymanager.cpp)
QT4_MOC(qtpropertymanager.cpp       qtpropertymanager.moc)
QT4_MOC(qttreepropertybrowser.h     moc_qttreepropertybrowser.cpp)
QT4_MOC(qttreepropertybrowser.cpp   qttreepropertybrowser.moc)
QT4_MOC(qtvariantproperty.h         moc_qtvariantproperty.cpp)

add_dependencies(QtPropertyBrowser
  moc_qtbuttonpropertybrowser.cpp
  moc_qteditorfactory.cpp
  qteditorfactory.moc
  moc_qtgroupboxpropertybrowser.cpp
  moc_qtpropertybrowser.cpp
  moc_qtpropertymanager.cpp
  qtpropertymanager.moc
  moc_qttreepropertybrowser.cpp
  qttreepropertybrowser.moc
  moc_qtvariantproperty.cpp
  )
