/*
 * $QNXLicenseC:
 * Copyright 2014, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software.   Free development
 * licenses are available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 * $
 */

/**
 * @credential_net.h
 *
 * This header file defines common network-related data and operations.
 */

#ifndef CREDENTIAL_NET_H_
#define CREDENTIAL_NET_H_

#include <stdbool.h>
#include <sys/credential_auth.h>

__BEGIN_DECLS

/**
 * Enumeration for special port values
 */
enum {
    /**
     * Reserved value that represents any port.
     */
    CREDENTIAL_NETWORK_PORT_ANY        = -1,

    /**
     * Reserved value that represents the default port for transport protocol.
     */
    CREDENTIAL_NETWORK_PORT_DEFAULT    = -2
};

/**
 * Enumeration for network host types.
 */
typedef enum {
    /**
     * A convenience value that matches any host type.
     */
    CREDENTIAL_NETWORK_HOST_ANY    = 1 << 0,

    /**
     * Indicates server host type.
     */
    CREDENTIAL_NETWORK_HOST_SERVER = 1 << 1,

    /**
     * Indicates proxy host type.
     */
    CREDENTIAL_NETWORK_HOST_PROXY  = 1 << 2,

    /**
     * Indicates other host type.
     */
    CREDENTIAL_NETWORK_HOST_OTHER  = 1 << 3,
} credential_net_host_type_t;

/**
 * Represents bitmask for network host types.
 */
typedef unsigned int credential_net_host_mask_t;

/**
 * Enumeration for network protocol types.
 */
typedef enum {
    /**
     * A convenience value that matches any protocol.
     */
    CREDENTIAL_NETWORK_PROTOCOL_ANY        = 1 << 0,

    /**
     * A convenience value that matches any secure protocol.
     */
    CREDENTIAL_NETWORK_PROTOCOL_ANY_SECURE = 1 << 1,

    /**
     * Indicates HTTP network protocol type.
     */
    CREDENTIAL_NETWORK_PROTOCOL_HTTP       = 1 << 2,

    /**
     * Indicates HTTP secure network protocol type.
     */
    CREDENTIAL_NETWORK_PROTOCOL_HTTPS      = 1 << 3,

    /**
     * Indicates FTP network protocol type.
     */
    CREDENTIAL_NETWORK_PROTOCOL_FTP        = 1 << 4,

    /**
     * Indicates FTP secure network protocol type.
     */
    CREDENTIAL_NETWORK_PROTOCOL_FTPS       = 1 << 5,

    /**
     * Indicates other network protocol type.
     */
    CREDENTIAL_NETWORK_PROTOCOL_OTHER      = 1 << 6
} credential_net_protocol_t;

/**
 * Represents bitmask for network protocol types.
 */
typedef unsigned int credential_net_protocol_mask_t;

/**
 * @brief Indicate whether given protocols provide communication security
 * @details Verify that all the protocols types in the input mask are are secure protocols.
 *
 * The following protocols are considered to provide communication security:
 * - @c #CREDENTIAL_NETWORK_PROTOCOL_HTTPS
 * - @c #CREDENTIAL_NETWORK_PROTOCOL_FTPS
 *
 * @param[in]   protocols   The network protocols in question.
 *
 * @return @c true if all of the given network protocols provide communication security,
 *         @c false otherwise.
 */
extern
bool
credential_net_protocols_are_secure(
    credential_net_protocol_mask_t protocols);

/**
 * @brief Indicate whether given protocol/authentication schemes are secure
 * @details Verify that all the authentication schemes included in the input mask are are secure.
 *
 * The following schemes are considered to be secure:
 * - @c #CREDENTIAL_AUTH_SCHEME_DIGEST
 * - @c #CREDENTIAL_AUTH_SCHEME_KERBEROS
 * - @c #CREDENTIAL_AUTH_SCHEME_NEGOTIATE
 * - @c #CREDENTIAL_AUTH_SCHEME_CLIENT_CERT
 *
 * The following schemes are considered to be secure if used over secure transport:
 * - @c #CREDENTIAL_AUTH_SCHEME_HTML_FORM
 * - @c #CREDENTIAL_AUTH_SCHEME_NTLM
 *
 * @param[in]   protocols       The network protocols in question.
 * @param[in]   auth_schemes    The authentication schemes in question.
 *
 * @return @c true if all of the given protocol/authentication schemes are secure,
 *         @c false otherwise.
 *
 */
extern
bool
credential_net_auth_schemes_are_secure(
    credential_net_protocol_mask_t protocols,
    credential_auth_scheme_mask_t auth_schemes);

/**
 * @brief Retrieve the username portion from identity name
 * @details Retrieve and return the user name from the network identity in a newly allocated buffer.
 *
 * @param[in]   identity_name       Identity name.
 * @param[out]  username            On return, a pointer to a string containing the username portion
 *                                  of the @c identity_name.
 *                                  The string is UTF-8 encoded and null-terminated.
 *                                  You must call @c credential_util_free()
 *                                  to release this string when you are finished using it.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_net_identity_get_username(
    const char* identity_name,
    char** username);

/**
 * @brief Retrieve the domain portion from the identity name
 * @details Retrieve and return the domain name from the network identity in a newly allocated buffer.
 *
 * @param[in]   identity_name       Identity name.
 * @param[out]  domain              On return, a pointer to a string containing the domain portion
 *                                  of the @c identity_name.
 *                                  The string is UTF-8 encoded and null-terminated.
 *                                  You must call @c credential_util_free()
 *                                  to release this string when you are finished using it.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_net_identity_get_domain(
    const char* identity_name,
    char** domain);

/**
 * @brief Create a new network-based authentication scope
 * @details This function allocates and initializes a new @c #credential_auth_scope_t structure.
 *
 * @param[in]   protocols           Protocols allowed in this authentication scope.
 * @param[in]   server_name         An ASCII encoded string that contains the server name (null-terminated).
 * @param[in]   server_port         Server port, or @c #CREDENTIAL_NETWORK_PORT_ANY if any server port is allowed.
 * @param[in]   resource_path (Optional) An ASCII string that contains the resource path (null-terminated).
 *                                  If set to @c #NULL, then any resource path is allowed.
 * @param[in]   host_types          The types of network host that are allowed in this authentication scope.
 * @param[in]   auth_schemes        Authentication schemes allowed in this authentication scope.
 *                                  If the authentication scheme is unknown
 *                                  use @c #CREDENTIAL_AUTH_SCHEME_ANY or @c #CREDENTIAL_AUTH_SCHEME_ANY_SECURE.
 * @param[out]  auth_scope          On return, a pointer to the network-based authentication scope structure,
 *                                  You must call @c credential_auth_scope_release()
 *                                  to release this structure when you're done using it.
 *                                  This is an optional parameter. If set to 0, then no return value is assigned.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_net_auth_scope_create_from_server(
    credential_net_protocol_mask_t protocols,
    const char* server_name,
    int server_port,
    const char* resource_path,
    credential_net_host_mask_t host_types,
    credential_auth_scheme_mask_t auth_schemes,
    credential_auth_scope_t** auth_scope);

/**
 * @brief Create an authentication scope from service URL
 * @details This function allocates a new @c #credential_auth_scope_t structure
 *          and populate it using data extracted from the input URL.
 *
 * The following URL parts are used to initialize authentication scope:
 * - protocol type  (@c #credential_net_protocol_t).
 * - server name
 * - server port:   If the URL does not explicitly specify the server port,
 *                  then the query is initialized with the default port
 *                  for the given protocol type (for example, port 80 for HTTP).
 * - resource path: If URL does not contain a resource path,
 *                  then the query is initialized with an empty resource path.
 *
 * @param[in]   url             The URL of the service requiring authentication (null-terminated).
 *                              The URL string should be null-terminated and comply with RFC 3986.
 * @param[in]   host_types      The network host types that are allowed in this authentication scope.
 * @param[in]   auth_schemes    Authentication schemes allowed in this authentication scope.
 *                              If the authentication scheme is unknown
 *                              use @c #CREDENTIAL_AUTH_SCHEME_ANY or @c #CREDENTIAL_AUTH_SCHEME_ANY_SECURE.
 * @param[out]  auth_scope      On return, a pointer to the network-based authentication scope structure,
 *                              You must call @c credential_auth_scope_release()
 *                              to release this structure when you're done using it.
 *                              This is an optional parameter. If set to 0, then no return value is assigned.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_net_auth_scope_create_from_url(
    const char* url,
    credential_net_host_mask_t host_types,
    credential_auth_scheme_mask_t auth_schemes,
    credential_auth_scope_t** auth_scope);

/**
 * @brief Add a server to an existing network-based authentication scope
 * @details This function associates a new server to an authentication scope,
 *          where a server consists of a server name, port number, and resource path.
 *
 * @param[in]   authDomain          The authentication scope you wish to update.
 * @param[in]   serverName          An ASCII encoded string that contains the server name (null-terminated).
 * @param[in]   serverPort          Server port, or @c #CREDENTIAL_NETWORK_PORT_ANY if any server port is allowed.
 * @param[in]   resourcePath (Optional) An ASCII string containing the resource path (null-terminated).
 *                                  This is an optional parameter. If set to 0, then any resource path is allowed.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_net_auth_scope_add_server(
    credential_auth_scope_t* auth_scope,
    const char* server_name,
    int server_port,
    const char* resource_path);

__END_DECLS

#endif  // CREDENTIAL_NET_H_

__SRCVERSION( "$URL$ $Rev$" )