/*-----------------------------------------------------------------------------
 * Research In Motion IKE Daemon
 *
 * Copyright 2012, Research In Motion, All Rights Reserved.
 *
 * This source code may contain confidential information of Research In
 * Motion (RIM) and its licensors.  Any use, reproduction, modification,
 * disclosure, distribution or transfer of this software, or any software
 * that includes or is based upon any of this code, is prohibited unless
 * expressly authorized by RIM by written agreement.  For more information
 * (including whether this source code file has been published) please
 * email licensing@rim.com.
 */

/*
 * Copyright © 1996-2010 Certicom Corp. All rights reserved.
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
 * Certicom Corp. has intellectual property rights relating to technology
 * embodied in the product that is described in this document. In particular,
 * and without limitation, these intellectual property rights may include one or
 * more of the U.S. and non-U.S. patents listed at www.certicom.com/patents and
 * one or more additional patents or pending patent applications in the U.S. and
 * in other countries. Information subject to change.
 *
 */
/* $Id: hutrans.h 28192 2006-01-27 15:27:37Z jgallant $
 * $Source$
 * $Name$
 */
#ifndef HUTRANS_H
#define HUTRANS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "huaes.h"
#include "hurandom.h"

/** @addtogroup hu_transition_apis Transition APIs
 *
 * @{
 */

/** Creates an AES key object from the given key value or from random data
that can later be used for encryption.

To set the key from a given key value, set the key value in
<tt>keyValue</tt>.

To generate a key randomly, set <tt>keyValue</tt> to NULL. The AES parameter
object must have been created with an RNG context.

@param aesParams [Input] 
       The AES parameters object.
@param keyLen [Input]
       The length in bits of the AES key value. The acceptable values are
       <tt>SB_AES_128_KEY_BITS</tt>, <tt>SB_AES_192_KEY_BITS</tt>, or
       <tt>SB_AES_256_KEY_BITS</tt>.
@param keyValue [Input]
       The key value.
@param aesKey [Output]
       The AES key object pointer.
@param sbCtx [Input]
       A global context.

@retval SB_ERR_NULL_PARAMS
        The <code>aesParams</code> object is <code>NULL</code>.
@retval SB_ERR_BAD_PARAMS
        The <code>aesParams</code> object is invalid.
@retval SB_ERR_BAD_KEY_LEN
        <code>keyLen</code> is an invalid key length.
@retval SB_ERR_NULL_KEY_PTR
        The <code>aesKey</code> object pointer is <code>NULL</code>.
@retval SB_FAIL_ALLOC
        Memory allocation failure.
@retval SB_SUCCESS
        Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_AESEncryptKeyCreate(
   sb_Params aesParams,
   size_t keyLen,
   const unsigned char *keyValue,
   sb_Key *aesKey, 
   sb_GlobalCtx sbCtx
);


/** Creates an AES key object from the given key value that can later be
used for decryption.

@param aesParams [Input]
       The AES parameters object.
@param keyLen [Input]
       The length in bits of the AES key value. The acceptable values are
       <tt>SB_AES_128_KEY_BITS</tt>, <tt>SB_AES_192_KEY_BITS</tt>, or
       <tt>SB_AES_256_KEY_BITS</tt>.
@param keyValue [Input]
       The key value.
@param aesKey [Output]
       The AES key object pointer.
@param sbCtx [Input]
       A global context.

@retval SB_ERR_NULL_PARAMS
        The <code>aesParams</code> object is <code>NULL</code>.
@retval SB_ERR_BAD_PARAMS
        The <code>aesParams</code> object is invalid.
@retval SB_ERR_BAD_KEY_LEN
        <code>keyLen</code> is an invalid key length.
@retval SB_ERR_NULL_KEY_PTR
        The <code>aesKey</code> object pointer is <code>NULL</code>.
@retval SB_FAIL_ALLOC
        Memory allocation failure.
@retval SB_SUCCESS
        Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_AESDecryptKeyCreate(
   sb_Params aesParams,
   size_t keyLen,
   const unsigned char *keyValue,
   sb_Key *aesKey, 
   sb_GlobalCtx sbCtx
);


/** Creates an AES key object of the specified length from the given key
value or from random data that can later be used for encryption and/or
decryption.

To set the key from a given key value, set the key value in
<tt>keyValue</tt>.

To generate a key randomly, set <tt>keyValue</tt> to NULL. The AES parameter
object must have been created with an RNG context.

@param aesParams [Input]
       The AES parameters object.
@param keyLen [Input]
       The length in bits of the AES key value. The acceptable values are
       <tt>SB_AES_128_KEY_BITS</tt>, <tt>SB_AES_192_KEY_BITS</tt>, or
       <tt>SB_AES_256_KEY_BITS</tt>.
@param keyValue [Input]
       The key value.
@param aesKey [Output]
       The AES key object pointer.
@param sbCtx [Input]
       A global context.

@retval SB_ERR_NULL_PARAMS
        The <code>aesParams</code> object is <code>NULL</code>.
@retval SB_ERR_BAD_PARAMS
        The <code>aesParams</code> object is invalid.
@retval SB_ERR_BAD_KEY_LEN
        <code>keyLen</code> is an invalid key length.
@retval SB_ERR_NULL_KEY_PTR
        The <code>aesKey</code> object pointer is <code>NULL</code>.
@retval SB_FAIL_ALLOC
        Memory allocation failure.
@retval SB_SUCCESS
        Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_AESKeyCreate(
   sb_Params aesParams,
   size_t keyLen,
   const unsigned char *keyValue,
   sb_Key *aesKey, 
   sb_GlobalCtx sbCtx
);


/** @see hu_AESBegin */
#define hu_AESDecryptBegin hu_AESBegin


/** @see hu_AESBegin */
#define hu_AESEncryptBegin hu_AESBegin


/** @see hu_RngCreate

You must first register the ANSI RNG from a provider before calling this
function.
*/

#define hu_ANSIRngCreate hu_RngCreate


/** @see hu_RngDestroy

You must first register the ANSI RNG from a provider before calling this
function.
*/

#define hu_ANSIRngDestroy hu_RngDestroy


/** @see hu_RngCreate

You must first register the FIPS 140-2 compliant ANSI RNG from a provider
before calling this function.
*/

#define hu_FIPS140ANSIRngCreate hu_RngCreate


/** @see hu_RngDestroy

You must first register the FIPS 140-2 compliant ANSI RNG from a provider
before calling this function.
*/

#define hu_FIPS140ANSIRngDestroy hu_RngDestroy


/** Retrieves settings from an ARC2 parameters object.

@param arc2Params [Input]
       The ARC2 parameters object.
@param mode [Output]
       The mode of operation.
@param sbCtx [Input]
       A global context.

@retval SB_ERR_NULL_PARAMS
        The <code>arc2Params</code> parameters object is <code>NULL</code>.
@retval SB_ERR_BAD_PARAMS
        The <code>arc2Params</code> parameters object is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF
        All output pointers are <code>NULL</code>.
@retval SB_SUCCESS
        Success.

*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ARC2ParamsGetV1(
   sb_Params arc2Params, 
   int *mode, 
   sb_GlobalCtx sbCtx
);


/** @see hu_ARC2ParamsGet */

#define hu_ARC2ParamsGetV2 hu_ARC2ParamsGet


/** Creates an ARC2 key object of the specified length from the given key
value or from random data that can later be used for encryption and/or
decryption.

To set the key from a given key value, set the key value in
<tt>keyValue</tt>.

To generate a key randomly, set <tt>keyValue</tt> to NULL. The ARC2 parameter
object must have been created with an RNG context.

@param arc2Params [Input]
       The ARC2 parameters object.
@param keyLen [Input]
       The length in bytes of the ARC2 key value. The maximum allowable length
       is <tt>SB_ARC2_MAX_KEY_SIZE</tt>.
@param keyValue [Input]
       The key value.
@param arc2Key [Output]
       An ARC2 key object pointer.
@param sbCtx [Input]
       A global context.

@retval SB_ERR_NULL_PARAMS
        The <code>arc2Params</code> parameters object is <code>NULL</code>.
@retval SB_ERR_BAD_PARAMS
        The <code>arc2Params</code> parameters object is invalid.
@retval SB_ERR_BAD_KEY_LEN
        <code>keyLen</code> is an invalid key length.
@retval SB_ERR_NULL_KEY_PTR
        The <code>arc2Key</code> key object pointer is <code>NULL</code>.
@retval SB_FAIL_ALLOC
        Memory allocation failure.
@retval SB_SUCCESS
        Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ARC2KeyCreate(
   sb_Params arc2Params,
   size_t keyLen,
   const unsigned char *key,
   sb_Key *arc2Key,
   sb_GlobalCtx sbCtx
);


/** Creates an ARC4 key object of the specified length from the given key
value or from random data that can later be used for encryption and/or
decryption.

To set the key from a given key value, set the key value in
<tt>keyValue</tt>.

To generate a key randomly, set <tt>keyValue</tt> to NULL. The ARC4 parameter
object must have been created with an RNG context.

@param arc4Params [Input]
       An ARC4 parameters object.
@param keyLen [Input]
       The length in bytes of the ARC4 key value. The maximum allowable length
       is <tt>SB_ARC4_MAX_KEY_LEN</tt>.
@param keyValue [Input]
       The key value.
@param arc4Key [Output]
       The ARC4 key object pointer.
@param sbCtx [Input]
       A global context.

@retval SB_ERR_NULL_PARAMS
        The <code>arc4Params</code> parameters object is <code>NULL</code>.
@retval SB_ERR_BAD_PARAMS
        The <code>arc4Params</code> parameters object is invalid.
@retval SB_ERR_BAD_KEY_LEN
        <code>keyLen</code> is an invalid key length.
@retval SB_ERR_NULL_KEY_PTR
        The <code>arc4Key</code> object pointer is <code>NULL</code>.
@retval SB_FAIL_ALLOC
        Memory allocation failure.
@retval SB_SUCCESS
        Success.
*/

extern
SB_EXPORT
int 
SB_CALLCONV
hu_ARC4KeyCreate(
   sb_Params arc4Params,
   size_t keyLen,
   const unsigned char *keyValue,
   sb_Key *arc4Key,
   sb_GlobalCtx sbCtx
);


/** Creates an DES key object of the specified length from the given key
value(s) or from random data that can later be used for encryption and/or
decryption.

To set the key object:

If the algorithm is <code>SB_DES_DES</code>, a key value must be given in
<code>key1</code>. The <code>key2</code> and <code>key3</code> arguments
will be ignored.

If the algorithm is <code>SB_DES_TDES</code> or <code>SB_DES_DESX</code>,
all three key buffers must be given.

For <code>SB_DES_DESX</code>, key 1 is the encryption key, key 2 is
the prewhitening key and key 3 is the postwhitening key.

If the parity mode is <code>SB_DES_PARITY_ON</code>, an error will be
returned if any of the encryption keys have incorrect parity.

If the weak key mode is <code>SB_DES_WEAK_KEY_ON</code>, an error will
be returned if any of the encryption keys match a known weak key.


To generate a key randomly:

Set <tt>key1</tt>, <tt>key2</tt> and <tt>key3</tt> to NULL. The DES parameter
object must have been created with an RNG context.

If the parity mode is <code>SB_DES_PARITY_ON</code>, the encryption keys
will be generated with odd parity.

If the weak key mode is <code>SB_DES_WEAK_KEY_ON</code>, the encryption keys
will be generated such that they will not match a known weak key.

@param desParams [Input]
       A DES parameters object.
@param key1Len [Input]
       The length in bytes of <code>key1</code>. The only acceptable value is
       <code>SB_DES_KEY_SIZE</code>.
@param key1 [Input]
       Key 1 value.
@param key2Len [Input]
       The length in bytes of <code>key1</code>. The only acceptable value is
       <code>SB_DES_KEY_SIZE</code>. Ignored if the mode is
       <code>SB_DES_DES</code>.
@param key2 [Input]
       Key 2 value. Ignored if the mode is <code>SB_DES_DES</code>.
@param key3Len [Input]
       The length in bytes of <code>key1</code>. The only acceptable value is
       <code>SB_DES_KEY_SIZE</code>. Ignored if the mode is
       <code>SB_DES_DES</code>.
@param key3 [Input]
       Key 3 value. Ignored if the mode is <code>SB_DES_DES</code>.
@param desKey [Output]
       The DES key object pointer.
@param sbCtx [Input]
       The global context.

@retval SB_ERR_NULL_PARAMS
        The <code>desParams</code> Parameters object is <code>NULL</code>.
@retval SB_ERR_BAD_PARAMS
        The <code>desParams</code> Parameters object is invalid.
@retval SB_ERR_BAD_KEY_LEN
        Key length is invalid.
@retval SB_ERR_BAD_KEY_PARITY
        Key value has incorrect parity.
@retval SB_ERR_WEAK_KEY
        Key value is known to be weak.
@retval SB_ERR_NULL_KEY_PTR
        Key object pointer is <code>NULL</code>.
@retval SB_FAIL_ALLOC
        Memory allocation failure.
@retval SB_SUCCESS
        Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_DESKeyCreate(
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


/** Creates an ECC private key object, and, optionally, the corresponding
public key object, from the given key value(s) or from random data.

To set the key objects:

If both private and public key values are supplied, a private key and/or a
public key object can be created. The key objects will be created from the
corresponding key values.

If only a private key value is supplied, a private key and/or a public key
object can be created. The public key will be computed from the private key.

If only a public key value is supplied, only a public key object can be
created.


To generate the keys randomly:

To generate key(s) randomly, set <tt>privateKeyValue</tt> and
<tt>publicKeyValue</tt> to NULL. The ECC parameter object must have been
created with an RNG context.

@param eccParams [Input]
       An ECC parameters object.
@param privateKeyLen [Input]
       The length in bytes of the private key value.
@param privateKeyValue [Input]
       The private key value.
@param publicKeyLen [Input]
       The length in bytes of the public key value.
@param publicKeyValue [Input]
       The public key value.
@param privateKey [Output]
       The private key object pointer.
@param publicKey [Output]
       The public key object pointer.
@param sbCtx [Input]
       A global context.

@retval SB_ERR_NULL_PARAMS
        The <code>eccParams</code> object is <code>NULL</code>.
@retval SB_ERR_BAD_PARAMS
        The <code>eccParams</code> object is invalid.
@retval SB_ERR_NULL_PRI_KEY_BUF
        The private key value is <code>NULL</code>.
@retval SB_ERR_BAD_PRI_KEY_BUF_LEN
        The private key length is invalid.
@retval SB_ERR_NULL_PUB_KEY_BUF
        The public key value is <code>NULL</code>.
@retval SB_ERR_BAD_PUB_KEY_BUF_LEN
        The public key length is invalid.
@retval SB_ERR_BAD_INPUT
        The public key value is invalid.
@retval SB_FAIL_INVALID_PRIVATE_KEY
        The private key value is invalid.
@retval SB_FAIL_ALLOC
        Memory allocation failure.
@retval SB_SUCCESS
        Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ECCKeyCreate(
   sb_Params eccParams,
   size_t privateKeyLen,
   const unsigned char *privateKeyValue,
   size_t publicKeyLen,
   const unsigned char *publicKeyValue,
   sb_PrivateKey *privateKey,
   sb_PublicKey *publicKey,
   sb_GlobalCtx sbCtx
);


/** @see hu_ECCParamsCreate

You must first register the sect163k1 curve with optimization level 0 from a
provider before calling this function.
*/

#define hu_ECCsect163k1_0ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECT163K1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate

You must first register the sect163k1 curve with optimization level 1 from a
provider before calling this function.
*/

#define hu_ECCsect163k1_1ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECT163K1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate

You must first register the sect163k1 curve with optimization level 2 from a
provider before calling this function.
*/

#define hu_ECCsect163k1_2ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECT163K1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the sect163r2 curve with optimization level 0 from a
provider before calling this function.
*/

#define hu_ECCsect163r2_0ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECT163R2, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the sect163r2 curve with optimization level 1 from a
provider before calling this function.
*/

#define hu_ECCsect163r2_1ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECT163R2, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the sect163r2 curve with optimization level 2 from a
provider before calling this function.
*/

#define hu_ECCsect163r2_2ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECT163R2, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the sect233k1 curve with optimization level 0 from a
provider before calling this function.
*/

#define hu_ECCsect233k1_0ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECT233K1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the sect233k1 curve with optimization level 1 from a
provider before calling this function.
*/

#define hu_ECCsect233k1_1ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECT233K1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the sect233k1 curve with optimization level 2 from a
provider before calling this function.
*/

#define hu_ECCsect233k1_2ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECT233K1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the sect233r1 curve with optimization level 0 from a
provider before calling this function.
*/

#define hu_ECCsect233r1_0ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECT233R1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the sect233r1 curve with optimization level 1 from a
provider before calling this function.
*/

#define hu_ECCsect233r1_1ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECT233R1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the sect233r1 curve with optimization level 2 from a
provider before calling this function.
*/

#define hu_ECCsect233r1_2ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECT233R1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the sect239k1 curve with optimization level 0 from a
provider before calling this function.
*/

#define hu_ECCsect239k1_0ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECT239K1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the sect239k1 curve with optimization level 1 from a
provider before calling this function.
*/

#define hu_ECCsect239k1_1ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECT239K1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the sect239k1 curve with optimization level 2 from a
provider before calling this function.
*/

#define hu_ECCsect239k1_2ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECT239K1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the sect283k1 curve with optimization level 0 from a
provider before calling this function.
*/

#define hu_ECCsect283k1_0ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECT283K1 , rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the sect283k1 curve with optimization level 1 from a
provider before calling this function.
*/

#define hu_ECCsect283k1_1ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECT283K1 , rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the sect283k1 curve with optimization level 2 from a
provider before calling this function.
*/

#define hu_ECCsect283k1_2ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECT283K1 , rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the sect283r1 curve with optimization level 0 from a
provider before calling this function.
*/

#define hu_ECCsect283r1_0ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECT283R1 , rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the sect283r1 curve with optimization level 1 from a
provider before calling this function.
*/

#define hu_ECCsect283r1_1ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECT283R1 , rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the sect283r1 curve with optimization level 2 from a
provider before calling this function.
*/

#define hu_ECCsect283r1_2ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECT283R1 , rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the sect409k1 curve with optimization level 0 from a
provider before calling this function.
*/

#define hu_ECCsect409k1_0ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECT409K1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the sect409k1 curve with optimization level 1 from a
provider before calling this function.
*/

#define hu_ECCsect409k1_1ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECT409K1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the sect409k1 curve with optimization level 2 from a
provider before calling this function.
*/

#define hu_ECCsect409k1_2ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECT409K1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the sect409r1 curve with optimization level 0 from a
provider before calling this function.
*/

#define hu_ECCsect409r1_0ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECT409R1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the sect409r1 curve with optimization level 1 from a
provider before calling this function.
*/

#define hu_ECCsect409r1_1ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECT409R1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the sect409r1 curve with optimization level 2 from a
provider before calling this function.
*/

#define hu_ECCsect409r1_2ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECT409R1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the sect571k1 curve with optimization level 0 from a
provider before calling this function.
*/

#define hu_ECCsect571k1_0ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECT571K1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the sect571k1 curve with optimization level 1 from a
provider before calling this function.
*/

#define hu_ECCsect571k1_1ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECT571K1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the sect571k1 curve with optimization level 2 from a
provider before calling this function.
*/

#define hu_ECCsect571k1_2ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECT571K1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the sect571r1 curve with optimization level 0 from a
provider before calling this function.
*/

#define hu_ECCsect571r1_0ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECT571R1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the sect571r1 curve with optimization level 1 from a
provider before calling this function.
*/

#define hu_ECCsect571r1_1ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECT571R1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the sect571r1 curve with optimization level 2 from a
provider before calling this function.
*/

#define hu_ECCsect571r1_2ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECT571R1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the secp160r1 curve with optimization level 0 from a
provider before calling this function.
*/

#define hu_ECCsecp160r1_0ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECP160R1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the secp160r1 curve with optimization level 1 from a
provider before calling this function.
*/

#define hu_ECCsecp160r1_1ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECP160R1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the secp160r1 curve with optimization level 2 from a
provider before calling this function.
*/

#define hu_ECCsecp160r1_2ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECP160R1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the secp192r1 curve with optimization level 0 from a
provider before calling this function.
*/

#define hu_ECCsecp192r1_0ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECP192R1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the secp192r1 curve with optimization level 1 from a
provider before calling this function.
*/

#define hu_ECCsecp192r1_1ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECP192R1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the secp192r1 curve with optimization level 2 from a
provider before calling this function.
*/

#define hu_ECCsecp192r1_2ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECP192R1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the secp224r1 curve with optimization level 0 from a
provider before calling this function.
*/

#define hu_ECCsecp224r1_0ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECP224R1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the secp224r1 curve with optimization level 1 from a
provider before calling this function.
*/

#define hu_ECCsecp224r1_1ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECP224R1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the secp224r1 curve with optimization level 2 from a
provider before calling this function.
*/

#define hu_ECCsecp224r1_2ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECP224R1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the secp256r1 curve with optimization level 0 from a
provider before calling this function.
*/

#define hu_ECCsecp256r1_0ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECP256R1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the secp256r1 curve with optimization level 1 from a
provider before calling this function.
*/

#define hu_ECCsecp256r1_1ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECP256R1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the secp256r1 curve with optimization level 2 from a
provider before calling this function.
*/

#define hu_ECCsecp256r1_2ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECP256R1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the secp384r1 curve with optimization level 0 from a
provider before calling this function.
*/

#define hu_ECCsecp384r1_0ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECP384R1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the secp384r1 curve with optimization level 1 from a
provider before calling this function.
*/

#define hu_ECCsecp384r1_1ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECP384R1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the secp384r1 curve with optimization level 2 from a
provider before calling this function.
*/

#define hu_ECCsecp384r1_2ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECP384R1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the secp521r1 curve with optimization level 0 from a
provider before calling this function.
*/

#define hu_ECCsecp521r1_0ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECP521R1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the secp521r1 curve with optimization level 1 from a
provider before calling this function.
*/

#define hu_ECCsecp521r1_1ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECP521R1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the secp521r1 curve with optimization level 2 from a
provider before calling this function.
*/

#define hu_ECCsecp521r1_2ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_SECP521R1, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the wtls5 curve with optimization level 0 from a
provider before calling this function.
*/

#define hu_ECCwTLS5_0ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_WTLS5, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the wtls5 curve with optimization level 1 from a
provider before calling this function.
*/

#define hu_ECCwTLS5_1ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_WTLS5, rng, yield, params, sbctx )


/** @see hu_ECCParamsCreate 

You must first register the wtls5 curve with optimization level 2 from a
provider before calling this function.
*/

#define hu_ECCwTLS5_2ParamsCreate( rng, yield, params, sbctx ) \
  hu_ECCParamsCreate( HU_ECC_CURVE_WTLS5, rng, yield, params, sbctx )


/** @see hu_ECCsect163k1_0ParamsCreate */
#define hu_ECCwTLS3_0ParamsCreate hu_ECCsect163k1_0ParamsCreate


/** @see hu_ECCsect163k1_1ParamsCreate */
#define hu_ECCwTLS3_1ParamsCreate hu_ECCsect163k1_1ParamsCreate


/** @see hu_ECCsect163k1_2ParamsCreate */
#define hu_ECCwTLS3_2ParamsCreate hu_ECCsect163k1_2ParamsCreate


/** @see hu_ECCsecp160r1_0ParamsCreate */
#define hu_ECCwTLS7_0ParamsCreate hu_ECCsecp160r1_0ParamsCreate


/** @see hu_ECCsecp160r1_1ParamsCreate */
#define hu_ECCwTLS7_1ParamsCreate hu_ECCsecp160r1_1ParamsCreate


/** @see hu_ECCsecp160r1_2ParamsCreate */
#define hu_ECCwTLS7_2ParamsCreate hu_ECCsecp160r1_2ParamsCreate


/** @see hu_ECDHCofacSharedGen */
#define hu_ECDHIPSecSharedGen hu_ECDHCofacSharedGen


/** @see hu_ECDHCofacRawSharedGen */
#define hu_ECDHIPSecRawSharedGen hu_ECDHCofacRawSharedGen


/** Creates an IDLC parameters object from the given values, or generating
them randomly, that can later be used for DH or DSA.

You must first register IDLC parameter creation with optimization level 0
from a provider before calling this function.

To set parameters:

An RNG context must be supplied if key generation or DSA will be performed.
A yielding context must be supplied if yielding will be performed.

The values should satisfy the following properties: p and q are prime, q is a
divisor of (p-1), and g has order q modulo p. p will have bitlength
<code>pSize</code> and q will have bitlength <code>qSize</code>.

<code>q</code> is optional. If <code>q</code> is not supplied, then
<code>qSize</code> specifies the size of private keys to be used with these
parameters. In this case, if <code>qSize</code> is set to zero, the default
size of 160 bits will be used.

To generate parameters:

An RNG context must be supplied. A yielding context must be supplied if
yielding will be performed.

Set <code>p</code>, <code>q</code> and <code>g</code> to <code>NULL</code>.
This function will generate values p, q, and g such that p and q are prime,
q is a divisor of (p-1), and g has order q modulo p. p will have bitlength
<code>pSize</code> and q will have bitlength <code>qSize</code>.

@param pSize [Input]
       The length in bits of the prime modulus p. The length must be greater
       than or equal to 512.
@param qSize [Input]
       The length in bits of the prime divisor q. The length must be greater
       than or equal to 160 and less than <code>pSize</code>.
@param pLength [Input]
       The length in bytes of the prime modulus.
@param p [Input]
       Prime modulus.
@param gLength [Input]
       The length in bytes of the generator. Must be less than or equal to
       <code>pLength</code>.
@param g [Input]
       Generator of order q.
@param qLength [Input]
       The length in bytes of the prime divisor.
@param q [Input]
       Prime divisor of p-1.
@param rngCtx [Input]
       An RNG context.
@param yieldCtx [Input]
       A yield context (optional). Set to <code>NULL</code> if yielding is not
       required.
@param idlcParams [Output]
       The IDLC parameters object pointer.
@param sbCtx [Input]
       A global context.

@retval SB_ERR_NULL_PARAMS_PTR
        The <code>idlcParams</code> object pointer is <code>NULL</code>.
@retval SB_ERR_NULL_IDLC_P
        The prime modulus value is <code>NULL</code>.
@retval SB_ERR_NULL_IDLC_Q
        The prime divisor value is <code>NULL</code>.
@retval SB_ERR_NULL_IDLC_G
        The generator value is <code>NULL</code>.
@retval SB_ERR_BAD_INPUT
        The length in bits of p or q is invalid.
@retval SB_ERR_BAD_INPUT_BUF_LEN
        The length in bytes of p, q or g buffers is invalid.
@retval SB_FAIL_ALLOC
        Memory allocation failure.
@retval SB_SUCCESS
        Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_IDLC_0ParamsCreate(
   size_t pSize,
   size_t qSize,
   size_t pLength,
   const unsigned char *p,
   size_t gLength,
   const unsigned char *g,
   size_t qLength,
   const unsigned char *q,
   sb_RNGCtx rngCtx,
   sb_YieldCtx yieldCtx,
   sb_Params *idlcParams,
   sb_GlobalCtx sbCtx
);


/* @see hu_IDLC_0ParamsCreate

You must first register IDLC parameter creation with optimization level 1
from a provider before calling this function.
*/
#define hu_IDLC_1ParamsCreate hu_IDLC_0ParamsCreate


/* @see hu_IDLC_0ParamsCreate

You must first register IDLC parameter creation with optimization level 2
from a provider before calling this function.
*/
#define hu_IDLC_2ParamsCreate hu_IDLC_0ParamsCreate


/* @see hu_IDLCParamsSet

You must first register IDLC parameter creation with optimization level 0
from a provider before calling this function.
*/
#define hu_IDLC_0ParamsCreateNoGen hu_IDLCParamsSet


/* @see hu_IDLCParamsSet

You must first register IDLC parameter creation with optimization level 1
from a provider before calling this function.
*/
#define hu_IDLC_1ParamsCreateNoGen hu_IDLCParamsSet


/* @see hu_IDLCParamsSet

You must first register IDLC parameter creation with optimization level 2
from a provider before calling this function.
*/
#define hu_IDLC_2ParamsCreateNoGen hu_IDLCParamsSet


/* @see hu_IDLC_0ParamsCreateNoGen

THIS FUNCTION IS DEPRECATED.
*/
#define hu_IDLCParamsCreateNoGen( optLevel, pSize, qSize, pLength, p, \
                             gLength, g, qLength, q, RNGContext, yieldCtx, \
                             IDLCParams, sbCtx ) \
        hu_IDLC_0ParamsCreateNoGen( pSize, qSize, pLength, p, \
                               gLength, g, qLength, q, RNGContext, yieldCtx, \
                               IDLCParams, sbCtx )


/** Creates an IDLC parameters object from the given values, or generating
the parameters randomly according to FIPS 186 specifications, that can
later be used for DH or DSA.

You must first register IDLC FIPS parameter creation with optimization level
0 from a provider before calling this function.

To set parameters:

The values should satisfy the following properties: p and q are prime, q is a
divisor of (p-1), and g has order q modulo p. p will have bitlength
<code>pSize</code> and q will have bitlength <code>qSize</code>.

To generate parameters:

An RNG context must be supplied. A yielding context must be supplied if
yielding will be performed.

Set <code>p</code>, <code>q</code> and <code>g</code> to <code>NULL</code>.
This function will generate values p, q, and g such that p and q are prime,
q is a divisor of (p-1) and, g has order q modulo p. p will have bitlength
<code>pSize</code> and q will have bitlength <code>qSize</code>.

@param pSize [Input]
       The length in bits of the prime modulus p. The length must be between
       512 and 1024 inclusive, and a multiple of 64.
@param qSize [Input]
       The length in bits of the prime divisor q. The only acceptable value is
       160.
@param pLength [Input]
       The length in bytes of the prime modulus.
@param p [Input]
       Prime modulus.
@param gLength [Input]
       The length in bytes of the generator. Must be less than or equal to
       <code>pLength</code>.
@param g [Input]
       Generator of order q.
@param qLength [Input]
       The length in bytes of the prime divisor.
@param q [Input]
       Prime divisor of p-1.
@param rngCtx [Input]
       An RNG context.
@param yieldCtx [Input]
       A yield context (optional). Set to <code>NULL</code> if yielding is not
       required.
@param idlcParams [Output]
       The IDLC parameters object pointer.
@param sbCtx [Input]
       A global context.

@retval SB_ERR_NULL_PARAMS_PTR
        The <code>idlcParams</code> object pointer is <code>NULL</code>.
@retval SB_ERR_NULL_IDLC_P
        The prime modulus value is <code>NULL</code>.
@retval SB_ERR_NULL_IDLC_Q
        The prime divisor value is <code>NULL</code>.
@retval SB_ERR_NULL_IDLC_G
        The generator value is <code>NULL</code>.
@retval SB_ERR_BAD_INPUT
        The length in bits of p or q is invalid.
@retval SB_ERR_BAD_INPUT_BUF_LEN
        The length in bytes of p, q or g buffers is invalid.
@retval SB_FAIL_ALLOC
        Memory allocation failure.
@retval SB_SUCCESS
        Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_IDLCFIPS_0ParamsCreate(
   size_t pSize,
   size_t qSize,
   size_t pLength,
   const unsigned char *p,
   size_t gLength,
   const unsigned char *g,
   size_t qLength,
   const unsigned char *q,
   sb_RNGCtx rngCtx,
   sb_YieldCtx yieldCtx,
   sb_Params *idlcParams,
   sb_GlobalCtx sbCtx
);


/** @see hu_IDLCFIPS_0ParamsCreate

You must first register IDLC FIPS parameter creation with optimization level
1 from a provider before calling this function.
*/
#define hu_IDLCFIPS_1ParamsCreate hu_IDLCFIPS_0ParamsCreate


/** @see hu_IDLCFIPS_0ParamsCreate

You must first register IDLC FIPS parameter creation with optimization level
2 from a provider before calling this function.
*/
#define hu_IDLCFIPS_2ParamsCreate hu_IDLCFIPS_0ParamsCreate


/* @see hu_IDLCFIPS_0ParamsCreate

THIS FUNCTION IS DEPRECATED.
*/
#define hu_IDLCFIPSParamsCreate( optLevel, pSize, qSize, pLength, p, \
                                 gLength, g, qLength, q, RNGContext, yieldCtx, \
                                 IDLCParams, sbCtx ) \
        hu_IDLCFIPS_0ParamsCreate( pSize, qSize, pLength, p, \
                               gLength, g, qLength, q, RNGContext, yieldCtx, \
                               IDLCParams, sbCtx )


/** Creates an IDLC parameters object from the given values, or generating
the parameters randomly according to ANSI X9.42 specifications, that can
later be used for DH or DSA.

You must first register IDLC ANSI parameter creation with optimization level
0 from a provider before calling this function.

To set parameters:

The values should satisfy the following properties: p and q are prime, q is a
divisor of (p-1), and g has order q modulo p. p will have bitlength
<code>pSize</code> and q will have bitlength <code>qSize</code>.

To generate parameters:

An RNG context must be supplied. A yielding context must be supplied if
yielding will be performed.

Set <code>p</code>, <code>q</code> and <code>g</code> to <code>NULL</code>.
This function will generate values p, q, and g such that p and q are prime,
q is a divisor of (p-1) and, g has order q modulo p. p will have bitlength
<code>pSize</code> and q will have bitlength <code>qSize</code>.

@param pSize [Input]
       The length in bits of the prime modulus p. The length must be greater
       than or equal to 512.
@param qSize [Input]
       The length in bits of the prime divisor q. The length must be greater
       than or equal to 160 and less than <code>pSize</code>.
@param pLength [Input]
       The length in bytes of the prime modulus.
@param p [Input]
       Prime modulus.
@param gLength [Input]
       The length in bytes of the generator. Must be less than or equal to
       <code>pLength</code>.
@param g [Input]
       Generator of order q.
@param qLength [Input]
       The length in bytes of the prime divisor.
@param q [Input]
       Prime divisor of p-1.
@param rngCtx [Input]
       An RNG context.
@param yieldCtx [Input]
       A yield context (optional). Set to <code>NULL</code> if yielding is not
       required.
@param idlcParams [Output]
       The IDLC parameters object pointer.
@param sbCtx [Input]
       A global context.

@retval SB_ERR_NULL_PARAMS_PTR
        The <code>idlcParams</code> object pointer is <code>NULL</code>.
@retval SB_ERR_NULL_IDLC_P
        The prime modulus value is <code>NULL</code>.
@retval SB_ERR_NULL_IDLC_Q
        The prime divisor value is <code>NULL</code>.
@retval SB_ERR_NULL_IDLC_G
        The generator value is <code>NULL</code>.
@retval SB_ERR_BAD_INPUT
        The length in bits of p or q is invalid.
@retval SB_ERR_BAD_INPUT_BUF_LEN
        The length in bytes of p, q or g buffers is invalid.
@retval SB_FAIL_ALLOC
        Memory allocation failure.
@retval SB_SUCCESS
        Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_IDLCANSI_0ParamsCreate(
   size_t pSize,
   size_t qSize,
   size_t pLength,
   const unsigned char *p,
   size_t gLength,
   const unsigned char *g,
   size_t qLength,
   const unsigned char *q,
   sb_RNGCtx rngCtx,
   sb_YieldCtx yieldCtx,
   sb_Params *idlcParams,
   sb_GlobalCtx sbCtx
);


/** @see hu_IDLCANSI_0ParamsCreate

You must first register IDLC ANSI parameter creation with optimization level
1 from a provider before calling this function.
*/
#define hu_IDLCANSI_1ParamsCreate hu_IDLCANSI_0ParamsCreate


/** @see hu_IDLCANSI_0ParamsCreate

You must first register IDLC ANSI parameter creation with optimization level
2 from a provider before calling this function.
*/
#define hu_IDLCANSI_2ParamsCreate hu_IDLCANSI_0ParamsCreate


/* @see hu_IDLCANSI_0ParamsCreate

THIS FUNCTION IS DEPRECATED.
*/
#define hu_IDLCANSIParamsCreate( optLevel, pSize, qSize, pLength, p, \
                                 gLength, g, qLength, q, RNGContext, yieldCtx, \
                                 IDLCParams, sbCtx ) \
        hu_IDLCANSI_0ParamsCreate( pSize, qSize, pLength, p, \
                               gLength, g, qLength, q, RNGContext, yieldCtx, \
                               IDLCParams, sbCtx )


/** @see hu_IDLCParamsCreate

You must first register the IPSec 1 Group with optimization level 0 from a
provider before calling this function.
*/
#define hu_IDLCIPSec1_0ParamsCreate( rng, yield, params, sbctx ) \
        hu_IDLCParamsCreate( HU_IDLC_GROUP_IPSEC_1, rng, yield, params, sbctx )


/** @see hu_IDLCParamsCreate

You must first register the IPSec 1 Group with optimization level 1 from a
provider before calling this function.
*/
#define hu_IDLCIPSec1_1ParamsCreate( rng, yield, params, sbctx ) \
        hu_IDLCParamsCreate( HU_IDLC_GROUP_IPSEC_1, rng, yield, params, sbctx )


/** @see hu_IDLCParamsCreate

You must first register the IPSec 1 Group with optimization level 2 from a
provider before calling this function.
*/
#define hu_IDLCIPSec1_2ParamsCreate( rng, yield, params, sbctx ) \
        hu_IDLCParamsCreate( HU_IDLC_GROUP_IPSEC_1, rng, yield, params, sbctx )

/* @see hu_IDLCIPSec1_0ParamsCreate

THIS FUNCTION IS DEPRECATED.
*/
#define hu_IDLCIPSec1ParamsCreate( optLevel, RNGContext, yieldCtx, \
                                   IDLCParams, sbCtx ) \
        hu_IDLCIPSec1_0ParamsCreate( RNGContext, yieldCtx, \
                                     IDLCParams, sbCtx )

/** @see hu_IDLCParamsCreate

You must first register the IPSec 2 Group with optimization level 0 from a
provider before calling this function.
*/
#define hu_IDLCIPSec2_0ParamsCreate( rng, yield, params, sbctx ) \
        hu_IDLCParamsCreate( HU_IDLC_GROUP_IPSEC_2, rng, yield, params, sbctx )


/** @see hu_IDLCParamsCreate

You must first register the IPSec 2 Group with optimization level 1 from a
provider before calling this function.
*/
#define hu_IDLCIPSec2_1ParamsCreate( rng, yield, params, sbctx ) \
        hu_IDLCParamsCreate( HU_IDLC_GROUP_IPSEC_2, rng, yield, params, sbctx )


/** @see hu_IDLCParamsCreate

You must first register the IPSec 2 Group with optimization level 2 from a
provider before calling this function.
*/
#define hu_IDLCIPSec2_2ParamsCreate( rng, yield, params, sbctx ) \
        hu_IDLCParamsCreate( HU_IDLC_GROUP_IPSEC_2, rng, yield, params, sbctx )


/** @see hu_IDLCIPSec2_0ParamsCreate

THIS FUNCTION IS DEPRECATED.
*/
#define hu_IDLCIPSec2ParamsCreate( optLevel, RNGContext, yieldCtx, \
                                   IDLCParams, sbCtx ) \
        hu_IDLCIPSec2_0ParamsCreate( RNGContext, yieldCtx, \
                                     IDLCParams, sbCtx )


/** @see hu_IDLCParamsCreate

You must first register the IPSec 5 Group with optimization level 0 from a
provider before calling this function.
*/
#define hu_IDLCIPSec5_0ParamsCreate( rng, yield, params, sbctx ) \
        hu_IDLCParamsCreate( HU_IDLC_GROUP_IPSEC_5, rng, yield, params, sbctx )


/** @see hu_IDLCParamsCreate

You must first register the IPSec 5 Group with optimization level 1 from a
provider before calling this function.
*/
#define hu_IDLCIPSec5_1ParamsCreate( rng, yield, params, sbctx ) \
        hu_IDLCParamsCreate( HU_IDLC_GROUP_IPSEC_5, rng, yield, params, sbctx )


/** @see hu_IDLCParamsCreate

You must first register the IPSec 5 Group with optimization level 2 from a
provider before calling this function.
*/
#define hu_IDLCIPSec5_2ParamsCreate( rng, yield, params, sbctx ) \
        hu_IDLCParamsCreate( HU_IDLC_GROUP_IPSEC_5, rng, yield, params, sbctx )


/** @see hu_IDLCIPSec5_0ParamsCreate

THIS FUNCTION IS DEPRECATED.
*/
#define hu_IDLCIPSec5ParamsCreate( optLevel, RNGContext, yieldCtx, \
                                   IDLCParams, sbCtx ) \
        hu_IDLCIPSec5_0ParamsCreate( RNGContext, yieldCtx, \
                                     IDLCParams, sbCtx )


/** @see hu_IDLCParamsCreate

You must first register the WTLS 1 Group with optimization level 0 from a
provider before calling this function.
*/
#define hu_IDLCwTLS1_0ParamsCreate( rng, yield, params, sbctx ) \
        hu_IDLCParamsCreate( HU_IDLC_GROUP_WTLS_1, rng, yield, params, sbctx )


/** @see hu_IDLCParamsCreate

You must first register the WTLS 1 Group with optimization level 1 from a
provider before calling this function.
*/
#define hu_IDLCwTLS1_1ParamsCreate( rng, yield, params, sbctx ) \
        hu_IDLCParamsCreate( HU_IDLC_GROUP_WTLS_1, rng, yield, params, sbctx )


/** @see hu_IDLCParamsCreate

You must first register the WTLS 1 Group with optimization level 2 from a
provider before calling this function.
*/
#define hu_IDLCwTLS1_2ParamsCreate( rng, yield, params, sbctx ) \
        hu_IDLCParamsCreate( HU_IDLC_GROUP_WTLS_1, rng, yield, params, sbctx )


/** @see hu_IDLCwTLS1_0ParamsCreate

THIS FUNCTION IS DEPRECATED.
*/
#define hu_IDLCwTLS1ParamsCreate( optLevel, RNGContext, yieldCtx, \
                                  IDLCParams, sbCtx ) \
        hu_IDLCwTLS1_0ParamsCreate( RNGContext, yieldCtx, \
                                     IDLCParams, sbCtx )


/** @see hu_IDLCParamsCreate

You must first register the WTLS 2 Group with optimization level 0 from a
provider before calling this function.
*/
#define hu_IDLCwTLS2_0ParamsCreate( rng, yield, params, sbctx ) \
        hu_IDLCParamsCreate( HU_IDLC_GROUP_WTLS_2, rng, yield, params, sbctx )


/** @see hu_IDLCParamsCreate

You must first register the WTLS 2 Group with optimization level 1 from a
provider before calling this function.
*/
#define hu_IDLCwTLS2_1ParamsCreate( rng, yield, params, sbctx ) \
        hu_IDLCParamsCreate( HU_IDLC_GROUP_WTLS_2, rng, yield, params, sbctx )


/** @see hu_IDLCParamsCreate

You must first register the WTLS 2 Group with optimization level 2 from a
provider before calling this function.
*/
#define hu_IDLCwTLS2_2ParamsCreate( rng, yield, params, sbctx ) \
        hu_IDLCParamsCreate( HU_IDLC_GROUP_WTLS_2, rng, yield, params, sbctx )


/** @see hu_IDLCwTLS2_0ParamsCreate

THIS FUNCTION IS DEPRECATED.
*/
#define hu_IDLCwTLS2ParamsCreate( optLevel, RNGContext, yieldCtx, \
                                  IDLCParams, sbCtx ) \
        hu_IDLCwTLS2_0ParamsCreate( RNGContext, yieldCtx, \
                                     IDLCParams, sbCtx )


/** Creates an IDLC private key object, and, optionally, the corresponding
public key object, from the given key value(s) or from random data.

To set the key objects:

If both private and public key values are supplied, a private key and/or a
public key object can be created. The key objects will be created from the
corresponding key values.

If only a private key value is supplied, a private key and/or a public key
object can be created. The public key will be computed from the private key.

If only a public key value is supplied, only a public key object can be
created.


To generate the keys randomly:

To generate key(s) randomly, set <tt>privateKeyValue</tt> and
<tt>publicKeyValue</tt> to NULL. The IDLC parameter object must have been
created with an RNG context.
 
@param idlcParams [Input]
       IDLC parameters object.
@param privateKeyLen [Input]
       The length in bytes of the private key value.
@param privateKeyValue [Input]
       The private key value.
@param publicKeyLen [Input]
       The length in bytes of the public key value.
@param publicKeyValue [Input]
       The public key value.
@param privateKey [Output]
       The private key object pointer.
@param publicKey [Output]
       The public key object pointer.
@param sbCtx [Input]
       A global context.

@retval SB_ERR_NULL_PARAMS
        The <code>idlcParams</code> object is <code>NULL</code>.
@retval SB_ERR_BAD_PARAMS
        The <code>idlcParams</code> object is invalid.
@retval SB_ERR_NULL_PRI_KEY_BUF
        The private key value is <code>NULL</code>.
@retval SB_ERR_BAD_PRI_KEY_BUF_LEN
        The private key length is invalid.
@retval SB_ERR_NULL_PUB_KEY_BUF
        The public key value is <code>NULL</code>.
@retval SB_ERR_BAD_PUB_KEY_BUF_LEN
        The public key length is invalid.
@retval SB_FAIL_INVALID_PRIVATE_KEY
        The private key value is invalid.
@retval SB_FAIL_ALLOC
        Memory allocation failure.
@retval SB_SUCCESS
        Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_IDLCKeyCreate(
   sb_Params idlcParams,
   size_t privateKeyLen,
   const unsigned char *privateKeyValue,
   size_t publicKeyLen,
   const unsigned char *publicKeyValue,
   sb_PrivateKey *privateKey,
   sb_PublicKey *publicKey,
   sb_GlobalCtx sbCtx
);



/** Creates an RSA parameters object for the specified modulus size with
blinding option on.  RSA blinding randomizes the RSA private
exponentiation to guard against timing attacks.

You must first register the RSA blinding parameter creation function from a
provider before calling this function.
 
@param modulusSize [Input]
       The length in bits of the RSA modulus. This value must be greater
       than or equal to 512.
@param rngContext [Input]
       An RNG context (optional). Set to <code>NULL</code> if key generation
       and encryption will not be performed.
@param yieldCtx [Input]
       A yield context (optional). Set to <code>NULL</code> if yielding is not
       required.
@param rsaParams [Output]
       The RSA parameters object pointer.
@param sbCtx [Input]
       A global context.

@retval SB_ERR_BAD_INPUT
        The modulus size is invalid.
@retval SB_ERR_NULL_PARAMS_PTR
        The <code>rsaParams</code> object pointer is <code>NULL</code>.
@retval SB_FAIL_ALLOC
        Memory allocation failure.
@retval SB_SUCCESS
        Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSABlindingParamsCreate(
   size_t modulusSize,
   sb_RNGCtx rngContext,
   sb_YieldCtx yieldCtx,
   sb_Params * RSAParams,
   sb_GlobalCtx sbCtx
);


/** Retrieves the key values and their lengths from an RSA private
and/or public key object.

The following values and their lengths can be retrieved from an RSA private
key: <code>n</code>, <code>d</code>, <code>p</code>, <code>q</code>, <code>d
mod p-1</code>, <code>d mod q-1</code>, <code>q inverse mod p</code>.

The following values and their lengths can be retrieved from an RSA public
key: <code>n</code>, <code>e</code>.

If the prime factors <code>p</code> and <code>q</code> were generated or
computed by the library, this function will return the primes such that
<code>p</code> is numerically greater or equal to <code>q</code>. Otherwise,
if these primes were supplied during key setting, this function will
return them as given.

If the length of a key data value is known, a pointer to a buffer large
enough to hold the key data value should be passed in the appropriate
argument and its length in the corresponding length argument. This function
will copy the value into the buffer and set the actual length of the value in
the length argument.

If a key data value argument is <code>NULL</code>, or the argument is not
<code>NULL</code> but the corresponding length argument is too small, this
function will set the correct length of the key data value in the length
argument.

Set both the parameter argument and its length to <code>NULL</code> for
any parameters that are to be ignored.

@param rsaParams [Input]
       An RSA parameters object.
@param privateKey [Input]
       An RSA private key object.
@param publicKey [Input]
       An RSA public key object.
@param eLen [Input/Output]
       The length in bytes of the public exponent.
@param e [Output]
       The public exponent.
@param n [Output]
       Modulus.
@param d [Output]
       The private exponent.
@param p [Output]
       First large prime factor of the modulus.
@param q [Output]
       Second large prime factor of the modulus.
@param dModPm1 [Output]
       d mod p-1 CRT coefficient.
@param dModQm1 [Output]
       d mod q-1 CRT coefficient.
@param qInvModP [Output]
       q inverse mod p CRT coefficient.
@param sbCtx [Input]
       A global context.

@retval SB_ERR_NULL_PARAMS
        The <code>rsaParams</code> object is <code>NULL</code>.
@retval SB_ERR_BAD_PARAMS
        The <code>rsaParams</code> object is invalid.
@retval SB_ERR_NULL_INPUT
        Both the private key and public key objects are <code>NULL</code>.
@retval SB_ERR_BAD_PRIVATE_KEY
        The private key object is invalid.
@retval SB_ERR_BAD_PUBLIC_KEY
        The public key object is invalid.
@retval SB_SUCCESS
        Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAKeyGetV1(
   sb_Params rsaParams,
   sb_PrivateKey privateKey,
   sb_PublicKey publicKey,
   size_t *eLen,
   unsigned char *e,
   unsigned char *n,
   unsigned char *d,
   unsigned char *p,
   unsigned char *q,
   unsigned char *dModPm1,
   unsigned char *dModQm1,
   unsigned char *qInvModP,
   sb_GlobalCtx sbCtx
);


/** @see hu_RSAKeyGet */
#define hu_RSAKeyGetV2 hu_RSAKeyGet


/** Creates an RSA private and/or public key object from the given key
value(s), or, generates an RSA private and public key object from random
data.

To set the key(s):

A private key object can be created by supplying one of the following
combinations of key data:

<ul>
<li><code>p</code>, <code>q</code>, <code>d</code>
<li><code>p</code>, <code>q</code>, <code>d mod p-1</code>,
<code>d mod q-1</code>
<li><code>n</code>, <code>d</code>, <code>e</code>
<li><code>n</code>, <code>d</code>
</ul>

Private key objects will always be stored with the CRT coefficients. If any
of these values are not supplied, they will be computed from the available
data subject to the following:

<ul>
<li>If <code>p</code> and <code>q</code> are supplied, either
<code>d mod p-1</code> and <code>d mod q-1</code>, or <code>d</code>
must be supplied. If all three are passed, <code>d</code> will be ignored,
and no check is done to ensure that the values are self-consistent.
<li>If <code>p</code>, <code>q</code> and <code>qInvModP</code> are supplied,
then no check is done to ensure that the values are self-consistent.
<li>If <code>n</code> and <code>d</code> are supplied, but <code>e</code>
is not supplied, this function will assume a default value of
65537 (0x10001) as the public exponent.
</ul>

A public key object can be created by supplying <code>n</code> and,
optionally, <code>e</code>. If <code>e</code> is not supplied, this function
will assume a default value of 65537 (0x10001) as the public exponent.


To generate the keys:

Set all input buffers to <code>NULL</code>. Optionally, if the public
exponent is not supplied (i.e. set to <code>NULL</code>), this function will
assume a default value of 65537 (0x10001).

@param rsaParams [Input]
       An RSA parameters object.
@param eLen [Input]
       The length in bytes of the public exponent. Must be less than or equal
       to <code>nLen</code>.
@param e [Input]
       The public exponent.
@param n [Input]
       The modulus.
@param d [Input]
       The private exponent.
@param p [Input]
       First large prime factor of the modulus.
@param q [Input]
       Second large prime factor of the modulus.
@param dModPm1 [Input]
       d mod p-1 CRT coefficient.
@param dModQm1 [Input]
       d mod q-1 CRT coefficient.
@param qInvModP [Input]
       q inverse mod p CRT coefficient.
@param privateKey [Output]
       The private key object pointer.
@param publicKey [Output]
       The public key object pointer.
@param sbCtx [Input]
       A global context.

@retval SB_ERR_NULL_PARAMS
        The <code>rsaParams</code> object is <code>NULL</code>.
@retval SB_ERR_BAD_PARAMS
        The <code>rsaParams</code> object is invalid.
@retval SB_ERR_NULL_OUTPUT
        Both the private and public key object pointers are <code>NULL</code>.
@retval SB_ERR_BAD_INPUT
        Not enough key data supplied to create a key.
@retval SB_ERR_BAD_RSA_E_LEN
        The length of the public exponent is invalid.
@retval SB_FAIL_ALLOC
        Memory allocation failure.
@retval SB_SUCCESS
        Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAKeyCreate(
   sb_Params rsaParams,
   size_t eLen,
   const unsigned char *e,
   const unsigned char *n,
   const unsigned char *d,
   const unsigned char *p,
   const unsigned char *q,
   const unsigned char *dModPm1,
   const unsigned char *dModQm1,
   const unsigned char *qInvModP,
   sb_PrivateKey *privateKey,
   sb_PublicKey *publicKey,
   sb_GlobalCtx sbCtx
);


/** Creates an RSA private and/or public key object from the given key
value(s).

A private key object can be created by supplying one of the following
combinations of key data:

<ul>
<li><code>p</code>, <code>q</code>, <code>d</code>
<li><code>p</code>, <code>q</code>, <code>d mod p-1</code>,
<code>d mod q-1</code>
<li><code>n</code>, <code>d</code>, <code>e</code>
<li><code>n</code>, <code>d</code>
</ul>

Private key objects will always be stored with the CRT coefficients. If any
of these values are not supplied, they will be computed from the available
data subject to the following:

<ul>
<li>If <code>p</code> and <code>q</code> are supplied, either
<code>d mod p-1</code> and <code>d mod q-1</code>, or <code>d</code>
must be supplied. If all three are passed, <code>d</code> will be ignored,
and no check is done to ensure that the values are self-consistent.
<li>If <code>p</code>, <code>q</code> and <code>qInvModP</code> are supplied,
then no check is done to ensure that the values are self-consistent.
<li>If <code>n</code> and <code>d</code> are supplied, but <code>e</code>
is not supplied, this function will assume a default value of
65537 (0x10001) as the public exponent.
</ul>

A public key object can be created by supplying <code>n</code> and,
optionally, <code>e</code>. If <code>e</code> is not supplied, this function
will assume a default value of 65537 (0x10001) as the public exponent.

@param rsaParams [Input]
       An RSA parameters object.
@param eLen [Input]
       The length in bytes of the public exponent. Must be less than or equal
       to <code>nLen</code>.
@param e [Input]
       The public exponent.
@param nLen [Input]
       The length in bytes of the modulus.
@param n [Input]
       The modulus.
@param dLen [Input]
       The length in bytes of the private exponent. Must be less than or equal
       to <code>nLen</code>.
@param d [Input]
       The private exponent.
@param pLen [Input]
       The length in bytes of the first prime p. Must be less than or equal
       to <code>nLen</code>.
@param p [Input]
       First large prime factor of the modulus.
@param qLen [Input]
       The length in bytes of the second prime p. Must be less than or equal
       to <code>nLen</code>.
@param q [Input]
       Second large prime factor of the modulus.
@param dModPLen [Input]
       The length in bytes of the d mod p-1 CRT coefficient. Must be equal to
       <code>pLen</code>.
@param dModPm1 [Input]
       d mod p-1 CRT coefficient.
@param dModQLen [Input]
       The length in bytes of the d mod q-1 CRT coefficient. Must be equal to
       <code>qLen</code>.
@param dModQm1 [Input]
       d mod q-1 CRT coefficient.
@param qInvLen [Input]
       The length in bytes of q inverse mod p CRT coefficient.
@param qInvModP [Input]
       q inverse mod p CRT coefficient.
@param privateKey [Output]
       The private key object pointer.
@param publicKey [Output]
       The public key object pointer.
@param sbCtx [Input]
       A global context.

@retval SB_ERR_NULL_PARAMS
        The <code>rsaParams</code> object is <code>NULL</code>.
@retval SB_ERR_BAD_PARAMS
        The <code>rsaParams</code> object is invalid.
@retval SB_ERR_NULL_OUTPUT
        Both the private and public key object pointers are <code>NULL</code>.
@retval SB_ERR_BAD_INPUT
        Not enough key data supplied to create a key.
@retval SB_ERR_BAD_RSA_E_LEN
        The length of the public exponent is invalid.
@retval SB_FAIL_ALLOC
        Memory allocation failure.
@retval SB_SUCCESS
        Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAKeyCreateNoGen(
   sb_Params RSAParams,
   size_t pubExpByteLen,
   const unsigned char *e,
   const unsigned char *n,
   const unsigned char *d,
   const unsigned char *p,
   const unsigned char *q,
   const unsigned char *dModPm1,
   const unsigned char *dModQm1,
   const unsigned char *qInvModP,
   sb_PrivateKey *privateKey,
   sb_PublicKey *publicKey,
   sb_GlobalCtx sbCtx
);


/** Begins a signature generation operation by initializing an RSA PKCS #1 v1.5
signing context.

@param rsaParams   [Input] RSA parameters object.
@param privateKey  [Input] Private key object.
@param hashAlgId   [Input] Hash algorithm identifier.
                           This parameter determines which message digest
                           algorithm will be used.
                           Acceptable values include:
                               <tt>SB_RSA_PKCS1_V15_SIG_SHA1</tt>,
                               <tt>SB_RSA_PKCS1_V15_SIG_MD5</tt> and
                               <tt>SB_RSA_PKCS1_V15_SIG_MD2</tt>.
@param signContext [Output] RSA PKCS #1 v1.5 signing context pointer.
@param sbCtx       [Input] A global context.

@retval SB_ERR_NULL_PARAMS      RSA parameters object is NULL.
@retval SB_ERR_NULL_PRIVATE_KEY Private key object is NULL.
@retval SB_ERR_NULL_CONTEXT_PTR Signing context pointer is NULL.
@retval SB_ERR_BAD_PARAMS       RSA parameters object is invalid.
@retval SB_ERR_BAD_PRIVATE_KEY  Private key object is invalid.
@retval SB_ERR_BAD_HASH_TYPE    Hash algorithm identifier is invalid .
@retval SB_FAIL_ALLOC           Memory allocation failure.
@retval SB_FAIL_LOCK            Memory locking failure.
@retval SB_SUCCESS              Success.

*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAPKCS1v15SignBegin(
    sb_Params rsaParams,
    sb_PrivateKey privateKey,
    int hashAlgId,
    sb_Context *signContext,
    sb_GlobalCtx sbCtx
);


/** Updates an RSA PKCS #1 v1.5 signing context with a message block.
A multiple-block message can be supplied by repeating this function.

@param signContext  [Input/Output] PKCS #1 v1.5 signing context.
@param length       [Input] Message block length.
@param messageBlock [Input] Message block data.
@param sbCtx        [Input] A global context.

@retval SB_ERR_NULL_CONTEXT   Signing context is NULL.
@retval SB_ERR_BAD_CONTEXT    Signing context is invalid.
@retval SB_ERR_NULL_INPUT_BUF <tt>messageBlock</tt> pointer is NULL.
@retval SB_FAIL_LOCK          Memory locking failure.
@retval SB_SUCCESS            Success.

*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAPKCS1v15Sign(
    sb_Context signContext,
    size_t length,
    const unsigned char *messageBlock,
    sb_GlobalCtx sbCtx
);


/** Generates a signature value and destroys a PKCS#1 v1.5 signing context.

If the signature buffer is not NULL and the buffer is large enough, the
signature data is placed in the supplied buffer and <tt>length</tt> is set to
the number of bytes that were copied into the buffer.
If the signature buffer is set to NULL, the minimum size of the output buffer
is returned to <tt>length</tt>.


@param signContext [Input] RSA PKCS #1 v1.5 signing context pointer.
@param length      [Input/Output] Length of signature buffer as input.
                                  Length of the signature as output.
@param signature   [Output] Signature data buffer.
                            If set to NULL, the required buffer size is
                            returned in <tt>length</tt>.
@param sbCtx       [Input] A global context.

@retval SB_ERR_NULL_CONTEXT_PTR   Signing context pointer is NULL.
@retval SB_ERR_NULL_CONTEXT       Signing context is NULL.
@retval SB_ERR_BAD_CONTEXT        Signing context is invalid.
@retval SB_ERR_NULL_LENGTH        Length pointer is NULL.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN Output buffer is too small.
@retval SB_FAIL_ALLOC             Memory allocation failure.
@retval SB_FAIL_LOCK              Memory locking failure.
@retval SB_SUCCESS                Success.

*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAPKCS1v15SignEnd(
    sb_Context *signContext,
    size_t *length,
    unsigned char *signature,
    sb_GlobalCtx sbCtx
);


/** Begins a signature verification operation by initializing an RSA PKCS #1
v1.5 verification context.

@param rsaParams     [Input] RSA parameters object.
@param publicKey     [Input] Public key object.
@param signatureLen  [Input] Length of the signature.
@param signature     [Input] Signature.
@param verifyContext [Output] RSA PKCS #1 v1.5 verification context pointer.
@param sbCtx         [Input] A global context.

@retval SB_ERR_NULL_PARAMS       RSA parameters object is NULL.
@retval SB_ERR_NULL_PUBLIC_KEY   Public key object is NULL.
@retval SB_ERR_NULL_CONTEXT_PTR  Verification context pointer is NULL.
@retval SB_ERR_BAD_PARAMS        RSA parameters object  is invalid.
@retval SB_ERR_BAD_PUBLIC_KEY    Public key object is invalid.
@retval SB_ERR_NULL_SIGNATURE    Signature pointer is NULL.
@retval SB_ERR_BAD_SIGNATURE_LEN Signature length does not match the
                                 RSA modulus size
@retval SB_FAIL_BAD_PADDING      Signature was not properly padded.
@retval SB_ERR_BAD_HASH_TYPE     Invalid hash type specified.
@retval SB_FAIL_ALLOC            Memory allocation failure.
@retval SB_FAIL_LOCK             Memory locking failure.
@retval SB_SUCCESS               Success.

*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAPKCS1v15VerifyBegin(
    sb_Params rsaParams,
    sb_PublicKey publicKey,
    size_t signatureLen,
    const unsigned char *signature,
    sb_Context *verifyContext,
    sb_GlobalCtx sbCtx
);


/** Updates an RSA PKCS #1 v1.5 verification context with a message block.
A multiple-block message can be supplied by repeating this function

@param verifyContext [Input/Output] RSA PKCS#1 v1.5 verification context.
@param length        [Input] Message block length.
@param messageBlock  [Input] Message block data.
@param sbCtx         [Input] A global context.

@retval SB_ERR_NULL_CONTEXT   Verification context is NULL.
@retval SB_ERR_BAD_CONTEXT    Verification context is invalid.
@retval SB_ERR_NULL_INPUT_BUF <tt>messageBlock</tt> pointer is NULL.
@retval SB_FAIL_LOCK          Memory locking failure.
@retval SB_SUCCESS            Success.

*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAPKCS1v15Verify(
    sb_Context verifyContext,
    size_t length,
    const unsigned char *messageBlock,
    sb_GlobalCtx sbCtx
);


/** Verifies the signature and destroys a PKCS#1 v1.5 verify context.
If the verification is successful, the <tt>result</tt> will be set to a non-zero
value.

@param verifyContext [Input] PKCS#1 v1.5 verify context pointer.
@param result        [Output] Verification result.
                              If the signature is valid, this value is set to
                              a non-zero value; otherwise it is set to zero.
@param sbCtx         [Input] A global context.

@retval SB_ERR_NULL_CONTEXT_PTR Verification context pointer is NULL.
@retval SB_ERR_NULL_CONTEXT     Verification context is NULL.
@retval SB_ERR_BAD_CONTEXT      Verification context is invalid.
@retval SB_FAIL_ALLOC           Memory allocation failure.
@retval SB_FAIL_LOCK            Memory locking failure.
@retval SB_SUCCESS              Success.

*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAPKCS1v15VerifyEnd(
    sb_Context *verifyContext,
    int *result,
    sb_GlobalCtx sbCtx
);




/** Begins a PKCS#1 encryption operation by initializing a PKCS#1 v1.5
encryption context.

@param rsaParams  [Input] RSA parameters object.
@param publicKey  [Input] RSA public key object.
@param encContext [Output] RSA PKCS #1 v1.5 encryption context pointer.
@param sbCtx      [Input] A global context.

@retval SB_ERR_NULL_PARAMS      RSA parameters object is NULL.
@retval SB_ERR_NULL_PUBLIC_KEY  Public key object is NULL.
@retval SB_ERR_NULL_CONTEXT_PTR Encryption context pointer is NULL.
@retval SB_ERR_BAD_PARAMS       RSA parameters object is invalid.
@retval SB_ERR_BAD_PUBLIC_KEY   Public key object is invalid.
@retval SB_ERR_NO_RNG           RNG does not exist in the <tt>rsaParams</tt>.
@retval SB_FAIL_ALLOC           Memory allocation failure.
@retval SB_FAIL_LOCK            Memory locking failure.
@retval SB_SUCCESS              Success.

*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAPKCS1v15EncryptBegin(
    sb_Params rsaParams,
    sb_PublicKey publicKey,
    sb_Context *encContext,
    sb_GlobalCtx sbCtx
);


/** Encrypts plaintext using PKCS#1 v1.5. Multiple-block plaintext can be
supplied by repeating this function. Note that each time this function is
called there may, or may not be, any output (ciphertext).

If the ciphertext buffer is not NULL and the buffer is large enough, the
ciphertext is copied into the supplied buffer and <tt>ciphertextLen</tt>
is set to the number of bytes that were copied into the buffer.
If the ciphertext buffer is set to NULL, its maximum size, including padding,
is returned to <tt>ciphertextLen</tt>.
If the size returned is zero, the context is updated; otherwise, the context
is unchanged.

@param encContext    [Input/Output] RSA PKCS #1 v1.5 encryption context.
@param plaintextLen  [Input] Length of the plaintext block.
@param plaintext     [Input] Plaintext block.
@param ciphertextLen [Input/Output] Length of ciphertext buffer as input.
                                    Length of the ciphertext as output.
@param ciphertext    [Output] Ciphertext buffer.
                              If set to NULL, the maximum size of the
                              ciphertext buffer is returned in
                              <tt>ciphertextLen</tt>.
@param sbCtx         [Input] A global context.

@retval SB_ERR_NULL_CONTEXT            Encryption context is NULL.
@retval SB_ERR_NULL_INPUT_BUF          Plaintext pointer is NULL.
@retval SB_ERR_NULL_OUTPUT_BUF_LEN_PTR <tt>ciphertextLen</tt> pointer is NULL.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN      Supplied output buffer is too small.
@retval SB_ERR_BAD_CONTEXT             Encryption context is invalid.
@retval SB_FAIL_LOCK                   Memory locking failure.
@retval SB_SUCCESS                     Success.
@retval SB_X                           Any return codes from
                                       <tt>hu_RSAPublicEncrypt</tt> may also
                                       be returned.

*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAPKCS1v15Encrypt(
    sb_Context encContext,
    size_t plaintextLen,
    const unsigned char *plaintext,
    size_t *ciphertextLen,
    unsigned char *ciphertext,
    sb_GlobalCtx sbCtx
);


/** Completes a PKCS#1 encrypt operation and destroys the PKCS#1 v1.5
encryption context. This function may encrypt the remaining plaintext from
a previous call to <tt>hu_RSAPKCS1v15Encrypt</tt>.

If the ciphertext buffer is not NULL and the buffer is large enough, any
remaining ciphertext is copied into the supplied buffer and
<tt>ciphertextLen</tt> is set to the number of bytes that were copied into
the buffer.
If the ciphertext buffer is set to NULL, its maximum size, including padding,
is returned in <tt>ciphertextLen</tt>.

@param encContext    [Input/Output] RSA PKCS #1 v1.5 encryption context pointer.
@param ciphertextLen [Input/Output] Length of ciphertext buffer as input.
                                    Length of the ciphertext as output.
@param ciphertext    [Output] Pointer to the supplied ciphertext buffer.
                              If set to NULL, the maximum size of the 
                              ciphertext buffer is returned in 
                              <tt>ciphertextLen</tt>.
@param sbCtx         [Input] A global context.

@retval SB_ERR_NULL_CONTEXT_PTR        Encryption context pointer is NULL.
@retval SB_ERR_NULL_CONTEXT            Encryption context is NULL.
@retval SB_ERR_NULL_OUTPUT_BUF_LEN_PTR <tt>ciphertextLen</tt> pointer is NULL.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN      Output buffer is too small.
@retval SB_ERR_BAD_CONTEXT             Encryption context is invalid.
@retval SB_FAIL_LOCK                   Memory locking failure.
@retval SB_SUCCESS                     Success.
@retval SB_X                           Any return codes from
                                       <tt>hu_RSAPublicEncrypt</tt> may also
                                       be returned.

*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAPKCS1v15EncryptEnd(
    sb_Context *encContext,
    size_t *ciphertextLen,
    unsigned char *ciphertext,
    sb_GlobalCtx sbCtx
);


/** Begins a PKCS#1 decryption operation by initializing a PKCS#1 v1.5
decryption context.

@param rsaParams  [Input] RSA parameters object.
@param privateKey [Input] RSA private key object.
@param decContext [Output] RSA PKCS #1 v1.5 decryption context pointer.
@param sbCtx      [Input] A global context.

@retval SB_ERR_NULL_PARAMS      RSA parameters object is NULL.
@retval SB_ERR_NULL_PRIVATE_KEY Private key object is NULL.
@retval SB_ERR_NULL_CONTEXT_PTR Decryption context pointer is NULL.
@retval SB_ERR_BAD_PARAMS       RSA parameters object is invalid.
@retval SB_ERR_BAD_PRIVATE_KEY  Private key object is invalid.
@retval SB_FAIL_ALLOC           Memory allocation failure.
@retval SB_FAIL_LOCK            Memory locking failure.
@retval SB_SUCCESS              Success.

*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAPKCS1v15DecryptBegin(
    sb_Params rsaParams,
    sb_PrivateKey privateKey,
    sb_Context *decContext,
    sb_GlobalCtx sbCtx
);


/** Decrypts ciphertext using PKCS#1 v1.5. Multiple-block ciphertext can be
supplied by repeating this function. The total length of ciphertext must be a
multiple of the size of the public modulus. Note that there may, or may not be,
output for each call.

If the plaintext buffer is not NULL and the buffer is large enough, the
plaintext is copied into the supplied buffer and <tt>plaintextLen</tt> is set
to the number of bytes that were copied into the buffer.
If the size returned is zero, the context is updated; otherwise, the context is
unchanged.
A <tt>SB_ERR_BAD_OUTPUT_BUF_LEN</tt> code will be returned if the decrypted
text with padding removed can not fit into the provided buffer.
Therefore, it is possible to supply a buffer of smaller size than the upper
bound without encountering an error if the caller knows beforehand how large
the decrypted plaintext will be.
If the plaintext buffer is set to NULL, an upper bound of the size of output
is returned to <tt>plaintextLen</tt>.

@param decContext    [Input/Output] RSA PKCS #1 v1.5 decryption context.
@param ciphertextLen [Input] Length of ciphertext block.
@param ciphertext    [Input] Ciphertext block.
@param plaintextLen  [Input/Output] Length of plaintext buffer as input.
                                    Length of the plaintext as output.
@param plaintext     [Output] Plaintext buffer.
                              If set to NULL, an upper bound of output is
                              returned in <tt>plaintextLen</tt>.
@param sbCtx         [Input] A global context.

@retval SB_ERR_NULL_INPUT_BUF          Ciphertext pointer is NULL.
@retval SB_ERR_NULL_OUTPUT_BUF_LEN_PTR <tt>plaintextLen</tt> pointer is NULL.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN      Output buffer is too small.
@retval SB_ERR_NULL_CONTEXT            Decryption context is NULL.
@retval SB_ERR_BAD_CONTEXT             Decryption context is invalid.
@retval SB_FAIL_BAD_PADDING            Decrypted plaintext was not properly
                                       padded.
@retval SB_FAIL_LOCK                   Memory locking failure.
@retval SB_SUCCESS                     Success.
@retval SB_X                           Any return codes from
                                       <tt>hu_RSAPrivateDecrypt</tt> may also
                                       be returned.

*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAPKCS1v15Decrypt(
    sb_Context decContext,
    size_t ciphertextLen,
    const unsigned char *ciphertext,
    size_t *plaintextLen,
    unsigned char *plaintext,
    sb_GlobalCtx sbCtx
);


/** Completes a decryption operation and destroys a PKCS#1 v1.5 decryption
context.

When this function is called there should be no remaining ciphertext blocks to
decrypt, since the size of the ciphertext must always be a multiple of the RSA
modulus size.
If any remaining ciphertext is detected in the operational context,
<tt>SB_ERR_BAD_INPUT_BUF_LEN</tt> is returned.
Under normal conditions, <tt>SB_SUCCESS</tt> is always returned.

@param decContext [Input/Output] RSA PKCS #1 v1.5 decryption context pointer.
@param sbCtx      [Input] A global context.

@retval SB_ERR_NULL_CONTEXT_PTR  Decryption context pointer is NULL.
@retval SB_ERR_NULL_CONTEXT      Decryption context is NULL.
@retval SB_ERR_BAD_CONTEXT       Decryption context is invalid.
@retval SB_ERR_BAD_INPUT_BUF_LEN Input is not a multiple of the
                                 RSA ciphertext block size.
@retval SB_FAIL_LOCK             Memory locking failure.
@retval SB_SUCCESS               Success.
@retval SB_X                     Any return codes from
                                 <tt>hu_RSAPrivateDecrypt</tt> may also be
                                 returned.

*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAPKCS1v15DecryptEnd(
    sb_Context *decContext,
    sb_GlobalCtx sbCtx
);




/*====== PKCS #1 v1.5 Signature Padding Exponentiation Legacy Functions ======*/

/** Begins a PKCS#1 signature padded private exponentiation operation by
initializing a PKCS#1 v1.5 signature context with padding.

@param rsaParams  [Input] RSA parameters object.
@param privateKey [Input] RSA private key object.
@param sigContext [Output] RSA PKCS #1 v1.5 signature context pointer.
@param sbCtx      [Input] A global context.

@retval SB_ERR_NULL_PARAMS      RSA parameters object is NULL.
@retval SB_ERR_NULL_PRIVATE_KEY Private key object is NULL.
@retval SB_ERR_NULL_CONTEXT_PTR Signing context pointer is NULL.
@retval SB_ERR_BAD_PARAMS       RSA parameters object is invalid.
@retval SB_ERR_BAD_PRIVATE_KEY  Private key object is invalid.
@retval SB_FAIL_ALLOC           Memory allocation failure.
@retval SB_FAIL_LOCK            Memory locking failure.
@retval SB_SUCCESS              Success.


*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAPKCS1v15SigPadBegin(
    sb_Params rsaParams,
    sb_PrivateKey privateKey,
    sb_Context *sigContext,
    sb_GlobalCtx sbCtx
);


/** Exponentiates a message using PKCS#1 v1.5 signature padding. Multiple-block
plaintext can be supplied by repeating this function.
Note that each time this function is called there may, or may not be, any
output (ciphertext).

If the signature buffer is not NULL and the buffer is large enough, the
signature is copied into the supplied buffer and <tt>sigtextLen</tt> is set
to the number of bytes that were copied into the buffer.
If the signature buffer is set to NULL, its maximum size, including padding,
is returned to <tt>sigtextLen</tt>.
If the size returned is zero, the context is updated; otherwise, the context
is unchanged.


@param sigContext [Input/Output] RSA PKCS #1 v1.5 signing context.
@param messageLen [Input] Length of the plaintext block.
@param message    [Input Plaintext block.
@param sigtextLen [Input/Output] Length of signature buffer as input.
                                 Length of the actual signature as output.
@param sigtext    [Output] Signature buffer.
                           If set to NULL, the maximum size of the signature
                           buffer is returned in <tt>sigtextLen</tt>.
@param sbCtx      [Input] A global context.

@retval SB_ERR_NULL_CONTEXT            Signing context is NULL.
@retval SB_ERR_NULL_INPUT_BUF          Plaintext pointer is NULL.
@retval SB_ERR_NULL_OUTPUT_BUF_LEN_PTR <tt>sigtextLen</tt> pointer is NULL.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN      Supplied output buffer is too small.
@retval SB_ERR_BAD_CONTEXT             Signing context is invalid.
@retval SB_FAIL_LOCK                   Memory locking failure.
@retval SB_SUCCESS                     Success.
@retval SB_X                           Any return codes from
                                       <tt>hu_RSAPublicEncrypt</tt> may also
                                       be returned.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAPKCS1v15SigPadExpo(
    sb_Context sigContext,
    size_t messageLen,
    const unsigned char *message,
    size_t *sigtextLen,
    unsigned char *sigtext,
    sb_GlobalCtx sbCtx
);


/** Completes a PKCS#1 signature padded private exponentiation operation and
destroys the PKCS#1 v1.5 signing context.
This function may exponentiate the remaining plaintext from a previous call to
<tt>hu_RSAPKCS1v15SigPadExpo</tt>.

If the signature buffer is not NULL and the buffer is large enough, the
ciphertext is copied into the supplied buffer and <tt>sigtextLen</tt> is set
to the number of bytes that were copied into the buffer.
If the signature buffer is set to NULL, its maximum size is returned in
<tt>sigtextLen</tt> and nothing else is done.


@param sigContext [Input/Output] RSA PKCS #1 v1.5 signing context pointer.
@param sigtextLen [Input/Output] Length of signature buffer as input.
                                 Length of the signature as output.
@param sigtext    [Output] Pointer to the supplied signature buffer.
                           If set to NULL, the maximum size of the signature
                           buffer is returned in <tt>sigtextLen</tt>.
@param sbCtx      [Input] A global context.

@retval SB_ERR_NULL_OUTPUT_BUF_LEN_PTR SigtextLen pointer is NULL
@retval SB_ERR_BAD_OUTPUT_BUF_LEN      Output buffer is too small.
@retval SB_ERR_NULL_CONTEXT            Signing context is NULL.
@retval SB_ERR_NULL_CONTEXT_PTR        Signing context pointer is NULL.
@retval SB_ERR_BAD_CONTEXT             Signing context is invalid.
@retval SB_SUCCESS                     Success.
@retval SB_FAIL_LOCK                   Memory locking failure.
@retval SB_X                           Any return codes from
                                       <tt>hu_RSAPrivateEncrypt</tt> may also
                                       be returned.

*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAPKCS1v15SigPadEnd(
    sb_Context *sigContext,
    size_t *sigtextLen,
    unsigned char *sigtext,
    sb_GlobalCtx sbCtx
);


/** Begins a PKCS#1 signature de-padded exponentiation operation by
initializing a PKCS#1 v1.5 verify context.

@param rsaParams  [Input] RSA parameters object.
@param publicKey  [Input] RSA public key object.
@param verContext [Output] RSA PKCS #1 v1.5 verify context pointer.
@param sbCtx      [Input] A global context.

@retval SB_ERR_NULL_PARAMS      RSA parameters object is NULL.
@retval SB_ERR_NULL_PUBLIC_KEY  Public key object is NULL.
@retval SB_ERR_NULL_CONTEXT_PTR Verify context pointer is NULL.
@retval SB_ERR_BAD_PARAMS       RSA parameters object is invalid.
@retval SB_ERR_BAD_PUBLIC_KEY   Public key object is invalid.
@retval SB_FAIL_ALLOC           Memory allocation failure.
@retval SB_FAIL_LOCK            Memory locking failure.
@retval SB_SUCCESS              Success.


*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAPKCS1v15VerPadBegin(
    sb_Params rsaParams,
    sb_PublicKey publicKey,
    sb_Context *verContext,
    sb_GlobalCtx sbCtx
);


/** Exponentiates a signature text using PKCS#1 v1.5 signature de-padding.
Multiple-block signature text can be supplied by repeating this function.
Note that each time this function is called there may, or may not be, any
output (plaintext).

If the verification buffer is not NULL and the buffer is large enough, the
plaintext is copied into the supplied buffer and <tt>messageLen</tt>
is set to the number of bytes that were copied into the buffer.
If the verification buffer is set to NULL, its maximum size, including padding, is returned to <tt>messageLen</tt>.
If the size returned is zero, the context is updated; otherwise, the context
is unchanged.


@param verContext [Input/Output] RSA PKCS #1 v1.5 signing context.
@param sigtextLen [Input] Length of the signature block.
@param sigtext    [Input] Signature block.
@param messageLen [Input/Output] Length of plaintext buffer as input.
                                 Length of the actual plaintext as output.
@param message    [Output] Plaintext buffer.
                           If set to NULL, the maximum size of the plaintext
                           buffer is returned in <tt>messageLen</tt>.
@param sbCtx      [Input] A global context.

@retval SB_ERR_NULL_CONTEXT            Verification context is NULL.
@retval SB_ERR_NULL_INPUT_BUF          Signature pointer is NULL.
@retval SB_ERR_NULL_OUTPUT_BUF_LEN_PTR <tt>messageLen</tt> pointer is NULL.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN      Supplied output buffer is too small.
@retval SB_ERR_BAD_CONTEXT             Verification context is invalid.
@retval SB_FAIL_LOCK                   Memory locking failure.
@retval SB_SUCCESS                     Success.
@retval SB_X                           Any return codes from
                                       <tt>hu_RSAPublicEncrypt</tt> may also
                                       be returned.

*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAPKCS1v15VerPadExpo(
    sb_Context verContext,
    size_t sigtextLen,
    const unsigned char *sigtext,
    size_t *messageLen,
    unsigned char *message,
    sb_GlobalCtx sbCtx
);


/** Completes a PKCS#1 signature de-padded public exponentiation operation and
destroys the PKCS#1 v1.5 verification context.


@param verContext [Input/Output] The RSA PKCS#1 verification context pointer.
@param sbCtx      [Input] A global context.

@retval SB_ERR_NULL_CONTEXT      Verification context is NULL.
@retval SB_ERR_NULL_CONTEXT_PTR  Verification context pointer is NULL.
@retval SB_ERR_BAD_CONTEXT       Verification context is invalid.
@retval SB_ERR_BAD_INPUT_BUF_LEN Input was not a multiple of the
                                 RSA ciphertext block size.
@retval SB_FAIL_LOCK             Memory locking failure.
@retval SB_SUCCESS               Success.

*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAPKCS1v15VerPadEnd(
    sb_Context *verContext,
    sb_GlobalCtx sbCtx
);

/** @} */

#ifdef __cplusplus
}
#endif

#endif

