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
 * @file credential_pwd.h
 *
 * This header file defines operations to manipulate password-based credentials.
 */

#ifndef CREDENTIAL_PWD_H_
#define CREDENTIAL_PWD_H_

#include <sys/credential_store.h>
#include <sys/credential_policy.h>

__BEGIN_DECLS

/**
 * @brief Create and save a new password credentials record
 * @details This function allocates a new @c #credential_t structure,
 * initializes it with the input password credential details,
 * and saves it in Credential Manager.
 *
 * @param[in]   account_label       An account label. This is a UTF-8 encoded string used to identify the credentials
 *                                  to user in UI.
 * @param[in]   account_name        Account name. This is a A UTF-8 encoded string used to identify the account principle
 *                                  (for example, username, email).
 * @param[in]   password            A UTF-8 encoded string that contains the password.
 * @param[in]   owner_type          The owner type to be used when creating credential.
 * @param[in]   store               The store where the new credential record should be saved.
 * @param[out]  cred                (Optional) On return, a pointer to the credential structure.
 *                                  You must call @c credential_release() to release this structure when you're done using it.
 *                                  If set to @c #NULL, then it will not be initialized on return.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_pwd_create(
    const char* account_label,
    const char* account_name,
    const char* password,
    credential_owner_type_t owner_type,
    const credential_store_t* store,
    credential_t** cred);

/**
 * @brief Retrieve account label from credentials
 * @details This function retrieves and returns the account label from the
 * password-based credential in a newly allocated buffer.
 *
 * @param[in]   cred                Password credentials record.
 * @param[out]  account_label       On return, a pointer to a string containing account label.
 *                                  The string is UTF-8 encoded and null-terminated.
 *                                  You must call @c credential_util_free()
 *                                  to release this string when you're done using it.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_pwd_get_account_label(
    const credential_t* cred,
    char** account_label);

/**
 * @brief Update the account label in a credential record
 * @details This function updates the in-memory copy of the password-based credential
 * with the new account label.
 *
 * You must invoke @c credential_pwd_update() to persist the account label update.
 *
 * @param[in]   cred                Password-based credential to update.
 * @param[in]   account_label       A UTF-8 encoded and null-terminated string that contains the account label.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
int
credential_pwd_set_account_label(
    credential_t* cred,
    const char* account_label);

/**
 * @brief Retrieve account name from the password-based credentials
 * @details This function retrieves and returns the account name for the given
 * password-based credential. The account name is returned in a newly allocated buffer.
 *
 * @param[in]   cred                Password-based credentials record.
 * @param[out]  account_name        On return, a pointer a string containing account name.
 *                                  The string is UTF-8 encoded and null-terminated.
 *                                  You must call @c credential_util_free()
 *                                  to release this string when you're done using it.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_pwd_get_account_name(
    const credential_t* cred,
    char** account_name);

/**
 * @brief Update the account name in a password-based credential record
 * @details This function updates the in-memory copy of the password-based credential
 * with the new account name.
 *
 * You must invoke @c credential_pwd_update() to persist the changes.
 *
 * @param[in]   cred                The password-based credential to update.
 * @param[in]   account_name        A UTF-8 encoded string that contains the account name.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_pwd_set_account_name(
    credential_t* cred,
    const char* account_name);

/**
 * @brief Retrieve the password of a credential
 * @details This function retrieves and returns the password from the given credential.
 * The password is returned in a newly allocated buffer.
 *
 * @param[in]   cred                The password-based credential.
 * @param[out]  password            On return, a pointer to a string containing password.
 *                                  The string is UTF-8 encoded and null-terminated.
 *                                  You must call @c credential_util_free()
 *                                  to release this string when you're done using it.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_pwd_get_password(
    const credential_t* cred,
    char** password);

/**
 * @brief Update the credential password
 * @details This function updates the in-memory copy of the credential with the new password.
 *
 * You must invoke @c credential_pwd_update() to persist the changes.
 *
 * @param[in]   cred                The password-based credential to update.
 * @param[in]   password            A UTF-8 encoded and null-terminated string that contains the password.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_pwd_set_password(
    credential_t* cred,
    const char* password);

__END_DECLS

#endif // CREDENTIAL_PWD_H_

__SRCVERSION( "$URL$ $Rev$" )