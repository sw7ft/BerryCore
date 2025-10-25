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
 * @file credential_return.h
 *
 * This header file defines the result codes returned by
 * Credential Manager operations.
 */

#ifndef CREDENTIAL_RETURN_H_
#define CREDENTIAL_RETURN_H_

#include <stddef.h>

__BEGIN_DECLS

/** Result code for credential manager operation. */
typedef int credential_return_t;

/*============= Common return codes ==============*/
/** Success */
#define CREDENTIAL_E_OK              0x0000

/** Feature is not implemented. */
#define CREDENTIAL_E_NOT_IMPLEMENTED 0xFFFE

/** Operation failed due to an unknown cause. */
#define CREDENTIAL_E_FAIL            0xFFFF

/*============= Common error codes ==============*/

/** One of the parameters passed a NULL value */
#define CREDENTIAL_E_NULL_PARAMS     0xE101

/** One of the parameters has an invalid value */
#define CREDENTIAL_E_BAD_PARAMS      0xE103

/** Operation is not allowed due to insufficient privileges */
#define CREDENTIAL_E_FORBIDDEN       0xE104

/** Operation is not supported */
#define CREDENTIAL_E_NOT_SUPPORTED   0xE105

/** Resource is not found */
#define CREDENTIAL_E_NOT_FOUND       0xE106

/** Device locked */
#define CREDENTIAL_E_LOCKED          0xE107

/*============= Common failure ==============*/

/** Failed to allocate memory. */
#define CREDENTIAL_E_FAIL_ALLOC      0xF001

/** Failed to acquire mutex lock. */
#define CREDENTIAL_E_FAIL_LOCK       0xF003

/*============= Common database error codes ==============*/

/** Failed to open database. */
#define CREDENTIAL_E_DB_OPEN         0xE201

/** No column returned. */
#define CREDENTIAL_E_DB_NO_COLUMN    0xE202

/** Operation not permitted. */
#define CREDENTIAL_E_DB_NOT_ALLOWED  0xE203

/** No row returned. */
#define CREDENTIAL_E_DB_NO_ROW       0xE204

/*============= Common ipc error codes ==============*/

/** Failed to open service. */
#define CREDENTIAL_E_IPC_OPEN        0xE301

/** Failed to send msg. */
#define CREDENTIAL_E_IPC_SEND        0xE302

/** Failed on receive msg. */
#define CREDENTIAL_E_IPC_RECEIVE     0xE303

/** No message available. */
#define CREDENTIAL_E_IPC_NO_MSG      0xE304

/** Failed to encode/decode message. */
#define CREDENTIAL_E_IPC_CODEC       0xE305
#define CREDENTIAL_E_IPC_ENCODE      CREDENTIAL_E_IPC_CODEC

/** Return a description for the input result code.
 *
 * @param[in]   result  The result code to look up the description for.
 *
 * @retval pointer to a string containing the description of the return code
 */
extern
const char*
credential_error_desc(int result);

__END_DECLS

#endif // CREDENTIAL_RETURN_H_

__SRCVERSION( "$URL$ $Rev$" )