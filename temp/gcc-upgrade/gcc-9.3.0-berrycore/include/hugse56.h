/*
 * Copyright © 1996-2012 Certicom Corp. All rights reserved.
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
/* $Id: hugse56.h 44194 2012-06-04 16:00:16Z hwang $
 * $Source$
 * $Name$
 */
#ifndef HUGSE56_H
#define HUGSE56_H

/** @file */

#ifdef __cplusplus
extern "C" {
#endif

#include "sbdef.h"

#define SBG56_STATE_INSTALLED   (0)
#define SBG56_STATE_ENABLED     (1)
#define SBG56_STATE_DISABLED    (2)


/** @addtogroup hugse56_initialization SB GSE-C 5.6 Initialization APIs

@{
*/

/** Initializes the module and performs a series of self-tests
to ensure the integrity of the module and correct operation of its
cryptographic algorithms.

Upon a successful call to this function, the state of the module
will be set to <tt>SBG56_STATE_ENABLED</tt>.

If for any reason the self-tests fail, the state of the module
will be set to <tt>SBG56_STATE_DISABLED</tt>.

This function may only be called if the state of the module is
<tt>SBG56_STATE_INSTALLED</tt>. Calling this function from any other
state will result in a <tt>SB_FAIL_LIBRARY_ALREADY_INIT</tt> error.

<em>Note</em>: This function must be called once to initialize the module 
before any cryptographic functions are called. It is not re-entrant.  

@param[in]  sbCtx  A global context.  
       
@retval SB_FAIL_KAT                  The module failed one or more known-answer 
                                     tests.
@retval SB_FAIL_INTEGRITY            The integrity test failed.
@retval SB_FAIL_LIBRARY_ALREADY_INIT The module has already been initialized.
@retval SB_FAIL_LIBRARY_DISABLED     The module is disabled and this operation 
                                     is not allowed.
@retval SB_SUCCESS                   Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_InitSbg56(
    sb_GlobalCtx sbCtx
);


/** Performs power-up self-tests required by FIPS 140-2.

Power-up self-tests by FIPS 140-2 include software integrity test and
known answer tests on FIPS Approved algorithms.

If the self-test fails for any reason, the state of the module 
will be set to <tt>SBG56_STATE_DISABLED</tt>.

The function may only be called if the module is in 
the <tt>SBG56_STATE_ENABLED</tt> state. Calling this function
from any other state will result in an error being returned.

@param[in]  sbCtx A global context.

@retval SB_FAIL_LIBRARY_DISABLED The self-tests could not be run because the 
                                 module has been disabled.
@retval SB_FAIL_LIBRARY_INTEGRITY The integrity of the module was compromised. 
                                  The module has been disabled.
@retval SB_FAIL_KAT              The module failed one or more known-answer 
                                 tests. The module has been disabled.
@retval SB_FAIL_LIBRARY_NOT_INIT The module has not been initialized.
@retval SB_FAIL_LIBRARY_DISABLED The module is disabled and this operation is 
                                 not allowed.
@retval SB_SUCCESS               Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_SelfTestSbg56(
    sb_GlobalCtx sbCtx
);


/** Uninitializes the module.

This function can be used to reset the module to the 
<tt>SBG56_STATE_INSTALLED</tt>.

The function may not be called if the module is in
the <tt>SBG56_STATE_INSTALLED</tt> state. Calling this 
function from this state will result in an error being 
returned.

Care must be used when calling this function.  If the 
module has entered the <tt>SBG56_STATE_DISABLED</tt>
state, it usually indicates a serious error. Any applications using the
module should be terminated and the module should be reinstalled.

This function is not thread safe and should not be called if any other 
threads are using the module.

@param[in]  sbCtx  A global context.

@retval SB_FAIL_LIBRARY_NOT_INIT The module is not initialized.
@retval SB_SUCCESS               Success.

*/
extern
int
SB_CALLCONV
hu_UninitSbg56(
    sb_GlobalCtx sbCtx
);


/** Retrieves the state of the module.  

Possible values for <tt>state</tt> are: 
<ul>
<li><tt>SBG56_STATE_INSTALLED</tt> - The module is installed.
It is uninitialized and cannot perform cryptographic operations.
<li><tt>SBG56_STATE_ENABLED</tt>   - The module has been initialized,
and is ready to perform cryptographic operations.
<li><tt>SBG56_STATE_DISABLED</tt>  - The module has been disabled,
and cannot perform cryptographic operations.
</ul>

@param[out] state  The state of the module.
@param[in]  sbCtx  A global context.

@retval SB_ERR_NULL_OUTPUT  The <tt>state</tt> pointer is <tt>NULL</tt>.
@retval SB_SUCCESS          Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_GetStateSbg56(
    int* state,
    sb_GlobalCtx sbCtx
);

/** @} */

/** @addtogroup hugse56_rng_cs Critical Section handler for RNG
 * @{
 */

/*
It is strongly recommended that you not share any context objects across
multiple threads or processes. However, for cases where it is absolutely
necessary to do so for the RNG context in particular, SB GSE provides a
critical section (CS) handling facility.

When the CS facility is enabled, calls to random number generation
functionality trigger a block on further access to the RNG context until the
random number generation process completes. This applies whether the calls are
explicitly to random number generation functions, e.g.,
<tt>hu_RngGetBytes()</tt>, or whether they are calls to functions that
implicitly use random number generation functionality, e.g., key and signature
generation functions.

When enabling the CS facility, you must supply callback functions that perform
the lock and unlock operations, maintaining state in the object <tt>csCtx</tt>.
*/


/** Prototype of user-provided callback function to lock a mutex object /
enter a critical section.

Any return code from this callback function will be interpreted by the calling
SB GSE function, since <tt>SB_FAIL_LOCK</tt> will <b>not</b> be returned to the 
calling application.

@param[in]  csCtx  A pointer to the critical section object, used to maintain 
                   state.

@return   <tt>0</tt> if successful, non-<tt>0</tt> if unsuccessful.
*/

typedef
int
SB_CALLCONV
hu_CSLockFuncSbg56(
    void *csCtx
);


/** Prototype of user-provided callback function to unlock a mutex object /  
leave a critical section.

Any return code from this callback function will be interpreted by the calling
SB GSE function, since <tt>SB_FAIL_LOCK</tt> and will <b>not</b> be returned to 
the calling application.

The <tt>SB_FAIL_UNLOCK</tt> return code may supersede other error codes 
triggered during the random number generation operation.

@param[in]  csCtx  A pointer to the critical section object, used to maintain 
                   state.

@return   <tt>0</tt> if successful, non-<tt>0</tt> if unsuccessful.
*/

typedef
int
SB_CALLCONV
hu_CSUnlockFuncSbg56(
    void *csCtx
);



/** Set mutex / critical section handler.

This function sets the mutex lock and unlock function pointers, as well as the
mutex object pointer (or the critical section entrance and exit function
pointers, as well as the critical section object pointer) that are to be tied
to the RNG context.  All three pointers must be supplied, unless <tt>NULL</tt>
is supplied for all three parameters (which resets the mutex / critical section
handling for the RNG context).

@param[in]  rngCtx   The RNG object pointer.
@param[in]  csCtx    The critical section object pointer.
@param[in]  csLock   The critical section lock function pointer.
@param[in]  csUnlock The critical sections unlock function pointer.
@param[in]  sbCtx    A global context.

@retval SB_FAIL_LIBRARY_NOT_INIT The module has not been initialized.
@retval SB_FAIL_LIBRARY_DISABLED The module is disabled and this operation is 
                                 not allowed.
@retval SB_ERR_NULL_CONTEX       The RNG context is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT       The RNG context is invalid.
@retval SB_ERR_NULL_INPUT        <tt>NULL</tt> is supplied to one or two of
                                 the mutex /critical section handler pointers
                                 but not to all.
@retval SB_SUCCESS               Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_SetCSRngSbg56(
    sb_RNGCtx rngCtx,
    void  *csCtx,
    hu_CSLockFuncSbg56 *csLock,
    hu_CSUnlockFuncSbg56 *csUnlock,
    sb_GlobalCtx sbCtx
);


/** Get mutex / critical section handler.

This function returns pointers to the mutex lock function, the mutex unlock
function, and/or the mutex object (or the critical section entrance function, 
the critical section exit function, and the critical section object) in the
RNG context.

@param[in]  rngCtx   The RNG object pointer.
@param[in]  csCtx    Pointer to the critical section object pointer.
@param[in]  csLock   Pointer to the critical section lock function pointer.
@param[in]  csUnlock Pointer to the critical section unlock function pointer.
@param[in]  sbCtx  A global context.

@retval SB_FAIL_LIBRARY_NOT_INIT The module has not been initialized.
@retval SB_FAIL_LIBRARY_DISABLED The module is disabled and this operation is 
                                 not allowed.
@retval SB_ERR_NULL_CONTEX       The RNG context is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT       The RNG context is invalid.
@retval SB_ERR_NULL_INPUT        All of the mutex / critical section handler
                                 pointers are <tt>NULL</tt>.
@retval SB_SUCCESS               Success.*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_GetCSRngSbg56(
    sb_RNGCtx rngCtx,
    void  **csCtx,
    hu_CSLockFuncSbg56 **csLock,
    hu_CSUnlockFuncSbg56 **csUnlock,
    sb_GlobalCtx sbCtx
);

/** @} */


/** @addtogroup hugse56_register_rng Random Number Generators
 * @{
 */

/** Enables support to create an RNG context that uses the ANSI X9.62-1998 RNG
from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_RngCreate()
  <li>hu_RngDestroy()
</ul>
$FunctionListEnd

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56ANSIRng(
    sb_GlobalCtx sbCtx
);


/** Enables support to create an RNG context that uses the NIST 800-90
DRBG compliant RNG from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_RngDrbgCreate()
  <li>hu_RngDrbgDestroy()
</ul>
$FunctionListEnd

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56DrbgHmacRng(
    sb_GlobalCtx sbCtx
);

/** Enables support to create an RNG context that uses the NIST 800-90
DRBG compliant RNG from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_RngDrbgCreate()
  <li>hu_RngDrbgDestroy()
</ul>
$FunctionListEnd

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56DrbgHashRng(
    sb_GlobalCtx sbCtx
);

/** Enables support to create an RNG context that uses the NIST 800-90
DRBG compliant RNG from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_RngDrbgCreate()
  <li>hu_RngDrbgDestroy()
</ul>
$FunctionListEnd

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56DrbgEcRng(
    sb_GlobalCtx sbCtx
);

/** Enables support to create an RNG context that uses the NIST 800-90
DRBG compliant RNG from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_RngDrbgCreate()
  <li>hu_RngDrbgDestroy()
</ul>
$FunctionListEnd

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56DrbgCipherRng(
    sb_GlobalCtx sbCtx
);

/** Enables support to create an RNG context that uses the ANSI X9.31 RNG,
supporting the AES and Triple DES cipher suites, from the
GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_RngANSIX931Create()
  <li>hu_RngANSIX931Destroy()
</ul>
$FunctionListEnd

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56ANSIX931Rng(
    sb_GlobalCtx sbCtx
);


/** Enables support to create an RNG context that uses the FIPS 140-2
compliant ANSI X9.62-1998 RNG from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_RngCreate()
  <li>hu_RngDestroy()
</ul>
$FunctionListEnd

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56FIPS140ANSIRng(
    sb_GlobalCtx sbCtx
);


/** Enables support to the function to obtain the RNG state value from the SB
software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_RngGetState()
</ul>
$FunctionListEnd

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56RngGetState(
    sb_GlobalCtx sbCtx
);

/** @} */


/** @addtogroup hugse56_register_ecc ECC
 * @{
 */

/** Enables support for ECC functions from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_ECCKeyDestroy()
  <li>hu_ECCKeyExpand()
  <li>hu_ECCKeyGen()
  <li>hu_ECCKeyGet()
  <li>hu_ECCKeySet()
  <li>hu_ECCParamsDestroy()
  <li>hu_ECCParamsGet()
  <li>hu_ECCParamsModeSet()
  <li>hu_ECDHCofacRawSharedGen()
  <li>hu_ECDHCofacSharedGen()
  <li>hu_ECDHKDFIEEESharedGen()
  <li>hu_ECDHRawSharedGen()
  <li>hu_ECDHSharedGen()
  <li>hu_ECQVPriKeyDerive()
  <li>hu_ECQVPriKeyReconstGen()
  <li>hu_ECQVPriKeyValidate()
  <li>hu_ECQVPubKeyConv()
  <li>hu_ECQVPubKeyReconstGen()
  <li>hu_ECDSANoHashSign()
  <li>hu_ECDSANoHashVerify()
  <li>hu_ECIESDecrypt()
  <li>hu_ECIESEncrypt()
  <li>hu_ECMQVRawSharedGen()
  <li>hu_ECMQVSharedGen()
  <li>hu_ECNRNoHashSign()
  <li>hu_ECNRNoHashVerify()
</ul>
$FunctionListEnd

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56ECC(
    sb_GlobalCtx sbCtx
);

/** @} */

/** @addtogroup hugse56_register_ecc_optimization ECC Curve Optimization
 * @{
 */

/** This is the generic prototype for the ECC registration functions 
 * listed below. The name of each function consists of three parts: a 
 * constant (<tt>hu_RegisterSbg56ECC</tt>), the name of the curve 
 * (<tt>Sect163k1</tt>) and the optimization level of the curve (<tt>0</tt>, 
 * <tt>1</tt>, or <tt>2</tt>). Note that only the optimization level of
 * <tt>2</tt> is available in this release.
 *
 * For example, the function <tt>hu_RegisterSbg56ECCSect163K1_2()</tt> breaks 
 * down into:
 * <ul>
 * <li>constant: <tt>hu_RegisterSbg56ECC</tt> 
 * <li>curve name: <tt>Sect163K1</tt> 
 * <li>optimization level: <tt>2</tt>
 * </ul>
 * 
 * Each of these functions enables support for the creation of a parameter 
 * object for a given curve with a given optimization level.  
 *
 * With this information you should easily be able to pick the registration
 * function you want from the list below and determine the identifier 
 * associated with it. Note that only <em>optlevel</em> of <tt>2</tt> is
 * available in this release.
 *
 * <tt>hu_RegisterSbg56ECCSect163k1_</tt><em>optlevel</em><tt>()</tt>
 * <tt>hu_RegisterSbg56ECCSect283k1_</tt><em>optlevel</em><tt>()</tt>
 * <tt>hu_RegisterSbg56ECCSecp192r1_</tt><em>optlevel</em><tt>()</tt>
 * <tt>hu_RegisterSbg56ECCSecp256r1_</tt><em>optlevel</em><tt>()</tt>
 * <tt>hu_RegisterSbg56ECCSecp384r1_</tt><em>optlevel</em><tt>()</tt>
 * <tt>hu_RegisterSbg56ECCSecp521r1_</tt><em>optlevel</em><tt>()</tt>
 *
 * Each of the above functions enable the following function to be called: 
 *
 * <ul>
 * <li>hu_ECCParamsCreate()
 * </ul>
 * @param[in]  sbCtx  A global context.
 *
 */

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56ECC_Curve_Optimization(
    sb_GlobalCtx sbCtx
);

/** @} */

/** @addtogroup hugse56_register_ecc_individual ECC Individual Functions
 * @{
 */


/** Enables support to create a parameters object for the ECC curve
    <code>sect163k1</code> with level 2 optimization from the GSE56 software
    provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_ECCParamsCreate()
</ul>
$FunctionListEnd

The identifier for this curve is <code>HU_ECC_CURVE_SECT163K1</code>.

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56ECCSect163k1_2(
    sb_GlobalCtx sbCtx
);


#define hu_RegisterSbg56ECCSect163k1 hu_RegisterSbg56ECCSect163k1_2


/** Enables support to create a parameters object for the ECC curve
    <tt>sect283k1</tt> with level 2 optimization from the GSE56 software
    provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_ECCParamsCreate()
</ul>
$FunctionListEnd

The identifier for this curve is <tt>HU_ECC_CURVE_SECT283K1</tt>.

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56ECCSect283k1_2(
    sb_GlobalCtx sbCtx
);


#define hu_RegisterSbg56ECCSect283k1 hu_RegisterSbg56ECCSect283k1_2


/** Enables support to create a parameters object for the ECC curve
    <tt>secp192r1</tt> with level 2 optimization from the GSE56 software
    provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_ECCParamsCreate()
</ul>
$FunctionListEnd

The identifier for this curve is <tt>HU_ECC_CURVE_SECP192R1</tt>.

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56ECCSecp192r1_2(
    sb_GlobalCtx sbCtx
);


#define hu_RegisterSbg56ECCSecp192r1 hu_RegisterSbg56ECCSecp192r1_2


/** Enables support to create a parameters object for the ECC curve
    <tt>secp256r1</tt> with level 2 optimization from the GSE56 software
    provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_ECCParamsCreate()
</ul>
$FunctionListEnd

The identifier for this curve is <tt>HU_ECC_CURVE_SECP256R1</tt>.

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56ECCSecp256r1_2(
    sb_GlobalCtx sbCtx
);


#define hu_RegisterSbg56ECCSecp256r1 hu_RegisterSbg56ECCSecp256r1_2


/** Enables support to create a parameters object for the ECC curve
    <tt>secp384r1</tt> with level 2 optimization from the GSE56 software
    provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_ECCParamsCreate()
</ul>
$FunctionListEnd

The identifier for this curve is <tt>HU_ECC_CURVE_SECP384R1</tt>.

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56ECCSecp384r1_2(
    sb_GlobalCtx sbCtx
);

#define hu_RegisterSbg56ECCSecp384r1 hu_RegisterSbg56ECCSecp384r1_2


/** Enables support to create a parameters object for the ECC curve
    <tt>secp521r1</tt> with level 2 optimization from the GSE56 software
    provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_ECCParamsCreate()
</ul>
$FunctionListEnd

The identifier for this curve is <tt>HU_ECC_CURVE_SECP521R1</tt>.

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56ECCSecp521r1_2(
    sb_GlobalCtx sbCtx
);

#define hu_RegisterSbg56ECCSecp521r1 hu_RegisterSbg56ECCSecp521r1_2

/** @} */

/** @addtogroup hugse56_register_idlc IDLC
 * @{
 */

/** Enables support for IDLC functions from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_IDLCDHRawSharedGen()
  <li>hu_IDLCDHSharedGen()
  <li>hu_IDLCDSANoHashSign()
  <li>hu_IDLCDSANoHashVerify()
  <li>hu_IDLCKeyDestroy()
  <li>hu_IDLCKeyGen()
  <li>hu_IDLCKeyGet()
  <li>hu_IDLCKeySet()
  <li>hu_IDLCParamsDestroy()
  <li>hu_IDLCParamsGet()
</ul>
$FunctionListEnd

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56IDLC(
    sb_GlobalCtx sbCtx
);

/** @} */


/** Enables support to generate a parameters object for IDLC with
    level 2 optimization from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_IDLCDHParamsSet()
  <li>hu_IDLCDSAParamsSet()
  <li>hu_IDLCParamsGen()
  <li>hu_IDLCParamsSet()
</ul>
$FunctionListEnd

@param[in]  sbCtx  A global context.
*/

/** @addtogroup hugse56_register_idlc_parameters IDLC Params functions
 * @{
 */

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56IDLCParamsIDLC_2(
    sb_GlobalCtx sbCtx
);


/** Enables support to generate a parameters object for IDLC according to
    FIPS 186-3 specifications with level 2 optimization from the GSE56 software
    provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_IDLCFIPSParamsGen()
  <li>hu_IDLCParamsSet()
</ul>
$FunctionListEnd

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56IDLCParamsFIPS_2(
    sb_GlobalCtx sbCtx
);


/** Enables support to generate a parameters object for IDLC according to
    ANSI X9.42 specifications with level 2 optimization from the GSE56 software
    provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_IDLCANSIParamsGen()
  <li>hu_IDLCParamsSet()
</ul>
$FunctionListEnd

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56IDLCParamsANSI_2(
    sb_GlobalCtx sbCtx
);


/** Enables support to create an IDLC parameters object for IPSec Group 1
    with level 2 optimization from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_IDLCParamsCreate()
</ul>
$FunctionListEnd

The identifier for this group is <tt>HU_IDLC_GROUP_IPSEC_1</tt>.

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56IDLCParamsIPSec1_2(
    sb_GlobalCtx sbCtx
);


/** Enables support to create an IDLC parameters object for IPSec Group 2
    with level 2 optimization from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_IDLCParamsCreate()
</ul>
$FunctionListEnd

The identifier for this group is <tt>HU_IDLC_GROUP_IPSEC_2</tt>.

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56IDLCParamsIPSec2_2(
    sb_GlobalCtx sbCtx
);


/** Enables support to create an IDLC parameters object for IPSec Group 5
    with level 2 optimization from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_IDLCParamsCreate()
</ul>
$FunctionListEnd

The identifier for this group is <tt>HU_IDLC_GROUP_IPSEC_5</tt>.

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56IDLCParamsIPSec5_2(
    sb_GlobalCtx sbCtx
);


/** Enables support to create an IDLC parameters object for IPSec Group 14
    with level 2 optimization from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_IDLCParamsCreate()
</ul>
$FunctionListEnd

The identifier for this group is <tt>HU_IDLC_GROUP_IPSEC_14</tt>.

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56IDLCParamsIPSec14_2(
    sb_GlobalCtx sbCtx
);


/** Enables support to create an IDLC parameters object for IPSec Group 15
    with level 2 optimization from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_IDLCParamsCreate()
</ul>
$FunctionListEnd

The identifier for this group is <tt>HU_IDLC_GROUP_IPSEC_15</tt>.

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56IDLCParamsIPSec15_2(
    sb_GlobalCtx sbCtx
);


/** Enables support to create an IDLC parameters object for IPSec Group 16
    with level 2 optimization from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_IDLCParamsCreate()
</ul>
$FunctionListEnd

The identifier for this group is <tt>HU_IDLC_GROUP_IPSEC_16</tt>.

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56IDLCParamsIPSec16_2(
    sb_GlobalCtx sbCtx
);


/** Enables support to create an IDLC parameters object for IPSec Group 17
    with level 2 optimization from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_IDLCParamsCreate()
</ul>
$FunctionListEnd

The identifier for this group is <tt>HU_IDLC_GROUP_IPSEC_17</tt>.

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56IDLCParamsIPSec17_2(
    sb_GlobalCtx sbCtx
);


/** Enables support to create an IDLC parameters object for IPSec Group 18
    with level 2 optimization from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_IDLCParamsCreate()
</ul>
$FunctionListEnd

The identifier for this group is <tt>HU_IDLC_GROUP_IPSEC_18</tt>.

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56IDLCParamsIPSec18_2(
    sb_GlobalCtx sbCtx
);


/** Enables support to create an IDLC parameters object for WTLS Group 1
    with level 2 optimization from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_IDLCParamsCreate()
</ul>
$FunctionListEnd

The identifier for this group is <tt>HU_IDLC_GROUP_WTLS_1</tt>.

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56IDLCParamsWTLS1_2(
    sb_GlobalCtx sbCtx
);



/** Enables support to create an IDLC parameters object for WTLS Group 2
    with level 2 optimization from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_IDLCParamsCreate()
</ul>
$FunctionListEnd

The identifier for this group is <tt>HU_IDLC_GROUP_WTLS_2</tt>.

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56IDLCParamsWTLS2_2(
    sb_GlobalCtx sbCtx
);

/** @} */


/** @addtogroup hugse56_register_rsa RSA
 * @{
 */

/** Enables support for RSA and PKCS#1 functions from the GSE56 software
    provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_RSAKeyDestroy()
  <li>hu_RSAKeyGen()
  <li>hu_RSAKeyGet()
  <li>hu_RSAKeySet()
  <li>hu_RSAPKCS1v15Dec()
  <li>hu_RSAPKCS1v15Enc()
  <li>hu_RSAPKCS1v15NoHashSign()
  <li>hu_RSAPKCS1v15NoHashVerify()
  <li>hu_RSAPKCS1v15SigPadExponent()
  <li>hu_RSAPKCS1v15VerPadExponent()
  <li>hu_RSAPKCS1v21SHA1Decrypt()
  <li>hu_RSAPKCS1v21SHA1Encrypt()
  <li>hu_RSAParamsCreate()
  <li>hu_RSAParamsDestroy()
  <li>hu_RSAParamsGet()
  <li>hu_RSAPrivateDecrypt()
  <li>hu_RSAPrivateEncrypt()
  <li>hu_RSAPSSNoHashSign()
  <li>hu_RSAPSSNoHashVerify()
  <li>hu_RSAPublicDecrypt()
  <li>hu_RSAPublicEncrypt()
  <li>hu_RSAKEMRawSecretEncrypt()
  <li>hu_RSAKEMRawSecretDecrypt()
  <li>hu_RSANSizeGet()
</ul>
$FunctionListEnd

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56RSA(
  sb_GlobalCtx sbCtx
);


/** Enables support to create a parameters object for RSA that uses blinding
from the GSE56 software provider. 

Blinding guards against timing attacks by randomizing private key
operations. <tt>hu_RegisterSbg56RSA()</tt> must be called prior to calling
this function.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_RSAParamsCreate()
</ul>
$FunctionListEnd

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56RSABlinding(
  sb_GlobalCtx sbCtx
);

/** @} */


/** @addtogroup hugse56_register_block Block Ciphers
 * @{
 */

/** Enables support for AES functions from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_AESBegin()
  <li>hu_AESBeginV2()
  <li>hu_AESCCMAuthDecrypt()
  <li>hu_AESCCMAuthEncrypt()
  <li>hu_AESCCMStarAuthDecrypt()
  <li>hu_AESCCMStarAuthEncrypt()
  <li>hu_AESDecrypt()
  <li>hu_AESDecryptKeySet()
  <li>hu_AESDecryptMsg()
  <li>hu_AESEncrypt()
  <li>hu_AESEncryptKeyGen()
  <li>hu_AESEncryptKeySet()
  <li>hu_AESEncryptMsg()
  <li>hu_AESEnd()
  <li>hu_AESKeyDestroy()
  <li>hu_AESKeyGen()
  <li>hu_AESKeyGet()
  <li>hu_AESKeySet()
  <li>hu_AESKeyUnwrap()
  <li>hu_AESKeyWrap()
  <li>hu_AESParamsCreate()
  <li>hu_AESParamsDestroy()
  <li>hu_AESParamsGet()
</ul>
$FunctionListEnd

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56AES(
    sb_GlobalCtx sbCtx
);

/** Enables support for AES-MMO from the GSE56 software provider.

You must also register support for AES from the SB software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_AESMMOBegin()
  <li>hu_AESMMOHash()
  <li>hu_AESMMODigestGet()
  <li>hu_AESMMOCtxReset()
  <li>hu_AESMMOEnd()
  <li>hu_AESMMOMsg()
</ul>
$FunctionListEnd

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56AESMMO(
    sb_GlobalCtx sbCtx
);

/** @} */

/** @addtogroup hugse56_register_authenc Authenticated Encryption Ciphers
 * @{
 */

/** Enables support for Authenticated Encryption GCM mode
    using functions from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_AuthEncKeySet()
  <li>hu_AuthEncKeyDestroy()
  <li>hu_AuthEncBegin()
  <li>hu_AuthEncAuthenticate()
  <li>hu_AuthEncEncrypt()  
  <li>hu_AuthEncDecrypt()  
  <li>hu_AuthEncEncryptEnd()
  <li>hu_AuthEncDecryptEnd()
  <li>hu_AuthEncEncryptMsg()
  <li>hu_AuthEncDecryptMsg()
</ul>
$FunctionListEnd

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56AuthEncGCM(
    sb_GlobalCtx sbCtx
);



/** Enables support for Authenticated Encryption GCM mode
    using functions from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_AuthEncKeySet()
  <li>hu_AuthEncKeyDestroy()
  <li>hu_AuthEncBegin()
  <li>hu_AuthEncAuthenticate()
  <li>hu_AuthEncEncrypt()  
  <li>hu_AuthEncDecrypt()  
  <li>hu_AuthEncEncryptEnd()
  <li>hu_AuthEncDecryptEnd()
  <li>hu_AuthEncEncryptMsg()
  <li>hu_AuthEncDecryptMsg()
</ul>
$FunctionListEnd

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56AuthEncGCM8K(
    sb_GlobalCtx sbCtx
);



/** Enables support for Authenticated Encryption CCM mode
    using functions from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_AuthEncKeySet()
  <li>hu_AuthEncKeyDestroy()
  <li>hu_AuthEncBegin()
  <li>hu_AuthEncAuthenticate()
  <li>hu_AuthEncEncrypt()  
  <li>hu_AuthEncDecrypt()  
  <li>hu_AuthEncEncryptEnd()
  <li>hu_AuthEncDecryptEnd()
  <li>hu_AuthEncEncryptMsg()
  <li>hu_AuthEncDecryptMsg()
</ul>
$FunctionListEnd

@param[in]  sbCtx  A global context.
*/
extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56AuthEncCCM(
    sb_GlobalCtx sbCtx
);

/** Enables support for Authenticated Encryption CCM* mode
    using functions from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_AuthEncKeySet()
  <li>hu_AuthEncKeyDestroy()
  <li>hu_AuthEncBegin()
  <li>hu_AuthEncAuthenticate()
  <li>hu_AuthEncEncrypt()  
  <li>hu_AuthEncDecrypt()  
  <li>hu_AuthEncEncryptEnd()
  <li>hu_AuthEncDecryptEnd()
  <li>hu_AuthEncEncryptMsg()
  <li>hu_AuthEncDecryptMsg()
</ul>
$FunctionListEnd

@param[in]  sbCtx  A global context.
*/
extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56AuthEncCCMStar(
    sb_GlobalCtx sbCtx
);


/** @} */

/** @addtogroup hugse56_register_block Block Ciphers
 * @{
 */

/** Enables support for DES functions from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_DESBegin()
  <li>hu_DESBeginV2()
  <li>hu_DESDecrypt()
  <li>hu_DESDecryptMsg()
  <li>hu_DESEncrypt()
  <li>hu_DESEncryptMsg()
  <li>hu_DESEnd()
  <li>hu_DESKeyDestroy()
  <li>hu_DESKeyGen()
  <li>hu_DESKeyGet()
  <li>hu_DESKeySet()
  <li>hu_DESParamsCreate()
  <li>hu_DESParamsDestroy()
  <li>hu_DESParamsGet()
</ul>
$FunctionListEnd

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56DES(
    sb_GlobalCtx sbCtx
);


/** Enables support for ARC2 functions from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_ARC2Begin()
  <li>hu_ARC2BeginV2()
  <li>hu_ARC2Decrypt()
  <li>hu_ARC2DecryptMsg()
  <li>hu_ARC2Encrypt()
  <li>hu_ARC2EncryptMsg()
  <li>hu_ARC2End()
  <li>hu_ARC2KeyDestroy()
  <li>hu_ARC2KeyGen()
  <li>hu_ARC2KeyGet()
  <li>hu_ARC2KeySet()
  <li>hu_ARC2ParamsCreate()
  <li>hu_ARC2ParamsDestroy()
  <li>hu_ARC2ParamsGet()
</ul>
$FunctionListEnd

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56ARC2(
    sb_GlobalCtx sbCtx
);

/** @} */


/** @addtogroup hugse56_register_stream Stream Ciphers
 * @{
 */

/** Enables support for ARC4 functions from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_ARC4Begin()
  <li>hu_ARC4Decrypt()
  <li>hu_ARC4DecryptMsg()
  <li>hu_ARC4Encrypt()
  <li>hu_ARC4EncryptMsg()
  <li>hu_ARC4End()
  <li>hu_ARC4KeyDestroy()
  <li>hu_ARC4KeyGen()
  <li>hu_ARC4KeyGet()
  <li>hu_ARC4KeySet()
  <li>hu_ARC4ParamsCreate()
  <li>hu_ARC4ParamsDestroy()
</ul>
$FunctionListEnd

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56ARC4(
    sb_GlobalCtx sbCtx
);

/** @} */


/** @addtogroup hugse56_register_hash Hash
 * @{
 */

/** Enables support for SHA-1 functions from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_SHA1Begin()
  <li>hu_SHA1CtxDuplicate()
  <li>hu_SHA1CtxReset()
  <li>hu_SHA1DigestGet()
  <li>hu_SHA1End()
  <li>hu_SHA1Hash()
  <li>hu_SHA1Msg()
</ul>
$FunctionListEnd

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56SHA1(
    sb_GlobalCtx sbCtx
);


/** Enables support for SHA-224 functions from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_SHA224Begin()
  <li>hu_SHA224CtxDuplicate()
  <li>hu_SHA224CtxReset()
  <li>hu_SHA224DigestGet()
  <li>hu_SHA224End()
  <li>hu_SHA224Hash()
  <li>hu_SHA224Msg()
</ul>
$FunctionListEnd

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56SHA224(
    sb_GlobalCtx sbCtx
);


/** Enables support for SHA-256 functions from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_SHA256Begin()
  <li>hu_SHA256CtxDuplicate()
  <li>hu_SHA256CtxReset()
  <li>hu_SHA256DigestGet()
  <li>hu_SHA256End()
  <li>hu_SHA256Hash()
  <li>hu_SHA256Msg()
</ul>
$FunctionListEnd

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56SHA256(
    sb_GlobalCtx sbCtx
);


/** Enables support for SHA-384 functions from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_SHA384Begin()
  <li>hu_SHA384CtxDuplicate()
  <li>hu_SHA384CtxReset()
  <li>hu_SHA384DigestGet()
  <li>hu_SHA384End()
  <li>hu_SHA384Hash()
  <li>hu_SHA384Msg()
</ul>
$FunctionListEnd

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56SHA384(
    sb_GlobalCtx sbCtx
);


/** Enables support for SHA-512 functions from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_SHA512Begin()
  <li>hu_SHA512CtxDuplicate()
  <li>hu_SHA512CtxReset()
  <li>hu_SHA512DigestGet()
  <li>hu_SHA512End()
  <li>hu_SHA512Hash()
  <li>hu_SHA512Msg()
</ul>
$FunctionListEnd

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56SHA512(
    sb_GlobalCtx sbCtx
);


/** Enables support for MD2 functions from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_MD2Begin()
  <li>hu_MD2CtxDuplicate()
  <li>hu_MD2CtxReset()
  <li>hu_MD2DigestGet()
  <li>hu_MD2End()
  <li>hu_MD2Hash()
  <li>hu_MD2Msg()
</ul>
$FunctionListEnd

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56MD2(
    sb_GlobalCtx sbCtx
);


/** Enables support for MD4 functions from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_MD4Begin()
  <li>hu_MD4CtxDuplicate()
  <li>hu_MD4CtxReset()
  <li>hu_MD4DigestGet()
  <li>hu_MD4End()
  <li>hu_MD4Hash()
  <li>hu_MD4Msg()
</ul>
$FunctionListEnd

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56MD4(
    sb_GlobalCtx sbCtx
);


/** Enables support for MD5 functions from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_MD5Begin()
  <li>hu_MD5CtxDuplicate()
  <li>hu_MD5CtxReset()
  <li>hu_MD5DigestGet()
  <li>hu_MD5End()
  <li>hu_MD5Hash()
  <li>hu_MD5Msg()
</ul>
$FunctionListEnd

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56MD5(
    sb_GlobalCtx sbCtx
);

/** @} */


/** @addtogroup hugse56_register_hmac HMAC
 * @{
 */

/** Enables support for HMAC-SHA-1 functions from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_HMACSHA1Begin()
  <li>hu_HMACSHA1End()
  <li>hu_HMACSHA1Hash()
  <li>hu_HMACSHA1Msg()
  <li>hu_MACBegin()
  <li>hu_MACEnd()
  <li>hu_MACKeyDestroy()
  <li>hu_MACKeyGen()
  <li>hu_MACKeyGet()
  <li>hu_MACKeySet()
  <li>hu_MACMsg()
  <li>hu_MACUpdate()
</ul>
$FunctionListEnd

The MAC identifier for this algorithm is <tt>HU_DIGEST_SHA1</tt>.

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56HMACSHA1(
    sb_GlobalCtx sbCtx
);


/** Enables support for HMAC-SHA-224 functions from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_HMACSHA224Begin()
  <li>hu_HMACSHA224End()
  <li>hu_HMACSHA224Hash()
  <li>hu_HMACSHA224Msg()
  <li>hu_MACBegin()
  <li>hu_MACEnd()
  <li>hu_MACKeyDestroy()
  <li>hu_MACKeyGen()
  <li>hu_MACKeyGet()
  <li>hu_MACKeySet()
  <li>hu_MACMsg()
  <li>hu_MACUpdate()
</ul>
$FunctionListEnd

The MAC identifier for this algorithm is <tt>HU_DIGEST_SHA224</tt>.

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56HMACSHA224(
    sb_GlobalCtx sbCtx
);


/** Enables support for HMAC-SHA-256 functions from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_HMACSHA256Begin()
  <li>hu_HMACSHA256End()
  <li>hu_HMACSHA256Hash()
  <li>hu_HMACSHA256Msg()
  <li>hu_MACBegin()
  <li>hu_MACEnd()
  <li>hu_MACKeyDestroy()
  <li>hu_MACKeyGen()
  <li>hu_MACKeyGet()
  <li>hu_MACKeySet()
  <li>hu_MACMsg()
  <li>hu_MACUpdate()
</ul>
$FunctionListEnd

The MAC identifier for this algorithm is <tt>HU_DIGEST_SHA256</tt>.

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56HMACSHA256(
    sb_GlobalCtx sbCtx
);


/** Enables support for HMAC-SHA-384 functions from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_HMACSHA384Begin()
  <li>hu_HMACSHA384End()
  <li>hu_HMACSHA384Hash()
  <li>hu_HMACSHA384Msg()
  <li>hu_MACBegin()
  <li>hu_MACEnd()
  <li>hu_MACKeyDestroy()
  <li>hu_MACKeyGen()
  <li>hu_MACKeyGet()
  <li>hu_MACKeySet()
  <li>hu_MACMsg()
  <li>hu_MACUpdate()
</ul>
$FunctionListEnd

The MAC identifier for this algorithm is <tt>HU_DIGEST_SHA384</tt>.

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56HMACSHA384(
    sb_GlobalCtx sbCtx
);


/** Enables support for HMAC-SHA-512 functions from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_HMACSHA512Begin()
  <li>hu_HMACSHA512End()
  <li>hu_HMACSHA512Hash()
  <li>hu_HMACSHA512Msg()
  <li>hu_MACBegin()
  <li>hu_MACEnd()
  <li>hu_MACKeyDestroy()
  <li>hu_MACKeyGen()
  <li>hu_MACKeyGet()
  <li>hu_MACKeySet()
  <li>hu_MACMsg()
  <li>hu_MACUpdate()
</ul>
$FunctionListEnd

The MAC identifier for this algorithm is <tt>HU_DIGEST_SHA512</tt>.

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56HMACSHA512(
    sb_GlobalCtx sbCtx
);


/** Enables support for HMAC-MD5 functions from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_HMACMD5Begin()
  <li>hu_HMACMD5End()
  <li>hu_HMACMD5Hash()
  <li>hu_HMACMD5Msg()
  <li>hu_MACBegin()
  <li>hu_MACEnd()
  <li>hu_MACKeyDestroy()
  <li>hu_MACKeyGen()
  <li>hu_MACKeyGet()
  <li>hu_MACKeySet()
  <li>hu_MACMsg()
  <li>hu_MACUpdate()
</ul>
$FunctionListEnd

The MAC identifier for this algorithm is <tt>HU_DIGEST_MD5</tt>.

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56HMACMD5(
    sb_GlobalCtx sbCtx
);


/** Enables support for AES-XCBC-MAC from the GSE56 software provider.

You must also register support for AES from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_MACBegin()
  <li>hu_MACEnd()
  <li>hu_MACKeyDestroy()
  <li>hu_MACKeyGen()
  <li>hu_MACKeyGet()
  <li>hu_MACKeySet()
  <li>hu_MACMsg()
  <li>hu_MACUpdate()
</ul>
$FunctionListEnd

The MAC identifier for this algorithm is <tt>HU_MAC_XCBC_AES</tt>.

@param[in]  sbCtx  A global context.
*/
extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56AESXCBCMAC(
    sb_GlobalCtx sbCtx
);

/** Enables support for AES-CMAC from the GSE56 software provider.

You must also register support for AES from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_MACBegin()
  <li>hu_MACEnd()
  <li>hu_MACKeyDestroy()
  <li>hu_MACKeyGen()
  <li>hu_MACKeyGet()
  <li>hu_MACKeySet()
  <li>hu_MACMsg()
  <li>hu_MACUpdate()
</ul>
$FunctionListEnd

The MAC identifier for this algorithm is <code>HU_MAC_CMAC_AES_128</code>,
<code>HU_MAC_CMAC_AES_192</code>, and <code>HU_MAC_CMAC_AES_256</code>.

@param[in]  sbCtx  A global context.
*/
extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56AESCMAC(
    sb_GlobalCtx sbCtx
);

/** @} */

/** @addtogroup hugse56_register_kdf KDF
 * @{
 */

/** Enables support for all KDFs from the SB software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_KDFDerive()
</ul>
$FunctionListEnd

The identifier for a particular KDF algorithm is defined in 
<code>hukdf.h</code>.

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56KdfDerive(
    sb_GlobalCtx sbCtx
);

/** Enables support for all PKCS#5 v1 and v2 and PKCS#12 password-based KDFs
from the GSE56 software provider.  

This function enables password-based encryption schemes supported by other
Security Builder toolkits such as GSE56 PKI-C.

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56PbeKdf(
    sb_GlobalCtx sbCtx
);

/** @} */


/** @addtogroup hugse56_register_eccalc Elliptic Curve Calculator
 * @{
 */

/** Enables support for EC Calculator functions from the SB software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_ECCalcOrderIntSet()
  <li>hu_ECCalcECPointSet()
  <li>hu_ECCalcOrderIntGet()
  <li>hu_ECCalcECPointGet()
  <li>hu_ECCalcOrderIntDestroy()
  <li>hu_ECCalcECPointDestroy()
  <li>hu_ECCalcIntMult()
  <li>hu_ECCalcLinMult()
  <li>hu_ECCalcAdd()
  <li>hu_ECCalcNeg()
</ul>
$FunctionListEnd

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56ECCalc(
    sb_GlobalCtx sbCtx
);

/** @} */



/** @addtogroup hugse56_register_ks Key Split
 * @{
 */

/** Enables support for Key Split functions from the GSE56 software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_KSBegin()
  <li>hu_KSGetShare()
  <li>hu_KSGetSecret()
  <li>hu_KSEnd()
</ul>
$FunctionListEnd

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56Ks(
    sb_GlobalCtx sbCtx
);

/** @} */


/** @addtogroup hugse56_register_zmodcalcexpo ZModCalcExpo
 * @{
 */

/** Enables support for ZModCalcExpo function from the SB software provider.

This function enables the following function(s) to be called:
$FunctionListBegin
<ul>
  <li>hu_ZModCalcExpo()
</ul>
$FunctionListEnd

@param[in]  sbCtx  A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56ZModCalcExpo(
    sb_GlobalCtx sbCtx
);

/** @} */


/** @addtogroup hugse56_register_all All
 * @{
 */

/** Enables support for all algorithms from the GSE56 software provider (but for algorithms available in multiple variations, only one is enabled).

This function calls the following functions:
$FunctionListBegin
<ul>
  <li>hu_RegisterSbg56AES()
  <li>hu_RegisterSbg56AESCMAC()
  <li>hu_RegisterSbg56AESXCBCMAC()
  <li>hu_RegisterSbg56ANSIX931Rng()
  <li>hu_RegisterSbg56AuthEncGCM()
  <li>hu_RegisterSbg56AuthEncCCM()
  <li>hu_RegisterSbg56AuthEncCCMStar()
  <li>hu_RegisterSbg56ARC2()
  <li>hu_RegisterSbg56ARC4()
  <li>hu_RegisterSbg56DES()
  <li>hu_RegisterSbg56DrbgCipherRng()
  <li>hu_RegisterSbg56DrbgEcRng()
  <li>hu_RegisterSbg56DrbgHashRng()
  <li>hu_RegisterSbg56DrbgHmacRng()
  <li>hu_RegisterSbg56ECC()
  <li>hu_RegisterSbg56ECCSecp192r1_2()
  <li>hu_RegisterSbg56ECCSecp256r1_2()
  <li>hu_RegisterSbg56ECCSecp384r1_2()
  <li>hu_RegisterSbg56ECCSecp521r1_2()
  <li>hu_RegisterSbg56ECCSect163k1_2()
  <li>hu_RegisterSbg56ECCSect283k1_2()
  <li>hu_RegisterSbg56FIPS140ANSIRng()
  <li>hu_RegisterSbg56HMACMD5()
  <li>hu_RegisterSbg56HMACSHA1()
  <li>hu_RegisterSbg56HMACSHA224()
  <li>hu_RegisterSbg56HMACSHA256()
  <li>hu_RegisterSbg56HMACSHA384()
  <li>hu_RegisterSbg56HMACSHA512()
  <li>hu_RegisterSbg56IDLC()
  <li>hu_RegisterSbg56IDLCParamsANSI_2()
  <li>hu_RegisterSbg56IDLCParamsFIPS_2()
  <li>hu_RegisterSbg56IDLCParamsIDLC_2()
  <li>hu_RegisterSbg56IDLCParamsIPSec1_2()
  <li>hu_RegisterSbg56IDLCParamsIPSec2_2()
  <li>hu_RegisterSbg56IDLCParamsIPSec5_2()
  <li>hu_RegisterSbg56IDLCParamsIPSec14_2()
  <li>hu_RegisterSbg56IDLCParamsIPSec15_2()
  <li>hu_RegisterSbg56IDLCParamsIPSec16_2()
  <li>hu_RegisterSbg56IDLCParamsIPSec17_2()
  <li>hu_RegisterSbg56IDLCParamsIPSec18_2()
  <li>hu_RegisterSbg56IDLCParamsWTLS1_2()
  <li>hu_RegisterSbg56IDLCParamsWTLS2_2()
  <li>hu_RegisterSbg56KdfDerive()
  <li>hu_RegisterSbg56MD2()
  <li>hu_RegisterSbg56MD4()
  <li>hu_RegisterSbg56MD5()
  <li>hu_RegisterSbg56PbeKdf()
  <li>hu_RegisterSbg56RSA()
  <li>hu_RegisterSbg56RngGetState()
  <li>hu_RegisterSbg56SHA1()
  <li>hu_RegisterSbg56SHA224()
  <li>hu_RegisterSbg56SHA256()
  <li>hu_RegisterSbg56SHA384()
  <li>hu_RegisterSbg56SHA512()
  <li>hu_RegisterSbg56AESMMO()
  <li>hu_RegisterSbg56Ks()
</ul>
$FunctionListEnd

<em>Note</em>: Any registration functions that require an optimization level 
(e.g. <tt>hu_RegisterSbg56ECCSecp256r1_</tt><em>optlevel</em><tt>()</tt>) will 
have the optimization level set to 2 by default.

@param[in]  sbCtx A global context.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_RegisterSbg56(
    sb_GlobalCtx sbCtx
);

/** @} */

#ifdef __cplusplus
}
#endif

#endif
