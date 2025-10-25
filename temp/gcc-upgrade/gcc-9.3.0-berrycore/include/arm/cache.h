/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
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
 *  arm/cache.h
 *

 */
 
#ifndef _ARM_CACHE_H_INCLUDED
#define _ARM_CACHE_H_INCLUDED

#ifndef __CACHE_H_INCLUDED
#include <sys/cache.h>
#endif

/* On ARM, we execute the callout routines in the syspage directly */
#define __CACHE_EXECUTE_CALLOUTS

#endif /* _ARM_CACHE_H_INCLUDED */

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/cache/public/arm/cache.h $ $Rev: 219996 $" )
