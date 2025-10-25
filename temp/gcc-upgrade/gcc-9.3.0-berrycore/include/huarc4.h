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
/* $Id: huarc4.h 36652 2008-03-14 19:59:06Z jgallant $ 
 * $Source$
 * $Name$
 */
#ifndef HUARC4_H
#define HUARC4_H

/** @file */

#ifdef __cplusplus
extern "C" {
#endif

#include "sbdef.h"

/** @addtogroup hu_arc4_api ARC4 APIs
 *
 * @{
 */

/** Key length */
#define SB_ARC4_MAX_KEY_LEN  256


/** Creates an ARC4 parameters object.

An RNG context and/or yielding context must be supplied if key generation
and/or yielding will be performed, respectively.

@param[in]  rngContext  An RNG context. (Optional - set to <tt>NULL</tt> if key 
                        generation will not be performed.)
@param[in]  yieldCtx    A yield context. (Optional - set to <tt>NULL</tt> if 
                        yielding is not required.)
@param[out] arc4Params  The ARC4 parameters object pointer.
@param[in]  sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS_PTR The <tt>arc4Params</tt> parameters object 
                               pointer is <tt>NULL</tt>.
@retval SB_FAIL_ALLOC          Memory allocation failure.
@retval SB_SUCCESS             Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ARC4ParamsCreate(
    sb_RNGCtx rngContext,
    sb_YieldCtx yieldCtx,
    sb_Params *arc4Params,
    sb_GlobalCtx sbCtx
);


/** Destroys an ARC4 parameters object.

ARC4 contexts and key objects must be destroyed before their corresponding
ARC4 parameters object is destroyed.

@param[in,out] arc4Params  ARC4 parameters object pointer.
@param[in]     sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS_PTR   The <tt>arc4Params</tt> parameters object 
                                 pointer is <tt>NULL</tt>.
@retval SB_ERR_NULL_PARAMS       The <tt>arc4Params</tt> parameters object is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS 
@retval SB_SUCCESS               Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ARC4ParamsDestroy(
    sb_Params *arc4Params,
    sb_GlobalCtx sbCtx
);


/** Creates an ARC4 key object from the given key value that can later be
used for encryption and/or decryption.

@param[in]  arc4Params  An ARC4 parameters object.
@param[in]  keyLen      The length (in bytes) of the ARC4 key value. The 
                        maximum allowable length is 
			<tt>SB_ARC4_MAX_KEY_LEN</tt>.
@param[in]  keyValue    The key value.
@param[out] arc4Key     The ARC4 key object pointer.
@param[in]  sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS    The <tt>arc4Params</tt> parameters object is 
                              <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS   
@retval SB_ERR_BAD_KEY_LEN    <tt>keyLen</tt> is an invalid key length.
@retval SB_ERR_NULL_INPUT_BUF Key value is <tt>NULL</tt>.
@retval SB_ERR_NULL_KEY_PTR   The <tt>arc4Key</tt> object pointer is 
                              <tt>NULL</tt>.
@retval SB_FAIL_ALLOC         Memory allocation failure.
@retval SB_SUCCESS            Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ARC4KeySet(
    sb_Params arc4Params,
    size_t keyLen,
    const unsigned char *keyValue,
    sb_Key *arc4Key,
    sb_GlobalCtx sbCtx
);


/** Creates an ARC4 key object of the specified length from random data that
can later be used for encryption and/or decryption.

The ARC4 parameter object must have been created with an RNG context.

@param[in]  arc4Params  An ARC4 parameters object.
@param[in]  keyLen      The length (in bytes) of the ARC4 key value. The 
                        maximum allowable length is 
			<tt>SB_ARC4_MAX_KEY_LEN</tt>.
@param[out] arc4Key     The ARC4 key object pointer.
@param[in]  sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS  The <tt>arc4Params</tt> parameters object is 
                            <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS   
@retval SB_ERR_BAD_KEY_LEN  <tt>keyLen</tt> is an invalid key length.
@retval SB_ERR_NULL_KEY_PTR The <tt>arc4Key</tt> object pointer is 
                            <tt>NULL</tt>.
@retval SB_FAIL_ALLOC       Memory allocation failure.
@retval SB_SUCCESS          Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ARC4KeyGen(
   sb_Params arc4Params,
   size_t keyLen,
   sb_Key *arc4Key,
   sb_GlobalCtx sbCtx
);


/** Retrieves the key value and its length from an ARC4 key object.

If the length of the key value is known, a pointer to a buffer large enough
to hold the key value should be passed in <tt>keyValue</tt> and its
length in <tt>keyLen</tt>. This function will copy the key value into
<tt>keyValue</tt> and set the actual length of the key value in
<tt>keyLen</tt>.

If <tt>keyValue</tt> is <tt>NULL</tt>, then this function will set the
correct length of the key value in <tt>keyLen</tt>.  If
<tt>keyValue</tt> is not <tt>NULL</tt> but <tt>keyLen</tt> is too
small, this function will return an error and also will set the correct length
of the key value in <tt>keyLen</tt>.

@param[in]     arc4Params  An ARC4 parameters object.
@param[in]     arc4Key     An ARC4 key object.
@param[in,out] keyLen      The length (in bytes) of the ARC4 key value.
@param[out]    keyValue    The key value.
@param[in]     sbCtx       A global context.

@retval SB_ERR_NULL_KEY           The <tt>arc4Key</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_KEY            The <tt>arc4Key</tt> object is invalid.
@retval SB_ERR_NULL_KEY_LEN       <tt>keyLen</tt> is <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN The length of the <tt>keyValue</tt> buffer is
                                  invalid.
@retval SB_SUCCESS                Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ARC4KeyGet(
   sb_Params arc4Params,
   sb_Key arc4Key,
   size_t *keyLen,
   unsigned char *keyValue,
   sb_GlobalCtx sbCtx
);


/** Destroys an ARC4 key object.

ARC4 contexts must be destroyed before any ARC4 key objects. ARC4 parameter
objects must be destroyed after ARC4 key objects.

@param[in]     arc4Params  An ARC4 parameters object.
@param[in,out] arc4Key     An ARC4 key object pointer.
@param[in]     sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS  The <tt>arc4Params</tt> parameters object is 
                            <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS   
@retval SB_ERR_NULL_KEY_PTR The <tt>arc4Key</tt> object pointer is 
                            <tt>NULL</tt>.
@retval SB_ERR_NULL_KEY     The <tt>arc4Key</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_KEY      The <tt>arc4Key</tt> object is invalid.
@retval SB_SUCCESS          Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ARC4KeyDestroy(
    sb_Params arc4Params,
    sb_Key *arc4Key,
    sb_GlobalCtx sbCtx
);


/** Creates an ARC4 context initialized with the given parameters and key
that can later be used for encryption and/or decryption.

@param[in]  arc4Params   An ARC4 parameters object.
@param[in]  arc4Key      An ARC4 key object.
@param[out] arc4Context  The ARC4 context object pointer.
@param[in]  sbCtx        A global context.

@retval SB_ERR_NULL_PARAMS      The <tt>arc4Params</tt> parameters object is 
                                <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS       
@retval SB_ERR_NULL_KEY         <tt>arc4Key</tt> is <tt>NULL</tt>.
@retval SB_ERR_BAD_KEY          <tt>arc4Key</tt> is invalid.
@retval SB_ERR_NULL_CONTEXT_PTR The <tt>sbCtx</tt> object pointer is 
                                <tt>NULL</tt>.
@retval SB_FAIL_ALLOC           Memory allocation failure.
@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ARC4Begin(
   sb_Params arc4Params,
   sb_Key arc4Key,
   sb_Context *arc4Context,
   sb_GlobalCtx sbCtx
);


/** Encrypts a plaintext buffer using the given ARC4 context.

The plaintext and ciphertext buffers must be the same length. They may point
to the same address in memory but must not otherwise overlap. This function
can be called repeatedly to encrypt more blocks of plaintext.

@param[in]  arc4Context  An ARC4 context object.
@param[in]  length       The length (in bytes) of plaintext.
@param[in]  plaintext    The plaintext buffer.
@param[out] ciphertext   The ciphertext buffer.
@param[in]  sbCtx        A global context.

@retval SB_ERR_NULL_CONTEXT      The <tt>arc4Context</tt> object is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT       The <tt>arc4Context</tt> object is invalid.
@retval SB_ERR_NULL_INPUT_BUF    The <tt>plaintext</tt> buffer is <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN The length of the <tt>plaintext</tt> buffer is
                                 invalid.
@retval SB_ERR_NULL_OUTPUT_BUF   The <tt>ciphertext</tt> buffer is 
                                 <tt>NULL</tt>.
@retval SB_SUCCESS               Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ARC4Encrypt(
    sb_Context arc4Context,
    size_t length,
    const unsigned char *plaintext,
    unsigned char *ciphertext,
    sb_GlobalCtx sbCtx
);


/** Decrypts a ciphertext buffer using the given ARC4 context.

The plaintext and ciphertext buffers must be the same length. They may point
to the same address in memory but must not otherwise overlap. This function
can be called repeatedly to decrypt more blocks of ciphertext.

@param[in]  arc4Context  An ARC4 context object.
@param[in]  length       The length (in bytes) of ciphertext.
@param[in]  ciphertext   The ciphertext buffer.
@param[out] plaintext    The plaintext buffer.
@param[in]  sbCtx        A global context.

@retval SB_ERR_NULL_CONTEXT      The <tt>arc4Context</tt> object is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT       The <tt>arc4Context</tt> object is invalid.
@retval SB_ERR_NULL_INPUT_BUF    The <tt>ciphertext</tt> buffer is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN The length of the <tt>ciphertext</tt> buffer is
                                 invalid.
@retval SB_ERR_NULL_OUTPUT_BUF   The <tt>plaintext</tt> buffer is <tt>NULL</tt>.
@retval SB_SUCCESS               Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ARC4Decrypt(
   sb_Context arc4Context,
   size_t length,
   const unsigned char *ciphertext,
   unsigned char *plaintext,
   sb_GlobalCtx sbCtx
);


/** Destroys an ARC4 context object.

This function must be called to terminate an encryption or decryption
operation. An ARC4 context must be destroyed before the corresponding ARC4
key object and ARC4 parameters object are destroyed.

@param[in,out] arc4Context  An ARC4 context object pointer.
@param[in]     sbCtx        A global context.

@retval SB_ERR_NULL_CONTEXT_PTR The <tt>arc4Context</tt> object pointer is 
                                <tt>NULL</tt>.
@retval SB_ERR_NULL_CONTEXT     The <tt>arc4Context</tt> object is 
                                <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT      The <tt>arc4Context</tt> object is invalid.
@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ARC4End(
    sb_Context *arc4Context,
    sb_GlobalCtx sbCtx
);


/** Encrypts a plaintext buffer using the given ARC4 parameters and key.

<em>Note</em>: This function should only be called for buffers of plaintext 
and ciphertext that can be stored entirely in memory.

@param[in]  arc4Params  An ARC4 parameters object.
@param[in]  arc4Key     An ARC4 key object.
@param[in]  length      The length (in bytes) of plaintext.
@param[in]  plaintext   The plaintext buffer.
@param[out] ciphertext  The ciphertext buffer.
@param[in]  sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS       The <tt>arc4Params</tt> parameters object is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS        
@retval SB_ERR_NULL_KEY          The <tt>arc4Key</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_KEY           The <tt>arc4Key</tt> object is invalid.
@retval SB_ERR_NULL_INPUT_BUF    The <tt>plaintext</tt> buffer is <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN The <tt>plaintext</tt> buffer length is 
                                 invalid.
@retval SB_ERR_NULL_OUTPUT_BUF   The <tt>ciphertext</tt> buffer is 
                                 <tt>NULL</tt>.
@retval SB_SUCCESS               Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ARC4EncryptMsg(
    sb_Params arc4Params,
    sb_Key arc4Key,
    size_t length,
    const unsigned char *plaintext,
    unsigned char *ciphertext,
    sb_GlobalCtx sbCtx
);


/** Decrypts a ciphertext buffer using the given ARC4 parameters and key.

This function should only be called for buffers of plaintext and ciphertext
that can be stored entirely in memory.

@param[in]  arc4Params  An ARC4 parameters object.
@param[in]  arc4Key     An ARC4 key object.
@param[in]  length      The length (in bytes) of ciphertext.
@param[in]  ciphertext  The ciphertext buffer.
@param[out] plaintext   The plaintext buffer.
@param[in]  sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS The <tt>arc4Params</tt> parameters object is 
                           <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS   
@retval SB_ERR_NULL_KEY          The <tt>arc4Key</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_KEY           The <tt>arc4Key</tt> object is invalid.
@retval SB_ERR_NULL_INPUT_BUF    The <tt>ciphertext</tt> buffer is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN The length of the <tt>ciphertext</tt> buffer 
                                 is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF   The plaintext buffer is <tt>NULL</tt>.
@retval SB_SUCCESS               Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ARC4DecryptMsg(
    sb_Params arc4Params,
    sb_Key arc4Key,
    size_t length,
    const unsigned char *ciphertext,
    unsigned char *plaintext,
    sb_GlobalCtx sbCtx
);


/** @} */

#ifdef __cplusplus
}
#endif

#endif
