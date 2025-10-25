#ifndef _GLES_EGL_H_
#define _GLES_EGL_H_

#include <GLES/gl.h>
#include <GLES/egltypes.h>

#define EGLAPI

#define EGL_VERSION_1_0                1
#define EGL_VERSION_1_1                1
#define EGL_VERSION_1_2                1

#define EGL_FALSE                      0
#define EGL_TRUE                       1

#define EGL_SUCCESS                    0x3000
#define EGL_NOT_INITIALIZED            0x3001
#define EGL_BAD_ACCESS                 0x3002
#define EGL_BAD_ALLOC                  0x3003
#define EGL_BAD_ATTRIBUTE              0x3004
#define EGL_BAD_CONFIG                 0x3005
#define EGL_BAD_CONTEXT                0x3006
#define EGL_BAD_CURRENT_SURFACE        0x3007
#define EGL_BAD_DISPLAY                0x3008
#define EGL_BAD_MATCH                  0x3009
#define EGL_BAD_NATIVE_PIXMAP          0x300A
#define EGL_BAD_NATIVE_WINDOW          0x300B
#define EGL_BAD_PARAMETER              0x300C
#define EGL_BAD_SURFACE                0x300D
#define EGL_CONTEXT_LOST               0x300E

#define EGL_BUFFER_SIZE                0x3020
#define EGL_ALPHA_SIZE                 0x3021
#define EGL_BLUE_SIZE                  0x3022
#define EGL_GREEN_SIZE                 0x3023
#define EGL_RED_SIZE                   0x3024
#define EGL_DEPTH_SIZE                 0x3025
#define EGL_STENCIL_SIZE               0x3026
#define EGL_CONFIG_CAVEAT              0x3027
#define EGL_CONFIG_ID                  0x3028
#define EGL_LEVEL                      0x3029
#define EGL_MAX_PBUFFER_HEIGHT         0x302A
#define EGL_MAX_PBUFFER_PIXELS         0x302B
#define EGL_MAX_PBUFFER_WIDTH          0x302C
#define EGL_NATIVE_RENDERABLE          0x302D
#define EGL_NATIVE_VISUAL_ID           0x302E
#define EGL_NATIVE_VISUAL_TYPE         0x302F
#define EGL_SAMPLES                    0x3031
#define EGL_SAMPLE_BUFFERS             0x3032
#define EGL_SURFACE_TYPE               0x3033
#define EGL_TRANSPARENT_TYPE           0x3034
#define EGL_TRANSPARENT_BLUE_VALUE     0x3035
#define EGL_TRANSPARENT_GREEN_VALUE    0x3036
#define EGL_TRANSPARENT_RED_VALUE      0x3037
#define EGL_BIND_TO_TEXTURE_RGB        0x3039
#define EGL_BIND_TO_TEXTURE_RGBA       0x303A
#define EGL_MAX_SWAP_INTERVAL          0x303B
#define EGL_MIN_SWAP_INTERVAL          0x303C
#define EGL_LUMINANCE_SIZE             0x3101
#define EGL_COLOR_BUFFER_TYPE          0x3102
#define EGL_RENDERABLE_TYPE            0x3103
#define EGL_RENDER_BUFFER              0x3104
#define EGL_HORIZONTAL_RESOLUTION      0x3105
#define EGL_VERTICAL_RESOLUTION        0x3106
#define EGL_PIXEL_ASPECT_RATIO         0x3107
#define EGL_SWAP_BEHAVIOR              0x3108
#define EGL_UNKNOWN                    0x3109
#define EGL_BUFFER_PRESERVED           0x310A
#define EGL_OPENVG_IMAGE               0x310B
#define EGL_OPENVG_API                 0x310C
#define EGL_CONTEXT_CLIENT_TYPE        0x310D
#define EGL_OPENGL_ES_API              0x310E
#define EGL_BUFFER_DESTROYED           0x310F
#define EGL_ALPHA_MASK_SIZE            0x3110
#define EGL_ALPHA_FORMAT               0x3111
#define EGL_COLORSPACE                 0x3112
#define EGL_ALPHA_FORMAT_NONPRE        0x3113
#define EGL_ALPHA_FORMAT_PRE           0x3114
#define EGL_SINGLE_BUFFER              0x3115
#define EGL_COLORSPACE_sRGB            0x3116
#define EGL_COLORSPACE_LINEAR          0x3117

#define EGL_NONE                       0x3038

#define EGL_DONT_CARE                  ((EGLint) -1)
#define EGL_PBUFFER_BIT                0x01
#define EGL_PIXMAP_BIT                 0x02
#define EGL_WINDOW_BIT                 0x04
#define EGL_SLOW_CONFIG                0x3050
#define EGL_NON_CONFORMANT_CONFIG      0x3051
#define EGL_TRANSPARENT_RGB            0x3052
#define EGL_NO_TEXTURE                 0x305C
#define EGL_TEXTURE_RGB                0x305D
#define EGL_TEXTURE_RGBA               0x305E
#define EGL_TEXTURE_2D                 0x305F
#define EGL_OPENVG_BIT                 0x01
#define EGL_OPENGL_ES_BIT              0x02
#define EGL_RGB_BUFFER                 0x01
#define EGL_LUMINANCE_BUFFER           0x02

#define EGL_DISPLAY_SCALING            10000

/* String names */
#define EGL_VENDOR                     0x3053
#define EGL_VERSION                    0x3054
#define EGL_EXTENSIONS                 0x3055
#define EGL_CLIENT_APIS                0x3100

#define EGL_HEIGHT                     0x3056
#define EGL_WIDTH                      0x3057
#define EGL_LARGEST_PBUFFER            0x3058
#define EGL_TEXTURE_FORMAT             0x3080
#define EGL_TEXTURE_TARGET             0x3081
#define EGL_MIPMAP_TEXTURE             0x3082
#define EGL_MIPMAP_LEVEL               0x3083

#define EGL_BACK_BUFFER                0x3084

#define EGL_DRAW                       0x3059
#define EGL_READ                       0x305A

#define EGL_CORE_NATIVE_ENGINE         0x305B

#ifdef __cplusplus
extern "C" {
#endif

EGLAPI EGLint APIENTRY eglGetError (void);

EGLAPI EGLDisplay APIENTRY eglGetDisplay (NativeDisplayType display);
EGLAPI EGLBoolean APIENTRY eglInitialize (EGLDisplay dpy, EGLint *major, EGLint *minor);
EGLAPI EGLBoolean APIENTRY eglTerminate (EGLDisplay dpy);
EGLAPI const char * APIENTRY eglQueryString (EGLDisplay dpy, EGLint name);
EGLAPI void (* APIENTRY eglGetProcAddress (const char *procname))();

EGLAPI EGLBoolean APIENTRY eglGetConfigs (EGLDisplay dpy, EGLConfig *configs, EGLint config_size, EGLint *num_config);
EGLAPI EGLBoolean APIENTRY eglChooseConfig (EGLDisplay dpy, const EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *num_config);
EGLAPI EGLBoolean APIENTRY eglGetConfigAttrib (EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *value);

EGLAPI EGLSurface APIENTRY eglCreateWindowSurface (EGLDisplay dpy, EGLConfig config, NativeWindowType window, const EGLint *attrib_list);
EGLAPI EGLSurface APIENTRY eglCreatePixmapSurface (EGLDisplay dpy, EGLConfig config, NativePixmapType pixmap, const EGLint *attrib_list);
EGLAPI EGLSurface APIENTRY eglCreatePbufferSurface (EGLDisplay dpy, EGLConfig config, const EGLint *attrib_list);
EGLAPI EGLBoolean APIENTRY eglDestroySurface (EGLDisplay dpy, EGLSurface surface);
EGLAPI EGLBoolean APIENTRY eglQuerySurface (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint *value);

EGLAPI EGLBoolean APIENTRY eglSurfaceAttrib (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint value);
EGLAPI EGLBoolean APIENTRY eglBindTexImage (EGLDisplay dpy, EGLSurface surface, EGLint buffer);
EGLAPI EGLBoolean APIENTRY eglReleaseTexImage (EGLDisplay dpy, EGLSurface surface, EGLint buffer);

EGLAPI EGLContext APIENTRY eglCreateContext (EGLDisplay dpy, EGLConfig config, EGLContext share_list, const EGLint *attrib_list);
EGLAPI EGLBoolean APIENTRY eglDestroyContext (EGLDisplay dpy, EGLContext ctx);
EGLAPI EGLBoolean APIENTRY eglMakeCurrent (EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx);
EGLAPI EGLContext APIENTRY eglGetCurrentContext (void);
EGLAPI EGLSurface APIENTRY eglGetCurrentSurface (EGLint readdraw);
EGLAPI EGLDisplay APIENTRY eglGetCurrentDisplay (void);
EGLAPI EGLBoolean APIENTRY eglQueryContext (EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint *value);

EGLAPI EGLBoolean APIENTRY eglSwapInterval (EGLDisplay dpy, EGLint interval);

EGLAPI EGLBoolean APIENTRY eglWaitGL (void);
EGLAPI EGLBoolean APIENTRY eglWaitNative (EGLint engine);
EGLAPI EGLBoolean APIENTRY eglSwapBuffers (EGLDisplay dpy, EGLSurface draw);
EGLAPI EGLBoolean APIENTRY eglCopyBuffers (EGLDisplay dpy, EGLSurface surface, NativePixmapType target);

EGLAPI EGLSurface APIENTRY eglCreatePbufferFromClientBuffer (EGLDisplay dpy, EGLenum buftype, EGLClientBuffer buffer, EGLConfig config, const EGLint *attrib_list);
EGLAPI EGLBoolean APIENTRY eglWaitClient (void);
EGLAPI EGLBoolean APIENTRY eglBindAPI (EGLenum api);
EGLAPI EGLenum APIENTRY eglQueryAPI (void);

EGLAPI EGLBoolean APIENTRY eglReleaseThread(void);

#ifdef __cplusplus
}
#endif

#endif /* _GLES_EGL_H_ */

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/khronos/devg/gles/egl/public/GLES/egl.h $ $Rev: 219996 $" )
