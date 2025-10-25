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
 * @file credential_krb5.h
 *
 * This header file defines Kerberos-based operations supported by Credential Manager.
 */

#ifndef CREDENTIAL_KRB5_H_
#define CREDENTIAL_KRB5_H_

#include <sys/credential_auth.h>

__BEGIN_DECLS

/**
 * @brief Initialize or renew a Kerberos ticket-granting ticket (TGT) for the given credential
 * @details This step is mandatory before using the given credential for Kerberos-based authentication.
 *          If the operation is successfull, Credential manager will associate the resulting TGT
 *          with the given credential, and use that TGT when Kerberos-based authentication is performed.
 *
 * @param[in]     cred              The credential to use to generate the kerberos ticket.
 * @param[in]     flag              Unused flag, reserved for future use.
 * @param[out]    result            The result of the kerberos ticket generation.
 *
 * @return 0 if operation was successful, error code otherwise.
 */
extern
int
credential_krb5_kinit(
    const credential_t* cred,
    unsigned int flag,
    credential_auth_status_t* result);

__END_DECLS

#endif // CREDENTIAL_KRB5_H_

__SRCVERSION( "$URL$ $Rev$" )