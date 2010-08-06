# Copyright (c) 2010 Daniel Pfeifer, University of Zurich

# http://get.qt.nokia.com/qt/solutions/lgpl/qtpropertybrowser-2.5_1-opensource.tar.gz
# http://doc.trolltech.com/qq/qq18-propertybrowser-code.zip

execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf
  ${CMAKE_CURRENT_SOURCE_DIR}/qtpropertybrowser-2.5_1-opensource.tar.gz
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf
  ${CMAKE_CURRENT_SOURCE_DIR}/qq18-propertybrowser-extension.tar.gz
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

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
  qvector3dpropertymanager.cpp
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

MACRO(ADD_COPY_ONLY file)
  set(input  ${CMAKE_CURRENT_SOURCE_DIR}/${file})
  set(output ${CMAKE_CURRENT_BINARY_DIR}/${file})
  add_custom_command(OUTPUT ${output}
    COMMAND ${CMAKE_COMMAND}
    ARGS -E copy ${input} ${output}
    DEPENDS ${input})
ENDMACRO(ADD_COPY_ONLY file)

MACRO(QT4_MOC infile outfile)
  set(input  ${CMAKE_CURRENT_BINARY_DIR}/${infile})
  set(output ${CMAKE_CURRENT_BINARY_DIR}/${outfile})
  add_custom_command(OUTPUT ${output}
    COMMAND ${QT_MOC_EXECUTABLE}
    ARGS -o ${output} ${input}
    DEPENDS ${input})
  list(APPEND MOC_OUTPUT_LIST ${output})
ENDMACRO(QT4_MOC)

ADD_COPY_ONLY(qvector3dpropertymanager.h)

set(MOC_OUTPUT_LIST)
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
QT4_MOC(qvector3dpropertymanager.h  moc_qvector3dpropertymanager.cpp)

add_custom_target(QtPropertyBrowser_moc DEPENDS ${MOC_OUTPUT_LIST})
add_dependencies(QtPropertyBrowser QtPropertyBrowser_moc)
