/*
 * Copyright © 1996-2014 Certicom Corp. All rights reserved.
 * 
 * This software contains trade secrets, confidential information, and other
 * intellectual property of Certicom Corp. and its licensors. This software
 * cannot be used, reproduced, or distributed in whole or in part by any means
 * without the explicit prior consent of Certicom Corp. Such consent must arise
 * from a separate license agreement from Certicom or its licensees, as 
 * appropriate.
 * 
 * Certicom, Certicom AMS, ACC, Asset Control Core, Certicom Bar Code
 * Authentication Agent, Certicom ECC Core, Certicom Security Architecture,
 * Certicom Trusted Infrastructure, Certicom CodeSign, Certicom KeyInject,
 * ChipActivate, DieMax, Security Builder, Security Builder API, 
 * Security Builder API for .NET, Security Builder BSP, Security Builder Crypto,
 * Security Builder ETS, Security Builder GSE, Security Builder IPSec, Security
 * Builder MCE, Security Builder NSE, Security Builder PKI, Security Builder SSL
 * and SysActivate are trademarks or registered trademarks of Certicom Corp.
 * All other companies and products listed herein are trademarks or registered
 * trademarks of their respective holders.
 *
 * BlackBerry®, RIM®, Research In Motion® and related trademarks are owned by
 * Research In Motion Limited. Used under license.
 * 
 */
/* $Id: hukdf.h 36652 2008-03-14 19:59:06Z jgallant $
 * $Source$
 * $Name$
 */
#ifndef HUKDF_H
#define HUKDF_H

/** @file */

#ifdef __cplusplus
extern "C" {
#endif

#include "sbdef.h"

/** @addtogroup hu_kdf_api KDF APIs
 *
 * @{
 */

/** ID for IEEE 1363-2000 KDF1 based on SHA-1. */
#define HU_KDF_IEEE_KDF1_SHA1     1

/** ID for ANSI X9.42/X9.63 KDF based on SHA-1. */
#define HU_KDF_ANSI_SHA1          2

/** ID for ANSI X9.42/X9.63 KDF based on SHA-224. */
#define HU_KDF_ANSI_SHA224        3

/** ID for ANSI X9.42/X9.63 KDF based on SHA-256. */
#define HU_KDF_ANSI_SHA256        4

/** ID for ANSI X9.42/X9.63 KDF based on SHA-384. */
#define HU_KDF_ANSI_SHA384        5

/** ID for ANSI X9.42/X9.63 KDF based on SHA-512. */
#define HU_KDF_ANSI_SHA512        6

/** IEEE 1363a-2004 KDF2 is based on the constructions in 
ANSI X9.42-2001 and ANSI X9.63. */
#define HU_KDF_IEEE_KDF2_SHA1     HU_KDF_ANSI_SHA1
#define HU_KDF_IEEE_KDF2_SHA256   HU_KDF_ANSI_SHA256
#define HU_KDF_IEEE_KDF2_SHA384   HU_KDF_ANSI_SHA384
#define HU_KDF_IEEE_KDF2_SHA512   HU_KDF_ANSI_SHA512

/** The Concatenation Key Derivation Function (Approved Alternative 1) in
Section 5.8.1 of SP 800-56A. */
#define HU_KDF_NIST_ALT1          0x0100
#define HU_KDF_NIST_ALT1_SHA1     (HU_KDF_NIST_ALT1 | HU_KDF_ANSI_SHA1)
#define HU_KDF_NIST_ALT1_SHA224   (HU_KDF_NIST_ALT1 | HU_KDF_ANSI_SHA224)
#define HU_KDF_NIST_ALT1_SHA256   (HU_KDF_NIST_ALT1 | HU_KDF_ANSI_SHA256)
#define HU_KDF_NIST_ALT1_SHA384   (HU_KDF_NIST_ALT1 | HU_KDF_ANSI_SHA384)
#define HU_KDF_NIST_ALT1_SHA512   (HU_KDF_NIST_ALT1 | HU_KDF_ANSI_SHA512)

/** Derives a value of the requested length based on shared secret
information, suitable for use as a key value.

Additional shared information may also be given.

For the IEEE KDF1 algorithm, the requested length must be the underlying
digest algorithm's output length.

When the NIST Alternative 1 KDF is used, the underlying hash algorithm
must be registered.  If not, a not supported error for the hash algorithm
will be returned.

@param[in]  algid         A KDF algorithm. The acceptable values are one of the 
                          <tt>HU_KDF_*</tt> macros.
@param[in]  secretLen     The length (in bytes) of the shared secret data.
@param[in]  sharedSecret  The shared secret data.
@param[in]  addInfoLen    The length (in bytes) of the additional information. 
                          (Optional)
@param[in]  addInfo       Additional information. (Optional - set to 
                          <tt>NULL</tt> if not used.)
@param[in]  keyLen        The length (in bytes) of the key buffer.
@param[out] keyValue      The key buffer.
@param[in]  sbCtx         A global context.

@retval SB_ERR_KDF_BAD_ALGORITHM  The KDF algorithm identifier is invalid.
@retval SB_ERR_NULL_INPUT_BUF     The shared secret value is <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN  The length of the shared secret length is 
                                  invalid.
@retval SB_ERR_NULL_ADDINFO       The additional information value is 
                                  <tt>NULL</tt>.
@retval SB_ERR_NULL_OUTPUT_BUF    The key buffer is <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN The length of the key buffer length is 
                                  invalid.
@retval SB_SUCCESS                Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_KDFDerive(
    int algid,
    size_t secretLen,
    const unsigned char *sharedSecret,
    size_t addInfoLen,
    const unsigned char *addInfo,
    size_t keyLen,
    unsigned char *keyValue,
    sb_GlobalCtx sbCtx
);


/** @} */

#ifdef __cplusplus
}
#endif

#endif
