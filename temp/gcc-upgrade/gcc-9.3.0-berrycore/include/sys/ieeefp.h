/*	$NetBSD: ieeefp.h,v 1.2 1998/01/05 07:02:56 perry Exp $	*/

/* 
 * Written by J.T. Conklin, Apr 6, 1995
 * Public domain.
 *
 * Modified by Steve Furr
 */

#ifndef _SYS_IEEEFP_H_
#define _SYS_IEEEFP_H_

#include <fpstatus.h>

typedef enum _exception_flags fp_except;
#define FP_X_INV	_FP_EXC_INVALID		/* invalid operation exception */
#define FP_X_DNML	_FP_EXC_DENORMAL	/* denormalization exception */
#define FP_X_DZ		_FP_EXC_DIVZERO		/* divide-by-zero exception */
#define FP_X_OFL	_FP_EXC_OVERFLOW	/* overflow exception */
#define FP_X_UFL	_FP_EXC_UNDERFLOW	/* underflow exception */
#define FP_X_IMP	_FP_EXC_INEXACT		/* imprecise (loss of precision) */

typedef enum {
    FP_RN=_FP_ROUND_NEAREST,			/* round to nearest representable number */
    FP_RM=_FP_ROUND_NEGATIVE,			/* round toward negative infinity */
    FP_RP=_FP_ROUND_POSITIVE,			/* round toward positive infinity */
    FP_RZ=_FP_ROUND_ZERO			/* round to zero (truncate) */
} fp_rnd;

#endif /* _I386_IEEEFP_H_ */

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/m/public/sys/ieeefp.h $ $Rev: 219996 $" )
