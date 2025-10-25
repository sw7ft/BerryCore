/*
 * $QNXLicenseC:
 * Copyright 2010, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable
 * license fees to QNX Software Systems before you may reproduce,
 * modify or distribute this software, or any work that includes
 * all or part of this software.   Free development licenses are
 * available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email
 * licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review
 * this entire file for other proprietary rights or license notices,
 * as well as the QNX Development Suite License Guide at
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */
/**
*   @file screen.h
*   @brief Functions for the Screen library
*
*   This file defines Screen API functions that are supported by
*   the Screen library. The Screen API facilitates the communication
*   between applications and Screen services.
*/
 /**
*   @mainpage Screen library overview
*
*   Screen library supports the API functions that facilitate the
*   communication between applications and the Screen
*   services.
*/

/**
*   @defgroup screen_contexts Contexts
*   @defgroup screen_windows Windows
*   @defgroup screen_devices Devices
*   @defgroup screen_groups Groups
*   @defgroup screen_buffers Buffers
*   @defgroup screen_pixmaps Pixmaps
*   @defgroup screen_blits Blits
*   @defgroup screen_displays Displays
*   @defgroup screen_effects Effects
*   @defgroup screen_events Events
*   @defgroup screen_debugging Debugging
*   @defgroup screen_sessions Sessions
*/

#ifndef _SCREEN_SCREEN_H_
#define _SCREEN_SCREEN_H_

#include <process.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/neutrino.h>

__BEGIN_DECLS

/**
*   @ingroup screen_contexts
*/
struct _screen_context;

/**
* @brief A handle for the screen context
* @details This handle is used to identify the scope of the relationship with
*          the underlying windowing system. A handle to the screen context is
*          used to:
*          - create screen API objects
*          - retrieve and send events
*/
typedef struct _screen_context *screen_context_t;

/**
* @ingroup screen_displays
*/
struct _screen_display;

/**
* @brief A handle for the screen display
*/
typedef struct _screen_display *screen_display_t;

/**
* @ingroup screen_windows
*/
struct _screen_window;

/**
* @brief A handle for the screen window.
* @details This handle is used to identify the window that you are performing
*          actions on. Such actions could include:
*          - querying or setting properties
*          - posting
*          - sharing buffers
*/
typedef struct _screen_window *screen_window_t;

/**
*   @ingroup screen_pixmaps
*/
struct _screen_pixmap;

/**
* @brief A handle for the screen pixmap
*/
typedef struct _screen_pixmap *screen_pixmap_t;

/**
*   @ingroup screen_buffers
*/
struct _screen_buffer;

/**
* @brief A handle for the screen buffer
*/
typedef struct _screen_buffer *screen_buffer_t;

/**
*   @ingroup screen_events
*/
struct _screen_event;

/**
* @brief A handle for the screen event
*/
typedef struct _screen_event *screen_event_t;

/**
*   @ingroup screen_groups
*/
struct _screen_group;

/**
* @brief A handle for the screen group
*/
typedef struct _screen_group *screen_group_t;

/**
*   @ingroup screen_devices
*/
struct _screen_device;

/**
* @brief A handle for the screen device
*/
typedef struct _screen_device *screen_device_t;

/**
*   @ingroup screen_sessions
*/
struct _screen_session;

/**
* @brief A handle for the screen session
*/
typedef struct _screen_session *screen_session_t;

/**
*   @addtogroup screen_contexts
*   @{
*/
/** @brief The types of context masks
*
*          These bits are intended to be combined in a single integer
*          representing combinations of desired privileges to be applied to a
*          context.
*   @anonenum Screen_Context_Types Screen context types
*/
enum {
	/** A context type that allows a process to create its own windows
	*   and control some of the window properties. Applications can't modify
	*   windows that were created by other applications and can't send
	*   events outside their process space. Application contexts aren't
	*   aware of other top-level windows in the system; neither are they
	*   allowed to operate on them. Application contexts are allowed to
	*   parent other windows, even if they are created in other contexts
	*   in other processes, and are allowed to control those windows.
	*   Application contexts that have read/write access to /dev/screen/.inject
	*   can inject Screen events.
	*/
	SCREEN_APPLICATION_CONTEXT = 0,

	/** A context type that requests a privileged context to allow
	*   a process to modify all windows in the system when new application
	*   windows are created or destroyed. The context also receives notifications
	*   when applications create new windows, existing application
	*   windows are destroyed, or when an application tries to change
	*   certain window properties. A process must have a user or group ID with
	*   read/write access to /dev/screen/.winmgr, to create a context of this
	*   type successfully.
	*/
	SCREEN_WINDOW_MANAGER_CONTEXT = (1 << 0),

	/** A context type that requests a privileged context to allow a
	*   process to send events to any application in the system. This context
	*   type doesn't receive notifications when applications create new windows,
	*   when applications destroy existing windows, or when an application
	*   attempts to change certain window properties. A process must have a
	*   user or group ID with read/write access to /dev/screen/.provider, to
	*   create a context of this type successfully.
	*/
	SCREEN_INPUT_PROVIDER_CONTEXT = (1 << 1),

	/** A context type that requests a privileged context to provide
	*   access to power management functionality in order to change display
	*   power modes. A process must have a user or group ID with read/write
	*   access to /dev/screen/.powmgr, to create a context of this type
	*   successfully.
	*/
	SCREEN_POWER_MANAGER_CONTEXT = (1 << 2),

	/** A context type that requests a privileged context to allow a
	*   process to modify all display properties in the system. A process must
	*   have an effective user ID of root to create a context of this type
	*   successfully. A process must have a user or group ID with read/write
	*   access to /dev/screen/.dpymgr, to create a context of this type
	*   successfully.
	*/
	SCREEN_DISPLAY_MANAGER_CONTEXT = (1 << 3),

	/** A context type that requests a privileged context to allow a
	*   process to be notified of all input sessions created and to modify
	*   specific session properties. A process must have a user or group ID with
	*   read/write access to /dev/screen/.inmgr, to create a context of this
	*   type successfully.
	*/
	SCREEN_INPUT_MANAGER_CONTEXT = (1 << 4),
};
/** @} */

/**
*   @addtogroup screen_windows
*   @{
*/
 /** @brief Types of windows that can be created
 *   @anonenum Screen_Window_Types Screen window types
 */
enum {
	/** A window type used to display the main application. The X and
	*   Y coordinates are always relative to the dimensions of the display.
	*/
	SCREEN_APPLICATION_WINDOW = 0,

	/** A window type commonly used to display a dialog. You must add a
	*   child window to an application's window group; otherwise the child
	*   window is invisible. A child window's display properties are relative
	*   to the application window to which it belongs. For example, the X and Y
	*   coordinates of the child window are all relative to the top left corner
	*   of the application window. This window type has its property,
	*   @c #SCREEN_PROPERTY_FLOATING, defaulted to indicate that the window
	*   is floating.
	*/
	SCREEN_CHILD_WINDOW = 1,

	/** A window type used to embed a window control within an object.
	*   Like the child window, the X and Y coordinates of the embedded window
	*   are all relative to the top left corner of the application window.
	*   You must add an embedded window to an application's window group,
	*   otherwise the embedded window is invisible. This window type has its
	*   property, @c #SCREEN_PROPERTY_FLOATING, defaulted to indicate that
	*   the window is non-floating.
	*/
	SCREEN_EMBEDDED_WINDOW = 2,

	/*   This window type is not used and will throw an error */
	SCREEN_ROOT_WINDOW = 3,
};
/** @} */

/** @brief Types of properties that are associated with Screen API objects
*
*   Full read/write access to Screen API object properties is product dependent.
*   @anonenum Screen_Property_Types Screen property types
*/
enum {
	/** A single integer that defines how alpha should be interpreted. The alpha
	*  mode must be of type <a href="screen_8h_1Screen_Alpha_Mode_Types.xml">Screen alpha mode types</a>.
	*  When retrieving or setting this property type, ensure that you have
	*  sufficient storage for one integer. The following API objects have this
	*  property and share this same definition:
	*   - pixmap
	*   - window
	*       - In the configuration file, the value of this property can
	*         be set so that windows of a specified class will have this property
	*         initialized to the value. The following are valid settings that
	*         can be used for this property in graphics.conf:
	*           - alpha-mode = pre-multipled
	*           - alpha-mode = non-pre-multipled
	*/
	SCREEN_PROPERTY_ALPHA_MODE = 1,

	/** A single integer that indicates the gamma value of the current display;
	*   a property of a display object. When retrieving or setting this property
	*   type, ensure that you provide sufficient storage for one integer.
	*/
	SCREEN_PROPERTY_GAMMA = 2,

	/** A single integer between @c [-255..255] that is used to adjust the
	*   brightness of a window; a property of a window object. When retrieving
	*   or setting this property type, ensure that you have sufficient storage for
	*   one integer. In the configuration file, graphics.conf, the value of this
	*   property can be set so that windows of a specified class will have this
	*   property initialized to the value. The following is the usage for setting
	*   this property in graphics.conf:
	*  - brightness = @c [brightness -255..255]
	*/
	SCREEN_PROPERTY_BRIGHTNESS = 3,

	/** A single integer that indicates the number of buffers that were created
	*   or attached to the window; a property of a window object. When
	*   retrieving this property type, ensure that you have sufficient storage
	*   for one integer. Also note that this property is local to the window object.
	*   This means that a query for this property will not trigger a flush of the
	*   command buffer despite that @c screen_get_window_property_iv() is of type
	*   flushing execution. In the configuration file, graphics.conf, the value
	*   of this property can be set so that windows of a specified class will
	*   have this property initialized to the value (beyond initialization, this property
	*   can only queried and not set. The following is the usage for setting this
	*   property in graphics.conf:
	*   - buffer-count = @c [number of buffers]
	*/
	SCREEN_PROPERTY_BUFFER_COUNT = 4,

	/**
	*   A pair of integers containing the width and height, in pixels, of the buffer.
	*   When retrieving or setting this property type, ensure that you provide
	*   sufficient storage for two integers. The following API objects have
	*   this property and share this same definition:
	*   - buffer
	*   - pixmap
	*   - window
	*       - In the configuration file, the value of this property can
	*         be set so that windows of a specified class will have this property
	*         initialized to the value. The following is the usage for setting
	*         this property in graphics.conf:
	*           - surface-size @c [width] x @c [height]
	*/
	SCREEN_PROPERTY_BUFFER_SIZE = 5,

	/** A single integer which is a bitmask indicating which buttons are
	*   pressed; a property of an event object or device object. Note that D-pad,
	*   A, B, X, Y, Start, Select, Left, and Right are all considered buttons on
	*   gamepads. Currently, there is no button-map on gamepads equivalent to
	*   keymaps for keyboards. When retrieving this property type, ensure that
	*   you provide sufficient storage for one integer.
	*   The @c #SCREEN_PROPERTY_BUTTONS property is applicable to the following
	*   events and device types:
	*   - @c #SCREEN_EVENT_GAMEPAD
	*   - @c #SCREEN_EVENT_JOG
	*   - @c #SCREEN_EVENT_JOYSTICK
	*   - @c #SCREEN_EVENT_MTOUCH_PRETOUCH
	*   - @c #SCREEN_EVENT_MTOUCH_TOUCH
	*   - @c #SCREEN_EVENT_MTOUCH_MOVE
	*   - @c #SCREEN_EVENT_MTOUCH_RELEASE
	*   - @c #SCREEN_EVENT_POINTER:
	*        In the case of a pointer, @c #SCREEN_PROPERTY_BUTTONS must be
	*        a combination of type
	*        <a href="screen_8h_1Screen_Mouse_Button_Types.xml"> Screen mouse button types</a>.
	*/
	SCREEN_PROPERTY_BUTTONS = 6,

	/** The name of a class as defined in the configuration file, graphics.conf;
	*   a property of a window object. The class specifies a set of window
	*   property and value pairs which will be applied to the window as initial or
	*   or default values. When retrieving or setting this property
	*   type, ensure that you have sufficient storage for a character buffer.
	*/
	SCREEN_PROPERTY_CLASS = 7,

	/** A single integer that indicates the color space of a buffer.
	*   The color space must be of type <a href="screen_8h_1Screen_Color_Space_Types.xml">Screen color space types</a>.
	*   The default value is @c #SCREEN_COLOR_SPACE_UNCORRECTED.
	*   When retrieving or setting this property type, ensure that you have
	*   sufficient storage for one integer. The following API
	*   objects have this property and share this same definition:
	*   - pixmap
	*   - window
	*/
	SCREEN_PROPERTY_COLOR_SPACE = 8,

	/** A single integer between @c [-128..127] that is used to adjust the
	*   contrast of a window; a property of a window object. When retrieving
	*   or setting this property type, ensure that you have sufficient storage
	*   for one integer. In the configuration file, graphics.conf, the value of
	*   this property can be set so that windows of a specified class will have
	*   this property initialized to the value. The following is the usage for
	*   setting this property in graphics.conf:
	*   - contrast = @c [window contrast -128..127]
	*/
	SCREEN_PROPERTY_CONTRAST = 9,

	/** A single integer representing the object handle for the input device that
	*   the event came from; a property of an event object. When retrieving this
	*   property type, ensure that you provide sufficient storage for one integer.
	*   The @c  #SCREEN_PROPERTY_DEVICE property is applicable to the
	*   following events:
	*   - @c #SCREEN_EVENT_GAMEPAD
	*   - @c #SCREEN_EVENT_INPUT
	*   - @c #SCREEN_EVENT_JOG
	*   - @c #SCREEN_EVENT_JOYSTICK
	*   - @c #SCREEN_EVENT_KEYBOARD
	*   - @c #SCREEN_EVENT_MTOUCH_PRETOUCH
	*   - @c #SCREEN_EVENT_MTOUCH_TOUCH
	*   - @c #SCREEN_EVENT_MTOUCH_MOVE
	*   - @c #SCREEN_EVENT_MTOUCH_RELEASE
	*   - @c #SCREEN_EVENT_POINTER
	*   - @c #SCREEN_EVENT_DEVICE
	*/
	SCREEN_PROPERTY_DEVICE = 10,

	/** @deprecated This property has been deprecated.
	*   Use @c #SCREEN_PROPERTY_DEVICE instead. */
	SCREEN_PROPERTY_DEVICE_INDEX = 10,

	/** A display handle. When retrieving or setting this property type, ensure
	*   that you have sufficient storage for one @c void pointer. The following
	*   API objects have this property, each with its own variant of the
	*   definition:
	*   - device:
	*           The display that is the focus for the specified input device. A value
	*           of @c NULL indicates that the input device is focused on the
	*           default display.
	*   - event:
	*           - In the case of the @c #SCREEN_EVENT_PROPERTY event,
	*             @c #SCREEN_PROPERTY_DISPLAY is the property of either
	*             a device or a window, depending on the recipient object of the
	*             event.
	*           - In the case of the @c #SCREEN_EVENT_DISPLAY event,
	*             @c #SCREEN_PROPERTY_DISPLAY is the handle of the new
	*             external display that has been detected.
	*           - In the case of the @c #SCREEN_EVENT_IDLE event,
	*             @c #SCREEN_PROPERTY_DISPLAY is the handle of the
	*             display in which a window entered an idle state.
	*   - session:
	*           The display associated with the specified input session if the
	*           session is active. When a session is linked to a window, the
	*           session and the window have the same display.
	*   - window:
	*           The display on which the specified window will be shown if the
	*           window is visible. A value of @c NULL indicates that the window
	*           will be shown on the default display. Note that setting
	*            @c #SCREEN_PROPERTY_DISPLAY invalidates the pipeline.
	*           In the configuration file, graphics.conf, the value of this property
	*           can be set so that windows of a specified class will have its
	*           property initialized to this value. The following are valid settings
	*           that can be used for this property in graphics.conf:
	*           - display = internal
	*           - display = composite
	*           - display = svideo
	*           - display = YPbPr
	*           - display = rgb
	*           - display = rgbhv
	*           - display = dvi
	*           - display = hdmi
	*           - display = @c [display id]
	*/
	SCREEN_PROPERTY_DISPLAY = 11,

	/** A handle to the EGL driver; a property of a buffer object.
	*   When retrieving or setting this property type, ensure that you provide
	*   sufficient storage for one @c void pointer.
	*/
	SCREEN_PROPERTY_EGL_HANDLE = 12,

	/** A single integer that indicates whether or not the window contents are
	*   flipped; a property of a window object. When retrieving or setting this
	*   property type, ensure that you have sufficient storage for one integer.
	*/
	SCREEN_PROPERTY_FLIP = 13,

	/** A single integer that indicates the pixel format of the buffer. The format
	*   must be of type <a href="screen_8h_1Screen_Pixel_Format_Types.xml">Screen pixel format types</a>.
	*   When retrieving or setting this property type, ensure that you provide
	*   sufficient storage for one integer.  The following API objects have this
	*   property and share this same definition:
	*   - buffer
	*   - pixmap
	*   - window
	*           -  In the configuration file, graphics.conf, the value of this property
	*              can be set so that windows of a specified class will have its
	*              property initialized to this value. The following are valid settings
	*              that can be used for this property in graphics.conf:
	*               - format = byte
	*               - format = rgba4444
	*               - format = rgbx4444
	*               - format = rgba5551
	*               - format = rgbx5551
	*               - format = rgb565
	*               - format = rgb888
	*               - format = rgba8888
	*               - format = rgbx8888
	*               - format = yvu9
	*               - format = nv12
	*               - format = yv12
	*               - format = uyvy
	*               - format = yuy2
	*               - format = yvyu
	*               - format = v422
	*               - format = ayuv
	*               - format = @c [pixel format type 0..16]
	*/
	SCREEN_PROPERTY_FORMAT = 14,

	/** A handle to the last buffer of the window to have been posted;
	*   a property of a window object. When retrieving this property type,
	*   ensure that you have sufficient storage for one @c void pointer.
	*/
	SCREEN_PROPERTY_FRONT_BUFFER = 15,

	/** A single integer that indicates the global alpha value to be applied to
	*   the window; a property of a window object. This value must be
	*   between @c 0 and @c 255. When retrieving or setting this property
	*   type, ensure that you have sufficient storage for one integer.
	*  In the configuration file, graphics.conf, the value of this property can
	*  be set so that windows of a specified class will have this property
	*  initialized to the value. The following is the usage for setting this
	*  property in graphics.conf:
	*   - global-alpha = @c [global alpha 0..255]	*/
	SCREEN_PROPERTY_GLOBAL_ALPHA = 16,

	/** A single integer that contains the pipeline ID; a property of a window
	*   object.
	*
	*   Layers are exposed as pipelines to display controllers. So, you have
	*   to choose the pipeline and/or layer on which you want to display a
	*   window. You must determine the pipelines that are on your system.
	*
	*   Pipeline ordering and the z-ordering of windows on a layer are not
	*   related to each other. If your application assigns pipelines manually,
	*   it must ensure that the z-order values makes sense with regard to the
	*   pipeline order of the target hardware. Pipeline ordering takes precedence
	*   over z-ordering operations in the Screen Library. The Screen Library
	*   does not have control over the ordering of hardware pipelines -- it
	*   always arranges windows in the z-order specified by the application.
	*
	*   If you assign a framebuffer to the top layer in a graphics configuration
	*   on a non-composited window (which does not have the correct z-order
	*   set), your application cannot display a new window (no matter its
	*   z-order) above the framebuffer. The same constraint applies if you
	*   assign a framebuffer to the bottom layer of a graphics configuration.
	*   In this case, your application cannot display a window below the
	*   framebuffer.
	*
	*   You need to set the @c #SCREEN_USAGE_OVERLAY flag in
	*   @c #SCREEN_PROPERTY_USAGE. Otherwise, Screen will ignore
	*   @c #SCREEN_PROPERTY_PIPELINE.
	*
	*   In the configuration file, graphics.conf, the value of this property can
	*   be set so that windows of a specified class will have this property
	*   initialized to the value. The following is the usage for setting this
	*   property in graphics.conf:
	*    - pipeline = @c [pipline id]
	*/
	SCREEN_PROPERTY_PIPELINE = 17,

	/**  The group that the API object is associated with.
	*    When retrieving or setting this property type, ensure that you have
	*    sufficient storage according to the definition of the property for the
	*    specific API object. The following API objects have this property, each
	*    with its own variant of this definition(s):
	*   - event:
	*       The window group that is associated with the event.
	*       @c #SCREEN_PROPERTY_GROUP is applicable for the following
	*       events:
	*           - @c #SCREEN_EVENT_IDLE
	*                   The pointer to a group of type @c #screen_group_t that has
	*                   changed to idle state.
	*           - @c #SCREEN_EVENT_PROPERTY
	*                   The pointer to a group of type @c #screen_group_t that has had a
	*                   property changed.
	*           - @c #SCREEN_EVENT_CREATE
	*                   The name of the group that the window has joined. Typically
	*                   this property would be relevant only to a
	*                   @c #SCREEN_EVENT_CREATE event for a child or embedded
	*                   window. For an application window, the @c #SCREEN_EVENT_CREATE
	*                   is forwarded to the windowing system immediately and will have no
	*                   group associated with it. However, a @c #SCREEN_EVENT_CREATE
	*                   event for a child or embedded window does not really exist unless it is
	*                   associated with a parent (window group). Therefore, the
	*                   @c #SCREEN_EVENT_CREATE event for a child or embedded window
	*                   has a group association.
	*   - pixmap:
	*           - The name of the group that the pixmap is associated with when
	*             @c #SCREEN_PROPERTY_GROUP is used with
	*             @c screen_get_pixmap_property_cv(). When retrieving this
	*             property type, ensure that you have sufficient storage for a
	*             character buffer.
	*           - The pointer to a group of type @c #screen_group_t, that the
	*              pixmap is associated with when @c #SCREEN_PROPERTY_GROUP
	*              is used with @c screen_get_pixmap_property_pv(). When
	*              retrieving this property type, ensure that you have sufficient
	*              storage for a structure of type @c #screen_group_t.
	*   - window
	*           - The name of the group that the window has created or parented when
	*             @c #SCREEN_PROPERTY_GROUP is used with
	*             @c screen_get_window_property_cv(). When retrieving this
	*             property type, ensure that you have sufficient storage for a
	*             character buffer. If the window has not created or parented a group, then
	*             this property refers to the group that the window has joined.
	*           - The pointer to a group of type @c #screen_group_t, that the
	*              window has created or parented when @c #SCREEN_PROPERTY_GROUP
	*              is used with @c screen_get_window_property_pv(). When
	*              retrieving this property type, ensure that you have sufficient
	*              storage for a for a structure of type @c #screen_group_t. If the window
	*              has not created or parented a group, then this property refers to the
	*              group that the window has joined.
	*/
	SCREEN_PROPERTY_GROUP = 18,

	/** A single integer between @c [-128..127] that is used to adjust the hue
	*   of a window; a property of a window object. When retrieving or setting
	*   this property type, ensure that you have sufficient storage for one
	*   integer. In the configuration file, graphics.conf, the value of this property
	*   can be set so that windows of a specified class will have this property
	*   initialized to the value. The following is the usage for setting this
	*   property in graphics.conf:
	*   - hue = @c [global alpha -128..127]
	*/
	SCREEN_PROPERTY_HUE = 19,

	/** A string that can be used by window manager or parent to identify the
	*   contents of the specified API object. When retrieving or setting this
	*   property type, ensure that you provide a character buffer. The following
	*   API objects have this property and share this same definition:
	*   - device
	*   - display (@c #SCREEN_PROPERTY_ID_STRING can only be retrieved
	*                  and not set for a display object)
	*   - pixmap
	*   - session
	*   - window
	*       - In the configuration file, graphics.conf, the value of this property can
	*         be set so that windows of a specified class will have this property
	*         initialized to the value. The following is the usage for setting this
	*         property in graphics.conf:
	*           - id_string = @c [string]
	*/
	SCREEN_PROPERTY_ID_STRING = 20,

	/** A single integer that indicates the input value associated with the
	*   specific event; a property of an event object. When retrieving or setting
	*   this property type, ensure that you provide sufficient storage for one
	*   integer. @c #SCREEN_PROPERTY_INPUT_VALUE is applicable only
	*   to a @c #SCREEN_EVENT_INPUT event.
	*/
	SCREEN_PROPERTY_INPUT_VALUE = 21,

	/** A single integer that indicates whether or not the buffer contains
	*   interlaced fields instead of progressive data; a property of a buffer
	*   object. When retrieving or setting this property type, ensure that you
	*   provide sufficient storage for one integer.
	*/
	SCREEN_PROPERTY_INTERLACED = 22,

	/** A single integer that indicates the jog count associated with the
	*   specific event; a property of an event object. When retrieving or setting
	*   this property type, ensure that you provide sufficient storage for one
	*   integer. @c #SCREEN_PROPERTY_JOG_COUNT is applicable only to
	*   a @c #SCREEN_EVENT_JOG event.
	*/
	SCREEN_PROPERTY_JOG_COUNT = 23,

	/** A single integer that indicates the keyboard cap associated with the
	*   specific event; a property of an event object. When retrieving or setting
	*   this property type, ensure that you provide sufficient storage for one
	*   integer. @c #SCREEN_PROPERTY_KEY_CAP is applicable only to
	*   a @c #SCREEN_EVENT_KEYBOARD event.
	*/
	SCREEN_PROPERTY_KEY_CAP = 24,

	/** A single integer that indicates the flags associated with the
	*   specific event; a property of an event object. When retrieving or setting
	*   this property type, ensure that you provide sufficient storage for one
	*   integer. @c #SCREEN_PROPERTY_FLAGS is applicable for the following
	*   events:
	*   - @c #SCREEN_EVENT_GESTURE
	*   - @c #SCREEN_EVENT_KEYBOARD
	*   - @c #SCREEN_EVENT_POINTER
	*/
	SCREEN_PROPERTY_FLAGS = 25,

	/** See @c #SCREEN_PROPERTY_FLAGS. */
	SCREEN_PROPERTY_KEY_FLAGS = 25,

	/** A single integer that indicates the modifiers associated with
	*   the specific API object. When retrieving or setting this property type,
	*   ensure that you provide sufficient storage for one integer. The
	*   following API objects have this property and share this same definition:
	*   - display(@c #SCREEN_PROPERTY_MODIFIERS can only be retrieved
	*                  and not set for a display object)
	*   - device
	*   - event:
	*       This is only applicable for the following events:
	*           - @c #SCREEN_EVENT_GAMEPAD
	*           - @c #SCREEN_EVENT_GESTURE
	*           - @c #SCREEN_EVENT_JOG
	*           - @c #SCREEN_EVENT_JOYSTICK
	*           - @c #SCREEN_EVENT_KEYBOARD
	*           - @c #SCREEN_EVENT_MTOUCH_MOVE
	*           - @c #SCREEN_EVENT_MTOUCH_PRETOUCH
	*           - @c #SCREEN_EVENT_MTOUCH_RELEASE
	*           - @c #SCREEN_EVENT_MTOUCH_TOUCH
	*           - @c #SCREEN_EVENT_POINTER
	*/
	SCREEN_PROPERTY_MODIFIERS = 26,

	/** See @c #SCREEN_PROPERTY_MODIFIERS. */
	SCREEN_PROPERTY_KEY_MODIFIERS = 26,

	/** A single integer that indicates the scan code associated with the
	*   specific event; a property of an event object. When retrieving or
	*   setting this property type, ensure that you provide sufficient storage
	*   for one integer. @c #SCREEN_PROPERTY_SCAN is applicable only to
	*   @c #SCREEN_EVENT_KEYBOARD and @c #SCREEN_EVENT_GESTURE events.
	*/
	SCREEN_PROPERTY_SCAN = 27,

	/** See @c #SCREEN_PROPERTY_SCAN. */
	SCREEN_PROPERTY_KEY_SCAN = 27,

	/** A single integer that indicates the symbols associated with the
	*   specific event; a property of an event object. When retrieving or setting
	*   this property type, ensure that you provide sufficient storage for one
	*   integer. @c #SCREEN_PROPERTY_SYM is applicable only to
	*   @c #SCREEN_EVENT_GESTURE and @c #SCREEN_EVENT_KEYBOARD events.
	*/
	SCREEN_PROPERTY_SYM = 28,

	/** See @c #SCREEN_PROPERTY_SYM. */
	SCREEN_PROPERTY_KEY_SYM = 28,

	/** A single integer (0 or 1) that indicates whether or not contents of the API
	*   object are mirrored (flipped horizontally); a property of a window object.
	*   When retrieving or setting this property type, ensure that you have
	*   sufficient storage for one integer.
	*/
	SCREEN_PROPERTY_MIRROR = 29,

	/** A single integer containing the name of the window group. When
	*   retrieving or setting this property type, ensure you provide sufficient
	*   storage a character buffer. The following API objects have this
	*   property, and share this same definition:
	*   - event (Applicable only to a @c #SCREEN_EVENT_PROPERTY event)
	*   - group
	*/
	SCREEN_PROPERTY_NAME = 30,

	/** A single integer that indicates the process id of the process responsible
	*   for creating the API object. When retrieving this property type, ensure
	*   that you have sufficient storage for one integer. The following API
	*   objects have this property, and share this same definition:
	*   - window
	*   - session
	*/
	SCREEN_PROPERTY_OWNER_PID = 31,

	/**  A single integer that indicates whether or not the buffer is physically
	*   contiguous; a property of a buffer object. When retrieving or setting this
	*   property type, ensure you provide sufficient storage for one integer.
	*/
	SCREEN_PROPERTY_PHYSICALLY_CONTIGUOUS = 32,

	/** Three integers that provide the offset from the base address for each
	*   of the Y, U and V components of planar YUV formats; a property of a
	*   buffer object. When retrieving or setting this property type, ensure that
	*   you have sufficient storage for three integers.
	*/
	SCREEN_PROPERTY_PLANAR_OFFSETS = 33,

	/** A pointer that can be used by software renderers to read from and/or
	*   write to the buffer; a property of a buffer object. When this property is
	*   used, ensure that you provide sufficient storage space for one @c void
	*   pointer. The buffer must have been realized with a usage containing
	*   @c #SCREEN_USAGE_READ and/or @c #SCREEN_USAGE_WRITE
	*   for this property to be a valid pointer.
	*/
	SCREEN_PROPERTY_POINTER = 34,

	/** Integers that define position of the screen coordinates of the related API
	*   object. The following API objects have this property, each with its own
	*   variant of this definition:
	*   - event:
	*      The x and y values for the contact point of the mtouch or
	*      pointer. When retrieving or setting this property type,
	*      ensure that you have sufficient storage for two integers.
	*       This is only applicable for the following events:
	*           - @c #SCREEN_EVENT_MTOUCH_PRETOUCH
	*           - @c #SCREEN_EVENT_MTOUCH_TOUCH
	*           - @c #SCREEN_EVENT_MTOUCH_MOVE
	*           - @c #SCREEN_EVENT_MTOUCH_RELEASE
	*           - @c #SCREEN_EVENT_POINTER
	*   - session:
	*           The x and y positions of the input region. The position is
	*           expressed relative to the top corner of the window buffer if
	*           the session is associated with a window. Otherwise, the
	*           position is in display coordinates. When retrieving or setting
	*           this property type, ensure that you have sufficient storage for
	*           two integers.
	*   - window:
	*           The x and y positions of the window screen coordinates. Remember
	*           that the position of child and embedded windows are relative to
	*           the parent window. For example, if the position of the application
	*           window is {10, 10} and the position of the child window is {10, 10},
	*           then the position of the child window on the screen is actually {20, 20}.
	*           When retrieving or setting this property type, ensure that you have
	*           sufficient storage for two integers.
	*           In the configuration file, the value of this property can
	*           be set so that windows of a specified class will have this property
	*           initialized to the value. The following is the usage for setting
	*           this property in graphics.conf:
	*           - window-position = @c [x-position] , @c [y-position]
	*/
	SCREEN_PROPERTY_POSITION = 35,

	/** A single integer that specifies whether or not there is protection for the
	*   buffer; a property of a buffer object.  The content of the buffer will not
	*   be displayed unless there is a secure link present. Operations on the buffer
	*   such as reading from, writing to, or mapping a region of the buffer to a
	*   different address space will be prohibited. Note that setting protection on a
	*   buffer does not invoke a request for authentication. Typically, the window
	*   that owns the buffer will have its window property,
	*   @c #SCREEN_PROPERTY_PROTECTION_ENABLE, set. The request
	*   for authentication will be made when the window is posted and its
	*   @c #SCREEN_PROPERTY_VISIBLE property indicates that the window is
	*   visible. When retrieving or setting this property type, ensure that you
	*   provide sufficient storage for one integer.
	*/
	SCREEN_PROPERTY_PROTECTED = 36,

	/** A handle to the buffer or buffers available for rendering. When retrieving
	*   this property type, ensure that you provide sufficient storage according
	*   to the API object type. The following API objects have this property,
	*   each with its own variant of this definition:
	*   - pixmap:
	*           Only one buffer is allowed for a pixmap object. When retrieving
	*           @c #SCREEN_PROPERTY_RENDER_BUFFERS for a pixmap
	*           object, ensure that you have sufficient storage for one @c void
	*           pointer.
	*   - window:
	*           Multiple buffers may be available for rendering for a window object.
	*           When retrieving @c #SCREEN_PROPERTY_RENDER_BUFFERS
	*           for a window, ensure that you have sufficient storage for one
	*           @c void pointer for each available buffer. Use the window property
	*           @c #SCREEN_PROPERTY_RENDER_BUFFER_COUNT to
	*           determine the number of buffers you have for the window object.
	*/
	SCREEN_PROPERTY_RENDER_BUFFERS = 37,

	/** A single integer that defines the current rotation of the  API object.
	*   When retrieving or setting this property type, ensure that you provide
	*   sufficient storage for one integer. The following API objects have this
	*   property, each with its own variant of this definition:
	*   - display:
	*           The current rotation of the display. The rotation value is one of:
	*           @c 0, @c 90, @c 180, @c 270 degrees clockwise. It's used for
	*           the positioning and sizing of the display. Changing the display
	*           rotation, does not implicitly change any window properties.
	*   - window:
	*           The current rotation of the window. Window rotation is absolute.
	*           In the configuration file, graphics.conf, the value of this property can
	*           be set so that windows of a specified class will have this property
	*           initialized to the value. The following is the usage for setting this
	*           property in graphics.conf:
	*               - rotation = @c [rotation 0, 90, 180, 270]
	*/
	SCREEN_PROPERTY_ROTATION = 38,

	/** A single integer between @c [-128..127] that is used to adjust the
	*   saturation of a window; a property of a window object. When retrieving
	*   or setting this property type, ensure that you have sufficient storage for
	*   one integer. In the configuration file, graphics.conf, the value of this
	*   property can be set so that windows of a specified class will have its
	*   property initialized to this value. The following is the usage for setting
	*   this property in graphics.conf:
	*   - saturation = @c [saturation -128..127]
	*/
	SCREEN_PROPERTY_SATURATION = 39,

	/** The size of the associated API object.  When retrieving or
	*    setting this property type, ensure that you provide sufficient storage
	*    according to the API object. The following API objects have this
	*    property, each with its own variant of this definition:
	*   - buffer:
	*           A single integer that indicates the size, in bytes, of the buffer.
	*           When retrieving or setting this property type, ensure that you have
	*           sufficient storage for one integer.
	*   - display:
	*           A pair of integers that define the width and height, in pixels,
	*           of the current video resolution. When retrieving this property
	*           type, ensure that you have sufficient storage for two integers.
	*           Note that the display size changes with the display rotation.
	*           For example, if the video mode is 1024x768 and the rotation is
	*           @c 0 degrees, the display size will indicate 1024x768. When the
	*           display rotation is set to @c 90 degrees, the display size will
	*           become 768x1024. (@c #SCREEN_PROPERTY_SIZE can only
	*           be retrieved and not set for a display object)
	*   - event:
	*           A pair of integers that define the width and height, in pixels,
	*           of the touch or contact area. This is only applicable for the
	*           following events:
	*           - @c #SCREEN_EVENT_MTOUCH_PRETOUCH
	*           - @c #SCREEN_EVENT_MTOUCH_TOUCH
	*           - @c #SCREEN_EVENT_MTOUCH_MOVE
	*           - @c #SCREEN_EVENT_MTOUCH_RELEASE
	*   - session:
	*           A pair of integers that define the width and height, in pixels,
	*           of the input region. The dimensions are expressed in buffer
	*           coordinates if the session is associated with a window.
	*           Otherwise, the size is in display coordinates. When retrieving
	*           or setting this property type, esnure that you have sufficient
	*           storage for two integers.
	*   - window:
	*           A pair of integers that define the width and height, in pixels,
	*           of the window. When retrieving this property type, ensure that
	*           you have sufficient storage for two integers.
	*           In the configuration file, graphics.conf, the value of this property can
	*           be set so that windows of a specified class will have this property
	*           initialized to the value. The following is the usage for setting this
	*           property in graphics.conf:
	*           - window-size = @c [width] x @c [height]
	*/
	SCREEN_PROPERTY_SIZE = 40,

	/** A pair of integers that define the x-and y- position of a source viewport
	*   within the window buffers. When retrieving or setting this property type,
	*   ensure that you have sufficient storage for two integers. The following
	*   API objects have this property, each with its own variant of this defnition:
	*   - event:
	*       This is only applicable for the following events:
	*           - @c #SCREEN_EVENT_MTOUCH_PRETOUCH
	*           - @c #SCREEN_EVENT_MTOUCH_TOUCH
	*           - @c #SCREEN_EVENT_MTOUCH_MOVE
	*           - @c #SCREEN_EVENT_MTOUCH_RELEASE
	*           - @c #SCREEN_EVENT_POINTER
	*   - window:
	*           The x and y coordinates of the top left corner of a rectangular
	*           region within the window buffer representing the source viewport
	*           of the window. This is the portion of the window buffer that is to
	*           be displayed.
	*           In the configuration file, graphics.conf, the value of this property can
	*           be set so that windows of a specified class will have this property
	*           initialized to the value. The following is the usage for setting this
	*           property in graphics.conf:
	*           - source-position = @c [x-position], @c [y-position]
	*/
	SCREEN_PROPERTY_SOURCE_POSITION = 41,

	/** A pair of integers that define the width and height, pixels, of a source
	*   viewport within the window buffers. When retrieving or setting this
	*   property type, ensure that you have sufficient storage for two integers.
	*   The following API objects have this property, each with its own variant
	*   of this definition:
	*   - event:
	*       This is only applicable for the following events:
	*           - @c #SCREEN_EVENT_MTOUCH_PRETOUCH
	*           - @c #SCREEN_EVENT_MTOUCH_TOUCH
	*           - @c #SCREEN_EVENT_MTOUCH_MOVE
	*           - @c #SCREEN_EVENT_MTOUCH_RELEASE
	*   - window:
	*           The width and height of a rectangular region within the window
	*           buffer representing the source viewport of the window.
	*           This is the portion of the window buffer that is to be
	*           displayed.
	*           In the configuration file, graphics.conf, the value of this
	*           property can be set so that windows of a specified class will
	*           have this property initialized to the value. The following is
	*           the usage for setting this property in graphics.conf:
	*           - source-size = @c [width] x @c [height]
	*/
	SCREEN_PROPERTY_SOURCE_SIZE = 42,

	/** A single integer that indicates whether or not the contents of a window
	*   are expected to change; a property of a window object. When
	*   retrieving or setting this property type, ensure that you have sufficient
	*   storage for one integer. In the configuration file, graphics.conf, the
	*   value of this property can be set so that windows of a specified class
	*   will have this property initialized to the value. The following is the
	*   usage for setting this property in graphics.conf:
	*   - static = @c [static 0,1]
	*/
	SCREEN_PROPERTY_STATIC = 43,

	/** A single integer that indicates the number of bytes between the same
	*   pixels on adjacent rows; a property of a buffer object. When retrieving
	*   or setting this property type, ensure that you provide sufficient storage for
	*   one integer.
	*/
	SCREEN_PROPERTY_STRIDE = 44,

	/** A single integer that specifies the minimum number of vsync periods
	*   between posts; a property of a window object, When retrieving or
	*   setting this property type, ensure that you have sufficient storage for
	*   one integer.
	*  In the configuration file, graphics.conf, the value of this property can
	*  be set so that windows of a specified class will have this property
	*  initialized to the value. The following is the usage for setting this
	*  property in graphics.conf:
	*   - interval = @c [swap interval]
	*/
	SCREEN_PROPERTY_SWAP_INTERVAL = 45,

	/** A single integer that defines the transparency type of an API object.
	*   The following API objects have this property, each with its own variant of
	*   this definition:
	*   - display:
	*           How multiple layers are combined. The transparencies that are
	*           applicable to a display object are:
	*           - @c #SCREEN_TRANSPARENCY_SOURCE_COLOR
	*           - @c #SCREEN_TRANSPARENCY_SOURCE_OVER
	*
	*           When retrieving this property type for a display object, ensure that you
	*           have sufficient storage for one integer.
	*   - window
	*          How the alpha channel of the window is used to combine a window
	*          with other windows or the background color underneath it. Although the
	*          window transparency property can be set, the actual transparency applied
	*          is dependent on hardware. If the hardware supports it, the transparency
	*          specified by this property will be applied, otherwise a best effort
	*          algorithm will be used to apply the window transparency. Transparency
	*          must be of the type  <a href="screen_8h_1Screen_Transparency_Types.xml">Screen transparency types</a>.
	*          When retrieving or setting this property type, ensure that you have
	*          sufficient storage for one integer.
	*/
	SCREEN_PROPERTY_TRANSPARENCY = 46,

	/** A single integer that indicates the type of the specified buffer object.
	*   When retrieving this property type, ensure that you provide sufficient
	*   storage for one integer. The following API objects have this property,
	*   each with its own variant of this definition:
	*   - device:
	*           The type of input device. Valid input device types are:
	*           - @c #SCREEN_EVENT_GAMEPAD
	*           - @c #SCREEN_EVENT_JOG
	*           - @c #SCREEN_EVENT_JOYSTICK
	*           - @c #SCREEN_EVENT_KEYBOARD
	*           - @c #SCREEN_EVENT_MTOUCH_TOUCH
	*           - @c #SCREEN_EVENT_POINTER
	*   - display:
	*           The type of display port. Valid display ports must be of type
	*            <a href="screen_8h_1Screen_Display_Types.xml">Screen display types</a>.
	*   - event:
	*           The type of event. Valid event types must be of type
	*           <a href="group__screen__events_1Screen_Event_Types.xml"> Screen event types</a>.
	*   - session:
	*           The type of input session. Valid session types must be of type
	*           - @c #SCREEN_EVENT_POINTER
	*           - @c #SCREEN_EVENT_KEYBOARD
	*           - @c #SCREEN_EVENT_GAMEPAD
	*           - @c #SCREEN_EVENT_JOYSTICK
	*           - @c #SCREEN_EVENT_MTOUCH_TOUCH
	*           - @c #SCREEN_EVENT_JOG
	*   - window:
	*           The type of window. Valid window types must be of type
	*           <a href="group__screen__windows_1Screen_Window_Types.xml">Screen window types</a>.
	*/
	SCREEN_PROPERTY_TYPE = 47,

	/** A single integer that is a bitmask indicating the intended usage
	*   for the buffers associated with the API object. The default usage for a
	*   buffer is @c #SCREEN_USAGE_READ|#SCREEN_USAGE_WRITE.
	*   @c #SCREEN_PROPERTY_USAGE must be a combination of type
	*   <a href="screen_8h_1Screen_Usage_Flag_Types.xml"> Screen usage flag types</a>.
	*	When retrieving or setting this property type, ensure that you have
	*   sufficient storage for one integer. Note that changing
	*   @c #SCREEN_PROPERTY_USAGE affects the pipeline when
	*   the overlay usage bit (@c #SCREEN_USAGE_OVERLAY) is added or
	*   removed. The following API objects have this property, and share the
	*   same definition:
	*   - pixmap
	*   - window
	*       - In the configuration file, graphics.conf, the value of this property can
	*         be set so that windows of a specified class will have this property
	*         initialized to this value. The following are valid usage flags and their
	*         implications that you can use to set this property in graphics.conf:
	*           - sw (read or write)
	*           - gles1 (OpenGL 1.X)
	*           - gles2 (OpenGL 2.X)
	*           - gles3 (OpenGL 3.X)
	*           - vg (OpenVG)
	*           - native (native API operations such as blits or fills)
	*           - rotation (re-configure orientation without re-allocation)
	*
	*       - The following is the usage for setting this property in graphics.conf:
	*          - usage = [usage flag1, usage flag2, ... ]
	*          - e.g., usage = sw, gles1
	*/
	SCREEN_PROPERTY_USAGE = 48,

	/** Four integers containing data associated with the user; a property of an
	*   event object. @c #SCREEN_PROPERTY_USER_DATA
	*   can be queried or set in association with an event of type
	*   @c #SCREEN_EVENT_USER. When retrieving or setting this property
	*   type, ensure that you have sufficient storage for four integers.
	*/
	SCREEN_PROPERTY_USER_DATA = 49,

	/** A handle that is passed to the application window when events are
	*   associated with the window; a handle to an object to associate the
	*   API object with user data. When retrieving or setting this property type,
	*   ensure that you have sufficient storage for one @c void pointer. The
	*   following API objects have this property, and share this same definition:
	*   - device
	*   - group
	*   - window
	*/
	SCREEN_PROPERTY_USER_HANDLE = 50,

	/** A single integer that specifies whether an API object is visible or
	*   active. When retrieving or setting this property type, ensure that you
	*   have sufficient storage for one integer. The following API objects
	*   have this property and share this same definition:
	*   - session
	*   - window:
	*          In the configuration file, , the value of this property can
	*          be set so that windows of a specified class will have this property
	*          initialized to the value. The following are valid settings that
	*          can be used for this property in graphics.conf:
	*          - visible = true
	*          - visible = false
	*/
	SCREEN_PROPERTY_VISIBLE = 51,

	/** A pointer to a window. When retrieving or setting this property type,
	*   ensure that you have sufficient storage for one @c void pointer. The
	*   following API objects have this property, each with its own variant of
	*   this definition:
	*   - device
	*           The window on which the input device is focused. All input from
	*           the device will be directed to this particular window.
	*   - event (@c #SCREEN_PROPERTY_WINDOW can only be retrieved
	*                  and not set for an event object)
	*
	*       For the following events, @c #SCREEN_PROPERTY_WINDOW
	*       refers to the window associated with the event:
	*           - @c #SCREEN_EVENT_CREATE
	*           - @c #SCREEN_EVENT_POST
	*           - @c #SCREEN_EVENT_CLOSE
	*           - @c #SCREEN_EVENT_UNREALIZE
	*
	*       For the following events, @c #SCREEN_PROPERTY_WINDOW
	*       refers to the window associated with the input device for which
	*       the event is intended:
	*           - @c #SCREEN_EVENT_GAMEPAD
	*           - @c #SCREEN_EVENT_JOYSTICK
	*           - @c #SCREEN_EVENT_KEYBOARD
	*           - @c #SCREEN_EVENT_MTOUCH_PRETOUCH
	*           - @c #SCREEN_EVENT_MTOUCH_TOUCH
	*           - @c #SCREEN_EVENT_MTOUCH_MOVE
	*           - @c #SCREEN_EVENT_MTOUCH_RELEASE
	*           - @c #SCREEN_EVENT_POINTER
	*
	*       For the following event, @c #SCREEN_PROPERTY_WINDOW
	*       refers to the window whose property is being set:
	*           - @c #SCREEN_EVENT_PROPERTY
	*   - session:
	*           The window on which the input session is focused.
	*/
	SCREEN_PROPERTY_WINDOW = 52,

	 /**A single integer that indicates he number of render buffers associated
	 *  with the window; a property of a window object. When retrieving this
	*   property type, ensure that you have sufficient storage for one integer.
	*/
	SCREEN_PROPERTY_RENDER_BUFFER_COUNT = 53,

	/** A single integer that indicates the distance from the bottom that is
	*   used when ordering API objects amongst each other. When retrieving or
	*   setting this property type, ensure that you have sufficient storage for
	*   one integer. The following API objects have this property and share this
	*   same definition:
	*   - session
	*        A window can have multiple input sessions. When regions of these
	*        multiple sessions overlap, this property is used to determine which
	*        session is on top. The session whose @c #SCREEN_PROPERTY_ZORDER is
	*        the highest will be the the session that receives the input event.
	*   - window:
	*        Indicates the distance from the bottom that is used when ordering
	*        window groups amongst each other.
	*        In the configuration file, graphics.conf, the value of this property can
	*        be set so that windows of a specified class will have this property
	*        initialized to the value. The following is the usage for setting this
	*        property in graphics.conf:
	*        - order = @c [zorder]
	*/
	SCREEN_PROPERTY_ZORDER = 54,

	/** A single long long integer that corresponds to the physical address of the
	*   buffer; a  property of a buffer object. This property is only valid when
	*   the buffer is physically contiguous. When retrieving or setting this
	*   property type, ensure that you provide sufficient storage for one long
	*   integer.
	*/
	SCREEN_PROPERTY_PHYSICAL_ADDRESS = 55,

	/** A single integer that indicates the amount of filtering performed by
	*   the windowing system when scaling is required to draw the window; a
	*   property of a window object. The scale quality must be of type
	*   <a href="screen_8h_1Screen_Scale_Quality_Types.xml">Screen scale quality types</a>.
	*   When retrieving or setting this property type, ensure that you have
	*   sufficient storage for one integer.
	*/
	SCREEN_PROPERTY_SCALE_QUALITY = 56,

	/** A single integer that indicates the API object input behavior. The
	*   sensitivity must be of type
	*   <a href="screen_8h_1Screen_Sensitivity_Types.xml">Screen sensitivity types</a>
	*   or an integer that is a bitmask combination of
	*   <a href="screen_8h_1Screen_Sensitivity_Masks.xml">Screen sensitivity masks</a>.
	*   When retrieving or setting this property type, ensure that you have
	*   sufficient storage for one integer. The following API objects have this
	*   property and share this same definition:
	*   - session
	*   - window
	*/
	SCREEN_PROPERTY_SENSITIVITY = 57,

	/** A single integer that defines whether or not the display is currently in
	*   mirror mode. Mirror mode indicates that the internal and external
	*   displays display the same signal. When retrieving or setting this property
	*   type, ensure that you have sufficient storage for one integer. The
	*   following API objects have this property, and share this same definition:
	*   - display
	*   - event (Applicable only to a @c #SCREEN_EVENT_DISPLAY event)
	*/
	SCREEN_PROPERTY_MIRROR_MODE = 58,

	/** A single integer containing the number of displays associated with this
	*   context; a property of a context object.  When retrieving this property
	*   type, ensure that you have sufficient storage for one integer.
	*/
	SCREEN_PROPERTY_DISPLAY_COUNT = 59,

	/** An array of display pointers; a property of a context object.
	*   When retrieving this property type, ensure that you have sufficient
	*   storage for one @c void pointer for each display. Retrieve the
	*   @c #SCREEN_PROPERTY_DISPLAY_COUNT property to find out
	*   how many displays are associated with this context; Once you know
	*   the number of displays, you can allocate sufficient storage to retrieve
	*   @c #SCREEN_PROPERTY_DISPLAYS.
	*/
	SCREEN_PROPERTY_DISPLAYS = 60,

	/** A single integer that indicates what the window content is; a property of a
	*   window object. The content mode must be of type
	*   <a href="screen_8h_1Screen_CBABC_Mode_Types.xml">Screen content mode types</a>.
	*   When getting or setting this property type, ensure that you have
	*   sufficient storage for one integer.
	*  In the configuration file, graphics.conf, the value of this property can
	*  be set so that windows of a specified class will have this property
	*  initialized to the value. The following are valid settings that can be
	*  used for this property in graphics.conf:
	*  - cbabc = none
	*  - cbabc = video
	*  - cbabc = ui
	*  - cbabc = photo
	*/
	SCREEN_PROPERTY_CBABC_MODE = 61,

	/** A single integer that indicates the effect associated with the specific event;
	*   a property of an event object. Effects must be of type
	*   <a href="group__screen__effects_1Screen_Effect_Types.xml">Screen effect types</a>.
	*   When retrieving or setting this property type, ensure that you have
	*   sufficient storage for one integer. This property is only applicable for a
	*   @c #SCREEN_EVENT_EFFECT_COMPLETE event.
	*/
	SCREEN_PROPERTY_EFFECT = 62,

	/** A single integer that indicates whether or not the window is a floating
	*   window; a property of a window object. When retrieving or setting this
	*   property type, ensure that you have sufficient storage for one integer.
	*/
	SCREEN_PROPERTY_FLOATING = 63,

	/** A single integer that indicates whether or not the display is currently
	*   attached. When retrieving or setting this property type, ensure you have
	*   sufficient storage for one integer.  The following API objects have this
	*   property, each with its own variant of this definition:
	*   - display:
	*           Indicates whether or not the display is connected. Display objects
	*           may exist in a context, but are not considered connected until they are
	*           attached.
	*   - event:
	*           - In the case of the @c #SCREEN_EVENT_DISPLAY event, this indicates
	*             that a display has changed its state; the display has either connected
	*             or disconnected.
	*           - In the case of the @c #SCREEN_EVENT_DEVICE event, this indicates
	*             that either a new device has been created and is now conntected, or
	*             that a device has disconnected and been deleted. Unlike displays,
	*             device objects only exist in a context if they are attached.
	*             (@c  SCREEN_PROPERTY_ATTACHED can only be retrieved and
	*             not set for device event.)
	*/
	SCREEN_PROPERTY_ATTACHED = 64,

	/** A single integer that indicates whether or not the display can be
	*   detached; a property of a display object. When retrieving this property
	*   type, ensure that you have sufficient storage for one integer.
	*/
	SCREEN_PROPERTY_DETACHABLE = 65,

	/** A pair of integers that define the width and height of the native video
	*   resolution; a property of a display object. When retrieving this property
	*   type, ensure that you have sufficient storage for two integers.
	*/
	SCREEN_PROPERTY_NATIVE_RESOLUTION = 66,

	/** A single integer that indicates whether or not content protection is
	*   enabled for the API object. You require a secure link in order to have protection
	*   enabled. When retrieving or setting this property type, ensure that you have
	*   sufficient storage for one integer. The following API objects have this property,
	*   each with its own variant of this definition:
	*   - display:
	*           Indicates whether or not content protection is needed for the window(s)
	*           on the display. Content protection is considered enabled as long as one
	*           window on the display has its content protection enabled and its
	*           @c #SCREEN_PROPERTY_VISIBLE property indicates that the
	*           window is visible. The @c #SCREEN_PROPERTY_PROTECTION_ENABLE
	*           property of a display is dynamic; its value depends on the
	*           @c #SCREEN_PROPERTY_PROTECTION_ENABLE property of the
	*           window(s) that are on the display. @c #SCREEN_PROPERTY_PROTECTION_ENABLE
	*           can only be retrieved and not set for a display object.
	*   - window:
	*           Indicates whether or not authentication is to be requested before the
	*           content of the window can be displayed. Authentication is requested
	*           when the window is posted and its @c #SCREEN_PROPERTY_VISIBLE
	*           property indicates that the window is visible.
	*   - event:  (Applicable only to a @c #SCREEN_EVENT_DISPLAY event)
	*           Indicates that a disabling of content protection is detected. This is
	*           likely due to the loss of a secure link to the display.
	*/
	SCREEN_PROPERTY_PROTECTION_ENABLE = 67,

	/** A pair of integers that define the x- and y- position of a clipped source
	*   rectangular viewport within the window buffers; a property of a window
	*   object. When retrieving or setting this property type, ensure that you
	*   have sufficient storage for two integers.
	*/
	SCREEN_PROPERTY_SOURCE_CLIP_POSITION = 68,

	/** A pair of integers that define the width and height, in millimeters,
	*   of the display; a property of a display object.  When retrieving this
	*   property type, ensure that you have sufficient storage for two integers.
	*/
	SCREEN_PROPERTY_PHYSICAL_SIZE = 69,

	/** A single integer that indicates the number of formats that the display
	*   supports; a property of a display object.  When retrieving this property
	*   type, ensure that you have sufficient storage for at least one integer.
	*/
	SCREEN_PROPERTY_FORMAT_COUNT = 70,

	/** An array of integers of size @c #SCREEN_PROPERTY_FORMAT_COUNT
	*   that defines the formats supported by the display; a property of a
	*   display object. If the display has many layers, the list is the union of
	*   all the formats supported on all layers. Formats are of type
	*   <a href="screen_8h_1Screen_Pixel_Format_Types.xml">Screen pixel format types</a>.
	*   When retrieving this property type, ensure that you have sufficient
	*   storage for one integer.
	*/
	SCREEN_PROPERTY_FORMATS = 71,

	/** A pair of integers that define the width and height, in pixels, of a
	*   clipped source rectangular viewport within he window buffers; a property
	*   of a window object. When retrieving or setting this property type, ensure
	*   that you have sufficient storage for two integers.
	*/
	SCREEN_PROPERTY_SOURCE_CLIP_SIZE = 72,

	/** A single integer that indicates the multi-touch contact id associated
	*   with the specific event; a property of an event object. When
	*   retrieving this property type, ensure that you have sufficient storage
	*   for one integer.
	*/
	SCREEN_PROPERTY_TOUCH_ID = 73,

	/** A pair of integers that define the x and y position of a rectangular
	*   region within the API object. When retrieving or setting this property
	*   type, ensure that you have sufficient storage for two integers. The
	*   following API objects have this property, each with its own variant of this
	*   definition:
	*   - display:
	*           The x and y coordinates of the top left corner of a rectangular
	*           region within the display that is intended to be mapped to and
	*           redrawn to the display. In order for you to access this display
	*           property, you need to be working within a privileged context.
	*           That is, a the context in which you are accessing this display
	*           property must have been created with at least the bit mask of
	*           @c #SCREEN_DISPLAY_MANAGER_CONTEXT.
	*   - window:
	*           The x and y coordinates of the top left corner of a virtual viewport.
	*           The virtual viewport is typically used to achieve the effect of scrolling
	*           or panning a source whose size is larger than the size of your window
	*           buffer.
	*/
	SCREEN_PROPERTY_VIEWPORT_POSITION = 74,

	/** A pair of integers that define the width and height of a rectangular
	*   region within the API object. When retrieving or setting this property
	*   type, ensure that you have sufficient storage for two integers. The
	*   following API objects have this property, each with its own variant of this
	*   definition:
	*   - display:
	*           The width and height, in pixels, of a rectangular region within the
	*           display that is intended to be mapped to and redrawn to the display.
	*           In order for you to access this display property, you need to be
	*           working within a privileged context. That is, a the context in which
	*           you are accessing this display property must have been created
	*           with at least the bit mask of
	*           @c #SCREEN_DISPLAY_MANAGER_CONTEXT.
	*   - window:
	*           The width and height, in pixels, of a virtual viewport.  The virtual
	*           viewport is typically used to achieve the effect of scrolling
	*           or panning a source whose size is larger than the size of your window
	*           buffer.
	*/
	SCREEN_PROPERTY_VIEWPORT_SIZE = 75,

	/** A single integer that indicates the multi-touch orientation associated
	*   with the specific event; a property of an event object. When retrieving
	*   or setting this property type, ensure that you have sufficient storage
	*   for one integer. This property is only applicable for the following events:
	*    - @c #SCREEN_EVENT_MTOUCH_PRETOUCH
	*    - @c #SCREEN_EVENT_MTOUCH_TOUCH
	*    - @c #SCREEN_EVENT_MTOUCH_MOVE
	*    - @c #SCREEN_EVENT_MTOUCH_RELEASE
	*/
	SCREEN_PROPERTY_TOUCH_ORIENTATION = 76,

	/** A single integer that indicates the multi-touch pressure associated with
	*   the specific event; a property of an event object. When retrieving
	*   or setting this property type, ensure that you have sufficient storage
	*   or one integer. This property is only applicable for the following events:
	*   events:
	*    - @c #SCREEN_EVENT_MTOUCH_PRETOUCH
	*    - @c #SCREEN_EVENT_MTOUCH_TOUCH
	*    - @c #SCREEN_EVENT_MTOUCH_MOVE
	*    - @c #SCREEN_EVENT_MTOUCH_RELEASE
	*/
	SCREEN_PROPERTY_TOUCH_PRESSURE = 77,

	/** A single @c long @c long integer that indicates a timestamp associated with
	*   the API object. When retrieving or setting this property type, ensure that
	*   you have sufficient storage for one long long integer. It is important
	*   to note that screen uses the realtime clock and not the monotonic clock
	*   when calculating the timestamp. The following API objects have this
	*   property, each with its own variant of this definition:
	*   - event:
	*         The timestamp at which the event was received by Screen
	*        (@c #SCREEN_PROPERTY_TIMESTAMP can only be retrieved and not set
	*         for an event object).
	*   - window:
	*         The timestamp to indicate the start of a frame. This timestamp can
	*         be used by the application to measure the elapsed time taken to
	*         perform functions of interest. For example, the application can
	*         measure the time between when the timestamap is set and when the
	*         window is posted (e.g., when OpenGL swap buffers). This timestamp
	*         allows for the application to track CPU time. The application can
	*         set the timestamp to any specific time. Then, the application
	*         uses the @c screen_get_window_property_llv() function to retrieve
	*         the #SCREEN_PROPERTY_METRICS property of the window to look at the
	*         timestamp for comparison to the set timestamp.
	*/
	SCREEN_PROPERTY_TIMESTAMP = 78,

	/** A single integer that is associated with the specific API object.
	*   When retrieving or setting this property type, ensure that you have
	*   sufficient storage for one integer. The following API objects have this
	*   property, each with its own variant of this definition:
	*   - event:
	*         The multi-touch sequence ID associated with the event.
	*         This property is only applicable for the following events:
	*         - @c #SCREEN_EVENT_MTOUCH_PRETOUCH
	*         - @c #SCREEN_EVENT_MTOUCH_TOUCH
	*         - @c #SCREEN_EVENT_MTOUCH_MOVE
	*         - @c #SCREEN_EVENT_MTOUCH_RELEASE
	*         - @c #SCREEN_EVENT_KEYBOARD
	*   - session
	*         The unique identifier used by Screen to track, in sequence, when
	*         a session of a specific type was created. This identifier is not
	*         to be confused with @c #SCREEN_PROPERTY_ID which is an identifier
	*         that can be used by applications to identify specific API objects.
	*   - window
	*         The unique identifier used by Screen to track, in sequence, when
	*         a session of a specific type was created. This identifier is not
	*         to be confused with @c #SCREEN_PROPERTY_ID which is an identifier
	*         that can be used by applications to identify specific API objects.
	*/
	SCREEN_PROPERTY_SEQUENCE_ID = 79,

	/** A single integer indicating the idle mode of the window; a property of a
	*   window object. The idle mode must be of type
	*   <a href="screen_8h_1Screen_Idle_Mode_Types.xml">Screen idle mode types</a>.
	*   When retrieving or setting this property type, ensure that you have
	*   sufficient storage for one integer.
	*/
	SCREEN_PROPERTY_IDLE_MODE = 80,

	/** A single integer that indicates the idle state of the API object.
	*   The idle state will be @c 1 if the system is idle, indicating that no input
	*   was received after the idle timeout period (@c #SCREEN_PROPERTY_IDLE_TIMEOUT).
	*   The idle state will be @c 0, if an input event was received prior to the
	*   idle timeout period expiring. When retrieving this property type,
	*   ensure that you have sufficient storage for one integer. The following
	*   API objects have this property, each sharing a similiar definition:
	*   - device:
	*           The idle state that is applicable to the entire device.
	*   - display:
	*           The idle state that is applicable to the entire display.
	*   - event (Applicable only to a @c #SCREEN_EVENT_IDLE event):
	*           Indicates that an idle state change has taken place for either a display or
	*           group object. Query the @c #SCREEN_PROPERTY_OBJECT_TYPE
	*           property of the event to determine the object type of this event.
	*   - group :
	*           The idle state that is applicable to only the group. A group is
	*           considered in idle state if none of the windows that are part of
	*           the group have received input after the idle timeout period for the group.
	*/
	SCREEN_PROPERTY_IDLE_STATE = 81,

	/** A single integer that indicates the number of windows with an idle mode
	*   of type @c #SCREEN_IDLE_MODE_KEEP_AWAKE that are visible on
	*   a display;  a property of a display object. When retrieving this property
	*   type, ensure that you have sufficient storage for one integer.
	*/
	SCREEN_PROPERTY_KEEP_AWAKES = 82,

	/** A single long long integer that indicates the amount of time, in seconds,
	*   after which the system will enter an idle state. When retrieving or
	*   setting this property type, ensure that you have sufficient storage for
	*   one long long integer. The following API objects have this property, each
	*   sharing a similar definition:
	*   - context:
	*           The amount of time after which the display of the context will
	*           enter an idle state.
	*   - device:
	*           The amount of time after which the device will enter an idle state.
	*   - display:
	*           The amount of time after which the display will enter an idle state.
	*   - group:
	*           The amount of time after which the group will enter in an idle
	*           state.
	*/
	SCREEN_PROPERTY_IDLE_TIMEOUT = 83,

	/** A handle which corresponds to the object that currently has
	*   keyboard focus. When retrieving or setting this property type, ensure
	*   that you have sufficient storage according to the definition of the
	*   property for the specific API object. The following API objects have
	*   this property, each with its own variant of this definition:
	*   - context:
	*           A handle to the top-level window (application window) on the
	*           display that currently has the keyboard focus. You must be
	*           working within a privileged context of type
	*           @c #SCREEN_WINDOW_MANAGER_CONTEXT to be able to set this
	*           property.
	*   - display:
	*           A handle to the top-level window (application window) on the
	*           display that currently has the keyboard focus. You must be
	*           working within a privileged context of type
	*           @c #SCREEN_WINDOW_MANAGER_CONTEXT to be able to set this
	*           property.
	*   - group:
	*           A handle to the immediate window in the group that currently has
	*           the keyboard focus. You must be the owner of the group,
	*           @c #screen_group_t, to be able to set this property.
	*   - session:
	*           A handle to the input session that currently has keyboard focus.
	*   - window:
	*           A single integer that indicates whether or not the window currently
	*           has the keyboard focus. (@c #SCREEN_PROPERTY_FOCUS
	*           can only be retrieved and not set for a window object)
	*/
	SCREEN_PROPERTY_FOCUS = 84,

	/** @deprecated This property has been deprecated.
	*   Use @c #SCREEN_PROPERTY_FOCUS instead. */
	SCREEN_PROPERTY_KEYBOARD_FOCUS = 84,

	/** A handle or an indicator which corresponds to the API object that
	*   currently has mtouch focus. When retrieving or setting this property
	*   type, ensure that you have sufficient storage for one @c void pointer.
	*   The following API objects have this property, each with its own variant
	*   of this definition:
	*   - context:
	*           A handle to the top-level window (application window) on the
	*           display that currently has the mtouch focus. You must be
	*           working within a privileged context of type
	*           @c #SCREEN_WINDOW_MANAGER_CONTEXT to be able to set this
	*           property.
	*   - display:
	*           A handle to the top-level window (application window) on the
	*           display that currently has the mtouch focus. You must be
	*           working within a privileged context of type
	*           @c #SCREEN_WINDOW_MANAGER_CONTEXT to be able to set this
	*           property.
	*   - group:
	*           A handle to the immediate window in the group that currently has
	*           the mtouch focus. You must be the owner of the group,
	*           @c #screen_group_t, to be able to set this property.
	*   - session:
	*           An integer (0 or 1) to indicate whether the input session
	*           currently has the mtouch focus (e.g., 0 = does not have focus
	*           and 1 = has focus)
	*/
	SCREEN_PROPERTY_MTOUCH_FOCUS = 85,

	/** A handle which corresponds to the API object that currently has
	*   pointer focus. When retrieving or setting this property type, ensure that
	*   you have sufficient storage for one @c void pointer. The following API
	*   objects have this property, each with its own variant of this
	*   definition:
	*   - context:
	*           A handle to the top-level window (application window) on the
	*           display that currently has the pointer focus. You must be
	*           working within a privileged context of type
	*           @c #SCREEN_WINDOW_MANAGER_CONTEXT to be able to set this
	*           property.
	*   - display:
	*           A handle to the top-level window (application window) on the
	*           display that currently has the pointer focus. You must be
	*           working within a privileged context of type
	*           @c #SCREEN_WINDOW_MANAGER_CONTEXT to be able to set this
	*           property.
	*   - group:
	*           A handle to the immediate window in the group that currently has
	*           the pointer focus. You must be the owner of the group,
	*           @c #screen_group_t, to be able to set this property.
	*   - session:
	*           A handle to the input session that currently has the pointer
	*           focus.
	*/
	SCREEN_PROPERTY_POINTER_FOCUS = 86,

	/** A single integer that indicates the identification of the API object.
	*   When retrieving this property type, ensure that you
	*   have sufficient storage for one integer. The following API
	*   objects have this property, and share this same definition:
	*   - device
	*   - display
	*   - group
	*   - pixmap
	*   - session
	*   - window
	*/
	SCREEN_PROPERTY_ID = 87,

	/** A single integer that defines the power mode. Power modes must be of type
	*   <a href="screen_8h_1Screen_Power_Mode_Types.xml">Screen power mode types</a>.
	*   When retrieving or setting this property type, ensure that you have
	*   sufficient storage for one integer. The following API objects have this
	*   property, and share this same definition:
	*   - device
	*   - display
	*/
	SCREEN_PROPERTY_POWER_MODE = 88,

	/** A single integer that indicates the number of modes supported by the
	*   display; a property of display object. When retrieving this property type,
	*   ensure that you have sufficient storage for one integer.
	*/
	SCREEN_PROPERTY_MODE_COUNT = 89,

	/** A pointer to a structure of type @c #screen_display_mode_t  whose
	*   content is based on the current video mode. When retrieving or setting
	*   this property type, ensure that you have sufficient storage for
	*   @c #screen_display_mode_t for each mode.  Retrieve the
	*   @c #SCREEN_PROPERTY_MODE_COUNT property to find out
	*   how many modes are supported by this display; Once you know
	*   the number of displays, you can allocate sufficient storage to retrieve
	*   @c #SCREEN_PROPERTY_MODE. When setting this property type,
	*   you can pass @c SCREEN_MODE_PREFERRED_INDEX to fall
	*   back to the default video mode without having to first query all the modes
	*   supported by the display to find the one with @c #SCREEN_MODE_PREFERRED
	*   set in @c flags of @c #screen_display_mode_t. The following API objects
	*   have this property, and share this same definition:
	*   - display
	*   - event (Applicable only to a @c #SCREEN_EVENT_DISPLAY event)
	*   - session
	*/
	SCREEN_PROPERTY_MODE = 90,

	/** A pair of integers that define the x- and y- position of a clipped
	*   rectangular viewport within the window buffers; a property of a window
	*   object. When retrieving or setting this property type, ensure that you
	*   have sufficient storage for two integers.
	*  In the configuration file, graphics.conf, the value of this property can
	*  be set so that windows of a specified class will have this property
	*  initialized to the value. The following is the usage for setting this
	*  property in graphics.conf:
	*   - clip-position = @c [x-position], @c [y-position]
	*/
	SCREEN_PROPERTY_CLIP_POSITION = 91,

	/** A pair of integers that define the width and height , in pixels, of a
	*   clipped rectangular viewport within the window buffers; a property of
	*   a window object. When retrieving or setting this property type, ensure
	*   that you have sufficient storage for two integers.
	*   In the configuration file, graphics.conf, the value of this property can
	*   be set so that windows of a specified class will have this property
	*   initialized to the value. The following is the usage for setting this
	*   property in graphics.conf:
	*   - clip-size = @c [width] x @c [height]
	*/
	SCREEN_PROPERTY_CLIP_SIZE = 92,

	/** A single integer that indicates the background color of the window;
	*   a property of a window object. When retrieving or setting this property
	*   type, ensure that you have sufficient storage for one integer.
	*  In the configuration file, graphics.conf, the value of this property can
	*  be set so that windows of a specified class will have this property
	*  initialized to the value. The following is the usage for setting this
	*  property in graphics.conf:
	*   - color = @c [window background color]
	*/
	SCREEN_PROPERTY_COLOR = 93,

	/** A single integer that indicates the pointer wheel associated with
	*   the specific event; a property of an event object. When retrieving or
	*   setting this property type, ensure that you have sufficient storage for
	*   one integer. This property is only applicable for a
	*   @c #SCREEN_EVENT_POINTER event.
	*/
	SCREEN_PROPERTY_MOUSE_WHEEL = 94,

	/** A pointer to the context associated with the API object.
	*   When retrieving this property type, ensure that you have sufficient
	*   storage for one integer. The following API objects have this property,
	*   and share this same definition:
	*   - device
	*   - display
	*   - event
	*   - group
	*   - pixmap
	*   - session
	*   - window
	*/
	SCREEN_PROPERTY_CONTEXT = 95,

	/** A single integer that enables an on-screen plot or a list of window
	*   statistics as a debugging aid; a property of a window object. The debug
	*   type must be a bitmask that represents a combination of the types
	*   <a href="group__screen__debugging_1Screen_Debug_Graph_Types.xml">Screen debug graph types</a>.
	*   When retrieving or setting this property type, ensure that you have
	*   sufficient storage for one integer.
	*/
	SCREEN_PROPERTY_DEBUG = 96,

	/** A handle to an alternate screen object. When retrieving or setting
	 *  this property type, ensure that you have sufficient storage for a
	 *  @c void pointer. The following API objects have this property, each
	 *  with its own variant of this definition:
	 *  - window
	 *  - session
	 */
	SCREEN_PROPERTY_ALTERNATE = 97,

	/** See @c #SCREEN_PROPERTY_ALTERNATE */
	SCREEN_PROPERTY_ALTERNATE_WINDOW = 97,

	/** A single integer containing the number of devices associated
	*   with this object. When retrieving this property type, ensure that you
	*   have sufficient storage for one integer. The following API
	*   objects have this property, each with its own variant of this
	*   definition:
	*   - context:
	*           The number of display devices associated with this context.
	*   - session:
	*           The number of input devices associated with this session.
	*/
	SCREEN_PROPERTY_DEVICE_COUNT = 98,

	/** @deprecated This property has been deprecated.
	*    Do not use. */
	SCREEN_PROPERTY_BUFFER_POOL = 99,

	/** A single integer that indicates the object type associated the with the
	*   specific event; a property of an event object. When retrieving this
	*   property type, ensure that you have sufficient storage for one integer.
	*   Object types must be of type
	*   <a href="screen_8h_1Screen_Object_Types.xml">Screen object types</a>.
	*   This property is only applicable for a @c #SCREEN_EVENT_PROPERTY
	*   event.
	*/
	SCREEN_PROPERTY_OBJECT_TYPE = 100,

	/** An array of device pointers. When retrieving this property type, ensure
	*   that you have sufficient storage for one @c void pointer for each device.
	*   Retrieve the @c #SCREEN_PROPERTY_DEVICE_COUNT property to find out
	*   how many devices are associated with this API object. Once you know
	*   the number of devices, you can allocate sufficient storage to retrieve
	*   @c #SCREEN_PROPERTY_DEVICES.
	*   The following API objects have this property and share this same
	*   definition:
	*   - context
	*   - session
	*/
	SCREEN_PROPERTY_DEVICES = 101,

	/** A single integer that indicates which page of a multi-page keymap
	*   must be used to translate scan codes into key caps and key symbols.
	*   Setting the keymap page on a USB or Bluetooth keyboard has no effect.
	*   Setting the keymap page on an external keyboard device created by an
	*   input provider context will cause the input provider context to receive
	*   a notification of the change.
	*/
	SCREEN_PROPERTY_KEYMAP_PAGE = 102,

	/** A single integer that indicates whether or not the window has self
	*   layout capabilities; a property of a window object. When set to @c true(1),
	*   the owner of the window is allowed to change window properties that can
	*   otherwise only be changed by its parent. When set to @c false(0), the owner
	*   of the window is permitted to change only its own window properties.
	*   Note that only the parent window can set this property. When retrieving
	*   or setting this property type, ensure that you have sufficient storage
	*   for one integer. The following are parent window properties that can be
	*   set by the owner of the window only if @c SCREEN_PROPERTY_SELF_LAYOUT is
	*   set to @c true(1):
	*   - @c #SCREEN_PROPERTY_SIZE
	*   - @c #SCREEN_PROPERTY_POSITION
	*   - @c #SCREEN_PROPERTY_CLIP_SIZE
	*   - @c #SCREEN_PROPERTY_CLIP_POSITION
	*   - @c #SCREEN_PROPERTY_VISIBLE
	*   - @c #SCREEN_PROPERTY_ZORDER
	*   - @c #SCREEN_PROPERTY_DISPLAY
	*   - @c #SCREEN_PROPERTY_GLOBAL_ALPHA
	*/
	SCREEN_PROPERTY_SELF_LAYOUT = 103,

	/** A single integer containing the number of groups associated with this
	*   context a property of a context object. When retrieving this property
	*   type, ensure that you have sufficient storage for one integer.
	*/
	SCREEN_PROPERTY_GROUP_COUNT = 104,

	/** An array of group pointers; a property of a context object. When
	*   retrieving this property type, ensure that you have sufficient storage
	*   for one @c void pointer for each group. Retrieve the
	*   @c #SCREEN_PROPERTY_GROUP_COUNT property to get the number of groups that
	*   are associated with this context; once you know the number of groups,
	*   you can allocate sufficient storage to retrieve
	*   @c #SCREEN_PROPERTY_GROUPS.
	*/
	SCREEN_PROPERTY_GROUPS = 105,

	/** A single integer containing the number of pixmaps associated with this
	*   context; a property of a context object. When retrieving or setting this
	*   property type, ensure that you have sufficient storage for one integer.
	*/
	SCREEN_PROPERTY_PIXMAP_COUNT = 106,

	/** An array of pixmap pointers; a property of a context object.
	*   When retrieving this property type, ensure that you have sufficient
	*   storage for one @c void pointer for each pixmap. Retrieve the
	*   @c #SCREEN_PROPERTY_PIXMAP_COUNT property to find out
	*   how many pixmaps are associated with this context; Once you know
	*   the number of pixmaps, you can allocate sufficient storage to retrieve
	*   @c #SCREEN_PROPERTY_PIXMAPS.
	*/
	SCREEN_PROPERTY_PIXMAPS = 107,

	/** A single integer containing the number of windows associated with this
	*   context; a property of a context object. When retrieving this property
	*   type, ensure that you have sufficient storage for one integer.
	*/
	SCREEN_PROPERTY_WINDOW_COUNT = 108,

	/** An array of window pointers; a property of a context object.
	*   When retrieving this property type, ensure that you have sufficient
	*   storage for one @c void pointer for each window. Retrieve
	*   the @c #SCREEN_PROPERTY_WINDOW_COUNT property to find
	*   out how many windows are associated with this context; Once you
	*   know the number of windows, you can allocate sufficient storage to
	*   retrieve @c #SCREEN_PROPERTY_WINDOWS.
	*/
	SCREEN_PROPERTY_WINDOWS = 109,

	/** A character string specifying a keymap. When retrieving or setting this
	*   property type, ensure that you provide a character buffer. The following
	*   API objects have this property, each with its own variant of the
	*   definition:
	*   - context:
	*           The default keymap. Unless specifically assigned, this keymap
	*           is applied to all input devices.
	*   - device:
	*           The keymap that is assigned to the specified input device. The
	*           keymap is only applicable to that device and is not persistent.
	*           For example, if the input device is removed and then replaced,
	*           the default keymap will be applied to it until a keymap is
	*           specifically set for the input device again.
	*/
	SCREEN_PROPERTY_KEYMAP = 110,

	/** A single integer that indicates the mouse horizontal wheel associated
	*   the with the specific event. a property of an event object. When
	*   retrieving or setting this property type, ensure that you have sufficient
	*   storage for one integer. This property is only applicable for a
	*   @c #SCREEN_EVENT_POINTER event.
	*/
	SCREEN_PROPERTY_MOUSE_HORIZONTAL_WHEEL = 111,

	/** A single integer that indicates the touch associated the with the
	*   specific event; a property of an event object. When retrieving or setting
	*   this property type, ensure that you have sufficient storage for one
	*   integer. Touch types must be of type
	*   <a href="screen_8h_1Screen_Touch_Types.xml"> Screen touch types</a>.
	*   This property is only applicable for the following events:
	*    - @c #SCREEN_EVENT_MTOUCH_PRETOUCH
	*    - @c #SCREEN_EVENT_MTOUCH_TOUCH
	*    - @c #SCREEN_EVENT_MTOUCH_MOVE
	*    - @c #SCREEN_EVENT_MTOUCH_RELEASE
	*/
	SCREEN_PROPERTY_TOUCH_TYPE = 112,

	/** A pointer to the image; a property of a buffer object. When retrieving
	*   or setting this property type, ensure that you have sufficient storage
	*   for one @c void pointer.
	*/
	SCREEN_PROPERTY_NATIVE_IMAGE = 113,

	/** A single integer that indicates the number of bits of the desired
	*   sub-pixel precision. When retrieving or setting this property type,
	*   ensure that you have sufficient storage for one integer. The following
	*   API objects have this property:
	*   - event: The default value is @c 0.
	*   - window: The default value is @c 16. Note that setting this property,
	*             @c SCREEN_PROPERTY_SCALE_FACTOR, prior to
	*             retrieving @c #SCREEN_PROPERTY_TRANSFORM will
	*             affect the values for the transformation matrix.
	*/
	SCREEN_PROPERTY_SCALE_FACTOR = 114,

	/** A pair of integers which represent the dpi measurement;  a property of
	*   a display object. The dpi is calculated from the physical dimensions and
	*   resolution of the display. When retrieving this property type, ensure
	*   that you have sufficient storage for one integer.
	*/
	SCREEN_PROPERTY_DPI = 115,

	/** A single integer that indicates the number of metrics associated with
	*   an API object.  Note that the actual value of the number of metrics may
	*   vary between API objects. When retrieving this property type, ensure
	*   that you have sufficient storage for one integer. The following API
	*   objects have this property, and share this same definition:
	*   - device
	*   - display
	*   - pixmap
	*   - window
	*/
	SCREEN_PROPERTY_METRIC_COUNT = 116,

	/** A array of metrics associated with an API object. Note that the size of
	*   the array of metrics may vary between API objects. When retrieving
	*   this property type, ensure that you have sufficient storage for one
	*   @c void pointer for each metric. Retrieve the
	*   @c #SCREEN_PROPERTY_METRIC_COUNT property to find out
	*   how many metrics are associated with the API object; once you know
	*   the number of metrics, you can allocate sufficient storage to retrieve
	*   @c #SCREEN_PROPERTY_METRICS. The following API objects have
	*   this property, and share this same definition:
	*   - device
	*   - display
	*   - pixmap
	*   - session
	*   - window
	*/
	SCREEN_PROPERTY_METRICS = 117,

	/** A single integer that indicates the number of buttons on the input device;
	*   a property of a device object. You can set this property on input devices
	*   you create. In the case of mtouch, this property refers to the number of
	*   buttons on the stylus, not necessarily the touch points. All users can
	*   query the value on the created device. When retrieving or setting this
	*   property type, ensure that you have sufficient storage for one integer.
	*/
	SCREEN_PROPERTY_BUTTON_COUNT = 118,

	/** A string that can be used to identify the vendor of the specified API object.
	*   When retrieving or setting this property type, ensure that you provide a
	*   character buffer. The following API objects have his property, and share
	*   this same definition:
	*   - device
	*   - display
	*/
	SCREEN_PROPERTY_VENDOR = 119,

	/** A string that can be used to identify the product name of the specified API object.
	*   When retrieving or setting this property type, ensure that you provide a
	*   character buffer. The following API objects have his property, and share
	*   this same definition:
	*   - device
	*   - display
	*/
	SCREEN_PROPERTY_PRODUCT = 120,

	/** A pair of integers that define the x- and y- position of a clipped
	*   rectangular area within the window buffers where brush strokes are
	*   allowed to be drawn; a property of a window object. When retrieving or
	*   setting this property type, ensure that you have sufficient storage for
	*   two integers.
	*/
	SCREEN_PROPERTY_BRUSH_CLIP_POSITION = 121,

	/** A pair of integers that define the width and height, in pixels, of a
	*   clipped rectangular area within the window buffers where brush strokes
	*   are allowed to be drawn; a property of a window object. When retrieving
	*   or setting this property type, ensure that you have sufficient storage
	*   for two integers.
	*/
	SCREEN_PROPERTY_BRUSH_CLIP_SIZE = 122,

	/** The x, y and z values for one analog controller; a property of an event
	*   object. For analog controllers that do not have three degrees of
	*   freedom, only x and y values are valid; z will have a value of
	*   @c 0. Regardless of two or three degress of freedom of your analog
	*   controller(s), when retrieving or setting this property type, ensure
	*   that you have sufficient storage for three integers. This property is
	*   only applicable for the following events:
	*   - @c #SCREEN_EVENT_GAMEPAD:
	*   - @c #SCREEN_EVENT_JOYSTICK:
	*/
	SCREEN_PROPERTY_ANALOG0 = 123,

	/** The rx, ry, and rz values for a second analog controller for the
	*   @c #SCREEN_EVENT_GAMEPAD event. For analog controllers that do not have
	*   three degrees of freedom, only x and y values are valid; z will have a
	*   value of @c 0. Regardless of two or three degress of freedom of your
	*   analog controller(s), when retrieving or setting this property type,
	*   ensure that you have sufficient storage for three integers.
	*/
	SCREEN_PROPERTY_ANALOG1 = 124,

	/** The pixmap that contains the brush to be used when the window property,
	*   @c #SCREEN_PROPERTY_SENSITIVITY, has a brush bit set and the
	*   corresponding type of input event is delivered to the API object.
	*   The sensitivity values that can be set to enable brush drawing in your
	*   sensitivity mask are:
	*   - @c #SCREEN_SENSITIVITY_MASK_POINTER_BRUSH for a mouse
	*   - @c #SCREEN_SENSITIVITY_MASK_FINGER_BRUSH for touch
	*   - @c #SCREEN_SENSITIVITY_MASK_STYLUS_BRUSH for a stylus
	*
	*   The pixmap can use an RGB color format for color information. The alpha
	*   channel can be used to define the brush shape. The pixmap buffer size
	*   will determine the size of the brush. No drawing will occur if the
	*   window has a brush sensitivity bit set and no brush pixmap.
	*
	*   When retrieving or setting this property type, ensure that you have
	*   sufficient storage for one @c void pointer. The following API objects
	*   have this  property and share this same definition:
	*   - session
	*   - window
	*/
	SCREEN_PROPERTY_BRUSH = 125,

	/** A single integer that indicates the index of the highest possible touch
	*   ID; a property of a device object. This property can be queried only
	*   from an input device that supports mtouch, i.e., a device of type
	*   @c #SCREEN_EVENT_MTOUCH_TOUCH. When retrieving this property type,
	*   ensure that you have sufficient storage for one integer.
	*/
	SCREEN_PROPERTY_MAXIMUM_TOUCH_ID = 126,

	/** A set of integers that represent the 3x3 transformation matrix used to
	*   convert buffer or device coordinates to display coordinates. The
	*   transformation matrix is stored in row-major order. This property is
	*   typically used when you have a known coordinate and need to know where
	*   it would be located on the display screen. Screen creates a vector
	*   V=(X, Y, 1.0) from the raw coordinates, (X, Y). Then, Screen multiplies
	*   the transformation matrix T with this vector (T x V) to achieve a
	*   resultant vector of (Xa, Ya, Wa). This resultant vector is then divided
	*   by Wa to result in (Xab, Yab, 1.0), which provides (Xab, Yab) as the
	*   transformed display coordinates. When retrieving this property, ensure
	*   that you have sufficient storage for 9 integers. When you set the
	*   @c #SCREEN_PROPERTY_SCALE_FACTOR property of a window or device prior to
	*   retrieving this property, you affect the values of this transformation
	*   matrix. The following API objects have this property, and share this
	*   same definition:
	*   - device (input devices of type @c #SCREEN_EVENT_MTOUCH_TOUCH)
	*             When setting this property, the last row of the transformation
	*             matrix must be [0, 0, non-zero].
	*   - window (@c #SCREEN_PROPERTY_TRANSFORM can only be retrieved and not
	*             set for a window object)
	*/
	SCREEN_PROPERTY_TRANSFORM = 127,

	/** A single integer that provides an alternate key symbol associated to
	*   the event; a property of an event object. On reduced keyboards with a
	*   limited number of keys, the alternate key symbol may correspond to a
	*   non-printable shortcut or command symbol while the main key symbol
	*   would be suitable for text entry. The alternate key symbol may be
	*   identical to the primary key symbol. When retrieving or setting this
	*   property type, ensure that you provide sufficient storage for one
	*   integer. @c #SCREEN_PROPERTY_KEY_ALTERNATE_SYM is applicable only to a
	*   @c #SCREEN_EVENT_KEYBOARD event.
	*/
	SCREEN_PROPERTY_KEY_ALTERNATE_SYM = 128,

	/** An integer that is used to identify the technology used by a particular
	*   object handle; a property of a display object. When retrieving this
	*   property type, ensure that you provide enough storage for one integer.
	*/
	SCREEN_PROPERTY_TECHNOLOGY = 129,

	/**  For internal use only. Do not use. */
	SCREEN_PROPERTY_ADDRESS = 130,

	/** A single integer bitmask indicating the permissions associated with an
	*   API object. @c SCREEN_PROPERTY_PERMISSIONS must be a combination of type
	*    <a href="screen_8h_1Screen_Permission_Masks.xml"> Screen permission masks</a>.
	*    In order to set @c SCREEN_PROPERTY_PERMISSIONS, you must be
	*    the owner of the API object. You can set this property at any time.
	*    Similar to setting file permissions with @c chmod (Change
	*    file modes in POSIX), if you want someone to have special access to
	*    the API object, you need to set the appropriate permissions on that
	*    API object. Screen permissions give you control over who has
	*    access to what. When retrieving or setting this property type, ensure
	*    that you provide sufficient storage for one integer. The following API
	*    objects have this property and share this same definition:
	*   - window
	*   - session
	*/
	SCREEN_PROPERTY_PERMISSIONS = 131,

	/** A single integer bitmask indicating which modifiers associated with a
	 *  device should have a sticky behavior; a property of a device object. A
	 *  sticky modifier turns on its corresponding locked modifier
	 *  automatically, which then gets cleared on the key press, key release
	 *  sequence immediately following. When multiple modifiers are set to be
	 *  sticky, they can be compounded, allowing \<Shift Down\>, \<Shift Up\>,
	 *  \<Alt Down\>, \<Alt Up\>, \<A\> to produce the same results as
	 *  \<Shift Down\>, \<Alt Down\>, \<A\>, \<Shift Up\>, \<Alt Up\>. When
	 *  retrieving or setting this property type, ensure that you provide
	 *  sufficient storage for one integer.
	 */
	SCREEN_PROPERTY_STICKY_MODIFIERS = 132,

	/** A single integer between [-1..100000] that controls the brightness of a
	 *  display on those displays that allow its brightness to be controlled; a
	 *  property of a display object. The default value of -1 implies that
	 *  Screen will automatically set the display intensity based on ambient
	 *  lighting. When retrieving or setting this property type, ensure that
	 *  you provide sufficient storage for one integer.
	 */
	SCREEN_PROPERTY_INTENSITY = 133,

	/*
	* For internal use only. Do not use.
	* SCREEN_PROPERTY_SWAP_WINDOW = 134,
	*/

	/** A pair of integers that can be communicated to the driver owning a
	 *  particular resource. When retrieving or setting this property type,
	 *  ensure that you provide sufficient storage for two integers. The
	 *  following API objects may support driver controls:
	 *  - display
	 *  - device
	 *  Consult your driver documentation to see what driver controls are
	 *  available and the specific usage semantics.
	 */
	SCREEN_PROPERTY_DRIVER_CONTROL = 135,

	/** A single @c long @c long integer that controls the device delay in nanoseconds;
	 *  a property of a device object. A value of zero will cancel the current
	 *  delay if one is set and flush any delayed events. A value greater than
	 *  zero will set the delay or reset an active delay to the specified value.
	 *  The delay is relative to the actual time of the from when the property
	 *  was set in Screen. Ensure that @c SCREEN_PROPERTY_BUFFER_COUNT is set
	 *  before using this property. When retrieving or setting this property
	 *  type, ensure that you provide sufficient storage for one integer.
	 */
	SCREEN_PROPERTY_DELAY = 136,

	/** A pointer to a session. When retrieving or setting this property type,
	*   ensure that you have sufficient storage for one @c void pointer. The
	*   following API objects have this property, each with its own variant of
	*   this definition:
	*   - device
	*           The session on which the input device is focused. All input from
	*           the device will be directed to this particular session.
	*   - event
	*       For the following events, @c #SCREEN_PROPERTY_SESSION
	*       refers to the session associated with the event:
	*           - @c #SCREEN_EVENT_CREATE
	*           - @c #SCREEN_EVENT_CLOSE
	*
	*       For the following events, @c #SCREEN_PROPERTY_SESSION
	*       refers to the session associated with the input for which
	*       the event is intended:
	*           - @c #SCREEN_EVENT_GESTURE
	*           - @c #SCREEN_EVENT_INPUT
	*           - @c #SCREEN_EVENT_JOG
	*           - @c #SCREEN_EVENT_POINTER
	*           - @c #SCREEN_EVENT_KEYBOARD
	*           - @c #SCREEN_EVENT_GAMEPAD
	*           - @c #SCREEN_EVENT_JOYSTICK
	*           - @c #SCREEN_EVENT_MTOUCH_PRETOUCH
	*           - @c #SCREEN_EVENT_MTOUCH_TOUCH
	*           - @c #SCREEN_EVENT_MTOUCH_MOVE
	*           - @c #SCREEN_EVENT_MTOUCH_RELEASE
	*
	*       For the following event, @c #SCREEN_PROPERTY_SESSION
	*       refers to the session whose property is being set or retrieved:
	*           - @c #SCREEN_EVENT_PROPERTY
	*/
	SCREEN_PROPERTY_SESSION = 137,

	/** An integer that is a color to be used with the
	*   @c #SCREEN_TRANSPARENCY_TEST, @c #SCREEN_TRANSPARENCY_REVERSED_TEST
	*   and @c #SCREEN_TRANSPARENCY_SOURCE_COLOR modes. The following API objects
	*   have this property:
	*   - window
	*   - display
	*
	*   When the transparency mode is @c #SCREEN_TRANSPARENCY_TEST or
	*   @c #SCREEN_TRANSPARENCY_REVERSED_TEST, transparency is applied
	*   to each pixel based on a comparison with the reference color.
	*
	*   When the transparency mode is @c #SCREEN_TRANSPARENCY_SOURCE_COLOR,
	*   transparency is applied to each pixel matching the reference color.
	*
	*   When retrieving or setting this property, ensure that you have
	*   sufficient storage for one integer. If this attribute is not specified,
	*   then a default of @c 0 will be used.
	*/
	SCREEN_PROPERTY_REFERENCE_COLOR = 138,

	/** An integer that determines whether gesture recognition is enabled on a
	 * given object. The following types of objects support gesture recognition:
	 *  - device
	 *  - session
	 *  When retrieving or setting this property, ensure that you have
	 *  sufficient storage for one integer.
	 */
	SCREEN_PROPERTY_GESTURE_RECOGNITION = 139,

	/** A single @c long @c long integer that indicates a time duration,
	*   in nanoseconds; a property of an event object. When retrieving or
	*   setting this property type, ensure that you have sufficient storage for
	*   one @c long @c long integer.
	*   This property is only applicable for the #SCREEN_EVENT_GESTURE event.
	*/
	SCREEN_PROPERTY_DURATION = 140,

	/** A pair of integers that define the x- and y- coordinates of
	 *  events with relative displacement.
	 *  When retrieving or setting this property, ensure that you have
	 *  sufficient storage for two integers.
	 *  This property is only applicable for the following events:
	 *  - @c #SCREEN_EVENT_GAMEPAD
	 *  - @c #SCREEN_EVENT_GESTURE
	 *  - @c #SCREEN_EVENT_JOG
	 *  - @c #SCREEN_EVENT_JOYSTICK
	 *  - @c #SCREEN_EVENT_POINTER
	 */
	SCREEN_PROPERTY_DISPLACEMENT = 141,

	/** An integer that represents the speed of an input device; a property of
	 *  a device object. When retrieving or setting this property, ensure that
	 *  you have sufficient storage for one integer.
	 */
	SCREEN_PROPERTY_SPEED = 142,

	/** Four integers that define the acceleration of an input device; a
	 *  property of a device object. The speed model is the following:
	 *    displacement' = displacement * (1 + acceleration) * speed;
	 *  where the acceleration is:
	 *    acceleration = velocity * (constant0 + velocity * constant1).
	 *  The first value corresponds to constant0, the linear factor. The second
	 *  value corresponds to constant1, or the quadratic factor. The third
	 *  and fourth values are minimum and maximum thresholds for the velocity.
	 *  Any displacement with a velocity less than the minimum threshold will
	 *  not be accelerated. Any displacement with a velocity greater than the
	 *  maximum threshold will have its acceleration clamped to the
	 *  acceleration corresponding to the maximum velocity threshold. When
	 *  retrieving or setting this property, ensure that you have sufficient
	 *  storage for one integer.
	 */
	SCREEN_PROPERTY_ACCELERATION = 143,

	/** A set of 16 integers that represent coefficients to configure ballistic
	 * filtering; a property of a device object. Touch events pass through
	 * ballistic filtering to reduce jitter. The first 6 integers configure a
	 * digital filter while the remaining 10 integers are currently unused and
	 * are reserved for future filter configurations.
	 * When retrieving or setting this property, ensure that you have sufficient
	 * storage for 16 integers.
	 */
	SCREEN_PROPERTY_BALLISTIC_COEFFICIENTS = 144,

	SCREEN_PROPERTY_TAB_POSITION = 145,

	/** A set of 32 integers that are used in the following events to
	 *  customize the mapping of the buttons on the input device:
	 *  - @c #SCREEN_EVENT_GAMEPAD
	 *  - @c #SCREEN_EVENT_JOG
	 *  - @c #SCREEN_EVENT_POINTER
	 *  - @c #SCREEN_EVENT_JOYSTICK
	 *  This is a property of a device object. When retrieving or setting this
	 *  property, ensure that you have sufficient storage for 32 integers.
	 */
	SCREEN_PROPERTY_BUTTON_MAP = 146,

	/**  A pair of integers that define the x and y position, in pixels, of a
	*   rectangular area where the shadow cast by a window is located. The
	*   shadow rectangle isn't clipped by the window. However, the size and
	*   position are relative to the window casting the shadow. If the shadow
	*   position is not specified (but the size is), the shadow position defaults
	*   to a (0,0) offset from the top left of the window. When retrieving
	*   or setting this property type, ensure that you have sufficient storage
	*   for two integers. The following API objects have this property, each with
	*   its own variant of this definition:
	*   - window
	*/
	SCREEN_PROPERTY_SHADOW_POSITION = 147,

	/**  A pair of integers that define the width and height, in pixels, of a
	*   rectangular area where the shadow cast by a window is located. The
	*   shadow rectangle isn't clipped by the window. However, its size and
	*   position are relative to the window casting the shadow. If the shadow size
	*   is not specified (but the shadow position is), the shadow size defaults to
	*   the size of the window casting the shadow. When retrieving or setting this
	*   property type, ensure that you have sufficient storage for two integers.
	*   The following API objects have this property, each with its own variant of
	*   this definition:
	*   - window
	*/
	SCREEN_PROPERTY_SHADOW_SIZE = 148,

	/** An integer specifying which cursor shape to display when the pointer
	 *  is over a session. When retrieving or setting this property type, ensure
	 *  that you have sufficient storage for one integer. The following API objects
	 *  have this property, each with its own variant of this definition:
	 *  - session
	 */
	SCREEN_PROPERTY_CURSOR = 149,
};

/** @brief The screen mode types
 *  @anonenum Screen_Mode_Types Screen mode types
 */
enum {
	/** Used in the @c flags of the type @c #screen_display_mode_t to
	*   indicate that this mode is the preferred mode.
	*/
	SCREEN_MODE_PREFERRED = 0x1
};

/** @brief The color space types that are supported by window and pixmap objects
*   @anonenum Screen_Color_Space_Types Screen color space types
*/
enum {
	SCREEN_COLOR_SPACE_UNCORRECTED = 0x0,  /**< Default */
	SCREEN_COLOR_SPACE_SRGB        = 0x1,  /**< Standard RGB */
	SCREEN_COLOR_SPACE_LRGB        = 0x2,  /**< Linear RGB */
	SCREEN_COLOR_SPACE_BT601       = 0x3,  /**< Refer to BT.601 standards */
	SCREEN_COLOR_SPACE_BT601_FULL  = 0x4,  /**< Refer to BT.601 standards */
	SCREEN_COLOR_SPACE_BT709       = 0x5,  /**< Refer to BT.709 standards */
	SCREEN_COLOR_SPACE_BT709_FULL  = 0x6,  /**< Refer to BT.709 standards */
};

/**
*   @brief Defines the mode preferred index
*
*   Used as a convenience value to pass when setting @c #SCREEN_PROPERTY_MODE
*   to fall back to the default video mode without having to first query all
*   the modes supported by the display to find the one with
*   @c #SCREEN_MODE_PREFERRED set in @c flags.
*/
#define SCREEN_MODE_PREFERRED_INDEX (-1)

/**
*    A structure to contain values related to Screen display mode.
*/
typedef struct _screen_mode {
	_Uint32t width;             /**< Width of display */
	_Uint32t height;            /**< Height of display*/
	_Uint32t refresh;           /**< Refresh of display */
	_Uint32t interlaced;        /**< Interlace mode of display */
	_Uint32t aspect_ratio[2];   /**< Aspect ratio of display */
	_Uint32t flags;             /**< Mutext flags of display */
	_Uint32t index;             /**< Index of display */
	_Uint32t reserved[6];       /**< Reserved bits */
} screen_display_mode_t;

/**@brief Types of Screen API objects
 * @section Screen_Object_Types Screen object types
 */
enum {
	SCREEN_OBJECT_TYPE_CONTEXT             = 0,
	SCREEN_OBJECT_TYPE_GROUP               = 1,
	SCREEN_OBJECT_TYPE_DISPLAY             = 2,
	SCREEN_OBJECT_TYPE_DEVICE              = 3,
	SCREEN_OBJECT_TYPE_PIXMAP              = 4,
	SCREEN_OBJECT_TYPE_SESSION             = 6,
	SCREEN_OBJECT_TYPE_WINDOW              = 8,
};

/** @brief Types of power modes
 *  @anonenum Screen_Power_Mode_Types Screen power mode types
 */
enum {
	/** The power mode in an inactive state. */
	SCREEN_POWER_MODE_OFF = 0x7680,

	/** The power mode in a state of being partially off; the display
	*   or device is no longer active. The power usage in this state can be
	*   greater than in @c #SCREEN_POWER_MODE_OFF, but will allow for a
	*   faster transition to active state.
	*/
	SCREEN_POWER_MODE_SUSPEND = 0x7681,

	/** The power mode in a state of reduced power; the display or
	*   device is active, but may be slower to update than if it was in
	*   @c #SCREEN_POWER_MODE_ON.
	*/
	SCREEN_POWER_MODE_LIMITED_USE = 0x7682,

	/** The power mode in an active state. */
	SCREEN_POWER_MODE_ON = 0x7683,
};

/** @brief Types of idle modes
 *  @anonenum Screen_Idle_Mode_Types Screen idle mode types
 */
enum {
	/** The default idle mode; the display is allowed to go idle after
	*   the period of time indicated by @c #SCREEN_PROPERTY_IDLE_TIMEOUT
	*   and potentially turn off.
	*/
	SCREEN_IDLE_MODE_NORMAL = 0,

	/** The idle mode which will prevent the display from going idle
	*   after a period of no input - such as video playback. By default, the
	*   display will go idle after the period of time indicated by
	*   @c #SCREEN_PROPERTY_IDLE_TIMEOUT.
	*/
	SCREEN_IDLE_MODE_KEEP_AWAKE = 1,
};

/** @brief Types of connections to a display
*   @anonenum Screen_Display_Types Screen display types
*/
enum {
	/** An internal connection type to the display */
	SCREEN_DISPLAY_TYPE_INTERNAL = 0x7660,

	/** A composite connection type to the display */
	SCREEN_DISPLAY_TYPE_COMPOSITE = 0x7661,

	/** A S-Video connection type to the display */
	SCREEN_DISPLAY_TYPE_SVIDEO = 0x7662,

	/** A component connection type to the display - specifically
	*   the YPbPr signal of the component connection.
	*/
	SCREEN_DISPLAY_TYPE_COMPONENT_YPbPr = 0x7663,

	/** A component connection type to the display - specifically
	*   the RGB signal of the component connection.
	*/
	SCREEN_DISPLAY_TYPE_COMPONENT_RGB = 0x7664,

	/** A component connection type to the display - specifically
	*   the RBGHV signal of the component connection.
	*/
	SCREEN_DISPLAY_TYPE_COMPONENT_RGBHV = 0x7665,

	/** A DVI connection type to the display */
	SCREEN_DISPLAY_TYPE_DVI = 0x7666,

	/** A HDMI connection type to the display */
	SCREEN_DISPLAY_TYPE_HDMI = 0x7667,

	/** A DisplayPort connection type to the display */
	SCREEN_DISPLAY_TYPE_DISPLAYPORT = 0x7668,

	/** A connection type to the display which is one other than
	*   internal, composite, S-Video, component, DVI, HDMI, or DisplayPort.
	*/
	SCREEN_DISPLAY_TYPE_OTHER = 0x7669,
};

/** @brief Types of technologies for a display
*   @anonenum Screen_Display_Technology_Types Screen display technology types
*/
enum {
	/** Any other display technology that isn't enumerated. */
	SCREEN_DISPLAY_TECHNOLOGY_UNKNOWN = 0,

	/** All monochrome and standard tricolor CRTs. */
	SCREEN_DISPLAY_TECHNOLOGY_CRT = 1,

	/** All active and passive matrix LCDs. */
	SCREEN_DISPLAY_TECHNOLOGY_LCD = 2,

	/** All PDP types including DC and AC plasma displays. */
	SCREEN_DISPLAY_TECHNOLOGY_PLASMA = 3,

	/** Inorganic LED. */
	SCREEN_DISPLAY_TECHNOLOGY_LED = 4,

	/** Organic LED/OEL. */
	SCREEN_DISPLAY_TECHNOLOGY_OLED = 5,
};

/** @brief Types of mirrors
 *  @anonenum Screen_Mirror_Types Screen mirror types
 */
enum {
	/** Mirroring is disabled. */
	SCREEN_MIRROR_DISABLED = 0,

	/** Mirroring is enabled and that the aspect-ratio of the image is 1:1.
	*/
	SCREEN_MIRROR_NORMAL = 1,

	/** Mirroring is enabled and that the image should fill the screen while not
	*    preserving the aspect-ratio.
	*/
	SCREEN_MIRROR_STRETCH = 2,

	/** Mirroring is enabled and that the image should fill the screen while
	*   preserving the aspect-ratio. Image content may be clipped.
	*/
	SCREEN_MIRROR_ZOOM = 3,

	/** Mirroring is enabled and that the image should fill the screen while
	*   preserving the aspect-ratio. Image may be shown with black bars where
	*    applicable.
	*/
	SCREEN_MIRROR_FILL = 4,
};

/** @brief Types of available alpha blending modes
*   @anonenum Screen_Alpha_Mode_Types Screen Alpha Blending Modes
*/
enum {
	/**  The non pre-multiplied alpha content. This is the default.
	*    In this case, the source blending is done using the equation:
	*
	*    c(r,g,b) = s(r,g,b) * s(a) + d(r,g,b) * (1 - s(a))
	**/
	SCREEN_NON_PRE_MULTIPLIED_ALPHA = 0,

	/**  The pre-multiplied alpha content.  In this case, the source blending is
	*    done using the equation:
	*
	*    c(r,g,b) = s(r,g,b) + d(r,g,b) * (1 - s(a))
	**/
	SCREEN_PRE_MULTIPLIED_ALPHA = 1,
};

/** @brief Types of supported pixel formats
*
*   Formats with an alpha channel will have source alpha enabled automatically.
*   Applications that want the Screen library to disregard the alpha channel can
*   choose a pixel format with an X.
*   @anonenum Screen_Pixel_Format_Types Screen pixel format types
*/
enum {
	SCREEN_FORMAT_BYTE = 1,

	/** 16 bits per pixel (4 bits per channel) RGB with alpha channel */
	SCREEN_FORMAT_RGBA4444 = 2,

	/** 16 bits per pixel (4 bits per channel) RGB with alpha channel
	*   disregarded
	*/
	SCREEN_FORMAT_RGBX4444 = 3,

	/** 16 bits per pixel, 2 bytes containing R, G, and B values
	* (5 bits per channel with single-bit alpha channel)
	*/
	SCREEN_FORMAT_RGBA5551 = 4,

	/** 16 bits per pixel, 2 bytes containing R, G, and B values
	* (5 bits per channel with single-bit alpha channel disregarded)
	*/
	SCREEN_FORMAT_RGBX5551 = 5,

	/** 16 bits per pixel; uses five bits for red, six bits for green and
	*   five bits for blue. This pixel format represents each pixel in the
	*   following order (high byte to low byte): RRRR RGGG GGGB BBBB
	*/
	SCREEN_FORMAT_RGB565 = 6,

	/** 24 bits per pixel (8 bits per channel) RGB */
	SCREEN_FORMAT_RGB888 = 7,

	/** 32 bits per pixel (8 bits per channel) RGB with alpha channel */
	SCREEN_FORMAT_RGBA8888 = 8,

	/** 32 bits per pixel (8 bits per channel) RGB with alpha channel disregarded */
	SCREEN_FORMAT_RGBX8888 = 9,

	/** 9 bits per pixel planar YUV format. 8-bit Y plane and
	*   8-bit 4x4 subsampled U and V planes. Registered by Intel.
	*/
	SCREEN_FORMAT_YVU9 = 10,

	/** Standard NTSC TV transmission format. */
	SCREEN_FORMAT_YUV420 = 11,

	/** 12 bits per pixel planar YUV format. 8-bit Y plane
	*   and 2x2 subsampled, interleaved U and V planes.
	*/
	SCREEN_FORMAT_NV12 = 12,

	/** 12 bits per pixel planar YUV format.  8-bit Y plane
	*  and 8-bit 2x2 subsampled  U and V planes.
	*/
	SCREEN_FORMAT_YV12 = 13,

	/** 16 bits per pixel packed YUV format. YUV 4:2:2 -
	*   Y sampled at every pixel, U and V sampled at every second pixel
	*   horizontally on each line. A macropixel contains 2 pixels in 1 uint32.
	*/
	SCREEN_FORMAT_UYVY = 14,

	/** 16 bits per pixel packed YUV format. YUV 4:2:2 -
	*   as in UYVY, but with different component ordering within the uint32
	*   macropixel.
	*/
	SCREEN_FORMAT_YUY2 = 15,

	/** 16 bits per pixel packed YUV format. YUV 4:2:2 -
	*   as in UYVY, but with different component ordering within the uint32
	*   macropixel.
	*/
	SCREEN_FORMAT_YVYU = 16,

	/** Packed YUV format. Inverted version of UYVY. */
	SCREEN_FORMAT_V422 = 17,

	/** Packed YUV format. Combined YUV and alpha */
	SCREEN_FORMAT_AYUV = 18,

	SCREEN_FORMAT_NFORMATS,  /* Number of pixel formats */
};

/** @brief Types of usage flags
*
*   Usage flags are used when allocating buffers. Depending on the usage,
*   different constraints such as width, height, stride granularity or special
*   alignment must be observed. The usage is also valuable in determining
*   the amount of caching that can be set on a particular buffer.
*   @anonenum Screen_Usage_Flag_Types Screen usage flag types
*/
enum {
	/** Reserved, cannot be used by applications */
	SCREEN_USAGE_DISPLAY = (1 << 0),

	/** Flag to indicate that buffer(s) associated with the API object can be
	*   read from.
	*/
	SCREEN_USAGE_READ = (1 << 1),

	/** Flag to indicate that buffer(s) associated with the API object can be
	*    written to.
	*/
	SCREEN_USAGE_WRITE = (1 << 2),

	/** Flag to indicate that buffer(s) associated with the API object can be
	*   used for native API operations. If using blits or fills, this flag must be
	*   set on the API object.
	*/
	SCREEN_USAGE_NATIVE = (1 << 3),

	/** Flag to indicate that OpenGL ES 1.X is used for rendering the buffer
	*    associated with the API object.
	*/
	SCREEN_USAGE_OPENGL_ES1 = (1 << 4),

	/** Flag to indicate that OpenGL ES 2.X is used for rendering the buffer
	*    associated with the API object.
	*/
	SCREEN_USAGE_OPENGL_ES2 = (1 << 5),

	/** Flag to indicate that OpenGL ES 3.X is used for rendering the buffer
	*    associated with the API object.
	*/
	SCREEN_USAGE_OPENGL_ES3 = (1 << 11),

	/** Flag to indicate that OpenVG is used for rendering the buffer
	*    associated with the API object.
	*/
	SCREEN_USAGE_OPENVG = (1 << 6),

	/** Flag to indicate that the buffer can be written to by a video decoder.
	*/
	SCREEN_USAGE_VIDEO = (1 << 7),

	/** Flag to indicate that the buffer can be written to by capture devices
	*   (such as cameras, analog-to-digital-converters, ...), and read by
	*   a hardware video encoder.
	*/
	SCREEN_USAGE_CAPTURE = (1 << 8),

	/** Flag to indicate that the buffer can be re-configured from landscape to
	*   portrait orientation without reallocation.
	*/
	SCREEN_USAGE_ROTATION = (1 << 9),   /**< Rotation */

	/** Flag to indicate the use of a non-composited layer.
	*   The Screen API uses a composited layer by default.
	*   The @c #SCREEN_USAGE_OVERLAY flag is used to override this
	*   default behaviour to use a non-composited layer instead. Note that
	*   when the overlay usage bit is added or removed, then changing
	*   @c #SCREEN_PROPERTY_USAGE affects the pipeline. Use the
	*   @c #SCREEN_USAGE_OVERLAY flag in favor of the
	*   @c #SCREEN_PROPERTY_PIPELINE property to specify whether
	*   to use a composited or a non-composited layer.
	*/
	SCREEN_USAGE_OVERLAY = (1 << 10),
};

/** @brief Types of window transparencies
 *  @anonenum Screen_Transparency_Types Screen transparency types
 */
enum {
	/** Destination pixels are replaced by source pixels, including the alpha
	*   channel.
	*/
	SCREEN_TRANSPARENCY_SOURCE = 0,

	/** Destination pixels are replaced by source pixels when the source pixel
	*   value is greater than the reference value.
	*   See @c #SCREEN_PROPERTY_REFERENCE_COLOR.
	*/
	SCREEN_TRANSPARENCY_TEST = 1,

	/** Destination pixels are replaced by source pixels when
	*   the source color does not match the reference color value.
	*   See @c #SCREEN_PROPERTY_REFERENCE_COLOR.
	*/
	SCREEN_TRANSPARENCY_SOURCE_COLOR = 2,

	/** Typical alpha blending; the source pixels are blended over the destination pixels.
	*/
	SCREEN_TRANSPARENCY_SOURCE_OVER = 3,

	/** Destination pixels are replaced by fully-visible source pixels.
	*/
	SCREEN_TRANSPARENCY_NONE = 4,

	/** Source is considered completely transparent; the destination is not modified.
	*/
	SCREEN_TRANSPARENCY_DISCARD = 5,

	/** Destination pixels are replaced by source pixels when the source pixel
	*   value is less than the reference value.
	*   See @c #SCREEN_PROPERTY_REFERENCE_COLOR.
	*/
	SCREEN_TRANSPARENCY_REVERSED_TEST = 6,
};

/** @brief Types of sensitivities
 *  @anonenum Screen_Sensitivity_Types Screen sensitivity types
 */
enum {
	/**
	*   The default sensitivity. Pointer and multi-touch events are
	*   forwarded to the window's context if they intersect with the window and
	*   are in an area of the window that is not fully transparent. The window
	*   receives keyboard, gamepad, joystick events if it has input focus.
	*   Raising a window, pointer or multi-touch release event in the window
	*   will cause the window to acquire input focus.
	*/
	SCREEN_SENSITIVITY_TEST = 0,

	/**
	*    That pointer and touch events are always forwarded to the
	*    window's context if they interect with the window - even if the window
	*    is transparent in that area. The window receives keyboard, gamepad,
	*    joystick events if it has input focus. Raising a window, pointer or
	*    multi-touch release event in that window will cause it to acquire input
	*    focus.
	*/
	SCREEN_SENSITIVITY_ALWAYS = 1,

	/**
	*    The window never receives pointer or multi-touch events.
	*    The window never acquires input focus, even after it has been raised.
	*    The window will only receive input events that are directly injected into
	*    it from outside sources.
	*/
	SCREEN_SENSITIVITY_NEVER = 2,

	/**
	*    Pointer and touch events are forwarded to the window's
	*    context if they intersect the window and are in an area of the window
	*    that is not fully transparent. The window does not acquire input focus
	*    after being raised or after a pointer or multi-touch release event
	*    occurs. Therefore, the window will not receive keyboard, gamepad, or
	*    joystick input unless it is sent directly into the window from an
	*    outside source.
	*/
	SCREEN_SENSITIVITY_NO_FOCUS = 3,

	/**
	*    Pointer and touch events are forwarded to the window's
	*    context no matter where they are on the screen. The window is considered
	*    full screen for the purposes of input hit tests. Transparency is
	*    ignored. The window will receive keyboard, gamepad, and joystick events
	*    if it has input focus. Raising the window or a pointer or multi-touch
	*    release event in the window will cause it to acquire input focus.
	*/
	SCREEN_SENSITIVITY_FULLSCREEN = 4,
};

/** @brief Types of sensitivity masks
*
*    These masks are intended to be combined in a single integer bitmask
*    representing combinations of desired senstivites to be applied to a
*    window.
*    @anonenum Screen_Sensitivity_Masks Screen sensitivity masks
*/
enum {
	/**
	*    Pointer and touch events are always forwarded to the
	*    window's context if they interect with the window - regardless of
	*    transparency. The window receives keyboard, gamepad,
	*    joystick events if it has input focus. Raising a window, pointer or
	*    multi-touch release event in that window will cause it to acquire input
	*    focus.
	*/
	SCREEN_SENSITIVITY_MASK_ALWAYS = (1 << 0),

	/**
	*    The window never receives pointer or multi-touch events.
	*    The window never acquires input focus, even after it has been raised.
	*    The window will only receive input events that are directly injected into
	*    it from outside sources.
	*/
	SCREEN_SENSITIVITY_MASK_NEVER = (2 << 0),

	   /**
	*    Pointer and touch events are forwarded to the window's
	*    context if they intersect the window and are in an area of the window
	*    that is not fully transparent. The window does not acquire input focus
	*    after being raised or after a pointer or multi-touch release event
	*    occurs. Therefore, the window will not receive keyboard, gamepad, or
	*    joystick input unless it is sent directly into the window from an
	*    outside source.
	*/
	SCREEN_SENSITIVITY_MASK_NO_FOCUS = (1 << 3),

	/**
	*    Pointer and touch events are forwarded to the window's
	*    context no matter where they are on the screen. The window is considered
	*    full screen for the purposes of input hit tests. Transparency is
	*    ignored. The window will receive keyboard, gamepad, and joystick events
	*    as long as the window is visible.
	*/
	SCREEN_SENSITIVITY_MASK_FULLSCREEN = (1 << 4),

	/**
	*   Windows underneath this window can receive pointer
	*   or multi-touch events even if this window has input focus.
	*/
	SCREEN_SENSITIVITY_MASK_CONTINUE = (1 << 5),

	/**
	*   The window never receives pointer or multi-touch events.
	*   The window never acquires input focus, even after it has been raised.
	*   The window will only receive input events that are directly injected into
	*   it from outside sources.
	*/
	SCREEN_SENSITIVITY_MASK_STOP = (2 << 5),

	/**
	*   The window receives pointer events, even in areas of transparency, if
	*   the source coordinates of the event are within the brush clip
	*   rectangle. This mode supercedes SCREEN_SENSITIVITY_MASK_NEVER. The
	*   windowing system also draws brush strokes based on the pointer events
	*   directly onto the screen and the window buffer.
	*/
	SCREEN_SENSITIVITY_MASK_POINTER_BRUSH = (1 << 7),

	/**
	*   The window receives multi-touch events with a finger contact type, even
	*   in areas of transparency, if the source coordinates of the event are
	*   within the brush clip rectangle. This mode supercedes
	*   SCREEN_SENSITIVITY_MASK_NEVER. The windowing system also draws brush
	*   strokes based on the touch events directly onto the screen and the
	*   window buffer. Multiple contacts will cause multiple brush strokes to
	*   be drawn.
	*/
	SCREEN_SENSITIVITY_MASK_FINGER_BRUSH = (1 << 8),

	/**
	*   The window receives multi-touch events with a stylus contact type, even
	*   in areas of transparency, if the source coordinates of the event are
	*   within the brush clip rectangle. This mode supercedes
	*   SCREEN_SENSITIVITY_MASK_NEVER. The windowing system also draws brush
	*   strokes based on the touch events directly onto the screen and the
	*   window buffer. Multiple contacts will cause multiple brush strokes to
	*   be drawn.
	*/
	SCREEN_SENSITIVITY_MASK_STYLUS_BRUSH = (1 << 9),

	/**
	 *   Setting this bit causes the system to go into overdrive when the window
	 *   gets an input event. The effect of this sensitivity mask depends on the
	 *   power management algorithms in place and on the platform in general.
	 */
	SCREEN_SENSITIVITY_MASK_OVERDRIVE = (1 << 10),

	/**
	 *   The window receives touch and point data only when the position is
	 *   within the bounds of the window. If a pointer drag operation or a
	 *   touch and move sequence leaves the window, the window will receive
	 *   an input control notification that the event has left the bounds of
	 *   the window and will not receive the subsequent events until the next
	 *   touch or button press, or when the events re-enter the window again.
	 *   Note that re-entry will only occur if the event leaves a window that
	 *   also has clipping enabled on its sensitivity mask.
	 */
	SCREEN_SENSITIVITY_MASK_CLIPPED = (1 << 11),
};

/**  @brief Types of scaling qualities
*
*   Each enumerator specifies the suggested amount of filtering to be performed
*   by the windowing system when scaling is required to draw the window. This
*   amount of filtering is not a constant quantity; it is specfied relative to
*   each of the other possible scale qualities.
*   @anonenum Screen_Scale_Quality_Types Screen scale quality types
*/
enum {
	/** The suggested amount of filtering that is slower than
	*   @c SCALE_QUALITY_FASTEST, but should have better quality.
	*/
	SCREEN_QUALITY_NORMAL = 0,

	/** The suggested amount of filtering that is faster than
	*   @c SCALE_QUALITY_NORMAL, but may have reduced quality.
	*/
	SCREEN_QUALITY_FASTEST = 1,

	/** The suggested amount of filtering that is slower than
	*   @c SCALE_QUALITY_NORMAL, but should have better quality.
	*/
	SCREEN_QUALITY_NICEST = 2,
};

/** @brief Types of content modes
 *
 *   The CBABC (content-based automatic brightness control) refers to the
 *   brightness control that is based on content, not ambient light. However,
 *   this enumeration is used mainly to describe the content type of the window,
 *   rather than the brightness control. If not set, the type will default to
 *   the mode of the display framebuffer.
 *  @anonenum Screen_CBABC_Mode_Types Screen content mode types
 */
enum {
	/** The window content is not video, UI or photo. */
	SCREEN_CBABC_MODE_NONE = 0x7671,

	/** The window content is video. */
	SCREEN_CBABC_MODE_VIDEO = 0x7672,

	/** The window content is UI. */
	SCREEN_CBABC_MODE_UI = 0x7673,

	/** The window content is photo. */
	SCREEN_CBABC_MODE_PHOTO = 0x7674,
};

/** @brief Types of permission masks
*
*    These masks are intended to be combined in a single integer bitmask
*    representing combinations of desired permissions to be applied to a
*    window.
*    @anonenum Screen_Permission_Masks Screen permission masks
*/
enum {
	/** Read access to the owner of a window.*/
	SCREEN_PERMISSION_IRWIN = (1 << 0),

	/** Write access to the owner of a window.*/
	SCREEN_PERMISSION_IWWIN = (1 << 1),

	/** Inject access to the owner of a window.*/
	SCREEN_PERMISSION_IXWIN = (1 << 2),

	/** Read access to the parent of a window.*/
	SCREEN_PERMISSION_IRTOP = (1 << 4),

	/** Write access to the parent of a window.*/
	SCREEN_PERMISSION_IWTOP = (1 << 5),

	/** Inject access to the parent of a window.*/
	SCREEN_PERMISSION_IXTOP = (1 << 6),

	/** Read access to contexts with the same process id.*/
	SCREEN_PERMISSION_IRPID = (1 << 8),

	/** Write access to contexts with the same process id.*/
	SCREEN_PERMISSION_IWPID = (1 << 9),

	/** Inject access to contexts with the same process id.*/
	SCREEN_PERMISSION_IXPID = (1 << 10),

	/** Read access to others with the same process group id.*/
	SCREEN_PERMISSION_IRPGP = (1 << 12),

	/** Write access to others with the same process group id.*/
	SCREEN_PERMISSION_IWPGP = (1 << 13),

	/** Inject access to others with the same process group id.*/
	SCREEN_PERMISSION_IXPGP = (1 << 14),

	/** Read access to clients with the same user id.*/
	SCREEN_PERMISSION_IRUSR = (1 << 16),

	/** Write access to clients with the same user id.*/
	SCREEN_PERMISSION_IWUSR = (1 << 17),

	/** Inject access to clients with the same user id.*/
	SCREEN_PERMISSION_IXUSR = (1 << 18),

	/** Read access to clients with the same group id.*/
	SCREEN_PERMISSION_IRGRP = (1 << 20),

	/** Write access to clients with the same group id.*/
	SCREEN_PERMISSION_IWGRP = (1 << 21),

	/** Inject access to clients with the same group id.*/
	SCREEN_PERMISSION_IXGRP = (1 << 22),

	/** Read access to others in the same application group.*/
	SCREEN_PERMISSION_IRAGP = (1 << 24),

	/** Write access to others in the same application group.*/
	SCREEN_PERMISSION_IWAGP = (1 << 25),

	/** Inject access to others in the same application group.*/
	SCREEN_PERMISSION_IXAGP = (1 << 26),

	/** Read access to all others.*/
	SCREEN_PERMISSION_IROTH = (1 << 28),

	/** Write access to all others.*/
	SCREEN_PERMISSION_IWOTH = (1 << 29),

	/** Inject access to all others.*/
	SCREEN_PERMISSION_IXOTH = (1 << 30),
};

/**
*   @addtogroup screen_events
*   @{
*/
/** @brief Types of events
 *  @anonenum Screen_Event_Types Screen event types
 */
enum {
	/** A blocking event indicating that there are currently no events in the
	*   queue.
	*/
	SCREEN_EVENT_NONE = 0,

	/** Dispatched when a child window is created.*/
	SCREEN_EVENT_CREATE = 1,

	/** Dispatched when a property is set.*/
	SCREEN_EVENT_PROPERTY = 2,

	/** Dispatched when a child window is destroyed.*/
	SCREEN_EVENT_CLOSE = 3,

	/** Dispatched when an unknown input event occurs.*/
	SCREEN_EVENT_INPUT = 4,

	/** Used to describe various Screen API objects:
	*   - device: represents a valid input device type; used for a device
	*             object's @c #SCREEN_PROPERTY_TYPE
	*   - event: dispatched when a jog dial input event occurs
	*   - session: represents a valid input session type; used for a session
	*             object's @c #SCREEN_PROPERTY_TYPE
	*/
	SCREEN_EVENT_JOG = 5,

	/** Used to describe various Screen API objects:
	*   - device: represents a valid input device type; used for a device
	*             object's @c #SCREEN_PROPERTY_TYPE
	*   - event: dispatched when a pointer input event occurs
	*   - session: represents a valid input session type; used for a session
	*             object's @c #SCREEN_PROPERTY_TYPE
	*/
	SCREEN_EVENT_POINTER = 6,

	/** Used to describe various Screen API objects:
	*   - device: represents a valid input device type; used for a device
	*             object's @c #SCREEN_PROPERTY_TYPE
	*   - event: dispatched when a keyboard input event occurs
	*   - session: represents a valid input session type; used for a session
	*             object's @c #SCREEN_PROPERTY_TYPE
	*/
	SCREEN_EVENT_KEYBOARD = 7,

	/** Dispatched when a user event is detected.*/
	SCREEN_EVENT_USER = 8,

	/** Dispatched when a child window has posted its first frame.*/
	SCREEN_EVENT_POST = 9,

	/** Dispatched to the window manager indicating that a rotation effect has
	*   completed.
	*/
	SCREEN_EVENT_EFFECT_COMPLETE = 10,

	/** Dispatched when an external display is detected.*/
	SCREEN_EVENT_DISPLAY = 11,

	/** Dispatched when the window enters an idle state.*/
	SCREEN_EVENT_IDLE = 12,

	/** Dispatched when a handle to a window is lost.*/
	SCREEN_EVENT_UNREALIZE = 13,

	/** Used to describe various Screen API objects:
	*   - device: represents a valid input device type; used for a device
	*             object's @c #SCREEN_PROPERTY_TYPE
	*   - event: dispatched when a gamepad input event occurs
	*   - session: represents a valid input session type; used for a session
	*             object's @c #SCREEN_PROPERTY_TYPE
	*/
	SCREEN_EVENT_GAMEPAD = 14,

	/** Used to describe various Screen API objects:
	*   - device: represents a valid input device type; used for a device
	*             object's @c #SCREEN_PROPERTY_TYPE
	*   - event: dispatched when a joystick input event occurs
	*   - session: represents a valid input session type; used for a session
	*             object's @c #SCREEN_PROPERTY_TYPE
	*/
	SCREEN_EVENT_JOYSTICK = 15,

	/** Dispatched when an input device is detected.*/
	SCREEN_EVENT_DEVICE = 16,

	/** Dispatched when changes to the input state require that a
	*   notification be sent to the application for the event processing to
	*   be performed correctly. This includes gestures that may start
	*   without a touch or button press; or end without a release.
	*/
	SCREEN_EVENT_INPUT_CONTROL = 17,

	/** Used to describe a device or event API object:
	*   - device: represents a valid input device type; used for a device
	*             object's @c #SCREEN_PROPERTY_TYPE
	*   - event: dispatched when a gesture-based input event occurs or when
	 *           gesture recognition is enabled on a touch or pointer device.
	 */
	SCREEN_EVENT_GESTURE = 18,

	/** Dispatched when a multi-touch event is detected before it can be
	 *  properly resolved. This event is used to help reduce latency when touch
	 *  processing requires several samples before a touch event can be
	 *  formulated. Any handling of delayed touch events should keep in mind
	 *  that the event is very likely to be aborted by an input control
	 *  event.
	 */
	SCREEN_EVENT_MTOUCH_PRETOUCH = 99,

	/* These are set to match the @c INPUT_EVENT_* enums to avoid having to
	*  remap the event types when they come in from libinputevents.
	*/
	/** Used to describe various Screen API objects:
	*   - device: represents a valid input device type; used for a device
	*             object's @c #SCREEN_PROPERTY_TYPE
	*   - event: dispatched when a multi-touch event is detected
	*   - session: represents a valid input session type; used for a session
	*             object's @c #SCREEN_PROPERTY_TYPE
	*/
	SCREEN_EVENT_MTOUCH_TOUCH = 100,

	/** Dispatched when a multi-touch move event is detected. For example,
	 *  when the user moves his or her fingers to make an input gesture.
	 */
	SCREEN_EVENT_MTOUCH_MOVE = 101,

	/** Dispatched when a multi-touch release event occurs, or when the user
	 *  completes the multi-touch gesture.
	 */
	SCREEN_EVENT_MTOUCH_RELEASE = 102,
};
/** @} */

/** @brief Types of event flags
*
*    Flags that indicate whether the event contains logical data that can be
*    used by applications.
*    @anonenum Screen_Flags_Masks Screen event flags
*/
enum {
	/** Event contains keyboard mapping for key down. */
	SCREEN_FLAG_KEY_DOWN              = (1 << 0),

	/** Event contains keyboard mapping for key repeat. */
	SCREEN_FLAG_KEY_REPEAT            = (1 << 1),

	/** Event contains valid scan codes. */
	SCREEN_FLAG_SCAN_VALID            = (1 << 5),

	/** Event contains keyboard mapping for key symbols. */
	SCREEN_FLAG_SYM_VALID             = (1 << 6),

	/** Event contains keyboard mapping for caps lock. */
	SCREEN_FLAG_CAP_VALID             = (1 << 7),

	/** Event contains valid displacements. */
	SCREEN_FLAG_DISPLACEMENT_VALID    = (1 << 12),

	/** Event contains valid absolute display coordinates. */
	SCREEN_FLAG_POSITION_VALID        = (1 << 13),

	/** Event contains valid buffer coordinates. */
	SCREEN_FLAG_SOURCE_POSITION_VALID = (1 << 14),

	/** Event contains valid size in display coordinates. */
	SCREEN_FLAG_SIZE_VALID            = (1 << 15),
};

/**
*   @addtogroup screen_blits
*   @{
*/
/** @brief Types of blit attributes
 *  @anonenum Screen_Blit_Types Screen blit types
 */
enum {
	/**  Used to terminate the token-value pairs in an attribute list. */
	SCREEN_BLIT_END = 0,

	/**
	*    The horizontal position of the rectangle in the source buffer.
	*    The offset is the distance, in pixels, from the left edge of the source
	*    buffer. If this attribute is not specified, then a default of @c 0 will
	*    be used.
	*/
	SCREEN_BLIT_SOURCE_X = 1,

	/**
	*    The vertical position of the rectangle in the source buffer.
	*    The offset is the distance, in pixels, from the top edge of the source
	*    buffer. If this attribute is not specified, then a default of @c 0 will
	*    be used.
	*/
	SCREEN_BLIT_SOURCE_Y = 2,

	/**
	*    The width, in pixels, of the rectangle in the source buffer.
	*    If this attribute is not specified, then the source buffer width will
	*    be used. The horizontal and vertical scale factors don't have to be
	*    equal. It is acceptable to specify a source width that is larger than
	*    the destination width while the source height is smaller than the
	*    destination height, and vice versa.
	*/
	SCREEN_BLIT_SOURCE_WIDTH = 3,

	/**
	*    The height, in pixels, of the rectangle in the source buffer.
	*    If this attribute is not specified, then the source buffer
	*    height will be used. The horizontal and vertical scale factors don't have
	*    to be equal. It is acceptable to specify a source width that is larger
	*    than the destination width while the source height is smaller than
	*    the destination height, and vice versa.
	*/
	SCREEN_BLIT_SOURCE_HEIGHT = 4,

	/**
	*    The horizontal position of the rectangle in the destination
	*    buffer. The offset is the distance, in pixels, from the left edge of the
	*    destination buffer. If this attribute is not specified, then a default
	*    of @c 0 will be used.
	*/
	SCREEN_BLIT_DESTINATION_X = 5,

	/**
	*    The vertical position of the rectangle in the destination
	*    buffer. The offset is the distance, in pixels, from the top edge of the
	*    destination buffer.  If this attribute is not specified, then a default
	*    of @c 0 will be used.
	*/
	SCREEN_BLIT_DESTINATION_Y = 6,

	/**
	*    The width, in pixels, of the rectangle in the destination buffer.
	*    The width does not have to match the source
	*    width. If the destination width is larger, the source rectangle will be
	*    stretched. If the destination width is smaller than the source width,
	*    the source rectangle will be compressed. If this attribute is not
	*    specified, then the destination buffer width will be used.
	*/
	SCREEN_BLIT_DESTINATION_WIDTH = 7,

	/**
	*    The height, in pixels, of the rectangle in the destination buffer.
	*    The height does not have to match the source
	*    height. If the destination height is larger, the source rectangle will
	*    be stretched. If the destination height is smaller than the source
	*    height, the source rectangle will be compressed. If this attribute
	*    is not specified, then the destination buffer height will be used.
	*/
	SCREEN_BLIT_DESTINATION_HEIGHT = 8,

	/**
	*    A global transparency value that is used to blend the source
	*    onto the destination. If this attribute is not specified, then a default
	*    of @c 255 will be used; this default indicates that no global
	*    transparency will be applied to the source.
	*/
	SCREEN_BLIT_GLOBAL_ALPHA = 9,

	/**
	*    A transparency operation. The transparency setting defines how
	*    the alpha channel, if present, is used to combine the source and
	*    destination pixels. The transparency values must be of type
	*    <a href="screen_8h_1Screen_Transparency_Types.xml">Screen transparency types</a>.
	*    If this attribute is not specified, then a default of
	*    @c #SCREEN_TRANSPARENCY_NONE will be used.
	*/
	SCREEN_BLIT_TRANSPARENCY = 10,

	/**
	*    A scale quality value. The scale quality setting defines the
	*    type and amount of filtering applied when scaling is required. If the
	*    source and destination rectangles are identical in size, the scale
	*    quality setting is not used. The scale quality value must be of type
	*    <a href="screen_8h_1Screen_Scale_Quality_Types.xml">Screen scale quality types</a>.
	*    If this attribute is not specified, then a default of
	*    @c #SCREEN_QUALITY_NORMAL will be used.
	*/
	SCREEN_BLIT_SCALE_QUALITY = 11,

	/**
	*    The color used by the blit operation. The color format is red
	*    bits 16 to 23, green in bits 8 to 15 and blue in bits 0 to 7.
	*    If this attribute is not specified, then a default of @c \#ffffff (white)
	*    will be used.
	*/
	SCREEN_BLIT_COLOR = 12,
};
/** @} */


/**   @brief Types of flushing options
 *    @anonenum Screen_Flushing_Types Screen flushing types
 */
enum {
	/**
	*    Indicates that the function will block until the operation
	*    has completed.
	*/
	SCREEN_WAIT_IDLE                       = (1 << 0),
	SCREEN_PROTECTED                       = (1 << 1),
	SCREEN_DONT_FLUSH                      = (1 << 2), /* internal use only */
	SCREEN_POST_RESUME                     = (1 << 3), /* internal use only */
	SCREEN_POST_RESIZE                     = (1 << 4), /* internal use only */
};

/** @brief Types of mouse buttons
 *  @anonenum Screen_Mouse_Button_Types Screen mouse button types
 */
enum {
	SCREEN_LEFT_MOUSE_BUTTON               = (1 << 0),
	SCREEN_MIDDLE_MOUSE_BUTTON             = (1 << 1),
	SCREEN_RIGHT_MOUSE_BUTTON              = (1 << 2),
};

/** @brief Types of stylus buttons
 *  @anonenum Screen_Stylus_Button_Types Screen stylus button types
 */
enum {
	SCREEN_LOWER_STYLUS_BUTTON             = (1 << 0),
	SCREEN_UPPER_STYLUS_BUTTON             = (1 << 1),
};

/**  @brief Types of touch
 *   @anonenum Screen_Touch_Types Screen touch types
 */
enum {
	SCREEN_TOUCH_FINGER                    = 0,
	SCREEN_TOUCH_STYLUS                    = 1,
};

/**  @brief Types of gestures
 *   @anonenum Screen_Gesture_Types Screen gesture types
 */
enum {
	SCREEN_GESTURE_TAP                     = 0x2C,
	SCREEN_GESTURE_ZOOM_OUT                = 0x2D,
	SCREEN_GESTURE_ZOOM_IN                 = 0x2E,
	SCREEN_GESTURE_SWIPE_RIGHT             = 0x4F,
	SCREEN_GESTURE_SWIPE_LEFT              = 0x50,
	SCREEN_GESTURE_SWIPE_DOWN              = 0x51,
	SCREEN_GESTURE_SWIPE_UP                = 0x52,
	SCREEN_GESTURE_HOLD                    = 0xE1,
};

/**
*   @addtogroup screen_devices
*   @{
*/
/** @brief Types of game buttons
 *
 *  These enumerator values are used as constants to map buttons from
 *  different controllers to a common game control layout. Typically, you create
 *  a structure to represent your game controller and map the buttons to
 *  constants in this enumeration.
 *
 *  @anonenum Screen_Game_Button_Types Screen game button types
 */
enum {
	SCREEN_A_GAME_BUTTON                   = (1 << 0),
	SCREEN_B_GAME_BUTTON                   = (1 << 1),
	SCREEN_C_GAME_BUTTON                   = (1 << 2),
	SCREEN_X_GAME_BUTTON                   = (1 << 3),
	SCREEN_Y_GAME_BUTTON                   = (1 << 4),
	SCREEN_Z_GAME_BUTTON                   = (1 << 5),
	SCREEN_MENU1_GAME_BUTTON               = (1 << 6),
	SCREEN_MENU2_GAME_BUTTON               = (1 << 7),
	SCREEN_MENU3_GAME_BUTTON               = (1 << 8),
	SCREEN_MENU4_GAME_BUTTON               = (1 << 9),
	SCREEN_L1_GAME_BUTTON                  = (1 << 10),
	SCREEN_L2_GAME_BUTTON                  = (1 << 11),
	SCREEN_L3_GAME_BUTTON                  = (1 << 12),
	SCREEN_R1_GAME_BUTTON                  = (1 << 13),
	SCREEN_R2_GAME_BUTTON                  = (1 << 14),
	SCREEN_R3_GAME_BUTTON                  = (1 << 15),
	SCREEN_DPAD_UP_GAME_BUTTON             = (1 << 16),
	SCREEN_DPAD_DOWN_GAME_BUTTON           = (1 << 17),
	SCREEN_DPAD_LEFT_GAME_BUTTON           = (1 << 18),
	SCREEN_DPAD_RIGHT_GAME_BUTTON          = (1 << 19),
};
/** @} */   /* end of addtogroup screen_devices */

/**
*   @addtogroup screen_events
*   @{
*/
/**  @brief Types of input control events
 *   @anonenum Screen_Input_Control_Events Screen input control events
 */
enum {
	/**
	 *   A touch event that started outside the window was re-focused
	 *   to this window.
	 */
	SCREEN_INPUT_CONTROL_MTOUCH_START = 0,

	/**
	 *   A touch event that started inside the window will not end
	 *   because it was re-focused to another window.
	 */
	SCREEN_INPUT_CONTROL_MTOUCH_STOP = 1,

	/**
	 *   A pointer event that started outside the window was
	 *   re-focused to this window. This is not sent unless one of
	 *   the mouse buttons was pressed when the sequence switched
	 *   focus to another window.
	 */
	SCREEN_INPUT_CONTROL_POINTER_START = 2,

	/**
	 *   A pointer event that started inside the window will not end
	 *   in this window because it was re-focused to another window.
	 */
	SCREEN_INPUT_CONTROL_POINTER_STOP = 3,
};
/** @} */   /* end of addtogroup screen_events */

/**
*   @addtogroup screen_contexts
*   @{
*/
/** @brief Types of notifications
 *  @anonenum Screen_Notification_Flag_Types Screen notification types
 */
enum {
	/** Notification of a vsync */
	SCREEN_NOTIFY_VSYNC                    = 0,
	/** Notification of an update */
	SCREEN_NOTIFY_UPDATE                   = 1,
	/** Notification of an event from an input device */
	SCREEN_NOTIFY_INPUT                    = 2,
	/** Notification of an event */
	SCREEN_NOTIFY_EVENT                    = 3,
};
/** @} */   /* end of addtogroup screen_contexts */

/**
*   @addtogroup screen_debugging
*   @{
*/
/** @brief Types of debug graphs
*
*   All masks except @c #SCREEN_DEBUG_STATISTICS are intended to be
*   combined in a single integer bitmask. The bitmask represents combinations
*   of desired debug graphs to be displayed. Only one window can enable debug
*   graphs at a time; the  last window to have enabled debug will have its
*   values displayed in the graph. All data but the FPS is normalized to buffer
*   size and refresh rate of display.
*   @anonenum Screen_Debug_Graph_Types Screen debug graph types
*/
enum {
	/** Frames per second; the number of posts over time */
	SCREEN_DEBUG_GRAPH_FPS = (1 << 0),

	/** Pixel count of pixels in dirty rectangles over time */
	SCREEN_DEBUG_GRAPH_POSTS = (1 << 1),

	/** Pixel count of pixels that were in blit requests over time */
	SCREEN_DEBUG_GRAPH_BLITS = (1 << 2),

	/** Pixel count of pixels used by composition manager in the window
	 *  to update the framebuffer over time */
	SCREEN_DEBUG_GRAPH_UPDATES = (1 << 3),

	/** The time spent on the CPU drawing each frame */
	SCREEN_DEBUG_GRAPH_CPU_TIME = (1 << 4),

	/** The time spent on the GPU drawing each frame */
	SCREEN_DEBUG_GRAPH_GPU_TIME = (1 << 5),

	/** Certain staticstics of a window. The statistics are updated once per
	 *  second and therefore represent a one second average. The statistics
	 *  that are displayed are:
	 *  - cpu usage, cpu time, gpu time
	 *  - private mappings, free memory
	 *  - window fps, display fps
	 *  - events
	 *  - objects
	 *  - draws
	 *  - triangles
	 *  - vertices
	 */
	SCREEN_DEBUG_STATISTICS = (1 << 7),
};
/** @} */   /* end of addtogroup screen_debugging */

/**
*   @addtogroup screen_devices
*   @{
*/
/** @brief Types of metric counts for devices
*
*   The metrics are on a per device basis and the counts are reset after being
*   queried. That is, the counts are reset to @c 0 after you call
*   @c screen_get_device_property_llv() to retrieve @c #SCREEN_PROPERTY_METRICS.
*   @anonenum Screen_Device_Metric_Count_Types Screen device metric count types
*/
enum {
	/** The number of input events generated by the device since the last time
	*    Screen device metric count types were queried.
	*/
	SCREEN_DEVICE_METRIC_EVENT_COUNT = 0,

	/** The number of times that the device has been powered on since the last
	*    time Screen device metrics were queried.
	*/
	SCREEN_DEVICE_METRIC_POWER_ON_COUNT = 1,

	/** The number of times the devices has gone idle since the last time
	 *   Screen device metrics were queried.
	 */
	SCREEN_DEVICE_METRIC_IDLE_COUNT = 2,
};
/** @} */   /* end of addtogroup screen_devices */

/**
*   @addtogroup screen_displays
*   @{
*/
/** @brief Types of metric counts for displays
*
*   The metrics are on a per display basis and the counts are reset after being
*   queried. That is, the counts are reset to @c 0 after you call
*   @c screen get_display_property_llv() to retrieve @c #SCREEN_PROPERTY_METRICS.
*   @anonenum Screen_Display_Metric_Count_Types Screen display metric count types
*/
enum {
	/** The number of times the display has been attached (connected) since
	*   the last time Screen display metrics were queried.
	*/
	SCREEN_DISPLAY_METRIC_ATTACH_COUNT = 0,

	/** The number of times the display has been powered on since
	*   the last time Screen display metrics were queried.
	*/
	SCREEN_DISPLAY_METRIC_POWER_ON_COUNT = 1,

	/** The number of times the display has been in idle state since
	*   the last time Screen display metrics were queried.
	*/
	SCREEN_DISPLAY_METRIC_IDLE_COUNT = 2,

	/** The number of input events that has been focused (or sent) to the
	*    display since the last time Screen display metrics were queried.
	*/
	SCREEN_DISPLAY_METRIC_EVENT_COUNT = 3,

	/** The number of times that the framebuffer of the display has been
	*    updated since the last time Screen display metrics were queried.
	*/
	SCREEN_DISPLAY_METRIC_UPDATE_COUNT = 4,

	/** The number of pixels that the framebuffer of the display has
	*    updated since the last time Screen display metrics were queried.
	*/
	SCREEN_DISPLAY_METRIC_UPDATE_PIXELS = 5,

	/** The number of bytes that has been read from the framebuffer
	*   of the display since the last time Screen display metrics have been
	*   queried. The number of bytes read is an estimation calculated based on
	*   the number of pixels updated by the framebuffer.
	*/
	SCREEN_DISPLAY_METRIC_UPDATE_READS = 6,

	/** The number of bytes that has been written to the framebuffer
	*   of the display since the last time Screen display metrics have been
	*   queried. The number of bytes written is an estimation calculated
	*   based on the number of pixels updated by the framebuffer.
	*/
	SCREEN_DISPLAY_METRIC_UPDATE_WRITES = 7,
};
/** @} */   /* end of addtogroup screen_displays */

/**
*   @addtogroup screen_pixmaps
*   @{
*/
/** @brief Types of metric counts for pixmaps
*
*   The metrics are on a per pixmap basis and the counts are reset after being
*   queried. That is, the counts are reset to @c 0 after you call
*   @c screen_get_pixmap_property_llv() to retrieve @c #SCREEN_PROPERTY_METRICS.
*   @anonenum Screen_Pixmap_Metric_Count_Types Screen pixmap metric count types
*/
enum {
	/** The number of blit requests (when the pixmap was a target of a blit)
	*   since the last time Screen pixmap metrics were queried.
	*/
	SCREEN_PIXMAP_METRIC_BLIT_COUNT = 0,

	/** The number of pixels affected by the blit requests (when the pixmap
	*   was a target of a blit) since the last time Screen pixmap metrics have
	*   been queried.
	*/
	SCREEN_PIXMAP_METRIC_BLIT_PIXELS = 1,

	/** An estimate of the number of bytes that has been read from the pixmap
	*   since the last time Screen pixmap metrics were queried.
	*   The number of bytes read is an estimation calculated based on
	*   the number of pixels affected by the blit requests.
	*/
	SCREEN_PIXMAP_METRIC_BLIT_READS = 2,

	/** An estimate of the number of bytes that has been written to the pixmap
	*   since the last time Screen pixmap metrics were queried.
	*   The number of bytes written is an estimation calculated based on
	*   the number of pixels affected by the blit requests.
	*/
	SCREEN_PIXMAP_METRIC_BLIT_WRITES = 3,
};
/** @} */   /* end of addtogroup screen_pixmaps */

/**
*   @addtogroup screen_sessions
*   @{
*/
/** @brief Types of metric counts for sessions
*
*   The metrics are on a per session basis and the counts are reset after being
*   queried. That is, the counts are reset to @c 0 after you call
*   @c screen_get_session_property_llv() to retrieve @c #SCREEN_PROPERTY_METRICS.
*   @anonenum Screen_Session_Metric_Count_Types Screen session metric count types
*/
enum {
	/** The number of input events received by the session since the last time
	*    Screen session metric count types were queried.
	*/
	SCREEN_SESSION_METRIC_EVENT_COUNT = 0,
};

/** @brief Types of modes for sessions
*
*   For future use.
*   @anonenum Screen_Session_Mode_Types Screen session mode types
*/
enum {
	SCREEN_SESSION_MODE_TEXT_ENTRY = 1,

	SCREEN_SESSION_MODE_NAVIGATION = 2,

	SCREEN_SESSION_MODE_SELECTION = 3,
};

/** @brief Types of input modes for devices and sessions.
*/
enum {
	SCREEN_INPUT_MODE_TEXT_ENTRY = 1,

	SCREEN_INPUT_MODE_NAVIGATION = 2,

	SCREEN_INPUT_MODE_SELECTION = 3,

	SCREEN_INPUT_MODE_RAW = 4,

	SCREEN_INPUT_MODE_POINTER = 5,

	SCREEN_INPUT_MODE_BEZEL = 6,
};
/** @} */   /* end of addtogroup screen_sessions */

/**
*   @addtogroup screen_windows
*   @{
*/
/** @brief Types of metric counts for windows
*
*   The metrics are on a per-window basis, and the counts are reset after being
*   queried. That is, the counts are reset to @c 0 after you call
*   @c screen_get_window_property_llv() to retrieve @c #SCREEN_PROPERTY_METRICS.
*   @anonenum Screen_Window_Metric_Count_Types Screen window metric count types
*/
enum {
	/** A general purpose counter whose meaning is defined by Cascades,
	*   Screen and other SDKs (e.g., WebKit, Adobe AIR, ...).
	*/
	SCREEN_WINDOW_METRIC_OBJECT_COUNT = 0,

	/** The number of OpenGL ES 1.X, OpenGL ES 2.X, and OpenVG API calls that
	*   were made by the process owning the window since the last time Screen
	*   window metrics were queried. Note that if multiple processes, other
	*   than the one that owns the window, made OpenGL ES 1.X,
	*   OpenGL ES 2.X, OpenVG API calls to the window, these API calls would
	*   not be counted.
	*/
	SCREEN_WINDOW_METRIC_API_COUNT = 1,

	/** The number of draw API calls (e.g., @c glDrawArrays(),
	*   @c glDrawElements(), ...) that were made by in the window since the last
	*   time Screen window metrics were queried. This metric is not counted for
	*   OpenVG API calls.
	*/
	SCREEN_WINDOW_METRIC_DRAW_COUNT = 2,

	/** An estimate of the number of triangles drawn in the window since the last
	*   time Screen window metrics were queried. This count
	*   is an estimate because two triangles are counted per line and two
	*   triangles are also counted per point. This metric is not counted for OpenVG
	*   API calls.
	*/
	SCREEN_WINDOW_METRIC_TRIANGLE_COUNT = 3,

	/** An estimate of the number of vertices passed to OpenGL in the window since
	*   the last time Screen window metrics were queried.
	*   This metric is not counted for OpenVG API calls.
	*/
	SCREEN_WINDOW_METRIC_VERTEX_COUNT = 4,

	/** An estimate of the number of bytes requested to upload the texture in
	*   the window since the last time Screen window metrics were
	*   queried. This metric is not counted for OpenVG API calls.
	*/
	SCREEN_WINDOW_METRIC_IMAGE_DATA_BYTES = 5,

	/** An estimate of the number of bytes uploaded to vertex buffers in
	*   the window (e.g., from calls such as @c glBufferData(),
	*   @c glBufferSubData(), ...) since the last time Screen window metrics
	*   were queried. This metric is not counted for OpenVG API calls.
	*/
	SCREEN_WINDOW_METRIC_BUFFER_DATA_BYTES = 6,

	/** The number of events that are sent directly to the window since the last time
	*   Screen window metrics were queried. This metric doesn't include
	*   events for any children windows that the window may have.
	*/
	SCREEN_WINDOW_METRIC_EVENT_COUNT = 7,

	/** The number of blit requests (when the window was a target of a blit)
	*   since the last time Screen window metrics were queried.
	*/
	SCREEN_WINDOW_METRIC_BLIT_COUNT = 8,

	/** The number of pixels affected by the blit requests (when the window
	*   was a target of a blit) since the last time Screen window metrics have
	*   been queried.
	*/
	SCREEN_WINDOW_METRIC_BLIT_PIXELS = 9,

	/** An estimate of the number of bytes that have been read from the window
	*   since the last time Screen window metrics were queried.
	*   The number of bytes read is an estimation calculated based on
	*   the number of pixels affected by the blit requests.
	*/
	SCREEN_WINDOW_METRIC_BLIT_READS = 10,

	/** An estimate of the number of bytes that have been written to the window
	*   since the last time Screen window metrics were queried.
	*   The number of bytes written is an estimate based on
	*   the number of pixels affected by the blit requests.
	*/
	SCREEN_WINDOW_METRIC_BLIT_WRITES = 11,

	/** The number times that the window has posted since the last time
	*   Screen window metrics were queried.
	*/
	SCREEN_WINDOW_METRIC_POST_COUNT = 12,

	/** The number of pixels that were marked as dirty in all of the window's posts
	*   since the last time Screen window metrics were queried.
	*/
	SCREEN_WINDOW_METRIC_POST_PIXELS = 13,

	/** The number of times that the window was in an update since the last
	*   time Screen window metrics were queried. The window
	*   must be visible (its @c #SCREEN_PROPERTY_VISIBLE is set) in order
	*   for this count to be incremented. If the window is static (i.e., the window
	*   property @c #SCREEN_PROPERTY_STATIC is set), this count can still
	*   increment if there is another window or layer on top so that there is
	*   blending required for this window.
	*/
	SCREEN_WINDOW_METRIC_UPDATE_COUNT = 14,

	/** The number of pixels that has been used in the updates of the window
	*   since the last time Screen window metrics were queried.
	*/
	SCREEN_WINDOW_METRIC_UPDATE_PIXELS = 15,

	/** An estimate of the number of bytes that have been read from the
	*   window buffer (if there are multiple buffers, it's the front buffer)
	*   since the last time Screen window metrics were queried.
	*   The number of bytes read is an estimate based on
	*   the number of pixels affected by the update.
	*/
	SCREEN_WINDOW_METRIC_UPDATE_READS = 16,

	/** An estimate of the number of bytes that has been written to the
	*   window framebuffer since the last time Screen window metrics have
	*   been queried. The number of bytes written is an estimate
	*   based on the number of pixels affected by the update.
	*/
	SCREEN_WINDOW_METRIC_UPDATE_WRITES = 17,

	/** An estimate of the total CPU time spent preparing updates. The
	*   quantity is estimated by measuring the time between the window
	*   timestamp property and the time when @c screen_post_window() is called.
	*   The @c #SCREEN_PROPERTY_TIMESTAMP must be set on the window for this
	*   metric to be reliable.
	*/
	SCREEN_WINDOW_METRIC_CPU_TIME = 18,

	/** An estimate of the total GPU time spent rendering to back buffers. The
	*   quantity is estimated by measuring the time between when
	*   @c eglSwapBuffers() is called and when the post is actually flushed out
	*   to the server. This metric is only reliable if the GPU does most of its
	*   rendering after @c eglSwapBuffers() is called.
	*/
	SCREEN_WINDOW_METRIC_GPU_TIME = 19,

	/**  An estimate of the total number of nanoseconds for which the window
	 *  was visible. The quantity is estimated by measuring the time spent
	 *  between scene rebuilds where the window is at least partially visible.
	 *  If the window is covered by another window with transparency, the
	 *  counter will be incremented.
	 */
	SCREEN_WINDOW_METRIC_VISIBLE_TIME = 20,

	/**  An estimate of the total number of nanoseconds for which the window
	 *  was fully visible. The quantity is estimated by measuring the time spent
	 *  between scene rebuilds where the window is completely visible. If the
	 *  window is covered by another window with transparency, the counter will
	 *  not be incremented even though the window may actually be visible.
	 */
	SCREEN_WINDOW_METRIC_FULLY_VISIBLE_TIME = 21,
};
/** @} */   /* end of addtogroup screen_windows */

/**
*   @addtogroup screen_debugging
*   @{
*/
/** @brief Types of packets
*
*   Screen packet types are for debugging purposes only. It identifies
*   binary chunks that are used only by the screeninfo utility (a command-
*   line tool in /dev/screen/ that is only visible if you have root access)
*   that is used to decode these packets.
*   @anonenum Screen_Packet_Types Screen packet types
*/
enum {
	/** A binary chunk from the request ring buffer.(/dev/screen/request/) */
	SCREEN_REQUEST_PACKET = 0,

	/** A binary chunk from the blit ring buffer or log.(/dev/screen/0/blit#/) */
	SCREEN_BLIT_PACKET = 1,

	/** A binary chunk from the input ring buffer or log.(/dev/screen/input/) */
	SCREEN_INPUT_PACKET = 2,

	/** A binary chunk from the event queue.(/dev/screen/pid/) */
	SCREEN_EVENT_PACKET = 3,
};
/** @} */   /* end of ingroup screen_debugging */

/** @brief The types of cursor shapes
*
*   @anonenum Screen_Cursor_Shapes Screen cursor shapes
*/
enum {
	SCREEN_CURSOR_SHAPE_CUSTOM   = -1,
	SCREEN_CURSOR_SHAPE_ARROW    = 0,
	SCREEN_CURSOR_SHAPE_KEYBOARD = 1,
	SCREEN_CURSOR_SHAPE_HOME     = 2,
	SCREEN_CURSOR_SHAPE_MENU     = 3,
	SCREEN_CURSOR_SHAPE_NONE     = 4,
	SCREEN_CURSOR_SHAPE_HAND     = 5,
	SCREEN_CURSOR_SHAPE_IBEAM    = 6,
	SCREEN_CURSOR_SHAPE_WAIT     = 7,
	SCREEN_CURSOR_SHAPE_ZOOM_IN  = 8,
	SCREEN_CURSOR_SHAPE_ZOOM_OUT = 9,
	SCREEN_CURSOR_SHAPE_GRAB     = 10,
	SCREEN_CURSOR_SHAPE_GRABBING = 11,
	SCREEN_CURSOR_SHAPE_CROSS    = 12,
	SCREEN_CURSOR_SHAPE_MOVE     = 13,
};

/**
*   @ingroup screen_blits
*   @{
*/
/**
*   @brief Copy pixel data from one buffer to another
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function requests pixels from one buffer be copied to another. The
*   operation is guaranteed not to be submitted until a flush is called, or
*   until the application posts changes to one of the context's windows.
*
*   The @c attribs argument is allowed to be @c NULL or empty (i.e. contains a
*   single element that is set to @c #SCREEN_BLIT_END). If @c attribs is empty,
*   then the following defaults will be applied:
*   - the source rectangle's vertical and horizontal positions are 0
*   - the destination rectangle's vertical and horizontal positions are 0
*   - the source rectangle includes the entire source buffer
*   - the destination buffer includes the entire destination buffer
*   - the transparency is @c #SCREEN_TRANSPARENCY_NONE
*   - the global alpha value is @c 255 (or opaque)
*   - the scale quality is @c #SCREEN_QUALITY_NORMAL.
*
*   To change any of this default behavior, set @c attribs with pairings of the
*   following valid tokens and their desired values:
*   - @c #SCREEN_BLIT_SOURCE_X
*   - @c #SCREEN_BLIT_SOURCE_Y
*   - @c #SCREEN_BLIT_SOURCE_WIDTH
*   - @c #SCREEN_BLIT_SOURCE_HEIGHT
*   - @c #SCREEN_BLIT_DESTINATION_X
*   - @c #SCREEN_BLIT_DESTINATION_Y
*   - @c #SCREEN_BLIT_DESTINATION_WIDTH
*   - @c #SCREEN_BLIT_DESTINATION_HEIGHT
*   - @c #SCREEN_BLIT_SCALE_QUALITY
*   - @c #SCREEN_BLIT_GLOBAL_ALPHA
*   - @c #SCREEN_BLIT_TRANSPARENCY (valid transparency values are:
*                                   @c #SCREEN_TRANSPARENCY_NONE,
*                                   @c #SCREEN_TRANSPARENCY_TEST, and
*                                   @c #SCREEN_TRANSPARENCY_SOURCE_OVER)
*
*   @param  ctx A connection to Screen
*   @param  dst The buffer which data will be copied to.
*   @param  src The buffer which the pixels will be copied from.
*   @param  attribs A list that contains the attributes that define the
*           blit. This list must consist of a series of token-value pairs
*           terminated with a @c #SCREEN_BLIT_END token. The tokens used in this
*           list must be of type
*           <a href="group__screen__blits_1Screen_Blit_Types.xml">Screen blit types</a>.
*   @return @c 0 if the blit operation was queued, or @c -1 if an error occurred
*           (@c errno is set).
*/
int screen_blit(screen_context_t ctx, screen_buffer_t dst, screen_buffer_t src, const int *attribs);

/**
*   @brief Fill an area of a specified buffer
*
*   <b>Function Type:</b> <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function requests that a rectangular area of the destination buffer be
*   filled with a solid color.
*
*   The @c attribs argument is allowed to be @c NULL or empty (i.e. contains a
*   single element that is set to @c #SCREEN_BLIT_END). If @c attribs is empty,
*   then the following defaults will be applied:
*   - the destination rectangle's vertical and horizontal positions are 0
*   - the destination buffer includes the entire destination buffer
*   - the global alpha value is @c 255 (or opaque)
*   - the color is \#ffffff (white)
*
*   To change any of this default behavior, set @c attribs with pairings of the
*   following valid tokens and their desired values:
*   - @c #SCREEN_BLIT_DESTINATION_X
*   - @c #SCREEN_BLIT_DESTINATION_Y
*   - @c #SCREEN_BLIT_DESTINATION_WIDTH
*   - @c #SCREEN_BLIT_DESTINATION_HEIGHT
*   - @c #SCREEN_BLIT_GLOBAL_ALPHA
*   - @c #SCREEN_BLIT_COLOR
*
*   @param  ctx A connection to Screen
*   @param  dst The buffer which data will be copied to.
*   @param  attribs A list that contains the attributes that define the
*           blit. This list must consist of a series of token-value pairs
*           terminated with a @c #SCREEN_BLIT_END token. The tokens used in this
*           list must be of type
*           <a href="group__screen__blits_1Screen_Blit_Types.xml">Screen blit types</a>.
*
*   @return @c 0 if the blit operation was queued, or @c -1 if an error occurred
*           (@c errno is set).
*/
int screen_fill(screen_context_t ctx, screen_buffer_t dst, const int *attribs);

/**
*   @brief Flush all the blits issued since the last call to this function, or
*          to @c screen_post_window()
*
*   <b>Function Type:</b> <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function flushes all delayed blits and fills since the last call to this
*   function, or since the last call to @c screen_post_window(). Note that this is a
*   flush of delayed blits and does not imply a flush of the command buffer.
*   The blits will start executing shortly after you call the function. The blits
*   may not be complete when the function returns, unless the @c #SCREEN_WAIT_IDLE
*   flag is set. This function has no effect on other non-blit delayed calls. The
*   @c screen_post_window() function performs an implicit flush of any pending blits.
*   The content that is to be presented via the call to @c screen_post_window()
*   is most likely the result of any pending blit operations completing.
*
*   The connection to Screen must have been acquired with the function
*   @c screen_create_context().
*
*   @param  ctx A connection to Screen
*   @param  flags A flag used by the mutex. Specify @c #SCREEN_WAIT_IDLE if the
*   function is required to block until all the blits have been completed.
*
*   @return @c 0 if the blit buffer was flushed, or @c -1 if an error occurred
*           (@c errno is set).
*/
int screen_flush_blits(screen_context_t ctx, int flags);
/** @} */   /* end of ingroup screen_blits */

/**
*   @ingroup screen_buffers
*   @{
*/

/**
*   @brief Create a buffer handle that can later be attached to a window or a
*          pixmap
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   This function creates a buffer object, which describes memory where pixels
*   can be drawn to or read from. Applications must use
*   @c screen_destroy_buffer() when a buffer is no longer used.
*
*   @param  pbuf An address where the function can store a handle for the native
*           buffer.
*
*   @return @c 0 if the buffer was created, or @c -1 if an error occurred
*           (@c errno is set).
*/
int screen_create_buffer(screen_buffer_t *pbuf);

/**
*   @brief Destroy a buffer and frees associated resources
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   This function destroys the buffer object associated with the buffer handle.
*   Any resources created for this buffer will also be released. The buffer
*   handle can no longer be used as argument in subsequent screen calls. The
*   actual memory buffer described by this buffer handle is not released by this
*   operation. The application is responsible for freeing its own external
*   buffers. Only buffers created with @c screen_create_buffer() must be
*   destroyed with this function.
*
*   @param  buf The handle of the buffer you want to destroy. This buffer must
*           have been created with @c screen_create_buffer().
*
*   @return @c 0 if the buffer was destroyed, or @c -1 if an error occurred
*           (@c errno is set).
*           otherwise @c -1 and @c errno is set
*/
int screen_destroy_buffer(screen_buffer_t buf);

/**
*   @brief Retrieve the current value of the specified buffer property of type
*          char
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   This function stores the current value of a buffer property in a
*   user-provided buffer. No more than @c len bytes of the specified type will be
*   written.
*
*   Currently there are no buffer properties that can be retrieved using this
*   function.
*
*   @param  buf The handle of the buffer whose property is being queried.
*   @param  pname The name of the property whose value is being queried. The
*           properties available for query are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  len The maximum number of bytes that can be written to @c param.
*   @param  param The buffer where the retrieved value(s) will be stored. This
*           buffer must be an array of type @c char with a maximum length of
*           @c len.
*
*   @return @c 0 if a query was successful and the value(s) of the property are
*           stored in @c param, or @c -1 if an error occurred (@c errno is set).
*/
int screen_get_buffer_property_cv(screen_buffer_t buf, int pname, int len, char *param);

/**
*   @brief Retrieve the current value of the specified buffer property of type
*          integer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   This function stores the current value of a buffer property in a
*   user-provided buffer.
*
*   The values of the following properties can be retrieved using this function:
*   - @c #SCREEN_PROPERTY_BUFFER_SIZE
*   - @c #SCREEN_PROPERTY_FORMAT
*   - @c #SCREEN_PROPERTY_INTERLACED
*   - @c #SCREEN_PROPERTY_PHYSICALLY_CONTIGUOUS
*   - @c #SCREEN_PROPERTY_PLANAR_OFFSETS
*   - @c #SCREEN_PROPERTY_PROTECTED
*   - @c #SCREEN_PROPERTY_STRIDE
*
*   @param  buf The handle of the buffer whose property is being queried.
*   @param  pname The name of the property whose value is being queried. The
*           properties available for query are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param The buffer where the retrieved value(s) will be stored. This
*           buffer must be of type @c int. @c param may be a single integer or
*           an array of integers depending on the property being set.
*
*   @return @c 0 if a query was successful and the value(s) of the property are
*           stored in @c param, or @c -1 if an error occurred (@c errno is set).
*/
int screen_get_buffer_property_iv(screen_buffer_t buf, int pname, int *param);

/**
*   @brief Retrieve the current value of the specified buffer property of type
*          long long integer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   This function stores the current value of a buffer property in a
*   user-provided buffer.
*
*   The values of the following properties can be retrieved using this function:
*   - @c #SCREEN_PROPERTY_PHYSICAL_ADDRESS
*
*   @param  buf The handle of the buffer whose property is being queried.
*   @param  pname The name of the property whose value is being queried. The
*           properties available for query are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param The buffer where the retrieved value(s) will be stored. This
*           buffer must be of type @c long @c long.
*
*   @return @c 0 if a query was successful and the value(s) of the property are
*           stored in @c param, or @c -1 if an error occurred (@c errno is set).
*/
int screen_get_buffer_property_llv(screen_buffer_t buf, int pname, long long *param);

/**
*   @brief Retrieve the current value of the specified buffer property of type
*          @c void*
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   This function stores the current value of a buffer property in a
*   user-provided buffer.
*
*   The values of the following properties can be retrieved using this function:
*   - @c #SCREEN_PROPERTY_EGL_HANDLE
*   - @c #SCREEN_PROPERTY_POINTER
*   - @c #SCREEN_PROPERTY_NATIVE_IMAGE
*
*   @param  buf The handle of the buffer whose property is being queried.
*   @param  pname The name of the property whose value is being queried. The
*           properties available for query are of type
*            <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param The buffer where the retrieved value(s) will be stored. This
*           buffer must be of type @c void*.
*
*   @return @c 0 if a query was successful and the value(s) of the property are
*           stored in @c param, or @c -1 if an error occurred (@c errno is set).
*/
int screen_get_buffer_property_pv(screen_buffer_t buf, int pname, void **param);

/**
*   @brief Set the value of the specified buffer property of type char
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   This function sets the value of a buffer property from a user-provided
*   buffer. The buffer must have been created with the function
*   @c screen_create_buffer().
*
*   Currently there are no buffer properties that can be set using this
*   function.
*
*   @param  buf The handle of the buffer whose property is to be set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type
*            <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  len The maximum number of bytes that can be read from @c param.
*   @param  param A pointer to a buffer containing the new value(s).  This
*           buffer must be an array of type @c char with a maximum length of
*           @c len.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_buffer_property_cv(screen_buffer_t buf, int pname, int len, const char *param);

/**
*   @brief Set the value of the specified buffer property of type integer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   This function sets the value of a buffer property from a user-provided
*   buffer. The buffer must have been created with the function
*   @c screen_create_buffer().
*
*   You can use this function to set the value of the following properties:
*   - @c #SCREEN_PROPERTY_BUFFER_SIZE
*   - @c #SCREEN_PROPERTY_FORMAT
*   - @c #SCREEN_PROPERTY_INTERLACED
*   - @c #SCREEN_PROPERTY_PHYSICALLY_CONTIGUOUS
*   - @c #SCREEN_PROPERTY_PLANAR_OFFSETS
*   - @c #SCREEN_PROPERTY_PROTECTED
*   - @c #SCREEN_PROPERTY_STRIDE
*
*   @param  buf The handle of the buffer whose property is to be set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type
*            <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param A pointer to a buffer containing the new value(s).  This
*           buffer must be of type @c int. @c param may be a single integer or
*           an array of integers depending on the property being set.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_buffer_property_iv(screen_buffer_t buf, int pname, const int *param);

/**
*   @brief Set the value of the specified buffer property of type long long
*          integer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   This function sets the value of a buffer property from a user-provided
*   buffer. The buffer must have been created with the function
*   @c screen_create_buffer().
*
*   You can use this function to set the value of the following properties:
*   - @c #SCREEN_PROPERTY_PHYSICAL_ADDRESS
*
*   @param  buf The handle of the buffer whose property is to be set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type
*            <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param A pointer to a buffer containing the new value(s).  This
*           buffer must be of type @c long @c long.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_buffer_property_llv(screen_buffer_t buf, int pname, const long long *param);

/**
*   @brief Set the value of the specified buffer property of type void*
*
*   <b>Function Type:</b> <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   This function sets the value of a buffer property from a user-provided
*   buffer. The buffer must have been created with the function
*   @c screen_create_buffer().
*
*   You can use this function to set the value of the following properties:
*   - @c #SCREEN_PROPERTY_EGL_HANDLE
*   - @c #SCREEN_PROPERTY_POINTER
*   - @c #SCREEN_PROPERTY_NATIVE_IMAGE
*
*   @param  buf The handle of the buffer whose property is to be set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param A pointer to a buffer containing the new value(s).  This
*           buffer must be of type @c void*.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_buffer_property_pv(screen_buffer_t buf, int pname, void **param);
/** @} */   /* end of ingroup screen_buffers */

/**
*   @ingroup screen_contexts
*   @{
**/

/**
*   @brief Establish a connection with the composited windowing system
*
*   <b>Function type:</b> <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   The @c screen_create_context() function tries to establish communication
*   with the composited windowing system resource manager (Screen).
*   To do this, the function opens /dev/screen and sends the proper connect
*   sequence. If the call succeeds, memory is allocated to store context state.
*   The composition manager then creates an event queue and associates it with
*   the connecting process.
*
*   @param  pctx A pointer to a @c screen_context_t where a handle for the new
*           context can be stored.
*   @param  flags The type of context to be created. The value must
*           be of type <a href="group__screen__contexts_1Screen_Context_Types.xml">Screen context types</a>.
*
*   @return @c 0 if the context was created, or @c -1 if an error occurred
*           (@c errno is set).
*/
int screen_create_context(screen_context_t *pctx, int flags);

/**
*   @brief Terminate a connection with the composited windowing system
*
*   <b>Function type:</b> <a href="manual/rscreen_apply_execution.xml">Apply Execution</a>
*
*   This function closes an existing connection with the composited windowing
*   system resource manager; the context is freed and can no longer be used.
*   All windows and pixmaps associated with this connection will be destroyed.
*   All events waiting in the event queue will be discarded.
*   This operation does not flush the command buffer. Any pending asynchronous
*   commands are discarded.
*
*   @param  ctx The connection to Screen that is to be terminated. This context
*           must have been created with @c screen_create_context().
*
*   @return @c 0 if the context was destroyed, or @c -1 if an error occurred
*           (@c errno is set).
*/
int screen_destroy_context(screen_context_t ctx);

/**
*   @brief Flush a context, given a context and a set of flags
*
*   <b>Function type:</b> <a href="manual/rscreen_apply_execution.xml">Apply Execution</a>
*
*   This function flushes any delayed command and causes the contents of
*   displays to be updated, when applicable. If @c #SCREEN_WAIT_IDLE is specified,
*   the function will not return until the contents of all affected displays
*   have been updated. Passing no flags causes the function to return
*   immediately.
*
*   If debugging, you can call this function after all delayed function calls
*   as a way to determine the exact function call which may have caused an error.
*
*   @param  ctx The connection to Screen that is to be flushed. This context
*           must have been created with @c screen_create_context().
*   @param  flags The flag to indicate whether or not to wait until contents
*           of all displays have been updated or to execute immediately.
*
*   @return @c 0 if the context was flushed, or @c -1 if an error occurred
*           (@c errno is set). The error could have been caused by any delayed
*           function that just got flushed.
*/
int screen_flush_context(screen_context_t ctx, int flags);

/**
*   @brief Retrieve the current value of the specified context property of type
*          char
*
*   <b>Function Type:</b> <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function stores the current value of a context property in a
*   user-provided buffer. No more than @c len bytes of the specified type will be
*   written.
*
*   The values of the following properties can be retrieved using this function:
*   - @c #SCREEN_PROPERTY_KEYMAP
*
*   @param  ctx The handle of the context whose property is being queried.
*   @param  pname The name of the property whose value is being queried. The
*           properties available for query are of type
*            <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  len The maximum number of bytes that can be written to @c param.
*   @param  param The buffer where the retrieved value(s) will be stored. This
*           buffer must be an array of type @c char with a maximum length of
*           @c len.
*
*   @return @c 0 if a query was successful and the value(s) of the property are
*           stored in @c param, or @c -1 if an error occurred (@c errno is set).
*/
int screen_get_context_property_cv(screen_context_t ctx, int pname, int len, char *param);

/**
*   @brief Retrieve the current value of the specified context property of type
*          integer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function stores the current value of a context property in a
*   user-provided buffer.
*
*   The values of the following properties can be retrieved using this function:
*   - @c #SCREEN_PROPERTY_DEVICE_COUNT
*   - @c #SCREEN_PROPERTY_DISPLAY_COUNT
*   - @c #SCREEN_PROPERTY_GROUP_COUNT
*   - @c #SCREEN_PROPERTY_IDLE_STATE
*   - @c #SCREEN_PROPERTY_PIXMAP_COUNT
*   - @c #SCREEN_PROPERTY_WINDOW_COUNT
*
*   @param  ctx The handle of the context whose property is being queried.
*   @param  pname The name of the property whose value is being queried. The
*           properties available for query are of type
*            <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param The buffer where the retrieved value(s) will be stored. This
*           buffer must be of type @c int. @c param may be a single integer or
*           an array of integers depending on the property being set.
*
*   @return @c 0 if a query was successful and the value(s) of the property are
*           stored in @c param, or @c -1 if an error occurred (@c errno is set).
*/
int screen_get_context_property_iv(screen_context_t ctx, int pname, int *param);

/**
*   @brief Retrieve the current value of the specified context property of type
*          long long integer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function stores the current value of a context property in a
*   user-provided buffer.
*
*   The values of the following properties can be retrieved using this function:
*   - @c #SCREEN_PROPERTY_IDLE_TIMEOUT
*
*   @param  ctx The handle of the context whose property is being queried.
*   @param  pname The name of the property whose value is being queried. The
*           properties available for query are of type
*            <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param The buffer where the retrieved value(s) will be stored. This
*           buffer must be of type @c long @c long.
*
*   @return @c 0 if a query was successful and the value(s) of the property are
*           stored in @c param, or @c -1 if an error occurred (@c errno is set).
*/
int screen_get_context_property_llv(screen_context_t ctx, int pname, long long *param);

/**
*   @brief Retrieve the current value of the specified context property of type
*          void*
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function stores the current value of a context property in a
*   user-provided buffer.
*
*   The values of the following properties can be retrieved using this function:
*   - @c #SCREEN_PROPERTY_DEVICES
*   - @c #SCREEN_PROPERTY_DISPLAYS
*   - @c #SCREEN_PROPERTY_GROUPS
*   - @c #SCREEN_PROPERTY_FOCUS
*   - @c #SCREEN_PROPERTY_MTOUCH_FOCUS
*   - @c #SCREEN_PROPERTY_POINTER_FOCUS
*   - @c #SCREEN_PROPERTY_PIXMAPS
*   - @c #SCREEN_PROPERTY_WINDOWS
*
*   @param  ctx The handle of the context whose property is being queried.
*   @param  pname The name of the property whose value is being queried. The
*           properties available for query are of type <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param The buffer where the retrieved value(s) will be stored. This
*           buffer must be of type @c void*.
*
*   @return @c 0 if a query was successful and the value(s) of the property are
*           stored in @c param, or @c -1 if an error occurred (@c errno is set).
*/
int screen_get_context_property_pv(screen_context_t ctx, int pname, void **param);

/**
*   @brief Send asynchronous notifications to Screen
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   This function sends an asynchronous event to Screen. For security reasons,
*   the notification is sent without its associated data.
*
*   @param  ctx The handle of the context of the notification.
*   @param  flags The type of notification that you want to be notified of.
*                 Valid notification types are of type
                  <a href="group__screen__contexts_1Screen_Notification_Flag_Types.xml">Screen notification flag types</a>.
*   @param  obj The object within the specified context that the notification is
*               for. For example, this object could be a window, or a display,
*               etc.
*   @param  event The notification.
*
*   @return @c 0 if , or @c -1 if an error occurred (@c errno is set).
*/
int screen_notify(screen_context_t ctx, int flags, const void *obj, const struct sigevent *event);

/**
*   @brief Set the value of the specified context property of type char
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function sets the value of a context property from a user-provided buffer.
*   No more than @c len bytes will be read from @c param.
*
*   You can use this function to set the value of the following properties:
*   - @c #SCREEN_PROPERTY_KEYMAP
*
*   @param  ctx The handle of the context whose property is to be set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  len The maximum number of bytes that can be read from @c param.
*   @param  param A pointer to a buffer containing the new value(s).  This
*           buffer must be of an array of type @c char with a maximum length of
*           @c len.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_context_property_cv(screen_context_t ctx, int pname, int len, const char *param);

/**
*   @brief Set the value of the specified context property of type integer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function sets the value of a context property from a user-provided buffer.
*
*   Currently, there are no context properties that can be set using this
*   function.
*
*   @param  ctx The handle of the context whose property is to be set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param A pointer to a buffer containing the new value(s). This
*           buffer must be of @c type int. @c param may be a single integer or
*           an array of integers depending on the property being set.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_context_property_iv(screen_context_t ctx, int pname, const int *param);

/**
*   @brief Set the value of the specified context property of type long long
*          integer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function sets the value of a context property from a user-provided buffer.
*
*   You can use this function to set the value of the following properties:
*   - @c #SCREEN_PROPERTY_IDLE_TIMEOUT
*
*   @param  ctx The handle of the context whose property is to be set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param A pointer to a buffer containing the new value(s).  This
*           buffer must be of type @c long @c long.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_context_property_llv(screen_context_t ctx, int pname, const long long *param);

/**
*   @brief Set the value of the specified context property of type void*
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function sets the value of a context property from a user-provided buffer.
*
*   You can use this function to set the value of the following properties:
*   - @c #SCREEN_PROPERTY_FOCUS
*   - @c #SCREEN_PROPERTY_MTOUCH_FOCUS
*   - @c #SCREEN_PROPERTY_POINTER_FOCUS
*
*   @param  ctx The handle of the context whose property is to be set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param A pointer to a buffer containing the new value(s).  This
*           buffer must be of type @c void*.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_context_property_pv(screen_context_t ctx, int pname, void **param);
/** @} */   /* end of ingroup screen_contexts */

/**
*   @ingroup screen_devices
*   @{
*/

/**
*   @brief Create a device of specified type to be associated with a context
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   The @c screen_create_device_type() function creates a input device object to
*   be associated with a context. Note that you need to be within a privileged
*   context to call this function.
*   The following are valid input devices which can be created:
*   - @c #SCREEN_EVENT_KEYBOARD
*   - @c #SCREEN_EVENT_POINTER
*   - @c #SCREEN_EVENT_JOYSTICK
*   - @c #SCREEN_EVENT_GAMEPAD
*   - @c #SCREEN_EVENT_MTOUCH_TOUCH
*   Applications must use @c screen_destroy_device() when a device is no longer
*   used.
*
*
*   @param  pdev A pointer to a @c #screen_device_t where a handle for the new
*           input device can be stored.
*   @param  ctx The handle of the context in which the input device is to be
*           created. This context must have been created with the context type
*           of @c #SCREEN_INPUT_PROVIDER_CONTEXT using @c screen_create_context().
*   @param  type The type of input device to be created.
*
*   @return @c 0 if the input device was created, or @c -1 if an error occurred
*           (@c errno is set).
*/
int screen_create_device_type(screen_device_t *pdev, screen_context_t ctx, int type);

/**
*   @brief Destroy a input device and frees associated resources
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function destroys the a input device object associated with the device
*   handle. Any resources created for this input device will be released.
*   Input devices created with @c screen_create_device_type() must be destroyed
*   with this function.
*
*   This function is of type flushing execution because if there are any entries
*   in the command buffer that have reference to this device, the entries will be
*   flushed and processed before destroying the device.
*
*   @param  dev The handle of the input device that you want to destroy.
*
*   @return @c 0 if the input device was destroyed, or @c -1 if an error occurred
*           (@c errno is set).
*/
int screen_destroy_device(screen_device_t dev);

/**
*   @brief Retrieve the current value of the specified device property of type
*          char
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function stores the current value of a device property in a
*   user-provided buffer. No more than @c len bytes of the specified type will be
*   written.
*
*   The values of the following properties can be retrieved using this function:
*   - @c #SCREEN_PROPERTY_KEYMAP
*   - @c #SCREEN_PROPERTY_ID_STRING
*   - @c #SCREEN_PROPERTY_VENDOR
*   - @c #SCREEN_PROPERTY_PRODUCT
*
*   @param  dev The handle of the device whose property is being queried.
*   @param  pname The name of the property whose value is being queried. The
*           properties available for query are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  len The maximum number of bytes that can be written to @c param.
*   @param  param The buffer where the retrieved value(s) will be stored. This
*           buffer must be an array of type @c char with a maximum length of
*           @c len.
*
*   @return @c 0 if a query was successful and the value(s) of the property are
*           stored in @c param, or @c -1 if an error occurred (@c errno is set).
*/
int screen_get_device_property_cv(screen_device_t dev, int pname, int len, char *param);

/**
*   @brief Retrieve the current value of the specified device property of type
*          integer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function stores the current value of a device property in a
*   user-provided buffer.
*
*   The values of the following properties can be retrieved using this function:
*   - @c #SCREEN_PROPERTY_ANALOG0
*   - @c #SCREEN_PROPERTY_ANALOG1
*   - @c #SCREEN_PROPERTY_BUTTONS
*   - @c #SCREEN_PROPERTY_BUTTON_COUNT
*   - @c #SCREEN_PROPERTY_MAXIMUM_TOUCH_ID
*   - @c #SCREEN_PROPERTY_METRIC_COUNT
*   - @c #SCREEN_PROPERTY_MODIFIERS
*   - @c #SCREEN_PROPERTY_KEYMAP_PAGE
*   - @c #SCREEN_PROPERTY_POWER_MODE
*   - @c #SCREEN_PROPERTY_SCALE_FACTOR
*   - @c #SCREEN_PROPERTY_STICKY_MODIFIERS
*   - @c #SCREEN_PROPERTY_TRANSFORM
*   - @c #SCREEN_PROPERTY_TYPE
*
*   @param  dev The handle of the device whose property is being queried.
*   @param  pname The name of the property whose value is being queried. The
*           properties available for query are of type <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param The buffer where the retrieved value(s) will be stored. This
*           buffer must be of type @c int. @c param may be a single integer or
*           an array of integers depending on the property being set.
*
*   @return @c 0 if a query was successful and the value(s) of the property are
*           stored in @c param, or @c -1 if an error occurred (@c errno is set).
*/
int screen_get_device_property_iv(screen_device_t dev, int pname, int *param);

/**
*   @brief Retrieve the current value of the specified device property of type
*          long long integer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function stores the current value of a device property in a
*   user-provided buffer.
*   The values of the following properties can be queried using this function:
*    - @c #SCREEN_PROPERTY_METRICS
*
*   @param  dev The handle of the device whose property is being queried.
*   @param  pname The name of the property whose value is being queried. The
*           properties available for query are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param The buffer where the retrieved value(s) will be stored. This
*           buffer must be of type @c long @c long.
*
*   @return @c 0 if a query was successful and the value(s) of the property are
*           stored in @c param, or @c -1 if an error occurred (@c errno is set).
*/
int screen_get_device_property_llv(screen_device_t dev, int pname, long long *param);

/**
*   @brief Retrieve the current value of the specified device property of type
*          void*
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function stores the current value of a device property in a
*   user-provided buffer.
*
*   The values of the following properties can be retrieved using this function:
*   - @c #SCREEN_PROPERTY_CONTEXT
*   - @c #SCREEN_PROPERTY_DISPLAY
*   - @c #SCREEN_PROPERTY_USER_HANDLE
*   - @c #SCREEN_PROPERTY_WINDOW
*
*   @param  dev The handle of the device whose property is being queried.
*   @param  pname The name of the property whose value is being queried. The
*           properties available for query are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param The buffer where the retrieved value(s) will be stored. This
*           buffer must be of type @c void*.
*
*   @return @c 0 if a query was successful and the value(s) of the property are
*           stored in @c param, or @c -1 if an error occurred (@c errno is set).
*/
int screen_get_device_property_pv(screen_device_t dev, int pname, void **param);

/**
*   @brief Set the value of the specified device property of type char
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function sets the value of a device property from a user-provided buffer.
*   No more than @c len bytes will be read from @c param.
*
*   You can use this function to set the value of the following properties:
*   - @c #SCREEN_PROPERTY_ID_STRING
*   - @c #SCREEN_PROPERTY_KEYMAP
*   - @c #SCREEN_PROPERTY_PRODUCT
*   - @c #SCREEN_PROPERTY_VENDOR
*
*   @param  dev The handle of the device whose property is to be set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  len The maximum number of bytes that can be read from @c param.
*   @param  param A pointer to a buffer containing the new value(s).  This
*           buffer must be an array of type @c char with a maximum length of
*           @c len.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_device_property_cv(screen_device_t dev, int pname, int len, const char *param);

/**
*   @brief Set the value of the specified device property of type integer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function sets the value of a device property from a user-provided buffer.
*
*   You can use this function to set the value of the following properties:
*   - @c #SCREEN_PROPERTY_BUTTON_COUNT
*   - @c #SCREEN_PROPERTY_MODIFIERS
*   - @c #SCREEN_PROPERTY_KEYMAP_PAGE
*   - @c #SCREEN_PROPERTY_POWER_MODE
*   - @c #SCREEN_PROPERTY_STICKY_MODIFIERS
*   - @c #SCREEN_PROPERTY_TRANSFORM
*   - @c #SCREEN_PROPERTY_SCALE_FACTOR
*
*   @param  dev The handle of the device whose property is to be set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param A pointer to a buffer containing the new value(s).  This
*           buffer must be of type @c int. @c param may be a single integer or
*           an array of integers depending on the property being set.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_device_property_iv(screen_device_t dev, int pname, const int *param);

/**
*   @brief Set the value of the specified device property of type long long
*          integer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function sets the value of a device property from a user-provided buffer.
*
*   Currently there are no device properties that can be set using
*   this function.
*
*   @param  dev The handle of the device whose property is to be set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param A pointer to a buffer containing the new value(s).  This
*           buffer must be of type @c long @c long.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_device_property_llv(screen_device_t dev, int pname, const long long *param);

/**
*   @brief Set the value of the specified device property of type void*
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function sets the value of a device property from a user-provided buffer.
*
*   You can use this function to set the value of the following properties:
*   - @c #SCREEN_PROPERTY_DISPLAY
*   - @c #SCREEN_PROPERTY_USER_HANDLE
*   - @c #SCREEN_PROPERTY_WINDOW
*
*   @param  dev The handle of the device whose property is to be set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param A pointer to a buffer containing the new value(s).  This
*           buffer must be of type @c void*.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_device_property_pv(screen_device_t dev, int pname, void **param);
/** @} */   /* end of ingroup screen_devices */

/*
 * Displays
 */
/**
*   @ingroup screen_displays
*   @{
*/

/**
*   @brief Retrieve the current value of the specified display property of type
*          char
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function stores the current value of a display property in a
*   user-provided buffer. No more than @c len bytes of the specified type will be
*   written.
*
*   The values of the following properties can be retrieved using this function:
*   - @c #SCREEN_PROPERTY_ID_STRING
*   - @c #SCREEN_PROPERTY_VENDOR
*   - @c #SCREEN_PROPERTY_PRODUCT
*
*   @param  disp The handle of the display whose property is being queried.
*   @param  pname The name of the property whose value is being queried. The
*           properties available for query are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  len The maximum number of bytes that can be written to @c param.
*   @param  param The buffer where the retrieved value(s) will be stored. This
*           buffer must be an array of type @c char with a maximum length of
*           @c len.
*
*   @return @c 0 if a query was successful and the value(s) of the property are
*           stored in @c param, or @c -1 if an error occurred (@c errno is set).
*/
int screen_get_display_property_cv(screen_display_t disp, int pname, int len, char *param);

/**
*   @brief Retrieve the current value of the specified display property of type
*          integer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function stores the current value of a display property in a
*   user-provided buffer.
*
*   The values of the following properties can be retrieved using this function:
*   - @c #SCREEN_PROPERTY_ID
*   - @c #SCREEN_PROPERTY_ATTACHED
*   - @c #SCREEN_PROPERTY_DETACHABLE
*   - @c #SCREEN_PROPERTY_FORMAT_COUNT
*   - @c #SCREEN_PROPERTY_GAMMA
*   - @c #SCREEN_PROPERTY_IDLE_STATE
*   - @c #SCREEN_PROPERTY_KEEP_AWAKES
*   - @c #SCREEN_PROPERTY_MODIFIERS
*   - @c #SCREEN_PROPERTY_MIRROR_MODE
*   - @c #SCREEN_PROPERTY_MODE_COUNT
*   - @c #SCREEN_PROPERTY_POWER_MODE
*   - @c #SCREEN_PROPERTY_PROTECTION_ENABLE
*   - @c #SCREEN_PROPERTY_ROTATION
*   - @c #SCREEN_PROPERTY_TRANSPARENCY
*   - @c #SCREEN_PROPERTY_TYPE
*   - @c #SCREEN_PROPERTY_DPI
*   - @c #SCREEN_PROPERTY_NATIVE_RESOLUTION
*   - @c #SCREEN_PROPERTY_PHYSICAL_SIZE
*   - @c #SCREEN_PROPERTY_SIZE
*   - @c #SCREEN_PROPERTY_FORMATS
*   - @c #SCREEN_PROPERTY_VIEWPORT_POSITION
*   - @c #SCREEN_PROPERTY_VIEWPORT_SIZE
*   - @c #SCREEN_PROPERTY_METRIC_COUNT
*   - @c #SCREEN_PROPERTY_TECHNOLOGY
*   - @c #SCREEN_PROPERTY_REFERENCE_COLOR
*   - @c #SCREEN_PROPERTY_INTENSITY
*
*   @param  disp The handle of the display whose property is being queried.
*   @param  pname The name of the property whose value is being queried. The
*           properties available for query are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param The buffer where the retrieved value(s) will be stored. This
*           buffer must be of type @c int. @c param may be a single integer or
*           an array of integers depending on the property being set.
*
*   @return @c 0 if a query was successful and the value(s) of the property are
*           stored in @c param, or @c -1 if an error occurred (@c errno is set).
*/
int screen_get_display_property_iv(screen_display_t disp, int pname, int *param);

/**
*   @brief Retrieve the current value of the specified display property of type
*          long long integer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function stores the current value of a display property in a
*   user-provided buffer.
*
*   The values of the following properties can be retrieved using this function:
*   - @c #SCREEN_PROPERTY_IDLE_TIMEOUT
*   - @c #SCREEN_PROPERTY_METRICS
*
*   @param  disp The handle of the device whose property is being queried.
*   @param  pname The name of the property whose value is being queried. The
*           properties available for query are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param The buffer where the retrieved value(s) will be stored. This
*           buffer must be of type @c long @c long.
*
*   @return @c 0 if a query was successful and the value(s) of the property are
*           stored in @c param, or @c -1 if an error occurred (@c errno is set).
*/
int screen_get_display_property_llv(screen_display_t disp, int pname, long long *param);

/**
*   @brief Retrieve the current value of the specified display property of type
*          void*
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function stores the current value of a display property in a
*   user-provided buffer.
*
*   The values of the following properties can be retrieved using this function:
*   - @c #SCREEN_PROPERTY_CONTEXT
*   - @c #SCREEN_PROPERTY_FOCUS
*   - @c #SCREEN_PROPERTY_MODE
*   - @c #SCREEN_PROPERTY_MTOUCH_FOCUS
*   - @c #SCREEN_PROPERTY_POINTER_FOCUS
*
*   @param  disp The handle of the display whose property is being queried.
*   @param  pname The name of the property whose value is being queried. The
*           properties available for query are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param The buffer where the retrieved value(s) will be stored. This
*           buffer must be of type @c void*.
*
*   @return @c 0 if a query was successful and the value(s) of the property are
*           stored in @c param, or @c -1 if an error occurred (@c errno is set).
*/
int screen_get_display_property_pv(screen_display_t disp, int pname, void **param);

/**
*   @brief Set the value of the specified display property of type char
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function sets the value of a display property from a user-provided buffer.
*   No more than @c len bytes will be read from @c param.
*
*   Currently there are no display properties that can be queried using this
*   function.
*
*   @param  disp The handle of the display whose property is to be set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  len The maximum number of bytes that can be read from @c param.
*   @param  param A pointer to a buffer containing the new value(s).  This
*           buffer must be an array of type @c char with a maximum length of
*           @c len.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_display_property_cv(screen_display_t disp, int pname, int len, const char *param);

/**
*   @brief Set the value of the specified display property of type integer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function sets the value of a display property from a user-provided buffer.
*
*   You can use this function to set the value of the following properties:
*   - @c #SCREEN_PROPERTY_GAMMA
*   - @c #SCREEN_PROPERTY_MIRROR_MODE
*   - @c #SCREEN_PROPERTY_MODE
*   - @c #SCREEN_PROPERTY_POWER_MODE
*   - @c #SCREEN_PROPERTY_PROTECTION_ENABLE
*   - @c #SCREEN_PROPERTY_ROTATION
*   - @c #SCREEN_PROPERTY_VIEWPORT_POSITION
*   - @c #SCREEN_PROPERTY_VIEWPORT_SIZE
*   - @c #SCREEN_PROPERTY_REFERENCE_COLOR
*   - @c #SCREEN_PROPERTY_INTENSITY
*
*   @param  disp The handle of the display whose property is to be set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param A pointer to a buffer containing the new value(s).  This
*           buffer must be of type @c int. @c param may be a single integer or
*           an array of integers depending on the property being set.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_display_property_iv(screen_display_t disp, int pname, const int *param);

/**
*   @brief Set the value of the specified display property of type long long
*          integer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function sets the value of a display property from a user-provided buffer.
*
*   You can use this function to set the value of the following properties:
*   - @c #SCREEN_PROPERTY_IDLE_TIMEOUT
*
*   @param  disp The handle of the display whose property is to be set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param A pointer to a buffer containing the new value(s).  This
*           buffer must be of type @c long @c long.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_display_property_llv(screen_display_t disp, int pname, const long long *param);

/**
*   @brief Set the value of the specified display property of type void*
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function sets the value of a display property from a user-provided buffer.
*
*   You can use this function to set the value of the following properties:
*   - @c #SCREEN_PROPERTY_FOCUS
*   - @c #SCREEN_PROPERTY_MTOUCH_FOCUS
*   - @c #SCREEN_PROPERTY_POINTER_FOCUS
*
*   @param  disp The handle of the display whose property is to be set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param A pointer to a buffer containing the new value(s).  This
*           buffer must be of type @c void*.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_display_property_pv(screen_display_t disp, int pname, void **param);

/**
*   @brief Retrieve the display modes supported by a specified display
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function returns the video modes that are supported by a display. All
*   elements in the list are unique. Note that several modes can have identical
*   resolutions and differ only in refresh rate or aspect ratio. You can obtain
*   the number of modes supported by querying the @c #SCREEN_PROPERTY_MODE_COUNT
*   property. No more than @c max modes will be stored.
*
*   @param  display The handle of the display whose display modes are being
*           queried.
*   @param  max The maximum number of display modes that can be written to the
*           array of modes pointed to by @c param.
*   @param  param The buffer where the retrieved display modes will be stored.
*
*   @return @c 0 if a query was successful and the display mode is
*           stored in @c param, or @c -1 if an error occurred (@c errno is set).
*/
int screen_get_display_modes(screen_display_t display, int max, screen_display_mode_t *param);

/**
*   @brief Take a screenshot of the display and store the resulting image in
*   the specified buffer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   This function takes a screenshot of a display and stores the result in a
*   user-provided buffer. The buffer can be a pixmap buffer or a window buffer.
*   The buffer must have been created with the usage flag @c #SCREEN_USAGE_NATIVE
*   in order for the operation to succeed. You need to be working within a
*   privileged context so that you have full access to the display properties of
*   the system. Therefore, a context which was created with the type
*   @c #SCREEN_DISPLAY_MANAGER_CONTEXT must be used. When capturing screenshots of
*   multiple displays, you will need to make one @c screen_read_display() function
*   call per display. The call blocks until the operation is completed. If count
*   is 0 and read_rects is NULL, the entire display is grabbed. Otherwise,
*   read_rects must point to count * 4 integers defining rectangles in screen
*   coordinates that need to be grabbed. Note that the buffer size does not have
*   to match the display size. Scaling will be applied to make the screenshot
*   fit into the buffer provided.
*
*   @param  disp The handle of the display that is the target of the screenshot.
*   @param  buf The buffer where the resulting image will be stored.
*   @param  count The number of rectables supplied in the @c read_rects
*           argument.
*   @param  read_rects A pointer to (@c count * 4) integers that define the
*           areas of display that need to be grabbed for the screenshot.
*   @param  flags The mutex flags; must be set to 0.
*
*   @return @c 0 if a the operation was successful and the pixels are written
*           to @c buf, or @c -1 of an error occurred (@c errno is set).
*/
int screen_read_display(screen_display_t disp, screen_buffer_t buf, int count, const int *read_rects, int flags);

/**
*   @brief Cause a window to share its buffers with a display
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function creates a @c count number of buffers with the size defined by the
*   @c #SCREEN_PROPERTY_BUFFER_SIZE window property of @c win. These buffers
*   are rendered by the windowing system. The display will be used to generate
*   content for the (window) buffers. Once there is a post for the window @c win,
*   the content of the buffers will be displayed on the display @c share.
*   To share display buffers, you need to be working within a privileged
*   context. Therefore, a context that was created with the type
*   @c #SCREEN_DISPLAY_MANAGER_CONTEXT must be used.
*
*   If the display has a framebuffer, then @c screen_share_display_buffers() is similar
*   to @c screen_share_window_buffers().
*
*   @param  win The handle of the window who will be sharing its buffer(s).
*   @param  share The handle of the display who is sharing buffer(s).
*   @param  count The number of buffer st that is shared by the window to the display.
*           A value of @c 0 will default to the Screen services
*           to select the appropriate values for properties such as @c #SCREEN_PROPERTY_FORMAT,
*           @c #SCREEN_PROPERTY_USAGE and @c #SCREEN_PROPERTY_BUFFER_SIZE.
*
*   @return @c 0 if the window shared its buffers, or @c -1 of an error occurred
*          (@c errno is set).
*/
int screen_share_display_buffers(screen_window_t win, screen_display_t share, int count);

/**
*   @brief Block the calling thread until the next vsync happens on the
*          specified display
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   This function blocks the calling thread and returns when the next vsync
*   operation occurs on the specified display.
*
*   @param  display An instance of the display on which to perform the the
*           vsync operation.
*
*   @return @c 0 if a vsync operation occurred, or @c -1 of an error occurred
*          (@c errno is set).
*/
int screen_wait_vsync(screen_display_t display);
/** @} */   /* end of ingroup screen_displays */

/**
*   @ingroup screen_effects
*   @{
*/
/**
*   @brief Prepare the specified window for an effect
*
*   <b>Function Type:</b>  <a href="manual/rscreen_apply_execution.xml">Apply Execution</a>
*
*   This function .
*
*   @param  win The window that is to be prepared for an effect.
*   @param  effect The effect to be prepared on the window.
*
*   @return @c 0 if an effect was successfully prepared, or @c -1 of an error
*           occurred (@c errno is set).
*/
int screen_prepare_effect(screen_window_t win, int effect);

/**
*   @brief Set the value of the specified effect property of type integer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function sets the value of a effect property from a user-provided buffer.
*
*   You can use this function to set the value of the following properties:
*   - @c SCREEN_FLIP_AXIS
*   - @c SCREEN_FLIP_DIRECTION
*   - @c SCREEN_ROTATE_DIRECTION
*   - @c SCREEN_PAGE_CURL_ORIGIN
*   - @c SCREEN_PAGE_CURL_POSITION
*   - @c SCREEN_REVEAL_ORIGIN
*   - @c SCREEN_REVEAL_POSITION
*
*   @param  win The handle of the window whose effect property is to be set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type Screen_Effect_Property_Types.
*   @param  param A pointer to a buffer containing the new value(s).  This
*           buffer must be of type @c int. @c param may be a single integer or
*           an array of integers depending on the property being set.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_effect_property_iv(screen_window_t win, int pname, const int *param);

/**
*   @brief Set the value of the specified effect property of type floating-point
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function sets the value of a effect property from a user-provided buffer.
*
*   Currently there are no effect properties that can be set using this
*   function.
*
*   @param  win The handle of the window whose effect property is to be set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type Screen_Effect_Property_Types.
*   @param  param A pointer to a buffer containing the new value(s).  This
*           buffer must be of type @c float.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_effect_property_fv(screen_window_t win, int pname, const float *param);

/**
*   @brief Start the effect on the specified window
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function starts the effect on a window for a specified duration.
*
*   @param  win The handle of the window whose effect property is to be started.
*   @param  duration The duration that the effect will be in place.
*   @param  notify A flag to indicate whether or not a
*           @c SCREEN_EVENT_EFFECT_COMPLETE event is to be sent upon completion
*           of @c screen_start_effect(). @c 1 indicates that a
*           @c SCREEN_EVENT_EFFECT_COMPLETE is to be sent and @c 0 indicates
*           that no event is sent upon completion of @c screen_start_effect().
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_start_effect(screen_window_t win, float duration, int notify);

/**
*   @brief Stop the effect on the specified window
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function stops the effect on a window for a specified duration.
*
*   Currently there are no effect properties that can be set using this
*   function.
*
*   @param  win The handle of the window whose effect property is to be stopped.
*   @param  duration The duration is not used in @c screen_stop_effect().
*   @param  notify A flag to indicate whether or not a
*           @c SCREEN_EVENT_EFFECT_COMPLETE event is to be sent upon completion
*           of @c screen_start_effect(). @c 1 indicates that a
*           @c SCREEN_EVENT_EFFECT_COMPLETE is to be sent and @c 0 indicates
*           that no event is sent upon completion of @c screen_start_effect().
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_stop_effect(screen_window_t win, float duration, int notify);
/** @} */   /* end of ingroup screen_effects */

/**
*   @ingroup screen_events
*   @{
*/
/**
*   @brief Create an event that can later be filled with event data
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   This function creates an event object. This event can be used to store
*   events from the process's event queue using @c screen_get_event(). Event data
*   can also be filled in with the @c screen_set_event_property() functions and
*   sent to other applications using @c screen_inject_event() or
*   @c screen_send_event(). Events are opaque handles. @c screen_get_event_property()
*   functions must be used to get information from the event. You must destroy
*   event objects when you no longer need them by using @c screen_destroy_event().
*
*   @param  pev An address where the function can store a handle to the native
*           event.
*
*   @return @c 0 if a new event was created, or @c -1 if an error occurred
*           (@c errno is set).
*/
int screen_create_event(screen_event_t *pev);

/**
*   @brief Destroy an event and free associated memory
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   This function frees the memory allocated to hold an event. The event can no
*   longer be used as an argument in subsequent screen calls.
*
*   @param  ev The handle of the event to destroy. This event must have been
*           created with @c screen_create_event().
*
*   @return @c 0 if the event was destroyed, or @c -1 if an error occurred
*           (@c errno is set).
*/
int screen_destroy_event(screen_event_t ev);

/**
*   @brief Wait for a screen event
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>

*   This function gets the next event associated with the given context. If no
*   events have been queued, the function will wait up to the specified amount
*   of time for an event to occur. If the function times out before an event
*   becomes available, an event with a @c #SCREEN_EVENT_NONE type will be returned.
*
*   @param  ctx The context to retrieve events from. This context must have been
*           created using @c screen_create_context().
*   @param  ev An event previously allocated with @c screen_create_event(). Any
*           contents in this event will be replaced with the next event.
*   @param  timeout The maximum time to wait for an event to occur if one has
*           not been queued up already. @c 0 indicates that the call must not
*           wait at all if there are no events associated with the specified
*           context. @c -1 indicates that the call must not return until an
*           event is ready.
*
*   @return @c 0 if the event was retrieved, or @c -1 if an error occurred
*           (@c errno is set).
*/
int screen_get_event(screen_context_t ctx, screen_event_t ev, uint64_t timeout);

/**
*   @brief Retrieve the current value of the specified event property of type
*          char
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   This function stores the current value of an event property in a
*   user-provided buffer. No more than @c len bytes of the specified type will be
*   written.
*   The list of properties that can be queried per event type are listed as
*   follows:
*
*   - @c #SCREEN_EVENT_CREATE
*   - @c #SCREEN_PROPERTY_GROUP
*
*   @param  ev The handle of the event whose property is being queried.
*   @param  pname The name of the property whose value is being queried. The
*           properties available for query are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  len The maximum number of bytes that can be written to @c param.
*   @param  param The buffer where the retrieved value(s) will be stored. This
*           buffer must be an array of type @c char with a maximum length of
*           @c len.
*
*   @return @c 0 if a query was successful and the value(s) of the property are
*           stored in @c param, or @c -1 if an error occurred (@c errno is set).
*/
int screen_get_event_property_cv(screen_event_t ev, int pname, int len, char *param);

/**
*   @brief Retrieve the current value of the specified event property of type
*          integer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   This function stores the current value of an event property in a
*   user-provided buffer.
*   The list of properties that can be queried per event type are listed as
*   follows:
*
*   Event Type: Any
*   - @c #SCREEN_PROPERTY_TYPE
*   - @c #SCREEN_PROPERTY_SCALE_FACTOR
*
*   Event Type: @c #SCREEN_EVENT_DISPLAY
*   - @c #SCREEN_PROPERTY_ATTACHED
*   - @c #SCREEN_PROPERTY_MIRROR_MODE
*   - @c #SCREEN_PROPERTY_MODE
*   - @c #SCREEN_PROPERTY_PROTECTION_ENABLE
*
*   Event Type: @c #SCREEN_EVENT_EFFECT_COMPLETE
*    - @c #SCREEN_PROPERTY_EFFECT
 *
*   Event Type: @c SCREEN_EVENT_GAMEPAD
*   - @c #SCREEN_PROPERTY_BUTTONS
*   - @c #SCREEN_PROPERTY_DEVICE
*   - @c #SCREEN_PROPERTY_ANALOG0
*   - @c #SCREEN_PROPERTY_ANALOG1
*   - @c #SCREEN_PROPERTY_MODIFIERS
*
*   Event Type: @c #SCREEN_EVENT_IDLE
*    - @c #SCREEN_PROPERTY_IDLE_STATE
*    - @c #SCREEN_PROPERTY_OBJECT_TYPE
*
*   Event Type: @c #SCREEN_EVENT_INPUT
*    - @c #SCREEN_PROPERTY_DEVICE
*    - @c #SCREEN_PROPERTY_INPUT_VALUE
*
*   Event Type: @c #SCREEN_EVENT_JOG
*    - @c #SCREEN_PROPERTY_DEVICE
*    - @c #SCREEN_PROPERTY_JOG_COUNT
*
*   Event Type: @c SCREEN_EVENT_JOYSTICK
*   - @c #SCREEN_PROPERTY_BUTTONS
*   - @c #SCREEN_PROPERTY_DEVICE
*   - @c #SCREEN_PROPERTY_ANALOG0
*   - @c #SCREEN_PROPERTY_MODIFIERS
*
*   Event Type: @c #SCREEN_EVENT_KEYBOARD
*   - @c #SCREEN_PROPERTY_KEY_ALTERNATE_SYM
*   - @c #SCREEN_PROPERTY_DEVICE
*   - @c #SCREEN_PROPERTY_KEY_CAP
*   - @c #SCREEN_PROPERTY_FLAGS
*   - @c #SCREEN_PROPERTY_MODIFIERS
*   - @c #SCREEN_PROPERTY_SCAN
*   - @c #SCREEN_PROPERTY_SYM
*   - @c #SCREEN_PROPERTY_SEQUENCE_ID
*
*   Event Types: @c #SCREEN_EVENT_MTOUCH_PRETOUCH, @c #SCREEN_EVENT_MTOUCH_TOUCH,
*                @c #SCREEN_EVENT_MTOUCH_MOVE, @c #SCREEN_EVENT_MTOUCH_RELEASE
*   - @c #SCREEN_PROPERTY_BUTTONS
*   - @c #SCREEN_PROPERTY_DEVICE
*   - @c #SCREEN_PROPERTY_MODIFIERS
*   - @c #SCREEN_PROPERTY_POSITION
*   - @c #SCREEN_PROPERTY_SEQUENCE_ID
*   - @c #SCREEN_PROPERTY_SIZE
*   - @c #SCREEN_PROPERTY_SOURCE_POSITION
*   - @c #SCREEN_PROPERTY_SOURCE_SIZE
*   - @c #SCREEN_PROPERTY_TOUCH_ID
*   - @c #SCREEN_PROPERTY_TOUCH_ORIENTATION
*   - @c #SCREEN_PROPERTY_TOUCH_PRESSURE
*   - @c #SCREEN_PROPERTY_TOUCH_TYPE
*
*   Event Type: @c #SCREEN_EVENT_POINTER
*   - @c #SCREEN_PROPERTY_BUTTONS
*   - @c #SCREEN_PROPERTY_DEVICE
*   - @c #SCREEN_PROPERTY_MODIFIERS
*   - @c #SCREEN_PROPERTY_MOUSE_HORIZONTAL_WHEEL
*   - @c #SCREEN_PROPERTY_MOUSE_WHEEL
*   - @c #SCREEN_PROPERTY_POSITION
*   - @c #SCREEN_PROPERTY_SOURCE_POSITION
*
*   Event Type: @c #SCREEN_EVENT_PROPERTY
*    - @c #SCREEN_PROPERTY_NAME
*    - @c #SCREEN_PROPERTY_OBJECT_TYPE
*
*   Event Type: @c #SCREEN_EVENT_USER
*    - @c #SCREEN_PROPERTY_USER_DATA
*
*   @param  ev The handle of the event whose property is being queried. The
*           event must have an event type of
*           <a href="group__screen__events_1Screen_Event_Types.xml">Screen event types</a>.
*   @param  pname The name of the property whose value is being queried. The
*           properties available for query are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param The buffer where the retrieved value(s) will be stored. This
*           buffer must be of type @c int. @c param may be a single integer or
*           an array of integers depending on the property being set.
*
*   @return @c 0 if a query was successful and the value(s) of the property are
*           stored in @c param, or @c -1 if an error occurred (@c errno is set).
*/
int screen_get_event_property_iv(screen_event_t ev, int pname, int *param);

/**
*   @brief Retrieve the current value of the specified event property of type
*          long long integer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   This function stores the current value of an event property in a
*   user-provided buffer.
*
*   Event Type: Any
*    - @c #SCREEN_PROPERTY_TIMESTAMP
*
*   @param  ev The handle of the event whose property is being queried.
*   @param  pname The name of the property whose value is being queried. The
*           properties available for query are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param The buffer where the retrieved value(s) will be stored. This
*           buffer must be of long long integer.
*
*   @return @c 0 if a query was successful and the value(s) of the property are
*           stored in @c param, or @c -1 if an error occurred (@c errno is set).
*/
int screen_get_event_property_llv(screen_event_t ev, int pname, long long *param);

/**
*   @brief Retrieve the current value of the specified event property of type
*          void*
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   This function stores the current value of an event property in a
*   user-provided buffer. The list of properties that can be queried per event
*   type are listed as follows:
*
*   Event Type: @c #SCREEN_EVENT_CLOSE
*   - @c #SCREEN_PROPERTY_WINDOW
*
*   Event Type: @c #SCREEN_EVENT_CREATE
*   - @c #SCREEN_PROPERTY_WINDOW
 *
*   Event Type: @c #SCREEN_EVENT_DISPLAY
*   - @c #SCREEN_PROPERTY_DISPLAY
*
*   Event Type: @c #SCREEN_EVENT_GAMEPAD
*   - @c #SCREEN_PROPERTY_DEVICE
*   - @c #SCREEN_PROPERTY_WINDOW
*
*   Event Type: @c #SCREEN_EVENT_IDLE
*    - @c #SCREEN_PROPERTY_DISPLAY
*    - @c #SCREEN_PROPERTY_GROUP
*
*   Event Type: @c #SCREEN_EVENT_INPUT
*    - @c #SCREEN_PROPERTY_DEVICE
*
*   Event Type: @c #SCREEN_EVENT_JOG
*   - @c #SCREEN_PROPERTY_DEVICE
*
*   Event Type: @c #SCREEN_EVENT_JOYSTICK
*   - @c #SCREEN_PROPERTY_DEVICE
*   - @c #SCREEN_PROPERTY_WINDOW
*
*   Event Type: @c #SCREEN_EVENT_KEYBOARD
*   - @c #SCREEN_PROPERTY_DEVICE
*   - @c #SCREEN_PROPERTY_WINDOW
*
*   Event Types: @c #SCREEN_EVENT_MTOUCH_PRETOUCH, @c #SCREEN_EVENT_MTOUCH_TOUCH,
*                @c #SCREEN_EVENT_MTOUCH_MOVE, @c #SCREEN_EVENT_MTOUCH_RELEASE
*   - @c #SCREEN_PROPERTY_DEVICE
*   - @c #SCREEN_PROPERTY_WINDOW
*
*   Event Type: @c #SCREEN_EVENT_POINTER
*   - @c #SCREEN_PROPERTY_DEVICE
*   - @c #SCREEN_PROPERTY_WINDOW
*
*   Event Type: @c #SCREEN_EVENT_POST
*   - @c #SCREEN_PROPERTY_WINDOW
*
*   Event Type: @c #SCREEN_EVENT_PROPERTY
*   - @c #SCREEN_PROPERTY_GROUP
*   - @c #SCREEN_PROPERTY_DISPLAY
*   - @c #SCREEN_PROPERTY_WINDOW
*
*   Event Type: @c #SCREEN_EVENT_UNREALIZE
*   - @c #SCREEN_PROPERTY_WINDOW
*
*   @param  ev The handle of the event whose property is being queried. The
*           event must have an event type of
*           <a href="group__screen__events_1Screen_Event_Types.xml">Screen event types</a>.
*   @param  pname The name of the property whose value is being queried. The
*           properties available for query are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param The buffer where the retrieved value(s) will be stored. This
*           buffer must be of type @c void*.
*
*   @return @c 0 if a query was successful and the value(s) of the property are
*           stored in @c param, or @c -1 if an error occurred (@c errno is set).
*/
int screen_get_event_property_pv(screen_event_t ev, int pname, void **param);

/**
*   @brief Send an input event to the window that has input focus on a
*          given display
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   A window manager and an input provider can use this function when they need
*   to inject an event in the system. You need to be within a privileged context
*   to be able to inject input events. You can create a privileged context by
*   calling the function @c screen_create_context() with a context type of
*   @c #SCREEN_WINDOW_MANAGER_CONTEXT or @c #SCREEN_INPUT_PROVIDER_CONTEXT.
*   Prior to calling @c screen_inject_event(), you must have set all relevant event
*   properties to valid values - especially the event type property.
*   When using @c screen_inject_event(), the event will be sent to the window that
*   has input focus on the specified display. If you want to send an event to a
*   particular window other than the one who has input focus, then use
*   @c screen_send_event().
*
*   @param  disp The display into which the event will be injected. You can
*           obtain a handle to the display by either @c screen_get_context_property()
*           or @c screen_get_window_property() functions.
*   @param  ev An event handle that was created with @c screen_create_event(). This
*           event must contain all the relevant event data pertaining to its type
*           when injected into the system.
*
*   @return @c 0 if the event was sent to the window that has input focus on
*           the display, or @c -1 if an error occurred (@c errno is set).
*/
int screen_inject_event(screen_display_t disp, screen_event_t ev);

/**
*   @brief Send an input event to a process
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   A window manager and an input provider can use this function when they need
*   to inject an event in the system. You need to be within a privileged context
*   to be able to inject input events. You can create a privileged context by
*   calling the function @c screen_create_context() with a context type of
*   @c #SCREEN_WINDOW_MANAGER_CONTEXT or @c #SCREEN_INPUT_PROVIDER_CONTEXT.
*   Prior to calling @c screen_inject_event(), you must have set all relevant event
*   properties to valid values - especially the event type property.
*   When using @c screen_inject_event(), the event will be sent to the window that
*   has input focus on the specified display. If you want to send an event to a
*   particular window other than the one who has input focus, then use
*   @c screen_send_event().
*
*   @param  ctx A context within Screen that was created with
*           @c screen_create_context().
*   @param  ev An event handle that was created with @c screen_create_event(). This
*           event must contain all the relevant event data pertaining to its type
*           when injected into the system.
*   @param  pid The process the event is to be sent to.
*
*   @return @c 0 if the event was sent to the specified process, or @c -1 if an
*           error occurred (@c errno is set).
*/
int screen_send_event(screen_context_t ctx, screen_event_t ev, pid_t pid);

/**
*   @brief Set the value of the specified event property of type char
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   This function sets the value of an event property from a user-provided buffer.
*   No more than @c len bytes of the specified type will be written.
*   The list of properties that can be set per event type are listed as follows:
*
*   Event Type: @c #SCREEN_EVENT_CREATE
*   - @c #SCREEN_PROPERTY_GROUP
*
*   @param  ev The handle of the event whose property is being set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  len The maximum number of bytes that can be read from @c param.
*   @param  param A pointer to a buffer containing the new value(s). This
*           buffer must be an array of type @c char with a maximum length of
*           @c len.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_event_property_cv(screen_event_t ev, int pname, int len, const char *param);

/**
*   @brief Set the value of the specified event property of type integer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   This function sets the value of an event property from a user-provided buffer.
*   The list of properties that can be set per event type are listed as follows:
*
*   Event Type: Any
*   - @c #SCREEN_PROPERTY_TYPE
*   - @c #SCREEN_PROPERTY_SCALE_FACTOR
*
*   Event Type: @c #SCREEN_EVENT_DISPLAY
*   - @c #SCREEN_PROPERTY_ATTACHED
*   - @c #SCREEN_PROPERTY_DISPLAY
*   - @c #SCREEN_PROPERTY_MIRROR_MODE
*   - @c #SCREEN_PROPERTY_MODE
*   - @c #SCREEN_PROPERTY_PROTECTION_ENABLE
*
*   Event Type: @c #SCREEN_EVENT_EFFECT_COMPLETE
*    - @c #SCREEN_PROPERTY_EFFECT
*
*   Event Type: @c SCREEN_EVENT_GAMEPAD
*   - @c #SCREEN_PROPERTY_BUTTONS
*   - @c #SCREEN_PROPERTY_DEVICE
*   - @c #SCREEN_PROPERTY_ANALOG0
*   - @c #SCREEN_PROPERTY_ANALOG1
*   - @c #SCREEN_PROPERTY_MODIFIERS
*
*   Event Type: @c #SCREEN_EVENT_IDLE
*    - @c #SCREEN_PROPERTY_IDLE_STATE
*
*   Event Type: @c #SCREEN_EVENT_INPUT
*    - @c #SCREEN_PROPERTY_DEVICE
*    - @c #SCREEN_PROPERTY_INPUT_VALUE
*
*   Event Type: @c #SCREEN_EVENT_JOG
*    - @c #SCREEN_PROPERTY_DEVICE
*    - @c #SCREEN_PROPERTY_JOG_COUNT
*
*   Event Type: @c SCREEN_EVENT_JOYSTICK
*   - @c #SCREEN_PROPERTY_BUTTONS
*   - @c #SCREEN_PROPERTY_DEVICE
*   - @c #SCREEN_PROPERTY_ANALOG0
*   - @c #SCREEN_PROPERTY_MODIFIERS
*
*   Event Type: @c #SCREEN_EVENT_KEYBOARD
*   - @c #SCREEN_PROPERTY_KEY_ALTERNATE_SYM
*   - @c #SCREEN_PROPERTY_DEVICE
*   - @c #SCREEN_PROPERTY_KEY_CAP
*   - @c #SCREEN_PROPERTY_FLAGS
*   - @c #SCREEN_PROPERTY_MODIFIERS
*   - @c #SCREEN_PROPERTY_SCAN
*   - @c #SCREEN_PROPERTY_SYM
*   - @c #SCREEN_PROPERTY_SEQUENCE_ID
*
*   Event Types: @c #SCREEN_EVENT_MTOUCH_PRETOUCH, @c #SCREEN_EVENT_MTOUCH_TOUCH,
*                @c #SCREEN_EVENT_MTOUCH_MOVE, @c #SCREEN_EVENT_MTOUCH_RELEASE
*   - @c #SCREEN_PROPERTY_BUTTONS
*   - @c #SCREEN_PROPERTY_DEVICE
*   - @c #SCREEN_PROPERTY_MODIFIERS
*   - @c #SCREEN_PROPERTY_POSITION
*   - @c #SCREEN_PROPERTY_SEQUENCE_ID
*   - @c #SCREEN_PROPERTY_SIZE
*   - @c #SCREEN_PROPERTY_SOURCE_POSITION
*   - @c #SCREEN_PROPERTY_SOURCE_SIZE
*   - @c #SCREEN_PROPERTY_TOUCH_ID
*   - @c #SCREEN_PROPERTY_TOUCH_ORIENTATION
*   - @c #SCREEN_PROPERTY_TOUCH_PRESSURE
*   - @c #SCREEN_PROPERTY_TOUCH_TYPE
*
*   Event Type: @c #SCREEN_EVENT_POINTER
*   - @c #SCREEN_PROPERTY_BUTTONS
*   - @c #SCREEN_PROPERTY_DEVICE
*   - @c #SCREEN_PROPERTY_MODIFIERS
*   - @c #SCREEN_PROPERTY_MOUSE_HORIZONTAL_WHEEL
*   - @c #SCREEN_PROPERTY_MOUSE_WHEEL
*   - @c #SCREEN_PROPERTY_POSITION
*   - @c #SCREEN_PROPERTY_SOURCE_POSITION
*
*   Event Type: @c #SCREEN_EVENT_PROPERTY
*    - @c #SCREEN_PROPERTY_NAME
*
*   Event Type: @c #SCREEN_EVENT_USER
*    - @c #SCREEN_PROPERTY_USER_DATA
*
*   @param  ev The handle of the event whose property is being set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param A pointer to a buffer containing the new value(s). This
*           buffer must be of type @c int. @c param may be a single integer or
*           an array of integers depending on the property being set.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_event_property_iv(screen_event_t ev, int pname, const int *param);

/**
*   @brief Set the current value of the specified event property of type long
*          long integer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   This function sets the value of an event property from a user-provided
*   array.
*
*   Currently, there are no event properties that can be set using this
*   function.
*
*   @param  ev The handle of the event whose property is being set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param A pointer to a buffer containing the new value(s). This
*           buffer must be of type @c long @c long.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_event_property_llv(screen_event_t ev, int pname, const long long *param);

/**
*   @brief Set the value of the specified event property of type void*
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   This function sets the value of an event property from a user-provided
*   array.
*   The list of properties that can be set per event type are listed as follows:
*
*   Event Type: @c #SCREEN_EVENT_CREATE
*   - @c #SCREEN_PROPERTY_WINDOW
*
*   Event Type: @c #SCREEN_EVENT_DISPLAY
*   - @c #SCREEN_PROPERTY_DISPLAY
*
*   Event Type: @c #SCREEN_EVENT_GAMEPAD
*   - @c #SCREEN_PROPERTY_DEVICE
*   - @c #SCREEN_PROPERTY_WINDOW
*
*   Event Type: @c #SCREEN_EVENT_IDLE
*    - @c #SCREEN_PROPERTY_DISPLAY
*    - @c #SCREEN_PROPERTY_GROUP
*
*   Event Type: @c #SCREEN_EVENT_INPUT
*    - @c #SCREEN_PROPERTY_DEVICE
*
*   Event Type: @c #SCREEN_EVENT_JOG
*   - @c #SCREEN_PROPERTY_DEVICE
*
*   Event Type: @c #SCREEN_EVENT_JOYSTICK
*   - @c #SCREEN_PROPERTY_DEVICE
*   - @c #SCREEN_PROPERTY_WINDOW
*
*   Event Type: @c #SCREEN_EVENT_KEYBOARD
*   - @c #SCREEN_PROPERTY_DEVICE
*   - @c #SCREEN_PROPERTY_WINDOW
*
*   Event Types: @c #SCREEN_EVENT_MTOUCH_PRETOUCH, @c #SCREEN_EVENT_MTOUCH_TOUCH,
*                @c #SCREEN_EVENT_MTOUCH_MOVE, @c #SCREEN_EVENT_MTOUCH_RELEASE
*   - @c #SCREEN_PROPERTY_WINDOW
*
*   Event Type: @c #SCREEN_EVENT_POINTER
*   - @c #SCREEN_PROPERTY_DEVICE
*   - @c #SCREEN_PROPERTY_WINDOW
*
*   Event Type: @c #SCREEN_EVENT_POST
*   - @c #SCREEN_PROPERTY_WINDOW
*
*   Event Type: @c #SCREEN_EVENT_PROPERTY
*   - @c #SCREEN_PROPERTY_GROUP
*   - @c #SCREEN_PROPERTY_DISPLAY
*   - @c #SCREEN_PROPERTY_WINDOW
*
*   Event Type: @c #SCREEN_EVENT_UNREALIZE
*   - @c #SCREEN_PROPERTY_WINDOW
*
*   @param  ev The handle of the event whose property is being set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param A pointer to a buffer containing the new value(s). This
*           buffer must be of type @c void*.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_event_property_pv(screen_event_t ev, int pname, void **param);
/** @} */   /* end of ingroup screen_events */

/*
 * Groups
 */
/**
*   @ingroup screen_groups
*   @{
*/
/**
*   @brief Create a window group
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   This function creates a window group given a group object and a context. The
*   context is shared by all windows in this group. You can use groups in order
*   to organize your application windows.
*
*   @param  pgrp The handle of the group.
*   @param  ctx The connection to the composition manager. This context must
*           have been created with @c screen_create_context().
*
*   @return @c 0 if a new window group was created, or @c -1 if an error
*           occurred (@c errno is set).
*/
int screen_create_group(screen_group_t *pgrp, screen_context_t ctx);

/**
*   @brief Destroy a window group
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function destroys a window group given a @c #screen_group_t instance. When
*   a window group is destroyed, all windows that belonged to the group are no
*   longer associated with the group. You must destroy each @c #screen_group_t
*   after it is no longer needed.
*
*   @param  grp The window group to be destroyed. The group must have been
*           created with @c screen_create_group().
*
*   @return @c 0 if the window group was destroyed, or @c -1 if an error
*           occurred (@c errno is set).
*/
int screen_destroy_group(screen_group_t grp);

/**
*   @brief Retrieve the current value of the specified group property of type
*          char
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function stores the current value of group property in a
*   user-provided buffer. No more than @c len bytes of the specified type will be
*   written.
*
*   The values of the following properties can be retrieved using this function:
*   - @c #SCREEN_PROPERTY_NAME
*
*   @param  grp The handle of the group whose property is being queried.
*   @param  pname The name of the property whose value is being queried. The
*           properties available for query are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  len The maximum number of bytes that can be written to @c param.
*   @param  param The buffer where the retrieved value(s) will be stored. This
*           buffer must be an array of type @c char with a maximum length of
*           @c len.
*
*   @return @c 0 if a query was successful and the value(s) of the property are
*           stored in @c param, or @c -1 if an error occurred (@c errno is set).
*/
int screen_get_group_property_cv(screen_group_t grp, int pname, int len, char *param);

/**
*   @brief Retrieve the current value of the specified group property of type
*          integer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function stores the current value of group property in a
*   user-provided buffer.
*
*   The values of the following properties can be retrieved using this function:
*
*   - @c #SCREEN_PROPERTY_BUFFER_POOL
*   - @c #SCREEN_PROPERTY_IDLE_STATE
*
*   @param  grp The handle of the group whose property is being queried.
*   @param  pname The name of the property whose value is being queried. The
*           properties available for query are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param The buffer where the retrieved value(s) will be stored. This
*           buffer must be of type @c int. @c param may be a single integer or
*           an array of integers depending on the property being set.
*
*   @return @c 0 if a query was successful and the value(s) of the property are
*           stored in @c param, or @c -1 if an error occurred (@c errno is set).
*/
int screen_get_group_property_iv(screen_group_t grp, int pname, int *param);

/**
*   @brief Retrieve the current value of the specified group property of type
*          long long integer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function stores the current value of group property in a
*   user-provided buffer.
*
*   The values of the following properties can be retrieved using this function:
*   - @c #SCREEN_PROPERTY_IDLE_TIMEOUT
*
*   @param  grp The handle of the group whose property is being queried.
*   @param  pname The name of the property whose value is being queried. The
*           properties available for query are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param The buffer where the retrieved value(s) will be stored. This
*           buffer must be of type @c long @c long.
*
*   @return @c 0 if a query was successful and the value(s) of the property are
*           stored in @c param, or @c -1 if an error occurred (@c errno is set).
*/
int screen_get_group_property_llv(screen_group_t grp, int pname, long long *param);

/**
*   @brief Retrieve the current value of the specified group property of type
*          void*
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function stores the current value of group property in a
*   user-provided buffer.
*
*   The values of the following properties can be retrieved using this function:
*   - @c #SCREEN_PROPERTY_CONTEXT
*   - @c #SCREEN_PROPERTY_FOCUS
*   - @c #SCREEN_PROPERTY_MTOUCH_FOCUS
*   - @c #SCREEN_PROPERTY_POINTER_FOCUS
*   - @c #SCREEN_PROPERTY_USER_HANDLE
*
*   @param  grp The handle of the group whose property is being queried.
*   @param  pname The name of the property whose value is being queried. The
*           properties available for query are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param The buffer where the retrieved value(s) will be stored. This
*           buffer must be of type @c void*.
*
*   @return @c 0 if a query was successful and the value(s) of the property are
*           stored in @c param, or @c -1 if an error occurred (@c errno is set).
*/
int screen_get_group_property_pv(screen_group_t grp, int pname, void **param);

/**
*   @brief Set the value of the specified group property of type char
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function sets the value of a group property from a user-provided buffer.
*   You can use this function to set the value of the following properties:
*   - @c #SCREEN_PROPERTY_NAME
*
*   @param  grp The handle of the group whose property is being set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  len The maximum number of bytes that can be read from @c param.
*   @param  param A pointer to a buffer containing the new value(s). This
*           buffer must be an array of type @c char with a maximum length of
*           @c len.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_group_property_cv(screen_group_t grp, int pname, int len, const char *param);

/**
*   @brief Set the value of the specified group property of type integer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function sets the value of a group property from a user-provided buffer.
*   You can use this function to set the value of the following properties:
*
*   - @c #SCREEN_PROPERTY_BUFFER_POOL
*
*   @param  grp The handle of the group whose property is being set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param A pointer to a buffer containing the new value(s). This
*           buffer must be of type @c int. @c param may be a single integer or
*           an array of integers depending on the property being set.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_group_property_iv(screen_group_t grp, int pname, const int *param);

/**
*   @brief Set the value of the specified group property of type long long
*          integer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function sets the value of a group property from a user-provided buffer.
*   You can use this function to set the value of the following properties:
*   - @c #SCREEN_PROPERTY_IDLE_TIMEOUT
*
*   @param  grp The handle of the group whose property is being set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type
*            <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param A pointer to a buffer containing the new value(s). This
*           buffer must be of type @c long @c long.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_group_property_llv(screen_group_t grp, int pname, const long long *param);

/**
*   @brief Set the value of the specified group property of type void*
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function sets the value of a group property from a user-provided buffer.
*   You can use this function to set the value of the following properties:
*   - @c #SCREEN_PROPERTY_FOCUS
*   - @c #SCREEN_PROPERTY_MTOUCH_FOCUS
*   - @c #SCREEN_PROPERTY_POINTER_FOCUS
*   - @c #SCREEN_PROPERTY_USER_HANDLE
*
*   @param  grp The handle of the group whose property is being set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param A pointer to a buffer containing the new value(s). This
*           buffer must be of type @c void*.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_group_property_pv(screen_group_t grp, int pname, void **param);
/** @} */   /* end of ingroup screen_groups */

/*
 * Pixmaps
 */
/**
*   @ingroup screen_pixmaps
*   @{
*/
/**
*   @brief Associate an externally allocated buffer with a pixmap
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function can be used to force a pixmap to use a buffer that was
*   allocated by the application. Since pixmaps can have only one buffer, it is
*   not possible to call this function or @c screen_create_pixmap_buffer() more
*   than once. Whoever allocates the buffer is required to meet all alignment
*   and granularity constraints required for the usage flags. The buffer @c buf
*   must have been created with the function @c screen_create_buffer(),
*   @c screen_create_pixmap_buffer(), or @c screen_create_window_buffers().
*
*   @param  pix The handle of a pixmap that does not already have a buffer
*           created or associated to it.
*   @param  buf A buffer that was allocated by the application.
*
*   @return @c 0 if the buffer was used by the specified pixmap, or @c -1 if an
*           error occurred (@c errno is set).
*/
int screen_attach_pixmap_buffer(screen_pixmap_t pix, screen_buffer_t buf);

/**
*   @brief Create a pixmap that can be used to do off-screen rendering
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   This function creates a pixmap object, which is an off-screen rendering
*   target. The results of this rendering can later be copied to a window object.
*   Applications must use @c screen_destroy_pixmap() when a pixmap is no longer
*   used.
*
*   @param  ppix An address where the function can store the handle to the
*           newly created native pixmap.
*   @param  ctx The connection to the composition manager. This context must
*           have been created with @c screen_create_context().
*
*   @return @c 0 if a new pixmap was created,or @c -1 if an error occurred
*          (@c errno is set).
*/
int screen_create_pixmap(screen_pixmap_t *ppix, screen_context_t ctx);

/**
*   @brief Send a request to the composition manager to add a new buffer to a
*          pixmap
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function to adds a buffer to a pixmap. A buffer cannot be created if a
*   buffer was previously attached using @c screen_attach_pixmap_buffer().
*
*   @param  pix The handle of the pixmap for which a new buffer will be created.
*
*   @return @c 0 if a new pixmap buffer was created,or @c -1 if an error
*           occurred (@c errno is set).
*/
int screen_create_pixmap_buffer(screen_pixmap_t pix);

/**
*   @brief Destroy a pixmap and frees associated resources
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function destroys the pixmap associated with the specified pixmap. Any
*   resources and buffer created for this pixmap, whether locally or by the
*   composition manager, will be released. The pixmap handle can no longer be
*   used as argument in subsequent screen calls. Pixmap buffers that are not
*   created by composition manager but are registered with
*   @c screen_attach_pixmap_buffer() are not freed by this operation. The
*   application is responsible for freeing its own external buffers.
*
*   @param  pix The handle of the pixmap which is to be destroyed.
*
*   @return @c 0 if the pixmap buffer was destroyed, or @c -1 if an error
*           occurred (@c errno is set).
*/
int screen_destroy_pixmap(screen_pixmap_t pix);

/**
*   @brief Send a request to the composition manager to destory the buffer of
*          the specified pixmap
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function releases the buffer that was allocated for a pixmap, without
*   destroying the pixmap. If the buffer was created with
*   @c screen_create_pixmap_buffer(), the memory is released and can be used for
*   other window or pixmap buffers. If the buffer was attached using
*   @c screen_attach_pixmap_buffer(), the buffer is destroyed but no memory is
*   actually released. In this case the application is responsible for freeing
*   the memory after calling @c screen_destroy_pixmap_buffer(). Once a pixmap
*   buffer has been destroyed, you can change the format, usage and buffer size
*   before creating a new buffer again.
*   The memory that is released by this call is not reserved and can be used for
*   any subsequent buffer allocation by the windowing system.
*
*   @param  pix The handle of the pixmap whose buffer is to be destroyed.
*
*   @return @c 0 if the memory used by the pixmap buffer was freed, or @c -1 if
*           an error occurred (@c errno is set).
*/
int screen_destroy_pixmap_buffer(screen_pixmap_t pix);

/**
*   @brief Retrieve the current value of the specified pixmap property of type
*          char
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function retrieves the value of pixmap property from a user-provided buffer.
*   The values of the following properties can be queried using this function:
*   - @c #SCREEN_PROPERTY_GROUP
*   - @c #SCREEN_PROPERTY_ID_STRING
*
*   @param  pix The handle of the pixmap whose property is being queried.
*   @param  pname The name of the property whose value is being queried. The
*           properties available for querying are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  len The maximum number of bytes that can be written to @c param.
*   @param  param A pointer to a buffer containing the new value(s). This
*           buffer must be an array of type @c char with a maximum length of
*           @c len.
*
*   @return @c 0 if a query was successful and the value(s) of the property are
*           stored in @c param, or @c -1 if an error occurred (@c errno is set).
*/
int screen_get_pixmap_property_cv(screen_pixmap_t pix, int pname, int len, char *param);

/**
*   @brief Retrieve the current value of the specified pixmap property of type
*          integer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function retrieves the value of pixmap property from a user-provided buffer.
*   The values of the following properties can be queried using this function:
*   - @c #SCREEN_PROPERTY_ALPHA_MODE
*   - @c #SCREEN_PROPERTY_COLOR_SPACE
*   - @c #SCREEN_PROPERTY_FORMAT
*   - @c #SCREEN_PROPERTY_USAGE
*   - @c #SCREEN_PROPERTY_BUFFER_SIZE
*   - @c #SCREEN_PROPERTY_METRIC_COUNT
*
*   @param  pix The handle of the pixmap whose property is being queried.
*   @param  pname The name of the property whose value is being queried. The
*           properties available for querying are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param A pointer to a buffer containing the new value(s). This
*           buffer must be of type @c int. @c param may be a single integer or
*           an array of integers depending on the property being set.
*
*   @return @c 0 if a query was successful and the value(s) of the property are
*           stored in @c param, or @c -1 if an error occurred (@c errno is set).
*/
int screen_get_pixmap_property_iv(screen_pixmap_t pix, int pname, int *param);

/**
*   @brief Retrieve the current value of the specified pixmap property of type
*          long long integer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function retrieves the value of pixmap property from a user-provided
*   array.
*   The values of the following properties can be queried using this function:
*    - @c #SCREEN_PROPERTY_METRICS
*
*   @param  pix The handle of the pixmap whose property is being queried.
*   @param  pname The name of the property whose value is being queried. The
*           properties available for querying are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param A pointer to a buffer containing the new value(s). This
*           buffer must be of type @c long @c long.
*
*   @return @c 0 if a query was successful and the value(s) of the property are
*           stored in @c param, or @c -1 if an error occurred (@c errno is set).
*/
int screen_get_pixmap_property_llv(screen_pixmap_t pix, int pname, long long *param);

/**
*   @brief Retrieve the current value of the specified pixmap property of type
*          void*
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function retrieves the value of pixmap property from a user-provided buffer.
*   The values of the following properties can be queried using this function:
*   - @c #SCREEN_PROPERTY_CONTEXT
*   - @c #SCREEN_PROPERTY_GROUP
*   - @c #SCREEN_PROPERTY_RENDER_BUFFERS
*
*   @param  pix The handle of the pixmap whose property is being queried.
*   @param  pname The name of the property whose value is being queried. The
*           properties available for querying are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param A pointer to a buffer containing the new value(s). This
*           buffer must be of type @c void*.
*
*   @return @c 0 if a query was successful and the value(s) of the property are
*           stored in @c param, or @c -1 if an error occurred (@c errno is set).
*/
int screen_get_pixmap_property_pv(screen_pixmap_t pix, int pname, void **param);

/**
*   @brief Cause a pixmap to join a group
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function is used to add a pixmap to a group.
*
*   @param  pix The handle of the pixmap that is to be joining the group.
*   @param  name A unique string that identifies the group.
*
*   @return @c 0 if the request for the pixmap to join the group was
*           queued for processing, or @c -1 if an error occurred
*           (@c errno is set).
*/
int screen_join_pixmap_group(screen_pixmap_t pix, const char *name);

/**
*   @brief Cause a pixmap to leave a group
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function is used to remove a pixmap from a group.
*
*   @param  pix The handle of the pixmap that is to be leaving the group.
*
*   @return @c 0 if the request for the pixmap to leave the group was
*           queued for processing, or @c -1 if an error occurred
*           (@c errno is set).
*/
int screen_leave_pixmap_group(screen_pixmap_t pix);

/**
*   @brief Create a reference to a pixmap
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   This function creates a reference to a pixmap. This function can be used
*   by libraries to prevent the pixmap or its buffer from disappearing while
*   the library is making use of it. The pixmap and its buffer will not be
*   destroyed until all references have been cleared with
*   @c screen_unref_pixmap(). In the event that a pixmap is destroyed before the
*   reference is cleared, @c screen_unref_pixmap() will cause the pixmap buffer
*   and/or the pixmap to be destroyed.
*
*   @param  pix The handle of the pixmap for which the reference is to be
*           created.
*
*   @return @c 0 if the reference to the specified window was created,
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_ref_pixmap(screen_pixmap_t pix);

/**
*   @brief Set the value of the specified pixmap property of type char
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function sets the value of a pixmap property from a user-provided buffer.
*   You can use this function to set the value of the following properties:
*   - @c #SCREEN_PROPERTY_ID_STRING
*
*   @param  pix handle of the pixmap whose property is being set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  len The maximum number of bytes that can be read from @c param.
*   @param  param A pointer to a buffer containing the new value(s). This
*           buffer must be an array of type @c char with a maximum length of
*           @c len.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_pixmap_property_cv(screen_pixmap_t pix, int pname, int len, const char *param);

/**
*   @brief Set the value of the specified pixmap property of type integer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function sets the value of a pixmap property from a user-provided buffer.
*   You can use this function to set the value of the following properties:
*   - @c #SCREEN_PROPERTY_ALPHA_MODE
*   - @c #SCREEN_PROPERTY_COLOR_SPACE
*   - @c #SCREEN_PROPERTY_FORMAT
*   - @c #SCREEN_PROPERTY_USAGE
*   - @c #SCREEN_PROPERTY_BUFFER_SIZE
*
*   @param  pix handle of the pixmap whose property is being set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param A pointer to a buffer containing the new value(s). This
*           buffer must be of type @c int. @c param may be a single integer or
*           an array of integers depending on the property being set.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_pixmap_property_iv(screen_pixmap_t pix, int pname, const int *param);

/**
*   @brief Set the value of the specified pixmap property of type long long
*          integer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function sets the value of a pixmap property from a user-provided buffer.
*   Currently, there are no pixmap properties that can be set using this
*   function.
*
*   @param  pix handle of the pixmap whose property is being set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param A pointer to a buffer containing the new value(s). This
*           buffer must be of type @c long @c long.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_pixmap_property_llv(screen_pixmap_t pix, int pname, const long long *param);

/**
*   @brief Set the value of the specified pixmap property of type void*

*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function sets the value of a pixmap property from a user-provided buffer.
*   You can use this function to set the value of the following properties:
*   - @c #SCREEN_PROPERTY_CONTEXT
*   - @c #SCREEN_PROPERTY_GROUP
*   - @c #SCREEN_PROPERTY_RENDER_BUFFERS
*
*   @param  pix handle of the pixmap whose property is being set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param A pointer to a buffer containing the new value(s). This
*           buffer must be of type @c void*.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_pixmap_property_pv(screen_pixmap_t pix, int pname, void **param);

/**
*   @brief Remove a reference from a specified pixmap
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   This function removes a reference to a pixmap. If the pixmap and its
*   buffer haven't been destroyed yet, the effect of @c screen_unref_pixmap() is
*   simply to decrease a reference count. If the pixmap or the pixmap buffer
*   was destroyed while still being referenced, @c screen_unref_pixmap() will
*   cause the pixmap and/or its buffer to be destroyed when the reference
*   count reaches zero.
*
*   @param  pix The handle of the pixmap for which the reference is to be
*           removed.
*
*   @return @c 0 if the reference to the specified pixmap was removed,
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_unref_pixmap(screen_pixmap_t pix);
/** @} */   /* end of ingroup screen_pixmaps */

/*
 * Sessions
 */
/**
*   @ingroup screen_sessions
*   @{
*/
/**
*   @brief Create a session of specified type to be associated with a context
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   The @c screen_create_session_type() function creates an input session object to
*   be associated with a context. Applications must use @c screen_destroy_session()
*   when a session is no longer active.
*
*   The following are valid input session types which can be created:
*   - @c #SCREEN_EVENT_KEYBOARD
*   - @c #SCREEN_EVENT_POINTER
*   - @c #SCREEN_EVENT_JOYSTICK
*   - @c #SCREEN_EVENT_GAMEPAD
*   - @c #SCREEN_EVENT_MTOUCH_TOUCH
*   - @c #SCREEN_EVENT_JOG
*
*   @param  pssn A pointer to a @c #screen_session_t where a handle for the new
*           input session can be stored.
*   @param  ctx The handle of the context in which the input session is to be
*           created.
*   @param  type The type of input session to be created.
*
*   @return @c 0 if the input session was created, or @c -1 if an error occurred
*           (@c errno is set).
*/
int screen_create_session_type(screen_session_t *pssn, screen_context_t ctx, int type);

/**
*   @brief Destroy a session
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function destroys a session given a @c #screen_session_t instance.
*   You must destroy each @c #screen_session_t after it is no longer needed.
*
*   @param  ssn The session to be destroyed. The session must have been
*           created with @c screen_create_session_type().
*
*   @return @c 0 if the session was destroyed, or @c -1 if an error
*           occurred (@c errno is set).
*/
int screen_destroy_session(screen_session_t ssn);

/**
*   @brief Retrieve the current value of the specified session property of type
*          char
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function stores the current value of a session property in a
*   user-provided buffer. No more than @c len bytes of the specified type will be
*   written.
*
*   The values of the following properties can be retrieved using this function:
*   - @c #SCREEN_PROPERTY_ID_STRING
*
*   @param  ssn The handle of the session whose property is being queried.
*   @param  pname The name of the property whose value is being queried. The
*           properties available for query are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  len The maximum number of bytes that can be written to @c param.
*   @param  param The buffer where the retrieved value(s) will be stored. This
*           buffer must be an array of type @c char with a maximum length of
*           @c len.
*
*   @return @c 0 if a query was successful and the value(s) of the property are
*           stored in @c param, or @c -1 if an error occurred (@c errno is set).
*/
int screen_get_session_property_cv(screen_session_t ssn, int pname, int len, char *param);

/**
*   @brief Retrieve the current value of the specified session property of type
*          integer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function stores the current value of a session property in a
*   user-provided buffer.
*
*   The values of the following properties can be retrieved using this function:
*   - @c #SCREEN_PROPERTY_DEVICE_COUNT
*   - @c #SCREEN_PROPERTY_ID
*   - @c #SCREEN_PROPERTY_TYPE
*   - @c #SCREEN_PROPERTY_OWNER_PID
*   - @c #SCREEN_PROPERTY_GESTURE_RECOGNITION
*   - @c #SCREEN_PROPERTY_FOCUS
*   - @c #SCREEN_PROPERTY_MODE
*   - @c #SCREEN_PROPERTY_MTOUCH_FOCUS
*   - @c #SCREEN_PROPERTY_PERMISSIONS
*   - @c #SCREEN_PROPERTY_POINTER_FOCUS
*   - @c #SCREEN_PROPERTY_PROTECTION_ENABLE
*   - @c #SCREEN_PROPERTY_SENSITIVITY
*   - @c #SCREEN_PROPERTY_SEQUENCE_ID
*   - @c #SCREEN_PROPERTY_VISIBLE
*   - @c #SCREEN_PROPERTY_ZORDER
*   - @c #SCREEN_PROPERTY_POSITION
*   - @c #SCREEN_PROPERTY_SIZE
*
*   @param  ssn The handle of the session whose property is being queried.
*   @param  pname The name of the property whose value is being queried. The
*           properties available for query are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param The buffer where the retrieved value(s) will be stored. This
*           buffer must be of type @c int. @c param may be a single integer or
*           an array of integers depending on the property being set.
*
*   @return @c 0 if a query was successful and the value(s) of the property are
*           stored in @c param, or @c -1 if an error occurred (@c errno is set).
*/
int screen_get_session_property_iv(screen_session_t ssn, int pname, int *param);

/**
*   @brief Retrieve the current value of the specified session property of type
*          long long integer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function stores the current value of a session property in a
*   user-provided buffer.
*
*   The values of the following properties can be retrieved using this function:
*    - @c #SCREEN_PROPERTY_METRICS
*
*   @param  ssn The handle of the session whose property is being queried.
*   @param  pname The name of the property whose value is being queried. The
*           properties available for query are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param The buffer where the retrieved value(s) will be stored. This
*           buffer must be of type @c long @c long.
*
*   @return @c 0 if a query was successful and the value(s) of the property are
*           stored in @c param, or @c -1 if an error occurred (@c errno is set).
*/
int screen_get_session_property_llv(screen_session_t ssn, int pname, long long *param);

/**
*   @brief Retrieve the current value of the specified session property of type
*          void*
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function stores the current value of a session property in a
*   user-provided buffer.
*
*   The values of the following properties can be retrieved using this function:
*   - @c #SCREEN_PROPERTY_ALTERNATE
*   - @c #SCREEN_PROPERTY_CONTEXT
*   - @c #SCREEN_PROPERTY_BRUSH
*   - @c #SCREEN_PROPERTY_DEVICES
*   - @c #SCREEN_PROPERTY_DISPLAY
*   - @c #SCREEN_PROPERTY_WINDOW
*
*   @param  ssn The handle of the session whose property is being queried.
*   @param  pname The name of the property whose value is being queried. The
*           properties available for query are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param The buffer where the retrieved value(s) will be stored. This
*           buffer must be of type @c void*.
*
*   @return @c 0 if a query was successful and the value(s) of the property are
*           stored in @c param, or @c -1 if an error occurred (@c errno is set).
*/
int screen_get_session_property_pv(screen_session_t ssn, int pname, void **param);

/**
*   @brief Set the value of the specified session property of type char
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function sets the value of a session property from a user-provided buffer.
*   - @c #SCREEN_PROPERTY_ID_STRING
*
*   @param  ssn The handle of the session whose property is being set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  len The maximum number of bytes that can be read from @c param.
*   @param  param A pointer to a buffer containing the new value(s). This
*           buffer must be an array of type @c char with a maximum length of
*           @c len.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_session_property_cv(screen_session_t ssn, int pname, int len, const char *param);

/**
*   @brief Set the value of the specified session property of type integer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function sets the value of a session property from a user-provided buffer.
*   You can use this function to set the value of the following properties:
*   - @c #SCREEN_PROPERTY_GESTURE_RECOGNITION
*   - @c #SCREEN_PROPERTY_MODE
*   - @c #SCREEN_PROPERTY_PERMISSIONS
*   - @c #SCREEN_PROPERTY_POSITION
*   - @c #SCREEN_PROPERTY_SENSITIVITY
*   - @c #SCREEN_PROPERTY_SIZE
*   - @c #SCREEN_PROPERTY_VISIBLE
*   - @c #SCREEN_PROPERTY_ZORDER
*
*   @param  ssn The handle of the session whose property is being set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param A pointer to a buffer containing the new value(s). This
*           buffer must be of type @c int. @c param may be a single integer or
*           an array of integers depending on the property being set.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_session_property_iv(screen_session_t ssn, int pname, const int *param);

/**
*   @brief Set the value of the specified session property of type long long
*          integer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function sets the value of a session property from a user-provided buffer.
*   Currently there are no session properties that can be set using this
*   function.
*
*   @param  ssn The handle of the session whose property is being set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type
*            <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param A pointer to a buffer containing the new value(s). This
*           buffer must be of type @c long @c long.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_session_property_llv(screen_session_t ssn, int pname, const long long *param);

/**
*   @brief Set the value of the specified session property of type void*
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function sets the value of a session property from a user-provided buffer.
*   You can use this function to set the value of the following properties:
*   - @c #SCREEN_PROPERTY_ALTERNATE
*   - @c #SCREEN_PROPERTY_BRUSH
*   - @c #SCREEN_PROPERTY_WINDOW
*
*   @param  ssn The handle of the session whose property is being set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param A pointer to a buffer containing the new value(s). This
*           buffer must be of type @c void*.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_session_property_pv(screen_session_t ssn, int pname, void **param);
/** @} */   /* end of ingroup screen_sessions */

/*
 * Windows
 */
/**
*   @ingroup screen_windows
*   @{
*/
/**
*   @brief Associate an externally allocated buffer with a window
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function can be used by drivers and other middleware components that
*   must allocate their own buffers. The client must ensure that all usage
*   constraints are met when allocating the buffers. Failure to do so may
*   prevent the buffers from being successfully attached, or may result in
*   artifacts and system instability. Calling both
*   @c screen_attach_window_buffers() and @c screen_create_window_buffers()
*   is not permitted.
*
*   @param  win The handle of a window that doesn't already share a buffer with
*           another window, and that doesn't have one or more buffers created
*           or associated to it.
*   @param  count The number of buffers to be attached.
*   @param  buf An array of @c count buffers to be attached that was allocated
*           by the application.
*
*   @return @c 0 if the buffers were successfully attached to the specified
*           window, or @c -1 if an error occurred (@c errno is set).
*/
int screen_attach_window_buffers(screen_window_t win, int count, screen_buffer_t *buf);

/**
*   @brief Create a window that can be used to make graphical content visible
*          on a display
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   This function creates a window object. The window size defaults to full
*   screen when it is created. This is equivalent to calling
*   @c screen_create_window_type() with a type of @c #SCREEN_APPLICATION_WINDOW.
*
*   @param  pwin An address where the function can store the handle to the
*           newly created native window.
*   @param  ctx The connection to the composition manager. This context must
*           have been created with @c screen_create_context().
*
*   @return @c 0 if a new window was created, or @c -1 if an error occurred
*           (@c errno is set).
*/
int screen_create_window(screen_window_t *pwin, screen_context_t ctx);

/**
*   @brief Create a new window of a specified type
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   This function creates a window object of the specified type.
*
*   @param  pwin An address where the function can store the handle to the
*           newly created native window.
*   @param  ctx The connection to the composition manager to be used to create
*           the window. This context must have been created with
*           @c screen_create_context().
*   @param  type The type of window to be created. @c type must be of type
*           Screen_Window_Types.
*
*   @return @c 0 if a new window type was created, or @c -1 if an error occurred
*           (@c errno is set).
*/
int screen_create_window_type(screen_window_t *pwin, screen_context_t ctx, int type);

/**
*   @brief Send a request to the composition manager to add new buffers to a
*          window
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function adds buffers to a window. Windows need at least one
*   buffer in order to be visible. Buffers cannot be created using
*   @c screen_create_window_buffers() if at some point prior, buffers were attached
*   to this window using @c screen_attach_window_buffers(). Buffers are
*   created with the size of @c #SCREEN_PROPERTY_BUFFER_SIZE as set for the
*   window.
*
*   @param  win The handle of the window for which the new buffers must be
*           allocated.
*   @param  count The number of buffers to be created for this window.
*
*   @return @c 0 if new buffers were created for the specified window,
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_create_window_buffers(screen_window_t win, int count);

/**
*   @brief Create a window group that other windows can join
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function creates a window group and assigns it to the specified window.
*   The group is identified by the name string, which must be unique. The
*   request will fail if another group was previously created with the same
*   name.
*
*   Windows can parent only one group. Therefore, @c screen_create_window_group()
*   can be called successfully only once for any given window.
*   Additionally, only windows of certain types can parent a
*   group of windows. Windows with a type of @c #SCREEN_APPLICATION_WINDOW
*   can parent windows of type @c #SCREEN_CHILD_WINDOW and
*   @c #SCREEN_EMBEDDED_WINDOW. Windows with a type of
*   @c #SCREEN_CHILD_WINDOW can also create a group and
*   parent windows of type @c #SCREEN_EMBEDDED_WINDOW.
*
*   Once a group is created, it exists until the window that parents the group
*   is destroyed. When a parent window is destroyed, all children are orphaned
*   and made invisible. Destroying a child has no effect on the group other than
*   removing the window from the group.
*
*   Group owners have privileged access to the windows that they
*   parent. When windows join the group, the parent will receive a
*   #SCREEN_EVENT_CREATE that contains a handle to the child window that can be
*   used by the parent to set properties or send events. Conversely, the parent
*   gets notified when a child window gets destroyed. The parent window is
*   expected to destroy its local copy of the window handle when one of its
*   children is destroyed.
*
*   @param  win The handle of the window for which the group is created. This
*           window must have been created with @c screen_create_window_type() with
*           a type of @c #SCREEN_APPLICATION_WINDOW or @c #SCREEN_CHILD_WINDOW.
*   @param  name A unique string that will be used to identify the window group.
*           This name must be communicated to any window wishing to join the
*           group as a child of @c win. Other than uniqueness, there are no
*           other constraints on this name (for example, lower case and special
*           characters are permitted). If @c name is a @c NULL pointer, then a
*           a string is generated for you with this format:
*           auto-\<pid\>-\<32 alpha-numeric characters\>
*           For example:
*           @code auto-1564694-00007FFF000000370000138A00002567
*           @endcode
*           It is recommended that, unless a static name is explicitly required,
*           you should call this function with @c name as @c NULL so that a
*           unique group name is automatically generated. You can use
*           @c screen_get_window_property_cv() with #SCREEN_PROPERTY_GROUP as
*           the property to retrieve the name of the window group.
*
*   @return @c 0 if request for the new window group was queued,
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_create_window_group(screen_window_t win, const char *name);

/**
*   @brief Destroy a window and free associated resources
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function destroys the window associated with the given window handle.
*   If the window is visible, it is removed from the display. Any resources or
*   buffers created for this window, both locally and by the composition
*   manager, are released.
*
*   The window handle can no longer be used as argument to subsequent
*   screen calls. Buffers that are not created by the composition manager and
*   registered with @c screen_attach_window_buffers() are not freed by this
*   operation.
*
*   The application is responsible for releasing its own external
*   buffers. Any window that shares buffers with the window is also destroyed.
*   @c screen_destroy_window() must be used to free windows that were
*   obtained by querying context or event properties. In this case, the
*   window is not removed from its display and destroyed. Only the local state
*   associated with the external window is released.
*
*   @param  win The handle of the window to be destroyed. This must
*           have been created with @c screen_create_window().
*
*   @return @c 0 if the specified window was destroyed,
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_destroy_window(screen_window_t win);

/**
*   @brief Send a request to the composition manager to destory the buffer of
*          the specified window
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function releases the buffer that was allocated for a window, without
*   destroying the window. If the buffer was created with
*   @c screen_create_window_buffers(), the memory is released and can be used for
*   other window or pixmap buffers. If the buffer was attached using
*   @c screen_attach_window_buffer(), the buffer is destroyed but no memory is
*   actually released. In this case the application is responsible for freeing
*   the memory after calling @c screen_destroy_window_buffer(). Once a window
*   buffer has been destroyed, you can change the format, the usage and the
*   buffer size before creating a new buffer again.
*   The memory that is released by this call is not reserved and can be used for
*   any subsequent buffer allocation by the windowing system.
*
*   @param  win The handle of the window whose buffer(s) you want to destroy.
*
*   @return @c 0 if the memory used by the window buffer was freed,
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_destroy_window_buffers(screen_window_t win);

/**
*   @brief Discard the specified window regions
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function is a hole-punching API. Use this function to specify window
*   regions you want to discard. The regions behave as if they were transparent,
*   or as if there were no transparency on the window. When you call this
*   function, it invalidates any regions you might have defined previously. You
*   can call the function with count set to 0 to remove discarded regions.
*
*   @param  win The handle of the window in which you want to specify regions
*           to discard.
*   @param  count The number of rectangles (retangular regions) you want to
*           discard, specified in the @c rects argument. The value of @c count
*           can be @c 0.
*   @param  rects An array of integers containing the x, y, width, and height
*           coordinates of rectangles that bound areas in the window you want to
*           discard. The @c rects argument must provide at least 4 times @c count
*           integers(quadruples of x, y, width and height).
*
*   @return @c 0 if the request for discarding window regions have been queued,
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_discard_window_regions(screen_window_t win, int count, const int *rects);

/**
*   @brief Retrieve the current value of the specified window property of type
*          char
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function retrieves the value of window property from a user-provided
*   array.
*   The values of the following properties can be queried using this function:
*   - @c #SCREEN_PROPERTY_CLASS
*   - @c #SCREEN_PROPERTY_ID_STRING
*   - @c #SCREEN_PROPERTY_GROUP
*
*   @param  win The handle of the window whose property is being queried.
*   @param  pname The name of the property whose value is being queried. The
*           properties available for querying are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  len The maximum number of bytes that can be written to @c param.
*   @param  param A pointer to a buffer containing the new value(s). This
*           buffer must be an array of type @c char with a maximum length of
*           @c len.
*
*   @return @c 0 if a query was successful and the value(s) of the property are
*           stored in @c param, or @c -1 if an error occurred (@c errno is set).
*/
int screen_get_window_property_cv(screen_window_t win, int pname, int len, char *param);

/**
*   @brief Retrieve the current value of the specified window property of type
*          integer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function retrieves the value of window property from a user-provided
*   array.
*   The values of the following properties can be queried using this function:
*   - @c #SCREEN_PROPERTY_ALPHA_MODE
*   - @c #SCREEN_PROPERTY_BUFFER_COUNT
*   - @c #SCREEN_PROPERTY_COLOR_SPACE
*   - @c #SCREEN_PROPERTY_FORMAT
*   - @c #SCREEN_PROPERTY_OWNER_PID
*   - @c #SCREEN_PROPERTY_RENDER_BUFFER_COUNT
*   - @c #SCREEN_PROPERTY_SCALE_FACTOR
*   - @c #SCREEN_PROPERTY_SIZE
*   - @c #SCREEN_PROPERTY_SWAP_INTERVAL
*   - @c #SCREEN_PROPERTY_USAGE
*   - @c #SCREEN_PROPERTY_BRIGHTNESS
*   - @c #SCREEN_PROPERTY_CBABC_MODE
*   - @c #SCREEN_PROPERTY_CONTRAST
*   - @c #SCREEN_PROPERTY_DEBUG
*   - @c #SCREEN_PROPERTY_FLIP
*   - @c #SCREEN_PROPERTY_FLOATING
*   - @c #SCREEN_PROPERTY_GLOBAL_ALPHA
*   - @c #SCREEN_PROPERTY_HUE
*   - @c #SCREEN_PROPERTY_IDLE_MODE
*   - @c #SCREEN_PROPERTY_FOCUS
*   - @c #SCREEN_PROPERTY_MIRROR
*   - @c #SCREEN_PROPERTY_PIPELINE
*   - @c #SCREEN_PROPERTY_PROTECTION_ENABLE
*   - @c #SCREEN_PROPERTY_ROTATION
*   - @c #SCREEN_PROPERTY_SATURATION
*   - @c #SCREEN_PROPERTY_SCALE_QUALITY
*   - @c #SCREEN_PROPERTY_SELF_LAYOUT
*   - @c #SCREEN_PROPERTY_SENSITIVITY
*   - @c #SCREEN_PROPERTY_STATIC
*   - @c #SCREEN_PROPERTY_TRANSPARENCY
*   - @c #SCREEN_PROPERTY_TYPE
*   - @c #SCREEN_PROPERTY_VISIBLE
*   - @c #SCREEN_PROPERTY_ZORDER
*   - @c #SCREEN_PROPERTY_BUFFER_SIZE
*   - @c #SCREEN_PROPERTY_CLIP_POSITION
*   - @c #SCREEN_PROPERTY_CLIP_SIZE
*   - @c #SCREEN_PROPERTY_POSITION
*   - @c #SCREEN_PROPERTY_SOURCE_CLIP_POSITION
*   - @c #SCREEN_PROPERTY_SOURCE_CLIP_SIZE
*   - @c #SCREEN_PROPERTY_SOURCE_POSITION
*   - @c #SCREEN_PROPERTY_SOURCE_SIZE
*   - @c #SCREEN_PROPERTY_VIEWPORT_POSITION
*   - @c #SCREEN_PROPERTY_VIEWPORT_SIZE
*   - @c #SCREEN_PROPERTY_METRIC_COUNT
*   - @c #SCREEN_PROPERTY_TRANSFORM
*   - @c #SCREEN_PROPERTY_REFERENCE_COLOR
*   - @c #SCREEN_PROPERTY_PERMISSIONS
*
*   @param  win The handle of the window whose property is being queried.
*   @param  pname The name of the property whose value is being queried. The
*           properties available for querying are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param A pointer to a buffer containing the new value(s). This
*           buffer must be of type @c int. @c param may be a single integer or
*           an array of integers depending on the property being set.
*
*   @return @c 0 if a query was successful and the value(s) of the property are
*           stored in @c param, or @c -1 if an error occurred (@c errno is set).
*/
int screen_get_window_property_iv(screen_window_t win, int pname, int *param);

/**
*   @brief Retrieve the current value of the specified window property of type
*          long long integer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function retrieves the value of a window property from a user-provided
*   array.
*   The values of the following properties can be queried using this function:
*    - @c #SCREEN_PROPERTY_METRICS
*
*   @param  win handle of the window whose property is being queried.
*   @param  pname The name of the property whose value is being queried. The
*           properties available for querying are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param A pointer to a buffer containing the new value(s). This
*           buffer must be of type @c long @c long.
*
*   @return @c 0 if a query was successful and the value(s) of the property are
*           stored in @c param, or @c -1 if an error occurred (@c errno is set).
*/
int screen_get_window_property_llv(screen_window_t win, int pname, long long *param);

/**
*   @brief Retrieve the current value of the specified window property of type
*          void*
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function retrieves the value of a window property from a user-provided
*   array.
*   The values of the following properties can be queried using this function:
*   - @c #SCREEN_PROPERTY_ALTERNATE
*   - @c #SCREEN_PROPERTY_CONTEXT
*   - @c #SCREEN_PROPERTY_DISPLAY
*   - @c #SCREEN_PROPERTY_FRONT_BUFFER
*   - @c #SCREEN_PROPERTY_GROUP
*   - @c #SCREEN_PROPERTY_RENDER_BUFFERS
*   - @c #SCREEN_PROPERTY_USER_HANDLE
*   - @c #SCREEN_PROPERTY_BRUSH
*
*   @param  win handle of the window whose property is being queried.
*   @param  pname The name of the property whose value is being queried. The
*           properties available for querying are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param A pointer to a buffer containing the new value(s). This
*           buffer must be of type @c void*.
*
*   @return @c 0 if a query was successful and the value(s) of the property are
*           stored in @c param, or @c -1 if an error occurred (@c errno is set).
*/
int screen_get_window_property_pv(screen_window_t win, int pname, void **param);

/**
*   @brief Cause a window to join a window group
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function is used to add a window to a group. Child and embedded windows
*   will remain invisible until they're properly parented.
*
*   Until the window joins a group, a window of any type behaves like an
*   application window. The window's positioning and visibility are not relative
*   to any other window on the display. In order to join a group parented by an
*   application window, a window must have a type of @c #SCREEN_CHILD_WINDOW or
*   @c #SCREEN_EMBEDDED_WINDOW. Windows with a type of @c #SCREEN_EMBEDDED_WINDOW
*   can join only groups parented by windows of type @c #SCREEN_CHILD_WINDOW.
*
*   Once a window successfully joins a group, its position on the screen will be
*   relative to the parent. The type of the window determines exactly how the
*   window will be positioned. Child windows are positioned relative to their
*   parent (i.e., their window position is added to the parent's window position.
*   Embedded windows are positioned relative to the source viewport of the
*   parent.
*
*   Windows in a group inherit the visibility and the global transparency
*   of their parent.
*
*   @param  win The handle for the window that is to join the group. This window
*           must have been created with @c screen_create_window_type() with a type
*           of either @c #SCREEN_CHILD_WINDOW or @c #SCREEN_EMBEDDED_WINDOW.
*   @param  name A unique string that identifies the group. This string must
*           have been communicated down from the parent window.
*
*   @return @c 0 if the request for the window joining the specified group was
*           queued, or @c -1 if an error occurred (@c errno is set).
*/
int screen_join_window_group(screen_window_t win, const char *name);

/**
*   @brief Cause a window to leave a window group
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function removes a window from a window group.
*
*   @param  win The handle for the window that is to leave the group. This window
*           must have been created with @c screen_create_window_type() with a type
*           of either @c #SCREEN_CHILD_WINDOW or @c #SCREEN_EMBEDDED_WINDOW.
*
*   @return @c 0 if the request for the window leaving its group was
*           queued, or @c -1 if an error occurred (@c errno is set).
*/
int screen_leave_window_group(screen_window_t win);

/**
*   @brief Make window content updates visible on the display
*
*   <b>Function Type:</b>  <a href="manual/rscreen_apply_execution.xml">Apply Execution</a>
*
*   This function makes some pixels in a rendering buffer visible. The pixels to
*   be posted are defined by the dirty rectangles contained in the
*   @c dirty_rects argument.
*
*   In addition to the area(s) defined by @c dirty_rects, Screen may update
*   all the pixels in the buffer. Screen may also retrieve data from the buffer
*   at times other than when @c screen_post_window() is called (e.g., when the
*   contents or properties of overlapping windows are updated, or when the window is
*   autonomous and so the entire buffer will be continuously read from by
*   the display hardware until another buffer is posted to replace it).
*   Your application must ensure that the entire content of a window buffer is
*   suitable for display at all times until a new buffer is posted to the window
*   and the content of the display has been updated from the new buffer.
*
*   @c screen_post_window() returns immediately if the render buffers are available
*   and if @c #SCREEN_WAIT_IDLE is not set. The use of multiple threads or
*   application buffer management schemes to render at the full
*   display frame rate are not necessary because unlike equivalent calls in
*   other graphics systems, @c screen_post_window() does not always block.
*
*   If @c #SCREEN_WAIT_IDLE is set in the flags, the function will return only
*   when the contents of the display have been updated. Note that a window will
*   not be made visible until @c screen_post_window() has been called at least
*   once.
*
*   The function may cause the @c #SCREEN_PROPERTY_RENDER_BUFFERS of the window
*   to change. If your application uses multiple threads, don't have this property
*   read by other threads in the application while one thread is running
*   @c screen_post_window() on the same window. If this happens, the
*   property may reflect out-of-date information that can lead to animation
*   artifacts. The presentation of new content may result in a copy or a buffer
*   flip, depending on how the composited windowing system chooses to perform
*   the operation.
*
*   If the window is currently locked, posting updates has the effect of flushing
*   all pending property changes and blocks until all other locked windows have
*   released the lock or posted updates of their own. In this case, the window
*   remains locked when @c screen_post_window() returns, and any subsequent
*   property change is delayed until the window lock is released or another
*   frame is posted.
*
*   If count is @c 0, the buffer is discarded and a new set of
*   rendering buffers is returned. The current front buffer remains unchanged
*   and the contents of the screen will not be updated.
*
*   @param  win The handle for the window whose content has changed.
*   @param  buf The rendering buffer of the window that contains the changes
*           needed to be made visible.
*   @param  count The number of rectangles provided in the @c dirty_rects
*           argument.
*   @param  dirty_rects An array of integers containing the x1, y1, x2, and y2
*           coordinates of a rectangle that bounds the area of the rendering
*           buffer that has changed since the last posting of the window. The
*           @c dirty_rects argument must provide at least @c count * 4 integers.
*   @param  flags A bitmask that can be used to alter the default posting
*           behaviour. Valid flags are of type Screen_Flushing_Types.
*
*   @return @c 0 if the area of the rendering buffer that is marked dirty has
*           updated on the screen and a new set of rendering buffers was
*           returned (this new set of buffers can be used for the next updates),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_post_window(screen_window_t win, screen_buffer_t buf, int count, const int *dirty_rects, int flags);

/**
*   @brief Take a screenshot of the window and stores the resulting image in
*          the specified buffer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_apply_execution.xml">Apply Execution</a>
*
*   This function takes a screenshot of a window and stores the result in a
*   user-provided buffer. The buffer can be a pixmap buffer or a window buffer.
*   The buffer must have been created with the usage flag @c #SCREEN_USAGE_NATIVE
*   in order for the operation to succeed. The call blocks until the operation
*   is completed. If @c count is 0 and @c read_rects is NULL, the entire window
*   is grabbed. Otherwise, @c read_rects must point to @c count * 4 integers
*   defining rectangles in screen coordinates that need to be grabbed. Note that
*   the buffer size does not have to match the window size. Scaling will be
*   applied to make the screenshot fit into the buffer provided.
*
*   @param  win The handle of the window that is the target of the screenshot.
*   @param  buf The buffer where the pixel data will be copied to.
*   @param  count The number of rectables supplied in the @c read_rects
*           argument.
*   @param  save_rects A pointer to (@c count * 4) integers that define the
*           areas of the window that need to be grabbed for the screenshot.
*   @param  flags The mutex flags; must be set to 0.
*
*   @return @c 0 if the operation was successful and the pixels are written to
*           @c buf, or @c -1 if an error occurred (@c errno is set).
*/
int screen_read_window(screen_window_t win, screen_buffer_t buf, int count, const int *save_rects, int flags);

/**
*   @brief Create a reference to a window
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   This function creates a reference to a window. This function can be used by
*   window managers and group parents to prevent a window from disappearing,
*   even when the process that originally created the window terminates
*   abnormally. If this happens, ownership of the window is transferred to the
*   window manager or group parent. The restrictions imposed on buffers still
*   exist. The contents of the buffers can't be changed. The buffers cannot be
*   destroyed until the window is unreferenced. When the original process owner
*   is no longer a client of the windowing system, the window will be destroyed
*   when @c screen_destroy_window() is called by the reference owner.
*
*   @param  win The handle of the window for which the reference is to be
*           created.
*
*   @return @c 0 if a reference to the specified window was created,
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_ref_window(screen_window_t win);

/**
*   @brief Set the value of the specified window property of type char
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function sets the value of a window property from a user-provided buffer.
*   You can use this function to set the value of the following properties:
*   - @c #SCREEN_PROPERTY_CLASS
*   - @c #SCREEN_PROPERTY_ID_STRING
*
*   @param  win handle of the window whose property is being set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  len The maximum number of bytes that can be read from @c param.
*   @param  param A pointer to a buffer containing the new value(s). This
*           buffer must be an array of type @c char with a maximum length of
*           @c len.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_window_property_cv(screen_window_t win, int pname, int len, const char *param);

/**
*   @brief Set the value of the specified window property of type integer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function sets the value of a window property from a user-provided buffer.
*   You can use this function to set the value of the following properties:
*   - @c #SCREEN_PROPERTY_SCALE_FACTOR
*   - @c #SCREEN_PROPERTY_ALPHA_MODE
*   - @c #SCREEN_PROPERTY_BRIGHTNESS
*   - @c #SCREEN_PROPERTY_CBABC_MODE
*   - @c #SCREEN_PROPERTY_COLOR
*   - @c #SCREEN_PROPERTY_COLOR_SPACE
*   - @c #SCREEN_PROPERTY_CONTRAST
*   - @c #SCREEN_PROPERTY_DEBUG
*   - @c #SCREEN_PROPERTY_FLIP
*   - @c #SCREEN_PROPERTY_FLOATING
*   - @c #SCREEN_PROPERTY_GLOBAL_ALPHA
*   - @c #SCREEN_PROPERTY_HUE
*   - @c #SCREEN_PROPERTY_IDLE_MODE
*   - @c #SCREEN_PROPERTY_MIRROR
*   - @c #SCREEN_PROPERTY_PIPELINE
*   - @c #SCREEN_PROPERTY_PROTECTION_ENABLE
*   - @c #SCREEN_PROPERTY_ROTATION
*   - @c #SCREEN_PROPERTY_SATURATION
*   - @c #SCREEN_PROPERTY_SCALE_QUALITY
*   - @c #SCREEN_PROPERTY_SELF_LAYOUT
*   - @c #SCREEN_PROPERTY_SENSITIVITY
*   - @c #SCREEN_PROPERTY_STATIC
*   - @c #SCREEN_PROPERTY_SWAP_INTERVAL
*   - @c #SCREEN_PROPERTY_TRANSPARENCY
*   - @c #SCREEN_PROPERTY_VISIBLE
*   - @c #SCREEN_PROPERTY_ZORDER
*   - @c #SCREEN_PROPERTY_BUFFER_SIZE
*   - @c #SCREEN_PROPERTY_FORMAT
*   - @c #SCREEN_PROPERTY_USAGE
*   - @c #SCREEN_PROPERTY_CLIP_POSITION
*   - @c #SCREEN_PROPERTY_CLIP_SIZE
*   - @c #SCREEN_PROPERTY_POSITION
*   - @c #SCREEN_PROPERTY_SIZE
*   - @c #SCREEN_PROPERTY_SOURCE_CLIP_POSITION
*   - @c #SCREEN_PROPERTY_SOURCE_CLIP_SIZE
*   - @c #SCREEN_PROPERTY_SOURCE_POSITION
*   - @c #SCREEN_PROPERTY_SOURCE_SIZE
*   - @c #SCREEN_PROPERTY_VIEWPORT_POSITION
*   - @c #SCREEN_PROPERTY_VIEWPORT_SIZE
*   - @c #SCREEN_PROPERTY_REFERENCE_COLOR
*   - @c #SCREEN_PROPERTY_PERMISSIONS
*
*   @param  win handle of the window whose property is being set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param A pointer to a buffer containing the new value(s). This
*           buffer must be of type @c int. @c param may be a single integer or
*           an array of integers depending on the property being set.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_window_property_iv(screen_window_t win, int pname, const int *param);

/**
*   @brief Set the value of the specified window property of type long long
*          integer
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function sets the value of a window property from a user-provided buffer.
*   You can use this function to set the value of the following properties:
*   - @c #SCREEN_PROPERTY_TIMESTAMP:
*     - Note that when the specified value for this property is @c NULL,
*       screen automatically calcuates and sets this property to the current
*       time. Screen uses the realtime clock and not the monotonic clock when
*       calculating the timestamp.
*
*   @param  win handle of the window whose property is being set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param A pointer to a buffer containing the new value(s). This
*           buffer must be of type @c long @c long.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_window_property_llv(screen_window_t win, int pname, const long long *param);

/**
*   @brief Set the value of the specified window property of type void*
*
*   <b>Function Type:</b>  <a href="manual/rscreen_delayed_execution.xml">Delayed Execution</a>
*
*   This function sets the value of a window property from a user-provided buffer.
*   You can use this function to set the value of the following properties:
*   - @c #SCREEN_PROPERTY_ALTERNATE
*   - @c #SCREEN_PROPERTY_DISPLAY
*   - @c #SCREEN_PROPERTY_USER_HANDLE
*   - @c #SCREEN_PROPERTY_BRUSH
*
*   @param  win handle of the window whose property is being set.
*   @param  pname The name of the property whose value is being set. The
*           properties that you can set are of type
*           <a href="screen_8h_1Screen_Property_Types.xml">Screen property types</a>.
*   @param  param A pointer to a buffer containing the new value(s). This
*           buffer must be of type @c void*.
*
*   @return @c 0 if the value(s) of the property was set to new value(s),
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_set_window_property_pv(screen_window_t win, int pname, void **param);

/**
*   @brief Cause a window to share buffers which have been created for or
*          attached to another window
*
*   <b>Function Type:</b>  <a href="manual/rscreen_flushing_execution.xml">Flushing Execution</a>
*
*   This function is used when a window needs to share the same buffers created
*   for, or attached to, another window. For this operation to be successful,
*   the window that is the owner of the buffer(s) to be shared must have at
*   least one buffer that was created with @c screen_create_window_buffers() or
*   attached with @c screen_attach_window_buffer(). Buffers cannot be created or
*   attached to any window that is sharing the buffers owned by another window.
*   Updates can only be posted using the window that is the owner of the buffers
*   (i.e. the window whose handle is identified as @c share). Any window that is
*   sharing buffers with another window is orphaned from the buffers and made
*   invisible when the window who owns the buffer(s) is destroyed. At this time,
*   that status of each orphaned window is such that a new buffer can be created
*   for it, or @c screen_share_window_buffers() can be called again. You can use the
*   @c screen_share_window_buffers() function to improve performance by reducing
*   the amount of blending on the screen. For example, a window might be
*   entirely transparent except for a watermark that needs to be blended in a
*   corner. Blending the entire window is costly and can be avoided by setting
*   the transparency of this window to @c #SCREEN_TRANSPARENCY_DISCARD. To keep the
*   watermark visible, another window can be created and made to share buffers
*   with the main window. This way, most of the window is discarded and a much
*   smaller area is actually blended. Any window property, such as
*   @c #SCREEN_PROPERTY_FORMAT, @c #SCREEN_PROPERTY_USAGE, and
*   @c #SCREEN_PROPERTY_BUFFER_SIZE, which was set prior to calling
*   @c screen_share_window_buffers(), is ignored and reset to the values of the
*   parent window.
*
*   @param  win The handle of the window that will be sharing the buffer(s) owned
*           by another window.
*   @param  share The handle of the window whose buffer(s) is to be shared.
*
*   @return @c 0 if the windows are sharing buffers,
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_share_window_buffers(screen_window_t win, screen_window_t share);

/**
*   @brief Relinquish input focus to another window
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   This function yields input focus to another window. The window that will
*   receive focus is not known by the caller. The focus is calculated by
*   adding the specified offset to the caller's tab position. The window with
*   a tab position closest to this reference value will be chosen. The @c type
*   argument can be used to restrict the operation to certain events, or
*   types of window. The @c flags can be used to control aspects such as
*   wrapping modes.
*
*   @param  win The handle of the window that wishes to relinquish its focus.
*           Calling this function when the specified window does not have
*           input focus may still generate some results. The window might
*           be part of a group of windows, and the focus within the group
*           could be changed as a result.
*   @param  off A pointer to three integers, specifying an x, y, and z
*           translation to be applied when determining where the focus should
*           go. The translation can be across, or up/down, but not both.
*           That means either z is non-zero or x and/or y may be non-zeri.
*   @param  type The type of focus that should be relinquished. A value of
*           @c #SCREEN_EVENT_NONE will cause everything to be tabbed. A value
*           of @c #SCREEN_EVENT_GAMEPAD, or @c #SCREEN_EVENT_JOG, or
*           @c #SCREEN_EVENT_JOYSTICK, or @c #SCREEN_EVENT_KEYBOARD, will
*           case focus changes for that type of event only. Events of type
*           @c #SCREEN_EVENT_POINTER and @c #SCREEN_EVENT_MTOUCH_TOUCH are not
*           focus-based, and therefore those types are not acceptable values
*   @param  flags Ignored for now. Pass 0.
*
*   @return @c 0 if the operation was successful,
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_tab_focus(screen_window_t win, const int *off, int type, int flags);

/**
*   @brief Remove a reference from a specified window
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   This function removes a reference to a window. When a window is being referenced,
*   its buffers cannot be destroyed until all references to that window have been
*   removed.
*
*   @param  win The handle of the window for which the reference is to be
*           removed.
*
*   @return @c 0 if a reference to the specified window was removed,
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_unref_window(screen_window_t win);


/**
*   @brief Add a wait for a post on a window
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   This call blocks until there is a post event for the window you are waiting on.
*   This function is typically used in conjunction with @c screen_share_display_buffers()
*   and/or @c screen_share_window_buffers().
*
*   @param  win The handle for the window whose post you are waiting on.
*   @param  flags A bitmask that can be used to alter the default posting
*           behaviour. Valid flags are of type
*           <a href="screen_8h_1Screen_Flushing_Types.xml">Screen flushing types</a>.
*
*   @return @c 0 if a wait for a post on the specified window was added,
*           or @c -1 if an error occurred (@c errno is set).
*/
int screen_wait_post(screen_window_t win, int flags);
/** @} */   /* end of ingroup screen_windows */

/*
 * Debugging
 */
/**
*   @ingroup screen_debugging
*   @{
*/
/**
*   @brief Print a screen packet to a specified file
*
*   <b>Function Type:</b>  <a href="manual/rscreen_immediate_execution.xml">Immediate Execution</a>
*
*   This function prints out the information relevant to the specified packet
*   to a specified file.
*
*   @param  type The type of packet to be printed. The packet must be of type
*            Screen_Packet_Types.
*   @param  packet The address of the packet to be printed.
*   @param  fd The file object where the packet is to be printed to.
*
*   @return @c 0 if the operation was successful, or @c -1 if an error occurred
*           (@c errno is set).
*/
int screen_print_packet(int type, void *packet, FILE *fd);
/** @} */   /* end of ingroup screen_debugging */

__END_DECLS

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/trunk/lib/screen/public/screen/screen.h $ $REV$")
#endif

#endif /* _SCREEN_SCREEN_H_ */
