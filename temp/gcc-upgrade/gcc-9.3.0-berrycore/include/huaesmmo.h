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
/* $Id: huaesmmo.h 36652 2008-03-14 19:59:06Z jgallant $
 * $Source$
 * $Name$
 */
#ifndef HUAESMMO_H
#define HUAESMMO_H
/** @file */

#ifdef __cplusplus
extern "C" {
#endif

#include "sbdef.h"
#include "huaes.h"
/** @addtogroup hu_aes_mmo_api AES MMO APIs
 *
 * @{
 */

#define SB_AESMMO_DIGEST_LEN SB_AES_128_BLOCK_BYTES



/** Creates an AES MMO hash context object.

<em>Note</em>: Yielding is not supported for message digest operations.

@param[in]  digestLen    The length (in bytes) of an AES MMO hash digest. The 
                         only acceptable value is <tt>SB_AESMMO_DIGEST_LEN</tt>.
@param[in]  yieldCtx     Ignored.
@param[out] hashContext  The AES MMO context object pointer.
@param[in]  sbCtx        A global context.

@retval SB_ERR_BAD_DIGEST_LEN   <tt>digestLen</tt> is an invalid digest length.
@retval SB_ERR_NULL_CONTEXT_PTR The <tt>hashContext</tt> object pointer is 
                                <tt>NULL</tt>.
@retval SB_FAIL_ALLOC           Memory allocation failure.
@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_AESMMOBegin(
    size_t digestLen,
    sb_YieldCtx yieldCtx,
    sb_Context *hashContext,
    sb_GlobalCtx sbCtx
);


/** Updates an AES MMO hash context with the given data.

@param[in]  hashContext The AES MMO hash context object.
@param[in]  messageLen  The length (in bytes) of the data.
@param[in]  messageData The data buffer.
@param[in]  sbCtx       A global context.

@retval SB_ERR_NULL_CONTEXT    The <tt>hashContext</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT     The <tt>hashContext</tt> object is invalid.
@retval SB_ERR_NULL_INPUT_BUF  The <tt>messageData</tt> data buffer is 
                               <tt>NULL</tt>.
@retval SB_ERR_BAD_MESSAGE_LEN The message length is too large. Total message 
                               size must be less than 65536 bits.
@retval SB_SUCCESS             Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_AESMMOHash(
    sb_Context hashContext,
    size_t messageLen,
    const unsigned char *messageData,
    sb_GlobalCtx sbCtx
);


/** Completes the message digest operation by generating the digest
and destroying the AES MMO hash context object.

@param[in,out] hashContext  The AES MMO hash context object pointer.
@param[out]    digest       The message digest buffer. The length (in bytes) of 
                            the buffer must be at least 
			    <tt>SB_AESMMO_DIGEST_LEN</tt>.
@param[in]  sbCtx           A global context.

@retval SB_ERR_NULL_CONTEXT_PTR The <tt>hashContext</tt> object pointer is 
                                <tt>NULL</tt>.
@retval SB_ERR_NULL_CONTEXT     The <tt>hashContext</tt> object is 
                                <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT      The <tt>hashContext</tt> object is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF  The message digest buffer is <tt>NULL</tt>.
@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_AESMMOEnd(
    sb_Context *hashContext,
    unsigned char *digest,
    sb_GlobalCtx sbCtx
);


/** Generates the AES MMO hash message digest for the given data.

<em>Note</em>: Yielding is not supported for message digest operations.

<em>Note</em>: This function should only be called for data that can be stored 
entirely in memory.

@param[in]  digestLen    The length (in bytes) of an AES MMO hash digest. The 
                         only acceptable value is <tt>SB_AESMMO_DIGEST_LEN</tt>.
@param[in]  yieldCtx     Ignored.
@param[in]  messageLen   The length (in bytes) of the data.
@param[in]  messageData  The data buffer.
@param[out] digest       The message digest buffer. The length (in bytes) of the
                         buffer must be at least <tt>SB_AESMMO_DIGEST_LEN</tt>.
@param[in]  sbCtx        A global context.

@retval SB_ERR_BAD_DIGEST_LEN  The length of the digest, <tt>messageLen</tt>, 
                               is invalid.
@retval SB_ERR_NULL_INPUT_BUF  The <tt>messageData</tt> data buffer is 
                               <tt>NULL</tt>.
@retval SB_ERR_NULL_OUTPUT_BUF <tt>digest</tt>, the message digest buffer, is 
                               <tt>NULL</tt>.
@retval SB_ERR_BAD_MESSAGE_LEN The message length is too large. Total message 
                               size must be less than 65536 bits.
@retval SB_SUCCESS             Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_AESMMOMsg(
    size_t digestLen,
    sb_YieldCtx yieldCtx,
    size_t messageLen,
    const unsigned char *messageData,
    unsigned char *digest,
    sb_GlobalCtx sbCtx
);


/** Generates the message digest from the data that has been updated
to the given AES MMO hash context.

<em>Note</em>: This function does not change the state of the context object.

@param[in,out] hashContext  The AES MMO hash context object.
@param[out]    digest       The message digest buffer. The length (in bytes) of 
                            the buffer must be at least 
			    <tt>SB_AESMMO_DIGEST_LEN</tt>.
@param[in]  sbCtx           A global context.

@retval SB_ERR_NULL_CONTEXT    The <tt>hashContext</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT     The <tt>hashContext</tt> object is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF The message digest buffer is <tt>NULL</tt>.
@retval SB_SUCCESS             Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_AESMMODigestGet(
    sb_Context hashContext,
    unsigned char *digest,
    sb_GlobalCtx sbCtx
);


/** Resets the given AES MMO hash context so it can be reused.

<em>Note</em>: This function returns the state of the context to the same state
as a context created after a call to <tt>hu_AESMMOBegin()</tt>.

@param[out] hashContext  The AES MMO context object.
@param[in]  sbCtx        A global context.

@retval SB_ERR_NULL_CONTEXT The <tt>hashContext</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT  The <tt>hashContext</tt> object is invalid.
@retval SB_SUCCESS          Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_AESMMOCtxReset(
    sb_Context hashContext,
    sb_GlobalCtx sbCtx
);


/** @} */

#ifdef __cplusplus
}
#endif

#endif
