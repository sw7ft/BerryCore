/*
 * $QNXLicenseC:
 * Copyright 2013-2014, QNX Software Systems. All Rights Reserved.
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

#ifndef __CAMERA_HDR_H__
#define __CAMERA_HDR_H__

#include <camera/camera_api.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @file camera_hdr.h
 *
 * @brief Functions to take high dynamic range (HDR) photos
 *
 * @details This file defines functions that applications can
 *          use to take high dynamic range (HDR) photos.
 *
 *          @e HDR imaging is a process for increasing the dynamic
 *          range of a photograph. The dynamic range of a photograph
 *          is defined as the difference between the darkest and brightest
 *          areas in the image. The process involves taking multiple photographs
 *          in quick succession at different exposure levels and then
 *          compositing them for final output.
 *
 *          There are two ways to generate HDR photos:
 *          - @ref camera_hdr_realtime_mode
 *          - @ref camera_hdr_offline_mode
 *
 * @section camera_hdr_realtime_mode Realtime HDR capture mode
 *          In realtime HDR capture mode, the HDR session is explicitly bound to
 *          an open camera handle. This binding allows the HDR session to
 *          directly operate the camera and capture the necessary input images
 *          to produce an output HDR image. The camera must be initialized and
 *          configured for exposure bracketing mode
 *          (@c CAMERA_VFMODE_EV_BRACKETING) prior to using the HDR module.
 *          The following example code illustrates how to use realtime HDR
 *          capture mode:
 *
 * @code
 *    camera_hdr_t hdr_session = NULL;
 *    camera_error_t result;
 *    camera_handle_t camera_handle;
 *
 *    // Open camera and start the viewfinder in EV bracketing mode
 *    // (not shown - refer to @c camera_api.h for details)
 *
 *    // Create and initialize the HDR session
 *    result = camera_hdr_create(&hdr_session);
 *
 *    // Bind the camera to the HDR session
 *    result = camera_hdr_bind_camera(hdr_session,
 *                                    camera_handle);
 *
 *    // Trigger an HDR capture
 *    result = camera_hdr_take_photo(hdr_session,
 *                                   my_shutter_callback_function,
 *                                   NULL,   // raw callbacks are not supported
 *                                   my_postview_callback_function,
 *                                   my_image_callback_function,
 *                                   my_unprocessed_image_callback_function,
 *                                   NULL,   // raw callbacks are not supported
 *                                   (void*)my_arbitrary_context_arg,
 *                                   false);
 *
 *    // clean up HDR session
 *    result = camera_hdr_destroy(hdr_session);
 * @endcode
 *          The above example code purposely omits implementation-specific
 *          details such as opening and configuring the camera, error checking,
 *          optional configuration, capability discovery, and the actual
 *          handling of output image buffers from the @c camera_hdr_take_photo()
 *          function.
 *
 * @section camera_hdr_offline_mode Offline HDR rendering mode
 *          In offline HDR rendering mode, the HDR module is explicitly given a
 *          series of input images at different exposure levels and then renders
 *          an output image. The details of how to acquire the input images is
 *          left as an implementation detail for the developer. Offline HDR
 *          rendering mode is provided to accommodate use cases where finer
 *          grained control over the capture conditions is desired. For example,
 *          an application may be designed to capture five exposure bracketed
 *          images as input and then provide the user with the option to render
 *          the final HDR image using any three of the five input images, or to
 *          render multiple HDR images for later consideration.
 *
 *          The following example code illustrates how to use offline HDR
 *          rendering mode:
 *
 * @code
 *    camera_hdr_t hdr_session = NULL;
 *    camera_error_t result;
 *    camera_buffer_t* underexposed_image;
 *    camera_buffer_t* normal_image;
 *    camera_buffer_t* overexposed_image;
 *    camera_buffer_t* rendered_image;
 *
 *    // Acquire three images at different exposure levels (not shown)
 *
 *    // Create and initialize the HDR session
 *    result = camera_hdr_create(&hdr_session);
 *
 *    // Add the three images to the HDR session
 *    result = camera_hdr_add_image_to_session(hdr_session,
 *                                             &underexposed_image,
 *                                             -2.0);
 *    result = camera_hdr_add_image_to_session(hdr_session,
 *                                             &normal_image,
 *                                             0.0);
 *    result = camera_hdr_add_image_to_session(hdr_session,
 *                                             overexposed_image,
 *                                             +2.0);
 *
 *    // render the HDR image
 *    result = camera_hdr_render(hdr_session,
 *                               &rendered_image,
 *                               CAMERA_HDR_RENDERTYPE_IMAGE);
 *
 *    // Free the three input image buffers (not shown)
 *
 *    // Save the rendered image to disk, or display on screen, etc. (not shown)
 *
 *    // Free the rendered image buffer
 *    camera_hdr_free_buffer(rendered_image);
 *
 *    // Clean up HDR session
 *    result = camera_hdr_destroy(hdr_session);
 * @endcode
 *          The above example code purposely omits implementation-specific
 *          details such as acquiring and releasing the input images, error
 *          checking, optional configuration and capability discovery.
 */


/**
 * An opaque type used as a handle to an HDR session.
 */
typedef struct _camera_hdr_t*  camera_hdr_t;


/**
 * Image render type. For use with the @c camera_hdr_render() function.
 */
typedef enum {
    /**
     * Reduced resolution image suitable for on-screen review.
     */
    CAMERA_HDR_RENDERTYPE_POSTVIEW = 0,

    /**
     * Full-resolution image.
     */
    CAMERA_HDR_RENDERTYPE_IMAGE

} camera_hdr_rendertype_t;


/**
 * @brief Create an HDR session handle
 *
 * @details Creates a new HDR session handle. A session handle is required to
 *          do HDR processing. When you are finished performing HDR processing,
 *          call @c camera_hdr_destroy() to clean up the memory that is used.
 *
 * @param hdr A pointer to the newly created HDR session handle.
 *
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_hdr_create(camera_hdr_t* hdr);


/**
 * @brief Get the HDR postview image size
 *
 * @details This function retrieves the currently configured
 *          HDR postview (review) image size.
 *
 * @param hdr The HDR session handle obtained from a call to @c
 *            camera_hdr_create().
 * @param width A pointer to the returned width of the HDR postview image.
 * @param height A pointer to the returned height of the HDR postview image.
 *
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_hdr_get_postview_size(camera_hdr_t hdr,
                             uint32_t* width,
                             uint32_t* height);


/**
 * @brief Set the HDR postview image size
 *
 * @details This function specifies the resolution of the HDR postview image
 *          buffer returned by @c camera_hdr_take_photo() or the image buffer
 *          returned by @c camera_hdr_render() when invoked with
 *          @c #CAMERA_HDR_RENDERTYPE_POSTVIEW.
 *
 *    @b Note: The HDR postview image size is reset when a camera is bound to
 *          the HDR session using @c camera_hdr_bind_camera().
 *
 * @param hdr The HDR session handle obtained from a call to @c
 *            camera_hdr_create().
 * @param width The width of the HDR postview image.
 * @param height The height of the HDR postview image.
 *
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_hdr_set_postview_size(camera_hdr_t hdr,
                             uint32_t width,
                             uint32_t height);


/**
 * @brief Get the HDR postview format
 *
 * @details This function queries the currently configured HDR postview image
 *          format.
 *
 * @param hdr The HDR session handle obtained from a call to @c
 *            camera_hdr_create().
 * @param format A pointer to the returned HDR postview image format.
 *
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_hdr_get_postview_format(camera_hdr_t hdr,
                               camera_frametype_t* format);


/**
 * @brief Set the HDR postview format
 *
 * @details The HDR postview format can be set to any of the formats returned by
 *          @c camera_hdr_get_supported_postview_formats().
 *
 * @param hdr The HDR session handle obtained from a call to @c
 *            camera_hdr_create().
 * @param format The HDR postview image format to set.
 *
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_hdr_set_postview_format(camera_hdr_t hdr,
                               camera_frametype_t format);


/**
 * @brief Retrieve the list of supported HDR postview formats
 *
 * @details This function returns the list of supported HDR postview formats
 *          that can be set using @c camera_hdr_set_postview_format().
 *
 *          Ensure that the @c formats argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          formats argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in @c numsupported argument. You can then allocate an array of the
 *          appropriate size and invoke the function again with @c numasked
 *          argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 * @param hdr The HDR session handle obtained from a call to @c
 *            camera_hdr_create().
 * @param numasked The requested number of HDR postview formats to
 *                 return in the @c formats array. You can specify a value of
 *                 0 to determine the number of HDR postview formats supported.
 * @param numsupported A pointer to an integer that is updated with the
 *                     number of HDR postview formats supported.
 * @param formats A pointer to a @c #camera_frametype_t array. The array is
 *                updated with the list of HDR postview formats supported.
 *                Ensure that you allocate an array with the
 *                same number of elements as the @c numasked argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_hdr_get_supported_postview_formats(camera_hdr_t hdr,
                                          uint32_t numasked,
                                          uint32_t* numsupported,
                                          camera_frametype_t* formats);


/**
 * @brief Get the HDR output image format
 *
 * @details This function queries the currently configured HDR output image
 *          format.
 *
 * @param hdr The HDR session handle obtained from a call to @c
 *            camera_hdr_create().
 * @param format A pointer to the returned HDR output image format.
 *
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_hdr_get_image_format(camera_hdr_t hdr,
                            camera_frametype_t* format);


/**
 * @brief Set the HDR output image format
 *
 * @details The HDR output image format can be set to any of the formats
 *          returned by @c camera_hdr_get_supported_image_formats().
 *
 * @param hdr The HDR session handle obtained from a call to @c
 *            camera_hdr_create().
 * @param format The HDR output image format to set.
 *
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_hdr_set_image_format(camera_hdr_t hdr,
                            camera_frametype_t format);


/**
 * @brief Retrieve the list of supported HDR output image formats
 *
 * @details This function returns the list of supported HDR output image formats
 *          that can be set using @c camera_hdr_set_image_format().
 *
 *          Ensure that the @c formats argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          formats argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in @c numsupported argument. You can then allocate an array of the
 *          appropriate size and invoke the function again with @c numasked
 *          argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 * @param hdr The HDR session handle obtained from a call to @c
 *            camera_hdr_create().
 * @param numasked The requested number of HDR output image formats to
 *                 return in the @c formats array. You can specify a value of
 *                 0 to determine the number of HDR output image formats
 *                 supported.
 * @param numsupported A pointer to an integer that is updated with the
 *                     number of HDR output image formats that are supported.
 * @param formats A pointer to a @c #camera_frametype_t array. The array is
 *                updated with the list of HDR output image formats that are
 *                supported. Ensure that you allocate an array with the
 *                same number of elements as the @c numasked argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_hdr_get_supported_image_formats(camera_hdr_t hdr,
                                       uint32_t numasked,
                                       uint32_t* numsupported,
                                       camera_frametype_t* formats);


/**
 * @brief Get the range of supported anti-ghosting factors
 *
 * @details This function is used to retrieve the range of supported
 *          anti-ghosting factors that can be set with
 *          @c camera_hdr_set_anti_ghosting_factor().
 *
 * @param hdr The HDR session handle obtained from a call to @c
 *            camera_hdr_create().
 * @param min A pointer to the returned minimum anti-ghosting factor.
 * @param max A pointer to the returned maximum anti-ghosting factor.
 *
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_hdr_get_anti_ghosting_range(camera_hdr_t hdr,
                                   double* min,
                                   double* max);


/**
 * @brief Get the current anti-ghosting factor
 *
 * @details When an HDR session is first created, calling this
 *          function returns the default anti-ghosting
 *          factor.
 *
 * @param hdr The HDR session handle obtained from a call to @c
 *            camera_hdr_create().
 * @param factor A pointer to the returned anti-ghosting factor.
 *
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_hdr_get_anti_ghosting_factor(camera_hdr_t hdr,
                                    double* factor);


/**
 * @brief Set the anti-ghosting factor for an HDR session.
 *
 * @details @e Ghosting is an artifact caused when objects in
 *          successive composited images are out of alignment due to
 *          motion. Anti-ghosting is an image processing algorithm that
 *          minimizes the effect of ghosting.
 *
 *          The anti-ghosting factor must be within the range returned by @c
 *          camera_hdr_get_anti_ghosting_range().
 *
 * @param hdr The HDR session handle obtained from a call to @c
 *            camera_hdr_create().
 * @param factor The amount of anti-ghosting to apply. Higher values
 *               result in a stronger reduction of ghosting.
 *
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_hdr_set_anti_ghosting_factor(camera_hdr_t hdr,
                                    double factor);


/**
 * @brief Get the minimum and maximum supported number of images
 *
 * @details The HDR algorithm requires a number of input images.
 *          The number of images must fall between the minimum and maximum value
 *          returned by this function (inclusive).
 *
 *          In @ref camera_hdr_realtime_mode, the range returned by this
 *          function defines the number of exposure values that can be
 *          programmed using @c camera_hdr_set_exposure_values().
 *
 *          In @ref camera_hdr_offline_mode, the range returned by this function
 *          defines the number of images that can be added as inputs to the HDR
 *          session using @c camera_hdr_add_image_to_session().
 *
 * @param hdr The HDR session handle obtained from a call to @c
 *            camera_hdr_create().
 * @param min A pointer to the returned minimum number of images required.
 * @param max A pointer to the returned maximum number of images supported.
 *
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_hdr_get_supported_image_count(camera_hdr_t hdr,
                                     uint32_t* min,
                                     uint32_t* max);


/**
 * @brief Get the list of configured exposure value offsets
 *
 * @details This function retrieves the exposure value (EV) offsets at which the
 *          input images will be captured from the camera.
 *
 *          Ensure that the @c offsets argument points to an array which has at
 *          least @c numasked elements allocated.
 *          To determine an appropriate size for this array, you can invoke this
 *          function in @e presizing mode by setting the @c numasked argument to
 *          0 or the @c offsets argument to @c NULL. When the function is
 *          invoked in this @e presizing mode, the maximum array size required
 *          is returned in the @c numreturned argument. You can then allocate an
 *          array of the appropriate size and invoke the function again with @c
 *          numasked argument set to the value returned previously in the @c
 *          numreturned argument.
 *
 *          This function can only be used in @ref camera_hdr_realtime_mode.
 *
 * @param hdr The HDR session handle obtained from a call to @c
 *            camera_hdr_create().
 * @param numasked The requested number of EV offsets to return in
 *                 in the @c offsets array. You can specify a value of 0 to
 *                 determine the number of EV offsets that can be returned.
 * @param numreturned A pointer to an integer that is updated with the
 *                    number of EV offsets in the @c offsets array.
 * @param offsets A pointer to a @c double array. The array is updated
 *                with the list of EV offsets currently configured.
 *                Ensure that you allocate an array with the same number of
 *                elements as the @c numasked argument.
 *
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_hdr_get_exposure_values(camera_hdr_t hdr,
                               uint32_t numasked,
                               uint32_t* numreturned,
                               double* offsets);


/**
 * @brief Set the exposure value offsets used for HDR capture
 *
 * @details This function sets the exposure value (EV) offsets at which the
 *          input images will be captured. The EV offsets must fall within the
 *          range reported by @c camera_hdr_get_supported_exposure_values().
 *
 *          This function can only be used in @ref camera_hdr_realtime_mode.
 *
 * @param hdr The HDR session handle obtained from a call to @c
 *            camera_hdr_create().
 * @param offsets The list of EV offsets to set.
 * @param num The number of EV offsets in the @c offsets array.
 *
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_hdr_set_exposure_values(camera_hdr_t hdr,
                               const double* offsets,
                               uint32_t num);


/**
 * @brief Retrieve the range of supported exposure value (EV) offsets
 *
 * @details Use this function to determine the list of valid EV offsets
 *          available for HDR capture. The returned list describes either
 *          a range or a discrete set of values.
 *
 *          In @ref camera_hdr_realtime mode, the range returned corresponds
 *          to the EV offset limits of the bound camera unit.
 *          These limits apply to the EV offsets configured using @c
 *          camera_hdr_set_exposure_values().
 *
 *          In @ref camera_hdr_offline_mode, the range returned corresponds
 *          to the limits of the HDR rendering engine. These limits apply to
 *          the EV offset passed to the @c camera_hdr_add_image_to_session()
 *          function.
 *
 *          Ensure that the @c offsets argument points to an array
 *          which has at least @c numasked elements allocated. To
 *          determine an appropriate size for this array, you can invoke this
 *          function in @e presizing mode by setting the @c numasked argument
 *          to 0 or the @c offsets argument to @c NULL. When the
 *          function is invoked in @e presizing mode, the maximum array size
 *          that is required is returned in the @c numsupported argument. You
 *          can then allocate an array of the appropriate size and invoke the
 *          function again with @c numasked argument set to the value returned
 *          previously in the @c numsupported argument.
 *
 * @param hdr The HDR session handle obtained from a call to @c
 *            camera_hdr_create().
 * @param numasked The requested number of EV offsets to return in
 *                 the @c offsets array. You can specify a value of 0 to
 *                 determine the number of supported EV offsets.
 * @param numsupported A pointer to an integer that is updated with the
 *                     number of supported EV offsets.
 * @param offsets A pointer to a @c double array. The array is updated
 *                with the range of EV offsets supported. Ensure that
 *                you allocate an array with the same number of elements as the
 *                @c numasked argument.  If the @c maxmin argument returns true,
 *                then the first value returned in the @c offsets array is the
 *                maximum supported EV offset, and the second value returned is
 *                the minimum supported EV offset.
 * @param maxmin A pointer to a @c boolean value which is set to @c true
 *               if the returned @c offsets should be interpreted as a maximum
 *               and a minimum value, or set to @c false if the returned @c
 *               offsets describe the discrete EV offsets that are supported.
 *
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_hdr_get_supported_exposure_values(camera_hdr_t hdr,
                                         unsigned numasked,
                                         unsigned *numsupported,
                                         double *offsets,
                                         bool *maxmin);


/**
 * @brief Add an input image to an HDR session
 *
 * @details Adds an input image to the HDR session prior to rendering. This
 *          function must be called multiple times to add successive images. Use
 *          @c camera_hdr_get_supported_image_count() to determine the number
 *          of input images required to render an HDR image. Use the @c
 *          camera_hdr_render() function to render an output HDR image from
 *          these input images. Each input image must be paired with a
 *          corresponding EV offset so that the rendering algorithm
 *          understands the exposure relation between the input images.
 *          The images provided must be of the same format and resolution.
 *
 *          This function can only be used in @ref camera_hdr_offline_mode.
 *
 * @param hdr The HDR session handle obtained from a call to @c
 *            camera_hdr_create().
 * @param image A pointer to an image buffer to add to the HDR session.
 *              See @c camera_api.h for a description of the @c camera_buffer_t
 *              structure.
 * @param offset The EV offset for the image supplied in @c image. Use @c
 *               camera_hdr_get_supported_exposure_values() to determine the
 *               valid range for this argument.
 *
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_hdr_add_image_to_session(camera_hdr_t hdr,
                                camera_buffer_t* image,
                                double offset);


/**
 * @brief Bind a camera to an HDR session handle
 *
 * @details Associate a camera for use as an input source to an HDR session.
 *          The camera must be configured for exposure bracketing capture prior
 *          to calling this function.
 *          See @c camera_api.h for more information.
 *
 *          Calling this function configures the HDR session for @ref
 *          camera_hdr_realtime_mode.
 *
 * @param hdr The HDR session handle obtained from a call to @c
 *            camera_hdr_create().
 * @param camera_handle The handle for the camera to use as an input source.
 *                      Call the @c camera_open() function from camera_api.h
 *                      to obtain a camera handle.
 *
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_hdr_bind_camera(camera_hdr_t hdr,
                       camera_handle_t camera_handle);


/**
 * @brief Close an HDR session
 *
 * @details This function releases any memory associated with the session and
 *          blocks until all outstanding HDR operations are complete. @b Do
 *          @b not call this function from the context of an HDR callback
 *          function, otherwise a deadlock scenario can occur.
 *
 * @param hdr The HDR session handle obtained from a call to @c
 *            camera_hdr_create(). This handle is no longer valid after this
 *            function returns.
 */
void
camera_hdr_destroy(camera_hdr_t hdr);


/**
 * @brief Takes an HDR photo using the camera
 *
 * @details The camera used for HDR capture must be bound to the HDR session
 *          using @c camera_hdr_bind_camera().
 *          The user-provided callback functions are invoked to deliver the
 *          image data to your application. There can be only one HDR capture
 *          active at any time per HDR session.
 *
 *          This function can only be used in @ref camera_hdr_realtime_mode.
 *
 *          See @c camera_api.h for more information regarding the operation
 *          of callback functions.
 *
 * @b Note: The Camera Features library @b does @b not automatically play audible
 *       shutter sounds when a picture is taken or a video is recorded.  Camera
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
 * @param hdr The HDR session handle obtained from a call to @c
 *            camera_hdr_create().
 *
 * @param shutter_callback A function pointer to a function with the following
 *                         signature:
 *                         @c void @c function_name( @c camera_handle_t,
 *                                                   @c void*).
 *                         The function is a callback that gets
 *                         invoked when the input image capture completes and
 *                         the HDR processing begins. Typically, the
 *                         callback function plays a shutter sound. You can
 *                         use @c NULL if no function needs to be called.
 *
 * @param raw_callback Use @c NULL. Reserved for future use.
 *
 * @param postview_callback A function pointer to a function with the
 *                          following signature:
 *                          @c void @c function_name( @c camera_handle_t,
 *                                                    @c camera_buffer_t*,
 *                                                    @c void*).
 *                          The function is a callback that gets invoked when
 *                          the postview (review) image data is available.
 *                          This callback is used to provide a postview-sized
 *                          copy of the HDR photo. Typically, the postview-sized
 *                          photo is used to provide visual feedback by the UI
 *                          before the final image is available. You can use @c
 *                          NULL if no function needs to be called.
 *
 * @param image_callback   A function pointer to a function with the following
 *                         signature:
 *                         @c void @c function_name( @c camera_handle_t,
 *                                                   @c camera_buffer_t*,
 *                                                   @c void*).
 *                         The function that is invoked when the final
 *                         full-resolution HDR image is available. You can
 *                         use @c NULL if no function needs to be called.
 *
 * @param image_callback_unprocessed   A function pointer to a function with
 *                        the following signature:
 *                        @c void @c function_name( @c camera_handle_t,
 *                                                  @c camera_buffer_t*,
 *                                                  @c void*).
 *                        The function that is invoked when the normal exposure
 *                        image (no EV offset) is available. Typically,
 *                        the unprocessed image may be used to provide a
 *                        "before and after" comparison of the non-HDR and HDR
 *                        images.
 *                        Use @c NULL if no function needs to be called.
 *
 * @param raw_callback_unprocessed   Use @c NULL. Reserved for future use.
 *
 * @param arg The argument passed to all callback functions.
 *            See @c camera_api.h for more information about callbacks.
 *
 * @param wait A boolean value that indicates whether the function blocks or
 *             not. If set to @c true, this function is blocking and
 *             returns after all specified callbacks have returned. If set to
 *             @c false, this function call is non-blocking and returns before
 *             all specified callbacks have returned.
 *
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */

camera_error_t
camera_hdr_take_photo(camera_hdr_t hdr,
                      void (*shutter_callback)(camera_handle_t, void*),
                      void (*raw_callback)(camera_handle_t,
                                           camera_buffer_t*,
                                           void*),
                      void (*postview_callback)(camera_handle_t,
                                                camera_buffer_t*,
                                                void*),
                      void (*image_callback)(camera_handle_t,
                                             camera_buffer_t*,
                                             void*),
                      void (*image_callback_unprocessed)(camera_handle_t,
                                                         camera_buffer_t*,
                                                         void*),
                      void (*raw_callback_unprocessed)(camera_handle_t,
                                                       camera_buffer_t*,
                                                       void*),
                      void *arg,
                      bool wait);


/**
 * @brief Render an HDR photo in offline mode
 *
 * @details Render an HDR photo using the supplied images and HDR session
 *          configuration settings. You can call this function multiple times
 *          with different @c rendertype arguments to generate different sized
 *          output images.
 *          This function is blocking. It is the caller's responsibility to
 *          release the returned photo buffer using @c camera_hdr_free_buffer().
 *
 *          This function can only be used in @ref camera_hdr_offline_mode.
 *
 * @b Note: This function should not be called from within the context of an
 *          executing camera callback function due to the fact that it may block
 *          the caller for a substantial amount of time while rendering
 *          completes. Doing so can lead to dropped frames in your callback
 *          functions.
 *          See @c camera_api.h for more information on using callback
 *          functions.
 *
 * @param hdr The HDR session handle obtained from a call to @c
 *            camera_hdr_create().
 * @param image The returned pointer to the rendered HDR image buffer.
 *              Use @c camera_hdr_free_buffer() to free the buffer when
 *              finished.
 * @param rendertype The rendering type that is defined by @c
 *                   ::camera_hdr_rendertype_t.
 *
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_hdr_render(camera_hdr_t hdr,
                  camera_buffer_t** image,
                  camera_hdr_rendertype_t rendertype);


/**
 * @brief Frees an HDR render buffer
 *
 * @details Frees an HDR image buffer that was previously allocated by the
 *          HDR module. Image buffers returned by @c camera_hdr_render() must
 *          be freed using this function. Image buffers returned by @c
 *          camera_hdr_take_photo() do not need to be explicitly freed.
 *
 * @param image The image buffer to be freed.
 */
void
camera_hdr_free_buffer(camera_buffer_t* image);

#ifdef __cplusplus
}
#endif

#endif// ifndef __CAMERA_HDR_H__
