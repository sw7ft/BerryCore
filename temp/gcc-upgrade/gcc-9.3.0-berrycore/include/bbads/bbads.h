
/*
 * Research In Motion Limited. Copyright (C) 2013.
 * Research In Motion Limited. All rights reserved.
 *
 * Version 1.0
 */

/**
 * BBAds public header (bbads.h)
 */

/**
 * @file bbads.h
 *
 * @brief Functions and types that can be used to create and customize banners
 * for displaying advertisements in BlackBerry 10 Native SDK applications.
 *
 * @since BlackBerry 10.0.0
 */

/**
* @mainpage  Advertising Service Library 
*
* Use the APIs for the Advertising Service to display ads in your applications.
*
* The Advertising Service APIs enable you to create and customize ad banners 
* in your app, which you can populate with ads sourced from various ad 
* networks. To specify which ad networks supply your app with ads, use the web 
* portal for the Advertising Service. In addition to creating and displaying 
* ad banners, the APIs allow you to manage properties such as the size and 
* position of ad banners, and the refresh rate for ads.
*/


#ifndef _BBADS_BBADS_H_INCLUDED
#define _BBADS_BBADS_H_INCLUDED

#include <screen/screen.h>
#include <sys/platform.h>

__BEGIN_DECLS


 /**
 * Error codes for the Advertising Service
 *
 * @c BBADS_EINTERNAL indicates that an internal error occurred, which 
 * prevented the requested operation from being fulfilled. While it's 
 * generally safe to attempt retrying the operation, this error could indicate
 * the presence of a more fundamental problem. @c BBADS_EINTERNAL is the only 
 * error code that will not be returned if you provide invalid parameters in a 
 * function call.
 */
 
 typedef enum
{
    /**
     * Success.
     *
     * @since BlackBerry 10.0.0
     */
    BBADS_EOK = 0,

    /**
     * Invalid banner provided.
     *
     * @since BlackBerry 10.0.0
     */
    BBADS_EBANNER = 1,

    /**
     * Invalid size.
     *
     * @since BlackBerry 10.0.0
     */
    BBADS_ESIZE = 2,

    /**
     * Invalid parameter provided.
     *
     * @since BlackBerry 10.0.0
     */
    BBADS_EINVAL = 3,

    /**
     * Invalid state to perform requested operation.
     *
     * @since BlackBerry 10.0.0
     */
    BBADS_ESTATE = 4,

    /**
     * Insufficient memory to fulfill requested operation.
     *
     * @since BlackBerry 10.0.0
     */
    BBADS_ENOMEM = 5,

    /**
     * The requested operation was not fulfilled due to an internal library 
	 * error.
    * @since BlackBerry 10.0.0     
    */
    BBADS_EINTERNAL = 127
} bbads_error_t;

/**
 * A structure that represents a BlackBerry Platform Services (BPS) event.
 */
struct bps_event_t;

/**
 * A structure that represents the banner.
 */
struct bbads_banner_t;

/**
 * @brief A structure that represents the banner.
 *
 * This structure represents the banner to be created or modified.
 *
 * @since BlackBerry 10.0.0 
 */

typedef struct bbads_banner_t bbads_banner_t;

/**
 * API version information.
 *
 * @since BlackBerry 10.0.0
 */
#define BBADS_VERSION_MAJOR    1

/**
 * API version information.
 *
 * @since BlackBerry 10.0.0
 */
#define BBADS_VERSION_MINOR    0

/**
 * @brief Get the library's major version number.
 *
 * This number represents the major version number of the API exposed by the 
 * library at runtime.
 *
 *
 * @return An unsigned int of the library's major version number.
 *
 * @since BlackBerry 10.0.0
 */
unsigned int bbads_get_version_major(void);

/**
 * @brief Get the library's minor version number.
 *
 * This number represents the minor version number of the API exposed by the 
 * library at runtime.
 *
 *
 * @return An unsigned int of the library's minor version number.
 *
 * @since BlackBerry 10.0.0
 */
unsigned int bbads_get_version_minor(void);

/**
 * @brief Get the library's revision number.
 *
 * This function retrieves the revision number of the Advertising Service 
 * library.
 *
 * @return An unsigned int of the library's revision number.
 *
 * @since BlackBerry 10.0.0
 */
unsigned int bbads_get_version_revision(void);

/**
 * @brief Set the library logging verbosity.
 *
 * The log will be printed to @c stderr and all log messages will be prefixed 
 * with "bbads:".
 *
 * The default verbosity is 0. At level 0, the library does not print log 
 * messages.
 *
 *
 * @param verbosity The verbosity of the log output. The following values are valid:
 * - 0: No logging. This is the default value.
 * - 1: Critical. Only critical errors are logged.
 * - 2: Informational. More verbose logging takes place.
 *
 * @since BlackBerry 10.0.0
 */
void bbads_set_log_verbosity(int verbosity);

/**
 * @brief Create a new banner.
 *
 * Creating a new banner will initialize it with the default parameters.
 *
 * Once the banner has been created, its parameters can be modified by calling
 * other functions.
 *
 *
 * @param banner This points to the location where the created 
 * @c ::bbads_banner_t* will be set.
 * @param window The top-level @c screen_window_t of the application.
 * @param window_group_name The group name of the top-level @c screen_window_t
 * of the application.
 * @param zone_id The zone ID identifies your application to the Advertising 
 * Service, and allows you to manage ad streams for your app using the web 
 * portal for the Advertising Service. The trial zone ID is 117145. This 
 * property is required.
 *
 * @return
 *  - @c BBADS_EOK if a banner was created successfully and the value in 
 *    @c banner was set.
 *  - @c BBADS_ENOMEM if memory for the banner could not be allocated.
 *
 * @since BlackBerry 10.0.0
 */
bbads_error_t bbads_banner_create(
    bbads_banner_t** banner,
    screen_window_t window,
    const char* window_group_name,
    unsigned int zone_id
);

/**
 * @brief Modify the banner's size.
 *
 * This function modifies the banner's size. Modifying the banner's size can 
 * only be performed before the banner has been loaded.
 *
 *
 * @param banner The @c bbads_banner_t* as created in the call to 
 * @c bbads_banner_create().
 * @param width The requested width of the banner. Must be greater than 0.
 * @param height The requested height of the banner. Must be greater than 0.
 *
 * @return
 *  - @c BBADS_EOK on success.
 *  - @c BBADS_EBANNER if the @c bbads_banner_t* provided is invalid.
 *  - @c BBADS_ESIZE if the size provided is invalid. 
 *  - @c BBADS_ESTATE if the banner has already been loaded.
 *
 * @since BlackBerry 10.0.0
 */
bbads_error_t bbads_banner_set_size(bbads_banner_t* banner, unsigned int width, unsigned int height);

/**
 * @brief Modify the banner's position on the screen.
 *
 * This function modifies the position of the banner on the screen.
 *
 *
 * @param banner The @c bbads_banner_t* as created in the call to 
 * @c bbads_banner_create().
 * @param x The x position on the screen of the top-left corner of the banner.
 * @param y The y position on the screen of the top-left corner of the banner.
 *
 * @return
 *  - @c BBADS_EOK on success.
 *  - @c BBADS_EBANNER if the @c bbads_banner_t* provided is invalid.
 *
 * @since BlackBerry 10.0.0
 */
bbads_error_t bbads_banner_set_position(bbads_banner_t* banner, unsigned int x, unsigned int y);

/**
 * @brief Modify the banner's refresh rate. 
 * 
 * This function modifies the banner's refresh rate. Modifying the banner's 
 * refresh rate can only be performed before the banner has been loaded.
 *
 *
 * @param banner The @c bbads_banner_t* as created in the call to 
 * @c bbads_banner_create().
 * @param seconds The time (in seconds) between each ad refresh. The minimum 
 * refresh rate is 60 seconds. The default refresh rate is also 60 seconds.
 *
 * @return
 *  - @c BBADS_EOK on success.
 *  - @c BBADS_EBANNER if the @c bbads_banner_t* provided is invalid.
 *  - @c BBADS_EINVAL if the refresh rate provided is invalid.
 *  - @c BBADS_ESTATE if the banner has already been loaded.
 *
 * @since BlackBerry 10.0.0
 */
bbads_error_t bbads_banner_set_refresh_rate(bbads_banner_t* banner, unsigned int seconds);

/**
 * @brief Modify the width of the banner's border.
 *
 * This is the width of the banner's border that appears when the user 
 * clicks/touches the banner. 
 *
 * Modifying the width of the banner's border can only be performed before the
 * banner has been loaded. See @c bbads_banner_is_loaded().
 *
 * The border width contributes to the banner's width and height. You can use 
 * these calculations to determine the final width and height of the banner. 
 *  - full banner width = (set banner width) + 2*(border width)
 *  - full banner height = (set banner height) + 2*(border width)
 * 
 * See @c bbads_banner_set_size() for more information on setting the banner's
 * size.
 *
 *
 * @param banner The @c bbads_banner_t* as created in the call to 
 * @c bbads_banner_create().
 * @param width The width of the border when the ad is clicked. This must be 
 * an integer value between 0 and 10, inclusive.
 *
 * @return
 *  - @c BBADS_EOK on success.
 *  - @c BBADS_EBANNER if the @c bbads_banner_t* provided is invalid.
 *  - @c BBADS_EINVAL if the width provided is invalid.
 *  - @c BBADS_ESTATE if the banner has already been loaded.
 *
 * @since BlackBerry 10.0.0
 */
bbads_error_t bbads_banner_set_border_width(bbads_banner_t* banner, unsigned int width);

/**
 * @brief Set a placeholder image URL for the ad banner.
 *
 * Changing the placeholder image URL can only be performed before the banner
 * has been loaded. See @c bbads_banner_is_loaded().
 *
 * The most recent call to this function replaces the previously set 
 * placeholder URL. 
 *
 * Setting @c placeholder_url to 0 removes any previously set placeholder URL.
 *
 * Note: If a placeholder image URL is not set or if the URL is not a local 
 * URL (using the "file:///" protocol), the ad banner will be made completely 
 * transparent on a network error event (@c BBADS_EVENT_NETWORK_ERROR). This 
 * will also result in an asynchronous event: @c BBADS_EVENT_INVISIBLE.
 *
 *
 * @param banner The @c bbads_banner_t* as created in the call to 
 * @c bbads_banner_create().
 * @param placeholder_url A null-terminated string containing the URL where 
 * the placeholder image is located. The placeholder_url must be a local 
 * URL and use the "file:///" protocol, for example, 
 * "file:///accounts/1000/shared/photos/placeholder_920x60.png". If set to 0,
 * the placeholder URL will not be set for the banner.
 *
 * @return
 *  - @c BBADS_EOK on success.
 *  - @c BBADS_EBANNER if the @c bbads_banner_t* provided is invalid.
 *  - @c BBADS_ESTATE if the banner has already been loaded.
 *  - @c BBADS_ENOMEM if there isn't enough memory to copy the placeholder URL.
 *
 * @since BlackBerry 10.0.0
 */
bbads_error_t bbads_banner_set_placeholder_url(bbads_banner_t* banner, const char* placeholder_url);

/**
 * @brief Load the ad banner and begins requesting ads.
 *
 * Use this function to start loading ads. Ads are supplied by the ad 
 * networks that you specify in the Advertising Service web portal.
 *
 *
 * @param banner The @c bbads_banner_t* as created in the call to 
 * @c bbads_banner_create().
 *
 * @return
 *  - @c BBADS_EOK on success.
 *  - @c BBADS_EBANNER if the @c bbads_banner_t* provided is invalid.
 *  - @c BBADS_ESTATE if the banner has already been loaded.
 *
 * @since BlackBerry 10.0.0
 */
bbads_error_t bbads_banner_load(bbads_banner_t* banner);

/**
 * @brief Display the ad banner on the screen.
 *
 * Use this function to display the ad banner on the screen. The 
 * banner will not contain ads until you call @c bbads_banner_load(). You must
 * also set @c bbads_banner_set_window_visible() to true before you can 
 * display the ad banner.
 *
 *
 * @param banner The @c bbads_banner_t* as created in the call to 
 * @c bbads_banner_create().
 * @param screen_context The @c screen_context_t* of the window handle of the
 * calling application.
 * @param event The @c bps_event_t* of the calling application that represents
 * the creation of the ads window.
 *
 * @return
 *  - @c BBADS_EOK on success.
 *  - @c BBADS_EBANNER if the @c bbads_banner_t* or @c screen_context_t* or 
 *    @c bps_event_t* provided is invalid.
 *  - @c BBADS_ESTATE if the banner has already been displayed.
 *
 * @since BlackBerry 10.0.0
 */
bbads_error_t bbads_banner_display(bbads_banner_t* banner, screen_context_t screen_context, bps_event_t* event);

/**
 * @brief Check whether a particular ad banner has been loaded.
 *
 * Use this function to check if a particular banner has been loaded.
 * 
 *
 * @param banner The @c bbads_banner_t* as created in the call to 
 * @c bbads_banner_create().
 * @param loaded A pointer to an int that will be set with the state 
 * information.
 * If @c loaded is a null pointer, then the state information is not provided.
 * If @c loaded is not a null pointer, then the integer it points to is set as
 * follows:
 *  - 0, if the banner has not yet been loaded.
 *  - 1, if the banner has been loaded.
 *  - -1, if there was an error. Check the function's return value for the 
 *    error code.
 *
 * @return
 *  - @c BBADS_EOK on success.
 *  - @c BBADS_EBANNER if the @c bbads_banner_t* provided is invalid.
 *
 * @since BlackBerry 10.0.0
 */
bbads_error_t bbads_banner_is_loaded(bbads_banner_t* banner, int* loaded);

/**
 * @brief Check whether a banner is visible.
 *
 * If the application requests receiving events for this banner (see 
 * @c bbads_banner_request_events()), it's also notified of the state 
 * change when the banner becomes transparent. See the @c BBADS_EVENT_INVISIBLE
 * event for more information.
 *
 * This function is only usable after @c bbads_banner_load() has been called, 
 * otherwise @c BBADS_ESTATE is returned.
 *
 *
 * @param banner The @c bbads_banner_t* as created in the call to 
 * @c bbads_banner_create().
 * @param visible A pointer to an int that will be set with the state 
 * information.
 * If @c visible is set to 0, then the state information will not be provided.
 * If @c visible is not 0, then the integer it points to is set as follows:
 *  - 0, if the banner has been made transparent (not visible).
 *  - 1, if the banner is currently visible.
 *  - -1, if there was an error. Check the function's return value for the 
 *    error code.
 *
 * @return
 *  - @c BBADS_EOK on success.
 *  - @c BBADS_EBANNER if the @c bbads_banner_t* provided is invalid.
 *  - @c BBADS_ESTATE if the banner has not yet been loaded.
 *
 * @since BlackBerry 10.0.0
 */
bbads_error_t bbads_banner_is_visible(bbads_banner_t* banner, int* visible);

/**
 * @brief Destroy an existing banner.
 *
 * Use this function to destroy an existing banner.
 *
 *
 * @param banner The @c bbads_banner_t* as created in the call to 
 * @c bbads_banner_create().
 *
 * @return
 *  - @c BBADS_EOK on success.
 *  - @c BBADS_EBANNER if the @c bbads_banner_t* provided is invalid.
 *
 * @since BlackBerry 10.0.0
 */
bbads_error_t bbads_banner_destroy(bbads_banner_t* banner);

/**
 * @brief Register a banner for asynchronous event delivery through the 
 * BlackBerry Platform Services (BPS).
 *
 * Use this function to activate event delivery, through BPS, for a banner.
 *
 *
 * @param banner The @c bbads_banner_t* as created in the call to 
 * @c bbads_banner_create().
 *
 * @return
 *  - @c BBADS_EOK on success.
 *  - @c BBADS_EBANNER if the @c bbads_banner_t* provided is invalid.
 *  - @c BBADS_ESTATE if the banner has already been registered for 
 *    asynchronous event delivery. You need to deregister the banner before 
 *    you can re-register it for asynchronous event delivery. See 
 *    @c bbads_banner_stop_events() for more information.
 *
 * @since BlackBerry 10.0.0
 */
bbads_error_t bbads_banner_request_events(bbads_banner_t* banner);

/**
 * @brief Deregister a banner for asynchronous event delivery.
 *
 * Turns off asynchronous event delivery for the banner.  
 * See @c bbads_banner_request_events() for information on how to register a 
 * banner for event delivery.
 *
 *
 * @param banner The @c bbads_banner_t* as created in the call to 
 * @c bbads_banner_create().
 *
 * @return
 *  - @c BBADS_EOK on success.
 *  - @c BBADS_EBANNER if the @c bbads_banner_t* provided is invalid.
 *  - @c BBADS_ESTATE if there's no active registration for event delivery for
 *    this banner. To register a banner for asynchronous events, see 
 *    @c bbads_banner_request_events().
 *
 * @since BlackBerry 10.0.0
 */
bbads_error_t bbads_banner_stop_events(bbads_banner_t* banner);

/**
 * @brief Set the window visibility of the banner to true. 
 * 
 * This function is a toggle that sets the window visibility of the banner to 
 * true, and is always called from the calling application. The default value 
 * is false, so it must be set to true in order for ad banners to display.
 *
 * @param banner The @c bbads_banner_t* as created in the call to 
 * @c bbads_banner_create().
 *
 * @return
 *  - @c BBADS_EOK on success.
 *  - @c BBADS_EBANNER if the @c bbads_banner_t* provided is invalid.
 *  - @c BBADS_ESTATE if there's no active registration for event delivery for
 *    this banner. To register a banner for asynchronous events, see 
 *    @c bbads_banner_request_events().
 *
 * @since BlackBerry 10.0.0
 */
bbads_error_t bbads_banner_set_window_visible(bbads_banner_t* banner);

 /**
 * @internal Do not use. For internal use only.
 * @brief Set web view visibility of banner to true.
 *
 * Sets web view visibility of banner to true.
 *
 * @param banner The @c bbads_banner_t* as created in the call to 
 * @c bbads_banner_create().
 *
 * @return
 *  - @c BBADS_EOK on success.
 *  - @c BBADS_EBANNER if the @c bbads_banner_t* provided is invalid.
 *  - @c BBADS_ESTATE if there's no active registration for event delivery for
 *    this banner. To register a banner for asynchronous events, see 
 *    @c bbads_banner_request_events().
 */
bbads_error_t bbads_banner_set_webview_visible(bbads_banner_t* banner);

 __END_DECLS

#endif /* _BBADS_BBADS_H_INCLUDED */
