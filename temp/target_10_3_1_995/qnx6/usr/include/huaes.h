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
/* $Id: huaes.h 44187 2012-05-29 21:19:50Z thowie $
 * $Source$
 * $Name$
 */
#ifndef HUAES_H
#define HUAES_H

/** @file */

#ifdef __cplusplus
extern "C" {
#endif

#include "sbdef.h"

/** @addtogroup hu_aes_api AES APIs
 *
 * @{
 */


/** CTR mode macros */
#define SB_AES_CTR_BASE 7
#define SB_AES_CTR(ctrBits) (SB_AES_CTR_BASE | (ctrBits << 8))


/** Modes of operation */
#define SB_AES_ECB      1
#define SB_AES_CBC      2
#define SB_AES_CFB128   3
#define SB_AES_OFB128   4
#define SB_AES_KEYWRAP  5
#define SB_AES_CFB8     6
#define SB_AES_CTR8    SB_AES_CTR(8)
#define SB_AES_CTR16   SB_AES_CTR(16)
#define SB_AES_CTR32   SB_AES_CTR(32)
#define SB_AES_CTR64   SB_AES_CTR(64)
#define SB_AES_CTR128  SB_AES_CTR(128)


/** XTS mode (NIST SP 800-38A) macros */
/* unitBytes is the number of bytes in a Data Unit */
#define SB_AES_XTS_BASE 8
#define SB_AES_XTS(unitBytes) (SB_AES_XTS_BASE | (unitBytes << 8))



/** Block length */
#define SB_AES_128_BLOCK_BITS   128
#define SB_AES_128_BLOCK_BYTES  (SB_AES_128_BLOCK_BITS >> 3)

#define SB_AES_KEYWRAP_BLOCK_BITS   64
#define SB_AES_KEYWRAP_BLOCK_BYTES  (SB_AES_KEYWRAP_BLOCK_BITS >> 3)

/** Key length */
#define SB_AES_128_KEY_BITS       128
#define SB_AES_128_KEY_BYTES      (SB_AES_128_KEY_BITS >> 3)
#define SB_AES_192_KEY_BITS       192
#define SB_AES_192_KEY_BYTES      (SB_AES_192_KEY_BITS >> 3)
#define SB_AES_256_KEY_BITS       256
#define SB_AES_256_KEY_BYTES      (SB_AES_256_KEY_BITS >> 3)

#define SB_AES_128_XTS_KEY_BITS   256
#define SB_AES_128_XTS_KEY_BYTES  (SB_AES_128_XTS_KEY_BITS >> 3)
#define SB_AES_256_XTS_KEY_BITS   512
#define SB_AES_256_XTS_KEY_BYTES  (SB_AES_256_XTS_KEY_BITS >> 3)


/** Creates an AES parameters object.

The mode of operation and block length must be specified. An RNG context
and/or yielding context must be supplied if key generation and/or yielding
will be performed, respectively.

If XTS mode is used, the mode must be specified in this function in order
to have correct keys are generated or set by the key functions.

@param[in]   mode        The mode of operation. The acceptable values are 
                         <tt>SB_AES_ECB</tt>, <tt>SB_AES_CBC</tt>, 
                         <tt>SB_AES_CFB128</tt>, <tt>SB_AES_CFB8</tt>,
                         <tt>SB_AES_OFB128</tt>, <tt>SB_AES_KEYWRAP</tt>, 
                         <tt>SB_AES_CTR(ctrBits)</tt> and 
			 <tt>SB_AES_XTS(unitBytes)</tt>.
                         For <tt>SB_AES_CTR(ctrBits)</tt>, <tt>ctrBits</tt> is
                         the number of bits that will be used for the counter. 
                         <tt>ctrBits</tt> must be less than or equal to 
                         <tt>SB_AES_128_BLOCK_BITS</tt>. <tt>0</tt> is also 
                         acceptable since some adapters support 
                         <tt>hu_AESBeginV2()</tt>.
                         For <tt>SB_AES_XTS(unitBytes)</tt>, <tt>unitBytes</tt>
                         is the number of bytes in a data unit. 
                         The number of bytes in a data unit must be a multiple
                         of 16.
                         By NIST SP 800-38E, the minimum number of bytes in
                         a data unit is 16, and the maximum number of bytes
                         allowed in a data unit is 2^24 = (0x1000000).
                         Note that on platforms where <tt>int</tt> is 4
                         bytes, only up to  2^24 - 16 (=0xFFFFF0) can be
                         specified.
@param[in]   blockLen    The length (in bits) of an encryption block. If 
                         <tt>mode</tt> is <tt>SB_AES_KEYWRAP</tt>, the length 
                         must be <tt>SB_AES_KEYWRAP_BLOCK_BITS</tt>; otherwise, 
                         the length must be <tt>SB_AES_128_BLOCK_BITS</tt>.
@param[in]   rngContext  An RNG context. (Optional - set to <tt>NULL</tt> if 
                         key generation will not be performed.)
@param[in]   yieldCtx    A yield context. (Optional - set to <tt>NULL</tt> if 
                         yielding is not required.)
@param[out]  aesParams   The AES parameters object pointer.
@param[in]   sbCtx       A global context.

@retval SB_ERR_BAD_MODE        <tt>mode</tt> is an invalid mode of operation.
@retval SB_ERR_BAD_BLOCK_LEN   <tt>blockLen</tt> is an invalid block length.
@retval SB_ERR_NULL_PARAMS_PTR The <tt>aesParams</tt> object is <tt>NULL</tt>.
@retval SB_FAIL_ALLOC          Memory allocation failure.
@retval SB_SUCCESS             Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_AESParamsCreate(
    int mode,
    size_t blockLen,
    sb_RNGCtx rngContext,
    sb_YieldCtx yieldCtx,
    sb_Params *aesParams,
    sb_GlobalCtx sbCtx
);


/** Retrieves settings from an AES parameters object.

@param[in]   aesParams  The AES parameters object.
@param[out]  mode       The mode of operation.
@param[out]  blockLen   The length (in bits) of an encryption block.
@param[in]   sbCtx      A global context.

@retval SB_ERR_NULL_PARAMS     The <tt>aesParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS      
@retval SB_ERR_NULL_OUTPUT_BUF All output pointers are <tt>NULL</tt>.
@retval SB_SUCCESS             Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_AESParamsGet(
    sb_Params aesParams,
    int *mode,
    size_t *blockLen,
    sb_GlobalCtx sbCtx
);


/** Destroys an AES parameters object.

AES contexts and key objects must be destroyed before their corresponding AES
parameters object is destroyed.

@param[in,out] aesParams  The AES parameters object pointer.
@param[in]     sbCtx      A global context.

@retval SB_ERR_NULL_PARAMS_PTR The <tt>aesParams</tt> object pointer is 
                               <tt>NULL</tt>.
@retval SB_ERR_NULL_PARAMS     The <tt>aesParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS      
@retval SB_SUCCESS             Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_AESParamsDestroy(
    sb_Params *aesParams,
    sb_GlobalCtx sbCtx
);


/** Creates an AES key object from the given key value that can later be
used for encryption and/or decryption.

If the key will be used exclusively for either encryption or decryption,
then <tt>hu_AESEncryptKeySet()</tt> or <tt>hu_AESDecryptKeySet()</tt> should be
called, respectively, as they use fewer resources.

In XTS mode, two AES keys are used. Therefore, the key size for XTS mode 
is twice as large as an AES key.

@param[in]   aesParams  An AES parameters object.
@param[in]   keyLen     The length (in bits) of the AES key value. The 
                        acceptable values are <tt>SB_AES_128_KEY_BITS</tt>, 
                        <tt>SB_AES_192_KEY_BITS</tt>,
                        <tt>SB_AES_256_KEY_BITS</tt>,
                        <tt>SB_AES_128_XTS_KEY_BITS</tt> and
                        <tt>SB_AES_256_XTS_KEY_BITS</tt>.
@param[in]   keyValue   The key value.
@param[out]  aesKey     The AES key object pointer.
@param[in]   sbCtx      A global context.

@retval SB_ERR_NULL_PARAMS    The <tt>aesParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS     
@retval SB_ERR_BAD_KEY_LEN    <tt>keyLen</tt> is an invalid key length.
@retval SB_ERR_NULL_INPUT_BUF <tt>keyValue</tt> is <tt>NULL</tt>.
@retval SB_ERR_NULL_KEY_PTR   <tt>aesKey</tt> is <tt>NULL</tt>.
@retval SB_FAIL_ALLOC         Memory allocation failure.
@retval SB_SUCCESS            Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_AESKeySet(
    sb_Params aesParams,
    size_t keyLen,
    const unsigned char *keyValue,
    sb_Key *aesKey,
    sb_GlobalCtx sbCtx
);


/** Creates an AES key object from the given key value that can later be
used for encryption.

If the key will be used for both encryption and decryption, then
<tt>hu_AESKeySet()</tt> should be called instead of this function.

In XTS mode, two AES keys are used. Therefore, the key size for XTS mode 
is twice as large as an AES key.

@param[in]   aesParams  The AES parameters object.
@param[in]   keyLen     The length (in bits) of the AES key value. The 
                        acceptable values are <tt>SB_AES_128_KEY_BITS</tt>, 
                        <tt>SB_AES_192_KEY_BITS</tt>,
                        <tt>SB_AES_256_KEY_BITS</tt>,
                        <tt>SB_AES_128_XTS_KEY_BITS</tt> and
                        <tt>SB_AES_256_XTS_KEY_BITS</tt>.
@param[in]   keyValue   The key value.
@param[out]  aesKey     The AES key object pointer.
@param[in]   sbCtx      A global context.

@retval SB_ERR_NULL_PARAMS    The <tt>aesParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS     
@retval SB_ERR_BAD_KEY_LEN    <tt>keyLen</tt> is an invalid key length.
@retval SB_ERR_NULL_INPUT_BUF <tt>keyValue</tt> is <tt>NULL</tt>.
@retval SB_ERR_NULL_KEY_PTR   The <tt>aesKey</tt> object pointer is 
                              <tt>NULL</tt>.
@retval SB_FAIL_ALLOC         Memory allocation failure.
@retval SB_SUCCESS            Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_AESEncryptKeySet(
    sb_Params aesParams,
    size_t keyLen,
    const unsigned char *keyValue,
    sb_Key *aesKey,
    sb_GlobalCtx sbCtx
);


/** Creates an AES key object from the given key value that can later be
used for decryption.

If the key will be used for both encryption and decryption, then
<tt>hu_AESKeySet()</tt> should be called instead of this function.

In XTS mode, two AES keys are used. Therefore, the key size for XTS mode is 
twice as large as an AES key.

@param[in]   aesParams  The AES parameters object.
@param[in]   keyLen     The length (in bits) of the AES key value. The 
                        acceptable values are <tt>SB_AES_128_KEY_BITS</tt>, 
                        <tt>SB_AES_192_KEY_BITS</tt>,
                        <tt>SB_AES_256_KEY_BITS</tt>,
                        <tt>SB_AES_128_XTS_KEY_BITS</tt> and
                        <tt>SB_AES_256_XTS_KEY_BITS</tt>.
@param[in]   keyValue   The key value.
@param[out]  aesKey     The AES key object pointer.
@param[in]   sbCtx      A global context.

@retval SB_ERR_NULL_PARAMS    The <tt>aesParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS     
@retval SB_ERR_BAD_KEY_LEN    <tt>keyLen</tt> is an invalid key length.
@retval SB_ERR_NULL_INPUT_BUF <tt>keyValue</tt> is <tt>NULL</tt>.
@retval SB_ERR_NULL_KEY_PTR   The <tt>aesKey</tt> object pointer is 
                              <tt>NULL</tt>.
@retval SB_FAIL_ALLOC         Memory allocation failure.
@retval SB_SUCCESS            Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_AESDecryptKeySet(
    sb_Params aesParams,
    size_t keyLen,
    const unsigned char *keyValue,
    sb_Key *aesKey,
    sb_GlobalCtx sbCtx
);


/** Creates an AES key object of the specified length from random data that
can later be used for encryption and/or decryption.

The AES parameter object must have been created with an RNG context.

If the key will be used only for encryption, then you
should use <tt>hu_AESEncryptKeyGen()</tt> as it uses fewer resources.

In XTS mode, two AES keys are used. Therefore, the key size for XTS mode is 
twice as large as an AES key.

@param[in]   aesParams  The AES parameters object.
@param[in]   keyLen     The length (in bits) of the AES key value. The 
                        acceptable values are <tt>SB_AES_128_KEY_BITS</tt>, 
                        <tt>SB_AES_192_KEY_BITS</tt>,
                        <tt>SB_AES_256_KEY_BITS</tt>,
                        <tt>SB_AES_128_XTS_KEY_BITS</tt> and
                        <tt>SB_AES_256_XTS_KEY_BITS</tt>.
@param[out]  aesKey     The AES key object pointer.
@param[in]   sbCtx      A global context.

@retval SB_ERR_NULL_PARAMS  The <tt>aesParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS   
@retval SB_ERR_BAD_KEY_LEN  <tt>keyLen</tt> is an invalid key length.
@retval SB_ERR_NULL_KEY_PTR The <tt>aesKey</tt> object pointer is <tt>NULL</tt>.
@retval SB_FAIL_ALLOC       Memory allocation failure.
@retval SB_SUCCESS          Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_AESKeyGen(
    sb_Params aesParams,
    size_t keyLen,
    sb_Key *aesKey,
    sb_GlobalCtx sbCtx
);


/** Creates an AES key object of the specified length from random data that
can later be used for encryption.

If the key will be used for encryption and decryption, <tt>hu_AESKeyGen()</tt> 
should be called instead of this function.

In XTS mode, two AES keys are used. Therefore, the key size for XTS mode is 
twice as large as an AES key.

The AES parameter object must have been created with an RNG context.

@param[in]  aesParams  The AES parameters object.
@param[in]  keyLen     The length (in bits) of the AES key value. The 
                       acceptable values are <tt>SB_AES_128_KEY_BITS</tt>, 
                       <tt>SB_AES_192_KEY_BITS</tt>,
                       <tt>SB_AES_256_KEY_BITS</tt>,
                       <tt>SB_AES_128_XTS_KEY_BITS</tt> and
                       <tt>SB_AES_256_XTS_KEY_BITS</tt>.
@param[out]  aesKey    The AES key object pointer.
@param[in]  sbCtx      A global context.

@retval SB_ERR_NULL_PARAMS  The <tt>aesParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS   
@retval SB_ERR_BAD_KEY_LEN  <tt>keyLen</tt> is an invalid key length.
@retval SB_ERR_NULL_KEY_PTR The <tt>aesKey</tt> object pointer is <tt>NULL</tt>.
@retval SB_FAIL_ALLOC       Memory allocation failure.
@retval SB_SUCCESS          Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_AESEncryptKeyGen(
    sb_Params aesParams,
    size_t keyLen,
    sb_Key *aesKey,
    sb_GlobalCtx sbCtx
);


/** Retrieves the key value and its length from an AES key object.

If the length of the key value is known, a pointer to a buffer large enough
to hold the key value should be passed in <tt>keyValue</tt> and its
length in <tt>keyLen</tt>. This function will copy the key value into
<tt>keyValue</tt> and set the actual length of the key value in
<tt>keyLen</tt>.

If <tt>keyValue</tt> is <tt>NULL</tt>, then this function will set the
correct length of the key value in <tt>keyLen</tt>. If <tt>keyValue</tt> is 
not <tt>NULL</tt> but <tt>keyLen</tt> is too small, this function will return 
an error and also will set the correct length of the key value in 
<tt>keyLen</tt>.

In XTS mode, two AES keys are used. Therefore, the key size for XTS mode is 
twice as large as an AES key.

@param[in]     aesParams  The AES parameters object.
@param[in]     aesKey     The AES key object.
@param[in,out] keyLen     The length (in bits) of the AES key value.
@param[out]    keyValue   The key value.
@param[in]     sbCtx      A global context.

@retval SB_ERR_NULL_PARAMS            The <tt>aesParams</tt> object is 
                                      <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS
@retval SB_ERR_NULL_KEY               The <tt>aesKey</tt> object is 
                                      <tt>NULL</tt>.
@retval SB_ERR_BAD_KEY                The <tt>aesKey</tt> object is invalid.
@retval SB_ERR_NULL_KEY_LEN           <tt>keyLen</tt> is <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN     The <tt>keyValue</tt> buffer length is 
                                      invalid.
@retval SB_ERR_SYM_KEY_NOT_EXPORTABLE The key value cannot be exported from 
                                      the <tt>aesKey</tt> object.
@retval SB_SUCCESS                    Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_AESKeyGet(
    sb_Params aesParams,
    sb_Key aesKey,
    size_t *keyLen,
    unsigned char *keyValue,
    sb_GlobalCtx sbCtx
);


/** Destroys an AES key object.

AES contexts must be destroyed before any AES key objects. AES parameter
objects must be destroyed after AES key objects.

@param[in]     aesParams  The AES parameters object.
@param[in,out] aesKey     The AES key object pointer.
@param[in]     sbCtx      Global context.

@retval SB_ERR_NULL_PARAMS  The <tt>aesParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS
@retval SB_ERR_NULL_KEY_PTR The <tt>aesKey</tt> object pointer is <tt>NULL</tt>.
@retval SB_ERR_NULL_KEY     The <tt>aesKey</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_KEY      The <tt>aesKey</tt> object is invalid.
@retval SB_SUCCESS          Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_AESKeyDestroy(
    sb_Params aesParams,
    sb_Key *aesKey,
    sb_GlobalCtx sbCtx
);


/** Creates an AES context initialized with the given parameters and key.

An initial vector is required for the <tt>SB_AES_CBC</tt>, 
<tt>SB_AES_CFB128</tt>, <tt>SB_AES_CFB8</tt>, <tt>SB_AES_OFB128</tt> and
<tt>SB_AES_CTR(X)</tt> modes of operation. For <tt>SB_AES_CTR(ctrBits)</tt>,
<tt>iv</tt> will be used as the initial counter block, where the initial
counter value must be set in the most significant (higher index)
<tt>ctrBits/8</tt> bytes of the initial counter, and the counter value must
be represented in big-endian.
The counter is incremented by 1.

<tt>iv</tt> is ignored for <tt>SB_AES_ECB</tt>, as an initial
vector is not required for that mode.

For XTS mode, IV is used to specify the Data Unit Sequence Number and block
index within the data unit to start the operation.
The following rules apply to the value of IV for XTS mode:
<ul>
<li>The Data Unit Sequence Number is internally represented by <tt>size_t</tt>.
<li>On platforms where the size of <tt>size_t</tt> is 4 bytes, the first 4 
    bytes of IV are used to specify the Data Unit Sequence Number, and the 
    subsequent 4 bytes are ignored.
<li>On platforms where the size of <tt>size_t</tt> is 8 bytes, the first 8 
    bytes of IV are used to specify the Data Unit Sequence Number.
<li>The 9th to 11th bytes are used to specify the block index in a data unit.
<li>Block index in a data unit starts at 0.
<li>The remaining bytes in IV are ignored.
<li>The Data Unit Sequence Number and block index are represented in 
    little-endian order, where the first byte is the least significant byte.
<li>If the specified block index exceeds the size of a data unit, 
    <tt>SB_ERR_BAD_IV</tt> will be returned.
<li>IV for the specified Data Unit Sequence Number and block index can be set
    by using the <tt>hu_AESXTSIVSet()</tt> function.
</ul>

@param[in]  aesParams   The AES parameters object.
@param[in]  aesKey      The AES key object.
@param[in]  ivLen       The length (in bytes) of initial vector. The only 
                        acceptable value is <tt>SB_AES_128_BLOCK_BYTES</tt>.
@param[in]  iv          The initial vector.
@param[out] aesContext  The AES context object pointer.
@param[in]  sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS      The <tt>aesParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS       The <tt>aesParams</tt> object is invalid.
@retval SB_ERR_NULL_KEY         The <tt>aesKey</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_KEY          The <tt>aesKey</tt> object is invalid.
@retval SB_ERR_NULL_IV          <tt>iv</tt>, the initial vector, is 
                                <tt>NULL</tt>.
@retval SB_ERR_BAD_IV_LEN       <tt>ivLen</tt> is an invalid vector length.
@retval SB_ERR_NULL_CONTEXT_PTR The context object pointer is <tt>NULL</tt>.
@retval SB_ERR_NO_MODE          No mode has been specified.
@retval SB_FAIL_ALLOC           Memory allocation failure.
@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_AESBegin(
    sb_Params aesParams,
    sb_Key aesKey,
    size_t ivLen,
    const unsigned char *iv,
    sb_Context *aesContext,
    sb_GlobalCtx sbCtx
);

/** Creates an AES context initialized with the given parameters (with the
ability to override the mode in the parameters) and key.

An initial vector is required for the <tt>SB_AES_CBC</tt>, 
<tt>SB_AES_CFB128</tt>, <tt>SB_AES_CFB8</tt>,
<tt>SB_AES_OFB128</tt>, and <tt>SB_AES_CTR(ctrBits)</tt> modes of operation.
For <tt>SB_AES_CTR(ctrBits)</tt>, <tt>iv</tt> will be used as the initial
counter block, where the initial counter value must be set in the most
significant (higher index) <tt>ctrBits/8</tt> bytes of the initial counter,
and the counter value must be represented in big-endian.
The counter is incremented by 1.
<tt>iv</tt> is ignored for <tt>SB_AES_ECB</tt>, as an initial vector
is not required for that mode.

For XTS mode, IV is used to specify the Data Unit Sequence Number and block
index within the data unit to start the operation.
The following rules apply to the value of IV for XTS mode:
<ul>
<li>The Data Unit Sequence Number is internally represented by <tt>size_t</tt>.
<li>On platforms where the size of <tt>size_t</tt> is 4 bytes, the first 4 
    bytes of IV are used to specify the Data Unit Sequence Number, and the 
    subsequent 4 bytes are ignored.
<li>On the platforms where the size of <tt>size_t</tt> is 8 bytes, the first 8 
    bytes of IV are used to specify the Data Unit Sequence Number.
<li>The 9th to 11th bytes are used to specify the block index in a data unit.
<li>Block index in a data unit starts at 0.
<li>The remaining bytes in IV are ignored.
<li>The Data Unit Sequence Number and block index are represented in 
    little-endian order, where the first byte is the least significant byte.
<li>If the specified block index exceeds the size of a data unit, 
    <tt>SB_ERR_BAD_IV</tt> will be returned.
<li>IV for the specified Data Unit Sequence Number and block index can be set
    by using the <tt>hu_AESXTSIVSet()</tt> function.
</ul>

If XTS mode is used and XTS mode was not specified in the 
<tt>hu_AESParamsCreate</tt> function, <tt>SB_ERR_BAD_KEY</tt> will be returned.

@param[in]  aesParams   The AES parameters object.
@param[in]  aesKey      The AES key object.
@param[in]  mode        The mode of operation. The acceptable values are 0, 
                        <tt>SB_AES_ECB</tt>, <tt>SB_AES_CBC</tt>, 
                        <tt>SB_AES_CFB128</tt>, <tt>SB_AES_CFB8</tt>,
                        <tt>SB_AES_OFB128</tt>, <tt>SB_AES_KEYWRAP</tt>,
                        <tt>SB_AES_CTR(ctrBits)</tt> and 
			<tt>SB_AES_XTS(unitBytes)</tt>.
                        For <tt>SB_AES_CTR(ctrBits)</tt>, <tt>ctrBits</tt> is
                        the number of bits that will be used for the counter. 
                        <tt>ctrBits</tt> must be less than or equal to 
                        <tt>SB_AES_128_BLOCK_BITS</tt>. Specifying <tt>0</tt> 
                        will use the mode from the parameters object.
                        For <tt>SB_AES_XTS(unitBytes)</tt>, <tt>unitBytes</tt>
                        is the number of bytes in a data unit. 
                        The number of bytes in a data unit must be a multiple
                        of 16.
                        By NIST SP 800-38E, the minimum number of bytes in
                        a data unit is 16, and the maximum number of bytes
                        allowed in a data unit is 2^24 = (0x1000000).
                        Note that on the platforms where <tt>int</tt> is 4
                        bytes, only up to  2^24 - 16 (=0xFFFFF0) can be
                        specified.
@param[in]  ivLen       The length (in bytes) of initial vector. The only 
                        acceptable value is <tt>SB_AES_128_BLOCK_BYTES</tt>.
@param[in]  iv          The initial vector.
@param[out] aesContext  The AES context object pointer.
@param[in]  sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS      The <tt>aesParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS       The <tt>aesParams</tt> object is invalid.
@retval SB_ERR_NULL_KEY         The <tt>aesKey</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_KEY          The <tt>aesKey</tt> object is invalid.
@retval SB_ERR_NULL_IV          <tt>iv</tt>, the initial vector, is 
                                <tt>NULL</tt>.
@retval SB_ERR_BAD_IV_LEN       <tt>ivLen</tt> is an invalid vector length.
@retval SB_ERR_BAD_IV           The value <tt>iv</tt> is invalid.
@retval SB_ERR_NULL_CONTEXT_PTR The context object pointer is <tt>NULL</tt>.
@retval SB_ERR_NO_MODE          No mode has been specified.
@retval SB_FAIL_ALLOC           Memory allocation failure.
@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_AESBeginV2(
    sb_Params aesParams,
    sb_Key aesKey,
    int mode,
    size_t ivLen,
    const unsigned char *iv,
    sb_Context *aesContext,
    sb_GlobalCtx sbCtx
);


/** Encrypts one or more blocks of plaintext using the given AES context.

The plaintext and ciphertext buffers must be the same length, and may overlap
in memory subject to the constraints described in the API Reference section
on overlapping buffers. This function can be called repeatedly to encrypt 
more blocks of plaintext.

@param[in]  aesContext  AES context object.
@param[in]  length      The length (in bytes) of plaintext. 
                        For ECB, CBC and XTS modes of operation, the length
                        must be a multiple of <tt>SB_AES_128_BLOCK_BYTES</tt>.
                        For XTS mode, the data length shall not exceed the
                        data size that Data Unit Sequence Number can represent.
                        The Data Unit Sequence Number is limited to the value
                        that can be expressed in type <tt>size_t</tt>.
@param[in]  plaintext   The plaintext buffer.
@param[out] ciphertext  The ciphertext buffer.
@param[in]  sbCtx       A global context.

@retval SB_ERR_BAD_KEY           The key associated with <tt>aesContext</tt>
                                 cannot be used for encryption.
@retval SB_ERR_NULL_CONTEXT      The <tt>aesContext</tt> object is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT       The <tt>aesContext</tt> object is invalid.
@retval SB_ERR_NULL_INPUT_BUF    The plaintext buffer, <tt>plaintext</tt>, is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN <tt>length</tt>, the length of the plaintext 
                                 buffer, is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF   The ciphertext buffer is <tt>NULL</tt>.
@retval SB_SUCCESS               Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_AESEncrypt(
    sb_Context aesContext,
    size_t length,
    const unsigned char *plaintext,
    unsigned char *ciphertext,
    sb_GlobalCtx sbCtx
);


/** Decrypts one or more blocks of ciphertext using the given AES context.

The plaintext and ciphertext buffers must be the same length, and may overlap
in memory subject to the constraints described in the API Reference section
on overlapping buffers. This function can be called repeatedly to decrypt 
more blocks of ciphertext.

@param[in]  aesContext  AES context object.
@param[in]  length      The length (in bytes) of ciphertext. 
                        For ECB, CBC, and XTS modes of operation the length
                        must be a multiple of <tt>SB_AES_128_BLOCK_BYTES</tt>.
                        For XTS mode, the data length shall not exceed the
                        data size that Data Unit Sequence Number can represent.
                        The Data Unit Sequence Number is limited to the value
                        that can be expressed in type <tt>size_t</tt>.
@param[in]  ciphertext  The ciphertext buffer.
@param[out] plaintext   The plaintext buffer.
@param[in]  sbCtx       A global context.

@retval SB_ERR_BAD_KEY           The key associated with <tt>aesContext</tt>
                                 cannot be used for decryption.
@retval SB_ERR_NULL_CONTEXT      The <tt>aesContext</tt> object is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT       The <tt>aesContext</tt> object is invalid.
@retval SB_ERR_NULL_INPUT_BUF    The <tt>ciphertext</tt> buffer is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN <tt>length</tt> is an invalid ciphertext 
                                 buffer length.
@retval SB_ERR_NULL_OUTPUT_BUF   The <tt>plaintext</tt> buffer is <tt>NULL</tt>.
@retval SB_SUCCESS               Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_AESDecrypt(
    sb_Context aesContext,
    size_t length,
    const unsigned char *ciphertext,
    unsigned char *plaintext,
    sb_GlobalCtx sbCtx
);


/** Resets the given AES context so it can be reused.

For XTS mode, IV is used to specify the Data Unit Sequence Number and block
index within the data unit to start the operation.
The following rules apply to the value of IV for XTS mode:
<ul>
<li>The Data Unit Sequence Number is internally represented by <tt>size_t</tt>.
<li>On platforms where the size of <tt>size_t</tt> is 4 bytes, the first 4 
    bytes of IV are used to specify the Data Unit Sequence Number, and the 
    subsequent 4 bytes are ignored.
<li>On platforms where the size of <tt>size_t</tt> is 8 bytes, the first 8 
    bytes of IV are used to specify the Data Unit Sequence Number.
<li>The 9th to 11th bytes are used to specify the block index in a data unit.
<li>Block index in a data unit starts at 0.
<li>The remaining bytes in IV are ignored.
<li>The Data Unit Sequence Number and block index are represented in 
    little-endian order, where the first byte is the least significant byte.
<li>If the specified block index exceeds the size of a data unit, 
    <tt>SB_ERR_BAD_IV</tt> will be returned.
<li>IV for the specified Data Unit Sequence Number and block index can be set
    by using the <tt>hu_AESXTSIVSet()</tt> function.
</ul>

@param[in]   ivLen       The length (in bytes) of initial vector. The only 
                         acceptable value is <tt>SB_AES_128_BLOCK_BYTES</tt>.
@param[in]   iv          The initial vector.
@param[out]  aesContext  The AES context object.
@param[in]   sbCtx       A global context.

@retval SB_ERR_NULL_CONTEXT   The <tt>aesContext</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT    The <tt>aesContext</tt> object is invalid.
@retval SB_ERR_NULL_IV        <tt>iv</tt>, the initial vector, is <tt>NULL</tt>.
@retval SB_ERR_BAD_IV_LEN     <tt>ivLen</tt> is an invalid vector length.
@retval SB_SUCCESS            Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_AESCtxReset(
    size_t ivLen,
    const unsigned char *iv,
    sb_Context aesContext,
    sb_GlobalCtx sbCtx
);


/** Destroys an AES context object.

This function must be called to terminate an encryption or decryption
operation. An AES context must be destroyed before the corresponding AES key
object and AES parameters object are destroyed.

@param[in,out] aesContext  The AES context object pointer.
@param[in]     sbCtx       A global context.

@retval SB_ERR_NULL_CONTEXT_PTR The <tt>aesContext</tt> object pointer is 
                                <tt>NULL</tt>.
@retval SB_ERR_NULL_CONTEXT     The <tt>aesContext</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT      <tt>aesContext</tt> is invalid.
@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_AESEnd(
    sb_Context *aesContext,
    sb_GlobalCtx sbCtx
);


/** Encrypts a plaintext buffer using the given AES parameters and key.

An initial vector is required for the <tt>SB_AES_CBC</tt>, 
<tt>SB_AES_CFB128</tt>, <tt>SB_AES_CFB8</tt>, <tt>SB_AES_OFB128</tt>,
<tt>SB_AES_CTR(ctrBits)</tt> and <tt>SB_AES_XTS(unitBytes)</tt> modes of
operation.

For <tt>SB_AES_CTR(ctrBits)</tt>, <tt>iv</tt> will be used as the initial
counter block.  <tt>iv</tt> is ignored for <tt>SB_AES_ECB</tt>, as an initial
vector is not required for that mode.

For XTS mode, IV is used to specify the Data Unit Sequence Number and block
index within the data unit to start the operation.
The following rules apply to the value of IV for XTS mode:
<ul>
<li>The Data Unit Sequence Number is internally represented by <tt>size_t</tt>.
<li>On platforms where the size of <tt>size_t</tt> is 4 bytes, the first 4 
    bytes of IV are used to specify the Data Unit Sequence Number, and the 
    subsequent 4 bytes are ignored.
<li>On platforms where the size of <tt>size_t</tt> is 8 bytes, the first 8 
    bytes of IV are used to specify the Data Unit Sequence Number.
<li>The 9th to 11th bytes are used to specify the block index in a data unit.
<li>Block index in a data unit starts at 0.
<li>The remaining bytes in IV are ignored.
<li>The Data Unit Sequence Number and block index are represented in 
    little-endian order, where the first byte is the least significant byte.
<li>If the specified block index exceeds the size of a data unit, 
     <tt>SB_ERR_BAD_IV</tt> will be returned.
<li>IV for the specified Data Unit Sequence Number and block index can be set
    by using the <tt>hu_AESXTSIVSet()</tt> function.
</ul>

The plaintext and ciphertext buffers must be the same length, and may overlap
in memory subject to the constraints described in the API Reference section on
overlapping buffers.

This function should only be called for blocks of plaintext and ciphertext
that can be stored entirely in memory.

@param[in]   aesParams   The AES parameters object.
@param[in]   aesKey      The AES key object.
@param[in]   ivLen       The length (in bytes) of initial vector. The only 
                         acceptable value is <tt>SB_AES_128_BLOCK_BYTES</tt>.
@param[in]   iv          The initial vector.
@param[in]   length      The length (in bytes) of plaintext. 
                         For ECB, CBC and XTS modes of operation, the length
                         must be a multiple of <tt>SB_AES_128_BLOCK_BYTES</tt>.
                         For XTS mode, the data length shall not exceed the
                         data size that Data Unit Sequence Number can represent.
                         The Data Unit Sequence Number is limited to the value
                         that can be expressed in type <tt>size_t</tt>.
@param[in]   plaintext   The plaintext buffer.
@param[out]  ciphertext  The ciphertext buffer.
@param[in]   sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS       The <tt>aesParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS        
@retval SB_ERR_NULL_KEY          The <tt>aesKey</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_KEY           The <tt>aesKey</tt> object is invalid.
@retval SB_ERR_NULL_IV           The initial vector, <tt>iv</tt>, is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_IV_LEN        The initial vector length, <tt>ivLen</tt>, is 
                                 invalid.
@retval SB_ERR_NULL_INPUT_BUF    The <tt>plaintext</tt> buffer is <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN <tt>length</tt>, the length of the plaintext 
                                 buffer, is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF   <tt>ciphertext</tt> is <tt>NULL</tt>.
@retval SB_SUCCESS               Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_AESEncryptMsg(
    sb_Params aesParams,
    sb_Key aesKey,
    size_t ivLen,
    const unsigned char *iv,
    size_t length,
    const unsigned char *plaintext,
    unsigned char *ciphertext,
    sb_GlobalCtx sbCtx
);


/** Decrypts a ciphertext buffer using the given AES parameters and key.

An initial vector is required for the <tt>SB_AES_CBC</tt>, 
<tt>SB_AES_CFB128</tt>, <tt>SB_AES_CFB8</tt>, <tt>SB_AES_OFB128</tt>,
<tt>SB_AES_CTR(ctrBits)</tt> and <tt>SB_AES_XTS(unitBytes)</tt> modes of
operation.

For <tt>SB_AES_CTR(ctrBits)</tt>, <tt>iv</tt> will be used as the initial
counter block.

For XTS mode, IV is used to specify the Data Unit Sequence Number and block
index within the data unit to start the operation.
The following rules apply to the value of IV for XTS mode:
<ul>
<li>The Data Unit Sequence Number is internally represeted by <tt>size_t</tt>.
<li>On platforms where the size of <tt>size_t</tt> is 4 bytes, the first 4 
    bytes of IV are used to specify the Data Unit Sequence Number, and the 
    subsequent 4 bytes are ignored.
<li>On platforms where the size of <tt>size_t</tt> is 8 bytes, the first 8 
    bytes of IV are used to specify the Data Unit Sequence Number.
<li>The 9th to 11th bytes are used to specify the block index in a data unit.
<li>Block index in a data unit starts at 0.
<li>The remaining bytes in IV are ignored. 
<li>The Data Unit Sequence Number and block index are represented in 
    little-endian order, where the first byte is the least significant byte.
<li>If the specified block index exceeds the size of a data unit, 
    <tt>SB_ERR_BAD_IV</tt> will be returned.
<li>IV for the specified Data Unit Sequence Number and block index can be set
    by using the <tt>hu_AESXTSIVSet()</tt> function.
</ul>

<tt>iv</tt> is ignored for <tt>SB_AES_ECB</tt>, as an initial vector 
is not required for that mode. The plaintext and ciphertext buffers must be 
the same length, and may overlap in memory subject to the constraints 
described in the API Reference section on overlapping buffers.

This function should only be called for blocks of plaintext and ciphertext
that can be stored entirely in memory.

@param[in]  aesParams   The AES parameters object.
@param[in]  aesKey      The AES key object.
@param[in]  ivLen       The length (in bytes) of initial vector. The only 
                        acceptable value is <tt>SB_AES_128_BLOCK_BYTES</tt>.
@param[in]  iv          The initial vector.
@param[in]  length      The length (in bytes) of <tt>ciphertext</tt>.
                        For ECB, CBC and XTS modes of operation the length
                        must be a multiple of <tt>SB_AES_128_BLOCK_BYTES</tt>.
                        For XTS mode, the data length shall not exceed the
                        data size that Data Unit Sequence Number can represent.
                        The Data Unit Sequence Number is limited to the value
                        that can be expressed in type <tt>size_t</tt>.
@param[in]  ciphertext  The ciphertext buffer.
@param[out] plaintext   The plaintext buffer.
@param[in]  sbCtx       A global context.

@retval SB_ERR_NULL_PARAMS       The <tt>aesParams</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS        
@retval SB_ERR_NULL_KEY          The <tt>aesKey</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_KEY           The <tt>aesKey</tt> object is invalid.
@retval SB_ERR_NULL_IV           <tt>iv</tt>, the initial vector, is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_IV_LEN        <tt>ivLen</tt> is an invalid vector length.
@retval SB_ERR_NULL_INPUT_BUF    The <tt>ciphertext</tt> buffer is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN The ciphertext buffer length, <tt>length</tt>,
                                 is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF   The <tt>plaintext</tt> buffer is <tt>NULL</tt>.
@retval SB_SUCCESS               Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_AESDecryptMsg(
    sb_Params aesParams,
    sb_Key aesKey,
    size_t ivLen,
    const unsigned char *iv,
    size_t length,
    const unsigned char *ciphertext,
    unsigned char *plaintext,
    sb_GlobalCtx sbCtx
);


/** Wraps a plaintext buffer according to the AES Key Wrap algorithm with
the given AES parameters and key objects.

The AES parameters must have been created with <tt>SB_AES_KEYWRAP</tt>
mode. The length of the plaintext must be a multiple of 
<tt>SB_AES_KEYWRAP_BLOCK_BYTES</tt> and at least 
<tt>2 * SB_AES_KEYWRAP_BLOCK_BYTES</tt>. The length of the ciphertext will be
<tt>SB_AES_KEYWRAP_BLOCK_BYTES</tt> bytes longer than the plaintext
length. The plaintext and ciphertext buffers may overlap 
in memory subject to the constraints described in the API Reference section
on overlapping buffers.

If the length of the ciphertext is known, a pointer to a buffer large enough
to hold the ciphertext should be passed in <tt>ciphertext</tt> and its
length in <tt>ciphertextLength</tt>. This function will copy the
ciphertext value into <tt>ciphertext</tt> and set the actual length of
the ciphertext in <tt>ciphertextLength</tt>.

If <tt>ciphertext</tt> is <tt>NULL</tt>, then this function will set
the correct length of the ciphertext value in <tt>ciphertextLen</tt>. If
<tt>ciphertext</tt> is not <tt>NULL</tt> but <tt>ciphertextLen</tt>
is too small, this function will return an error and also will set the correct
length of the ciphertext value in <tt>ciphertextLen</tt>.

@param[in]     aesParams         The AES parameters object.
@param[in]     aesKey            The AES key object.
@param[in]     plaintextLength   The length (in bytes) of plaintext.
@param[in]     plaintext         Plaintext buffer.
@param[in,out] ciphertextLength  The length (in bytes) of ciphertext.
@param[out]    ciphertext        The ciphertext buffer.
@param[in]     sbCtx             A global context.

@retval SB_ERR_NULL_PARAMS         The <tt>aesParams</tt> object is 
                                   <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS          
@retval SB_ERR_NULL_KEY            The <tt>aesKey</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_KEY             The <tt>aesKey</tt> object is invalid.
@retval SB_ERR_BAD_MODE            <tt>aesParams</tt> uses an invalid mode of 
                                   operation.
@retval SB_ERR_NULL_INPUT_BUF      The <tt>plaintext</tt> buffer is 
                                   <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN   <tt>plaintextLength</tt> is incorrect.
@retval SB_ERR_NULL_OUTPUT_BUF_LEN The <tt>ciphertextLength</tt> pointer is 
                                   <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN  <tt>ciphertextLength</tt> is invalid.
@retval SB_FAIL_ALLOC              Memory allocation failure.
@retval SB_SUCCESS                 Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_AESKeyWrap(
    sb_Params aesParams,
    sb_Key aesKey,
    size_t plaintextLength,
    const unsigned char *plaintext,
    size_t *ciphertextLength,
    unsigned char *ciphertext,
    sb_GlobalCtx sbCtx
);


/** Unwraps a ciphertext buffer according to the AES Key Wrap algorithm with
the given AES parameters and key objects.

The AES parameters must have been created with <tt>SB_AES_KEYWRAP</tt> mode. 
The length of the ciphertext must be a multiple of 
<tt>SB_AES_KEYWRAP_BLOCK_BYTES</tt> and at least 
<tt>3 * SB_AES_KEYWRAP_BLOCK_BYTES</tt>. The length of the plaintext will be
<tt>SB_AES_KEYWRAP_BLOCK_BYTES</tt> bytes shorter than the ciphertext length. 
The ciphertext and plaintext buffers may overlap in memory subject to the 
constraints described in the API Reference section on overlapping buffers.

If the length of the plaintext is known, a pointer to a buffer large enough
to hold the plaintext should be passed in <tt>plaintext</tt> and its
length in <tt>plaintextLength</tt>. This function will copy the
plaintext value into <tt>plaintext</tt> and set the actual length of
the plaintext in <tt>plaintextLength</tt>.

If <tt>plaintext</tt> is <tt>NULL</tt>, then this function will set
the correct length of the plaintext value in <tt>plaintextLen</tt>. If
<tt>plaintext</tt> is not <tt>NULL</tt> but <tt>plaintextLen</tt>
is too small, this function will return an error and also will set the correct
length of the plaintext value in <tt>plaintextLen</tt>.

@param[in]     aesParams         The AES parameters object.
@param[in]     aesKey            The AES key object.
@param[in]     ciphertextLength  The length (in bytes) of ciphertext.
@param[in]     ciphertext        The ciphertext buffer.
@param[in,out] plaintextLength   The length (in bytes) of plaintext.
@param[out]    plaintext         The plaintext buffer.
@param[in]     sbCtx             A global context.

@retval SB_ERR_NULL_PARAMS         The <tt>aesParams</tt> object is 
                                   <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS          
@retval SB_ERR_NULL_KEY            The <tt>aesKey</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_KEY             The <tt>aesKey</tt> object is invalid.
@retval SB_ERR_BAD_MODE            <tt>aesParams</tt> uses an invalid mode of 
                                   operation.
@retval SB_ERR_NULL_INPUT_BUF      <tt>ciphertext</tt> is <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN   <tt>ciphertextLength</tt> is incorrect.
@retval SB_ERR_NULL_OUTPUT_BUF_LEN The <tt>plaintextLength</tt> pointer is 
                                   <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN  <tt>plaintextLength</tt> is invalid.
@retval SB_FAIL_ALLOC              Memory allocation failure.
@retval SB_SUCCESS                 Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_AESKeyUnwrap(
    sb_Params aesParams,
    sb_Key aesKey,
    size_t ciphertextLength,
    const unsigned char *ciphertext,
    size_t *plaintextLength,
    unsigned char *plaintext,
    sb_GlobalCtx sbCtx
);


/** Does an authenticated encryption according to the AES CCM* algorithm with
the given AES parameters and key objects.

CCM is described in the NIST Special Publication 800-38C and CCM* is described 
in Version 1.0 of the Zigbee Specification. CCM* is a variant of CCM that 
allows encryption without authentication. Please note that CCM* is not NIST 
certified and therefore this function should not be used if your implementation 
must comply with the NIST CCM mode of operation. 

The <tt>plaintext</tt> and <tt>ciphertext</tt> buffers may overlap in memory, 
subject to the constraints described in the API Reference section on 
overlapping buffers.

The provider registered for AES must support <tt>SB_AES_ECB</tt>
and <tt>SB_AES_CBC</tt>.

<em>Note</em>: This function should only be called for buffers of plaintext and 
ciphertext that can be stored entirely in memory.

@param[in]  aesParams     The AES parameters object.
@param[in]  aesKey        The AES key object. The key must be a valid encryption
                          key.
@param[in]  nonceLen      The length (in bytes) of nonce. Acceptable values are 
                          <tt>7</tt>, <tt>8</tt>, <tt>9</tt>, <tt>10</tt>, 
                          <tt>11</tt>, <tt>12</tt> and <tt>13</tt>.
@param[in]  nonce         Nonce buffer.
@param[in]  addDataLen    The length (in bytes) of additional data. If 
                          <tt>addDataLen</tt> is not 0, <tt>addData</tt> cannot 
                          be <tt>NULL</tt>.
@param[in]  addData       Additional data buffer. This data will be 
                          authenticated, but will not be encrypted.
@param[in]  plaintextLen  The length (in bytes) of plaintext. If 
                          <tt>plaintextLen</tt> is not 0, <tt>plaintext</tt> 
                          cannot be <tt>NULL</tt>.
@param[in]  plaintext     Plaintext buffer. This data will be authenticated and 
                          encrypted.
@param[in]  macLen        The length of the CBC-MAC used for authentication. 
                          Acceptable values are <tt>0</tt>, <tt>4</tt>, 
                          <tt>6</tt>, <tt>8</tt>, <tt>10</tt>, <tt>12</tt>, 
                          <tt>14</tt> and <tt>16</tt>. If <tt>macLen</tt> is 0, 
                          then <tt>addData</tt> and <tt>plaintext</tt> will not 
                          be authenticated.
@param[out]  ciphertext   The ciphertext buffer. The ciphertext buffer must be 
                          at least <tt>plaintextLen</tt> + <tt>macLen</tt> 
                          bytes in length.
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
hu_AESCCMStarAuthEncrypt(
    sb_Params aesParams,
    sb_Key aesKey,
    size_t nonceLen,
    const unsigned char* nonce,
    size_t addDataLen,
    const unsigned char* addData,
    size_t plaintextLen,
    const unsigned char* plaintext,    
    size_t macLen,
    unsigned char* ciphertext,
    sb_GlobalCtx sbCtx
    );


/** Does an authenticated decryption according to the AES CCM* algorithm with
the given AES parameters and key objects.

This is a variant of CCM that allows the encryption without
authentication. CCM* is not NIST certified. This function should 
not be used if your implementation must comply with the NIST
CCM mode of operation. 
CCM is described in NIST Special Publication 800-38C.
CCM* is described in the Zigbee Specification, Version 1.0.
The plaintext and ciphertext buffers may overlap 
in memory subject to the constraints described in the API Reference section
on overlapping buffers.
The adapter registered for AES must support <tt>SB_AES_ECB</tt>,
and <tt>SB_AES_CBC</tt>.
This function should only be called for buffers of plaintext and ciphertext
that can be stored entirely in memory.


@param[in]  aesParams      The AES parameters object.
@param[in]  aesKey         The AES key object. The key must be a valid 
                           encryption key.
@param[in]  nonceLen       The length (in bytes) of nonce. Acceptable values 
                           are <tt>7</tt>, <tt>8</tt>, <tt>9</tt>, <tt>10</tt>, 
                           <tt>11</tt>, <tt>12</tt> and <tt>13</tt>.
@param[in]  nonce          Nonce buffer.
@param[in]  addDataLen     The length (in bytes) of additional data. If 
                           <tt>addDataLen</tt> is not 0, then
                           <tt>addData</tt> cannot be <tt>NULL</tt>.
@param[in]  addData        Additional data buffer. This data will be 
                           authenticated, but will not be encrypted.
@param[in]  ciphertextLen  The length (in bytes) of ciphertext. If 
                           <tt>ciphertextLen</tt> is not 0, then 
                           <tt>ciphertext</tt> cannot be <tt>NULL</tt>.
@param[in]  ciphertext     Ciphertext buffer. This data will be authenticated 
                           and decrypted.
@param[in]  macLen         The length of the CBC-MAC used for authentication. 
                           Acceptable values are <tt>0</tt>, <tt>4</tt>, 
                           <tt>6</tt>, <tt>8</tt>, <tt>10</tt>, <tt>12</tt>, 
                           <tt>14</tt> and <tt>16</tt>. If <tt>macLen</tt> is 0,
                           then <tt>addData</tt> and <tt>ciphertext</tt> will 
                           not be authenticated.
@param[out] plaintext      The plaintext buffer. The plaintext buffer must be 
                           at least <tt>ciphertextLen</tt> - <tt>macLen</tt> 
                           bytes in length.
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
hu_AESCCMStarAuthDecrypt(
    sb_Params aesParams,
    sb_Key aesKey,
    size_t nonceLen,
    const unsigned char* nonce,
    size_t addDataLen,
    const unsigned char* addData,
    size_t ciphertextLen,
    const unsigned char* ciphertext,
    size_t macLen,
    unsigned char* plaintext,
    sb_GlobalCtx sbCtx
    );


/** Does an authenticated encryption according to the AES CCM algorithm with
the given AES parameters and key objects.
CCM is described in NIST Special Publication 800-38C.

The plaintext and ciphertext buffers may overlap in memory subject to the 
constraints described in the API Reference section on overlapping buffers.

The adapter registered for AES must support <tt>SB_AES_ECB</tt> and 
<tt>SB_AES_CBC</tt>.

This function should only be called for buffers of plaintext and ciphertext
that can be stored entirely in memory.


@param[in]  aesParams     The AES parameters object.
@param[in]  aesKey        The AES key object. The key must be a valid 
                          encryption key.
@param[in]  nonceLen      The length (in bytes) of nonce. Acceptable values are 
                          <tt>7</tt>, <tt>8</tt>, <tt>9</tt>, <tt>10</tt>, 
                          <tt>11</tt>, <tt>12</tt> and <tt>13</tt>.
@param[in]  nonce         Nonce buffer.
@param[in]  addDataLen    The length (in bytes) of additional data. If 
                          <tt>addDataLen</tt> is not 0, then <tt>addData</tt> 
                          cannot be <tt>NULL</tt>.
@param[in]  addData       Additional data buffer. This data will be 
                          authenticated, but will not be encrypted.
@param[in]  plaintextLen  The length (in bytes) of plaintext. If 
                          <tt>plaintextLen</tt> is not 0, then 
                          <tt>plaintext</tt> cannot be <tt>NULL</tt>.
@param[in]  plaintext     Plaintext buffer. This data will be authenticated and 
                          encrypted.
@param[in]  macLen        The length of the CBC-MAC used for authentication. 
                          Acceptable values are <tt>4</tt>, <tt>6</tt>, 
                          <tt>8</tt>, <tt>10</tt>, <tt>12</tt>, <tt>14</tt> and 
                          <tt>16</tt>.
@param[out] ciphertext    The ciphertext buffer. The ciphertext buffer must be 
                          at least <tt>plaintext</tt> + <tt>macLen</tt> bytes 
                          in length.
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
hu_AESCCMAuthEncrypt(
    sb_Params aesParams,
    sb_Key aesKey,
    size_t nonceLen,
    const unsigned char* nonce,
    size_t addDataLen,
    const unsigned char* addData,
    size_t plaintextLen,
    const unsigned char* plaintext,    
    size_t macLen,
    unsigned char* ciphertext,
    sb_GlobalCtx sbCtx
    );


/** Does an authenticated decryption according to the AES CCM algorithm with
the given AES parameters and key objects.
CCM is described in NIST Special Publication 800-38C.

The plaintext and ciphertext buffers may overlap 
in memory subject to the constraints described in the API Reference section
on overlapping buffers.
The adapter registered for AES must support <tt>SB_AES_ECB</tt>,
and <tt>SB_AES_CBC</tt>.
This function should only be called for buffers of plaintext and ciphertext
that can be stored entirely in memory.


@param[in]  aesParams      The AES parameters object.
@param[in]  aesKey         The AES key object. The key must be a valid 
                           encryption key.
@param[in]  nonceLen       The length (in bytes) of nonce. Acceptable values are
                           <tt>7</tt>, <tt>8</tt>, <tt>9</tt>, <tt>10</tt>, 
                           <tt>11</tt>, <tt>12</tt> and <tt>13</tt>.
@param[in]  nonce          Nonce buffer.
@param[in]  addDataLen     The length (in bytes) of additional data. If 
                           <tt>addDataLen</tt> is not 0, then <tt>addData</tt> 
                           cannot be <tt>NULL</tt>.
@param[in]  addData        Additional data buffer. This data will be 
                           authenticated, but will not be encrypted.
@param[in]  ciphertextLen  The length (in bytes) of ciphertext. If 
                           <tt>ciphertextLen</tt> is not 0, then 
                           <tt>ciphertext</tt> cannot be <tt>NULL</tt>.
@param[in]  ciphertext     Ciphertext buffer. This data will be authenticated 
                           and decrypted.
@param[in]  macLen         The length of the CBC-MAC used for authentication. 
                           Acceptable values are <tt>4</tt>, <tt>6</tt>, 
                           <tt>8</tt>, <tt>10</tt>, <tt>12</tt>, <tt>14</tt> and
                           <tt>16</tt>.
@param[out] plaintext      The plaintext buffer. The plaintext buffer must be 
                           at least <tt>ciphertext</tt> - <tt>macLen</tt> bytes 
                           in length.
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
@retval SB_ERR_BAD_LENGTH          The <tt>macLen</tt> is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF     The <tt>plaintext</tt> buffer is 
                                   <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN   <tt>ciphertextLen</tt> is not consistent
                                   with <tt>nonceLen</tt>.
@retval SB_ERR_MAC_INVALID         The MAC is invalid.
@retval SB_FAIL_ALLOC              Memory allocation failure.
@retval SB_SUCCESS                 Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_AESCCMAuthDecrypt(
    sb_Params aesParams,
    sb_Key aesKey,
    size_t nonceLen,
    const unsigned char* nonce,
    size_t addDataLen,
    const unsigned char* addData,
    size_t ciphertextLen,
    const unsigned char* ciphertext,
    size_t macLen,
    unsigned char* plaintext,
    sb_GlobalCtx sbCtx
    );


/** Sets the IV for XTS mode.

This function does not consider the size of a data unit.
Therefore, if the block index supplied to this function exceeds the size
of the data unit, it will be detected by the calls to <tt>hu_AESBegin()</tt>,
<tt>hu_AESBeginV2()</tt> or <tt>hu_AESCtxReset()</tt>.

Block index in a data unit starts at 0.

@param[in]  unitNo     Data Unit Sequence Number to start.
@param[in]  blockIndex Block index to start in a Data Unit.
                       The value shall not be equal to or larger than 2^20.
@param[out] ivLen      The byte length of the IV.
                       This value must be <tt>SB_AES_128_BLOCK_BYTES</tt> (=16).
@param[out] iv         The IV value.
@param[in]  sbCtx      A global context.

@retval SB_ERR_BAD_INPUT          Block index is invalid.
@retval SB_ERR_NULL_KEY_LEN       <tt>ivLen</tt> is <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN  The <tt>iv</tt> buffer length is invalid.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_AESXTSIVSet(
    size_t unitNo,
    sb_Uint32 blockIndex,
    size_t ivLen,
    unsigned char *iv,
    sb_GlobalCtx sbCtx
);

/** @} */

#ifdef __cplusplus
}
#endif

#endif
