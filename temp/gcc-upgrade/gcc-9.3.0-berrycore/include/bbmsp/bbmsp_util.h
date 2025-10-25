/**
 * @file bbmsp_util.h
 *
 * @brief Functions and structures that allow your app to create,
 * retrieve, and destroy images for a user's BBM profile display picture
 * and the profile box icon for your app.
 *
 * @copyright Copyright (C) Research In Motion Limited 2012. All rights reserved.
 */

#ifndef BBMSP_UTIL_H_
#define BBMSP_UTIL_H_

#include "bbmsp.h"

#include <stdio.h>

__BEGIN_DECLS

/**
 * @brief A structure that represents a user's display image.
 *
 * @since BlackBerry 10.0.0
 */

typedef struct bbmsp_image_t bbmsp_image_t;

/**
 * @brief The image types supported by the BBM Social Platform
 *
 * @since BlackBerry 10.0.0
 */
typedef enum
{
  /**
   * @since BlackBerry 10.0.0
   */
  BBMSP_IMAGE_TYPE_JPG = 0,
  /**
   * @since BlackBerry 10.0.0
   */
  BBMSP_IMAGE_TYPE_PNG = 1,
  /**
   * @since BlackBerry 10.0.0
   */
  BBMSP_IMAGE_TYPE_GIF = 2,
  /**
   * @since BlackBerry 10.0.0
   */
  BBMSP_IMAGE_TYPE_BMP = 3
} bbmsp_image_type_t;

/**
 * @brief Creates an empty @c bbmsp_image_t.
 *
 * @param image An updated pointer to hold the empty @c bbmsp_image_t. If
 * a null pointer is provided, this method returns @c BBMSP_FAILURE.
 *
 * @return BBMSP_FAILURE if a parameter is invalid; BBMSP_SUCCESS otherwise.
 * @since BlackBerry 10.0.0
 */
BBMSP_API int bbmsp_image_create_empty(bbmsp_image_t** image);

/**
 * @brief Creates a new @c bbmsp_image_t to hold an image.
 *
 * @details Images should be constructed by using the complete image file data that is read from the
 * image source file, not just the canvas data. The image size must be > 0 and < * 32 KB (32 * 1024).
 * Pixel size should be 333 x 333.
 *
 * @param image An updated a pointer to the @c bbmsp_image_t.
 * @param type The image type. If an invalid MIME type is provided,
 * the behaviour of this method is undefined.

 * @param data A pointer to the image data. Cannot be null.
 * @param data_size The size of the image data in bytes. Must be > 0.
 *
 * @return BBMSP_SUCCESS if successful, BBMSP_FAILURE otherwise.
 * @see bbmsp_image_type_t, BBMSP_SUCCESS, BBMSP_FAILURE
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t bbmsp_image_create(
    bbmsp_image_t** image,
    const bbmsp_image_type_t type,
    const char* data,
    const unsigned int data_size);

/**
 * @brief Destroy an image.
 *
 * @details Destroys the @bbmsp_image_t that represents the image and frees up the associated memory.
 *
 * @param image A pointer to the image to destroy.
 *
 * @return BBMSP_SUCCESS if successful, BBMSP_FAILURE otherwise.
 * @see bbmsp_image_type_t, BBMSP_SUCCESS, BBMSP_FAILURE
 * @since BlackBerry 10.0.0
 */
BBMSP_API int bbmsp_image_destroy(bbmsp_image_t** image);

/**
 * @brief Returns the image MIME type.
 *
 * @details If an invalid MIME type was provided, the behaviour of this method
 * is undefined.
 *
 * @param image A pointer to the @c bbmsp_image_t.
 *
 * @return the image MIME type.
 * @see bbmsp_image_t, bbmsp_image_create
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_image_type_t bbmsp_image_get_type(bbmsp_image_t* image);

/**
 * @brief Retrieve the image data.
 *
 * @param image A pointer to the image whose data to retrieve.
 *
 * @return A pointer to the buffer that contains the image data.
 * @see bbmsp_image_type_t
 * @since BlackBerry 10.0.0
 */
BBMSP_API char* bbmsp_image_get_data(bbmsp_image_t* image);

/**
 * @brief Retrieve the size of the image data.
 *
 * @param image A pointer to the image whose data size to retrieve.
 *
 * @return The size of the image data.
 * @see bbmsp_image_type_t
 * @since BlackBerry 10.0.0
 */
BBMSP_API unsigned int bbmsp_image_get_data_size(bbmsp_image_t* image);

__END_DECLS

#endif /* BBMSP_UTIL_H_ */
