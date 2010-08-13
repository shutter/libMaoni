// Copyright (c) 2010 Daniel Pfeifer, University of Zurich

#ifdef _MSC_VER
#  pragma warning(push)
#  //pragma warning(disable: 100)
#  pragma warning(disable: 244)
#  //pragma warning(disable: 324)
#  //pragma warning(disable: 512)
#endif

// wants to be included before Bool is defined
#include <QMetaType>
#include <eq/eq.h>

// <X.h> conflicts with <qcursor.h>
#undef CursorShape

// <X.h> conflicts with <qcoreevent.h>
#undef None
#undef KeyPress
#undef KeyRelease
#undef FocusIn
#undef FocusOut
#undef FontChange

#ifdef _MSC_VER
#  pragma warning(pop) 
#endif
