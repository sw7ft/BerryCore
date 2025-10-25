/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_bbcascades_global_h
#define cascades_bbcascades_global_h

#include <QtCore/qglobal.h>

#ifndef BBCASCADES_STATIC_LINK
#  ifdef BBCASCADES_LIB
#    define BBCASCADES_EXPORT Q_DECL_EXPORT
#  else
#    define BBCASCADES_EXPORT Q_DECL_IMPORT
#  endif
#else
#  define BBCASCADES_EXPORT
#endif // !BBCASCADES_STATIC_LINK

#endif // !defined(cascades_bbcascades_global_h)

