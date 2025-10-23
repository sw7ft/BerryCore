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

#ifndef __CAMERA_H264AVC_H__
#define __CAMERA_H264AVC_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file camera_h264avc.h
 *
 * @brief Supported H.264/AVC video encoder parameters
 *
 * @details This file defines the video encoder parameters supported by the
 *          H.264/AVC (MPEG-4 Part 10 Advanced Video Coding) encoder. These
 *          are the parameters to use with the @c
 *          camera_set_videoencoder_parameter() function if you configured
 *          @c #CAMERA_IMGPROP_VIDEOCODEC to @c #CAMERA_VIDEOCODEC_AVC1 or @c
 *          #CAMERA_VIDEOCODEC_H264 using @c camera_set_video_property().
 *
 *          Use the parameters provided in this file for parameter-value
 *          pairs that you pass to the video encoder configuration functions
 *          in camera_encoder.h.
 */


/**
 * The list of supported video encoder parameters for H.264/AVC.
 * Use these as parameters in parameter-value pairs that you pass as an
 * argument list to video encoder configuration functions.
 */
typedef enum {
    /**
     * The target bitrate or target average bitrate.
     * - When the @c CAMERA_H264AVC_RATECONTROL parameter is set to @c
     *   #CAMERA_H264AVC_RATECONTROL_CBR, this parameter represents the
     *   target bitrate of the encoded video.
     * - When @c CAMERA_H264AVC_RATECONTROL parameter is set to @c
     *   #CAMERA_H264AVC_RATECONTROL_VBR, this parameter represents the
     *   target average bitrate of the encoded video
     * - When @c CAMERA_H264AVC_RATECONTROL parameter is set to @c
     *   #CAMERA_H264AVC_RATECONTROL_NONE, this parameter is ignored.
     *
     *   The units are in bits per second as an @c unsigned @c int value.
     */
    CAMERA_H264AVC_BITRATE = 0,
    /**
     * The interval (in frames) between the generation of each keyframe as an @c
     * @c unsigned @c int value.
     */
    CAMERA_H264AVC_KEYFRAMEINTERVAL,
    /**
     * The algorithm used to generate NAL slices. The value must be set to a
     * value from the @c ::camera_h264avc_slicetype_t enumerated type. This
     * parameter can only be modified before you start to encode video.
     */
    CAMERA_H264AVC_SLICETYPE,
    /**
     * The slice size as an @c unsigned @c int value. 
     * Depending on the value you configured for @c #CAMERA_H264AVC_SLICETYPE,
     * the slice size is interpreted as follows:
     * - @c #CAMERA_H264AVC_SLICE_FRAME: The slice size is ignored.
     * - @c #CAMERA_H264AVC_SLICE_BYTES: The slice size represents
     *                                   the size of the slice in bytes.
     * - @c #CAMERA_H264AVC_SLICE_MACROBLOCKS: The slice size represents
     *                                         the size as a number of
     *                                         macroblocks.
     * On some devices, this parameter can only be modified before you start
     * encoding video.
     */
    CAMERA_H264AVC_SLICESIZE,
    /**
     * The profile used to encode the video. The value must be set to a
     * value from @c ::camera_h264avc_profile_t. You can only modify
     * this parameter before you start encoding video.
     */
    CAMERA_H264AVC_PROFILE,
    /**
     * The level used to encode the video. The value must be set to a
     * value from @c ::camera_h264avc_level_t. You can only modify
     * this parameter before you start encoding video.
     */
    CAMERA_H264AVC_LEVEL,
    /**
     * The entropy coding method to use. The value must be set to a value
     * from @c ::camera_h264avc_entropycoding_t. You can only
     * modify this parameter before you start encoding video.
     */
    CAMERA_H264AVC_ENTROPYCODING,
    /**
     * The rate control method used for the encoding.  The value must be set to
     * a value from @c ::camera_h264avc_ratecontrol_t. You can only
     * modify this parameter before you start encoding video.
     */
    CAMERA_H264AVC_RATECONTROL,
    /**
     * The Quantization Parameter (QP) that is used to encode key (I) frames
     * when the @c #CAMERA_H264AVC_RATECONTROL parameter is set to @c
     * #CAMERA_H264AVC_RATECONTROL_NONE. For other rate control methods, this
     * parameter has no impact. The value being set is an @c unsigned @c int
     * value.
     */
    CAMERA_H264AVC_QPI,
    /**
     * The Quantization Parameter (QP) that is used to encode inter (P) frames
     * when the @c #CAMERA_H264AVC_RATECONTROL parameter is set to @c
     * #CAMERA_H264AVC_RATECONTROL_NONE. For other rate control methods, this
     * parameter has no impact. The value being set is an @c unsigned @c int
     * value.
     */
    CAMERA_H264AVC_QPP,
    /**
     * An end-of-list identifier.
     */
    CAMERA_H264AVC_NUMPARAMETERS
} camera_h264avc_parameters_t;


/**
 * The supported slice types for H.264/AVC. These are acceptable values to
 * use when you configure the @c #CAMERA_H264AVC_SLICETYPE parameter in
 * parameter-value pairs that you pass in encoding functions.
 * Use @c camera_get_supported_videoencoder_parameter_values() to determine
 * the supported values at runtime.
 */
typedef enum {
    /**
     * The frame is encoded as a single slice NAL.
     */
    CAMERA_H264AVC_SLICE_FRAME = 0,
    /**
     * The frame is encoded as multiple slice NALs where each slice NAL size
     * does not exceed the configured @c #CAMERA_H264AVC_SLICESIZE in bytes.
    */
   CAMERA_H264AVC_SLICE_BYTES,
   /**
    * The frame is encoded as multiple slice NALs where each slice NAL size
    * does not exceed the configured number of @c #CAMERA_H264AVC_SLICESIZE
    * macroblocks.
   */
   CAMERA_H264AVC_SLICE_MACROBLOCKS
} camera_h264avc_slicetype_t;


/**
 * Supported profiles for H.264/AVC. These are the acceptable values to use
 * when you use the @c #CAMERA_H264AVC_PROFILE parameter in a parameter-value
 * pair. For information about these profiles, refer to the H.264/AVC standard.
 * Use @c camera_get_supported_videoencoder_parameter_values() to determine
 * the supported values at runtime.
 */
typedef enum {
    /**
     * The encoder automatically selects the profile to use based on
     * configuration and video resolution.
     */
    CAMERA_H264AVC_PROFILE_AUTOMATIC = 0,
    /**
     * Baseline profile of H.264/AVC.
     */
    CAMERA_H264AVC_PROFILE_BASELINE,
    /**
     * High profile of H.264/AVC.
     */
    CAMERA_H264AVC_PROFILE_HIGH,
    /**
     * Constrained Baseline profile (CBP) of H.264/AVC.
     */
    CAMERA_H264AVC_PROFILE_CONSTRAINEDBASELINE,
    /**
     * Constrained High profile (CHP) of H.264/AVC.
     */
    CAMERA_H264AVC_PROFILE_CONSTRAINEDHIGH
} camera_h264avc_profile_t;


/**
 * The supported levels for H.264/AVC. These are the valid values to use
 * when configuring the @c #CAMERA_H264AVC_LEVEL parameter. For more information
 * about these levels, refer to the H.264/AVC standard.
 * Use @c camera_get_supported_videoencoder_parameter_values() to determine
 * the supported values at runtime.
 */
typedef enum {
    /**
     * The encoder automatically selects the level to use based on
     * configuration and video resolution.
     */
    CAMERA_H264AVC_LEVEL_AUTOMATIC = 0,
    /**
     * Level 1 of H.264/AVC.
     */
    CAMERA_H264AVC_LEVEL_1,
    /**
     * Level 1B of H.264/AVC.
     */
    CAMERA_H264AVC_LEVEL_1B,
    /**
     * Level 1.1 of H.264/AVC.
     */
    CAMERA_H264AVC_LEVEL_11,
    /**
     * Level 1.2 of H.264/AVC.
     */
    CAMERA_H264AVC_LEVEL_12,
    /**
     * Level 1.3 of H.264/AVC.
     */
    CAMERA_H264AVC_LEVEL_13,
    /**
     * Level 2 of H.264/AVC.
     */
    CAMERA_H264AVC_LEVEL_2,
    /**
     * Level 2.1 of H.264/AVC.
     */
    CAMERA_H264AVC_LEVEL_21,
    /**
     * Level 2.2 of H.264/AVC.
     */
    CAMERA_H264AVC_LEVEL_22,
    /**
     * Level 3 of H.264/AVC.
     */
    CAMERA_H264AVC_LEVEL_3,
    /**
     * Level 3.1 of H.264/AVC.
     */
    CAMERA_H264AVC_LEVEL_31,
    /**
     * Level 3.2 of H.264/AVC.
     */
    CAMERA_H264AVC_LEVEL_32,
    /**
     * Level 4 of H.264/AVC.
     */
    CAMERA_H264AVC_LEVEL_4,
    /**
     * Level 4.1 of H.264/AVC.
     */
    CAMERA_H264AVC_LEVEL_41,
    /**
     * Level 4.2 of H.264/AVC.
     */
    CAMERA_H264AVC_LEVEL_42,
    /**
     * Level 5 of H.264/AVC.
     */
    CAMERA_H264AVC_LEVEL_5,
    /**
     * Level 5.1 of H.264/AVC.
     */
    CAMERA_H264AVC_LEVEL_51
} camera_h264avc_level_t;


/**
 * The supported entropy coding methods for H.264/AVC. These are the valid
 * values to use when configuring the @c #CAMERA_H264AVC_ENTROPYCODING
 * parameter.
 * Use @c camera_get_supported_videoencoder_parameter_values() to determine
 * the supported values at runtime.
 */
typedef enum {
    /**
     * The video is encoded using Context-based Adaptive Variable Length
     * Coding (CAVLC).
     */
    CAMERA_H264AVC_ENTROPYCODING_CAVLC = 0,
    /**
     * The video is encoded using Context-based Adaptive Binary Arithmetic
     * Coding (CABAC). This entropy coding method is not permitted
     * for some of the supported profiles for H.264/AVC (see @c
     * ::camera_h264avc_profile_t).
    */
   CAMERA_H264AVC_ENTROPYCODING_CABAC
} camera_h264avc_entropycoding_t;


/**
 * The supported rate control algorithms for H.264/AVC. These are the valid
 * values to use to configure the @c #CAMERA_H264AVC_RATECONTROL parameter.
 * Use @c camera_get_supported_videoencoder_parameter_values() to determine
 * the supported values at runtime.
 */
typedef enum {
    /**
     * No rate control algorithm is used and as such, disables rate control
     * (referred to as constant quality encoding). Constant quality encoding
     * means that the bitrate varies with the scene content but the quality
     * stays constant.
     */
    CAMERA_H264AVC_RATECONTROL_NONE = 0,
    /**
     * Constant Bit Rate (CBR) encoding is used. This control algorithm
     * indicates that the bitrate will remain constant while quality will vary.
     * The bitrate that is maintained is specified by the @c
     * #CAMERA_H264AVC_BITRATE parameter.
    */
   CAMERA_H264AVC_RATECONTROL_CBR,
   /**
    * Variable Bit Rate (VBR) encoding is used. This control algorithm indicates
    * that the average bitrate remains constant while quality may vary. The
    * average bitrate that is maintained is specified by the @c
    * @c #CAMERA_H264AVC_BITRATE parameter.
   */
  CAMERA_H264AVC_RATECONTROL_VBR,
} camera_h264avc_ratecontrol_t;


#ifdef __cplusplus
}
#endif

#endif // __CAMERA_H264AVC_H__
