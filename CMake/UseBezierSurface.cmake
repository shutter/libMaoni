# Copyright (c) 2010 Daniel Pfeifer, University of Zurich

# http://www.csit.fsu.edu/~burkardt/data/bezier_surface/bezier_surface.html
set(BEZIER_SURFACE_URL http://people.sc.fsu.edu/~burkardt/data/bezier_surface)
set(BEZIER_SURFACE_DIR ${CMAKE_BINARY_DIR}/bezier_surface)

include_directories(${BEZIER_SURFACE_DIR})

macro(BEZIER_SURFACE NAME)

  file(DOWNLOAD
    ${BEZIER_SURFACE_URL}/${NAME}_nodes.txt
    ${BEZIER_SURFACE_DIR}/${NAME}_nodes.txt
    )
  file(DOWNLOAD
    ${BEZIER_SURFACE_URL}/${NAME}_rectangles.txt
    ${BEZIER_SURFACE_DIR}/${NAME}_rectangles.txt
    )

  set(HEADER_FILE ${BEZIER_SURFACE_DIR}/${NAME}.h)
  set(SOURCE_FILE ${BEZIER_SURFACE_DIR}/${NAME}.c)

  file(WRITE ${HEADER_FILE} "")
  file(WRITE ${SOURCE_FILE} "#include \"${NAME}.h\"\n\n")
  
  file(STRINGS ${BEZIER_SURFACE_DIR}/${NAME}_nodes.txt NODES)
  list(LENGTH NODES NUMBER_OF_NODES)
  math(EXPR NUMBER_OF_FLOATS "${NUMBER_OF_NODES} * 3")
  file(APPEND ${HEADER_FILE} "extern float ${NAME}_nodes[${NUMBER_OF_FLOATS}];\n")
  file(APPEND ${SOURCE_FILE} "float ${NAME}_nodes[${NUMBER_OF_FLOATS}] = {\n")

  foreach(NODE ${NODES})
    separate_arguments(NODE)
    set(LINE "   ")
    foreach(FLOAT ${NODE})
      set(LINE "${LINE} ${FLOAT},")
    endforeach(FLOAT ${NODE})
    file(APPEND ${SOURCE_FILE} "${LINE}\n")
  endforeach(NODE ${NODES})

  file(APPEND ${SOURCE_FILE} "};\n\n")

  file(STRINGS ${BEZIER_SURFACE_DIR}/${NAME}_rectangles.txt RECTANGLES)
  list(LENGTH RECTANGLES NUMBER_OF_RECTANGLES) 
  math(EXPR NUMBER_OF_INTS "${NUMBER_OF_RECTANGLES} * 16")
  file(APPEND ${HEADER_FILE} "extern int ${NAME}_rectangles[${NUMBER_OF_INTS}];\n")
  file(APPEND ${SOURCE_FILE} "int ${NAME}_rectangles[${NUMBER_OF_INTS}] = {\n")

  foreach(RECTANGLE ${RECTANGLES})
    separate_arguments(RECTANGLE)
    set(LINE "   ")
    foreach(INT ${RECTANGLE})
      set(LINE "${LINE} ${INT},")
    endforeach(INT ${RECTANGLE})
    file(APPEND ${SOURCE_FILE} "${LINE}\n")
  endforeach(RECTANGLE ${RECTANGLES})

  file(APPEND ${SOURCE_FILE} "};\n")
  
  file(REMOVE ${BEZIER_SURFACE_DIR}/${NAME}_nodes.txt)
  file(REMOVE ${BEZIER_SURFACE_DIR}/${NAME}_rectangles.txt)

endmacro(BEZIER_SURFACE NAME)


set(BEZIER_SURFACE_SRC)
set(BEZIER_SURFACE_LIST "teacup;teapot;teaspoon")

foreach(NAME ${BEZIER_SURFACE_LIST})
  set(HEADER_FILE ${BEZIER_SURFACE_DIR}/${NAME}.h)
  set(SOURCE_FILE ${BEZIER_SURFACE_DIR}/${NAME}.c)
  
  if((NOT EXISTS ${HEADER_FILE}) OR (NOT EXISTS ${SOURCE_FILE}))
    bezier_surface(${NAME})
  endif((NOT EXISTS ${HEADER_FILE}) OR (NOT EXISTS ${SOURCE_FILE}))
  
  list(APPEND BEZIER_SURFACE_SRC ${SOURCE_FILE})
endforeach(NAME ${BEZIER_SURFACE_LIST})

add_library(bezier_surface STATIC ${BEZIER_SURFACE_SRC})
