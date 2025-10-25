/*
 * BlackBerry Limited, Copyright (C) 2013
 * BlackBerry Limited. All rights reserved.
 */

/**
 * @file push_payload.h
 * @brief Functions to store and access push content received from the Push
 *        Proxy Gateway (PPG)
 *
 * @since BlackBerry 10.2.0
 */

#ifndef _PUSH_PAYLOAD_H_INCLUDED
#define _PUSH_PAYLOAD_H_INCLUDED

#include <stdbool.h>
#include <sys/platform.h>
#include <push/push_errno.h>

__BEGIN_DECLS

/**
 * When processing an invocation request, this value can be used to check that
 * the request data contains a push message.
 *
 * For more information about invocation requests, see @c
 * bps/navigator_invoke.h.
 *
 * @since BlackBerry 10.2.0
 */
#define PUSH_INVOCATION_ACTION      "bb.action.PUSH"

/**
 * The MIME type of a push message. Used by the invocation framework as part of
 * the target filter.
 *
 * For more information about invocation requests, see @c
 * bps/navigator_invoke.h.
 *
 * @since BlackBerry 10.2.0
 */
#define PUSH_INVOCATION_TYPE        "application/vnd.push"

/**
 * The target filter used by an application in order to tell the invocation
 * framework that the application supports receiving push messages.
 *
 * For more information about invocation requests, see @c
 * bps/navigator_invoke.h.
 *
 * @since BlackBerry 10.2.0
 */
#define PUSH_INVOCATION_FILTER      "actions=bb.action.PUSH; types=application/vnd.push;"

/**
 * @brief The opaque push_header_t argument type that represents the structure
 *        of a header in a push message
 *
 * This type defines the @c #push_header_t structure used to access the headers
 * of the push content received from the Push Proxy Gateway (PPG). The @c
 * #push_header_t structure includes the following members:
 * - @b name: the header name (@c push_header_get_name())
 * - @b value: the header value (@c push_header_get_value())
 *
 * @since BlackBerry 10.2.0
 */
typedef struct push_header_t push_header_t;

/**
 * @brief The opaque push_payload_t argument type that represents the structure
 *        of the content in a push message
 *
 * This type defines the @c #push_payload_t structure used to access the push
 * content received from the Push Proxy Gateway (PPG).
 *
 * The @c #push_payload_t structure is opaque, but includes the following
 * members:
 *
 * - @b id: The push identifier (@c push_payload_get_id()).
 * - @b data: The push notification data that the push-enabled application
 *      received (@c push_payload_get_data()).
 * - @b dataLength: The length of the push notification data (@c
 *      push_payload_get_data_length()).
 * - @b ackRequired: Indicates whether an acknowledgment is required for this
 *      push message. Your application must invoke the @c
 *      push_service_accept_push() function if this value is true (@c
 *      push_payload_is_ack_required()).
 * - @b headersLength: The number of push headers (@c
 *      push_payload_get_headers_length()).
 * - @b headers: An array of @c #push_header_t structures. To retrieve a
 *      specific header use the @c push_payload_get_header() function.
 *
 * @since BlackBerry 10.2.0
 */
typedef struct push_payload_t push_payload_t;

/**
 * @brief Create a push_payload_t structure and allocate all necessary memory
 *
 * The @c push_payload_create() function creates an instance of a @c
 * #push_payload_t structure called @c push_payload to be used to store the push
 * content received from the Push Proxy Gateway (PPG).
 *
 * Use the @c push_payload_destroy() function to deallocate memory used by a @c
 * #push_payload_t structure (created by the @c push_payload_create() function)
 * that's no longer in use. Failing to do so will result in a memory leak.
 *
 * @param push_payload The @c #push_payload_t structure to populate.
 *
 * @return @c #PUSH_SUCCESS upon success, @c #PUSH_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.2.0
 */
int push_payload_create(push_payload_t** push_payload);

/**
 * @brief Deallocate the memory used by a push_payload_t structure
 *
 * The @c push_payload_destroy() function deallocates any memory set to a given
 * @c push_payload. Use this function to deallocate memory used by a @c
 * #push_payload_t structure (created by the @c push_payload_create() function)
 * that's no longer in use. Failing to do so will result in a memory leak.
 *
 * @param push_payload The @c #push_payload_t structure to deallocate.
 *
 * @return @c #PUSH_SUCCESS upon success, @c #PUSH_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.2.0
 */
int push_payload_destroy(push_payload_t* push_payload);

/**
 * @brief Set the payload data of a push_payload_t structure
 *
 * The @c push_payload_set_payload() function sets the @c payload and @c
 * payload_length of a given @c #push_payload_t structure.
 *
 * @param push_payload A pointer to the @c #push_payload_t structure whose @c
 *                     payload you want to set.
 *
 * @param payload The payload object contains push id, the raw pushed content,
 *                the headers (which are the key-value pairs of metadata sent
 *                with the pushed content), and a flag to indicate that
 *                application level acknowledgment is required for this push
 *                message.
 *
 * @param payload_length The length of the payload data.
 *
 * @return @c #PUSH_SUCCESS upon success, @c #PUSH_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.2.0
 */
int push_payload_set_payload(push_payload_t* push_payload, const unsigned char* payload, int payload_length);


/**
 * @brief Get the push ID from a push_payload_t structure
 *
 * The @c push_payload_get_id() function extracts the push ID of a given @c
 * #push_payload_t structure. This function doesn't copy members, and the
 * returned values are released once the @c #push_payload_t structure is
 * destroyed with the @c push_payload_destroy() function.
 *
 * @param push_payload A pointer to the @c #push_payload_t structure whose @c
 *                     id member you want to retrieve.
 *
 * @return The push identifier.
 *
 * @since BlackBerry 10.2.0
 */
const char* push_payload_get_id(const push_payload_t* push_payload);

/**
 * @brief Get the data that the push-enabled application received from a
 *        push_payload_t structure
 *
 * The push ID is the unique identifier that is given to a specific push request
 * by the content provider when they send the push request. The @c
 * push_payload_get_data() function extracts the push data of a given @c
 * #push_payload_t structure.
 *
 * This function doesn't copy members, and the returned values are released once
 * the @c #push_payload_t structure is destroyed with the @c
 * push_payload_destroy() function.
 *
 * @param push_payload A pointer to the @c #push_payload_t structure whose @c
 *                     data member you want to retrieve.
 *
 * @return The data that the push-enabled application received.
 *
 * @since BlackBerry 10.2.0
 */
const unsigned char* push_payload_get_data(const push_payload_t* push_payload);

/**
 * @brief Get the length of the push notification data from a push_payload_t
 *        structure
 *
 * The @c push_payload_get_data_length() function extracts the length of the
 * push notification data of a given @c #push_payload_t structure.
 *
 * This function doesn't copy members, and the returned values are released once
 * the @c #push_payload_t structure is destroyed with the @c
 * push_payload_destroy() function.
 *
 * @param push_payload A pointer to the @c #push_payload_t structure whose @c
 *                     dataLength member you want to retrieve.
 *
 * @return The length of the push notification data.
 *
 * @since BlackBerry 10.2.0
 */
int push_payload_get_data_length(const push_payload_t* push_payload);

/**
 * @brief Get whether an acknowledgment is required for the specified
 *        push_payload_t structure
 *
 * The @c push_payload_is_ack_required() function extracts the acknowledgment
 * required flag of a given @c #push_payload_t structure. This flag indicates
 * whether an acknowledgment is required for this push message.
 *
 * This function doesn't copy members, and the returned values are released once
 * the @c #push_payload_t structure is destroyed with the @c
 * push_payload_destroy() function.
 *
 * @param push_payload A pointer to the @c #push_payload_t structure whose @c
 *                     ackRequired member you want to retrieve.
 *
 * @return @c true if application level acknowledgment is required, @c false
 *         otherwise. Your application must invoke the @c
 *         push_service_accept_push() function if this function returns true.
 *
 * @since BlackBerry 10.2.0
 */
bool push_payload_is_ack_required(const push_payload_t* push_payload);

/**
 * @brief Get the number of the push headers from a push_payload_t structure
 *
 * The @c push_payload_get_headers_length() function extracts the length of the
 * push headers of a given @c #push_payload_t structure.
 *
 * To access a specific header, use the @c push_payload_get_header() function.
 * This function doesn't copy members, and the returned values are released once
 * the @c #push_payload_t structure is destroyed with the @c
 * push_payload_destroy() function.
 *
 * @param push_payload A pointer to the @c #push_payload_t structure whose @c
 *                     headersLength member you want to retrieve.
 *
 * @return The number of push headers received with the push content.
 *
 * @since BlackBerry 10.2.0
 */
int push_payload_get_headers_length(const push_payload_t* push_payload);

/**
 * @brief Get the push header at the specified index from a push_payload_t
 *        structure
 *
 * The @c push_payload_get_header() function extracts the push header at the
 * specified @c index of a given @c #push_payload_t structure.
 *
 * To access the header name and value, use the @c push_header_get_name() and
 * @c push_header_get_value() functions.
 *
 * This function doesn't copy members, and the returned values are released once
 * the @c #push_payload_t structure is destroyed with the @c
 * push_payload_destroy() function.
 *
 * @param push_payload A pointer to the @c #push_payload_t structure whose @c
 *                     #push_header_t member you want to retrieve.
 * @param index The index of the @c #push_header_t member you want to retrieve.
 *
 * @return A pointer to the push header at the specified @c index.
 *
 * @since BlackBerry 10.2.0
 */
const push_header_t* push_payload_get_header(const push_payload_t* push_payload, int index);

/**
 * @brief Get the header name from a push_header_t structure
 *
 * The @c push_header_get_name() function extracts the header name of a given
 * @c #push_header_t structure.
 *
 * This function doesn't copy members, and the returned values are released once
 * the @c #push_payload_t structure is destroyed with the @c
 * push_payload_destroy() function.
 *
 * @param header A pointer to the @c #push_header_t structure whose @c name
 *               member you want to retrieve.
 *
 * @return The header name.
 *
 * @since BlackBerry 10.2.0
 */
const char* push_header_get_name(const push_header_t* header);

/**
 * @brief Get the header value from a push_header_t structure
 *
 * The @c push_header_get_value() function extracts the header value of a given
 * @c #push_header_t structure. This function doesn't copy members, and the
 * returned values are released once the @c #push_payload_t structure is
 * destroyed with the @c push_payload_destroy() function.
 *
 * @param header A pointer to the @c #push_header_t structure whose @c value
 *               member you want to retrieve.
 *
 * @return The header value.
 *
 * @since BlackBerry 10.2.0
 */
const char* push_header_get_value(const push_header_t* header);

/**
 * @brief Determines whether data validation was successful for a provided
 *        push_payload_t structure
 *
 * The @c push_payload_is_valid() function extracts the valid flag of a given
 * @c #push_payload_t structure. This flag indicates whether or not data
 * validation is successful. Your application should call this function before
 * calling @c push_payload_get_data() and @c push_payload_get_data_length().
 *
 * This function doesn't copy members, and the returned values are released once
 * the @c #push_payload_t structure is destroyed with the @c
 * push_payload_destroy() function.
 *
 * @param push_payload A pointer to the @c #push_payload_t structure whose @c
 *                     valid member you want to retrieve.
 *
 * @return @c true if the push notification data is valid, @c false otherwise
 *
 * @since BlackBerry 10.2.0
 */
bool push_payload_is_valid(const push_payload_t* push_payload);

__END_DECLS
#endif /* _PUSH_PAYLOAD_H_INCLUDED */
