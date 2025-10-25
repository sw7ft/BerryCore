/*	$NetBSD: icmp_var.h,v 1.25 2005/12/10 23:36:23 elad Exp $	*/

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
 *	@(#)icmp_var.h	8.1 (Berkeley) 6/10/93
 */

#ifndef _NETINET_ICMP_VAR_H_INCLUDED
#define _NETINET_ICMP_VAR_H_INCLUDED

#ifndef _INTTYPES_H_INCLUDED
#include <inttypes.h>
#endif

#ifndef _NETINET_IP_ICMP_H_INCLUDED
#include <netinet/ip_icmp.h>
#endif

/*
 * Variables related to this implementation
 * of the internet control message protocol.
 */
struct	icmpstat {
/* statistics related to icmp packets generated */
	uint64_t icps_error;		/* # of calls to icmp_error */
	uint64_t icps_oldshort;		/* no error 'cuz old ip too short */
	uint64_t icps_oldicmp;		/* no error 'cuz old was icmp */
	uint64_t icps_outhist[ICMP_MAXTYPE + 1];
/* statistics related to input messages processed */
 	uint64_t icps_badcode;		/* icmp_code out of range */
	uint64_t icps_tooshort;		/* packet < ICMP_MINLEN */
	uint64_t icps_checksum;		/* bad checksum */
	uint64_t icps_badlen;		/* calculated bound mismatch */
	uint64_t icps_reflect;		/* number of responses */
	uint64_t icps_inhist[ICMP_MAXTYPE + 1];
	uint64_t icps_pmtuchg;		/* path MTU changes */
};

/*
 * Names for ICMP sysctl objects
 */
#define	ICMPCTL_MASKREPL	1	/* allow replies to netmask requests */
#if 0	/*obsoleted*/
#define ICMPCTL_ERRRATELIMIT	2	/* error rate limit */
#endif
#define ICMPCTL_RETURNDATABYTES	3	/* # of bytes to include in errors */
#define ICMPCTL_ERRPPSLIMIT	4	/* ICMP error pps limitation */
#define ICMPCTL_REDIRACCEPT	5	/* Accept redirects from routers */
#define ICMPCTL_REDIRTIMEOUT	6	/* Remove routes added via redirects */
#define ICMPCTL_TSTAMPREPL	7	/* allow replies to timestamp requests */
#define	ICMPCTL_STATS		8	/* ICMP statistics */
#define ICMPCTL_MAXID		9

#define ICMPCTL_NAMES { \
	{ 0, 0 }, \
	{ "maskrepl", CTLTYPE_INT }, \
	{ 0, 0 }, \
	{ "returndatabytes", CTLTYPE_INT }, \
	{ "errppslimit", CTLTYPE_INT }, \
	{ "rediraccept", CTLTYPE_INT }, \
	{ "redirtimeout", CTLTYPE_INT }, \
	{ "tstamprepl", CTLTYPE_INT }, \
	{ "stats", CTLTYPE_STRUCT }, \
}

#ifdef _KERNEL
extern struct	icmpstat icmpstat;

#ifdef __NO_STRICT_ALIGNMENT
#define	ICMP_HDR_ALIGNED_P(ic)	1
#else
#define	ICMP_HDR_ALIGNED_P(ic)	((((vaddr_t) (ic)) & 3) == 0)
#endif
#endif /* _KERNEL_ */

#endif /* !_NETINET_ICMP_VAR_H_INCLUDED */

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/socket/public/netinet/icmp_var.h $ $Rev: 233581 $" )
