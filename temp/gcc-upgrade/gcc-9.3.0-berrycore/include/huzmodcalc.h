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
/* $Id: huzmodcalc.h 41602 2010-11-22 20:17:42Z korr $
 * $Source$
 * $Name$
 */
#ifndef HUZMODCALC_H
#define HUZMODCALC_H

/** @file */

#ifdef __cplusplus
extern "C" {
#endif

#include "sbdef.h"

/** @addtogroup hu_zmodcalc_api ZMod Calculator APIs
 *
 * @{
 */


/** Computes integer modulo exponentiation.

Inputs to this function are integers represented in octet string.

There can be leading <tt>0</tt> octets for base and exponent.
However, leading <tt>0</tt> octet is not allowed for modulus.

The result is an element of a finite field. Thus, the result is represented
in octet string, where the value is represented in the same number of octets
as the modulus.  If the value is smaller, it will be padded with <tt>0</tt>
octets to the size of the modulus.

@param[in]  baseLen   Length of the base in bytes.
@param[in]  baseValue Value of the base as an integer
@param[in]  expoLen   Length of the exponent in bytes.
@param[in]  expoValue Value of the exponent as an integer.
@param[in]  modLen    Length of the modulus in bytes.
@param[in]  modValue  Value of the modulus as an integer.  
                      The modulus must be a prime number.
@param[out] result    The result finite field element.
@param[in]  yieldCtx  Yield context.
@param[in]  sbCtx     A global context.

@retval SB_ERR_BAD_INPUT_LEN Input parameter length is invalid.
@retval SB_ERR_NULL_INPUT    Input parameter is <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT     Input parameter value is invalid.
@retval SB_FAIL_ALLOC        Memory allocation failure.
@retval SB_FAILURE           Operation failed.
@retval SB_SUCCESS           Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ZModCalcExpo(
    size_t baseLen,
    const unsigned char *baseValue,
    size_t expoLen,
    const unsigned char *expoValue,
    size_t modLen,
    const unsigned char *modValue,
    unsigned char *result,
    sb_YieldCtx yieldCtx,
    sb_GlobalCtx sbCtx
);


/** @} */

#ifdef __cplusplus
}
#endif

#endif
