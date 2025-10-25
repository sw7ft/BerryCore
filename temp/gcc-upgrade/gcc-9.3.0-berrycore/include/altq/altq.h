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

/*	$NetBSD: altq.h,v 1.4 2006/10/12 19:59:08 peter Exp $ */
/*	$KAME: altq.h,v 1.10 2003/07/10 12:07:47 kjc Exp $	*/

/*
 * Copyright (C) 1998-2003
 *	Sony Computer Science Laboratories Inc.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY SONY CSL AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL SONY CSL OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#ifndef _ALTQ_ALTQ_H_INCLUDED
#define	_ALTQ_ALTQ_H_INCLUDED

#if 1
/*
 * allow altq-3 (altqd(8) and /dev/altq) to coexist with the new pf-based altq.
 * altq3 is mainly for research experiments. pf-based altq is for daily use.
 */
#define ALTQ3_COMPAT		/* for compatibility with altq-3 */
#define ALTQ3_CLFIER_COMPAT	/* for compatibility with altq-3 classifier */
#endif

#ifdef ALTQ3_COMPAT
#ifndef __TYPES_H_INCLUDED
#include <sys/types.h>
#endif

#include <sys/param.h>
#ifndef __QNXNTO__
#include <sys/ioccom.h>
#else
#include <net/if.h>
#endif
#include <sys/queue.h>
#include <netinet/in.h>

#ifndef IFNAMSIZ
#define	IFNAMSIZ	16
#endif
#endif /* ALTQ3_COMPAT */

/* altq discipline type */
#define	ALTQT_NONE		0	/* reserved */
#define	ALTQT_CBQ		1	/* cbq */
#define	ALTQT_WFQ		2	/* wfq */
#define	ALTQT_AFMAP		3	/* afmap */
#define	ALTQT_FIFOQ		4	/* fifoq */
#define	ALTQT_RED		5	/* red */
#define	ALTQT_RIO		6	/* rio */
#define	ALTQT_LOCALQ		7	/* local use */
#define	ALTQT_HFSC		8	/* hfsc */
#define	ALTQT_CDNR		9	/* traffic conditioner */
#define	ALTQT_BLUE		10	/* blue */
#define	ALTQT_PRIQ		11	/* priority queue */
#define	ALTQT_JOBS		12	/* JoBS */
#define	ALTQT_MAX		13	/* should be max discipline type + 1 */

#ifdef ALTQ3_COMPAT
struct	altqreq {
	char	ifname[IFNAMSIZ];	/* if name, e.g. "en0" */
	u_long	arg;			/* request-specific argument */
};
#endif

/* simple token backet meter profile */
struct	tb_profile {
	u_int	rate;	/* rate in bit-per-sec */
	u_int	depth;	/* depth in bytes */
};

#ifdef ALTQ3_COMPAT
struct	tbrreq {
	char	ifname[IFNAMSIZ];	/* if name, e.g. "en0" */
	struct	tb_profile tb_prof;	/* token bucket profile */
};

#ifdef ALTQ3_CLFIER_COMPAT
/*
 * common network flow info structure
 */
struct flowinfo {
	u_char		fi_len;		/* total length */
	u_char		fi_family;	/* address family */
	uint8_t		fi_data[46];	/* actually longer; address family
					   specific flow info. */
};

/*
 * flow info structure for internet protocol family.
 * (currently this is the only protocol family supported)
 */
struct flowinfo_in {
	u_char		fi_len;		/* sizeof(struct flowinfo_in) */
	u_char		fi_family;	/* AF_INET */
	uint8_t		fi_proto;	/* IPPROTO_XXX */
	uint8_t		fi_tos;		/* type-of-service */
	struct in_addr	fi_dst;		/* dest address */
	struct in_addr	fi_src;		/* src address */
	uint16_t	fi_dport;	/* dest port */
	uint16_t	fi_sport;	/* src port */
	uint32_t	fi_gpi;		/* generalized port id for ipsec */
	uint8_t		_pad[28];	/* make the size equal to
					   flowinfo_in6 */
};

#ifdef SIN6_LEN
struct flowinfo_in6 {
	u_char		fi6_len;	/* sizeof(struct flowinfo_in6) */
	u_char		fi6_family;	/* AF_INET6 */
	uint8_t		fi6_proto;	/* IPPROTO_XXX */
	uint8_t		fi6_tclass;	/* traffic class */
	uint32_t	fi6_flowlabel;	/* ipv6 flowlabel */
	uint16_t	fi6_dport;	/* dest port */
	uint16_t	fi6_sport;	/* src port */
	uint32_t	fi6_gpi;	/* generalized port id */
	struct in6_addr fi6_dst;	/* dest address */
	struct in6_addr fi6_src;	/* src address */
};
#endif /* INET6 */

/*
 * flow filters for AF_INET and AF_INET6
 */
struct flow_filter {
	int			ff_ruleno;
	struct flowinfo_in	ff_flow;
	struct {
		struct in_addr	mask_dst;
		struct in_addr	mask_src;
		uint8_t		mask_tos;
		uint8_t		_pad[3];
	} ff_mask;
	uint8_t	 _pad2[24];	/* make the size equal to flow_filter6 */
};

#ifdef SIN6_LEN
struct flow_filter6 {
	int			ff_ruleno;
	struct flowinfo_in6	ff_flow6;
	struct {
		struct in6_addr	mask6_dst;
		struct in6_addr	mask6_src;
		uint8_t		mask6_tclass;
		uint8_t		_pad[3];
	} ff_mask6;
};
#endif /* INET6 */
#endif /* ALTQ3_CLFIER_COMPAT */
#endif /* ALTQ3_COMPAT */

/*
 * generic packet counter
 */
struct pktcntr {
	uint64_t	packets;
	uint64_t	bytes;
};

#define	PKTCNTR_ADD(cntr, len)	\
	do { (cntr)->packets++; (cntr)->bytes += len; } while (/*CONSTCOND*/ 0)

#ifdef ALTQ3_COMPAT
/*
 * altq related ioctls
 */
#define	ALTQGTYPE	_IOWR('q', 0, struct altqreq)	/* get queue type */
#if 0
/*
 * these ioctls are currently discipline-specific but could be shared
 * in the future.
 */
#define	ALTQATTACH	_IOW('q', 1, struct altqreq)	/* attach discipline */
#define	ALTQDETACH	_IOW('q', 2, struct altqreq)	/* detach discipline */
#define	ALTQENABLE	_IOW('q', 3, struct altqreq)	/* enable discipline */
#define	ALTQDISABLE	_IOW('q', 4, struct altqreq)	/* disable discipline*/
#define	ALTQCLEAR	_IOW('q', 5, struct altqreq)	/* (re)initialize */
#define	ALTQCONFIG	_IOWR('q', 6, struct altqreq)	/* set config params */
#define	ALTQADDCLASS	_IOWR('q', 7, struct altqreq)	/* add a class */
#define	ALTQMODCLASS	_IOWR('q', 8, struct altqreq)	/* modify a class */
#define	ALTQDELCLASS	_IOWR('q', 9, struct altqreq)	/* delete a class */
#define	ALTQADDFILTER	_IOWR('q', 10, struct altqreq)	/* add a filter */
#define	ALTQDELFILTER	_IOWR('q', 11, struct altqreq)	/* delete a filter */
#define	ALTQGETSTATS	_IOWR('q', 12, struct altqreq)	/* get statistics */
#define	ALTQGETCNTR	_IOWR('q', 13, struct altqreq)	/* get a pkt counter */
#endif /* 0 */
#define	ALTQTBRSET	_IOW('q', 14, struct tbrreq)	/* set tb regulator */
#define	ALTQTBRGET	_IOWR('q', 15, struct tbrreq)	/* get tb regulator */
#endif /* ALTQ3_COMPAT */

#ifdef _KERNEL
#include <altq/altq_var.h>
#endif

#endif /* _ALTQ_ALTQ_H_INCLUDED */

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/socket/public/altq/altq.h $ $Rev: 233581 $" )
