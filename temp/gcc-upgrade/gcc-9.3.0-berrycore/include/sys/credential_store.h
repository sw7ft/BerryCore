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
 * @file credential_store.h
 *
 * This header file defines operations to manipulate the Credential Manager store.
 */

#ifndef CREDENTIAL_STORE_H_
#define CREDENTIAL_STORE_H_

#include <stdbool.h>
#include <stddef.h>

__BEGIN_DECLS

/**
 * This structure represents a Credential Manager store.
 */
typedef struct _credential_store_t credential_store_t;

/**
 * This structure represents an credential in a Credential Manager store.
 */
typedef struct _credential_t credential_t;

/**
 * This structure represents an credential query.
 */
typedef struct _credential_query_t credential_query_t;

/**
 * This structure represents a result of an credential query.
 */
typedef struct _credential_query_result_t credential_query_result_t;

/**
 * This structure represents an credential iterator.
 */
typedef struct _credential_iterator_t credential_iterator_t;

/**
 * This enumeration defines the types of device perimeters.
 * Hybrid applications @b must explicitly specify the Credential Manager perimeter.
 * All other applications @b must use the @c #CREDENTIAL_STORE_PERIMETER_TYPE_DEFAULT
 * to indicate the current application perimeter.
 */
typedef enum {
    /**
     * Indicates default or current application perimeter.
     */
    CREDENTIAL_STORE_PERIMETER_TYPE_DEFAULT          = 0,

    /**
     * Indicates personal perimeter.
     */
    CREDENTIAL_STORE_PERIMETER_TYPE_PERSONAL         = 1,

    /**
     * Indicates enterprise perimeter.
     */
    CREDENTIAL_STORE_PERIMETER_TYPE_ENTERPRISE       = 2,

    /**
     * Indicates the number of unique values in perimeter type enumeration.
     */
    CREDENTIAL_STORE_PERIMETER_TYPE_LAST
} credential_store_perimeter_t;

/**
 * An enumeration of the ADARP (Advanced Data At Rest Protection) domain types.
 */
typedef enum {
    /**
     * Indicates lock data area; accessible only when perimeter is unlocked.
     */
    CREDENTIAL_STORE_ADARP_DOMAIN_LOCK        = 0,

    /**
     * Indicates operational data area; accessible only after first user login.
     */
    CREDENTIAL_STORE_ADARP_DOMAIN_OPERATIONAL = 1,

    /**
     * Indicates startup data area; accessible only after device boot.
     */
    CREDENTIAL_STORE_ADARP_DOMAIN_STARTUP     = 2,

    /**
     * Indicates the number of unique values in ADARP domain enumeration.
     */
    CREDENTIAL_STORE_ADARP_DOMAIN_LAST
} credential_store_adarp_domain_t;

/**
 * Credential Manager credential type.
 * This enumeration defines the concrete types for stored credentials.
 */
typedef enum {
    /**
     * Reserved value that represents any credential type.
     * This value can only be used in credential queries.
     */
    CREDENTIAL_TYPE_ANY           = 0,

    /**
     * Indicates a password-based credential.
     */
    CREDENTIAL_TYPE_PASSWORD_CRED = 1 << 0,

    /**
     * Indicates a certificate-based credential.
     */
    CREDENTIAL_TYPE_CLIENT_CERT   = 1 << 1
} credential_type_t;

/**
 * An enumeration of possible termination conditions for a credential query.
 */
typedef enum {
    /**
     * Indicates that credential query has completed normally.
     */
    CREDENTIAL_QUERY_STATUS_OK = 0,

    /**
     * Indicates that credential query was canceled.
     */
    CREDENTIAL_QUERY_STATUS_CANCEL = 1
} credential_query_status_t;

/**
 * A convenience reference to the default perimeter store.
 * This store reference is thread-safe.
 */
extern const credential_store_t* CREDENTIAL_STORE_DEFAULT;

/**
 * @brief Open a Credential Manager store with default ADARP lock domain
 * @details This function opens a Credential Manager store for the given perimeter using the default
 *          ADARP lock domain.
 *
 * @param[in]   perimeter       The perimeter where the store is persisted.
 * @param[out]  store           On return, a pointer to the store structure.
 *                              You must call @c credential_store_close()
 *                              to release this structure when you're done using it.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_perimeter_store_open(
    credential_store_perimeter_t perimeter,
    credential_store_t** store);

/**
 * @brief Open a Credential Manager store for a specific ADARP domain
 * @details This function opens a Credential Manager store for the given perimeter and ADARP domain.
 *
 * @param[in]   perimeter       The perimeter where the store is persisted.
 * @param[in]   domain          The ADARP domain governing store accessibility.
 * @param[out]  store           On return, a pointer to the store structure.
 *                              You must call @c credential_store_close()
 *                              to release this structure when you're done using it.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_perimeter_adarp_store_open(
    credential_store_perimeter_t perimeter,
    credential_store_adarp_domain_t domain,
    credential_store_t** store);

/**
 * @brief Open a temporary Credential Manager store
 * @details This function opens a temporary nested Credential Manager store, using the optional @c main_store
 *          as fallback.
 *
 * @param[in]   main_store      The store used when credential queries in the temporary store return no results.
 *                              This is an optional argument and can be set to 0.
 * @param[out]  store           On return, a pointer to the store structure.
 *                              You must call @c credential_store_close()
 *                              to release this structure when you're done using it.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_store_create_temporary(
    const credential_store_t* main_store,
    credential_store_t** store);

/**
 * @brief Close a store
 * @details This function closes the Credential Manager store and releases the memory allocated for the store.
 *
 * @param[in]   store   The store to close.
 */
extern
void
credential_store_close(
    credential_store_t** store);

/**
 * @brief Retrieve the concrete credential type
 * @details This function returns the type of given credential.
 *
 * @param[in]   cred  The credential from which to retrieve the type.
 * @param[out]  type  The concrete type for given credential.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_get_type(
    const credential_t* cred,
    credential_type_t* type);

/**
 * @brief Permanently remove an credential from Credential Manager
 * @details This function deletes the credential from Credential Manager's storage.
 *
 * This function does not release in-memory credential structure.
 *
 * @param[in]   cred    The credential you wish to permanently remove.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_delete(
    credential_t* cred);

/**
 * @brief Retrieve a handle representation of the credential
 * @details This function retrieves an opaque handle that
 * uniquely identifies the given credential. The handle is returned in a newly allocated buffer.
 *
 * The handle is an opaque buffer that can be used to:
 * - save a reference to the credential in offline storage
 * - pass a reference to the credential over the wire
 * - pass a reference to the credential through components that are unaware of Credential Manager
 *
 * @param[in]   cred        The credential to convert to a handle.
 * @param[out]  handle      On return, a pointer to buffer that contains credential handle.
 *                          You must call @c credential_util_free()
 *                          to release this buffer when you're done using it.
 * @param[out]  handle_sz   On return, the size (in bytes) of the buffer that contains credential handle.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_to_handle(
    const credential_t* cred,
    unsigned char** handle,
    size_t* handle_sz);

/**
 * @brief Retrieve a string representation of credential handle
 * @details This function retrieves a string representation of the of the credential handle.
 * The handle string is returned in a newly allocated buffer.
 *
 * This is a convenience function that encodes the result of @c credential_to_handle()
 * into a null terminated string.
 *
 * This function is more expensive than @c credential_to_handle() and should be used
 * only if caller cannot process the credential handle as a buffer and needs a null-terminated string.
 *
 * @param[in]   cred        The credential to convert to a handle string.
 * @param[out]  handle_str  On return, a pointer to a string containing encoded credential handle.
 *                          The string is ASCII encoded and null-terminated.
 *                          You must call @c credential_util_free()
 *                          to release this string when you're done using it.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_to_handle_string(
    const credential_t* cred,
    char** handle_str);

/**
 * @brief Create an credential from its handle representation
 * @details This function allocates a new @c #credential_t structure,
 * and initializes it represent the same credential as the handle.
 *
 * @param[in]   handle      A pointer to buffer that contains credential handle.
 * @param[in]   handleSz    The size (in bytes) of the handle buffer.
 * @param[out]  cred        The credential that corresponds to the given handle.
 *                          You must call @c credential_release() to release this structure when you're done using it.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_from_handle(
    const unsigned char* handle,
    size_t handle_sz,
    credential_t** cred);

/**
 * @brief Create an credential from its encoded handle representation
 * @details This function allocates a new @c #credential_t structure
 * and initializes it to represent the same credential as the handle string.
 *
 * This is a convenience function that decodes the credential handle from a string
 * created by @c credential_to_handle_string()
 *
 * @param[in]   handle_str  ASCII encoded string that contains the encoded credential handle.
 * @param[out]  cred        Credential that corresponds to the given handle.
 *                          You must call @c credential_release() to release this structure when you're done using it.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_from_handle_string(
    const char* handle_str,
    credential_t** cred);

/**
 * @brief Create a clone of the given credential
 * @details This function allocates a new @c #credential_t structure,
 * and initializes a deep copy of the attributes of the given credential.
 *
 * Changes to a cloned credential will not be reflected in the original, and vice versa.
 *
 * @param[in]   cred        The credential to clone.
 * @param[in]   clone       On return, a pointer to a cloned credential.
 *                          You must call @c credential_release()
 *                          to release this structure when you're done using it.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_clone(
    const credential_t* cred,
    credential_t** clone);

/**
 * @brief Release an credential handle
 * @details This function releases an credential handle to return resources to the system and avoid memory leakage.
 *
 * @param[in]  cred  The handle to release.
 */
extern
void
credential_release(
    credential_t** cred);

/**
 * @brief Indicate whether the iteration has more credentials
 * @details This function queries the credential iterator and returns @c #true if more credentials are available,
 * and returns @c #false if there are no more credentials left.
 *
 * @param[in]   iter    Credential iteration.
 *
 * @return @c #true if iteration has more credentials,
 *         @c #false otherwise.
 */
extern
bool
credential_iterator_has_next(
    const credential_iterator_t* iter);

/**
 * @brief Return the next credential of an iteration
 * @details This function queries the credential iterator and returns the next available credential.
 * The returned credential is owned by the credential iterator and its memory will be released when the credential iterator is released.
 *
 * @param[in]   iter    Credential iteration.
 * @param[out]  cred    On return, a pointer to the next credential in iteration.  If no more credentials are available,
 *                      then this pointer will be set to 0.
 *                      The memory for the returned credential is owned by the credential iterator.
 *                      If you need a private copy of the credential, call @c credential_clone() to create a copy.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_iterator_next(
    credential_iterator_t* iter,
    credential_t** cred);

/**
 * @brief Release an credential iterator handle
 * @details This function releases an credential iterator and credentials stored in the iterator.
 *
 * This is done to return resources to the system and to avoid memory leakage.
 *
 * @param[in]  iter  The handle to release.
 */
extern
void
credential_iterator_release(
    credential_iterator_t** iter);

/**
 * @brief Set the window group that should be used for user prompts
 * @details This function sets the window group that owns the dialog when a user is prompted.
 *
 * By default, no window group id will be stored.
 *
 * @param[in]   query           The query to update.
 * @param[in]   windowGroupId   The window group id to use when prompting.
 *
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_query_set_window_group_id(
    credential_query_t* query,
    const char* window_group_id);

/**
 * @brief Set the credential type that should be used when performing query
 * @details Specify the credential type that the input query should be restricted to when it is executed.
 *
 *  By default, the query will use @c #CREDENTIAL_TYPE_ANY.
 *  This implies that query result may include credential of any type.
 *
 * @param[in]   query   The query to update.
 * @param[in]   type    The credential type to set.
 *
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_query_set_cred_type(
    credential_query_t* query,
    credential_type_t type);

/**
 * @brief Lookup credentials using given query
 * @details Using the input query values, search within Credential Manager and return all credentials
 *          which match the input criteria.  Allocates a new @c #credential_query_result_t structure
 *          and initializes with query status and any credentials returned for query.
 *
 * @param[in]     store             The store where you want to perform the query.
 * @param[in]     query             The query to execute.
 * @param[out]    result            On return, a pointer to query result.
 *                                  You must call @c credential_query_result_release()
 *                                  to release the credential structure passed as arguments to the callback.
 *                                  when you're done using it.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_find(
    const credential_store_t* store,
    const credential_query_t* query,
    credential_query_result_t** result);

/**
 * @brief Release a structure that represents an credential query
 * @details This is done to return resources to the system and to avoid memory leakage.
 *
 * @param[in]  query  The handle to release.
 */
extern
void
credential_query_release(
    credential_query_t** query);

/**
 * @brief Retrieve an iterator for credentials in query result
 * @details This function extracts the returned credentials from the query result and
 * stores them in a newly allocated @c #credential_iterator_t stucture.
 *
 * @param[in]     result            The credential query result.
 * @param[out]    credIter          On return, a pointer to iterator for query results.
 *                                  You must call @c credential_iterator_release()
 *                                  to release the credential structure passed as arguments to the callback.
 *                                  when you're done using it.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_query_result_get_iterator(
    const credential_query_result_t* result,
    credential_iterator_t** credIter);

/**
 * @brief Retrieve the first credential from query result
 * @details This is a convenience function that returns the first credential from a query result.
 * The returned credential is owned by the query result and will be released when the query result is released.
 *
 * @param[in]     result            The credential query result.
 * @param[out]    cred              On return, a pointer to the first credential in iteration.
 *                                  If query did not produce any results, then this pointer will be set to 0.
 *                                  The memory for the returned credential is owned by the underlying query result.
 *                                  If you need a private copy of the credential, call @c credential_close() to create a copy.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_query_result_get_first(
    const credential_query_result_t* result,
    credential_t** cred);

/**
 * @brief Retrieve the termination reason for an credential query
 * @details This function returns the completion status of the query.
 *
 * For example, if the user is prompted for their credentials, but they hit cancel instead,
 * @c #CREDENTIAL_QUERY_STATUS_CANCEL status would be returned.
 *
 * @param[in]     result            The credential query result.
 *
 * @return The termination reason for credential query.
 */
extern
credential_query_status_t
credential_query_result_get_status(
    const credential_query_result_t* result);

/**
 * @brief Release a structure that represents an credential query result
 * @details This is done to return resources to the system and to avoid memory leakage.
 *
 * @param[in]  result  The handle to release.
 */
extern
void
credential_query_result_release(
    credential_query_result_t** result);

/**
 * @brief Release memory
 *
 * @param[in]   ptr     Pointer to the memory to be freed.
 */
extern
void
credential_util_free(
    void* ptr);

__END_DECLS

#endif // CREDENTIAL_STORE_H_

__SRCVERSION( "$URL$ $Rev$" )