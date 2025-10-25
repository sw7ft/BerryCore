#ifndef _GLES_EGLTYPES_H_
#define _GLES_EGLTYPES_H_

#include <sys/types.h>

#ifndef APIENTRY
#ifdef _MSC_VER
#define APIENTRY __stdcall
#else
#define APIENTRY
#endif
#endif
#ifndef APIENTRYP
#define APIENTRYP APIENTRY *
#endif
#ifndef GLAPI
#define GLAPI extern
#endif

/*
 * Types and resources
 */
typedef int EGLBoolean;
typedef int EGLint;
typedef unsigned EGLenum;
typedef void *EGLDisplay;
typedef unsigned EGLConfig;
typedef void *EGLSurface;
typedef void *EGLContext;
typedef unsigned int EGLClientBuffer;

typedef void *NativeDisplayType;
typedef void *NativeWindowType;
typedef void *NativePixmapType;

/*
 * EGL and native handle values
 */
#define EGL_DEFAULT_DISPLAY	(NULL)
#define EGL_NO_CONTEXT		(NULL)
#define EGL_NO_DISPLAY		(NULL)
#define EGL_NO_SURFACE		(NULL)

#endif	/* _GLES_EGLTYPES_H_ */

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/khronos/devg/gles/egl/public/GLES/egltypes.h $ $Rev: 230948 $" )
