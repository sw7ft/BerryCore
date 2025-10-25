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
 * @file credential_policy.h
 *
 * This header file defines policies that can be enforced on credentials
 * managed by Credential Manager.
 */

#ifndef CREDENTIAL_POLICY_H_
#define CREDENTIAL_POLICY_H_

#include <stddef.h>
#include <sys/credential_store.h>

__BEGIN_DECLS

/**
 * Management policy flags
 */
typedef enum {
    /**
     * Indicates that associated credential can't be exported via plug-in API.
     * By default, credentials are eligible for export.
     */
    CREDENTIAL_MGMT_POLICY_FLAG_DISALLOW_EXPORT = 1 << 0,

    /**
     * Indicates that associated credential can't be included in device backup.
     * By default, credentials will be included in device backup.
     */
    CREDENTIAL_MGMT_POLICY_FLAG_DISALLOW_BACKUP = 1 << 1
} credential_mgmt_policy_t;

/**
 * Management policy flag mask
 */
typedef unsigned int credential_mgmt_policy_mask_t;

/**
 * Owner types for credential.
 */
typedef enum {
    /**
     * Represents a user-owned credential
     */
    CREDENTIAL_OWNER_TYPE_USER        = 1,

    /**
     * Represents enterprise-owned credential
     */
    CREDENTIAL_OWNER_TYPE_ENTERPRISE  = 2,

    /**
     * Represents application-owned credential
     */
    CREDENTIAL_OWNER_TYPE_APPLICATION = 3
} credential_owner_type_t;

/**
 * Represents an access subject.
 */
typedef struct _credential_access_subject_t credential_access_subject_t;

/**
 * Access permission types.
 */
typedef enum {
    /**
     * The subject can query and read credential.
     */
    CREDENTIAL_ACCESS_PERMISSION_READ           = 1 << 0,

    /**
     * The subject can update (and delete) credentials.
     */
    CREDENTIAL_ACCESS_PERMISSION_UPDATE_DATA    = 1 << 1,

    /**
    * The subject can update credential policies.
    */
    CREDENTIAL_ACCESS_PERMISSION_UPDATE_POLICY  = 1 << 2,

    /**
     * Access permission flag that allows
     * the subject to access the raw credential.
     * In case of a password-based credential, this
     * allows the subject to read the username and password.
     */
    CREDENTIAL_ACCESS_PERMISSION_READ_RAW       = 1 << 3,

    /**
     * Access permission flag that allows
     * the subject to revoke the granted credential.
     */
    CREDENTIAL_ACCESS_PERMISSION_MANAGE_GRANTED = 1 << 4

} credential_access_permission_t;

/**
 * A bitmask that contains permission types.
 */
typedef unsigned int credential_access_permission_mask_t;

/**
 * Policy used to control user prompts
 */
typedef enum {
    /**
     * User prompts are not allowed.
     */
    CREDENTIAL_USER_PROMPT_POLICY_ALLOW_NONE       = 1 << 0,

    /**
     * User can be prompted for credentials.
     * For example, if a credential query did not produce any results.
     */
    CREDENTIAL_USER_PROMPT_POLICY_ALLOW_SOLICIT    = 1 << 1,

    /**
     * User can be prompted to resolve credential conflicts.
     * For example, if a credential query produced multiple results.
     */
    CREDENTIAL_USER_PROMPT_POLICY_ALLOW_RESOLVE    = 1 << 2,

    /**
     * User can be prompted to verify credential.
     * For example, allow user to re-enter credentials that failed
     * a previous authentication attempt.
     */
    CREDENTIAL_USER_PROMPT_POLICY_ALLOW_VERIFY     = 1 << 3,

    /**
     * User credentials will be saved without confirmation prompt.
     */
    CREDENTIAL_USER_PROMPT_POLICY_SAVE_WITHOUT_CONFIRM = 1 << 4

} credential_user_prompt_policy_t;

/**
 * A bitmask that contains prompt policy types
 */
typedef unsigned int credential_user_prompt_policy_mask_t;

/**
 * Policy used to control provider operations
 */
typedef enum {
    /**
     * Provider operations are not allowed.
     */
    CREDENTIAL_PROVIDER_POLICY_DISALLOW_ALL        = 0,

    /**
     * Provider can be used to add credentials.
     */
    CREDENTIAL_PROVIDER_POLICY_ALLOW_ADD           = 1 << 0,

    /**
     * Provider can be used to update credentials.
     */
    CREDENTIAL_PROVIDER_POLICY_ALLOW_UPDATE        = 1 << 1,

    /**
     * Provider can be used to find credentials.
     */
    CREDENTIAL_PROVIDER_POLICY_ALLOW_FIND          = 1 << 2
} credential_provider_policy_t;

/**
 * A bitmask that contains provider policy types
 */
typedef unsigned int credential_provider_policy_mask_t;

/**
 * Application types
 */
typedef enum {
    /**
     * Indicates an BAR packaged application.
     */
    CREDENTIAL_APP_ACCESS_SUBJECT_TYPE_BAR          = 1 << 0,

    /**
     * Indicates a system service.
     */
    CREDENTIAL_APP_ACCESS_SUBJECT_TYPE_SYS_SERVICE  = 1 << 1
} credential_app_access_subject_type_t;

/**
 * @brief Create an access subject for the current application
 * @details This function allocates a new @c #credential_access_subject_t structure
 * and initializes it to represent the current application.
 *
 * @param[in]   flag        Unused flag, reserved for future use.
 * @param[out]  app_subject On return, a pointer to the access subject structure.
 *                          You must call @c credential_access_subject_release()
 *                          to release this structure when you're done using it.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_access_subject_create_for_current_app(
    unsigned int flag,
    credential_access_subject_t** app_subject);

/**
 * @brief Create an access subject that represents all applications
 * @details This function allocates a new @c #credential_access_subject_t structure
 * and initializes it to represent all applications.
 *
 * @param[in]   flag        Unused flag, reserved for future use.
 * @param[out]  app_subject On return, a pointer to the access subject structure.
 *                          You must call @c credential_access_subject_release()
 *                          to release this structure when you're done using it.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_access_subject_create_for_all_apps(
    unsigned int flag,
    credential_access_subject_t** app_subject);

/**
 * @brief Create an access subject for given application
 * @details This function allocates a new @c #credential_access_subject_t structure
 * and initializes it for given application.
 *
 * @param[in]   app_id      Application identifier.
 *                          For a BAR-packaged application, this is the dname.
 *                          For system services, this is the gid.
 * @param[in]   app_type    Application type.
 * @param[in]   flag        Unused flag, reserved for future use.
 * @param[out]  app_subject On return, a pointer to the access subject structure.
 *                          You must call @c credential_access_subject_release()
 *                          to release this structure when you're done using it.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_access_subject_create_for_app(
    const char* app_id,
    credential_app_access_subject_type_t app_type,
    unsigned int flag,
    credential_access_subject_t** app_subject);

/**
 * @brief Release an access subject handle
 * @details This function releases an access subject handle to return resources to the system and avoid memory leakage.
 *
 * @param[in]  subject  The handle to release.
 *
 */
extern
void
credential_access_subject_release(
    credential_access_subject_t** subject);

/**
 * @brief Update the access policy of a given credential
 * @details This function update the permission flags for the given credential for the specified access subject.
 *
 * For example, for an credential, a read-only permission can be granted to everyone,
 * or a read/write permission can be granted to a specific application.
 *
 * @param[in]   cred            The credential which is protected by the access policy.
 * @param[in]   subject         The access subject whose access permissions you wish to update.
 *                              Set this parameter to 0 to modify the global permissions.
 * @param[in]   permission      Access permission flags that should be assigned to target subject.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_set_access_policy(
    credential_t* cred,
    const credential_access_subject_t* subject,
    credential_access_permission_mask_t permission);

/**
 * @brief Update the management policy of a given credential
 * @details For example, you can specify that a specific credential cannot be exported.
 *
 * @param[in]   cred            The credential to update.
 * @param[in]   policy          The new management policy flags.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_set_mgmt_policy(
    credential_t* cred,
    credential_mgmt_policy_mask_t policy);

/** @brief Retrieve the owner type from credentials.
 * @details This function returns the owner type of given credential.
 *
 * @param[in]   cred            The credential from which to retrieve the owner type.
 * @param[out]  owner_type      The concrete owner type for given credential.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_get_owner_type(
    const credential_t* cred,
    credential_owner_type_t* owner_type);

/**
 * @brief Permanently remove all credentials that are owned by the given subject
 * @details This function deletes all credentials that belong to the given subject
 * from Credential Manager's storage.
 *
 * @param[in]   store   The store from which credentials should be removed.
 * @param[in]   subject The access subject whose credentials should be deleted.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_delete_all_for_access_subject(
    const credential_store_t* store,
    const credential_access_subject_t* subject);

/**
 * @brief Set the owner type that should be used when performing query
 * @details Specify the owner type that the input query should be restricted to when it is executed.
 *
 *  By default, the query will use @c #CREDENTIAL_OWNER_TYPE_USER.
 *
 * @param[in]   query       The query to update.
 * @param[in]   owner_type  The owner type to restrict query to.
 *
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_query_set_owner_type(
    credential_query_t* query,
    credential_owner_type_t owner_type);

/**
 * @brief Set the user prompt policy for the given input query
 * @details This function sets the user prompt policy that should be enforced if the query fails to
 *          retrieve any existing credentials.
 *
 *  By default, the query will use @c #CREDENTIAL_USER_PROMPT_POLICY_ALLOW.
 *  This implies that if target query does not find existing credentials,
 *  the user @b may be prompted.
 *
 * @param[in]   query   The query to update.
 * @param[in]   policy  The user prompt policy to apply.
 *
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_query_set_user_prompt_policy(
    credential_query_t* query,
    credential_user_prompt_policy_mask_t policy);


/**
 * @brief Set the provider policy that should be enforced
 * @details Specify which provider operations are permitted when the input query is executed.
 *
 * By default, the query will use
 * @c #CREDENTIAL_PROVIDER_POLICY_ALLOW_ADD | @c #CREDENTIAL_PROVIDER_POLICY_ALLOW_UPDATE
 * for password-based credentials and
 * @c #CREDENTIAL_PROVIDER_POLICY_DISALLOW_ALL for certificate-based credentials.
 *
 * @param[in]   query   The query to update.
 * @param[in]   policy  The provider policy to apply.
 *
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_query_set_provider_policy(
    credential_query_t* query,
    credential_provider_policy_mask_t policy);

__END_DECLS

#endif // CREDENTIAL_POLICY_H_

__SRCVERSION( "$URL$ $Rev$" )