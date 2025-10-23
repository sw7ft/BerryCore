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

/*	$NetBSD: if_inarp.h,v 1.37 2006/05/18 09:05:51 liamjfoy Exp $	*/

/*
 * Copyright (c) 1982, 1986, 1993
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
 *	@(#)if_ether.h	8.1 (Berkeley) 6/10/93
 */

#ifndef _NETINET_IF_INARP_H_INCLUDED
#define _NETINET_IF_INARP_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef __QUEUE_H_INCLUDED
#include <sys/queue.h>
#endif

#ifndef _INTTYPES_H_INCLUDED
#include <inttypes.h>
#endif

#ifndef _NETINET_IN_H_INCLUDED
#include <netinet/in.h>
#endif

struct llinfo_arp {
	LIST_ENTRY(llinfo_arp) la_list;
	struct	rtentry *la_rt;
	struct	mbuf *la_hold;		/* last packet until resolved/timeout */
	long	la_asked;		/* last time we QUERIED for this addr */
#define la_timer la_rt->rt_rmx.rmx_expire /* deletion time in seconds */
};

struct sockaddr_inarp {
	uint8_t  sin_len;
	uint8_t  sin_family;
	uint16_t sin_port;
	struct	  in_addr sin_addr;
	struct	  in_addr sin_srcaddr;
	uint16_t sin_tos;
#ifdef __QNXNTO__

/*
 * Previously, the sockaddr_inarp structure member sin_tos was unused. It is
 * now used to hold the interface index to support proxy ARP for broadcast
 * type interfaces (Ethernet/ARP).
 */

#define sin_iface sin_tos

#endif
	uint16_t sin_other;
#define SIN_PROXY 1
};

/*
 * IP and ethernet specific routing flags
 */
#define	RTF_USETRAILERS	RTF_PROTO1	/* use trailers */
#define	RTF_ANNOUNCE	RTF_PROTO2	/* announce new arp entry */

#ifdef _KERNEL
extern struct ifqueue arpintrq;
void arp_ifinit(struct ifnet *, struct ifaddr *);
#ifndef QNX_MFIB
void arp_rtrequest(int, struct rtentry *, struct rt_addrinfo *);
#else
void arp_rtrequest(int, struct rtentry *, struct rt_addrinfo *, int);
#endif
#ifndef __QNXNTO__
int arpresolve(struct ifnet *, struct rtentry *, struct mbuf *,
		    struct sockaddr *, u_char *);
void arpintr(void);
#else 
int arpresolve(struct ifnet *, struct rtentry *, struct mbuf *,
#ifndef QNX_MFIB
		    struct sockaddr *, u_char *, int);
#else
			struct sockaddr *, u_char *, int, int);
#endif
int arp_isresolved(struct rtentry *);
void arpinit(void);
#endif
void arprequest(struct ifnet *, struct in_addr *, struct in_addr *, u_int8_t *);
void arp_drain(void);
int arpioctl(u_long, caddr_t);
void arpwhohas(struct ifnet *, struct in_addr *);

void revarpinput(struct mbuf *);
void in_revarpinput(struct mbuf *);
void revarprequest(struct ifnet *);
int revarpwhoarewe(struct ifnet *, struct in_addr *, struct in_addr *);
#endif

#endif /* !_NETINET_IF_INARP_H_INCLUDED */

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/socket/public/netinet/if_inarp.h $ $Rev: 647703 $" )
