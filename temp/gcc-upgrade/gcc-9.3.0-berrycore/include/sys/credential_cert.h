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
 * @file credential_cert.h
 *
 * This header file defines operations to create
 * and manipulate  client certificate queries.
 */

#ifndef CREDENTIAL_CERT_H_
#define CREDENTIAL_CERT_H_

#include <stddef.h>

#include <sys/credential_net.h>
#include <sys/credential_store.h>

__BEGIN_DECLS

/**
 * @brief Retrieve the certificate handle from credentials
 * @details Retrieve and return the certificate handle in a newly allocated buffer.
 *          You can use the certificate handle to configure a client certificate in the OpenSSL engine.
 *
 * @param[in]   cert                Certificate credentials record.
 * @param[out]  handle              On return, a pointer to a string containing the certificate handle.
 *                                  The string is UTF-8 encoded and null-terminated.
 *                                  You must call @c credential_util_free()
 *                                  to release this string when you are finished using it.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_cert_get_handle(
    const credential_t* cert,
    char** handle);

/**
 * @brief Retrieve the certificate fingerprint from credentials
 * @details Retrieve and return the fingerprint from the client certificate in a newly allocated buffer.
 *
 *
 * @param[in]   cert                Certificate credentials record.
 * @param[out]  fingerprint         On return, a pointer to a string containing the certificate fingerprint.
 *                                  The string is UTF-8 encoded and null-terminated.
 *                                  You must call @c credential_util_free()
 *                                  to release this string when you are finished using it.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_cert_get_fingerprint(
    const credential_t* cert,
    char** fingerprint);

/**
 * @brief Retrieve the certificate subject from credentials
 * @details Retrieve and return the subject name from the client certificate in a newly allocated buffer.
 *
 * @param[in]   cert                Certificate credentials record.
 * @param[out]  subject             On return, a pointer to a string containing the certificate subject.
 *                                  The string is UTF-8 encoded and null-terminated.
 *                                  You must call @c credential_util_free()
 *                                  to release this string when you are finished using it.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_cert_get_subject(
    const credential_t* cert,
    char** subject);

/**
 * @brief Retrieve the certificate issuer from credentials
 * @details Retrieve and return the issuer name from the client certificate in a newly allocated buffer.
 *
 * @param[in]   cert                Certificate credentials record.
 * @param[out]  issuer              On return, a pointer to a string containing the certificate issuer.
 *                                  The string is UTF-8 encoded and null-terminated.
 *                                  You must call @c credential_util_free()
 *                                  to release this string when you are finished using it.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_cert_get_issuer(
    const credential_t* cert,
    char** issuer);

__END_DECLS

#endif // CREDENTIAL_CERT_H_

__SRCVERSION( "$URL$ $Rev$" )