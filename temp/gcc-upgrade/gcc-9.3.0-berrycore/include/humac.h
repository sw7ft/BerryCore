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
/* $Id: humac.h 36652 2008-03-14 19:59:06Z jgallant $
 * $Source$
 * $Name$
 */
#ifndef HUMAC_H
#define HUMAC_H

/** @file */

#include "sbdef.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 
 *
 * Structure of algorithm identifiers is:
 *
 * | 8 | 8 |
 * +-+-+-+-+
 *   |   | 
 *   |   +-- algorithm (match symcipher algID if applicable)
 *   | 
 *   +-- MAC type (Hash, XCBC, CMAC)
 */

/* HMAC algorithm identifiers. Refer to RFC 2104 for details. */

#define HU_DIGEST_MD2      0x0001
#define HU_DIGEST_MD4      0x0002
#define HU_DIGEST_MD5      0x0003
#define HU_DIGEST_SHA1     0x0004
#define HU_DIGEST_SHA224   0x0005
#define HU_DIGEST_SHA256   0x0006
#define HU_DIGEST_SHA384   0x0007
#define HU_DIGEST_SHA512   0x0008

/* XCBC-MAC algorithm identifiers. */

/* Refer to RFC 3566 for details about AES-XCBC-MAC. */
#define HU_MAC_XCBC_AES    0x0104

/* AES CMAC algorithm identifiers. */

/* Refer to NIST Special Publication 800-38B for details about AES CMAC. */
#define HU_MAC_CMAC_AES_128 0x0204
#define HU_MAC_CMAC_AES_192 0x0209
#define HU_MAC_CMAC_AES_256 0x020a

/** @addtogroup hu_mac_api MAC APIs
 *
 * @{
 */

/** Creates a key object for the specified MAC algorithm from the given key
value.

<tt>macAlgId</tt> should be one of the algorithm identifiers defined
in this file (e.g. <tt>HU_DIGEST_SHA1</tt>, <tt>HU_MAC_XCBC_AES</tt>).

For HMAC algorithms, if <tt>keyLen</tt> is larger than the block size of
the specified hash function, the key will first be hashed and the resulting
digest will be used as the key (as described in RFC 2104). 
<tt>hu_MACKeyGet()</tt> will return this digest as the key value.

For cipher-based MAC algorithms, <tt>keyLen</tt> must be the appropriate
length for a key of the underlying cipher.

@param[in]  macAlgId  The MAC algorithm identifier.
@param[in]  keyLen    The length (in bytes) of the MAC key value.
@param[in]  key       The MAC key value.
@param[out] macKey    The MAC key object pointer.
@param[in]  sbCtx     A global context.

@retval SB_ERR_BAD_MAC_TYPE   <tt>macAlgId</tt> is unknown.
@retval SB_ERR_NULL_KEY_PTR   <tt>macKey</tt> is <tt>NULL</tt>.
@retval SB_ERR_NULL_INPUT_BUF <tt>key</tt> is <tt>NULL</tt>.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_MACKeySet(
    int macAlgId,
    size_t keyLen,
    const unsigned char *key,
    sb_Key *macKey,
    sb_GlobalCtx sbCtx
);


/** Creates a key object for the specified MAC algorithm from random data.

<tt>macAlgId</tt> should be one of the algorithm identifiers defined
in this file (e.g. <tt>HU_DIGEST_SHA1</tt>, <tt>HU_MAC_XCBC_AES</tt>).

For HMAC algorithms, the length of the generated key will be the digest
output length (the minimum recommended in RFC 2104).

For cipher-based MAC algorithms, the length of the generated key will be
the length for a key of the underlying cipher.

@param[in]  macAlgId  The MAC algorithm identifier.
@param[in]  rngCtx    An RNG context.
@param[out] macKey    The MAC key object pointer.
@param[in]  sbCtx     A global context.

@retval SB_ERR_BAD_MAC_TYPE <tt>macAlgId</tt> is unknown.
@retval SB_ERR_NULL_KEY_PTR <tt>macKey</tt> is <tt>NULL</tt>.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_MACKeyGen(
    int macAlgId,
    sb_RNGCtx rngCtx,
    sb_Key *macKey,
    sb_GlobalCtx sbCtx
);


/** Retrieves the algorithm identifier, key length and value from a MAC key
object.

If the length of the key value is known, a pointer to a buffer large
enough to hold the key value should be passed in <tt>key</tt>
and its length in <tt>keyLen</tt>. This function will copy the key
value into <tt>key</tt> and set the actual length of the key
value in <tt>keyLen</tt>.

If <tt>key</tt> is <tt>NULL</tt>, then this function will
set the correct length of the key value in <tt>keyLen</tt>.  If
<tt>key</tt> is not <tt>NULL</tt> but <tt>keyLen</tt>
is too small, this function will return an error and also will set
the correct length of the key value in <tt>keyLen</tt>.

For HMAC algorithms, the maximum value of <tt>keyLen</tt> will be the
underlying hash algorithm's block size.

For cipher-based MAC algorithms, the maximum value of <tt>keyLen</tt>
will be the length for a key of the underlying cipher.

@param[in]     macKey    The MAC key object.
@param[out]    macAlgId  The MAC algorithm identifier.
@param[in,out] keyLen    The length (in bytes) of the MAC key value.
@param[in,out] key       The key value.
@param[in]     sbCtx     A global context.

@retval SB_ERR_NULL_KEY               <tt>macKey</tt> is <tt>NULL</tt>.
@retval SB_ERR_BAD_KEY                <tt>macKey</tt> is invalid.
@retval SB_ERR_NULL_KEY_LEN           <tt>keyLen</tt> is <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN     <tt>keyLen</tt> is invalid.
@retval SB_ERR_SYM_KEY_NOT_EXPORTABLE <tt>macKey</tt> cannot be exported.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_MACKeyGet(
    sb_Key macKey,
    int *macAlgId,
    size_t *keyLen,
    unsigned char *key,
    sb_GlobalCtx sbCtx
);


/** Destroys a MAC key object.

MAC contexts must be destroyed before MAC key objects.

@param[in] macKey  The MAC key object pointer.
@param[in] sbCtx   A global context.

@retval SB_ERR_NULL_KEY_PTR The <tt>macKey</tt> object pointer is <tt>NULL</tt>.
@retval SB_ERR_NULL_KEY     The <tt>macKey</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_KEY      The <tt>macKey</tt> object is invalid.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_MACKeyDestroy(
    sb_Key *macKey,
    sb_GlobalCtx sbCtx
);


/** Creates a MAC context initialized with the given key.

@param[in]  macKey      The MAC key object.
@param[out] macContext  The MAC context object pointer.
@param[in]  sbCtx       A global context.

@retval SB_ERR_NULL_KEY         The <tt>macKey</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_KEY          The <tt>macKey</tt> object is invalid.
@retval SB_ERR_NULL_CONTEXT_PTR The <tt>macContext</tt> object pointer is 
                                <tt>NULL</tt>.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_MACBegin(
    sb_Key macKey,
    sb_Context *macContext,
    sb_GlobalCtx sbCtx
);


/** Updates the MAC context with a block of data.

This function can be called repeatedly with multiple blocks of data.

@param[in] macContext  The MAC context object.
@param[in] dataLen     The length (in bytes) of the data.
@param[in] data        The data value.
@param[in] sbCtx       A global context.

@retval SB_ERR_NULL_CONTEXT   The <tt>macContext</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT    The <tt>macContext</tt> object is invalid.
@retval SB_ERR_NULL_INPUT_BUF The <tt>data</tt> buffer is <tt>NULL</tt>.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_MACUpdate(
    sb_Context macContext,
    size_t dataLen,
    const unsigned char *data,
    sb_GlobalCtx sbCtx
);


/** Computes the MAC value without destroying or changing the state of the MAC
context.

To specify the length of the tag value, a pointer to a buffer large enough to
hold the tag value should be passed in <tt>tag</tt> and its length in
<tt>tagLen</tt>. This function will copy the first <tt>tagLen</tt>
bytes of the computed tag into <tt>tag</tt>. If <tt>tagLen</tt> is
greater than the default tag length, the entire tag value is copied, and the
default length of the tag value is set in <tt>tagLen</tt>.

If <tt>tag</tt> is <tt>NULL</tt>, then this function will set the
default length of the tag value in <tt>tagLen</tt>.  If <tt>tag</tt>
is not <tt>NULL</tt> but <tt>tagLen</tt> is too small, this function
will return an error and will also set the default length of the tag value in
<tt>tagLen</tt>.

For HMAC algorithms, the default length of the tag value is the underlying 
digest's output length. The minimum length of the tag value is half the
default length.

@param[in]     macContext  The MAC context object.
@param[in,out] tagLen      The length (in bytes) of the tag.
@param[out]    tag         The MAC output.
@param[in]     sbCtx       A global context.

@retval SB_ERR_NULL_CONTEXT            The <tt>macContext</tt> object is 
                                       <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT             The <tt>macContext</tt> object is 
                                       invalid.
@retval SB_ERR_NULL_OUTPUT_BUF_LEN_PTR The <tt>tagLen</tt> pointer is 
                                       <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN      The <tt>tagLen</tt> value is too small.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_MACTagGet(
    sb_Context macContext,
    size_t *tagLen, 
    unsigned char *tag,
    sb_GlobalCtx sbCtx
);


/** Reset a MAC context initialized with the given key.

@param[in,out] macContext  The MAC context object.
@param[in]     sbCtx       A global context.

@retval SB_ERR_NULL_CONTEXT     The <tt>macContext</tt> object is 
                                <tt>NULL</tt>.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_MACCtxReset(
    sb_Context macContext,
    sb_GlobalCtx sbCtx
);


/** Computes the MAC value and destroys the MAC context.

To specify the length of the tag value, a pointer to a buffer large enough to
hold the tag value should be passed in <tt>tag</tt> and its length in
<tt>tagLen</tt>. This function will copy the first <tt>tagLen</tt>
bytes of the computed tag into <tt>tag</tt>. If <tt>tagLen</tt> is
greater than the default tag length, the entire tag value is copied, and the
default length of the tag value is set in <tt>tagLen</tt>.

If <tt>tag</tt> is <tt>NULL</tt>, then this function will set the
default length of the tag value in <tt>tagLen</tt>.  If <tt>tag</tt>
is not <tt>NULL</tt> but <tt>tagLen</tt> is too small, this function
will return an error and will also set the default length of the tag value in
<tt>tagLen</tt>.

For HMAC algorithms, the default length of the tag value is the underlying 
digest's output length. The minimum length of the tag value is half the
default length.

For cipher-based MAC algorithms, the default length of the tag value
is the block length of the underlying cipher. The minimum length of the tag 
value is half the default length.

@param[in,out] macContext  The MAC context object pointer.
@param[in,out] tagLen      The length (in bytes) of the tag.
@param[out]    tag         The MAC output.
@param[in]     sbCtx       A global context.

@retval SB_ERR_NULL_CONTEXT_PTR        The <tt>macContext</tt> object pointer is
                                       <tt>NULL</tt>.
@retval SB_ERR_NULL_CONTEXT            The <tt>macContext</tt> object is 
                                       <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT             The <tt>macContext</tt> object is 
                                       invalid.
@retval SB_ERR_NULL_OUTPUT_BUF_LEN_PTR The <tt>tagLen</tt> pointer is 
                                       <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN      The <tt>tagLen</tt> value is too small.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_MACEnd(
    sb_Context *macContext,
    size_t *tagLen,
    unsigned char *tag,
    sb_GlobalCtx sbCtx
);


/** Computes the MAC output on the given data using the specified key.

To specify the length of the tag value, a pointer to a buffer large enough to
hold the tag value should be passed in <tt>tag</tt> and its length in
<tt>tagLen</tt>. This function will copy the first <tt>tagLen</tt>
bytes of the computed tag into <tt>tag</tt>. If <tt>tagLen</tt> is
greater than the default tag length, the entire tag value is copied, and the
default length of the tag value is set in <tt>tagLen</tt>.

If <tt>tag</tt> is <tt>NULL</tt>, then this function will set the default length
of the tag value in <tt>tagLen</tt>.  If <tt>tag</tt> is not <tt>NULL</tt> but 
<tt>tagLen</tt> is too small, this function will return an error and will also 
set the default length of the tag value in <tt>tagLen</tt>.

For HMAC algorithms, the default length of the tag value is the underlying 
digest's output length. The minimum length of the tag value is half the
default length.

For cipher-based MAC algorithms, the default length of the tag value
is the block length of the underlying cipher. The minimum length of the tag 
value is half the default length.

@param[in]     macKey   The MAC key object.
@param[in]     dataLen  The length (in bytes) of the data.
@param[in]     data     The data value.
@param[in,out] tagLen   The length (in bytes) of the tag.
@param[out]    tag      The MAC output.
@param[in]     sbCtx    A global context.

@retval SB_ERR_NULL_KEY                The <tt>macKey</tt> object is 
                                       <tt>NULL</tt>.
@retval SB_ERR_BAD_KEY                 The <tt>macKey</tt> object is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF_LEN_PTR The <tt>tagLen</tt> pointer is 
                                       <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN      The <tt>tagLen</tt> value is too small.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_MACMsg(
    sb_Key macKey,
    size_t dataLen,
    const unsigned char *data,
    size_t *tagLen,
    unsigned char *tag,
    sb_GlobalCtx sbCtx
);

/** @} */

#ifdef __cplusplus
}
#endif

#endif
