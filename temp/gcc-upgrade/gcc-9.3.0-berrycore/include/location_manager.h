#pragma once


/**
 * @file    location_manager.h
 * @brief   A library for accessing the Location Manager service
 *
 * @mainpage
 *
 * @tableofcontents
 *
 * @details The location_manager library provides a C API for requesting
 * location from the Location Manager service.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/select.h>

#define LM_MAX_NUM_SATELLITES       (64)

/**
 * @brief The lm_error_t codes provide information on the status of any
 * library call.
 *
 * This enumeration defines all the possible error codes that are supported
 * by this API.
 */
typedef enum {
    /**
     * The operation completed successfully with no error.
     */
    LM_ERR_NONE = 0,

    /**
     * The operation failed due to lack of memory.
     */
    LM_ERR_NO_MEMORY = 1,

    /**
     * The operation could not complete because one or more of the supplied
     * parameters were invalid.
     */
    LM_ERR_INVALID_PARAM = 2,

    /**
     * The operation could not complete because handle is already open.
     */
    LM_ERR_ALREADY_OPEN = 3,

    /**
     * The operation could not complete because the Location Manager service
     * could not be opened.
     */
    LM_ERR_OPEN = 4,

    /**
     * The operation could not complete because the supplied handle was
     * not open.
     */
    LM_ERR_NOT_OPEN = 5,

    /**
     * The operation could not complete because the supplied handle was
     * invalid.
     */
    LM_ERR_INVALID_HANDLE = 6,

    /**
     * The operation could not complete because the supplied request was
     * invalid.
     */
    LM_ERR_INVALID_REQUEST = 7,

    /**
     * The operation could not complete because the supplied reply was
     * invalid.
     */
    LM_ERR_INVALID_REPLY = 8,

    /**
     * The operation could not complete in the allowed amount of time and
     * has timed out.
     */
    LM_ERR_TIMEOUT = 9,

    /**
     * The operation could not complete due to some unknown system error.
     */
    LM_ERR_SYSTEM = 10
} lm_error_t;

/**
 * @brief The lm_reply_error_t codes provide information on the status of a
 * particular completed request.
 *
 * This enumeration defines all the possible reply error codes that are
 * supported by this API. Each request made to Location Manager can either
 * succeed or fail, even though the parameters of the request were all valid.
 *
 * Note that the codes have been split in two categories: fatal and non-fatal
 * (i.e. warning). Fatal errors mean to say that the location request that was
 * made simply cannot be serviced and has been rejected by Location Manager,
 * meaning you will never get a location reply due to this failed request.
 * Non-fatal errors, on the other hand, simply mean that there was some sort
 * of event which may impair the receipt of location updates. Updates may or
 * may not resume on their own and the behavior is documented for each of the
 * possible non-fatal error codes.
 */
typedef enum {
    /**
     * The request completed successfully and there was no error.
     */
    LM_REP_ERR_NONE = 0,

    /**
     * Location Manager is disabled and cannot currently process requests.
     */
    LM_REP_ERR_FATAL_DISABLED = 1,

    /**
     * The last known location request failed because Location Manager is not
     * aware of any last known locations.
     */
    LM_REP_ERR_FATAL_NO_LAST_KNOWN_POSITION = 2,

    /**
     * There are insufficient location providers for Location Manager to be
     * able to service the given request.
     */
    LM_REP_ERR_FATAL_INSUFFICIENT_PROVIDERS = 3,

    /**
     * The request specified was invalid. This most likely means that a bad
     * parameter was supplied as part of the request.
     */
    LM_REP_ERR_FATAL_INVALID_REQUEST = 4,

    /**
     * An unknown error has occurred.
     */
    LM_REP_ERR_FATAL_UNKNOWN = 5,

    /**
     * Your application or service does not have enough permissions to access
     * the Location Manager service.
     */
    LM_REP_ERR_FATAL_PERMISSION = 6,

    /**
     * A timeout has occurred while waiting for a location response. This
     * indicates that the response time of the location request has been
     * surpassed. Location Manager will continue to search for the current
     * location and an update will be sent when the location is known.
     */
    LM_REP_ERR_WARN_TIMEOUT = 0x10000,

    /**
     * Location Manager lost continuous updates of position, likely due to
     * bad or no signal. Location Manager will continue to search for a
     * position and an update will be sent when the location is once again
     * known.
     */
    LM_REP_ERR_WARN_LOST_TRACKING = 0x10001,

    /**
     * Location Manager has determined that the device is currently stationary
     * and in order to save power no further updates will be sent until the
     * device resumes movement and/or the client re-sends their request.
     */
    LM_REP_ERR_WARN_STATIONARY = 0x10002,

    /**
     * Location Manager has suspended the client's request. A resume request
     * needs to be sent before receiving further updates.
     */
    LM_REP_ERR_WARN_SUSPENDED = 0x10003
} lm_reply_error_code_t;


/**
 * @brief Describes the type of a request
 *
 * The enumeration details all the different types of requests that can be made
 * of Location Manager by clients, through this API.
 */
typedef enum {
    /**
     * Request location updates.
     * Will receive @c #LM_REP_TYPE_LOCATION or @c #LM_REP_TYPE_ERROR
     */
    LM_REQ_TYPE_LOCATION = 0,

    /**
     * Cancel location updates. Can receive @c #LM_REP_TYPE_ERROR
     */
    LM_REQ_TYPE_CANCEL = 1,

    /**
     * Request status updates. Can receive @c #LM_REP_TYPE_STATUS or
     * @c #LM_REP_TYPE_ERROR.
     */
    LM_REQ_TYPE_STATUS = 2,

    /**
     * Request a Location Manager reset. Can receive @c #LM_REP_TYPE_ERROR.
     */
    LM_REQ_TYPE_RESET = 3,

    /**
     * Resume a location request. This is sent in response to receiving the
     * @c #LM_REP_ERR_WARN_SUSPENDED as a reply error.
     */
    LM_REQ_TYPE_RESUME = 4,
} lm_request_type_t;

/**
 * @brief Describes the type of a reply
 *
 * The enumeration details all the different reply types that can be received
 * from Location Manager.
 */
typedef enum {
    /**
     * An error in reply
     */
    LM_REP_TYPE_ERROR = 0,

    /**
     * A location update
     */
    LM_REP_TYPE_LOCATION = 1,

    /**
     * A status update
     */
    LM_REP_TYPE_STATUS = 2,

    /**
     * Location status update (i.e. location on/off)
     */
    LM_REP_TYPE_LOCATION_STATUS = 3,
} lm_reply_type_t;

/**
 * @brief Specifies a location request flag.
 *
 * A location request can have a number of flags that can be set with the
 * @c lm_loc_req_set_flag API call.
 */
typedef enum {
    /**
     * A background request is allowed to run while the device is in standby.
     * Note that your application or service needs to have separate permissions
     * to run while the device is in standby.
     */
    LM_LOC_REQ_FLAG_BACKGROUND = 0,

    /**
     * A passive location request will not actively trigger the hardware for
     * location updates, but if that hardware is on due to other requests, the
     * client will receive passive location replies.
     */
    LM_LOC_REQ_FLAG_PASSIVE = 1,

    /**
     * A last known location request uses a caching mechanism within Location
     * Manager to return the last received location update that matches the
     * request.
     */
    LM_LOC_REQ_FLAG_LAST_KNOWN = 2,

    /**
     * Whether or not to report satellite information without a location, i.e.
     * while searching for a location.
     */
    LM_LOC_REQ_FLAG_REPORT_SAT = 3,

    /**
     * Whether or not to enable client to service flow control. Location
     * Manager will become aware of the status of a client with respect to
     * that client reading its own updates and keeping up with the replies
     * that Location Manager is sending. When a client seemingly has stopped
     * from consuming the replies, a @c #LM_REP_TYPE_ERROR with code @c
     * #LM_REP_ERR_WARN_SUSPENDED will be returned. @c #LM_REQ_TYPE_RESUME needs
     * to be sent for updates to resume.
     */
    LM_LOC_REQ_FLAG_FLOW_CONTROL = 4,

    /**
     * Whether or not to enable the stationary detection filter in Location
     * Manager. Low power sensors information will be used to determine that
     * a device is stationary. Location updates will stop when the device
     * enters the stationary state and the client will receive the @c
     * #LM_REP_ERR_WARN_STATIONARY error code. Updates will resume automatically
     * when the device resumes movement, or manually when the client re-sends
     * their request.
     */
    LM_LOC_REQ_FLAG_STATIONARY_DETECTION = 5,

    /**
     * Whether or not to use a last known location reply in place of the first
     * fix, while waiting on a fresh fix to be computed. This is meant to be
     * used with periodic location requests in an attempt to get a much faster
     * and less power expensive location update that might be acceptable to the
     * location client.
     */
    LM_LOC_REQ_FLAG_LAST_KNOWN_FIX_FIRST = 6,
} lm_loc_request_flag_t;

/**
 * @brief Identifies the type of a location provider
 *
 * Location Manager supports different types of underlying technology or
 * location providers, such as GNSS (including GPS and GLONASS), network
 * (including WiFi and cellular positioning) as well as a combined, best-effort
 * hybrid provider type.
 */
typedef enum {
    /**
     * Identifies a hybrid provider type that may blend GNSS and Network
     * location updates on a best effort basis.
     */
    LM_PROVIDER_TYPE_HYBRID = 0,

    /**
     * Identifies a satellite-based positioning method, such as GPS or GLONASS.
     */
    LM_PROVIDER_TYPE_GNSS = 1,

    /**
     * Identifies a network-based positioning method, such as WiFi or cellular.
     */
    LM_PROVIDER_TYPE_NETWORK = 2,
} lm_provider_type_t;

/**
 * @brief Identifies the type of a location update (fix).
 *
 * Certain location providers are capable of returning multiple fix types,
 * depending on configuration and the request that is made. This enumeration
 * describes all the different fix types that are supported by Location
 * Manager.
 */
typedef enum {
    /**
     * Best describes a fix type where it is left up to the configuration and
     * underlying location providers to determine which type of fix should be
     * acquired and returned. Best is understood to be the default fix type
     * when no other type is specified.
     */
    LM_FIX_TYPE_BEST = 0,

    /**
     * GPS MS-Based fix type. If you don't understand what that is, you don't
     * need to use it.
     */
    LM_FIX_TYPE_GPS_MS_BASED = 1,

    /**
     * GPS MS-Assisted fix type. If you don't understand what that is, you don't
     * need to use it.
     */
    LM_FIX_TYPE_GPS_MS_ASSISTED = 2,

    /**
     * GPS Autonomous fix, implying that the only allowed aiding type is
     * Extended Ephemeris / QCT GPS XTRA
     */
    LM_FIX_TYPE_GPS_AUTONOMOUS = 3,

    /**
     * WiFi fix type, implying that WiFi access points will be used to
     * calculate the user's position.
     */
    LM_FIX_TYPE_WIFI = 4,

    /**
     * Cellsite fix type, implying that cellular towers will be used to
     * calculate the user's position.
     */
    LM_FIX_TYPE_CELLSITE = 5,
} lm_fix_type_t;

/**
 * @brief Identifies the type of reset to be performed
 *
 * To be used with @c #LM_REQ_TYPE_RESET.
 */
typedef enum {
    /**
     * Reset cached time, almanac, ephemeris and position information
     */
    LM_RESET_TYPE_COLD = 0,

    /**
     * Reset all but cached time, almanac and position estimate
     */
    LM_RESET_TYPE_WARM = 1,

    /**
     * Reset all aiding from receiver, but used cached values
     */
    LM_RESET_TYPE_HOT = 2,

    /**
     * Reset GPS to a known factory state
     */
    LM_RESET_TYPE_FACTORY = 3,

    /**
     * Reset Extended Ephemeris / QCT XTRA data
     */
    LM_RESET_TYPE_EE_DATA = 4,

    /**
     * Reset almanac
     */
    LM_RESET_TYPE_ALMANAC = 5,

    /**
     * Reset ephemeris
     */
    LM_RESET_TYPE_EPHEMERIS = 6,

    /**
     * Reset time
     */
    LM_RESET_TYPE_TIME = 7,
} lm_reset_type_t;

/**
 * @brief Specifies satellite flags
 *
 * A location reply will have a number of satellites and each satellite can
 * have a number of the flags in the enumeration below set.
 */
typedef enum {
    /**
     * The satellite's ephemeris is known.
     */
    LM_SAT_FLAG_EPHEMERIS = 0,

    /**
     * The satellite is being tracked.
     */
    LM_SAT_FLAG_TRACKED = 1,

    /**
     * The satellite is being used to compute the current fix.
     */
    LM_SAT_FLAG_USED = 2,

    /**
     * The satellite's almanac is known.
     */
    LM_SAT_FLAG_ALMANAC = 3,
} lm_satellite_flag_t;

/**
 * @brief A handle to the Location Manager service
 *
 * This handle is provided when the Location Manager service is opened and is
 * a required parameter when calling any of the other library functions.
 */
typedef struct lm_handle_s  *lm_handle_t;

/**
 * @brief A handle to a Location Manager request
 *
 * This handle can be allocated and filled in using the appropriate functions
 * in the library. Any request made to Location Manager starts with a request.
 */
typedef struct lm_request_s *lm_request_t;

/**
 * @brief A handle to a Location Manager reply
 *
 * This handle is returned by the library and represents a reply from Location
 * Manager to one of the requests.
 */
typedef struct lm_reply_s   *lm_reply_t;


/**
 * @brief Open the Location Manager service
 *
 * Opens the Location Manager service and fills in the corresponding handle.
 * When the client no longer needs to use the handle, it should be closed with
 * @c lm_close().
 *
 * You can open a Location Manager handle and check for errors as follows:
 * @code
 * lm_handle_t h;
 * lm_error_t err;
 *
 * err = lm_open(&h);
 * if (LM_ERR_NONE != err) {
 *     fprintf(stderr, "lm_open() returned %d\n", err);
 *     return -1;
 * }
 *
 * // Use the handle... 
 *
 * err = lm_close(&h);
 * if (LM_ERR_NONE != err) {
 *     fprintf(stderr, "lm_close() returned %d\n", err);
 *     return -1;
 * }
 * @endcode
 * 
 * @param [out] handle A valid pointer to a @c #lm_handle_t
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_open (lm_handle_t *handle);

/**
 * @brief Close a handle to the Location Manager service
 *
 * Closes a handle to the Location Manager service and frees any associated
 * memory. See @c lm_open() for an usage example.
 * 
 * @param [in] handle A pointer to a valid @c #lm_handle_t
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_close (lm_handle_t *handle);

/**
 * @brief Get the number of file descriptors of a handle
 *
 * Gets the number of file descriptors associated with a particular
 * @c #lm_handle_t. To be used if you wish to integrate liblocation_manager
 * in your event model. See @c lm_get_fds() for an usage example.
 *
 * @param [in] handle A pointer to a valid @c #lm_handle_t
 * @param [out] num_fds A pointer ot a @c size_t to store the number of fd's
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_get_num_fds (lm_handle_t *handle, size_t *num_fds);

/**
 * @brief Fill an array with a handle's file descriptors
 *
 * Fills @c fds with all the file descriptors that are associated with a
 * @c #lm_handle_t. Up to @c fds_size file descriptors will be filled in
 * and the actual number of file descriptors will be returned in @c num_fds.
 *
 * Here is an example of how this library can be integrated in your event
 * model:
 * @code
 * lm_handle_t h;
 * lm_error_t err;
 * lm_reply_t reply;
 * size_t fds_size, num_fds;
 * int *fds;
 *
 * // open the handle
 *
 * err = lm_get_num_fds(&h, &fds_size);
 * if (LM_ERR_NONE != err) {
 *     fprintf(stderr, "lm_get_num_fds() returned %d\n", err);
 *     return -1;
 * }
 * 
 * fds = calloc(sizeof(int), fds_size);
 * if (NULL == fds) {
 *     fprintf(stderr, "not enough memory to allocate %d int's\n", fds_size);
 *     return -1;
 * }
 *
 * err = lm_get_fds(&h, fds, fds_size, &num_fds);
 * if (LM_ERR_NONE != err) {
 *     fprintf(stderr, "lm_get_fds() returned %d\n", err);
 *     free(fds);
 *     return -1;
 * }
 *
 * // Allocate a reply to be used for all responses from Location Manager
 * err = lm_rep_alloc(&reply);
 * if (LM_ERR_NONE != err) {
 *     fprintf(stderr, "lm_rep_alloc() returned %d\n", err);
 *     free(fds);
 *     return -1;
 * }
 *
 * for (;;) {
 *     size_t i;
 *     int st, maxfd = 0;
 *     fd_set fdset;
 *     FD_ZERO(&fdset);
 *
 *     for (i=0; i<num_fds; ++i) {
 *         FD_SET(fds[i], &fdset);
 *         maxfd = max(fds[i], max);
 *     }
 *
 *     // add your own fd's to fdset
 *
 *     st = select(maxfd+1, &fds, NULL, NULL, NULL);
 *     if (st == -1) {
 *         fprintf(stderr, "select() failed: %d - %s\n", errno, strerror(errno));
 *         free(fds);
 *         lm_rep_free(reply);
 *         return -1;
 *     }
 *
 *     for (i=0; i<num_fds; ++i) {
 *         if (FD_ISSET(fds[i], &fdset)) {
 *
 *             err = lm_get_reply(&lmh, &fdset, &reply);
 *             if (LM_ERR_NONE != err) {
 *                 fprintf(stderr, "lm_get_reply() returned %d\n", err);
 *                 free(fds);
 *                 lm_rep_free(reply);
 *                 return -1;
 *             }
 *
 *             // process reply
 *
 *             break;
 *         }
 *     }
 * }
 *
 * // Free the reply once we're done getting replies
 * err = lm_rep_free(&reply);
 * if (LM_ERR_NONE != err) {
 *     fprintf(stderr, "lm_rep_free() returned %d\n", err);
 *     free(fds);
 *     return -1;
 * }
 *
 * free(fds);
 *
 * @endcode
 *
 * @param [in]  handle   A pointer to a valid @c #lm_handle_t
 * @param [out] fds      An array of int's
 * @param [in]  fds_size The size of the @c fds array
 * @param [out] num_fds  The number of fd's that have been filled into @c fds
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_get_fds (lm_handle_t *handle, int *fds, size_t fds_size, size_t *num_fds);


/**
 * @brief Allocates a @c #lm_request_t and sets the type
 *
 * Allocates the required memory for @c request and fills in the
 * @c type of the request.
 *
 * @param [in]  request  A pointer to a valid @c #lm_request_t
 * @param [in]  type     The type of request you wish to allocate
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_req_alloc (lm_request_t *request, lm_request_type_t type);

/**
 * @brief Frees a @c #lm_request_t
 *
 * De-allocates any memory taken up by @c request.
 *
 * @param [in]  request  A valid pointer to a @c #lm_request_t
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_req_free (lm_request_t *request);

/**
 * @brief Sets a specific @c id in the @c request
 *
 * Each Location Manager request can have a specific @c id and any reply
 * will be tagged with it. In absence of one a default @c id will be
 * chosen.
 *
 * @param [in]   request  A valid pointer to a @c #lm_request_t
 * @param [in]   id       A valid C string to identify the request by
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_req_set_id (lm_request_t *request, const char *id);

/**
 * @brief Set the period of a location request
 *
 * Set the @c period of a @c request.
 *
 * @param [in]   request  A valid pointer to a @c #lm_request_t
 * @param [in]   period   The period of the request, in seconds
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_loc_req_set_period (lm_request_t *request, double period);

/**
 * @brief Set the accuracy of a location request
 *
 * Set the @c accuracy of a @c request.
 *
 * @param [in]   request  A valid pointer to a @c #lm_request_t
 * @param [in]   accuracy The accuracy of the request, in meters
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_loc_req_set_accuracy (lm_request_t *request, double accuracy);

/**
 * @brief Set the response time of a location request
 *
 * Set the @c response_time of a @c request.
 *
 * @param [in]   request  A valid pointer to a @c #lm_request_t
 * @param [in]   response_time The response time of the request, in seconds
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_loc_req_set_response_time (lm_request_t *request, int response_time);

/**
 * @brief Set a flag of a location request
 *
 * Set a flag of a @c request.
 *
 * @param [in]   request  A valid pointer to a @c #lm_request_t
 * @param [in]   flag     The flag that needs to be set
 * @param [in]   value    The value to set the flag to
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_loc_req_set_flag (lm_request_t *request, lm_loc_request_flag_t flag, bool value);

/**
 * @brief Set the provider type of a location request
 *
 * Set the @c provider_type of a @c request.
 *
 * @param [in]   request  A valid pointer to a @c #lm_request_t
 * @param [in]   provider_type The provider type to set in the request
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_loc_req_set_provider_type (lm_request_t *request, lm_provider_type_t provider_type);

/**
 * @brief Set the fix type of a location request
 *
 * Set the @c fix_type of a @c request.
 *
 * @param [in]   request  A valid pointer to a @c #lm_request_t
 * @param [in]   fix_type The fix type to set in the request
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_loc_req_set_fix_type (lm_request_t *request, lm_fix_type_t fix_type);

/**
 * @brief Set the application id of a location request
 *
 * Set the @c app_id of a @c request. If you don't know what this is,
 * then you most likely don't need to use it.
 *
 * @param [in]   request  A valid pointer to a @c #lm_request_t
 * @param [in]   app_id   The application id to set in the request
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_loc_req_set_app_id (lm_request_t *request, int app_id);

/**
 * @brief Set the application password of a location request
 *
 * Set the @c app_password of a @c request.
 *
 * @param [in]   request  A valid pointer to a @c #lm_request_t
 * @param [in]   app_password The application password to set in the request,
 *                            should be a valid C string. It will be copied by the library
 *                            and the user is free to do as they please with the
 *                            pointer that was passed in.
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_loc_req_set_app_password (lm_request_t *request, const char *app_password);

/**
 * @brief Set the PDE URL of a location request
 *
 * Set the @c pde_url of a @c request. If you don't know what this is,
 * then you most likely don't need to use it.
 *
 * @param [in]   request  A valid pointer to a @c #lm_request_t
 * @param [in]   pde_url  The PDE URL to set in the location request, should
 *                        be a valid C string. It will be copied by the library
 *                        and the user is free to do as they please with the
 *                        pointer that was passed in.
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_loc_req_set_pde_url (lm_request_t *request, const char *pde_url);

/**
 * @brief Set the SLP URL of a location request
 *
 * Set the @c slp_url of a @c request. If you don't know what this is,
 * then you most likely don't need to use it.
 *
 * @param [in]   request  A valid pointer to a @c #lm_request_t
 * @param [in]   slp_url  The SLP URL to set in the location request, should
 *                        be a valid C string. It will be copied by the library
 *                        and the user is free to do as they please with the
 *                        pointer that was passed in.
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_loc_req_set_slp_url (lm_request_t *request, const char *slp_url);

/**
 * @brief Set the type of a reset request
 *
 * Set the @c reset_type of a @c request.
 *
 * @param [in] request    A valid pointer to a @c #lm_request_t of type
 *                        @c #LM_REQ_TYPE_RESET
 * @param [in] reset_type The reset type
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_reset_req_set_type (lm_request_t *request, lm_reset_type_t reset_type);

/**
 * @brief Send a location request
 *
 * Send @c request to the Location Manager service through the @c handle.
 * Here is an usage example:
 * @code
 * lm_handle_t h;
 * lm_error_t err;
 * lm_request_t r;
 *
 * // open a handle, h
 *
 * // allocate the request
 * err = lm_req_alloc(&r, LM_REQ_TYPE_LOCATION);
 * if (LM_ERR_NONE != err) {
 *     fprintf(stderr, "lm_req_alloc() returned %d\n", err);
 *     return -1;
 * }
 *
 * // optionally set an id
 * err = lm_req_set_id(&r, "custom_id");
 * if (LM_ERR_NONE != err) {
 *     fprintf(stderr, "lm_req_set_id() returned %d\n", err);
 *     lm_req_free(&r);
 *     return -1;
 * }
 *
 * // send the request
 * err = lm_send_request(&h, &r);
 * if (LM_ERR_NONE != err) {
 *     fprintf(stderr, "lm_send_request() returned %d\n", err);
 *     lm_req_free(&r);
 *     return -1;
 * }
 *
 * // free request
 * err = lm_req_free(&r);
 * if (LM_ERR_NONE != err) {
 *     fprintf(stderr, "lm_req_free() returned %d\n", err);
 *     return -1;
 * }
 *
 * @endcode
 *
 * @param [in] handle  A pointer to a valid @c #lm_handle_t
 * @param [in] request A pointer to a valid @c #lm_request_t
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_send_request (lm_handle_t *handle, lm_request_t *request);


/**
 * @brief Allocates a @c #lm_reply_t
 *
 * Allocates the required memory for @c reply.
 *
 * @param [in]  reply  A valid pointer to a @c #lm_reply_t
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_rep_alloc (lm_reply_t *reply);

/**
 * @brief Free a reply
 *
 * Frees @c reply and any associated memory that has been allocated with
 * @c lm_rep_alloc()
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_rep_free (lm_reply_t *reply);

/**
 * @brief Read a reply from Location Manager in non-blocking mode
 *
 * Process the fd's that are set in @c fds and return a @c reply.
 * Note that this function will not block and will return an error if there
 * is no work to be done. This function is to be used when you wish to integrate
 * this library into your own event model.
 *
 * The @c reply will be allocated and filled in and must be freed by
 * the client using @c lm_rep_free(). See @c lm_get_fds() for an usage example.
 *
 * @param [in]  handle  A pointer to a valid @c #lm_handle_t
 * @param [in]  fds     A pointer to a valid @c fd_set
 * @param [out] reply   A pointer to a @c #lm_reply_t
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_get_reply (lm_handle_t *handle, fd_set *fds, lm_reply_t *reply);

/**
 * @brief Read a reply from Location Manager in blocking mode
 *
 * Wait for Location Manager to send a reply up to a maximum amount of time
 * specified with @c timeout. Allocates and fills in the @c reply. Following is
 * an usage example:
 * @code
 * lm_handle_t h;
 * lm_reply_t r;
 * lm_error_t err;
 *
 * // open handle, h and send a request
 *
 * // allocate a reply
 * err = lm_rep_alloc(&r);
 * if (LM_ERR_NONE != err) {
 *     fprintf(stderr, "lm_rep_alloc() returned %d\n", err);
 *     return -1;
 * }
 *
 * for (;;) {
 *    struct timeval tv = {10, 0}; // 10 second timeout
 *
 *    // wait for a reply for up to 10 seconds
 *    err = lm_wait_reply(&h, &r, &tv);
 *    if (LM_ERR_NONE != err) {
 *        fprintf(stderr, "lm_wait_reply() returned %d\n", err);
 *        lm_rep_free(&r);
 *        return -1;
 *    }
 *
 *    // process reply...
 *
 * }
 *
 * // free reply
 * lm_rep_free(&r);
 * @endcode
 *
 * @param [in]  handle  A pointer to a valid @c #lm_handle_t
 * @param [out] reply   A pointer to a @c #lm_reply_t
 * @param [in]  timeout A pointer to a valid @c struct @c timeval
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_wait_reply (lm_handle_t *handle, lm_reply_t *reply, struct timeval *timeout);

/**
 * @brief Print a reply
 *
 * Convenience function to print a @c reply
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t
 * @param [in]  pFile  A valid FILE *, such as @c stdout
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_rep_print (lm_reply_t *reply, FILE *pFile);

/**
 * @brief Get the type of a reply from Location Manager
 *
 * Return the type of @c reply in @c reply_type
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t
 * @param [out] reply_type A valid pointer to a @c #lm_reply_type_t
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_rep_get_type (lm_reply_t *reply, lm_reply_type_t *reply_type);


/**
 * @brief Get the id of a reply from Location Manager
 *
 * Return the id of @c reply in @c pId. Copy only up to
 * @c id_len bytes.
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t
 * @param [out] pId    A valid C string pointer
 * @param [in]  id_len The length of @c pId. No more than this many bytes
 *                     will be copied into @c pId
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_rep_get_id (lm_reply_t *reply, char *pId, size_t id_len);


/**
 * @brief Get the provider type of a location reply from Location Manager
 *
 * Return the provider type of @c reply into @c provider_type.
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t of type @c #LM_REP_TYPE_LOCATION
 * @param [out] provider_type A valid pointer to a @c #lm_provider_type_t
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_loc_rep_get_provider_type (lm_reply_t *reply, lm_provider_type_t *provider_type);

/**
 * @brief Get the fix type of a location reply from Location Manager
 *
 * Return the fix type of @c reply into @c fix_type.
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t of type @c #LM_REP_TYPE_LOCATION
 * @param [out] fix_type A valid pointer to a @c #lm_fix_type_t
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_loc_rep_get_fix_type (lm_reply_t *reply, lm_fix_type_t *fix_type);

/**
 * @brief Get the latitude of a location reply from Location Manager
 *
 * Return the latitude of @c reply into @c latitude. Range is [-90,90] degrees.
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t of type @c #LM_REP_TYPE_LOCATION
 * @param [out] latitude A valid pointer to a @c double
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_loc_rep_get_latitude  (lm_reply_t *reply, double *latitude);

/**
 * @brief Get the longitude of a location reply from Location Manager
 *
 * Return the longitude of @c reply into @c longitude. Range is [-180,180] degrees.
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t of type @c #LM_REP_TYPE_LOCATION
 * @param [out] longitude A valid pointer to a @c double
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_loc_rep_get_longitude (lm_reply_t *reply, double *longitude);

/**
 * @brief Get the accuracy of a location reply from Location Manager
 *
 * Return the accuracy (in meters) of @c reply into @c accuracy.
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t of type @c #LM_REP_TYPE_LOCATION
 * @param [out] accuracy A valid pointer to a @c double
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_loc_rep_get_accuracy (lm_reply_t *reply, double *accuracy);

/**
 * @brief Get the altitude of a location reply from Location Manager
 *
 * Return the altitude (in meters) of @c reply into @c altitude. Reference is Mean Sea Level.
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t of type @c #LM_REP_TYPE_LOCATION
 * @param [out] altitude A valid pointer to a @c double.
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_loc_rep_get_altitude (lm_reply_t *reply, double *altitude);

/**
 * @brief Get the altitude accuracy of a location reply from Location Manager
 *
 * Return the altitude accuracy (in meters) of @c reply into @c altitude_accuracy.
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t of type @c #LM_REP_TYPE_LOCATION
 * @param [out] altitude_accuracy A valid pointer to a @c double
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_loc_rep_get_altitude_accuracy (lm_reply_t *reply, double *altitude_accuracy);

/**
 * @brief Get the heading of a location reply from Location Manager
 *
 * Return the heading (in degrees from North) of @c reply into @c heading.
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t of type @c #LM_REP_TYPE_LOCATION
 * @param [out] heading A valid pointer to a @c double
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_loc_rep_get_heading (lm_reply_t *reply, double *heading);

/**
 * @brief Get the speed of a location reply from Location Manager
 *
 * Return the speed (in meters / second) of @c reply into @c speed.
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t of type @c #LM_REP_TYPE_LOCATION
 * @param [out] speed  A valid pointer to a @c double
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_loc_rep_get_speed (lm_reply_t *reply, double *speed);

/**
 * @brief Get the time-to-first-fix of a location reply from Location Manager
 *
 * Return the time to first fix (in seconds) of @c reply into @c ttff.
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t of type @c #LM_REP_TYPE_LOCATION
 * @param [out] ttff   A valid pointer to an @c int
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_loc_rep_get_ttff (lm_reply_t *reply, int *ttff);

/**
 * @brief Get the GPS Week of a location reply from Location Manager
 *
 * Return the GPS Week of @c reply into @c gps_week.
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t of type @c #LM_REP_TYPE_LOCATION
 * @param [out] gps_week A valid pointer to a @c uint16_t
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_loc_rep_get_gps_week (lm_reply_t *reply, uint16_t *gps_week);

/**
 * @brief Get the GPS Time of Week of a location reply from Location Manager
 *
 * Return the GPS Time of Week (TOW) of @c reply into @c gps_tow .
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t of type @c #LM_REP_TYPE_LOCATION
 * @param [out] gps_tow A valid pointer to a @c uint32_t
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_loc_rep_get_gps_tow (lm_reply_t *reply, uint32_t *gps_tow);

/**
 * @brief Get the UTC time of a location reply from Location Manager
 *
 * Return the UTC time of @c reply into @c utc. Specified in milliseconds since UTC epoch.
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t of type @c #LM_REP_TYPE_LOCATION
 * @param [out] utc    A valid pointer to a @c uint64_t
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_loc_rep_get_utc (lm_reply_t *reply, uint64_t *utc);

/**
 * @brief Get the HDOP of a location reply from Location Manager
 *
 * Return the HDOP of @c reply into @c hdop.
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t of type @c #LM_REP_TYPE_LOCATION
 * @param [out] hdop   A valid pointer to a @c double.
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_loc_rep_get_hdop (lm_reply_t *reply, double *hdop);

/**
 * @brief Get the VDOP of a location reply from Location Manager
 *
 * Return the VDOP of @c reply into @c vdop.
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t of type @c #LM_REP_TYPE_LOCATION
 * @param [out] vdop   A valid pointer to a @c double.
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_loc_rep_get_vdop (lm_reply_t *reply, double *vdop);

/**
 * @brief Get the PDOP of a location reply from Location Manager
 *
 * Return the PDOP of @c reply into @c pdop.
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t of type @c #LM_REP_TYPE_LOCATION
 * @param [out] pdop   A valid pointer to a @c double.
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_loc_rep_get_pdop (lm_reply_t *reply, double *pdop);

/**
 * @brief Get the propagated status of a location reply from Location Manager
 *
 * Return whether or not a location reply @c reply is propagated. Certain
 * location technologies can propagate a location reply for a certain amount of
 * time in case of temporary loss of signal.
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t of type @c #LM_REP_TYPE_LOCATION
 * @param [out] propagated A valid pointer to a @c bool
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_loc_rep_is_propagated (lm_reply_t *reply, bool *propagated);

/**
 * @brief Get the geoid height of a location reply from Location Manager
 *
 * Return the geoid height of @c reply into @c geoid_height. The geoid height is
 * location-dependent and is equivalent to the geoid undulation, which is defined
 * as the height of the geoid (MSL) above the earth reference ellipsoid (WGS84).
 * As a result, this value can be either negative or positive, depending on your
 * location. Specified in meters.
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t of type @c #LM_REP_TYPE_LOCATION
 * @param [out] geoid_height A valid pointer to a @c double
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_loc_rep_get_geoid_height (lm_reply_t *reply, double *geoid_height);

/**
 * @brief Get the elliptical accuracy of a location reply from Location Manager
 *
 * Return the elliptical accuracy of @c reply into @c semi_major,
 * @c semi_minor and @c rotation.
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t of type @c #LM_REP_TYPE_LOCATION
 * @param [out] semi_major A valid pointer to a @c double
 * @param [out] semi_minor A valid pointer to a @c double
 * @param [out] rotation   A valid pointer to a @c double
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_loc_rep_get_accuracy_elliptical (lm_reply_t *reply, double *semi_major, double *semi_minor, double *rotation);

/**
 * @brief Get the vertical speed of a location reply from Location Manager
 *
 * Return the vertical speed of @c reply into @c vertical_speed.
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t of type @c #LM_REP_TYPE_LOCATION
 * @param [out] vertical_speed A valid pointer to a @c double
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_loc_rep_get_vertical_speed (lm_reply_t *reply, double *vertical_speed);

/**
 * @brief Get the number of satellites of a location reply from Location Manager
 *
 * Return the number of satellites of @c reply into @c num_satellites.
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t of type @c #LM_REP_TYPE_LOCATION
 * @param [out] num_satellites A valid pointer to a @c size_t
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_loc_rep_get_num_satellites (lm_reply_t *reply, size_t *num_satellites);

/**
 * @brief Get the PRN of a satellite of a location reply from Location Manager
 *
 * Return the PRN of satellite @c id @c reply into @c prn.
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t of type @c #LM_REP_TYPE_LOCATION
 * @param [in]  id     The id of the satellite, between 0 and num_satellite
 * @param [out] prn    A valid pointer to a @c uint16_t
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_loc_rep_get_satellite_prn (lm_reply_t *reply, size_t id, uint16_t *prn);

/**
 * @brief Get the Carrier-to-Noise ratio of a location reply from Location Manager
 *
 * Return the CNO of satellite @c id @c reply into @c cno.
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t of type @c #LM_REP_TYPE_LOCATION
 * @param [in]  id     The id of the satellite, between 0 and num_satellite
 * @param [out] cno    A valid pointer to a @c double
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_loc_rep_get_satellite_cno (lm_reply_t *reply, size_t id, double *cno);

/**
 * @brief Get a flag of a satellite of a location reply from Location Manager
 *
 * Return a flag of satellite @c id @c reply into @c value.
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t of type @c #LM_REP_TYPE_LOCATION
 * @param [in]  id     The id of the satellite, between 0 and num_satellite
 * @param [in]  flag   The flag to read
 * @param [out] value  A valid pointer to a @c bool
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_loc_rep_get_satellite_flag (lm_reply_t *reply, size_t id, lm_satellite_flag_t flag, bool *value );

/**
 * @brief Get the azimuth of a location reply from Location Manager
 *
 * Return the azimuth of satellite @c id @c reply into @c elevation.
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t of type @c #LM_REP_TYPE_LOCATION
 * @param [in]  id     The id of the satellite, between 0 and num_satellite
 * @param [out] azimuth A valid pointer to a @c double
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_loc_rep_get_satellite_azimuth (lm_reply_t *reply, size_t id, double *azimuth);

/**
 * @brief Get the elevation of a location reply from Location Manager
 *
 * Return the elevation of satellite @c id @c reply into @c elevation.
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t of type @c #LM_REP_TYPE_LOCATION
 * @param [in]  id     The id of the satellite, between 0 and num_satellite
 * @param [out] elevation A valid pointer to a @c double
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_loc_rep_get_satellite_elevation (lm_reply_t *reply, size_t id, double *elevation);


/**
 * @brief Get the active request flag of a status reply from Location Manager
 *
 * Returns whether or not the status reply indicates that there is a current
 * request of this client with Location Manager.
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t of type @c #LM_REP_TYPE_STATUS
 * @param [out] active_request  A valid pointer to a @c bool
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_status_rep_get_active_request (lm_reply_t *reply, bool *active_request);

/**
 * @brief Get the period from a status reply from Location Manager
 *
 * Returns the period from a status reply from Location Manager.
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t of type @c #LM_REP_TYPE_STATUS
 * @param [out] period  A valid pointer to a @c double
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_status_rep_get_period (lm_reply_t *reply, double *period);

/**
 * @brief Get the accuracy from a status reply from Location Manager
 *
 * Returns the accuracy from a status reply from Location Manager.
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t of type @c #LM_REP_TYPE_STATUS
 * @param [out] accuracy  A valid pointer to a @c double
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_status_rep_get_accuracy (lm_reply_t *reply, double *accuracy);

/**
 * @brief Get the response time from a status reply from Location Manager
 *
 * Returns the response time from a status reply from Location Manager.
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t of type @c #LM_REP_TYPE_STATUS
 * @param [out] response_time  A valid pointer to a @c int
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_status_rep_get_response_time (lm_reply_t *reply, int *response_time);

/**
 * @brief Get the passive request flag from a status reply from Location Manager
 *
 * Returns whether or not the status reply indicates that the current request is passive.
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t of type @c #LM_REP_TYPE_STATUS
 * @param [out] passive  A valid pointer to a @c bool
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_status_rep_get_passive (lm_reply_t *reply, bool *passive);

/**
 * @brief Get the background request flag of a status reply from Location Manager
 *
 * Returns whether or not the status reply indicates that the current request is background mode.
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t of type @c #LM_REP_TYPE_STATUS
 * @param [out] background  A valid pointer to a @c bool
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_status_rep_get_background (lm_reply_t *reply, bool *background);


/**
 * @brief Get the error code from an error reply from Location Manager
 *
 * Returns the @c #lm_reply_error_code_t error code from a location reply into
 * @c err_code
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t of type @c #LM_REP_TYPE_ERROR
 * @param [out] err_code A valid pointer to a @c #lm_reply_error_code_t
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_error_rep_get_code (lm_reply_t *reply, lm_reply_error_code_t *err_code);

/**
 * @brief Get the error string from an error reply from Location Manager
 *
 * Returns the error string from a location reply into @c err_str
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t of type @c #LM_REP_TYPE_ERROR
 * @param [out] err_str A valid pointer to a C string
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_error_rep_get_string (lm_reply_t *reply, const char **err_str);

/**
 * @brief Get the long error string from an error reply from Location Manager
 *
 * Returns the long error string from a location reply into @c err_str
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t of type @c #LM_REP_TYPE_ERROR
 * @param [out] err_str A valid pointer to a C string
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_error_rep_get_long_string (lm_reply_t *reply, const char **err_str);


/**
 * @brief Get the status of Location Manager being on or off
 *
 * Returns the location status into @c location_on.
 *
 * @param [in]  reply  A pointer to a valid @c #lm_reply_t of type @c #LM_REP_TYPE_LOCATION_STATUS
 * @param [out] location_on A valid pointer to a bool
 *
 * @return @c #LM_ERR_NONE if successful.
 */
lm_error_t lm_loc_status_rep_get_state (lm_reply_t *reply, bool *location_on);


/**
 * @brief Queries the status of Location Manager
 *
 * Makes a blocking request to retrieve the latest status of Location Manager
 * and returns it into @c location_on.
 *
 * @param [out] location_on A valid pointer to a @c bool
 *
 * @return @c 0 if successful, @c -1 on failure
 */
int location_manager_get_status( bool *location_on );

#ifdef __cplusplus
}
#endif

