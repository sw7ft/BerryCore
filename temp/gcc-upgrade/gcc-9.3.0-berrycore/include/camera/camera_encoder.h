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

#ifndef __CAMERA_ENCODER_H__
#define __CAMERA_ENCODER_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file camera_encoder.h
 *
 * @brief Functions to configure parameters for video and audio encoding
 *
 * @details This file defines functions that applications can use to configure
 *          video and audio encoding. The configurations that can be
 *          used are dependent on the codecs that are available on the device.
 *
 *          To select the video codec, you can call the @c
 *          camera_set_video_property() function with the @c
 *          #CAMERA_IMGPROP_VIDEOCODEC property. The parameters that are
 *          supported for each video codec are defined in the corresponding
 *          file as follows:
 *          - H.264/AVC: camera/camera_h264avc.h
 *
 *          For example, the H.264/AVC codec is defined in the
 *          camera_h264avc.h file.
 *
 *          To select the audio codec, call the @c
 *          camera_set_video_property() function with the @c
 *          #CAMERA_IMGPROP_AUDIOCODEC property.
 */

#include <camera/camera_api.h>

/*
 * The parameters supported for each video codec are defined in the
 * corresponding header files below.
 */
#include <camera/camera_h264avc.h>


/**
 * @internal
 * For internal use only. Do not use.
 * The end-of-list identifier for camera audio/video encoder parameters.
 */
#define CAMERA_PARAMETER_END -1


/**
 * @brief Configure the video encoder parameters
 * @details Use this function to configure the video encoder before you
 *          start to encode or record video. To encode or record
 *          video, call the @c camera_start_video() or the @c
 *          camera_start_encode() function. The parameters that you can
 *          configure depend on the codec you selected using @c
 *          camera_set_video_property().
 *
 *          For the @c args argument, you can provide one or more
 *          parameter-value pairs using the parameter enumerations defined
 *          by the following enumerated types:
 *          - @c ::camera_h264avc_parameters_t
 *
 *          Multiple parameter-value pairs are delimited using a comma.
 *          The parameter that you choose depends on the video codec you
 *          want to use. For example, for the H.264/AVC codec, you use the
 *          parameter enumerations defined in @c ::camera_h264avc_parameters_t
 *          enumerated type and the correct type for the value, such as an @c
 *          int or @c double.
 *
 *          You can specify multiple parameter-value pairs by delimiting them
 *          with a comma as follows:
 * @code
 * camera_set_videoencoder_parameter( camera_handle,
 *                   CAMERA_H264AVC_BITRATE, 1000000,
 *                   CAMERA_H264AVC_KEYFRAMEINTERVAL, 60,
 *                   CAMERA_H264AVC_RATECONTROL, CAMERA_H264AVC_RATECONTROL_CBR,
 *                   CAMERA_H264AVC_PROFILE, CAMERA_H264AVC_PROFILE_HIGH,
 *                   CAMERA_H264AVC_LEVEL, CAMERA_H264AVC_LEVEL_4 );
 *
 * @endcode
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param args... A series of comma-delimited parameter-value pairs.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
#define camera_set_videoencoder_parameter(handle, args...) \
   camera_private_set_videoencoder_parameter(handle, args, CAMERA_PARAMETER_END)


/**
 * @internal
 * For internal use only. Use the camera_set_videoencoder_parameter() function
 * instead which auto-terminates the ... varargs list.
 */
camera_error_t
camera_private_set_videoencoder_parameter(camera_handle_t handle,
                                          ...);


/**
 * @brief Retrieve the current value of a video encoder parameter
 * @details Use this function to retrieve the currently set video encoder
 *          parameters. The parameters that you can retrieve depend on the codec
 *          you selected using @c camera_set_video_property().
 *
 *          For the @c args argument, you can provide one or more
 *          parameter-value pairs using the parameter enumerations defined
 *          by the following enumerated types:
 *          - @c ::camera_h264avc_parameters_t
 *
 *          Multiple parameter-value pairs are delimited using a comma.
 *          The parameter name that you choose depends on the video codec that
 *          is configured. For example, for H.264/AVC, use a parameter
 *          enumeration from the @c ::camera_h264avc_parameters_t enumerated
 *          type and the expected type for each value, such as an @c int or
 *          @c double.
 *
 *          For example, you can get the H.264/AVC parameter-value pairs as
 *          shown in the following code:
 * @code
 * camera_get_videoencoder_parameter( camera_handle,
 *     CAMERA_H264AVC_BITRATE, &bitrate,
 *     CAMERA_H264AVC_ENTROPYCODING, &entropy_coding,
 *     CAMERA_H264AVC_SLICETYPE, &slice_type,
 *     CAMERA_H264AVC_SLICESIZE, &slice_size );
 * @endcode
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param args... A series of comma-delimited parameter-value pairs where each
 *                value must be a pointer a variable of the expected type.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
#define camera_get_videoencoder_parameter(handle, args...) \
    camera_private_get_videoencoder_parameter(handle, args, CAMERA_PARAMETER_END)


/**
 * @internal
 * For internal use only. Use the camera_get_videoencoder_parameter() function
 * instead which auto-terminates the ... varargs list.
 */
camera_error_t
camera_private_get_videoencoder_parameter(camera_handle_t handle,
                                          ...);


/**
 * @brief Retrieve the supported values of a video encoder parameter
 * @details Use this function to determine whether a specific video encoder
 *          parameter is supported and to determine the acceptable values for
 *          each supported parameter.
 *
 *          Ensure that the @c values argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          values argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in the @c numsupported argument. You can then allocate an array of
 *          the appropriate size and invoke the function again with the @c
 *          numasked argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 *          The values that you retrieve using this function can be written to
 *          the given parameter using the @c camera_set_videoencoder_parameter()
 *          function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param parameter The parameter that you want to query supported values for.
 *                  The enumerated type that you select your parameter from must
 *                  correspond with the currently configured video codec.
 *                  For example, if you are using the H.264/AVC video codec,
 *                  you can query parameters from the
 *                  @c ::camera_h264avc_parameters_t enumerated type.
 * @param numasked The requested number of values to return in the @c values
 *                 array. You can specify a value of 0 to determine the number
 *                 of supported values.
 * @param numsupported A pointer to an @c int value that is updated with the
 *                     the number of supported video encoder parameters.
 * @param values  A pointer to an @c int array. The array is updated
 *                with the values supported for the queried parameter. Ensure
 *                that you allocate an array with the same number of elements
 *                as the @c numasked argument. If the @c maxmin flag returns
 *                @c true, then the first value returned in the @c values array
 *                is the maximum supported value for the parameter, and the
 *                second value returned is the minimum supported value for the
 *                parameter.
 * @param maxmin A pointer to a @c bool value which will be set to @c true
 *               if the values returned should be interpreted as a maximum and
 *               a minimum value, or set to @c false if the values only
 *               describe the discrete encoder parameter values supported.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed. @c #CAMERA_EOPNOTSUPP is returned when a given parameter
 *         is not supported for one of these reasons:
 *         - The current value of another parameter has made @c parameter
 *           invalid.
 *         - The queried @c parameter is not supported by the platform.
 *           It is important to recognize that if you change the value of one
 *           parameter, a parmeter that previously was not supported may
 *           now become supported (or vice-versa).
 */
camera_error_t
camera_get_supported_videoencoder_parameter_values(camera_handle_t handle,
    int parameter, int numasked, int *numsupported, int *values, bool *maxmin);


#ifdef __cplusplus
}
#endif

#endif // __CAMERA_ENCODER_H__
