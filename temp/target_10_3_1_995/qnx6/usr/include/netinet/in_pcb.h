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

/*	$NetBSD: in_pcb.h,v 1.50 2012/06/25 15:28:39 christos Exp $	*/

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
 * Copyright (c) 1982, 1986, 1990, 1993
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
 *	@(#)in_pcb.h	8.1 (Berkeley) 6/10/93
 */

#ifndef _NETINET_IN_PCB_H_INCLUDED
#define _NETINET_IN_PCB_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
#include <sys/types.h>
#endif

#ifndef _INTTYPES_H_INCLUDED
#include <inttypes.h>
#endif

#ifndef _NET_ROUTE_H_INCLUDED
#include <net/route.h>
#endif

#ifndef _NETINET_IP_H_INCLUDED
#include <netinet/ip.h>
#endif

#ifndef __QUEUE_H_INCLUDED
#include <sys/queue.h>
#endif

#ifndef _NET_IF_H_INCLUDED
#include <net/if.h>
#endif

#ifndef _NETINET_IN_PCB_HDR_H_INCLUDED
#include <netinet/in_pcb_hdr.h>
#endif

#ifndef _STDBOOL_H_INCLUDED
#include <stdbool.h>
#endif

/*
 * Common structure pcb for internet protocol implementation.
 * Here are stored pointers to local and foreign host table
 * entries, local and foreign socket numbers, and pointers
 * up (to a socket structure) and down (to a protocol-specific)
 * control block.
 */
struct inpcb {
	struct inpcb_hdr inp_head;
#define inp_hash	inp_head.inph_hash
#define inp_queue	inp_head.inph_queue
#define inp_af		inp_head.inph_af
#define inp_ppcb	inp_head.inph_ppcb
#define inp_state	inp_head.inph_state
#define inp_portalgo	inp_head.inph_portalgo
#define inp_socket	inp_head.inph_socket
#define inp_table	inp_head.inph_table
#define inp_sp		inp_head.inph_sp
	struct	  route inp_route;	/* placeholder for routing entry */
	uint16_t  inp_fport;		/* foreign port */
	uint16_t  inp_lport;		/* local port */
	int	  inp_flags;		/* generic IP/datagram flags */
	struct	  ip inp_ip;		/* header prototype; should have more */
	struct	  mbuf *inp_options;	/* IP options */
	struct	  ip_moptions *inp_moptions; /* IP multicast options */
	int	  inp_errormtu;		/* MTU of last xmit status = EMSGSIZE */
	bool      inp_bindportonsend;
#ifdef __QNXNTO__
	struct ifnet	*inp_bounddevice;
#endif
};

#define	inp_faddr	inp_ip.ip_dst
#define	inp_laddr	inp_ip.ip_src

/* flags in inp_flags: */
#define	INP_RECVOPTS		0x01	/* receive incoming IP options */
#define	INP_RECVRETOPTS		0x02	/* receive IP options for reply */
#define	INP_RECVDSTADDR		0x04	/* receive IP dst address */
#define	INP_HDRINCL		0x08	/* user supplies entire IP header */
#define	INP_HIGHPORT		0x10	/* (unused; FreeBSD compat) */
#define	INP_LOWPORT		0x20	/* user wants "low" port binding */
#define	INP_ANONPORT		0x40	/* port chosen for user */
#define	INP_RECVIF		0x80	/* receive incoming interface */
/* XXX should move to an UDP control block */
#define INP_ESPINUDP		0x100	/* ESP over UDP for NAT-T */
#define INP_ESPINUDP_NON_IKE	0x200	/* ESP over UDP for NAT-T */
#ifdef __QNXNTO__
#define INP_DEVPURGE		0x80000000	/* bound device was detached */
#endif
#define	INP_CONTROLOPTS		(INP_RECVOPTS|INP_RECVRETOPTS|INP_RECVDSTADDR|\
				INP_RECVIF)
#define INP_ESPINUDP_ALL	(INP_ESPINUDP|INP_ESPINUDP_NON_IKE)

#define	sotoinpcb(so)		((struct inpcb *)(so)->so_pcb)

#ifdef _KERNEL
void	in_losing(struct inpcb *);
int	in_pcballoc(struct socket *, void *);
int	in_pcbbind(void *, struct mbuf *, struct lwp *);
int	in_pcbconnect(void *, struct mbuf *, struct lwp *);
void	in_pcbdetach(void *);
void	in_pcbdisconnect(void *);
#ifdef __QNXNTO__
int	in_pcbformat(struct inpcb *, const char *,
	const char *, int, char *, int *);
int	inpcblist_unbindif(struct ifnet *, struct sockaddr *);
#endif
void	in_pcbinit(struct inpcbtable *, int, int);
struct inpcb *
	in_pcblookup_port(struct inpcbtable *,
	    struct in_addr, u_int, int);
struct inpcb *
	in_pcblookup_bind(struct inpcbtable *,
	    struct in_addr, u_int);
#ifdef __QNXNTO__
struct inpcb *
	in_pcblookup_bind_hint(struct inpcbtable *,
	    struct in_addr, u_int, struct ifnet *
#ifdef QNX_MFIB
	    , int
#endif
	);
#endif
struct inpcb *
	in_pcblookup_connect(struct inpcbtable *,
	    struct in_addr, u_int, struct in_addr, u_int);
#ifdef __QNXNTO__
struct inpcb *
	in_pcblookup_connect_hint(struct inpcbtable *,
	    struct in_addr, u_int, struct in_addr, u_int, void *
#ifdef QNX_MFIB
	    , int
#endif
	    );
void	in_unbindif(struct inpcb *);
#endif
int	in_pcbnotify(struct inpcbtable *, struct in_addr, u_int,
	    struct in_addr, u_int, int, void (*)(struct inpcb *, int));
void	in_pcbnotifyall(struct inpcbtable *, struct in_addr, int,
	    void (*)(struct inpcb *, int));
void	in_pcbpurgeif0(struct inpcbtable *, struct ifnet *);
void	in_pcbpurgeif(struct inpcbtable *, struct ifnet *);
void	in_pcbstate(struct inpcb *, int);
void	in_rtchange(struct inpcb *, int);
void	in_setpeeraddr(struct inpcb *, struct mbuf *);
void	in_setsockaddr(struct inpcb *, struct mbuf *);
struct rtentry *
	in_pcbrtentry(struct inpcb *);
#ifndef QNX_MFIB
extern struct sockaddr_in *in_selectsrc(struct sockaddr_in *,
	struct route *, int, struct ip_moptions *, int *, struct ifnet *);
#define in_selectsrc(sin, rt, a, ipm, bp) (in_selectsrc)((sin), (rt), (a), (ipm), (bp), NULL)
#else
extern struct sockaddr_in *in_selectsrc(struct sockaddr_in *,
	struct route *, int, struct ip_moptions *, int *, struct ifnet *, int);
#define in_selectsrc(sin, rt, a, ipm, bp) (in_selectsrc)((sin), (rt), (a), (ipm), (bp), NULL, fib)
#endif
#endif

#endif /* !_NETINET_IN_PCB_H_INCLUDED */

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/socket/public/netinet/in_pcb.h $ $Rev: 710616 $" )
