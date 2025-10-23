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
/* $Id: huecc.h 44390 2013-03-25 17:52:29Z hwang $
 * $Source$
 * $Name$
 */
#ifndef HUECC_H
#define HUECC_H

/** @file */

#ifdef __cplusplus
extern "C" {
#endif

#include "sbdef.h"
#include "hukdf.h"
#include "humac.h"

/** @addtogroup hu_ecc_api ECC APIs
 *
 * @{
 */

/** ID for the sect163k1 elliptic curve. */
#define HU_ECC_CURVE_SECT163K1 1

/** ID for the sect163r2 elliptic curve. */
#define HU_ECC_CURVE_SECT163R2 2

/** ID for the sect233k1 elliptic curve. */
#define HU_ECC_CURVE_SECT233K1 3

/** ID for the sect233r1 elliptic curve. */
#define HU_ECC_CURVE_SECT233R1 4

/** ID for the sect239k1 elliptic curve. */
#define HU_ECC_CURVE_SECT239K1 5

/** ID for the sect283k1 elliptic curve. */
#define HU_ECC_CURVE_SECT283K1 6

/** ID for the sect283r1 elliptic curve. */
#define HU_ECC_CURVE_SECT283R1 7

/** ID for the sect409k1 elliptic curve. */
#define HU_ECC_CURVE_SECT409K1 8

/** ID for the sect409r1 elliptic curve. */
#define HU_ECC_CURVE_SECT409R1 9

/** ID for the sect571k1 elliptic curve. */
#define HU_ECC_CURVE_SECT571K1 10

/** ID for the sect571r1 elliptic curve. */
#define HU_ECC_CURVE_SECT571R1 11

/** ID for the secp160r1 elliptic curve. */
#define HU_ECC_CURVE_SECP160R1 12

/** ID for the secp192r1 elliptic curve. */
#define HU_ECC_CURVE_SECP192R1 13

/** ID for the secp224r1 elliptic curve. */
#define HU_ECC_CURVE_SECP224R1 14

/** ID for the secp256r1 elliptic curve. */
#define HU_ECC_CURVE_SECP256R1 15

/** ID for the secp384r1 elliptic curve. */
#define HU_ECC_CURVE_SECP384R1 16

/** ID for the secp521r1 elliptic curve. */
#define HU_ECC_CURVE_SECP521R1 17

/** ID for the wtls5 elliptic curve. */
#define HU_ECC_CURVE_WTLS5 18

/** Reserved for WAPI1. */
/* #define HU_ECC_CURVE_WAPI1 19 */

/** German BrainPool curves: */

/** ID for the gbp160r1 elliptic curve. */
#define HU_ECC_CURVE_GBP160R1 101

/** ID for the gbp160t1 elliptic curve. */
#define HU_ECC_CURVE_GBP160T1 102

/** ID for the gbp192r1 elliptic curve. */
#define HU_ECC_CURVE_GBP192R1 103

/** ID for the gbp192t1 elliptic curve. */
#define HU_ECC_CURVE_GBP192T1 104

/** ID for the gbp224r1 elliptic curve. */
#define HU_ECC_CURVE_GBP224R1 105

/** ID for the gbp224t1 elliptic curve. */
#define HU_ECC_CURVE_GBP224T1 106

/** ID for the gbp256r1 elliptic curve. */
#define HU_ECC_CURVE_GBP256R1 107

/** ID for the gbp256t1 elliptic curve. */
#define HU_ECC_CURVE_GBP256T1 108

/** ID for the gbp320r1 elliptic curve. */
#define HU_ECC_CURVE_GBP320R1 109

/** ID for the gbp320t1 elliptic curve. */
#define HU_ECC_CURVE_GBP320T1 110

/** ID for the gbp384r1 elliptic curve. */
#define HU_ECC_CURVE_GBP384R1 111

/** ID for the gbp384t1 elliptic curve. */
#define HU_ECC_CURVE_GBP384T1 112

/** ID for the gbp512r1 elliptic curve. */
#define HU_ECC_CURVE_GBP512R1 113

/** ID for the gbp512t1 elliptic curve. */
#define HU_ECC_CURVE_GBP512T1 114


/** Finite field types */
#define SB_ECC_FIELD_F2M   2
#define SB_ECC_FIELD_FP    3

/** Point compression input policy values */
#define SB_ECC_POINT_INPUT_ACCEPT   0
#define SB_ECC_POINT_INPUT_REJECT   1

/** Point compresssion output mode values */
#define SB_ECC_COMPRESSION_OFF       2
#define SB_ECC_COMPRESSION_ON        4
#define SB_ECC_COMPRESSION_HYBRID    6


/** Creates an ECC parameters object for the specified curve.

An RNG context must be supplied if key generation or signature generation
will be performed. A yielding context must be supplied if yielding will be
performed.

@param[in]  curve      The curve identifier. The acceptable values are one of 
                       the <tt>HU_ECC_CURVE_*</tt> macros.
@param[in]  rngCtx     An RNG context. (Optional - set to <tt>NULL</tt> if key 
                       generation or signature generation will not be 
		       performed.)
@param[in]  yieldCtx   A yield context. (Optional - set to <tt>NULL</tt> if 
                       yielding is not required.)
@param[out] eccParams  The ECC parameters object pointer.
@param[in]  sbCtx      A global context.

@retval SB_ERR_ECC_BAD_CURVE   The curve identifier is invalid.
@retval SB_ERR_NULL_PARAMS_PTR The <tt>eccParams</tt> object pointer is 
                               <tt>NULL</tt>.
@retval SB_FAIL_ALLOC          Memory allocation failure.
@retval SB_SUCCESS             Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ECCParamsCreate(
    int curve,
    sb_RNGCtx rngCtx,
    sb_YieldCtx yieldCtx,
    sb_Params * eccParams,
    sb_GlobalCtx sbCtx
);


/** Sets the input policy and output format of elliptic curve point
representations in the ECC parameters object.

This function affects all functions that accept elliptic curve point
representations as input or produce them as output (e.g. creation
of elliptic curve key objects).

By default, elliptic curve points can be passed as input in any supported
representation; on output, they will be returned in compressed
representation.

The <tt>mode</tt> can be set to change the output format of elliptic
curve points. The <tt>policy</tt> can be set to either accept points in
any supported representation, or, to reject input that is not in the same
representation chosen for output. A detailed discussion of elliptic curve 
points and point compression may be found in the "Point Compression" section of
the <em>Security Builder API User's Guide</em>.

For example, if the input policy is <tt>SB_ECC_POINT_INPUT_REJECT</tt>
and the output mode is <tt>SB_ECC_COMPRESSION_OFF</tt>, then elliptic
curve points will be returned in uncompressed representation, and only
uncompressed points will be accepted as input.

A more detailed discussion of elliptic curve points and point compression is
contained in the "Point Compression" section of the <em>Security Builder API 
User's Guide</em>.

@param[in]     policy     Point compression input policy.
@param[in]     mode       Point compression output mode.
@param[in,out] eccParams  An ECC parameters object.
@param[in]     sbCtx      A global context.

@retval SB_ERR_BAD_INPUT   The policy or mode is invalid.
@retval SB_ERR_NULL_PARAMS The <tt>eccParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS  
@retval SB_SUCCESS         Success.
*/
extern
SB_EXPORT
int
SB_CALLCONV
hu_ECCParamsModeSet(
    int policy,
    int mode,
    sb_Params eccParams,
    sb_GlobalCtx sbCtx
);

/** Gets the input policy and output format of elliptic curve point
representations in the ECC parameters object.

For a description of  <tt>policy</tt> and <tt>mode</tt> values and what
they mean, see <tt>hu_ECCParamsModeSet()</tt>.

@param[in]  eccParams  An ECC parameters object.
@param[out] policy     Point compression input policy. (Optional)
@param[out] mode       Point compression output mode. (Optional)
@param[in]  sbCtx      A global context.

@retval SB_ERR_NULL_PARAMS The <tt>eccParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS  
@retval SB_SUCCESS         Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ECCParamsModeGet(
    sb_Params eccParams,
    int* policy,
    int* mode,
    sb_GlobalCtx sbCtx
);



/** Retrieves the ECC curve identifier from an ECC parameters object.

@param[in]  eccParams  An ECC parameters object.
@param[out] curve      The curve identifier.
@param[in]  sbCtx      A global context.

@retval SB_ERR_NULL_PARAMS The <tt>eccParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS  
@retval SB_ERR_NULL_OUTPUT The curve identifier pointer is <tt>NULL</tt>.
@retval SB_SUCCESS         Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ECCParamsInfo(
    sb_Params eccParams,
    int * curve,
    sb_GlobalCtx sbCtx
);


/** Retrieves settings from an ECC parameters object.

One or more of the domain parameters can be retrieved in one call to this
function.

If the length of a parameter is known, then a pointer to a buffer large enough 
to hold the parameter should be passed in the appropriate argument and its 
length in the corresponding length argument. This function will copy the value 
into the buffer and set the actual length of the value in the length argument.

If a parameter argument is <tt>NULL</tt>, then this function will set the
correct length of the parameter in the length argument.  If the argument is not
<tt>NULL</tt> but the corresponding length argument is too small, this
function will return an error.

Set both the parameter argument and its length to <tt>NULL</tt> for
any parameters that are to be ignored.

@param[in]  eccParams  An ECC parameters object.
@param[out] fieldType  Type of underlying finite field. The two values that can 
                       be returned are <tt>SB_ECC_FIELD_F2M</tt> and 
		       <tt>SB_ECC_FIELD_FP</tt>.
@param[out] reducLen   The length (in bytes) of <tt>reduc</tt>.
@param[out] reduc      Prime (<tt>SB_ECC_FIELD_FP</tt>) or irreducible 
                       polynomial (<tt>SB_ECC_FIELD_F2M</tt>) defining the 
		       underlying finite field.
@param[out] seedLen    The length (in bytes) of <tt>seed</tt>.
@param[out] seed       The seed from which parameters were generated.
@param[out] aLen       The length (in bytes) of <tt>a</tt>.
@param[out] a          Coefficient <em>a</em> in the elliptic curve equation.
@param[out] bLen       The length (in bytes) of <tt>b</tt>.
@param[out] b          Coefficient <em>b</em> in the elliptic curve equation.
@param[out] GLen       The length (in bytes) of <tt>G</tt>.
@param[out] G          The generator or base point.
@param[out] OrdLen     The length (in bytes) of <tt>Ord</tt>.
@param[out] Ord        The order of the base point.
@param[out] CofactLen  The length (in bytes) of <tt>Cofact</tt>.
@param[out] Cofact     Cofactor.
@param[out] OIDLen     The length (in bytes) of <tt>OID</tt>.
@param[out] OID        The ASN.1 object identifier of curve parameters 
                       (DER-encoded).
@param[in]  sbCtx      A global context.

@retval SB_ERR_NULL_PARAMS_PTR    The <tt>eccParams</tt> object pointer is 
                                  <tt>NULL</tt>.
@retval SB_ERR_NULL_PARAMS        The <tt>eccParams</tt> object is 
                                  <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS         
@retval SB_ERR_BAD_OUTPUT_BUF_LEN The output buffer length is invalid.
@retval SB_SUCCESS                Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ECCParamsGet(
    sb_Params eccParams,
    int *fieldType,
    size_t *reducLen,
    unsigned char *reduc,
    size_t *seedLen,
    unsigned char *seed,
    size_t *aLen,
    unsigned char *a,
    size_t *bLen,
    unsigned char *b,
    size_t *GLen,
    unsigned char *G,
    size_t *OrdLen,
    unsigned char *Ord,
    size_t *CofactLen,
    unsigned char *Cofact,
    size_t *OIDLen,
    unsigned char *OID,
    sb_GlobalCtx sbCtx
);


/** Destroys an ECC parameters object.

<em>Note</em>: ECC contexts and key objects must be destroyed before their 
corresponding ECC parameters object is destroyed.

@param[in,out] eccParams  An ECC parameters object pointer.
@param[in]     sbCtx      A global context.

@retval SB_ERR_NULL_PARAMS_PTR The <tt>eccParams</tt> object pointer is 
                               <tt>NULL</tt>.
@retval SB_ERR_NULL_PARAMS     The <tt>eccParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS      
@retval SB_SUCCESS             Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ECCParamsDestroy(
    sb_Params *eccParams,
    sb_GlobalCtx sbCtx
);

/** @} */

/** @addtogroup hu_ecc_key_api ECC Key APIs
 *
 * @{
 */

/** Creates an ECC private and/or public key object from the given key
value(s).

If both the private and public key values are supplied, then a private key 
and/or a public key object can be created. These objects will be created from 
the corresponding key values.

If only a private key value is supplied, then a private key and/or a public key
object can be created. The public key will be computed from the private key.

If only a public key value is supplied, then only a public key object can be
created.

@param[in]  eccParams        An ECC parameters object.
@param[in]  privateKeyLen    The length (in bytes) of the private key value.
@param[in]  privateKeyValue  The private key value.
@param[in]  publicKeyLen     The length (in bytes) of the public key value.
@param[in]  publicKeyValue   The public key value.
@param[out] privateKey       The private key object pointer.
@param[out] publicKey        The public key object pointer.
@param[in]  sbCtx            A global context.

@retval SB_ERR_NULL_PARAMS          The <tt>eccParams</tt> object is 
                                    <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS           
@retval SB_ERR_NULL_PRI_KEY_BUF     The private key value is <tt>NULL</tt>.
@retval SB_ERR_BAD_PRI_KEY_BUF_LEN  The private key length is invalid.
@retval SB_ERR_NULL_PUB_KEY_BUF     The public key value is <tt>NULL</tt>.
@retval SB_ERR_BAD_PUB_KEY_BUF_LEN  The public key length is invalid.
@retval SB_ERR_BAD_INPUT            The public key value is invalid.
@retval SB_FAIL_INVALID_PRIVATE_KEY The private key value is invalid.
@retval SB_FAIL_ALLOC               Memory allocation failure.
@retval SB_SUCCESS                  Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ECCKeySet(
    sb_Params eccParams,
    size_t privateKeyLen,
    const unsigned char *privateKeyValue,
    size_t publicKeyLen,
    const unsigned char *publicKeyValue,
    sb_PrivateKey *privateKey,
    sb_PublicKey *publicKey,
    sb_GlobalCtx sbCtx
);


/** Creates an ECC private key object from random data, and, optionally,
the corresponding public key object.

The ECC parameter object must have been created with an RNG context.

@param[in]  eccParams   An ECC parameters object.
@param[out] privateKey  The private key object pointer.
@param[out] publicKey   The public key object pointer. If non-<tt>NULL</tt>, 
                        then a public key object is created in addition to the 
			private key.
@param[in]  sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS The <tt>eccParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS  
@retval SB_FAIL_ALLOC      Memory allocation failure.
@retval SB_SUCCESS         Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ECCKeyGen(
    sb_Params eccParams,
    sb_PrivateKey *privateKey,
    sb_PublicKey *publicKey,
    sb_GlobalCtx sbCtx
);


/** Retrieves the key values and their lengths from an ECC private
and/or public key object.

If the length of the key value is known, a pointer to a buffer large enough to 
hold the key value should be passed in the key value buffer and its length in 
the corresponding length argument. This function will copy the key value into 
the buffer and set the actual length of the key value in the length argument.

If key value buffer is <tt>NULL</tt>, then this function will set the correct 
length of the key value in the length argument. If the buffer is not 
<tt>NULL</tt> but buffer length is too small, this function will return an error
and also will set the correct length of the key value in length argument.

@param[in]     eccParams        An ECC parameters object.
@param[in]     privateKey       An ECC private key object.
@param[in]     publicKey        An ECC public key object.
@param[in,out] privateKeyLen    The length (in bytes) of the private key 
                                      buffer.
@param[out]    privateKeyValue  The private key buffer.
@param[in,out] publicKeyLen     The length (in bytes) of the public key buffer.
@param[out]    publicKeyValue   The public key buffer.
@param[in]     sbCtx            A global context.

@retval SB_ERR_NULL_PARAMS      The <tt>eccParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS  
@retval SB_ERR_NULL_INPUT          Both the private key and public key objects 
                                   are <tt>NULL</tt>.
@retval SB_ERR_BAD_PRIVATE_KEY     The private key object is invalid.
@retval SB_ERR_BAD_PRI_KEY_BUF_LEN The private key buffer length is invalid.
@retval SB_ERR_BAD_PUBLIC_KEY      The public key object is invalid.
@retval SB_ERR_BAD_PUB_KEY_BUF_LEN The public key buffer length is invalid.
@retval SB_ERR_NULL_KEY_LEN        The length of the key buffer is 
                                   <tt>NULL</tt>.
@retval SB_SUCCESS                 Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ECCKeyGet(
    sb_Params eccParams,
    sb_PrivateKey privateKey,
    sb_PublicKey publicKey,
    size_t *privateKeyLen,
    unsigned char *privateKeyValue,
    size_t *publicKeyLen,
    unsigned char *publicKeyValue,
    sb_GlobalCtx sbCtx
);


/** Expands the given ECC public key object so that subsequent operations
using the key may be faster.

Additional memory is allocated to store the expansion data in the public key
object. The amount of memory required depends on the optimization level of
the corresponding ECC parameters object.

@param[in] eccParams  An ECC parameters object.
@param[in] optLevel   Ignored.
@param[in] publicKey  An ECC public key object.
@param[in] sbCtx      A global context.

@retval SB_ERR_NULL_PARAMS     The <tt>eccParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS  
@retval SB_ERR_NULL_PUBLIC_KEY The <tt>publicKey</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PUBLIC_KEY  The <tt>publicKey</tt> object is invalid.
@retval SB_FAIL_ALLOC          Memory allocation failure.
@retval SB_SUCCESS             Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ECCKeyExpand(
    sb_Params eccParams,
    int optLevel,
    sb_PublicKey publicKey,
    sb_GlobalCtx sbCtx
);


/** Destroys an ECC private and/or public key object.

ECC key objects must be destroyed before the ECC parameters object is
destroyed.

@param[in]      eccParams   An ECC parameters object.
@param[in,out]  privateKey  An ECC private key object pointer.
@param[in,out]  publicKey   An ECC public key object pointer.
@param[in]      sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS      The <tt>eccParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS  
@retval SB_ERR_NULL_PRIVATE_KEY The <tt>privateKey</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PRIVATE_KEY  The <tt>privateKey</tt> object is invalid.
@retval SB_ERR_NULL_PUBLIC_KEY  The <tt>publicKey</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PUBLIC_KEY   The <tt>publicKey</tt> object is invalid.
@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ECCKeyDestroy(
    sb_Params eccParams,
    sb_PrivateKey *privateKey,
    sb_PublicKey *publicKey,
    sb_GlobalCtx sbCtx
);

/** @} */

/** @addtogroup hu_ecc_ecdh_api ECC ECDH APIs
 *
 * @{
 */

/** Generates a shared secret of the requested length by applying the ANSI
X9.42/X9.63 KDF with SHA-1 to the output of an ECDH key agreement.

@param[in]  eccParams        An ECC parameters object.
@param[in]  privateKey       An ECC private key object.
@param[in]  remotePublicKey  An ECC public key object.
@param[in]  addInfoLen       The length (in bytes) of additional information. 
                             (Optional)
@param[in]  addInfo          Additional information for use with the KDF. 
                             (Optional - set to <tt>NULL</tt> if not used.)
@param[in]  secretLen        The length (in bytes) of the shared secret.
@param[out] sharedSecret     The shared secret value.
@param[in]  sbCtx            A global context.

@retval SB_ERR_NULL_PARAMS        The <tt>eccParams</tt> object is 
                                  <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS  
@retval SB_ERR_NULL_PRIVATE_KEY   The <tt>privateKey</tt> object is 
                                  <tt>NULL</tt>.
@retval SB_ERR_BAD_PRIVATE_KEY    The <tt>privateKey</tt> object is invalid.
@retval SB_ERR_NULL_PUBLIC_KEY    The <tt>publicKey</tt> object is 
                                  <tt>NULL</tt>.
@retval SB_ERR_BAD_PUBLIC_KEY     The <tt>publicKey</tt> object is invalid.
@retval SB_ERR_NULL_ADDINFO       Additional information is <tt>NULL</tt>.
@retval SB_ERR_NULL_OUTPUT_BUF    The shared secret buffer is <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN The length of the shared secret is invalid.
@retval SB_FAIL_ALLOC             Memory allocation failure.
@retval SB_SUCCESS                Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ECDHSharedGen(
    sb_Params eccParams,
    sb_PrivateKey privateKey,
    sb_PublicKey remotePublicKey,
    size_t addInfoLen,
    const unsigned char *addInfo,
    size_t secretLen,
    unsigned char *sharedSecret,
    sb_GlobalCtx sbCtx
);


/** Generates a shared secret of fixed length by applying IEEE 1363 KDF1 to
the output of an ECDH key agreement.

@param[in]  eccParams        An ECC parameters object.
@param[in]  privateKey       An ECC private key object.
@param[in]  remotePublicKey  An ECC public key object.
@param[in]  addInfoLen       The length (in bytes) of additional information. 
                             (Optional)
@param[in]  addInfo          Additional information for use with the KDF. 
                             (Optional - set to <tt>NULL</tt> if not used.)
@param[in]  secretLen        The length (in bytes) of the shared secret. The 
                             only acceptable value is 
			     <tt>SB_SHA1_DIGEST_LEN</tt>.
@param[out]  sharedSecret    The shared secret value.
@param[in]  sbCtx            A global context.

@retval SB_ERR_NULL_PARAMS        The <tt>eccParams</tt> object is 
                                  <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS   
@retval SB_ERR_NULL_PRIVATE_KEY   <tt>privateKey</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PRIVATE_KEY    <tt>privateKey</tt> object is invalid.
@retval SB_ERR_NULL_PUBLIC_KEY    The <tt>publicKey</tt> object is 
                                  <tt>NULL</tt>.
@retval SB_ERR_BAD_PUBLIC_KEY     The <tt>publicKey</tt> object is invalid.
@retval SB_ERR_NULL_ADDINFO       Additional information is <tt>NULL</tt>.
@retval SB_ERR_NULL_OUTPUT_BUF    The shared secret buffer is <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN The shared secret length is invalid.
@retval SB_FAIL_ALLOC             Memory allocation failure.
@retval SB_SUCCESS                Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ECDHKDFIEEESharedGen(
    sb_Params eccParams,
    sb_PrivateKey privateKey,
    sb_PublicKey remotePublicKey,
    size_t addInfoLen,
    const unsigned char *addInfo,
    size_t secretLen,
    unsigned char *sharedSecret,
    sb_GlobalCtx sbCtx
);


/** Generates a shared secret that is the output of an ECDH key agreement.

If the length of the shared secret is known, a pointer to a buffer large enough 
to hold the shared secret should be passed in <tt>sharedSecret</tt> and its 
length in <tt>secretLen</tt>. This function will copy the shared secret into 
<tt>sharedSecret</tt> and set the actual length of the shared secret in 
<tt>secretLen</tt>.

If <tt>sharedSecret</tt> is <tt>NULL</tt>, this function will set the
correct length of the shared secret in <tt>secretLen</tt>.  If
<tt>sharedSecret</tt> is not <tt>NULL</tt> but <tt>secretLen</tt>
is too small, this function will return an error.

The length of the shared secret can also be determined by calling
<tt>hu_ECCParamsGet()</tt> and retrieving the <tt>reducLen</tt>
argument.

@param[in]     eccParams        An ECC parameters object.
@param[in]     privateKey       An ECC private key object.
@param[in]     remotePublicKey  An ECC public key object.
@param[in,out] secretLen        The length (in bytes) of the shared secret.
@param[out]    sharedSecret     The shared secret buffer.
@param[in]     sbCtx            A global context.

@retval SB_ERR_NULL_PARAMS         The <tt>eccParams</tt> object is 
                                   <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS          
@retval SB_ERR_NULL_PRIVATE_KEY    The <tt>privateKey</tt> object <tt>NULL</tt>.
@retval SB_ERR_BAD_PRIVATE_KEY     The <tt>privateKey</tt> object invalid.
@retval SB_ERR_NULL_PUBLIC_KEY     The <tt>publicKey</tt> object is 
                                   <tt>NULL</tt>.
@retval SB_ERR_BAD_PUBLIC_KEY      The <tt>publicKey</tt> object is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF_LEN The shared secret buffer length is 
                                   <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN  The shared secret length is invalid.
@retval SB_FAIL_ALLOC              Memory allocation failure.
@retval SB_SUCCESS                 Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ECDHRawSharedGen(
    sb_Params eccParams,
    sb_PrivateKey privateKey,
    sb_PublicKey remotePublicKey,
    size_t *secretLen,
    unsigned char *sharedSecret,
    sb_GlobalCtx sbCtx
);


/** Generates a shared secret of the requested length by applying the ANSI
X9.42/X9.63 KDF with SHA-1 to the output of an ECDH key agreement using
cofactor exponentiation.

@param[in]  eccParams        An ECC parameters object.
@param[in]  privateKey       An ECC private key object.
@param[in]  remotePublicKey  An ECC public key object.
@param[in]  addInfoLen       The length (in bytes) of additional information. 
                             (Optional)
@param[in]  addInfo          Additional information for use with the KDF. 
                             (Optional - set to <tt>NULL</tt> if not used.)
@param[in]  secretLen        The length (in bytes) of the shared secret.
@param[out] sharedSecret     The shared secret value.
@param[in]  sbCtx            A global context.

@retval SB_ERR_NULL_PARAMS        The <tt>eccParams</tt> object is 
                                  <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS         
@retval SB_ERR_NULL_PRIVATE_KEY   The <tt>privateKey</tt> object <tt>NULL</tt>.
@retval SB_ERR_BAD_PRIVATE_KEY    The <tt>privateKey</tt> object invalid.
@retval SB_ERR_NULL_PUBLIC_KEY    The <tt>publicKey</tt> object is 
                                  <tt>NULL</tt>.
@retval SB_ERR_BAD_PUBLIC_KEY     The <tt>publicKey</tt> object is invalid.
@retval SB_ERR_NULL_ADDINFO       Additional information is <tt>NULL</tt>.
@retval SB_ERR_NULL_OUTPUT_BUF    The shared secret buffer is <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN The shared secret length is invalid.
@retval SB_FAIL_ALLOC             Memory allocation failure.
@retval SB_SUCCESS                Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ECDHCofacSharedGen(
    sb_Params eccParams,
    sb_PrivateKey privateKey,
    sb_PublicKey remotePublicKey,
    size_t addInfoLen,
    const unsigned char *addInfo,
    size_t secretLen,
    unsigned char *sharedSecret,
    sb_GlobalCtx sbCtx
);


/** Generates a shared secret that is the output of an ECDH key agreement
using cofactor multiplication.

If the length of the shared secret is known, a pointer to a buffer large
enough to hold the shared secret should be passed in
<tt>sharedSecret</tt> and its length in <tt>secretLen</tt>. This
function will copy the shared secret into <tt>sharedSecret</tt> and set
the actual length of the shared secret in <tt>secretLen</tt>.

If <tt>sharedSecret</tt> is <tt>NULL</tt>, this function will set the correct 
length of the shared secret in <tt>secretLen</tt>. If <tt>sharedSecret</tt> is 
not <tt>NULL</tt> but <tt>secretLen</tt> is too small, this function will 
return an error and set the correct length of the shared secret in 
<tt>secretLen</tt>.

The length of the shared secret can also be determined by calling
<tt>hu_ECCParamsGet()</tt> and retrieving the <tt>reducLen</tt> argument.

@param[in]     eccParams        An ECC parameters object.
@param[in]     privateKey       An ECC private key object.
@param[in]     remotePublicKey  An ECC public key object.
@param[in,out] secretLen        The length (in bytes) of the shared secret.
@param[out]    sharedSecret     The shared secret buffer.
@param[in]     sbCtx            A global context.

@retval SB_ERR_NULL_PARAMS         The <tt>eccParams</tt> object is 
                                   <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS          
@retval SB_ERR_NULL_PRIVATE_KEY    The <tt>privateKey</tt> object <tt>NULL</tt>.
@retval SB_ERR_BAD_PRIVATE_KEY     The <tt>privateKey</tt> object invalid.
@retval SB_ERR_NULL_PUBLIC_KEY     The <tt>publicKey</tt> object is 
                                   <tt>NULL</tt>.
@retval SB_ERR_BAD_PUBLIC_KEY      The <tt>publicKey</tt> object is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF_LEN The shared secret buffer is <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN  The shared secret length is invalid.
@retval SB_FAIL_ALLOC              Memory allocation failure.
@retval SB_SUCCESS                 Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ECDHCofacRawSharedGen(
    sb_Params eccParams,
    sb_PrivateKey privateKey,
    sb_PublicKey remotePublicKey,
    size_t *secretLen,
    unsigned char *sharedSecret,
    sb_GlobalCtx sbCtx
);


/** Generates a shared secret that is the output of an ECDH key agreement
using cofactor multiplication with optional y-coordinate output.

The x-coordinate of the resultant elliptic curve point from the ECDH Cofactor
operation is the raw shared secret.
If the length of the shared secret is known, a pointer to a buffer large
enough to hold the shared secret should be passed in
<tt>sharedSecretX</tt> and its length in <tt>secretLen</tt>. This
function will copy the shared secret (x-coordinate) into <tt>sharedSecretX</tt>
and set the actual length of the shared secret (i.e. the x-coordinate) in
<tt>secretLen</tt>.

If <tt>sharedSecretX</tt> is <tt>NULL</tt>, this function will set the
correct length of the shared secret (i.e. the x-coordinate) in 
<tt>secretLen</tt>.

If <tt>sharedSecretX</tt> is not <tt>NULL</tt> but <tt>secretLen</tt>
is too small, this function will return an error and set the correct length of
the shared secret (i.e. the x-coordinate) in <tt>secretLen</tt>.

The output of y-coordinate is optional.
Set <tt>sharedSecretY</tt> to <tt>NULL</tt> if the y-coordinate is not required.
If <tt>sharedSecretX</tt> is <tt>NULL</tt>, this argument is ignored.
Note that the length of x- and y-coordinates are the same. Therefore,
<tt>secretLen</tt> is shared to contain the size of each buffer.

The length of the shared secret can also be determined by calling
<tt>hu_ECCParamsGet()</tt> and retrieving the <tt>reducLen</tt>
argument.

@param[in]     eccParams        An ECC parameters object.
@param[in]     privateKey       An ECC private key object.
@param[in]     remotePublicKey  An ECC public key object.
@param[in,out] secretLen        The length (in bytes) of the shared secret (x- 
                                or y- coordinate).
@param[out]  sharedSecretX      The shared secret buffer for x-coordinate.
@param[out]  sharedSecretY      The shared secret buffer for y-coordinate.
@param[in]  sbCtx               A global context.

@retval SB_ERR_NULL_PARAMS         The <tt>eccParams</tt> object is 
                                   <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS          
@retval SB_ERR_NULL_PRIVATE_KEY    The <tt>privateKey</tt> object <tt>NULL</tt>.
@retval SB_ERR_BAD_PRIVATE_KEY     The <tt>privateKey</tt> object invalid.
@retval SB_ERR_NULL_PUBLIC_KEY     The <tt>publicKey</tt> object is 
                                   <tt>NULL</tt>.
@retval SB_ERR_BAD_PUBLIC_KEY      The <tt>publicKey</tt> object is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF_LEN The shared secret buffer is <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN  The shared secret length is invalid.
@retval SB_FAIL_ALLOC              Memory allocation failure.
@retval SB_SUCCESS                 Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ECDHCofacRawXYSharedGen(
    sb_Params eccParams,
    sb_PrivateKey privateKey,
    sb_PublicKey remotePublicKey,
    size_t *secretLen,
    unsigned char *sharedSecretX,
    unsigned char *sharedSecretY,
    sb_GlobalCtx sbCtx
);


/** @} */

/** @addtogroup hu_ecc_ecdsa_api ECC ECDSA APIs
 *
 * @{
 */

/** Generates a signature on the given message digest using ECDSA.

This function assumes that the input is a message digest (of any length);
no digest operation will be performed on the input.

The ECC parameter object must have been created with an RNG context.

If the length of s is known, a pointer to a buffer large enough to hold s
should be passed in <tt>sValue</tt> and its length in
<tt>sLength</tt>. This function will copy s into <tt>sValue</tt> and
set the actual length of s in <tt>sLength</tt>.

If <tt>sValue</tt> is <tt>NULL</tt>, this function will set the correct
length of s in <tt>sLength</tt>.  If <tt>sValue</tt> is not
<tt>NULL</tt> but <tt>sLength</tt> is too small, this function will
return an error.

Similarly for r.

s and r will always have the same length.

The length of s or r can also be determined by calling
<tt>hu_ECCParamsGet()</tt> and retrieving the <tt>OrdLen</tt>
argument.

@param[in]     eccParams      An ECC parameters object.
@param[in]     privateKey     An ECC private key object.
@param[in]     length         The length (in bytes) of the message digest.
@param[in]     messageDigest  The message digest.
@param[in,out] sLength        The length (in bytes) of <tt>sValue</tt>.
@param[out]    sValue         The 's' component from the signature computation.
@param[in,out] rLength        The length (in bytes) of <tt>rValue</tt>.
@param[out]    rValue         The 'r' component from the signature computation. 
                              This is the x-coordinate of the ephemeral public 
			      key.
@param[in]  sbCtx             A global context.

@retval SB_ERR_NULL_PARAMS       The <tt>eccParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS        
@retval SB_ERR_NULL_PRIVATE_KEY  The <tt>privateKey</tt> object <tt>NULL</tt>.
@retval SB_ERR_BAD_PRIVATE_KEY   The <tt>privateKey</tt> object invalid.
@retval SB_ERR_BAD_INPUT_BUF_LEN The message digest length is invalid.
@retval SB_ERR_NULL_INPUT_BUF    The message digest is <tt>NULL</tt>.
@retval SB_ERR_NULL_S_VALUE_LEN  The signature component length is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_S_VALUE_LEN   The signature component length is invalid.
@retval SB_ERR_NULL_R_VALUE_LEN  The signature component length is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_R_VALUE_LEN   The signature component length is invalid.
@retval SB_FAIL_ALLOC            Memory allocation failure.
@retval SB_SUCCESS               Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ECDSANoHashSign(
   sb_Params eccParams,
   sb_PrivateKey privateKey,
   size_t length,
   const unsigned char *messageDigest,
   size_t *sLength,
   unsigned char *sValue,
   size_t *rLength,
   unsigned char *rValue,
   sb_GlobalCtx sbCtx
);


/** Verifies an ECDSA signature on the given message digest.

This function assumes that the input is a message digest (of any length);
no digest operation will be performed on the input.

If the signature is valid for the given digest, this function will return
<tt>SB_SUCCESS</tt> and set <tt>result</tt> to a non-zero value.

If the signature is not valid for the given digest, this function will return
<tt>SB_SUCCESS</tt> but <tt>result</tt> will be set to zero.

@param[in]  eccParams      An ECC parameters object.
@param[in]  publicKey      An ECC public key object.
@param[in]  length         The length (in bytes) of the message digest.
@param[in]  messageDigest  A message digest.
@param[in]  sLength        The length (in bytes) of <tt>sValue</tt>.
@param[in]  sValue         The <tt>s</tt> component of the signature.
@param[in]  rLength        The length (in bytes) of <tt>rValue</tt>.
@param[in]  rValue         The <tt>r</tt> component of the signature.
@param[out] result         The verification result. This is non-zero if the 
                           signature is valid; zero if the signature is invalid.
@param[in]  sbCtx          A global context.

@retval SB_ERR_NULL_PARAMS       The <tt>eccParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS        
@retval SB_ERR_NULL_PUBLIC_KEY   The <tt>publicKey</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PUBLIC_KEY    The <tt>publicKey</tt> object is invalid.
@retval SB_ERR_BAD_INPUT_BUF_LEN The message digest length is invalid.
@retval SB_ERR_NULL_INPUT_BUF    The message digest is <tt>NULL</tt>.
@retval SB_ERR_NULL_S_VALUE      The signature component is <tt>NULL</tt>.
@retval SB_ERR_BAD_S_VALUE_LEN   The signature component length is invalid.
@retval SB_ERR_NULL_R_VALUE      The signature component is <tt>NULL</tt>.
@retval SB_ERR_BAD_R_VALUE_LEN   The signature component length is invalid.
@retval SB_ERR_NULL_OUTPUT       The verification result pointer is 
                                 <tt>NULL</tt>.
@retval SB_FAIL_ALLOC            Memory allocation failure.
@retval SB_SUCCESS               Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ECDSANoHashVerify(
   sb_Params eccParams,
   sb_PublicKey publicKey,
   size_t length,
   const unsigned char *messageDigest,
   size_t sLength,
   const unsigned char *sValue,
   size_t rLength,
   const unsigned char *rValue,
   int *result,
   sb_GlobalCtx sbCtx
);

/** @} */


/** @} */

/** @addtogroup hu_ecgdsa_api ECGDSA APIs
 *
 * @{
 */

/** Creates an ECC private and/or public key object for ECGDSA from the given 
key value(s). The difference between this API and <tt>hu_ECCKeySet()</tt> is 
that this API will produce an inverted private key and associated public key.

If both the private and public key values are supplied, then a private key 
and/or a public key object can be created. These objects will be created from 
the corresponding key values.

If only a private key value is supplied, then a private key and/or a public key
object can be created. The public key will be computed from the private key.

If only a public key value is supplied, then only a public key object can be
created.

@param[in]  eccParams        An ECC parameters object.
@param[in]  privateKeyLen    The length (in bytes) of the private key value.
@param[in]  privateKeyValue  The private key value.
@param[in]  publicKeyLen     The length (in bytes) of the public key value.
@param[in]  publicKeyValue   The public key value.
@param[out] privateKey       The private key object pointer.
@param[out] publicKey        The public key object pointer.
@param[in]  sbCtx            A global context.

@retval SB_ERR_NULL_PARAMS          The <tt>eccParams</tt> object is 
                                    <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS           
@retval SB_ERR_NULL_PRI_KEY_BUF     The private key value is <tt>NULL</tt>.
@retval SB_ERR_BAD_PRI_KEY_BUF_LEN  The private key length is invalid.
@retval SB_ERR_NULL_PUB_KEY_BUF     The public key value is <tt>NULL</tt>.
@retval SB_ERR_BAD_PUB_KEY_BUF_LEN  The public key length is invalid.
@retval SB_ERR_BAD_INPUT            The public key value is invalid.
@retval SB_FAIL_INVALID_PRIVATE_KEY The private key value is invalid.
@retval SB_FAIL_ALLOC               Memory allocation failure.
@retval SB_SUCCESS                  Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ECGDSAKeySet(
  sb_Params            eccParams,
  size_t               privateKeyLen,
  const unsigned char *privateKeyValue,
  size_t               publicKeyLen,
  const unsigned char *publicKeyValue,
  sb_PrivateKey       *privateKey,
  sb_PublicKey        *publicKey,
  sb_GlobalCtx         sbCtx
  );


/** Generates a digital signature using the Elliptic Curve German Digital
Signature Algorithm (ECGDSA). An ECGDSA signature consists of the following
two components:

The <tt>s</tt> value is the result of the signature equation.

The <tt>r</tt> value is the x co-ordinate of the ephemeral public key.

This function assumes that the input is a message digest (of any length);
no digest operation will be performed on the input.

The ECC parameter object must have been created with an RNG context.

If the length of s is known, a pointer to a buffer large enough to hold s
should be passed in <tt>sValue</tt> and its length in
<tt>sLength</tt>. This function will copy s into <tt>sValue</tt> and
set the actual length of s in <tt>sLength</tt>.

If <tt>sValue</tt> is <tt>NULL</tt>, this function will set the correct
length of s in <tt>sLength</tt>.  If <tt>sValue</tt> is not
<tt>NULL</tt> but <tt>sLength</tt> is too small, this function will
return an error.

Similarly for r.

s and r will always have the same length.

The length of s or r can also be determined by calling
<tt>hu_ECCParamsGet()</tt> and retrieving the <tt>OrdLen</tt>
argument.

@param[in]     eccParams      An ECC parameters object.
@param[in]     privateKey     An ECC private key object.
@param[in]     length         The length (in bytes) of the message digest.
@param[in]     messageDigest  The message digest.
@param[in,out] sLength        The length (in bytes) of <tt>sValue</tt>.
@param[out]    sValue         The 's' component from the signature computation.
@param[in,out] rLength        The length (in bytes) of <tt>rValue</tt>.
@param[out]    rValue         The 'r' component from the signature computation. 
                              This is the x-coordinate of the ephemeral public 
                              key.
@param[in]  sbCtx             A global context.

@retval SB_ERR_NULL_PARAMS       ECC parameters object is NULL.
@retval SB_ERR_BAD_PARAMS        ECC parameters object is invalid.
@retval SB_ERR_NO_RNG            RNG does not exist in the parameters.
@retval SB_ERR_NULL_PRIVATE_KEY  Private key is NULL.
@retval SB_ERR_BAD_PRIVATE_KEY   Private key is invalid.
@retval SB_ERR_BAD_INPUT_BUF_LEN Message digest length is invalid.
@retval SB_ERR_NULL_INPUT_BUF    Message digest pointer is NULL when the length
                                 is positive.
@retval SB_ERR_NULL_S_VALUE_LEN  The <tt>s</tt> value buffer length pointer is
                                 NULL.
@retval SB_ERR_BAD_S_VALUE_LEN   The <tt>s</tt> value buffer is invalid.
@retval SB_ERR_NULL_R_VALUE_LEN  The <tt>r</tt> value buffer length pointer is
                                 NULL.
@retval SB_ERR_BAD_R_VALUE_LEN   The <tt>r</tt> value buffer is invalid.
@retval SB_FAIL_ALLOC            Memory allocation failure.
@retval SB_FAILURE               Operation failed.
@retval SB_SUCCESS               Success.

*/


extern
SB_EXPORT
int
SB_CALLCONV
hu_ECGDSANoHashSign(
   sb_Params eccParams,
   sb_PrivateKey privateKey,
   size_t length,
   const unsigned char *messageDigest,
   size_t *sLength,
   unsigned char *sValue,
   size_t *rLength,
   unsigned char *rValue,
   sb_GlobalCtx sbCtx
);


/** Verifies an Elliptic Curve German Digital Signature Algorithm (ECGDSA) signature.
An ECGDSA signature consists of the following two components:

The <tt>s</tt> value is the result of the signature equation.

The <tt>r</tt> value is the x co-ordinate of the ephemeral public key.

If the signature is valid for the given digest, this function will return
<tt>SB_SUCCESS</tt> and set <tt>result</tt> to a non-zero value.

If the signature is not valid for the given digest, this function will return
<tt>SB_SUCCESS</tt> but <tt>result</tt> will be set to zero.

@param[in]  eccParams      An ECC parameters object.
@param[in]  publicKey      An ECC public key object.
@param[in]  length         The length (in bytes) of the message digest.
@param[in]  messageDigest  A message digest.
@param[in]  sLength        The length (in bytes) of <tt>sValue</tt>.
@param[in]  sValue         The <tt>s</tt> component of the signature.
@param[in]  rLength        The length (in bytes) of <tt>rValue</tt>.
@param[in]  rValue         The <tt>r</tt> component of the signature.
@param[out] result         The verification result. This is non-zero if the 
                           signature is valid; zero if the signature is invalid.
@param[in]  sbCtx          A global context.

@retval SB_ERR_NULL_PARAMS         ECC parameters object is NULL
@retval SB_ERR_BAD_PARAMS          ECC parameters object is invalid.
@retval SB_ERR_NULL_PUBLIC_KEY     Public key is NULL.
@retval SB_ERR_BAD_PUBLIC_KEY      Public key is invalid.
@retval SB_ERR_NULL_INPUT_BUF      Message digest pointer is NULL.
@retval SB_ERR_BAD_INPUT_BUF_LEN   Message digest length is invalid.
@retval SB_ERR_NULL_S_VALUE        The <tt>s</tt> value buffer pointer is NULL.
@retval SB_ERR_BAD_S_VALUE_BUF_LEN The <tt>s</tt> value buffer is invalid.
@retval SB_ERR_NULL_R_VALUE        The <tt>r</tt> value buffer pointer is NULL.
@retval SB_ERR_BAD_R_VALUE_BUF_LEN The <tt>r</tt> value buffer is invalid.
@retval SB_ERR_NULL_OUTPUT         Result pointer is NULL.
@retval SB_FAIL_ALLOC              Memory allocation failure.
@retval SB_FAILURE                 Operation failed.
@retval SB_SUCCESS                 Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ECGDSANoHashVerify(
   sb_Params eccParams,
   sb_PublicKey publicKey,
   size_t length,
   const unsigned char *messageDigest,
   size_t sLength,
   const unsigned char *sValue,
   size_t rLength,
   const unsigned char *rValue,
   int *result,
   sb_GlobalCtx sbCtx
);

/** @} */


/** @addtogroup hu_ecc_ecmqv_api ECC ECMQV APIs
 *
 * @{
 */

/** Generates a shared secret of the requested length by applying the ANSI
X9.42/X9.63 KDF with SHA-1 to the output of an ECMQV key agreement.

@param[in]  eccParams             An ECC parameters object.
@param[in]  privateKey            An ECC private key object.
@param[in]  ephemPrivateKey       An ECC private key object.
@param[in]  ephemPublicKey        An ECC public key object.
@param[in]  remotePublicKey       An ECC public key object.
@param[in]  remoteEphemPublicKey  An ECC public key object.
@param[in]  addInfoLen            The length (in bytes) of additional 
                                  information. (Optional)
@param[in]  addInfo               Additional information for use with the KDF. 
                                  (Optional - set to <tt>NULL</tt> if not used.)
@param[in]  secretLen             The length (in bytes) of the shared secret.
@param[out] sharedSecret          The shared secret value.
@param[in]  sbCtx                 A global context.

@retval SB_ERR_NULL_PARAMS            The <tt>eccParams</tt> object is 
                                      <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS             
@retval SB_ERR_NULL_PRIVATE_KEY       The <tt>privateKey</tt> object 
                                      <tt>NULL</tt>.
@retval SB_ERR_BAD_PRIVATE_KEY        The <tt>privateKey</tt> object invalid.
@retval SB_ERR_NULL_EPHEM_PRI_KEY     The ephemeral private key object is 
                                      <tt>NULL</tt>.
@retval SB_ERR_BAD_EPHEM_PRI_KEY      The ephemeral private key object is 
                                      invalid.
@retval SB_ERR_NULL_EPHEM_PUB_KEY     The ephemeral public key is <tt>NULL</tt>.
@retval SB_ERR_BAD_EPHEM_PUB_KEY      The ephemeral public key is invalid.
@retval SB_ERR_NULL_REM_PUB_KEY       The remote public key is <tt>NULL</tt>.
@retval SB_ERR_BAD_REM_PUB_KEY        The remote public key is invalid.
@retval SB_ERR_NULL_REM_EPHEM_PUB_KEY The remote ephemeral public key is 
                                      <tt>NULL</tt>.
@retval SB_ERR_BAD_REM_EPHEM_PUB_KEY  The remote ephemeral public key is 
                                      invalid.
@retval SB_ERR_NULL_ADDINFO           Additional information is <tt>NULL</tt>.
@retval SB_ERR_NULL_OUTPUT_BUF        The shared secret buffer is <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN     The shared secret length is invalid.
@retval SB_FAIL_ALLOC                 Memory allocation failure.
@retval SB_SUCCESS                    Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ECMQVSharedGen(
    sb_Params eccParams,
    sb_PrivateKey privateKey,
    sb_PrivateKey ephemPrivateKey,
    sb_PublicKey ephemPublicKey,
    sb_PublicKey remotePublicKey,
    sb_PublicKey remoteEphemPublicKey,
    size_t addInfoLen,
    const unsigned char *addInfo,
    size_t secretLen,
    unsigned char *sharedSecret,
    sb_GlobalCtx sbCtx
);


/** Generates a shared secret that is the output of an ECMQV key agreement.

If the length of the shared secret is known, a pointer to a buffer large enough 
to hold the shared secret should be passed in <tt>sharedSecret</tt> and its 
length in <tt>secretLen</tt>. This function will copy the shared secret into
<tt>sharedSecret</tt> and set the actual length of the shared secret in 
<tt>secretLen</tt>.

If <tt>sharedSecret</tt> is <tt>NULL</tt>, this function will set the
correct length of the shared secret in <tt>secretLen</tt>.  If
<tt>sharedSecret</tt> is not <tt>NULL</tt> but <tt>secretLen</tt>
is too small, this function will return an error.

The length of the shared secret can also be determined by calling
<tt>hu_ECCParamsGet()</tt> and retrieving the <tt>reducLen</tt>
argument.

@param[in]     eccParams             An ECC parameters object.
@param[in]     privateKey            An ECC private key object.
@param[in]     ephemPrivateKey       An ECC private key object.
@param[in]     ephemPublicKey        An ECC public key object.
@param[in]     remotePublicKey       An ECC public key object.
@param[in]     remoteEphemPublicKey  An ECC public key object.
@param[in,out] secretLen             The length (in bytes) of the shared secret.
@param[out]    sharedSecret          The shared secret value.
@param[in]     sbCtx                 A global context.

@retval SB_ERR_NULL_PARAMS            The <tt>eccParams</tt> object is 
                                      <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS             
@retval SB_ERR_NULL_PRIVATE_KEY       The <tt>privateKey</tt> object 
                                      <tt>NULL</tt>.
@retval SB_ERR_BAD_PRIVATE_KEY        The <tt>privateKey</tt> object invalid.
@retval SB_ERR_NULL_EPHEM_PRI_KEY     The ephemeral private key object is 
                                      <tt>NULL</tt>.
@retval SB_ERR_BAD_EPHEM_PRI_KEY      The ephemeral private key object is 
                                      invalid.
@retval SB_ERR_NULL_EPHEM_PUB_KEY     The ephemeral public key is <tt>NULL</tt>.
@retval SB_ERR_BAD_EPHEM_PUB_KEY      The ephemeral public key is invalid.
@retval SB_ERR_NULL_REM_PUB_KEY       The remote public key is <tt>NULL</tt>.
@retval SB_ERR_BAD_REM_PUB_KEY        The remote public key is invalid.
@retval SB_ERR_NULL_REM_EPHEM_PUB_KEY The remote ephemeral public key is 
                                      <tt>NULL</tt>.
@retval SB_ERR_BAD_REM_EPHEM_PUB_KEY  The remote ephemeral public key is 
                                      invalid.
@retval SB_ERR_NULL_OUTPUT_BUF_LEN    The shared secret buffer length is 
                                      <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN     The shared secret length is invalid.
@retval SB_FAIL_ALLOC                 Memory allocation failure.
@retval SB_SUCCESS                    Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ECMQVRawSharedGen(
    sb_Params eccParams,
    sb_PrivateKey privateKey,
    sb_PrivateKey ephemPrivateKey,
    sb_PublicKey ephemPublicKey,
    sb_PublicKey remotePublicKey,
    sb_PublicKey remoteEphemPublicKey,
    size_t *secretLen,
    unsigned char *sharedSecret,
    sb_GlobalCtx sbCtx
);

/** @} */


/** @addtogroup hu_ecc_ecies_api ECC ECIES APIs
 *
 * @{
 */

/** Encrypts plaintext using ECIES with XOR encryption, standard
Diffie-Hellman, ANSI X9.42/X9.63 KDF with SHA-1 and HMAC-SHA-1 primitives.

A MAC tag forms part of the ciphertext and is used to verify integrity during
decryption.

The ECC parameter object must have been created with an RNG context.

If the length of the ciphertext is known, a pointer to a buffer large enough
to hold the ciphertext should be passed in <tt>ciphertext</tt> and its
length in <tt>ciphertextLen</tt>. This function will copy the ciphertext
into <tt>ciphertext</tt> and set the actual length of the ciphertext in
<tt>ciphertextLen</tt>.

If <tt>ciphertext</tt> is <tt>NULL</tt>, or <tt>ciphertext</tt>
is not <tt>NULL</tt> but <tt>ciphertextLen</tt> is too small, this
function will set the correct length of the ciphertext in
<tt>ciphertextLen</tt>.

@param[in]     eccParams       An ECC parameters object.
@param[in]     publicKey       An ECC public key object.
@param[in]     addInfoKDFLen   The length (in bytes) of additional information 
                               for KDF. (Optional)
@param[in]     addInfoKDF      Additional information for KDF. (Optional - set 
                               to <tt>NULL</tt> if not used.)
@param[in]     addInfoHMACLen  The length (in bytes) of additional information 
                               for HMAC. (Optional)
@param[in]     addInfoHMAC     Additional information for HMAC. (Optional - set 
                               to <tt>NULL</tt> if not used.)
@param[in]     plaintextLen    The length (in bytes) of the plaintext.
@param[in]     plaintext       The plaintext.
@param[in,out] ciphertextLen   The length (in bytes) of the ciphertext.
@param[out]    ciphertext      The ciphertext.
@param[in]     sbCtx           A global context.

@retval SB_ERR_NULL_PARAMS             The <tt>eccParams</tt> object is 
                                       <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS              
@retval SB_ERR_NO_RNG                  No RNG context was found in the 
                                       parameters object.
@retval SB_ERR_NULL_PUBLIC_KEY         The <tt>publicKey</tt> object is 
                                       <tt>NULL</tt>.
@retval SB_ERR_BAD_PUBLIC_KEY          The <tt>publicKey</tt> object is invalid.
@retval SB_ERR_NULL_INPUT_BUF          Plaintext buffer is <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN       The length of the plaintext buffer is 
                                       invalid.
@retval SB_ERR_NULL_OUTPUT_BUF_LEN_PTR The ciphertext buffer is <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN      The length of the ciphertext buffer is 
                                       invalid.
@retval SB_FAIL_ALLOC                  Memory allocation failure.
@retval SB_SUCCESS                     Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ECIESEncrypt(
    sb_Params eccParams,
    sb_PublicKey publicKey,
    size_t addInfoKDFLen,
    const unsigned char *addInfoKDF,
    size_t addInfoHMACLen,
    const unsigned char *addInfoHMAC,
    size_t plaintextLen,
    const unsigned char *plaintext,
    size_t *ciphertextLen,
    unsigned char *ciphertext,
    sb_GlobalCtx sbCtx
);


/** Decrypts ciphertext using ECIES with XOR encryption, standard
Diffie-Hellman, ANSI X9.42/X9.63 KDF with SHA-1 and HMAC-SHA-1 primitives.

If the length of the plaintext is known, a pointer to a buffer large enough
to hold the plaintext should be passed in <tt>plaintext</tt> and its
length in <tt>plaintextLen</tt>. This function will copy the plaintext
into <tt>plaintext</tt> and set the actual length of the plaintext in
<tt>plaintextLen</tt>.

If <tt>plaintext</tt> is <tt>NULL</tt>, this function will set the correct
length of the plaintext in <tt>plaintextLen</tt>.
If <tt>plaintext</tt> is not <tt>NULL</tt> but <tt>plaintextLen</tt> is too
small, this function will return an error.

If this function returns <tt>SB_FAIL_ECIES_HMAC</tt>, the integrity check
on the ciphertext failed, and could be due to using the wrong private key or
corrupted ciphertext or MAC tag.

@param[in]     eccParams       An ECC parameters object.
@param[in]     privateKey      An ECC private key object.
@param[in]     addInfoKDFLen   The length (in bytes) of additional information 
                               for KDF. (Optional)
@param[in]     addInfoKDF      Additional information for KDF. (Optional - set 
                               to <tt>NULL</tt> if not used.)
@param[in]     addInfoHMACLen  The length (in bytes) of additional information 
                               for HMAC. (Optional)
@param[in]     addInfoHMAC     Additional information for HMAC. (Optional - set 
                               to <tt>NULL</tt> if not used.)
@param[in]     ciphertextLen   The length (in bytes) of the ciphertext.
@param[in]     ciphertext      The ciphertext.
@param[in,out] plaintextLen    The length (in bytes) of the plaintext.
@param[out]    plaintext       The plaintext.
@param[in]     sbCtx           A global context.

@retval SB_ERR_NULL_PARAMS             The <tt>eccParams</tt> object is 
                                       <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS              
@retval SB_ERR_NULL_PRIVATE_KEY        The <tt>privateKey</tt> object 
                                       <tt>NULL</tt>.
@retval SB_ERR_BAD_PRIVATE_KEY         The <tt>privateKey</tt> object invalid.
@retval SB_ERR_NULL_INPUT_BUF          The ciphertext buffer is <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN       The length of the ciphertext buffer 
                                       length is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF_LEN_PTR The plaintext buffer is <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN      The length of the plaintext buffer is 
                                       invalid.
@retval SB_ERR_BAD_INPUT               The ephemeral public key in the 
                                       ciphertext is invalid.
@retval SB_FAIL_ECIES_HMAC             The ciphertext integrity check failed.
@retval SB_FAIL_ALLOC                  Memory allocation failure.
@retval SB_SUCCESS                     Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ECIESDecrypt(
    sb_Params eccParams,
    sb_PrivateKey privateKey,
    size_t addInfoKDFLen,
    const unsigned char *addInfoKDF,
    size_t addInfoHMACLen,
    const unsigned char *addInfoHMAC,
    size_t ciphertextLen,
    const unsigned char *ciphertext,
    size_t *plaintextLen,
    unsigned char *plaintext,
    sb_GlobalCtx sbCtx
);


/** ECIES Mode identifiers

When <tt>HU_ECIES_SEC1</tt> is specified, the ECIES algorithm (in normal mode)
in SEC1 is performed.

When <tt>HU_ECIES_IEEE</tt> is specified, the ECIES algorithm in DHAES mode
in IEEE 1363a-2004 is performed.

When <tt>HU_ECIES_BACK_COMP</tt> is specified, the ECIES algorithm in the
backwards compatibility mode in SEC1, which is equivalent to the ECIES
algorithm in IEEE 1363-2000 (or in non-DHAES mode in IEEE 1363a-2004), is
performed.
*/
#define HU_ECIES_SEC1       0
#define HU_ECIES_IEEE       1
#define HU_ECIES_BACK_COMP  2


/** ECDH Mode identifiers */
#define HU_ECIES_ECDH_STANDARD  0
#define HU_ECIES_ECDH_COFACTOR  1


/** MAC Algorithm identifiers

The <tt>hu_MACEnd</tt> functions require the tag length to be specified,
and does not specifically support the half length tag.
However, ECIES must use only full length and half length tags.
In order to differenciate this and allow users to specify full or half,
the 5th bit from the lowest, which is not used to identify a MAC algorithm,
is used.
*/
#define HU_ECIES_HMAC_SHA1_80     0x0014 /* (0x10 | HU_DIGEST_SHA1) */
#define HU_ECIES_HMAC_SHA1_160    HU_DIGEST_SHA1
#define HU_ECIES_HMAC_SHA224_112  0x0015 /* (0x10 | HU_DIGEST_SHA224) */
#define HU_ECIES_HMAC_SHA224_224  HU_DIGEST_SHA224
#define HU_ECIES_HMAC_SHA256_128  0x0016 /* (0x10 | HU_DIGEST_SHA256) */
#define HU_ECIES_HMAC_SHA256_256  HU_DIGEST_SHA256
#define HU_ECIES_HMAC_SHA384_192  0x0017 /* (0x10 | HU_DIGEST_SHA384) */
#define HU_ECIES_HMAC_SHA384_384  HU_DIGEST_SHA384
#define HU_ECIES_HMAC_SHA512_256  0x0018 /* (0x10 | HU_DIGEST_SHA512) */
#define HU_ECIES_HMAC_SHA512_512  HU_DIGEST_SHA512
#define HU_ECIES_CMAC_AES_128     HU_MAC_CMAC_AES_128
#define HU_ECIES_CMAC_AES_192     HU_MAC_CMAC_AES_192
#define HU_ECIES_CMAC_AES_256     HU_MAC_CMAC_AES_256


/** KDF Algorithm identifiers */
#define HU_ECIES_KDF_ANSI_SHA1         HU_KDF_ANSI_SHA1
#define HU_ECIES_KDF_ANSI_SHA224       HU_KDF_ANSI_SHA224
#define HU_ECIES_KDF_ANSI_SHA256       HU_KDF_ANSI_SHA256
#define HU_ECIES_KDF_ANSI_SHA384       HU_KDF_ANSI_SHA384
#define HU_ECIES_KDF_ANSI_SHA512       HU_KDF_ANSI_SHA512
#define HU_ECIES_KDF_NIST_ALT1_SHA1    HU_KDF_NIST_ALT1_SHA1
#define HU_ECIES_KDF_NIST_ALT1_SHA224  HU_KDF_NIST_ALT1_SHA224
#define HU_ECIES_KDF_NIST_ALT1_SHA256  HU_KDF_NIST_ALT1_SHA256
#define HU_ECIES_KDF_NIST_ALT1_SHA384  HU_KDF_NIST_ALT1_SHA384
#define HU_ECIES_KDF_NIST_ALT1_SHA512  HU_KDF_NIST_ALT1_SHA512



/** Encrypts plaintext using ECIES with KDF-XOR cipher,
based on IEEE 1363A and SEC1 Version 1.7.

The IEEE KDF is not supported.

The ECC parameter object must have been created with an RNG context.

If the length of the ciphertext is known, a pointer to a buffer large enough
to hold the ciphertext should be passed in <tt>ciphertext</tt> and its
length in <tt>ciphertextLen</tt>. This function will place the ciphertext
into <tt>ciphertext</tt> and set the actual length of the ciphertext in
<tt>ciphertextLen</tt>.

If <tt>ciphertext</tt> is <tt>NULL</tt>, this function will set the correct
length of the ciphertext in <tt>ciphertextLen</tt>.
If <tt>ciphertext</tt> is not <tt>NULL</tt> but <tt>ciphertextLen</tt> is too
small, this function will return an error.

@param[in]     eccParams      An ECC parameters object.
@param[in]     publicKey      An ECC public key object.
@param[in]     eciesMode      ECIES mode. It selects SEC1 normal, IEEE DHAES or 
                              SEC1 backwards compatibility mode (equivalent to 
			      IEEE non-DHAES mode).
@param[in]     ecdhMode       ECDH Mode.  It selects standard ECDH or cofactor
                              version of ECDH.
@param[in]     macAlgId       MAC Algorithm ID.
@param[in]     addInfoMACLen  The length (in bytes) of additional information 
                              for MAC. (Optional)
@param[in]     addInfoMAC     Additional information for MAC. (Optional - set to
                              <tt>NULL</tt> if not used.)
@param[in]     kdfAlgId       KDF Algorithm ID.
@param[in]     addInfoKDFLen  The length (in bytes) of additional 
                              information for KDF. (Optional)
@param[in]     addInfoKDF     Additional information for KDF. (Optional - set to
                              <tt>NULL</tt> if not used.)
@param[in]     plaintextLen   The length (in bytes) of the plaintext.
@param[in]     plaintext      The plaintext.
@param[in,out] ciphertextLen  The length (in bytes) of the ciphertext.
@param[out]    ciphertext     The ciphertext.
@param[in]     sbCtx          A global context.

@retval SB_ERR_NULL_PARAMS             The <tt>eccParams</tt> object is 
                                       <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS              
@retval SB_ERR_NO_RNG                  No RNG context was found in the 
                                       parameters object.
@retval SB_ERR_NULL_PUBLIC_KEY         The <tt>publicKey</tt> object is 
                                       <tt>NULL</tt>.
@retval SB_ERR_BAD_PUBLIC_KEY          The <tt>publicKey</tt> object is invalid.
@retval SB_ERR_NULL_INPUT_BUF          Plaintext buffer is <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN       The length of the plaintext buffer is 
                                       invalid.
@retval SB_ERR_NULL_OUTPUT_BUF_LEN_PTR The ciphertext buffer is <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN      The length of the ciphertext buffer is 
                                       invalid.
@retval SB_FAIL_ALLOC                  Memory allocation failure.
@retval SB_SUCCESS                     Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ECIESKDFXOREncrypt(
    sb_Params eccParams,
    sb_PublicKey publicKey,
    int eciesMode,
    int ecdhMode,
    int macAlgId,
    size_t addInfoMACLen,
    const unsigned char *addInfoMAC,
    int kdfAlgId,
    size_t addInfoKDFLen,
    const unsigned char *addInfoKDF,
    size_t plaintextLen,
    const unsigned char *plaintext,
    size_t *ciphertextLen,
    unsigned char *ciphertext,
    sb_GlobalCtx sbCtx
);


/** Decrypts ciphertext using ECIES with KDF-XOR cipher, based on IEEE 1363A and
 * SEC1 Version 1.7.

The IEEE KDF is not supported.

If the length of the plaintext is known, a pointer to a buffer large enough
to hold the plaintext should be passed in <tt>plaintext</tt> and its length in 
<tt>plaintextLen</tt>. This function will place the plaintext into 
<tt>plaintext</tt> and set the actual length of the plaintext in 
<tt>plaintextLen</tt>.

If <tt>plaintext</tt> is <tt>NULL</tt>, this function will set the correct
length of the plaintext in <tt>plaintextLen</tt>.
If <tt>plaintext</tt> is not <tt>NULL</tt> but <tt>plaintextLen</tt> is too
small, this function will return an error.

If this function returns <tt>SB_FAIL_ECIES_HMAC</tt>, the integrity check
on the ciphertext failed. Such a failure can be caused by altered ciphertext
or MAC tag, or a wrong private key.

@param[in]     eccParams      An ECC parameters object.
@param[in]     privateKey     An ECC private key object.
@param[in]     eciesMode      ECIES mode. It selects SEC1 normal, IEEE DHAES or 
                              SEC1 backwards compatibility mode (equivalent to 
			      IEEE non-DHAES mode).
@param[in]     ecdhMode       ECDH Mode.  It selects standard ECDH or cofactor
                              version of ECDH.
@param[in]     macAlgId       MAC Algorithm ID.
@param[in]     addInfoMACLen  The length (in bytes) of additional information 
                              for MAC. (Optional)
@param[in]     addInfoMAC     Additional information for MAC. (Optional - set to
                              <tt>NULL</tt> if not used.)
@param[in]     kdfAlgId       KDF Algorithm ID.
@param[in]     addInfoKDFLen  The length (in bytes) of additional 
                              information for KDF. (Optional)
@param[in]     addInfoKDF     Additional information for KDF. (Optional - set to
                              <tt>NULL</tt> if not used.)
@param[in]     ciphertextLen  The length (in bytes) of the ciphertext.
@param[in]     ciphertext     The ciphertext.
@param[in,out] plaintextLen   The length (in bytes) of the plaintext.
@param[out]    plaintext      The plaintext.
@param[in]     sbCtx          A global context.

@retval SB_ERR_NULL_PARAMS             The <tt>eccParams</tt> object is 
                                       <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS              
@retval SB_ERR_NULL_PRIVATE_KEY        The <tt>privateKey</tt> object 
                                       <tt>NULL</tt>.
@retval SB_ERR_BAD_PRIVATE_KEY         The <tt>privateKey</tt> object invalid.
@retval SB_ERR_NULL_INPUT_BUF          The ciphertext buffer is <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN       The length of the ciphertext buffer 
                                       length is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF_LEN_PTR The plaintext buffer is <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN      The length of the plaintext buffer is 
                                       invalid.
@retval SB_ERR_BAD_INPUT               The ephemeral public key in the 
                                       ciphertext is invalid.
@retval SB_FAIL_ECIES_HMAC             The ciphertext integrity check failed.
@retval SB_FAIL_ALLOC                  Memory allocation failure.
@retval SB_SUCCESS                     Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ECIESKDFXORDecrypt(
    sb_Params eccParams,
    sb_PrivateKey privateKey,
    int eciesMode,
    int ecdhMode,
    int macAlgId,
    size_t addInfoMACLen,
    const unsigned char *addInfoMAC,
    int kdfAlgId,
    size_t addInfoKDFLen,
    const unsigned char *addInfoKDF,
    size_t ciphertextLen,
    const unsigned char *ciphertext,
    size_t *plaintextLen,
    unsigned char *plaintext,
    sb_GlobalCtx sbCtx
);

/** @} */

/** @addtogroup hu_ecc_ecqv_api ECC ECQV APIs
 *
 * @{
 */

/** Generates public key reconstruction data from public key request data
and the CA's ephemeral public key.

The CA's ephemeral key pair must be generated prior to calling this function.
Any data from the requester that is to be used in generating the public key 
reconstruction data must be passed in <tt>publicKeyReconstData</tt>.

@param[in]  eccParams             An ECC parameters object.
@param[in]  ephemeralPublicKey    An ECC public key object of CA's ephemeral 
                                  public key.
@param[in]  publicKeyRequestData  An ECC public key object of the requester's 
                                  public key request data.
@param[out] publicKeyReconstData  ECC public key object pointer of the public 
                                  key reconstruction data.
@param[in]  sbCtx                 A global context.

@retval SB_ERR_NULL_PARAMS        The <tt>eccParams</tt> object is
                                  <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS         
@retval SB_ERR_NULL_EPHEM_PUB_KEY The <tt>ephemeralPublicKey</tt> object is
                                  <tt>NULL</tt>.
@retval SB_ERR_BAD_EPHEM_PUB_KEY  The <tt>ephemeralPublicKey</tt> object is
                                  invalid.
@retval SB_ERR_NULL_PUBLIC_KEY    The <tt>publicKeyRequestData</tt> object is
                                  <tt>NULL</tt>.
@retval SB_ERR_BAD_PUBLIC_KEY     The <tt>publicKeyRequestData</tt> object is
                                  invalid.
@retval SB_ERR_NULL_OUTPUT        The <tt> publicKeyReconstData</tt> object
                                  pointer is <tt>NULL</tt>.
@retval SB_FAIL_ALLOC             Memory allocation failure.
@retval SB_SUCCESS                Success.

*/

extern
SB_EXPORT
int 
SB_CALLCONV
hu_ECQVPubKeyReconstGen(
    sb_Params eccParams,
    sb_PublicKey ephemeralPublicKey,
    sb_PublicKey publicKeyRequestData,
    sb_PublicKey *publicKeyReconstData,
    sb_GlobalCtx sbCtx
);


/** Generates private key reconstruction data from the CA's private key, the 
 * CA's ephemeral private key and a hash of the certificate.

The public key reconstruction data must be generated prior to calling this
function and it must be included in the certificate.

Please note that this is function does not perform any hashing, and therefore,
the message digest of the certificate must be supplied in 
<tt>messageDigest</tt>.

@param[in]  eccParams              An ECC parameters object.
@param[in]  privateKey             An ECC private key object of the CA's private
                                   key.
@param[in]  ephemeralPrivateKey    An ECC private key object of the CA's 
                                   ephemeral private key.
@param[in]  digestLen              The length of the message digest.
@param[in]  messageDigest          Message digest of the certificate.
@param[out] privateKeyReconstData  An ECC private key object pointer of the
                                   private key reconstruction data.
@param[in]  sbCtx                  A global context.

@retval SB_ERR_NULL_PARAMS        The <tt>eccParams</tt> object is
                                  <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS         
@retval SB_ERR_NULL_PRIVATE_KEY   The <tt>privateKey</tt> object is
                                  <tt>NULL</tt>.
@retval SB_ERR_BAD_PRIVATE_KEY    The <tt>privateKey</tt> object is invalid.
@retval SB_ERR_NULL_EPHEM_PRI_KEY The <tt>ephemeralPrivateKey</tt> object is
                                  <tt>NULL</tt>.
@retval SB_ERR_BAD_EPHEM_PRI_KEY  The <tt>ephemeralPrivateKey</tt> object is
                                  invalid.
@retval SB_ERR_NULL_INPUT_BUF     Message digest pointer is <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_LEN      Message digest length is zero.
@retval SB_ERR_NULL_OUTPUT        The <tt>privateKeyReconstData</tt> object
                                  pointer is <tt>NULL</tt>.
@retval SB_FAIL_ALLOC             Memory allocation failure.
@retval SB_SUCCESS                Success. 
 
*/

extern
SB_EXPORT
int 
SB_CALLCONV
hu_ECQVPriKeyReconstGen(
    sb_Params eccParams,
    sb_PrivateKey privateKey,
    sb_PrivateKey ephemeralPrivateKey,
    size_t digestLen,
    const unsigned char *messageDigest,
    sb_PrivateKey *privateKeyReconstData,
    sb_GlobalCtx sbCtx
);


/** Derives a private key from private key request data, private key
reconstruction data and a hash of the certificate.

Please note that this is function does not perform any hashing, and therefore,
the message digest of the certificate must be supplied in 
<tt>messageDigest</tt>.

@param[in]  eccParams              An ECC parameters object.
@param[in]  privateKeyRequestData  An ECC private key object of the requester's 
                                   private key request data.
@param[in]  privateKeyReconstData  An ECC private key object of the private key 
                                   reconstruction data.
@param[in]  digestLen              The length of the message digest.
@param[in]  messageDigest          Message digest of the certificate.
@param[out] privateKey             ECC private key object pointer of the 
                                   requester's private key.
@param[in]  sbCtx                  A global context.

@retval SB_ERR_NULL_PARAMS        The <tt>eccParams</tt> object is
                                  <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS         
@retval SB_ERR_NULL_EPHEM_PRI_KEY The <tt>privateKeyRequestData</tt> object
                                  is <tt>NULL</tt>.
@retval SB_ERR_BAD_EPHEM_PRI_KEY  The <tt>privateKeyRequestData</tt> object
                                  is invalid.
@retval SB_ERR_NULL_PRIVATE_KEY   The <tt>privateKeyReconstData</tt> object
                                  is <tt>NULL</tt>.
@retval SB_ERR_BAD_PRIVATE_KEY    The <tt>privateKeyReconstData</tt> object
                                  is invalid.
@retval SB_ERR_NULL_INPUT_BUF     Message digest pointer is <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_LEN      Message digest length is zero.
@retval SB_ERR_NULL_OUTPUT        The <tt>privateKey</tt> object pointer is
                                  <tt>NULL</tt>.
@retval SB_FAIL_ALLOC             Memory allocation failure.
@retval SB_SUCCESS                Success. 
 
*/

extern
SB_EXPORT
int 
SB_CALLCONV
hu_ECQVPriKeyDerive(
    sb_Params eccParams,
    sb_PrivateKey privateKeyRequestData,
    sb_PrivateKey privateKeyReconstData,
    size_t digestLen,
    const unsigned char *messageDigest,
    sb_PrivateKey *privateKey,
    sb_GlobalCtx sbCtx
);


/** Checks that the private key reconstruction data and certificate are valid 
 * using public key request data, public key reconstruction data, the CA's 
 * public key, and a hash of the certificate.

Please note that this is function does not perform any hashing, and therefore,
the message digest of the certificate must be supplied in 
<tt>messageDigest</tt>.

@param[in]  eccParams              An ECC parameters object.
@param[in]  privateKeyReconstData  An ECC private key object of the private key 
                                   reconstruction data.
@param[in]  publicKeyReconstData   An ECC public key object of the public key 
                                   reconstruction data.
@param[in]  publicKeyRequestData   An ECC public key object of the requester's 
                                   public key request data.
@param[in]  caPublicKey            An ECC public key object of CA's public key.
@param[in]  digestLen              The length of the message digest.
@param[in]  messageDigest          Message digest of the certificate.
@param[out] result                 The validation result. This is non-zero if 
                                   valid; zero if invalid.
@param[in]  sbCtx                  A global context.

@retval SB_ERR_NULL_PARAMS        The <tt>eccParams</tt> object is
                                  <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS         
@retval SB_ERR_NULL_PRIVATE_KEY   The <tt>privateKeyReconstData</tt> object
                                  is <tt>NULL</tt>.
@retval SB_ERR_BAD_PRIVATE_KEY    The <tt>privateKeyReconstData</tt> object
                                  is invalid.
@retval SB_ERR_NULL_PUBLIC_KEY    The <tt>publicKeyReconstData</tt> object
                                  is <tt>NULL</tt>.
@retval SB_ERR_BAD_PUBLIC_KEY     The <tt>publicKeyReconstData</tt> object
                                  is invalid.
@retval SB_ERR_NULL_EPHEM_PUB_KEY The <tt>publicKeyRequestData</tt> object
                                  is <tt>NULL</tt>.
@retval SB_ERR_BAD_EPHEM_PUB_KEY  The <tt>publicKeyRequestData</tt> object
                                  is invalid.
@retval SB_ERR_NULL_REM_PUB_KEY   The <tt>caPublicKey</tt> object is
                                  <tt>NULL</tt>.
@retval SB_ERR_BAD_REM_PUB_KEY    The <tt>caPublicKey</tt> object is invalid.
@retval SB_ERR_NULL_INPUT_BUF     Message digest pointer is <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_LEN      Message digest length is zero.
@retval SB_ERR_NULL_OUTPUT        The validation result pointer is 
                                  <tt>NULL</tt>.
@retval SB_FAIL_ALLOC             Memory allocation failure.
@retval SB_SUCCESS                Success. 
 
*/

extern
SB_EXPORT
int 
SB_CALLCONV
hu_ECQVPriKeyValidate(
    sb_Params eccParams,
    sb_PrivateKey privateKeyReconstData,
    sb_PublicKey publicKeyReconstData,
    sb_PublicKey publicKeyRequestData,
    sb_PublicKey caPublicKey,
    size_t digestLen,
    const unsigned char *messageDigest,
    int *result,
    sb_GlobalCtx sbCtx
);


/** Converts public key reconstruction data into a public key using the CA's
public key and a hash of the certificate.

Please note that this is function does not perform any hashing, and therefore,
the message digest of the certificate must be supplied in 
<tt>messageDigest</tt>.

@param[in]  eccParams             An ECC parameters object.
@param[in]  publicKeyReconstData  An ECC public key object of the public key
                                  reconstruction data.
@param[in]  caPublicKey           An ECC public key object of CA's public key.
@param[in]  digestLen             The length of the message digest.
@param[in]  messageDigest         Message digest of the certificate.
@param[out] publicKey             ECC public key object pointer of the resulting
                                  public key.
@param[in]  sbCtx                 A global context.

@retval SB_ERR_NULL_PARAMS      The <tt>eccParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS       
@retval SB_ERR_NULL_PUBLIC_KEY  The <tt>publicKeyReconstData</tt> object is
                                <tt>NULL</tt>.
@retval SB_ERR_BAD_PUBLIC_KEY   The <tt>publicKeyReconstData</tt> object is
                                invalid.
@retval SB_ERR_NULL_REM_PUB_KEY The <tt>caPublicKey</tt> object is
                                <tt>NULL</tt>.
@retval SB_ERR_BAD_REM_PUB_KEY  The <tt>caPublicKey</tt> object is invalid.
@retval SB_ERR_NULL_INPUT_BUF   Message digest pointer is <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_LEN    Message digest length is zero.
@retval SB_ERR_NULL_OUTPUT      The <tt>publicKey</tt> object pointer is
                                <tt>NULL</tt>.
@retval SB_FAIL_ALLOC           Memory allocation failure.
@retval SB_SUCCESS              Success. 
 
*/

extern
SB_EXPORT
int 
SB_CALLCONV
hu_ECQVPubKeyConv(
    sb_Params eccParams,
    sb_PublicKey publicKeyReconstData,
    sb_PublicKey caPublicKey,
    size_t digestLen,
    const unsigned char *messageDigest,
    sb_PublicKey *publicKey,
    sb_GlobalCtx sbCtx
);

/** @} */ 

/** @addtogroup hu_ecc_ecnr_api ECC ECNR APIs
 *
 * @{
 */


/** Generates a signature on the given message digest using ECNR.

This function assumes that the input is a message digest (of any length);
no digest operation will be performed on the input.

The ECC parameter object must have been created with an RNG context.

If the length of s is known, a pointer to a buffer large enough to hold s
should be passed in <tt>sValue</tt> and its length in
<tt>sLength</tt>. This function will copy s into <tt>sValue</tt> and
set the actual length of s in <tt>sLength</tt>.

If <tt>sValue</tt> is <tt>NULL</tt>, this function will set the correct
length of s in <tt>sLength</tt>.  If <tt>sValue</tt> is not
<tt>NULL</tt> but <tt>sLength</tt> is too small, this function will
return an error.

Similarly for r.

s and r will always have the same length.

The length of s or r can also be determined by calling
<tt>hu_ECCParamsGet()</tt> and retrieving the <tt>OrdLen</tt>
argument.

@param[in]     eccParams      An ECC parameters object.
@param[in]     privateKey     An ECC private key object.
@param[in]     length         The length (in bytes) of the message digest.
@param[in]     messageDigest  The message digest.
@param[in,out] sLength        The length (in bytes) of <tt>sValue</tt>.
@param[out]    sValue         The 's' component from the signature computation.
@param[in,out] rLength        The length (in bytes) of <tt>rValue</tt>.
@param[out]    rValue         The 'r' component from the signature computation. 
                              This is the x-coordinate of the ephemeral public 
			      key.
@param[in]  sbCtx             A global context.

@retval SB_ERR_NULL_PARAMS       The <tt>eccParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS        
@retval SB_ERR_NULL_PRIVATE_KEY  The <tt>privateKey</tt> object <tt>NULL</tt>.
@retval SB_ERR_BAD_PRIVATE_KEY   The <tt>privateKey</tt> object invalid.
@retval SB_ERR_BAD_INPUT_BUF_LEN The message digest length is invalid.
@retval SB_ERR_NULL_INPUT_BUF    The message digest is <tt>NULL</tt>.
@retval SB_ERR_NULL_S_VALUE_LEN  The signature component length is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_S_VALUE_LEN   The signature component length is invalid.
@retval SB_ERR_NULL_R_VALUE_LEN  The signature component length is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_R_VALUE_LEN   The signature component length is invalid.
@retval SB_FAIL_ALLOC            Memory allocation failure.
@retval SB_SUCCESS               Success.
*/
extern
SB_EXPORT
int
SB_CALLCONV
hu_ECNRNoHashSign(
   sb_Params eccParams,
   sb_PrivateKey privateKey,
   size_t length,
   const unsigned char *messageDigest,
   size_t *sLength,
   unsigned char *sValue,
   size_t *rLength,
   unsigned char *rValue,
   sb_GlobalCtx sbCtx
);


/** Verifies an ECNR signature on the given message digest.

This function assumes that the input is a message digest (of any length);
no digest operation will be performed on the input.

If the signature is valid for the given digest, this function will return
<tt>SB_SUCCESS</tt> and set <tt>result</tt> to a non-zero value.

If the signature is not valid for the given digest, this function will return
<tt>SB_SUCCESS</tt> but <tt>result</tt> will be set to zero.

@param[in]  eccParams      An ECC parameters object.
@param[in]  publicKey      An ECC public key object.
@param[in]  length         The length (in bytes) of the message digest.
@param[in]  messageDigest  A message digest.
@param[in]  sLength        The length (in bytes) of <tt>sValue</tt>.
@param[in]  sValue         The <tt>s</tt> component of the signature.
@param[in]  rLength        The length (in bytes) of <tt>rValue</tt>.
@param[in]  rValue         The <tt>r</tt> component of the signature.
@param[out] result         The verification result. This is non-zero if the 
                           signature is valid; zero if the signature is invalid.
@param[in]  sbCtx          A global context.

@retval SB_ERR_NULL_PARAMS       The <tt>eccParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS        
@retval SB_ERR_NULL_PUBLIC_KEY   The <tt>publicKey</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PUBLIC_KEY    The <tt>publicKey</tt> object is invalid.
@retval SB_ERR_BAD_INPUT_BUF_LEN The message digest length is invalid.
@retval SB_ERR_NULL_INPUT_BUF    The message digest is <tt>NULL</tt>.
@retval SB_ERR_NULL_S_VALUE      The signature component is <tt>NULL</tt>.
@retval SB_ERR_BAD_S_VALUE_LEN   The signature component length is invalid.
@retval SB_ERR_NULL_R_VALUE      The signature component is <tt>NULL</tt>.
@retval SB_ERR_BAD_R_VALUE_LEN   The signature component length is invalid.
@retval SB_ERR_NULL_OUTPUT       The verification result pointer is 
                                 <tt>NULL</tt>.
@retval SB_FAIL_ALLOC            Memory allocation failure.
@retval SB_SUCCESS               Success.
*/
extern
SB_EXPORT
int
SB_CALLCONV
hu_ECNRNoHashVerify(
   sb_Params eccParams,
   sb_PublicKey publicKey,
   size_t length,
   const unsigned char *messageDigest,
   size_t sLength,
   const unsigned char *sValue,
   size_t rLength,
   const unsigned char *rValue,
   int *result,
   sb_GlobalCtx sbCtx
);

/** @} */


#ifdef __cplusplus
}
#endif

#endif
