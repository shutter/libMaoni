# Copyright (c) 2009-2010 Daniel Pfeifer, University of Zurich

file(GLOB MAONI_COMMON_SOURCE *.cpp)

add_library(MaoniCommon STATIC ${MAONI_COMMON_SOURCE})
