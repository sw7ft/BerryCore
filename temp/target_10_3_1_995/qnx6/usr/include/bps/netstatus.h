/*
 * Copyright (C) 2011-2014 BlackBerry Limited. All rights reserved.
 */

/**
 * @file netstatus.h
 *
 * @brief Functions to determine the current network status and networking
 * information
 *
 * This file defines the network status service, which provides functions for
 * reading the device's current networking state.  You can use the network
 * status service to determine network availability, HTTP and FTP proxy
 * information, and so on.
 *
 *
 * @since BlackBerry 10.0.0
 */

#ifndef _BPS_NETSTATUS_H_INCLUDED
#define _BPS_NETSTATUS_H_INCLUDED

#include <stdbool.h>
#include <sys/platform.h>
#include "bps/bps.h"

__BEGIN_DECLS

/**
 * @brief Possible network status events
 *
 * This enumeration defines the possible network status events.  Currently,
 * there is only one event.
 * @anonenum bps_netstatus_events Network status events
 *
 * @since BlackBerry 10.0.0
 */
enum {
    /**
     * The single networking status event, which contains all of the
     * information about the current networking state.
     *
     * @since BlackBerry 10.0.0
     */
    NETSTATUS_INFO          = 0x01
};

/**
 * @typedef struct netstatus_info_t
 *
 * @brief An opaque data type representing the network status information type
 *
 * The @c #netstatus_info_t structure is an opaque handle to network status
 * information.  You can extract the network status information using Netstatus
 * API functions.
 *
 * @since BlackBerry 10.2.0
 */
typedef struct netstatus_info_t netstatus_info_t;

/**
 * @brief Proxy details
 *
 * The @c #netstatus_proxy_details_t structure defines HTTP and FTP proxy
 * details, such as host, port, username, and password.
 *
 * @since BlackBerry 10.0.0
 */
struct netstatus_proxy_details_t {
    /**
     * The HTTP proxy host, or @c NULL if there is no HTTP proxy host.
     *
     * @since BlackBerry 10.0.0
     */
    char *      http_proxy_host;

    /**
     * The HTTP proxy port, or 0 if there is no HTTP proxy port.
     *
     * @since BlackBerry 10.0.0
     */
    int         http_proxy_port;

    /**
     * The HTTPS proxy host, or @c NULL if there is no HTTPS proxy host.
     *
     * @since BlackBerry 10.0.0
     */
    char *      https_proxy_host;

    /**
     * The HTTPS proxy port, or 0 if there is no HTTPS proxy port.
     *
     * @since BlackBerry 10.0.0
     */
    int         https_proxy_port;

    /**
     * The FTP proxy host, or @c NULL if there is no FTP proxy host.
     *
     * @since BlackBerry 10.0.0
     */
    char *      ftp_proxy_host;

    /**
     * The FTP proxy port, or 0 if there is no FTP proxy port.
     *
     * @since BlackBerry 10.0.0
     */
    int         ftp_proxy_port;

    /**
     * The user to log into the proxy as, or @c NULL if a login is not required.
     *
     * @since BlackBerry 10.0.0
     */
    char *      http_proxy_login_user;

    /**
     * The password to log into the proxy with, or @c NULL if a password is not
     * required.
     *
     * @since BlackBerry 10.0.0
     */
    char *      http_proxy_login_password;
};
/**
 * A data type that contains information about the proxy used for HTTP and FTP
 * connections.
 *
 * @since BlackBerry 10.0.0
 */
typedef struct netstatus_proxy_details_t netstatus_proxy_details_t;

/**
 * @brief Network interface list
 *
 * The @c #netstatus_interface_list_t structure defines the list of network
 * interfaces.
 *
 * @since BlackBerry 10.0.0
 */
struct netstatus_interface_list_t
{
    /**
     * The number of interfaces.  This is the size of the @c interfaces array.
     *
     * @since BlackBerry 10.0.0
     */
    int num_interfaces;

    /**
     * The names of the interfaces.  The size of this array is @c
     * num_interfaces.
     *
     * @since BlackBerry 10.0.0
     */
    char ** interfaces;
};
/**
 *  A data type that stores the number of and the names of the network
 *  interfaces.
 *
 * @since BlackBerry 10.0.0
 */
typedef struct netstatus_interface_list_t netstatus_interface_list_t;

/**
 * @brief Interface types
 *
 * This enumeration defines the different types of network interfaces.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * An unknown network interface.
     *
     * @since BlackBerry 10.0.0
     */
    NETSTATUS_INTERFACE_TYPE_UNKNOWN = 0,

    /**
     * A wired network interface.
     *
     * @since BlackBerry 10.0.0
     */
    NETSTATUS_INTERFACE_TYPE_WIRED = 1,

    /**
     * A wi-fi network interface.
     *
     * @since BlackBerry 10.0.0
     */
    NETSTATUS_INTERFACE_TYPE_WIFI = 2,

    /**
     * A Bluetooth dial-up network interface.
     *
     * @since BlackBerry 10.0.0
     */
    NETSTATUS_INTERFACE_TYPE_BLUETOOTH_DUN = 3,

    /**
     * A USB network interface.
     *
     * @since BlackBerry 10.0.0
     */
    NETSTATUS_INTERFACE_TYPE_USB = 4,

    /**
     * A virtual private network interface.
     *
     * @since BlackBerry 10.0.0
     */
    NETSTATUS_INTERFACE_TYPE_VPN = 5,

    /**
     * A BlackBerry network interface.
     *
     * @since BlackBerry 10.0.0
     */
    NETSTATUS_INTERFACE_TYPE_BB = 6,

    /**
     * A cellular network interface.
     *
     * @since BlackBerry 10.0.0
     */
    NETSTATUS_INTERFACE_TYPE_CELLULAR = 7,

    /**
     * A P2P network interface.
     *
     * @since BlackBerry 10.2.0
     */
    NETSTATUS_INTERFACE_TYPE_P2P = 8,
} netstatus_interface_type_t;

/**
 * @brief IP status
 *
 * This enumeration defines the values for IP status.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * IP is not OK, error unknown.
     *
     * @since BlackBerry 10.0.0
     */
    NETSTATUS_IP_STATUS_ERROR_UNKNOWN = 0,

    /**
     * IP is OK.
     *
     * @since BlackBerry 10.0.0
     */
    NETSTATUS_IP_STATUS_OK,

    /**
     * IP is not connected.
     *
     * @since BlackBerry 10.0.0
     */
    NETSTATUS_IP_STATUS_ERROR_NOT_CONNECTED,

    /**
     * IP is not up.
     *
     * @since BlackBerry 10.0.0
     */
    NETSTATUS_IP_STATUS_ERROR_NOT_UP,

    /**
     * IP is not configured.
     *
     * @since BlackBerry 10.0.0
     */
    NETSTATUS_IP_STATUS_ERROR_NOT_CONFIGURED,

    /**
     * IPv6 is off.
     *
     * @since BlackBerry 10.0.0
     */
    NETSTATUS_IP_STATUS_ERROR_IP6_OFF,

    /**
     * IP has no IP address.
     *
     * @since BlackBerry 10.0.0
     */
    NETSTATUS_IP_STATUS_ERROR_NO_IP_ADDRESS,

    /**
     * IP has no IPv6 address.
     *
     * @since BlackBerry 10.0.0
     */
    NETSTATUS_IP_STATUS_ERROR_NO_IP6_ADDRESS,

    /**
     * IP has no IP gateway.
     *
     * @since BlackBerry 10.0.0
     */
    NETSTATUS_IP_STATUS_ERROR_NO_IP_GATEWAY,

    /**
     * IP has no IPv6 gateway.
     *
     * @since BlackBerry 10.0.0
     */
    NETSTATUS_IP_STATUS_ERROR_NO_IP6_GATEWAY,

    /**
     * IP has no name server.
     *
     * @since BlackBerry 10.0.0
     */
    NETSTATUS_IP_STATUS_ERROR_NO_NAME_SERVER,
} netstatus_ip_status_t;

/**
 * @brief Network interface details
 *
 * The @c #netstatus_interface_details_t structure defines network interface
 * details, such as name, type, and IP addresses.  Its fields can be accessed
 * by the @c netstatus_interface_*() functions.
 *
 * @since BlackBerry 10.0.0
 */
typedef struct netstatus_interface_details_t netstatus_interface_details_t;

/**
 * @brief Start receiving networking change events
 *
 * The @c netstatus_request_events() function starts to deliver networking
 * change events to your application using BPS.  Events will be posted to
 * the currently active channel.
 *
 * @param flags The types of events to deliver.  A value of zero indicates that
 * all events are requested. The meaning of non-zero values is reserved for
 * future use.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int netstatus_request_events(int flags);

/**
 * @brief Stop receiving networking change events
 *
 * The @c netstatus_stop_events() function stops networking change events from
 * being delivered to the application using BPS.
 *
 * @param flags The types of events to stop. A value of zero indicates that all
 * events are stopped. The meaning of non-zero values is reserved for future
 * use.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int netstatus_stop_events(int flags);

/**
 * @brief Get the unique domain ID for the network status service
 *
 * The @c netstatus_get_domain() function gets the unique domain ID for
 * the network status service.  You can use this function in your application
 * to test whether an event that you retrieve using @c bps_get_event() is a
 * network status event, and respond accordingly.
 *
 * @return The domain ID for the network status service.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int netstatus_get_domain();

/**
 * @brief This function has been deprecated
 *
 * @deprecated This function has been deprecated - use @c netstatus_get_info(),
 * @c netstatus_info_get_availability() and @c netstatus_free_info().
 *
 * The @c netstatus_get_availability() function indicates whether a network
 * connection is available.
 *
 * @param is_available If @c true the network is available, if @c
 * false the network is not available.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int netstatus_get_availability(bool *is_available) BPS_DEPRECATED;

/**
 * @brief This function has been deprecated
 *
 * @deprecated This function has been deprecated - use @c netstatus_get_info(),
 * @c netstatus_info_get_default_interface() and @c netstatus_free_info().
 *
 * The @c netstatus_get_default_interface() function gets the default interface.
 *
 * @param interface This will be populated with the default interface.  May be
 * @c NULL if there is no default interface.  The caller must call @c bps_free()
 * when done with this string.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int netstatus_get_default_interface(char **interface) BPS_DEPRECATED;

/**
 * @brief Get the proxy details
 *
 * The @c netstatus_get_proxy_details() function gets the proxy details of the
 * network connection.
 *
 * @param details This will be populated with the proxy details.  The
 * caller must call @c netstatus_free_proxy_details() when done with this
 * structure.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int netstatus_get_proxy_details(netstatus_proxy_details_t *details);

/**
 * @brief Get the proxy details for a given URL and (optional) interface
 *
 * The @c netstatus_get_proxy_details_for_url() function gets the proxy details
 * of the network connection for a given URL. System proxy credentials are
 * retrieved only for the default interface.
 *
 * Note that the API caller is responsible for validating the UTF-8 encoding and
 * the format of the proxy host returned in @c details.
 *
 * @param url The URL to check proxy settings against.
 *
 * @param interface The name of the interface whose proxy is being checked. This
 * may be @c NULL, in which case the default interface will be checked.
 *
 * @param details A pointer to a location where the function can store the proxy
 * details. The caller must call @c netstatus_free_proxy_details() when done
 * with this structure.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int netstatus_get_proxy_details_for_url(const char *url, const char *interface, netstatus_proxy_details_t *details);

/**
 * @brief Free the memory that is used by a proxy details structure
 *
 * The @c netstatus_free_proxy_details() function frees the memory that is used
 * by the specified @c #netstatus_proxy_details_t structure.
 *
 * @param details The structure whose memory needs to be freed.  Note that the
 * pointer to the structure is not freed.
 *
 * @return Nothing.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API void netstatus_free_proxy_details(netstatus_proxy_details_t *details);

/**
 * @brief This function has been deprecated
 *
 * @deprecated This function has been deprecated - use @c
 * netstatus_event_get_info() and @c netstatus_info_get_availability().
 *
 * The @c netstatus_event_get_availability() function indicates whether the
 * network is available from the specified @c NETSTATUS_INFO event.
 *
 * @param event The @c NETSTATUS_INFO event to get the networking status from.
 *
 * @return @c true if the network is available, @c false otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool netstatus_event_get_availability(bps_event_t *event) BPS_DEPRECATED;

/**
 * @brief This function has been deprecated
 *
 * @deprecated This function has been deprecated - use @c
 * netstatus_event_get_info() and @c netstatus_info_get_default_interface().
 *
 * The @c netstatus_event_get_default_interface() function gets the current
 * default interface from the specified @c NETSTATUS_INFO event.
 *
 * @param event The @c NETSTATUS_INFO event to get the default interface
 * information from.
 *
 * @return The default interface, or @c NULL if there is no default interface.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char * netstatus_event_get_default_interface(bps_event_t *event) BPS_DEPRECATED;

/**
 * @brief This function has been deprecated
 *
 * @deprecated This function has been deprecated - use @c
 * netstatus_event_get_info() and @c
 * netstatus_info_get_http_proxy_login_required().
 *
 * The @c netstatus_event_get_http_proxy_login_required() function indicates
 * whether login information is required for HTTP proxy from the specified @c
 * NETSTATUS_INFO event.  If login information is required, call @c
 * netstatus_get_proxy_details() to get the user and password to log in with.
 *
 * @param event The @c NETSTATUS_INFO event to get the HTTP proxy information
 * from.
 *
 * @return @c true if login information is required for HTTP proxy, @c false
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool netstatus_event_get_http_proxy_login_required(bps_event_t *event) BPS_DEPRECATED;

/**
 * @brief This function has been deprecated
 *
 * @deprecated This function has been deprecated - use @c
 * netstatus_event_get_info() and @c netstatus_info_get_http_proxy_host().
 *
 * The @c netstatus_event_get_http_proxy_host() function gets the current HTTP
 * proxy host from the specified @c NETSTATUS_INFO event.
 *
 * @param event The @c NETSTATUS_INFO event to get the HTTP proxy host
 * information from.
 *
 * @return The HTTP proxy host, or @c NULL if there is no HTTP proxy host.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char * netstatus_event_get_http_proxy_host(bps_event_t *event) BPS_DEPRECATED;

/**
 * @brief This function has been deprecated
 *
 * @deprecated This function has been deprecated - use @c
 * netstatus_event_get_info() and @c netstatus_info_get_http_proxy_port().
 *
 * The @c netstatus_event_get_http_proxy_port() function gets the current HTTP
 * proxy port from the specified @c NETSTATUS_INFO event.
 *
 * @param event The @c NETSTATUS_INFO event to get the HTTP proxy port
 * information from.
 *
 * @return The HTTP proxy port, or 0 if there is no HTTP proxy port.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int netstatus_event_get_http_proxy_port(bps_event_t *event) BPS_DEPRECATED;

/**
 * @brief This function has been deprecated
 *
 * @deprecated This function has been deprecated - use
 * @c netstatus_event_get_info() and @c netstatus_info_get_https_proxy_host().
 *
 * The @c netstatus_event_get_https_proxy_host() function gets the current
 * HTTPS proxy host from the specified @c NETSTATUS_INFO event.
 *
 * @param event The @c NETSTATUS_INFO event to get the HTTPS proxy host
 * information from.
 *
 * @return The HTTPS proxy host, or @c NULL if there is no HTTPS proxy host.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char * netstatus_event_get_https_proxy_host(bps_event_t *event) BPS_DEPRECATED;

/**
 * @brief This function has been deprecated
 *
 * @deprecated This function has been deprecated - use @c
 * netstatus_event_get_info() and @c netstatus_info_get_https_proxy_port().
 *
 * The @c netstatus_event_get_https_proxy_port() function gets the current
 * HTTPS proxy port from the specified @c NETSTATUS_INFO event.
 *
 * @param event The @c NETSTATUS_INFO event to get the HTTPS proxy port
 * information from.
 *
 * @return The HTTPS proxy port, or 0 if there is no HTTPS proxy port.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int netstatus_event_get_https_proxy_port(bps_event_t *event) BPS_DEPRECATED;

/**
 * @brief This function has been deprecated
 *
 * @deprecated This function has been deprecated - use @c
 * netstatus_event_get_info() and @c netstatus_info_get_ftp_proxy_host().
 *
 * The @c netstatus_event_get_ftp_proxy_host() function gets the current FTP
 * proxy host from the specified @c NETSTATUS_INFO event.
 *
 * @param event The @c NETSTATUS_INFO event to get the FTP proxy host
 * information from.
 *
 * @return The FTP proxy host, or @c NULL if there is no FTP proxy host.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char * netstatus_event_get_ftp_proxy_host(bps_event_t *event) BPS_DEPRECATED;

/**
 * @brief This function has been deprecated
 *
 * @deprecated This function has been deprecated - use @c
 * netstatus_event_get_info() and @c netstatus_info_get_ftp_proxy_port().
 *
 * The @c netstatus_event_get_ftp_proxy_port() function gets the current FTP
 * proxy port from the specified @c NETSTATUS_INFO event.
 *
 * @param event The @c NETSTATUS_INFO event to get the FTP proxy port
 * information from.
 *
 * @return The FTP proxy port, or 0 if there is no FTP proxy port.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int netstatus_event_get_ftp_proxy_port(bps_event_t *event) BPS_DEPRECATED;

/**
 * @brief Retrieve the network status information structure from a @c
 *        NETSTATUS_INFO event
 *
 * You call the @c netstatus_event_get_info() function to retrieve the network
 * status information structure from a @c NETSTATUS_INFO event. Details about
 * the network status can be determined using the @c netstatus_info_get_*()
 * functions.  Do not use the @c netstatus_free_info() function on this @c
 * #netstatus_info_t pointer. The memory associated with the network status
 * information structure is valid as long as the event is valid and is freed
 * internally by BlackBerry Platform Services (BPS).
 *
 * @param event The @c NETSTATUS_INFO event to get the network status
 * information structure from.
 *
 * @return The network status information structure.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API netstatus_info_t * netstatus_event_get_info(bps_event_t *event);

/**
 * @brief Retrieve the current network status information
 *
 * The @c netstatus_get_info() function gets the current network status
 * information.  Details about the network status can be extracted using the @c
 * netstatus_info_get_*() functions.  @c netstatus_free_info() must be used on
 * the network status information structure when your application is finished
 * using it.
 *
 * @param info If this function successfully completes, this pointer is
 * populated with the network status information. The caller must call the @c
 * netstatus_free_info() function when finished with using the @c info value. If
 * the function does not complete successfully, the pointer is set to @c NULL.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int netstatus_get_info(netstatus_info_t **info);

/**
 * @brief Free the memory that is used by a network status information structure
 *
 * The @c netstatus_free_info() function releases the memory that is used by the
 * specified network status information structure, @c #netstatus_info_t. Only
 * use this function on structures retrieved from the @c netstatus_get_info()
 * function.
 *
 * @param info The structure whose memory needs to be freed.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API void netstatus_free_info(netstatus_info_t **info);

/**
 * @brief Indicate whether the network is available from a network status
 * structure
 *
 * The @c netstatus_get_availability() function indicates whether a network
 * connection is available from a @c #netstatus_info_t structure.
 *
 * @return @c true if the network is available, @c false if the network is not
 * available.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API bool netstatus_info_get_availability(netstatus_info_t *info);

/**
 * @brief Get the IP status from a network status structure
 *
 * The @c netstatus_info_get_ip_status() function gets the IP status from the
 * specified @c #netstatus_info_t structure.
 *
 * @param info The @c #netstatus_info_t structure to get the IP status from.
 *
 * @return The IP status.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API netstatus_ip_status_t netstatus_info_get_ip_status(netstatus_info_t *info);

/**
 * @brief Get the IPv4 status from a network status structure
 *
 * The @c netstatus_info_get_ip_status() function gets the IPv4 status from the
 * specified @c #netstatus_info_t structure.
 *
 * @param info The @c #netstatus_info_t structure to get the IPv4 status
 * from.
 *
 * @return The IP status.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API netstatus_ip_status_t netstatus_info_get_ip4_status(netstatus_info_t *info);

/**
 * @brief Get the IPv6 status from a network status structure
 *
 * The @c netstatus_info_get_ip_status() function gets the IPv6 status from the
 * specified @c #netstatus_info_t structure.
 *
 * @param info The @c #netstatus_info_t structure to get the IPv6 status
 * from.
 *
 * @return The IP status.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API netstatus_ip_status_t netstatus_info_get_ip6_status(netstatus_info_t *info);

/**
 * @brief Get the number of default gateways from a network status
 * structure
 *
 * The @c netstatus_info_get_num_default_gateways() function gets the number of
 * default gateways from the specified @c #netstatus_info_t structure.
 * The @c index argument of @c netstatus_info_get_ip_gateway() must be
 * less than this number.
 *
 * @param info The @c #netstatus_info_t structure to get the number of
 * default gateways from.
 *
 * @return The number of default gateways.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int netstatus_info_get_num_default_gateways(netstatus_info_t *info);

/**
 * @brief Get the default gateway at the specified index from a network status
 * structure
 *
 * The @c netstatus_info_get_default_gateway() function gets the default
 * gateway at the specified index from the specified @c #netstatus_info_t
 * structure.
 *
 * @param info The @c #netstatus_info_t structure to get the default gateway
 * from.
 *
 * @param index The index of the default gateway to get.  Must be in the range 0
 * to @c netstatus_info_get_num_ip_gateways() - 1.
 *
 * @return The default gateway at the specified index, or @c NULL if the index
 * is invalid.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API const char * netstatus_info_get_default_gateway(netstatus_info_t *info, int index);

/**
 * @brief Get the default interface from a network status structure
 *
 * The @c netstatus_info_get_default_interface() function gets the default
 * interface from the specified @c #netstatus_info_t structure.
 *
 * @return The default interface.  May be @c NULL if there is no default
 * interface.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API const char * netstatus_info_get_default_interface(netstatus_info_t *info);

/**
 * @brief Get the default IPv4 interface from a network status structure
 *
 * The @c netstatus_info_get_default_ip4_interface() function gets the default
 * IPv4 interface from the specified @c #netstatus_info_t structure.
 *
 * @return The default IPv4 interface.  May be @c NULL if there is no default
 * IPv4 interface.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API const char * netstatus_info_get_default_ip4_interface(netstatus_info_t *info);

/**
 * @brief Get the default IPv6 interface from a network status structure
 *
 * The @c netstatus_info_get_default_ip6_interface() function gets the default
 * IPv6 interface from the specified @c #netstatus_info_t structure.
 *
 * @return The default IPv6 interface.  May be @c NULL if there is no default
 * IPv6 interface.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API const char * netstatus_info_get_default_ip6_interface(netstatus_info_t *info);

/**
 * @brief Get the number of name servers from a network status structure
 *
 * The @c netstatus_info_get_num_name_servers() function gets the number of name
 * servers from the specified @c #netstatus_info_t structure.  The @c index
 * argument of @c netstatus_info_get_name_server() must be less than this
 * number.
 *
 * @param info The @c #netstatus_info_t structure to get the info name from.
 *
 * @return The number of name servers.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int netstatus_info_get_num_name_servers(netstatus_info_t *info);

/**
 * @brief Get the name server at the specified index from a network status
 * structure
 *
 * The @c netstatus_info_get_name_server() function gets the name server at the
 * specified index from the specified @c #netstatus_info_t structure.
 *
 * @param info The @c #netstatus_info_t structure to get the name server from.
 *
 * @param index The index of the name server to get.  Must be in the range 0 to
 * @c netstatus_info_get_num_name_servers() - 1.
 *
 * @return The name server at the specified index, or @c NULL if the index is
 * invalid.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API const char * netstatus_info_get_name_server(netstatus_info_t *info, int index);

/**
 * @brief Get the number of search domains from a network status structure
 *
 * The @c netstatus_info_get_num_search_domains() function gets the number of
 * search domains from the specified @c #netstatus_info_t structure.  The @c
 * index argument of @c netstatus_info_get_search_domain() must be less than
 * this number.
 *
 * @param info The @c #netstatus_info_t structure to get the number of search
 * domains from.
 *
 * @return The number of search domains.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int netstatus_info_get_num_search_domains(netstatus_info_t *info);

/**
 * @brief Get the search domain at the specified index from a network status
 * structure
 *
 * The @c netstatus_info_get_search_domain() function gets the search domain at
 * the specified index from the specified @c #netstatus_info_t structure.
 *
 * @param info The @c #netstatus_info_t structure to get the search domain from.
 *
 * @param index The index of the search domain to get.  Must be in the range 0
 * to @c netstatus_info_get_num_search_domains() - 1.
 *
 * @return The search domain at the specified index, or @c NULL if the index is
 * invalid.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API const char * netstatus_info_get_search_domain(netstatus_info_t *info, int index);

/**
 * @brief Indicate whether login information is required for HTTP proxy from a
 * network status structure
 *
 * The @c netstatus_info_get_http_proxy_login_required() function indicates
 * whether login information is required for HTTP proxy from the specified @c
 * #netstatus_info_t structure.  If login information is required, call @c
 * netstatus_get_proxy_details() to get the user and password to log in with.
 *
 * @param info The @c #netstatus_info_t structure to get the HTTP proxy information
 * from.
 *
 * @return @c true if login information is required for HTTP proxy, @c false
 * otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API bool netstatus_info_get_http_proxy_login_required(netstatus_info_t *info);

/**
 * @brief Get the current HTTP proxy host from a network status structure
 *
 * The @c netstatus_info_get_http_proxy_host() function gets the current HTTP
 * proxy host from the specified @c #netstatus_info_t structure.
 *
 * @param info The @c #netstatus_info_t structure to get the HTTP proxy host
 * information from.
 *
 * @return The HTTP proxy host, or @c NULL if there is no HTTP proxy host.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API const char * netstatus_info_get_http_proxy_host(netstatus_info_t *info);

/**
 * @brief Get the current HTTP proxy port from a network status structure
 *
 * The @c netstatus_info_get_http_proxy_port() function gets the current HTTP
 * proxy port from the specified @c #netstatus_info_t structure.
 *
 * @param info The @c #netstatus_info_t structure to get the HTTP proxy port
 * information from.
 *
 * @return The HTTP proxy port, or 0 if there is no HTTP proxy port.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int netstatus_info_get_http_proxy_port(netstatus_info_t *info);

/**
 * @brief Get the current HTTPS proxy host from a network status structure
 *
 * The @c netstatus_info_get_https_proxy_host() function gets the current HTTPS
 * proxy host from the specified @c #netstatus_info_t structure.
 *
 * @param info The @c #netstatus_info_t structure to get the HTTPS proxy host
 * information from.
 *
 * @return The HTTPS proxy host, or @c NULL if there is no HTTPS proxy host.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API const char * netstatus_info_get_https_proxy_host(netstatus_info_t *info);

/**
 * @brief Get the current HTTPS proxy port from a network status structure
 *
 * The @c netstatus_info_get_https_proxy_port() function gets the current HTTPS
 * proxy port from the specified @c #netstatus_info_t structure.
 *
 * @param info The @c #netstatus_info_t structure to get the HTTPS proxy port
 * information from.
 *
 * @return The HTTPS proxy port, or 0 if there is no HTTPS proxy port.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int netstatus_info_get_https_proxy_port(netstatus_info_t *info);

/**
 * @brief Get the current FTP proxy host from a network status structure
 *
 * The @c netstatus_info_get_ftp_proxy_host() function gets the current FTP
 * proxy host from the specified @c #netstatus_info_t structure.
 *
 * @param info The @c #netstatus_info_t structure to get the FTP proxy host
 * information from.
 *
 * @return The FTP proxy host, or @c NULL if there is no FTP proxy host.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API const char * netstatus_info_get_ftp_proxy_host(netstatus_info_t *info);

/**
 * @brief Get the current FTP proxy port from a network status structure
 *
 * The @c netstatus_info_get_ftp_proxy_port() function gets the current FTP
 * proxy port from the specified @c #netstatus_info_t structure.
 *
 * @param info The @c #netstatus_info_t structure to get the FTP proxy port
 * information from.
 *
 * @return The FTP proxy port, or 0 if there is no FTP proxy port.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int netstatus_info_get_ftp_proxy_port(netstatus_info_t *info);

/**
 * @brief Get the network interfaces
 *
 * The @c netstatus_get_interfaces() function gets all the network interfaces
 * present.
 *
 * @param interface_list This will be populated with the list of interfaces.
 * The caller must call @c netstatus_free_interfaces() when done with this
 * structure.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int netstatus_get_interfaces(netstatus_interface_list_t *interface_list);

/**
 * @brief Free the memory that is used by a network interface list structure
 *
 * The @c netstatus_free_interfaces() function frees the memory that is
 * used by the specified @c #netstatus_interface_list_t structure.
 *
 * @param interface_list The structure whose memory needs to be freed. Note that
 * the pointer to the structure is not freed.
 *
 * @return Nothing.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API void netstatus_free_interfaces(netstatus_interface_list_t *interface_list);

/**
 * @brief Get the details of a specified network interface
 *
 * The @c netstatus_get_interface_details() function gets the details of the
 * specified network interface.
 *
 * @param interface the interface to get the details of.  Should be one of the
 * interfaces received from @c netstatus_get_interfaces(), or @c
 * netstatus_info_get_default_interface().  If @c NULL, reports the details of
 * the default interface, if there is one.
 *
 * @param details This will be populated with the network interface details.
 * The caller must call @c netstatus_free_interface_details() when done with
 * this structure.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int netstatus_get_interface_details(const char *interface, netstatus_interface_details_t **details);

/**
 * @brief Free the memory that is used by a network interface details structure
 *
 * The @c netstatus_free_interface_details() function frees the memory that is
 * used by the specified @c #netstatus_interface_details_t structure.
 *
 * @param details The structure whose memory needs to be freed.
 *
 * @return Nothing.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API void netstatus_free_interface_details(netstatus_interface_details_t **details);

/**
 * @brief Get the interface name from a network interface details structure
 *
 * The @c netstatus_interface_get_name() function gets the interface name from
 * the specified @c #netstatus_interface_details_t structure.
 *
 * @param details The @c #netstatus_interface_details_t structure to get the
 * interface name from.
 *
 * @return The interface name.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char * netstatus_interface_get_name(netstatus_interface_details_t *details);

/**
 * @brief Get the interface type from a network interface details structure
 *
 * The @c netstatus_interface_get_type() function gets the interface name from
 * the specified @c #netstatus_interface_details_t structure.
 *
 * @param details The @c #netstatus_interface_details_t structure to get the
 * interface type from.
 *
 * @return The interface type.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API netstatus_interface_type_t netstatus_interface_get_type(netstatus_interface_details_t *details);

/**
 * @brief Indicate whether the interface is connected from a network interface
 * details structure
 *
 * The @c netstatus_interface_is_connected() function indicates whether the
 * interface is connected from the specified @c #netstatus_interface_details_t
 * structure.
 *
 * @param details The @c #netstatus_interface_details_t structure to get the
 * interface connected status from.
 *
 * @return @c true if the interface is connected, @c false otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool netstatus_interface_is_connected(netstatus_interface_details_t *details);

/**
 * @brief Indicate whether the interface is up from a network interface details
 * structure
 *
 * The @c netstatus_interface_is_up() function indicates whether the interface
 * is up from the specified @c #netstatus_interface_details_t structure.
 *
 * @param details The @c #netstatus_interface_details_t structure to get the
 * interface up status from.
 *
 * @return @c true if the interface is up, @c false otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool netstatus_interface_is_up(netstatus_interface_details_t *details);

/**
 * @brief Get the IP status from a network interface details structure
 *
 * The @c netstatus_interface_get_ip_status() function gets the IP status from
 * the specified @c #netstatus_interface_details_t structure.
 *
 * @param details The @c #netstatus_interface_details_t structure to get the
 * IP status from.
 *
 * @return The IP status.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API netstatus_ip_status_t netstatus_interface_get_ip_status(netstatus_interface_details_t *details);

/**
 * @brief Get the IPv4 status from a network interface details structure
 *
 * The @c netstatus_interface_get_ip4_status() function gets the IPv4 status
 * from the specified @c #netstatus_interface_details_t structure.
 *
 * @param details The @c #netstatus_interface_details_t structure to get the
 * IPv4 status from.
 *
 * @return The IPv4 status.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API netstatus_ip_status_t netstatus_interface_get_ip4_status(netstatus_interface_details_t *details);

/**
 * @brief Get the IPv6 status from a network interface details structure
 *
 * The @c netstatus_interface_get_ip6_status() function gets the IPv6 status
 * from the specified @c #netstatus_interface_details_t structure.
 *
 * @param details The @c #netstatus_interface_details_t structure to get the
 * IPv6 status from.
 *
 * @return The IPv6 status.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API netstatus_ip_status_t netstatus_interface_get_ip6_status(netstatus_interface_details_t *details);

/**
 * @brief Get the number of IP addresses from a network interface details
 * structure
 *
 * The @c netstatus_interface_get_num_ip_addresses() function gets the number of
 * IP addresses from the specified @c #netstatus_interface_details_t structure.
 * The @c index argument of @c netstatus_interface_get_ip_address() and @c
 * netstatus_interface_get_ip_address_netmask() must be less than this number.
 *
 * @param details The @c #netstatus_interface_details_t structure to get the
 * interface name from.
 *
 * @return The number of IP addresses.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int netstatus_interface_get_num_ip_addresses(netstatus_interface_details_t *details);

/**
 * @brief Get the IP address at the specified index from a network interface
 * details structure
 *
 * The @c netstatus_interface_get_ip_address() function gets the IP address at
 * the specified index from the specified @c #netstatus_interface_details_t
 * structure.
 *
 * @param details The @c #netstatus_interface_details_t structure to get the
 * IP address from.
 *
 * @param index The index of the IP address to get.  Must be in the range 0 to
 * @c netstatus_interface_get_num_ip_addresses() - 1.
 *
 * @return The IP address at the specified index, or @c NULL if the index is
 * invalid.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char * netstatus_interface_get_ip_address(netstatus_interface_details_t *details, int index);

/**
 * @brief Get the IP address netmask at the specified index from a network
 * interface details structure
 *
 * The @c netstatus_interface_get_ip_address_netmask() function gets the IP
 * address netmask at the specified index from the specified @c
 * #netstatus_interface_details_t structure.
 *
 * @param details The @c #netstatus_interface_details_t structure to get the IP
 * address netmask from.
 *
 * @param index The index of the IP address netmask to get.  Must be in the
 * range 0 to @c netstatus_interface_get_num_ip_addresses() - 1.
 *
 * @return The IP address netmask at the specified index, or @c NULL if the
 * index is invalid.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char * netstatus_interface_get_ip_address_netmask(netstatus_interface_details_t *details, int index);

/**
 * @brief Get the IP broadcast address from a network interface details
 * structure
 *
 * The @c netstatus_interface_get_ip_broadcast_address() function gets the IP
 * broadcast address from the specified @c #netstatus_interface_details_t
 * structure.
 *
 * @param details The @c #netstatus_interface_details_t structure to get the IP
 * broadcast address from.
 *
 * @return The IP broadcast address.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char * netstatus_interface_get_ip_broadcast_address(netstatus_interface_details_t *details);

/**
 * @brief Get the IP destination address from a network interface details
 * structure
 *
 * The @c netstatus_interface_get_ip_destination_address() function gets the IP
 * destination address from the specified @c #netstatus_interface_details_t
 * structure.
 *
 * @param details The @c #netstatus_interface_details_t structure to get the IP
 * destination address from.
 *
 * @return The IP destination address, or @c NULL if there is no destination
 * address.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API const char * netstatus_interface_get_ip_destination_address(netstatus_interface_details_t *details);

/**
 * @brief Get the number of IP gateways from a network interface details
 * structure
 *
 * The @c netstatus_interface_get_num_ip_gateways() function gets the number of
 * IP gateways from the specified @c #netstatus_interface_details_t structure.
 * The @c index argument of @c netstatus_interface_get_ip_gateway() must be less
 * than this number.
 *
 * @param details The @c #netstatus_interface_details_t structure to get the
 * number of IP gateways from.
 *
 * @return The number of IP gateways.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int netstatus_interface_get_num_ip_gateways(netstatus_interface_details_t *details);

/**
 * @brief Get the IP gateway at the specified index from a network interface
 * details structure
 *
 * The @c netstatus_interface_get_ip_gateway() function gets the IP gateway at
 * the specified index from the specified @c #netstatus_interface_details_t
 * structure.
 *
 * @param details The @c #netstatus_interface_details_t structure to get the
 * IP gateway from.
 *
 * @param index The index of the IP gateway to get.  Must be in the range 0 to
 * @c netstatus_interface_get_num_ip_gateways() - 1.
 *
 * @return The IP gateway at the specified index, or @c NULL if the index is
 * invalid.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char * netstatus_interface_get_ip_gateway(netstatus_interface_details_t *details, int index);

/**
 * @brief Get the link address from a network interface details structure
 *
 * The @c netstatus_interface_get_link_address() function gets the link address
 * from the specified @c #netstatus_interface_details_t structure.
 *
 * @param details The @c #netstatus_interface_details_t structure to get the
 * link address from.
 *
 * @return The link address.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char * netstatus_interface_get_link_address(netstatus_interface_details_t *details);

/**
 * @brief Get the MTU from a network interface details structure
 *
 * The @c netstatus_interface_get_link_address() function gets the maximum
 * transmission unit from the specified @c #netstatus_interface_details_t
 * structure.
 *
 * @param details The @c #netstatus_interface_details_t structure to get the MTU
 * from.
 *
 * @return The MTU.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int netstatus_interface_get_mtu(netstatus_interface_details_t *details);

/**
 * @brief Get the parent interface from a network interface details structure
 *
 * The @c netstatus_interface_get_parent_interface() function gets the parent
 * interface from the specified @c #netstatus_interface_details_t structure.
 *
 * @param details The @c #netstatus_interface_details_t structure to get the
 * parent interface from.
 *
 * @return The parent interface.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API const char * netstatus_interface_get_parent_interface(netstatus_interface_details_t *details);

/**
 * @brief Get the number of name servers from a network interface details
 * structure
 *
 * The @c netstatus_interface_get_num_name_servers() function gets the number of
 * name servers from the specified @c #netstatus_interface_details_t structure.
 * The @c index argument of @c netstatus_interface_get_name_server() must be
 * less than this number.
 *
 * @param details The @c #netstatus_interface_details_t structure to get the
 * interface name from.
 *
 * @return The number of name servers.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int netstatus_interface_get_num_name_servers(netstatus_interface_details_t *details);

/**
 * @brief Get the name server at the specified index from a network interface
 * details structure
 *
 * The @c netstatus_interface_get_name_server() function gets the name server at
 * the specified index from the specified @c #netstatus_interface_details_t
 * structure.
 *
 * @param details The @c #netstatus_interface_details_t structure to get the
 * name server from.
 *
 * @param index The index of the name server to get.  Must be in the range 0 to
 * @c netstatus_interface_get_num_name_servers() - 1.
 *
 * @return The name server at the specified index, or @c NULL if the index is
 * invalid.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char * netstatus_interface_get_name_server(netstatus_interface_details_t *details, int index);

/**
 * @brief This function has been deprecated
 *
 * @deprecated This function has been deprecated - use @c
 * netstatus_interface_get_num_search_domains() and @c
 * netstatus_interface_get_search_domain().
 *
 * The @c netstatus_interface_get_search_domains() function gets the search
 * domains from the specified @c #netstatus_interface_details_t structure.
 *
 * @param details The @c #netstatus_interface_details_t structure to get the
 * search domains from.
 *
 * @return The search domains.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char * netstatus_interface_get_search_domains(netstatus_interface_details_t *details) BPS_DEPRECATED;

/**
 * @brief Get the number of search domains from a network interface details
 * structure
 *
 * The @c netstatus_interface_get_num_search_domains() function gets the number
 * of search domains from the specified @c #netstatus_interface_details_t
 * structure. The @c index argument of @c
 * netstatus_interface_get_search_domain() must be less than this number.
 *
 * @param details The @c #netstatus_interface_details_t structure to get the
 * number of search domains from.
 *
 * @return The number of search domains.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int netstatus_interface_get_num_search_domains(netstatus_interface_details_t *details);

/**
 * @brief Get the search domain at the specified index from a network interface
 * details structure
 *
 * The @c netstatus_interface_get_search_domain() function gets the search
 * domain at the specified index from the specified @c
 * #netstatus_interface_details_t structure.
 *
 * @param details The @c #netstatus_interface_details_t structure to get the
 * search domain from.
 *
 * @param index The index of the search domain to get.  Must be in the range 0
 * to @c netstatus_interface_get_num_search_domains() - 1.
 *
 * @return The search domain at the specified index, or @c NULL if the index is
 * invalid.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API const char * netstatus_interface_get_search_domain(netstatus_interface_details_t *details, int index);

/**
 * @brief Indicate whether login information is required for HTTP proxy from a
 * network interface details structure
 *
 * The @c netstatus_interface_get_http_proxy_login_required() function indicates
 * whether login information is required for HTTP proxy from the specified @c
 * #netstatus_interface_details_t structure.  If login information is required,
 * call @c netstatus_get_proxy_details() to get the user and password to log in
 * with.
 *
 * @param details The @c #netstatus_interface_details_t structure to get the
 * HTTP proxy information from.
 *
 * @return @c true if login information is required for HTTP proxy, @c false
 * otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API bool netstatus_interface_get_http_proxy_login_required(netstatus_interface_details_t *details);

/**
 * @brief Get the current HTTP proxy host from a network interface details
 * structure
 *
 * The @c netstatus_interface_get_http_proxy_host() function gets the current
 * HTTP proxy host from the specified @c #netstatus_interface_details_t
 * structure.
 *
 * @param details The @c #netstatus_interface_details_t structure to get the
 * HTTP proxy host information from.
 *
 * @return The HTTP proxy host, or @c NULL if there is no HTTP proxy host.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API const char * netstatus_interface_get_http_proxy_host(netstatus_interface_details_t *details);

/**
 * @brief Get the current HTTP proxy port from a network interface details
 * structure
 *
 * The @c netstatus_interface_get_http_proxy_port() function gets the current
 * HTTP proxy port from the specified @c #netstatus_interface_details_t
 * structure.
 *
 * @param details The @c #netstatus_interface_details_t structure to get the
 * HTTP proxy port information from.
 *
 * @return The HTTP proxy port, or 0 if there is no HTTP proxy port.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int netstatus_interface_get_http_proxy_port(netstatus_interface_details_t *details);

__END_DECLS

#endif // include guard
