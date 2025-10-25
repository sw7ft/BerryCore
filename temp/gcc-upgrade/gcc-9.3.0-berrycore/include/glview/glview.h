/*
 * Research In Motion Limited. Copyright (C) 2012.
 * Research In Motion Limited. All rights reserved.
 */

/**
 * @file glview.h
 *
 * @brief The glview library allows you to more easily develop apps with
 *        OpenGL ES 1.1 and  OpenGL ES 2.0
 *
 * This header file provides all the functions used by libglview. The purpose
 * of this library is to simplify development when you want to use
 * OpenGL ES 1.1 and OpenGL ES 2.0 for rendering graphics in apps.
 */

#ifndef _GLVIEW_GLVIEW_H_INCLUDED
#define _GLVIEW_GLVIEW_H_INCLUDED

#include <bps/bps.h>
#include <sys/platform.h>

/**
 * The version of the library. The version number is determined as follows:
 * (Major * 1000000) + (Minor * 1000) + Patch
 *
 * @sa glview_get_version()
 */
#define GLVIEW_VERSION             (1001000)

/**
 * The string version of the library.
 *
 * @see GLVIEW_VERSION
 */
#define GLVIEW_VERSION_STRING      "1.1.0"

/**
 * A return code that indicates that a function completed successfully.
 */
#define GLVIEW_SUCCESS (0)

/**
 * A return code that indicates that a function did not complete successfully.
 * Generally, check @c errno for a reason.
 */
#define GLVIEW_FAILURE (-1)

/**
 * @brief OpenGL versions
 * An enumeration that indicates the version of OpenGL ES to use.
 */
typedef enum {
    GLVIEW_API_OPENGLES_11              = 0,
    GLVIEW_API_OPENGLES_20              = 1
} glview_api_t;

/**
 * @brief Minimum number of samples required in multisample buffers
 */
typedef enum {
    GLVIEW_MULTISAMPLES_0               = 0,
    GLVIEW_MULTISAMPLES_1X              = 1,
    GLVIEW_MULTISAMPLES_2X              = 2,
    GLVIEW_MULTISAMPLES_4X              = 4
} glview_multisamples_t;

/**
 * @cond HIDDEN
 */

#ifndef GLVIEW_API
#define GLVIEW_API
#endif

__BEGIN_DECLS

/**
 * @endcond
 */

/**
 * @brief The options struct used for initialization with greater control over
 * graphics setup.
 *
 * @see glview_initialize_v2()
 *
 * @since 1.1
 */
typedef struct glview_options_t glview_options_t;

/**
 * @brief The callback that is invoked prior to entering the execution loop.
 *
 * @details The initialize_callback is fired from within the @c
 *          glview_loop() function. Prior to executing this callback,
 *          glview will have already completed initializing the graphics stack.
 *          Events are not processed until after this call returns.
 *
 * @param callback_data The callback_data provided by calling the @c
 *                      glview_set_callback_data() function.
 *
 * @see glview_register_initialize_callback()
 *
 * @since 1.0
 */
typedef void(*initialize_callback)(void *callback_data);

/**
 * @brief The callback that is invoked when the app is put into the background
 *
 * @details An app is put into the background whenever it no longer occupies the
 *          entire screen. An app is put into the background when:
 *          - the user puts the app into a thumbnail
 *          - the user switches to another app
 *          - an idle timeout occurs causing the device to go into standby mode
 *
 * @param callback_data The callback_data provided by calling the @c
 *                      glview_set_callback_data() function.
 *
 * @see glview_register_background_callback()
 *
 * @since 1.0
 */
typedef void(*background_callback)(void *callback_data);

/**
 * @brief The callback that is invoked when the app is put into the foreground
 *
 * @details An app is put into the foreground whenever it goes fullscreen. An
 *          app is put into the foreground when:
 *          - the user switches to the app
 *          - the device wakes up after it has previously gone into standby mode
 *            with the app in the foreground
 *
 * @param callback_data The callback_data provided by calling the @c
 *                      glview_set_callback_data() function.
 *
 * @see glview_register_foreground_callback()
 *
 * @since 1.0
 */
typedef void(*foreground_callback)(void *callback_data);

/**
 * @brief The callback that is invoked when an orientation change occurs that
 *        the app must respond to
 *
 * @details The application descriptor file (bar-descriptor.xml) specifies the
 *          orientation behavior for an app. If the behavior is set to @c
 *          default or @c auto-orient, then any registered resize_callback will
 *          be invoked whenever the device is turned from landscape to portrait
 *          or vice-versa. Turning the device 180 degrees does not result
 *          in executing the @c resize_callback.
 *
 * @param width The new width of the surface.
 * @param height The new height of the surface.
 *
 * @param callback_data The callback_data provided by calling the @c
 *                      glview_set_callback_data() function.
 *
 * @see glview_register_resize_callback()
 *
 * @since 1.0
 */
typedef void(*resize_callback)(unsigned int width, unsigned int height, void *callback_data);

/**
 * @brief The callback that is invoked when the app receives an event
 *
 * @details This callback is invoked for every event read from the application's
 *          event queue. Processing events occurs during each iteration of the
 *          @c glview_loop() execution loop. Each event popped from the queue
 *          is passed into the event_callback.
 *
 * @param event The event that was popped off the app's event queue. The event
 *              is loaned out to the application for the duration of the
 *              callback. Using the event after the callback is completed will
 *              result in unspecified behavior.
 *
 * @param domain The same value that would be returned by calling the @c
 *               bps_event_get_domain(event) function.
 *
 * @param code The per-domain code. This is the same value that would be
 *             returned by calling the @c bps_event_get_code(event) function.
 *
 * @param callback_data The callback_data provided by calling the @c
 *                      glview_set_callback_data() function.
 *
 * @see glview_register_event_callback()
 *
 * @since 1.0
 */
typedef void(*event_callback)(bps_event_t *event, int domain, int code, void *callback_data);

/**
 * @brief The callback that is invoked every time glview is about to display
 * a frame.
 *
 * @details The frame_callback is invoked within the @c glview_loop() function
 *          every time the application is expected to draw a single frame. By
 *          default this occurs 60 times a second.
 *
 *          The callback will not be invoked if the app is no longer expected to
 *          draw a frame. This can occur if the app has been minimized, or
 *          is hidden in some way (by the user's action, or on idle timeout). An
 *          app can still draw during this time (for example, to show a pause
 *          screen) by calling the @c glview_display_once() function.
 *
 * @param callback_data The callback_data provided by calling the @c
 *                      glview_set_callback_data() function.
 *
 * @see glview_register_frame_callback()
 * @see glview_initialize()
 *
 * @since 1.0
 */
typedef void(*frame_callback)(void *callback_data);

/**
 * @brief The callback that is executed on a call to @c glview_display_once().
 *
 * @details This callback is provided as a parameter to the @c
 *           glview_display_once() function and will be called immediately from
 *           within that function call.
 *
 * @param callback_data The callback_data provided by calling the @c
 *                      glview_set_callback_data() function.
 *
 * @see glview_display_once()
 *
 * @since 1.0
 */
typedef void(*display_once_callback)(void *callback_data);

/**
 * @brief The callback that is fired once the execution loop is exited, but
 *        before glview is destroyed.
 *
 * @details The @c finalize_callback function is invoked within the
 *          glview_loop() function after the application is given an exit event
 *          but before the graphic stack is destroyed. Once the @c
 *          finalize_callback function returns, the graphic stack will be taken
 *          down and glview will be destroyed.
 *
 * @param callback_data The callback_data provided by calling the @c
 *                      glview_set_callback_data() function.
 
 * @see glview_register_finalize_callback()
 *
 * @since 1.0
 */
typedef void(*finalize_callback)(void *callback_data);

/**
 * @brief Retrieve the version of glview
 * @details The @c glview_get_version() function retrieves the version of the
 *          glview library that your application is using.
 *
 * @return The version of the glview library using the scheme described for @c
 *         GLVIEW_VERSION.
 *
 * @see GLVIEW_VERSION
 *
 * @since 1.0
 */
GLVIEW_API int glview_get_version(void);

/**
 * @brief Initialize glview for use
 * @details This call must be made prior to calling any other glview function.
 *          After initialization callbacks can be registered to hook into
 *          various phases of the execution loop. Call the @c glview_loop()
 *          function in your app to start the glview execution loop.
 *
 * @param api The version of OpenGL ES the app intends to use.
 *
 * @param callback The callback that is fired to draw the frame. This
 *                       callback is mandatory, and cannot be @c NULL.
 *
 * @return @c GLVIEW_SUCCESS upon success, @c GLVIEW_FAILURE otherwise, with
 *         errno set to one of the following:
 *         - @c EPERM: glview has already been initialized.
 *         - @c EFAULT: callback is @c NULL.
 *         - @c ENOMEM: out of memory.
 *
 * @since 1.0
 */
GLVIEW_API int glview_initialize(glview_api_t api, frame_callback callback);

/**
 * @brief Initialize glview with options
 * @details This call must be made prior to calling any other glview function.
 *          After initialization callbacks can be registered to hook into
 *          various phases of the execution loop. Call the @c glview_loop()
 *          function in your app to start the glview execution loop.
 *
 * @param api The version of OpenGL ES the app intends to use.
 *
 * @param callback The callback that is fired to draw the frame. This
 *                 callback is mandatory, and cannot be @c NULL.
 *
 * @param options A set of options to use when initializing glview.  This
 *                parameter can be NULL.  In which case, all default options
 *                will be chosen.
 *
 * @return @c GLVIEW_SUCCESS upon success, @c GLVIEW_FAILURE otherwise, with
 *         errno set to one of the following:
 *         - @c EPERM: glview has already been initialized.
 *         - @c EFAULT: callback is @c NULL.
 *         - @c ENOMEM: out of memory.
 *
 * @see glview_options_create()
 *
 * @since 1.1
 */
GLVIEW_API int glview_initialize_v2(glview_api_t api, frame_callback callback, glview_options_t *options);

/**
 * @brief Create an options handle for use with @c glview_initialize_v2().
 *
 * @details The options handle is used to get/set various glview initialization
 *          settings.  After calling @c glview_initialize_v2(), the user can
 *          destroy the options handle by calling @c glview_options_destroy().
 *
 * @param options This will contain the options handle to use in subsequent calls.
 * 
 * @return @c GLVIEW_SUCCESS upon success, with options pointing to a valid handle.
 *         @c GLVIEW_FAILURE if an error occurred, errno will be set to one of:
 *         - @c EFAULT: options is @c NULL.
 *         - @c ENOMEM: no memory for allocating the handle.
 *         On failure, options will not point to a valid handle.
 *
 * @see glview_options_destroy()
 * @see glview_initialize_v2()
 *
 * @since 1.1
 */
GLVIEW_API int glview_options_create(glview_options_t **options);

/**
 * @brief Destroys an options handle.
 *
 * @details After options are used to initialize glview via @c
 *          glview_initialize_v2().  The options handle is no longer needed and
 *          should be destroyed to prevent any leaks.
 *
 * @param options A valid options handle that was created by @c glview_options_create().
 *
 * @return @c GLVIEW_SUCCESS
 *
 * @since 1.1
 */
GLVIEW_API int glview_options_destroy(glview_options_t *options);

/**
 * @brief Set the minimum number of samples for the multisample buffers
 *
 * @details This function will set the minimum number of samples for the
 *          multisample buffers.  The default is GLVIEW_MULTISAMPLES_0.
 *
 * @param options A valid options handle created by @c glview_options_create().
 *
 * @param multisamples One of @c glview_multisamples_t.
 *
 * @return @c GLVIEW_SUCCESS with the multisamples option set to the passed in value.
 *         @c GLVIEW_FAILURE in the event of an error.  Errno will then be set
 *         to one of:
 *         - @c EINVAL: @c multisamples was not a valid value.
 *         - @c EFAULT: @c options was @c NULL.
 *
 * @since 1.1
 */
GLVIEW_API int glview_options_set_multisamples(glview_options_t *options, glview_multisamples_t multisamples);

/**
 * @brief Get the requested minimum number of samples for the multisample
 *        buffers
 *
 * @details This function will get the requested minimum number of samples for
 *          the multisample buffers.  The default is GLVIEW_MULTISAMPLES_0.
 *
 * @param options A valid options handle created by @c glview_options_create().
 *
 * @param multisamples The result will be placed here.  Should not be @c NULL.
 *
 * @return @c GLVIEW_SUCCESS with the multisamples parameter set to the current value.
 *         @c GLVIEW_FAILURE in the event of an error.  Errno will then be set
 *         to one of:
 *         - @c EFAULT: @c options was @c NULL or @c multisamples was @c NULL.
 *
 * @since 1.1
 */
GLVIEW_API int glview_options_get_multisamples(glview_options_t *options, glview_multisamples_t *multisamples);

/**
 * @brief Set the window group ID.
 *
 * @details This function will set the window group ID.
 *
 * @param options A valid options handle created by @c glview_options_create().
 *
 * @param window_group_id The window group ID.
 *
 * @return @c GLVIEW_SUCCESS with the window group ID option set to the passed in value.
 *         @c GLVIEW_FAILURE in the event of an error.  Errno will then be set
 *         to one of:
 *         - @c ENOMEM: not enough memory to copy the window group ID string.
 *         - @c EFAULT: @c options was @c NULL.
 *
 * @since 1.1
 */
GLVIEW_API int glview_options_set_window_group_id(glview_options_t *options, const char *window_group_id);

/**
 * @brief Get the window group ID.
 *
 * @details This function will get the window group ID.
 *
 * @param options A valid options handle created by @c glview_options_create().
 *
 * @param buffer The window group ID will be copied into this buffer, up to
 *        @c buffer_size bytes.
 *
 * @param buffer_size The size of @c buffer.
 *
 * @return @c GLVIEW_SUCCESS with the window_group_id parameter set to the current value.
 *         @c GLVIEW_FAILURE in the event of an error.  Errno will then be set
 *         to one of:
 *         - @c EFAULT: @c options or @c buffer was @c NULL or @c buffer_size
 *           was less than or equal to 0.
 *         - @c ENOMSG: The window group ID is not set.
 *
 * @since 1.1
 */
GLVIEW_API int glview_options_get_window_group_id(glview_options_t *options, char *buffer, int buffer_size);

/**
 * @brief Register a callback that will be invoked prior to entering the
 *        execution loop.
 *
 * @param callback The function to call prior to @c glview_loop() entering the
 *                 execution loop. If initialize_callback is @c NULL, any
 *                 previously registered callback will be disabled and no
 *                 function will be called prior to entering the execution
 *                 loop.
 *
 * @return @c GLVIEW_SUCCESS
 *
 * @since 1.0
 */
GLVIEW_API int glview_register_initialize_callback(initialize_callback callback);

/**
 * @brief Register a callback that will be fired once the execution loop is
 *        exited, but before glview is destroyed.
 *
 * @param callback The function to call immediately after exiting the event
 *                 loop. If finalize_callback is @c NULL, any previously
 *                 registered callback will be disabled and no function will be
 *                 called.
 *
 * @return @c GLVIEW_SUCCESS
 *
 * @since 1.0
 */
GLVIEW_API int glview_register_finalize_callback(finalize_callback callback);

/**
 * @brief Register a callback that will be fired every time the app is expected
 *        to draw a frame.
 *
 * @details The display callback is initially set by the @c glview_initialize()
 *          function and is the only mandatory callback. An app can use this
 *          function to set a different display callback. A display callback
 *          must always be registered and valid. Setting the callback to @c NULL
 *          is invalid and will fail. 
 *
 * @param callback The function to call after all events have been processed,
 *                 and the app is expected to draw the frame.
 *
 * @return @c GLVIEW_SUCCESS upon success, @c GLVIEW_FAILURE otherwise, with
 *         errno set to the following:
 *         - @c EFAULT: Attempt to register a NULL display callback.
 *         In the event of @c GLVIEW_FAILURE, the previously registered
 *         frame_callback will remain.
 *
 * @since 1.0
 */
GLVIEW_API int glview_register_frame_callback(frame_callback callback);

/**
 * @brief Register a callback to be fired whenever an orientation occurs that
 *        the app must respond to.
 *
 * @details Calling @c glview_register_resize_callback with a NULL @c
 *          resize_callback will prevent any previously set callback from being
 *          fired on a resize event. Any resize callback will never be fired if
 *          the app is set to landscape or portrait only.
 *
 * @param callback The callback to be fired on a resize event. If this
 *                 parameter is @c NULL then any previously set callback is
 *                 disabled.
 *
 * @return @c GLVIEW_SUCCESS upon success, @c GLVIEW_FAILURE otherwise, with
 *         errno set to the following:
 *         - @c EPERM: @c glview_initialize() was not called prior to @c
 *                     glview_register_resize_callback().
 *
 * @since 1.0
 */
GLVIEW_API int glview_register_resize_callback(resize_callback callback);

/**
 * @brief Register a callback to be fired whenever the app is put into the
 * background.
 *
 * @details Calling @c glview_register_background_callback() with a @c NULL
 *          background callback will disable any previously set callback from
 *          being fired on a background event.
 *
 * @param callback The callback to be fired on a background event. If this
 *                 parameter is @c NULL then any previously set callback is
 *                 disabled.
 *
 * @return @c GLVIEW_SUCCESS
 *
 * @since 1.0
 */
GLVIEW_API int glview_register_background_callback(background_callback callback);

/**
 * @brief Register a callback to be fired whenever the app is put into the
 * foreground.
 *
 * @details Calling @c glview_register_foreground_callback() with a @c NULL
 *          foreground callback will disable any previously set callback from
 *          being fired on a foreground event.
 *
 * @param callback The callback to be fired on a foreground event. If this
 *                 parameter is @c NULL then any previously set callback is
 *                 disabled.
 *
 * @return @c GLVIEW_SUCCESS
 *
 * @since 1.0
 */
GLVIEW_API int glview_register_foreground_callback(foreground_callback callback);

/**
 * @brief Register a callback to be fired for every event the app receives.
 *
 * @details Calling @c glview_register_event_callback() with a @c NULL event
 *          callback will disable any previously set callback from being fired 
 *          on an event.
 *
 * @param callback The callback to be fired on an event. If this parameter is
 *                 @c NULL then any previously set callback is disabled.
 *
 * @return @c GLVIEW_SUCCESS
 *
 * @since 1.0
 */
GLVIEW_API int glview_register_event_callback(event_callback callback);

/**
 * @brief Set the callback data that will be passed into callback functions.
 *
 * @details Every callback that the app registers has, as a paramter, a @c void
 *          * @c callback_data. Whatever @c callback_data that is set here will
 *          be passed into any registered callback when invoked by glview.
 *
 *          Calling this function with a @c NULL parameter will result in a NULL
 *          being passed into any registered callback when invoked by glview.
 *
 * @param callback_data Application-specific data that will be passed as a
 *                      parameter to each of the registered callbacks whenever
 *                      they are fired. This can be changed by calling @c
 *                      glview_set_callback_data() again. This can be set to @c
 *                      NULL, in which case any previously set callback_data
 *                      will no longer be passed into a callback.
 *
 * @return @c GLVIEW_SUCCESS
 *
 * @since 1.0
 */
GLVIEW_API int glview_set_callback_data(void *callback_data);

/**
 * @brief Get the callback data that will be passed into callback functions. 
 *
 * @details Retrieve the app specific data that is being passed into any invoked
 *          callback.
 *
 * @param callback_data The out parameter that gets set to the app-specific data
 *                      obtained by calls to the @c glview_set_callback_data()
 *                      function.
 *
 * @return @c GLVIEW_SUCCESS upon success, @c GLVIEW_FAILURE otherwise, with
 *         errno set to the following:
 *         - @c EINVAL: A @c NULL callback_data was passed in.
 *
 * @see glview_set_callback_data()
 *
 * @since 1.0
 */
GLVIEW_API int glview_get_callback_data(void **callback_data);

/**
 * @brief Fetch the current surface size
 *
 * @details Query the surface to determine the size of the current surface.
 *
 * @param width If this parameter is non-null then it will be set to the current
 *              width of the surface.
 *
 * @param height If this parameter is non-null then it will be set to the
 *               current height of the surface.
 *
 * @return @c GLVIEW_SUCCESS upon success, @c GLVIEW_FAILURE otherwise, with
 *         errno set to the following:
 *         - @c EPERM: @c glview_intialize() was not called prior to @c 
 *                     glview_get_size().
 *
 * @since 1.0
 */
GLVIEW_API int glview_get_size(unsigned int *width, unsigned int *height);

/**
 * @brief Change the vsync setting
 *
 * @details By default, @c vsync is enabled (set to 1). Call this function to
 *          disable @c vsync or to change the @c vsync interval.
 *
 * @param vsync If this parameter is non-zero, it specifies the minimum number
 *              of video frames before a buffer swap. If it is zero then vsync
 *              is disabled.
 *
 * @return @c GLVIEW_SUCCESS upon success, @c GLVIEW_FAILURE otherwise, with
 *         errno set to the following:
 *         - @c EPERM: @c glview_intialize() was not called prior to @c 
 *                     glview_set_vsync().
 *
 * @since 1.0
 */
GLVIEW_API int glview_set_vsync(int vsync);

/**
 * @brief Fetch the vsync setting
 *
 * @details Fetch the current vsync setting. By default, vsync is enabled (set 
 *          to 1).
 *
 * @param vsync The output parameter that the current vsync setting will be
 *              written to. This parameter cannot be @c NULL.  A non-zero value
 *              indicates the number of video frames that will occur before the
 *              buffer is swapped. A zero value indicates that vsync is disabled.
 *
 * @return @c GLVIEW_SUCCESS upon success, @c GLVIEW_FAILURE otherwise, with
 *         errno set to one of the following:
 *         - @c EPERM: @c glview_intialize() was not called prior to @c 
 *                     glview_get_vsync().
 *         - @c EINVAL: output parameter is @c NULL.
 *
 * @since 1.0
 */
GLVIEW_API int glview_get_vsync(int *vsync);

/**
 * @brief Provide a callback that will be called to draw a single frame.
 *
 * @details When the app has been put into the background (due to idle timeout,
 *          or by user action) rendering no longer occurs in the glview
 *          execution loop. This function allows the app to draw a pause screen
 *          (or anything else the app wishes to display). The callback will be
 *          invoked immediately, and once the function completes glview will
 *          swap the buffers to immediately display what was drawn.
 *
 *          There are other common scenarios that may use this function:
 *          - Whenever the app wishes to display something prior to entering the
 *            @c glview_loop()function.
 *          - To dislay some kind of loading indicator while the app's thread is
 *            performing a long-running operation.
 *
 * @param callback The callback that will be fired to draw a single frame. This
 *                 is the callback_data specified during the call to @c
 *                 glview_set_callback_data().
 *
 * @return @c GLVIEW_SUCCESS upon success, @c GLVIEW_FAILURE otherwise, with
 *         errno set to the following:
 *         - @c EPERM: @c glview_initialize() was not called prior to @c 
 *                     glview_display_once().
 *
 * @since 1.0
 */
GLVIEW_API int glview_display_once(display_once_callback callback);

/**
 * @brief Enter glview's execution loop.
 *
 * @details This function contains glview's main execution loop. You must call
 *          @c glview_initialize() before calling this function.
 *
 *          This function invokes the initialize callback before entering the
 *          execution loop. Once started, the execution loop runs for the life
 *          of the app, invoking at various points the registered callbacks. The
 *          only mandatory callback is the display callback, which is called
 *          once per loop.
 *
 *          The execution loop occurs in the following order:
 *          - Pull all events off the event queue and process them:
 *            - On background: fire the background callback (if registered)
 *            - On foreground: fire the foreground callback (if registered)
 *            - On orientation change: fire the resize callback (if registered)
 *            - Fire the event callback with event details (if registered)
 *            - On exit: break out of the execution loop.
 *          - Call the display callback if the app is in the foreground.
 *          - Swap the graphic's buffers.
 *          - Repeat from the top.
 *
 *          When the user exits the app, the execution loop breaks, and the
 *          finalize callback is invoked.
 *
 *          The @c glview_loop() function does not return until the user exits
 *          the application. When glview_loop() returns, the graphics stack has
 *          already been taken down, and glview has already been destroyed. Any
 *          calls to glview after glview_loop() has returned will either fail or
 *          have unspecified behavior.
 *
 * @return GLVIEW_SUCCESS when the user exits the application, GLVIEW_FAILURE
 *         otherwise, with errno set to one of the following:
 *         - EPERM: @c glview_initialize() was not called prior to @c
 *                  glview_loop().
 *         - EACCES: Failed to set BPS channel.
 *
 * @since 1.0
 */
GLVIEW_API int glview_loop(void);

/**
 * @cond HIDDEN
 */
__END_DECLS
/**
 * @endcond
 */

#endif
