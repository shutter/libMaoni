# Copyright (c) 2010 Daniel Pfeifer, University of Zurich

# http://get.qt.nokia.com/qt/solutions/lgpl/qtpropertybrowser-2.5_1-opensource.tar.gz
# http://doc.trolltech.com/qq/qq18-propertybrowser-code.zip

find_program(7Z_EXECUTABLE 7z $ENV{ProgramFiles}/7-Zip)

set(QTPB_FILE       ${CMAKE_CURRENT_SOURCE_DIR}/qtpropertybrowser-2.5_1-opensource.zip)
set(QTPBE_FILE      ${CMAKE_CURRENT_SOURCE_DIR}/qq18-propertybrowser-extension.zip)

message(STATUS
  "\"${7Z_EXECUTABLE}\" x -y -o\"${CMAKE_CURRENT_BINARY_DIR}\" \"${QTPB_FILE}\"")
execute_process(COMMAND
  "\"${7Z_EXECUTABLE}\" x -y -o\"${CMAKE_CURRENT_BINARY_DIR}\" \"${QTPB_FILE}\"")

message(STATUS
  "\"${7Z_EXECUTABLE}\" x -y -o\"${CMAKE_CURRENT_BINARY_DIR}\" \"${QTPBE_FILE}\"")
execute_process(COMMAND
  "\"${7Z_EXECUTABLE}\" x -y -o\"${CMAKE_CURRENT_BINARY_DIR}\" \"${QTPBE_FILE}\"")

set(QT_PROPERTY_BROWSER_SRC
  ${CMAKE_CURRENT_BINARY_DIR}/qtbuttonpropertybrowser.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/qteditorfactory.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/qtgroupboxpropertybrowser.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/qtpropertybrowser.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/qtpropertybrowserutils.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/qtpropertymanager.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/qttreepropertybrowser.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/qtvariantproperty.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/fileedit.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/fileeditfactory.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/filepathmanager.cpp
  )

qt4_wrap_cpp(QT_PROPERTY_BROWSER_MOC
  ${CMAKE_CURRENT_BINARY_DIR}/qtpropertybrowserutils_p.h
  ${CMAKE_CURRENT_BINARY_DIR}/fileedit.h
  ${CMAKE_CURRENT_BINARY_DIR}/fileeditfactory.h
  ${CMAKE_CURRENT_BINARY_DIR}/filepathmanager.h
  )

qt4_add_resources(QT_PROPERTY_BROWSER_RCC
  ${CMAKE_CURRENT_BINARY_DIR}/qtpropertybrowser.qrc
  )

add_library(QtPropertyBrowser STATIC
  ${QT_PROPERTY_BROWSER_SRC}
  ${QT_PROPERTY_BROWSER_RCC}
  ${QT_PROPERTY_BROWSER_MOC}
  )

##############################################################

MACRO(QT4_MOC infile outfile)
  set(input  ${CMAKE_CURRENT_BINARY_DIR}/${infile})
  set(output ${CMAKE_CURRENT_BINARY_DIR}/${outfile})
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
