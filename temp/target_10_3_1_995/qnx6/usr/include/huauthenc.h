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
/* $Id: huauthenc.h 39908 2010-02-18 20:19:44Z korr $
 * $Source$
 * $Name$
 */
#ifndef HUAUTHENC_H
#define HUAUTHENC_H

/** @file */

#include "sbdef.h"

#ifdef __cplusplus
extern "C" {
#endif

  /* Mode identifiers. */

#define SB_CCM           0x0001
#define SB_CCM_STAR      0x0002
#define SB_GCM           0x0003


#define SB_AUTHENC_128_BLOCK_BYTES 16

/** @addtogroup hu_authenc_api AUTHENC  APIs
 *
 * @{
 */

/** Creates an Authenticated Encryption key object that can later be
used for encryption and/or decryption.

@param[in]     symParams   A symmetric algorithm parameters object. AES is the 
                           only algorithm currently supported.
@param[in]     symKey      A symmetric algorithm key object. AES is the only 
                           algorithm currently supported.
@param[in]     mode        The mode of operation. The acceptable values are 
                           <tt>SB_CCM</tt>, <tt>SB_CCM_STAR</tt> and 
                           <tt>SB_GCM</tt>.
@param[in,out] authEncKey  The Authenticated Encryption key object.
@param[in]     sbCtx       A global context.


@retval SB_ERR_NULL_PARAMS    The <tt>symParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_NULL_KEY       The <tt>symParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_NULL_KEY_PTR   The <tt>authEncKey</tt> object is <tt>NULL</tt>.
@retval SB_FAIL_ALLOC         Memory allocation failure.
@retval SB_SUCCESS            Success.
*/
extern
SB_EXPORT
int
SB_CALLCONV
hu_AuthEncKeySet(
    sb_Params symParams,
    sb_Key symKey,
    int mode,
    sb_Key *authEncKey,
    sb_GlobalCtx sbCtx
);



/** Destroys an Authenticated Encryption key object.

The symmetric key object used to create the Authenticated Encryption key object 
must be destroyed after the Authenticated Encryption key object.

@param[in,out] authEncKey  The Authenticated Encryption key object pointer.
@param[in]     sbCtx       Global context.

@retval SB_ERR_NULL_KEY_PTR The <tt>authEncKey</tt> object pointer is 
                            <tt>NULL</tt>.
@retval SB_ERR_NULL_KEY     The <tt>authEncKey</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_KEY      The <tt>authEncKey</tt> object is invalid.
@retval SB_SUCCESS          Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_AuthEncKeyDestroy(
    sb_Key *authEncKey,
    sb_GlobalCtx sbCtx
);


/** Creates an Authenticated Encryption context initialized with the given 
 *  symmetric parameters and key.

The <tt>addDataLen</tt> and <tt>plaintextLen</tt> parameters are required for 
the <tt>SB_CCM</tt> and <tt>SB_CCM_STAR</tt> modes, and are optional for the 
<tt>SB_GCM</tt> mode. If those parameters are provided for the <tt>SB_GCM</tt> 
mode, then a check will be done in the <tt>hu_AuthEncEncryptEnd()</tt> and 
<tt>hu_AuthEncDecryptEnd()</tt> functions to ensure the length of plaintext and 
additional data processed matches the lengths specified in the 
<tt>hu_AuthEncBegin()</tt> function.

@param[in]  symParams     The symmetric algorithm parameters object. AES is the 
                          only algorithm currently supported.
@param[in]  authEncKey    An authenticated encryption key
@param[in]  nonceLen      The length (in bytes) of the nonce. For 
                          <tt>SB_CCM</tt> and <tt>SB_CCM_STAR</tt>, acceptable 
                          values are <tt>7</tt>, <tt>8</tt>, <tt>9</tt>, 
                          <tt>10</tt>, <tt>11</tt>, <tt>12</tt> and <tt>13</tt>.
                          For <tt>SB_GCM</tt>, <tt>nonceLen</tt> must be 
                          greater than <tt>0</tt> and the recommended value is 
                          <tt>12</tt>.
@param[in]  nonce         Nonce buffer.
@param[in]  addDataLen    The length (in bytes) of additional data that will be 
                          processed. This is optional for <tt>SB_GCM</tt>.
@param[in]  plaintextLen  The length (in bytes) of plaintext that will be 
                          processed. This is optional for <tt>SB_GCM</tt>.
@param[in]  macLen        The length of the MAC used for authentication. For 
                          <tt>SB_CCM</tt> and <tt>SB_CCM_STAR</tt>, acceptable 
                          values are <tt>4</tt>, <tt>6</tt>, <tt>8</tt>, 
                          <tt>10</tt>, <tt>12</tt>, <tt>14</tt> and <tt>16</tt>.
                          <tt>SB_CCM_STAR</tt> may also specify a 
                          <tt>macLen</tt> of <tt>0</tt> if authentication is not
                          required. For <tt>SB_GCM</tt>, <tt>macLen</tt> must be
                          greater than or equal to <tt>4</tt> and less than or 
                          equal to <tt>16</tt>. 
@param[out] authEncCtx   The Authenticated Encryption context object pointer.
@param[in]  sbCtx        Global context.

@retval SB_ERR_BAD_KEY           The <tt>authEncKey</tt> parameter is of the 
                                 wrong type.
@retval SB_ERR_BAD_INPUT_BUF_LEN The <tt>nonceLen</tt> parameter violates 
                                 acceptable values 
@retval SB_ERR_NULL_INPUT_BUF    The <tt>nonce</tt> parameter is <tt>NULL</tt>
@retval SB_ERR_BAD_LENGTH        The <tt>macLen</tt> parameter violates 
                                 acceptable values.
*/


extern
SB_EXPORT
int
SB_CALLCONV
hu_AuthEncBegin(
    sb_Params symParams,
    sb_Key authEncKey,
    size_t nonceLen,
    const unsigned char* nonce,
    size_t addDataLen,
    size_t plaintextLen,
    size_t macLen,
    sb_Context *authEncCtx,
    sb_GlobalCtx sbCtx
);




/** Authenticates any provided additional data.  
   
This function should be called for any additional data that must be 
authenticated but not encrypted. This function can be called repeatedly to 
authenticate more additional data. All additional data must be processed before 
the <tt>hu_AuthEncEncrypt()</tt> function is called.  

@param[in] authEncCtx  Authenticate encryption context object.
@param[in] addDataLen  The length (in bytes) of additional data. If the mode is 
                       <tt>SB_CCM_STAR</tt> and the <tt>macLen</tt> specified in
                       <tt>hu_authEncBegin()</tt> was 0, then 
                       <tt>addDataLen</tt> must be <tt>0</tt>.
@param[in] addData     The additional data buffer.
@param[in] sbCtx       Global context.

@retval SB_ERR_BAD_CONTEXT    The <tt>authEncCtx</tt> parameter is of the wrong
                              type.
@retval SB_ERR_BAD_LENGTH     The <tt>addDataLen</tt> parameter violates 
                              acceptable values.
@retval SB_ERR_NULL_INPUT_BUF The <tt>addData</tt> buffer is unexpectedly
                              <tt>NULL</tt>.
*/
extern
SB_EXPORT
int
SB_CALLCONV
hu_AuthEncAuthenticate(
    sb_Context authEncCtx,
    size_t addDataLen,
    const unsigned char* addData,
    sb_GlobalCtx sbCtx
);


/** Encrypts and authenticates the provided plaintext.  

The plaintext and ciphertext buffers must be the same length and they may 
overlap in memory subject to the constraints described in the API Reference 
section on overlapping buffers. This function can be called repeatedly to 
encrypt more plaintext.   

@param[in]  authEncCtx    Authenticate encryption context object.
@param[in]  plaintextLen  The length (in bytes) of plaintext.
@param[in]  plaintext     The plaintext buffer.
@param[out] ciphertext    The ciphertext buffer.
@param[in]  sbCtx         Global context.

@retval SB_ERR_BAD_CONTEXT     The <tt>authEncCtx</tt> is of the wrong type.
@retval SB_ERR_BAD_LENGTH      The <tt>plaintextLen</tt> is invalid.
@retval SB_ERR_NULL_INPUT_BUF  The <tt>plaintext</tt> buffer is <tt>NULL</tt>.
@retval SB_ERR_NULL_OUTPUT_BUF The <tt>ciphertext</tt> buffer is <tt>NULL</tt>.
*/
extern
SB_EXPORT
int
SB_CALLCONV
hu_AuthEncEncrypt(
    sb_Context authEncCtx,
    size_t plaintextLen,
    const unsigned char* plaintext,
    unsigned char* ciphertext,
    sb_GlobalCtx sbCtx    
);

/** Decrypts and authenticates the provided ciphertext.  

The plaintext and ciphertext buffers must be the same length, and may overlap
in memory subject to the constraints described in the API Reference section
on overlapping buffers. This function can be called repeatedly to encrypt 
more plaintext.   

@param[in]  authEncCtx       Authenticate encryption context object.
@param[in]  ciphertextLen    The length (in bytes) of ciphertext.
@param[in]  ciphertext       The ciphertext buffer.
@param[out] plaintext        The plaintext buffer.
@param[in]  sbCtx            Global context.

@retval SB_ERR_BAD_CONTEXT     The <tt>authEncCtx</tt> is of the wrong type.
@retval SB_ERR_BAD_LENGTH      The <tt>plaintextLen</tt> is invalid.
@retval SB_ERR_NULL_INPUT_BUF  The <tt>ciphertext</tt> buffer is <tt>NULL</tt>.
@retval SB_ERR_NULL_OUTPUT_BUF The <tt>plaintext</tt> buffer is <tt>NULL</tt>.
*/
extern
SB_EXPORT
int
SB_CALLCONV
hu_AuthEncDecrypt(
    sb_Context authEncCtx,
    size_t ciphertextLen,
    const unsigned char* ciphertext,
    unsigned char* plaintext,
    sb_GlobalCtx sbCtx
);



/** Destroys an authenticated encryption context object, and computes the MAC.

This function must be called to terminate an authenticated encryption operation.
An authenticate encryption context must be destroyed before the corresponding
symmetric key object and symmetric key parameters object are destroyed.
The MAC computed from the authentication operation will be returned in 
the supplied buffer. 

@param[in,out] authEncCtx  The AuthEnc context object pointer.
@param[in]     macLen      The length of the mac buffer in bytes. The 
                           <tt>macLen</tt> must match the value supplied in the 
                           <tt>hu_AuthEncBegin()</tt> function.
@param[out]  mac           The mac buffer.
@param[in]  sbCtx          Global context.

@retval SB_ERR_BAD_CONTEXT          The <tt>authEncCtx</tt> is of the wrong 
                                    type.
@retval SB_ERR_NULL_OUTPUT_BUF_LEN  The <tt>macLen</tt> parameter does not 
                                    match the length specified in the 
                                    <tt>hu_AuthEncBegin</tt> function.
@retval SB_ERR_NULL_OUTPUT_BUF      The <tt>mac</tt> buffer is unexpectedly 
                                    <tt>NULL</tt>.
*/
extern
SB_EXPORT
int
SB_CALLCONV
hu_AuthEncEncryptEnd(
  sb_Context *authEncCtx,
  size_t macLen,
  unsigned char* mac,
  sb_GlobalCtx sbCtx
);


/** Destroys an authenticated encryption context object, and verifies the MAC.

This function must be called to terminate an authenticated decryption operation.
An authenticate encryption context must be destroyed before the corresponding
symmetric key object and symmetric key parameters object are destroyed. The MAC 
supplied will be verified.

@param[in,out] authEncCtx  The AuthEnc context object pointer.
@param[in]     macLen      The length of the mac buffer in bytes. The 
                           <tt>macLen</tt> must match the value supplied in the 
                           <tt>hu_AuthEncBegin()</tt> function.
@param[in]  mac            The mac buffer.
@param[in]  sbCtx          Global context.

@retval SB_ERR_BAD_CONTEXT         The <tt>authEncCtx</tt> is of the wrong 
                                    type.
@retval SB_ERR_NULL_INPUT_BUF_LEN  The <tt>macLen</tt> parameter does not 
                                   match the length specified in the 
                                   <tt>hu_AuthEncBegin</tt> function.
@retval SB_ERR_NULL_INPUT_BUF      The <tt>mac</tt> buffer is unexpectedly 
                                   <tt>NULL</tt>.
@retval SB_ERR_MAC_INVALID         The value of <tt>mac</tt> is invalid
*/
extern
SB_EXPORT
int
SB_CALLCONV
hu_AuthEncDecryptEnd(
  sb_Context *authEncCtx,
  size_t macLen,
  const unsigned char* mac,
  sb_GlobalCtx sbCtx
);


/** Does an Authenticated Encryption according to the mode desired, using the 
 * given symmetric parameters, the mode and the encryption parameters.

@param[in]  symParams     A symmetric algorithm parameters object. AES is the 
                          only algorithm currently supported.
@param[in]  mode          The mode of operation. The acceptable values are 
                          <tt>SB_CCM</tt>, <tt>SB_CCM_STAR</tt> and 
                          <tt>SB_GCM</tt>.
@param[in]  authEncKey    An authenticated encryption key
@param[in]  nonceLen      The length (in bytes) of nonce. For <tt>SB_CCM</tt> 
                          and <tt>SB_CCM_STAR</tt>, acceptable values are 
                          <tt>7</tt>, <tt>8</tt>, <tt>9</tt>, <tt>10</tt>, 
                          <tt>11</tt>, <tt>12</tt> and <tt>13</tt>. For 
                          <tt>SB_GCM</tt>, <tt>nonceLen</tt> must be greater 
                          than <tt>0</tt> and the recommended value is 
                          <tt>12</tt>.
@param[in]  nonce         Nonce buffer.
@param[in]  addDataLen    The length (in bytes) of additional data that will be 
                          processed. This is optional for <tt>SB_GCM</tt>.
@param[in]  addData       The additional data buffer.
@param[in]  plaintextLen  The length (in bytes) of plaintext.
@param[in]  plaintext     The plaintext buffer.
@param[in]  macLen        The length (in bytes) of the mac buffer. The 
                          <tt>macLen</tt> must match the value supplied in the 
                          <tt>hu_AuthEncBegin()</tt> function.
@param[out] mac           The mac buffer.
@param[out] ciphertext    The ciphertext buffer.
@param[in]  sbCtx         A global context.

@retval SB_ERR_NULL_PARAMS         The <tt>aesParams</tt> object is 
                                   <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS          
@retval SB_ERR_NULL_KEY            The <tt>aesKey</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_KEY             The <tt>aesKey</tt> object is invalid.
@retval SB_ERR_BAD_MODE            <tt>aesParams</tt> uses an invalid mode of 
                                   operation.
@retval SB_ERR_NULL_INPUT_BUF      The <tt>plaintext</tt>, <tt>nonce</tt>,
                                   or <tt>addData</tt> buffer is <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN   The <tt>nonceLen</tt> is invalid.
@retval SB_ERR_BAD_LENGTH          The <tt>macLen</tt> is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF     The <tt>ciphertext</tt> buffer is 
                                   <tt>NULL</tt>.
@retval SB_FAIL_ALLOC              Memory allocation failure.
@retval SB_SUCCESS                 Success.

*/
extern
SB_EXPORT
int
SB_CALLCONV
hu_AuthEncAuthenticateEncryptMsg(
    sb_Params symParams,
    int mode,
    sb_Key authEncKey,
    size_t nonceLen,
    const unsigned char* nonce,
    size_t addDataLen,
    const unsigned char* addData,
    size_t plaintextLen,
    const unsigned char* plaintext,    
    size_t macLen,
    unsigned char* mac,
    unsigned char* ciphertext,
    sb_GlobalCtx sbCtx
    );


/** Does an Authenticated Decryption according to the mode desired, using the 
 * given symmetric parameters, the mode and the decryption parameters.

@param[in]  symParams      A symmetric algorithm parameters object. AES is the 
                           only algorithm currently supported.
@param[in]  mode           The mode of operation. The acceptable values are 
                           <tt>SB_CCM</tt>, <tt>SB_CCM_STAR</tt> and 
                           <tt>SB_GCM</tt>.
@param[in]  authEncKey     An authenticated encryption key
@param[in]  nonceLen       The length (in bytes) of nonce. For <tt>SB_CCM</tt> 
                           and <tt>SB_CCM_STAR</tt>, acceptable values are 
                           <tt>7</tt>, <tt>8</tt>, <tt>9</tt>, <tt>10</tt>, 
                           <tt>11</tt>, <tt>12</tt> and <tt>13</tt>. For 
                           <tt>SB_GCM</tt>, <tt>nonceLen</tt> must be greater 
                           than <tt>0</tt>, and the recommended value is 
                           <tt>12</tt>.
@param[in]  nonce          Nonce buffer.
@param[in]  addDataLen     The length (in bytes) of additional data that will be
                           processed. This is optional for <tt>SB_GCM</tt>.
@param[in]  addData        The additional data buffer.
@param[in]  ciphertextLen  The length (in bytes) of ciphertext.
@param[in]  ciphertext     The ciphertext buffer.
@param[in]  macLen         The length of the mac buffer in bytes. The 
                           <tt>macLen</tt> must match the value supplied in the 
                           <tt>hu_AuthEncBegin()</tt> function.
@param[in]  mac            The mac buffer.
@param[out] plaintext      The plaintext buffer.
@param[in]  sbCtx          A global context.

@retval SB_ERR_NULL_PARAMS         The <tt>aesParams</tt> object is 
                                   <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS          
@retval SB_ERR_NULL_KEY            The <tt>aesKey</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_KEY             The <tt>aesKey</tt> object is invalid.
@retval SB_ERR_BAD_MODE            <tt>aesParams</tt> uses an invalid mode of 
                                   operation.
@retval SB_ERR_NULL_INPUT_BUF      The <tt>ciphertext</tt>, <tt>nonce</tt>,
                                   or <tt>addData</tt> buffer is <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN   The <tt>nonceLen</tt> or 
                                   <tt>ciphertextLen</tt> is invalid.
@retval SB_ERR_BAD_LENGTH          The <tt>macLen</tt> is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF     The <tt>plaintext</tt> buffer is 
                                   <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN  <tt>ciphertextLen</tt> is not consistent
                                   with <tt>nonceLen</tt>.
@retval SB_ERR_MAC_INVALID         The MAC is invalid.
@retval SB_FAIL_ALLOC              Memory allocation failure.
@retval SB_SUCCESS                 Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_AuthEncAuthenticateDecryptMsg(
    sb_Params symParams,
    int mode,
    sb_Key authEncKey,
    size_t nonceLen,
    const unsigned char* nonce,
    size_t addDataLen,
    const unsigned char* addData,
    size_t ciphertextLen,
    const unsigned char* ciphertext,
    size_t macLen,
    const unsigned char* mac,
    unsigned char* plaintext,
    sb_GlobalCtx sbCtx
    );

/** @} */

#ifdef __cplusplus
}
#endif

#endif
