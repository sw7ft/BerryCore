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
/* $Id: hursa.h 41616 2010-11-23 15:54:14Z thowie $
 * $Source$
 * $Name$
 */
#ifndef HURSA_H
#define HURSA_H

/** @file */

#ifdef __cplusplus
extern "C" {
#endif

#include "sbdef.h"

/** @addtogroup hu_rsa_api RSA APIs
 *
 *@{
 */

/** Creates an RSA parameters object for the specified modulus size.

An RNG context must be supplied if key generation or encryption will be
performed. A yielding context must be supplied if yielding will be performed.

@param[in]  modulusSize  The length (in bits) of the RSA modulus. This value 
                         must be greater than or equal to 512.
@param[in]  rngContext   An RNG context. (Optional - set to <tt>NULL</tt> if key
                         generation and encryption will not be performed.)
@param[in]  yieldCtx     A yield context. (Optional - set to <tt>NULL</tt> if
                         yielding is not required.)
@param[out] rsaParams    The RSA parameters object pointer.
@param[in]  sbCtx        A global context.

@retval SB_ERR_BAD_INPUT       The modulus size is invalid.
@retval SB_ERR_NULL_PARAMS_PTR The <tt>rsaParams</tt> object pointer is 
                               <tt>NULL</tt>.
@retval SB_FAIL_ALLOC          Memory allocation failure.
@retval SB_SUCCESS             Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAParamsCreate(
    size_t modulusSize,
    sb_RNGCtx rngContext,
    sb_YieldCtx yieldCtx,
    sb_Params *rsaParams,
    sb_GlobalCtx sbCtx
);


/** Retrieves settings from an RSA parameters object.

@param[in]  rsaParams    RSA parameters object.
@param[out] modulusSize  The length (in bits) of the RSA modulus.
@param[in]  sbCtx        A global context.

@retval SB_ERR_NULL_PARAMS The <tt>rsaParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS  
@retval SB_ERR_NULL_OUTPUT The output buffer is <tt>NULL</tt>.
@retval SB_SUCCESS         Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAParamsGet(
    sb_Params rsaParams,
    size_t *modulusSize,
    sb_GlobalCtx sbCtx
);


/** Destroys an RSA parameters object.

@param[in,out] rsaParams  The RSA parameters object pointer.
@param[in]     sbCtx      A global context.

@retval SB_ERR_NULL_PARAMS_PTR The <tt>rsaParams</tt> object pointer is 
                               <tt>NULL</tt>.
@retval SB_ERR_NULL_PARAMS     The <tt>rsaParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS      
@retval SB_SUCCESS             Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAParamsDestroy(
    sb_Params *rsaParams,
    sb_GlobalCtx sbCtx
);


/** Creates an RSA private and/or public key object from the given key
value(s).

A private key object can be created by supplying one of the following
combinations of key data:

<ul>
<li><tt>p</tt>, <tt>q</tt>, <tt>d</tt>
<li><tt>p</tt>, <tt>q</tt>, <tt>d mod p-1</tt>,
<tt>d mod q-1</tt>
<li><tt>n</tt>, <tt>d</tt>, <tt>e</tt>
<li><tt>n</tt>, <tt>d</tt>
</ul>

Private key objects contains the key data in the CRT format.
The following rules apply:

<ul>
<li>If <tt>p</tt> and <tt>q</tt> are supplied, either <tt>d mod p-1</tt>
and <tt>d mod q-1</tt>, or <tt>d</tt> must be supplied.
If all three are supplied, <tt>d</tt> will be ignored, and no check will be
performed to ensure that the values are self-consistent.
<li>If <tt>p</tt>, <tt>q</tt> and <tt>qInvModP</tt> are supplied,
then no check is performed to ensure that the values are self-consistent.
<li>If <tt>n</tt> and <tt>d</tt> are supplied, <tt>n</tt> is factored to
construct CRT format using <tt>e</tt>.
In all cases, public exponent <tt>e</tt> is required.
If <tt>e</tt> is not supplied, this function will assume a default value of
65537 (0x10001) as the public exponent.
</ul>

Private key object always

A public key object can be created by supplying <tt>n</tt> and,
optionally, <tt>e</tt>. If <tt>e</tt> is not supplied, this function
will assume a default value of 65537 (0x10001) as the public exponent.

@param[in]  rsaParams   An RSA parameters object.
@param[in]  eLen        The length (in bytes) of the public exponent. Must be 
                        less than or equal to <tt>nLen</tt>.
@param[in]  e           The public exponent.
@param[in]  nLen        The length (in bytes) of the modulus.
@param[in]  n           The modulus.
@param[in]  dLen        The length (in bytes) of the private exponent. Must be 
                        less than or equal to <tt>nLen</tt>.
@param[in]  d           The private exponent.
@param[in]  pLen        The length (in bytes) of the first prime p. Must be less
                        than or equal to <tt>nLen</tt>.
@param[in]  p           First large prime factor of the modulus.
@param[in]  qLen        The length (in bytes) of the second prime p. Must be 
                        less than or equal to <tt>nLen</tt>.
@param[in]  q           Second large prime factor of the modulus.
@param[in]  dModPLen    The length (in bytes) of the d mod p-1 CRT coefficient. 
                        Must be equal to <tt>pLen</tt>.
@param[in]  dModPm1     d mod p-1 CRT coefficient.
@param[in]  dModQLen    The length (in bytes) of the d mod q-1 CRT coefficient. 
                        Must be equal to <tt>qLen</tt>.
@param[in]  dModQm1     d mod q-1 CRT coefficient.
@param[in]  qInvLen     The length (in bytes) of q inverse mod p CRT 
                        coefficient.
@param[in]  qInvModP    q inverse mod p CRT coefficient.
@param[out] privateKey  The private key object pointer.
@param[out] publicKey   The public key object pointer.
@param[in]  sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS   The <tt>rsaParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS    
@retval SB_ERR_NULL_OUTPUT   Both the private and public key object pointers 
                             are <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT     Not enough key data supplied to create a key.
@retval SB_ERR_BAD_RSA_E_LEN The length of the public exponent is invalid.
@retval SB_FAIL_ALLOC        Memory allocation failure.
@retval SB_SUCCESS           Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAKeySet(
    sb_Params rsaParams,
    size_t eLen,
    const unsigned char *e,
    size_t nLen,
    const unsigned char *n,
    size_t dLen,
    const unsigned char *d,
    size_t pLen,
    const unsigned char *p,
    size_t qLen,
    const unsigned char *q,
    size_t dModPLen,
    const unsigned char *dModPm1,
    size_t dModQLen,
    const unsigned char *dModQm1,
    size_t qInvLen,
    const unsigned char *qInvModP,
    sb_PrivateKey *privateKey,
    sb_PublicKey *publicKey,
    sb_GlobalCtx sbCtx
);


/** Creates an RSA private and public key object from random data.

If the public exponent is not supplied (i.e. set to <tt>NULL</tt>),
this function will assume a default value of 65537 (0x10001).

@param[in]  rsaParams   An RSA parameters object.
@param[in]  eLen        The length (in bytes) of the public exponent. (Optional)
@param[in]  e           The public exponent. (Optional - set to <tt>NULL</tt> if
                        the default value should be used.)
@param[out] privateKey  The private key object pointer.
@param[out] publicKey   The public key object pointer.
@param[in]  sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS   The <tt>rsaParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS    
@retval SB_ERR_NULL_OUTPUT   The private and/or public key object pointers 
                             are <tt>NULL</tt>.
@retval SB_ERR_BAD_RSA_E_LEN The length of the public exponent is invalid.
@retval SB_FAIL_ALLOC        Memory allocation failure.
@retval SB_SUCCESS           Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAKeyGen(
    sb_Params rsaParams,
    size_t eLen,
    const unsigned char *e,
    sb_PrivateKey *privateKey,
    sb_PublicKey *publicKey,
    sb_GlobalCtx sbCtx
);


/** Retrieves the key values and their lengths from an RSA private
and/or public key object.

The following values and their lengths can be retrieved from an RSA private
key: <tt>n</tt>, <tt>d</tt>, <tt>p</tt>, <tt>q</tt>, <tt>d
mod p-1</tt>, <tt>d mod q-1</tt>, <tt>q inverse mod p</tt>.

The following values and their lengths can be retrieved from an RSA public
key: <tt>n</tt>, <tt>e</tt>.

If the prime factors <tt>p</tt> and <tt>q</tt> were generated or
computed by the library, this function will return the primes such that
<tt>p</tt> is numerically greater or equal to <tt>q</tt>. Otherwise,
if these primes were supplied during key setting, this function will
return them as given.

If the length of a key data value is known, a pointer to a buffer large
enough to hold the key data value should be passed in the appropriate
argument and its length in the corresponding length argument. This function
will copy the value into the buffer and set the actual length of the value in
the length argument.

If key value buffer is <tt>NULL</tt>, then this function will set the correct
length of the key value in the length argument. If the buffer is not
<tt>NULL</tt> but buffer length is too small, this function will return
an error.

Set both the parameter argument and its length to <tt>NULL</tt> for
any parameters that are to be ignored.

@param[in]     rsaParams   An RSA parameters object.
@param[in]     privateKey  An RSA private key object.
@param[in]     publicKey   An RSA public key object.
@param[in,out] eLen        The length (in bytes) of the public exponent.
@param[out]    e           The public exponent.
@param[in,out] nLen        The length (in bytes) of the modulus.
@param[out]    n           Modulus.
@param[in,out] dLen        The length (in bytes) of the private exponent. (This 
                           is the same as <tt>nLen</tt>.)
@param[out]    d           The private exponent.
@param[in,out] pLen        The length (in bytes) of the first prime p.
@param[out]    p           First large prime factor of the modulus.
@param[in,out] qLen        The length (in bytes) of the second prime q.
@param[out]    q           Second large prime factor of the modulus.
@param[in,out] dModPLen    The length (in bytes) of the d mod p-1 CRT 
                           coefficient. (This is the same as <tt>pLen</tt>.)
@param[out]    dModPm1     d mod p-1 CRT coefficient.
@param[in,out] dModQLen    The length (in bytes) of the d mod q-1 CRT 
                           coefficient. (This is the same as <tt>qLen</tt>.)
@param[out]    dModQm1     d mod q-1 CRT coefficient.
@param[in,out] qInvLen     The length (in bytes) of q inverse mod p CRT 
                           coefficient. (This is the same as <tt>pLen</tt>.)
@param[out]    qInvModP    q inverse mod p CRT coefficient.
@param[in]     sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS            The <tt>rsaParams</tt> object is 
                                      <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS             
@retval SB_ERR_NULL_INPUT             Both the private key and public key 
                                      objects are <tt>NULL</tt>.
@retval SB_ERR_BAD_PRIVATE_KEY        The private key object is invalid.
@retval SB_ERR_BAD_PUBLIC_KEY         The public key object is invalid.
@retval SB_ERR_PRI_KEY_NOT_EXPORTABLE The private exponent (d) is not 
                                      exportable.
@retval SB_ERR_RSA_CRT_NOT_AVAILABLE  The CRT components (p, q, d mod p-1, 
                                      d mod q-1, q inverse mod p) cannot be 
				      retrieved.
@retval SB_SUCCESS                    Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAKeyGet(
    sb_Params rsaParams,
    sb_PrivateKey privateKey,
    sb_PublicKey publicKey,
    size_t *eLen,
    unsigned char *e,
    size_t *nLen,
    unsigned char *n,
    size_t *dLen,
    unsigned char *d,
    size_t *pLen,
    unsigned char *p,
    size_t *qLen,
    unsigned char *q,
    size_t *dModPLen,
    unsigned char *dModPm1,
    size_t *dModQLen,
    unsigned char *dModQm1,
    size_t *qInvLen,
    unsigned char *qInvModP,
    sb_GlobalCtx sbCtx
);


/** Destroys an RSA private and/or public key object.

@param[in]     rsaParams   An RSA parameters object.
@param[in,out] privateKey  The private key object pointer.
@param[in,out] publicKey   The public key object pointer.
@param[in]     sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS      The <tt>rsaParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS       
@retval SB_ERR_NULL_PRIVATE_KEY The private key object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PRIVATE_KEY  The private key object is invalid.
@retval SB_ERR_NULL_PUBLIC_KEY  The public key object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PUBLIC_KEY   The public key object is invalid.
@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAKeyDestroy(
    sb_Params rsaParams,
    sb_PrivateKey *privateKey,
    sb_PublicKey  *publicKey,
    sb_GlobalCtx sbCtx
);


/** Produces an output block by applying the basic RSA primitive on an
input block using a public key.

The mathematical operation performed is raising the input value
to the public exponent modulo the modulus.

The input value, treated as the octet string encoding of an integer, must be
numerically smaller than the modulus.

The <tt>input</tt> and <tt>output</tt> buffers may point to the
same address.

The length of the modulus can be determined by calling
<tt>hu_RSAKeyGet()</tt> and retrieving the <tt>nLen</tt> argument.

@param[in]  rsaParams  An RSA parameters object.
@param[in]  publicKey  An RSA public key object.
@param[in]  input      The input buffer. This must be equal to the modulus 
                       length.
@param[out] output     The output buffer. This must be equal to the modulus 
                       length.
@param[in]  sbCtx      A global context.

@retval SB_ERR_NULL_PARAMS     The <tt>rsaParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS      
@retval SB_ERR_NULL_PUBLIC_KEY The <tt>publicKey</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PUBLIC_KEY  The <tt>publicKey</tt> object is invalid.
@retval SB_ERR_NULL_INPUT_BUF  The <tt>input</tt> buffer is <tt>NULL</tt>.
@retval SB_ERR_NULL_OUTPUT_BUF The <tt>output</tt> buffer is <tt>NULL</tt>.
@retval SB_FAIL_ALLOC          Memory allocation failure.
@retval SB_SUCCESS             Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAPublicEncrypt(
    sb_Params rsaParams,
    sb_PublicKey publicKey,
    const unsigned char * input,
    unsigned char * output,
    sb_GlobalCtx sbCtx
);


/** Produces an output block by applying the basic RSA primitive on an
input block using a private key.

The mathematical operation performed is raising the input value
to the private exponent modulo the modulus.

The input value, treated as the octet string encoding of an integer, must be
numerically smaller than the modulus.

The <tt>input</tt> and <tt>output</tt> buffers may point to the
same address.

The length of the modulus can be determined by calling
<tt>hu_RSAKeyGet()</tt> and retrieving the <tt>nLen</tt> argument.

@param[in]  rsaParams   An RSA parameters object.
@param[in]  privateKey  An RSA private key object.
@param[in]  input       The input buffer. This must be equal to the modulus 
                        length.
@param[out] output      The output buffer. This must be equal to the modulus
                        length.
@param[in]  sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS      The <tt>rsaParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS       
@retval SB_ERR_NULL_PRIVATE_KEY The <tt>privateKey</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PRIVATE_KEY  The <tt>privateKey</tt> object is invalid.
@retval SB_ERR_NULL_INPUT_BUF   The <tt>input</tt> buffer is <tt>NULL</tt>.
@retval SB_ERR_NULL_OUTPUT_BUF  The <tt>output</tt> buffer is <tt>NULL</tt>.
@retval SB_FAIL_ALLOC           Memory allocation failure.
@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAPrivateDecrypt(
    sb_Params rsaParams,
    sb_PrivateKey privateKey,
    const unsigned char *input,
    unsigned char *output,
    sb_GlobalCtx sbCtx
);


/** This function is identical to the <tt>hu_RSAPublicEncrypt()</tt> function.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAPublicDecrypt(
    sb_Params rsaParams,
    sb_PublicKey publicKey,
    const unsigned char * input,
    unsigned char * output,
    sb_GlobalCtx sbCtx
);


/** This function is identical to the <tt>hu_RSAPrivateDecrypt()</tt> function.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAPrivateEncrypt(
    sb_Params rsaParams,
    sb_PrivateKey privateKey,
    const unsigned char *input,
    unsigned char *output,
    sb_GlobalCtx sbCtx
);

/** @} */

/** @addtogroup hu_pkcs_api PKCS APIs
 *
 *@{
 */

/** Encrypts a single plaintext block by applying the PKCS#1 v1.5 encryption
scheme with an RSA public key.

This function implements the operation known as RSAES-PKCS1-v1_5-Encrypt in
PKCS#1 v2.1.

The RSA parameter object must have been created with an RNG context.

If the length of the ciphertext is known, a pointer to a buffer large enough
to hold the ciphertext should be passed in <tt>ciphertext</tt> and its
length in <tt>ciphertextLen</tt>. This function will copy the ciphertext
into <tt>ciphertext</tt> and set the actual length of the ciphertext in
<tt>ciphertextLen</tt>.

If <tt>ciphertext</tt> is <tt>NULL</tt>, then this function will set
the correct length of the ciphertext value in <tt>ciphertextLen</tt>.  If
<tt>ciphertext</tt> is not <tt>NULL</tt> but <tt>ciphertextLen</tt>
is too small, this function will return an error and also will set the correct
length of the ciphertext value in <tt>ciphertextLen</tt>.

The length of the modulus can be determined by calling
<tt>hu_RSAKeyGet()</tt> and retrieving the <tt>nLen</tt> argument.

@param[in]     rsaParams      An RSA parameters object.
@param[in]     publicKey      An RSA public key object.
@param[in]     plaintextLen   The length (in bytes) of the plaintext. This must 
                              be at most the modulus length minus 11.
@param[in]     plaintext      The plaintext buffer.
@param[in,out] ciphertextLen  The length (in bytes) of the ciphertext buffer. 
                              This must be at least the modulus length.
@param[out]    ciphertext     The ciphertext buffer.
@param[in]     sbCtx          A global context.

@retval SB_ERR_NULL_PARAMS             The <tt>rsaParams</tt> object is 
                                       <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS              
@retval SB_ERR_NULL_PUBLIC_KEY         The public key object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PUBLIC_KEY          The public key object is invalid.
@retval SB_ERR_NULL_INPUT_BUF          The plaintext buffer is <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN       The length of the plaintext is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF_LEN_PTR The ciphertext buffer length is <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN      The ciphertext buffer length is invalid.
@retval SB_FAIL_ALLOC                  Memory allocation failure.
@retval SB_SUCCESS                     Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAPKCS1v15Enc(
    sb_Params rsaParams,
    sb_PublicKey publicKey,
    size_t plaintextLen,
    const unsigned char *plaintext,
    size_t *ciphertextLen,
    unsigned char *ciphertext,
    sb_GlobalCtx sbCtx
);


/** Decrypts a single ciphertext block by applying the PKCS#1 v1.5 decryption
scheme with an RSA private key.

This function implements the operation known as RSAES-PKCS1-v1_5-Decrypt in
PKCS#1 v2.1.

If the length of the plaintext is known, a pointer to a buffer large enough to 
hold the plaintext should be passed in <tt>plaintext</tt> and its length in 
<tt>plaintextLen</tt>. This function will copy the plaintext into 
<tt>plaintext</tt> and set the actual length of the plaintext in 
<tt>plaintextLen</tt>.

If <tt>plaintext</tt> is <tt>NULL</tt>, or <tt>plaintext</tt> is not 
<tt>NULL</tt> but <tt>plaintextLen</tt> is too small, this function will set the
maximum length of the plaintext in <tt>plaintextLen</tt>.

The length of the modulus can be determined by calling
<tt>hu_RSAKeyGet()</tt> and retrieving the <tt>nLen</tt> argument.

@param[in]     rsaParams      An RSA parameters object.
@param[in]     privateKey     An RSA private key object.
@param[in]     ciphertextLen  The length (in bytes) of the ciphertext buffer. 
                              This must be equal to the modulus length.
@param[in]     ciphertext     The ciphertext buffer.
@param[in,out] plaintextLen   The length (in bytes) of the plaintext. This will 
                              be at most the modulus length minus 11.
@param[out]    plaintext      The plaintext buffer.
@param[in]     sbCtx          A global context.

@retval SB_ERR_NULL_PARAMS             The <tt>rsaParams</tt> object is 
                                       <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS              
@retval SB_ERR_NULL_PRIVATE_KEY        The private key object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PRIVATE_KEY         The private key object is invalid.
@retval SB_ERR_NULL_INPUT_BUF          The ciphertext buffer is <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN       The ciphertext buffer length is 
                                       incorrect.
@retval SB_ERR_NULL_OUTPUT_BUF_LEN_PTR The plaintext buffer length is 
                                       <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN      The plaintext buffer length is invalid.
@retval SB_FAIL_ALLOC                  Memory allocation failure.
@retval SB_SUCCESS                     Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAPKCS1v15Dec(
    sb_Params rsaParams,
    sb_PrivateKey privateKey,
    size_t ciphertextLen,
    const unsigned char *ciphertext,
    size_t *plaintextLen,
    unsigned char *plaintext,
    sb_GlobalCtx sbCtx
);


/** Message digest algorithm identifiers for use with the PKCS#1 v1.5
signature functions */

#define SB_RSA_PKCS1_V15_SIG_SHA1    0
#define SB_RSA_PKCS1_V15_SIG_MD5     1
#define SB_RSA_PKCS1_V15_SIG_MD2     2
#define SB_RSA_PKCS1_V15_SIG_SHA224  3
#define SB_RSA_PKCS1_V15_SIG_SHA256  4
#define SB_RSA_PKCS1_V15_SIG_SHA384  5
#define SB_RSA_PKCS1_V15_SIG_SHA512  6


/** Generates a signature on the given message digest by applying the
PKCS#1 v1.5 signature scheme.

This function implements the operation known as RSASSA-PKCS1-v1_5-Sign
in PKCS#1 v2.1.

This function assumes that the input is a message digest produced by the 
specified digest algorithm; no digest operation will be performed on the input.

If the length of the signature is known, a pointer to a buffer large enough
to hold the signature should be passed in <tt>signature</tt> and its length in 
<tt>signatureLen</tt>. This function will copy the signature into 
<tt>signature</tt> and set the actual length of the signature in 
<tt>signatureLen</tt>.

If <tt>signature</tt> is <tt>NULL</tt>, or <tt>signature</tt> is not 
<tt>NULL</tt> but <tt>signatureLen</tt> is too small, this function will set the
maximum length of the signature in <tt>signatureLen</tt>.

The length of the modulus can be determined by calling
<tt>hu_RSAKeyGet()</tt> and retrieving the <tt>nLen</tt> argument.

@param[in]     rsaParams     An RSA parameters object.
@param[in]     privateKey    An RSA private key object.
@param[in]     hashAlgId     The message digest algorithm identifier. 
                             The acceptable values are one of the 
			     <tt>SB_RSA_PKCS1_V15_SIG_*</tt> macros.
@param[in]     digestLen     The length (in bytes) of the message digest.
@param[in]     digest        The message digest.
@param[in,out] signatureLen  The length (in bytes) of the signature. This must 
                             be at least the modulus length.
@param[out]    signature     The signature value.
@param[in]     sbCtx         A global context.

@retval SB_ERR_NULL_PARAMS             The <tt>rsaParams</tt> object is 
                                       <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS              
@retval SB_ERR_NULL_PRIVATE_KEY        The private key object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PRIVATE_KEY         The private key object is invalid.
@retval SB_ERR_BAD_HASH_TYPE           The message digest algorithm identifier 
                                       is invalid.
@retval SB_ERR_NULL_INPUT_BUF          The message digest buffer is 
                                       <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN       The length of the message digest is 
                                       invalid.
@retval SB_ERR_NULL_OUTPUT_BUF_LEN_PTR The length of the signature buffer is 
                                       <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN      The signature buffer is invalid.
@retval SB_FAIL_ALLOC                  Memory allocation failure.
@retval SB_SUCCESS                     Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAPKCS1v15NoHashSign(
    sb_Params rsaParams,
    sb_PrivateKey privateKey,
    int hashAlgId,
    size_t digestLen,
    const unsigned char *digest,
    size_t *signatureLen,
    unsigned char *signature,
    sb_GlobalCtx sbCtx
);


/** Verifies a PKCS#1 v1.5 signature on the given message digest.

This function implements the operation known as RSASSA-PKCS1-v1_5-Verify
in PKCS#1 v2.1.

This function assumes that the input is a message digest produced by the
specified digest algorithm; no digest operation will be performed on the
input. If the specified digest algorithm does not match the algorithm encoded
in the signature, an error will be returned.

If the signature is valid for the given digest, this function will return
<tt>SB_SUCCESS</tt> and set <tt>result</tt> to a non-zero value.

If the signature is not valid for the given digest, this function may return
<tt>SB_SUCCESS</tt> but <tt>result</tt> will be set to zero.

The length of the modulus can be determined by calling
<tt>hu_RSAKeyGet()</tt> and retrieving the <tt>nLen</tt> argument.

@param[in]  rsaParams     An RSA parameters object.
@param[in]  publicKey     An RSA public key object.
@param[in]  hashAlgId     The message digest algorithm identifier. The 
                          acceptable values are one of the 
			  <tt>SB_RSA_PKCS1_V15_SIG_*</tt> macros.
@param[in]  digestLen     The length (in bytes) of the message digest.
@param[in]  digest        The message digest.
@param[in]  signatureLen  The length (in bytes) of the signature. This must be 
                          equal to the modulus length.
@param[in]  signature     The signature value.
@param[out] result        Verification result. This is non-zero if the signature
                          is valid; otherwise this is zero, meaning that the 
			  signature is invalid.
@param[in]  sbCtx         A global context.

@retval SB_ERR_NULL_PARAMS       The <tt>rsaParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS        
@retval SB_ERR_NULL_PUBLIC_KEY   The public key object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PUBLIC_KEY    The public key object is invalid.
@retval SB_ERR_BAD_HASH_TYPE     The message digest algorithm identifier is 
                                 invalid.
@retval SB_ERR_NULL_INPUT_BUF    The message digest buffer is <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN The length of the message digest is invalid.
@retval SB_ERR_NULL_SIGNATURE    The signature buffer is <tt>NULL</tt>.
@retval SB_ERR_BAD_SIGNATURE_LEN The length of the signature buffer is invalid.
@retval SB_ERR_BAD_HASH_TYPE     The message digest algorithm identifier is 
                                 invalid.
@retval SB_FAIL_BAD_PADDING      The signature was not properly padded.
@retval SB_ERR_NULL_OUTPUT       The verification result pointer is 
                                 <tt>NULL</tt>.
@retval SB_FAIL_ALLOC            Memory allocation failure.
@retval SB_SUCCESS               Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAPKCS1v15NoHashVerify(
    sb_Params rsaParams,
    sb_PublicKey publicKey,
    int hashAlgId,
    size_t digestLen,
    const unsigned char *digest,
    size_t signatureLen,
    const unsigned char *signature,
    int *result,
    sb_GlobalCtx sbCtx
);


/** Produces a ciphertext block by applying the basic RSA primitive on
a PKCS#1 v1.5 signature padded plaintext block using an RSA private key.

This function implements a modified version of the operation known as
RSASSA-PKCS1-v1_5-Sign in PKCS#1 v2.1. The encoding of a message digest into
an ASN.1 DigestInfo structure with DER is replaced by the plaintext message
unchanged.

In other words, the operation consists of padding the plaintext
message using the block formatting of EMSA-PKCS1-v1_5-Encode, and applying
the basic RSA primitive on the padded message using a private key.

If the length of the ciphertext is known, a pointer to a buffer large enough
to hold the ciphertext should be passed in <tt>sigtext</tt> and its
length in <tt>sigtextLen</tt>. This function will copy the ciphertext
into <tt>sigtext</tt> and set the actual length of the ciphertext in
<tt>sigtextLen</tt>.

If <tt>sigtext</tt> is <tt>NULL</tt>, this function will set the
correct length of the ciphertext in <tt>sigtextLen</tt>.  If
<tt>sigtext</tt> is not <tt>NULL</tt> but <tt>sigtextLen</tt> is
too small, this function will return an error and set the correct length of the
ciphertext in <tt>sigtextLen</tt>.

The length of the modulus can be determined by calling
<tt>hu_RSAKeyGet()</tt> and retrieving the <tt>nLen</tt> argument.

@param[in]     rsaParams   An RSA parameters object.
@param[in]     privateKey  An RSA private key object.
@param[in]     messageLen  The length (in bytes) of the plaintext buffer. This 
                           must be at most the modulus length minus 11.
@param[in]     message     The plaintext buffer.
@param[in,out] sigtextLen  The length (in bytes) of the ciphertext buffer.
                           This must be at least the modulus length.
@param[out]    sigtext     The ciphertext buffer.
@param[in]     sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS             The <tt>rsaParams</tt> object is 
                                       <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS              
@retval SB_ERR_NULL_PRIVATE_KEY        The private key object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PRIVATE_KEY         The private key object is invalid.
@retval SB_ERR_NULL_INPUT_BUF          The plaintext buffer is <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN       The plaintext buffer length is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF_LEN_PTR The ciphertext buffer length is 
                                       <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN      The ciphertext buffer length is invalid.
@retval SB_FAIL_ALLOC                  Memory allocation failure.
@retval SB_SUCCESS                     Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAPKCS1v15SigPadExponent(
    sb_Params rsaParams,
    sb_PrivateKey privateKey,
    size_t messageLen,
    const unsigned char *message,
    size_t *sigtextLen,
    unsigned char *sigtext,
    sb_GlobalCtx sbCtx
);


/** Produces a plaintext block by applying the basic RSA primitive using a
public key on a ciphertext block that was PKCS#1 v1.5 signature padded.

This function implements a modified version of the operation known as
RSASSA-PKCS1-v1_5-Verify in PKCS#1 v2.1. The encoding of a message digest into
an ASN.1 DigestInfo structure with DER is replaced by the plaintext message
unchanged.

In other words, the operation consists of applying the basic RSA primitive on
the ciphertext using a public key, ensuring that the decrypted block uses the
block formatting of EMSA-PKCS1-v1_5-Encode, and returning the unpadded
plaintext.

If the length of the plaintext is known, a pointer to a buffer large enough
to hold the plaintext should be passed in <tt>message</tt> and its
length in <tt>messageLen</tt>. This function will copy the plaintext
into <tt>message</tt> and set the actual length of the plaintext in
<tt>messageLen</tt>.

If <tt>message</tt> is <tt>NULL</tt>, or <tt>message</tt>
is not <tt>NULL</tt> but <tt>messageLen</tt> is too small, this
function will set the maximum length of the plaintext in
<tt>messageLen</tt>.

The length of the modulus can be determined by calling
<tt>hu_RSAKeyGet()</tt> and retrieving the <tt>nLen</tt> argument.

@param[in]     rsaParams   An RSA parameters object.
@param[in]     publicKey   An RSA public key object.
@param[in]     sigtextLen  The length (in bytes) of the ciphertext buffer. This 
                           must be equal to the modulus length.
@param[in]     sigtext     The ciphertext buffer.
@param[in,out] messageLen  The length (in bytes) of the plaintext buffer. This 
                           must be at most the modulus length minus 11.
@param[out]    message     The plaintext buffer.
@param[in]     sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS             The <tt>rsaParams</tt> object is 
                                       <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS              
@retval SB_ERR_NULL_PUBLIC_KEY         The public key object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PUBLIC_KEY          The public key object is invalid.
@retval SB_ERR_NULL_INPUT_BUF          The ciphertext buffer is <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN       The ciphertext buffer length is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF_LEN_PTR The plaintext buffer length is 
                                       <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN      The plaintext buffer length is invalid.
@retval SB_FAIL_ALLOC                  Memory allocation failure.
@retval SB_SUCCESS                     Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAPKCS1v15VerPadExponent(
    sb_Params rsaParams,
    sb_PublicKey publicKey,
    size_t sigtextLen,
    const unsigned char *sigtext,
    size_t *messageLen,
    unsigned char *message,
    sb_GlobalCtx sbCtx
);


/** Encrypts a single plaintext block by applying the PKCS#1 v2.1
RSAES-OAEP-Encrypt operation with SHA-1 and MGF1.

The RSA parameter object must have been created with an RNG context.

If the length of the ciphertext is known, a pointer to a buffer large enough
to hold the ciphertext should be passed in <tt>ciphertext</tt> and its
length in <tt>ciphertextLen</tt>. This function will copy the ciphertext
into <tt>ciphertext</tt> and set the actual length of the ciphertext in
<tt>ciphertextLen</tt>.

If <tt>ciphertext</tt> is <tt>NULL</tt>, then this function will set
the correct length of the ciphertext value in <tt>ciphertextLen</tt>.  If
<tt>ciphertext</tt> is not <tt>NULL</tt> but <tt>ciphertextLen</tt>
is too small, this function will return an error.

The length of the modulus can be determined by calling
<tt>hu_RSAKeyGet()</tt> and retrieving the <tt>nLen</tt> argument.

@param[in]     rsaParams      An RSA parameters object.
@param[in]     publicKey      An RSA public key object.
@param[in]     addInfoLen     The length (in bytes) of the message label. 
                              (Optional)
@param[in]     addInfo        The label to be associated with the message. 
                              (Optional - set to <tt>NULL</tt> if not used.)
@param[in]     plaintextLen   The length (in bytes) of the plaintext buffer. 
                              This must be at most the modulus length minus 42.
@param[in]     plaintext      The plaintext buffer.
@param[in,out] ciphertextLen  The length (in bytes) of the ciphertext buffer. 
                              This must be at least the modulus length.
@param[out]    ciphertext     The ciphertext buffer.
@param[in]     sbCtx          A global context.

@retval SB_ERR_NULL_PARAMS             The <tt>rsaParams</tt> object is 
                                       <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS              
@retval SB_ERR_NULL_PUBLIC_KEY         The public key object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PUBLIC_KEY          The public key object is invalid.
@retval SB_ERR_NULL_ADDINFO            The message label is <tt>NULL</tt>.
@retval SB_ERR_NULL_INPUT_BUF          The plaintext buffer is <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN       The plaintext buffer length is too large.
@retval SB_ERR_NULL_OUTPUT_BUF_LEN_PTR The ciphertext buffer length is 
                                       <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN      The ciphertext buffer length is invalid.
@retval SB_FAIL_ALLOC                  Memory allocation failure.
@retval SB_SUCCESS                     Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAPKCS1v21SHA1Encrypt(
    sb_Params rsaParams,
    sb_PublicKey publicKey,
    size_t addInfoLen,
    const unsigned char *addInfo,
    size_t plaintextLen,
    const unsigned char *plaintext,
    size_t *ciphertextLen,
    unsigned char *ciphertext,
    sb_GlobalCtx sbCtx
);


/** Decrypts a single ciphertext block by applying the PKCS#1 v2.1
RSAES-OAEP-Decrypt operation with SHA-1 and MGF1.

If the length of the plaintext is known, a pointer to a buffer large enough
to hold the plaintext should be passed in <tt>plaintext</tt> and its
length in <tt>plaintextLen</tt>. This function will copy the plaintext
into <tt>plaintext</tt> and set the actual length of the plaintext in
<tt>plaintextLen</tt>.

If <tt>plaintext</tt> is <tt>NULL</tt>, or <tt>plaintext</tt>
is not <tt>NULL</tt> but <tt>plaintextLen</tt> is too small, this
function will set the maximum length of the plaintext in
<tt>plaintextLen</tt>.

The length of the modulus can be determined by calling
<tt>hu_RSAKeyGet()</tt> and retrieving the <tt>nLen</tt> argument.

@param[in]      rsaParams      An RSA parameters object.
@param[in]      privateKey     An RSA private key object.
@param[in]      addInfoLen     The length (in bytes) of the message label. 
                               (Optional)
@param[in]      addInfo        The label to be associated with the message. 
                               (Optional - set to <tt>NULL</tt> if not used.)
@param[in]      ciphertextLen  The length (in bytes) of the ciphertext buffer. 
                               This must be equal to the modulus length.
@param[in]      ciphertext     The ciphertext buffer.
@param[in,out]  plaintextLen   The length (in bytes) of the plaintext buffer. 
                               This will be at most the modulus length minus 42.
@param[out]     plaintext      The plaintext buffer.
@param[in]      sbCtx          A global context.

@retval SB_ERR_NULL_PARAMS             The <tt>rsaParams</tt> object is 
                                       <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS              
@retval SB_ERR_NULL_PRIVATE_KEY        The private key object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PRIVATE_KEY         The private key object is invalid.
@retval SB_ERR_NULL_ADDINFO            The message label is <tt>NULL</tt>.
@retval SB_ERR_NULL_INPUT_BUF          The ciphertext buffer is <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN       The ciphertext buffer length is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF_LEN_PTR The plaintext buffer length is 
                                       <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN      The plaintext buffer length is invalid.
@retval SB_FAIL_PKCS1_DECRYPT          The decrypted data is incorrectly padded
                                       or <tt>addInfo</tt> does not match what 
				       was used to generate the ciphertext.
@retval SB_FAIL_ALLOC                  Memory allocation failure.
@retval SB_SUCCESS                     Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAPKCS1v21SHA1Decrypt(
    sb_Params rsaParams,
    sb_PrivateKey privateKey,
    size_t addInfoLen,
    const unsigned char *addInfo,
    size_t ciphertextLen,
    const unsigned char *ciphertext,
    size_t *plaintextLen,
    unsigned char *plaintext,
    sb_GlobalCtx sbCtx
);

/** @} */

/** @addtogroup hu_rsa_api RSA APIs
 *
 *@{
 */

/** This function performs the first two steps of RSA KEM: generating a random 
 * number and encrypting it with a public key.

If the <tt>secret</tt> or <tt>ciphertext</tt> buffer is set to <tt>NULL</tt>, 
the necessary length will be returned to <tt>secretLen</tt> or 
<tt>ciphertextLen</tt>.

If the length of the secret or ciphertext buffer is larger than necessary, 
this function will set <tt>secretLen</tt> or <tt>ciphertextLen</tt> to the 
right value upon return.

@param[in]     RSAParams      RSA parameters object.
@param[in]     publicKey      Public key object.
@param[in,out] secretLen      The length (in bytes) of the secret.
                              On input, this must not less than the modulus 
			      length.
@param[out]    secret         The buffer for the generated random number.
@param[in,out] ciphertextLen  The length (in bytes) of the ciphertext.
                              On input, this must not less than the modulus 
			      length.
@param[out]    ciphertext     Ciphertext.
@param[in]     sbCtx          Memory callback data.

@retval SB_ERR_NULL_PARAMS              RSA parameters object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS               RSA parameters object is invalid.
@retval SB_ERR_NULL_PUBLIC_KEY          Public key object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PUBLIC_KEY           Public key object is invalid.
@retval SB_ERR_NULL_CONTEXT             The <tt>rngCtx</tt> in 
                                        <tt>RSAParams</tt> is <tt>NULL</tt>.
@retval SB_ERR_NULL_OUTPUT_BUF_LEN_PTR  The <tt>secretLen</tt> or 
                                        <tt>ciphertextLen</tt> is <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN        The <tt>secretLen</tt> or 
                                        <tt>ciphertextLen</tt> is shorter than 
					necessary.
@retval SB_FAIL_ALLOC                   Memory allocation failure.
@retval SB_SUCCESS                      Success.

*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAKEMRawSecretEncrypt(
    sb_Params            RSAParams,
    sb_PublicKey         publicKey,
    size_t              *secretLen,
    unsigned char       *secret,
    size_t              *ciphertextLen,
    unsigned char       *ciphertext,
    sb_GlobalCtx         sbCtx
    );


/** Decrypt the ciphertext with a private key:

If the <tt>secret</tt> buffer is set to <tt>NULL</tt>, its necessary length 
will be returned to <tt>secretLen</tt>.

If the length of the secret buffer is larger than necessary, this function will 
set <tt>secretLen</tt> to the right value upon return.

@param[in]     RSAParams     RSA parameters object.
@param[in]     privateKey    Private key object.
@param[in]     ciphertextLen The length (in bytes) of the ciphertext.
                             This must be equal to the modulus length.
@param[in]     ciphertext    Ciphertext.
@param[in,out] secretLen     The length (in bytes) of the secret. On input, 
                             this must not less than the modulus length.
@param[out]    secret        The buffer for the decryption result
@param[in]     sbCtx         Memory callback data.

@retval SB_ERR_NULL_PARAMS              RSA parameters object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS               RSA parameters object is invalid.
@retval SB_ERR_NULL_PRIVATE_KEY         Private key object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PRIVATE_KEY          Private key object is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF_LEN_PTR  The <tt>secretLen</tt> is <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN        The <tt>secretLen</tt> or 
                                        <tt>ciphertextLen</tt> is shorter than 
					necessary.
@retval SB_FAIL_ALLOC                   Memory allocation failure.
@retval SB_SUCCESS                      Success.

*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAKEMRawSecretDecrypt(
    sb_Params            RSAParams,
    sb_PrivateKey        privateKey,
    size_t               ciphertextLen,
    const unsigned char *ciphertext,
    size_t              *secretLen,
    unsigned char       *secret,
    sb_GlobalCtx         sbCtx
    );


/** Get size of n (in bits) by giving p and q:

@param[in]  pLen          Byte length of the first large prime.
@param[in]  p             First large prime.
@param[in]  qLen          Byte length of the second large prime.
@param[in]  q             Second large prime.
@param[out] modulusBits   Bit length of the modulus.
@param[in]  sbCtx         Memory callback data.

@retval SB_ERR_BAD_INPUT_BUF_LEN        <tt>pLen</tt> or <tt>qLen</tt> is zero.
@retval SB_ERR_NULL_INPUT_BUF           <tt>p</tt> or <tt>q</tt> is 
                                        <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT                <tt>p</tt> or <tt>q</tt> is zero.
@retval SB_FAIL_ALLOC                   Memory allocation failure.
@retval SB_SUCCESS                      Success.

*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSANSizeGet(
    const size_t         pLen,
    const unsigned char *p,
    const size_t         qLen,
    const unsigned char *q,
    size_t              *modulusBits,
    sb_GlobalCtx         sbCtx
    );

/** @} */

#ifdef __cplusplus
}
#endif

#endif
