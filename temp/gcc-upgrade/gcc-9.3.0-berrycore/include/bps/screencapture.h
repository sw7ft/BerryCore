/*
 * Copyright (C) 2013-2014 BlackBerry Limited. All rights reserved.
 */

/**
 * @file screencapture.h
 * 
 * @brief Functions for taking a snapshot of the display
 *
 * This file defines the Screen Capture service, which provides functions for
 * taking screenshots.
 *
 * You can take a screenshot by calling @c screencapture_grab() and store the
 * captured image in any of the image formats defined by @c
 * #screencapture_format_t.
 *
 * @since BlackBerry 10.2.0
 *
 */

#ifndef _BPS_SCREENCAPTURE_H_INCLUDED
#define _BPS_SCREENCAPTURE_H_INCLUDED

#include <sys/platform.h>

#include "bps/bps.h"

__BEGIN_DECLS

/**
 * @brief This enum defines the supported image formats for screen captures
 *
 * @since BlackBerry 10.2.0
 *
 */
typedef enum {
    /**
     * The image format will be determined by the file name extension.
     *
     * @since BlackBerry 10.2.0
     *
     */
    SCREENCAPTURE_FORMAT_FILENAME   = 0,

    /**
     * The image format is JPEG, regardless of the file name.
     *
     * @since BlackBerry 10.2.0
     *
     */
    SCREENCAPTURE_FORMAT_JPG        = 1,

    /**
     * The image format is PNG, regardless of the file name.
     *
     * @since BlackBerry 10.2.0
     *
     */
    SCREENCAPTURE_FORMAT_PNG        = 2
} screencapture_format_t;

/**
 * @brief The result handle created on a screen capture
 *
 * The result handle created by calling @c screencapture_grab().
 *
 * @since BlackBerry 10.2.0
 *
 */
typedef struct screencapture_result_t screencapture_result_t;

/**
 * @brief Take a snapshot of the current display
 *
 * Take a snapshot of the current display.  The resulting image will be stored
 * based on the given filename, or placed in the camera roll.
 *
 * An application must have the @c use_camera_desktop capability in order to
 * use this function. To grant an application the @c use_camera_desktop
 * capability, the bar-descriptor.xml file in the application's project must
 * contain the line "<permission>use_camera_desktop</permission>".
 *
 * @param filename If @c NULL, the screenshot will be stored in the camera roll
 * and the file name will be automatically generated.  Otherwise, @c filename
 * will be used as the file name.  The path can be the absolute path, or a
 * relative one.  For example: "./data/mysnapshot.jpg" will store the snapshot
 * in the application's data directory.
 *
 * @param format The format of the image, which is one of @c
 * #screencapture_format_t. If @c #SCREENCAPTURE_FORMAT_FILENAME is used, the
 * image format will be selected based on the extension from @c filename.
 * Otherwise, the screen capture will be stored in the specified image format,
 * regardless of filename.
 *
 * @param result If not @c NULL, @c screencapture_grab() will assign a result
 * handle.  The result handle can be used to get extended result information.
 * The result handle needs to be destroyed by calling @c
 * screencapture_destroy_result().  If it is @c NULL, no extended information
 * will be provided.
 *
 * @return @c BPS_SUCCESS if the snapshot was successful.  Otherwise, return @c
 * BPS_FAILURE with @c errno set.  Further error details are provided in the
 * result handle, if available.  If this function fails with the @c errno of @c
 * ENOMEM, the result could not be allocated, and could not be returned to the
 * user.
 *
 * @since BlackBerry 10.2.0
 *
 */
BPS_API int screencapture_grab(const char * filename, int format, screencapture_result_t **result);

/**
 * @brief Get the extended error code from a failed screen grab
 *
 * @param result The result handle created by @c screencapture_grab().
 *
 * @return An error code from camera/camera_api.h will be returned.  @c
 * CAMERA_EOK indicates that no failure had occurred.
 *
 * @since BlackBerry 10.2.0
 *
 */
BPS_API int screencapture_result_get_error_code(screencapture_result_t *result);

/**
 * @brief Get the error message from a failed screen grab
 *
 * @param result The result handle created by @c screencapture_grab().
 *
 * @return If @c screencapture_grab() failed, this function returns a more
 * detailed error message.  If @c screencapture_grab() succeeded, this will
 * return @c NULL.
 *
 * @since BlackBerry 10.2.0
 *
 */
BPS_API const char * screencapture_result_get_error_message(screencapture_result_t *result);

/**
 * @brief Get the filename of the saved screenshot
 *
 * Get the filename of the saved screenshot.  This is particularly useful if no
 * filename was specified in the call to @c screencapture_grab().  In that
 * case, a file name was automatically generated, and can be retrieved here.
 *
 * @param result The result handle created by @c screencapture_grab().
 *
 * @return If @c screencapture_grab() returned success, this function returns
 * the filename of the stored screenshot.  If @c screencapture_grab() failed,
 * this function will return @c NULL.
 *
 * @since BlackBerry 10.2.0
 *
 */
BPS_API const char * screencapture_result_get_filename(screencapture_result_t *result);

/**
 * @brief Destroy a result handle
 *
 * @param result The result handle assigned in @c screencapture_grab().
 *
 * @return @c BPS_SUCCESS if the handle was successfully destroyed, otherwise
 * return @c BPS_FAILURE with @c errno set.
 *
 * @since BlackBerry 10.2.0
 *
 */
BPS_API int screencapture_destroy_result(screencapture_result_t *result);

__END_DECLS

#endif
