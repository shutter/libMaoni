# Copyright (c) 2009 Daniel Pfeifer, University of Zurich

find_package(Doxygen)
find_package(HTMLHelp)

function(ADD_DOCUMENTATION name)
  if(DOXYGEN_FOUND)

  set(FILE_LIST "")
  foreach(FILE ${ARGN})
    set(FILE_LIST "${FILE_LIST} ${FILE}")
  endforeach(FILE)

  set(DOXYFILE ${CMAKE_CURRENT_BINARY_DIR}/${name}.doxy)
  execute_process(
    COMMAND ${DOXYGEN} -s -g ${DOXYFILE}
    OUTPUT_QUIET ERROR_QUIET)

  if(DOXYGEN_DOT_EXECUTABLE)
    file(APPEND ${DOXYFILE} "HAVE_DOT       = YES\n")
  endif(DOXYGEN_DOT_EXECUTABLE)

  file(APPEND ${DOXYFILE} "EXTRACT_ALL      = YES\n")
  file(APPEND ${DOXYFILE} "OUTPUT_DIRECTORY = ${CMAKE_CURRENT_BINARY_DIR}\n")
  file(APPEND ${DOXYFILE} "HTML_OUTPUT      = ${name}-doc\n")
  file(APPEND ${DOXYFILE} "GENERATE_LATEX   = NO\n")
  file(APPEND ${DOXYFILE} "GENERATE_HTML    = YES\n")
  file(APPEND ${DOXYFILE} "GENERATE_XML     = NO\n")
  file(APPEND ${DOXYFILE} "INPUT            = ${FILE_LIST}\n")

  add_custom_target(${name}-doc
    COMMAND ${DOXYGEN} ${DOXYFILE}
    COMMENT "generating documentation for ${name}"
    DEPENDS ${ARGN})

  if(HTML_HELP_COMPILER)
  ## TODO: Implement this in Windows
  # SET (TMP "${CMAKE_CURRENT_BINARY_DIR}\\doc\\html\\index.hhp")
  # STRING(REGEX REPLACE "[/]" "\\\\" HHP_FILE ${TMP} )
  # ADD_CUSTOM_TARGET(winhelp ${HTML_HELP_COMPILER} ${HHP_FILE})
  # ADD_DEPENDENCIES (winhelp doc)
  endif(HTML_HELP_COMPILER)

  endif(DOXYGEN_FOUND)
endfunction(ADD_DOCUMENTATION name)
