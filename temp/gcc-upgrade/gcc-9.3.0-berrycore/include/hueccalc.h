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
/* $Id: hueccalc.h 38431 2009-02-19 18:12:30Z ayamada $
 * $Source$
 * $Name$
 */
#ifndef HUECCALC_H
#define HUECCALC_H

/** @file */

#ifdef __cplusplus
extern "C" {
#endif

#include "sbdef.h"

/** @addtogroup hu_eccalc_api EC Calculator APIs
 *
 * @{
 */


/** Create a point order integer object and set integer value if supplied.
If the value is not supplied, it generates an empty object.

A point order object contains an element of the point order finite field.

When supplied, the point order integer value (a finite field element) must be
represented as an octet string.  Even if the supplied value has correct byte
length, it can be rejected by returning an error if the value is larger than
or equal to point order.

An empty point order integer object represents an integer with the value of 0.
In order to generate an empty elliptic curve point object, set <tt>NULL</tt>
to <tt>orderIntValue</tt>.

The appropriate length can be inquired by using <tt>hu_ECCalcOrderIntGet()</tt>
function.


@param[in]     eccParams      ECC parameters object.
@param[in]     orderIntLen    The length (in bytes) of the integer value.
@param[in]     orderIntValue  The point order integer value.
@param[in,out] orderInt       The point order integer object.
@param[in]     sbCtx          SB context or memory callback data.

@retval SB_ERR_NULL_PARAMS        ECC parameters object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS         ECC parameters object is invalid.
@retval SB_ERR_NULL_ORDER_INT_PTR Point order object pointer is <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN  The value length is invalid.
@retval SB_ERR_BAD_INPUT          The value is larger than or equal to point
                                  order.
@retval SB_FAIL_ALLOC             Memory allocation failure.
@retval SB_FAILURE                Operation failed.
@retval SB_SUCCESS                Success.
 
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ECCalcOrderIntSet(
    sb_Params eccParams,
    size_t orderIntLen,
    const unsigned char *orderIntValue,
    sb_ECCalcOrderInt *orderInt,
    sb_GlobalCtx sbCtx
);


/** Create an elliptic curve point object, and set an elliptic curve point
value if supplied. If the value is not supplied, then this function generates an
empty object.

When supplied, the elliptic curve point value must be represented as an octet
string. The supplied point must belong to the subgroup specified by the ECC
domain parameter, including point at infinity.

An empty elliptic curve point object represents a two-tuple with both x- and
y-coordinates are 0. It acts as a point at infinity.

To generate an empty elliptic curve point object, set <tt>pointValue</tt> to 
<tt>NULL</tt>.

The appropriate length can be determined by using the 
<tt>hu_ECCalcECPointGet()</tt> function.

@param[in]     eccParams   ECC parameters object.
@param[in]     pointLen    The length (in bytes) of the elliptic curve point 
                           value.
@param[in]     pointValue  The elliptic curve point value.
@param[in,out] point       The elliptic curve point object.
@param[in]     sbCtx       SB context or memory callback data.

@retval SB_ERR_NULL_PARAMS       ECC parameters object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS        ECC parameters object is invalid.
@retval SB_ERR_NULL_ECPOINT_PTR  The elliptic curve point object pointer is
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_INPUT_BUF_LEN The value length is invalid.
@retval SB_ERR_BAD_INPUT         The value is invalid.
@retval SB_FAIL_ALLOC            Memory allocation failure.
@retval SB_FAILURE               Operation failed.
@retval SB_SUCCESS               Success.
 
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ECCalcECPointSet(
    sb_Params eccParams,
    size_t pointLen,
    const unsigned char *pointValue,
    sb_ECCalcECPoint *point,
    sb_GlobalCtx sbCtx
);


/** Obtain integer value from point order integer object.

If the output buffer is sufficiently large, the integer value will be set in the
output buffer, and the length is set in the length parameter. The integer value 
is represented in the octet string format (as a finite field element).

If the output buffer is not sufficient, an error is returned, and the necessary 
(correct) size is set in the length parameter.

In order to retrieve the necessary size of the output buffer, set 
<tt>orderIntValue</tt> to <tt>NULL</tt>. The length is set in the 
<tt>orderIntLen</tt> parameter.

@param[in]     eccParams      ECC parameters object.
@param[in]     orderInt       The point order integer object.
@param[in,out] orderIntLen    The length (in bytes) of the point order integer 
                              buffer.
@param[out]    orderIntValue  The point order integer buffer.
@param[in]     sbCtx          SB context or memory callback data.

@retval SB_ERR_NULL_PARAMS             ECC parameters object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS              ECC parameters object is invalid.
@retval SB_ERR_NULL_ORDER_INT          The point order integer objects is
                                       <tt>NULL</tt>.
@retval SB_ERR_BAD_ORDER_INT           The point order integer object is
                                       invalid.
@retval SB_ERR_NULL_OUTPUT_BUF_LEN_PTR The length pointer of the value buffer is
                                       <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN      The point order integer buffer length is
                                       invalid.
@retval SB_SUCCESS                     Success.
 
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ECCalcOrderIntGet(
    sb_Params eccParams,
    sb_ECCalcOrderInt orderInt,
    size_t *orderIntLen,
    unsigned char *orderIntValue,
    sb_GlobalCtx sbCtx
);


/** Obtain value from an elliptic curve point object.

If the output buffer is sufficiently large, the point value will be set in the 
output buffer, and the length is set in the length parameter. The elliptic curve
point value is represented in the octet string format.

If the output buffer is not sufficient, an error is returned, and the necessary 
(correct) size is set in the length parameter.

In order to retrieve the necessary size of the output buffer, set 
<tt>pointValue</tt> to <tt>NULL</tt>. The length is set in the 
<tt>pointLen</tt> parameter.

@param[in]     eccParams   ECC parameters object.
@param[in]     point       The elliptic curve point object.
@param[in,out] pointLen    The length (in bytes) of the elliptic curve point 
                           buffer.
@param[out]    pointValue  The elliptic curve point buffer.
@param[in]     sbCtx       SB context or memory callback data.

@retval SB_ERR_NULL_PARAMS             ECC parameters object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS              ECC parameters object is invalid.
@retval SB_ERR_NULL_ECPOINT            The elliptic curve point objects is
                                       <tt>NULL</tt>.
@retval SB_ERR_BAD_ECPOINT             The elliptic curve point object is
                                       invalid.
@retval SB_ERR_NULL_OUTPUT_BUF_LEN_PTR The length pointer of the value buffer is
                                       <tt>NULL</tt>.
@retval SB_ERR_BAD_OUTPUT_BUF_LEN      The elliptic curve point buffer length is
                                       invalid.
@retval SB_SUCCESS                     Success.
 
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ECCalcECPointGet(
    sb_Params eccParams,
    sb_ECCalcECPoint point,
    size_t *pointLen,
    unsigned char *pointValue,
    sb_GlobalCtx sbCtx
);


/** Destroys a point order integer object.

Point order integer object must be destroyed before the ECC parameters object
is destroyed.

@param[in]     eccParams  ECC parameters object.
@param[in,out] orderInt   The point order integer object.
@param[in]     sbCtx      SB context or memory callback data.

@retval SB_ERR_NULL_PARAMS        ECC parameters object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS         ECC parameters object is invalid.
@retval SB_ERR_NULL_ORDER_INT_PTR The point order integer object pointer is
                                  <tt>NULL</tt>.
@retval SB_ERR_NULL_ORDER_INT     The point order integer objects is
                                  <tt>NULL</tt>.
@retval SB_ERR_BAD_ORDER_INT      The point order integer object is invalid.
@retval SB_SUCCESS                Success.
 
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ECCalcOrderIntDestroy(
    sb_Params eccParams,
    sb_ECCalcOrderInt *orderInt,
    sb_GlobalCtx sbCtx
);


/** Destroys an elliptic curve point object.

Elliptic curve point object must be destroyed before the ECC parameters object
is destroyed.

@param[in]     eccParams   ECC parameters object.
@param[in,out] point       The elliptic curve point object.
@param[in]     sbCtx       SB context or memory callback data.

@retval SB_ERR_NULL_PARAMS      ECC parameters object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS       ECC parameters object is invalid.
@retval SB_ERR_NULL_ECPOINT_PTR The elliptic curve point object pointer is
                                <tt>NULL</tt>.
@retval SB_ERR_NULL_ECPOINT     The elliptic curve point object is
                                <tt>NULL</tt>.
@retval SB_ERR_BAD_ECPOINT      The elliptic curve point object is
                                invalid.
@retval SB_SUCCESS              Success.
 
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ECCalcECPointDestroy(
    sb_Params eccParams,
    sb_ECCalcECPoint *point,
    sb_GlobalCtx sbCtx
);


/** Computes integer multiplication of an integer and an elliptic curve point.

If the input point is <tt>NULL</tt>, the generating point is used.

<tt>resultPoint = multInt * point</tt>

Input and output elliptic curve point objects can be the same.

@param[in]  eccParams     ECC parameters object.
@param[in]  multInt       The multiplying integer.
@param[in]  point         The point.
@param[out] resultPoint   The result point.
@param[in]  sbCtx         A global context.

@retval SB_ERR_NULL_PARAMS       ECC parameters object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS        ECC parameters object is invalid.
@retval SB_ERR_NULL_ORDER_INT    The point order integer object is <tt>NULL</tt>.
@retval SB_ERR_BAD_ORDER_INT     The point order integer object is invalid.
@retval SB_ERR_NULL_ECPOINT      The elliptic curve point object is <tt>NULL</tt>.
@retval SB_ERR_BAD_ECPOINT       The elliptic curve point object is invalid.
@retval SB_FAIL_ALLOC            Memory allocation failure.
@retval SB_FAILURE               Operation failed.
@retval SB_ERR_POINT_AT_INFINITY Operation resulted in point at infinity 
                                 (caller to interpret as error or not).
@retval SB_SUCCESS               Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ECCalcIntMult(
    sb_Params eccParams,
    sb_ECCalcOrderInt multInt,
    sb_ECCalcECPoint point,
    sb_ECCalcECPoint resultPoint,
    sb_GlobalCtx sbCtx
);


/** Computes linear combination of two points (sum of two integer multiplies).

If the second EC point (<tt>pointB</tt>) is <tt>NULL</tt>, the generating point is used.

<tt>resultPoint = multIntA * pointA + multIntB * pointB</tt>

Any or all of the input and output elliptic curve point objects can be the same.

@param[in]  eccParams    ECC parameters object.
@param[in]  multIntA     The multiplying integer to Point A.
@param[in]  pointA       Point A.
@param[in]  multIntB     The multiplying integer to Point B.
@param[in]  pointB       Point B.
@param[out] resultPoint  The result linear combination (containing only 
                         x-coordinate value).
@param[in]  sbCtx        A global context.

@retval SB_ERR_NULL_PARAMS       ECC parameters object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS        ECC parameters object is invalid.
@retval SB_ERR_NULL_ORDER_INT    The point order integer object is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_ORDER_INT     The point order integer object is invalid.
@retval SB_ERR_NULL_ECPOINT      The elliptic curve point object is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_ECPOINT       The elliptic curve point object is invalid.
@retval SB_FAIL_ALLOC            Memory allocation failure.
@retval SB_FAILURE               Operation failed.
@retval SB_ERR_POINT_AT_INFINITY Operation resulted in point at infinity 
                                 (caller to interpret as error or not).
@retval SB_SUCCESS               Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ECCalcLinMult(
    sb_Params eccParams,
    sb_ECCalcOrderInt multIntA,
    sb_ECCalcECPoint pointA,
    sb_ECCalcOrderInt multIntB,
    sb_ECCalcECPoint pointB,
    sb_ECCalcECPoint resultPoint,
    sb_GlobalCtx sbCtx
);


/** Adds two elliptic curve points.

<tt>resultPoint = pointA + pointB</tt>

Any or all of the input and output elliptic curve point objects can be the same.

@param[in]  eccParams    The ECC parameters object.
@param[in]  pointA       Point A.
@param[in]  pointB       Point B.
@param[out] resultPoint  Sum of Point A and Point B.
@param[in]  sbCtx        A global context

@retval SB_ERR_NULL_PARAMS       ECC parameters object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS        ECC parameters object is invalid.
@retval SB_ERR_NULL_ECPOINT      The elliptic curve point object is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_ECPOINT       The elliptic curve point object is invalid.
@retval SB_FAIL_ALLOC            Memory allocation failure.
@retval SB_FAILURE               Operation failed.
@retval SB_ERR_POINT_AT_INFINITY Operation resulted in point at infinity 
                                 (caller to interpret as error or not).
@retval SB_SUCCESS               Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ECCalcAdd(
    sb_Params eccParams,
    sb_ECCalcECPoint pointA,
    sb_ECCalcECPoint pointB,
    sb_ECCalcECPoint resultPoint,
    sb_GlobalCtx sbCtx
);


/** Negates an elliptic curve point.

<tt>resultPoint = -point</tt>

Input and output elliptic curve point objects can be the same.

@param[in]  eccParams    ECC parameters object.
@param[in]  point        The point.
@param[out] resultPoint  Negation of the point.
@param[in]  sbCtx        A global context

@retval SB_ERR_NULL_PARAMS       ECC parameters object is <tt>NULL</tt>.
@retval SB_ERR_BAD_PARAMS        ECC parameters object is invalid.
@retval SB_ERR_NULL_ECPOINT      The elliptic curve point object is 
                                 <tt>NULL</tt>.
@retval SB_ERR_BAD_ECPOINT       The elliptic curve point object is invalid.
@retval SB_FAIL_ALLOC            Memory allocation failure.
@retval SB_FAILURE               Operation failed.
@retval SB_ERR_POINT_AT_INFINITY Operation resulted in point at infinity 
                                 (caller to interpret as error or not).
@retval SB_SUCCESS               Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_ECCalcNeg(
    sb_Params eccParams,
    sb_ECCalcECPoint point,
    sb_ECCalcECPoint resultPoint,
    sb_GlobalCtx sbCtx
);


/** @} */

#ifdef __cplusplus
}
#endif

#endif
