/*-----------------------------------------------------------------------------
 * BlackBerry VPN Extensions Library
 *
 * Copyright 2013-2014, BlackBerry Limited. All Rights Reserved.
 *
 * This source code may contain confidential information of BlackBerry
 * and its licensors. Any use, reproduction, modification,
 * disclosure, distribution or transfer of this software, or any software
 * that includes or is based upon any of this code, is prohibited unless
 * expressly authorized by BlackBerry by written agreement. For more information
 * (including whether this source code file has been published) please
 * email licensing@blackberry.com.
 */


/**
 * @file vpn_ext_api.h
 * @brief Functions that represent the VPN Extensions Provider API
 *
 * @details You can use these functions to perform fundamental VPN Extension
 *          operations, such as creating a VPN Extension context
 *          (@c vpn_ext_create_context()), adding a Key Agreement callback
 *          (@c vpn_ext_register_key_agreement()), and running the VPN service
 *          (@c vpn_ext_run_service()).
 */

/**
 * @defgroup vpnprovider VPN Extension Provider APIs
 */

#ifndef _VPN_EXT_API_H_
#define _VPN_EXT_API_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <vpnext/vpn_ext_type.h>

/**
 * @brief A macro to identify APIs that are exported from the VPN Extension's
 * shared library
 */
#define VPN_EXT_PUBLIC __attribute__ ((visibility ("default")))


/**
 * @brief Determine if the process is running in the enterprise perimeter
 *
 * @return @c true if the process is running in the enterprise perimeter,
 *         @c false otherwise.
 *
 * @ingroup vpnprovider
 */
VPN_EXT_PUBLIC
bool vpn_ext_running_in_enterprise( void );


/**
 * @brief Create the VPN Extension context
 *
 * @details This function creates a context that is passed into all subsequent
 * provider calls. Before the provider is finished, it should call
 * @c VPN_ExP_DestroyContext() to clean up memory that was allocated by the
 * library.
 *
 * @param extensionName The extension name that is used by the client to
 *                          open connections.
 * @param maxMsgLen The maximum message length. If @c 0 is provided, a
 *                      default value is used as the maximum message length.
 * @param maxGets The maximum number of reply messages that can be queued.
 *                    If @c 0 is provided, a default value is used as the
 *                    maximum number of reply messages.
 *
 * @return The VPN Extensions context structure. If the structure is @c NULL,
 *         then the @c errno value is set to indicate the error that occurred.
 *
 * @ingroup vpnprovider
 */
VPN_EXT_PUBLIC
vpn_ext_context vpn_ext_create_context( const char *extensionName, unsigned int maxMsgLen, unsigned int maxGets );


/**
 * @brief Provide the list of callbacks for VPN service functions that are
 * supported by the VPN Extension Provider library
 *
 * @details These callbacks are used to start or stop a registered VPN service.
 * Typically, these callbacks will be used to start or stop a 3rd party VPN
 * daemon. The VPN service will be started or stopped under the control of the
 * VPN Manager.
 *
 * @param context The VPN Extension context.
 * @param service_type The VPN service adapter type.
 * @param callbacks The structure that represents the callbacks.
 *
 * @retval EOK Success.
 * @retval EINVAL One or more invalid parameters were specified.
 *
 * @ingroup vpnprovider
 */
VPN_EXT_PUBLIC
errno_t vpn_ext_register_service( vpn_ext_context context, vpn_service_type_e service_type, const vpn_service_callbacks_t * callbacks );

/**
 * @brief Register a VPN Service that does not support callbacks
 *
 * @param context The VPN Extension context.
 * @param service_type The VPN service adapter type.
 *
 * @retval EOK Success.
 * @retval EINVAL One or more invalid parameters were specified.
 *
 * @ingroup vpnprovider
 */
VPN_EXT_PUBLIC
errno_t vpn_ext_register_service_no_deamon( vpn_ext_context context, vpn_service_type_e service_type );

/**
 * @brief Add a Key Agreement callback
 *
 * @param context The VPN Extension context.
 * @param api The API name. Possible values are @c VPN_EXT_KEYAGREE_*.
 * @param version The API version in the following format: @c xxxxyyyy, where
 *                    @c xxxx represents the major version number and @c yyyy
 *                    represents the minor version number.
 * @param mapping A JSON string containing the mapping that the callback
 *                    provides.
 * @param callback The callback function to add.
 *
 * @retval EOK Success.
 * @retval EINVAL One or more invalid parameters were specified.
 *
 * @ingroup vpnprovider
 */
VPN_EXT_PUBLIC
errno_t vpn_ext_register_key_agreement( vpn_ext_context context,
                                        const char *api,
                                        unsigned int version,
                                        const char *mapping,
                                        vpn_ext_callback_t callback );


/**
 * @brief Remove a Key Agreement callback that was added by
 *        @c vpn_ext_register_key_agreement()
 *
 * @param context The VPN Extension context.
 * @param api The API name. Possible values are @c VPN_EXT_KEYAGREE_*.
 *
 * @retval EOK Success.
 * @retval EINVAL One or more invalid parameters were specified.
 *
 * @ingroup vpnprovider
 */
VPN_EXT_PUBLIC
errno_t vpn_ext_deregister_key_agreement( vpn_ext_context context, const char *api );


/**
 * @brief Run the VPN service
 *
 * @param context The VPN Extension context.
 * @param run_timeout The timeout period (in seconds). When this timeout
 *                        period elapses, if there are no client connections,
 *                        this function will return. If @c 0 is provided, a
 *                        default value is used as the timeout period.
 *
 * @retval EOK Success.
 * @retval EINVAL One or more invalid parameters were specified.
 *
 * @ingroup vpnprovider
 */
VPN_EXT_PUBLIC
errno_t vpn_ext_run_service( vpn_ext_context context, unsigned int run_timeout );


/**
 * @brief Close the VPN Extension Provider library and interprocess
 *        communication (IPC) with the core VPN service.
 *
 * @param context The VPN Extension context.
 *
 * @retval EOK Success.
 * @retval EINVAL The library is already closed.
 *
 * @ingroup vpnprovider
 */
VPN_EXT_PUBLIC
errno_t vpn_ext_destroy_context( vpn_ext_context context );

#ifdef __cplusplus
}
#endif

#endif // _VPN_EXT_API_H_
