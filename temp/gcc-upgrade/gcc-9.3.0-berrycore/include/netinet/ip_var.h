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

/*	$NetBSD: ip_var.h,v 1.77 2006/02/16 20:17:20 perry Exp $	*/

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
 *	@(#)ip_var.h	8.2 (Berkeley) 1/9/95
 */

#ifndef _NETINET_IP_VAR_H_INCLUDED
#define _NETINET_IP_VAR_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
#include <sys/types.h>
#endif

#ifndef _INTTYPES_H_INCLUDED
#include <inttypes.h>
#endif

#ifndef _NETINET_IN_H_INCLUDED
#include <netinet/in.h>
#endif

#ifndef __QUEUE_H_INCLUDED
#include <sys/queue.h>
#endif

#ifndef _NET_ROUTE_H_INCLUDED
#include <net/route.h>
#endif

/*
 * Overlay for ip header used by other protocols (tcp, udp).
 */
struct ipovly {
	uint8_t  ih_x1[9];		/* (unused) */
	uint8_t  ih_pr;		/* protocol */
	uint16_t ih_len;		/* protocol length */
	struct	  in_addr ih_src;	/* source internet address */
	struct	  in_addr ih_dst;	/* destination internet address */
} __attribute__((__packed__));

/*
 * Ip (reassembly or sequence) queue structures.
 *
 * XXX -- The following explains why the ipqe_m field is here, for TCP's use:
 * We want to avoid doing m_pullup on incoming packets but that
 * means avoiding dtom on the tcp reassembly code.  That in turn means
 * keeping an mbuf pointer in the reassembly queue (since we might
 * have a cluster).  As a quick hack, the source & destination
 * port numbers (which are no longer needed once we've located the
 * tcpcb) are overlayed with an mbuf pointer.
 */
TAILQ_HEAD(ipqehead, ipqent);
struct ipqent {
	TAILQ_ENTRY(ipqent) ipqe_q;
	union {
		struct ip	*_ip;
		struct tcpiphdr *_tcp;
	} _ipqe_u1;
	struct mbuf	*ipqe_m;	/* point to first mbuf */
	struct mbuf	*ipre_mlast;	/* point to last mbuf */
	uint8_t	ipqe_mff;	/* for IP fragmentation */
	/*
	 * The following are used in TCP reassembly
	 */
	TAILQ_ENTRY(ipqent) ipqe_timeq;
	uint32_t ipqe_seq;
	uint32_t ipqe_len;
	uint32_t ipqe_flags;
};
#define	ipqe_ip		_ipqe_u1._ip
#define	ipqe_tcp	_ipqe_u1._tcp

/*
 * Ip reassembly queue structure.  Each fragment
 * being reassembled is attached to one of these structures.
 * They are timed out after ipq_ttl drops to 0, and may also
 * be reclaimed if memory becomes tight.
 */
struct ipq {
	LIST_ENTRY(ipq) ipq_q;		/* to other reass headers */
	uint8_t  ipq_ttl;		/* time for reass q to live */
	uint8_t  ipq_p	;		/* protocol of this fragment */
	uint16_t ipq_id;		/* sequence id for reassembly */
	struct   ipqehead ipq_fragq;	/* to ip fragment queue */
	struct   in_addr ipq_src, ipq_dst;
	uint16_t ipq_nfrags;		/* frags in this queue entry */
};

/*
 * Structure stored in mbuf in inpcb.ip_options
 * and passed to ip_output when ip options are in use.
 * The actual length of the options (including ipopt_dst)
 * is in m_len.
 */
#define	MAX_IPOPTLEN	40

struct ipoption {
	struct	in_addr ipopt_dst;	/* first-hop dst if source routed */
	int8_t	ipopt_list[MAX_IPOPTLEN];	/* options proper */
};

/*
 * Structure attached to inpcb.ip_moptions and
 * passed to ip_output when IP multicast options are in use.
 */
struct ip_moptions {
	struct	  ifnet *imo_multicast_ifp; /* ifp for outgoing multicasts */
	struct in_addr imo_multicast_addr; /* ifindex/addr on MULTICAST_IF */
	uint8_t  imo_multicast_ttl;	/* TTL for outgoing multicasts */
	uint8_t  imo_multicast_loop;	/* 1 => hear sends if a member */
	uint16_t imo_num_memberships;	/* no. memberships this socket */
	struct	  in_multi *imo_membership[IP_MAX_MEMBERSHIPS];
};

struct	ipstat {
	uint64_t ips_total;		/* total packets received */
	uint64_t ips_badsum;		/* checksum bad */
	uint64_t ips_tooshort;		/* packet too short */
	uint64_t ips_toosmall;		/* not enough data */
	uint64_t ips_badhlen;		/* ip header length < data size */
	uint64_t ips_badlen;		/* ip length < ip header length */
	uint64_t ips_fragments;		/* fragments received */
	uint64_t ips_fragdropped;	/* frags dropped (dups, out of space) */
	uint64_t ips_fragtimeout;	/* fragments timed out */
	uint64_t ips_forward;		/* packets forwarded */
	uint64_t ips_fastforward;	/* packets fast forwarded */
	uint64_t ips_cantforward;	/* packets rcvd for unreachable dest */
	uint64_t ips_redirectsent;	/* packets forwarded on same net */
	uint64_t ips_noproto;		/* unknown or unsupported protocol */
	uint64_t ips_delivered;		/* datagrams delivered to upper level*/
	uint64_t ips_localout;		/* total ip packets generated here */
	uint64_t ips_odropped;		/* lost packets due to nobufs, etc. */
	uint64_t ips_reassembled;	/* total packets reassembled ok */
	uint64_t ips_fragmented;	/* datagrams successfully fragmented */
	uint64_t ips_ofragments;	/* output fragments created */
	uint64_t ips_cantfrag;		/* don't fragment flag was set, etc. */
	uint64_t ips_badoptions;	/* error in option processing */
	uint64_t ips_noroute;		/* packets discarded due to no route */
	uint64_t ips_badvers;		/* ip version != 4 */
	uint64_t ips_rawout;		/* total raw ip packets generated */
	uint64_t ips_badfrags;		/* malformed fragments (bad length) */
	uint64_t ips_rcvmemdrop;	/* frags dropped for lack of memory */
	uint64_t ips_toolong;		/* ip length > max ip packet size */
	uint64_t ips_nogif;		/* no match gif found */
	uint64_t ips_badaddr;		/* invalid address on header */
};

#define	IPFLOW_HASHBITS			6 /* should not be a multiple of 8 */
					  /* Must be <= 8 * sizeof((struct ipflow).hash) <= 16 */
#ifdef _KERNEL
#ifdef __QNXNTO__
#include <tpass.h>
#endif

struct ipflow {
	struct tpass_entry ipf_tpe;	/* As first member for tpass */
	LIST_ENTRY(ipflow) ipf_list;	/* next in active list */
	LIST_ENTRY(ipflow) ipf_hash;	/* next ipflow in bucket */
	struct in_addr ipf_dst;		/* destination address */
	struct in_addr ipf_src;		/* source address */
	uint8_t ipf_tos;		/* type-of-service */
	uint8_t _;			/* pad */
	uint16_t hash;                  /* cached hash index (see comment WRT IPFLOW_HASHBITS) */
	struct route ipf_ro;		/* associated route entry */
	struct rtentry *ipf_gw;		/* gateway route */
	u_long ipf_uses;		/* number of uses in this period */
	u_long ipf_last_uses;		/* number of uses in last period */
	u_long ipf_dropped;		/* ENOBUFS returned by if_output */
	u_long ipf_errors;		/* other errors returned by if_output */
	u_int ipf_timer;		/* lifetime timer */
	time_t ipf_start;		/* creation time */

	struct ipflow_thread {
		TPASS_LIST_DECLARE(, ipflow)     ipf_th_tplu;
#define ipf_th_passlist ipf_th_tplu.tpl_local
		LIST_ENTRY(ipflow) ipf_th_hash;	/* next ipflow in bucket */
	} ipf_thread[1];		/* More if multithreaded */
};

#define IPF_MARK_OFFLIST(ipfth)	\
	TPASS_MARK_OFFLIST(&(ipfth)->ipf_th_tplu.tpl_private)


#ifdef _KERNEL_OPT
#include "opt_gateway.h"
#include "opt_mbuftrace.h"
#endif

/* flags passed to ip_output as last parameter */
#define	IP_FORWARDING		0x1		/* most of ip header exists */
#define	IP_RAWOUTPUT		0x2		/* raw ip header exists */
#define	IP_RETURNMTU		0x4		/* pass back mtu on EMSGSIZE */
#define	IP_ROUTETOIF		SO_DONTROUTE	/* bypass routing tables */
#define	IP_ALLOWBROADCAST	SO_BROADCAST	/* can send broadcast packets */
#define	IP_MTUDISC		0x0400		/* Path MTU Discovery; set DF */
#ifdef __QNXNTO__
#define	IP_BINDTODEVICE		SO_BINDTODEVICE	/* 0x0800 */
#define IP_IPSECINNERIF		0x1000
#endif

#ifdef __NO_STRICT_ALIGNMENT
#define	IP_HDR_ALIGNED_P(ip)	1
#else
#define	IP_HDR_ALIGNED_P(ip)	((((vaddr_t) (ip)) & 3) == 0)
#endif

extern struct domain inetdomain;

extern struct ipstat ipstat;		/* ip statistics */
extern LIST_HEAD(ipqhead, ipq) ipq[];	/* ip reass. queue */
extern int   ip_defttl;			/* default IP ttl */
extern int   ipforwarding;		/* ip forwarding */
#ifdef QNX_MFIB
extern int   ipforwarding_mfibmask;
#endif
extern int   ip_mtudisc;		/* mtu discovery */
extern int   ip_mtudisc_timeout;	/* seconds to timeout mtu discovery */
extern int   anonportmin;		/* minimum ephemeral port */
extern int   anonportmax;		/* maximum ephemeral port */
extern int   lowportmin;		/* minimum reserved port */
extern int   lowportmax;		/* maximum reserved port */
extern int   ip_do_loopback_cksum;	/* do IP checksum on loopback? */
#ifndef QNX_MFIB
extern struct rttimer_queue *ip_mtudisc_timeout_q;
#else
extern struct rttimer_queue *ip_mtudisc_timeout_q[];
#endif
#ifdef MBUFTRACE
extern struct mowner ip_rx_mowner;
extern struct mowner ip_tx_mowner;
#endif
#ifdef GATEWAY
extern int ip_maxflows;
#endif
extern struct pool inmulti_pool;
extern struct pool ipqent_pool;
struct	 inpcb;
#ifdef __QNXNTO__
struct ipflow_threadinfo;
extern int   ip_bindinterface;
extern int   ip_checkinterface;
#endif

int	 ip_ctloutput(int, struct socket *, int, int, struct mbuf **);
int	 ip_dooptions(struct mbuf *);
void	 ip_drain(void);
void	 ip_forward(struct mbuf *, int);
void	 ip_freef(struct ipq *);
void	 ip_freemoptions(struct ip_moptions *);
int	 ip_getmoptions(int, struct ip_moptions *, struct mbuf **);
void	 ip_init(void);
int	 ip_optcopy(struct ip *, struct ip *);
u_int	 ip_optlen(struct inpcb *);
#ifndef QNX_MFIB
int	 ip_output(struct mbuf *, ...);
#else
int	 ip_output(struct mbuf *, int, ...);
#endif
int	 ip_fragment(struct mbuf *, struct ifnet *, u_long);
int	 ip_pcbopts(struct mbuf **, struct mbuf *);
struct mbuf *
	 ip_reass(struct ipqent *, struct ipq *, struct ipqhead *);
#ifndef QNX_MFIB
struct in_ifaddr *
	 ip_rtaddr(struct in_addr);
#else
struct in_ifaddr *
	 ip_rtaddr(struct in_addr, int);
#endif
void	 ip_savecontrol(struct inpcb *, struct mbuf **, struct ip *,
	   struct mbuf *);
#ifndef QNX_MFIB
int	 ip_setmoptions(int, struct ip_moptions **, struct mbuf *);
#else
int	 ip_setmoptions(int, struct ip_moptions **, struct mbuf *, int);
#endif

#ifndef __QNXNTO__
void	 ip_slowtimo(void);
#else
int	 ip_slowtimo(void);
#endif
struct mbuf *
	 ip_srcroute(void);
void	 ip_stripoptions(struct mbuf *, struct mbuf *);
int	 ip_sysctl(int *, u_int, void *, size_t *, void *, size_t);
void	 ipintr(void);
void *	 rip_ctlinput(int, const struct sockaddr *, void *);
int	 rip_ctloutput(int, struct socket *, int, int, struct mbuf **);
void	 rip_init(void);
void	 rip_input(struct mbuf *, ...);
#ifndef QNX_MFIB
int	 rip_output(struct mbuf *, ...);
#else
int	 rip_output(struct mbuf *, int, ...);
#endif
int	 rip_usrreq(struct socket *,
	    int, struct mbuf *, struct mbuf *, struct mbuf *, struct lwp *);
void	ipflow_init(void);
#ifdef __QNXNTO__
int	ipflow_pre_main_init(void);
void	ipflow_pre_main_fini(void);
int	ipflow_register(struct ipflow_threadinfo **);
int	ipflow_deregister(struct ipflow_threadinfo *);
#endif
struct	ipflow *ipflow_reap(int);
void	ipflow_create(const struct route *, struct mbuf *);
#ifndef __QNXNTO__
void	ipflow_slowtimo(void);
#else
int	ipflow_slowtimo(void);
#endif
void	ipflow_invalidate_all(void);

extern uint16_t	ip_id;
static __inline uint16_t ip_newid(void);

uint16_t ip_randomid(void);
extern int ip_do_randomid;

/*
 * ip_newid_range: "allocate" num contiguous ip_ids.
 *
 * => return the first id.
 */

static __inline uint16_t
ip_newid_range(unsigned int num)
{
	uint16_t id;

	if (ip_do_randomid) {
		/* XXX ignore num */
		return ip_randomid();
	}

	id = htons(ip_id);
	ip_id += num;

	return id;
}

static __inline uint16_t
ip_newid(void)
{

	return ip_newid_range(1);
}

#endif  /* _KERNEL */

#endif /* !_NETINET_IP_VAR_H_INCLUDED */

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/socket/public/netinet/ip_var.h $ $Rev: 741882 $" )
