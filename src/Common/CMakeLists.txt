# Copyright (c) 2009-2010 Daniel Pfeifer, University of Zurich

file(GLOB MAONI_COMMON_SOURCE *.c*)

add_library(maoni_common STATIC ${MAONI_COMMON_SOURCE})
