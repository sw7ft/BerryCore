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
/* $Id: hurandom.h 44185 2012-05-29 21:13:15Z thowie $
 * $Source$
 * $Name$
 */
#ifndef HURANDOM_H
#define HURANDOM_H

/** @file */

#ifdef __cplusplus
extern "C" {
#endif

#include "sbdef.h"


/** @addtogroup hu_rng_cb RNG callbacks
 *
 * @{
 */

/** Prototype of user-provided callback function that generates random seeds
of the specified length.

This function should copy <tt>bufsize</tt> bytes of seed data into <tt>buf</tt>.
This callback should be registered during RNG context creation.

@param[in]  rsourceParam  A user-defined data pointer.
@param[in]  bufsize       The length (in bytes) of desired seed data.
@param[out] buf           The seed data buffer. This buffer will be at least
                          <tt>bufsize</tt> bytes in length.
@param[in]  sbCtx         A global context.

@retval SB_SUCCESS Indicates successful completion.
*/

typedef
int
SB_CALLBACK_CALLCONV
hu_ReseedCallbackFunc(
    void *rsourceParam,
    size_t bufsize,
    unsigned char *buf,
    sb_GlobalCtx sbCtx
);


/** Prototype of user-provided callback function that performs initialization
for a user-defined RNG context.

This function is called by <tt>hu_CustomRngCreate()</tt> to allow users to
create and initialize their own context. On completion, set <tt>*rngctx</tt>
to the context structure you allocate.

This callback should be registered during custom RNG context creation.

@param[in]  initinput  Arbitrary parameter to user-defined initialization
                       function. This is just the data that was passed in the 
                       <tt>initInput</tt> argument in 
                       <tt>hu_CustomRngCreate()</tt>.
@param[out] rngctx     User defined RNG context parameter.
@param[in]  sbCtx      SB context or memory callback data. (This may not be used
                       by the user implementation.)

@retval SB_SUCCESS Indicates successful completion.
*/

typedef
int
SB_CALLBACK_CALLCONV
hu_RngInitFunc(
    void  *initinput,
    void **rngctx,
    void *sbCtx
);


/** Prototype of user-provided callback function that generates random data.

This function is called by <tt>hu_RngGetBytes()</tt> and
<tt>hu_RngReseedGetBytes()</tt>. It will be passed the <tt>rngctx</tt> object
that was created by the <tt>hu_RngInitFunc()</tt> callback. This callback may
be passed seeding data as well. On completion, you should write
<tt>bufsize</tt> bytes of random data into <tt>buf</tt>.

This callback should be registered during custom RNG context creation.

@param[in]  rngctx     User defined RNG context.
@param[in]  seedlen    Length of <tt>seed</tt> argument, in bytes.
@param[in]  seed       Additional seed data. May be <tt>NULL</tt>.
@param[in]  bufsize    Amount of random data requested, in bytes.
@param[out]  buf       Buffer to hold requested random data.
@param[in]  sbCtx      SB context or memory callback data. (This may not be used
                       by the user implementation.)

@retval SB_SUCCESS Indicates successful completion.
*/
typedef
int
SB_CALLBACK_CALLCONV
hu_RngGetBytesFunc(
    void                *rngctx,
    size_t               seedlen,
    const unsigned char *seed,
    size_t               bufsize,
    unsigned char       *buf,
    void *sbCtx
);


/** Prototype of user-provided callback function that reseeds a user-defined
RNG context.

This function is called by <tt>hu_RngReseed()</tt>. It will be passed seeding
material that the user-defined RNG can use to reseed itself.

This callback should be registered during custom RNG context creation.

@param[in] rngctx   User defined RNG context.
@param[in] seedlen  The length (in bytes) of <tt>seed</tt> argument.
@param[in] seed     Additional seed data.
@param[in] sbCtx    SB context or memory callback data. (This may not be used by
                    the user implementation.)

@retval SB_SUCCESS Indicates successful completion.
*/
typedef
int
SB_CALLBACK_CALLCONV
hu_RngReseedFunc(
    void                *rngctx,
    size_t               seedlen,
    const unsigned char *seed,
    void *sbCtx
);


/** Prototype of user-provided callback function that cleans up a
user-defined RNG context.

This function is called by <tt>hu_CustomRngDestroy()</tt>. It will be passed
the <tt>rngctx</tt> object that was created by the <tt>hu_RngInitFunc()</tt>
callback. You should perform any cleanup and deallocation of the object.

This callback should be registered during custom RNG context creation.

@param[in,out] rngctx  User defined RNG context.
@param[in]     sbCtx   SB context or memory callback data. (This may not be used
                       by the user implementation.)

@retval SB_SUCCESS Indicates successful completion.
*/
typedef
int
SB_CALLBACK_CALLCONV
hu_RngEndFunc(
    void **rngctx,
    void *sbCtx
);


/** @} */


/** @addtogroup hu_rng_api RNG APIs
 *
 * @{
 */

/** Creates an RNG context object with optional initial seed and reseed
callback.

If a reseed callback function is provided, it will be called periodically to
obtain additional seeding data.

@param[in]  seedLen       The length (in bytes) of initial seed. (Optional)
@param[in]  seed          The initial seed value. Set to <tt>NULL</tt> if not
                          used.
@param[in]  seedFunc      A user-provided callback function. (Optional - set to 
                          <tt>NULL</tt> if not used.)
@param[in]  rsourceParam  A user-defined data that will be passed to 
                          <tt>seedFunc</tt>. (Optional - set to <tt>NULL</tt> if
                          not used.)
@param[in]  yieldCtx      A yield context. (Optional - set to <tt>NULL</tt> if 
                          not used.)
@param[out] rngCtx        An RNG context object pointer.
@param[in]  sbCtx         A global context.

@retval SB_ERR_NULL_CONTEXT_PTR The RNG context object pointer is <tt>NULL</tt>.
@retval SB_FAIL_ALLOC           Memory allocation failure.
@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RngCreate(
    size_t seedLen,
    const unsigned char *seed,
    hu_ReseedCallbackFunc* seedFunc,
    void *rsourceParam,
    sb_YieldCtx yieldCtx,
    sb_RNGCtx *rngCtx,
    sb_GlobalCtx sbCtx
);


/** Destroys an RNG context object.

@param[in,out] rngCtx  An RNG context object pointer.
@param[in]     sbCtx   A global context.

@retval SB_ERR_NULL_CONTEXT_PTR The RNG context object pointer is <tt>NULL</tt>.
@retval SB_ERR_NULL_CONTEXT     The RNG context object is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT      The RNG context is invalid.
@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RngDestroy(
    sb_RNGCtx *rngCtx,
    sb_GlobalCtx sbCtx
);

/** @} */

/** @addtogroup hu_ansi_x931_rng_api RNG APIs
 *
 * @{
 */

/** Specify AES algorithm for X9.31  */
#define HU_RNG_X931_ALG_AES 0x01

/** Specify Triple DES algorithm for X9.31  */
#define HU_RNG_X931_ALG_3DES 0x02


/** Specify AES V size for X9.31  */
#define HU_RNG_X931_ALG_AES_V_SIZE 0x10

/** Specify Triple-DES V size for X9.31  */
#define HU_RNG_X931_ALG_3DES_V_SIZE 0x08


/** Creates an ANSI X9.31 RNG context object.

Any reseeding information in calls to <tt>hu_RngReseed()</tt> or
<tt>hu_RngReseedGetBytes()</tt> will update the internal <tt>v</tt> state
but will not affect the internal symmetric key.

<em>Note</em>: You must call <tt>hu_RngANSIX931Destroy()</tt> to destroy
the context; the <tt>hu_RngDestroy()</tt> function cannot destroy an RNG 
context object created by <tt>hu_RngANSIX931Create()</tt>.

@param[in]  alg           The algorithm to use. The acceptable values are:
                          <tt>HU_RNG_X931_ALG_AES</tt> and 
                          <tt>HU_RNG_X931_ALG_3DES</tt>.
@param[in]  keyLen        The length (in bytes) of <tt>key</tt>.
                          For AES, the acceptable values are:
                          <tt>SB_AES_128_KEY_BYTES</tt>, 
                          <tt>SB_AES_192_KEY_BYTES</tt> and 
                          <tt>SB_AES_256_KEY_BYTES</tt>.
                          For DES, the acceptable value is:
                          3*<tt>SB_DES_KEY_SIZE</tt>.
@param[in]  key           The symmetric algorithm key.
@param[in]  vLen          The length (in bytes) of the initial seed 
                          (<tt>v</tt>). When <tt>alg</tt> is set to
                          <tt>HU_RNG_X931_ALG_AES</tt>, the buffer size must be 
                          16 bytes. When <tt>alg</tt> is set to 
                          <tt>HU_RNG_X931_ALG_3DES</tt>, the buffer size must 
                          be 8 bytes.
@param[in]  v             The initial seed value.
@param[in]  timeFunc      A user-provided callback function. When called, the
                          user is required to fill the buffer with the current 
                          time and date.

                          You are not required to fill the whole buffer;
                          just as much as you can. One easy solution is to 
                          call the standard <tt>time()</tt> function, which 
                          returns the number of seconds since January 1, 1970 
                          (GMT) and then place that value in the buffer. 
                          However, should you have access to a more granular 
                          time (e.g. includes ms) - and its value fits 
                          in the buffer - then that value should be placed in 
                          the buffer instead.
                          
                          When <tt>alg</tt> is set to 
                          <tt>HU_RNG_X931_ALG_AES</tt>, the buffer size will
                          always be 16 bytes. When <tt>alg</tt> is set to 
                          <tt>HU_RNG_X931_ALG_3DES</tt>, the buffer size 
                          will always be 8 bytes.
@param[in]  rsourceParam  This is user-defined data that will be passed to 
                          <tt>seedFunc</tt>. (Optional - set to <tt>NULL</tt> if
                          not used.)
@param[in]  yieldCtx      A yield context. (Optional - set to <tt>NULL</tt> if 
                          not used.)
@param[out] rngCtx        An RNG context object pointer.
@param[in]  sbCtx         A global context.

@retval SB_ERR_NULL_CONTEXT_PTR  The RNG context object pointer is <tt>NULL</tt>.
@retval SB_ERR_BAD_ALGORITHM           Unacceptable <tt>alg</tt>.
@retval SB_ERR_BAD_KEY_LEN             Unacceptable <tt>keyLen</tt>.
@retval SB_ERR_NULL_KEY                <tt>key</tt> is <tt>NULL</tt>.
@retval SB_ERR_NULL_INPUT_BUF          <tt>seed</tt> is <tt>NULL</tt>.
@retval SB_ERR_RNG_NULL_TIME_CALLBACK  <tt>timeFunc</tt> is <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN       <tt>seedLen</tt> is less than required.
@retval SB_SUCCESS                     Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RngANSIX931Create(
    int alg,
    size_t keyLen,
    const unsigned char * key,
    size_t vLen,
    const unsigned char * v,
    hu_ReseedCallbackFunc * timeFunc,
    void * rsourceParam,
    sb_YieldCtx yieldCtx,
    sb_RNGCtx *rngCtx,
    sb_GlobalCtx sbCtx
);


/** Destroys an ANSI X9.31 RNG context object.

@param[in,out] rngCtx  An RNG context object pointer.
@param[in]     sbCtx   A global context.

@retval SB_ERR_NULL_CONTEXT_PTR The RNG context object pointer is <tt>NULL</tt>.
@retval SB_ERR_NULL_CONTEXT     The RNG context object is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT      The RNG context is invalid.

@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RngANSIX931Destroy(
    sb_RNGCtx *rngCtx,
    sb_GlobalCtx sbCtx
);


/** @} */ 

/** @addtogroup hu_drbg_rng_api RNG APIs
 *
 * @{
 */

/** ID for Cipher DRBG RNG algorithm. */
#define HU_DRBG_CIPHER 0x01

/** ID for Dual-EC DRBG RNG algorithm. */
#define HU_DRBG_EC     0x02

/** ID for Hash DRBG RNG algorithm. */
#define HU_DRBG_HASH   0x03

/** ID for HMAC DRBG RNG algorithm. */
#define HU_DRBG_HMAC   0x04

/** ID for Dual-EC DRBG RNG algorithm using Certicom points. */
#define HU_DRBG_EC_CERTICOM     0x05



/** Creates an DRBG RNG context object with optional personalized String.

@param[in]  algId                     DRBG algorithm Identifier. The acceptable 
                                      values are <tt>HU_DRBG_CIPHER</tt>, 
                                      <tt>HU_DRBG_EC</tt>, <tt>HU_DRBG_EC_CERTICOM</tt>,
                                      <tt>HU_DRBG_HASH</tt>, and <tt>HU_DRBG_HMAC</tt>. 
@param[in]  securityStrength          Security strength in bits; must be less 
                                      than or equal to 256. While you can 
                                      specify any number between 0 and 256, 
                                      inclusive; internally the value will be 
                                      rounded up to the four supported 
                                      strengths: 112, 128, 192, 256.
@param[in]  predictiveResistanceFlag  Future use; set to zero.
@param[in]  personalizedStringLen     The length (in bytes) of personalized 
                                      string. (Optional - set to zero if not 
                                      used.)
@param[in]  personalizedString        The intent of the personalization string 
                                      is to differentiate this DRBG instance 
                                      from all other instantiations that might 
                                      be created. It should be set to some 
                                      bitstring as unique as possible. Examples 
                                      include: device serial number, public key,
                                      user identification, timestamps, network 
                                      address, application identifiers, 
                                      protocol version identifiers, random 
                                      number and nonce. (Optional - set to 
                                      <tt>NULL</tt> if not used.)
@param[in]  yieldCtx                  A yield context. (Optional - set to 
                                      <tt>NULL</tt> if not used.)
@param[out] rngCtx                    An RNG context object pointer.
@param[in]  sbCtx                     A global context.

@retval SB_ERR_BAD_ALG          The DRBG algorithm identifier is unknown.
@retval SB_ERR_NULL_CONTEXT_PTR The RNG context object pointer is <tt>NULL</tt>.
@retval SB_FAIL_ALLOC           Memory allocation failure.
@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RngDrbgCreate(
    int algId,
    int securityStrength,
    int predictiveResistanceFlag,
    size_t personalizedStringLen,
    const unsigned char *personalizedString,
    sb_YieldCtx yieldCtx,
    sb_RNGCtx * rngCtx,
    sb_GlobalCtx sbCtx
);


/** Destroys an DRBG RNG context object.

@param[in,out] rngCtx  An RNG context object pointer.
@param[in]     sbCtx   A global context.

@retval SB_ERR_NULL_CONTEXT_PTR The RNG context object pointer is <tt>NULL</tt>.
@retval SB_ERR_NULL_CONTEXT     The RNG context object is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT      The RNG context is invalid.
@retval SB_ERR_RNG_SECURITY_STRENGTH_TOO_SMALL The security strength is less
                                               than the minimum value of 80
                                               bits.
@retval SB_ERR_RNG_SECURITY_STRENGTH_NOT_SUPPORTED The security strength is
                                                   higher than the maximum
                                                   supported strength.
@retval SB_ERR_RNG_PREDICTIVE_RESISTANCE_NOT_SUPPORTED The predictive resistance
                                                       is not supported.
@retval SB_ERR_RNG_PERSONALIZATION_STRING_TOO_BIG The personalization string is
                                                  too long.
@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RngDrbgDestroy(
    sb_RNGCtx *rngCtx,
    sb_GlobalCtx sbCtx
);


/** @} */ 

/** @addtogroup hu_rng_custom_api Custom RNG APIs
 *
 * @{
 */

/** Initializes a random number generator (RNG) context for the user defined
RNG using user-provided callback functions and seed value.

@param[in]  initInput  Input to the supplied initialization function. This value
                       is passed to the user-defined init function.
@param[in]  init       RNG initialization callback function pointer. (Optional -
                       set to <tt>NULL</tt> if not used.)
@param[in]  end        RNG end callback function pointer. (Optional - set to 
                       <tt>NULL</tt> if not used.)
@param[in]  getbytes   RNG get bytes callback function pointer. This function 
                       pointer must be supplied.
@param[in]  reseed     RNG reseed callback function pointer. (Optional - set to 
                       <tt>NULL</tt> if not used.)
@param[in]  yieldCtx   Yield context. (Optional - set to <tt>NULL</tt> if not 
                       used.)
@param[out] rngCtx     RNG context pointer.
@param[in]  sbCtx      A global context.

@retval SB_ERR_NULL_CONTEXT_PTR  RNG context pointer is <tt>NULL</tt>.
@retval SB_FAIL_ALLOC            Memory allocation failure.
@retval SB_X                     Failure return from the callback function.
@retval SB_SUCCESS               Success.

*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_CustomRngCreate(
    void *initInput,
    hu_RngInitFunc* init,
    hu_RngEndFunc* end,
    hu_RngGetBytesFunc* getbytes,
    hu_RngReseedFunc* reseed,
    sb_YieldCtx yieldCtx,
    sb_RNGCtx *rngCtx,
    sb_GlobalCtx sbCtx
);


/** Destroys RNG context for the user defined RNG.

This function will call the registered <tt>hu_RngEndFunc()</tt> function
(if any) before the RNG context is destroyed.

@param[in,out] rngCtx  RNG context pointer.
@param[in]     sbCtx   A global context.

@retval SB_ERR_NULL_CONTEXT_PTR RNG context pointer is <tt>NULL</tt>.
@retval SB_ERR_NULL_CONTEXT     RNG context is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT      RNG context is invalid.
@retval SB_X                    Failure return from the callback function.
@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_CustomRngDestroy(
    sb_RNGCtx *rngCtx,
    sb_GlobalCtx sbCtx
);


/** @} */

/** @addtogroup hu_rng_api RNG APIs
 *
 * @{
 */

/** For ANSI and FIPS140 ANSI RNGs, this function updates the RNG context object
with the given seed data and generates random data of the specified length.
For cipher, hash, HMAC and EC DRBG RNGs, this function uses the given 'seed'
data as an additional input into the generation of random data of the specified
length.  It does not gather entropy to do a full reseed of the DRBG RNG context. 
To do a full reseed of the DRBG RNG context use <tt>hu_RngReseed()</tt>.

Reseeding the RNG context with whatever new entropy is collected is excellent
practice.

@param[in]  rngCtx   An RNG context object.
@param[in]  seedLen  The length (in bytes) of seed.
@param[in]  seed     The seed value.
@param[in]  bufSize  The length (in bytes) of random data buffer.
@param[out] buf      Random data.
@param[in]  sbCtx    A global context.

@retval SB_ERR_NULL_CONTEXT       The RNG context object is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT        The RNG context object is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF    The output buffer is <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN The length of the output buffer is invalid.
@retval SB_FAIL_RANDOM_GEN        A FIPS 140-1/2 condition failed.
@retval SB_ERR_RNG_ADDITIONAL_INPUT_TOO_BIG The <tt>seed</tt> (additional input
                                            for DRBG) is too long.
@retval SB_SUCCESS                Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RngReseedGetBytes(
    sb_RNGCtx rngCtx,
    size_t seedLen,
    const unsigned char *seed,
    size_t bufSize,
    unsigned char *buf,
    sb_GlobalCtx sbCtx
);


/** Generates random data of the specified length.

@param[in]  rngCtx   An RNG context object.
@param[in]  bufSize  The length (in bytes) of random data buffer.
@param[out] buf      Random data.
@param[in]  sbCtx    A global context.

@retval SB_ERR_NULL_CONTEXT       The RNG context object is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT        The RNG context object is invalid.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN The length of the output buffer is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF    The output buffer is <tt>NULL</tt>.
@retval SB_FAIL_RANDOM_GEN        FIPS 140-1/2 condition failed.
@retval SB_SUCCESS                Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RngGetBytes(
    sb_RNGCtx rngCtx,
    size_t bufSize,
    unsigned char *buf,
    sb_GlobalCtx sbCtx
);


/** Retrieves the RNG context state.

This function allows you to retrieve the running secret, <tt>state</tt>, which is
associated with the PRNG specification. 

This function can be useful if you want the PRNG byte stream to survive a 
reboot or a program restart. In order to restore the PRNG byte stream, you need 
to know the initial seeding values, and call this API to retrieve the value
of <tt>state</tt> before the <tt>rngCtx</tt> is destroyed. If you have these values,
then after the reboot or program restart, the seeding values and <tt>state</tt> value
can be passed to the RNG create function, which will restore the PRNG
byte stream to its state prior to the disruption.

If you use this API, you <b>must</b> ensure that the stored seed and state are kept
secret; otherwise this will reduce the overall security of your system. 
We recommend that you not use this API unless you are very familiar
with cryptographic issues.

For PRNG X.931 the running state is v.

@param[in]      rngCtx    An RNG context object pointer.
@param[in,out]  stateLen  The length (in bytes) of <tt>v</tt>.
@param[out]     state     The PRNG running secret.
@param[in]      sbCtx     A global context.

@retval SB_ERR_NULL_CONTEXT         The RNG context is <tt>NULL</tt>.
@retval SB_ERR_NULL_OUTPUT_BUF_LEN  <tt>stateLen</tt> is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT          The RNG context is invalid.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN   <tt>stateLen</tt> is not big enough.
@retval SB_SUCCESS                  Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RngGetState(
    sb_RNGCtx rngCtx,
    size_t * stateLen,
    unsigned char * state,
    sb_GlobalCtx sbCtx
);


/** For ANSI and FIPS140 ANSI RNGs, updates the RNG context object with the
given seed data.

For cipher, hash, HMAC and EC DRBG RNGs, the given 'seed' data is used as the
additional input into the reseeding function.

Reseeding the RNG context with whatever new entropy is collected is excellent
practice.

@param[in] rngCtx   An RNG context object.
@param[in] seedLen  The length (in bytes) of seed.
@param[in] seed     The seed value.
@param[in] sbCtx    A global context.

@retval SB_ERR_BAD_INPUT_BUF_LEN The length of the input buffer is invalid.
@retval SB_ERR_NULL_INPUT_BUF    The input buffer is <tt>NULL</tt>.
@retval SB_ERR_NULL_CONTEXT      The RNG context object is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT       The RNG context object is invalid.
@retval SB_ERR_RNG_ADDITIONAL_INPUT_TOO_BIG The <tt>seed</tt> (additional input
                                            in DRBG) is too long.
@retval SB_SUCCESS               Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RngReseed(
    sb_RNGCtx rngCtx,
    size_t seedLen,
    const unsigned char *seed,
    sb_GlobalCtx sbCtx
);

/** @} */

#ifdef __cplusplus
}
#endif

#endif

