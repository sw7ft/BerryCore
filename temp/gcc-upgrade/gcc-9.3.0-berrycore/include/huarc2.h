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
/* $Id: huarc2.h 36652 2008-03-14 19:59:06Z jgallant $
 * $Source$
 * $Name$
 */
#ifndef HUARC2_H
#define HUARC2_H

/** @file */

#ifdef __cplusplus
extern "C" {
#endif

#include "sbdef.h"

/** @addtogroup hu_arc2_api ARC2 APIs
 *
 * @{
 */

/** Modes of operation */
#define SB_ARC2_ECB    1
#define SB_ARC2_CBC    2
#define SB_ARC2_CFB64  3
#define SB_ARC2_OFB64  4

/** Block length */
#define SB_ARC2_BLOCK_SIZE  8
#define SB_ARC2_IV_SIZE     8

/** Key length and strength */
#define SB_ARC2_MAX_KEY_SIZE                    128
#define SB_ARC2_MAX_DEFAULT_EFFECTIVE_KEY_BITS  32
#define SB_ARC2_MAX_EFFECTIVE_KEY_BITS          1024


/** Creates an ARC2 parameters object.

The mode of operation and effective key length must be specified. An RNG
context and/or yielding context must be supplied if key generation and/or
yielding will be performed, respectively.

@param[in]  mode               The mode of operation. The acceptable values are 
                               <tt>SB_ARC2_ECB</tt>, <tt>SB_ARC2_CBC</tt>, 
			       <tt>SB_ARC2_CFB64</tt> or <tt>SB_ARC2_OFB64</tt>.
			       <tt>0</tt> is also acceptable since some adapters
			       support <tt>hu_ARC2BeginV2()</tt>.
@param[in]   effectiveKeyBits  The length (in bits) of the effective key 
                               strength. The maximum allowable length is 
			       <tt>SB_ARC2_MAX_EFFECTIVE_KEY_BITS</tt>.
@param[in]   rngContext        An RNG context. (Optional - set to <tt>NULL</tt> 
                               if key generation will not be performed.)
@param[in]   yieldCtx          The yield context. (Optional - set to 
                               <tt>NULL</tt> if yielding is not required.)
@param[out]  arc2Params        The ARC2 parameters object pointer.
@param[in]   sbCtx             A global context.

@retval SB_ERR_BAD_MODE        The mode of operation is invalid.
@retval SB_ERR_BAD_INPUT       <tt>effectiveKeyBits</tt> is an invalid 
                               effective key strength.
@retval SB_ERR_NULL_PARAMS_PTR The <tt>arc2Params</tt> parameters object 
                               pointer is <tt>NULL</tt>.
@retval SB_FAIL_ALLOC          Memory allocation failure.
@retval SB_SUCCESS             Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ARC2ParamsCreate(
    int mode,
    size_t effectiveKeyBits,
    sb_RNGCtx rngContext,
    sb_YieldCtx yieldCtx,
    sb_Params *arc2Params,
    sb_GlobalCtx sbCtx
);


/** Retrieves settings from an ARC2 parameters object.

@param[in]   arc2Params        The ARC2 parameters object.
@param[out]  mode              The mode of operation.
@param[out]  effectiveKeyBits  The length (in bits) of the effective key 
                               strength.
@param[in]  sbCtx              A global context.

@retval SB_ERR_NULL_PARAMS     The <tt>arc2Params</tt> parameters object is 
                               <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS      
@retval SB_ERR_NULL_OUTPUT_BUF All output pointers are <tt>NULL</tt>.
@retval SB_SUCCESS             Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ARC2ParamsGet(
    sb_Params arc2Params,
    int *mode,
    size_t *effectiveKeyBits,
    sb_GlobalCtx sbCtx
);


/** Destroys an ARC2 parameters object.

ARC2 contexts and key objects must be destroyed before their corresponding
ARC2 parameters object is destroyed.

@param[in,out] arc2Params  The ARC2 parameters object pointer.
@param[in]     sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS_PTR The <tt>arc2Params</tt> parameters object 
                               pointer is <tt>NULL</tt>.
@retval SB_ERR_NULL_PARAMS     The <tt>arc2Params</tt> parameters object is 
                               <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS      
@retval SB_SUCCESS             Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ARC2ParamsDestroy(
   sb_Params *arc2Params,
   sb_GlobalCtx sbCtx
);


/** Creates an ARC2 key object from the given key value that can later be
used for encryption and/or decryption.

@param[in]   arc2Params  The ARC2 parameters object.
@param[in]   keyLen      The length (in bytes) of the ARC2 key value. The 
                         maximum allowable length is 
			 <tt>SB_ARC2_MAX_KEY_SIZE</tt>.
@param[in]   keyValue    The key value.
@param[out]  arc2Key     An ARC2 key object pointer.
@param[in]   sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS The <tt>arc2Params</tt> parameters object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS     
@retval SB_ERR_BAD_KEY_LEN    <tt>keyLen</tt> is an invalid key length.
@retval SB_ERR_NULL_INPUT_BUF <tt>keyValue</tt> is <tt>NULL</tt>.
@retval SB_ERR_NULL_KEY_PTR   The <tt>arc2Key</tt> key object pointer is 
                              <tt>NULL</tt>.
@retval SB_FAIL_ALLOC         Memory allocation failure.
@retval SB_SUCCESS            Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ARC2KeySet(
    sb_Params arc2Params,
    size_t keyLen,
    const unsigned char *keyValue,
    sb_Key *arc2Key,
    sb_GlobalCtx sbCtx
);


/** Creates an ARC2 key object of the specified length from random data that
can later be used for encryption and/or decryption.

The ARC2 parameter object must have been created with an RNG context.

@param[in]   arc2Params  An ARC2 parameters object.
@param[in]   keyLen      The length (in bytes) of the ARC2 key value. The 
                         maximum allowable length is 
			 <tt>SB_ARC2_MAX_KEY_SIZE</tt>.
@param[out]  arc2Key     The ARC2 key object pointer.
@param[in]   sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS  The <tt>arc2Params</tt> parameters object is 
                            <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS   
@retval SB_ERR_BAD_KEY_LEN  <tt>keyLen</tt> is an invalid key length.
@retval SB_ERR_NULL_KEY_PTR The <tt>arc2Key</tt> key object pointer is 
                            <tt>NULL</tt>.
@retval SB_FAIL_ALLOC       Memory allocation failure.
@retval SB_SUCCESS          Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ARC2KeyGen(
    sb_Params arc2Params,
    size_t keyLen,
    sb_Key *arc2Key,
    sb_GlobalCtx sbCtx
);


/** Retrieves the key value and its length from an ARC2 key object.

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

@param[in]     arc2Params  An ARC2 parameters object.
@param[in]     arc2Key     An ARC2 key object.
@param[in,out] keyLen      The length (in bytes) of the ARC2 key value.
@param[out]    keyValue    The key value.
@param[in]     sbCtx       A global context.

@retval SB_ERR_NULL_KEY           The <tt>arc2Key</tt> key object is 
                                  <tt>NULL</tt>.
@retval SB_ERR_BAD_KEY            The <tt>arc2Key</tt> key object is invalid.
@retval SB_ERR_NULL_KEY_LEN       <tt>keyLen</tt> is <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN <tt>keyLen</tt>, the key value buffer length,
                                  is invalid.
@retval SB_SUCCESS                Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ARC2KeyGet(
    sb_Params arc2Params,
    sb_Key arc2Key,
    size_t *keyLen,
    unsigned char *keyValue,
    sb_GlobalCtx sbCtx
);


/** Destroys an ARC2 key object.

ARC2 contexts must be destroyed before any ARC2 key objects. ARC2 parameter
objects must be destroyed after ARC2 key objects.

@param[in]     arc2Params The ARC2 parameters object.
@param[in,out] arc2Key    The ARC2 key object pointer.
@param[in]     sbCtx      A global context.

@retval SB_ERR_NULL_PARAMS  The <tt>arc2Params</tt> parameters object is 
                            <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS   
@retval SB_ERR_NULL_KEY_PTR The <tt>arc2Key</tt> key object pointer is 
                            <tt>NULL</tt>.
@retval SB_ERR_NULL_KEY     The <tt>arc2Key</tt> key object is <tt>NULL</tt>.
@retval SB_ERR_BAD_KEY      The <tt>arc2Key</tt> key object is invalid.
@retval SB_SUCCESS          Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ARC2KeyDestroy(
    sb_Params arc2Params,
    sb_Key *arc2Key,
    sb_GlobalCtx sbCtx
);


/** Creates an ARC2 context initialized with the given parameters and key
that can later be used for encryption and/or decryption.

An initial vector, <tt>iv</tt>, is required for the <tt>SB_ARC2_CBC</tt>, 
<tt>SB_ARC2_CFB64</tt> and <tt>SB_ARC2_OFB64</tt> modes of operation. 
<tt>iv</tt> is ignored for <tt>SB_ARC2_ECB</tt>, since that mode does not 
require an initial vector.

@param[in]   arc2Params   An ARC2 parameters object.
@param[in]   arc2Key      An ARC2 key object.
@param[in]   ivLen        The length (in bytes) of the initial vector. The 
                          only acceptable value is <tt>SB_ARC2_IV_SIZE</tt>.
@param[in]   iv           The initial vector.
@param[out]  arc2Context  The ARC2 context object pointer.
@param[in]   sbCtx        A global context.

@retval SB_ERR_NULL_PARAMS      The <tt>arc2Params</tt> parameters object is 
                                <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS       
@retval SB_ERR_NULL_KEY         The <tt>arc2Key</tt> key object is 
                                <tt>NULL</tt>.
@retval SB_ERR_BAD_KEY          The <tt>arc2Key</tt> key object is invalid.
@retval SB_ERR_NULL_IV          The initial vector, <tt>iv</tt>, is 
                                <tt>NULL</tt>.
@retval SB_ERR_BAD_IV_LEN       <tt>ivLen</tt> is an invalid initial vector 
                                length.
@retval SB_ERR_NULL_CONTEXT_PTR The <tt>arc2Context</tt> context object pointer
                                is <tt>NULL</tt>.
@retval SB_ERR_NO_MODE          No mode has been specified.
@retval SB_FAIL_ALLOC           Memory allocation failure.
@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ARC2Begin(
    sb_Params arc2Params,
    sb_Key arc2Key,
    size_t ivLen,
    const unsigned char *iv,
    sb_Context *arc2Context,
    sb_GlobalCtx sbCtx
);

/** Creates an ARC2 context initialized with the given parameters, with the
ability to override the mode in the parameters, and key that can later be used
for encryption and/or decryption.

An initial vector, <tt>iv</tt>, is required for the 
<tt>SB_ARC2_CBC</tt>, <tt>SB_ARC2_CFB64</tt> and
<tt>SB_ARC2_OFB64</tt> modes of operation. <tt>iv</tt> is ignored for 
<tt>SB_ARC2_ECB</tt>, as an initial vector is not required for that mode.

@param[in]   arc2Params   An ARC2 parameters object.
@param[in]   arc2Key      An ARC2 key object.
@param[in]   mode         The mode of operation. The acceptable values are 
                          <tt>SB_ARC2_ECB</tt>, <tt>SB_ARC2_CBC</tt>, 
			  <tt>SB_ARC2_CFB64</tt> and <tt>SB_ARC2_OFB64</tt>.
			  Specifying <tt>0</tt> will use the mode from the 
			  parameters object.
@param[in]   ivLen        The length (in bytes) of the initial vector. The 
                          only acceptable value is <tt>SB_ARC2_IV_SIZE</tt>.
@param[in]   iv           The initial vector.
@param[out]  arc2Context  The ARC2 context object pointer.
@param[in]   sbCtx        A global context.

@retval SB_ERR_NULL_PARAMS      The <tt>arc2Params</tt> parameters object is 
                                <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS       
@retval SB_ERR_NULL_KEY         The <tt>arc2Key</tt> key object is 
                                <tt>NULL</tt>.
@retval SB_ERR_BAD_KEY          The <tt>arc2Key</tt> key object is invalid.
@retval SB_ERR_NULL_IV          The initial vector, <tt>iv</tt>, is 
                                <tt>NULL</tt>.
@retval SB_ERR_BAD_IV_LEN       <tt>ivLen</tt> is an invalid initial vector 
                                length.
@retval SB_ERR_NULL_CONTEXT_PTR The <tt>arc2Context</tt> context object 
                                pointer is <tt>NULL</tt>.
@retval SB_ERR_NO_MODE          No mode has been specified.
@retval SB_FAIL_ALLOC           Memory allocation failure.
@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ARC2BeginV2(
    sb_Params arc2Params,
    sb_Key arc2Key,
    int mode,
    size_t ivLen,
    const unsigned char *iv,
    sb_Context *arc2Context,
    sb_GlobalCtx sbCtx
);

/** Encrypts one or more blocks of plaintext using the given ARC2 context.

The plaintext and ciphertext buffers must be the same length, and may overlap
in memory subject to the constraints described in the API Reference section
on overlapping buffers. This function can be called repeatedly to encrypt
more blocks of plaintext.

@param[in]   arc2Context  An ARC2 context object.
@param[in]   length       The length (in bytes) of plaintext. The acceptable 
                          values are multiples of <tt>SB_ARC2_BLOCK_SIZE</tt>.
@param[in]   plaintext    The plaintext buffer.
@param[out]  ciphertext   The ciphertext buffer.
@param[in]   sbCtx        A global context.

@retval SB_ERR_NULL_CONTEXT      The <tt>arc2Context</tt> context object is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT       The <tt>arc2Context</tt> context object is 
                                 invalid.
@retval SB_ERR_NULL_INPUT_BUF    The <tt>plaintext</tt> plaintext buffer is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN The <tt>plaintext</tt> plaintext buffer length
                                 is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF   The <tt>ciphertext</tt> ciphertext buffer is 
                                 <tt>NULL</tt>.
@retval SB_SUCCESS               Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ARC2Encrypt(
    sb_Context arc2Context,
    size_t length,
    const unsigned char *plaintext,
    unsigned char *ciphertext,
    sb_GlobalCtx sbCtx
);


/** Decrypts one or more blocks of ciphertext using the given ARC2 context.

The plaintext and ciphertext buffers must be the same length, and may overlap
in memory subject to the constraints described in the API Reference section
on overlapping buffers. This function can be called repeatedly to decrypt
more blocks of ciphertext.

@param[in]   arc2Context  An ARC2 context object.
@param[in]   length       The length (in bytes) of ciphertext. The acceptable
                          values are multiples of <tt>SB_ARC2_BLOCK_SIZE</tt>.
@param[in]   ciphertext   The ciphertext buffer.
@param[out]  plaintext    The plaintext buffer.
@param[in]   sbCtx        A global context.

@retval SB_ERR_NULL_CONTEXT      The <tt>arc2Context</tt> context object is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT       The <tt>arc2Context</tt> context object is 
                                 invalid.
@retval SB_ERR_NULL_INPUT_BUF    The <tt>ciphertext</tt> ciphertext buffer is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN The <tt>ciphertext</tt> ciphertext buffer 
                                 length is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF   The <tt>plaintext</tt> plaintext buffer is 
                                 <tt>NULL</tt>.
@retval SB_SUCCESS               Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ARC2Decrypt(
   sb_Context arc2Context,
   size_t length,
   const unsigned char *ciphertext,
   unsigned char *plaintext,
   sb_GlobalCtx sbCtx
);


/** Destroys an ARC2 context object.

This function must be called to terminate an encryption or decryption
operation. An ARC2 context must be destroyed before the corresponding ARC2
key object and ARC2 parameters object are destroyed.

@param[in,out] arc2Context  An ARC2 context object pointer.
@param[in]     sbCtx        A global context.

@retval SB_ERR_NULL_CONTEXT_PTR The <tt>arc2Context</tt> context object pointer
                                is <tt>NULL</tt>.
@retval SB_ERR_NULL_CONTEXT     The <tt>arc2Context</tt> context object is 
                                <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT      The <tt>arc2Context</tt> context object is 
                                invalid.
@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ARC2End(
    sb_Context *arc2Context,
    sb_GlobalCtx sbCtx
);


/** Encrypts a plaintext buffer using the given ARC2 parameters and key.

An initial vector, <tt>iv</tt>, is required for the <tt>SB_ARC2_CBC</tt>, 
<tt>SB_ARC2_CFB64</tt> and <tt>SB_ARC2_OFB64</tt> modes of operation. 
<tt>iv</tt> is ignored for <tt>SB_ARC2_ECB</tt>, as an initial vector is not 
required for that mode. 

The plaintext and ciphertext buffers must be the same length, and may overlap
in memory subject to the constraints described in the API Reference section
on overlapping buffers.

This function should only be called for blocks of plaintext and ciphertext
that can be stored entirely in memory.

@param[in]   arc2Params  An ARC2 parameters object.
@param[in]   arc2Key     An ARC2 key object.
@param[in]   ivLen       The length (in bytes) of initial vector. The only 
                         acceptable value is <tt>SB_ARC2_IV_SIZE</tt>.
@param[in]   iv          The initial vector.
@param[in]   length      The length (in bytes) of plaintext. The acceptable 
                         values are multiples of <tt>SB_ARC2_BLOCK_SIZE</tt>.
@param[in]   plaintext   The plaintext buffer.
@param[out]  ciphertext  The ciphertext buffer.
@param[in]   sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS       The <tt>arc2Params</tt> parameters object is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS  
@retval SB_ERR_NULL_KEY          The <tt>arc2Key</tt> key object is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_KEY           The <tt>arc2Key</tt> key object is invalid.
@retval SB_ERR_NULL_IV           The initial vector, <tt>iv</tt>, is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_IV_LEN        <tt>ivLen</tt> is an invalid initial vector 
                                 length.
@retval SB_ERR_NULL_INPUT_BUF    The <tt>plaintext</tt> plaintext buffer is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN The <tt>plaintext</tt> plaintext buffer length 
                                 is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF   The <tt>ciphertext</tt> ciphertext buffer is 
                                 <tt>NULL</tt>.
@retval SB_SUCCESS               Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ARC2EncryptMsg(
    sb_Params arc2Params,
    sb_Key arc2Key,
    size_t ivLen,
    const unsigned char *iv,
    size_t length,
    const unsigned char *plaintext,
    unsigned char *ciphertext,
    sb_GlobalCtx sbCtx
);


/** Decrypts a ciphertext buffer using the given ARC2 parameters and key.

An initial vector, <tt>iv</tt>, is required for the <tt>SB_ARC2_CBC</tt>, 
<tt>SB_ARC2_CFB64</tt> and <tt>SB_ARC2_OFB64</tt> modes of operation. 
<tt>iv</tt> is ignored for <tt>SB_ARC2_ECB</tt>, as an initial vector is not 
required for that mode. 

The plaintext and ciphertext buffers must be the same length, and may overlap
in memory subject to the constraints described in the API Reference section
on overlapping buffers.

<em>Note</em>: This function should only be called for blocks of plaintext and 
ciphertext that can be stored entirely in memory.

@param[in]  arc2Params  An ARC2 parameters object.
@param[in]  arc2Key     An ARC2 key object.
@param[in]  ivLen       The length (in bytes) of initial vector. The only 
                        acceptable value is <tt>SB_ARC2_IV_SIZE</tt>.
@param[in]  iv          The initial vector.
@param[in]  length      The length (in bytes) of ciphertext. The acceptable 
                        values are multiples of <tt>SB_ARC2_BLOCK_SIZE</tt>.
@param[in]  ciphertext  The ciphertext buffer.
@param[out] plaintext   The plaintext buffer.
@param[in]  sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS    The <tt>arc2Params</tt> parameters object is 
                              <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS   
@retval SB_ERR_NULL_KEY       The <tt>arc2Key</tt> key object is <tt>NULL</tt>.
@retval SB_ERR_BAD_KEY        The <tt>arc2Key</tt> key object is invalid.
@retval SB_ERR_NULL_IV        The initial vector, <tt>iv</tt>, is <tt>NULL</tt>.
@retval SB_ERR_BAD_IV_LEN     <tt>ivLen</tt> is an invalid initial vector 
                              length.
@retval SB_ERR_NULL_INPUT_BUF The <tt>ciphertext</tt> ciphertext buffer is 
                              <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN The <tt>ciphertext</tt> ciphertext buffer 
                                 length is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF   The <tt>plaintext</tt> plaintext buffer is 
                                 <tt>NULL</tt>.
@retval SB_SUCCESS               Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ARC2DecryptMsg(
    sb_Params arc2Params,
    sb_Key arc2Key,
    size_t ivLen,
    const unsigned char *iv,
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
