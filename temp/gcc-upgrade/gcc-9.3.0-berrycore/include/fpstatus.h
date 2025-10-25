/*
 * $QNXLicenseC:
 * Copyright 2007, 2009, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software.   Free development
 * licenses are available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 * $
 */



/*
 *  fpstatus.h
 *

 */
#ifndef __FPSTATUS_H_INCLUDED
#define __FPSTATUS_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

enum _round_type {
	_FP_ROUND_NEAREST	= 0,
	_FP_ROUND_ZERO,
	_FP_ROUND_POSITIVE,
	_FP_ROUND_NEGATIVE
};

enum _exception_flags {
	_FP_EXC_INEXACT		= 0x01,
	_FP_EXC_DIVZERO		= 0x02,
	_FP_EXC_UNDERFLOW	= 0x04,
	_FP_EXC_OVERFLOW	= 0x08,
	_FP_EXC_INVALID		= 0x10,
	_FP_EXC_DENORMAL	= 0x20
};

#define _FP_EXC_ALL (_FP_EXC_INEXACT | _FP_EXC_DIVZERO |	\
					 _FP_EXC_UNDERFLOW | _FP_EXC_OVERFLOW | \
					 _FP_EXC_INVALID | _FP_EXC_DENORMAL )

enum _precision_type {
	_FP_PREC_FLOAT		= 0,
	_FP_PREC_DOUBLE,
	_FP_PREC_EXTENDED,
	_FP_PREC_DOUBLE_EXTENDED
};

__BEGIN_DECLS

/*
 Return the current precision if 'newprecison' is < 0,
 otherwise set the precision to newprecision and return
 the old precision
*/
int fp_precision(int newprecision);
/*
 Return the current rounding mode if 'newrounding' is < 0,
 otherwise set the rounding mode to newrounding and return
 the old rounding mode
*/
int fp_rounding(int newrounding);
/*
 Return the current exception mask if set is < 0
 Otherwise enable the execption mask defined by
 new_mask if set is 1, else disable the exception
 mask defined by new_mask if set is 0.

if (set)  --> Enable interrupts defined by new_mask
if (!set) --> Disable interrupts defined by new_mask
*/
int fp_exception_mask(int new_mask, int set);
/*
 Get the value of the current exception registers
 Set bits indicate that the exception has signaled,
 Unset bits indicate that the exception has not signaled
*/
int fp_exception_value(int mask);

/*
 Set the floating point environment.
 If rounding >= 0, sets rounding mode as fp_rounding().
 Sets exception value bits given by "fmask" to "flags".
 Sets exception mask bits given by "emask" to "exc".
*/
void fp_setenv(int rounding, int flags, int fmask, int exc, int emask);

__END_DECLS

#endif

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/m/public/fpstatus.h $ $Rev: 219996 $" )
