# Copyright (c) 2009 Daniel Pfeifer, University of Zurich

find_package(Equalizer REQUIRED)

file(GLOB VMMVIEW_EQ_SOURCE src/Equalizer/*.c*)

add_library(VMMView_eq STATIC ${VMMVIEW_COMMON_SOURCE} ${VMMVIEW_EQ_SOURCE})

install(TARGETS VMMView VMMView_eq ARCHIVE DESTINATION lib)
