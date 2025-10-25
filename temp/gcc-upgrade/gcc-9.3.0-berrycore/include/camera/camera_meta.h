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

#ifndef __CAMERA_META_H__
#define __CAMERA_META_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file camera_meta.h
 *
 * @brief This file defines functions that you can use to extract the metadata
 *        that is associated with a camera buffer.
 * @details Camera buffers are represented by a @c ::camera_buffer_t structure.
 *          Whenever you have a camera buffer, it is possible that there is
 *          metadata associated with it. Use functions from this module to
 *          extract metadata from a camera buffer.
 *
 *          @e Metadata is the descriptive information about a camera buffer.
 *          The following functions are commonly used to extract the required
 *          information from the payload:
 *          - @c camera_meta_get_face_region()
 *          - @c camera_meta_get_face_score()
 *          - @c camera_meta_get_face_yaw()
 *          - @c camera_meta_get_face_pitch()
 *          - @c camera_meta_get_face_roll()
 *          - @c camera_meta_get_exif()
 *
 */


/**
 * The metadata format payload type. Metadata is the descriptive
 * information about the contents in a camera buffer (@c ::camera_buffer_t).
 */
typedef enum {
    /**
     * No metadata format is used.
     */
    CAMERA_METAFORMAT_NONE = 0,
    /**
     * Metadata is encoded in Exchangeable Image File Format(EXIF).
     */
    CAMERA_METAFORMAT_EXIF,
    /**
     * Metadata is encoded in XML-based Extensible Metadata Platform (XMP)
     * format. XMP is an open-source, public standard. XMP metadata can be
     * applied to many image file types.
     */
    CAMERA_METAFORMAT_XMP,
    /**
     * Face metadata is encoded in binary format. This binary format
     * can be passed to the following functions to extract metadata about
     * the face:
     * - @c camera_meta_get_face_region()
     * - @c camera_meta_get_face_score()
     * - @c camera_meta_get_face_yaw()
     * - @c camera_meta_get_face_pitch()
     * - @c camera_meta_get_face_roll()
     */
    CAMERA_METAFORMAT_FACE,
    /**
     * Histogram data is encoded in binary format. This binary format data
     * can be passed to the following functions to extract histogram values.
     * - @c camera_meta_get_rgby_histogram_values()
     */
    CAMERA_METAFORMAT_HISTOGRAM_RGBY,
    /**
     * Exposure information is encoded in binary format.
     * This binary format data can be passed to following functions to extract
     * data.
     * - @c camera_meta_get_shutter_speed()
     * - @c camera_meta_get_ISO()
     */
    CAMERA_METAFORMAT_EXPOSURE,
    /**
     * Whitebalance information is encoded in binary format.
     * This binary format data can be passed to following functions to extract
     * whitebalance.
     * - @c camera_meta_get_whitebalance()
     */
    CAMERA_METAFORMAT_WHITEBALANCE,
    /**
     * @internal
     * Reserved for internal use.
     */
    CAMERA_METAFORMAT_CONTENT_PROTECTION_REQUIRED,
    /**
     * The total number of metadata formats available.
     */
    CAMERA_METAFORMAT_NUMMETAFORMATS
} camera_metaformat_t;


/**
 * An opaque type used as a handle to a single piece of metadata.
 * Use the @c camera_meta_iterate_metadata() function to extract these pieces
 * of metadata from the associated camera buffer.
 */
typedef struct _camera_metadata* camera_metadata_t;


/**
 * The Histogram bin descriptor.
 */
typedef struct {
    /**
     * The histogram data.
     */
    uint32_t *data;
    /**
     * The size of the histogram data.
     */
    uint32_t bin_size;
    /**
     * The maximum value possible in each bin.
     */
    uint32_t bin_value_limit;
    /**
     * The number of samples taken for histogram data generation.
     */
    uint32_t number_of_sample_points;
} camera_meta_histogram_t;


/**
 * @brief Extract all metadata from a buffer for processing
 * @details This function extracts all metadata associated with the provided
 *          buffer and passes it one piece at a time to a user-defined consumer
 *          function for further processing.
 *
 *          The user-defined metadata consumer function must have the following
 *          signature:
 *          @code
 *          bool metadata_consumer(const camera_metadata_t metadata,
 *                                 camera_metaformat_t format,
 *                                 void* arg);
 *          @endcode
 *          - metadata: The piece of metadata extracted.
 *          - format: The type of the metadata extracted.
 *          - arg: The user-specified argument in the @c arg argument of the
 *                 @c camera_meta_iterate_metadata() function.
 *
 *          The metadata consumer function returns a @c bool value to indicate
 *          whether the iterator loop should continue. When the provided
 *          consumer function returns @c true, metadata processing will continue.
 *          Metadata processing stops when the consumer function returns @c
 *          false.
 *
 * @param buffer A pointer to the buffer from which to extract metadata.
 * @param metadata_consumer A pointer to the user-defined consumer function
 *                          that is invoked for each piece of metadata that is
 *                          extracted.
 * @param arg A user-defined argument that is passed to the @c metadata_consumer
 *            function each time it is invoked.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
int camera_meta_iterate_metadata(const camera_buffer_t *buffer,
                                 bool(*metadata_consumer)(const camera_metadata_t,
                                                          camera_metaformat_t,
                                                          void*),
                                 void *arg);


/**
 * @brief Retrieve the bounding box associated with a face that is detected in
 *        the image
 * @details This function extracts the bounding box from the provided face
 *          metadata and returns it as a @c ::camera_region_t value.
 *
 * @param metadata The metadata supplied to the user-defined consumer function
 *                 by @c camera_meta_iterate_metadata().
 * @param region A pointer to a @c ::camera_region_t structure that will be
 *               updated with the coordinates of the bounding box defining
 *               the face.
 * @return @c #CAMERA_EOK when the function successfully
 *         completes, otherwise another @c ::camera_error_t value
 *         that provides the reason that the call failed.
 */
int camera_meta_get_face_region(const camera_metadata_t metadata,
                                camera_region_t *region);


/**
 * @brief Retrieve the score that represents the certainty that a face has been
 *        detected in the image
 * @details This function is used to retrieve the score information (or face
 *          score) from the provided face metadata.
 *          The score is a value between 0 and 100 that represents the
 *          confidence that the object identified in the image is a face.
 *
 * @param metadata The metadata supplied to the user-defined consumer function
 *                 by @c camera_meta_iterate_metadata().
 * @param score The returned face score as a value between 0 and 100.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
int camera_meta_get_face_score(const camera_metadata_t metadata,
                               float *score);


/**
 * @brief Extract the detected face @e yaw angle from the provided face metadata
 * @details The yaw value ranges from -180 degrees to +180 degrees relative to
 *          the preview buffer coordinate space. A negative yaw angle indicates
 *          that the face is looking to the left from the face's frame of
 *          reference. A positive yaw angle indicates that the face is looking
 *          to the right from the face's frame of reference.
 *
 * @param metadata The metadata supplied to the user-defined consumer function
 *                 by @c camera_meta_iterate_metadata().
 * @param yaw The angle of rotation of the face around the y-axis.
 * @return @c #CAMERA_EOK when the function successfully completes, @c
 *          #CAMERA_ENODATA if the camera did not provide a roll value otherwise
 *          another @c ::camera_error_t value that provides the reason that the
 *          call failed.
 */
int camera_meta_get_face_yaw(const camera_metadata_t metadata,
                             float *yaw);



/**
 * @brief Extract the detected face @e roll angle from the provided face
 *        metadata
 * @details The roll value ranges from -180 degrees to +180 degrees relative
 *          to the preview buffer coordinate space. A negative roll angle
 *          indicates that the face is rotated counter-clockwise from the
 *          camera's frame of reference. A positive roll angle indicates that
 *          the face is rotated clockwise from the camera's frame of reference.
 *
 * @param metadata The metadata supplied to the user-defined consumer function
 *                 by @c camera_meta_iterate_metadata().
 * @param roll The angle of rotation of the face around the z-axis.
 * @return  @c #CAMERA_EOK when the function successfully completes, @c
 *          #CAMERA_ENODATA if the camera did not provide a roll value otherwise
 *          another @c ::camera_error_t value that provides the reason that the
 *          call failed.
 */
int camera_meta_get_face_roll(const camera_metadata_t metadata,
                              float *roll);


/**
 * @brief Extract the detected face @e pitch angle from the provided face
 *        metadata
 * @details The pitch value ranges from -180 degrees to +180 degrees relative
 *          to the preview buffer coordinate space. A negative pitch angle
 *          indicates that the face is tilted downward. A positive pitch angle
 *          indicates that the face is tilted upward.
 *
 * @param metadata The metadata supplied to the user-defined consumer function
 *                 by @c camera_meta_iterate_metadata().
 * @param pitch The angle of rotation of the face around the x-axis.
 * @return @c #CAMERA_EOK when the function successfully completes, @c
 *         #CAMERA_ENODATA if the camera did not provide a pitch value otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
int camera_meta_get_face_pitch(const camera_metadata_t metadata,
                               float *pitch);


/**
 * @brief Extract the detected face @e identity from the provided face
 *        metadata
 * @details The identity is a number which uniquely identifies this face
 *          across successive frames.
 *
 * @param metadata The metadata supplied to the user-defined consumer function
 *                 by @c camera_meta_iterate_metadata().
 * @param id The returned identity associated with the face.
 * @return @c #CAMERA_EOK when the function successfully completes, @c
 *         #CAMERA_ENODATA if the camera did not provide an identity value otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
int camera_meta_get_face_id(const camera_metadata_t metadata,
                            uint32_t *id);


/**
 * @brief Retrieve the Exchangeable Image File Format (EXIF) buffer pointer
 *        from the metadata
 * @details Use this function to extract a pointer to the EXIF binary data and
 *          the size of the EXIF binary data.
 *
 * @param metadata The metadata supplied to the user-defined consumer function
 *                 by @c camera_meta_iterate_metadata().
 * @param data Returns a pointer to the binary EXIF data.
 * @param size The returned size of the binary EXIF data.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
int camera_meta_get_exif(const camera_metadata_t metadata,
                         unsigned char **data,
                         uint64_t *size);


/**
 * @brief Retrieve the RGBY histogram
 * @details Use this function to extract RGBY histograms from the provided
 *          metadata.
 *
 * @param metadata The metadata of type @c #CAMERA_METAFORMAT_HISTOGRAM_RGBY
 *                 supplied to the user-defined consumer function
 *                 by @c camera_meta_iterate_metadata().
 *
 * @param red A pointer to a @c ::camera_meta_histogram_t structure that will
 *            be filled with the red histogram data.
 * @param green A pointer to a @c ::camera_meta_histogram_t structure that will
 *              be filled with the green histogram data.
 * @param blue A pointer to a @c ::camera_meta_histogram_t structure that will
 *             be filled with the blue histogram data.
 * @param luma A pointer to a @c ::camera_meta_histogram_t structure that will
 *             be filled with the luma histogram data.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
int camera_meta_get_rgby_histogram_values(const camera_metadata_t metadata,
                                          camera_meta_histogram_t *red,
                                          camera_meta_histogram_t *green,
                                          camera_meta_histogram_t *blue,
                                          camera_meta_histogram_t *luma);


/**
 * @brief Retrieve the shutter speed for the frame
 * @details Use this function to extract the shutter speed used when the frame
 *          was captured from the provided metadata.
 *
 * @param metadata The metadata of type @c #CAMERA_METAFORMAT_EXPOSURE
 *                 supplied to the user-defined consumer function by
 *                 @c camera_meta_iterate_metadata().
 * @param shutter_speed The returned shutter speed in seconds.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
int camera_meta_get_shutter_speed(const camera_metadata_t metadata,
                                  double *shutter_speed);


/**
 * @brief Retrieve the ISO setting for the frame
 * @details Use this function to extract the ISO setting used when the frame was
 *          captured from the provided metadata.
 *
 * @param metadata The metadata of type @c #CAMERA_METAFORMAT_EXPOSURE
 *                 supplied to the user-defined consumer function by
 *                 @c camera_meta_iterate_metadata().
 * @param iso The returned ISO setting.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
int camera_meta_get_ISO(const camera_metadata_t metadata,
                        uint32_t *iso);


/**

 * @brief Retrieve the whitebalance for the frame
 * @details Use this function to extract the whitebalance setting used when the
 *          frame was captured from provided metadata.
 *
 * @param metadata The metadata of type @c #CAMERA_METAFORMAT_WHITEBALANCE
 *                 supplied to the user-defined consumer function
 *                 @c camera_meta_iterate_metadata().
 * @param whitebalance The returned white balance setting, in Kelvin.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
int camera_meta_get_whitebalance(const camera_metadata_t metadata,
                                 uint16_t *whitebalance);

#ifdef __cplusplus
}
#endif

#endif // __CAMERA_META_H__
