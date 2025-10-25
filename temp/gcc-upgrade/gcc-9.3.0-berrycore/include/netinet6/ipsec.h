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

/*	$NetBSD: ipsec.h,v 1.45 2005/12/10 23:39:56 elad Exp $	*/
/*	$KAME: ipsec.h,v 1.51 2001/08/05 04:52:58 itojun Exp $	*/

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
 * IPsec controller part.
 */

#ifndef _NETINET6_IPSEC_H_INCLUDED
#define _NETINET6_IPSEC_H_INCLUDED

#if defined(_KERNEL_OPT)
#include "opt_inet.h"
#endif

#ifndef __TYPES_H_INCLUDED
#include <sys/types.h>
#endif

#ifndef _INTTYPES_H_INCLUDED
#include <inttypes.h>
#endif

#ifndef _NET_PFKEYV2_H_INCLUDED
#include <net/pfkeyv2.h>
#endif

#ifndef _NETKEY_KEYDB_H_INCLUDED
#include <netkey/keydb.h>
#endif

#ifdef _KERNEL
#ifdef __QNXNTO__
extern int qnxnto_ipsec_enabled;
#endif

/*
 * Security Policy Index
 * NOTE: Ensure to be same address family and upper layer protocol.
 * NOTE: ul_proto, port number, uid, gid:
 *	ANY: reserved for waldcard.
 *	0 to (~0 - 1): is one of the number of each value.
 */
struct secpolicyindex {
	struct sockaddr_storage src;	/* IP src address for SP */
	struct sockaddr_storage dst;	/* IP dst address for SP */
	uint8_t prefs;			/* prefix length in bits for src */
	uint8_t prefd;			/* prefix length in bits for dst */
	uint16_t ul_proto;		/* upper layer Protocol */
#ifdef notyet
	uid_t uids;
	uid_t uidd;
	gid_t gids;
	gid_t gidd;
#endif
};

/* Security Policy Data Base */
struct secpolicy {
	TAILQ_ENTRY(secpolicy) tailq;	/* all SPD entries, both pcb/table */
	LIST_ENTRY(secpolicy) chain;	/* SPD entries on table */

	uint8_t dir;			/* direction of packet flow */
	int readonly;			/* write prohibited */
	int persist;			/* will never be removed */
	int refcnt;			/* reference count */
	struct secpolicyindex *spidx;	/* selector - NULL if not valid */
	uint16_t tag;			/* PF tag */
	uint32_t id;			/* it identifies a policy in the SPD. */
#define IPSEC_MANUAL_POLICYID_MAX	0x3fff
				/*
				 * 1 - 0x3fff are reserved for user operation.
				 * 0 are reserved.  Others are for kernel use.
				 */
	struct socket *so;		/* backpointer to per-socket policy */
	u_int state;			/* 0: dead, others: alive */
#define IPSEC_SPSTATE_DEAD	0
#define IPSEC_SPSTATE_ALIVE	1

	int policy;		/* DISCARD, NONE or IPSEC, see below */
	struct ipsecrequest *req;
				/* pointer to the ipsec request tree, */
				/* if policy == IPSEC else this value == NULL.*/

	/*
	 * lifetime handler.
	 * the policy can be used without limitiation if both lifetime and
	 * validtime are zero.
	 * "lifetime" is passed by sadb_lifetime.sadb_lifetime_addtime.
	 * "validtime" is passed by sadb_lifetime.sadb_lifetime_usetime.
	 */
	long created;		/* time created the policy */
	long lastused;		/* updated every when kernel sends a packet */
	long lifetime;		/* duration of the lifetime of this policy */
	long validtime;		/* duration this policy is valid without use */
#ifdef __QNXNTO__
	char if_inner[ IFNAMSIZ ];
	char if_outer[ IFNAMSIZ ];
	struct ifnet *ifn_inner;
	struct ifnet *ifn_outer;
#endif
};

/* Request for IPsec */
struct ipsecrequest {
	struct ipsecrequest *next;
				/* pointer to next structure */
				/* If NULL, it means the end of chain. */
	struct secasindex saidx;/* hint for search proper SA */
				/* if __ss_len == 0 then no address specified.*/
	u_int level;		/* IPsec level defined below. */

	struct secasvar *sav;	/* place holder of SA for use */
	struct secpolicy *sp;	/* back pointer to SP */
};

/* security policy in PCB */
struct inpcbpolicy {
	struct secpolicy *sp_in;
	struct secpolicy *sp_out;
	int priv;			/* privileged socket ? */

	/* cached policy */
	struct {
		struct secpolicy *cachesp;
		struct secpolicyindex cacheidx;
		int cachehint;		/* processing requirement hint: */
#define	IPSEC_PCBHINT_MAYBE	0	/* IPsec processing maybe required */
#define	IPSEC_PCBHINT_YES	1	/* IPsec processing is required */
#define	IPSEC_PCBHINT_NO	2	/* IPsec processing not required */
		u_int cachegen;		/* spdgen when cache filled */
	} sp_cache[3];			/* XXX 3 == IPSEC_DIR_MAX */
	int sp_cacheflags;
#define IPSEC_PCBSP_CONNECTED	1
};

#define	IPSEC_PCB_SKIP_IPSEC(inpp, dir)					\
	((inpp)->sp_cache[(dir)].cachehint == IPSEC_PCBHINT_NO &&	\
	 (inpp)->sp_cache[(dir)].cachegen == ipsec_spdgen)

/* SP acquiring list table. */
struct secspacq {
	LIST_ENTRY(secspacq) chain;

	struct secpolicyindex spidx;

	long created;		/* for lifetime */
	int count;		/* for lifetime */
	/* XXX: here is mbuf place holder to be sent ? */
};

struct ipsecaux {
	struct socket *so;
	int hdrs;	/* # of ipsec headers */

	struct secpolicy *sp;
	struct ipsecrequest *req;
};
#endif /* _KERNEL */

/* according to IANA assignment, port 0x0000 and proto 0xff are reserved. */
#define IPSEC_PORT_ANY		0
#define IPSEC_ULPROTO_ANY	255
#define IPSEC_PROTO_ANY		255

/* mode of security protocol */
/* NOTE: DON'T use IPSEC_MODE_ANY at SPD.  It's only use in SAD */
#define	IPSEC_MODE_ANY		0	/* i.e. wildcard. */
#define	IPSEC_MODE_TRANSPORT	1
#define	IPSEC_MODE_TUNNEL	2

/*
 * Direction of security policy.
 * NOTE: Since INVALID is used just as flag.
 * The other are used for loop counter too.
 */
#define IPSEC_DIR_ANY		0
#define IPSEC_DIR_INBOUND	1
#define IPSEC_DIR_OUTBOUND	2
#define IPSEC_DIR_MAX		3
#define IPSEC_DIR_INVALID	4

/* Policy level */
/*
 * IPSEC, ENTRUST and BYPASS are allowed for setsockopt() in PCB,
 * DISCARD, IPSEC and NONE are allowed for setkey() in SPD.
 * DISCARD and NONE are allowed for system default.
 */
#define IPSEC_POLICY_DISCARD	0	/* discarding packet */
#define IPSEC_POLICY_NONE	1	/* through IPsec engine */
#define IPSEC_POLICY_IPSEC	2	/* do IPsec */
#define IPSEC_POLICY_ENTRUST	3	/* consulting SPD if present. */
#define IPSEC_POLICY_BYPASS	4	/* only for privileged socket. */

/* Security protocol level */
#define	IPSEC_LEVEL_DEFAULT	0	/* reference to system default */
#define	IPSEC_LEVEL_USE		1	/* use SA if present. */
#define	IPSEC_LEVEL_REQUIRE	2	/* require SA. */
#define	IPSEC_LEVEL_UNIQUE	3	/* unique SA. */

#define IPSEC_MANUAL_REQID_MAX	0x3fff
				/*
				 * if security policy level == unique, this id
				 * indicate to a relative SA for use, else is
				 * zero.
				 * 1 - 0x3fff are reserved for manual keying.
				 * 0 are reserved for above reason.  Others is
				 * for kernel use.
				 * Note that this id doesn't identify SA
				 * by only itself.
				 */
#define IPSEC_REPLAYWSIZE  32

/* statistics for ipsec processing */
struct ipsecstat {
	uint64_t in_success;  /* succeeded inbound process */
	uint64_t in_polvio;
			/* security policy violation for inbound process */
	uint64_t in_nosa;     /* inbound SA is unavailable */
	uint64_t in_inval;    /* inbound processing failed due to EINVAL */
	uint64_t in_nomem;    /* inbound processing failed due to ENOBUFS */
	uint64_t in_badspi;   /* failed getting a SPI */
	uint64_t in_ahreplay; /* AH replay check failed */
	uint64_t in_espreplay; /* ESP replay check failed */
	uint64_t in_ahauthsucc; /* AH authentication success */
	uint64_t in_ahauthfail; /* AH authentication failure */
	uint64_t in_espauthsucc; /* ESP authentication success */
	uint64_t in_espauthfail; /* ESP authentication failure */
	uint64_t in_esphist[256];
	uint64_t in_ahhist[256];
	uint64_t in_comphist[256];
	uint64_t out_success; /* succeeded outbound process */
	uint64_t out_polvio;
			/* security policy violation for outbound process */
	uint64_t out_nosa;    /* outbound SA is unavailable */
	uint64_t out_inval;   /* outbound process failed due to EINVAL */
	uint64_t out_nomem;    /* inbound processing failed due to ENOBUFS */
	uint64_t out_noroute; /* there is no route */
	uint64_t out_esphist[256];
	uint64_t out_ahhist[256];
	uint64_t out_comphist[256];

	uint64_t spdcachelookup;
	uint64_t spdcachemiss;
};

/*
 * Definitions for IPsec & Key sysctl operations.
 */
/*
 * Names for IPsec & Key sysctl objects
 */
#define IPSECCTL_STATS			1	/* stats */
#define IPSECCTL_DEF_POLICY		2
#define IPSECCTL_DEF_ESP_TRANSLEV	3	/* int; ESP transport mode */
#define IPSECCTL_DEF_ESP_NETLEV		4	/* int; ESP tunnel mode */
#define IPSECCTL_DEF_AH_TRANSLEV	5	/* int; AH transport mode */
#define IPSECCTL_DEF_AH_NETLEV		6	/* int; AH tunnel mode */
#if 0	/* obsolete, do not reuse */
#define IPSECCTL_INBOUND_CALL_IKE	7
#endif
#define	IPSECCTL_AH_CLEARTOS		8
#define	IPSECCTL_AH_OFFSETMASK		9
#define	IPSECCTL_DFBIT			10
#define	IPSECCTL_ECN			11
#define	IPSECCTL_DEBUG			12
#define IPSECCTL_MAXID			13

#define IPSECCTL_NAMES { \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ "def_policy", CTLTYPE_INT }, \
	{ "esp_trans_deflev", CTLTYPE_INT }, \
	{ "esp_net_deflev", CTLTYPE_INT }, \
	{ "ah_trans_deflev", CTLTYPE_INT }, \
	{ "ah_net_deflev", CTLTYPE_INT }, \
	{ 0, 0 }, \
	{ "ah_cleartos", CTLTYPE_INT }, \
	{ "ah_offsetmask", CTLTYPE_INT }, \
	{ "dfbit", CTLTYPE_INT }, \
	{ "ecn", CTLTYPE_INT }, \
	{ "debug", CTLTYPE_INT }, \
}

#define IPSEC6CTL_NAMES { \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ "def_policy", CTLTYPE_INT }, \
	{ "esp_trans_deflev", CTLTYPE_INT }, \
	{ "esp_net_deflev", CTLTYPE_INT }, \
	{ "ah_trans_deflev", CTLTYPE_INT }, \
	{ "ah_net_deflev", CTLTYPE_INT }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ 0, 0 }, \
	{ "ecn", CTLTYPE_INT }, \
	{ "debug", CTLTYPE_INT }, \
}

#ifdef _KERNEL
struct ipsec_output_state {
	struct mbuf *m;
	struct route *ro;
	struct sockaddr *dst;
	int encap;
};

struct ipsec_history {
	int ih_proto;
	uint32_t ih_spi;
};

extern int ipsec_debug;

#ifdef INET
extern struct ipsecstat ipsecstat;
extern struct secpolicy *ip4_def_policy;
extern int ip4_esp_trans_deflev;
extern int ip4_esp_net_deflev;
extern int ip4_ah_trans_deflev;
extern int ip4_ah_net_deflev;
extern int ip4_ah_cleartos;
extern int ip4_ah_offsetmask;
extern int ip4_ipsec_dfbit;
extern int ip4_ipsec_ecn;
#endif

#ifdef INET6
extern struct ipsecstat ipsec6stat;
extern struct secpolicy *ip6_def_policy;
extern int ip6_esp_trans_deflev;
extern int ip6_esp_net_deflev;
extern int ip6_ah_trans_deflev;
extern int ip6_ah_net_deflev;
extern int ip6_ipsec_ecn;
#endif

#define ipseclog(x)	do { if (ipsec_debug) log x; } while (/*CONSTCOND*/ 0)

extern int ipsec_pcbconn __P((struct inpcbpolicy *));
extern int ipsec_pcbdisconn __P((struct inpcbpolicy *));
extern void ipsec_invalpcbcacheall __P((void));

extern u_int ipsec_spdgen;

extern struct secpolicy *ipsec4_getpolicybysock
#ifndef __QNXNTO__
	__P((struct mbuf *, u_int, struct socket *, int *));
#else
__P((struct mbuf *, u_int, struct socket *, int *, struct ifnet *));
#endif
extern struct secpolicy *ipsec4_getpolicybyaddr
#ifndef __QNXNTO__
	__P((struct mbuf *, u_int, int, int *));
#else
	__P((struct mbuf *, u_int, int, int *, struct ifnet *));
#endif

#ifdef INET6
extern struct secpolicy *ipsec6_getpolicybysock
#ifndef __QNXNTO__
	__P((struct mbuf *, u_int, struct socket *, int *));
#else
	__P((struct mbuf *, u_int, struct socket *, int *, struct ifnet *));
#endif
extern struct secpolicy *ipsec6_getpolicybyaddr
#ifndef __QNXNTO__
	__P((struct mbuf *, u_int, int, int *));
#else
	__P((struct mbuf *, u_int, int, int *, struct ifnet *));
#endif
#endif /* INET6 */

struct inpcb;
#ifdef INET6
struct in6pcb;
#endif
extern int ipsec_init_pcbpolicy __P((struct socket *, struct inpcbpolicy **));
extern int ipsec_copy_pcbpolicy
	__P((struct inpcbpolicy *, struct inpcbpolicy *));
extern u_int ipsec_get_reqlevel __P((struct ipsecrequest *, int));

extern int ipsec4_set_policy __P((struct inpcb *, int, caddr_t, size_t, kauth_cred_t));
extern int ipsec4_get_policy __P((struct inpcb *, caddr_t, size_t,
	    struct mbuf **));
extern int ipsec4_delete_pcbpolicy __P((struct inpcb *));
extern int ipsec4_in_reject_so __P((struct mbuf *, struct socket *));
extern int ipsec4_in_reject __P((struct mbuf *, struct inpcb *));

#ifdef INET6
extern int ipsec6_in_reject_so __P((struct mbuf *, struct socket *));
extern int ipsec6_delete_pcbpolicy __P((struct in6pcb *));
extern int ipsec6_set_policy __P((struct in6pcb *, int, caddr_t, size_t, kauth_cred_t));
extern int ipsec6_get_policy __P((struct in6pcb *, caddr_t, size_t,
	    struct mbuf **));
extern int ipsec6_in_reject __P((struct mbuf *, struct in6pcb *));
#endif /* INET6 */

struct secas;
struct tcpcb;
struct tcp6cb;
extern int ipsec_chkreplay __P((uint32_t, struct secasvar *));
extern int ipsec_updatereplay __P((uint32_t, struct secasvar *));

extern size_t ipsec4_hdrsiz __P((struct mbuf *, u_int, struct inpcb *));
extern size_t ipsec4_hdrsiz_tcp __P((struct tcpcb *));
#ifdef INET6
extern size_t ipsec6_hdrsiz __P((struct mbuf *, u_int, struct in6pcb *));
extern size_t ipsec6_hdrsiz_tcp __P((struct tcpcb *));
#endif

struct ip;
#ifdef INET6
struct ip6_hdr;
#endif
extern const char *ipsec4_logpacketstr __P((struct ip *, uint32_t));
#ifdef INET6
extern const char *ipsec6_logpacketstr __P((struct ip6_hdr *, uint32_t));
#endif
extern const char *ipsec_logsastr __P((struct secasvar *));

extern void ipsec_dumpmbuf __P((struct mbuf *));

extern int ipsec4_output __P((struct ipsec_output_state *, struct secpolicy *,
	int));
#ifdef INET6
extern int ipsec6_output_trans __P((struct ipsec_output_state *, u_char *,
	struct mbuf *, struct secpolicy *, int, int *
#ifdef QNX_MFIB
	, int
#endif
));
extern int ipsec6_output_tunnel __P((struct ipsec_output_state *,
	struct secpolicy *, int));
#endif
extern int ipsec4_tunnel_validate __P((struct ip *, u_int, struct secasvar *));
#ifdef INET6
extern int ipsec6_tunnel_validate __P((struct ip6_hdr *, u_int,
	struct secasvar *));
#endif
extern struct mbuf *ipsec_copypkt __P((struct mbuf *));
extern void ipsec_delaux __P((struct mbuf *));
extern int ipsec_addhist __P((struct mbuf *, int, uint32_t));
extern int ipsec_getnhist __P((struct mbuf *));
extern struct ipsec_history *ipsec_gethist __P((struct mbuf *, int *));
extern void ipsec_clearhist __P((struct mbuf *));

extern int ipsec_sysctl __P((int *, u_int, void *, size_t *, void *, size_t));
extern int ipsec6_sysctl __P((int *, u_int, void *, size_t *, void *, size_t));

#endif /* _KERNEL */

#ifndef _KERNEL
__BEGIN_DECLS
typedef void *ipsec_policy_t;
extern ipsec_policy_t ipsec_set_policy __P((const char *, int));
extern int ipsec_get_policylen __P((ipsec_policy_t));
extern char *ipsec_dump_policy __P((ipsec_policy_t, const char *));

extern const char *ipsec_strerror __P((void));
__END_DECLS
#endif /* !_KERNEL */

#endif /* !_NETINET6_IPSEC_H_INCLUDED */

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/socket/public/netinet6/ipsec.h $ $Rev: 744412 $" )
