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
/* $Id: hursapss.h 36652 2008-03-14 19:59:06Z jgallant $
 * $Source$
 * $Name$
 */
#ifndef HURSAPSS_H
#define HURSAPSS_H

#include "sbdef.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Message digest algorithm identifiers for use with the PKCS#1 v2.1
PSS signature functions */

#define SB_RSA_PSS_SHA1      4
#define SB_RSA_PSS_SHA224    5
#define SB_RSA_PSS_SHA256    6
#define SB_RSA_PSS_SHA384    7
#define SB_RSA_PSS_SHA512    8

/** @addtogroup hu_rsapss_api RSA PSS APIs
 *
 * @{
 */

/** Generates a signature on the given message digest by applying the
PKCS#1 v2.1 signature scheme.

This function implements the operation known as RSASSA-PSS-Sign
in PKCS#1 v2.1.

This function uses the EMSA-PSS encoding method, with the MGF1 Mask
Generation function as described in PKCS#1 v2.1.

This function assumes that the input is a message digest produced by the
specified digest algorithm; no digest operation will be performed on the
input. The specified message digest algorithm will be used in the 
EMSA-PSS encoding method as well.

If the length of the signature is known, a pointer to a buffer large enough
to hold the signature should be passed in <tt>signature</tt> and its
length in <tt>signatureLen</tt>. This function will copy the signature
into <tt>signature</tt> and set the actual length of the signature in
<tt>signatureLen</tt>.

If <tt>signature</tt> is <tt>NULL</tt>, or <tt>signature</tt>
is not <tt>NULL</tt> but <tt>signatureLen</tt> is too small, this
function will return an error.

The value of <tt>saltLen</tt> determines the length of the salt that
will be used in the signature operation. It is recommended in PKCS#1 v2.1 
that this value be the same as <tt>digestLen</tt>. The salt length
used for the verification operation must match the salt length used for 

the signature operation. The recommended salt length should always
be used unless the salt length is clearly specified and known 
by both the signer and the verifier.

The modulus being used must be large enough for the data being signed. Thus,
the minimum size of the modulus depends on both the <tt>saltLen</tt> and 
<tt>digestLen</tt>. This minimum is roughly equal to the sum of 
<tt>saltLen</tt> and <tt>digestLen</tt>. The exact relation that must be 
preserved is: ((# of bits in the modulus) - 1) >= 8*<tt>digestLen</tt> + 8*<tt>saltLen</tt> + 9

The RSA parameter object must have been created with an RNG context if 
<tt>saltLen</tt> is not zero.


@param[in]     rsaParams     An RSA parameters object.
@param[in]     privateKey    An RSA private key object.
@param[in]     hashAlgId     The message digest algorithm identifier. The 
                             acceptable values are one of the 
			     <tt>SB_RSA_PSS_*</tt> macros.
@param[in]     digestLen     The length in bytes of the message digest.
@param[in]     digest        The message digest.
@param[in]     saltLen       The length of the salt. The recommended value is 
                             <tt>digestLen</tt>.
@param[in,out] signatureLen  The length in bytes of the signature. This must be 
                             at least the modulus length.
@param[out]    signature     The signature value.
@param[in]     sbCtx         A global context.

@retval SB_ERR_NULL_PARAMS             The <tt>rsaParams</tt> object is 
                                       <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS              The <tt>rsaParams</tt> object is invalid.
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
hu_RSAPSSNoHashSign(
    sb_Params rsaParams,
    sb_PrivateKey privateKey,
    int hashAlgId,
    size_t digestLen,
    const unsigned char *digest,
    size_t saltLen,
    size_t *signatureLen,
    unsigned char *signature,
    sb_GlobalCtx sbCtx
);


/** Verifies a PKCS#1 v2.1 signature on the given message digest.

This function implements the operation known as RSASSA-PSS-Verify
in PKCS#1 v2.1.

This function assumes that the input is a message digest produced by the
specified digest algorithm; no digest operation will be performed on the
input.

If the signature is valid for the given digest, this function will return
<tt>SB_SUCCESS</tt> and set <tt>result</tt> to a non-zero value.

If the signature is not valid for the given digest, this function may return
<tt>SB_SUCCESS</tt> but <tt>result</tt> will be set to zero.

The modulus being used must be large enough for the data being signed. Thus,
the minimum size of the modulus depends on both the <tt>saltLen</tt> and 
<tt>digestLen</tt>. This minimum is roughly equal to the sum of 
<tt>saltLen</tt> and <tt>digestLen</tt>. The exact relation that must be 
preserved is: ((# of bits in the modulus) - 1) >= 8*<tt>digestLen</tt> + 8*<tt>saltLen</tt> + 9

The value of <tt>saltLen</tt> specifies the length of the salt that
is expected by the verification operation. The value of <tt>saltLen</tt>
must match the value of <tt>saltLen</tt> that was used to generate the 
signature. It is recommended in PKCS#1 v2.1 that this value be the same as 
<tt>digestLen</tt>.

@param[in]  rsaParams     An RSA parameters object.
@param[in]  publicKey     An RSA public key object.
@param[in]  hashAlgId     The message digest algorithm identifier. The 
                          acceptable values are one of the <tt>SB_RSA_PSS_*</tt>
			  macros.
@param[in]  digestLen     The length in bytes of the message digest.
@param[in]  digest        The message digest.
@param[in]  saltLen       The length of the salt that was used to generate the 
                          signature. The recommended value of <tt>saltLen</tt> 
			  is <tt>digestLen</tt>. The value of <tt>saltLen</tt> 
			  must match the value of <tt>saltLen</tt> that was used
			  to generate the signature.
@param[in]  signatureLen  The length in bytes of the signature. This must be 
                          equal to the modulus length.
@param[in]  signature     The signature value.
@param[out] result        Verification result. This is non-zero if the signature
                          is valid; zero, if the signature is invalid.
@param[in]  sbCtx         A global context.

@retval SB_ERR_NULL_PARAMS       The <tt>rsaParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS        The <tt>rsaParams</tt> object is invalid.
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
@retval SB_ERR_NULL_OUTPUT       The verification result pointer is 
                                 <tt>NULL</tt>.
@retval SB_FAIL_ALLOC            Memory allocation failure.
@retval SB_SUCCESS               Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RSAPSSNoHashVerify(
    sb_Params rsaParams,
    sb_PublicKey publicKey,
    int hashAlgId,
    size_t digestLen,
    const unsigned char *digest,
    size_t saltLen,
    size_t signatureLen,
    const unsigned char *signature,
    int *result,
    sb_GlobalCtx sbCtx
);

/** @} */

#ifdef __cplusplus
}
#endif

#endif
