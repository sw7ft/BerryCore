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
/* $Id: hupkc.h 44184 2012-05-29 21:07:39Z thowie $
 * $Source$
 * $Name$
 */
#ifndef HUPKC_H
#define HUPKC_H

/** @file */

#ifdef __cplusplus
extern "C" {
#endif

#include "sbdef.h"

/** @addtogroup hu_pkc_api Abstract key-pair APIs
 *
 * @{
 */

/** Generate a private and public key object from random data.

For ECC and IDLC params objects, the <tt>params</tt> completely specifies
the keys. For RSA, keys are generated with the default public exponent (see
<tt>hu_RSAKeyGen()</tt> for more details).

@param[in]  params      A parameters object pointer.
@param[out] privateKey  The private key object pointer. 
@param[out] publicKey   The public key object pointer. 
@param[in]  sbCtx       A global context. 

@retval SB_ERR_NULL_PARAMS      The <tt>params</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS       
@retval SB_ERR_NULL_PRIVATE_KEY The <tt>privateKey</tt> object is <tt>NULL</tt>.
@retval SB_ERR_NULL_PUBLIC_KEY  The <tt>publicKey</tt> object is <tt>NULL</tt>.
@retval SB_SUCCESS              Success.
*/

extern 
SB_EXPORT
int
SB_CALLCONV
hu_KeyPairGen(
    sb_Params params,
    sb_PrivateKey * privateKey,
    sb_PublicKey * publicKey,
    sb_GlobalCtx sbCtx
); 

/** Creates a copy of private and public key, and parameter objects.

The new key and parameter objects will be thread-safe handles to the same
underlying key, and permit the keys to be used in multiple threads.

The <tt>dstCtx</tt> must be compatible with <tt>srcCtx</tt> which means
it should have been created by calling <tt>hu_GlobalCtxCopyCrypto()</tt> or
by other means where the result is indistinguishable from having called
<tt>hu_GlobalCtxCopyCrypto()</tt>.

The <tt>srcParams</tt> must be present, however <tt>srcPriv</tt> is
needed only when <tt>dstPriv</tt> is to be created. Similarly for
<tt>srcPub</tt> and <tt>dstPub</tt>. The <tt>dstParams</tt> must
be non-null since it always needs to be created.

The <tt>dstParams</tt> will not have the <tt>sb_RngCtx</tt> (if any)
that <tt>srcParams</tt> has because the <tt>sb_RngCtx</tt> is not
thread safe and that would make the <tt>dstParams</tt> not thread safe. If
the <tt>dstParams</tt> is required to have a <tt>sb_RngCtx</tt>, it
must be explicitly provided. Similarly for a <tt>sb_YieldCtx</tt>.

@param[in] srcCtx     The global context associated with <tt>srcParams</tt>,
                      <tt>srcPriv</tt> and <tt>srcPub</tt>.
@param[in] srcParams  The parameters object associated with <tt>srcCtx</tt>,
                      <tt>srcPriv</tt> and <tt>srcPub</tt>.
@param[in] srcPriv    The private key object associated with <tt>srcCtx</tt>,
                      <tt>srcParams</tt> and <tt>srcPub</tt>.
@param[in] srcPub     The public key object associated with <tt>srcCtx</tt>,
                      <tt>srcParams</tt> and <tt>srcPriv</tt>.
@param[in] dstCtx     The global context associated with <tt>dstParams</tt>,
                      <tt>dstPriv</tt> and <tt>dstPub</tt>.
@param[in] dstRng     The RNG context to add to <tt>dstParams</tt>.
@param[in] dstYield   The yield context to add to <tt>dstParams</tt>.
@param[out] dstParams  The parameters object pointer associated with 
                       <tt>dstCtx</tt>, <tt>dstPriv</tt> and <tt>dstPub</tt>.
@param[out] dstPriv    The private key object pointer associated with 
                       <tt>dstCtx</tt>, <tt>dstParams</tt> and <tt>dstPub</tt>.
@param[out] dstPub     The public key object pointer associated with 
                       <tt>dstCtx</tt>, <tt>dstParams</tt> and
                       <tt>dstPriv</tt>.
*/

extern 
SB_EXPORT
int
SB_CALLCONV
hu_KeyPairDuplicate(
    sb_GlobalCtx srcCtx,
    sb_Params srcParams,
    sb_PrivateKey srcPriv,
    sb_PublicKey srcPub,
    sb_GlobalCtx dstCtx,
    sb_RngCtx dstRng,
    sb_YieldCtx dstYield,
    sb_Params* dstParams,
    sb_PrivateKey* dstPriv,
    sb_PublicKey* dstPub
    );

/** Destroys a parameter object. 

Contexts and key objects must be destroyed before their corresponding
parameters object is destroyed.
 
@param[in,out] params  The parameters object.
@param[in]     sbCtx   A global context. 

@retval SB_ERR_NULL_PARAMS_PTR  The <tt>params</tt> object pointer is 
                                <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS      
@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ParamsDestroy(
    sb_Params * params,
    sb_GlobalCtx sbCtx
);


/** Destroys a public and/or private key object. 

The context for the key object(s) must be destroyed before the key object(s)
are destroyed. After the key object(s) are destroyed, the corresponding
parameters object can be destroyed.

@param[in]     params      A parameters object pointer.
@param[in,out] privateKey  The private key object pointer. 
@param[in,out] publicKey   The public key object pointer. 
@param[in]     sbCtx       A global context. 

@retval SB_ERR_NULL_PARAMS      The <tt>params</tt> object is <tt>NULL</tt>.
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
hu_KeyPairDestroy(
    sb_Params params,
    sb_PrivateKey * privateKey,
    sb_PublicKey * publicKey,
    sb_GlobalCtx sbCtx
); 

/** @} */

#ifdef __cplusplus
}
#endif

#endif
