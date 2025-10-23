/*
 *
 * Copyright (c) Research In Motion Limited 2012-2013. All rights reserved.
 */

/**
 * @file   geomonitor.h
 *
 * @brief  A library for the geomonitor service
 *
 * The geomonitor service API provide functions to create virtual perimeters
 * (regions) for real-world geographic areas.
 * Perimeters are monitored by the geomonitor service and applications receive
 * online (via geomonitor events) or offline (via invocation framework)
 * notifications when the device enters or exits the observed perimeters.
 *
 * A region is defined by its name (which must be unique in the scope of the
 * application), and location.
 *
 * A geomonitoring event consists of a region, event type, and the location
 * where the event occurred.
 *
 * To use the geomonitor service API functions, the application must
 * have the @c access_location_services capability. To grant an application
 * the @c access_location_services capability, the BAR application descriptor
 * file (bar-descriptor.xml) in the application's project must contain the
 * line "<permission>access_location_services</permission>".
 *
 * The following sample code demonstrates how to use this library to create and
 * add a region for monitoring:
 *
 * @code
 *
 *  // Scenario #1 (Persistent region monitoring)
 *
 *  // 1. Create a new region, give it a name and set its location.
 *
 *  geomonitor_region_t region = NULL;
 *  geomonitor_create_region(&region, "Home");
 *  geomonitor_region_set_circle_shape(region, 45.342102,-75.770581, 200.0);
 *
 *  // 2. Set additional optional parameters.
 *
 *  // Set region monitoring mode to persistent so that the region is monitored
 *  // even when the application that added the region is not running.
 *  // Note! The default monitoring mode is transient, which requires you to
 *  // create and initialize at least one instance of geomonitor_service_t prior
 *  // to adding a region. Persistent regions do not require a
 *  // geomonitor_service_t to be initialized.
 *  geomonitor_region_set_monitoring_mode( region,
 *                          GEOMONITOR_MONITORING_MODE_PERSISTENT);
 *
 *  // Set notification invoke target. This notification is pushed to the Hub
 *  // where the user taps on it and an application is launched.
 *  // Note! Application has to be registered with the invocation framework
 *  // and to have "blackberry.sample.myapp" - as a valid invoke target.
 *  geomonitor_region_set_notification_invoke_target(region,
 *                                            "blackberry.sample.myapp",
 *                                            GEOMONITOR_NOTIFICATION_UIB);
 *
 *  // Set Hub notification message content.
 *  geomonitor_region_set_notification_message(region, "Message content");
 *
 *  // Set the expiration of the region. Convert the date/time of the
 *  // expiration to its UTC equivalent. For example, to set the expiration
 *  // of the region to November 7, 2012, at 16:34:45, use the UTC value
 *  // 1352306085.
 *  geomonitor_region_set_expiration(region, 1352306085);
 *
 *  // Remove the monitored region once device leaves the region.
 *  geomonitor_region_set_stop_monitoring_event(region,
 *                                              GEOMONITOR_EVENT_TYPE_EXIT);
 *
 *  // 3. Add the region and start monitoring.
 *
 *  geomonitor_add(region);
 *
 *  // Release the region.
 *  // Note! This will not remove the region from the list of monitored regions.
 *  geomonitor_destroy_region(&region);
 *
 *  // 4. Initialize the geomonitor service handle and wait for notifications.
 *
 *  // Declare and initialize service.
 *  geomonitor_service_t geomonitor = NULL;
 *  geomonitor_service_initialize(&geomonitor);
 *
 *  // Get service fd.
 *  int fd = 0;
 *  geomonitor_service_get_fd(geomonitor, &fd);
 *
 *  // Wait for the notification.
 *  fd_set fds;
 *  FD_ZERO( &fds );
 *  FD_SET( fd, &fds );
 *  while ( select( fd+1, &fds, NULL, NULL, NULL ) > 0)
 *  {
 *      if (FD_ISSET(fd, &fds)) {
 *          // Read and parse the notifications.
 *          geomonitor_service_event_t event = NULL;
 *          geomonitor_service_get_event(geomonitor, &event);
 *
 *          // Get region, event type, and location.
 *          geomonitor_event_type_t event_type = GEOMONITOR_EVENT_TYPE_NONE;
 *          geomonitor_service_event_get_type(event, &event_type);
 *          geomonitor_region_t event_region = NULL;
 *          geomonitor_service_event_get_region(event, &event_region );
 *          geomonitor_geolocation_t event_location = NULL;
 *          geomonitor_service_event_get_location(event, &event_location);
 *
 *          // Handle event here
 *          // ...
 *          // and release the geomonitor event
 *          geomonitor_service_destroy_event(&event);
 *      }
 *  }
 *  // 5. Shut down the geomonitor service handle and remove the region.
 *
 *  geomonitor_service_shutdown(&geomonitor);
 *  // The region must be explicitly removed when it no longer needs
 *  // to be monitored; otherwise it will be continuously monitored.
 *  geomonitor_remove("Home");
 *
 *
 *  // Scenario #2 (Transient region monitoring)
 *
 *  // 1. Initialize the geomonitor service handle and get fd.
 *
 *  // Declare and initialize service.
 *  geomonitor_service_t geomonitor = NULL;
 *  geomonitor_service_initialize(&geomonitor);
 *
 *  // Get service fd.
 *  int fd = 0;
 *  geomonitor_service_get_fd(geomonitor, &fd);
 *
 *  // 2. Create a new region, give it a name and set its location.
 *
 *  // Note! Default monitoring state is transient so there is no need to set
 *  // it explicitly.
 *  geomonitor_region_t region = NULL;
 *  geomonitor_create_region(&region, "Home");
 *  geomonitor_region_set_circle_shape(region, 45.342102,-75.770581, 200.0);
 *
 *  // 3. Add the region and start monitoring.
 *
 *  geomonitor_add(region);
 *
 *  // Release the region.
 *  // Note! This will not remove the region from the list of monitored regions.
 *  geomonitor_destroy_region(&region);
 *
 *  // 4. Wait for notifications, get an event and handle it.
 *
 *  // Wait for the notification.
 *  fd_set fds;
 *  FD_ZERO( &fds );
 *  FD_SET( fd, &fds );
 *  while ( select( fd+1, &fds, NULL, NULL, NULL ) > 0)
 *  {
 *      if (FD_ISSET(fd, &fds)) {
 *          // Read/parse the notifications, handle the event
 *          // and release it afterwards
 *          // ...
 *      }
 *  }
 *
 *  // 5. Shut down the geomonitor service handle and remove the region.
 *
 *  // Note! When the last geomonitor instance is shut down, all the regions in
 *  // the GEOMONITOR_MONITORING_MODE_TRANSIENT will be removed automatically.
 *  geomonitor_service_shutdown(&geomonitor);
 *
 * @endcode
 */

#ifndef GEOMONITOR_H_
#define GEOMONITOR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>
#include <stdbool.h>
#include <time.h>

/**
 * @typedef struct geomonitor_region_t
 *
 * @brief An opaque handle to a region instance
 */
typedef struct _geomonitor_region_t *geomonitor_region_t;

/**
 * @typedef region_names_list_t
 * @brief An opaque handle to a region names list instance
 *
 * The @c #region_names_list_t structure defines an opaque handle to a region
 * names list.
 */
typedef struct _region_names_list_t *region_names_list_t;

/**
 * @typedef geomonitor_geolocation_t;
 *
 * @brief An opaque handle to a geolocation instance
 *
 * This structure contains information about the geographic location, time, and
 * accuracy of its acquisition.
 */
typedef struct _geomonitor_geolocation_t *geomonitor_geolocation_t;

/**
 * @typedef struct geomonitor_service_t
 * @brief An opaque handle to a geomonitor service instance
 *
 * An opaque handle to the service handle.
 */
typedef struct _geomonitor_service_t *geomonitor_service_t;

/**
 * @typedef struct geomonitor_service_event_t
 * @brief Contains geomonitor event information, including event type,
 * geomonitor region, and location where an event occurred.
 *
 * An opaque handle to a geomonitor service event.
 */
typedef struct _geomonitor_service_event_t *geomonitor_service_event_t;

/**
 * @brief Geomonitor region shape types
 *
 * This enumeration defines the supported region shape types.
 *
 */
typedef enum {
	/**
	 * Region shape type is not set, this is a default value for region
	 */
    GEOMONITOR_SHAPE_TYPE_NONE = 0,
    /**
     * Region shape type is circle
     */
    GEOMONITOR_SHAPE_TYPE_CIRCLE = 1
} geomonitor_shape_type_t;


/**
 * @brief Geomonitor region monitoring modes
 *
 * This enumeration defines the supported region monitoring modes.
 *
 */
typedef enum {
    /**
     * Region will be monitored only while the originating application is
     * running and has at least one initialized geomonitor service handle.
     */
    GEOMONITOR_MONITORING_MODE_TRANSIENT = 0,
    /**
     * Region will be persisted and monitored until it is explicitly removed by
     * the originating application, or until the originating application is
     * uninstalled, or until the region expires.
     */
    GEOMONITOR_MONITORING_MODE_PERSISTENT = 1
} geomonitor_monitoring_mode_t;

/**
 * @brief Geomonitor event types
 *
 * This enumeration defines the geomonitor service event types.
 *
 */
typedef enum
{
	/**
	 * Event type is not specified.
	 */
    GEOMONITOR_EVENT_TYPE_NONE  = 0,
    /**
     * Location Services are disabled.
     */
    GEOMONITOR_EVENT_TYPE_OUT_OF_SERVICE = 1,
    /**
     * Device enters monitored region.
     */
    GEOMONITOR_EVENT_TYPE_ENTER = 2,
    /**
     * Device exits monitored region.
     */
    GEOMONITOR_EVENT_TYPE_EXIT  = 3
} geomonitor_event_type_t;

/**
 * @brief Offline notification types
 *
 * This enumeration defines the delivery methods for offline notifications.
 *
 */
typedef enum {
    /**
     * Offline notification type is not set.
     */
    GEOMONITOR_NOTIFICATION_NONE = 0,
    /**
     * Direct offline notification.
     * A geomonitor event is sent directly to the application, invoking the app
     * if it is not running.
     */
    GEOMONITOR_NOTIFICATION_DIRECT = 1,
    /**
     * BlackBerry Hub offline notifications.
     * The geomonitor event appears as a notification in the BlackBerry Hub. The
     * event is sent to the application when the app is launched.
     */
    GEOMONITOR_NOTIFICATION_UIB = 2
} geomonitor_notification_type_t;

/**
 * @brief Geomonitor error types
 *
 * This enumeration defines the errors that can be returned by geomonitor
 * functions.
 *
 */
typedef enum {
	/**
	 * Correct result for an operation.
	 */
    GEOMONITOR_OK = 0,

    /**
     * Invalid parameters were passed to the function.
     */
    GEOMONITOR_INVALID_IPARAM                     = 0x10,
    /**
     * A NULL-referenced handle was passed to the function, which expects a
     * valid handle initialized to NULL.
     */
    GEOMONITOR_INVALID_IPARAM_NULL_HANDLE         = 0x11,
    /**
     * An already initialized handle was passed to the function, which expects
     * a NULL-referenced handle.
     */
    GEOMONITOR_INVALID_IPARAM_INITIALIZED_HANDLE  = 0x12,
    /**
     * A NULL referenced parameter was passed to the function, which expects a
     * valid pointer to perform an operation.
     */
    GEOMONITOR_INVALID_IPARAM_NULL_VALUE          = 0x13,
    /**
     * A string type input parameter passed to the function is too long.
     */
    GEOMONITOR_INVALID_IPARAM_STRING_TOO_LONG     = 0x14,
    /**
     * A NULL referenced output parameter was passed to the function, which
     * expects a valid pointer.
     */
    GEOMONITOR_INVALID_OPARAM_NULL_REFERENCE      = 0x15,
    /**
     * An invalid index value (e.g., out of bounds) was passed to the function.
     */
    GEOMONITOR_INVALID_IPARAM_INDEX               = 0x16,
    /**
     * An invalid or unsupported shape type was passed to the function.
     */
    GEOMONITOR_INVALID_IPARAM_SHAPE               = 0x17,
    /**
     * One or more invalid geocordinates were passed to the function.
     */
    GEOMONITOR_INVALID_IPARAM_COORDS              = 0x18,
    /**
     * An invalid radius value was passed to the function. The radius must be
     * greater than 0.
     */
    GEOMONITOR_INVALID_IPARAM_RADIUS              = 0x19,
    /**
     * An invalid geomonitor event type was passed to the function.
     */
    GEOMONITOR_INVALID_IPARAM_EVENT_TYPE          = 0x1A,
    /**
     * An invalid expiration time was passed to the function.
     */
    GEOMONITOR_INVALID_IPARAM_EXPIRATION          = 0x1B,
    /**
     * Not enough memory to perform operation.
     */
    GEOMONITOR_MEMORY_ALLOCATION_ERROR            = 0x1C,
    /**
     * An invalid geomonitor monitoring mode was passed to the function.
     */
    GEOMONITOR_INVALID_IPARAM_MONITORING_MODE     = 0x1D,
    /**
     * Application name cannot be defined.
     */
    GEOMONITOR_INVALID_APPLICATION_NAME           = 0x20,
    /**
     * Internal geomonitor API error.
     */
    GEOMONITOR_INTERNAL_API_ERROR                 = 0x21,
    /**
     * Invalid geomonitor service reply.
     */
    GEOMONITOR_INVALID_SERVICE_REPLY              = 0x22,
    /**
     * Internal geomonitor service service error.
     */
    GEOMONITOR_INTERNAL_SERVICE_ERROR             = 0x23,
    /**
     * Geomonitor service is not available.
     */
    GEOMONITOR_ERROR_NO_SERVICE_CONNECTION        = 0x24,
    /**
     * Location services are disabled.
     */
    GEOMONITOR_LOCATION_SERVICES_DISABLED         = 0x25,
    /**
     * Current location is not available.
     */
    GEOMONITOR_CURRENT_LOCATION_NOT_AVAILABLE     = 0x26,
    /**
     * Calling code does not have permissions to access geomonitor service.
     */
    GEOMONITOR_ERROR_NO_PERMISSION                = 0x27,
    /**
     * Region processing error
     */
    GEOMONITOR_REGION_ERROR                       = 0x100,
    /**
     * Region with the given name was already added by the application.
     */
    GEOMONITOR_REGION_ALREADY_ADDED               = 0x101,
    /**
     * Region with the given name was not found.
     */
    GEOMONITOR_REGION_NOT_FOUND                   = 0x102,
    /**
     * Region shape type is not set or is different from the requested type.
     * This error is returned if @c geomonitor_region_get_shape_type() is called
     * for the region that has a shape other than circle.
     */
    GEOMONITOR_REGION_INVALID_SHAPE_TYPE		  = 0x103,
    /**
     * Empty name (0 length string) for the region is not allowed.
     */
    GEOMONITOR_REGION_EMPTY_NAME				  = 0x104,
    /**
     * Region cannot be added in the transient monitoring mode since the calling
     * application does not have an initialized geomonitor service handle.
     */
    GEOMONITOR_ERROR_NOTIFICATIONS_RECEIVER_NOT_ADDED = 0x105,
    /**
     * Notification processing error.
     */
    GEOMONITOR_NOTIFICATIONS_ERROR                 = 0x200,
    /**
     * Client already requested notification via the given geomonitor service
     * handle.
     */
    GEOMONITOR_NOTIFICATIONS_ALREADY_REQUESTED     = 0x201,
    /**
     * Client has not requested any notification via the given geomonitor
     * service handle.
     */
    GEOMONITOR_NOTIFICATIONS_NOT_REQUESTED         = 0x202,
    /**
     * An application that requested the notification is closed or the
     * geomonitor service handle is closed.
     */
    GEOMONITOR_NOTIFICATIONS_RECEIVER_NOT_FOUND    = 0x203,
    /**
     * Offline notification invoke target is not valid or is used to invoke a
     * different application.
     */
    GEOMONITOR_INVALID_OFFLINE_NOTIFICATION_TARGET = 0x204

} geomonitor_error_t;

/**
 * @brief Return the printable error string from the supplied error code
 *
 * @param[in] error A valid error code
 *
 * @return A printable error string. If @c error is not valid, an "Unknown" type
 *         string is returned.
 */
const char *geomonitor_strerror(geomonitor_error_t error);


/**
 * @brief Create and initialize a geomonitor region instance
 *
 * This region is not monitored until it is added to the list of monitored
 * regions by calling @c geomonitor_add().
 *
 * @c region must be initialized to NULL before being passed to this function.
 * You must call @c geomonitor_destroy_region() to properly release @c region.
 *
 * @param[out] region  The created region.
 * @param[in]  name    A name for the region. This name should be unique and
 *                     its length cannot exceed 200 characters.
 *
 * @return @c #GEOMONITOR_OK upon success, an error from @c #geomonitor_error_t
 *         otherwise.
 */
geomonitor_error_t geomonitor_create_region(geomonitor_region_t *region,
        const char *name);

/**
 * @brief Set the monitored region to be a circle
 *
 * This function creates a circle with a radius of @c radius meters, with a
 * centre at a specific geographical location. If the specified radius is less
 * than the minimum or more than the maximum supported radius, then the circle
 * is monitored using the minimum or maximum supported value correspondingly.
 *
 * @param[in] region  A geomonitor region handle.
 * @param[in] lat     The latitude of the center of the region. This is a value
 *                    (in degrees) in the range [-90.0, 90.0].
 * @param[in] lon     The longitude of the center of the region. This is a value
 *                    (in degrees) in the range [-180, 180.0].
 * @param[in] radius  The radius of the region (in meters).
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c #geomonitor_error_t
 *         otherwise.
 */
geomonitor_error_t geomonitor_region_set_circle_shape(geomonitor_region_t region,
        double lat, double lon, double radius);

/**
 * @brief Set an expiration time for the monitored region
 *
 * Once a region expires, it is removed from the list of monitored regions. By
 * default, regions are set to never expire.
 *
 * @param[in] region      A handle to the geomonitor region whose expiration
 *                        time is being set.
 * @param[in] expiration  This is the UTC time after which the region expires.
 *                        Pass 0 to set the region to have no expiry.
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c #geomonitor_error_t
 *         otherwise.
 */
geomonitor_error_t geomonitor_region_set_expiration(geomonitor_region_t region,
        time_t expiration);

/**
 * @brief Set a notification invoke target for the region
 *
 * An application can set an notification invoke target to receive
 * geomonitor events even when the application is not running.
 *
 * When a geomonitor event occurs, the geomonitor event type and monitored
 * region name are sent to the application via the Invocation Framework. However,
 * an application must have a valid invoke target-key to handle invocation
 * framework events.
 *
 * The application is launched if it is not running, and the event type and
 * region name are passed to it.
 *
 * Events can be sent to the application directly (only if the application
 * provides an invoke key for launching its headless version) or they can be
 * pushed to the BlackBerry Hub as notifications with actionable items.
 *
 * By default these parameters are set to NULL and to
 * @c GEOMONITOR_NOTIFICATION_NONE. Both parameters must either be set to valid
 * values or to the default values. Setting only one parameter to a valid value
 * will result in an error.
 *
 * @param[in] region             A handle to the geomonitor region.
 * @param[in] invocation_target  The application invocation target key. This is
 *                               set in the application's BAR manifest file and
 *                               is used by the Invocation Framework to launch
 *                               an app. The length of the key cannot exceed 50
 *                               characters. Ownership of this parameter is not
 *                               transferred.
 * @param[in] notification_type  The method used to send the event to the
 *                               application; either directly or via the Hub.
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c
 *         #geomonitor_error_t otherwise.
 */
geomonitor_error_t geomonitor_region_set_notification_invoke_target(geomonitor_region_t region,
        const char *invocation_target,
        geomonitor_notification_type_t notification_type);

/**
 * @brief Set notification message text
 *
 * An application can set the BlackBerry Hub notification message. This message
 * will be displayed in the Hub as notification content. If the notification
 * invoke target is not set, or is set to be directly invoked, then the
 * notification message will not be used.
 *
 * @param[in] notification_message  A customized notification message content
 *                                  to be displayed in the Hub. The length of
 *                                  this message cannot exceed 100 characters.
 *                                  This parameter can be initialized to NULL
 *                                  when passed to this function to set empty
 *                                  notification content. Ownership of this
 *                                  parameter is not transferred.
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c
 *         #geomonitor_error_t otherwise.
 */
geomonitor_error_t geomonitor_region_set_notification_message(geomonitor_region_t region,
        const char *notification_message);

/**
 * @brief Specify a type of geomonitor event that, upon occurring, stops region
 *        monitoring and triggers the region to be removed from the list of
 *        monitored regions.
 *
 * @param[in] region                 A handle to the geomonitor region to be
 *                                   removed when the specified event occurs.
 * @param[in] stop_monitoring_event  The type of event that stops region
 *                                   monitoring and triggers its removal.
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c #geomonitor_error_t
 *         otherwise.
 */
geomonitor_error_t geomonitor_region_set_stop_monitoring_event(geomonitor_region_t region,
        geomonitor_event_type_t stop_monitoring_event);

/**
 * @brief Set the region monitoring mode
 *
 * A region in @c #GEOMONITOR_MONITORING_MODE_TRANSIENT mode is only monitored
 * while the application keeps at least one initialized geomonitor service
 * handle. If an application closes all the geomonitor service handles,
 * then the region will be removed. A region in
 * @c #GEOMONITOR_MONITORING_MODE_PERSISTENT mode will always be monitored until
 * the region is explicitly removed by the originating application, or until
 * the originating application is uninstalled, or until the region expires.
 *
 * An application must have at least one open initialized geomonitor service
 * handle to create a region in @c #GEOMONITOR_MONITORING_MODE_TRANSIENT mode.
 *
 * @param[in] region          A handle to the geomonitor region.
 * @param[in] monitoring_mode The monitoring mode of the region.
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c #geomonitor_error_t
 *         otherwise.
 */
geomonitor_error_t geomonitor_region_set_monitoring_mode(geomonitor_region_t region,
        geomonitor_monitoring_mode_t monitoring_mode);

/**
 * @brief Return the name of the region
 *
 * Ownership is not transferred to the output parameter, so the caller should
 * not release it.
 *
 * @param[in]  region A handle to the geomonitor region.
 * @param[out] name   The name of the region.
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c #geomonitor_error_t
 *         otherwise.
 */
geomonitor_error_t geomonitor_region_get_name(geomonitor_region_t region,
        char **name);

/**
 * @brief Return the shape of the region
 *
 * @param[in]  region      A handle to the geomonitor region.
 * @param[out] shape_type  The shape of the region.
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c #geomonitor_error_t
 *         otherwise.
 */
geomonitor_error_t geomonitor_region_get_shape_type(geomonitor_region_t region,
        geomonitor_shape_type_t *shape_type);

/**
 * @brief Return region parameters
 *
 * This function returns the region's parameters (i.e., latitude, longitude, and
 * radius) provided that the region's shape is a circle. If the region is any
 * other shape, then @c #GEOMONITOR_REGION_INVALID_SHAPE_TYPE is returned.
 *
 * @param[in] region  A handle to the geomonitor region.
 * @param[out] lat    The latitude of the center of the region. This is a value
 *                    (in degrees) in the range [-90.0, 90.0].
 * @param[out] lon    The longitude of the center of the region. This is a value
 *                    (in degrees) in the range [-180, 180.0].
 * @param[out] radius The radius of the region (in meters).
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c #geomonitor_error_t
 *         otherwise.
 */
geomonitor_error_t geomonitor_region_get_circle_shape(geomonitor_region_t region,
        double *lat, double *lon, double *radius);
/**
 * @brief Return the expiration time of a region
 *
 * The expiration time is the UTC time after which the region expires. Once a
 * region expires, it is removed from the monitored regions list.
 *
 * @param[in]  region      A handle to the geomonitor region.
 * @param[out] expiration  This is the UTC time after which the region expires.
 *                         A value of 0 means that the region does not expire.
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c #geomonitor_error_t
 *         otherwise.
 */
geomonitor_error_t geomonitor_region_get_expiration(geomonitor_region_t region,
        time_t *expiration);

/**
 * @brief Return the region's notification invocation target and notification
 * type
 *
 * Ownership is not transferred to the output parameters.
 *
 * @param[in]  region               A handle to the geomonitor region.
 * @param[out] target               The region's notification invoke target.
 * @param[out] notification_type    The region's notification type.
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c #geomonitor_error_t
 *         otherwise.
 */
geomonitor_error_t geomonitor_region_get_notification_invoke_target(geomonitor_region_t region,
        const char **invocation_target,
        geomonitor_notification_type_t *notification_type);

/**
 * @brief Return the region's Hub notification message
 *
 * Ownership is not transferred to the output parameters.
 *
 * @param[out] notification_content The notification message content to display
 *                                  in the BlackBerry Hub.
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c #geomonitor_error_t
 *         otherwise.
 */
geomonitor_error_t geomonitor_region_get_notification_message(geomonitor_region_t region,
        const char **notification_message);

/**
 * @brief  Retrieve the type of geomonitor event that stops region monitoring
 *         and triggers the removal of the region from the list of monitored
 *         regions.
 *
 * @param[in] region                 A handle to the geomonitor region to be
 *                                   removed when the specified event occurs.
 * @param[in] stop_monitoring_event  The type of event that stops region
 *                                   monitoring and triggers its removal.
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c #geomonitor_error_t
 *         otherwise.
 */
geomonitor_error_t geomonitor_region_get_stop_monitoring_event(geomonitor_region_t region,
        geomonitor_event_type_t *stop_monitoring_event);

/**
 * @brief Set the monitoring mode of the region.
 *
 * @param[in]  region           A handle to the geomonitor region.
 * @param[out] monitoring_mode  The monitoring mode of the region.
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c #geomonitor_error_t
 *         otherwise.
 */
geomonitor_error_t geomonitor_region_get_monitoring_mode(geomonitor_region_t region,
        geomonitor_monitoring_mode_t *monitoring_mode);

/**
 * @brief Release the instance of the region handle and set its value to NULL
 *
 * This function must be called to free the memory used by the @c
 * #geomonitor_region_t.
 *
 * @param[out] region The @c #geomonitor_region_t to be released.
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c #geomonitor_error_t
 *         otherwise.
 */
geomonitor_error_t geomonitor_destroy_region(geomonitor_region_t *region);

/**
 * @brief Return the number of elements in the region names list
 *
 * A list of monitored regions can be acquired by calling one of the geomonitor
 * search functions.
 *
 * @param[in] region_names_list  The list of monitored regions.
 *
 * @return The number of elements in the region names list (i.e., the length of
 *         the list).
 */
size_t geomonitor_region_names_list_length(region_names_list_t region_names_list);

/**
 * @brief Return the name of the region from the specified index of the
 *        monitored regions list
 *
 * @param[in] region_names_list  The list of monitored regions.
 * @param[in] index              The index of the region to return the name of.
 *
 * @return The name of the region from position @c index of the list. NULL is
 *         returned on error (e.g., @c index is out of bounds or @c
 *         region_names_list is NULL).
 */
const char *geomonitor_region_names_list_get(region_names_list_t region_names_list,
        size_t index);

/**
 * @brief Release a region names list
 *
 * @param[out] region_names_list  The list to be released.
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c #geomonitor_error_t
 *         otherwise.
  */
geomonitor_error_t geomonitor_region_names_list_destroy(region_names_list_t *region_names_list);

/**
 * @brief Return the latitude of the geographic location
 *
 * @param[in]  geolocation A handle to a geolocation.
 * @param[out] latitude    The latitude of the center of the geographic
 *                         location. This is a value (in degrees) in the range
 *                         [-90.0, 90.0].
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c #geomonitor_error_t
 *         otherwise.
 */
geomonitor_error_t geomonitor_geolocation_get_latitude(geomonitor_geolocation_t geolocation,
        double *latitude);

/**
 * @brief Return the longitude of the geographic location
 *
 * @param[in]  geolocation  A handle to a geolocation.
 * @param[out]  longitude   The longitude of the center of the geographic
 *                          location. This is a value (in degrees) in the range
 *                          [-180, 180.0].
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c #geomonitor_error_t
 *         otherwise.
 */
geomonitor_error_t geomonitor_geolocation_get_longitude(geomonitor_geolocation_t geolocation,
        double *longitude);

/**
 * @brief Return the accuracy of the location calculation
 *
 * @param[in]  geolocation  A handle to a geolocation.
 * @param[out] accuracy     The accuracy (in meters) of the location
 *                          calculation.
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c #geomonitor_error_t
 *         otherwise.
 */
geomonitor_error_t geomonitor_geolocation_get_accuracy(geomonitor_geolocation_t geolocation,
        double *accuracy);

/**
 * @brief Return the location acquisition time
 *
 * @param[in]  geolocation  A handle to a geolocation.
 * @param[out] timestamp    The UTC time of the location acquisition in milliseconds.
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c #geomonitor_error_t
 *         otherwise.
 */
geomonitor_error_t geomonitor_geolocation_get_timestamp(geomonitor_geolocation_t geolocation,
        uint64_t *timestamp);

/**
 * @brief Return whether the location is valid
 *
 * @param[in]  geolocation  A handle to a geolocation.
 * @param[out] is_valid     True if the location is valid, false otherwise.
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c #geomonitor_error_t
 *         otherwise.
 */
geomonitor_error_t geomonitor_geolocation_is_valid(geomonitor_geolocation_t geolocation,
        bool *is_valid);

/**
 * @brief Add a region to the list of monitored regions
 *
 * The region is stored and monitored until:
 *  - it is explicitly removed by the originate application,
 *  - the originating application is uninstalled,
 *  - the region expires, or
 *  - the originating application is running and has at least one initialized
 *     geomonitor service handle (in case region monitoring mode is set to
 *     @c #GEOMONITOR_MONITORING_MODE_TRANSIENT).
 *
 * The region is monitored from the time it is added to the list.
 *
 * When you add a region to the list of monitored regions, this function makes a
 * service request and blocks until the service responds.
 *
 * @param[in] region  The region to add to the list of monitored regions.
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c #geomonitor_error_t
 *         otherwise.
 */
geomonitor_error_t geomonitor_add(geomonitor_region_t region);

/**
 * @brief Find the region with the given name in the monitored regions list
 *
 * If the region is found, a copy of it is returned via the @c region parameter.
 * The caller is responsible for releasing the region.
 *
 * This function makes a service request that blocks until the service responds.
 *
 * @param [in]  region_name  The unique region name to search for.
 * @param [out] region       If @c region_name is found, this is a @c
 *                           #geomonitor_region_t containing a copy of the
 *                           region.
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c #geomonitor_error_t
 *         otherwise.
 */
geomonitor_error_t geomonitor_find(const char *region_name, geomonitor_region_t *region);

/**
 * @brief Search for all the regions (added by the application)
 *
 * The list of region names is not sorted and not capped so this function
 * has to be able to allocate enough memory to fit all the regions names.
 *
 * This function makes a service request that blocks until the service responds.
 *
 * @param[out] region_names_list  The list of region names found. This parameter
 *                                must be initialized to NULL when passed to
 *                                this function. The calling code takes
 *                                ownership of the list and must release it
 *                                using @c
 *                                geomonitor_region_names_list_destroy().
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c #geomonitor_error_t
 *         otherwise.
 */
geomonitor_error_t geomonitor_find_all_regions(region_names_list_t *region_names_list);

/**
 * @brief Search for regions (added by the application) that are within the
 *        specified radius area around the current location (if available)
 *
 * The list of region names is sorted by proximity to the current location. The
 * search area is bounded by the given radius. The number of the regions found
 * is capped and regions located furthest from the current location are not
 * returned.
 *
 * If the current location is unavailable, this function returns @c
 * GEOMONITOR_CURRENT_LOCATION_NOT_AVAILABLE.
 *
 * This function makes a service request that blocks until the service responds.
 *
 * @param[in]  radius             The radius (in meters) of the search area.
 * @param[out] region_names_list  The list of region names found. This parameter
 *                                must be initialized to NULL when passed to
 *                                this function. The calling code takes
 *                                ownership of the list and must release it
 *                                using @c
 *                                geomonitor_region_names_list_destroy().
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c #geomonitor_error_t
 *         otherwise.
 */
geomonitor_error_t geomonitor_search_nearby_regions(double radius,
        region_names_list_t *region_names_list);

/**
 * @brief Search for regions (added by the application) located within the area
 * defined by the latitude, longitude, and radius values.
 *
 * The list of region names is sorted by proximity to the current location. The
 * search area is bounded by the given radius. The number of the regions found
 * is capped and regions located furthest from the current location are not
 * returned.
 *
 * This function makes a service request that blocks until the service responds.
 *
 * @param[in] lat     The latitude of the center of the search area. This is a
 *                    value (in degrees) in the range [-90.0, 90.0].
 * @param[in] lon     The longitude of the center of the search area. This is a
 *                    value (in degrees) in the range [-180, 180.0].
 * @param[in]  radius            The radius (in meters) of the search area.
 * @param[out] region_names_list The list of region names found. This parameter
 *                               must be initialized to NULL when passed to this
 *                               function. The calling code takes ownership of
 *                               the list and must release it using @c
 *                               geomonitor_region_names_list_destroy().
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c #geomonitor_error_t
 *         otherwise.
 */
geomonitor_error_t geomonitor_search_regions_by_location(double lat, double lon,
        double radius, region_names_list_t *region_names_list);

/**
 * @brief Search for regions (added by the application) by a region name mask
 *
 * This function returns a list of regions whose names include the substring @c
 * name_mask. For example, if @c name_mask is "Toronto", then @c
 * region_names_list will contain regions whose name includes that string (e.g.,
 * Toronto-Lakeshore, Toronto-Beaches, Toronto-North, etc.).
 *
 * The number of regions returned is capped to a maximum number.
 *
 * This function makes a service request that blocks until the service responds.
 *
 * @param[in]  name_mask          The mask used to search the regions by name.
 * @param[out] region_names_list  The list of region names found. This parameter
 *                                must be initialized to NULL when passed to
 *                                this function. The calling code takes
 *                                ownership of the list and must release it
 *                                using @c
 *                                geomonitor_region_names_list_destroy().
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c #geomonitor_error_t
 *         otherwise.
 */
geomonitor_error_t geomonitor_search_regions_by_name(const char *name_mask,
        region_names_list_t *region_names_list);

/**
 * @brief Stop monitoring the region and remove it from the list of monitored
 *        regions
 *
 * When you remove a region, this function makes a service request and blocks
 * until the service responds.
 *
 * @param[in] region_name  The name of the region to be removed.
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c #geomonitor_error_t
 *         otherwise.
 */
geomonitor_error_t geomonitor_remove(const char *region_name);

/**
 * @brief Stop monitoring all regions added by the application and remove them
 *        from the list of monitored regions
 *
 * When you remove the regions, this function makes a service request and blocks
 * until the service responds.
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c #geomonitor_error_t
 *         otherwise.
 */
geomonitor_error_t geomonitor_remove_all(void);

/**
 * @brief Create and initialize a geomonitor service handle and open a
 *        service connection
 *
 * The handle created and initialized by this function represents a service
 * connection that you can use to receive geomonitor events.
 *
 * The handle passed to the function must be initialized to NULL. The handle
 * returned by the function has to be released by calling @c
 * geomonitor_service_shutdown().
 *
 * When you initialize the geomonitor service handle, this function makes a
 * service request and blocks until the service responds.
 *
 * @param[out] geomonitor  The @c #geomonitor_service_t handle to be created and
 *                         initialized by this function. This parameter must be
 *                         initialized to NULL when passed to this function.
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c #geomonitor_error_t
 *         otherwise.
 */
geomonitor_error_t geomonitor_service_initialize(geomonitor_service_t *geomonitor);

/**
 * @brief Close and release the geomonitor service handle
 *
 * @param[out] geomonitor  The @c #geomonitor_service_t handle to be closed and
 *                         released. The function sets the value of @c
 *                         geomonitor to NULL.
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c #geomonitor_error_t
 *         otherwise.
 */
geomonitor_error_t geomonitor_service_shutdown(geomonitor_service_t *geomonitor);

/**
 * @brief Read an event from the geomonitor service
 *
 * The calling code assumes ownership of the event.
 *
 * @param[in]  geomonitor  A handle to the geomonitor service.
 * @param[out] event       The event from the geomonitor service. This parameter
 *                         must be initialized to NULL when passed to this
 *                         function.
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c #geomonitor_error_t
 *         otherwise.
 */
geomonitor_error_t geomonitor_service_get_event(geomonitor_service_t geomonitor,
        geomonitor_service_event_t *event);

/**
 * @brief Release a geomonitor event handle
 *
 * @param[out] event  The geomonitor event handle to be released. This function
 *                    sets the value of @c event to NULL.
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c #geomonitor_error_t
 *         otherwise.
 */
geomonitor_error_t geomonitor_service_destroy_event(geomonitor_service_event_t *event);

/**
 * @brief Return a file descriptor for the geomonitor service
 *
 * Ownership of @c service_fd is not transferred to the caller.
 *
 * @param[in]  geomonitor  A handle to the geomonitor service.
 * @param[out] service_fd  A file descriptor to the geomonitor service.
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c #geomonitor_error_t
 *         otherwise.
 */
geomonitor_error_t geomonitor_service_get_fd(geomonitor_service_t geomonitor,
        int *service_fd);

/**
 * @brief Return the type of the event
 *
 * Ownership of @c event_type is not transferred to the caller.
 *
 * @param[in]  event       A handle to the geomonitor service.
 * @param[out] event_type  The geomonitor event type of @c event.
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c #geomonitor_error_t
 *         otherwise.
 */
geomonitor_error_t geomonitor_service_event_get_type(geomonitor_service_event_t event,
        geomonitor_event_type_t *event_type);

/**
 * @brief Returns the geomonitor region where an event occurred
 *
 * Ownership of @c region is not transferred to the caller.
 *
 * @param[in]  event   A geomonitor event.
 * @param[out] region  The region where @c event occurred. This parameter must
 *                     be initialized to NULL.
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c #geomonitor_error_t
 *         otherwise.
 */
geomonitor_error_t geomonitor_service_event_get_region(geomonitor_service_event_t event,
        geomonitor_region_t *region);

/**
 * @brief Return the location where the geomonitor event occurred
 *
 * Ownership of @c region is not transferred to the caller.
 *
 * @param[in]  event     A geomonitor event.
 * @param[out] location  The location of the event. This parameter must be
 *                       initialized to NULL.
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c #geomonitor_error_t
 *         otherwise.
 */
geomonitor_error_t geomonitor_service_event_get_location(geomonitor_service_event_t event,
        geomonitor_geolocation_t *location);

/**
 * @brief Start listening for geomonitor notifications
 *
 * The caller assumes ownership of @c event and must release it by calling @c
 * geomonitor_service_destroy_event().
 *
 * This function blocks the calling thread until a geomonitor event occurs.
 *
 * @param[out] event  A pointer to the geomonitor event. This parameter must be
 *                    initialized to NULL.
 *
 * @return @c #GEOMONITOR_OK if successful, an error from @c #geomonitor_error_t
 *         otherwise. @c #GEOMONITOR_LOCATION_SERVICES_DISABLED is returned if
 *         location services are turned off.
 */
geomonitor_error_t geomonitor_service_wait_event(geomonitor_service_event_t *event);

#ifdef __cplusplus
}
#endif

#endif /* GEOMONITOR_H_ */
