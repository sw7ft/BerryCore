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
 * @credential_client.h
 *
 * This header file defines operations to initialize and clean up
 * the Credential Manager client library.
 */

#ifndef CREDENTIAL_CLIENT_H_
#define CREDENTIAL_CLIENT_H_

#include <stdbool.h>
#include <stddef.h>

__BEGIN_DECLS

/**
 * Enumeration of logger types supported by client
 */
typedef enum {
    /**
     * slog2 based logger, that reuses the log buffer already setup by application.
     */
    CREDENTIAL_LOG_TARGET_SLOG2_REUSE_BUFFER,

    /**
     * slog2 based logger, that creates a new log buffer.
     *
     */
    CREDENTIAL_LOG_TARGET_SLOG2_CREATE_BUFFER,

    /**
     * Logger that prints to standard output
     */
    CREDENTIAL_LOG_TARGET_STDIO
} credential_log_target_t;

/**
 * @brief Indicate whether Credential Manager is available on this platform
 *
 * The Credential Manager is not provided on all platforms.
 * Clients can use this function to check if Credential Manager is available on this platform.
 * If Credential manager is not available on this platform, all other Credential Manager API functions
 * will return @c #CREDMGR_ERR_NOT_IMPLEMENTED or @c #false.
 *
 * @return @c #true if the Credential Manager is available on this platform,
 *         @c #false otherwise.
 */
extern
bool
credential_client_is_available(
    void);

/**
 * @brief Initialize the Credential Manager client library
 *
 * You must call this function before invoking any of the Credential Manager API functions.
 * Calling this function multiple times does not have any effect.
 *
 * @param[in]   log_target  The type of logger that should be used by client.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_client_initialize(
    credential_log_target_t log_target);

__END_DECLS

#endif // CREDENTIAL_CLIENT_H_

__SRCVERSION( "$URL$ $Rev$" )