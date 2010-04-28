# - Try to find QGLViewer
# Once done this will define
#
#  QGLVIEWER_FOUND - system has QGLViewer
#  QGLVIEWER_INCLUDE_DIR - the QGLViewer include directory
#  QGLVIEWER_LIBRARY - Link these to use QGLViewer
#

find_path(QGLVIEWER_INCLUDE_DIR qglviewer.h
  /usr/include
  /usr/local/include
  /opt/local/include
  /usr/include/QGLViewer
  /usr/include/qglviewer-qt4
  $ENV{ProgramFiles}/libQGLViewer/QGLViewer
  )

find_library(QGLVIEWER_LIBRARY
  NAMES
    QGLViewer2
    qglviewer-qt4
  PATHS
    /usr/lib
    /usr/local/lib
    /opt/local/lib
    $ENV{ProgramFiles}/libQGLViewer
  )

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(QGLVIEWER
  DEFAULT_MSG QGLVIEWER_LIBRARY QGLVIEWER_INCLUDE_DIR)

mark_as_advanced(QGLVIEWER_INCLUDE_DIR QGLVIEWER_LIBRARY)

