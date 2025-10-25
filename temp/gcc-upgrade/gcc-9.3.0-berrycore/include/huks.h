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
/* $Id: huks.h 42238 2011-02-03 22:07:57Z hwang $
 * $Source$
 * $Name$
 */
#ifndef HUKS_H
#define HUKS_H

/** @file */

#ifdef __cplusplus
extern "C" {
#endif

#include "sbdef.h"

/** @addtogroup hu_ks_api Key Split APIs
 *
 * @{
 */


/****************** Constants ******************/

/** Lengths for 256 bit prime */
#define SB_KS_PRIME_256_BITS 256
#define SB_KS_PRIME_256_BYTES (SB_KS_PRIME_256_BITS >> 3)

/** a 256 bit prime */
extern SB_EXPORT const unsigned char hu_ksPrime256[];



/** Creates a Key Split context initialized with the given parameters.

The behaviour of this function depends on whether <tt>secret</tt> is specified.

If <tt>secret</tt> is specified, then a brand new key splitting polynomial
is randomly generated from which shared keys can be produced. This function 
should only be called once for any given secret, after which 
<tt>hu_KSGetShare()</tt> can be called multiple times to return shares which
can be used to rebuild the polynomial in the future. Note that at least 
<tt>degree</tt> shares are required to rebuild <tt>secret</tt>, so 
<tt>hu_KSGetShare()</tt> must be called at least <tt>degree</tt> times with 
<tt>index=1, 2, .., degree (, degree+1, ...</tt>.

If <tt>secret</tt> not specified (i.e. it is set to <tt>NULL</tt>), then the 
<tt>index</tt> and <tt>share</tt> parameters from <tt>ksContext</tt> are used 
to rebuild the polynomial.

Currently, only prime bit size of 256 is supported.
Any 256-bit prime, including <tt>hu_kePrime256</tt> can be used.

@param[in]   degree     Degree of polynomial.  Degree must be greater than one.
@param[in]   primeBits  The size (in bits) of <tt>prime</tt>.
                        This value must be 256 (<tt>SB_KS_PRIME_256_BITS</tt>).
@param[in]   primeBytes The size (in bytes) of <tt>prime</tt> and 
                        <tt>secret</tt>.
                        This value must be 32 (<tt>SB_KS_PRIME_256_BYTES</tt>).
@param[in]   prime      Prime number value.
@param[in]   secret     Value of secret to split.
@param[in]   index      Array of key indexes; it must contain <tt>degree</tt>
                        elements.
@param[in]   share      Array of shares corresponding to the index array.
                        specified in <tt>index</tt>.
@param[in]   rngCtx     An RNG context object.
@param[in]   yieldCtx   A yield context object.
@param[out]  ksContext  A Key Split context pointer.
@param[in]   sbCtx      A global context.

@retval SB_ERR_BAD_PARAMETER  <tt>degree</tt> is less than two.
@retval SB_ERR_BAD_INPUT_LEN  <tt>primeBits</tt> or <tt>primeBytes</tt> is
                              incorrect.
@retval SB_ERR_NULL_INPUT_LEN <tt>prime</tt> is <tt>NULL</tt>, or
                              <tt>secret</tt> is <tt>NULL</tt> and
                              <tt>index</tt> or <tt>share</tt> is
                              <tt>NULL</tt>.
@retval SB_ERR_NULL_RNG       <tt>rngCtx</tt> is <tt>NULL</tt>.
@retval SB_ERR_NULL_CONTEXT   Key Split Context pointer is <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT      Supplied prime is not a prime, or supplied
                              secret is not less than the prime.
@retval SB_SUCCESS            Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_KSBegin(
    size_t degree,
    size_t primeBits,
    size_t primeBytes,
    const unsigned char *prime,
    const unsigned char *secret,
    const size_t *index,
    unsigned char * const *share,
    sb_RNGCtx rngCtx,
    sb_YieldCtx yieldCtx,
    sb_Context *ksContext,
    sb_GlobalCtx sbCtx
);


/** Returns the share corresponding to the index.
 
The size of output buffer specified in <tt>share</tt> must be sufficiently
large, and the size must be indicated in <tt>shareLen</tt>.

If <tt>NULL</tt> is passed in as the value of <tt>share</tt>, this function 
will return the buffer length required to store the requested <tt>share</tt>. 
The size/length of the output buffer will be returned in <tt>shareLen</tt>.

@param[in]   ksContext A Key Split context.
@param[in]   index     Index of share.  Index must be greater than zero.
@param[in]   shareLen  Size of <tt>share</tt> in bytes.
@param[in]   share     Value of share.
@param[in]   sbCtx     A global context.

@retval SB_ERR_BAD_PARAMETER       <tt>index</tt> is zero.
@retval SB_ERR_NULL_CONTEXT        Key Split context is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT         Key Split context is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF_LEN <tt>shareLen</tt> is <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN  Insufficient output buffer.
@retval SB_SUCCESS                 Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_KSGetShare(
    sb_Context ksContext,
    size_t index,
    size_t *shareLen,
    unsigned char *share,
    sb_GlobalCtx sbCtx
);


/** Recovers the secret.

The size of output buffer specified in <tt>secret</tt> must be sufficiently
large, and the size must be indicated in <tt>secretLen</tt>.

If <tt>NULL</tt> is passed in as the value of <tt>secret</tt>, this function
will return the buffer length required to store <tt>secret</tt>. The length will
be returned in <tt>secretLen</tt>. 

@param[in]   ksContext A Key Split context.
@param[in]   secretLen Size of <tt>secret</tt> in bytes.
@param[in]   secret    Value of secret.
@param[in]   sbCtx     A global context.

@retval SB_ERR_NULL_CONTEXT        Key Split context is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT         Key Split context is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF_LEN <tt>secretLen</tt> is <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN  Insufficient output buffer.
@retval SB_SUCCESS                  Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_KSGetSecret(
    sb_Context ksContext,
    size_t *secretLen,
    unsigned char *secret,
    sb_GlobalCtx sbCtx
);


/** Destroys the Key Split context.

@param[out]  ksContext A Key Split context pointer.
@param[in]   sbCtx     A global context.

@retval SB_ERR_NULL_CONTEXT_PTR Key Split context pointer is
                                <tt>NULL</tt>.
@retval SB_ERR_NULL_CONTEXT     Key Split context is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT      Key Split context is invalid.
@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_KSEnd(
    sb_Context *ksContext,
    sb_GlobalCtx sbCtx
);

#ifdef __cplusplus
}
#endif

/** @} */

#endif
