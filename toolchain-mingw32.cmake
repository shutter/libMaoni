# the name of the target operating system
set(CMAKE_SYSTEM_NAME Windows)

# which compilers to use for C and C++
set(CMAKE_C_COMPILER   i586-mingw32msvc-gcc)
set(CMAKE_CXX_COMPILER i586-mingw32msvc-g++)

# here is the target environment located
set(CMAKE_FIND_ROOT_PATH /usr/i586-mingw32msvc)

# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search 
# programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE BOTH)

set(MAONI_DEPEND_LIB_PATH /home/daniel/mingw-install)

set(QT_QTCORE_LIBRARY_DEBUG     ${MAONI_DEPEND_LIB_PATH}/QtCored4.lib)
set(QT_QTCORE_LIBRARY_RELEASE   ${MAONI_DEPEND_LIB_PATH}/QtCore4.lib)
set(QT_QTGUI_LIBRARY_DEBUG      ${MAONI_DEPEND_LIB_PATH}/QtGuid4.lib)
set(QT_QTGUI_LIBRARY_RELEASE    ${MAONI_DEPEND_LIB_PATH}/QtGui4.lib)
set(QT_QTOPENGL_LIBRARY_DEBUG   ${MAONI_DEPEND_LIB_PATH}/QtOpenGLd4.lib)
set(QT_QTOPENGL_LIBRARY_RELEASE ${MAONI_DEPEND_LIB_PATH}/QtOpenGL4.lib)
set(QT_QTXML_LIBRARY_DEBUG      ${MAONI_DEPEND_LIB_PATH}/QtXmld4.lib)
set(QT_QTXML_LIBRARY_RELEASE    ${MAONI_DEPEND_LIB_PATH}/QtXml4.lib)

set(QGLVIEWER_LIBRARY           ${MAONI_DEPEND_LIB_PATH}/QGLViewer2.lib)

set(GLEW_INCLUDE_DIR            ${MAONI_DEPEND_LIB_PATH}/include)
set(GLEW_LIBRARY                ${MAONI_DEPEND_LIB_PATH}/glew32.lib)
