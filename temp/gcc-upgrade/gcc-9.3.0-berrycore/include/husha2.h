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
/* $Id: husha2.h 36652 2008-03-14 19:59:06Z jgallant $
 * $Source$
 * $Name$
 */
#ifndef HUSHA2_H
#define HUSHA2_H

/** @file */

#ifdef __cplusplus
extern "C" {
#endif

#include "sbdef.h"


#define SB_SHA224_DIGEST_LEN 28
#define SB_SHA256_DIGEST_LEN 32
#define SB_SHA384_DIGEST_LEN 48
#define SB_SHA512_DIGEST_LEN 64

#define SB_HMAC_SHA224_224_TAG_LEN   SB_SHA224_DIGEST_LEN
#define SB_HMAC_SHA224_112_TAG_LEN   (SB_SHA224_DIGEST_LEN/2)

#define SB_HMAC_SHA256_256_TAG_LEN   SB_SHA256_DIGEST_LEN
#define SB_HMAC_SHA256_128_TAG_LEN   (SB_SHA256_DIGEST_LEN/2)

#define SB_HMAC_SHA384_384_TAG_LEN   SB_SHA384_DIGEST_LEN
#define SB_HMAC_SHA384_192_TAG_LEN   (SB_SHA384_DIGEST_LEN/2)

#define SB_HMAC_SHA512_512_TAG_LEN   SB_SHA512_DIGEST_LEN
#define SB_HMAC_SHA512_256_TAG_LEN   (SB_SHA512_DIGEST_LEN/2)

 
/** @addtogroup hu_sha2_api SHA2 APIs
 *
 * @{
 */

/** Creates a SHA-224 context object.

<em>Note</em>: Yielding is not supported for message digest operations.

@param[in]  digestLen     The length (in bytes) of a SHA-224 digest. The only
                          acceptable value is <tt>SB_SHA224_DIGEST_LEN</tt>.
@param[in]  yieldCtx      Ignored.
@param[out] hashContext   SHA-224 context object pointer.
@param[in]  sbCtx         A global context.

@retval SB_ERR_BAD_DIGEST_LEN   <tt>digestLen</tt> is an invalid digest length.
@retval SB_ERR_NULL_CONTEXT_PTR The <tt>hmacContext</tt> object pointer is 
                                <tt>NULL</tt>.
@retval SB_FAIL_ALLOC           Memory allocation failure.
@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_SHA224Begin(
    size_t digestLen,
    sb_YieldCtx yieldCtx,
    sb_Context *hashContext,
    sb_GlobalCtx sbCtx
);


/** Updates a SHA-224 context with the given data.

@param[in] hashContext  SHA-224 context object.
@param[in] messageLen   The length (in bytes) of the data.
@param[in] messageData  The data buffer.
@param[in] sbCtx        A global context.

@retval SB_ERR_NULL_CONTEXT   The <tt>hashContext</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT    The <tt>hashContext</tt> object is invalid.
@retval SB_ERR_NULL_INPUT_BUF The data buffer, <tt>messageData</tt>, is 
                              <tt>NULL</tt>.
@retval SB_SUCCESS            Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_SHA224Hash(
    sb_Context hashContext,
    size_t messageLen,
    const unsigned char *messageData,
    sb_GlobalCtx sbCtx
);


/** Generates the message digest from the data that has been updated
to the given SHA-224 context.

This function does not change the state of the context object.

@param[in]  hashContext  SHA-224 context object.
@param[out] digest       Message digest buffer. The length (in bytes) of the 
                         buffer must be at least <tt>SB_SHA224_DIGEST_LEN</tt>.
@param[in]  sbCtx        A global context.

@retval SB_ERR_NULL_CONTEXT    The <tt>hashContext</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT     The <tt>hashContext</tt> object is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF Message digest buffer is <tt>NULL</tt>.
@retval SB_SUCCESS             Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_SHA224DigestGet(
    sb_Context hashContext,
    unsigned char *digest,
    sb_GlobalCtx sbCtx
);


/** Resets the given SHA-224 context so it can be reused.

This function returns the state of the context to the same state as
a context created after a call to <tt>hu_SHA224Begin</tt>.

@param[in] hashContext  SHA-224 context object.
@param[in] sbCtx        A global context.

@retval SB_ERR_NULL_CONTEXT The <tt>hashContext</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT  The <tt>hashContext</tt> object is invalid.
@retval SB_SUCCESS          Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_SHA224CtxReset(
    sb_Context hashContext,
    sb_GlobalCtx sbCtx
);


/** Duplicates a SHA-224 context.

This function can be used to compute the digest of multiple items of data
with identical prefixes.

@param[in]  hashContext     The original SHA-224 context object.
@param[out] newHashContext  The target SHA-224 context object pointer.
@param[in]  sbCtx           A global context.

@retval SB_ERR_NULL_CONTEXT     The original SHA-224 context object is 
                                <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT      The original SHA-224 context object is invalid.
@retval SB_ERR_NULL_CONTEXT_PTR The target SHA-224 context object pointer is 
                                <tt>NULL</tt>.
@retval SB_FAIL_ALLOC           Memory allocation failure.
@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_SHA224CtxDuplicate(
    sb_Context hashContext,
    sb_Context *newHashContext,
    sb_GlobalCtx sbCtx
);


/** Completes the message digest operation by generating the digest
and destroying the SHA-224 context object.

@param[in,out] hashContext  SHA-224 context object pointer.
@param[out]    digest       Message digest buffer. The length (in bytes) of the 
                            buffer must be at least 
                            <tt>SB_SHA224_DIGEST_LEN</tt>.
@param[in]     sbCtx        A global context.

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
hu_SHA224End(
    sb_Context *hashContext,
    unsigned char *digest,
    sb_GlobalCtx sbCtx
);


/** Generates the SHA-224 message digest for the given data.

<em>Note</em>: Yielding is not supported for message digest operations.

<em>Note</em>: This function should only be called for data that can be stored 
entirely in memory.

@param[in]  digestLen    The length (in bytes) of a SHA-224 digest. The only 
                         acceptable value is <tt>SB_SHA224_DIGEST_LEN</tt>.
@param[in]  yieldCtx     Ignored.
@param[in]  messageLen   The length (in bytes) of the data.
@param[in]  messageData  The data buffer.
@param[out] digest       Message digest buffer. The length (in bytes) of the 
                         buffer must be at least <tt>SB_SHA224_DIGEST_LEN</tt>.
@param[in]  sbCtx        A global context.

@retval SB_ERR_BAD_DIGEST_LEN  <tt>digestLen</tt> is an invalid digest length.
@retval SB_ERR_NULL_INPUT_BUF  The data buffer, <tt>messageData</tt>, is 
                               <tt>NULL</tt>.
@retval SB_ERR_NULL_OUTPUT_BUF Message digest buffer is <tt>NULL</tt>.
@retval SB_SUCCESS             Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_SHA224Msg(
    size_t digestLen,
    sb_YieldCtx yieldCtx,
    size_t messageLen,
    const unsigned char *messageData,
    unsigned char *digest,
    sb_GlobalCtx sbCtx
);


/** Creates a SHA-256 context object.

<em>Note</em>: Yielding is not supported for message digest operations.

@param[in]  digestLen    The length (in bytes) of a SHA-256 digest. The only
                         acceptable value is <tt>SB_SHA256_DIGEST_LEN</tt>.
@param[in]  yieldCtx     Ignored.
@param[out] hashContext  The SHA-256 context object pointer.
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
hu_SHA256Begin(
    size_t digestLen,
    sb_YieldCtx yieldCtx,
    sb_Context *hashContext,
    sb_GlobalCtx sbCtx
);


/** Updates a SHA-256 context with the given data.

@param[in] hashContext  A SHA-256 context object.
@param[in] messageLen   The length (in bytes) of the data.
@param[in] messageData  The data buffer.
@param[in] sbCtx        A global context.

@retval SB_ERR_NULL_CONTEXT   The <tt>hashContext</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT    The <tt>hashContext</tt> object is invalid.
@retval SB_ERR_NULL_INPUT_BUF The data buffer, <tt>messageData</tt>, is 
                              <tt>NULL</tt>.
@retval SB_SUCCESS            Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_SHA256Hash(
    sb_Context hashContext,
    size_t messageLen,
    const unsigned char *messageData,
    sb_GlobalCtx sbCtx
);


/** Generates the message digest from the data that has been updated
to the given SHA-256 context.

This function does not change the state of the context object.

@param[in]  hashContext  A SHA-256 context object.
@param[out] digest       The message digest buffer. The length (in bytes) of the
                         buffer must be at least <tt>SB_SHA256_DIGEST_LEN</tt>.
@param[in]  sbCtx        A global context.

@retval SB_ERR_NULL_CONTEXT    The <tt>hashContext</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT     The <tt>hashContext</tt> object is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF The message digest buffer is <tt>NULL</tt>.
@retval SB_SUCCESS             Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_SHA256DigestGet(
    sb_Context hashContext,
    unsigned char *digest,
    sb_GlobalCtx sbCtx
);


/** Resets the given SHA-256 context so it can be reused.

This function returns the state of the context to the same state as a context 
created after a call to <tt>hu_SHA256Begin</tt>.

@param[in] hashContext  A SHA-256 context object.
@param[in] sbCtx        A global context.

@retval SB_ERR_NULL_CONTEXT The <tt>hashContext</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT  The <tt>hashContext</tt> object is invalid.
@retval SB_SUCCESS          Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_SHA256CtxReset(
    sb_Context hashContext,
    sb_GlobalCtx sbCtx
);


/** Duplicates a SHA-256 context.

This function can be used to compute the digest of multiple items of data
with identical prefixes.

@param[in]  hashContext     The original SHA-256 context object.
@param[out] newHashContext  The target SHA-256 context object pointer.
@param[in]  sbCtx           A global context.

@retval SB_ERR_NULL_CONTEXT     The original SHA-256 context object is 
                                <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT      The original SHA-256 context object is invalid.
@retval SB_ERR_NULL_CONTEXT_PTR The target SHA-256 context object pointer is 
                                <tt>NULL</tt>.
@retval SB_FAIL_ALLOC           Memory allocation failure.
@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_SHA256CtxDuplicate(
    sb_Context hashContext,
    sb_Context *newHashContext,
    sb_GlobalCtx sbCtx
);


/** Completes the message digest operation by generating the digest
and destroying the SHA-256 context object.

@param[in,out] hashContext  The SHA-256 context object pointer.
@param[out]    digest       The message digest buffer. The length (in bytes) of 
                            the buffer must be at least 
                            <tt>SB_SHA256_DIGEST_LEN</tt>.
@param[in]     sbCtx        A global context.

@retval SB_ERR_NULL_CONTEXT_PTR   The <tt>hashContext</tt> object pointer is 
                                  <tt>NULL</tt>.
@retval SB_ERR_NULL_CONTEXT       The <tt>hashContext</tt> object is 
                                  <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT        The <tt>hashContext</tt> object is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF    The message digest buffer is <tt>NULL</tt>.
@retval SB_SUCCESS                Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_SHA256End(
    sb_Context *hashContext,
    unsigned char *digest,
    sb_GlobalCtx sbCtx
);


/** Generates the SHA-256 message digest for the given data.

<em>Note</em>: Yielding is not supported for message digest operations.

<em>Note</em>: This function should only be called for data that can be stored 
entirely in memory.

@param[in]  digestLen    The length (in bytes) of a SHA-256 digest. The only
                         acceptable value is <tt>SB_SHA256_DIGEST_LEN</tt>.
@param[in]  yieldCtx     Ignored.
@param[in]  messageLen   The length (in bytes) of the data.
@param[in]  messageData  The data buffer.
@param[out] digest       The message digest buffer. The length (in bytes) of the
                         buffer must be at least <tt>SB_SHA256_DIGEST_LEN</tt>.
@param[in]  sbCtx        A global context.

@retval SB_ERR_BAD_DIGEST_LEN  <tt>digestLen</tt> is an invalid digest length.
@retval SB_ERR_NULL_INPUT_BUF  The data buffer, <tt>messageData</tt>, is 
                               <tt>NULL</tt>.
@retval SB_ERR_NULL_OUTPUT_BUF The message digest buffer is <tt>NULL</tt>.
@retval SB_SUCCESS             Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_SHA256Msg(
    size_t digestLen,
    sb_YieldCtx yieldCtx,
    size_t messageLen,
    const unsigned char *messageData,
    unsigned char *digest,
    sb_GlobalCtx sbCtx
);


/** Creates a SHA-384 context object.

<em>Note</em>: Yielding is not supported for message digest operations.

@param[in]  digestLen    The length (in bytes) of a SHA-384 digest. The only
                         acceptable value is <tt>SB_SHA384_DIGEST_LEN</tt>.
@param[in]  yieldCtx     Ignored.
@param[out] hashContext  The SHA-384 context object pointer.
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
hu_SHA384Begin(
    size_t digestLen,
    sb_YieldCtx yieldCtx,
    sb_Context *hashContext,
    sb_GlobalCtx sbCtx
);


/** Updates a SHA-384 context with the given data.

@param[in] hashContext  A SHA-384 context object.
@param[in] messageLen   The length (in bytes) of the data.
@param[in] messageData  The data buffer.
@param[in] sbCtx        A global context.

@retval SB_ERR_NULL_CONTEXT   The <tt>hashContext</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT    The <tt>hashContext</tt> object is invalid.
@retval SB_ERR_NULL_INPUT_BUF The data buffer, <tt>messageData</tt>, is 
                              <tt>NULL</tt>.
@retval SB_SUCCESS            Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_SHA384Hash(
    sb_Context hashContext,
    size_t messageLen,
    const unsigned char *messageData,
    sb_GlobalCtx sbCtx
);


/** Generates the message digest from the data that has been updated
to the given SHA-384 context.

This function does not change the state of the context object.

@param[in]  hashContext  A SHA-384 context object.
@param[out] digest       The message digest buffer. The length (in bytes) of the
                         buffer must be at least <tt>SB_SHA384_DIGEST_LEN</tt>.
@param[in]  sbCtx        A global context.

@retval SB_ERR_NULL_CONTEXT    The <tt>hashContext</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT     The <tt>hashContext</tt> object is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF The message digest buffer is <tt>NULL</tt>.
@retval SB_SUCCESS             Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_SHA384DigestGet(
    sb_Context hashContext,
    unsigned char *digest,
    sb_GlobalCtx sbCtx
);


/** Resets the given SHA-384 context so it can be reused.

This function returns the state of the context to the same state as
a context created after a call to <tt>hu_SHA384Begin</tt>.

@param[in] hashContext  A SHA-384 context object.
@param[in] sbCtx        A global context.

@retval SB_ERR_NULL_CONTEXT The <tt>hashContext</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT  The <tt>hashContext</tt> object is invalid.
@retval SB_SUCCESS          Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_SHA384CtxReset(
    sb_Context hashContext,
    sb_GlobalCtx sbCtx
);


/** Duplicates a SHA-384 context.

This function can be used to compute the digest of multiple items of data
with identical prefixes.

@param[in]  hashContext     The original SHA-384 context object.
@param[out] newHashContext  The target SHA-384 context object pointer.
@param[in]  sbCtx           A global context.

@retval SB_ERR_NULL_CONTEXT     The original SHA-384 context object is 
                                <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT      The original SHA-384 context object is invalid.
@retval SB_ERR_NULL_CONTEXT_PTR The target SHA-384 context object pointer is 
                                <tt>NULL</tt>.
@retval SB_FAIL_ALLOC           Memory allocation failure.
@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_SHA384CtxDuplicate(
    sb_Context hashContext,
    sb_Context *newHashContext,
    sb_GlobalCtx sbCtx
);


/** Completes the message digest operation by generating the digest
and destroying the SHA-384 context object.

@param[in,out] hashContext  The SHA-384 context object pointer.
@param[out]    digest       The message digest buffer. The length (in bytes) of 
                            the buffer must be at least 
                            <tt>SB_SHA384_DIGEST_LEN</tt>.
@param[in]     sbCtx        A global context.

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
hu_SHA384End(
    sb_Context *hashContext,
    unsigned char *digest,
    sb_GlobalCtx sbCtx
);


/** Generates the SHA-384 message digest for the given data.

<em>Note</em>: Yielding is not supported for message digest operations.

<em>Note</em>: This function should only be called for data that can be stored 
entirely in memory.

@param[in]  digestLen    The length (in bytes) of a SHA-384 digest. The only
                         acceptable value is <tt>SB_SHA384_DIGEST_LEN</tt>.
@param[in]  yieldCtx     Ignored.
@param[in]  messageLen   The length (in bytes) of the data.
@param[in]  messageData  The data buffer.
@param[out] digest       The message digest buffer. The length (in bytes) of the
                         buffer must be at least <tt>SB_SHA384_DIGEST_LEN</tt>.
@param[in]  sbCtx        A global context.

@retval SB_ERR_BAD_DIGEST_LEN  <tt>digestLen</tt> is an invalid digest length.
@retval SB_ERR_NULL_INPUT_BUF  The data buffer, <tt>messageData</tt>, is 
                               <tt>NULL</tt>.
@retval SB_ERR_NULL_OUTPUT_BUF The message digest buffer is <tt>NULL</tt>.
@retval SB_SUCCESS             Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_SHA384Msg(
    size_t digestLen,
    sb_YieldCtx yieldCtx,
    size_t messageLen,
    const unsigned char *messageData,
    unsigned char *digest,
    sb_GlobalCtx sbCtx
);


/** Creates a SHA-512 context object.

<em>Note</em>: Yielding is not supported for message digest operations.

@param[in]  digestLen    The length (in bytes) of a SHA-512 digest. The only
                         acceptable value is <tt>SB_SHA512_DIGEST_LEN</tt>.
@param[in]  yieldCtx     Ignored.
@param[out] hashContext  The SHA-512 context object pointer.
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
hu_SHA512Begin(
    size_t digestLen,
    sb_YieldCtx yieldCtx,
    sb_Context *hashContext,
    sb_GlobalCtx sbCtx
);


/** Updates a SHA-512 context with the given data.

@param[in] hashContext  A SHA-512 context object.
@param[in] messageLen   The length (in bytes) of the data.
@param[in] messageData  The data buffer.
@param[in] sbCtx        A global context.

@retval SB_ERR_NULL_CONTEXT   The <tt>hashContext</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT    The <tt>hashContext</tt> object is invalid.
@retval SB_ERR_NULL_INPUT_BUF The data buffer, <tt>messageData</tt>, is 
                              <tt>NULL</tt>.
@retval SB_SUCCESS            Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_SHA512Hash(
    sb_Context hashContext,
    size_t messageLen,
    const unsigned char *messageData,
    sb_GlobalCtx sbCtx
);


/** Generates the message digest from the data that has been updated
to the given SHA-512 context.

This function does not change the state of the context object.

@param[in]  hashContext  A SHA-512 context object.
@param[out] digest       The message digest buffer. The length (in bytes) of the
                         buffer must be at least <tt>SB_SHA512_DIGEST_LEN</tt>.
@param[in]  sbCtx        A global context.

@retval SB_ERR_NULL_CONTEXT    The <tt>hashContext</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT     The <tt>hashContext</tt> object is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF The message digest buffer is <tt>NULL</tt>.
@retval SB_SUCCESS             Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_SHA512DigestGet(
    sb_Context hashContext,
    unsigned char *digest,
    sb_GlobalCtx sbCtx
);


/** Resets the given SHA-512 context so it can be reused.

This function returns the state of the context to the same state as
a context created after a call to <tt>hu_SHA512Begin()</tt>.

@param[in] hashContext  The SHA-512 context object.
@param[in] sbCtx        A global context.

@retval SB_ERR_NULL_CONTEXT The <tt>hashContext</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT  The <tt>hashContext</tt> object is invalid.
@retval SB_SUCCESS          Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_SHA512CtxReset(
    sb_Context hashContext,
    sb_GlobalCtx sbCtx
);


/** Duplicates a SHA-512 context.

This function can be used to compute the digest of multiple items of data
with identical prefixes.

@param[in]  hashContext     The original SHA-512 context object.
@param[out] newHashContext  The target SHA-512 context object pointer.
@param[in]  sbCtx           A global context.

@retval SB_ERR_NULL_CONTEXT     The original SHA-512 context object is 
                                <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT      The original SHA-512 context object is invalid.
@retval SB_ERR_NULL_CONTEXT_PTR The target SHA-512 context object pointer is 
                                <tt>NULL</tt>.
@retval SB_FAIL_ALLOC           Memory allocation failure.
@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_SHA512CtxDuplicate(
    sb_Context hashContext,
    sb_Context *newHashContext,
    sb_GlobalCtx sbCtx
);


/** Completes the message digest operation by generating the digest
and destroying the SHA-512 context object.

@param[in,out] hashContext  The SHA-512 context object pointer.
@param[out]    digest       The message digest buffer. The length (in bytes) of 
                            the buffer must be at least 
                            <tt>SB_SHA512_DIGEST_LEN</tt>.
@param[in]     sbCtx        A global context.

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
hu_SHA512End(
    sb_Context *hashContext,
    unsigned char *digest,
    sb_GlobalCtx sbCtx
);


/** Generates the SHA-512 message digest for the given data.

<em>Note</em>: Yielding is not supported for message digest operations.

<em>Note</em>: This function should only be called for data that can be stored 
entirely in memory.

@param[in]  digestLen    The length (in bytes) of a SHA-512 digest. The only
                         acceptable value is <tt>SB_SHA512_DIGEST_LEN</tt>.
@param[in]  yieldCtx     Ignored.
@param[in]  messageLen   The length (in bytes) of the data.
@param[in]  messageData  The data buffer.
@param[out] digest       The message digest buffer. The length (in bytes) of the
                         buffer must be at least <tt>SB_SHA512_DIGEST_LEN</tt>.
@param[in]  sbCtx        A global context.

@retval SB_ERR_BAD_DIGEST_LEN  <tt>digestLen</tt> is an invalid digest length.
@retval SB_ERR_NULL_INPUT_BUF  The data buffer, <tt>messageData</tt>, is 
                               <tt>NULL</tt>.
@retval SB_ERR_NULL_OUTPUT_BUF The message digest buffer is <tt>NULL</tt>.
@retval SB_SUCCESS             Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_SHA512Msg(
    size_t digestLen,
    sb_YieldCtx yieldCtx,
    size_t messageLen,
    const unsigned char *messageData,
    unsigned char *digest,
    sb_GlobalCtx sbCtx
);


/** @} */


/** @addtogroup hu_hmac_sha2_api HMAC SHA-2 APIs
 *
 * @{
 *
 */


/** Creates an HMAC-SHA-224 context object with the given key.

<em>Note</em>: Yielding is not supported for HMAC operations.

@param[in]  keyLen       The length (in bytes) of the key.
@param[in]  key          The key value.
@param[in]  yieldCtx     Ignored.
@param[out] hmacContext  The HMAC-SHA-224 context object pointer.
@param[in]  sbCtx        A global context.

@retval SB_ERR_NULL_CONTEXT_PTR The <tt>hmacContext</tt> object pointer is 
                                <tt>NULL</tt>.
@retval SB_ERR_NULL_INPUT_BUF   The <tt>key</tt> value is <tt>NULL</tt>.
@retval SB_FAIL_ALLOC           Memory allocation failure.
@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_HMACSHA224Begin(
   size_t keyLen,
   const unsigned char *key,
   sb_YieldCtx yieldCtx,
   sb_Context *hmacContext,
   sb_GlobalCtx sbCtx
);


/** Updates an HMAC-SHA-224 context with the given data.

@param[in] hmacContext  A HMAC-SHA-224 context object.
@param[in] dataBlkLen   The length (in bytes) of the data.
@param[in] dataBlk      The data buffer.
@param[in] sbCtx        A global context.

@retval SB_ERR_NULL_CONTEXT   The <tt>hmacContext</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT    The <tt>hmacContext</tt> object is invalid.
@retval SB_ERR_NULL_INPUT_BUF The data buffer, <tt>dataBlk</tt>, is 
                              <tt>NULL</tt>.
@retval SB_SUCCESS            Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_HMACSHA224Hash(
    sb_Context hmacContext,
    size_t dataBlkLen,
    const unsigned char *dataBlk,
    sb_GlobalCtx sbCtx
);


/** Generates a MAC tag without destroying the HMAC-SHA-224 context.
Sufficient buffer space for MAC tag must be supplied.

@param[in,out] hmacContext HMAC-SHA-224 context pointer.
@param[in]     tagLen      MAC tag length in bytes. This value must be between
                           <tt>SB_HMAC_SHA224_224_TAG_LEN</tt> (28) and 
                           <tt>SB_HMAC_SHA224_112_TAG_LEN</tt> (14) inclusive.
@param[out]    tag         MAC tag buffer.
@param[in]     sbCtx       SB context or memory callback data.

@retval SB_ERR_NULL_CONTEXT       Context is <tt>NULL</tt>. 
@retval SB_ERR_BAD_CONTEXT        Context is invalid. 
@retval SB_ERR_BAD_OUTPUT_BUF_LEN Length of the tag buffer is greater than 
                                  <tt>SB_HMAC_SHA224_224_TAG_LEN</tt> or less
                                  than <tt>SB_HMAC_SHA224_80_TAG_LEN</tt>. 
@retval SB_ERR_NULL_OUTPUT_BUF    Tag buffer is <tt>NULL</tt>. 
@retval SB_SUCCESS                Success. 
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_HMACSHA224TagGet(
    sb_Context hmacContext,
    size_t tagLen,
    unsigned char *tag,
    sb_GlobalCtx sbCtx
);


/** Re-initializes the existing HMAC-SHA-224 context

@param[in,out] hmacContext  HMAC-SHA-224 context.
@param[in]     sbCtx        SB context or memory callback data.

@retval SB_ERR_NULL_CONTEXT     Context is <tt>NULL</tt>. 
@retval SB_ERR_BAD_CONTEXT      Context is invalid. 
@retval SB_SUCCESS              Success. 

*/

int
SB_CALLCONV
hu_HMACSHA224CtxReset(
    sb_Context hmacContext,
    sb_GlobalCtx sbCtx
);


/** Completes the HMAC operation by generating a MAC tag of the specified
length for the given data and destroying the HMAC-SHA-224 context.

@param[in,out] hmacContext  The HMAC-SHA-224 context object pointer.
@param[in]     tagLen       The length (in bytes) of MAC tag. This value must be
                            between <tt>SB_HMAC_SHA224_112_TAG_LEN</tt> and 
                            <tt>SB_HMAC_SHA224_224_TAG_LEN</tt> inclusive.
@param[out]    tag          The MAC tag buffer.
@param[in]     sbCtx        A global context.

@retval SB_ERR_NULL_CONTEXT_PTR   The <tt>hmacContext</tt> object pointer is 
                                  <tt>NULL</tt>.
@retval SB_ERR_NULL_CONTEXT       The <tt>hmacContext</tt> object is 
                                  <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT        The <tt>hmacContext</tt> object is invalid.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN The length of the tag buffer is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF    The tag buffer is <tt>NULL</tt>.
@retval SB_SUCCESS                Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_HMACSHA224End(
    sb_Context *hmacContext,
    size_t tagLen,
    unsigned char *tag,
    sb_GlobalCtx sbCtx
);


/** Generates a MAC tag of the specified length for the given data using
HMAC-SHA-224.

<em>Note</em>: Yielding is not supported for message digest operations.

<em>Note</em>: This function should only be called for data that can be stored 
entirely in memory.

@param[in]  keyLen      The length (in bytes) of the key.
@param[in]  key         The key value.
@param[in]  yieldCtx    Ignored.
@param[in]  dataBlkLen  The length (in bytes) of the data.
@param[in]  dataBlk     The data buffer.
@param[in]  tagLen      The length (in bytes) of MAC tag. This value must be
                        between <tt>SB_HMAC_SHA224_112_TAG_LEN</tt> and 
                        <tt>SB_HMAC_SHA224_224_TAG_LEN</tt>, inclusive.
@param[out] tag         The MAC tag buffer.
@param[in]  sbCtx       A global context.

@retval SB_ERR_NULL_KEY           The key value is <tt>NULL</tt>.
@retval SB_ERR_NULL_INPUT_BUF     The data buffer, <tt>dataBlk</tt>, is 
                                  <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN The length of the tag buffer is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF    The tag buffer is <tt>NULL</tt>.
@retval SB_FAIL_ALLOC             Memory allocation failure.
@retval SB_SUCCESS                Success.
*/

int
SB_CALLCONV
hu_HMACSHA224Msg(
    size_t keyLen,
    const unsigned char *key,
    sb_YieldCtx yieldCtx,
    size_t dataBlkLen,
    const unsigned char *dataBlk,
    size_t tagLen,
    unsigned char *tag,
    sb_GlobalCtx sbCtx
);


/** Creates an HMAC-SHA-256 context object with the given key.

<em>Note</em>: Yielding is not supported for HMAC operations.

@param[in]  keyLen       The length (in bytes) of the key.
@param[in]  key          The key value.
@param[in]  yieldCtx     Ignored.
@param[out] hmacContext  The HMAC-SHA-256 context object pointer.
@param[in]  sbCtx        A global context.

@retval SB_ERR_NULL_CONTEXT_PTR The <tt>hmacContext</tt> object pointer is 
                                <tt>NULL</tt>.
@retval SB_ERR_NULL_INPUT_BUF   The <tt>key</tt> value is <tt>NULL</tt>.
@retval SB_FAIL_ALLOC           Memory allocation failure.
@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_HMACSHA256Begin(
   size_t keyLen,
   const unsigned char *key,
   sb_YieldCtx yieldCtx,
   sb_Context *hmacContext,
   sb_GlobalCtx sbCtx
);


/** Updates an HMAC-SHA-256 context with the given data.

@param[in] hmacContext  The HMAC-SHA-256 context object.
@param[in] dataBlkLen   The length (in bytes) of the data.
@param[in] dataBlk      The data buffer.
@param[in] sbCtx        A global context.

@retval SB_ERR_NULL_CONTEXT   The <tt>hmacContext</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT    The <tt>hmacContext</tt> object is invalid.
@retval SB_ERR_NULL_INPUT_BUF The data buffer, <tt>dataBlk</tt>, is 
                              <tt>NULL</tt>.
@retval SB_SUCCESS            Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_HMACSHA256Hash(
    sb_Context hmacContext,
    size_t dataBlkLen,
    const unsigned char *dataBlk,
    sb_GlobalCtx sbCtx
);


/** Generates a MAC tag without destroying the HMAC-SHA-256 context.
Sufficient buffer space for MAC tag must be supplied.

@param[in,out] hmacContext HMAC-SHA-256 context pointer.
@param[in]     tagLen      MAC tag length in bytes. This value must be between
                           <tt>SB_HMAC_SHA256_256_TAG_LEN</tt> (32) and
                           <tt>SB_HMAC_SHA256_128_TAG_LEN</tt> (16) inclusive.
@param[out]    tag         MAC tag buffer.
@param[in]     sbCtx       SB context or memory callback data.

@retval SB_ERR_NULL_CONTEXT       Context is <tt>NULL</tt>. 
@retval SB_ERR_BAD_CONTEXT        Context is invalid. 
@retval SB_ERR_BAD_OUTPUT_BUF_LEN Length of the tag buffer is greater than 
                                  <tt>SB_HMAC_SHA256_256_TAG_LEN</tt> or less
                                  than <tt>SB_HMAC_SHA256_128_TAG_LEN</tt>. 
@retval SB_ERR_NULL_OUTPUT_BUF    Tag buffer is <tt>NULL</tt>. 
@retval SB_SUCCESS                Success. 
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_HMACSHA256TagGet(
    sb_Context hmacContext,
    size_t tagLen,
    unsigned char *tag,
    sb_GlobalCtx sbCtx
);


/** Re-initializes the existing HMAC-SHA-256 context

@param[in,out] hmacContext  HMAC-SHA-256 context.
@param[in]     sbCtx        SB context or memory callback data.

@retval SB_ERR_NULL_CONTEXT     Context is <tt>NULL</tt>. 
@retval SB_ERR_BAD_CONTEXT      Context is invalid. 
@retval SB_SUCCESS              Success. 

*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_HMACSHA256CtxReset(
    sb_Context hmacContext,
    sb_GlobalCtx sbCtx
);


/** Completes the HMAC operation by generating a MAC tag of the specified
length for the given data and destroying the HMAC-SHA-256 context.

@param[in,out] hmacContext  The HMAC-SHA-256 context object pointer.
@param[in]     tagLen       The length (in bytes) of MAC tag. This value must be
                            between <tt>SB_HMAC_SHA256_128_TAG_LEN</tt> and 
                            <tt>SB_HMAC_SHA256_256_TAG_LEN</tt>, inclusive.
@param[out]    tag          The MAC tag buffer.
@param[in]     sbCtx        A global context.

@retval SB_ERR_NULL_CONTEXT_PTR   The <tt>hmacContext</tt> object pointer is 
                                  <tt>NULL</tt>.
@retval SB_ERR_NULL_CONTEXT       The <tt>hmacContext</tt> object is 
                                  <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT        The <tt>hmacContext</tt> object is invalid.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN The length of the tag buffer is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF    The tag buffer is <tt>NULL</tt>.
@retval SB_SUCCESS                Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_HMACSHA256End(
    sb_Context *hmacContext,
    size_t tagLen,
    unsigned char *tag,
    sb_GlobalCtx sbCtx
);


/** Generates a MAC tag of the specified length for the given data using
HMAC-SHA-256.

<em>Note</em>: Yielding is not supported for message digest operations.

<em>Note</em>: This function should only be called for data that can be stored 
entirely in memory.

@param[in]  keyLen      The length (in bytes) of the key.
@param[in]  key         The key value.
@param[in]  yieldCtx    Ignored.
@param[in]  dataBlkLen  The length (in bytes) of the data.
@param[in]  dataBlk     The data buffer.
@param[in]  tagLen      The length (in bytes) of MAC tag. This value must be
                        between <tt>SB_HMAC_SHA256_128_TAG_LEN</tt> and 
                        <tt>SB_HMAC_SHA256_256_TAG_LEN</tt>, inclusive.
@param[out] tag         The MAC tag buffer.
@param[in]  sbCtx       A global context.

@retval SB_ERR_NULL_KEY           The key value is <tt>NULL</tt>.
@retval SB_ERR_NULL_INPUT_BUF     The data buffer, <tt>dataBlk</tt>, is 
                                  <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN The length of the tag buffer is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF    The tag buffer is <tt>NULL</tt>.
@retval SB_FAIL_ALLOC             Memory allocation failure.
@retval SB_SUCCESS                Success.
*/

int
SB_CALLCONV
hu_HMACSHA256Msg(
    size_t keyLen,
    const unsigned char *key,
    sb_YieldCtx yieldCtx,
    size_t dataBlkLen,
    const unsigned char *dataBlk,
    size_t tagLen,
    unsigned char *tag,
    sb_GlobalCtx sbCtx
);


/** Creates an HMAC-SHA-384 context object with the given key.

<em>Note</em>: Yielding is not supported for HMAC operations.

@param[in]  keyLen       The length (in bytes) of the key.
@param[in]  key          The key value.
@param[in]  yieldCtx     Ignored.
@param[out] hmacContext  The HMAC-SHA-384 context object pointer.
@param[in]  sbCtx        A global context.

@retval SB_ERR_NULL_CONTEXT_PTR The <tt>hmacContext</tt> object pointer is 
                                <tt>NULL</tt>.
@retval SB_ERR_NULL_INPUT_BUF   The <tt>key</tt> value is <tt>NULL</tt>.
@retval SB_FAIL_ALLOC           Memory allocation failure.
@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_HMACSHA384Begin(
   size_t keyLen,
   const unsigned char *key,
   sb_YieldCtx yieldCtx,
   sb_Context *hmacContext,
   sb_GlobalCtx sbCtx
);


/** Updates an HMAC-SHA-384 context with the given data.

@param[in] hmacContext  The HMAC-SHA-384 context object.
@param[in] dataBlkLen   The length (in bytes) of the data.
@param[in] dataBlk      The data buffer.
@param[in] sbCtx        A global context.

@retval SB_ERR_NULL_CONTEXT   The <tt>hmacContext</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT    The <tt>hmacContext</tt> object is invalid.
@retval SB_ERR_NULL_INPUT_BUF The data buffer, <tt>dataBlk</tt>, is 
                              <tt>NULL</tt>.
@retval SB_SUCCESS            Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_HMACSHA384Hash(
    sb_Context hmacContext,
    size_t dataBlkLen,
    const unsigned char *dataBlk,
    sb_GlobalCtx sbCtx
);


/** Generates a MAC tag without destroying the HMAC-SHA-384 context.
Sufficient buffer space for MAC tag must be supplied.

@param[in,out] hmacContext  HMAC-SHA-384 context pointer.
@param[in]     tagLen       MAC tag length in bytes. This value must be between
                            <tt>SB_HMAC_SHA384_384_TAG_LEN</tt> (48) and
                            <tt>SB_HMAC_SHA384_192_TAG_LEN</tt> (24) inclusive.
@param[out]    tag          MAC tag buffer.
@param[in]     sbCtx        SB context or memory callback data.

@retval SB_ERR_NULL_CONTEXT       Context is <tt>NULL</tt>. 
@retval SB_ERR_BAD_CONTEXT        Context is invalid. 
@retval SB_ERR_BAD_OUTPUT_BUF_LEN Length of the tag buffer is greater than 
                                  <tt>SB_HMAC_SHA384_384_TAG_LEN</tt> or less
                                  than <tt>SB_HMAC_SHA384_80_TAG_LEN</tt>. 
@retval SB_ERR_NULL_OUTPUT_BUF    Tag buffer is <tt>NULL</tt>. 
@retval SB_SUCCESS                Success. 
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_HMACSHA384TagGet(
    sb_Context hmacContext,
    size_t tagLen,
    unsigned char *tag,
    sb_GlobalCtx sbCtx
);


/** Re-initializes the existing HMAC-SHA-384 context

@param[in,out] hmacContext  HMAC-SHA-384 context.
@param[in]     sbCtx        SB context or memory callback data.

@retval SB_ERR_NULL_CONTEXT     Context is <tt>NULL</tt>. 
@retval SB_ERR_BAD_CONTEXT      Context is invalid. 
@retval SB_SUCCESS              Success. 

*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_HMACSHA384CtxReset(
    sb_Context hmacContext,
    sb_GlobalCtx sbCtx
);


/** Completes the HMAC operation by generating a MAC tag of the specified
length for the given data and destroying the HMAC-SHA-384 context.

@param[in,out] hmacContext  HMAC-SHA-384 context object pointer.
@param[in]     tagLen       The length (in bytes) of MAC tag. This value must be
                            between <tt>SB_HMAC_SHA384_192_TAG_LEN</tt> and 
                            <tt>SB_HMAC_SHA384_384_TAG_LEN</tt>, inclusive.
@param[out]    tag          The MAC tag buffer.
@param[in]     sbCtx        A global context.

@retval SB_ERR_NULL_CONTEXT_PTR   The <tt>hmacContext</tt> object pointer is 
                                  <tt>NULL</tt>.
@retval SB_ERR_NULL_CONTEXT       The <tt>hmacContext</tt> object is 
                                  <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT        The <tt>hmacContext</tt> object is invalid.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN The length of the tag buffer is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF    The tag buffer is <tt>NULL</tt>.
@retval SB_SUCCESS                Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_HMACSHA384End(
    sb_Context *hmacContext,
    size_t tagLen,
    unsigned char *tag,
    sb_GlobalCtx sbCtx
);


/** Generates a MAC tag of the specified length for the given data using
HMAC-SHA-384.

<em>Note</em>: Yielding is not supported for message digest operations.

<em>Note</em>: This function should only be called for data that can be stored 
entirely in memory.

@param[in]  keyLen      The length (in bytes) of the key.
@param[in]  key         The key value.
@param[in]  yieldCtx    Ignored.
@param[in]  dataBlkLen  The length (in bytes) of the data.
@param[in]  dataBlk     The data buffer.
@param[in]  tagLen      The length (in bytes) of MAC tag. This value must be
                        between <tt>SB_HMAC_SHA384_192_TAG_LEN</tt> and 
                        <tt>SB_HMAC_SHA384_384_TAG_LEN</tt>, inclusive.
@param[out] tag         The MAC tag buffer.
@param[in]  sbCtx       A global context.

@retval SB_ERR_NULL_KEY           The key value is <tt>NULL</tt>.
@retval SB_ERR_NULL_INPUT_BUF     The data buffer, <tt>dataBlk</tt>, is 
                                  <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN The length of the tag buffer is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF    The tag buffer is <tt>NULL</tt>.
@retval SB_FAIL_ALLOC             Memory allocation failure.
@retval SB_SUCCESS                Success.
*/

int
SB_CALLCONV
hu_HMACSHA384Msg(
    size_t keyLen,
    const unsigned char *key,
    sb_YieldCtx yieldCtx,
    size_t dataBlkLen,
    const unsigned char *dataBlk,
    size_t tagLen,
    unsigned char *tag,
    sb_GlobalCtx sbCtx
);


/** Creates an HMAC-SHA-512 context object with the given key.

<em>Note</em>: Yielding is not supported for HMAC operations.

@param[in]  keyLen       The length (in bytes) of the key.
@param[in]  key          The key value.
@param[in]  yieldCtx     Ignored.
@param[out] hmacContext  The HMAC-SHA-512 context object pointer.
@param[in]  sbCtx        A global context.

@retval SB_ERR_NULL_CONTEXT_PTR The <tt>hmacContext</tt> object pointer is 
                                <tt>NULL</tt>.
@retval SB_ERR_NULL_INPUT_BUF   The <tt>key</tt> value is <tt>NULL</tt>.
@retval SB_FAIL_ALLOC           Memory allocation failure.
@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_HMACSHA512Begin(
   size_t keyLen,
   const unsigned char *key,
   sb_YieldCtx yieldCtx,
   sb_Context *hmacContext,
   sb_GlobalCtx sbCtx
);


/** Updates an HMAC-SHA-512 context with the given data.

@param[in] hmacContext  The HMAC-SHA-512 context object.
@param[in] dataBlkLen   The length (in bytes) of the data.
@param[in] dataBlk      The data buffer.
@param[in] sbCtx        A global context.

@retval SB_ERR_NULL_CONTEXT   The <tt>hmacContext</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT    The <tt>hmacContext</tt> object is invalid.
@retval SB_ERR_NULL_INPUT_BUF The data buffer, <tt>dataBlk</tt>, is 
                              <tt>NULL</tt>.
@retval SB_SUCCESS            Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_HMACSHA512Hash(
    sb_Context hmacContext,
    size_t dataBlkLen,
    const unsigned char *dataBlk,
    sb_GlobalCtx sbCtx
);


/** Generates a MAC tag without destroying the HMAC-SHA-512 context.
Sufficient buffer space for MAC tag must be supplied.

@param[in,out] hmacContext  HMAC-SHA-512 context pointer.
@param[in]     tagLen       MAC tag length in bytes. This value must be between
                            <tt>SB_HMAC_SHA512_512_TAG_LEN</tt> (64) and 
                            <tt>SB_HMAC_SHA512_256_TAG_LEN</tt> (32), inclusive.
@param[out]    tag          MAC tag buffer.
@param[in]     sbCtx        SB context or memory callback data.

@retval SB_ERR_NULL_CONTEXT       Context is <tt>NULL</tt>. 
@retval SB_ERR_BAD_CONTEXT        Context is invalid. 
@retval SB_ERR_BAD_OUTPUT_BUF_LEN Length of the tag buffer is greater than 
                                  <tt>SB_HMAC_SHA512_512_TAG_LEN</tt> or less
                                  than <tt>SB_HMAC_SHA512_256_TAG_LEN</tt>. 
@retval SB_ERR_NULL_OUTPUT_BUF    Tag buffer is <tt>NULL</tt>. 
@retval SB_SUCCESS                Success. 
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_HMACSHA512TagGet(
    sb_Context hmacContext,
    size_t tagLen,
    unsigned char *tag,
    sb_GlobalCtx sbCtx
);


/** Re-initializes the existing HMAC-SHA-512 context

@param[in,out] hmacContext  HMAC-SHA-512 context.
@param[in]     sbCtx        SB context or memory callback data.

@retval SB_ERR_NULL_CONTEXT     Context is <tt>NULL</tt>. 
@retval SB_ERR_BAD_CONTEXT      Context is invalid. 
@retval SB_SUCCESS              Success. 

*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_HMACSHA512CtxReset(
    sb_Context hmacContext,
    sb_GlobalCtx sbCtx
);


/** Completes the HMAC operation by generating a MAC tag of the specified
length for the given data and destroying the HMAC-SHA-512 context.

@param[in,out] hmacContext  The HMAC-SHA-512 context object pointer.
@param[in]     tagLen       The length (in bytes) of MAC tag. This value must be
                            between <tt>SB_HMAC_SHA512_256_TAG_LEN</tt> and 
                            <tt>SB_HMAC_SHA512_512_TAG_LEN</tt>, inclusive.
@param[out]    tag          The MAC tag buffer.
@param[in]     sbCtx        A global context.

@retval SB_ERR_NULL_CONTEXT_PTR   The <tt>hmacContext</tt> object pointer is 
                                  <tt>NULL</tt>.
@retval SB_ERR_NULL_CONTEXT       The <tt>hmacContext</tt> object is 
                                  <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT        The <tt>hmacContext</tt> object is invalid.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN The length of the tag buffer is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF    The tag buffer is <tt>NULL</tt>.
@retval SB_SUCCESS                Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_HMACSHA512End(
    sb_Context *hmacContext,
    size_t tagLen,
    unsigned char *tag,
    sb_GlobalCtx sbCtx
);


/** Generates a MAC tag of the specified length for the given data using
HMAC-SHA-512.

<em>Note</em>: Yielding is not supported for message digest operations.

<em>Note</em>: This function should only be called for data that can be stored entirely in
memory.

@param[in]  keyLen      The length (in bytes) of the key.
@param[in]  key         The key value.
@param[in]  yieldCtx    Ignored.
@param[in]  dataBlkLen  The length (in bytes) of the data.
@param[in]  dataBlk     The data buffer.
@param[in]  tagLen      The length (in bytes) of MAC tag. This value must be
                        between <tt>SB_HMAC_SHA512_256_TAG_LEN</tt> and 
                        <tt>SB_HMAC_SHA512_512_TAG_LEN</tt>, inclusive.
@param[out] tag         The MAC tag buffer.
@param[in]  sbCtx       A global context.

@retval SB_ERR_NULL_KEY           The key value is <tt>NULL</tt>.
@retval SB_ERR_NULL_INPUT_BUF     The data buffer, <tt>dataBlk</tt>, is 
                                  <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN The length of the tag buffer is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF    The tag buffer is <tt>NULL</tt>.
@retval SB_FAIL_ALLOC             Memory allocation failure.
@retval SB_SUCCESS                Success.
*/

int
SB_CALLCONV
hu_HMACSHA512Msg(
    size_t keyLen,
    const unsigned char *key,
    sb_YieldCtx yieldCtx,
    size_t dataBlkLen,
    const unsigned char *dataBlk,
    size_t tagLen,
    unsigned char *tag,
    sb_GlobalCtx sbCtx
);


/** @} */

#ifdef __cplusplus
}
#endif

#endif
