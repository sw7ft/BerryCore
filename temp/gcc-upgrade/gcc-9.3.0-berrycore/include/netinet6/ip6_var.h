/*	$NetBSD: ip6_var.h,v 1.37.12.1 2007/04/28 18:30:13 bouyer Exp $	*/
/*	$KAME: ip6_var.h,v 1.33 2000/06/11 14:59:20 jinmei Exp $	*/

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
 *	@(#)ip_var.h	8.1 (Berkeley) 6/10/93
 */

#ifndef _NETINET6_IP6_VAR_H_INCLUDED
#define _NETINET6_IP6_VAR_H_INCLUDED

#ifndef _INTTYPES_H_INCLUDED
#include <inttypes.h>
#endif

#ifndef _NETINET_IN_H_INCLUDED
#include <netinet/in.h>
#endif

#ifndef __SYS_QUEUE_H_INCLUDED
#include <sys/queue.h>
#endif

/*
 * IP6 reassembly queue structure.  Each fragment
 * being reassembled is attached to one of these structures.
 */
struct	ip6q {
	uint32_t	ip6q_head;
	uint16_t	ip6q_len;
	uint8_t		ip6q_nxt;	/* ip6f_nxt in first fragment */
	uint8_t		ip6q_hlim;
	struct ip6asfrag *ip6q_down;
	struct ip6asfrag *ip6q_up;
	uint32_t	ip6q_ident;
	uint8_t		ip6q_arrive;
	uint8_t		ip6q_ttl;
	struct in6_addr	ip6q_src, ip6q_dst;
	struct ip6q	*ip6q_next;
	struct ip6q	*ip6q_prev;
	int		ip6q_unfrglen;	/* len of unfragmentable part */
#ifdef notyet
	u_char		*ip6q_nxtp;
#endif
	int		ip6q_nfrag;	/* # of fragments */
};

struct	ip6asfrag {
	uint32_t	ip6af_head;
	uint16_t	ip6af_len;
	uint8_t		ip6af_nxt;
	uint8_t		ip6af_hlim;
	/* must not override the above members during reassembling */
	struct ip6asfrag *ip6af_down;
	struct ip6asfrag *ip6af_up;
	struct mbuf	*ip6af_m;
	int		ip6af_offset;	/* offset in ip6af_m to next header */
	int		ip6af_frglen;	/* fragmentable part length */
	int		ip6af_off;	/* fragment offset */
	uint16_t	ip6af_mff;	/* more fragment bit in frag off */
};

#define IP6_REASS_MBUF(ip6af) ((ip6af)->ip6af_m)

struct	ip6_moptions {
	struct	ifnet *im6o_multicast_ifp; /* ifp for outgoing multicasts */
	u_char	im6o_multicast_hlim;	/* hoplimit for outgoing multicasts */
	u_char	im6o_multicast_loop;	/* 1 >= hear sends if a member */
	LIST_HEAD(, in6_multi_mship) im6o_memberships;
};

/*
 * Control options for outgoing packets
 */

/* Routing header related info */
struct	ip6po_rhinfo {
	struct	ip6_rthdr *ip6po_rhi_rthdr; /* Routing header */
	struct	route_in6 ip6po_rhi_route; /* Route to the 1st hop */
};
#define ip6po_rthdr	ip6po_rhinfo.ip6po_rhi_rthdr
#define ip6po_route	ip6po_rhinfo.ip6po_rhi_route

/* Nexthop related info */
struct	ip6po_nhinfo {
	struct	sockaddr *ip6po_nhi_nexthop;
	struct	route_in6 ip6po_nhi_route; /* Route to the nexthop */
};
#define ip6po_nexthop	ip6po_nhinfo.ip6po_nhi_nexthop
#define ip6po_nextroute	ip6po_nhinfo.ip6po_nhi_route

struct	ip6_pktopts {
	struct	mbuf *ip6po_m;	/* Pointer to mbuf storing the data */
	int	ip6po_hlim;		/* Hoplimit for outgoing packets */
	struct	in6_pktinfo *ip6po_pktinfo; /* Outgoing IF/address information */
	struct	ip6po_nhinfo ip6po_nhinfo; /* Next-hop address information */
	struct	ip6_hbh *ip6po_hbh; /* Hop-by-Hop options header */
	struct	ip6_dest *ip6po_dest1; /* Destination options header(1st part) */
	struct	ip6po_rhinfo ip6po_rhinfo; /* Routing header related info. */
	struct	ip6_dest *ip6po_dest2; /* Destination options header(2nd part) */
	int	ip6po_tclass;	/* traffic class */
	int	ip6po_minmtu;  /* fragment vs PMTU discovery policy */
#define IP6PO_MINMTU_MCASTONLY	-1 /* default; send at min MTU for multicast*/
#define IP6PO_MINMTU_DISABLE	 0 /* always perform pmtu disc */
#define IP6PO_MINMTU_ALL	 1 /* always send at min MTU */

#ifdef __QNXNTO__
	int ip6po_prefer_tempaddr; /* whether temporary addresses are
								  preferred as source address */
#define IP6PO_TEMPADDR_SYSTEM   -1 /* follow the system default */
#define IP6PO_TEMPADDR_NOTPREFER 0 /* not prefer temporary address */
#define IP6PO_TEMPADDR_PREFER    1 /* prefer temporary address */
#endif

	int ip6po_flags;
#if 0	/* parameters in this block is obsolete. do not reuse the values. */
#define IP6PO_REACHCONF	0x01	/* upper-layer reachability confirmation. */
#define IP6PO_MINMTU	0x02	/* use minimum MTU (IPV6_USE_MIN_MTU) */
#endif
#define IP6PO_DONTFRAG	0x04	/* disable fragmentation (IPV6_DONTFRAG) */
};

struct	ip6stat {
	uint64_t ip6s_total;		/* total packets received */
	uint64_t ip6s_tooshort;		/* packet too short */
	uint64_t ip6s_toosmall;		/* not enough data */
	uint64_t ip6s_fragments;	/* fragments received */
	uint64_t ip6s_fragdropped;	/* frags dropped(dups, out of space) */
	uint64_t ip6s_fragtimeout;	/* fragments timed out */
	uint64_t ip6s_fragoverflow;	/* fragments that exceeded limit */
	uint64_t ip6s_forward;		/* packets forwarded */
	uint64_t ip6s_cantforward;	/* packets rcvd for unreachable dest */
	uint64_t ip6s_redirectsent;	/* packets forwarded on same net */
	uint64_t ip6s_delivered;	/* datagrams delivered to upper level*/
	uint64_t ip6s_localout;		/* total ip packets generated here */
	uint64_t ip6s_odropped;		/* lost packets due to nobufs, etc. */
	uint64_t ip6s_reassembled;	/* total packets reassembled ok */
	uint64_t ip6s_fragmented;	/* datagrams successfully fragmented */
	uint64_t ip6s_ofragments;	/* output fragments created */
	uint64_t ip6s_cantfrag;		/* don't fragment flag was set, etc. */
	uint64_t ip6s_badoptions;	/* error in option processing */
	uint64_t ip6s_noroute;		/* packets discarded due to no route */
	uint64_t ip6s_badvers;		/* ip6 version != 6 */
	uint64_t ip6s_rawout;		/* total raw ip packets generated */
	uint64_t ip6s_badscope;		/* scope error */
	uint64_t ip6s_notmember;	/* don't join this multicast group */
	uint64_t ip6s_nxthist[256];	/* next header history */
	uint64_t ip6s_m1;		/* one mbuf */
	uint64_t ip6s_m2m[32];		/* two or more mbuf */
	uint64_t ip6s_mext1;		/* one ext mbuf */
	uint64_t ip6s_mext2m;		/* two or more ext mbuf */
	uint64_t ip6s_exthdrtoolong;	/* ext hdr are not continuous */
	uint64_t ip6s_nogif;		/* no match gif found */
	uint64_t ip6s_toomanyhdr;	/* discarded due to too many headers */

	/*
	 * statistics for improvement of the source address selection
	 * algorithm:
	 * XXX: hardcoded 16 = # of ip6 multicast scope types + 1
	 */
	/* number of times that address selection fails */
	uint64_t ip6s_sources_none;
	/* number of times that an address on the outgoing I/F is chosen */
	uint64_t ip6s_sources_sameif[16];
	/* number of times that an address on a non-outgoing I/F is chosen */
	uint64_t ip6s_sources_otherif[16];
	/*
	 * number of times that an address that has the same scope
	 * from the destination is chosen.
	 */
	uint64_t ip6s_sources_samescope[16];
	/*
	 * number of times that an address that has a different scope
	 * from the destination is chosen.
	 */
	uint64_t ip6s_sources_otherscope[16];
	/* number of times that an deprecated address is chosen */
	uint64_t ip6s_sources_deprecated[16];

	uint64_t ip6s_forward_cachehit;
	uint64_t ip6s_forward_cachemiss;
};

#ifdef _KERNEL
/*
 * Auxiliary attributes of incoming IPv6 packets, which is initialized when we
 * come into ip6_input().
 * XXX do not make it a kitchen sink!
 */
struct ip6aux {
	/* ip6.ip6_dst */
	struct in6_ifaddr *ip6a_dstia6;	/* my ifaddr that matches ip6_dst */
};

/* flags passed to ip6_output as last parameter */
#define	IPV6_UNSPECSRC		0x01	/* allow :: as the source address */
#define	IPV6_FORWARDING		0x02	/* most of IPv6 header exists */
#define	IPV6_MINMTU		0x04	/* use minimum MTU (IPV6_USE_MIN_MTU) */

#ifdef __NO_STRICT_ALIGNMENT
#define	IP6_HDR_ALIGNED_P(ip)	1
#else
#define	IP6_HDR_ALIGNED_P(ip)	((((vaddr_t) (ip)) & 3) == 0)
#endif

extern struct	ip6stat ip6stat;	/* statistics */
extern uint32_t ip6_id;		/* fragment identifier */
extern int	ip6_defhlim;		/* default hop limit */
extern int	ip6_defmcasthlim;	/* default multicast hop limit */
extern int	ip6_forwarding;		/* act as router? */
#ifdef QNX_MFIB
extern int	ip6_forwarding_mfibmask; /* act as a router on these fibs */
#endif
extern int	ip6_sendredirect;	/* send ICMPv6 redirect? */
extern int	ip6_forward_srcrt;	/* forward src-routed? */
extern int	ip6_use_deprecated;	/* allow deprecated addr as source */
extern int	ip6_rr_prune;		/* router renumbering prefix
					 * walk list every 5 sec.    */
extern int	ip6_mcast_pmtu;		/* enable pMTU discovery for multicast? */
extern int	ip6_v6only;

extern struct socket *ip6_mrouter; 	/* multicast routing daemon */
extern int	ip6_sendredirects;	/* send IP redirects when forwarding? */
extern int	ip6_maxfragpackets; /* Maximum packets in reassembly queue */
extern int	ip6_maxfrags;	/* Maximum fragments in reassembly queue */
extern int	ip6_sourcecheck;	/* Verify source interface */
extern int	ip6_sourcecheck_interval; /* Interval between log messages */
extern int	ip6_accept_rtadv;	/* Acts as a host not a router */
extern int	ip6_keepfaith;		/* Firewall Aided Internet Translator */
extern int	ip6_log_interval;
extern time_t	ip6_log_time;
extern int	ip6_hdrnestlimit; /* upper limit of # of extension headers */
extern int	ip6_dad_count;		/* DupAddrDetectionTransmits */
#ifdef __QNXNTO__
#define DAD_COUNT_GLOBAL -1
#endif

extern int ip6_auto_flowlabel;
extern int ip6_auto_linklocal;

extern int   ip6_anonportmin;		/* minimum ephemeral port */
extern int   ip6_anonportmax;		/* maximum ephemeral port */
extern int   ip6_lowportmin;		/* minimum reserved port */
extern int   ip6_lowportmax;		/* maximum reserved port */

extern int	ip6_use_tempaddr; /* whether to use temporary addresses. */
extern int	ip6_prefer_tempaddr; /* whether to prefer temporary addresses
					in the source address selection */
extern int	ip6_use_defzone; /* whether to use the default scope zone
				    when unspecified */

#ifdef __QNXNTO__
extern int	ip_bindinterface;
#endif

struct in6pcb;

int	icmp6_ctloutput(int, struct socket *, int, int, struct mbuf **);
extern int	ip6_rht0;		/* processing routing header type 0 */

void	ip6_init(void);
void	ip6intr(void);
void	ip6_input(struct mbuf *);
struct in6_ifaddr *ip6_getdstifaddr(struct mbuf *);
void	ip6_freepcbopts(struct ip6_pktopts *);
void	ip6_freemoptions(struct ip6_moptions *);
int	ip6_unknown_opt(uint8_t *, struct mbuf *, int);
uint8_t *ip6_get_prevhdr(struct mbuf *, int);
int	ip6_nexthdr(struct mbuf *, int, int, int *);
int	ip6_lasthdr(struct mbuf *, int, int, int *);

struct m_tag *ip6_addaux(struct mbuf *);
struct m_tag *ip6_findaux(struct mbuf *);
void	ip6_delaux(struct mbuf *);

int	ip6_mforward(struct ip6_hdr *, struct ifnet *, struct mbuf *);
int	ip6_hopopts_input(u_int32_t *, u_int32_t *, struct mbuf **, int *);
void	ip6_savecontrol(struct in6pcb *, struct mbuf **, struct ip6_hdr *,
		struct mbuf *);
void	ip6_notify_pmtu(struct in6pcb *, const struct sockaddr_in6 *,
		u_int32_t *);
int	ip6_sysctl(int *, u_int, void *, size_t *, void *, size_t);

void	ip6_forward(struct mbuf *, int);

void	ip6_mloopback(struct ifnet *, struct mbuf *,
	              const struct sockaddr_in6 *);
#ifndef __QNXNTO__
int	ip6_output(struct mbuf *, struct ip6_pktopts *,
			struct route_in6 *, int,
			struct ip6_moptions *, struct socket *,
			struct ifnet **);
#else
#ifndef QNX_MFIB
int	ip6_output(struct mbuf *, struct ip6_pktopts *,
			struct route_in6 *, int,
			struct ip6_moptions *, struct socket *,
			struct ifnet **, struct ifnet *, struct ifnet *);
#else
int	ip6_output(struct mbuf *, struct ip6_pktopts *,
			struct route_in6 *, int,
			struct ip6_moptions *, struct socket *,
			struct ifnet **, struct ifnet *, struct ifnet *, int);
#endif
#endif
int	ip6_ctloutput(int, struct socket *, int, int, struct mbuf **);
int	ip6_raw_ctloutput(int, struct socket *, int, int, struct mbuf **);
void	ip6_initpktopts(struct ip6_pktopts *);
int	ip6_setpktopts(struct mbuf *, struct ip6_pktopts *,
			    struct ip6_pktopts *, kauth_cred_t, int);
void	ip6_clearpktopts(struct ip6_pktopts *, int);
struct ip6_pktopts *ip6_copypktopts(struct ip6_pktopts *, int);
int	ip6_optlen(struct in6pcb *);

int	route6_input(struct mbuf **, int *, int);

void	frag6_init(void);
int	frag6_input(struct mbuf **, int *, int);
#ifndef __QNXNTO__
void	frag6_slowtimo(void);
#else
int	frag6_slowtimo(void);
#endif
void	frag6_drain(void);

void	rip6_init(void);
int	rip6_input(struct mbuf **, int *, int);
void	*rip6_ctlinput(int, const struct sockaddr *, void *);
int	rip6_ctloutput(int, struct socket *, int, int, struct mbuf **);
int	rip6_output(struct mbuf *, ...);
int	rip6_usrreq(struct socket *,
	    int, struct mbuf *, struct mbuf *, struct mbuf *, struct lwp *);

int	dest6_input(struct mbuf **, int *, int);
int	none_input(struct mbuf **, int *, int);

#ifndef __QNXNTO__
struct 	in6_addr *in6_selectsrc(struct sockaddr_in6 *,
	struct ip6_pktopts *, struct ip6_moptions *, struct route_in6 *,
	struct in6_addr *, struct ifnet **, int *);
int in6_selectroute(struct sockaddr_in6 *, struct ip6_pktopts *,
	struct ip6_moptions *, struct route_in6 *, struct ifnet **,
	struct rtentry **, int);
#else
#ifndef QNX_MFIB
struct 	in6_addr *in6_selectsrc(struct sockaddr_in6 *,
	struct ip6_pktopts *, struct ip6_moptions *, struct route_in6 *,
	struct in6_addr *, struct ifnet **, int *, struct ifnet *);
int in6_selectroute(struct sockaddr_in6 *, struct ip6_pktopts *,
	struct ip6_moptions *, struct route_in6 *, struct ifnet **,
	struct rtentry **, int, struct ifnet *);
#else
struct 	in6_addr *in6_selectsrc(struct sockaddr_in6 *,
	struct ip6_pktopts *, struct ip6_moptions *, struct route_in6 *,
	struct in6_addr *, struct ifnet **, int *, struct ifnet *, int);
int in6_selectroute(struct sockaddr_in6 *, struct ip6_pktopts *,
	struct ip6_moptions *, struct route_in6 *, struct ifnet **,
	struct rtentry **, int, struct ifnet *, int);
#endif
#endif

uint32_t ip6_randomid(void);
uint32_t ip6_randomflowlabel(void);

#ifdef __QNXNTO__
#ifndef QNX_MFIB
#define IP6FORWARDING(ifp)    (ip6_forwarding || (ifp && ((ifp->if_flags & IFF_IP6FORWARDING))))
#else
#define IP6FORWARDING(ifp)    (ip6_forwarding || (ifp && ((ifp->if_flags & IFF_IP6FORWARDING) || ((ip6_forwarding_mfibmask & ifp->if_fibmask) != 0))))
#define IP6FORWARD_FIB(ifp, fib)    (ip6_forwarding || ((ifp) && (((ifp)->if_flags & IFF_IP6FORWARDING) || ((ip6_forwarding_mfibmask & (1<<((fib)))) != 0))))
#endif
#endif /* __QNXNTO__ */

#endif /* _KERNEL */

#endif /* !_NETINET6_IP6_VAR_H_INCLUDED */

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/socket/public/netinet6/ip6_var.h $ $Rev: 744412 $" )
