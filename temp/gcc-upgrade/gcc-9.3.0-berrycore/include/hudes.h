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
/* $Id: hudes.h 36652 2008-03-14 19:59:06Z jgallant $
 * $Source$
 * $Name$
 */
#ifndef HUDES_H
#define HUDES_H

/** @file */

#ifdef __cplusplus
extern "C" {
#endif

#include "sbdef.h"

/** @addtogroup hu_des_api DES APIs
 *
 * @{
 */

/* DES algorithms */
#define SB_DES_DES   1
#define SB_DES_TDES  2 /* DES-EDE */
#define SB_DES_DESX  3

/* Modes of operation */
#define SB_DES_ECB    1
#define SB_DES_CBC    2
#define SB_DES_CFB64  3
#define SB_DES_OFB64  4

/* Key parity */
#define SB_DES_PARITY_OFF  0
#define SB_DES_PARITY_ON   1

/* Weak key detection and prevention */
#define SB_DES_WEAK_KEY_OFF  0
#define SB_DES_WEAK_KEY_ON   1

/* Block and key lengths */
#define SB_DES_BLOCK_SIZE  8
#define SB_DES_KEY_SIZE    8
#define SB_DES_IV_SIZE     8


/** Creates a DES parameters object.

The algorithm, mode of operation, key parity and weak key settings must be
specified. An RNG context and/or yielding context must be supplied if key
generation and/or yielding will be performed, respectively.

@param[in]  algorithm   The DES algorithm. The acceptable values are 
                        <tt>SB_DES_DES</tt>, <tt>SB_DES_TDES</tt> and 
			<tt>SB_DES_DESX</tt>.
@param[in]  mode        The mode of operation. The acceptable values are 
                        <tt>SB_DES_ECB</tt>, <tt>SB_DES_CBC</tt>, 
			<tt>SB_DES_CFB64</tt> and <tt>SB_DES_OFB64</tt>.  
			<tt>0</tt> is also acceptable since some adapters 
			support <tt>hu_DESBeginV2()</tt>.   
@param[in]  parity      The parity mode. The acceptable values are 
                        <tt>SB_DES_PARITY_OFF</tt> and 
			<tt>SB_DES_PARITY_ON</tt>.
@param[in]  weakKey     The weak key detection mode. The acceptable values are 
                        <tt>SB_DES_WEAK_KEY_OFF</tt> and 
			<tt>SB_DES_WEAK_KEY_ON</tt>.
@param[in]  rngContext  An RNG context. (Optional - set to <tt>NULL</tt> if key 
                        generation will not be performed.)
@param[in]  yieldCtx    A yield context. (Optional - set to <tt>NULL</tt> if 
                        yielding is not required.)
@param[out] desParams   The DES parameters object pointer.
@param[in]  sbCtx       A global context.

@retval SB_ERR_BAD_ALGORITHM   The algorithm type is invalid.
@retval SB_ERR_BAD_MODE        The mode of operation is invalid.
@retval SB_ERR_NULL_PARAMS_PTR The <tt>desParams</tt> object pointer is 
                               <tt>NULL</tt>.
@retval SB_FAIL_ALLOC          Memory allocation failure.
@retval SB_SUCCESS             Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_DESParamsCreate(
    int algorithm,
    int mode,
    int parity,
    int weakKey,
    sb_RNGCtx rngContext,
    sb_YieldCtx yieldCtx,
    sb_Params *desParams,
    sb_GlobalCtx sbCtx
);


/** Retrieves settings from a DES parameters object.

@param[in]  desParams  A DES parameters object.
@param[out] algorithm  The DES algorithm.
@param[out] mode       The mode of operation.
@param[out] parity     The key parity mode.
@param[out] weakKey    The weak key detection mode.
@param[in]  sbCtx      A global context.

@retval SB_ERR_NULL_PARAMS     The <tt>desParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS      
@retval SB_ERR_NULL_OUTPUT_BUF All output pointers are <tt>NULL</tt>.
@retval SB_SUCCESS             Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_DESParamsGet(
    sb_Params desParams,
    int *algorithm,
    int *mode,
    int *parity,
    int *weakKey,
    sb_GlobalCtx sbCtx
);


/** Destroys an DES parameters object.

DES contexts and key objects must be destroyed before their corresponding
DES parameters object is destroyed.

@param[in,out] desParams  The DES parameters object pointer.
@param[in]     sbCtx      A global context.

@retval SB_ERR_NULL_PARAMS_PTR The <tt>desParams</tt> object pointer is 
                               <tt>NULL</tt>.
@retval SB_ERR_NULL_PARAMS     The <tt>desParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS
@retval SB_SUCCESS             Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_DESParamsDestroy(
    sb_Params *desParams,
    sb_GlobalCtx sbCtx
);


/** Creates an DES key object from the given key value(s) that can later be
used for encryption and/or decryption.

If the algorithm is <tt>SB_DES_DES</tt>, a key value must be given in 
<tt>key1</tt>. The <tt>key2</tt> and <tt>key3</tt> arguments will be ignored.

If the algorithm is <tt>SB_DES_TDES</tt> or <tt>SB_DES_DESX</tt>,
all three key buffers must be given.

For <tt>SB_DES_DESX</tt>, key 1 is the encryption key, key 2 is
the prewhitening key and key 3 is the postwhitening key.

If the parity mode is <tt>SB_DES_PARITY_ON</tt>, an error will be
returned if any of the encryption keys have incorrect parity.

If the weak key mode is <tt>SB_DES_WEAK_KEY_ON</tt>, an error will
be returned if any of the encryption keys match a known weak key.

@param[in]  desParams  A DES parameters object.
@param[in]  key1Len    The length (in bytes) of <tt>key1</tt>. The only 
                       acceptable value is <tt>SB_DES_KEY_SIZE</tt>.
@param[in]  key1       Key 1 value.
@param[in]  key2Len    The length (in bytes) of <tt>key1</tt>. The only 
                       acceptable value is <tt>SB_DES_KEY_SIZE</tt>. Ignored if 
		       the mode is <tt>SB_DES_DES</tt>.
@param[in]  key2       Key 2 value. Ignored if the mode is <tt>SB_DES_DES</tt>.
@param[in]  key3Len    The length (in bytes) of <tt>key1</tt>. The only 
                       acceptable value is <tt>SB_DES_KEY_SIZE</tt>. Ignored if 
		       the mode is <tt>SB_DES_DES</tt>.
@param[in]  key3       Key 3 value. Ignored if the mode is <tt>SB_DES_DES</tt>.
@param[out] desKey     The DES key object pointer.
@param[in]  sbCtx      The global context.

@retval SB_ERR_NULL_PARAMS    The <tt>desParams</tt> parameters object is 
                              <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS
@retval SB_ERR_BAD_KEY_LEN    Key length is invalid.
@retval SB_ERR_BAD_KEY_PARITY Key value has incorrect parity.
@retval SB_ERR_WEAK_KEY       Key value is known to be weak.
@retval SB_ERR_NULL_KEY_PTR   Key object pointer is <tt>NULL</tt>.
@retval SB_FAIL_ALLOC         Memory allocation failure.
@retval SB_SUCCESS            Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_DESKeySet(
    sb_Params desParams,
    size_t key1Len,
    const unsigned char *key1,
    size_t key2Len,
    const unsigned char *key2,
    size_t key3Len,
    const unsigned char *key3,
    sb_Key *desKey,
    sb_GlobalCtx sbCtx
);


/** Creates an DES key object of the specified length from random data that
can later be used for encryption and/or decryption.

The DES parameter object must have been created with an RNG context.

If the parity mode is <tt>SB_DES_PARITY_ON</tt>, the encryption keys
will be generated with odd parity.

If the weak key mode is <tt>SB_DES_WEAK_KEY_ON</tt>, the encryption keys
will be generated such that they will not match a known weak key.

@param[in]  desParams  A DES parameters object.
@param[out] desKey     The DES key object pointer.
@param[in]  sbCtx      A global context.

@retval SB_ERR_NULL_PARAMS  The <tt>desParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS
@retval SB_ERR_NULL_KEY_PTR The <tt>desKey</tt> object pointer is <tt>NULL</tt>.
@retval SB_FAIL_ALLOC       Memory allocation failure.
@retval SB_SUCCESS          Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_DESKeyGen(
    sb_Params desParams,
    sb_Key *desKey,
    sb_GlobalCtx sbCtx
);


/** Retrieves the key values and their lengths from an DES key object.

If the length of the key value is known, a pointer to a buffer large enough
to hold the key value should be passed in <tt>keyValue</tt> and its
length in <tt>keyLen</tt>. This function will copy the key value into
<tt>keyValue</tt> and set the actual length of the key value in
<tt>keyLen</tt>.

If <tt>keyValue</tt> is <tt>NULL</tt>, then this function will set the
correct length of the key value in <tt>keyLen</tt>. If
<tt>keyValue</tt> is not <tt>NULL</tt> but <tt>keyLen</tt> is too
small, this function will return an error and also will set the correct length
of the key value in <tt>keyLen</tt>.

@param[in]     desParams  A DES parameters object.
@param[in]     desKey     A DES key object pointer.
@param[in,out] key1Len    The length (in bytes) of <tt>key1Value</tt>.
@param[out]    key1Value  Key 1 value.
@param[in,out] key2Len    The length (in bytes) of <tt>key2Value</tt>. Ignored 
                          if the mode is <tt>SB_DES_DES</tt>.
@param[out]    key2Value  Key 2 value. Ignored if the mode is 
                          <tt>SB_DES_DES</tt>.
@param[in,out] key3Len    The length (in bytes) of <tt>key3Value</tt>. Ignored 
                          if the mode is <tt>SB_DES_DES</tt>.
@param[out]    key3Value  Key 3 value. Ignored if the mode is 
                          <tt>SB_DES_DES</tt>.
@param[in]     sbCtx      A global context.

@retval SB_ERR_NULL_KEY           Key object is <tt>NULL</tt>.
@retval SB_ERR_BAD_KEY            Key object is invalid.
@retval SB_ERR_NULL_KEY_LEN       Key length is <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN Key value buffer length is invalid.
@retval SB_SUCCESS                Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_DESKeyGet(
    sb_Params desParams,
    sb_Key desKey,
    size_t *key1Len,
    unsigned char *key1Value,
    size_t *key2Len,
    unsigned char *key2Value,
    size_t *key3Len,
    unsigned char *key3Value,
    sb_GlobalCtx sbCtx
);


/** Destroys a DES key object.

DES contexts must be destroyed before any DES key objects. DES parameter
objects must be destroyed after DES key objects.

@param[in]     desParams  A DES parameters object.
@param[in,out] desKey     The DES key object pointer.
@param[in]     sbCtx      A global context.

@retval SB_ERR_NULL_PARAMS  The <tt>desParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS
@retval SB_ERR_NULL_KEY_PTR The <tt>desKey</tt> object pointer is <tt>NULL</tt>.
@retval SB_ERR_NULL_KEY     The <tt>desKey</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_KEY      The <tt>desKey</tt> object is invalid.
@retval SB_SUCCESS          Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_DESKeyDestroy(
    sb_Params desParams,
    sb_Key* desKey,
    sb_GlobalCtx sbCtx
);


/** Creates an DES context initialized with the given parameters and key
that can later be used for encryption and/or decryption.

An initial vector, <tt>iv</tt>, is required for the <tt>SB_DES_CBC</tt>, 
<tt>SB_DES_CFB64</tt> and <tt>SB_DES_OFB64</tt> modes of operation. <tt>iv</tt>
is ignored for <tt>SB_DES_ECB</tt>, as an initial vector is not required for 
that mode.

@param[in]  desParams   A DES parameters object.
@param[in]  desKey      A DES key object.
@param[in]  ivLen       The length (in bytes) of initial vector. The only 
                        acceptable value is <tt>SB_DES_IV_SIZE</tt>.
@param[in]  iv          The initial vector.
@param[out] desContext  The DES context object pointer.
@param[in]  sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS      The <tt>desParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS
@retval SB_ERR_NULL_KEY         The <tt>desKey</tt> key object is <tt>NULL</tt>.
@retval SB_ERR_BAD_KEY          The <tt>desKey</tt> key object is invalid.
@retval SB_ERR_NULL_IV          The initial vector, <tt>iv</tt>, is 
                                <tt>NULL</tt>.
@retval SB_ERR_BAD_IV_LEN       The initial vector length, <tt>ivLen</tt>, is 
                                invalid.
@retval SB_ERR_NULL_CONTEXT_PTR The <tt>sbCtx</tt> object pointer is 
                                <tt>NULL</tt>.
@retval SB_ERR_NO_MODE          No mode has been specified.
@retval SB_FAIL_ALLOC           Memory allocation failure.
@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_DESBegin(
    sb_Params desParams,
    sb_Key desKey,
    size_t ivLen,
    const unsigned char *iv,
    sb_Context *desContext,
    sb_GlobalCtx sbCtx
);


/** Creates an DES context initialized with the given parameters, with the
ability to override the mode in the parameters, and a key that can later be used
for encryption and/or decryption.

An initial vector, <tt>iv</tt>, is required for the <tt>SB_DES_CBC</tt>, 
<tt>SB_DES_CFB64</tt> and <tt>SB_DES_OFB64</tt> modes of operation. <tt>iv</tt>
is ignored for <tt>SB_DES_ECB</tt>, as an initial vector is not required for 
that mode.

@param[in]  desParams   A DES parameters object.
@param[in]  desKey      A DES key object.
@param[in]  mode        The mode of operation. The acceptable values are 
                        <tt>SB_DES_ECB</tt>, <tt>SB_DES_CBC</tt>, 
			<tt>SB_DES_CFB64</tt> and <tt>SB_DES_OFB64</tt>. 
			Specifying <tt>0</tt> will use the mode from the 
			parameters object.
@param[in]  ivLen       The length (in bytes) of initial vector. The only 
                        acceptable value is <tt>SB_DES_IV_SIZE</tt>.
@param[in]  iv          The initial vector.
@param[out] desContext  The DES context object pointer.
@param[in]  sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS      The <tt>desParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS
@retval SB_ERR_NULL_KEY         The <tt>desKey</tt> key object is <tt>NULL</tt>.
@retval SB_ERR_BAD_KEY          The <tt>desKey</tt> key object is invalid.
@retval SB_ERR_NULL_IV          The initial vector, <tt>iv</tt>, is 
                                <tt>NULL</tt>.
@retval SB_ERR_BAD_IV_LEN       The initial vector length, <tt>ivLen</tt>, is 
                                invalid.
@retval SB_ERR_NULL_CONTEXT_PTR The <tt>sbCtx</tt> object pointer is 
                                <tt>NULL</tt>.
@retval SB_ERR_NO_MODE          No mode has been specified.
@retval SB_FAIL_ALLOC           Memory allocation failure.
@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_DESBeginV2(
    sb_Params desParams,
    sb_Key desKey,
    int mode,
    size_t ivLen,
    const unsigned char *iv,
    sb_Context *desContext,
    sb_GlobalCtx sbCtx
);
/** Encrypts one or more blocks of plaintext using the given DES context.

The plaintext and ciphertext buffers must be the same length, and may overlap
in memory subject to the constraints described in the API Reference section
on overlapping buffers. This function can be called repeatedly to encrypt
more blocks of plaintext.

@param[in]  desContext  A DES context object.
@param[in]  length      The length (in bytes) of plaintext. The acceptable 
                        values are multiples of <tt>SB_DES_BLOCK_SIZE</tt>.
@param[in]  plaintext   The plaintext buffer.
@param[out] ciphertext  The ciphertext buffer.
@param[in]  sbCtx       A global context.

@retval SB_ERR_NULL_CONTEXT      The <tt>desContext</tt> object is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT       The <tt>desContext</tt> object is invalid.
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
hu_DESEncrypt(
    sb_Context desContext,
    size_t length,
    const unsigned char *plaintext,
    unsigned char *ciphertext,
    sb_GlobalCtx sbCtx
);


/** Decrypts one or more blocks of ciphertext using the given DES context.

The plaintext and ciphertext buffers must be the same length, and may overlap
in memory subject to the constraints described in the API Reference section
on overlapping buffers. This function can be called repeatedly to decrypt
more blocks of ciphertext.

@param[in]  desContext  A DES context object.
@param[in]  length      The length (in bytes) of ciphertext. The acceptable 
                        values are multiples of <tt>SB_DES_BLOCK_SIZE</tt>.
@param[in]  ciphertext  The ciphertext buffer.
@param[out] plaintext   The plaintext buffer.
@param[in]  sbCtx       A global context.

@retval SB_ERR_NULL_CONTEXT      The <tt>desContext</tt> object is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT       The <tt>desContext</tt> object is invalid.
@retval SB_ERR_NULL_INPUT_BUF    The <tt>ciphertext</tt> buffer is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN The length of the <tt>ciphertext</tt> buffer 
                                 is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF   The <tt>plaintext</tt> buffer is <tt>NULL</tt>.
@retval SB_SUCCESS               Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_DESDecrypt(
    sb_Context desContext,
    size_t length,
    const unsigned char *ciphertext,
    unsigned char *plaintext,
    sb_GlobalCtx sbCtx
);


/** Resets the given DES context so it can be reused.

@param[in]  ivLen       The length (in bytes) of initial vector. The only 
                        acceptable value is <tt>SB_DES_IV_SIZE</tt>.
@param[in]  iv          The initial vector.
@param[out] desContext  The DES context object.
@param[in]  sbCtx       A global context.

@retval SB_ERR_NULL_CONTEXT      The <tt>desContext</tt> object is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT       The <tt>desContext</tt> object is invalid.
@retval SB_ERR_NULL_IV           The initial vector, <tt>iv</tt>, is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_IV_LEN        The initial vector length, <tt>ivLen</tt>, is 
                                 invalid.
@retval SB_SUCCESS               Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_DESCtxReset(
    size_t ivLen,
    const unsigned char *iv,
    sb_Context desContext,
    sb_GlobalCtx sbCtx
);


/** Destroys an DES context object.

This function must be called to terminate an encryption or decryption
operation. A DES context must be destroyed before the corresponding DES
key object and DES parameters object are destroyed.

@param[in,out] desContext  A DES context object pointer.
@param[in]     sbCtx       A global context.

@retval SB_ERR_NULL_CONTEXT_PTR The <tt>desContext</tt> object pointer is 
                                <tt>NULL</tt>.
@retval SB_ERR_NULL_CONTEXT     The <tt>desContext</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT      The <tt>desContext</tt> object is invalid.
@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_DESEnd(
    sb_Context *desContext,
    sb_GlobalCtx sbCtx
);


/** Encrypts a plaintext buffer using the given DES parameters and key.

An initial vector is required for the <tt>SB_DES_CBC</tt>, 
<tt>SB_DES_CFB64</tt> and <tt>SB_DES_OFB64</tt> modes of operation.
<tt>iv</tt> is ignored for <tt>SB_DES_ECB</tt>, as an initial vector
is not required for that mode. The plaintext and ciphertext buffers must be 
the same length, and may overlap in memory subject to the constraints 
described in the API Reference section on overlapping buffers.

<em>Note</em>: This function should only be called for blocks of plaintext and 
ciphertext that can be stored entirely in memory.

@param[in]  desParams   A DES parameters object.
@param[in]  desKey      A DES key object.
@param[in]  ivLen       The length (in bytes) of the initial vector. The only 
                        acceptable value is <tt>SB_DES_IV_SIZE</tt>.
@param[in]  iv          The initial vector.
@param[in]  length      The length (in bytes) of plaintext. The acceptable 
                        values are multiples of <tt>SB_DES_BLOCK_SIZE</tt>.
@param[in]  plaintext   The plaintext buffer.
@param[out] ciphertext  The ciphertext buffer.
@param[in]  sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS     The <tt>desParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS
@retval SB_ERR_NULL_KEY        The <tt>desKey</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_KEY         The <tt>desKey</tt> object is invalid.
@retval SB_ERR_NULL_IV         The initial vector, <tt>iv</tt>, is 
                               <tt>NULL</tt>.
@retval SB_ERR_BAD_IV_LEN      The length of the initial vector, <tt>ivLen</tt>,
                               is invalid.
@retval SB_ERR_NULL_INPUT_BUF  The <tt>plaintext</tt> buffer is <tt>NULL</tt>. 
@retval SB_ERR_NULL_OUTPUT_BUF The <tt>ciphertext</tt> buffer is <tt>NULL</tt>.
@retval SB_SUCCESS             Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_DESEncryptMsg(
    sb_Params desParams,
    sb_Key desKey,
    size_t ivLen,
    const unsigned char *iv,
    size_t length,
    const unsigned char *plaintext,
    unsigned char *ciphertext,
    sb_GlobalCtx sbCtx
);


/** Decrypts a ciphertext buffer using the given DES parameters and key.

For the <tt>SB_DES_CBC</tt>, <tt>SB_DES_CFB64</tt> and <tt>SB_DES_OFB64</tt> 
modes of operation, an initial vector is required. <tt>iv</tt> is ignored for 
<tt>SB_DES_ECB</tt>, as an initial vector is not required for that mode. The 
plaintext and ciphertext buffers must be the same length, and may overlap in 
memory subject to the constraints described in the API Reference section on 
overlapping buffers.

<em>Note</em>: This function should only be called for blocks of plaintext and 
ciphertext that can be stored entirely in memory.

@param[in]  desParams   A DES parameters object.
@param[in]  desKey      A DES key object.
@param[in]  ivLen       The length (in bytes) of initial vector. The only 
                        acceptable value is <tt>SB_DES_IV_SIZE</tt>.
@param[in]  iv          The initial vector.
@param[in]  length      The length (in bytes) of ciphertext. The acceptable 
                        values are multiples of <tt>SB_DES_BLOCK_SIZE</tt>.
@param[in]  ciphertext  The ciphertext buffer.
@param[out] plaintext   The plaintext buffer.
@param[in]  sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS       The <tt>deskParams</tt> object is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS
@retval SB_ERR_NULL_KEY          The <tt>desKey</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_KEY           The <tt>desKey</tt> object is invalid.
@retval SB_ERR_NULL_IV           The initial vector, <tt>iv</tt>, is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_IV_LEN        The length of the initial vector, 
                                 <tt>ivLen</tt>, is invalid.
@retval SB_ERR_NULL_INPUT_BUF    The <tt>ciphertext</tt> buffer is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN The length of the <tt>ciphertext</tt> buffer 
                                 is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF   The <tt>plaintext</tt> buffer is <tt>NULL</tt>.
@retval SB_SUCCESS               Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_DESDecryptMsg(
    sb_Params desParams,
    sb_Key desKey,
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
