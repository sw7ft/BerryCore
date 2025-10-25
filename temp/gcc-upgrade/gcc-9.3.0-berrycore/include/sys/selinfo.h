/*
 * $QNXtpLicenseC:
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

/*	$NetBSD: selinfo.h,v 1.2 2005/12/11 12:25:21 christos Exp $	*/

/*-
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)select.h	8.2 (Berkeley) 1/4/94
*	from: NetBSD: select.h,v 1.21 2005/03/10 00:25:45 kleink Exp
 */

#ifndef __SELINFO_H_INCLUDED
#define	__SELINFO_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef __TYPES_H_INCLUDED
#include <sys/types.h>
#endif

#ifndef __INTTYPES_H_INCLUDED
#include <inttypes.h>
#endif

#ifdef __EXT_BSD
#if !defined(__QNXNTO__) || defined(_KERNEL)	/* Until kqueue is supported */
#ifndef __EVENT_H_INCLUDED
#include <sys/event.h>		/* for struct klist */
#endif
#else
/* As in <sys/event.h> */
#include <sys/queue.h>
struct knote;
SLIST_HEAD(klist, knote);
#endif

/*
 * Used to maintain information about processes that wish to be
 * notified when I/O becomes possible.
 */
struct selinfo {
	struct klist	sel_klist;	/* knotes attached to this selinfo */
	pid_t		sel_pid;	/* process to be notified */
	uint8_t		sel_collision;	/* non-zero if a collision occurred */
};
#endif /* __EXT_BSD */

#ifdef _KERNEL
#include <sys/signal.h>			/* for sigset_t */

struct lwp;
struct proc;
struct timeval;

int	selcommon(struct lwp *, register_t *, int, fd_set *, fd_set *,
	    fd_set *, struct timeval *, sigset_t *);
void	selrecord(struct lwp *selector, struct selinfo *);
void	selwakeup(struct selinfo *);

static __inline void
selnotify(struct selinfo *sip, long knhint)
{

#ifndef __QNXNTO__
	if (sip->sel_pid != 0)
		selwakeup(sip);
#endif
	KNOTE(&sip->sel_klist, knhint);
}
#endif /* _KERNEL */

#endif /* !__SELINFO_H_INCLUDED */

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/socket/public/sys/selinfo.h $ $Rev: 233581 $" )
