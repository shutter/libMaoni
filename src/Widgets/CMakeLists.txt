# Copyright (c) 2009-2010 Daniel Pfeifer, University of Zurich

file(GLOB MAONI_WIDGETS_HPP *.hpp)
file(GLOB MAONI_WIDGETS_SRC *.cpp)

qt4_wrap_cpp(MAONI_WIDGETS_MOC ${MAONI_WIDGETS_HPP})
qt4_add_resources(MAONI_WIDGETS_RCC Resources.qrc)

add_library(MaoniWidgets STATIC
  ${MAONI_WIDGETS_SRC}
  ${MAONI_WIDGETS_MOC}
  ${MAONI_WIDGETS_RCC}
  )

add_dependencies(MaoniWidgets QtPropertyBrowser)
