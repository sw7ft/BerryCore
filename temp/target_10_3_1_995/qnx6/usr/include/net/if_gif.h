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

/*	$NetBSD: if_gif.h,v 1.13 2005/12/11 23:05:25 thorpej Exp $	*/
/*	$KAME: if_gif.h,v 1.23 2001/07/27 09:21:42 itojun Exp $	*/

/*
 * Copyright (C) 1995, 1996, 1997, and 1998 WIDE Project.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE PROJECT AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE PROJECT OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * if_gif.h
 */

#ifndef _NET_IF_GIF_H_INCLUDED
#define _NET_IF_GIF_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef __QUEUE_H_INCLUDED
#include <sys/queue.h>
#endif

#ifndef _NET_IF_H_INCLUDED
#include <net/if.h>
#endif

#if defined(_KERNEL) && !defined(_LKM)
#include "opt_inet.h"
#endif

#ifndef _NET_ROUTE_H_INCLUDED
#include <net/route.h>
#endif

#if defined(INET6) && !defined(_NETINET_IN_H_INCLUDED)
#include <netinet/in.h>
#endif
/* xxx sigh, why route have struct route instead of pointer? */

struct encaptab;

struct gif_softc {
	struct ifnet	gif_if;	   /* common area - must be at the top */
	struct sockaddr	*gif_psrc; /* Physical src addr */
	struct sockaddr	*gif_pdst; /* Physical dst addr */
	union {
		struct route  gifscr_ro;    /* xxx */
#ifdef INET6
		struct route_in6 gifscr_ro6; /* xxx */
#endif
	} gifsc_gifscr;
	int		gif_flags;
	const struct encaptab *encap_cookie4;
	const struct encaptab *encap_cookie6;
	LIST_ENTRY(gif_softc) gif_list;	/* list of all gifs */
#ifdef __HAVE_GENERIC_SOFT_INTERRUPTS
	void	*gif_si;		/* softintr handle */
#endif
	long	gif_route_expire;
#ifdef __QNXNTO__
	void	*gif_alloc;
#ifdef QNX_MFIB
	int		gif_tunnelfib; /* tunnel routing fib (post-encap, pre-decap) */
#endif
#endif
};
#define GIF_ROUTE_TTL	10

#define gif_ro gifsc_gifscr.gifscr_ro
#ifdef INET6
#define gif_ro6 gifsc_gifscr.gifscr_ro6
#endif

#define GIF_MTU		(1280)	/* Default MTU */
#define	GIF_MTU_MIN	(1280)	/* Minimum MTU */
#define	GIF_MTU_MAX	(8192)	/* Maximum MTU */

__BEGIN_DECLS

/* Prototypes */
void	gifattach0(struct gif_softc *);
void	gif_input(struct mbuf *, int, struct ifnet *);
int	gif_output(struct ifnet *, struct mbuf *,
		   struct sockaddr *, struct rtentry *);
int	gif_ioctl(struct ifnet *, u_long, caddr_t);
int	gif_set_tunnel(struct ifnet *, struct sockaddr *, struct sockaddr *);
void	gif_delete_tunnel(struct ifnet *);
#ifdef GIF_ENCAPCHECK
int	gif_encapcheck(struct mbuf *, int, int, void *);
#endif

__END_DECLS

#endif /* !_NET_IF_GIF_H_INCLUDED */

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/socket/public/net/if_gif.h $ $Rev: 647703 $" )
