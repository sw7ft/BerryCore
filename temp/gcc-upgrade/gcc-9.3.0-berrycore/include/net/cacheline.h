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





#ifndef _NET_CACHELINE_H_INCLUDED
#define _NET_CACHELINE_H_INCLUDED

/*
 * Assumed largest cacheline size.  We try
 * to align certain structures / members
 * to this.
 */
#define NET_CACHELINE_SIZE 64
#define NET_CACHELINE_ALIGN(p) ((void *)(((unsigned int)(p) + NET_CACHELINE_SIZE - 1) & ~(NET_CACHELINE_SIZE - 1)))

#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/socket/public/net/cacheline.h $ $Rev: 241309 $" )
#endif
