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
/* $Id: huidlc.h 41551 2010-11-15 16:47:14Z hwang $
 * $Source$
 * $Name$
 */
#ifndef HUIDLC_H
#define HUIDLC_H

/** @file */

#ifdef __cplusplus
extern "C" {
#endif

#include "sbdef.h"

/** @addtogroup hu_idlc_params IDLC Parameters
 *
 * @{
 */

/** ID for IPSec Group 1 (RFC 2409 First Oakley Group). */
#define HU_IDLC_GROUP_IPSEC_1  1

/** ID for IPSec Group 2 (RFC 2409 Second Oakley Group). */
#define HU_IDLC_GROUP_IPSEC_2  2

/** ID for IPSec Group 5 (RFC 3526 Group 5). */
#define HU_IDLC_GROUP_IPSEC_5  3

/** ID for WTLS Diffie-Hellman Group 1. */
#define HU_IDLC_GROUP_WTLS_1   4

/** ID for WTLS Diffie-Hellman Group 2. */
#define HU_IDLC_GROUP_WTLS_2   5

/** ID for IPSec Group 14 (RFC 3526 Group 14). */
#define HU_IDLC_GROUP_IPSEC_14  6

/** ID for IPSec Group 15 (RFC 3526 Group 15). */
#define HU_IDLC_GROUP_IPSEC_15  7

/** ID for IPSec Group 16 (RFC 3526 Group 16). */
#define HU_IDLC_GROUP_IPSEC_16  8

/** ID for IPSec Group 17 (RFC 3526 Group 17). */
#define HU_IDLC_GROUP_IPSEC_17  9

/** ID for IPSec Group 18 (RFC 3526 Group 18). */
#define HU_IDLC_GROUP_IPSEC_18  10


/** Generate IDLC domain parameters, and set them into the IDLC parameters
object.
This IDLC parameter object can be used for DH or DSA.

An RNG context must be supplied. A yielding context must be supplied if
yielding will be performed.

This function will generate values p, q, and g such that p and q are prime,
q is a divisor of (p-1), and g has order q modulo p. p will have bitlength
<tt>pSize</tt> and q will have bitlength <tt>qSize</tt>.

@param[in]  pSize       The length (in bits) of the prime modulus p. The length 
                        must be greater than or equal to 512.
@param[in]  qSize       The length (in bits) of the prime divisor q. The length 
                        must be greater than or equal to 160 and less than 
			<tt>pSize</tt>.
@param[in]  rngCtx      An RNG context.
@param[in]  yieldCtx    A yield context. (Optional - set to <tt>NULL</tt> if 
                        yielding is not required.)
@param[out] idlcParams  The IDLC parameters object pointer.
@param[in]  sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS_PTR The <tt>idlcParams</tt> object pointer is 
                               <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT       The length (in bits) of p or q was invalid.
@retval SB_FAIL_ALLOC          Memory allocation failure.
@retval SB_SUCCESS             Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_IDLCParamsGen(
    size_t pSize,
    size_t qSize,
    sb_RNGCtx rngCtx,
    sb_YieldCtx yieldCtx,
    sb_Params *idlcParams,
    sb_GlobalCtx sbCtx
);


/** GEnerate IDLC domain parameters based on ANSI X9.42, and set them into
the IDLC parameters object.
This IDLC parameter object can be used for DH or DSA.

An RNG context must be supplied. A yielding context must be supplied if
yielding will be performed.

This function will generate values p, q and g such that p and q are prime,
q is a divisor of (p-1) and g has order q modulo p. p will have bitlength
<tt>pSize</tt> and q will have bitlength <tt>qSize</tt>.

@param[in]  pSize       The length (in bits) of the prime modulus p. The length 
                        must be greater than or equal to 512.
@param[in]  qSize       The length (in bits) of the prime divisor q. The length 
                        must be greater than or equal to 160 and less than 
			<tt>pSize</tt>.
@param[in]  rngCtx      An RNG context.
@param[in]  yieldCtx    A yield context. (Optional - set to <tt>NULL</tt> if 
                        yielding is not required.)
@param[out] idlcParams  The IDLC parameters object pointer.
@param[in]  sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS_PTR The <tt>idlcParams</tt> object pointer is
                               <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT       The length of p and/or q was invalid.
@retval SB_FAIL_ALLOC          Memory allocation failure.
@retval SB_SUCCESS             Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_IDLCANSIParamsGen(
    size_t pSize,
    size_t qSize,
    sb_RNGCtx rngCtx,
    sb_YieldCtx yieldCtx,
    sb_Params *idlcParams,
    sb_GlobalCtx sbCtx
);


/** Generate IDLC domain parameters based on FIPS 186-3, and set them into
the IDLC parameters object.
This IDLC parameter object can be used for DH or DSA.

An RNG context must be supplied. A yielding context must be supplied if
yielding will be performed.

This function will generate values p, q, and g such that p and q are prime,
q is a divisor of (p-1) and, g has order q modulo p. p will have bitlength
<tt>pSize</tt> and q will have bitlength <tt>qSize</tt>.

@param[in]  pSize       The length (in bits) of the prime modulus p.
@param[in]  qSize       The length (in bits) of the prime divisor q.
@param[in]  rngCtx      An RNG context.
@param[in]  yieldCtx    A yield context. (Optional - set to <tt>NULL</tt> if 
                        yielding is not required.)
@param[out] idlcParams  The IDLC parameters object pointer.
@param[in]  sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS_PTR The <tt>idlcParams</tt> object pointer is 
                               <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT       The length of p and/or q was invalid.
@retval SB_FAIL_ALLOC          Memory allocation failure.
@retval SB_SUCCESS             Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_IDLCFIPSParamsGen(
    size_t pSize,
    size_t qSize,
    sb_RNGCtx rngCtx,
    sb_YieldCtx yieldCtx,
    sb_Params *idlcParams,
    sb_GlobalCtx sbCtx
);

/** Creates an IDLC parameters object from the given IDLC domain parameter
values.
This IDLC parameter object can be used for DSA.

An RNG context must be supplied. A yielding context must be supplied if
yielding will be performed.

The values should satisfy the following properties: p and q are prime, q is a
divisor of (p-1), and g has order q modulo p. The bit length of prime p must
be set in <tt>pSize</tt> and that of prime q in <tt>qSize</tt>.

@param[in]  pSize       The size (in bits) of the prime modulus p. The size 
                        must be greater than or equal to 512.
@param[in]  qSize       The size (in bits) of the prime divisor q. The size 
                        must be greater than or equal to 160 and less than 
			<tt>pSize</tt>.
@param[in]  pLength     The length (in bytes) of the prime modulus.
@param[in]  p           Prime modulus.
@param[in]  gLength     The length (in bytes) of the generator. Must be less 
                        than or equal to <tt>pLength</tt>.
@param[in]  g           Generator of order q.
@param[in]  qLength     The length (in bytes) of the prime divisor.
@param[in]  q           Prime divisor of p-1.
@param[in]  rngCtx      An RNG context.
@param[in]  yieldCtx    A yield context. (Optional - set to <tt>NULL</tt> if 
                        yielding is not required.)
@param[out] idlcParams  The IDLC parameters object pointer.
@param[in]  sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS_PTR   The <tt>idlcParams</tt> object pointer is 
                                 <tt>NULL</tt>.
@retval SB_ERR_NULL_IDLC_P       The prime modulus value is <tt>NULL</tt>.
@retval SB_ERR_NULL_IDLC_Q       The prime divisor value is <tt>NULL</tt>.
@retval SB_ERR_NULL_IDLC_G       The generator value is <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT         The bit size of p and/or q is invalid.
@retval SB_ERR_BAD_INPUT_BUF_LEN The length of the p, q and/or g buffers is 
                                 invalid.
@retval SB_FAIL_ALLOC            Memory allocation failure.
@retval SB_SUCCESS               Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_IDLCDSAParamsSet(
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

/** Creates an IDLC parameters object from the given IDLC domain parameter
values.
This IDLC parameter object can be used for DH.

An RNG context and/or yielding context must be supplied if key
generation and/or yielding will be performed, respectively.

The values should satisfy the following properties: p and q are prime, q is a
divisor of (p-1), and g has order q modulo p.  The bit length of prime p must
be set in <tt>pSize</tt> and that of prime q in <tt>qSize</tt>.

<tt>q</tt> is optional. If <tt>q</tt> is not supplied, then
<tt>qSize</tt> specifies the size of private keys to be used with these
parameters. In this case, if <tt>qSize</tt> is set to zero, the default
size of 160 bits will be used.

@param[in]  pSize       The length (in bits) of the prime modulus p. The length 
                        must be greater than or equal to 512.
@param[in]  qSize       The length (in bits) of the prime divisor q, if using. 
                        Otherwise, the length (in bits) of the private keys.
@param[in]  pLength     The length (in bytes) of the prime modulus.
@param[in]  p           Prime modulus.
@param[in]  gLength     The length (in bytes) of the generator. Must be less 
                        than or equal to <tt>pLength</tt>.
@param[in]  g           Generator of order q.
@param[in]  qLength     The length (in bytes) of the prime divisor. (Optional)
@param[in]  q           Prime divisor of p-1. (Optional)
@param[in]  rngCtx      An RNG context. (Optional - set to <tt>NULL</tt> if key 
                        generation will not be performed.)
@param[in]  yieldCtx    A yield context. (Optional - set to <tt>NULL</tt> if 
                        yielding is not required.)
@param[out] idlcParams  The IDLC parameters object pointer.
@param[in]  sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS_PTR   The <tt>idlcParams</tt> object pointer is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT         The length of p and/or q is invalid.
@retval SB_ERR_BAD_INPUT_BUF_LEN The length of the p, q and/or g buffers is 
                                 invalid.
@retval SB_FAIL_ALLOC            Memory allocation failure.
@retval SB_SUCCESS               Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_IDLCDHParamsSet(
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


/** Creates an IDLC parameters object from the given IDLC domain parameter
values.
This IDLC parameter object can be used for DH or DSA.

An RNG context must be supplied if key generation or DSA will be performed.
A yielding context must be supplied if yielding will be performed.

The values should satisfy the following properties: p and q are prime, q is a
divisor of (p-1), and g has order q modulo p.  The bit length of prime p must
be set in <tt>pSize</tt> and that of prime q in <tt>qSize</tt>.

<tt>q</tt> is optional. If <tt>q</tt> is not supplied, then
<tt>qSize</tt> specifies the size of private keys to be used with these
parameters. In this case, if <tt>qSize</tt> is set to zero, the default
size of 160 bits will be used.

@param[in]  pSize       The length (in bits) of the prime modulus p. The length 
                        must be greater than or equal to 512.
@param[in]  qSize       The length (in bits) of the prime divisor q, if using. 
                        Otherwise, the length (in bits) of the private keys.
@param[in]  pLength    The length (in bytes) of the prime modulus.
@param[in]  p           Prime modulus.
@param[in]  gLength     The length (in bytes) of the generator. Must be less 
                        than or equal to <tt>pLength</tt>.
@param[in]  g           Generator of order q.
@param[in]  qLength     The length (in bytes) of the prime divisor. (Optional)
@param[in]  q           Prime divisor of p-1. (Optional)
@param[in]  rngCtx      An RNG context. (Optional - set to <tt>NULL</tt> if key 
                        generation and DSA will not be performed.)
@param[in]  yieldCtx    A yield context. (Optional - set to <tt>NULL</tt> if 
                        yielding is not required.)
@param[out] idlcParams  The IDLC parameters object pointer.
@param[in]  sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS_PTR   The <tt>idlcParams</tt> object pointer is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT         The length of p and/or q is invalid.
@retval SB_ERR_BAD_INPUT_BUF_LEN The length of the p, q and/or g buffers is 
                                 invalid.
@retval SB_FAIL_ALLOC            Memory allocation failure.
@retval SB_SUCCESS               Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_IDLCParamsSet(
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


/** Creates an IDLC parameters object for the specified type of IDLC domain
parameter set.
This IDLC parameter object can be used for DH.

An RNG context must be supplied if key generation will be performed.
A yielding context must be supplied if yielding will be performed.

For IPSec Groups 1, 2 and 5, and wTLS Groups 1 and 2, private keys may be as
large as 160 bits.

For IPSec Group 14, private keys may be as large as 224 bits; for IPSec Group
15, 264 bits; for IPSec Group 16, 304 bits; for IPSec 17, 344 bits; for IPSec
Group 18, 384 bits.

@param[in]  paramset    A parameter set identifier. The acceptable values are 
                        one of the <tt>HU_IDLC_GROUP_*</tt> macros.
@param[in]  rngCtx      An RNG context. (Optional - set to <tt>NULL</tt> if key 
                        generation will not be performed.)
@param[in]  yieldCtx    A yield context. (Optional - set to <tt>NULL</tt> if 
                        yielding is not required.)
@param[out] idlcParams  The IDLC parameters object pointer.
@param[in]  sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS_PTR The <tt>idlcParams</tt> object pointer is 
                               <tt>NULL</tt>.
@retval SB_ERR_IDLC_BAD_GROUP  The parameter set identifier is invalid.
@retval SB_FAIL_ALLOC          Memory allocation failure.
@retval SB_SUCCESS             Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_IDLCParamsCreate(
    int paramset,
    sb_RNGCtx rngCtx,
    sb_YieldCtx yieldCtx,
    sb_Params *idlcParams,
    sb_GlobalCtx sbCtx
);


/** Retrieves settings from an IDLC parameters object.

If the length of a parameter is known, a pointer to a buffer large enough to 
hold the parameter should be passed in the appropriate argument and its length 
in the corresponding length argument. This function will copy the value into the
buffer and set the actual length of the value in the length argument.

If a parameter argument is <tt>NULL</tt>, this function will set the correct 
length of the parameter in the length argument.  If the argument is not 
<tt>NULL</tt> but the corresponding length argument is too small, this function 
will return an error.

Set both the parameter argument and its length to <tt>NULL</tt> for
any parameters that are to be ignored.

@param[in]  idlcParams  An IDLC parameters object.
@param[out] pSize       The length (in bits) of the prime modulus p.
@param[out] qSize       The length (in bits) of the prime divisor q, if using. 
                        Otherwise, the length (in bits) of the private keys.
@param[out] pLength     The length (in bytes) of the prime modulus.
@param[out] p           Prime modulus.
@param[out] gLength     The length (in bytes) of the generator. Equal to 
                        <tt>pLength</tt>.
@param[out] g           Generator of order q.
@param[out] qLength     The length (in bytes) of the prime divisor, if using. 
                        Otherwise, <tt>0</tt> will be returned.
@param[out] q           Prime divisor of <tt>p-1</tt>, if using.
@param[in]  sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS        The <tt>idlcParams</tt> object is 
                                  <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS         
@retval SB_ERR_BAD_OUTPUT_BUF_LEN The length of the output buffer is invalid.
@retval SB_SUCCESS                Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_IDLCParamsGet(
    sb_Params idlcParams,
    size_t *pSize,
    size_t *qSize,
    size_t *pLength,
    unsigned char *p,
    size_t *gLength,
    unsigned char *g,
    size_t *qLength,
    unsigned char *q,
    sb_GlobalCtx sbCtx
);


/** Destroys an IDLC parameters object.

IDLC contexts and key objects must be destroyed before their corresponding
IDLC parameters object is destroyed.

@param[in,out]  idlcParams  The IDLC parameters object pointer.
@param[in]      sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS_PTR The <tt>idlcParams</tt> object pointer is 
                               <tt>NULL</tt>.
@retval SB_ERR_NULL_PARAMS     The <tt>idlcParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS      
@retval SB_SUCCESS             Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_IDLCParamsDestroy(
    sb_Params *idlcParams,
    sb_GlobalCtx sbCtx
);

/** @} */

/** @addtogroup hu_idlc_key IDLC Keys
 *
 * @{
 *
 */

/** Creates an IDLC private and/or public key object from the given key
value(s).

If both private and public key values are supplied, a private key and/or a
public key object can be created. The key objects will be created from the
corresponding key values.

If only a private key value is supplied, a private key and/or a public key
object can be created. The public key will be computed from the private key.

If only a public key value is supplied, only a public key object can be
created.

When a public key is supplied, this function attempts to validate it using
the specification in Section 5.6.2.4 of NIST SP 800-56A.
This operation is applied when the domain parameter q is available in the IDLC
parameters object (<tt>idlcParams</tt>). In such a case, it will cost 
approximately the same amount of time as computing a DH shared secret. When an 
IDLC parameters object does not include the q value, this operation will not be 
applied. The IDLC parameters object will not include the q value, if the 
parameters object was created by the <tt>hu_IDLCParamsCreate()</tt> function, 
or by the <tt>hu_IDLCParamsSet()</tt> function without supplying the q value.
 
@param[in]  idlcParams       IDLC parameters object.
@param[in]  privateKeyLen    The length (in bytes) of the private key value.
@param[in]  privateKeyValue  The private key value.
@param[in]  publicKeyLen     The length (in bytes) of the public key value.
@param[in]  publicKeyValue   The public key value.
@param[out] privateKey       The private key object pointer.
@param[out] publicKey        The public key object pointer.
@param[in]  sbCtx            A global context.

@retval SB_ERR_NULL_PARAMS          The <tt>idlcParams</tt> object is 
                                    <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS           
@retval SB_ERR_NULL_PRI_KEY_BUF     The private key value is <tt>NULL</tt>.
@retval SB_ERR_BAD_PRI_KEY_BUF_LEN  The private key length is invalid.
@retval SB_ERR_NULL_PUB_KEY_BUF     The public key value is <tt>NULL</tt>.
@retval SB_ERR_BAD_PUB_KEY_BUF_LEN  The public key length is invalid.
@retval SB_FAIL_INVALID_PRIVATE_KEY The private key value is invalid.
@retval SB_ERR_BAD_PUBLIC_KEY       The public key is invalid.
@retval SB_FAIL_ALLOC               Memory allocation failure.
@retval SB_SUCCESS                  Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_IDLCKeySet(
    sb_Params idlcParams,
    size_t privateKeyLen,
    const unsigned char *privateKeyValue,
    size_t publicKeyLen,
    const unsigned char *publicKeyValue,
    sb_PrivateKey *privateKey,
    sb_PublicKey *publicKey,
    sb_GlobalCtx sbCtx
);


/** Creates an IDLC private key object from random data, and, optionally,
the corresponding public key object.

The IDLC parameter object must have been created with an RNG context.

@param[in]  idlcParams  An IDLC parameters object.
@param[out] privateKey  The private key object pointer.
@param[out] publicKey   The public key object pointer.
@param[in]  sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS The <tt>idlcParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS  
@retval SB_FAIL_ALLOC      Memory allocation failure.
@retval SB_SUCCESS         Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_IDLCKeyGen(
    sb_Params idlcParams,
    sb_PrivateKey *privateKey,
    sb_PublicKey *publicKey,
    sb_GlobalCtx sbCtx
);


/** Retrieves the key values and their lengths from an IDLC private
and/or public key object.

If the length of the key value is known, a pointer to a buffer large enough to 
hold the key value should be passed in the key value buffer and its length in 
the corresponding length argument. This function will copy the key value into 
the buffer and set the actual length of the key value in the length argument.

If <tt>keyValue</tt> is <tt>NULL</tt>, then this function will set the correct 
length of the key value in <tt>keyLen</tt>.  If <tt>keyValue</tt> is not 
<tt>NULL</tt> but <tt>keyLen</tt> is too small, this function will return an 
error.

@param[in]     idlcParams       An IDLC parameters object.
@param[in]     privateKey       An IDLC private key object.
@param[in]     publicKey        An IDLC public key object.
@param[in,out] privateKeyLen    The length (in bytes) of the private key buffer.
@param[out]    privateKeyValue  The private key buffer.
@param[in,out] publicKeyLen     The length (in bytes) of the public key buffer.
@param[out]    publicKeyValue   The public key buffer.
@param[in]     sbCtx            A global context.

@retval SB_ERR_NULL_PARAMS            The <tt>idlcParams</tt> object is 
                                      <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS             
@retval SB_ERR_NULL_INPUT             Both of the private and public key objects
                                      are <tt>NULL</tt>.
@retval SB_ERR_BAD_PRIVATE_KEY        The private key object is invalid.
@retval SB_ERR_BAD_PRI_KEY_BUF_LEN    The private key buffer length is invalid.
@retval SB_ERR_BAD_PUBLIC_KEY         The public key object is invalid.
@retval SB_ERR_BAD_PUB_KEY_BUF_LEN    The public key buffer length is invalid.
@retval SB_ERR_NULL_KEY_LEN           The length of the key buffer is 
                                      <tt>NULL</tt>.
@retval SB_ERR_PRI_KEY_NOT_EXPORTABLE The private key buffer cannot be 
                                      retrieved.
@retval SB_SUCCESS                    Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_IDLCKeyGet(
    sb_Params idlcParams,
    sb_PrivateKey privateKey,
    sb_PublicKey publicKey,
    size_t *privateKeyLen,
    unsigned char *privateKeyValue,
    size_t *publicKeyLen,
    unsigned char *publicKeyValue,
    sb_GlobalCtx sbCtx
);


/** Destroys an IDLC private and/or public key object.

IDLC key objects must be destroyed before the IDLC parameters object is
destroyed.

@param[in]     idlcParams  The IDLC parameters object.
@param[in,out] privateKey  The IDLC private key object pointer.
@param[in,out] publicKey   The IDLC public key object pointer.
@param[in]     sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS      The <tt>idlcParams</tt> object is <tt>NULL</tt>.
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
hu_IDLCKeyDestroy(
    sb_Params idlcParams,
    sb_PrivateKey *privateKey,
    sb_PublicKey *publicKey,
    sb_GlobalCtx sbCtx
);

/** @} */

/** @addtogroup hu_idlc_dh IDLC DH
 *
 * @{
 *
 */

/** Generates a shared secret of the requested length by applying the ANSI
X9.42/X9.63 KDF with SHA-1 to the output of a DH key agreement.

@param[in]  idlcParams       IDLC parameters object.
@param[in]  privateKey       IDLC private key object.
@param[in]  remotePublicKey  IDLC public key object.
@param[in]  addInfoLen       The length (in bytes) of additional information.
                             (Optional)
@param[in]  addInfo          Additional information for use with the KDF. 
                             (Optional - set to <tt>NULL</tt> if not used.)
@param[in]  secretLen        The length (in bytes) of the shared secret.
@param[out] sharedSecret     Shared secret value.
@param[in]  sbCtx            A global context.

@retval SB_ERR_NULL_PARAMS        The <tt>idlcParams</tt> object is 
                                  <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS         
@retval SB_ERR_NULL_PRIVATE_KEY   The private key object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PRIVATE_KEY    The private key object is invalid.
@retval SB_ERR_NULL_PUBLIC_KEY    The public key object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PUBLIC_KEY     The public key object is invalid.
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
hu_IDLCDHSharedGen(
    sb_Params idlcParams,
    sb_PrivateKey privateKey,
    sb_PublicKey remotePublicKey,
    size_t addInfoLen,
    const unsigned char *addInfo,
    size_t secretLen,
    unsigned char *sharedSecret,
    sb_GlobalCtx sbCtx
);


/** Generates a shared secret that is the output of a DH key agreement.

If the length of the shared secret is known, a pointer to a buffer large
enough to hold the shared secret should be passed in
<tt>sharedSecret</tt> and its length in <tt>secretLen</tt>. This
function will copy the shared secret into <tt>sharedSecret</tt> and set
the actual length of the shared secret in <tt>secretLen</tt>.

If <tt>sharedSecret</tt> is <tt>NULL</tt>, this function will set the
correct length of the shared secret in <tt>secretLen</tt>.  If
<tt>sharedSecret</tt> is not <tt>NULL</tt> but <tt>secretLen</tt>
is too small, this function will return an error.

The length of the shared secret can also be determined by calling
<tt>hu_IDLCParamsGet()</tt> and retrieving the <tt>pLength</tt> argument.

@param[in]     idlcParams       An IDLC parameters object.
@param[in]     privateKey       An IDLC private key object.
@param[in]     remotePublicKey  An IDLC public key object.
@param[in,out] secretLen        The length (in bytes) of the shared secret.
@param[out]    sharedSecret     The shared secret buffer.
@param[in]     sbCtx            A global context.

@retval SB_ERR_NULL_PARAMS         The <tt>idlcParams</tt> object is 
                                   <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS          
@retval SB_ERR_NULL_PRIVATE_KEY    The private key object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PRIVATE_KEY     The private key object is invalid.
@retval SB_ERR_NULL_PUBLIC_KEY     The public key object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PUBLIC_KEY      The public key object is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF_LEN The shared secret buffer length is 
                                   <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN  The length of the shared secret is invalid.
@retval SB_FAIL_ALLOC              Memory allocation failure.
@retval SB_SUCCESS                 Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_IDLCDHRawSharedGen(
    sb_Params idlcParams,
    sb_PrivateKey privateKey,
    sb_PublicKey remotePublicKey,
    size_t *secretLen,
    unsigned char *sharedSecret,
    sb_GlobalCtx sbCtx
);


/** @} */

/** @addtogroup hu_idlc_dsa IDLC DSA
 *
 * @{
 *
 */

/** Generates a signature on the given message digest using DSA based on
FIPS 186.

This function assumes that the input is a message digest (of any length);
no digest operation will be performed on the input.

The IDLC parameter object must have been created with an RNG context.

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
<tt>hu_IDLCParamsGet()</tt> and retrieving the <tt>qLength</tt> argument.

@param[in]     idlcParams     An IDLC parameters object.
@param[in]     privateKey     An IDLC private key object.
@param[in]     length         The length (in bytes) of the message digest.
@param[in]     messageDigest  A message digest.
@param[in,out] sLength        The length (in bytes) of <tt>sValue</tt>.
@param[out]    sValue         The 's' component from the signature computation.
@param[in,out] rLength        The length (in bytes) of <tt>rValue</tt>.
@param[out]    rValue         The 'r' component from the signature computation.
@param[in]     sbCtx          A global context.

@retval SB_ERR_NULL_PARAMS       The <tt>idlcParams</tt> object is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS        
@retval SB_ERR_NULL_PRIVATE_KEY  The private key object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PRIVATE_KEY   The private key object is invalid.
@retval SB_ERR_BAD_INPUT_BUF_LEN The length of the message digest is invalid.
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
hu_IDLCDSANoHashSign(
    sb_Params idlcParams,
    sb_PrivateKey privateKey,
    size_t length,
    const unsigned char *messageDigest,
    size_t *sLength,
    unsigned char *sValue,
    size_t *rLength,
    unsigned char *rValue,
    sb_GlobalCtx sbCtx
);


/** Verifies a DSA signature on the given message digest based on FIPS 186.

This function assumes that the input is a message digest (of any length);
no digest operation will be performed on the input.

If the signature is valid for the given digest, this function may return
<tt>SB_SUCCESS</tt> and set <tt>result</tt> to a non-zero value.

If the signature is not valid for the given digest, this function may return
<tt>SB_SUCCESS</tt> but <tt>result</tt> will be set to zero.

@param[in]  idlcParams     An IDLC parameters object.
@param[in]  publicKey      An IDLC public key object.
@param[in]  length         The length (in bytes) of the message digest.
@param[in]  messageDigest  The message digest.
@param[in]  sLength        The length (in bytes) of <tt>sValue</tt>.
@param[in]  sValue         The <tt>s</tt> component of the signature.
@param[in]  rLength        The length (in bytes) of <tt>rValue</tt>.
@param[in]  rValue         The <tt>r</tt> component of the signature.
@param[out] result         Verification result. This is non-zero if the 
                           signature is valid; otherwise it is zero, meaning the
			   signature is invalid.
@param[in]  sbCtx          A global context.

@retval SB_ERR_NULL_PARAMS       The <tt>idlcParams</tt> object is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS        
@retval SB_ERR_NULL_PUBLIC_KEY   The public key object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PUBLIC_KEY    The public key object is invalid.
@retval SB_ERR_BAD_INPUT_BUF_LEN The length of the message digest is invalid.
@retval SB_ERR_NULL_INPUT_BUF    The message digest is <tt>NULL</tt>.
@retval SB_ERR_NULL_S_VALUE      The signature component is <tt>NULL</tt>.
@retval SB_ERR_BAD_S_VALUE_LEN   The signature component length is invalid.
@retval SB_ERR_NULL_R_VALUE      The signature component is <tt>NULL</tt>.
@retval SB_ERR_BAD_R_VALUE_LEN   The signature component length is invalid.
@retval SB_ERR_NULL_OUTPUT       The verification result pointer is 
                                 <tt>NULL</tt>.
@retval SB_FAIL_ALLOC            Memory allocation failure.
@retval SB_SUCCESS Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_IDLCDSANoHashVerify(
    sb_Params idlcParams,
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
