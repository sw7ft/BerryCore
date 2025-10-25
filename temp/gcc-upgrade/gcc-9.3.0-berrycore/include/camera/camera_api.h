/*
 * $QNXLicenseC:
 * Copyright 2012-2014, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable
 * license fees to QNX Software Systems before you may reproduce,
 * modify or distribute this software, or any work that includes
 * all or part of this software. Free development licenses are
 * available for evaluation and non-commercial purposes. For more
 * information visit http://licensing.qnx.com or email
 * licensing@qnx.com.
 *
 * This file may contain contributions from others. Please review
 * this entire file for other proprietary rights or license notices,
 * as well as the QNX Development Suite License Guide at
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */

/**
 * @file camera_api.h
 *
 * @brief Functions to take images and record videos with one or more cameras
 *        on a device.
 */

/**
 * @mainpage Camera Library
 * The Camera library provides an application with a consistent interface to
 * interact with one or more cameras connected to a device.
 *
 * @section camera_intro_sec About the Camera API
 * To use the Camera API, you must set one or more of the following
 * permissions in the application descriptor (bar-descriptor.xml) file based on
 * what you want to do:
 * - @c use_camera: To access the camera for taking photos or videos
 * - @c record_audio: To access the microphone when recording video. This
 *                    permission is not required to take photos or video without
 *                    audio
 * - @c use_camera_desktop: To share the user's screen
 * Note: Include the @c access_shared permission if you want to save images to
 *       the camera roll directory on the file system.
 *
 * To grant an app the proper permissions, you must set each permission using
 * the @c <permission> element in the application descriptor file. For example,
 * <permission>use_camera</permission>. For more information on @c use_camera,
 * @c record_audio, and @c use_camera_desktop, see "App permissions"
 * in the "Developing with the Native SDK" guide.
 *
 * Using the Camera library, you can perform operations such as:
 *  - Connect and disconnect from a camera.
 *  - Start and stop the viewfinder.
 *  - Use features on the camera, such as scene modes, zoom, autofocus,
 *    auto white balance, and auto exposure.
 *  - Adjust focus, exposure, and white balance algorithms by defining
 *    regions of interest, or applying manual controls.
 *  - Take pictures individually or in burst mode.
 *  - Encode video and save recordings to file.
 *  - Turn flash and video-lights on and off.
 *
 * The Camera library @b does @b not automatically play audible shutter sounds
 * when a picture is taken or a video is recorded. Camera applications must
 * supply their own sound when a photo is captured or a video recording begins
 * and ends. While you can choose to not have a shutter sound when taking a
 * picture or shooting a video - you are responsible to ensure that
 * the application adheres to the local laws of the regions in which you wish to
 * distribute the application.
 *
 * For example, it is illegal to mute or modify the shutter sound of a camera
 * application in Japan and Korea. Ensure that you comply with the laws and
 * regulations for the countries in which you distribute your application.
 * For more information, see the BlackBerry World Vetting Criteria at
 * https://appworld.blackberry.com/isvportal/home.do.
 *
 * @section camapi_buffer_access Camera image buffer access
 * The operating system provides read access to image data from different
 * stages in the imaging datapath (image buffers). Applications access buffers
 * by binding callback functions or events to a particular stage of the imaging
 * datapath.
 *
 * The camera API is widely adaptable to the specific design patterns of your
 * application due to the option of using either threaded callbacks
 * (@e callback @e mode) or events received in an event-loop (@e event @e mode).
 * Using events does not preclude you from also using callbacks.
 * The two are interoperable and the camera API internally implements
 * callback threads using events.
 *
 * Whether you decide to use callback mode, event mode, or both, depends on
 * the requirements of your application.
 *
 * Callback mode is simple to use and the code that it executes runs
 * in its own thread. Callbacks give you access to one buffer
 * at a time. The access is readonly. Any memory allocated for the
 * buffer is released when the callback completes its execution.
 *
 * Event mode allows you read/write access to the buffers and allows
 * you to select your own threading model. Event mode permits you access to
 * more than one buffer at a time because you can manage when the buffer
 * is released. Event mode requires that you write your own event loop.
 *
 * @subsection camapi_event_mode About event mode
 * Camera events are used asynchronously to notify an application when the
 * camera has some data or status information available that can be
 * acted upon. For example, a status event may indicate that a change in focus
 * has occurred, that the shutter has fired, or that a video recording has run
 * out of disk space.
 *
 * Status events do not have buffers associated with them, but instead carry
 * just enough data to convey the necessary status information. In comparison,
 * an imaging event signals to the application that a data buffer has become
 * available and can be retrieved and processed. An example of an imaging event
 * would be a viewfinder buffer or a still image buffer becoming available.
 *
 * When an imaging event is received, your application should perform the
 * following actions:
 * 1. Call the corresponding get-buffer function (@c
 *    camera_get_viewfinder_buffers(), for example).
 * 2. Process the image data appropriately.
 * 3. Release the buffer back to the camera using the @c
 *    camera_return_buffer() function.
 *
 * To bind an event to a given point in the camera datapath, use one of the
 * following functions:
 * - @c camera_enable_image_event()
 * - @c camera_enable_postview_event()
 * - @c camera_enable_shutter_event()
 * - @c camera_enable_status_event()
 * - @c camera_enable_video_event()
 * - @c camera_enable_viewfinder_event()
 *
 * Multiple events can be bound to the same point in the datapath, but this may
 * be less efficient than dispatching multiple tasks after receiving a single
 * event in your application.
 *
 * To unbind an event from a given point in the camera datapath, use the @c
 * camera_disable_event() function.
 *
 * When a non-status event occurs, such as an image or viewfinder event, your
 * application can retrieve the buffer associated with this event by calling
 * the corresponding get function:
 * - @c camera_get_image_buffers()
 * - @c camera_get_postview_buffers()
 * - @c camera_get_video_buffers()
 * - @c camera_get_viewfinder_buffers()
 *
 * After your application is finished processing the buffer, (e.g., you have
 * saved the image to disk) the buffer must be returned to the camera
 * using the @c camera_return_buffer() function.
 *
 * You should use caution if your application needs to process frames within a
 * set interval. If concurrent events occur in your application where
 * the time to process one event could interfere with the deadline to complete
 * processing another event, then you should consider handling the events in
 * separate threads. For example, you might implement an algorithm to detect
 * smiles in the viewfinder frames, but concurrently, the user may want to
 * capture a still image to disk. Since it's possible to take more time to
 * save this image to disk than the inter-frame period of the viewfinder frames,
 * it's best to process the image-saving task in a different thread from the
 * viewfinder-processing task. You can also use callback mode to resolve this
 * problem because callbacks inherently execute in separate threads.
 *
 * @b Note: It is important that your application follows the guidelines for
 *          resource management outlined in @ref camapi_resource_management.
 *          If you do not observe these guidelines, your application is at
 *          risk of crashing due to memory access errors when resource
 *          arbitration is performed by the operating system.
 *
 * @subsection camapi_callback_mode About callback mode
 * Callbacks are one mechanism of asynchronously accessing camera image data
 * as well as status information. You provide custom code to be executed as a
 * callback when performing camera operations such as taking a picture or
 * encoding video. Using callbacks provide you a great amount of flexibility
 * to control what occurs in your application when a function executes. For
 * example, you can use callbacks to perform image processing or to save data
 * to disk. Callback functions execute in a separate thread, so you need to be
 * sure that your code is thread-safe through the use of appropriate thread
 * synchronization primitives (mutexes, semaphores, condvars, etc.).
 *
 * Unlike events, which can be explicitly bound to a specific location in the
 * image datapath, callbacks are implicitly registered only when invoking the
 * following functions:
 *  - @c camera_start_viewfinder()
 *  - @c camera_take_photo()
 *  - @c camera_take_burst()
 *  - @c camera_start_burst()
 *  - @c camera_start_video()
 *  - @c camera_start_encode()
 *
 * Callbacks are deregistered when the operation started by one of the above
 * functions completes.  For example, when the @c camera_stop_viewfinder()
 * function is invoked, any callbacks registered during the @c
 * camera_start_viewfinder() function call are deregistered.
 *
 * These are the callback signatures for various Camera library functions:
 *
 * - image_callback: This callback is invoked when the final image data becomes
 *                   available. This is typically a full-resolution photograph.
 *                   You can choose to save the image to disk or
 *                   perform other post-processing algorithms on the image.
 *                   The callback has the following signature:
 * @code
 * void function_name( camera_handle_t,
 *                     camera_buffer_t*,
 *                     void* );
 * @endcode
 *          - camera_handle_t: The handle of the camera invoking the callback.
 *          - camera_buffer_t*: A pointer to a @c ::camera_buffer_t structure
 *                              which describes the image data. This data is
 *                              guaranteed to be valid only while your callback
 *                              function is executing.
 *          - void*: The user-specified @c arg argument.
 *
 * - postview_callback: This callback is invoked when the postview image data is
 *                      available. The image data provided is a
 *                      preview-sized version of the captured still image. For
 *                      example, you could display the preview-sized image
 *                      instead of decompressing and down-sampling the final
 *                      image. The callback has the following signature:
 * @code
 * void function_name( camera_handle_t,
 *                     camera_buffer_t*,
 *                     void* );
 * @endcode
 *          - camera_handle_t: The handle of the camera invoking the callback.
 *          - camera_buffer_t*: A pointer to a @c ::camera_buffer_t structure
 *                              which describes the postview frame. This data
 *                              is only guaranteed to be valid while your
 *                              callback function is executing.
 *          - void*: The user-specified @c arg argument.
 *
 * - raw_callback: This callback is reserved for future use. Do not use.
 *
 * - shutter_callback: This callback is invoked when the shutter activates on
 *                     the camera.
 *                     It's your responsibility to play audible shutter
 *                     sounds when a picture is taken or a video is recorded.
 *                     While you can choose to not have a shutter sound when
 *                     taking a picture - you are responsible to ensure that
 *                     the application adheres to the local laws of the regions
 *                     in which you wish to distribute the application.
 *                     For example, it is illegal to mute or modify the shutter
 *                     sound of a camera application in Japan and Korea. Ensure
 *                     that you comply with the laws and regulations for the
 *                     countries in which you distribute your application. For
 *                     more information, see the BlackBerry World Vetting
 *                     Criteria at
 *                     https://appworld.blackberry.com/isvportal/home.do.
 *                     If you use burst mode to capture images in rapid
 *                     succession, choose an appropriate moment to play the
 *                     shutter sound rather than play the shutter sound
 *                     repeatedly.
 *
 *                     The callback has the following signature:
 * @code
 * void function_name( camera_handle_t,
 *                     void* );
 * @endcode
 *          - camera_handle_t: The handle of the camera invoking the callback.
 *          - void*: The user-specified @c arg argument.
 *
 * - status_callback: This callback is invoked when non-image data relevant to
 *                    the state of the camera is being reported. For example,
 *                    a change in autofocus state, or a disk space warning.
 *                    The callback has the following signature:
 * @code
 * void function_name( camera_handle_t,
 *                     camera_devstatus_t,
 *                     uint16_t,
 *                     void* );
 * @endcode
 *          - camera_handle_t: The handle of the camera invoking the callback.
 *          - camera_devstatus_t: The status event that occurred.
 *          - uint16_t: Any extra data associated with the status event that
 *                      occurred.
 *          - void*: The user-specified @c arg argument.
 *
 * - video_callback: This callback is invoked when an uncompressed video frame
 *                   becomes available. The callback has the following
 *                   signature:
 * @code
 * void function_name( camera_handle_t,
 *                     camera_buffer_t*,
 *                     void* );
 * @endcode
 *          - camera_handle_t: The handle of the camera invoking the callback.
 *          - camera_buffer_t*: A pointer to a @c ::camera_buffer_t structure
 *                              which describes the video frame. This data is
 *                              only guaranteed to be valid while your callback
 *                              function is executing.
 *          - void*: The user-specified @c arg argument.
 *
 *    @b Note: On platforms that advertise the @c #CAMERA_FEATURE_PREVIEWISVIDEO
 *             feature, video frames are not explicitly available.
 *             Instead, use the frames returned by the @c viewfinder_callback.
 *
 * - viewfinder_callback: This callback is invoked when a viewfinder buffer
 *                        becomes available. The viewfinder is rendered to a
 *                        screen window by the operating system. You are not
 *                        required to add display code, unless you need to
 *                        perform custom output using some other mechanism.
 *                        The callback has the following signature:
 * @code
 * void function_name( camera_handle_t,
 *                     camera_buffer_t*,
 *                     void* );
 * @endcode
 *          - camera_handle_t: The handle of the camera invoking the callback.
 *          - camera_buffer_t*: A pointer to a @c ::camera_buffer_t structure
 *                              which describes the viewfinder frame. This
 *                              data is only guaranteed to be valid while your
 *                              callback function is executing.
 *          - void*: The user-specified @c arg argument.
 *
 * - enc_video_callback: This callback is invoked when an encoded video frame
 *                       becomes available.
 *                       The callback has the following signature:
 * @code
 * void function_name( camera_handle_t,
 *                     camera_buffer_t*,
 *                     void* );
 * @endcode
 *          - camera_handle_t: The handle of the camera invoking the callback.
 *          - camera_buffer_t*: A pointer to a @c ::camera_buffer_t structure
 *                              which describes the encoded frame. This data
 *                              is only guaranteed to be valid while your
 *                              callback function is executing.
 *          - void*: The user-specified @c arg argument.
 *
 * - enc_audio_callback: This callback is invoked when an encoded audio frame
 *                       becomes available.
 *                       The callback has the following signature:
 * @code
 * void function_name( camera_handle_t,
 *                     camera_buffer_t*,
 *                     void* );
 * @endcode
 *          - camera_handle_t: The handle of the camera invoking the callback.
 *          - camera_buffer_t*: A pointer to a @c ::camera_buffer_t structure
 *                              which describes the encoded frame. This data
 *                              is only guaranteed to be valid while your
 *                              callback function is executing.
 *          - void*: The user-specified argument in the @c arg argument.
 *
 * @b Note: It is important that your application follows the guidelines for
 *          resource management outlined in @ref camapi_resource_management.
 *          If you do not observe these guidelines, your application is at
 *          risk of crashing due to memory access errors when resource
 *          arbitration is performed by the operating system.
 *
 * @section camapi_manual_settings Manual camera settings
 *
 * You can configure various manual settings (i.e., ISO, shutter
 * speed, white balance, and aperture) after you start the
 * viewfinder on the camera. Changes in settings may not be visible for several
 * frames due to latency in the image processing pipeline.
 *
 * For example, when you use an exposure mode (@c ::camera_exposuremode_t) that
 * has a manual component such as @c #CAMERA_EXPOSUREMODE_ISO_PRIORITY and you
 * change the ISO setting (@c camera_set_manual_iso()), you may not see the
 * results of the ISO change until several frames later.
 *
 * @b Note: Not all cameras may support all manual settings. You should call
 *          the @c camera_get_exposure_modes() to determine which manual
 *          exposure settings can be adjusted.
 *
 * @section camapi_viewfinder_modes Viewfinder modes
 *
 * Viewfinder modes are only supported in @c #CAMERA_API_VERSION 3 (BlackBerry
 * 10.3.0) and higher.
 * Use the @c camera_get_api_version() function to determine the API version
 * of the device your application is running on.
 *
 * A viewfinder mode is used to specify the major operating mode of the camera.
 * For more information about the defined viewfinder modes, see
 * @c ::camera_vfmode_t.
 * Using viewfinder modes enables the operating system to optimize configuration
 * of the camera hardware to provide the best user experience and image quality.
 * Using viewfinder modes also allows for easier discovery of camera
 * capabilities and available modes and settings. For example, by selecting the
 * @c #CAMERA_VFMODE_FIXED_BURST, you are indicating that your application
 * needs to capture photos in rapid succession. Once you have selected a
 * viewfinder mode, all of the other capability query functions (e.g.,
 * @c camera_get_supported_vf_resolutions(), @c camera_get_scene_modes(),
 * @c camera_has_feature(), etc.) will properly return lists which are
 * guaranteed to work with your intended use case.
 *
 * You must select a viewfinder mode prior to configuring and starting the
 * viewfinder. Use the @c camera_set_vf_mode() function to select the
 * appropriate mode for your specific use case. After selecting a mode, you can
 * modify the viewfinder settings using the @c camera_set_vf_property()
 * function. Start the viewfinder using the @c camera_start_viewfinder()
 * function. When finished using the camera, stop the viewfinder using the
 * @c camera_stop_viewfinder() function. You may only switch between viewfinder
 * modes when the viewfinder is not running.
 *
 * @b Note: Releases of the Camera library prior to @c #CAMERA_API_VERSION 3
 *          (BlackBerry 10.3.0) do not support viewfinder modes.
 *          Instead, the viewfinder functions were
 *          divided into photovf and videovf variants (e.g., @c
 *          camera_set_photovf_property()). This usage pattern is now,
 *          deprecated, however, for backwards compatibility purposes, it is
 *          still possible to operate the camera using these deprecated
 *          functions. When using the deprecated functions, the viewfinder mode
 *          is equivalent to @c #CAMERA_VFMODE_DEFAULT. Once you change the
 *          viewfinder mode using the @c camera_set_vf_mode() function, you can
 *          no longer use the deprecated functions until you close and re-open
 *          the camera. If your application does not need to use more advanced
 *          viewfinder modes, then you can continue using the legacy photovf
 *          and videovf functions for backwards compatibility.
 *
 * Certain advanced functionality is only available using viewfinder modes,
 * so if your application requires any of this new functionality, you must
 * use viewfinder modes in your application. Your application will not run on
 * devices that are running BlackBerry 10.2.1 or older. The viewfinder modes
 * listed in @c ::camera_vfmode_t have notes which indicate whether the
 * functionality can be accessed on older software versions using alternate
 * configuration means.
 *
 * The list of deprecated viewfinder functions and their replacements are:
 * - @c camera_set_vf_property() deprecates @c camera_set_photovf_property()
 *   and @c camera_set_videovf_property().
 * - @c camera_get_vf_property() deprecates @c camera_get_photovf_property()
 *   and @c camera_get_videovf_property().
 * - @c camera_start_viewfinder() deprecates @c camera_start_photo_viewfinder()
 *   and @c camera_start_video_viewfinder().
 * - @c camera_stop_viewfinder() deprecates @c camera_stop_photo_viewfinder()
 *   and @c camera_stop_video_viewfinder().
 * - @c camera_get_supported_vf_resolutions() deprecates @c
 *   camera_get_photo_vf_resolutions() and @c camera_get_video_vf_resolutions().
 * - @c camera_get_supported_vf_rotations() deprecates @c
 *   camera_get_photo_vf_rotations() and @c camera_get_video_vf_rotations().
 * - @c camera_get_supported_vf_framerates() deprecates @c
 *   camera_get_photo_vf_framerates() and @c camera_get_video_vf_framerates().
 * - @c camera_get_supported_vf_frametypes() deprecates @c
 *   camera_get_photovf_frame_types() and @c camera_get_videovf_frame_types().
 *
 * @section camapi_resource_management Camera resource management
 *
 * System resources are limited in a mobile device environment. Since users
 * may run multiple applications concurrently in a multitasking environment,
 * it is not always possible to satisfy all of the resourcing needs of all
 * applications simultaneously. For this reason, system resources may be
 * revoked from a running application when they are needed elsewhere.
 *
 * At any point in time, it is possible that the resources used by the camera
 * are required by a higher priority application. When this situation occurs,
 * the viewfinder is stopped by the operating system and your application will
 * receive a @c #CAMERA_STATUS_POWERDOWN status event. If buffers are still in
 * use by your application when the viewfinder is stopped, this can cause your
 * application to crash if it is accessing buffer memory when it is unmapped.
 *
 * Your application can call the @c camera_register_resource() function to
 * request that the operating system defer the unmapping of buffer memory
 * temporarily.
 *
 * Whenever resources are needed elsewhere by higher priority applications, or
 * when the camera is about to be powered off for any reason, your application
 * will now receive a @c #CAMERA_STATUS_RESOURCENOTAVAIL status event.
 * When your application receives this status event, you must immediately cease
 * processing all camera buffers and then call the @c
 * camera_deregister_resource() function to let the operating system know that
 * it can proceed to unmap allocated buffer memory. A timeout is in place that
 * limits the amount of time your application has before resources will be
 * forcefully revoked. For this reason, it is important that your application
 * respond as soon as possible after receiving the @c
 * #CAMERA_STATUS_RESOURCENOTAVAIL status event.
 *
 * Please see @c camera_register_resource() and @c camera_deregister_resource()
 * for further information.
 */

#ifndef __CAMERA_API_H__
#define __CAMERA_API_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <screen/screen.h>
#include <sys/siginfo.h>


/**
 * The version of the Camera library. The version is used for IPC handshaking
 * and communication between the Camera API and the operating system.
 * You can compare @c CAMERA_API_VERSION with the value returned by the @c
 * camera_get_api_version() function to determine whether the runtime library is
 * different from the version your application was compiled with. Differences
 * may indicate potential incompatibilities.
 *
 * For reference, the @c CAMERA_API_VERSION values can be mapped to BlackBerry
 * 10 software releases that they first appeared in as follows:
 *  - @c CAMERA_API_VERSION 1 was introduced in BlackBerry 10.0.
 *  - @c CAMERA_API_VERSION 2 was introduced in BlackBerry 10.1.
 *  - @c CAMERA_API_VERSION 3 was introduced in BlackBerry 10.3.0.
 */
#define CAMERA_API_VERSION    3


/**
 * Error codes for the Camera library.
 * If you receive an error code which is not enumerated in this list, consult
 * the system-wide list of error codes in errno.h.
 */
typedef enum {
    /**
     * The function call to the camera completed successfully.
     */
    CAMERA_EOK = EOK,
    /**
     * The function call failed due to a temporary unavailable condition.
     * Try to call the function again.
     */
    CAMERA_EAGAIN = EAGAIN,
    /**
     * The function call failed because of an invalid argument.
     */
    CAMERA_EINVAL = EINVAL,
    /**
     * The function call failed because the specified camera was not found.
     */
    CAMERA_ENODEV = ENODEV,
    /**
     * The function call failed because of a file table overflow.
     */
    CAMERA_EMFILE = EMFILE,
    /**
     * The function call failed because an invalid @c
     * ::camera_handle_t value was used.
     */
    CAMERA_EBADF = EBADF,
    /**
     * The function call failed because the necessary permissions to access
     * the camera are not available.
     */
    CAMERA_EACCESS = EACCES,
    /**
     * The function call failed because an invalid file descriptor was used.
     */
    CAMERA_EBADR = EBADR,
    /**
     * The function call failed because the requested data does not
     * exist.
     */
    CAMERA_ENODATA = ENODATA,
    /**
     * The function call failed because the specified file or directory does
     * not exist.
     */
    CAMERA_ENOENT = ENOENT,
    /**
     * The function call failed because memory allocation failed.
     */
    CAMERA_ENOMEM = ENOMEM,
    /**
     * The function call failed because the requested operation is not
     * supported.
     */
    CAMERA_EOPNOTSUPP = EOPNOTSUPP,
    /**
     * The function call failed due to communication problem or time-out with
     * the camera.
     */
    CAMERA_ETIMEDOUT = ETIMEDOUT,
    /**
     * The function call failed because an operation on the camera is already in
     * progress. In addition, this error can indicate that a call could not be
     * completed because it was invalid or completed already. For example,
     * if you called the @c camera_stop_video() function but the camera had
     * already stopped recording video, this error code would be returned.
     */
#ifdef EALREADY_NEW
    CAMERA_EALREADY = EALREADY_NEW,
#else
    CAMERA_EALREADY = EALREADY,
#endif
    /**
     * The function call failed because the camera is busy.  Typically you
     * receive this error when you try to open a camera while the camera or
     * its required resources are in use.
     */
    CAMERA_EBUSY = EBUSY,
    /**
     * The function call failed because the disk is full.  This typically
     * happens when you are trying to start a video recording and less than
     * the system-reserved amount of disk space remains.
     */
    CAMERA_ENOSPC = ENOSPC,
    /**
     * The function call failed because the Camera library has not been
     * initialized.
     */
    CAMERA_EUNINIT = 0x1000,
    /**
     * The function call failed because the registration of a callback failed.
     */
    CAMERA_EREGFAULT,
    /**
     * The function call failed because the microphone is already in use.
     */
    CAMERA_EMICINUSE,
    /**
     * The function call failed because the operation cannot be completed while
     * the camera @c #CAMERA_UNIT_DESKTOP is in use.
     */
    CAMERA_EDESKTOPCAMERAINUSE,
    /**
     * The function call failed because the camera is in the power down state.
     */
    CAMERA_EPOWERDOWN,
    /**
     * The function call failed because a 3A lock is active.
     */
    CAMERA_3ALOCKED,
    /**
     * The function call failed because the viewfinder freeze flag was set on
     * the device for privacy reasons.
     */
    CAMERA_EVIEWFINDERFROZEN,
    /**
     * The function call failed due to an internal overflow.
     */
    CAMERA_EOVERFLOW,
    /**
     * The function call failed because the camera is in power down state to
     * prevent damage due to excessive heat.
     */
    CAMERA_ETHERMALSHUTDOWN
    /*...*/
} camera_error_t;


/**
 * @brief This enumerated type specifies the image properties list.
 *
 * These properties are used as keys for the following functions:
 * - @c camera_set_vf_property()
 * - @c camera_get_vf_property()
 * - @c camera_set_photo_property()
 * - @c camera_set_video_property()
 * - @c camera_get_photo_property()
 * - @c camera_get_video_property()
 *
 * Each key is associated with a value of the indicated type.
 */
typedef enum {
    /**
     * @internal
     * End-of-list identifier.
     */
    CAMERA_IMGPROP_END = -1,
    /**
     * The image format as a @c ::camera_frametype_t value.
     */
    CAMERA_IMGPROP_FORMAT = 0,
    /**
     * The width of the image as a @c uint32_t value.
     */
    CAMERA_IMGPROP_WIDTH,
    /**
     * The height of the image as a @c uint32_t value.
     */
    CAMERA_IMGPROP_HEIGHT,
    /**
     * The frame rate of the image sequence as a @c double value.
     * When @c #CAMERA_IMGPROP_VARIABLEFRAMERATE is set to a
     * value of 1, @c #CAMERA_IMGPROP_FRAMERATE indicates the maximum
     * frame rate to use for the image sequence.
     */
    CAMERA_IMGPROP_FRAMERATE,
    /**
     * @deprecated As of BlackBerry 10.2.0. Do not use this property.
     *             Instead, use the appropriate
     *             bitrate property that corresponds to the video codec. For
     *             example, if you configure an H.264/AVC video recording, use
     *             the @c camera_set_videoencoder_parameter() function
     *             to set the @c #CAMERA_H264AVC_BITRATE parameter.
     *
     * (Deprecated) The units are in bits per second as a @c uint32_t value
     */
    CAMERA_IMGPROP_BITRATE,
    /**
     * @deprecated As of BlackBerry 10.2.0. Do not use this property.
     *             Instead, use the appropriate
     *             bitrate property that corresponds to the video codec. For
     *             example, if you configure an H.264/AVC video recording, use
     *             the @c camera_set_videoencoder_parameter() function
     *             to set the @c #CAMERA_H264AVC_KEYFRAMEINTERVAL parameter.
     *
     * (Deprecated) The interval (in frames) between the generation of each
     * keyframe as a @c uint32_t value.
     */
    CAMERA_IMGPROP_KEYFRAMEINTERVAL,
    /**
     * The image rotation angle (in degrees) as a @c uint32_t
     * value. Rotation angles are measured in the clockwise direction.
     */
    CAMERA_IMGPROP_ROTATION,
    /**
     * Enable built-in stabilization algorithms to help avoid a
     * blurry image. The value is specified as an @c int value. A
     * value of 0 indicates that stabilization is off and a value of 1
     * indicates that stabilization is on. To enable stabilization for video, @c
     * #CAMERA_FEATURE_VIDEOSTABILIZATION must be available on the camera.
     * Note that @c #CAMERA_IMGPROP_MAXFOV must be set to 0 when starting
     * the video viewfinder before video stabilization can be enabled.
     * To enable stabilization for photos, @c #CAMERA_FEATURE_PHOTOSTABILIZATION
     * must be available on the camera.
     */
    CAMERA_IMGPROP_STABILIZATION,
    /**
     * Zoom factor is used as a @c uint32_t value.
     * The zoom factor is a value supported by the camera hardware and
     * represents digital zoom or optical zoom. Optical zoom is
     * only supported if the camera supports it. Most digital cameras
     * support digital zoom.
     */
    CAMERA_IMGPROP_ZOOMFACTOR,
    /**
     * The viewfinder can use hardware acceleration for @e blitting.
     * To use this feature, the hardware acceleration for the blitting feature
     * must be available (@c #CAMERA_FEATURE_VFHWOVERLAY). Use
     * the @c camera_can_feature() function to determine whether the camera
     * supports the feature. To use blitting, specify as an @c int value where
     * 0 indicates not to use blitting and 1 indicates to use blitting.
     *
     * Blitting is a hardware acceleration feature used for efficiently
     * transferring viewfinder buffers to the video display. For more
     * information, see @c SCREEN_USAGE_OVERLAY used in the @c
     * screen_set_window_property_iv() function in Screen Graphics Subsystem
     * library. When you use this value, the viewfinder window uses @c
     * SCREEN_USAGE_OVERLAY window property where possible.
     */
    CAMERA_IMGPROP_HWOVERLAY,
    /**
     * The JPEG quality setting of the camera as an @c int value.
     * The value represents a percentage. Some camera hardware may be
     * limited to a maximum JPEG quality setting for performance reasons.
     * Values that you program may be internally clipped to the maximum
     * supported value.
     */
    CAMERA_IMGPROP_JPEGQFACTOR,
    /**
     * The window group ID the viewfinder should be created in, as a @c const
     * @c char* value. For more information, see the Screen and Windowing
     * library.
     */
    CAMERA_IMGPROP_WIN_GROUPID,
    /**
     * The window ID to apply to the viewfinder window that is created
     * as a @c const @c char* value.
     */
    CAMERA_IMGPROP_WIN_ID,
    /**
     * @deprecated As of @c #CAMERA_API_VERSION 3 (BlackBerry 10.3.0). Instead,
     *             use @c camera_set_vf_mode() to select a burst viewfinder
     *             mode. The list of viewfinder modes is defined by
     *             @c ::camera_vfmode_t.
     *
     * (Deprecated) Burst mode should be used as an @c int value. A value
     * of 0 indicates to disable burst capture mode while a value of 1 indicates
     * to enable burst capture mode.
     */
    CAMERA_IMGPROP_BURSTMODE,
    /**
     * @deprecated As of BlackBerry 10.2.0. Instead, set @c
     *             #CAMERA_IMGPROP_FRAMERATE using the @c
     *             camera_set_photo_property() function.
     *
     * (Deprecated) The frame rate divisor to apply when operating in burst
     * capture mode as a @c double value. A value of 1 will yield a capture
     * frame rate equal to the viewfinder frame rate. A value of 2 will yield
     * a capture frame rate equal to the viewfinder frame rate divided by 2,
     * where every second frame is captured. Fractional values are allowed.
     */
    CAMERA_IMGPROP_BURSTDIVISOR,
    /**
     * @deprecated As of BlackBerry 10.2.0. Do not use this property.
     *             Instead, use the appropriate
     *             slice size property that corresponds to the video codec. For
     *             example, if you configure an H.264/AVC video recording, use
     *             the @c camera_set_videoencoder_parameter() function
     *             to set the @c #CAMERA_H264AVC_SLICESIZE parameter.
     * (Deprecated)
     */
    CAMERA_IMGPROP_SLICESIZE,
    /**
     * Enable variable frame rate for the image sequence.
     * To use this feature, variable frame rate must be
     * supported by the photo viewfinder (@c
     * #CAMERA_FEATURE_PHOTOVFVARIABLEFRAMERATE). The use of variable frame
     * rate mode allows the camera to decrease the frame rate in order to
     * increase exposure time to compensate for poor lighting conditions.
     * You can use variable frame rate to vary the frame rate based on the
     * lighting conditions in a range defined as follows:
     * @code
     * CAMERA_IMGPROP_FRAMERATE >= frame rate >= CAMERA_IMGPROP_MINFRAMERATE
     * @endcode
     * The value of this property is specified as an @c int value.
     * A value of 0 indicates that variable frame rate is disabled (frame rate
     * is fixed as specified by @c #CAMERA_IMGPROP_FRAMERATE)
     * and a value of 1 indicates that variable frame rate is enabled.
     */
    CAMERA_IMGPROP_VARIABLEFRAMERATE,
    /**
     * The minimum frame rate of the image sequence as a @c double
     * value.
     * @b Note: If variable frame rate mode is enabled, be sure to change @c
     * #CAMERA_IMGPROP_FRAMERATE and @c #CAMERA_IMGPROP_MINFRAMERATE at the same
     * time via a single call to the @c camera_set_vf_property() function.
     * Doing so ensures that range checks can be properly performed.
     */
    CAMERA_IMGPROP_MINFRAMERATE,
    /**
     * An embedded window will be created (see Screen Graphics Subsystem library
     * on window-types). If the viewfinder is being created as a child of an
     * existing child window, then this flag must be set using an @c int. Use a
     * value of 1 to create an embedded window and 0 otherwise.
     */
    CAMERA_IMGPROP_ISEMBEDDED,
    /**
     * Whether to create a visible viewfinder window or not. This flag accepts
     * @c int values. Setting the value to 1 causes a viewfinder window to be
     * created (see Screen and Windowing API for more information on managing
     * windows). Setting the value to 0 suppresses the creation of a viewfinder
     * window.
     */
    CAMERA_IMGPROP_CREATEWINDOW,
    /**
     * Whether automatic embedding of metadata orientation hints is enabled.
     * This flag must be set using an @c int value. Use a value of 1 if the
     * desired @c #CAMERA_IMGPROP_ROTATION value cannot be selected due to
     * limitations in available rotation values reported by
     * @c camera_get_photo_rotations() and 0 otherwise. If you have enabled
     * metadata orientation hints, use @c camera_set_device_orientation() to
     * indicate which way the device is oriented.
     */
    CAMERA_IMGPROP_METAORIENTATIONHINT,
    /**
     * Indicates that the FOV (field of view) of the viewfinder should not be
     * cropped when the viewfinder is started. This parameter must be set using
     * an @c int value. A value of 0 indicates that the viewfinder may be
     * started with cropping applied in order to support use of the
     * @c #CAMERA_IMGPROP_STABILIZATION property. A value of 1 indicates that
     * the viewfinder will provide the widest possible field of view at startup
     * and will disallow attempts to use the @c #CAMERA_IMGPROP_STABILIZATION
     * property.
     */
    CAMERA_IMGPROP_MAXFOV,
    /**
     * The video codec used when generating video files or streams using
     * @c camera_start_video() or @c camera_start_encode(). The video
     * codec value is of type @c ::camera_videocodec_t.
     */
    CAMERA_IMGPROP_VIDEOCODEC,
    /**
     * The audio codec used when generating video files or streams using
     * @c camera_start_video() or @c camera_start_encode(). The audio
     * codec value is of type @c ::camera_audiocodec_t.
     */
    CAMERA_IMGPROP_AUDIOCODEC,
    /**
     * The viewfinder window will be updated with frames from the camera when
     * this property is set to 1. Rendering is suspended if the value is set
     * to 0. The parameter must be an @c int value, and can be used to mask
     * undesirable visual artifacts when exposure bracketing is active.
     */
    CAMERA_IMGPROP_RENDERTOWINDOW
} camera_imgprop_t;


/**
 * @brief This enumerated type specifies the camera physical properties list
 *
 *        These properties are used as keys for the @c
 *        camera_get_physical_property() function.
 *        Each key is associated with a value of the indicated type.
 */
typedef enum {
    /**
     * @internal
     * end-of-list identifier.
     */
    CAMERA_PHYSPROP_END = -1,
    /**
     * The focal length of the lens in millimeters as a @c double value.
     */
    CAMERA_PHYSPROP_FOCALLENGTH = 0,
    /**
     * The horizontal field of view of the camera when set to its minimum zoom
     * factor and at its full-frame resolution. The value (in degrees) is a @c
     * double value. The horizontal axis is defined as the axis running
     * from left to right of the device when held in its default orientation
     * (i.e., the BlackBerry logo is upright).
     */
    CAMERA_PHYSPROP_HORIZONTALFOV,
    /**
     * The vertical field of view of the camera when set to its minimum zoom
     * factor and its full-frame resolution. The value (in degrees) is a @c
     * double value. The vertical axis is defined as the axis running
     * from top to bottom of the device when held in its default orientation
     * (i.e., the BlackBerry logo is upright).
     */
    CAMERA_PHYSPROP_VERTICALFOV,
    /**
     * The full-frame width of the imaging sensor in millimeters as a
     * @c double value. The width corresponds to the sensor axis which runs
     * from left to right of the device when held in its default orientation
     * (i.e., the BlackBerry logo is upright).
     */
    CAMERA_PHYSPROP_SENSORWIDTH,
    /**
     * The full-frame height of the imaging sensor in millimeters as a @c double
     * value. The height corresponds to the sensor axis which runs from top
     * to bottom of the device when held in its default orientation
     * (i.e., the BlackBerry logo is upright).
     */
    CAMERA_PHYSPROP_SENSORHEIGHT,
    /**
     * The magnification ratio between the maximum zoom factor
     * and the minimum zoom factor as a @c double value.
     * For example, a ratio of 3.0 indicates that a fully zoomed-in image
     * is expanded by a magnification factor of 3.0 times when compared with the
     * fully zoomed-out version of the image.
     */
    CAMERA_PHYSPROP_MAXZOOMRATIO,
    /**
     * The full-frame width of the imaging sensor in pixels as a
     * @c uint32_t value. The width corresponds to the sensor axis which runs
     * from left to right of the device when held in its default orientation
     * (i.e., the BlackBerry logo is upright).
     */
    CAMERA_PHYSPROP_SENSORWIDTHPIXELS,
    /**
     * The full-frame height of the imaging sensor in pixels as a @c uint32_t
     * value. The height corresponds to the sensor axis which runs from top
     * to bottom of the device when held in its default orientation
     * (i.e., the BlackBerry logo is upright).
     */
    CAMERA_PHYSPROP_SENSORHEIGHTPIXELS,
    /**
     * The 35mm-equilvalent focal length of the lens in millimeters as a
     * @c double value.
     */
    CAMERA_PHYSPROP_FOCALLENGTH35MM,
    /**
     * The aperture (or F-number) is expressed as the ratio of the focal length
     * to the diameter of the entrance pupil of the lens as a @c double value.
     * If a variable aperture is supported, the value reported refers to the
     * ratio at maximum pupil opening.
     */
    CAMERA_PHYSPROP_APERTURE,
    /**
     * The native sensitivity of the camera sensor expressed as a @c uint32_t
     * ISO value. The native sensitivity is defined as the effective sensitivity
     * of the camera at unity gain.
     */
    CAMERA_PHYSPROP_SENSORISO
} camera_physprop_t;


/**
 * The status of the camera device.
 * These values are delivered to your status callback functions or via the
 * @c camera_get_status_details() function whenever the state of the camera
 * changes.
 *
 * Some examples of conditions which may trigger a status change include:
 * - whether the viewfinder was started
 * - whether recording has stopped
 * - whether autofocus is searching or has locked
 * - whether the camera has powered down
 * - whether a capture was aborted due to a fault
 *
 * Status changes may also convey additional information as a @c uint16_t
 * value where indicated.
 */
typedef enum {
    /**
     * The status of the camera is not known.
     */
    CAMERA_STATUS_UNKNOWN = 0,
    /**
     * No user is connected to the camera.
     */
    CAMERA_STATUS_DISCONNECTED,
    /**
     * A user is connected to the camera but the camera is in the
     * idle state.
     */
    CAMERA_STATUS_CONNECTED,
    /**
     * The camera is not powered. This is typical when the device is going into
     * a standby state. The extra @c uint16_t value can be interpreted as
     * follows:
     * @code
     * Bits 15..8 - Reserved for future use.
     * Bits  7..0 - A @c ::camera_powerdownreason_t value indicating the reason.
     * @endcode
     */
    CAMERA_STATUS_POWERDOWN,
    /**
     * The photo viewfinder has started.
     */
    CAMERA_STATUS_PHOTOVF,
    /**
     * The video viewfinder has started.
     */
    CAMERA_STATUS_VIDEOVF,
    /**
     * The recording has stopped due to a memory error or multimedia
     * framework error (used by the video encoder). The error is received from
     * the encoding graph.
     */
    CAMERA_STATUS_MM_ERROR,
    /**
     * A file has exceeded the maximum size. Recordings
     * will stop with this error when the size is getting too close to the
     * limit.
     */
    CAMERA_STATUS_FILESIZE_ERROR,
    /**
     * The recording has stopped because there is no more disk space
     * available.
     */
    CAMERA_STATUS_NOSPACE_ERROR,
    /**
     * The capture of a still image failed and was aborted.
     */
    CAMERA_STATUS_CAPTURE_ABORTED,
    /**
     * The user-configurable time-remaining threshold has been
     * exceeded while recording video. The default is 60 seconds, but you can
     * change the time-remaining threshold using the @c
     * camera_set_video_filesize_warning() function.
     */
    CAMERA_STATUS_FILESIZE_WARNING,
    /**
     * The focus changed on the camera.
     * The extra @c uint16_t value can be interpreted as follows:
     * @code
     * Bits 15..8 - Reserved for future use.
     * Bits  7..0 - A @c ::camera_focusstate_t value indicating the focus state.
     * @endcode
     * You can call the @c camera_get_focus_state() function to retrieve
     * further details, including the focus region co-ordinates.
     */
    CAMERA_STATUS_FOCUS_CHANGE,
    /**
     * A warning that the camera is about to free resources
     * due to a power-down or arbitration event (resources needed elsewhere).
     * You should release camera resources by returning buffers, stopping
     * recordings, and stopping viewfinders. This event happens when
     * the device is about to enter standby mode or a higher-priority process
     * needs access to resources that are shared with the camera.
     * The extra @c uint16_t value can be interpreted as follows:
     * @code
     * Bits 15..8 - Reserved for future use.
     * Bits  7..0 - A @c ::camera_powerdownreason_t value indicating the reason.
     * @endcode
     *
     * @b Note: For more important information related to the triggering of
     *          this status event, see @ref camapi_resource_management and
     *          @c camera_register_resource().
     */
    CAMERA_STATUS_RESOURCENOTAVAIL,
    /**
     * Video encoding has been paused. This pause is due to
     * resources needed for video encoding not being currently available
     * (needed elsewhere). Once resources are available again, @c
     * #CAMERA_STATUS_VIDEO_RESUME status change will be sent.
     * While encoding is in this paused state, there will be a gap in the
     * video file. Your application may choose to stop video encoding when
     * this status event is received.
     */
    CAMERA_STATUS_VIDEO_PAUSE,
    /**
     * Video encoding has resumed again following a pause or has
     * started encoding for the first time.
     */
    CAMERA_STATUS_VIDEO_RESUME,
    /**
     * Still capture has completed and you may now take another picture.
     * This occurs at the end of a @c camera_take_photo() or
     * @c camera_take_burst() cycle, or when @c camera_stop_burst() is called.
     * This status event is mainly useful when you are capturing photos in
     * non-blocking mode.
     */
    CAMERA_STATUS_CAPTURECOMPLETE,
    /**
     * The camera has been repowered. This status typically occurs when the
     * device returns from the standby (i.e., @c #CAMERA_STATUS_POWERDOWN)
     * state.
     */
    CAMERA_STATUS_POWERUP,
    /**
     * For system privacy reasons, the viewfinder has been frozen. When the
     * viewfinder is frozen, the same frame is continually sent until the
     * @c #CAMERA_STATUS_VIEWFINDER_UNFREEZE status is sent.
     * Currently, only the @c #CAMERA_UNIT_DESKTOP and @c
     * #CAMERA_UNIT_SECONDARY_DESKTOP cameras can be frozen.
     */
    CAMERA_STATUS_VIEWFINDER_FREEZE,
    /**
     * The viewfinder that was previously frozen has resumed the display of
     * frames. This status can only be received after the
     * @c #CAMERA_STATUS_VIEWFINDER_FREEZE status has been received previously.
     */
    CAMERA_STATUS_VIEWFINDER_UNFREEZE,
    /**
     * This indicates that the low-light status has changed. The least
     * significant bit of the @c uint16_t value will be 1 when low-light
     * is detected, and 0 when low-light is not detected. All other bits in
     * the @c uint16_t value are reserved for future use.
     */
    CAMERA_STATUS_LOWLIGHT,
    /**
     * This indicates that a frame was dropped internally either due to the
     * user taking too long to process a callback frame or due to some internal
     * error. The @c uint16_t extra argument contains the least significant bits
     * of the @c ::camera_eventkey_t associated with the buffer queue that
     * overflowed.
     */
    CAMERA_STATUS_FRAME_DROPPED,
    /**
     * For system privacy reasons, the viewfinder has been suspended. No frames
     * will be delivered while the viewfinder is suspended.
     * Currently, only the @c #CAMERA_UNIT_DESKTOP and @c
     * #CAMERA_UNIT_SECONDARY_DESKTOP cameras may be suspended.
     */
    CAMERA_STATUS_VIEWFINDER_SUSPEND,
    /**
     * The viewfinder that was previously suspended has resumed the delivery of
     * frames. This status will only be received after the @c
     * #CAMERA_STATUS_VIEWFINDER_SUSPEND status has been received previously.
     */
    CAMERA_STATUS_VIEWFINDER_UNSUSPEND,
    /**
     * This indicates that the flash power level has changed from its previous
     * value. You can call the @c camera_get_flash_level() function to
     * retrieve additional information.
     */
    CAMERA_STATUS_FLASH_LEVEL_CHANGE,
    /**
     * This indicates that the video light power level has changed from its
     * previous value. You can call the @c camera_get_videolight_level()
     * function to retrieve additional information.
     */
    CAMERA_STATUS_VIDEOLIGHT_LEVEL_CHANGE,
    /**
     * This indicates that the state of the videolight has changed.
     * The extra @c uint16_t field in the status event can be interpreted
     * as follows:
     * @code
     * Bits 15..8 - Reserved for future use.
     * Bits  7..0 - A @c ::camera_videolightmode_t value indicating the state.
     * @endcode
     */
    CAMERA_STATUS_VIDEOLIGHT_CHANGE
} camera_devstatus_t;


/**
 * The reason that the camera was turned off or was shutdown.
 *
 * When you use @e event mode, you can use @c camera_get_status_details()
 * to retrieve the reason the camera was turned off. The @c devstatusextra
 * argument is one of the listed enumerations from this enumerated type.
 * For information about the event mode, see @ref camapi_event_mode.
 *
 * When you are in @e callback mode, you can retrieve the reason using the third
 * argument from the status callback. For information about the callback
 * arguments, see @ref camapi_callback_mode.
 */
typedef enum {
    /**
     * The camera was turned off for an unknown reason.
     */
    CAMERA_POWERDOWNREASON_UNKNOWN = 0,
    /**
     * The camera was turned off because the device went into standby mode.
     */
    CAMERA_POWERDOWNREASON_STANDBY,
    /**
     * The camera was turned off because the shared resources used by the camera
     * were required by another component of the operating system.
     */
    CAMERA_POWERDOWNREASON_RESOURCEARBITRATION,
    /**
     * The camera was turned off to prevent damage due to excessive heat.
     */
    CAMERA_POWERDOWNREASON_THERMAL,
    /**
     * The camera was required by a higher priority application. Your
     * application must close the camera.
     */
    CAMERA_POWERDOWNREASON_FORCECLOSE
} camera_powerdownreason_t;


/**
 * Represents the camera units on the device. It is possible for a
 * device to have multiple cameras units.
 */
typedef enum {
    /**
     * No specific camera specified.
     */
    CAMERA_UNIT_NONE = 0,
    /**
     * The camera on the front of the device. The front of a handset is the
     * side which typically has a screen and faces the user.
     */
    CAMERA_UNIT_FRONT,
    /**
     * The camera on the rear of the device.
     */
    CAMERA_UNIT_REAR,
    /**
     * The virtual @e desktop camera used for sharing your desktop.
     * Sharing your desktop is a capability that's available for some devices.
     */
    CAMERA_UNIT_DESKTOP,
    /**
     * The virtual @e secondary @e desktop camera used for sharing your
     * secondary screen desktop output.
     * Sharing your secondary desktop is a capability that's available for some
     * devices.
     */
    CAMERA_UNIT_SECONDARY_DESKTOP,
    /**
     * For internal use only. The value is used to determine the
     * maximum number of cameras supported.
     */
    CAMERA_UNIT_NUM_UNITS
} camera_unit_t;


/**
 * Represents the major mode of the viewfinder. Each viewfinder mode provides a
 * different set of capabilities, which can be checked using @c
 * camera_has_feature() after choosing a mode. Not all cameras support all
 * viewfinder modes, so ensure you query @c camera_get_supported_vf_modes()
 * before using @c camera_set_vf_mode().
 *
 * For more information about viewfinder modes, see @ref
 * camapi_viewfinder_modes.
 */
typedef enum {
    /**
     * The default viewfinder mode when a camera is opened. The
     * @c camera_has_feature() function provides a complete list of features
     * supported by the camera.
     *
     * @b Note: In default mode, you can only use the deprecated viewfinder
     *          functions referenced in @ref camapi_viewfinder_modes. You can
     *          not use the deprecated viewfinder functions with any mode other
     *          than the default viewfinder mode.
     */
    CAMERA_VFMODE_DEFAULT,
    /**
     * Photo mode allows single pictures to be taken. For more information
     * about taking photos, see @c camera_take_photo().
     *
     * @b Note: For backwards compatibility, photo viewfinder mode may also be
     *          enabled using the deprecated functions referenced in @ref
     *          camapi_viewfinder_modes.
     */
    CAMERA_VFMODE_PHOTO,
    /**
     * Continuous burst mode allows for continuous image capture at the highest
     * possible speed. For more information, see @c camera_start_burst().
     *
     * @b Note: For backwards compatibility, photo viewfinder mode may also be
     *          enabled using the deprecated functions referenced in @ref
     *          camapi_viewfinder_modes. Instead of using this viewfinder mode,
     *          you would instead use the @c #CAMERA_IMGPROP_BURSTMODE
     *          image property with @c camera_set_photovf_property().
     */
    CAMERA_VFMODE_CONTINUOUS_BURST,
    /**
     * Fixed burst mode allows for a finite number of images to be captured
     * in rapid succession. For more information, see @c camera_take_burst().
     *
     * @b Note: For backwards compatibility, photo viewfinder mode may also be
     *          enabled using the deprecated functions referenced in @ref
     *          camapi_viewfinder_modes. Instead of using this viewfinder mode,
     *          you would instead use the @c #CAMERA_IMGPROP_BURSTMODE
     *          image property with @c camera_set_photovf_property().
     */
    CAMERA_VFMODE_FIXED_BURST,
    /**
     * EV bracketing mode allows for a finite number of images to be captured
     * in rapid succession with different exposure value (EV) offsets applied
     * to the images. For more information, see @c camera_config_ev_bracketing()
     * and @c camera_take_burst().
     *
     * @b Note: For backwards compatibility, photo viewfinder mode may also be
     *          enabled using the deprecated functions referenced in @ref
     *          camapi_viewfinder_modes. Instead of using this viewfinder mode,
     *          you would instead use the @c #CAMERA_IMGPROP_BURSTMODE
     *          image property with @c camera_set_photovf_property().
     */
    CAMERA_VFMODE_EV_BRACKETING,
    /**
     * Video mode allows for videos to be recorded or encoded. For more
     * information, see @c camera_start_video() and @c camera_start_encode().
     *
     * @b Note: For backwards compatibility, photo viewfinder mode may also be
     *          enabled using the deprecated functions referenced in @ref
     *          camapi_viewfinder_modes.
     */
    CAMERA_VFMODE_VIDEO,
    /**
     * Video snapshot mode allows for still image capture while recording or
     * encoding videos. For more information, see @c camera_start_video(),
     * @c camera_start_encode(), and @c camera_take_photo().
     */
    CAMERA_VFMODE_VIDEO_SNAPSHOT,
    /**
     * High-speed video mode allows for videos to be recorded or encoded at
     * higher frame rates than @c CAMERA_VFMODE_VIDEO. For more information,
     * see @c camera_start_video() and @c camera_start_encode().
     */
    CAMERA_VFMODE_HIGH_SPEED_VIDEO,
    /**
     * HDR (high dynamic range) video mode allows for videos to be recorded
     * with a higher dynamic range than @c CAMERA_VFMODE_VIDEO. For more
     * information, see @c camera_start_video() and @c camera_start_encode().
     */
    CAMERA_VFMODE_HDR_VIDEO,
    /**
     * For internal use only. The value is used to determine the
     * maximum number of view finder modes supported.
     */
    CAMERA_VFMODE_NUM_MODES
} camera_vfmode_t;


/**
 * A 32-bit value representing a handle used to identify an open instance of
 * a logical camera unit on a device. A handle to the camera is created by
 * calling the @c camera_open() function and is released by calling the @c
 * camera_close() function. A handle, when available, is similar to a file
 * descriptor used to access the camera. Various Camera library calls use the
 * handle to interact with the camera.
 */
typedef int32_t camera_handle_t;


/**
 * A safe-initializer value for a @c ::camera_handle_t. Use this value to
 * check that correct initialization occurred and whether a call to the @c
 * camera_open() function was successful. You should use this value to
 * initialize camera handle variables, and after you close a handle.
 */
#define CAMERA_HANDLE_INVALID  (-1)


/**
 * The camera capabilities or features available on the camera. The enumerated
 * type is used with the @c camera_has_feature() and @c camera_can_feature()
 * functions.
 */
typedef enum {
    /**
     * The camera supports queries from the @c
     * camera_can_feature() and @c camera_has_feature() functions.
     */
    CAMERA_FEATURE_FBM = 0,
    /**
     * It is possible to take photos (still images).
     */
    CAMERA_FEATURE_PHOTO = 1,
    /**
     * It is possible to encode video.
     */
    CAMERA_FEATURE_VIDEO = 2,
    /**
     * Zoom is available in photo viewfinder mode.
     */
    CAMERA_FEATURE_PHOTOZOOM = 3,
    /**
     * Zoom is available in the video viewfinder mode.
     */
    CAMERA_FEATURE_VIDEOZOOM = 4,
    /**
     * Zero-shutter lag is available.
     */
    CAMERA_FEATURE_ZSL = 5,
    /**
     * Burst mode is available for taking multiple photos
     * consecutively.
     *
     * @b Note: When @c #CAMERA_FEATURE_BURST is available, but @c
     * #CAMERA_FEATURE_CONTINUOUSBURST isn't, then only the @c
     * camera_take_burst() function can be used. The @c camera_start_burst()
     * function will not work.
     */
    CAMERA_FEATURE_BURST = 6,
    /**
     * Exposure bracketing is available in burst capture mode.
     */
    CAMERA_FEATURE_EVBRACKETING = 7,
    /**
     * Flash is available.
     */
    CAMERA_FEATURE_FLASH = 8,
    /**
     * An on-board light source is available for use with video
     * capture.
     */
    CAMERA_FEATURE_VIDEOLIGHT = 9,
    /**
     * There is no standalone video buffer stream available.
     * Preview buffers are used for both viewfinder and video encoding.
     * For more information, see @c camera_set_video_property().
     */
    CAMERA_FEATURE_PREVIEWISVIDEO = 10,
    /**
     * Autofocus is available.
     */
    CAMERA_FEATURE_AUTOFOCUS = 11,
    /**
     * Manual focus is available.
     */
    CAMERA_FEATURE_MANUALFOCUS = 12,
    /**
     * It is possible to focus on a specific region
     * in the viewfinder.
     */
    CAMERA_FEATURE_REGIONFOCUS = 13,
    /**
     * Macro focus mode is available. Macro mode allows you to
     * focus on objects that are close to the camera, such as 10 centimeters
     * away.
     */
    CAMERA_FEATURE_MACROFOCUS = 14,
    /**
     * The focus assist feature is available. Focus assist turns on the
     * light when running single focus cycles in low-light conditions.
     * The light will also be turned on in low-light conditions if
     * continuous autofocus is enabled and focus is not locked prior to
     * calling @c camera_take_photo().
     * Turning on the light improves autofocus performance in low-light
     * conditions.
     */
    CAMERA_FEATURE_FOCUSASSIST = 15,
    /**
     * The viewfinder can use hardware acceleration for blitting.
     * Blitting is a hardware acceleration feature used for efficiently
     * transferring viewfinder buffers to the video display. For more
     * information, see @c SCREEN_USAGE_OVERLAY used in the @c
     * screen_set_window_property_iv() function in Screen Graphics Subsystem
     * library. When you use this value, the viewfinder window uses @c
     * SCREEN_USAGE_OVERLAY window property where possible.
     */
    CAMERA_FEATURE_VFHWOVERLAY = 16,
    /**
     * Region exposure is available. Region exposure allows you
     * to perform spot and partial metering in specific regions of an image.
     */
    CAMERA_FEATURE_REGIONEXPOSURE = 17,
    /**
     * Region white balance is available. Region white balance uses the image
     * data in the user-specified region to make white balance adjustment
     * (color correction) computations.
     */
    CAMERA_FEATURE_REGIONWHITEBALANCE = 18,
    /**
     * Continuous burst mode is available. Continuous burst mode
     * allows for rapid successive image capture over an indefinite time-frame.
     *
     * @b Note: When @c #CAMERA_FEATURE_BURST is available, but @c
     * #CAMERA_FEATURE_CONTINUOUSBURST isn't, then only the @c
     * camera_take_burst() function can be used. The @c camera_start_burst()
     * function will not work.
     */
    CAMERA_FEATURE_CONTINUOUSBURST = 19,
    /**
     * Face detection is available in the viewfinder image
     * stream. Face detection permits you retrieve the coordinates of the faces
     * detected in the scene via the accompanying viewfinder metadata.
     */
    CAMERA_FEATURE_VFFACEDETECT = 20,
    /**
     * Face detection is available in the still image
     * stream. Face detection permits you retrieve the coordinates of the faces
     * detected in the scene via the accompanying still image metadata.
     */
    CAMERA_FEATURE_FACEDETECT = 21,
    /**
     * Variable frame rate is supported for photo viewfinder.
     * For more information, see the description for @c
     * #CAMERA_IMGPROP_VARIABLEFRAMERATE.
     */
    CAMERA_FEATURE_PHOTOVFVARIABLEFRAMERATE = 22,
    /**
     * Auto exposure is available.
     */
    CAMERA_FEATURE_AUTOEXPOSURE = 23,
    /**
     * Auto white balance is available.
     */
    CAMERA_FEATURE_AUTOWHITEBALANCE = 24,
    /**
     * Manual exposure is available.
     */
    CAMERA_FEATURE_MANUALEXPOSURE = 25,
    /**
     * Manual white balance is available.
     */
    CAMERA_FEATURE_MANUALWHITEBALANCE = 26,
    /**
     * @internal
     * Reserved for internal use. Do not use.
     */
    CAMERA_FEATURE_PREMAPBUFFERS = 27,
    /**
     * Low-light status notification is available.
     */
    CAMERA_FEATURE_LOWLIGHT_STATUS = 28,
    /**
     * Histogram feature is available.
     */
    CAMERA_FEATURE_VFHISTOGRAM = 29,
    /**
     * Video stabilization is available on the camera. For more information,
     * see @c #CAMERA_IMGPROP_STABILIZATION.
     */
    CAMERA_FEATURE_VIDEOSTABILIZATION = 30,
    /**
     * Photo stabilization is available on the camera. For more information,
     * see @c #CAMERA_IMGPROP_STABILIZATION.
     */
    CAMERA_FEATURE_PHOTOSTABILIZATION = 31,
    /**
     * Optical image stabilization is available on the camera.
     */
    CAMERA_FEATURE_OPTICALIMAGESTABILIZATION = 32,
    /**
     * An end-of-list identifier. Also indicates the total number of features
     * recognized by the Camera library.
     */
    CAMERA_FEATURE_NUMFEATURES
} camera_feature_t;


/**
 * The maximum length of a filename returned by camera-roll functions. The value
 * is useful for you to determine the largest @c char* buffer to allocate. The
 * camera roll is a directory where photo and video files can be saved.
 */
#define CAMERA_ROLL_NAMELEN  (256)


/**
 * The frame types identifiers for an image buffer. Frame types are used to
 * distinguish between frame descriptors within a @c ::camera_buffer_t
 * structure.
 */
typedef enum {
    /**
     * The frame type has no associated format, no recognized
     * format, or is unformatted.
     */
    CAMERA_FRAMETYPE_UNSPECIFIED = 0,
    /**
     * The frame type is NV12 formatted data. The @c
     * ::camera_frame_nv12_t structure represents this frame type.
     */
    CAMERA_FRAMETYPE_NV12,
    /**
     * The frame type is 32-bit ARGB data. The @c
     * ::camera_frame_rgb8888_t structure represents this frame type.
     */
    CAMERA_FRAMETYPE_RGB8888,
    /**
     * The frame type is 24-bit RGB data. The @c
     * ::camera_frame_rgb888_t structure represents this frame type.
     */
    CAMERA_FRAMETYPE_RGB888,
    /**
     * The frame type is JPEG image data. The @c
     * ::camera_frame_jpeg_t structure represents this frame type.
     */
    CAMERA_FRAMETYPE_JPEG,
    /**
     * The frame type is 8-bit gray-scale image data. The @c
     * ::camera_frame_gray8_t structure represents this frame type.
     */
    CAMERA_FRAMETYPE_GRAY8,
    /**
     * The frame type is metadata. The @c
     * ::camera_frame_meta_t structure represents this frame type.
     */
    CAMERA_FRAMETYPE_METADATA,
    /**
     * The image is a 10-bit Bayer frame type. The @c
     * ::camera_frame_bayer_t structure represents this frame type.
     */
    CAMERA_FRAMETYPE_BAYER,
    /**
     * The image is a YCbCr 4:2:2 packed frame type. The @c
     * ::camera_frame_cbycry_t structure represents this frame type.
     */
    CAMERA_FRAMETYPE_CBYCRY,
    /**
     * The frame consists of compressed video data.  The @c
     * ::camera_frame_compressedvideo_t structure represents this frame type.
     */
    CAMERA_FRAMETYPE_COMPRESSEDVIDEO,
    /**
     * The frame consists of compressed audio data.  The @c
     * ::camera_frame_compressedaudio_t structure represents this frame type.
     */
    CAMERA_FRAMETYPE_COMPRESSEDAUDIO,
    /**
     * The frame type is 16-bit RGB data (5-bit red component, 6-bit green
     * component, 5-bit blue component). The @c ::camera_frame_rgb565_t
     * structure represents this frame type.
     */
    CAMERA_FRAMETYPE_RGB565,
    /**
     * @internal
     * For internal use only. Do not use.
     */
    CAMERA_FRAMETYPE_PRIVATE,
    /**
     * An end-of-list identifier.
     */
    CAMERA_FRAMETYPE_NUMFRAMETYPES
} camera_frametype_t;


/**
 * The video compression formats used by the video encoder.
 */
typedef enum {
    /**
     * No compression.
     */
    CAMERA_VIDEOCODEC_NONE = 0,
    /**
     * AVC1 compression (NALU).
     */
    CAMERA_VIDEOCODEC_AVC1,
    /**
     * H264 compression (Annex B).
     */
    CAMERA_VIDEOCODEC_H264
} camera_videocodec_t;


/**
 * The audio compression formats used by the video encoder.
 */
typedef enum {
    /**
     * No compression.
     */
    CAMERA_AUDIOCODEC_NONE = 0,
    /**
     * MPEG-2/4 AAC compression.
     */
    CAMERA_AUDIOCODEC_AAC,
    /**
     * Uncompressed PCM audio samples.
     */
    CAMERA_AUDIOCODEC_RAW
} camera_audiocodec_t;


/**
 * The maximum size, in bytes, of the frame descriptor.
 */
#define CAMERA_MAX_FRAMEDESC_SIZE  (256)


/**
 * A camera event key that is used to identify an event that is enabled.
 * For more information about events, see @ref camapi_event_mode.
 */
typedef int32_t camera_eventkey_t;


/**
 * @brief Event buffering modes
 * @details The event buffering mode dictates the behavior of the @c inbuffer
 *          and @c outbuffer arguments of the buffer retrieval functions.
 *          The enumerated values are for use with the following functions:
 *          - @c camera_enable_image_event()
 *          - @c camera_enable_postview_event()
 *          - @c camera_enable_status_event()
 *          - @c camera_enable_shutter_event()
 *          - @c camera_enable_video_event()
 *          - @c camera_enable_viewfinder_event()
 *
 *          You use the following functions to retrieve the buffers:
 *          - @c camera_get_image_buffers()
 *          - @c camera_get_postview_buffers()
 *          - @c camera_get_video_buffers()
 *          - @c camera_get_viewfinder_buffers()
 */
typedef enum {
    /**
     * Read-only access to buffers is requested. This is the same buffer access
     * mode employed when a callback function is used. The @c inbuffer argument
     * is read-only.
     */
    CAMERA_EVENTMODE_READONLY,
    /**
     * Read-write access to buffers is requested. Using this mode allows you to
     * modify buffers prior to delivery to callback functions or read-only event
     * consumers. The @c inbuffer and @c outbuffer arguments refer to the same
     * image data in physical memory however, @c outbuffer is modifiable, while
     * @c inbuffer remains read-only.
     */
    CAMERA_EVENTMODE_READWRITE,
} camera_eventmode_t;


/**
 * A frame descriptor that holds only data. Use this frame descriptor when the
 * @c #CAMERA_FRAMETYPE_UNSPECIFIED is reported as the @c ::camera_frametype_t.
 */
typedef struct {
    /**
     * An array representing the frame data. The size of the array is
     * the size indicated by the @c #CAMERA_MAX_FRAMEDESC_SIZE value. This
     * placeholder value ensures that the buffer descriptor is always padded for
     * future compatibility.
     */
     uint8_t  framedata[CAMERA_MAX_FRAMEDESC_SIZE];
} camera_frame_unspecified_t;


/**
 * A frame descriptor used for NV12 frame types. Use this file descriptor when
 * @c #CAMERA_FRAMETYPE_NV12 is reported as the @c ::camera_frametype_t.
 */
typedef struct {
    /**
     * The height of the frame in pixels.
     */
     uint32_t height;
    /**
     * The width of the frame in pixels.
     */
     uint32_t width;
    /**
     * The number of bytes between the first pixel of the first row in memory
     * and the first pixel of the second row in memory of the luminance (Y)
     * plane. Stride is often called @e pitch. For more information, see the
     * @c uv_stride member.
     */
     uint32_t stride;
    /**
     * The number of bytes between the first pixel of the Y plane in memory
     * and the first pixel of the UV plane in memory. On a device where
     * there is no gap between the Y and UV planes, the uv_offset would be
     * height times stride bytes. This equivalence is not guaranteed across
     * all devices, so it is important to observe the uv_offset value rather
     * than attempting to compute the offset.
     */
     int64_t uv_offset;
    /**
     * The number of bytes between the first pixel of the first row in memory
     * and the first pixel of the second row in memory of the chrominance (UV)
     * plane. For more information, see the @c stride member.
     */
     int64_t uv_stride;
} camera_frame_nv12_t;


/**
 * A frame descriptor used for RGB8888 frame types. Use this file descriptor
 * when @c #CAMERA_FRAMETYPE_RGB8888 is reported as the @c ::camera_frametype_t.
 */
typedef struct {
    /**
     * The height of the frame in pixels.
     */
    uint32_t height;
       /**
    * The width of the frame in pixels.
    */
    uint32_t width;
    /**
     * The number of bytes between the first pixel of the first row in memory
     * and the first pixel of the second row in memory.
     * Stride is often called @e pitch.
     */
    uint32_t stride;
} camera_frame_rgb8888_t;


/**
 * A frame descriptor used for RGB888 frame types. Use this frame descriptor
 * when @c #CAMERA_FRAMETYPE_RGB888 is reported as the @c ::camera_frametype_t.
 */
typedef struct {
    /**
     * The height of the frame in pixels.
     */
    uint32_t height;
    /**
     * The width of the frame in pixels.
     */
    uint32_t width;
    /**
     * The number of bytes between the first pixel of the first row in memory
     * and the first pixel of the second row in memory.
     * Stride is often called @e pitch.
     */
    uint32_t stride;
} camera_frame_rgb888_t;


/**
 * A frame descriptor used for RGB565 frame types. Use this frame descriptor
 * when @c #CAMERA_FRAMETYPE_RGB565 is reported as the @c ::camera_frametype_t.
 */
typedef struct {
    /**
     * The height of the frame in pixels.
     */
    uint32_t height;
    /**
     * The width of the frame in pixels.
     */
    uint32_t width;
    /**
     * The number of bytes between the first pixel of the first row in memory
     * and the first pixel of the second row in memory.
     * Stride is often called @e pitch.
     */
    uint32_t stride;
} camera_frame_rgb565_t;


/**
 * A frame descriptor used for JPEG frame types. Use this frame descriptor
 * when @c #CAMERA_FRAMETYPE_JPEG is reported as the @c ::camera_frametype_t.
 */
typedef struct {
    /**
     * The size of the JPEG buffer in bytes.
     */
    uint64_t bufsize;
    /*...*/
} camera_frame_jpeg_t;


/**
 * A frame descriptor for 8-bits per pixel grayscale frame types. Use this
 * frame descriptor when @c #CAMERA_FRAMETYPE_GRAY8 is reported as the @c
 * ::camera_frametype_t.
 */
typedef struct {
    /**
     * The height of the frame in pixels.
     */
    uint32_t height;
    /**
     * The width of the frame in pixels.
     */
    uint32_t width;
    /**
     * The number of bytes between the first pixel of the first row in memory
     * and the first pixel of the second row in memory.
     * Stride is often called @e pitch.
     */
    uint32_t stride;
} camera_frame_gray8_t;


/**
 * A frame descriptor for metadata frame types. Use this frame descriptor
 * when @c #CAMERA_FRAMETYPE_METADATA is reported as the @c
 * ::camera_frametype_t.
 */
typedef struct {
    /**
     * The size of the frame in bytes.
     */
    uint64_t bufsize;
    /*...*/
} camera_frame_meta_t;


/**
 * Bayer bit justification.
 * The Bayer bit justification indicates whether bit 0 is the
 * least significant or most significant bit of the word, and
 * it also indicates whether the bits are justified towards
 * the 0th bit (right justified), or to the Nth bit (left justified).
 * For example:
 * @code
 * le = false
 * bpp = 10
 * packing = 16
 * cadence_length = 16
 * pixels_per_cadence = 1
 * format = CAMERA_BAYERFORMAT_RGGB
 * @endcode
 * @c #CAMERA_BAYERJUSTIFY_RIGHT_BIT0LSB would represent:
 * @code
 * Bit:          FEDCBA9876543210 FEDCBA9876543210
 * Scanline n:   000000RRRRRRRRRR 000000GGGGGGGGGG
 * Scanline n+1: 000000GGGGGGGGGG 000000BBBBBBBBBB
 * @endcode
 * Note that the 0th bit in the word represents the least-significant bit,
 * and the bits are justified to the right of the word.
 */
typedef enum {
    /** Bit 0 is the least significant bit, and the bits are right justified.
     */
    CAMERA_BAYERJUSTIFY_RIGHT_BIT0LSB,
    /** Bit 0 is the least significant bit, and the bits are left justified.
     */
    CAMERA_BAYERJUSTIFY_LEFT_BIT0LSB,
    /** Bit 0 is the most significant bit, and the bits are right justified.
     */
    CAMERA_BAYERJUSTIFY_RIGHT_BIT0MSB,
    /** Bit 0 is the most significant bit, and the bits are left justified.
     */
    CAMERA_BAYERJUSTIFY_LEFT_BIT0MSB,
} camera_bayerjustify_t;


/**
 * The Bayer array macro-pixel format. For more information about the Bayer
 * frame format, see @c ::camera_frame_bayer_t.
 */
typedef enum {
    /**
     * Camera Bayer array macro-pixel format is unknown or unspecified.
     */
    CAMERA_BAYERFORMAT_UNSPECIFIED,

    /**
     * Camera Bayer array macro-pixel format is:
     * @code
     *  G R
     *  B G
     * @endcode
     */
    CAMERA_BAYERFORMAT_GRBG,

    /**
     * Camera Bayer array macro-pixel format is:
     * @code
     *  R G
     *  G B
     * @endcode
     */
    CAMERA_BAYERFORMAT_RGGB,

    /**
     * Camera Bayer array macro-pixel format is:
     * @code
     *  B G
     *  G R
     * @endcode
     */
    CAMERA_BAYERFORMAT_BGGR,

    /**
     * Camera Bayer array macro-pixel format is:
     * @code
     *  G B
     *  R G
     * @endcode
     */
    CAMERA_BAYERFORMAT_GBRG,
} camera_bayerformat_t;


/**
 * A frame descriptor for a Bayer frame type. Use this frame
 * descriptor when @c #CAMERA_FRAMETYPE_BAYER is reported as the @c
 * ::camera_frametype_t.
 *
 * Each pixel in the Bayer frame is part of a Bayer @e macro-pixel. Each Bayer
 * macro-pixel is made up of four color components: one red, one blue, and two
 * green. We refer to the color components as @e pixels, and the group of four
 * as a macro-pixel.
 *
 * Each macro-pixel is stored across two lines in the frame. The first two
 * pixels are stored contiguously on the first line. The @c stride separates the
 * first pixel from the third, and the second pixel from the fourth.
 *
 * Each pixel of the Bayer macro-pixel comprises @c bpp bits. These bits can
 * be packed into larger sized words with a size indicated by the @c packing
 * field. In addition, groups of pixels may be tightly packed into a cadence
 * which is defined by @c cadence_length and @c pixels_per_cadence. The ordering
 * of the bits is determined by the @c justification field.
 *
 * Example 1:
 * @code
 * le = true
 * bpp = 10
 * packing = 16
 * cadence_length = 16
 * pixels_per_cadence = 1
 * justification = CAMERA_BAYERJUSTIFY_RIGHT_BIT0LSB
 * format = CAMERA_BAYERFORMAT_RGGB
 * @endcode
 * This example describes a 10-bit Bayer frame where each color component is
 * stored as 10 bits packed into 16-bit words. The word is stored in little-
 * endian byte order. Bit 0 represents the least significant bit, and the bits
 * are justified to the right of each byte. This leaves six unused bits per
 * pixel.
 * The Bayer macro-pixels in one cadence would be stored like so, with
 * PxHi indicating the most significant bits of pixel x, and PxLo indicating
 * the least significant bits of pixel x:
 * @code
 * Bit:                  76543210
 * Scanline n,   byte 0: RRRRRRRR    P1Lo(Red)
 * Scanline n,   byte 1: 000000RR    P1Hi(Red)
 * Scanline n,   byte 2: GGGGGGGG    P2Lo(Green)
 * Scanline n,   byte 3: 000000GG    P2Hi(Green)
 * ...and repeats.
 *
 * Scanline n+1, byte 0: GGGGGGGG    P1Lo(Green)
 * Scanline n+1, byte 1: 000000GG    P1Hi(Green)
 * Scanline n+1, byte 2: BBBBBBBB    P2Lo(Blue)
 * Scanline n+1, byte 3: 000000BB    P2Hi(Blue)
 * ...and repeats.
 * @endcode
 *
 * Example 2:
 * @code
 * le = false
 * bpp = 10
 * packing = 10
 * justification = CAMERA_BAYERJUSTIFY_LEFT_BIT0LSB
 * cadence_length = 10
 * pixels_per_cadence = 1
 * format = CAMERA_BAYERFORMAT_RGGB
 * @endcode
 * This example describes a 10-bit Bayer frame where each 10-bit pixel is
 * tightly packed into a 10-bit word. There are no wasted bits in between
 * pixels in this example. Each word is stored in big-endian byte order.
 * Bit 0 represents the least significant bit, and the bits
 * are justified to the left of each byte.
 * The Bayer macro-pixels in one cadence would be stored like so, with PxHi
 * indicating the most significant bits of pixel x, and PxLo indicating the
 * least significant bits of pixel x:
 *
 * @code
 * Bits:                 76543210
 * Scanline n,   byte 0: RRRRRRRR    P1Hi(Red)
 * Scanline n,   byte 1: RRGGGGGG    P1Lo(Red)     & P2Hi(Green)
 * Scanline n,   byte 2: GGGGRRRR    P2Lo(Green)   & P3Hi(Red)
 * Scanline n,   byte 3: RRRRRRGG    P3Lo(Red)     & P4Hi(Green)
 * Scanline n,   byte 4: GGGGGGGG    P4Lo(Green)
 * ...and repeats.
 *
 * Scanline n+1, byte 0: GGGGGGGG    P1Hi(Green)
 * Scanline n+1, byte 1: GGBBBBBB    P1Lo(Green)   & P2Hi(Blue)
 * Scanline n+1, byte 2: BBBBGGGG    P2Lo(Blue)    & P3Hi(Green)
 * Scanline n+1, byte 3: GGGGGGBB    P3Lo(Green)   & P4Hi(Blue)
 * Scanline n+1, byte 4: BBBBBBBB    P4Lo(Blue)
 * ...and repeats.
 * @endcode
 *
 * Example 3:
 * @code
 * le = true
 * bpp = 10
 * packing = 10
 * justification = CAMERA_BAYERJUSTIFY_RIGHT_BIT0LSB
 * cadence_length = 64
 * pixels_per_cadence = 6
 * format = CAMERA_BAYERFORMAT_RGGB
 * @endcode
 * This example describes a 10-bit Bayer frame where each 10-bit pixel
 * is tightly packed into a 10-bit word, and six pixels are packed into
 * a 64-bit cadence. The word is stored in little-endian byte order. Bit
 * 0 represents the least significant bit and the bits are justified to
 * the right of each byte. This leaves four unused bits for each six
 * pixel cadence.
 * The Bayer macro-pixels in one cadence would be stored
 * like so, with PxHi indicating the most significant bits of pixel x,
 * and PxLo indicating the least significant bits of pixel x:
 * @code
 * Bits:                 76543210
 * Scanline n,   byte 0: RRRRRRRR    P1Lo(Red)
 * Scanline n,   byte 1: GGGGGGRR    P2Lo(Green)   & P1Hi(Red)
 * Scanline n,   byte 2: RRRRGGGG    P3Lo(Red)     & P2Hi(Green)
 * Scanline n,   byte 3: GGRRRRRR    P4Lo(Green)   & P3Hi(Red)
 * Scanline n,   byte 4: GGGGGGGG    P4Hi(Green)
 * Scanline n,   byte 5: RRRRRRRR    P5Lo(Red)
 * Scanline n,   byte 6: GGGGGGRR    P6Lo(Green)   & P5Hi(Red)
 * Scanline n,   byte 7: 0000GGGG    4 bits unused & P6Hi(Green)
 * ...and repeats.
 *
 * Scanline n+1, byte 0: GGGGGGGG    P1Lo(Green)
 * Scanline n+1, byte 1: BBBBBBGG    P2Lo(Blue)    & P1Hi(Green)
 * Scanline n+1, byte 2: GGGGBBBB    P3Lo(Green)   & P2Hi(Blue)
 * Scanline n+1, byte 3: BBGGGGGG    P4Lo(Blue)    & P3Hi(Green)
 * Scanline n+1, byte 4: BBBBBBBB    P4Hi(Blue)
 * Scanline n+1, byte 5: GGGGGGGG    P5Lo(Green)
 * Scanline n+1, byte 6: BBBBBBGG    P6Lo(Blue)    & P5Hi(Green)
 * Scanline n+1, byte 7: 0000BBBB    4 bits unused & P6Hi(Blue)
 * ...and repeats.
 * @endcode
 * NOTE: Looking at Scanline n, byte 1, you will note that the P1Hi bits
 * (the most significant bits of pixel 1) begin at the right of the byte.
 * This is because right justification is indicated by
 * @c #CAMERA_BAYERJUSTIFY_RIGHT_BIT0LSB. This is in contrast to example 2
 * where bits are justified to the left, and occupy the upper bits of
 * Scanline n, byte 1.
 */
typedef struct {
    /**
     * The size of the frame, in bytes.
     */
    uint64_t bufsize;
    /**
     * The height of the frame, in pixels.
     */
    uint32_t height;
    /**
     * The width of the frame, in pixels.
     */
    uint32_t width;
    /**
     * The number of bytes between the first pixel of the first row in memory
     * and the first pixel of the second row in memory.
     * Stride is often called @e pitch.
     */
    uint32_t stride;
    /**
     * The format of the Bayer macro-pixel.
     */
    camera_bayerformat_t format;
    /**
     * The inter-pixel stride, in bits.
     */
    uint32_t packing;
    /**
     * The bits per pixel component inside the packing size.
     */
    uint32_t bpp;
    /**
     * Whether little-endian is used to pack the frame. When @c le is true,
     * the bytes are packed in little-endian, otherwise when @c le is false,
     * the bytes are packed using big-endian.
     */
    bool le;
    /**
     * The size (in bits) of a packing candence.
     */
    uint32_t cadence_length;
    /**
     * The number of pixels in a packing cadence.
     */
    uint32_t pixels_per_cadence;
    /**
     * The justification of the pixel bits, For more information
     * see @c ::camera_bayerjustify_t
     */
    camera_bayerjustify_t justification;
    /*...*/
} camera_frame_bayer_t;


/**
 * A frame descriptor for a YCbCr 4:2:2 packed frame type. Use this frame
 * descriptor when @c #CAMERA_FRAMETYPE_CBYCRY is reported as the @c
 * ::camera_frametype_t.
 *
 * Each pixel in the CbYCrY frame is part of a macro-pixel. Each CbYCrY
 * macro-pixel is made up of four color components: one U (Cr, or
 * red-difference chroma), one V (Cb, or blue-difference chroma), and two Y
 * (luma) components. We refer to the color components as @e pixels, and the
 * group of four color components as a @e macro-pixel.
 *
 * Each macro-pixel is stored contiguously on the same line, unlike @c
 * ::camera_frame_bayer_t, where each macro-pixel is divided into two lines.
 *
 * Each pixel of the CBYCRY macro-pixel is stored in @c packing bits. If @c le
 * is true, the lower @c bpp bits of @c packing contain color information, if
 * @c le is false, the higher @c bpp bits of @c packing contain color
 * information.
 *
 * For example, @c le = true, @c bpp = 8, and @c packing = 8 describes an 8-bit
 * CbYCrY frame such that each color component is stored in the lower 8 bits of
 * a 8-bit pixel. Thus, the macro-pixel would be stored like so:
 * @code
 * Bit:          01234567 01234567 01234567 01234567
 * Scanline n:   UUUUUUUU YYYYYYYY VVVVVVVV YYYYYYYY = 32 bits
 * @endcode
 */
typedef struct {
    /**
     * The size of the buffer as a 64-bit integer.
     */
    uint64_t bufsize;
    /**
     * The height of the image, in pixels.
     */
    uint32_t height;
    /**
     * The width of the image, in pixels.
     */
    uint32_t width;
    /**
     * The number of bytes between the first pixel of the first row in memory
     * and the first pixel of the second row in memory.
     * Stride is often called @e pitch.
     */
    uint32_t stride;
    /**
     * The inter-pixel distance, in bits.
     */
    uint32_t packing;
    /**
     * The bits per pixel component inside the packing size.
     */
    uint32_t bpp;
    /**
     * The endian order used for packing the data. A value of @c true indicates
     * that the bytes are packed using little-endian order, otherwise, a value
     * of @c false indicates that the bytes are packed using big-endian
     * order.
     */
    bool le;
    /*...*/
} camera_frame_cbycry_t;


/**
 * A frame descriptor for compressed video frame types. Use this
 * frame descriptor when @c #CAMERA_FRAMETYPE_COMPRESSEDVIDEO is reported as
 * the @c ::camera_frametype_t.
 */
typedef struct {
    /**
     * The size of the buffer as a 64-bit integer.
     */
    uint64_t bufsize;
    /**
     * The format of the compressed video.
     */
    camera_videocodec_t codec;
    /**
     * A flag indicating whether this frame is a keyframe.
     */
    bool keyframe;
    /**
     * Bitrate expressed in bits per second.
     */
    uint64_t bitrate;
} camera_frame_compressedvideo_t;


/**
 * A frame descriptor for compressed audio frame types. Use this
 * frame descriptor when @c #CAMERA_FRAMETYPE_COMPRESSEDAUDIO is reported as
 * the @c ::camera_frametype_t.
 */
typedef struct {
    /**
     * The size of the buffer as a 64-bit integer.
     */
    uint64_t bufsize;
    /**
     * The format of the compressed audio.
     */
    camera_audiocodec_t codec;
    /**
     * A flag indicating whether this frame is a keyframe.
     */
    bool keyframe;
    /**
     * Number of channels in the audio stream.
     */
    uint32_t channels;
    /**
     * Number of bits per sample per channel.
     */
    uint32_t bits;
    /**
     * Uncompressed sample rate in hertz (Hz).
     */
    uint32_t samplerate;
    /**
     * Bitrate expressed in bits per second.
     */
    uint64_t bitrate;
} camera_frame_compressedaudio_t;


/**
 * A union that contains all available frame descriptors for the
 * Camera library.
 */
typedef union {
    /**
     * An unknown frame type or unspecified frame type.
     */
    camera_frame_unspecified_t      unspecified;
    /**
     * The @c ::camera_frame_nv12_t member corresponds to the @c
     * #CAMERA_FRAMETYPE_NV12 enumerator in the @c ::camera_frametype_t type.
     */
    camera_frame_nv12_t             nv12;
    /**
     * The @c ::camera_frame_rgb8888_t member corresponds to the @c
     * #CAMERA_FRAMETYPE_RGB8888 enumerator in the @c ::camera_frametype_t type.
     */
    camera_frame_rgb8888_t          rgb8888;
    /**
     * The @c ::camera_frame_rgb888_t member corresponds to the
     * #CAMERA_FRAMETYPE_RGB888 enumerator in the @c ::camera_frametype_t type.
     */
    camera_frame_rgb888_t           rgb888;
    /**
     * The @c ::camera_frame_jpeg_t member corresponds to the @c
     * #CAMERA_FRAMETYPE_JPEG enumerator in the @c ::camera_frametype_t type.
     */
    camera_frame_jpeg_t             jpeg;
    /**
     * The @c ::camera_frame_gray8_t member corresponds to the @c
     * #CAMERA_FRAMETYPE_GRAY8 enumerator in the @c ::camera_frametype_t type.
     */
    camera_frame_gray8_t            gray8;
    /**
     * The @c ::camera_frame_meta_t member corresponds to the @c
     * #CAMERA_FRAMETYPE_METADATA enumerator in the @c ::camera_frametype_t
     * type.
     */
    camera_frame_meta_t             meta;
    /**
     * The @c ::camera_frame_bayer_t member corresponds to the @c
     * #CAMERA_FRAMETYPE_BAYER enumerator in the @c ::camera_frametype_t type.
     */
    camera_frame_bayer_t            bayer;
    /**
     * The @c ::camera_frame_cbycry_t member corresponds to the @c
     * #CAMERA_FRAMETYPE_CBYCRY enumerator in the @c ::camera_frametype_t type.
     */
    camera_frame_cbycry_t           cbycry;
    /**
     * The @c ::camera_frame_compressedvideo_t member corresponds to the @c
     * #CAMERA_FRAMETYPE_COMPRESSEDVIDEO enumerator in the @c
     * ::camera_frametype_t type.
     */
    camera_frame_compressedvideo_t  compvid;
    /**
     * The @c ::camera_frame_compressedaudio_t member corresponds to the
     * #CAMERA_FRAMETYPE_COMPRESSEDAUDIO enumerator in the @c
     * ::camera_frametype_t type.
     */
    camera_frame_compressedaudio_t  compaud;
    /**
     * The @c ::camera_frame_rgb565_t member corresponds to the
     * #CAMERA_FRAMETYPE_RGB565 enumerator in the @c ::camera_frametype_t type.
     */
    camera_frame_rgb565_t           rgb565;
    /*...*/
} camera_framedesc_t;


/**
 * The camera buffer structure is used to convey image data between the API
 * and an application and to adequately describe the format of the image data.
 */
typedef struct {
    /**
     * The type of frame descriptor that is used to distinguish between members
     * of the @c ::camera_framedesc_t union.
     */
    camera_frametype_t      frametype;
    /**
     * The size of the @c ::camera_buffer_t structure.
     * @b Note: This does not describe the size of the image data pointed to
     *          by @c framebuf. The actual image size must be computed using
     *          format-specific fields in the appropriate @c
     *          ::camera_framedesc_t member.
     */
    uint64_t                framesize;
    /**
     * A pointer to the frame data.
     */
    uint8_t                *framebuf;
    /**
     * The size of the associated metadata.
     */
    uint64_t                framemetasize;
    /**
     * A pointer to the associated metadata.
     */
    void                   *framemeta;
    /**
     * The timestamp when the buffer was filled. The timestamp is referenced to
     * the system monotonic clock (CLOCK_MONOTONIC).
     */
    int64_t                 frametimestamp;
    /**
     * The rotation delta from the default device orientation. The rotation
     * is measured in degrees, clockwise.
     */
    int32_t                 frameorientation;
    /**
     * For internal use. Do not use.
     */
    uint32_t                reserved[4];
    /**
     * The union which describes the geometry of the image data being reported
     * by the @c framebuf field in this structure.
     */
    camera_framedesc_t      framedesc;
} camera_buffer_t;


/**
 * The resolution (height and width of an image) in pixels. Use this structure
 * when querying supported resolutions.
 */
typedef struct {
    /**
     * The width of the image in pixels.
     */
    unsigned int            width;
    /**
     * The height of the image in pixels.
     */
    unsigned int            height;
} camera_res_t;


/**
 * The scene mode to use for the camera. A scene mode specifies a predefined
 * visual style applied by the camera hardware to achieve a specific image
 * result. For example, one scene mode may use a faster shutter speed in order
 * to capture fast moving subjects more clearly, whereas another scene mode
 * may use a slower shutter speed in order to capture images in lower light.
 * You can use the @c camera_get_scene_modes() function to determine which modes
 * are supported by the current camera.
 */
typedef enum {
    /**
     * The camera default scene mode. This value acts as an alias
     * for the preferred scene mode for a particular camera. When you start the
     * viewfinder, a default scene mode is selected, such as
     * @c #CAMERA_SCENE_AUTO. The default that is selected is dependent on the
     * specific camera hardware. If you have changed the scene mode, you
     * can later revert back to the default scene mode setting by calling
     * @c camera_set_scene_mode() with a value of @c #CAMERA_SCENE_DEFAULT.
     * If you read the scene mode using @c camera_get_scene_mode(), the camera
     * will report the actual scene mode that has been selected, rather than the
     * @c #CAMERA_SCENE_DEFAULT alias.
     */
    CAMERA_SCENE_DEFAULT = 0,
    /**
     * Auto scene mode is a specific exposure program, which tries to achieve
     * the best picture by automatically varying shutter speed, iso, and white
     * balance. This differs from the other more specialized scene modes which
     * may constrain one or more of these parameters to achieve a particular
     * result under different lighting conditions.
     */
    CAMERA_SCENE_AUTO,
    /**
     * Use a faster shutter speed. A fast shutter speed allows
     * you to capture images with less motion blur where the subjects are
     * quickly moving, such as sports shots.
     */
    CAMERA_SCENE_SPORTS,
    /**
     * Drop the mid-range tones in an image.
     */
    CAMERA_SCENE_WHITEBOARD,
    /**
     * Produce a soft-effect when photographing people.
     */
    CAMERA_SCENE_CLOSEUP,
    /**
     * The scene being photographed is a piece of paper with text on it.
     */
    CAMERA_SCENE_BUSINESSCARD,
    /**
     * The scene being photographed is a barcode.
     */
    CAMERA_SCENE_BARCODE,
    /**
     * Use a faster shutter speed. A fast shutter speed allows
     * you to capture images with less motion blur where the subjects are
     * quickly moving, such as action shots.
     */
    CAMERA_SCENE_ACTION,
    /**
     * Don't apply any post-processing effects. In test
     * mode, pixels are untouched by the image signal processor (ISP) as image
     * optimizations are turned off. This mode is used for factory testing
     * and calibration.
     */
    CAMERA_SCENE_TEST,
    /**
     * Compensate exposure for bright scenes.
     */
    CAMERA_SCENE_BEACHANDSNOW,
    /**
     * Compensate exposure for dark scenes.
     */
    CAMERA_SCENE_NIGHT,
    /**
     * The total number of supported scene modes.
     */
    CAMERA_SCENE_NUMSCENEMODES
} camera_scenemode_t;


/**
 * The operating mode for the flash.
 * Used with the @c camera_config_flash() function.
 */
typedef enum {
    /**
     * The flash will not fire.
     */
    CAMERA_FLASH_OFF = 0,
    /**
     * The flash will fire.
     */
    CAMERA_FLASH_ON,
    /**
     * The flash will fire as required by lighting conditions.
     */
    CAMERA_FLASH_AUTO
} camera_flashmode_t;


/**
 * The operating mode for the video light.
 * Used with the @c camera_config_videolight() function.
 */
typedef enum {
    /**
     * The video light is off.
     */
    CAMERA_VIDEOLIGHT_OFF = 0,
    /**
     * The video light is on.
     */
    CAMERA_VIDEOLIGHT_ON
} camera_videolightmode_t;


/**
 * The state of the autofocus algorithm on the camera.
 */
typedef enum {
    /**
     * Autofocus is disabled or not available.
     */
    CAMERA_FOCUSSTATE_NONE = 0,
    /**
     * The system is waiting for the scene to stabilize before trying to focus.
     * Not all platforms may report this intermediate state.
     */
    CAMERA_FOCUSSTATE_WAITING,
    /**
     * The system is searching for an object to focus on.
     */
    CAMERA_FOCUSSTATE_SEARCHING,
    /**
     * The system has failed to focus.
     */
    CAMERA_FOCUSSTATE_FAILED,
    /**
     * The focus is successfully locked.
     */
    CAMERA_FOCUSSTATE_LOCKED,
    /**
     * The system detected a significant change in the scene.
     */
     CAMERA_FOCUSSTATE_SCENECHANGE
} camera_focusstate_t;


/**
 * The focus mode of the camera. Use @c camera_get_focus_modes() to determine
 * the focus modes that are supported by the current platform and camera.
 */
typedef enum {
    /**
     * Focus is disabled.
     */
    CAMERA_FOCUSMODE_OFF = 0,
    /**
     * The camera is using extended depth of field (EDoF) focus
     * mode.
     */
    CAMERA_FOCUSMODE_EDOF,
    /**
     * The camera is using manual focus mode.
     */
    CAMERA_FOCUSMODE_MANUAL,
    /**
     * The camera is using single-cycle autofocus. Single-cycle
     * focus occurs once and then stops.
     */
    CAMERA_FOCUSMODE_AUTO,
    /**
     * The camera is using single-cycle macro autofocus.
     * Single-cycle focus occurs once and then stops.
     */
    CAMERA_FOCUSMODE_MACRO,
    /**
     * The camera is using continuous autofocus mode. The
     * autofocus algorithm restarts if the scene goes out of focus.
     */
    CAMERA_FOCUSMODE_CONTINUOUS_AUTO,
    /**
     * The camera is using continuous autofocus mode for macro-range subjects.
     * The autofocus algorithm restarts if the scene goes out of focus.
     */
    CAMERA_FOCUSMODE_CONTINUOUS_MACRO,
    /**
     * The total number of supported focus modes.
     */
    CAMERA_FOCUSMODE_NUMFOCUSMODES
} camera_focusmode_t;


/**
 * The exposure mode of the camera. You can use the @c
 * camera_get_exposure_modes() function to determine which modes are supported
 * by the current platform and camera.
 */
typedef enum {
    /**
     * The default exposure mode for the camera. Since not all cameras support
     * all exposure modes, @c CAMERA_EXPOSUREMODE_DEFAULT can always be used as
     * an alias to the most automatic exposure mode supported by the camera.
     */
    CAMERA_EXPOSUREMODE_DEFAULT,
    /**
     * Auto exposure is off.
     */
    CAMERA_EXPOSUREMODE_OFF,
    /**
     * Exposure is automatically adjusted by the camera by varying the
     * shutter speed, ISO value, and aperture value.
     */
    CAMERA_EXPOSUREMODE_AUTO,
    /**
     * Manual exposure mode.
     * The camera will not automatically adjust any of the exposure controls.
     * The shutter speed, ISO value, and aperture value must all be set
     * manually.
     */
    CAMERA_EXPOSUREMODE_MANUAL,
    /**
     * The ISO value must be manually set. The camera automatically adjusts
     * the shutter speed and aperture value.
     */
    CAMERA_EXPOSUREMODE_ISO_PRIORITY,
    /**
     * The shutter speed must be manually set. The camera automatically
     * adjusts the ISO value and aperture value.
     */
    CAMERA_EXPOSUREMODE_SHUTTER_PRIORITY,
    /**
     * The aperture value must be manually set. The camera automatically
     * adjusts the shutter speed and ISO value.
     */
    CAMERA_EXPOSUREMODE_APERTURE_PRIORITY,
    /**
     * The ISO value and shutter speed must be manually set. The camera
     * automatically adjusts the aperture value.
     */
    CAMERA_EXPOSUREMODE_ISO_SHUTTER_PRIORITY,
    /**
     * The ISO value and aperture value must be manually set. The camera
     * automatically adjusts the shutter speed.
     */
    CAMERA_EXPOSUREMODE_ISO_APERTURE_PRIORITY,
    /**
     * The shutter speed and aperture value must be manually set.
     * The camera automatically adjusts the ISO value.
     */
    CAMERA_EXPOSUREMODE_SHUTTER_APERTURE_PRIORITY,
    /**
     * The total number of exposure modes.
     */
    CAMERA_EXPOSUREMODE_NUMEXPOSUREMODES
} camera_exposuremode_t;


/**
 * The white balance mode of the camera. You can use the @c
 * camera_get_whitebalance_modes() function to determine which modes are
 * supported by the current platform and camera.
 */
typedef enum {
    /**
     * The default white balance mode. Since not all cameras may support all
     * white balance modes, @c CAMERA_WHITEBALANCEMODE_DEFAULT can always be
     * used as an alias to select a valid white balance mode.
     */
    CAMERA_WHITEBALANCEMODE_DEFAULT,
    /**
     * Auto white balance is disabled.
     */
    CAMERA_WHITEBALANCEMODE_OFF,
    /**
     * Auto white balance is enabled and the white balance will
     * be automatically adjusted by the camera.
     */
    CAMERA_WHITEBALANCEMODE_AUTO,
    /**
     * White balance must be manually set.
     */
    CAMERA_WHITEBALANCEMODE_MANUAL,
    /**
     * The total number of white balance modes.
     */
    CAMERA_WHITEBALANCEMODE_NUMWHITEBALANCEMODES
} camera_whitebalancemode_t;


/**
 * The autofocus, auto exposure, and auto white balance algorithms (3A).
 * The values in this enumerated type are typically used as bitmasks
 * for use with the 3A functions to indicate which of the 3A algorithms
 * to apply.
 */
typedef enum {
    /**
     * No 3A algorithm.
     */
    CAMERA_3A_NONE = 0,
    /**
     * The autofocus algorithm.
     */
    CAMERA_3A_AUTOFOCUS =        1<<0,
    /**
     * The auto exposure algorihtm.
     */
    CAMERA_3A_AUTOEXPOSURE =     1<<1,
    /**
     * The auto white balance algorithm.
     */
    CAMERA_3A_AUTOWHITEBALANCE = 1<<2
} camera_3a_t;


/**
 * This structure is used to identify a subset of pixels in an image.
 * Regions are used to report focus lock positions and to configure
 * region-dependent focus, exposure, and white balance operations.
 */
typedef struct {
    /**
     * The left coordinate of the region. A value of 0 refers to the leftmost
     * column of the image.
     */
    uint32_t left;
    /**
     * The top coordinate of the region. A value of 0 refers to the topmost
     * column of the image.
     */
    uint32_t top;
    /**
     * The width of the region in pixels.
     */
    uint32_t width;
    /**
     * The height of the region in pixels.
     */
    uint32_t height;
    /**
     * An additional application-dependent value that can be used to convey
     * extra information about a region. Typically, this extra information may
     * be a weighting, ranking, or other application-specific value to apply
     * when defining a set of regions.
     */
    uint32_t extra;
} camera_region_t;


/**
 * The camera access mode flags that are passed to the @c camera_open() function
 * to indicate the type of access that is required.
 * @anonenum camapi_camera_modeflags Camera access mode flags
 */
enum {
    /**
     * Read-access to the camera configuration.
     */
    CAMERA_MODE_PREAD =      1<<0,
    /**
     * Write-access to the camera configuration.
     */
    CAMERA_MODE_PWRITE =     1<<1,
    /**
     * Read-access to the camera imaging datapath (image buffers).
     */
    CAMERA_MODE_DREAD =      1<<2,
    /**
     * Write access to the camera imaging datapath (image buffers).
     */
    CAMERA_MODE_DWRITE =     1<<3,
    /**
     * Access to the camera roll. The camera roll creates uniquely named
     * files in the camera roll directory.
     */
    CAMERA_MODE_ROLL =       1<<4,
    /**
     * @internal
     * Reserved for future use.
     */
    CAMERA_MODE_SHARED =    1<<6,
    /**
     * @internal
     * Reserved for internal use.
     */
    CAMERA_MODE_PRIVILEGED = 1<<5,
    /**
     * The application has read-only access to the camera configuration and the
     * camera imaging datapath.
     */
    CAMERA_MODE_RO =         (CAMERA_MODE_PREAD | CAMERA_MODE_DREAD),
    /**
     * The application has read-access and write-access to camera
     * configuration and the camera imaging datapath. Use this as an alias for
     * @c #CAMERA_MODE_PREAD, @c #CAMERA_MODE_PWRITE, @c #CAMERA_MODE_DREAD, and
     * @c #CAMERA_MODE_DWRITE.
     */
    CAMERA_MODE_RW =         (CAMERA_MODE_PREAD | CAMERA_MODE_PWRITE |
                              CAMERA_MODE_DREAD | CAMERA_MODE_DWRITE),
};


/**
 * The supported image file format extensions on the camera roll.
 * These extensions are only used to generate filenames. The actual formatting
 * of the image data is the responsibility of the application writing to the
 * file.
 */
typedef enum {
    /**
     * Use the system-specified default photo file format extension.
     */
    CAMERA_ROLL_PHOTO_FMT_DEFAULT = 0,
    /**
     * Image files are saved to the camera roll with a ".jpg" extension.
     */
    CAMERA_ROLL_PHOTO_FMT_JPG,
    /**
     * Image files are saved to the camera roll with a ".png" extension.
     */
    CAMERA_ROLL_PHOTO_FMT_PNG,
} camera_roll_photo_fmt_t;


/**
 * The supported video file format extensions on the camera roll.
 * These extensions are only used to generate filenames. The actual formatting
 * of the video data is the responsibility of the application writing to the
 * file.
 */
typedef enum {
    /**
     * Use the system-specified default video file format extension.
     */
    CAMERA_ROLL_VIDEO_FMT_DEFAULT = 0,
    /**
     * Video files are saved to the camera roll with an ".mp4" extension.
     */
    CAMERA_ROLL_VIDEO_FMT_MP4,
} camera_roll_video_fmt_t;


/**
 * @brief Retrieve the current build version of the Camera library
 * @details The API build version is useful to ensure that certain calls are
 *          available. You can use the returned value to compare to the @c
 *          #CAMERA_API_VERSION to determine if the runtime library is different
 *          from the version your application was compiled with. Differences
 *          may indicate potential incompatibilities.
 *
 *          For more information about current and previous versions, see
 *          @c #CAMERA_API_VERSION.
 *
 * @return A value representing the version of the Camera library.
 */
int
camera_get_api_version(void);


/**
 * @brief Request a handle to access a logical camera unit
 * @details If the camera is available, a handle for exclusive access to the
 *          camera unit is returned. You must pass in a @c ::camera_handle_t
 *          value to store the handle. You must also have access permissions to
 *          use the camera.
 *
 * @b Note: This function call may block for several seconds if another
 *          application already has the camera open.
 *
 * @param unit The logical camera unit to open.
 * @param mode The access mode of the camera, which is comprised of the
 *             @c camapi_camera_modeflags flags ORed together.
 * @param handle A pointer to the returned camera handle if access is granted.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_open(camera_unit_t unit,
            uint32_t mode,
            camera_handle_t *handle);


/**
 * @brief Discontinue use of a logical camera on the device
 *
 * @details Any internal resources associated with a previously
 *          opened camera unit are freed.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_close(camera_handle_t handle);


/**
 * @brief Retrieve an enumerated list of cameras available on the device
 * @details An array of camera units is returned in the @c cameras
 *          argument.
 *
 *          Ensure that the @c cameras argument points to an array which has at
 *          least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          cameras argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in the @c numsupported argument. You can then allocate an array of
 *          the appropriate size and invoke the function again with the @c
 *          numasked argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 * @param numasked The requested number of camera units to return in the
 *                 array.
 * @param numsupported A pointer to the number of camera units that you have
 *                     access to. The argument is updated when the function
 *                     completes successfully.
 * @param cameras A pointer to the first element in a @c ::camera_unit_t array.
 *                The array is updated with the cameras that you have access
 *                to when the function completes successfully.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_supported_cameras(unsigned int numasked,
                             unsigned int *numsupported,
                             camera_unit_t *cameras);


/**
 * @brief Retrieve the list of supported viewfinder modes
 * @details Use this function to determine which viewfinder modes can be
 *          selected using the @c camera_set_vf_mode() function.
 *
 *          For more information about new and deprecated viewfinder
 *          functionality, see @ref camapi_viewfinder_modes.
 *
 *          Ensure that the @c modes argument points to an array which has at
 *          least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          modes argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in the @c numsupported argument. You can then allocate an array of
 *          the appropriate size and invoke the function again with the @c
 *          numasked argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of viewfinder modes to return in the
 *                 @c modes array. You can specify a value of 0 to determine the
 *                 number of viewfinder modes supported.
 * @param numsupported A pointer to an integer that will be updated with the
 *                     number of viewfinder modes supported.
 * @param modes A pointer to a @c ::camera_vfmode_t array. The array is
 *              updated with the list of viewfinder modes supported.
 *              Ensure that you allocate an array with the
 *              same number of elements as the @c numasked argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_supported_vf_modes(camera_handle_t handle,
                              uint32_t numasked,
                              uint32_t *numsupported,
                              camera_vfmode_t *modes);


/**
 * @brief Set the viewfinder mode for a camera
 * @details A viewfinder mode must be selected prior to configuring and starting
 *          the viewfinder. Changing viewfinder modes is not allowed while the
 *          viewfinder is already running.
 *          The @c camera_get_supported_vf_modes() function should be called
 *          prior to setting the viewfinder mode to determine the supported
 *          viewfinder modes.
 *
 *          For more information about new and deprecated viewfinder
 *          functionality, see @ref camapi_viewfinder_modes.
 *
 * @b Note: Once you change the viewfinder mode using this
 *          @c camera_set_vf_mode() function, you can no longer use the
 *          deprecated viewfinder functions until you close and re-open the
 *          camera.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param mode The desired viewfinder mode to set the camera to.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_vf_mode(camera_handle_t handle,
                   camera_vfmode_t mode);


/**
 * @brief Query the viewfinder mode for a camera
 * @details Use this function to retrieve the currently configured
 *          viewfinder mode.
 *
 *          For more information about new and deprecated viewfinder
 *          functionality, see @ref camapi_viewfinder_modes.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param mode A pointer to @c ::camera_vfmode_t value in which to return the
 *             current viewfinder mode.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_vf_mode(camera_handle_t handle,
                   camera_vfmode_t *mode);


/**
 * @brief Start the viewfinder on the camera
 * @details Use this function to start the viewfinder on the camera. Only call
 *          this function if the viewfinder mode has been
 *          set to a value other than @c #CAMERA_VFMODE_DEFAULT using @c
 *          camera_set_vf_mode().
 *
 *          As of @c #CAMERA_API_VERSION 3 (BlackBerry 10.3.0), this function
 *          deprecates @c camera_start_photo_viewfinder() and
 *          @c camera_start_video_viewfinder().
 *          For more information about new and deprecated viewfinder
 *          functionality, see @ref camapi_viewfinder_modes.
 *
 *          Before calling this function, ensure that you:
 *           - Use the @c camera_set_vf_property() function to configure
 *             the viewfinder.
 *           - Create a screen window to be the parent of the child viewfinder
 *             window that will be created by this call.
 *
 *          Once the viewfinder is running, you can capture images, configure
 *          scene modes, adjust zoom levels, and other operations. In addition,
 *          you can reposition or resize the viewfinder window using the Screen
 *          and Windowing API. In order to retrieve a window handle to the
 *          viewfinder window that is created, you must listen for the
 *          appropriate @c SCREEN_EVENT_CREATE event using the Screen and
 *          Windowing API.
 *
 * @b Note: It is important that your application follows the guidelines for
 *          resource management outlined in @ref camapi_resource_management.
 *          If you do not observe these guidelines, your application is at
 *          risk of crashing due to memory access errors when resource
 *          arbitration is performed by the operating system.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param viewfinder_callback A function pointer to a function with the
 *                            following signature:
 * @code
 * void function_name( camera_handle_t,
 *                     camera_buffer_t*,
 *                     void* );
 * @endcode
 *                            The function is a callback that is invoked
 *                            when a viewfinder buffer becomes available.
 *                            Set this argument to @c NULL if no function
 *                            needs to be called.
 *                            For information about the callback arguments, see
 *                            @ref camapi_callback_mode.
 * @param status_callback A function pointer to a function with the following
 *                        signature:
 * @code
 * void function_name( camera_handle_t,
 *                     camera_devstatus_t,
 *                     uint16_t,
 *                     void* );
 * @endcode
 *                        The function is a callback that is invoked when
 *                        status events occur. Set this argument to @c NULL
 *                        if no function needs to be called.
 *                        For information about the callback arguments, see
 *                        @ref camapi_callback_mode.
 * @param arg The argument passed to all callback functions, which is the
 *            last argument in the callback functions.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_start_viewfinder(camera_handle_t handle,
                        void (*viewfinder_callback)
                             (camera_handle_t, camera_buffer_t*, void*),
                        void (*status_callback)
                             (camera_handle_t, camera_devstatus_t,
                              uint16_t, void*),
                        void *arg);


/**
 * @brief Stop using the viewfinder
 * @details You can only stop the viewfinder after you have successfully
 *          started it using @c camera_start_viewfinder().
 *          After you stop running the viewfinder, you can no longer capture
 *          images or record videos.
 *
 *          As of @c #CAMERA_API_VERSION 3 (BlackBerry 10.3.0), this function
 *          deprecates @c camera_stop_photo_viewfinder() and
 *          @c camera_stop_video_viewfinder().
 *          For more information about new and deprecated viewfinder
 *          functionality, see @ref camapi_viewfinder_modes.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_stop_viewfinder(camera_handle_t handle);


/**
 * @brief Determine whether a feature is available on the camera
 * @details The availability of a feature does not mean that the feature is
 *          usable. For example, this function may indicate that physical
 *          flash is available, but the feature actually may not be used
 *          until the viewfinder is active. To determine if a feature can be
 *          used in the camera's current state, use the @c camera_can_feature()
 *          function.
 *
 *          Many developers may choose to use the set of available features
 *          in order to determine whether their application will function
 *          properly, or whether a different behaviour may be required. For
 *          example: if @c #CAMERA_FEATURE_VIDEO is not supported, then they
 *          may disable any photo/video mode-switching buttons in their UI.
 *
 * @b Note: The set of available features may vary based on the current
 *          viewfinder mode. For more information, see @ref
 *          camapi_viewfinder_modes.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param feature The specific feature to query.
 * @return @c true when the specified feature is available on the camera,
 *         otherwise a value of @c false.
 */


bool
camera_has_feature(camera_handle_t handle,
                   camera_feature_t feature);


/**
 * @brief Determine whether a feature is available on the camera in its
 *        current state
 * @details The difference between this function and the @c
 *          camera_has_feature() function is that this function indicates the
 *          features on the camera are usable in the current
 *          camera state rather than just available.
 *
 *          Many developers may choose to use the set of usable features
 *          in order to disable specific UI elements in their application. For
 *          example: if @c #CAMERA_FEATURE_FLASH is usable when the photo
 *          viewfinder is running, but is not usable when the burst viewfinder
 *          is running, then they may choose to gray out a flash toggle button
 *          in their UI, or they may choose to opt for a longer exposure to
 *          compensate in darker scenes.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param feature The specific feature to query.
 * @return @c true when the specified feature is currently usable on the camera,
 *         otherwise a value of @c false.
 */
bool
camera_can_feature(camera_handle_t handle,
                   camera_feature_t feature);


/**
 * @brief Find the cameras that have the specified features
 * @details Use this function to find cameras with the features required for
 *          your application. For example, you can use it to find cameras which
 *          have a flash or that support video recording.
 *
 *          This function provides a list of cameras by implementing an
 *          iterator.
 *
 *          To start iterating through the cameras, set the @c
 *          prevunit argument to @c #CAMERA_UNIT_NONE. Doing so returns the
 *          first camera found by the iterator that supports the list of
 *          features defined by @c features. The matching camera unit is
 *          returned in the @c nextunit argument. To continue iterating through
 *          the list, you can call this function again and set @c prevunit to
 *          the value previously returned by @c nextunit. In this way, the
 *          function is always searching the list using @c prevunit as the
 *          starting point.
 *          When the end of the list is reached, @c nextunit returns a value of
 *          @c #CAMERA_UNIT_NONE.
 *
 * @param features A pointer to an array of @c ::camera_feature_t values.
 * @param nfeatures The number of features specified in the first argument.
 * @param prevunit The previous unit that was returned or @c #CAMERA_UNIT_NONE
 *                 if this is the first call to this function.
 * @param nextunit A pointer to a @c ::camera_unit_t value where the function
 *                 returns the next unit which supports all requested
 *                 features.
 * @return @c #CAMERA_EOK when the function successfully completes.
 *         @c #CAMERA_ENODEV indicates that the end of list was reached.
 */
camera_error_t
camera_find_capable(camera_feature_t *features,
                    int nfeatures,
                    camera_unit_t prevunit,
                    camera_unit_t *nextunit);


/**
 * @brief Get the list of supported viewfinder resolutions
 * @details After you use this function to retrieve the viewfinder resolutions
 *          that are supported by the camera, you can configure the viewfinder
 *          size using @c camera_set_vf_property().
 *
 *          As of @c #CAMERA_API_VERSION 3 (BlackBerry 10.3.0), this function
 *          deprecates @c camera_get_photo_vf_resolutions() and
 *          @c camera_get_video_vf_resolutions().
 *          For more information about new and deprecated viewfinder
 *          functionality, see @ref camapi_viewfinder_modes.
 *
 *          Ensure that the @c resolutions argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          resolutions argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in the @c numsupported argument. You can then allocate an array of
 *          the appropriate size and invoke the function again with the @c
 *          numasked argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of viewfinder resolutions to return in
 *                 the @c resolutions array. You can use a value of 0 to
 *                 determine the number of viewfinder resolutions
 *                 supported by the camera.
 * @param numsupported The returned number of viewfinder resolutions supported
 *                     by the specified camera.
 * @param resolutions A pointer to a @c ::camera_res_t array. The array
 *                    is updated with the viewfinder resolutions supported by
 *                    the camera. Ensure that you allocate an array with the
 *                    same number of elements as specified in the @c numasked
 *                    argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_supported_vf_resolutions(camera_handle_t handle,
                                    uint32_t numasked,
                                    uint32_t *numsupported,
                                    camera_res_t *resolutions);


/**
 * @brief Retrieve the list of supported viewfinder rotation angles
 * @details After you use this function to retrieve the viewfinder rotations
 *          that are supported by the camera, you can configure the viewfinder
 *          rotation using @c camera_set_vf_property().
 *
 *          As of @c #CAMERA_API_VERSION 3 (BlackBerry 10.3.0), this function
 *          deprecates @c camera_get_photo_vf_rotations() and
 *          @c camera_get_video_vf_rotations().
 *          For more information about new and deprecated viewfinder
 *          functionality, see @ref camapi_viewfinder_modes.
 *
 *          Typical rotations are multiples of 90 degrees (called square
 *          rotations), such as 0, 90, 180, and 270. For cameras that
 *          support only square rotations, a value of @c false will be
 *          returned in the @c nonsquare argument.
 *
 *          Ensure that the @c rotations argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          rotations argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in the @c numsupported argument. You can then allocate an array of
 *          the appropriate size and invoke the function again with the @c
 *          numasked argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param frametype The frame type to query supported rotations for. Using
 *                  @c #CAMERA_FRAMETYPE_UNSPECIFIED will return the supported
 *                  rotations for the currently configured frame type.
 * @param numasked The requested number of viewfinder rotations to return in the
 *                 @c rotations array. You can use a value of 0 to
 *                 determine the number of viewfinder rotations
 *                 supported by the camera.
 * @param numsupported The returned number of viewfinder rotations supported by
 *                     the specified camera.
 * @param rotations A pointer to a @c uint32_t array. The array
 *                  is updated with the viewfinder rotations supported by
 *                  the camera. Ensure that you allocate an array with the
 *                  same number of elements as specified in the @c numasked
 *                  argument.
 * @param nonsquare  The value updated to reflect whether the camera supports
 *                   rotation of viewfinder images that are not a square angle
 *                   (multiples of 90 degrees).
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_supported_vf_rotations(camera_handle_t handle,
                                  camera_frametype_t frametype,
                                  uint32_t numasked,
                                  uint32_t *numsupported,
                                  uint32_t *rotations,
                                  bool *nonsquare);


/**
 * @brief Retrieve the viewfinder frame types available on the camera
 * @details Use this function to retrieve the viewfinder frame
 *          types supported by the current camera.
 *          The returned formats can be applied to @c #CAMERA_IMGPROP_FORMAT
 *          using the @c camera_set_vf_property() function.
 *
 *          As of @c #CAMERA_API_VERSION 3 (BlackBerry 10.3.0), this function
 *          deprecates @c camera_get_photovf_frame_types() and
 *          @c camera_get_videovf_frame_types().
 *          For more information about new and deprecated viewfinder
 *          functionality, see @ref camapi_viewfinder_modes.
 *
 *          Ensure that the @c frametypes argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          types argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in the @c numsupported argument. You can then allocate an array of
 *          the appropriate size and invoke the function again with the @c
 *          numasked argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of viewfinder frame types to return in
 *                 the @c frametypes array. You can use a value of 0 to
 *                 determine the number of viewfinder frame types
 *                 supported by the camera.
 * @param numsupported The returned number of viewfinder frame types supported
 *                     by the specified camera.
 * @param frametypes A pointer to a @c ::camera_frametype_t array. The array
 *                   is updated with the viewfinder frame types supported by
 *                   the camera. Ensure that you allocate an array with the
 *                   same number of elements as specified in the @c numasked
 *                   argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_supported_vf_frametypes(camera_handle_t handle,
                                   uint32_t numasked,
                                   uint32_t *numsupported,
                                   camera_frametype_t *frametypes);


/**
 * @brief Retrieve the supported viewfinder frame rates
 * @details Use this function to retrieve the set of supported
 *          viewfinder frame rates. You can use the values returned by
 *          this function to configure the viewfinder frame rate using
 *          @c camera_set_vf_property().
 *
 *          As of @c #CAMERA_API_VERSION 3 (BlackBerry 10.3.0), this function
 *          deprecates @c camera_get_photo_vf_framerates() and
 *          @c camera_get_video_vf_framerates().
 *          For more information about new and deprecated viewfinder
 *          functionality, see @ref camapi_viewfinder_modes.
 *
 *          Ensure that the @c rates argument points to an array
 *          which has at least @c numasked elements allocated. To
 *          determine an appropriate size for this array, you can invoke this
 *          function in @e presizing mode by setting the @c numasked argument to
 *          to 0 or the @c rates argument to @c NULL. When the function is
 *          invoked in @e presizing mode, the maximum array size that is
 *          required is returned in the @c numsupported argument. You can then
 *          allocate an array of the appropriate size and invoke the function
 *          again with the @c numasked argument set to the value returned
 *          previously in the @c numsupported argument.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param frametype The frame type to query supported frame rates for. Using
 *                  @c #CAMERA_FRAMETYPE_UNSPECIFIED will return the supported
 *                  frame rates for the currently configured frame type.
 * @param numasked The requested number of frame rates to return in the
 *                 @c rates array. You can use a value of 0 to
 *                 determine the number of viewfinder frame rates
 *                 supported by the camera.
 * @param numsupported The returned number of frame rates supported by the
 *                     specified camera.
 * @param rates A pointer to a @c double array. The array
 *              is updated with the viewfinder frame rates supported by
 *              the camera. Ensure that you allocate an array with the
 *              same number of elements as specified in the @c numasked
 *              argument. If the @c maxmin flag returns @c true, then
 *              the first value returned in the @c rates array is the maximum
 *              supported frame rate, and the second value returned is the
 *              minimum supported frame rate.
 * @param maxmin A pointer to a @c bool value which will be set to @c true
 *               if the values returned should be interpreted as a maximum and
 *               a minimum value, or set to @c false if the values only
 *               describe the discrete frame rates that are supported.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_supported_vf_framerates(camera_handle_t handle,
                                   camera_frametype_t frametype,
                                   uint32_t numasked,
                                   uint32_t *numsupported,
                                   double *rates,
                                   bool *maxmin);


/**
 * @brief Configure one or more settings of the viewfinder
 *
 * @details As of @c #CAMERA_API_VERSION 3 (BlackBerry 10.3.0), this function
 *          deprecates @c camera_set_photovf_property() and
 *          @c camera_set_videovf_property().
 *          For more information about new and deprecated viewfinder
 *          functionality, see @ref camapi_viewfinder_modes.
 *
 *          For the @c args argument, you can provide one or more
 *          property-value pairs using @c ::camera_imgprop_t values as the name
 *          of the property and the correct type for the value such as an
 *          @c int or @c double value. The following
 *          @c ::camera_imgprop_t values can be used with this function:
 *           - @c #CAMERA_IMGPROP_WIN_GROUPID
 *           - @c #CAMERA_IMGPROP_WIN_ID
 *           - @c #CAMERA_IMGPROP_CREATEWINDOW
 *           - @c #CAMERA_IMGPROP_RENDERTOWINDOW
 *           - @c #CAMERA_IMGPROP_FORMAT
 *           - @c #CAMERA_IMGPROP_WIDTH
 *           - @c #CAMERA_IMGPROP_HEIGHT
 *           - @c #CAMERA_IMGPROP_FRAMERATE
 *           - @c #CAMERA_IMGPROP_ROTATION
 *           - @c #CAMERA_IMGPROP_HWOVERLAY
 *           - @c #CAMERA_IMGPROP_ISEMBEDDED
 *           - @c #CAMERA_IMGPROP_ZOOMFACTOR
 *           - @c #CAMERA_IMGPROP_VARIABLEFRAMERATE
 *           - @c #CAMERA_IMGPROP_MINFRAMERATE
 *           - @c #CAMERA_IMGPROP_MAXFOV
 *
 *           @b Note: There is no type-checking performed by the compiler,
 *                    therefore, you must ensure that the value you provide
 *                    for each property-value pair matches the expected data
 *                    type. Data type mismatches can result in undefined
 *                    behavior and may cause your application to crash.
 *
 *           You can specify multiple property-value pairs by delimiting them
 *           with a comma as follows:
 * @code
 * camera_set_vf_property( camera_handle,
 *                         CAMERA_IMGPROP_WIN_GROUPID, "mygroup",
 *                         CAMERA_IMGPROP_WIN_ID, "vfwindow",
 *                         CAMERA_IMGPROP_WIDTH, 720,
 *                         CAMERA_IMGPROP_HEIGHT, 1280,
 *                         CAMERA_IMGPROP_ROTATION, 270,
 *                         CAMERA_IMGPROP_FRAMERATE, (double)15.0 );
 * @endcode
 *
 * @b Note: The following properties can't be changed while the viewfinder
 *          is running:
 *           - @c #CAMERA_IMGPROP_WIN_ID
 *           - @c #CAMERA_IMGPROP_CREATEWINDOW
 *           - @c #CAMERA_IMGPROP_FORMAT
 *           - @c #CAMERA_IMGPROP_ISEMBEDDED
 *           - @c #CAMERA_IMGPROP_HWOVERLAY
 *           - @c #CAMERA_IMGPROP_MAXFOV
 *          When the viewfinder is running, then
 *          @c #CAMERA_IMGPROP_WIN_GROUPID can only be changed if the
 *          current value is an empty string.
 *
 * @b Note: The following properties can't be changed while a non-video
 *          viewfinder is running:
 *           - @c #CAMERA_IMGPROP_WIDTH
 *           - @c #CAMERA_IMGPROP_HEIGHT
 *           - @c #CAMERA_IMGPROP_ROTATION
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param args... A series of comma-delimited property-value pairs.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
#define camera_set_vf_property(handle, args...) \
camera_private_set_vf_property(handle, args, CAMERA_IMGPROP_END)


/**
 * @internal
 * For internal use only. Use the @c camera_set_vf_property() function
 * instead which auto-terminates the ... varargs list.
 */
camera_error_t
camera_private_set_vf_property(camera_handle_t handle, ...);


/**
 * @brief Retrieve one or more properties of the viewfinder
 *
 * @details As of @c #CAMERA_API_VERSION 3 (BlackBerry 10.3.0), this function
 *          deprecates @c camera_get_photovf_property() and
 *          @c camera_get_videovf_property().
 *          For more information about new and deprecated viewfinder
 *          functionality, see @ref camapi_viewfinder_modes.
 *
 *          For the @c args argument, you can provide one or more
 *          property-value pairs using @c ::camera_imgprop_t values as the name
 *          of the property and a pointer to the correct type for the value such
 *          as an @c int or @c double value. The following @c
 *          ::camera_imgprop_t can be used with this function:
 *           - @c #CAMERA_IMGPROP_WIN_GROUPID
 *           - @c #CAMERA_IMGPROP_WIN_ID
 *           - @c #CAMERA_IMGPROP_CREATEWINDOW
 *           - @c #CAMERA_IMGPROP_RENDERTOWINDOW
 *           - @c #CAMERA_IMGPROP_FORMAT
 *           - @c #CAMERA_IMGPROP_WIDTH
 *           - @c #CAMERA_IMGPROP_HEIGHT
 *           - @c #CAMERA_IMGPROP_FRAMERATE
 *           - @c #CAMERA_IMGPROP_ROTATION
 *           - @c #CAMERA_IMGPROP_HWOVERLAY
 *           - @c #CAMERA_IMGPROP_ISEMBEDDED
 *           - @c #CAMERA_IMGPROP_ZOOMFACTOR
 *           - @c #CAMERA_IMGPROP_VARIABLEFRAMERATE
 *           - @c #CAMERA_IMGPROP_MINFRAMERATE
 *           - @c #CAMERA_IMGPROP_MAXFOV
 *
 *           @b Note: There is no type-checking performed by the compiler,
 *                    therefore, you must ensure that the value you provide
 *                    for each property matches the expected data type. Data
 *                    type mismatches can result in undefined
 *                    behavior and may cause your application to crash.
 *
 *           You can specify multiple property-value pairs by delimiting them
 *           with a comma as follows:
 * @code
 * camera_get_vf_property( camera_handle,
 *                         CAMERA_IMGPROP_WIDTH, &vf_width,
 *                         CAMERA_IMGPROP_HEIGHT, &vf_height,
 *                         CAMERA_IMGPROP_ROTATION, &vf_rotation,
 *                         CAMERA_IMGPROP_FRAMERATE, &framerate );
 * @endcode
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param args... A series of comma-delimited property-value pairs where each
 *                value must be a pointer a variable of the expected type.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
#define camera_get_vf_property(handle, args...) \
camera_private_get_vf_property(handle, args, CAMERA_IMGPROP_END)


/**
 * @internal
 * For internal use only. Use the @c camera_get_vf_property() function
 * instead which auto-terminates the ... varargs list.
 */
camera_error_t
camera_private_get_vf_property(camera_handle_t handle, ...);


/**
 * @brief Retrieve the supported output resolutions for photo capture
 * @details After you use this function to retrieve the photo resolutions
 *          that are supported by the camera on the device, you can
 *          configure the photo size using @c camera_set_photo_property().
 *
 *          Ensure that the @c resolutions argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          resolutions argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in the @c numsupported argument. You can then allocate an array of
 *          the appropriate size and invoke the function again with the @c
 *          numasked argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param outputformat The frame type that the viewfinder supports.
 * @param numasked The requested number of photo resolutions to return in the
 *                 @c resolutions array. You can use a value of 0 to
 *                 determine the number of photo resolutions
 *                 supported by the camera.
 * @param numsupported The returned number of photo resolutions supported by the
 *                     specified camera.
 * @param resolutions A pointer to a @c ::camera_res_t array. The array
 *                    is updated with the photo resolutions supported by
 *                    the camera. Ensure that you allocate an array with the
 *                    same number of elements as specified in the @c numasked
 *                    argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_photo_output_resolutions(camera_handle_t handle,
                                    camera_frametype_t outputformat,
                                    unsigned int numasked,
                                    unsigned int *numsupported,
                                    camera_res_t *resolutions);


/**
 * @brief Retrieve the supported output resolutions for video
 * @details After you use this function to retrieve the video resolutions that
 *          are supported by the camera, you can configure the video size using
 *          @c camera_set_video_property().
 *
 *          Ensure that the @c resolutions argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          resolutions argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in the @c numsupported argument. You can then allocate an array of
 *          the appropriate size and invoke the function again with the @c
 *          numasked argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of video resolutions to return in the
 *                 @c resolutions array. You can use a value of 0 to
 *                 determine the number of video resolutions
 *                 supported by the camera.
 * @param numsupported The returned number of video resolutions supported by the
 *                     specified camera.
 * @param resolutions A pointer to a @c ::camera_res_t array. The array
 *                    is updated with the video resolutions supported by
 *                    the camera. Ensure that you allocate an array with the
 *                    same number of elements as specified in the @c numasked
 *                    argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_video_output_resolutions(camera_handle_t handle,
                                    unsigned int numasked,
                                    unsigned int *numsupported,
                                    camera_res_t *resolutions);


/**
 * @brief (Deprecated) Get the list of supported photo viewfinder resolutions
 *
 * @deprecated As of @c #CAMERA_API_VERSION 3 (BlackBerry 10.3.0).
 *             Instead, use the @c camera_get_supported_vf_resolutions()
 *             function.
 *             For more information about new and deprecated viewfinder
 *             functionality, see @ref camapi_viewfinder_modes.
 *
 * @details After you use this function to retrieve the photo viewfinder
 *          resolutions that are supported by the camera, you can configure
 *          the photo viewfinder size using @c camera_set_photovf_property().
 *
 *          Ensure that the @c resolutions argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          resolutions argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in the @c numsupported argument. You can then allocate an array of
 *          the appropriate size and invoke the function again with the @c
 *          numasked argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of photo viewfinder resolutions to
 *                 return in the @c resolutions array. You can use a value of
 *                 0 to determine the number of photo viewfinder
 *                 resolutions supported by the camera.
 * @param numsupported The returned number of photo viewfinder resolutions
 *                     supported by the specified camera.
 * @param resolutions A pointer to a @c ::camera_res_t array. The array
 *                    is updated with the photo viewfinder resolutions supported
 *                    by the camera. Ensure that you allocate an array with the
 *                    same number of elements as specified in the @c numasked
 *                    argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_photo_vf_resolutions(camera_handle_t handle,
                                unsigned int numasked,
                                unsigned int *numsupported,
                                camera_res_t *resolutions);


/**
 * @brief (Deprecated) Get the list of supported video viewfinder resolutions
 *
 * @deprecated As of @c #CAMERA_API_VERSION 3 (BlackBerry 10.3.0).
 *             Instead, use the @c camera_get_supported_vf_resolutions()
 *             function.
 *             For more information about new and deprecated viewfinder
 *             functionality, see @ref camapi_viewfinder_modes.
 *
 * @details After you use this function to retrieve the video viewfinder
 *          resolutions that are supported by the camera, you can configure
 *          the video viewfinder size using @c camera_set_videovf_property().
 *
 *          Ensure that the @c resolutions argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          resolutions argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in the @c numsupported argument. You can then allocate an array of
 *          the appropriate size and invoke the function again with the @c
 *          numasked argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of video viewfinder resolutions to
 *                 return in the @c resolutions array. You can use a value of
 *                 0 to determine the number of video viewfinder
 *                 resolutions supported by the camera.
 * @param numsupported The returned number of video viewfinder resolutions
 *                     supported by the specified camera.
 * @param resolutions A pointer to a @c ::camera_res_t array. The array
 *                    is updated with the video viewfinder resolutions supported
 *                    by the camera. Ensure that you allocate an array with the
 *                    same number of elements as specified in the @c numasked
 *                    argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_video_vf_resolutions(camera_handle_t handle,
                                unsigned int numasked,
                                unsigned int *numsupported,
                                camera_res_t *resolutions);


/**
 * @brief (Deprecated) Configure one or more settings of the photo viewfinder
 *
 * @deprecated As of @c #CAMERA_API_VERSION 3 (BlackBerry 10.3.0).
 *             Instead, use the @c camera_set_vf_property() function.
 *             For more information about new and deprecated viewfinder
 *             functionality, see @ref camapi_viewfinder_modes.
 *
 * @details For the @c args argument, you can provide one or more
 *          property-value pairs using @c ::camera_imgprop_t values as the name
 *          of the property and the correct type for the value such as an
 *          @c int or @c double value. The following
 *          @c ::camera_imgprop_t can be used with this function:
 *           - @c #CAMERA_IMGPROP_WIN_GROUPID
 *           - @c #CAMERA_IMGPROP_WIN_ID
 *           - @c #CAMERA_IMGPROP_RENDERTOWINDOW
 *           - @c #CAMERA_IMGPROP_FORMAT
 *           - @c #CAMERA_IMGPROP_WIDTH
 *           - @c #CAMERA_IMGPROP_HEIGHT
 *           - @c #CAMERA_IMGPROP_FRAMERATE
 *           - @c #CAMERA_IMGPROP_ROTATION
 *           - @c #CAMERA_IMGPROP_HWOVERLAY
 *           - @c #CAMERA_IMGPROP_ISEMBEDDED
 *           - @c #CAMERA_IMGPROP_ZOOMFACTOR
 *           - @c #CAMERA_IMGPROP_BURSTMODE
 *           - @c #CAMERA_IMGPROP_VARIABLEFRAMERATE
 *           - @c #CAMERA_IMGPROP_MINFRAMERATE
 *           - @c #CAMERA_IMGPROP_MAXFOV
 *
 *           @b Note: There is no type-checking performed by the compiler,
 *                    therefore, you must ensure that the value you provide
 *                    for each property-value pair matches the expected data
 *                    type. Data type mismatches can result in undefined
 *                    behavior and may cause your application to crash.
 *
 *           You can specify multiple property-value pairs by delimiting them
 *           with a comma as follows:
 * @code
 * camera_set_vf_property( camera_handle,
 *                         CAMERA_IMGPROP_WIN_GROUPID, "mygroup",
 *                         CAMERA_IMGPROP_WIN_ID, "vfwindow",
 *                         CAMERA_IMGPROP_WIDTH, 720,
 *                         CAMERA_IMGPROP_HEIGHT, 1280,
 *                         CAMERA_IMGPROP_ROTATION, 270,
 *                         CAMERA_IMGPROP_FRAMERATE, (double)15.0 );
 * @endcode
 *
 * @b Note: The following properties can't be changed while the viewfinder is
 *          running:
 *           - @c #CAMERA_IMGPROP_WIN_ID
 *           - @c #CAMERA_IMGPROP_FORMAT
 *           - @c #CAMERA_IMGPROP_WIDTH
 *           - @c #CAMERA_IMGPROP_HEIGHT
 *           - @c #CAMERA_IMGPROP_ROTATION
 *           - @c #CAMERA_IMGPROP_HWOVERLAY
 *           - @c #CAMERA_IMGPROP_BURSTMODE
 *           - @c #CAMERA_IMGPROP_ISEMBEDDED
 *           - @c #CAMERA_IMGPROP_MAXFOV
 *          When the viewfinder is running, then
 *          @c #CAMERA_IMGPROP_WIN_GROUPID can only be changed if the
 *          current value is an empty string.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param args... A series of comma-delimited property-value pairs.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
#define camera_set_photovf_property(handle, args...) \
        _camera_set_photovf_property(handle, args, CAMERA_IMGPROP_END)


/**
 * @internal
 * @deprecated
 * For internal use only. Use the @c camera_set_photovf_property() function
 * instead which auto-terminates the ... varargs list.
 */
camera_error_t
_camera_set_photovf_property(camera_handle_t handle,
                             ...);


/**
 * @brief (Deprecated) Retrieve one or more properties of the photo viewfinder
 *
 * @deprecated As of @c #CAMERA_API_VERSION 3 (BlackBerry 10.3.0).
 *             Instead, use the @c camera_get_vf_property() function.
 *             For more information about new and deprecated viewfinder
 *             functionality, see @ref camapi_viewfinder_modes.
 *
 * @details For the @c args argument, you can provide one or more
 *          property-value pairs using @c ::camera_imgprop_t values as the name
 *          of the property and a pointer to the correct type for the value such
 *          as an @c int or @c double value. The following @c
 *          ::camera_imgprop_t can be used with this function:
 *           - @c #CAMERA_IMGPROP_WIN_GROUPID
 *           - @c #CAMERA_IMGPROP_WIN_ID
 *           - @c #CAMERA_IMGPROP_RENDERTOWINDOW
 *           - @c #CAMERA_IMGPROP_FORMAT
 *           - @c #CAMERA_IMGPROP_WIDTH
 *           - @c #CAMERA_IMGPROP_HEIGHT
 *           - @c #CAMERA_IMGPROP_FRAMERATE
 *           - @c #CAMERA_IMGPROP_ROTATION
 *           - @c #CAMERA_IMGPROP_HWOVERLAY
 *           - @c #CAMERA_IMGPROP_ISEMBEDDED
 *           - @c #CAMERA_IMGPROP_ZOOMFACTOR
 *           - @c #CAMERA_IMGPROP_BURSTMODE
 *           - @c #CAMERA_IMGPROP_VARIABLEFRAMERATE
 *           - @c #CAMERA_IMGPROP_MINFRAMERATE
 *           - @c #CAMERA_IMGPROP_MAXFOV
 *
 *           @b Note: There is no type-checking performed by the compiler,
 *                    therefore, you must ensure that the value you provide
 *                    for each property matches the expected data type. Data
 *                    type mismatches can result in undefined
 *                    behavior and may cause your application to crash.
 *
 *           You can specify multiple property-value pairs by delimiting them
 *           with a comma as follows:
 * @code
 * camera_get_photovf_property( camera_handle,
 *                              CAMERA_IMGPROP_WIDTH, &vf_width,
 *                              CAMERA_IMGPROP_HEIGHT, &vf_height,
 *                              CAMERA_IMGPROP_ROTATION, &vf_rotation,
 *                              CAMERA_IMGPROP_BURSTMODE, &burstmode,
 *                              CAMERA_IMGPROP_FRAMERATE, &framerate );
 * @endcode
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param args... A series of comma-delimited property-value pairs where each
 *                value must be a pointer a variable of the expected type.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
#define camera_get_photovf_property(handle, args...) \
        _camera_get_photovf_property(handle, args, CAMERA_IMGPROP_END)


/**
 * @internal
 * @deprecated
 * For internal use only. Use the @c camera_get_photovf_property() function
 * instead which auto-terminates the ... varargs list.
 */
camera_error_t
_camera_get_photovf_property(camera_handle_t handle,
                             ...);


/**
 * @brief (Deprecated) Configure one or more settings of the video viewfinder
 *
 * @deprecated As of @c #CAMERA_API_VERSION 3 (BlackBerry 10.3.0).
 *             Instead, use the @c camera_set_vf_property() function.
 *             For more information about new and deprecated viewfinder
 *             functionality, see @ref camapi_viewfinder_modes.
 *
 * @details For the @c args argument, you can provide one or more
 *          property-value pairs using @c ::camera_imgprop_t values as the name
 *          of the property and the correct type for the value such as an
 *          @c int or @c double value. The following @c
 *          ::camera_imgprop_t can be used with this function:
 *           - @c #CAMERA_IMGPROP_WIN_GROUPID
 *           - @c #CAMERA_IMGPROP_WIN_ID
 *           - @c #CAMERA_IMGPROP_RENDERTOWINDOW
 *           - @c #CAMERA_IMGPROP_FORMAT
 *           - @c #CAMERA_IMGPROP_WIDTH
 *           - @c #CAMERA_IMGPROP_HEIGHT
 *           - @c #CAMERA_IMGPROP_FRAMERATE
 *           - @c #CAMERA_IMGPROP_ROTATION
 *           - @c #CAMERA_IMGPROP_HWOVERLAY
 *           - @c #CAMERA_IMGPROP_ISEMBEDDED
 *           - @c #CAMERA_IMGPROP_CREATEWINDOW
 *           - @c #CAMERA_IMGPROP_ZOOMFACTOR
 *           - @c #CAMERA_IMGPROP_MAXFOV
 *
 *           @b Note: There is no type-checking performed by the compiler,
 *                    therefore, you must ensure that the value you provide
 *                    for each property matches the expected data type. Data
 *                    type mismatches can result in undefined
 *                    behavior and may cause your application to crash.
 *
 *           You can specify multiple property-value pairs by delimiting them
 *           with a comma as follows:
 * @code
 * camera_set_videovf_property( camera_handle,
 *                              CAMERA_IMGPROP_WIN_GROUPID, "mygroup",
 *                              CAMERA_IMGPROP_WIN_ID, "vfwindow",
 *                              CAMERA_IMGPROP_WIDTH, 720,
 *                              CAMERA_IMGPROP_HEIGHT, 1280,
 *                              CAMERA_IMGPROP_ROTATION, 270,
 *                              CAMERA_IMGPROP_FRAMERATE, (double)30.0 );
 * @endcode
 *
 * @b Note: The following properties can't be changed while the viewfinder is
 *          running:
 *           - @c #CAMERA_IMGPROP_WIN_ID
 *           - @c #CAMERA_IMGPROP_FORMAT
 *           - @c #CAMERA_IMGPROP_HWOVERLAY
 *           - @c #CAMERA_IMGPROP_CREATEWINDOW
 *           - @c #CAMERA_IMGPROP_ISEMBEDDED
 *           - @c #CAMERA_IMGPROP_MAXFOV
 *          When the viewfinder is running, then
 *          @c #CAMERA_IMGPROP_WIN_GROUPID can only be changed if the
 *          current value is an empty string.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param args... A series of comma-delimited property-value pairs where each
 *                value must be a pointer a variable of the expected type.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
#define camera_set_videovf_property(handle, args...) \
        _camera_set_videovf_property(handle, args, CAMERA_IMGPROP_END)


/**
 * @internal
 * @deprecated
 * For internal use only. Use the camera_set_videovf_property() function
 * instead which auto-terminates the ... varargs list.
 */
camera_error_t
_camera_set_videovf_property(camera_handle_t handle,
                             ...);


/**
 * @brief (Deprecated) Retrieve one or more properties of the video viewfinder
 *
 * @deprecated As of @c #CAMERA_API_VERSION 3 (BlackBerry 10.3.0).
 *             Instead, use the @c camera_get_vf_property() function.
 *             For more information about new and deprecated viewfinder
 *             functionality, see @ref camapi_viewfinder_modes.
 *
 * @details For the @c args argument, you can provide one or more
 *          property-value pairs using @c ::camera_imgprop_t values as the name
 *          of the property and a pointer to the correct type for the value such
 *          as an @c int or @c double value. The following @c
 *          ::camera_imgprop_t can be used with this function:
 *           - @c #CAMERA_IMGPROP_WIN_GROUPID
 *           - @c #CAMERA_IMGPROP_WIN_ID
 *           - @c #CAMERA_IMGPROP_RENDERTOWINDOW
 *           - @c #CAMERA_IMGPROP_FORMAT
 *           - @c #CAMERA_IMGPROP_WIDTH
 *           - @c #CAMERA_IMGPROP_HEIGHT
 *           - @c #CAMERA_IMGPROP_FRAMERATE
 *           - @c #CAMERA_IMGPROP_ROTATION
 *           - @c #CAMERA_IMGPROP_HWOVERLAY
 *           - @c #CAMERA_IMGPROP_ISEMBEDDED
 *           - @c #CAMERA_IMGPROP_CREATEWINDOW
 *           - @c #CAMERA_IMGPROP_ZOOMFACTOR
 *           - @c #CAMERA_IMGPROP_MAXFOV
 *
 *           @b Note: There is no type-checking performed by the compiler,
 *                    therefore, you must ensure that the value you provide
 *                    for each property matches the expected data type. Data
 *                    type mismatches can result in undefined
 *                    behavior and may cause your application to crash.
 *
 *           You can specify multiple property-value pairs by delimiting them
 *           with a comma as follows:
 * @code
 * camera_get_videovf_property( camera_handle,
 *                              CAMERA_IMGPROP_WIDTH, &vf_width,
 *                              CAMERA_IMGPROP_HEIGHT, &vf_height,
 *                              CAMERA_IMGPROP_ROTATION, &vf_rotation,
 *                              CAMERA_IMGPROP_FRAMERATE, &vf_framerate );
 * @endcode
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param args... A series of comma-delimited property-value pairs where each
 *                value must be a pointer a variable of the expected type.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
#define camera_get_videovf_property(handle, args...) \
        _camera_get_videovf_property(handle, args, CAMERA_IMGPROP_END)


/**
 * @internal
 * @deprecated
 * For internal use only. Use the camera_set_videovf_property() function
 * instead which auto-terminates the ... varargs list.
 */
camera_error_t
_camera_get_videovf_property(camera_handle_t handle,
                             ...);


/**
 * @brief (Deprecated) Start the photo viewfinder on the camera
 *
 * @deprecated As of @c #CAMERA_API_VERSION 3 (BlackBerry 10.3.0).
 *             Instead, use the @c camera_start_viewfinder() function.
 *             For more information about new and deprecated viewfinder
 *             functionality, see @ref camapi_viewfinder_modes.
 *
 * @details This function can only be called if the @c #CAMERA_FEATURE_PHOTO
 *          feature is available. You can determine whether this feature is
 *          available by calling the @c camera_can_feature() function.
 *
 *          Before calling this function, ensure that you:
 *           - Use the @c camera_set_photovf_property() function to configure
 *             the photo viewfinder.
 *           - Use the @c camera_set_photo_property()  function to set any photo
 *             properties.
 *           - Create a screen window to be the parent of the child viewfinder
 *             window that will be created by this call.
 *
 *          Once the viewfinder is running, you can capture images, configure
 *          scene modes, adjust zoom levels, and other operations. In addition,
 *          you can reposition or resize the viewfinder window using the Screen
 *          and Windowing API. In order to retrieve a window handle to the
 *          viewfinder window that is created, you must listen for the
 *          appropriate @c SCREEN_EVENT_CREATE event using the Screen and
 *          Windowing API.
 *
 * @b Note: It is important that your application follows the guidelines for
 *          resource management outlined in @ref camapi_resource_management.
 *          If you do not observe these guidelines, your application is at
 *          risk of crashing due to memory access errors when resource
 *          arbitration is performed by the operating system.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param viewfinder_callback A function pointer to a function with the
 *                            following signature:
 * @code
 * void function_name( camera_handle_t,
 *                     camera_buffer_t*,
 *                     void* );
 * @endcode
 *                            The function is a callback that is invoked
 *                            when a viewfinder buffer becomes available.
 *                            Set this argument to @c NULL if no function
 *                            needs to be called.
 *                            For information about the callback arguments, see
 *                            @ref camapi_callback_mode.
 * @param status_callback A function pointer to a function with the following
 *                        signature:
 * @code
 * void function_name( camera_handle_t,
 *                     camera_devstatus_t,
 *                     uint16_t,
 *                     void* );
 * @endcode
 *                        The function is a callback that is invoked when
 *                        status events occur. Set this argument to @c NULL
 *                        if no function needs to be called.
 *                        For information about the callback arguments, see
 *                        @ref camapi_callback_mode.
 * @param arg The argument passed to all callback functions, which is the
 *            last argument in the callback functions.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_start_photo_viewfinder(camera_handle_t handle,
                              void (*viewfinder_callback)
                                   (camera_handle_t, camera_buffer_t*, void*),
                              void (*status_callback)
                                   (camera_handle_t, camera_devstatus_t,
                                    uint16_t, void*),
                              void *arg);


/**
 * @brief (Deprecated) Start the video viewfinder on the camera
 *
 * @deprecated As of @c #CAMERA_API_VERSION 3 (BlackBerry 10.3.0).
 *             Instead, use the @c camera_start_viewfinder() function.
 *             For more information about new and deprecated viewfinder
 *             functionality, see @ref camapi_viewfinder_modes.
 *
 * @details Only call this function if the @c #CAMERA_FEATURE_VIDEO feature
 *          is available. You can determine whether this feature is available by
 *          calling the @c camera_can_feature() function.
 *
 *          Before you call this function, ensure you:
 *           - Use the @c camera_set_videovf_property() function to configure
 *             the video viewfinder.
 *           - Use the @c camera_set_video_property() function to set any video
 *             properties.
 *           - Create a screen window to be the parent of the child viewfinder
 *             window that will be created by this call.
 *
 *          Once the viewfinder is running, you can record videos, configure
 *          scene modes, adjust zoom levels, and other operations. In addition,
 *          you can reposition or resize the viewfinder window using the Screen
 *          and Windowing API. In order to retrieve a window handle to the
 *          viewfinder window that is created, you must listen for the
 *          appropriate @c SCREEN_EVENT_CREATE event using the Screen and
 *          Windowing API.
 *
 * @b Note: It is important that your application follows the guidelines for
 *          resource management outlined in @ref camapi_resource_management.
 *          If you do not observe these guidelines, your application is at
 *          risk of crashing due to memory access errors when resource
 *          arbitration is performed by the operating system.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param viewfinder_callback A function pointer to a function with the
 *                            following signature:
 * @code
 * void function_name( camera_handle_t,
 *                     camera_buffer_t*,
 *                     void* );
 * @endcode
 *                            The function is a callback that is invoked
 *                            when a viewfinder buffer becomes available.
 *                            Set this argument to @c NULL if no function
 *                            needs to be called.
 *                            For information about the callback arguments, see
 *                            @ref camapi_callback_mode.
 * @param status_callback A function pointer to a function with the following
 *                        signature:
 * @code
 * void function_name( camera_handle_t,
 *                     camera_devstatus_t,
 *                     uint16_t,
 *                     void* );
 * @endcode
 *                        The function is a callback that is invoked when
 *                        status events occur. Set this argument to @c NULL
 *                        if no function needs to be called.
 *                        For information about the callback arguments, see
 *                        @ref camapi_callback_mode.
 * @param arg The argument passed to all callback functions, which is the last
 *            argument in the callback functions.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_start_video_viewfinder(camera_handle_t handle,
                              void (*viewfinder_callback)
                                   (camera_handle_t, camera_buffer_t*, void*),
                              void (*status_callback)
                                   (camera_handle_t, camera_devstatus_t,
                                    uint16_t, void*),
                              void *arg);


/**
 * @brief (Deprecated) Stop using the photo viewfinder
 *
 * @deprecated As of @c #CAMERA_API_VERSION 3 (BlackBerry 10.3.0).
 *             Instead, use the @c camera_stop_viewfinder() function.
 *             For more information about new and deprecated viewfinder
 *             functionality, see @ref camapi_viewfinder_modes.
 *
 * @details You can only stop the photo viewfinder after you have successfully
 *          started it using @c camera_start_photo_viewfinder().
 *          After you stop running the photo viewfinder, you can no longer take
 *          photos.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_stop_photo_viewfinder(camera_handle_t handle);


/**
 * @brief (Deprecated) Stop using the video viewfinder
 *
 * @deprecated As of @c #CAMERA_API_VERSION 3 (BlackBerry 10.3.0).
 *             Instead, use the @c camera_stop_viewfinder() function.
 *             For more information about new and deprecated viewfinder
 *             functionality, see @ref camapi_viewfinder_modes.
 *
 * @details You can only stop the video viewfinder after you have successfully
 *          started it using @c camera_start_video_viewfinder().
 *          After you stop running the video viewfinder, you can no longer
 *          record videos.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_stop_video_viewfinder(camera_handle_t handle);


/**
 * @brief Configure the current output properties for a photo
 * @details Ensure that you call this function before you start the viewfinder
 *          in photo mode.
 *
 *          For the @c args argument, you can provide one or more
 *          property-value pairs using @c ::camera_imgprop_t values as the name
 *          of the property and the correct type for the value such as an
 *          @c int or @c double value. The following @c
 *          ::camera_imgprop_t can be used with this function:
 *           - @c #CAMERA_IMGPROP_FORMAT
 *           - @c #CAMERA_IMGPROP_WIDTH
 *           - @c #CAMERA_IMGPROP_HEIGHT
 *           - @c #CAMERA_IMGPROP_ROTATION
 *           - @c #CAMERA_IMGPROP_STABILIZATION
 *           - @c #CAMERA_IMGPROP_JPEGQFACTOR
 *           - @c #CAMERA_IMGPROP_BURSTDIVISOR
 *           - @c #CAMERA_IMGPROP_METAORIENTATIONHINT
 *           - @c #CAMERA_IMGPROP_FRAMERATE
 *
 *           @b Note: There is no type-checking performed by the compiler,
 *                    therefore, you must ensure that the value you provide
 *                    for each property matches the expected data type. Data
 *                    type mismatches can result in undefined
 *                    behavior and may cause your application to crash.
 *
 *           You can specify multiple property-value pairs by delimiting them
 *           with a comma as follows:
 * @code
 * camera_set_photo_property( camera_handle,
 *                            CAMERA_IMGPROP_WIDTH, 2322,
 *                            CAMERA_IMGPROP_HEIGHT, 4128,
 *                            CAMERA_IMGPROP_ROTATION, 270 );
 * @endcode
 *
 * @b Note: The following properties can't be changed while the viewfinder
 *          is running:
 *           - @c #CAMERA_IMGPROP_FORMAT
 *           - @c #CAMERA_IMGPROP_WIDTH
 *           - @c #CAMERA_IMGPROP_HEIGHT
 *           - @c #CAMERA_IMGPROP_JPEGQFACTOR
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param args... A series of comma-delimited property-value pairs.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
#define camera_set_photo_property(handle, args...) \
    _camera_set_photo_property(handle, args, CAMERA_IMGPROP_END)


/**
 * @internal
 * For internal use only. Use the camera_set_photo_property() function
 * instead which auto-terminates the ... varargs list.
 */
camera_error_t
_camera_set_photo_property(camera_handle_t handle,
                           ...);


/**
 * @brief Retrieve the output properties for a photo
 * @details For the @c args argument, you can provide one or more
 *          property-value pairs using @c ::camera_imgprop_t values as the name
 *          of the property and a pointer to the correct type for the value such
 *          as an @c int or @c double value. The following @c
 *          ::camera_imgprop_t can be used with this function:
 *           - @c #CAMERA_IMGPROP_FORMAT
 *           - @c #CAMERA_IMGPROP_WIDTH
 *           - @c #CAMERA_IMGPROP_HEIGHT
 *           - @c #CAMERA_IMGPROP_ROTATION
 *           - @c #CAMERA_IMGPROP_STABILIZATION
 *           - @c #CAMERA_IMGPROP_JPEGQFACTOR
 *           - @c #CAMERA_IMGPROP_BURSTDIVISOR
 *           - @c #CAMERA_IMGPROP_METAORIENTATIONHINT
 *           - @c #CAMERA_IMGPROP_FRAMERATE
 *
 *           @b Note: There is no type-checking performed by the compiler,
 *                    therefore, you must ensure that the value you provide
 *                    for each property matches the expected data type. Data
 *                    type mismatches can result in undefined
 *                    behavior and may cause your application to crash.
 *
 *           You can specify multiple property-value pairs by delimiting them
 *           with a comma as follows:
 * @code
 * camera_get_photo_property( camera_handle,
 *                            CAMERA_IMGPROP_WIDTH, &vf_width,
 *                            CAMERA_IMGPROP_HEIGHT, &vf_height,
 *                            CAMERA_IMGPROP_ROTATION, &vf_rotation,
 *                            CAMERA_IMGPROP_STABILIZATION, &stable );
 * @endcode
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param args... A series of comma-delimited property-value pairs where each
 *                value must be a pointer a variable of the expected type.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
#define camera_get_photo_property(handle, args...) \
        _camera_get_photo_property(handle, args, CAMERA_IMGPROP_END)


/**
 * @internal
 * For internal use only. Use the camera_get_photo_property() function
 * instead which auto-terminates the ... varargs list.
 */
camera_error_t
_camera_get_photo_property(camera_handle_t handle,
                           ...);


/**
 * @brief Configure the output properties for video recording and encoding
 * @details Ensure that you call this function before you start a video encoding
 *          or recording.
 *
 *          For the @c args argument, you can provide one or more
 *          property-value pairs using @c ::camera_imgprop_t values as the name
 *          of the property and the correct type for the value such as an
 *          @c int or @c double value. The following @c
 *          ::camera_imgprop_t can be used with this function:
 *          - @c #CAMERA_IMGPROP_WIDTH
 *          - @c #CAMERA_IMGPROP_HEIGHT
 *          - @c #CAMERA_IMGPROP_FRAMERATE
 *          - @c #CAMERA_IMGPROP_ROTATION
 *          - @c #CAMERA_IMGPROP_STABILIZATION
 *          - @c #CAMERA_IMGPROP_VIDEOCODEC
 *          - @c #CAMERA_IMGPROP_AUDIOCODEC
 *          - @c #CAMERA_IMGPROP_FORMAT
 *
 *           @b Note: @c #CAMERA_IMGPROP_STABILIZATION may impact the
 *                    field-of-view of the viewfinder. You may want to apply
 *                    this setting prior to starting the viewfinder.
 *
 *           @b Note: There is no type-checking performed by the compiler,
 *                    therefore, you must ensure that the value you provide
 *                    for each property matches the expected data type. Data
 *                    type mismatches can result in undefined
 *                    behavior and may cause your application to crash.
 *
 *           You can specify multiple property-value pairs by delimiting them
 *           with a comma as follows:
 * @code
 * camera_set_video_property( camera_handle,
 *                            CAMERA_IMGPROP_WIDTH, 720,
 *                            CAMERA_IMGPROP_HEIGHT, 1280,
 *                            CAMERA_IMGPROP_ROTATION, 270,
 *                            CAMERA_IMGPROP_FRAMERATE, (double)30.0 );
 *
 * @endcode
 * @b Note: You should determine whether the @c #CAMERA_FEATURE_PREVIEWISVIDEO
 *          property is available using the @c camera_has_feature() function
 *          before configuring the video output properties. If this feature is
 *          available, then the camera does not provide independent video and
 *          viewfinder image streams.
 *          When using such a camera, the @c #CAMERA_IMGPROP_WIDTH, @c
 *          #CAMERA_IMGPROP_HEIGHT, @c #CAMERA_IMGPROP_FORMAT, and
 *          @c #CAMERA_IMGPROP_ROTATION properties
 *          must match the values supplied to the @c camera_set_vf_property()
 *          function. The viewfinder frame rate (the value used for the @c
 *          @c #CAMERA_IMGPROP_FRAMERATE property in the @c
 *          camera_set_vf_property() function) must be an integer multiple
 *          of the video frame rate used in this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param args... A series of comma-delimited property-value pairs.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
#define camera_set_video_property(handle, args...) \
        _camera_set_video_property(handle, args, CAMERA_IMGPROP_END)


/**
 * @internal
 * For internal use only. Use the camera_set_video_property() function
 * instead which auto-terminates the ... varargs list.
 */
camera_error_t
_camera_set_video_property(camera_handle_t handle,
                           ...);


/**
 * @brief Retrieve the current output properties for video
 *
 * @details For the @c args argument, you can provide one or more
 *          property-value pairs using @c ::camera_imgprop_t values as the name
 *          of the property and a pointer to the correct type for the value such
 *          as an @c int or @c double value. The following @c
 *          ::camera_imgprop_t can be used with this function:
 *           - @c #CAMERA_IMGPROP_WIDTH
 *           - @c #CAMERA_IMGPROP_HEIGHT
 *           - @c #CAMERA_IMGPROP_FRAMERATE
 *           - @c #CAMERA_IMGPROP_ROTATION
 *           - @c #CAMERA_IMGPROP_STABILIZATION
 *           - @c #CAMERA_IMGPROP_VIDEOCODEC
 *           - @c #CAMERA_IMGPROP_AUDIOCODEC
 *           - @c #CAMERA_IMGPROP_FORMAT
 *
 *           @b Note: There is no type-checking performed by the compiler,
 *                    therefore, you must ensure that the value you provide
 *                    for each property matches the expected data type. Data
 *                    type mismatches can result in undefined
 *                    behavior and may cause your application to crash.
 *
 *           You can specify multiple property-value pairs by delimiting them
 *           with a comma as follows:
 * @code
 * camera_get_video_property( camera_handle,
 *                            CAMERA_IMGPROP_WIDTH, &vid_width,
 *                            CAMERA_IMGPROP_HEIGHT, &vid_height,
 *                            CAMERA_IMGPROP_ROTATION, &vid_rotation,
 *                            CAMERA_IMGPROP_FRAMERATE, &vid_framerate );
 * @endcode
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param args... A series of comma-delimited property-value pairs where each
 *                value must be a pointer a variable of the expected type.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
#define camera_get_video_property(handle, args...) \
        _camera_get_video_property(handle, args, CAMERA_IMGPROP_END)


/**
 * @internal
 * For internal use only. Use the camera_get_video_property() function
 * instead which auto-terminates the ... varargs list.
 */
camera_error_t
_camera_get_video_property(camera_handle_t handle,
                           ...);


/**
 * @brief Take a photo
 * @details Before you take a photo, ensure that you have configured the
 *          viewfinder, set the output properties for the photo, and started
 *          the viewfinder. This function can only be called if the @c
 *          #CAMERA_FEATURE_PHOTO feature is available. You can determine
 *          whether this feature is available by calling the @c
 *          camera_can_feature() function. Callbacks that are invoked by this
 *          function are called only once.
 *
 *          The viewfinder must be started in a viewfinder mode that supports
 *          photo capture.
 *          For more information about viewfinder modes, see
 *          @ref camapi_viewfinder_modes.
 *
 *          If you want an application to save the photo to a
 *          file, then this function should be invoked with the @c
 *          image_callback argument set. When the @c image_callback is set,
 *          the image buffer is provided as the second argument to the callback
 *          function. Then, when your @c image_callback function is invoked, you
 *          can save the buffer to a file.
 *
 *          A @c #CAMERA_STATUS_CAPTURECOMPLETE status event is emitted once the
 *          photo capture is completed.
 *
 * Note: The Camera library @b does @b not automatically play audible shutter
 *       sounds when a picture is taken or a video is recorded. Camera
 *       applications must supply their own sound when a photo is captured or a
 *       video recording begins and ends. While you can choose to not have a
 *       shutter sound when taking a picture - you are responsible to ensure
 *       that the application adheres to the local laws of the regions in which
 *       you wish to distribute the application.
 *
 *       For example, it is illegal to mute or modify the shutter sound of a
 *       camera application in Japan and Korea. Ensure that you comply with the
 *       laws and regulations for the countries in which you distribute your
 *       application. For more information, see the BlackBerry World Vetting
 *       Criteria at https://appworld.blackberry.com/isvportal/home.do.
 *
 * @b Note: It is important that your application follows the guidelines for
 *          resource management outlined in @ref camapi_resource_management.
 *          If you do not observe these guidelines, your application is at
 *          risk of crashing due to memory access errors when resource
 *          arbitration is performed by the operating system.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param shutter_callback A function pointer to a function with the following
 *                         signature:
 * @code
 * void function_name( camera_handle_t,
 *                     void* );
 * @endcode
 *                         The function is a callback that is
 *                         invoked when the shutter activates. Typically, the
 *                         callback function plays a shutter sound. You can
 *                         use @c NULL if no function needs to be called.
 *                         For information about the callback arguments, see
 *                         @ref camapi_callback_mode.
 * @param raw_callback Use @c NULL. Reserved for future use.
 * @param postview_callback A function pointer to a function with the following
 *                          signature:
 * @code
 * void function_name( camera_handle_t,
 *                     camera_buffer_t*,
 *                     void* );
 * @endcode
 *                          The function is a callback that is invoked when
 *                          the post-view (review) image data is available. This
 *                          callback is used to provide a preview-sized copy of
 *                          the photo. Typically, the preview-sized photo is
 *                          used to provide visual feedback by the UI before
 *                          the final image is available. You can use @c
 *                          NULL if no function needs to be called.
 *                          For information about the callback arguments, see
 *                          @ref camapi_callback_mode.
 * @param image_callback  A function pointer to a function with the following
 *                        signature:
 * @code
 * void function_name( camera_handle_t,
 *                     camera_buffer_t*,
 *                     void* );
 * @endcode
 *                        The function is a callback that is invoked when the
 *                        final image, such as a JPEG, is available. You can use
 *                        @c camera_set_photo_property() to change the
 *                        @c #CAMERA_IMGPROP_FORMAT to another format other than
 *                        @c #CAMERA_FRAMETYPE_JPEG. You can use @c NULL if
 *                        no function needs to be called.
 *                        For information about the callback arguments, see
 *                        @ref camapi_callback_mode.
 * @param arg The argument passed to all callback functions, which is the
 *            last argument in the callback functions.
 * @param wait A boolean value that indicates whether the function blocks or
 *             not. If the value is set to @c true, this function is
 *             blocking and will return once all specified callbacks have
 *             returned. If the value is set to @c false, this function call is
 *             non-blocking and returns before all specified callbacks have
 *             returned.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_take_photo(camera_handle_t handle,
                  void (*shutter_callback)(camera_handle_t, void*),
                  void (*raw_callback)(camera_handle_t, camera_buffer_t*,
                                       void*),
                  void (*postview_callback)(camera_handle_t,
                                            camera_buffer_t*, void*),
                  void (*image_callback)(camera_handle_t, camera_buffer_t*,
                                         void*),
                  void *arg,
                  bool wait);


/**
 * @brief Take a fixed number of photos in rapid succession
 * @details Before you take photos, ensure that you have configured the
 *          viewfinder, set the output properties for the photo, and started
 *          the viewfinder. This function can only be called if the @c
 *          #CAMERA_FEATURE_BURST feature is available. You can determine
 *          whether this feature is available by calling the @c
 *          camera_can_feature() function.
 *
 *          The viewfinder must be started in @c #CAMERA_VFMODE_FIXED_BURST
 *          mode or @c #CAMERA_VFMODE_EV_BRACKETING mode.
 *          Burst capture is also possible using the deprecated photo viewfinder
 *          with @c #CAMERA_IMGPROP_BURSTMODE set to 1.
 *          For more information about viewfinder modes, see
 *          @ref camapi_viewfinder_modes.
 *
 *          If you want an application to save the photos to a
 *          file, then this function should be invoked with the @c
 *          image_callback argument set. When the @c image_callback is set,
 *          the image buffer is provided as the second argument to the callback
 *          function. When your @c image_callback function is invoked, you can
 *          save the buffer to a file.
 *
 *          @b Note: While in burst mode, you should not save files in the
 *                   callback for performance reasons. Instead, you
 *                   should buffer the images and save them at a later time.
 *
 *          The callbacks that you set for this function are invoked for each
 *          photo and therefore, are called multiple times.
 *
 * @b Note: The Camera library @b does @b not automatically play audible shutter
 *          sounds when a picture is taken or a video is recorded. Camera
 *          applications must supply their own sound when a photo is captured or
 *          a video recording begins and ends. While you can choose to not have
 *          a shutter sound when taking a picture - you are responsible to
 *          ensure that the application adheres to the local laws of the regions
 *          in which you wish to distribute the application.
 *
 *          For example, it is illegal to mute or modify the shutter sound of a
 *          camera application in Japan and Korea. Ensure that you comply with
 *          the laws and regulations for the countries in which you distribute
 *          your application. For more information, see the BlackBerry World
 *          Vetting Criteria at
 *          https://appworld.blackberry.com/isvportal/home.do.
 *
 *          Since burst mode captures images in rapid succession, you can
 *          choose an appropriate moment to play the shutter sound rather than
 *          play the shutter sound repeatedly.
 *
 *          A @c #CAMERA_STATUS_CAPTURECOMPLETE status event is emitted once the
 *          burst capture is completed.
 *
 * @b Note: It is important that your application follows the guidelines for
 *          resource management outlined in @ref camapi_resource_management.
 *          If you do not observe these guidelines, your application is at
 *          risk of crashing due to memory access errors when resource
 *          arbitration is performed by the operating system.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param burst_count The number of photos to capture in a single burst.
 * @param shutter_callback A function pointer to a function with the following
 *                         signature:
 * @code
 * void function_name( camera_handle_t,
 *                     void* );
 * @endcode
 *                         The function is a callback that is invoked when
 *                         the shutter activates. Typically, the callback
 *                         function plays a shutter sound. You can use @c NULL
 *                         if no function needs to be called.
 *                         For information about the callback arguments, see
 *                         @ref camapi_callback_mode.
 * @param raw_callback Use @c NULL. Reserved for future use.
 * @param postview_callback A function pointer to a function with the following
 *                          signature:
 * @code
 * void function_name( camera_handle_t,
 *                     camera_buffer_t*,
 *                     void* );
 * @endcode
 *                          The function is a callback
 *                          that is invoked when a postview (review) image
 *                          is available. This callback is used to provide
 *                          a preview-sized copy of the photo. Typically, the
 *                          preview-sized photo is used to provide visual
 *                          feedback before the final image is available. You
 *                          can use @c NULL if no function needs to be called.
 *                          For information about the callback arguments, see
 *                          @ref camapi_callback_mode.
 * @param image_callback   A function pointer to a function with the following
 *                         signature:
 * @code
 * void function_name( camera_handle_t,
 *                     camera_buffer_t*,
 *                     void* );
 * @endcode
 *                         The function is a callback that is invoked when a
 *                         full-resolution image is available. You can use @c
 *                         NULL if no function needs to be called.
 *                         For information about the callback arguments, see
 *                         @ref camapi_callback_mode.
 * @param arg The argument passed to all callback functions, which is the
 *            last argument in the callback functions.
 * @param wait A boolean value that indicates whether the function blocks or
 *             not. If set to @c true, this function is blocking and will
 *             return once all specified callbacks have returned. If set to
 *             @c false, this function call is non-blocking and returns before
 *             all specified callbacks have returned.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_take_burst(camera_handle_t handle,
                  int burst_count,
                  void (*shutter_callback)(camera_handle_t, void*),
                  void (*raw_callback)(camera_handle_t,
                                       camera_buffer_t*, void*),
                  void (*postview_callback)(camera_handle_t,
                                            camera_buffer_t*, void*),
                  void (*image_callback)(camera_handle_t, camera_buffer_t*,
                                        void*),
                  void *arg,
                  bool wait);


/**
 * @brief Start to capture photos in rapid succession
 * @details Before you take photos, ensure that you have configured the
 *          viewfinder, set the output properties for the photo, and started
 *          the viewfinder. This function can only be called if the @c
 *          #CAMERA_FEATURE_CONTINUOUSBURST feature is available. You can
 *          determine whether this feature is available by calling the @c
 *          camera_can_feature() function.
 *
 *          The viewfinder must be started in @c #CAMERA_VFMODE_CONTINUOUS_BURST
 *          mode.
 *          Burst capture is also possible using the deprecated photo viewfinder
 *          with @c #CAMERA_IMGPROP_BURSTMODE set to 1.
 *          For more information about viewfinder modes, see
 *          @ref camapi_viewfinder_modes.
 *
 *          This function does not block. To terminate a continuous burst
 *          capture, call the @c camera_stop_burst() function.
 *
 *         Unlike the @c camera_take_burst() function, there is no upper limit
 *         to the number of pictures you can take. Buffers are only valid for
 *         the duration of the callback to prevent memory exhaustion. To prevent
 *         memory exhaustion, you can:
 *         - Maintain a circular buffer in order to implement negative-shutter
 *           lag.
 *         - Maintain a growing heap of buffers after capture begins in order
 *           to select your favorite photo - after the fact.
 *         - Only capture images where certain criteria has been met. For
 *           example, capture images that contain only smiles or when three
 *           faces are seen in the photo.
 *
 *         Burst runs at the frame rate specified by calling @c
 *         camera_set_photo_property() to set @c #CAMERA_IMGPROP_FRAMERATE.
 *         Use the @c camera_start_burst() function when image-capture
 *         latency is a concern or when your application cannot tolerate brief
 *         disruptions to the viewfinder. Brief disruptions can occur when using
 *         the @c camera_take_photo() function.
 *
 *         You should make copies of the frames as they arrive and exit the
 *         callback as quickly as possible. You should avoid saving the files
 *         within your @c image_callback function because writing to disk may
 *         take more time that is available before the next frame arrives.
 *         Buffers are only valid until your callback function returns.
 *         Memory that was valid before a callback begins executing may be
 *         unmapped from your process when the callback completes. Attempts to
 *         access memory buffers after the end of a callback function may
 *         result in memory access errors.
 *
 * @b Note: The Camera library @b does @b not automatically play audible shutter
 *          sounds when a picture is taken or a video is recorded. Camera
 *          applications must supply their own sound when a photo is captured or
 *          a video recording begins and ends. While you can choose to not have
 *          a shutter sound when taking a picture - you are responsible to
 *          ensure that the application adheres to the local laws of the regions
 *          in which you wish to distribute the application.
 *
 *          For example, it is illegal to mute or modify the shutter sound of a
 *          camera application in Japan and Korea. Ensure that you comply with
 *          the laws and regulations for the countries in which you distribute
 *          your application. For more information, see the BlackBerry World
 *          Vetting Criteria at
 *          https://appworld.blackberry.com/isvportal/home.do.
 *
 *          Since burst mode captures images in rapid succession, you can
 *          choose an appropriate moment to play the shutter sound rather than
 *          play the shutter sound repeatedly.
 *
 * @b Note: It is important that your application follows the guidelines for
 *          resource management outlined in @ref camapi_resource_management.
 *          If you do not observe these guidelines, your application is at
 *          risk of crashing due to memory access errors when resource
 *          arbitration is performed by the operating system.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param shutter_callback A function pointer to a function with the following
 *                         signature:
 * @code
 * void function_name( camera_handle_t,
 *                     void* );
 * @endcode
 *                         The function is a callback that is invoked when
 *                         the shutter activates. Typically, the callback
 *                         function plays a shutter sound. You can use @c NULL
 *                         if no function needs to be called.
 *                         For information about the callback arguments, see
 *                         @ref camapi_callback_mode.
 * @param raw_callback Use @c NULL. Reserved for future use.
 * @param postview_callback A function pointer to a function with the following
 *                          signature:
 * @code
 * void function_name( camera_handle_t,
 *                     camera_buffer_t*,
 *                     void* );
 * @endcode
 *                          The function is a callback that is invoked when
 *                          a post-view (review) image is available.
 *                          This callback is used to provide a preview-sized
 *                          copy of the photo. Typically, the preview-sized
 *                          photo is used to provide visual feedback before the
 *                          final image is available. You can use @c NULL if no
 *                          function needs to be called.
 *                          For information about the callback arguments, see
 *                          @ref camapi_callback_mode.
 * @param image_callback   A function pointer to a function with the following
 *                         signature:
 * @code
 * void function_name( camera_handle_t,
 *                     camera_buffer_t*,
 *                     void* );
 * @endcode
 *                         The function is a callback that is invoked when a
 *                         full-resolution image is available. You can use @c
 *                         NULL if no function needs to be called.
 *                         For information about the callback arguments, see
 *                         @ref camapi_callback_mode.
 * @param arg The argument passed to all callback functions, which is
 *            the last argument in the callback functions.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         callfailed.
 */
camera_error_t
camera_start_burst(camera_handle_t handle,
                   void (*shutter_callback)(camera_handle_t, void*),
                   void (*raw_callback)(camera_handle_t,
                                        camera_buffer_t*, void*),
                   void (*postview_callback)(camera_handle_t,
                                             camera_buffer_t*, void*),
                   void (*image_callback)(camera_handle_t, camera_buffer_t*,
                                          void*),
                   void *arg);


/**
 * @brief Stop capturing photos in continuous burst mode
 * @details Use this function to terminate a continuous burst capture that
 *          was started with the @c camera_start_burst() function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_stop_burst(camera_handle_t handle);


/**
 * @brief Performs optional initialization for video recording and encoding
 * @details Calling this function is optional, however, when called once, the
 *          first call to the @c camera_start_video() or @c
 *          camera_start_encode() functions take less time. If this function is
 *          not called, more initialization time is required when you call the
 *          @c camera_start_video() or @c camera_start_encode() functions the
 *          first time.
 *
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_init_video_encoder(void);


/**
 * @brief Start recording video to a file
 * @details This function can only be called if the @c #CAMERA_FEATURE_VIDEO
 *          feature is available. You can determine whether this feature is
 *          available by calling the @c camera_can_feature() function.
 *
 *          The viewfinder must be started in a viewfinder mode that supports
 *          video recording.
 *          For more information about viewfinder modes, see
 *          @ref camapi_viewfinder_modes.
 *
 *          Video is recorded based on the configured properties. The audio
 *          track is recorded from the active audio input on the device.
 *
 * @b Note: The Camera library @b does @b not automatically play audible shutter
 *          sounds when a picture is taken or a video is recorded. Camera
 *          applications must supply their own sound when a photo is captured or
 *          a video recording begins and ends. While you can choose to not have
 *          a shutter sound when taking a picture - you are responsible to
 *          ensure that the application adheres to the local laws of the regions
 *          in which you wish to distribute the application.
 *
 *          For example, it is illegal to mute or modify the shutter sound of a
 *          camera application in Japan and Korea. Ensure that you comply with
 *          the laws and regulations for the countries in which you distribute
 *          your application. For more information, see the BlackBerry World
 *          Vetting Criteria at
 *          https://appworld.blackberry.com/isvportal/home.do.
 *
 * @b Note: Before calling this function, ensure that all required video
 *          encoding properties are set using @c camera_set_video_property().
 *          For more information about encoding configurations, see the
 *          functions in camera_encoder.h.
 *
 *          If you require direct access to the encoded audio and video
 *          bitstreams for applications such as video chat or streaming,
 *          then you should use @c camera_start_encode() instead.
 *
 * @b Note: It is important that your application follows the guidelines for
 *          resource management outlined in @ref camapi_resource_management.
 *          If you do not observe these guidelines, your application is at
 *          risk of crashing due to memory access errors when resource
 *          arbitration is performed by the operating system.
 *
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param filename The name of the file to save the video to.
 * @param video_callback A function pointer to a function with the following
 *                       signature:
 * @code
 * void function_name( camera_handle_t,
 *                     camera_buffer_t*,
 *                     void* );
 * @endcode
 *                       The function is a callback function to invoke
 *                       when an uncompressed video frame is available.
 *                       You can use @c NULL if no function needs to be called.
 *                       For information about the callback arguments, see
 *                       @ref camapi_callback_mode.
 * @param status_callback A function pointer to a function with the following
 *                        signature:
 * @code
 * void function_name( camera_handle_t,
 *                     camera_devstatus_t,
 *                     uint16_t,
 *                     void* );
 * @endcode
 *                        The function is a callback that is invoked when
 *                        status events occur. You can use @c NULL if no
 *                        function needs to be called.
 *                        For information about the callback arguments, see
 *                        @ref camapi_callback_mode.
 * @param arg The argument passed to all callback functions, which is the
 *            last argument in the callback functions.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed. @c #CAMERA_EINVAL is returned if there
 *         is a mismatch in video properties set using @c
 *         camera_set_video_property() function.
 */
camera_error_t
camera_start_video(camera_handle_t handle,
                   const char *filename,
                   void (*video_callback)(camera_handle_t,
                                          camera_buffer_t*, void*),
                   void (*status_callback)(camera_handle_t, camera_devstatus_t,
                                           uint16_t, void*),
                   void *arg);


/**
 * @brief Stop recording video
 * @details Use this function to stop a video recording that was started
 *          with the @c camera_start_video() function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_stop_video(camera_handle_t handle);


/**
 * @brief Start encoding video
 * @details This function can only be called if the @c #CAMERA_FEATURE_VIDEO
 *          feature is available. You can determine whether this feature is
 *          available by calling the @c camera_can_feature() function.
 *
 *          The viewfinder must be started in a viewfinder mode that supports
 *          video encoding.
 *          For more information about viewfinder modes, see
 *          @ref camapi_viewfinder_modes.
 *
 *          Video is encoded based on the configured properties. The audio
 *          track is encoded from the active audio input on the device.
 *
 * @b Note: The Camera library @b does @b not automatically play audible shutter
 *          sounds when a picture is taken or a video is recorded. Camera
 *          applications must supply their own sound when a photo is captured or
 *          a video recording begins and ends. While you can choose to not have
 *          a shutter sound when taking a picture - you are responsible to
 *          ensure that the application adheres to the local laws of the regions
 *          in which you wish to distribute the application.
 *
 *          For example, it is illegal to mute or modify the shutter sound of a
 *          camera application in Japan and Korea. Ensure that you comply with
 *          the laws and regulations for the countries in which you distribute
 *          your application. For more information, see the BlackBerry World
 *          Vetting Criteria at
 *          https://appworld.blackberry.com/isvportal/home.do.
 *
 * @b Note: Before calling this function, ensure that all required video
 *          encoding properties are set using @c camera_set_video_property().
 *          For more information about encoding configurations, see the
 *          functions in camera_encoder.h.
 *
 * @b Note: It is important that your application follows the guidelines for
 *          resource management outlined in @ref camapi_resource_management.
 *          If you do not observe these guidelines, your application is at
 *          risk of crashing due to memory access errors when resource
 *          arbitration is performed by the operating system.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param video_callback A function pointer to a function with the following
 *                       signature:
 * @code
 * void function_name( camera_handle_t,
 *                     camera_buffer_t*,
 *                     void* );
 * @endcode
 *                       The function is a callback function that is invoked
 *                       when an uncompressed video frame is available.
 *                       You can use @c NULL if no function needs to be called.
 *                       For information about the callback arguments, see
 *                       @ref camapi_callback_mode.
 * @param enc_video_callback A function pointer to a function with the following
 *                           signature:
 * @code
 * void function_name( camera_handle_t,
 *                     camera_buffer_t*,
 *                     void* );
 * @endcode
 *                           The function is a callback function that is invoked
 *                           when an encoded video frame is available.
 *                           This argument is mandatory and can't be a @c NULL
 *                           value.
 *                           For information about the callback arguments, see
 *                           @ref camapi_callback_mode.
 * @param enc_video_callback A function pointer to a function with the following
 *                           signature:
 * @code
 * void function_name( camera_handle_t,
 *                     camera_buffer_t*,
 *                     void* );
 * @endcode
 *                           The function is a callback function that is invoked
 *                           when an encoded audio frame is available.
 *                           You can use @c NULL if no function needs to be
 *                           called. For information about the callback
 *                           arguments, see @ref camapi_callback_mode.
 * @param status_callback A function pointer to a function with the following
 *                        signature:
 * @code
 * void function_name( camera_handle_t,
 *                     camera_devstatus_t,
 *                     uint16_t,
 *                     void* );
 * @endcode
 *                        The function is a callback function that is invoked
 *                        when status events occur. You can use @c NULL if no
 *                        function needs to be called.
 *                        For information about the callback arguments, see
 *                        @ref camapi_callback_mode.
 * @param arg The argument passed to all callback functions, which is the
 *            last argument in the callback functions.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed. @c #CAMERA_EINVAL is returned if there
 *         is a mismatch in video properties set using @c
 *         camera_set_video_property() function.
 */
camera_error_t
camera_start_encode(camera_handle_t handle,
                    void (*video_callback)(camera_handle_t,
                                           camera_buffer_t*, void*),
                    void (*enc_video_callback)(camera_handle_t,
                                               camera_buffer_t*, void*),
                    void (*enc_audio_callback)(camera_handle_t,
                                               camera_buffer_t*, void*),
                    void (*status_callback)(camera_handle_t, camera_devstatus_t,
                                            uint16_t, void*),
                    void *arg);


/**
 * @brief Stop encoding video
 * @details Use this function to stop a video recording that was started
 *          with the @c camera_start_encode() function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_stop_encode(camera_handle_t handle);


/**
 * @brief Configure the zoom level on the camera
 * @details Only call this function if the @c #CAMERA_FEATURE_VIDEOZOOM
 *          or @c #CAMERA_FEATURE_PHOTOZOOM features are available. You can
 *          determine whether these feature are available by calling the @c
 *          camera_can_feature() function. The viewfinder must be running
 *          before using this function.
 *
 *          The value that you specify as the @c level argument sets the
 *          viewfinder zoom-level. The zoom level is a value supported by the
 *          camera hardware and can represent an optical or digital zoom
 *          depending on which the hardware supports.
 *
 *          You can specify whether to use smooth zooming using the
 *          @c smooth argument. You can use the @c camera_get_zoom_limits()
 *          function to determine the supported zoom levels and whether the
 *          camera supports smooth zooming.
 *
 *  @b Note: Changing the zoom level can interfere with existing settings,
 *           which depend on coordinates within the viewfinder frame.
 *           For example, the @c camera_set_focus_regions() function can
 *           exhibit undefined behavior after the zoom level has changed.
 *           To resolve this issue, ensure that you reapply any region-dependent
 *           settings after a zoom level change.
 *
 *           The zoom level is reset to default when the viewfinder is stopped.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param level An @c unsigned @c int value which falls within the range
 *              returned by @c camera_get_zoom_limits() function.
 *              A value of 0 indicates not to use zoom. Values larger than 0
 *              indicate increasing magnification.
 * @param smooth A of @c true specifies to smoothly transition to the specified
 *               @c level value, while a value of @c false, specifies to jump
 *               to the specified zoom level.
 * @return @c #CAMERA_EOK when the function successfully sets the zoom level,
 *         otherwise another @c ::camera_error_t value that provides the reason
 *         that the call failed.
 */
camera_error_t
camera_set_zoom(camera_handle_t handle,
                unsigned int level,
                bool smooth);


/**
 * @brief Retrieve the supported range of zoom levels and whether smooth zooming
 *        is supported by the camera
 * @details The range returned by this function represent the limits of the zoom
 *          values you can set using @c camera_set_zoom().
 *          Not all cameras support smooth zooming.
 *
 *          If you are using @c #CAMERA_VFMODE_DEFAULT, or if your application
 *          is running on a device which uses @c #CAMERA_API_VERSION 2 or lower
 *          (BlackBerry 10.2.1 or older), the viewfinder must be running prior
 *          to calling this function. If you are using a different viewfinder
 *          mode, then this function may be queried prior to starting the
 *          viewfinder.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param min_level A pointer to an @c int value that will be updated with the
 *                  minimal zoom level supported by the camera.
 * @param max_level A pointer to an @c int value that will be updated with the
 *                  maximum zoom level supported by the camera.
 * @param smooth A pointer to a boolean value that will be updated when the call
 *               completes. A value of @c true indicates that smooth zooming is
 *               supported by the camera.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_zoom_limits(camera_handle_t handle,
                       unsigned int *min_level,
                       unsigned int *max_level,
                       bool *smooth);


/**
 * @brief   Retrieves the zoom ratio corresponding to a given zoom level
 * @details Use this function to retrieve the zoom ratio associated with a given
 *          zoom level. The zoom ratio describes the amount of magnification
 *          applied to the scene being photographed. For example: A zoom ratio
 *          of 1.0 indicates that no magnification is being applied to the
 *          image. A zoom ratio of 2.0 indicates that 1/2 of the width 1/2 of
 *          the height of the scene is pictured when compared to the 1.0 zoom
 *          ratio.
 *
 * @param handle     The handle returned by a call to the @c camera_open()
 *                   function.
 * @param zoom_level The zoom level to retrieve a corresponding zoom ratio for.
 * @param zoom_ratio A pointer to a @c double value which will be set to the
 *                   magnification at the given zoom level.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_zoom_ratio_from_zoom_level(camera_handle_t handle,
                      uint32_t zoom_level,
                      double* zoom_ratio);


/**
 * @brief Change the scene mode on the camera
 * @details You specify the scene mode to set using the @c mode
 *          argument. The viewfinder must be running before you set the scene
 *          mode. Use @c camera_get_scene_modes() to determine the scene modes
 *          that are supported by the current camera.
 *
 * @b Note: Some scene modes override previously configured settings.  For
 *          example, if you set the scene mode to @c #CAMERA_SCENE_NIGHT, it
 *          may override the programmed frame rate in order to achieve better
 *          low-light performance.
 *
 *          The scene mode is reset to default when the viewfinder is stopped.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param mode The desired scene mode to set the camera to.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_scene_mode(camera_handle_t handle,
                      camera_scenemode_t mode);


/**
 * @brief Query the current scene mode of the camera
 * @details Use this function to retrieve the currently configured scene
 *          mode for the camera.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param mode A pointer to a @c ::camera_scenemode_t value in which to return
 *        the currently configured scene mode.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_scene_mode(camera_handle_t handle,
                      camera_scenemode_t* mode);


/**
 * @brief Retrieve the scene modes available on the camera
 * @details The API allows you to retrieve the scene modes available given the
 *          current platform and camera.
 *
 *          The list of supported scene modes may vary based on the currently
 *          configured viewfinder mode. However, if you are using the deprecated
 *          @c #CAMERA_VFMODE_DEFAULT viewfinder mode, then you must start the
 *          viewfinder prior to retrieving supported scene modes.
 *          For more information about new and deprecated viewfinder
 *          functionality, see @ref camapi_viewfinder_modes.
 *
 *          Ensure that the @c modes argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          modes argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in the @c numsupported argument. You can then allocate an array of
 *          the appropriate size and invoke the function again with the @c
 *          numasked argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of scene modes to return in the @c modes
 *                 array. You can specify a value of 0 to determine the
 *                 number of scene modes supported by the camera.
 * @param numsupported A pointer to an integer that will be updated  with the
 *                     number of scene modes supported by the camera.
 * @param modes A pointer to a @c ::camera_scenemode_t array. The array is
 *              updated with the scene modes supported by the camera. Ensure
 *              that you allocate an array with the same number of elements as
 *              the @c numasked argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_scene_modes(camera_handle_t handle,
                       int numasked,
                       int *numsupported,
                       camera_scenemode_t *modes);


/**
 * @brief Configure the flash mode for the camera
 * @details Only call this function if the @c #CAMERA_FEATURE_FLASH
 *          feature is available. You can determine whether this feature is
 *          available by calling the @c camera_can_feature() function. You
 *          specify the flash mode to set using the @c mode argument.
 *
 *          The viewfinder must be running before using this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param mode The desired flash mode to apply.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_config_flash(camera_handle_t handle,
                    camera_flashmode_t mode);


/**
 * @brief Configure the focus assist light
 * @details The focus assist feature allows for improved focus performance in
 *          low-light situations.
 *          When focus assist is enabled, the light will be turned on when the
 *          camera is running a single autofocus cycle and a low-light condition
 *          is detected. A single autofocus cycle can occur in either of the
 *          following situations:
 *
 *          - the user invoked @c camera_set_focus_mode() explicitly to trigger
 *            a single autofocus cycle.
 *          - the user triggered a capture using @c camera_take_photo() while
 *            in a continuous autofocus mode and while a low-light condition is
 *            detected.
 *
 *          Only call this function if the @c #CAMERA_FEATURE_FOCUSASSIST
 *          feature is available. You can determine whether this feature is
 *          available by calling the @c camera_can_feature() function.
 *
 *          The viewfinder must be running before using this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param enable A flag that indicates whether or not to enable focus assist.
 *               To enable, set to @c true. To disable, set to @c false.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_config_focus_assist(camera_handle_t handle,
                           bool enable);


/**
 * @brief Configure the video-light on the camera
 * @details Only call this function if the @c #CAMERA_FEATURE_VIDEOLIGHT
 *          feature is available. You can determine whether this feature is
 *          available by calling the @c camera_can_feature() function.
 *
 *          The viewfinder does not need to be running in order to use this
 *          function. The video-light is turned off whenever the viewfinder
 *          starts or stops.
 *
 *          Please see also @c camera_get_videolight_level() to determine if
 *          sufficient power is available to operate the videolight.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param mode The desired video-light mode to apply.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_config_videolight(camera_handle_t handle,
                         camera_videolightmode_t mode);


/**
 * @brief Configure the exposure value (EV) bracketing settings
 * @details EV Bracketing is a technique that involves taking several shots
 *          of the same subject using different exposure levels.
 *
 *          Only call this function if the @c #CAMERA_FEATURE_EVBRACKETING
 *          feature is available. You can determine whether this feature is
 *          available by calling the @c camera_can_feature() function.
 *
 *          The viewfinder must be started in @c #CAMERA_VFMODE_EV_BRACKETING
 *          mode before using this function.
 *          For more information about new and deprecated viewfinder
 *          functionality, see @ref camapi_viewfinder_modes.
 *
 *          An array of EV deltas can be configured for a fixed burst capture.
 *          The exposure deltas will be applied to successive frames. For
 *          example, {-3.0, 0.0, +3.0} in conjunction with a three-shot burst
 *          would yield three images. The first underexposed by three stops,
 *          the second at nominal exposure, and the third would be overexposed
 *          by three stops.
 *
 *          You can use the @c camera_get_ev_bracketing_limits()
 *          function to determine the exposure bracketing minimum and maximum
 *          values, as well as the maximum value for the @c num argument.
 *
 *          For more information about capturing a fixed burst of images,
 *          see @c camera_take_burst().
 *
 *          An example use of this function may look like:
 * @code
 * camera_error_t error;
 * double ev_deltas[] = {-3.0, 0.0, +3.0};
 * error = camera_config_ev_bracketing( handle,
 *                                      sizeof(ev_deltas)/sizeof(double),
 *                                      ev_deltas );
 * @endcode
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param num The number of exposure bracket delta values.
 * @param ev_deltas A pointer to an array of exposures deltas values.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_config_ev_bracketing(camera_handle_t handle,
                            uint32_t num,
                            double *ev_deltas);


/**
 * @brief Retrieve the exposure value (EV) bracketing limits
 * @details EV Bracketing is a technique that involves taking several shots
 *          of the same subject using different exposure levels. To use this
 *          function, pass in pointers to the @c max_num, @c min_delta, @c and
 *          max_delta arguments to retrieve the appropriate limits supported
 *          by the camera.
 *
 *          The viewfinder must be configured for @c
 *          #CAMERA_VFMODE_EV_BRACKETING mode before using this function.
 *          For more information about new and deprecated viewfinder
 *          functionality, see @ref camapi_viewfinder_modes.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param max_num A pointer to a @c uint32_t value that will be updated with the
 *                maximum number of bracketing deltas that are supported by the
 *                camera.
 * @param min_delta A pointer to a @c double value that will be updated with
 *                  the minimum EV delta that is supported by the camera.
 * @param max_delta A pointer to a @c double value that will be updated with
 *                  the maximum EV delta that is supported by the camera.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_ev_bracketing_limits(camera_handle_t handle,
                                uint32_t *max_num,
                                double *min_delta,
                                double *max_delta);


/**
 * @brief Retrieve the focus state of the camera
 * @details Determine The focus state and the region of focus.
 *          Typically, you call this function when a status event of type
 *          @c #CAMERA_STATUS_FOCUS_CHANGE is received.
 *
 *          The viewfinder must be running before using this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param state A pointer to a @c ::camera_focusstate_t value that will be
 *              updated with the focus state of the camera.
 * @param region A pointer to a @c ::camera_region_t value that will be updated
 *               with the region that the focus has locked to.
 *               This argument only returns valid data when @c state reports @c
 *               #CAMERA_FOCUSSTATE_LOCKED.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_focus_state(camera_handle_t handle,
                       camera_focusstate_t *state,
                       camera_region_t *region);


/**
 * @brief Configure the focus mode of the camera
 * @details You can use values defined by @c ::camera_focusmode_t to set the
 *          focus mode of the camera. Use @c camera_get_focus_modes() to
 *          determine the focus modes that are supported by the current
 *          camera.
 *
 *          The viewfinder must be running before using this function.
 *
 *          The focus mode is reset to default when the viewfinder is stopped.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param mode The focus mode to use.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_focus_mode(camera_handle_t handle,
                      camera_focusmode_t mode);


/**
 * @brief Retrieve the current focus mode of the camera
 * @details Use this function to determine the currently configured focus
 *          mode of the camera.
 *
 *          The viewfinder must be running before using this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param mode A pointer to a @c ::camera_focusmode_t value that is updated with
 *             the current focus mode of the camera.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_focus_mode(camera_handle_t handle,
                      camera_focusmode_t *mode);


/**
 * @brief Retrieve the focus modes available on the camera
 * @details Use this function to retrieve the focus modes available on the
 *          current camera.
 *
 *          Ensure that the @c modes argument points to an array
 *          which has at least @c numasked element allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          modes argument to NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in the @c numsupported argument. You can then allocate an array of
 *          the appropriate size and invoke the function again with the @c
 *          numasked argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 *          If you are using @c #CAMERA_VFMODE_DEFAULT, or if your application
 *          is running on a device which uses @c #CAMERA_API_VERSION 2 or lower
 *          (BlackBerry 10.2.1 or older), the viewfinder must be running prior
 *          to calling this function. If you are using a different viewfinder
 *          mode, then this function may be queried before starting the
 *          viewfinder.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of focus modes to return in the
 *                 @c modes array. You can use a value of 0 to
 *                 determine the number of focus modes supported
 *                 by the camera.
 * @param numsupported The returned number of focus modes supported by the
 *                     camera.
 * @param modes A pointer to a @c ::camera_focusmode_t array. The array
 *              is updated with the focus modes supported by
 *              the camera. Ensure that you allocate an array with the
 *              same number of elements as specified in the @c numasked
 *              argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_focus_modes(camera_handle_t handle,
                       int numasked,
                       int *numsupported,
                       camera_focusmode_t *modes);


/**
 * @brief Configure the focus regions on the camera
 * @details When focus regions are defined, the autofocus algorithm will give
 *          priority to focusing on objects in the defined areas of the scene.
 *
 *          Only call this function if the @c #CAMERA_FEATURE_REGIONFOCUS
 *          feature is available. You can determine whether this feature is
 *          available by calling the @c camera_can_feature() function.
 *
 *          The maximum number of focus regions that you can configure is
 *          returned by the @c numsupported argument of the
 *          @c camera_get_focus_regions() function.
 *
 *          After setting the regions, you must call the @c
 *          camera_set_focus_mode() function to commit the changes.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numregions The number of regions to apply, which is the number of
 *                   elements in the @c regions array.
 * @param regions A pointer to an array of focus regions to apply. The region
 *                co-ordinates are interpreted relative to a viewfinder buffer
 *                with (0, 0) representing the top-left corner of the frame,
 *                and (width-1, height-1) representing the bottom-right corner.
 *                If @c #CAMERA_IMGPROP_ROTATION is applied to the viewfinder,
 *                then the co-ordinate frame of reference is also rotated
 *                accordingly.
 *
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_focus_regions(camera_handle_t handle,
                         int numregions,
                         camera_region_t *regions);


/**
 * @brief Retrieve the focus regions configured on the camera
 * @details Use this function to retrieve the configured autofocus
 *          regions from the camera. For more information on configuring focus
 *          regions, see @c camera_set_focus_regions().
 *          When focus regions are defined, the autofocus algorithm will give
 *          priority to focusing on objects in the defined areas of the scene.
 *
 *          The maximum number of supported focus regions is determined by
 *          checking the @c numsupported argument when the function completes
 *          successfully.
 *
 *          Ensure that the @c regions argument points to an array
 *          which has at least @c numasked element allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          regions argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in the @c numsupported argument. You can then allocate an array of
 *          the appropriate size and invoke the function again with the @c
 *          numasked argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 *          The viewfinder must be running before using this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of regions to return in the @c regions
 *                 array. You can specify a value of 0 to determine the number
 *                 of focus regions supported by the camera.
 * @param numsupported A pointer to an integer that will be updated with the
 *                     number of focus regions supported by the camera.
 * @param numreturned A pointer to an integer that will be updated with the
 *                    number of focus regions returned in the @c regions array.
 * @param regions A pointer to a @c ::camera_region_t array. The array is
 *                updated with the focus regions configured on the camera.
 *                Ensure that you allocate an array with the same number of
 *                elements as the @c numasked argument.
 *                For more information about interpreting region geometry,
 *                see @c camera_set_focus_regions().
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_focus_regions(camera_handle_t handle,
                         int numasked,
                         int *numsupported,
                         int *numreturned,
                         camera_region_t *regions);


/**
 * @brief Configure the auto exposure regions on the camera
 * @details When exposure regions are defined, the auto exposure algorithm will
 *          give exposure priority to objects in the defined areas of the scene.
 *
 *          Only call this function if the @c #CAMERA_FEATURE_REGIONEXPOSURE
 *          feature is available. You can determine whether this feature is
 *          available by calling the @c camera_can_feature() function.
 *
 *          The maximum number of exposure regions that you can configure is
 *          returned by the @c numsupported argument of the
 *          @c camera_get_exposure_regions() function.
 *
 *          After setting the regions, you must call the @c
 *          camera_set_exposure_mode() function to commit the changes.
 *
 *          The viewfinder must be running before using this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numregions The number of regions to apply, which is the number of
 *                   elements in the @c regions array.
 * @param regions A pointer to an array of exposure regions to apply. The region
 *                co-ordinates are interpreted relative to a viewfinder buffer
 *                with (0, 0) representing the top-left corner of the frame,
 *                and (width-1, height-1) representing the bottom-right corner.
 *                If @c #CAMERA_IMGPROP_ROTATION is applied to the viewfinder,
 *                then the co-ordinate frame of reference is also rotated
 *                accordingly.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_exposure_regions(camera_handle_t handle,
                            int numregions,
                            camera_region_t *regions);


/**
 * @brief Retrieve the exposure regions configured on the camera
 * @details Use this function to retrieve the configured auto exposure
 *          regions from the camera.  For more information on configuring
 *          exposure regions, see @c camera_set_exposure_regions().
 *          When exposure regions are defined, the auto exposure algorithm will
 *          give exposure priority to objects in the defined areas of the scene.
 *
 *          The maximum number of supported exposure regions is determined by
 *          checking the @c numsupported argument when the function completes
 *          successfully.
 *
 *          Ensure that the @c regions argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          regions argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in the @c numsupported argument. You can then allocate an array of
 *          the appropriate size and invoke the function again with the @c
 *          numasked argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 *          The viewfinder must be running before using this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of regions to return in the @c regions
 *                 array. You can specify a value of 0 to determine the number
 *                 of focus regions supported by the camera.
 * @param numsupported A pointer to an integer that will be updated with the
 *                     number of exposure regions supported by the camera.
 * @param numreturned A pointer to an integer that will be updated with the
 *                    number of exposure regions returned in the @c regions
 *                    array.
 * @param regions A pointer to a @c ::camera_region_t array. The array is
 *                updated with the exposure regions configured on the camera.
 *                Ensure that you allocate an array with the same number of
 *                elements as the @c numasked argument.
 *                For more information about interpreting region geometry,
 *                see @c camera_set_exposure_regions().
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_exposure_regions(camera_handle_t handle,
                            int numasked,
                            int *numsupported,
                            int *numreturned,
                            camera_region_t *regions);


/**
 * @brief Configure the white balance regions on the camera
 * @details When white balance regions are defined, the auto white balance
 *          algorithm gives priority to objects in the defined areas of
 *          the scene.
 *
 *          Only call this function if the @c
 *          #CAMERA_FEATURE_REGIONWHITEBALANCE feature is available.
 *          Use the @c camera_can_feature() function to determine whether this
 *          feature is available.
 *
 *          The maximum number of white balance regions that you can configure
 *          is returned by the @c numsupported argument of the @c
 *          camera_get_whitebalance_regions() function.
 *
 *          After setting the regions, you must call the @c
 *          camera_set_whitebalance_mode() function to commit the changes.
 *
 *          The viewfinder must be running before using this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numregions The number of regions to apply, which is the number of
 *                   elements in the @c regions array.
 * @param regions A pointer to an array of white balance regions to apply. The
 *                region co-ordinates are interpreted relative to a viewfinder
 *                buffer with (0, 0) representing the top-left corner of the
 *                frame, and (width-1, height-1) representing the bottom-right
 *                corner.
 *                If @c #CAMERA_IMGPROP_ROTATION is applied to the viewfinder,
 *                then the co-ordinate frame of reference is also rotated
 *                accordingly.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_whitebalance_regions(camera_handle_t handle,
                                int numregions,
                                camera_region_t *regions);


/**
 * @brief Retrieve the white balance regions configured on the camera
 * @details Use this function to retrieve the configured auto
 *          white balance regions from the camera. For more information
 *          on configuring white balance regions, see @c
 *          camera_set_whitebalance_regions().
 *          When white balance regions are defined, the auto white balance
 *          algorithm gives priority to objects in the defined areas of the
 *          scene.
 *
 *          The maximum number of supported white balance regions is determined
 *          by checking the @c numsupported argument when the function completes
 *          successfully.
 *
 *          Ensure that the @c regions argument points to an array
 *          which has at least @c numasked elements allocated.To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or
 *          setting the regions argument to NULL. When the function is invoked
 *          in @e presizing mode, the maximum array size required is returned
 *          in the @c numsupported argument. You can then allocate an array of
 *          the appropriate size and invoke the function again with the @c
 *          numasked argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 *          The viewfinder must be running before using this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of regions to return in the @c regions
 *                 array. You can specify a value of 0 to determine the
 *                 number of white balance regions supported by the camera.
 * @param numsupported A pointer to an integer that will be updated with the
 *                     number of white balance regions supported by the camera.
 * @param numreturned A pointer to an integer that will be updated with the
 *                    number of white balance regions returned in the @c regions
 *                    array.
 * @param regions A pointer to a @c ::camera_region_t array. The array is
 *                updated with the white balance regions configured on the
 *                camera. Ensure that you allocate an array with the same number
 *                of elements as the @c numasked argument.
 *                For more information about interpreting region geometry,
 *                see @c camera_set_whitebalance_regions().
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_whitebalance_regions(camera_handle_t handle,
                                int numasked,
                                int *numsupported,
                                int *numreturned,
                                camera_region_t *regions);


/**
 * @brief Configures the autofocus, auto exposure, and auto white balance
 *        (the 3A algorithms) locks on the camera
 *
 * @details For the @c locks argument, you can specify the 3A algorithms to
 *          lock by ORing values from the @c ::camera_3a_t enumerated type.
 *          The following are examples:
 *          - To unlock autofocus, auto exposure, and auto white balance, use
 *            the value of @c #CAMERA_3A_NONE.
 *          - To lock autofocus and auto exposure and unlock
 *            auto white balance, use the value of
 *            (@c #CAMERA_3A_AUTOFOCUS | @c #CAMERA_3A_AUTOEXPOSURE).
 *
 * @b Note: Not all cameras may allow the independent locking of individual
 *          3A algorithms. For example, it may be required that auto exposure
 *          and auto white balance be locked together. Use the @c
 *          camera_get_3a_lock_modes() function to discover these restrictions.
 *
 *          The viewfinder must be running before using this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param locks A bitmask of 3A algorithms to lock on the camera.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_3a_lock(camera_handle_t handle,
                   uint32_t locks);


/**
 * @brief Retrieve the list of supported 3A lock modes on the camera
 *
 * @details The 3A lock modes that are independently lockable are returned as
 *          separate elements in an array. Not all of the 3A algorithms may
 *          be independently lockable. The following examples illustrate some
 *          possible @c modes lists that may be returned:
 *
 *          For a camera where all three 3A algorithms can be locked
 *          independently, the array returned is as follows:
 *          @code
 *           - element 0: CAMERA_3A_AUTOFOCUS
 *           - element 1: CAMERA_3A_AUTOEXPOSURE
 *           - element 2: CAMERA_3A_AUTOWHITEBALANCE
 *           - element 3: CAMERA_3A_NONE
 *          @endcode
 *          For a camera where autofocus and auto exposure need to be locked
 *          simultaneously, and auto white balance may be locked independently,
 *          the array returned is as follows:
 *           @code
 *           - element 0: CAMERA_3A_AUTOFOCUS | CAMERA_3A_AUTOEXPOSURE
 *           - element 1: CAMERA_3A_AUTOWHITEBALANCE
 *           - element 1: CAMERA_3A_NONE
 *           @endcode
 *          For a camera where autofocus, auto exposure, and auto white balance
 *          need to be locked together, the array returned is as follows:
 *          @code
 *           - element 0: CAMERA_3A_AUTOFOCUS | CAMERA_3A_AUTOEXPOSURE |
 *                        CAMERA_3A_AUTOWHITEBALANCE
 *           - element 1: CAMERA_3A_NONE
 *          @endcode
 *          For a camera where only autofocus may be locked, the array returned
 *          is as follows:
 *          @code
 *           - element 0: CAMERA_3A_AUTOFOCUS
 *           - element 1: CAMERA_3A_NONE
 *          @endcode
 *
 *          You may safely OR any of the elements of the returned @c modes list
 *          together to obtain a valid @c locks argument for use with the
 *          @c camera_set_3a_lock() function.
 *
 *          Ensure that the @c modes argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          modes argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in the @c numsupported argument. You can then allocate an array of
 *          the appropriate size and invoke the function again with the @c
 *          numasked argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 *          If you are using @c #CAMERA_VFMODE_DEFAULT, or if your application
 *          is running on a device which uses @c #CAMERA_API_VERSION 2 or lower
 *          (BlackBerry 10.2.1 or older), the viewfinder must be running prior
 *          to calling this function. If you are using a different viewfinder
 *          mode, then this function may be queried before starting the
 *          viewfinder.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of independently lockable 3A modes
 *                 in the @c modes array. You can use a value of 0 to
 *                 determine the number of independently lockable 3A modes
 *                 supported by the camera.
 * @param numsupported The returned number of independently lockable 3A
 *                     modes supported by the camera.
 * @param modes A pointer to a @c uint32_t array. The array is updated with the
 *              combinations of independently lockable 3A modes supported by
 *              the camera. Ensure that you allocate an array with the
 *              same number of elements as specified in the @c numasked
 *              argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_3a_lock_modes(camera_handle_t handle,
                         int numasked,
                         int *numsupported,
                         uint32_t *modes);


/**
 * @brief Configure 3A algorithms for face-detection priority
 *
 * @details The autofocus, auto exposure, and auto white balance algorithms
 *          (the 3A algorithms) may be switched into face-detection priority
 *          mode. When in face-detection priority mode, the 3A algorithms
 *          will prioritize focus, exposure, or white balance on faces
 *          in the scene.
 *
 *          For the @c priority argument, you can specify the 3A algorithms to
 *          switch to face-detection priority by ORing values from the
 *          @c ::camera_3a_t enumerated type.
 *          The following are examples:
 *
 *          - To enable 3A face-detection priority for autofocus and auto
 *            exposure, but not auto white balance, use the value of
 *            (@c #CAMERA_3A_AUTOFOCUS | @c #CAMERA_3A_AUTOEXPOSURE).
 *          - To disable 3A face-detection priority for all 3A algorithms, use
 *            the value of @c #CAMERA_3A_NONE.
 *
 * @b Note: Not all cameras may allow the independent switching of individual
 *          3A algorithms to face-detection priority mode. For example, it may
 *          be required that auto focus and auto exposure be switched to face-
 *          detection priority mode together. Use the @c
 *          camera_get_3a_face_priority_modes() function to discover these
 *          restrictions.
 *
 * @b Note: Enabling 3A face-detection priority for a given mode will
 *          clear any corresponding @c ::camera_region_t definitions. For
 *          example, if @c priority includes @c #CAMERA_3A_AUTOEXPOSURE, the
 *          @c ::camera_region_t set by @c camera_set_exposure_regions()
 *          is cleared.
 *
 *          After 3A face-priority algorithms are enabled, the camera will
 *          select a default face to track. You can explicitly select a
 *          different face using @c camera_set_3a_face_id().
 *
 *          The viewfinder must be running before using this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param priority A bitmask of 3A algorithms to switch to 3A face-detection
 *                 priority mode.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_3a_face_priority(camera_handle_t handle,
                            uint32_t priority);


/**
 * @brief Retrieve the list of supported 3A face-detection priority modes
 *        on the camera
 *
 * @details The 3A face-detection priority algorithms that are independently
 *          usable in face-detection priority mode are returned as separate
 *          elements in an array. Not all of the 3A algorithms may be
 *          independently usable in face-detection priority mode. The following
 *          examples illustrate some possible @c modes lists that may be
 *          returned:
 *
 *          For a camera where all three 3A algorithms may be independently
 *          switched to face-detection priority mode, the array returned is as
 *          follows:
 *          @code
 *           - element 0: CAMERA_3A_AUTOFOCUS
 *           - element 1: CAMERA_3A_AUTOEXPOSURE
 *           - element 2: CAMERA_3A_AUTOWHITEBALANCE
 *           - element 3: CAMERA_3A_NONE
 *          @endcode
 *
 *          For a camera where autofocus and auto exposure need to be switched
 *          to face-detection priority mode simultaneously, and auto white
 *          balance may be switched to face-detection priority independently,
 *          the array returned is as follows:
 *          @code
 *           - element 0: CAMERA_3A_AUTOFOCUS | CAMERA_3A_AUTOEXPOSURE
 *           - element 1: CAMERA_3A_AUTOWHITEBALANCE
 *           - element 1: CAMERA_3A_NONE
 *          @endcode
 *
 *          For a camera where autofocus, auto exposure, and auto white balance
 *          need to be switched to face-detection priority mode simultaneously,
 *          the array returned is as follows:
 *          @code
 *           - element 0: CAMERA_3A_AUTOFOCUS | CAMERA_3A_AUTOEXPOSURE |
 *                        CAMERA_3A_AUTOWHITEBALANCE
 *           - element 1: CAMERA_3A_NONE
 *          @endcode
 *
 *          For a camera where only autofocus may be switched to face-detection
 *          priority mode, the array returned is as follows:
 *          @code
 *           - element 0: CAMERA_3A_AUTOFOCUS
 *           - element 1: CAMERA_3A_NONE
 *          @endcode
 *
 *          You can safely OR any of the elements of the returned @c modes list
 *          together to obtain a valid @c priority argument for use with the
 *          @c camera_set_3a_face_priority() function.
 *
 *          Ensure that the @c modes argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          modes argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in the @c numsupported argument. You can then allocate an array of
 *          the appropriate size and invoke the function again with the @c
 *          numasked argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 *          If you are using @c #CAMERA_VFMODE_DEFAULT, or if your application
 *          is running on a device which uses @c #CAMERA_API_VERSION 2 or lower
 *          (BlackBerry 10.2.1 or older), the viewfinder must be running prior
 *          to calling this function. If you are using a different viewfinder
 *          mode, then this function may be queried before starting the
 *          viewfinder.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of independently switchable 3A face-
 *                 detection priority modes in the @c modes array. You can use
 *                 a value of 0 to determine the number of independently
 *                 switchable 3A face-detection priority modes supported by the
 *                 camera.
 * @param numsupported The returned number of independently switchable 3A face-
 *                     detection priority modes supported by the camera.
 * @param modes A pointer to a @c uint32_t array. The array is updated with the
 *              combinations of independently switchable 3A face-detection
 *              priority modes supported by the camera.
 *              Ensure that you allocate an array with the same number of
 *              elements as specified in the @c numasked argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_3a_face_priority_modes(camera_handle_t handle,
                                  int numasked,
                                  int *numsupported,
                                  uint32_t *modes);


/**
 * @brief Select a face for the 3A face-detection priority algorithms to track
 *
 * @details Use this function to instruct the 3A face-detection priority
 *          algorithms to operate only on the face identified by the caller.
 *          The face ID must correspond to a valid face as reported by the face
 *          detection metadata and retrieved by a call to @c
 *          camera_meta_get_face_id().
 *
 *          You can only use this function after face-detection priority 3A
 *          algorithms are enabled using @c camera_set_3a_face_priority().
 *
 *          The viewfinder must be running before using this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param id The face ID to select. This must be a valid face ID previously
 *           returned by the @c camera_meta_get_face_id() function.
 *
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_3a_face_id(camera_handle_t handle,
                      uint32_t id);


/**
 * @brief Deselect a face for the 3A face-detection priority algorithms to track
 *
 * @details Use this function to instruct the 3A face-detection priority
 *          algorithms to disregard a previously programmed face ID and to
 *          return to the default 3A face-priority behaviour. You can only use
 *          this function after face-priority 3A algorithms are enabled using
 *          @c camera_set_3a_face_priority().
 *
 *          The viewfinder must be running before using this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_clear_3a_face_id(camera_handle_t handle);


/**
 * @brief Retrieve the ID of the face that the 3A face-detection priority
 *        algorithms are currently tracking
 *
 * @details Use this function to query which face the 3A face-detection
 *          priority algorithms are currently operating on. If the user has
 *          previously selected a face to track using @c
 *          camera_set_3a_face_id(), then the returned ID will match the ID the
 *          user provided. If the user has not previously specified a face to
 *          track, then this function will return the ID of the face which the
 *          3A face-priority algorithms have defaulted to tracking. You can only
 *          use this function after 3A algorithms are switched to face-detection
 *          priority mode using @c camera_set_3a_face_priority().
 *
 *          If no face is being tracked, this function returns
 *          @c #CAMERA_ENODATA. Reasons for no face being tracked include:
 *          - There are no faces detected in the scene.
 *          - The user-selected face is no longer present in the scene.
 *
 *          The viewfinder must be running before using this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param id A pointer to a @c uint32_t value that is updated with the ID of the
 *           face that is currently being tracked.
 *
 * @return @c #CAMERA_EOK when the function successfully completes,
 *         @c #CAMERA_ENODATA when there is no face being tracked, otherwise
 *         another @c ::camera_error_t value that provides the reason
 *         that the call failed.
 */
camera_error_t
camera_get_3a_face_id(camera_handle_t handle,
                      uint32_t *id);


/**
 * @brief Manually adjust the lens position on the camera
 * @details Use this function to adjust the lens position when using
 *          manual focus mode. Larger @c step values correspond to lens
 *          positions approaching infinity focus, and smaller @c step values
 *          correspond to lens positions approaching macro focus.
 *
 *          You can only use this function when the @c
 *          #CAMERA_FEATURE_MANUALFOCUS feature is available.
 *          You can determine whether this feature is
 *          available by calling the @c camera_can_feature() function.
 *
 *          Before you can change the focus, you need to set the
 *          camera to @c #CAMERA_FOCUSMODE_MANUAL using the @c
 *          camera_set_focus_mode() function.
 *
 *          The viewfinder must be running before using this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param step The position to set the lens to. Use the @c
 *             camera_get_manual_focus_step() function to retrieve the details
 *             on the range of values supported.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_manual_focus_step(camera_handle_t handle,
                             int step);


/**
 * @brief Retrieve the current manual focus lens position and range
 *
 * @details Use this function to query the current position of the lens
 *          in manual focus mode and the maximum step value supported
 *          by @c camera_set_manual_focus_step().
 *
 *          You can only use this function when the @c
 *          #CAMERA_FEATURE_MANUALFOCUS feature is available.
 *          You can determine whether this feature is
 *          available by calling the @c camera_can_feature() function.
 *
 *          Before you can use this function to retrieve the range of accepted
 *          values, you need to set the camera to @c
 *          #CAMERA_FOCUSMODE_MANUAL using the @c camera_set_focus_mode()
 *          function.
 *
 *          The viewfinder must be running before using this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param maxstep A pointer to the returned maximum settable step value that can
 *                be used for manual focus. It also indicates the infinity focus
 *                lens position.
 * @param step A pointer to the returned current step value (position) of the
 *             lens. The minimum step value is 0 and the maximum step is the
 *             value returned in the @c maxstep argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_manual_focus_step(camera_handle_t handle,
                             int *maxstep,
                             int *step);


/**
 * @brief Create and open the next available photo file on the camera roll for
 *        writing
 * @details The camera roll is a directory on the device where the camera
 *          application saves files. The camera library manages unique
 *          filenames on behalf of the application. Use this function to
 *          retrieve the next available file from the camera roll. You require
 *          @c #CAMERA_MODE_ROLL access mode when you call the @c camera_open()
 *          function to open the camera in order to use this function.
 *
 *          After this function successfully returns, a file is created and
 *          opened for writing. To close the file, you must call the @c
 *          camera_roll_close_photo() function.
 *
 *          For information about changing the camera roll path, see the
 *          @c camera_roll_set_path() function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param  fd A pointer to the returned open file descriptor. The value that is
 *            returned corresponds to an open photo file on the camera roll.
 * @param  filename A pointer to returned name of the file on the camera roll.
 *                  Ensure that the buffer pointed to by filename is the
 *                  same size as specified by @c namelen.
 * @param  namelen The size of the buffer provided by the caller as @c
 *                 filename. The recommended size for filenames is defined by
 *                 @c #CAMERA_ROLL_NAMELEN.
 * @param fmt A @c ::camera_roll_photo_fmt_t value indicating the type of file
 *            to create.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_roll_open_photo(camera_handle_t handle,
                       int *fd,
                       char *filename,
                       int namelen,
                       camera_roll_photo_fmt_t fmt);


/**
 * @brief Close the file descriptor for a photo file on the camera roll
 *
 * @details The camera roll is a directory on the device where the camera
 *          application saves files. The camera library manages unique filenames
 *          on behalf of the application. Use this function to close the file
 *          descriptor that was returned by calling the @c
 *          camera_roll_open_photo() function on the camera roll.
 *
 * @param fd The file descriptor for the file on the camera roll to close.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_roll_close_photo(int fd);


/**
 * @brief Create and open the next available video file on the camera roll for
 *        writing
 * @details The camera roll is a directory on the device where the camera
 *          application saves files. The camera library manages unique
 *          filenames on behalf of the application. Use this function to
 *          retrieve the next available file from the camera roll. You require
 *          @c #CAMERA_MODE_ROLL access mode when you call the @c camera_open()
 *          function to open the camera in order to use this function.
 *
 *          After this function successfully returns, a file is created and
 *          opened for writing. To close the file, you must call the @c
 *          camera_roll_close_video() function.
 *
 *          For information about changing the roll path, see the @c
 *          camera_roll_set_path() function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param  fd A pointer to the returned open file descriptor. The value that is
 *            returned corresponds to an open video file on the camera roll.
 * @param  filename A pointer to returned name of the file on the camera roll.
 *                  Ensure that the buffer pointed to by filename is the
 *                  same size as specified by @c namelen.
 * @param  namelen The size of the buffer provided by the caller as @c
 *                 filename. The recommended size for filenames is defined by
 *                 @c #CAMERA_ROLL_NAMELEN.
 * @param fmt A @c ::camera_roll_photo_fmt_t value indicating the type of file
 *            to create.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_roll_open_video(camera_handle_t handle,
                       int *fd,
                       char *filename,
                       int namelen,
                       camera_roll_video_fmt_t fmt);


/**
 * @brief Close the file descriptor for a video file on the camera roll
 *
 * @details The camera roll is a directory on the device where the camera
 *          application saves files. The camera library manages unique filenames
 *          on behalf of the application. Use this function to close the file
 *          descriptor that was returned by calling the @c
 *          camera_roll_open_photo() function on the camera roll.
 *
 * @param fd The file descriptor for the file on the camera roll to close.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_roll_close_video(int fd);


/**
 * @brief Determines how much space (in bytes) is available for new photo files
 *        on the camera roll
 * @details The @c size argument is updated with the amount of free space in
 *          bytes.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param size A pointer that is updated with the number of bytes available
 *             for saving photos.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_roll_available_photo(camera_handle_t handle,
                            long long *size);


/**
 * @brief Determines how much space (in bytes) is available for new video files
 *        on the camera roll
 * @details The @c size argument is updated with the amount of free space in
 *          bytes.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param size A pointer that is updated with the number of bytes available
 *             for saving videos.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_roll_available_video(camera_handle_t handle,
                            long long *size);


/**
 * @brief Instruct the video encoder to generate a keyframe on demand when
 *        encoding video
 * @details Typically, you would request a new keyframe when an error occurs
 *          while recording video, such as a network or system error. The new
 *          keyframe allows you to recover from the error as quickly as
 *          possible.
 *
 *          Only call this function after the video encoder has been
 *          started with a call to @c camera_start_video() or
 *          @c camera_start_encode().
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_force_video_keyframe(camera_handle_t handle);


/**
 * @brief (Deprecated) Retrieve the rotation angles supported by the viewfinder
 *        in photo mode
 *
 * @deprecated As of @c #CAMERA_API_VERSION 3 (BlackBerry 10.3.0).
 *             Instead, use the @c camera_get_supported_vf_rotations() function.
 *             For more information about new and deprecated viewfinder
 *             functionality, see @ref camapi_viewfinder_modes.
 *
 * @details Typical rotations are multiples of 90 degrees (called square
 *          rotations), such as 0, 90, 180, and 270. For cameras that
 *          support only square rotations, a value of @c false will be
 *          returned in the @c nonsquare argument.
 *
 *          The values that you retrieve using this function can be written to
 *          @c #CAMERA_IMGPROP_ROTATION property using the @c
 *          camera_set_photovf_property() function.
 *
 *          Ensure that the @c rotations argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          rotations argument to NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in the @c numsupported argument. You can then allocate an array of
 *          the appropriate size and invoke the function again with the @c
 *          numasked argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param frametype The frame type to query supported rotations for. Using
 *                  @c #CAMERA_FRAMETYPE_UNSPECIFIED will return the supported
 *                  rotations for the currently configured frame type.
 * @param numasked The requested number of viewfinder rotations to return in the
 *                 @c rotations array. You can use a value of 0 to
 *                 determine the number of viewfinder rotations
 *                 supported by the camera.
 * @param numsupported The returned number of viewfinder rotations supported by
 *                     the specified camera.
 * @param rotations A pointer to a @c uint32_t array. The array
 *                  is updated with the viewfinder rotations supported by
 *                  the camera. Ensure that you allocate an array with the
 *                  same number of elements as specified in the @c numasked
 *                  argument.
 * @param nonsquare  The value updated to reflect whether the camera supports
 *                   rotation of viewfinder images that are not a square angle
 *                   (multiples of 90 degrees).
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_photo_vf_rotations(camera_handle_t handle,
                              camera_frametype_t frametype,
                              int numasked,
                              int *numsupported,
                              uint32_t *rotations,
                              bool *nonsquare);


/**
 * @brief (Deprecated) Retrieve the rotation angles supported by the viewfinder
 *        in video mode
 *
 * @deprecated As of @c #CAMERA_API_VERSION 3 (BlackBerry 10.3.0).
 *             Instead, use the @c camera_get_supported_vf_rotations() function.
 *             For more information about new and deprecated viewfinder
 *             functionality, see @ref camapi_viewfinder_modes.
 *
 * @details Typical rotations are multiples of 90 degrees (called square
 *          rotations), such as 0, 90, 180, and 270. For cameras that
 *          support only square rotations, a value of @c false will be
 *          returned in the @c nonsquare argument.
 *
 *          The values that you retrieve using this function can be written to
 *          @c #CAMERA_IMGPROP_ROTATION property using the @c
 *          camera_set_videovf_property() function.
 *
 *          Ensure that the @c rotations argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          rotations argument to NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in the @c numsupported argument. You can then allocate an array of
 *          the appropriate size and invoke the function again with the @c
 *          numasked argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param frametype The frame type to query supported rotations for. Using
 *                  @c #CAMERA_FRAMETYPE_UNSPECIFIED will return the supported
 *                  rotations for the currently configured frame type.
 * @param numasked The requested number of viewfinder rotations to return in the
 *                 @c rotations array. You can use a value of 0 to
 *                 determine the number of viewfinder rotations
 *                 supported by the camera.
 * @param numsupported The returned number of viewfinder rotations supported by
 *                     the specified camera.
 * @param rotations A pointer to a @c uint32_t array. The array
 *                  is updated with the viewfinder rotations supported by
 *                  the camera. Ensure that you allocate an array with the
 *                  same number of elements as specified in the @c numasked
 *                  argument.
 * @param nonsquare  The value updated to reflect whether the camera supports
 *                   rotation of viewfinder images that are not a square angle
 *                   (multiples of 90 degrees).
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_video_vf_rotations(camera_handle_t handle,
                              camera_frametype_t frametype,
                              int numasked,
                              int *numsupported,
                              uint32_t *rotations,
                              bool *nonsquare);


/**
 * @brief Retrieve the rotation angles supported for pictures by the camera
 *
 * @details Typical rotations are multiples of 90 degrees (called square
 *          rotations), such as 0, 90, 180, and 270. For cameras that
 *          support only square rotations, a value of @c false will be
 *          returned in the @c nonsquare argument.
 *
 *          The values that you retrieve using this function can be written to
 *          @c #CAMERA_IMGPROP_ROTATION property using the @c
 *          camera_set_photo_property() function.
 *
 *          Ensure that the @c rotations argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          rotations argument to NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in the @c numsupported argument. You can then allocate an array of
 *          the appropriate size and invoke the function again with the @c
 *          numasked argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param frametype The frame type to query supported rotations for. Using
 *                  @c #CAMERA_FRAMETYPE_UNSPECIFIED will return the supported
 *                  rotations for the currently configured frame type.
 * @param burst Set to @c true to query supported photo rotations usable in
 *              burst mode. Set to @c false otherwise.
 * @param numasked The requested number of photo rotations to return in the
 *                 @c rotations array. You can use a value of 0 to
 *                 determine the number of photo rotations
 *                 supported by the camera.
 * @param numsupported The returned number of photo rotations supported by
 *                     the specified camera.
 * @param rotations A pointer to a @c uint32_t array. The array
 *                  is updated with the photo rotations supported by
 *                  the camera. Ensure that you allocate an array with the
 *                  same number of elements as specified in the @c numasked
 *                  argument.
 * @param nonsquare  The value updated to reflect whether the camera supports
 *                   rotation of photo images that are not a square angle
 *                   (multiples of 90 degrees).
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_photo_rotations(camera_handle_t handle,
                           camera_frametype_t frametype,
                           bool burst,
                           int numasked,
                           int *numsupported,
                           uint32_t *rotations,
                           bool *nonsquare);


/**
 * @brief Retrieve the configurable rotation angles supported for the encoded
 *        video produced by the camera
 *
 * @details Typical rotations are multiples of 90 degrees (called square
 *          rotations), such as 0, 90, 180, and 270. For cameras that
 *          support only square rotations, a value of @c false will be
 *          returned in the @c nonsquare argument.
 *
 *          The values that you retrieve using this function can be written to
 *          @c #CAMERA_IMGPROP_ROTATION property using the @c
 *          camera_set_video_property() function.
 *
 *          Ensure that the @c rotations argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          rotations argument to NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in the @c numsupported argument. You can then allocate an array of
 *          the appropriate size and invoke the function again with the @c
 *          numasked argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param frametype The frame type to query supported rotations for. Using
 *                  @c #CAMERA_FRAMETYPE_UNSPECIFIED will return the supported
 *                  rotations for the currently configured frame type.
 * @param numasked The requested number of video rotations to return in the
 *                 @c rotations array. You can use a value of 0 to
 *                 determine the number of photo rotations
 *                 supported by the camera.
 * @param numsupported The returned number of video rotations supported by
 *                     the specified camera.
 * @param rotations A pointer to a @c uint32_t array. The array
 *                  is updated with the video rotations supported by
 *                  the camera. Ensure that you allocate an array with the
 *                  same number of elements as specified in the @c numasked
 *                  argument.
 * @param nonsquare  The value updated to reflect whether the camera supports
 *                   rotation of video output images that are not a square angle
 *                   (multiples of 90 degrees).
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_video_rotations(camera_handle_t handle,
                           camera_frametype_t frametype,
                           int numasked,
                           int *numsupported,
                           uint32_t *rotations,
                           bool *nonsquare);


/**
 * @brief Notify the camera of the current device orientation
 *
 * @details Use this function to let the camera on the system know how the
 *          user is holding the device. This allows the camera to adjust
 *          internal settings, such as exposure weighting, face detection, or
 *          other orientation-dependent features to match the orientation of the
 *          device. If the @c #CAMERA_IMGPROP_METAORIENTATIONHINT property
 *          is enabled for photo output, then the EXIF orientation hint
 *          will be computed using a combination of the orientation set using
 *          this function as well as the rotation angle indicated by
 *          @c #CAMERA_IMGPROP_ROTATION.
 *
 *          You can specify values such as 0, 90, 180 or 270 degrees, where 0
 *          degrees is the default orientation of the device (i.e., the
 *          BlackBerry logo is upright). It is the
 *          responsibility of an application to notify the camera when
 *          the device orientation changes.
 *
 *          This function has no effect on the output image rotations.
 *          It is simply used to inform the camera hardware that the
 *          orientation of the scene has changed in order to optimize
 *          internal algorithms, such as metering and face detection.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param val The orientation angle value, such as 0, 90, 180, or 270. 0
 *            represents the default orientation, 90
 *            represents rotated to the right, and 180 degrees represents
 *            upside down based on the marking on the device.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_device_orientation(camera_handle_t handle,
                              uint32_t val);


/**
 * @brief Configure the threshold of recording time left on the
 *        device before a warning is issued
 * @details The device has a recording capacity measured in bytes, which can
 *          also be expressed as a number of seconds depending on the encoding
 *          bit-rate. The recording capacity is indicated as seconds of
 *          recording time, which is a reflection of the amount of time left
 *          before a video recording will be stopped. While encoding, there is a
 *          continual estimation of the how many seconds of recording time
 *          remains before the storage device is full.
 *
 *          The camera will deliver a status event to the application with
 *          a value of @c #CAMERA_STATUS_FILESIZE_WARNING when the estimated
 *          amount of time left to record video is less than the value set in
 *          the @c seconds_remaining argument. The status event is delivered to
 *          any status callback functions registered when you called the @c
 *          camera_start_viewfinder() or @c camera_start_video() functions.
 *          The status event will also be delivered via any @c sigevent that you
 *          enabled using the @c camera_enable_status_event() function.
 *          See @ref camapi_event_mode and @ref camapi_callback_mode for
 *          additional details.
 *
 * @b Note: The time remaining that is calculated is an estimate based
 *          on the encoder's past performance and is subject to jitter. For this
 *          reason, the calculated time remaining may not be perfectly accurate.
 *
 *          Typically, an application would set this to five minutes (or 3000
 *          seconds). Once that threshold is crossed, an application would
 *          indicate a low-space warning. You can decide to adjust the threshold
 *          lower to receive additional warnings as the recording time
 *          approaches 0. For example, you could move the threshold to one
 *          minute (60 seconds) for the next warning.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param seconds_remaining The desired threshold (in seconds) remaining in
 *                          a recording when a warning status event will be
 *                          delivered.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_video_filesize_warning(camera_handle_t handle,
                                  uint16_t seconds_remaining);


/**
 * @brief Retrieve the photo frame types available on the camera
 *
 * @details Use this function to retrieve the photo frame types supported
 *          by the current camera. The returned formats can be applied to
 *          @c #CAMERA_IMGPROP_FORMAT using the @c camera_set_photo_property()
 *          function.
 *
 *          Ensure that the @c types argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          types argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in the @c numsupported argument. You can then allocate an array of
 *          the appropriate size and invoke the function again with the @c
 *          numasked argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of photo frame types to return in the @c
 *                 types array. You can use a value of 0 to determine the
 *                 number of photo frame types supported by the camera.
 * @param numsupported The returned number of photo frame types supported by
 *                     the specified camera.
 * @param types A pointer to a @c ::camera_frametype_t array. The array
 *              is updated with the photo frame types supported by
 *              the camera. Ensure that you allocate an array with the
 *              same number of elements as specified in the @c numasked
 *              argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_photo_frame_types(camera_handle_t handle,
                             int numasked,
                             int *numsupported,
                             camera_frametype_t *types);


/**
 * @brief (Deprecated) Retrieve the photo viewfinder frame types available on
 *        the camera.
 *
 * @deprecated As of @c #CAMERA_API_VERSION 3 (BlackBerry 10.3.0).
 *             Instead, use the @c camera_get_supported_vf_frametypes()
 *             function.
 *             For more information about new and deprecated viewfinder
 *             functionality, see @ref camapi_viewfinder_modes.
 *
 * @details Use this function to retrieve the photo viewfinder frame
 *          types supported by the current camera.
 *          The returned formats can be applied to @c #CAMERA_IMGPROP_FORMAT
 *          using the @c camera_set_photovf_property() function.
 *
 *          Ensure that the @c types argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          types argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in the @c numsupported argument. You can then allocate an array of
 *          the appropriate size and invoke the function again with the @c
 *          numasked argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of photo viewfinder frame types to
 *                 return in the @c types array. You can use a value of 0 to
 *                 determine the number of photo viewfinder frame types
 *                 supported by the camera.
 * @param numsupported The returned number of photo viewfinder frame types
 *                     supported by the specified camera.
 * @param types A pointer to a @c ::camera_frametype_t array. The array
 *              is updated with the photo viewfinder frame types supported by
 *              the camera. Ensure that you allocate an array with the
 *              same number of elements as specified in the @c numasked
 *              argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_photovf_frame_types(camera_handle_t handle,
                               int numasked,
                               int *numsupported,
                               camera_frametype_t *types);


/**
 * @brief Retrieve the video output frame types available on the camera
 *
 * @details Use this function to retrieve the video output frame
 *          types supported by the current camera.
 *          The returned formats can be applied to @c #CAMERA_IMGPROP_FORMAT
 *          using the @c camera_set_video_property() function.
 *
 *          Ensure that the @c types argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          types argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in the @c numsupported argument. You can then allocate an array of
 *          the appropriate size and invoke the function again with the @c
 *          numasked argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of video output frame types to
 *                 return in the @c types array. You can use a value of 0 to
 *                 determine the number of video output frame types
 *                 supported by the camera.
 * @param numsupported The returned number of video output frame types
 *                     supported by the specified camera.
 * @param types A pointer to a @c ::camera_frametype_t array. The array
 *              is updated with the video output frame types supported by
 *              the camera. Ensure that you allocate an array with the
 *              same number of elements as specified in the @c numasked
 *              argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_video_frame_types(camera_handle_t handle,
                             int numasked,
                             int *numsupported,
                             camera_frametype_t *types);


/**
 * @brief (Deprecated) Retrieve the video viewfinder frame types available on
 *        the camera
 *
 * @deprecated As of @c #CAMERA_API_VERSION 3 (BlackBerry 10.3.0).
 *             Instead, use the @c camera_get_supported_vf_frametypes()
 *             function.
 *             For more information about new and deprecated viewfinder
 *             functionality, see @ref camapi_viewfinder_modes.
 *
 * @details Use this function to retrieve the video viewfinder frame
 *          types supported by the current camera.
 *          The returned formats can be applied to @c #CAMERA_IMGPROP_FORMAT
 *          using the @c camera_set_videovf_property() function.
 *
 *          Ensure that the @c types argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          types argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in the @c numsupported argument. You can then allocate an array of
 *          the appropriate size and invoke the function again with the @c
 *          numasked argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of video viewfinder frame types to
 *                 return in the @c types array. You can use a value of 0 to
 *                 determine the number of video viewfinder frame types
 *                 supported by the camera.
 * @param numsupported The returned number of video viewfinder frame types
 *                     supported by the specified camera.
 * @param types A pointer to a @c ::camera_frametype_t array. The array
 *              is updated with the video viewfinder frame types supported by
 *              the camera. Ensure that you allocate an array with the
 *              same number of elements as specified in the @c numasked
 *              argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_videovf_frame_types(camera_handle_t handle,
                               int numasked,
                               int *numsupported,
                               camera_frametype_t *types);


/**
 * @brief Configure the exposure mode on the camera
 * @details Use this function to set the active exposure mode on the
 *          camera. To determine valid exposure modes that can be set,
 *          call the @c camera_get_exposure_modes() function.
 *
 *          The viewfinder must be running before calling this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param mode The exposure mode to apply.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_exposure_mode(camera_handle_t handle,
                         camera_exposuremode_t mode);


/**
 * @brief Retrieve the exposure mode from the camera
 * @details Use this function to query the current exposure mode
 *          of the camera. See also @c camera_set_exposure_mode().
 *
 *          The viewfinder must be running before calling this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param mode A pointer to a @c ::camera_exposuremode_t value that is updated
 *             with the current exposure mode of the camera.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_exposure_mode(camera_handle_t handle,
                         camera_exposuremode_t *mode);


/**
 * @brief Retrieve the exposure modes that are available on the camera
 *
 * @details Use this function to retrieve the list of exposure modes that
 *          are available on the camera. You can change the current exposure
 *          mode using the @c camera_set_exposure_mode() function.
 *
 *          Ensure that the @c modes argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          modes argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in the @c numsupported argument. You can then allocate an array of
 *          the appropriate size and invoke the function again with the @c
 *          numasked argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 *          If you are using @c #CAMERA_VFMODE_DEFAULT, or if your application
 *          is running on a device which uses @c #CAMERA_API_VERSION 2 or lower
 *          (BlackBerry 10.2.1 or older), the viewfinder must be running prior
 *          to calling this function. If you are using a different viewfinder
 *          mode, then this function may be queried before starting the
 *          viewfinder.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of exposure modes to return in the
 *                 @c modes array. You can specify a value of 0 to determine
 *                 the number of supported exposure modes available on the
 *                 camera.
 * @param numsupported A pointer to an integer that will be updated with the
 *                     number of exposure modes supported by the camera.
 * @param modes   A pointer to a @c ::camera_exposuremode_t array. The array is
 *                updated with the exposure modes available on the camera.
 *                Ensure that you allocate an array with the same number of
 *                elements as the @c numasked argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_exposure_modes(camera_handle_t handle,
                          int numasked,
                          int *numsupported,
                          camera_exposuremode_t *modes);


/**
 * @brief Configure the white balance mode on the camera
 * @details Use this function to set the active white balance mode on the
 *          camera. To determine valid white balance modes that can be set,
 *          call the @c camera_get_whitebalance_modes() function.
 *
 *          The viewfinder must be running before calling this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param mode The white balance mode to apply.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_whitebalance_mode(camera_handle_t handle,
                             camera_whitebalancemode_t mode);


/**
 * @brief Retrieve the white balance mode from the camera
 * @details Use this function to query the current white balance mode
 *          of the camera. See also @c camera_set_whitebalance_mode().
 *
 *          The viewfinder must be running before calling this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param mode A pointer to a @c ::camera_whitebalancemode_t value that is
 *             updated with the current white balance mode of the camera.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_whitebalance_mode(camera_handle_t handle,
                             camera_whitebalancemode_t *mode);


/**
 * @brief Retrieve the white balance modes that are available on the camera
 *
 * @details Use this function to retrieve the list of white balance modes that
 *          are available on the camera. You can change the current white
 *          balance mode using the @c camera_set_whitebalance_mode() function.
 *
 *          Ensure that the @c modes argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          modes argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in the @c numsupported argument. You can then allocate an array of
 *          the appropriate size and invoke the function again with the @c
 *          numasked argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 *          If you are using @c #CAMERA_VFMODE_DEFAULT, or if your application
 *          is running on a device which uses @c #CAMERA_API_VERSION 2 or lower
 *          (BlackBerry 10.2.1 or older), the viewfinder must be running prior
 *          to calling this function. If you are using a different viewfinder
 *          mode, then this function may be queried before starting the
 *          viewfinder.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of white balance modes to return in the
 *                 @c modes array. You can specify a value of 0 to determine
 *                 the number of supported white balance modes available on the
 *                 camera.
 * @param numsupported A pointer to an integer that will be updated with the
 *                     number of white balance modes supported by the camera.
 * @param modes   A pointer to a @c ::camera_whitebalancemode_t array. The array
 *                is updated with the white balance modes available on the
 *                camera. Ensure that you allocate an array with the same number
 *                of elements as the @c numasked argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_whitebalance_modes(camera_handle_t handle,
                              int numasked,
                              int *numsupported,
                              camera_whitebalancemode_t *modes);


/**
 * @brief Change the manual white balance color temperature
 * @details Use this function to set the white balance color
 *          temperature. The white balance alters the color for the image.
 *          The value that you set using this function is only applied when the
 *          white balance mode has been set to manual white balance using the
 *          @c camera_set_whitebalance_mode() function with the @c
 *          #CAMERA_WHITEBALANCEMODE_MANUAL property.
 *
 *          For more information regarding when these manual settings take
 *          effect, see @ref camapi_manual_settings and
 *          @c ::camera_whitebalancemode_t.
 *
 *          The viewfinder must be running before calling this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param whitebalancevalue The manual white balance color temperature (in
 *                          Kelvin). Use the @c
 *                          camera_get_supported_manual_white_balance_values()
 *                          function to determine the white balance color
 *                          temperature values that can be set.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_manual_white_balance(camera_handle_t handle,
                                unsigned whitebalancevalue);


/**
 * @brief Retrieve the manual white balance color temperature
 * @details Use this function to retrieve the current manual white balance
 *          color temperature. If no white balance value was set, a default
 *          white balance value is returned.
 *          See also @c camera_set_manual_white_balance().
 *
 *          The viewfinder must be running before calling this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param whitebalancevalue A pointer to an integer value that will be updated
 *                          with the manual white balance color temperature
 *                          value (in Kelvin).
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_manual_white_balance(camera_handle_t handle,
                                unsigned *whitebalancevalue);


/**
 * @brief Retrieve the supported manual white balance color temperature values
 *
 * @details Use this function to retrieve the set of supported manual white
 *          balance color temperature values for the camera.
 *
 *          Ensure that the @c whitebalancevalues argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          whitebalancevalues argument to @c NULL. When the function is invoked
 *          in this @e presizing mode, the maximum array size required is
 *          returned in the @c numsupported argument. You can then allocate an
 *          array of the appropriate size and invoke the function again with the
 *          @c numasked argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 *          The values that you retrieve using this function can be set using
 *          the @c camera_set_manual_white_balance() function.
 *
 *          If you are using @c #CAMERA_VFMODE_DEFAULT, or if your application
 *          is running on a device which uses @c #CAMERA_API_VERSION 2 or lower
 *          (BlackBerry 10.2.1 or older), the viewfinder must be running prior
 *          to calling this function. If you are using a different viewfinder
 *          mode, then this function may be queried before starting the
 *          viewfinder.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of white balance color temperature
 *                 values to return in the @c whitebalancevalues array. You can
 *                 specify a value of 0 to determine the number of supported
 *                 white balance color temperature values.
 * @param numsupported A pointer to an integer that will be updated with the
 *                     number of supported white balance color temperature
 *                     values.
 * @param whitebalancevalues A pointer to an @c unsigned @c int array. The array
 *                           is updated with the manual white balance color
 *                           temperature values supported. Ensure that you
 *                           allocate an array with the same number of elements
 *                           as the @c numasked argument. If the @c maxmin
 *                           argument returns @c true, then the first value
 *                           returned in the @c whitebalancevalues array is the
 *                           maximum suppoted white balance value, and the
 *                           second value returned is the minimum supported
 *                           color temperature.
 * @param maxmin A pointer to a @c bool value which will be set to @c true
 *               if the values returned should be interpreted as a maximum and
 *               a minimum value, or set to @c false if the values
 *               only describe the discrete white balance colour temperature
 *               values supported.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_supported_manual_white_balance_values(camera_handle_t handle,
                                                 unsigned numasked,
                                                 unsigned *numsupported,
                                                 unsigned *whitebalancevalues,
                                                 bool *maxmin);


/**
 * @brief Change the manual ISO value on the camera
 * @details Use this function to set the manual ISO value. The value
 *          that you set using this function is only applied when the exposure
 *          mode has been set to allow manual ISO settings using
 *          @c camera_set_exposure_mode(). You can use the
 *          @c camera_get_supported_manual_iso_values() function to determine
 *          the range of valid ISO values that you can use.
 *
 *          For more information regarding when these manual settings take
 *          effect, see @ref camapi_manual_settings and
 *          @c ::camera_exposuremode_t.
 *
 *          The viewfinder must be running before calling this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param isovalue The ISO value to set on the camera.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_manual_iso(camera_handle_t handle,
                      unsigned isovalue);


/**
 * @brief Retrieve the current manual ISO value
 * @details Use this function to retrieve the current manual ISO value.
 *          See also @c camera_set_manual_iso().
 *
 *          The viewfinder must be running before calling this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param isovalue A pointer to an @c unsigned @c int value that will be updated
 *                 with the current manual ISO value.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_manual_iso(camera_handle_t handle,
                      unsigned *isovalue);


/**
 * @brief Retrieve the supported manual ISO values
 *
 * @details Use this function to retrieve the set of supported manual ISO
 *          values for the camera.
 *
 *          Ensure that the @c isovalues argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          isovalues argument to @c NULL. When the function is invoked
 *          in this @e presizing mode, the maximum array size required is
 *          returned in the @c numsupported argument. You can then allocate an
 *          array of the appropriate size and invoke the function again with the
 *          @c numasked argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 *          The values that you retrieve using this function can be set using
 *          the @c camera_set_manual_iso() function.
 *
 *          If you are using @c #CAMERA_VFMODE_DEFAULT, or if your application
 *          is running on a device which uses @c #CAMERA_API_VERSION 2 or lower
 *          (BlackBerry 10.2.1 or older), the viewfinder must be running prior
 *          to calling this function. If you are using a different viewfinder
 *          mode, then this function may be queried before starting the
 *          viewfinder.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of manual ISO values to return in the
 *                 @c isovalues array. You can specify a value of 0 to determine
 *                 the number of supported manual ISO values.
 * @param numsupported A pointer to an integer that will be updated with the
 *                     number of supported manual ISO values.
 * @param isovalues  A pointer to an @c unsigned @ int array that will be
 *                   updated with the manual ISO values that are supported.
 *                   Ensure that you allocate the array with at least @c
 *                   numasked elements. If the @c maxmin argument returns @c
 *                   true, then the first value returned in the @c isovalues
 *                   array is the maximum supported manual ISO value, and the
 *                   second value that is returned is the minimum supported
 *                   manual ISO value.
 * @param maxmin A pointer to a @c bool value which will be set to @c true
 *               if the values returned should be interpreted as a maximum and
 *               a minimum value, or set to @c false if the values
 *               describe only the discrete manual ISO values supported.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_supported_manual_iso_values(camera_handle_t handle,
                                       unsigned numasked,
                                       unsigned *numsupported,
                                       unsigned *isovalues,
                                       bool *maxmin);


/**
 * @brief Change the manual shutter speed
 * @details Use this function to set the manual shutter speed on the camera.
 *          The value that you set using this function is only applied when
 *          the exposure mode is set to allow manual shutter speed control
 *          using @c camera_set_exposure_mode(). You can use the
 *          @c camera_get_supported_manual_shutter_speeds() function to
 *          determine the range of valid shutter speeds values that you can use.
 *
 *          For more information regarding when the value takes
 *          effect, see @ref camapi_manual_settings and
 *          @c ::camera_exposuremode_t.
 *
 *          The viewfinder must be running before calling this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param shutterspeed The manual shutter speed (in seconds) to set.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_manual_shutter_speed(camera_handle_t handle,
                                double shutterspeed);


/**
 * @brief Retrieve the current manual shutter speed
 * @details Use this function to retrieve the currently set manual shutter
 *          speed.
 *          See also @c camera_set_manual_shutter_speed().
 *
 *          The viewfinder must be running before calling this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param shutterspeed A pointer to a @c double value that will be updated with
 *                     the current manual shutter speed (in seconds).
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_manual_shutter_speed(camera_handle_t handle,
                                double *shutterspeed);


/**
 * @brief Retrieve the supported manual shutter speeds
 * @details Use this function to retrieve the set of supported manual shutter
 *          speeds that you can use with the current camera.
 *
 *          Ensure that the @c shutterspeeds argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          shutterspeeds argument to @c NULL. When the function is invoked
 *          in this @e presizing mode, the maximum array size required is
 *          returned in the @c numsupported argument. You can then allocate an
 *          array of the appropriate size and invoke the function again with the
 *          @c numasked argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 *          The values that you retrieve using this function can be set using
 *          the @c camera_set_manual_shutter_speed() function.
 *
 *          If you are using @c #CAMERA_VFMODE_DEFAULT, or if your application
 *          is running on a device which uses @c #CAMERA_API_VERSION 2 or lower
 *          (BlackBerry 10.2.1 or older), the viewfinder must be running prior
 *          to calling this function. If you are using a different viewfinder
 *          mode, then this function may be queried before starting the
 *          viewfinder.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of manaul shutter speeds to return in
 *                 the @c shutterspeeds array. You can specify a value of 0 to
 *                 determine the number of supported manual shutter speeds.
 * @param numsupported A pointer to an integer that will be updated with the
 *                     number of supported shutter speeds.
 * @param shutterspeeds  A pointer to a @c double array. The array is updated
 *                       with the manual shutter speeds (in seconds) supported.
 *                       Ensure that you allocate an array at least @c numasked
 *                       elements. If the @c maxmin argument returns @c true,
 *                       then the first value returned in the @c shutterspeeds
 *                       array is the maximum supported shutter speed, and the
 *                       second value returned is the minimum supported shutter
 *                       speed.
 * @param maxmin A pointer to a @c bool value which will be set to @c true
 *               if the values returned should be interpreted as a maximum and
 *               a minimum value, or set to @c false if the values describe
 *               only the discrete shutter speeds that are supported.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_supported_manual_shutter_speeds(camera_handle_t handle,
                                           unsigned numasked,
                                           unsigned *numsupported,
                                           double *shutterspeeds,
                                           bool *maxmin);


/**
 * @brief Change the manual aperture value (f-number) on the camera
 * @details Use this function to set the manual aperture value.
 *
 *          Setting a small f-number results in a reduced depth of field.
 *          Setting a large f-number results in an increased depth of field.
 *
 *          The value that you set using this function is only applied when the
 *          exposure mode has been set to allow manual aperture settings using
 *          @c camera_set_exposure_mode(). You can use the
 *          @c camera_get_supported_manual_aperture_values() function to
 *          determine the range of valid aperture values that you can use.
 *          For more information regarding when manual settings take
 *          effect, see @ref camapi_manual_settings and
 *          @c ::camera_exposuremode_t.
 *
 *          The viewfinder must be running before calling this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param aperturevalue The aperture value to set on the camera.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_manual_aperture(camera_handle_t handle,
                           double aperturevalue);


/**
 * @brief Retrieve the current manual aperture value (f-number)
 * @details Use this function to retrieve the current manual aperture
 *          value (f-number). See also @c camera_set_manual_aperture().
 *
 *          The viewfinder must be running before calling this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param aperturevalue A pointer to a @c double that will be updated with the
 *                      current manual aperture value.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_manual_aperture(camera_handle_t handle,
                           double *aperturevalue);


/**
 * @brief Retrieve the supported manual aperture values (f-numbers)
 * @details Use this function to retrieve the set of supported manual
 *          aperture values (f-numbers) for the camera.
 *
 *          Ensure that the @c aperturevalues argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          aperturevalues argument to @c NULL. When the function is invoked
 *          in this @e presizing mode, the maximum array size required is
 *          returned in the @c numsupported argument. You can then allocate an
 *          array of the appropriate size and invoke the function again with the
 *          @c numasked argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 *          The values that you retrieve using this function can be set using
 *          the @c camera_set_manual_aperture() function.
 *
 *          If you are using @c #CAMERA_VFMODE_DEFAULT, or if your application
 *          is running on a device which uses @c #CAMERA_API_VERSION 2 or lower
 *          (BlackBerry 10.2.1 or older), the viewfinder must be running prior
 *          to calling this function. If you are using a different viewfinder
 *          mode, then this function may be queried before starting the
 *          viewfinder.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of manual aperture values to return in
 *                 the @c aperturevalues array. You can specify a value of 0 to
 *                 determine the number of supported manual aperture values.
 * @param numsupported A pointer to an integer that will be updated with the
 *                     number of supported manual aperture values.
 * @param aperturevalues A pointer to a @c double array. The array is updated
 *                       with the manual aperture values supported. Ensure that
 *                       you allocate an array with the same number of elements
 *                       as the @c numasked argument. If the @c maxmin argument
 *                       returns @c true, then the first value returned in the
 *                       @c aperturevalues array is the maximum supported
 *                       manual aperture value, and the second value returned
 *                       is the minimum supported manual aperture value.
 * @param maxmin A pointer to a @c bool value which will be set to @c true
 *               if the values returned should be interpreted as a maximum and
 *               a minimum value, or set to @c false if the values describe
 *               only the discrete manual aperture values that are supported.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_supported_manual_aperture_values(camera_handle_t handle,
                                            unsigned numasked,
                                            unsigned *numsupported,
                                            double *aperturevalues,
                                            bool *maxmin);


/**
 * @brief Set the exposure value (EV) offset for exposure compensation
 * @details Use this function to set the EV offset to make pictures brighter
 *          or darker. The value set in this function @b does @b not take effect
 *          if the exposure mode (@c ::camera_exposuremode_t) is set to one of
 *          these values:
 *            - @c #CAMERA_EXPOSUREMODE_MANUAL
 *            - @c #CAMERA_EXPOSUREMODE_OFF
 *
 *          You can call @c camera_get_supported_ev_offsets() to determine
 *          the available EV offset values that can be used.
 *
 *          The viewfinder must be running before calling this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param offset The EV offset to set. Positive values, such as +1 will
 *               make the picture brighter while negative values, such as -1
 *               will make the picture darker.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_ev_offset(camera_handle_t handle,
                     double offset);


/**
 * @brief Retrieve the current exposure value (EV) offset for exposure
 *        compensation
 * @details Use this function to retrieve the current EV offset. The
 *          current EV offset is disabled when the exposure mode is one of
 *          these values:
 *            - @c #CAMERA_EXPOSUREMODE_MANUAL
 *            - @c #CAMERA_EXPOSUREMODE_OFF
 *
 *          See also @c camera_set_ev_offset().
 *
 *          The viewfinder must be running before calling this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param offset A pointer to a @c double value that will be updated with the
 *               current EV offset.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_ev_offset(camera_handle_t handle,
                     double *offset);


/**
 * @brief Retrieve the supported range of EV offset values
 * @details Use this function to retrieve the EV offset values that are
 *          available on the camera.
 *
 *          Ensure that the @c offsets argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          offsets argument to @c NULL. When the function is invoked
 *          in this @e presizing mode, the maximum array size required is
 *          returned in the @c numsupported argument. You can then allocate an
 *          array of the appropriate size and invoke the function again with the
 *          @c numasked argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 *          The values that you retrieve using this function can be set using
 *          the @c camera_set_ev_offset() function.
 *
 *          If you are using @c #CAMERA_VFMODE_DEFAULT, or if your application
 *          is running on a device which uses @c #CAMERA_API_VERSION 2 or lower
 *          (BlackBerry 10.2.1 or older), the viewfinder must be running prior
 *          to calling this function. If you are using a different viewfinder
 *          mode, then this function may be queried before starting the
 *          viewfinder.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of EV offset values to return in the
 *                 @c offsets array. You can specify a value of 0 to
 *                 determine the number of supported EV offsets values.
 * @param numsupported A pointer to an integer that will be updated with the
 *                     number of supported EV offset values.
 * @param offsets A pointer to a @c double array. The array is updated
 *                with the EV offset values supported by the camera. Ensure that
 *                you allocate an array with the same number of elements as the
 *                @c numasked argument. If the @c maxmin argument returns true,
 *                then the first value returned in the @c offsets array is the
 *                maximum supported EV offset, and the second value returned is
 *                the minimum supported EV offset.
 * @param maxmin A pointer to a @c bool value which will be set to @c true
 *               if the values returned should be interpreted as a maximum and
 *               a minimum value, or set to @c false if the values describe
 *               only the discrete EV offset values that are supported.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_supported_ev_offsets(camera_handle_t handle,
                                unsigned numasked,
                                unsigned *numsupported,
                                double *offsets,
                                bool *maxmin);


/**
 * @brief (Deprecated) Retrieve the supported photo viewfinder frame rates
 *
 * @deprecated As of @c #CAMERA_API_VERSION 3 (BlackBerry 10.3.0).
 *             Instead, use the @c camera_get_supported_vf_framerates()
 *             function.
 *             For more information about new and deprecated viewfinder
 *             functionality, see @ref camapi_viewfinder_modes.
 *
 * @details Use this function to retrieve the set of supported photo
 *          viewfinder frame rates.
 *
 *          Ensure that the @c rates argument points to an array
 *          which has at least @c numasked elements allocated. To
 *          determine an appropriate size for this array, you can invoke this
 *          function in @e presizing mode by setting the @c numasked argument to
 *          to 0 or the @c rates argument to @c NULL. When the function is
 *          invoked in @e presizing mode, the maximum array size that is
 *          required is returned in the @c numsupported argument. You can then
 *          allocate an array of the appropriate size and invoke the function
 *          again with the @c numasked argument set to the value returned
 *          previously in the @c numsupported argument.
 *
 *          You can call the @c camera_set_photovf_property() function to set
 *          the @c #CAMERA_IMGPROP_FRAMERATE property to one of the values
 *          retrieved using this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param burst Whether the frame rates should be valid for burst viewfinder
 *              mode. To enable burst viewfinder mode, call the
 *              @c camera_set_photovf_property() function and set the
 *              @c CAMERA_IMGPROP_BURSTMODE property to 1.
 * @param numasked The requested number of frame rates to return in the @c rates
 *                 array. You can specify a value of 0 to determine the
 *                 number of supported photo viewfinder frame rates.
 * @param numsupported A pointer to an @c int that will be updated with the
 *                     number of supported photo viewfinder frame rates.
 * @param rates   A pointer to a @c double array. The array is updated
 *                with the photo viewfinder frame rates supported. Ensure that
 *                you allocate an array with the same number of elements as the
 *                @c numasked argument. If the @c maxmin flag returns @c true,
 *                then the first value returned in the rates array is the
 *                maximum supported frame rate, and the second value returned is
 *                the minimum supported frame rate.
 * @param maxmin A pointer to a @c bool value which will be set to @c true
 *               if the values returned should be interpreted as a maximum and
 *               a minimum value, or set to @c false if the values only
 *               describe the discrete photo viewfinder frame rates that are
 *               supported.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_photo_vf_framerates(camera_handle_t handle,
                               bool burst,
                               int numasked,
                               int *numsupported,
                               double *rates,
                               bool *maxmin);


/**
 * @brief Retrieve the supported photo output frame rates
 * @details Use this function to retrieve the set of supported photo
 *          output frame rates.
 *
 * @b Note: The photo output frame rate is used in burst capture modes
 *          and deprecates the previous method of using
 *          @c #CAMERA_IMGPROP_BURSTDIVISOR as of BlackBerry 10.2.0.
 *
 *          Ensure that the @c rates argument points to an array
 *          which has at least @c numasked elements allocated. To
 *          determine an appropriate size for this array, you can invoke this
 *          function in @e presizing mode by setting the @c numasked argument to
 *          to 0 or the @c rates argument to @c NULL. When the function is
 *          invoked in @e presizing mode, the maximum array size that is
 *          required is returned in the @c numsupported argument. You can then
 *          allocate an array of the appropriate size and invoke the function
 *          again with the @c numasked argument set to the value returned
 *          previously in the @c numsupported argument.
 *
 *          The values that you retrieve using this function can be written to
 *          @c #CAMERA_IMGPROP_FRAMERATE property using the @c
 *          camera_set_photo_property() function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param frametype The frametype for which supported framerates are being
 *                  requested.
 * @param numasked The requested number of frame rates to return in the @c rates
 *                 array. You can specify a value of zero to determine the
 *                 number of supported photo output frame rates.
 * @param numsupported The pointer to an integer that is populated with the
 *                     number of supported frame rates.
 * @param rates   A pointer to a double array. The array is updated
 *                with the photo output frame rates supported. Ensure that
 *                you allocate an array with the same number of elements as the
 *                @c numasked argument.  If the @c maxmin flag returns @c true,
 *                then the first value returned in the rates array is the
 *                maximum supported frame rate, and the second value returned is
 *                the minimum supported frame rate.
 * @param maxmin  A pointer to a bool value which is set to @c true if the
 *                rates returned should be interpreted as a continuous range of
 *                framerates between a maximum and minimum, or set to @c false
 *                if the rates returned describe only the discrete frame rates
 *                supported.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_photo_output_framerates(camera_handle_t handle,
                                   camera_frametype_t frametype,
                                   int numasked,
                                   int *numsupported,
                                   double *rates,
                                   bool *maxmin);


/**
 * @brief (Deprecated) Retrieve the supported video viewfinder frame rates
 *
 * @deprecated As of @c #CAMERA_API_VERSION 3 (BlackBerry 10.3.0).
 *             Instead, use the @c camera_get_supported_vf_framerates()
 *             function.
 *             For more information about new and deprecated viewfinder
 *             functionality, see @ref camapi_viewfinder_modes.
 *
 * @details Use this function to retrieve the set of supported video
 *          viewfinder frame rates.
 *
 *          Ensure that the @c rates argument points to an array
 *          which has at least @c numasked elements allocated. To
 *          determine an appropriate size for this array, you can invoke this
 *          function in @e presizing mode by setting the @c numasked argument to
 *          to 0 or the @c rates argument to @c NULL. When the function is
 *          invoked in @e presizing mode, the maximum array size that is
 *          required is returned in the @c numsupported argument. You can then
 *          allocate an array of the appropriate size and invoke the function
 *          again with the @c numasked argument set to the value returned
 *          previously in the @c numsupported argument.
 *
 *          You can call the @c camera_set_videovf_property() function to set
 *          the @c #CAMERA_IMGPROP_FRAMERATE property to one of the values
 *          retrieved using this function
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of frame rates to return in the @c rates
 *                 array. You can specify a value of 0 to determine the
 *                 number of supported video viewfinder frame rates.
 * @param numsupported A pointer to an @c int that will be updated with the
 *                     number of supported video viewfinder frame rates.
 * @param rates   A pointer to a @c double array. The array is updated
 *                with the video viewfinder frame rates supported. Ensure that
 *                you allocate an array with the same number of elements as the
 *                @c numasked argument. If the @c maxmin flag returns @c true,
 *                then the first value returned in the rates array is the
 *                maximum supported frame rate, and the second value returned is
 *                the minimum supported frame rate.
 * @param maxmin A pointer to a @c bool value which will be set to @c true
 *               if the values returned should be interpreted as a maximum and
 *               a minimum value, or set to @c false if the values only
 *               describe the discrete video viewfinder frame rates that are
 *               supported.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_video_vf_framerates(camera_handle_t handle,
                               int numasked,
                               int *numsupported,
                               double *rates,
                               bool *maxmin);

/**
 * @brief  Retrieve the native orientation of the camera relative to the default
 *         orientation of the device
 * @details The native orientation describes the installed clockwise angular
 *          offset of the camera sensor with respect to the screen when the
 *          device is held upright. When a camera is installed with a non-zero
 *          orientation offset relative to the rest of the device, the image
 *          data output by the camera must be rotated for correct presentation
 *          on the screen.
 *
 *          This concept is similar to taking a photo on a film which has
 *          been reoriented to take a portrait (tall) rather than a landscape
 *          (wide) photograph. The film is still landscape, and when printed,
 *          these photographs are printed in landscape (wide) format. It is
 *          the responsibility of the viewer to hold the finished photographic
 *          print in the correct orientation in order to recreate the captured
 *          scene. The value returned by this function indicates how far
 *          clockwise the camera hardware has been oriented from the viewer, and
 *          therefore indicates how far the user must rotate the output photo
 *          buffer clock-wise in order for it to appear upright on-screen.
 *
 * @b Note: Since the camera hardware is able to render to rotated buffers on
 *          behalf of the user on some devices, it is sufficient to use the @c
 *          camera_get_supported_vf_rotations() and @c
 *          camera_get_photo_rotations() to cover many common use cases.
 *
 *          It is important to understand that even though the camera hardware
 *          may be physically installed with a non-zero orientation, the Camera
 *          API internally compensates for the native orientation offset when
 *          communicating rotation angles between the user and the hardware.
 *
 * The following are examples of how this function works in relation to
 * other functions available in this API:
 *  - Scenario 1: The @c camera_get_native_orientation() function reports an
 *                orientation of 90 degrees, such as for a smartphone.
 *                The @c camera_get_supported_vf_rotations() function reports
 *                that 0, 90, 180, 270 are supported viewfinder rotation angles.
 *                The user configures the photo viewfinder using @c
 *                camera_set_vf_property() and specifies a value of 0 for
 *                @c #CAMERA_IMGPROP_ROTATION to receive upright viewfinder
 *                buffers.
 *                In this scenario, the API will internally translate 0 to a
 *                physical rotation which is relative to the camera hardware
 *                by adding the orientation (90) and yielding 90. This
 *                ensures that the buffers output from The Camera API are
 *                presentable upright on-screen as-is.
 *
 *  - Scenario 2: The @c camera_get_native_orientation() reports an orientation
 *                of 90 degrees, such as for a smartphone. The @c
 *                camera_get_supported_vf_rotations() reports that 270 is the
 *                only supported viewfinder rotation angle. This could be the
 *                case on a device which does not support capture rotation. The
 *                use has no choice but to configure the photo viewfinder using
 *                a value of 270 when setting @c #CAMERA_IMGPROP_ROTATION using
 *                @c camera_set_vf_property().
 *                The API will internally translate 270 to a physical rotation,
 *                which is relative to the camera by adding the orientation (90)
 *                and yielding 0. The buffer being rendered to is now understood
 *                to be 0-degrees offset relative to the camera hardware.
 *                Note that this is consistent with the fact that this
 *                particular physical camera does not support viewfinder buffer
 *                rotation.  Since we also know that this camera has a non-zero
 *                native orientation (90), we know that rendering this buffer to
 *                the screen will result in a sideways image. The application
 *                must rotate this buffer by 90 degrees (the native orientation)
 *                prior to being displayed on the screen. You can accomplish
 *                this by using the Screen and Windowing API to adjust the
 *                @c #SCREEN_PROPERTY_ROTATION of the viewfinder window.
 *
 * For more information about viewfinder buffer rotation, see the
 * @c camera_get_supported_vf_rotations(), @c camera_get_video_rotations(), and
 * @c camera_get_photo_rotations() functions.
 *
 * @param handle The handle returned by a call to the @c camera_open() function
 * @param orientation A pointer to a @c uint32_t value that will be updated with
 *                    the native orientation of the camera expressed in degrees
 *                    clockwise.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_native_orientation(camera_handle_t handle,
                              uint32_t *orientation);


/**
 * @brief Enable the final image data event
 * @details Use this function to enable the image event. The image event is
 *          delivered when the final image data is available. You can then
 *          retrieve the image buffer using @c camera_get_image_buffers().
 *          This is the same image buffer that is delivered to your
 *          @c image_callback function registered when you started photo
 *          capture using @c camera_take_photo(), @c camera_take_burst(), or
 *          @c camera_start_burst().
 *
 *          Call this function when you are using the Camera API in
 *          @e event mode.
 *          For more information, see @ref camapi_event_mode.
 *
 *          Use @c camera_disable_event() to disable an event when you no
 *          longer require image events to be delivered.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param eventmode The event buffering mode as a @c ::camera_eventmode_t value.
 * @param key A pointer to a returned @c ::camera_eventkey_t value. This
 *            argument is required for subsequent function calls to identify the
 *            proper event.
 * @param event A pointer to a @c struct @c sigevent. The @c struct @c sigevent
 *              must be initialized by the caller. This is the @c struct
 *              @c sigevent that will be delivered when a still image is
 *              available to retrieve using @c camera_get_image_buffers().
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_enable_image_event(camera_handle_t handle,
                          camera_eventmode_t eventmode,
                          camera_eventkey_t *key,
                          struct sigevent* event);


/**
 * @brief Enable the postview event
 * @details Use this function to enable the postview event. The postview event
 *          is delivered when the preview-sized version of a captured still
 *          image is available (the postview image). You can then retrieve
 *          the image buffer using @c camera_get_postview_buffers().
 *          This is the same image buffer that is delivered to your
 *          @c postview_callback function registered when you started photo
 *          capture using @c camera_take_photo(), @c camera_take_burst(), or
 *          @c camera_start_burst().
 *
 *          Call this function when you are using the Camera API in
 *          @e event mode.
 *          For more information, see @ref camapi_event_mode.
 *
 *          Use @c camera_disable_event() to disable an event when you no
 *          longer require postview events to be delivered.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param eventmode The event buffering mode as a @c ::camera_eventmode_t value.
 * @param key A pointer to a returned @c ::camera_eventkey_t value. This
 *            argument is required for subsequent function calls to identify the
 *            proper event.
 * @param event A pointer to a @c struct @c sigevent. The @c struct @c sigevent
 *              must be initialized by the caller. This is the @c struct
 *              @c sigevent that will be delivered when a postview image is
 *              available to retrieve using @c camera_get_postview_buffers().
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_enable_postview_event(camera_handle_t handle,
                             camera_eventmode_t eventmode,
                             camera_eventkey_t *key,
                             struct sigevent* event);


/**
 * @internal
 * @brief Reserved for future use
 * @details Do not use this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param eventmode The event buffering mode as a @c ::camera_eventmode_t value.
 * @param key A pointer to a returned @c ::camera_eventkey_t value. This
 *            argument is required for subsequent function calls to identify the
 *            proper event.
 * @param event A pointer to a @c struct @c sigevent. The @c struct @c sigevent
 *              must be initialized by the caller. This is the @c struct
 *              @c sigevent that will be delivered when a raw image is
 *              available to retrieve using @c camera_get_raw_buffers().
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_enable_raw_event(camera_handle_t handle,
                        camera_eventmode_t eventmode,
                        camera_eventkey_t *key,
                        struct sigevent* event);


/**
 * @brief Enable the shutter event
 * @details Use this function to enable the shutter event. The shutter event
 *          is delivered when the shutter activates for image capture. There
 *          are no corresponding buffers to retrieve when the shutter event is
 *          delivered.
 *          The shutter event occurs at the same time that a the camera
 *          invokes your @c shutter_callback function registered when you
 *          started photo capture using @c camera_take_photo(),
 *          @c camera_take_burst(), or @c camera_start_burst().
 *
 *          Call this function when you are using the Camera API in
 *          @e event mode.
 *          For more information, see @ref camapi_event_mode.
 *
 *          Use @c camera_disable_event() to disable an event when you no
 *          longer require shutter events to be delivered.
 *
 * Note: The Camera library @b does @b not automatically play audible shutter
 *       sounds when a picture is taken or a video is recorded. Camera
 *       applications must supply their own sound when a photo is captured or a
 *       video recording begins and ends. While you can choose to not have a
 *       shutter sound when taking a picture - you are responsible to ensure
 *       that the application adheres to the local laws of the regions in which
 *       you wish to distribute the application.
 *
 *       For example, it is illegal to mute or modify the shutter sound of a
 *       camera application in Japan and Korea. Ensure that you comply with the
 *       laws and regulations for the countries in which you distribute your
 *       application. For more information, see the BlackBerry World Vetting
 *       Criteria at https://appworld.blackberry.com/isvportal/home.do.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param key A pointer to a returned @c ::camera_eventkey_t value. This
 *            argument is required for subsequent function calls to identify the
 *            proper event.
 * @param event A pointer to a @c struct @c sigevent. The @c struct @c sigevent
 *              must be initialized by the caller. This is the @c struct
 *              @c sigevent that will be delivered when the shutter activates.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_enable_shutter_event(camera_handle_t handle,
                            camera_eventkey_t *key,
                            struct sigevent* event);


/**
 * @brief Enable the status event
 * @details Use this function to enable the status event. The status event
 *          is delivered whenever there is additional status information to
 *          be reported by the camera. Such status information may include
 *          changes in focus state, whether the camera has powered off,
 *          or other events detailed by the @c ::camera_status_t enumerated
 *          type. After a status event is delivered, you can retrieve specific
 *          details using @c camera_get_status_details().
 *          This is the same status information that is delivered
 *          to your @c status_callback function registered
 *          when you started the viewfinder using @c camera_start_viewfinder(),
 *          or started a capture using @c camera_take_photo(),
 *          @c camera_take_burst(), @c camera_start_burst(),
 *          @c camera_start_encode() or @c camera_start_video().
 *
 *          Call this function when you are using the Camera API in
 *          @e event mode.
 *          For more information, see @ref camapi_event_mode.
 *
 *          Use @c camera_disable_event() to disable an event when you no
 *          longer require status events to be delivered.
 *
 * @b Note: It is not possible to receive status callbacks prior to starting
 *          the viewfinder, since callback functions are attached using
 *          @c camera_start_viewfinder(). Status events, however, may be
 *          enabled at any time after opening the camera.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param key A pointer to a returned @c ::camera_eventkey_t value. This
 *            argument is required for subsequent function calls to identify the
 *            proper event.
 * @param event A pointer to a @c struct @c sigevent. The @c struct @c sigevent
 *              must be initialized by the caller. This is the @c struct
 *              @c sigevent that will be delivered when a status change occurs.
 *              You can then retrieve the specific status details using
 *              @c camera_get_status_details().
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_enable_status_event(camera_handle_t handle,
                           camera_eventkey_t *key,
                           struct sigevent* event);


/**
 * @brief Enable the video event
 * @details Use this function to enable the video event. The video event
 *          is delivered when an uncompressed video frame is available.
 *          You can then retrieve the video frame using @c
 *          camera_get_video_buffers(). This is the same image data that
 *          is delivered to your @c video_callback function registered
 *          when you started video encoding using @c camera_start_video()
 *          or @c camera_start_encode().
 *
 * @b Note: On platforms that advertise the @c #CAMERA_FEATURE_PREVIEWISVIDEO
 *          feature, video frames will be identical to viewfinder frames.
 *
 *          Call this function when you are using the Camera API in
 *          @e event mode.
 *          For more information, see @ref camapi_event_mode.
 *
 *          Use @c camera_disable_event() to disable an event when you no
 *          longer require video events to be delivered.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param eventmode The event buffering mode as a @c ::camera_eventmode_t value.
 * @param key A pointer to a returned @c ::camera_eventkey_t value. This
 *            argument is required for subsequent function calls to identify the
 *            proper event.
 * @param event A pointer to a @c struct @c sigevent. The @c struct @c sigevent
 *              must be initialized by the caller. This is the @c struct
 *              @c sigevent that will be delivered when a video frame is
 *              available to retrieve using @c camera_get_postview_buffers().
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_enable_video_event(camera_handle_t handle,
                          camera_eventmode_t eventmode,
                          camera_eventkey_t *key,
                          struct sigevent* event);


/**
 * @brief Enable the viewfinder event
 * @details Use this function to enable the viewfinder event. The viewfinder
 *          event is delivered when a viewfinder frame is available.
 *          You can then retrieve the viewfinder frame using @c
 *          camera_get_viewfinder_buffers(). This is the same image data that
 *          is delivered to your @c viewfinder_callback function registered
 *          when you started the viewfinder using @c camera_start_viewfinder().
 *
 *          Call this function when you are using the Camera API in
 *          @e event mode.
 *          For more information, see @ref camapi_event_mode.
 *
 *          Use @c camera_disable_event() to disable an event when you no
 *          longer require viewfinder events to be delivered.
 *
 * @b Note: The viewfinder is automatically rendered to a screen window by the
 *          operating system. It is not required to provide display code unless
 *          custom output is required using some other mechanism such as
 *          OpenGL.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param eventmode The event buffering mode as a @c ::camera_eventmode_t value.
 * @param key A pointer to a returned @c ::camera_eventkey_t value. This
 *            argument is required for subsequent function calls to identify the
 *            proper event.
 * @param event A pointer to a @c struct @c sigevent. The @c struct @c sigevent
 *              must be initialized by the caller. This is the @c struct
 *              @c sigevent that will be delivered when a viewfinder frame is
 *              available to retrieve using @c camera_get_viewfinder_buffers().
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_enable_viewfinder_event(camera_handle_t handle,
                               camera_eventmode_t eventmode,
                               camera_eventkey_t *key,
                               struct sigevent* event);


/**
 * @brief Disable the specified event
 * @details Use this function to disable an event when you no longer want
 *          to receive the event.
 *
 *          For more information, see @ref camapi_event_mode.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param key The key value that was returned by a call to an enable event
 *            function.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_disable_event(camera_handle_t handle,
                     camera_eventkey_t key);


/**
 * @brief Retrieve video buffers from the camera
 * @details Use this function to retrieve buffers with video data. Only call
 *          this function after receiving a video event.
 *
 *          Video events are enabled using @c camera_enable_video_event().
 *          Use the @c camera_return_buffer() when you are finished processing
 *          a buffer.
 *          For more information about event mode, see @ref camapi_event_mode.
 *          For more information about when @c inbuffer and @c outbuffer are
 *          used, see @c ::camera_eventmode_t.
 *
 * @b Note: It is important that your application follows the guidelines for
 *          resource management outlined in @ref camapi_resource_management.
 *          If you do not observe these guidelines, your application is at
 *          risk of crashing due to memory access errors when resource
 *          arbitration is performed by the operating system.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param key The key value that was returned by a call to the @c
 *            camera_enable_video_event() function.
 * @param inbuffer A pointer to the input @c ::camera_buffer_t struct returned
 *                 by the camera.
 * @param outbuffer A pointer to the output @c ::camera_buffer_t struct returned
 *                  by the camera.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_video_buffers(camera_handle_t handle,
                         camera_eventkey_t key,
                         camera_buffer_t *inbuffer,
                         camera_buffer_t *outbuffer);


/**
 * @brief Retrieve viewfinder buffers from the camera
 * @details Use this function to retrieve buffers with viewfinder data. Only
 *          call this function after receiving a viewfinder event.
 *
 *          Viewfinder events are enabled using @c
 *          camera_enable_viewfinder_event().
 *          Use the @c camera_return_buffer() when you are finished processing
 *          a buffer.
 *          For more information about event mode, see @ref camapi_event_mode.
 *          For more information about when @c inbuffer and @c outbuffer are
 *          used, see @c ::camera_eventmode_t.
 *
 * @b Note: It is important that your application follows the guidelines for
 *          resource management outlined in @ref camapi_resource_management.
 *          If you do not observe these guidelines, your application is at
 *          risk of crashing due to memory access errors when resource
 *          arbitration is performed by the operating system.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param key The key value that was returned by a call to the @c
 *            camera_enable_viewfinder_event() function.
 * @param inbuffer A pointer to the input @c ::camera_buffer_t struct returned
 *                 by the camera.
 * @param outbuffer A pointer to the output @c ::camera_buffer_t struct returned
 *                  by the camera.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_viewfinder_buffers(camera_handle_t handle,
                              camera_eventkey_t key,
                              camera_buffer_t *inbuffer,
                              camera_buffer_t *outbuffer);


/**
 * @brief Retrieve image buffers from the camera
 * @details Use this function to retrieve buffers with image data. Only
 *          call this function after receiving an image event.
 *
 *          Image events are enabled using @c camera_enable_image_event().
 *          Use the @c camera_return_buffer() when you are finished processing
 *          a buffer.
 *          For more information about event mode, see @ref camapi_event_mode.
 *          For more information about when @c inbuffer and @c outbuffer are
 *          used, see @c ::camera_eventmode_t.
 *
 * @b Note: It is important that your application follows the guidelines for
 *          resource management outlined in @ref camapi_resource_management.
 *          If you do not observe these guidelines, your application is at
 *          risk of crashing due to memory access errors when resource
 *          arbitration is performed by the operating system.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param key The key value that was returned by a call to the @c
 *            camera_enable_image_event() function.
 * @param inbuffer A pointer to the input @c ::camera_buffer_t struct returned
 *                 by the camera.
 * @param outbuffer A pointer to the output @c ::camera_buffer_t struct returned
 *                  by the camera.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_image_buffers(camera_handle_t handle,
                         camera_eventkey_t key,
                         camera_buffer_t *inbuffer,
                         camera_buffer_t *outbuffer);


/**
 * @brief Retrieve postview buffers from the camera
 * @details Use this function to retrieve buffers with postview data. Only
 *          call this function after receiving a postview event.
 *
 *          Postview events are enabled using @c camera_enable_postview_event().
 *          Use the @c camera_return_buffer() when you are finished processing
 *          a buffer.
 *          For more information about event mode, see @ref camapi_event_mode.
 *          For more information about when @c inbuffer and @c outbuffer are
 *          used, see @c ::camera_eventmode_t.
 *
 * @b Note: It is important that your application follows the guidelines for
 *          resource management outlined in @ref camapi_resource_management.
 *          If you do not observe these guidelines, your application is at
 *          risk of crashing due to memory access errors when resource
 *          arbitration is performed by the operating system.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param key The key value that was returned by a call to the @c
 *            camera_enable_postview_event() function.
 * @param inbuffer A pointer to the input @c ::camera_buffer_t struct returned
 *                 by the camera.
 * @param outbuffer A pointer to the output @c ::camera_buffer_t struct returned
 *                  by the camera.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_postview_buffers(camera_handle_t handle,
                            camera_eventkey_t key,
                            camera_buffer_t *inbuffer,
                            camera_buffer_t *outbuffer);


/**
 * @internal
 * @brief Reserved for future use
 * @details Do not use this function.
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param key The key value that was returned by a call to the @c
 *           camera_enable_raw_event() function.
 * @param inbuffer A pointer to the input @c ::camera_buffer_t struct returned
 *                 by the camera.
 * @param outbuffer A pointer to the output @c ::camera_buffer_t struct returned
 *                  by the camera.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_raw_buffers(camera_handle_t handle,
                       camera_eventkey_t key,
                       camera_buffer_t *inbuffer,
                       camera_buffer_t *outbuffer);


/**
 * @brief Retrieve the status details from a status event.
 * @details Use this function to parse device status details from the
 *          @c sigval returned by a status event.
 *
 *          Status events are enabled using @c
 *          camera_enable_status_event().
 *          For more information about event mode, see @ref camapi_event_mode.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param value The @c sigval extracted from the @c struct @c sigevent that was
 *              delivered to your application.
 * @param devstatus The returned device status details. For more information,
 *                  see @c ::camera_devstatus_t.
 * @param devstatusextra The returned extra device status details. For more
 *                       information, see @c ::camera_devstatus_t.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_status_details(camera_handle_t handle,
                          union sigval value,
                          camera_devstatus_t *devstatus,
                          uint16_t *devstatusextra);


/**
 * @brief Return a buffer to the camera
 * @details Use this function to return a buffer back to the camera after you
 *          are finished processing it.
 *          The @c buffer value you provide must be one that was acquired from
 *          the camera using one of the following functions:
 *          - @c camera_get_video_buffers()
 *          - @c camera_get_viewfinder_buffers()
 *          - @c camera_get_image_buffers()
 *          - @c camera_get_postview_buffers()
 *
 * @b Note: Do not return a buffer that was delivered to a callback
 *          function, or was allocated through other means.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param buffer A pointer to a buffer acquired by a call to one of the above
 *               get-buffer functions.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_return_buffer(camera_handle_t handle,
                     camera_buffer_t *buffer);


/**
 * @brief Configure reporting of viewfinder histogram metadata
 * @details Use this function to enable viewfinder histogram reporting if
 *          supported on the camera. To determine whether histogram data is
 *          supported, call the @c camera_can_feature() function with the @c
 *          #CAMERA_FEATURE_VFHISTOGRAM feature.
 *
 *          Viewfinder histogram metadata is processed using the functions in
 *          camera_meta.h.
 *
 *          The viewfinder must be running before using this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param enable Enable histogram data reporting. Set to @c true to enable,
 *               @c false otherwise.
 *
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_config_vf_histogram(camera_handle_t handle,
                           bool enable);


/**
 * @brief Configure viewfinder face-detection metadata reporting
 * @details Use this function to enable the reporting of viewfinder
 *          face-detection metadata if the feature is supported on the camera.
 *          You can call the @c camera_can_feature() function with the @c
 *          #CAMERA_FEATURE_VFFACEDETECT to determine if the camera supports
 *          face-detection.
 *
 *          Viewfinder face-detection metadata is processed using the functions
 *          in camera_meta.h.
 *
 *          The viewfinder must be running before using this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param enable Set to @c true to enable viewfinder face-detection metadata
 *               reporting, @c false otherwise.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_config_vf_face_detect(camera_handle_t handle,
                             bool enable);


/**
 * @brief Configure face-detection metadata reporting for still images
 * @details Use this function to enable the reporting of still image
 *          face-detection metadata if the feature is supported on the camera.
 *          You can call the the @c camera_can_feature() function with
 *          the @c #CAMERA_FEATURE_FACEDETECT property to determine if the
 *          camera supports the face-detection feature.
 *
 *          Still image face-detection metadata is processed using the
 *          functions in camera_meta.h.
 *
 *          The viewfinder must be running before using this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param enable Set to @c true to enable reporting of face-detection metadata
 *               for still images, @c false otherwise.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_config_photo_face_detect(camera_handle_t handle,
                                bool enable);


/**
 * @brief Retrieve the flash power level
 * @details Use this function to get the available flash power level, as a
 *          percentage of the maximum. A non-zero level indicates that there
 *          is sufficient power available to fire the flash (see @c
 *          camera_config_flash()).  You can listen for @c
 *          #CAMERA_STATUS_FLASH_LEVEL_CHANGE status events to know when the
 *          flash power level has changed from its previous value.
 *
 *          The viewfinder must be running before using this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param percent A pointer to the returned percentage value.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_flash_level(camera_handle_t handle,
                       uint32_t *percent);


/**
 * @brief Retrieve the video light power level
 * @details Use this function to get the available video light power level,
 *          as a percentage of the maximum. A non-zero level indicates that
 *          there is sufficient power available to turn on the video light
 *          (see @c camera_config_videolight()).  You can listen for @c
 *          #CAMERA_STATUS_VIDEOLIGHT_LEVEL_CHANGE status events to know
 *          when the video light power level has changed from its previous
 *          value.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param percent A pointer to the returned percentage value.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_videolight_level(camera_handle_t handle,
                            uint32_t *percent);


/**
 * @brief Set or clear the geolocation data for photo metadata
 * @details Use this function to add or remove geolocation metadata
 *          to your images. The geolocation metadata will persist until
 *          you close the camera.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param latitude The desired latitude in degrees.
 * @param longitude The desired longitude in degrees.
 * @param altitude The desired altitude in meters.
 * @param valid A flag that sets or clears the geolocation data. Set to @c true
 *              to set the data, set to @c false to clear the data.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_geolocation(camera_handle_t handle,
                       double latitude,
                       double longitude,
                       double altitude,
                       bool valid);


/**
 * @brief Set the camera roll path
 * @details Use this function to change the directory that the camera uses
 *          to create photo and video files when you call @c
 *          camera_roll_open_photo() or @c camera_roll_open_video().
 *          The value you set for the @c pathname argument must a
 *          NULL-terminated string and must not be larger than @c
 *          #CAMERA_ROLL_NAMELEN.
 *          The path you select must be a directory which your application has
 *          write access to.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param pathname The absolute path to the new camera roll directory as a
 *                 NULL-terminated string.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_roll_set_path(camera_handle_t handle,
                     char* pathname);


/**
 * @brief Retrieve the camera roll path
 * @details Use this function to retrieve the camera roll path in which the
 *          camera stores photo and video files using @c
 *          camera_roll_open_photo() and @c camera_roll_open_video().
 *          See also @c camera_roll_set_path().
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param pathname A buffer to receive the NULL-terminated string specifying the
 *                 path to the camera roll.
 * @param pathlen The size of the @c pathname buffer. This should be set to @c
 *                #CAMERA_ROLL_NAMELEN.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_roll_get_path(camera_handle_t handle,
                     char* pathname,
                     int pathlen);


/**
 * @brief Register with the camera resource management component to let the
 *        operating system know that your application may be processing buffers
 * @details Please see @ref camapi_resource_management for important details
 *          about the resource management procedure.
 *
 *          You should use this function if any of your application code
 *          directly accesses camera buffers, otherwise you risk encountering
 *          memory access errors if buffers are unmapped while you are
 *          referencing them (e.g., saving to disk, image processing, etc.)
 *
 * @b Note: You can call the @c camera_register_resource() function more than
 *          once if you wish to perform cleanup on multiple threads, but
 *          you must call the @c camera_deregister_resource() function the same
 *          number of times when cleaning up.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_register_resource(camera_handle_t handle);


/**
 * @brief Deregister from the camera resource management component
 * @details Please see @ref camapi_resource_management for important details
 *          about the resource management procedure.
 *
 *          Use this function to indicate to the operating system that your
 *          application is no longer processing camera buffers.
 *          For more information, see @c camera_register_resource().
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_deregister_resource(camera_handle_t handle);


/**
 * @brief Retrieve one or more physical properties of the camera
 * @details For the @c args argument, you can provide one or more
 *          property-value pairs using @c ::camera_physprop_t values as the name
 *          of the property and a pointer to the correct type for the value such
 *          as an @c int or @c double value. For more information about the
 *          correct types to use, see @c ::camera_physprop_t.
 *
 *          @b Note: There is no type-checking performed by the compiler,
 *                   therefore, you must ensure that the value you provide
 *                   for each property matches the expected data type. Data type
 *                   mismatches can result in undefined behavior and may cause
 *                   your application to crash.
 *
 *          You can specify multiple property-value pairs by delimiting them
 *          with a comma as follows:
 * @code
 * camera_get_physical_property( camera_handle,
 *                               CAMERA_PHYSPROP_FOCALLENGTH, &focalLength,
 *                               CAMERA_PHYSPROP_HORIZONTALFOV, &horizFov );
 * @endcode
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param args... A series of comma-delimited property-value pairs where each
 *                value must be a pointer a variable of the expected type.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
#define camera_get_physical_property(handle, args...)\
        _camera_get_physical_property(handle, args, CAMERA_PHYSPROP_END)


/**
 * @internal
 * For internal use only. Use the @c camera_get_physical_property() function
 * instead which auto-terminates the ... varargs list.
 */
camera_error_t
_camera_get_physical_property(camera_handle_t handle,
                              ...);


/**
 * @brief Retrieve the low-light status indicator state
 * @details Use this function to determine if the camera considers the current
 *          conditions to be low in light.
 *
 *          The viewfinder must be started before using this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param lowlight A pointer to a @c bool value which is set to @c true if
 *                 the camera considers the light level to be low, and @c false
 *                 otherwise.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_lowlight_status(camera_handle_t handle,
                           bool *lowlight);


/**
 * @brief Verify whether a given video codec is supported
 * @details Use this function to determine if a given video codec is supported
 *          on the device.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param codec The video codec to verify.
 * @return @c true when the specified video codec is supported by the device,
 *         otherwise a value of @c false.
 */
bool
camera_is_videocodec_supported(camera_handle_t handle,
                               camera_videocodec_t codec);


/**
 * @brief Verify whether a given audio codec is supported
 * @details Use this function to determine if a given audio codec is supported
 *          on the device.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param codec The audio codec to verify.
 * @return @c true when the specified audio codec is supported by the device,
 *         otherwise a value of @c false.
 */
bool
camera_is_audiocodec_supported(camera_handle_t handle,
                               camera_audiocodec_t codec);


#ifdef __cplusplus
}
#endif
#endif   /* __CAMERA_API_H__ */

#include <sys/srcversion.h>
__SRCVERSION( "$URL$ $Rev$" )
