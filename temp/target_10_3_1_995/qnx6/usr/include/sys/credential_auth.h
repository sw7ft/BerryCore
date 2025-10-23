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
 * @file credential_auth.h
 *
 * This header file defines operations
 * to report authentication results.
 */

#ifndef CREDENTIAL_AUTH_H_
#define CREDENTIAL_AUTH_H_

#include <sys/credential_store.h>

__BEGIN_DECLS

/**
 * Enumeration of authentication results.
 */
typedef enum {
    /**
     * Authentication succeeded.
     */
    CREDENTIAL_AUTH_STATUS_OK = 0,

    /**
     * Authentication failed (generic error).
     */
    CREDENTIAL_AUTH_STATUS_FAILED    = 1,

    /**
     * Authentication mechanism is not available.
     */
    CREDENTIAL_AUTH_STATUS_MECH_NOT_AVAIL = 2
} credential_auth_status_t;

/**
 * Enumeration for authentication schemes types.
 */
typedef enum {
    /**
     * A convenience value that matches any authentication scheme.
     */
    CREDENTIAL_AUTH_SCHEME_ANY         = 1 << 0,

    /**
     * A convenience value that matches any secure authentication scheme.
     */
    CREDENTIAL_AUTH_SCHEME_ANY_SECURE  = 1 << 1,

    /**
     * Indicates basic authentication scheme
     */
    CREDENTIAL_AUTH_SCHEME_BASIC       = 1 << 2,

    /**
     * Indicates digest-based authentication scheme
     */
    CREDENTIAL_AUTH_SCHEME_DIGEST      = 1 << 3,

    /**
     * Indicates html form-based authentication scheme
     */
    CREDENTIAL_AUTH_SCHEME_HTML_FORM   = 1 << 4,

    /**
     * Indicates NTLM-based authentication scheme
     */
    CREDENTIAL_AUTH_SCHEME_NTLM        = 1 << 5,

    /**
     * Indicates Kerberos-based authentication scheme
     */
    CREDENTIAL_AUTH_SCHEME_KERBEROS    = 1 << 6,

    /**
     * Indicates negotiate authentication scheme
     */
    CREDENTIAL_AUTH_SCHEME_NEGOTIATE   = 1 << 7,

    /**
     * Indicates client certificate authentication scheme
     */
    CREDENTIAL_AUTH_SCHEME_CLIENT_CERT = 1 << 8,

    /**
     * Indicates other authentication scheme
     */
    CREDENTIAL_AUTH_SCHEME_OTHER = 1 << 9
} credential_auth_scheme_t;

/**
 * Represents bitmask for authentication schemes types.
 */
typedef unsigned int credential_auth_scheme_mask_t;

/**
 * Represents an authentication scope.
 *
 * Credentials can have multiple authentication scopes.
 */
typedef struct _credential_auth_scope_t credential_auth_scope_t;

/**
 * @brief Associate an authentication scope with given credential
 * @details Adds an authentication scope to given credential, so that the credential
 *          can be retrieved using queries initialized from a matching authentication scope.
 *
 * @param[in]  cred         The credential to associate with authentication scope.
 * @param[in]  auth_scope   The authentication scope to associate with credential.
 *                          The caller continues to own the memory for this structure.
 *
 * @retval 0 if operation was successful, error code otherwise.
 */
extern
int
credential_add_auth_scope(
    const credential_t* cred,
    const credential_auth_scope_t* auth_scope);

/**
 * @brief Release a structure that represents an authentication scope
 * @details This function releases the @c #credential_auth_scope_t to return resources
 * to the system and avoid memory leakage.
 *
 * @param[in]  auth_scope The handle to release.
 *
 * @retval 0 if operation was successful, error code otherwise.
 */
extern
void
credential_auth_scope_release(
    credential_auth_scope_t** auth_scope);

/**
 * @brief Create a credential query from authentication scope.
 * @details Create a credential query that matches all credentials that are suitable
 *          for given authentication scope.
 *
 * @param[in]   auth_scope  The authentication scope of interest.
 * @param[out]  query       The credential query that can be used to lookup credentials
 *                          based on given authentication scope.
 *                          You must call @c credential_query_release()
 *                          to release this structure when you're done using it.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_query_create_from_auth_scope(
    const credential_auth_scope_t* auth_scope,
    credential_query_t** query);


/**
 * @brief Report failure of the last authentication attempt using given credentials
 * @details The authentication status for given credential is set to @c #CREDENTIAL_AUTH_STATUS_FAILED.
 *          The next time these credentials are retrieved, the user will be prompted
 *          (provided it is permitted by the prompt policy) to verify the credentials.
 *
 *
 * @param[in]   cred        The credentials used to authenticate.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_set_auth_status_failed(
    credential_t* cred);

/**
 * @brief Retrieve the result of the last authentication attempt using given credentials
 * @details Retrieve the authentication result for the given credential stored in Credential Manager.
 *
 * @param[in]   cred        The credentials of interest.
 * @param[out]  status      The result of the last authentication attempt.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_get_auth_status(
    const credential_t* cred,
    credential_auth_status_t* status);

__END_DECLS

#endif // CREDENTIAL_AUTH_H_

__SRCVERSION( "$URL$ $Rev$" )