
file(GLOB QT_PROPERTY_BROWSER_SRC src/*.cpp)

qt4_wrap_cpp(QT_PROPERTY_BROWSER_MOC src/qtpropertybrowserutils_p.h)

qt4_add_resources(QT_PROPERTY_BROWSER_RCC qtpropertybrowser.qrc)

add_library(QtPropertyBrowser STATIC
  ${QT_PROPERTY_BROWSER_SRC}
  ${QT_PROPERTY_BROWSER_RCC}
  ${QT_PROPERTY_BROWSER_MOC}
  )

##############################################################

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/moc)
include_directories(include ${CMAKE_CURRENT_BINARY_DIR}/moc)

MACRO(QT4_MOC infile outfile)

  set(input  ${CMAKE_CURRENT_SOURCE_DIR}/${infile})
  set(output ${CMAKE_CURRENT_BINARY_DIR}/moc/${outfile})

  ADD_CUSTOM_COMMAND(OUTPUT ${output}
    COMMAND ${QT_MOC_EXECUTABLE}
    ARGS -o ${output} ${input}
    DEPENDS ${input})

  ADD_CUSTOM_TARGET(${outfile} DEPENDS ${output})
  
ENDMACRO(QT4_MOC)

QT4_MOC(include/qtbuttonpropertybrowser.h   moc_qtbuttonpropertybrowser.cpp)
QT4_MOC(include/qteditorfactory.h           moc_qteditorfactory.cpp)
QT4_MOC(src/qteditorfactory.cpp             qteditorfactory.moc)
QT4_MOC(include/qtgroupboxpropertybrowser.h moc_qtgroupboxpropertybrowser.cpp)
QT4_MOC(include/qtpropertybrowser.h         moc_qtpropertybrowser.cpp)
QT4_MOC(include/qtpropertymanager.h         moc_qtpropertymanager.cpp)
QT4_MOC(src/qtpropertymanager.cpp           qtpropertymanager.moc)
QT4_MOC(include/qttreepropertybrowser.h     moc_qttreepropertybrowser.cpp)
QT4_MOC(src/qttreepropertybrowser.cpp       qttreepropertybrowser.moc)
QT4_MOC(include/qtvariantproperty.h         moc_qtvariantproperty.cpp)

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
