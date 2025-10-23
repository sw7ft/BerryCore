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

/*	$NetBSD: un.h,v 1.39 2006/07/23 22:06:14 ad Exp $	*/

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
 *	@(#)un.h	8.3 (Berkeley) 2/19/95
 */

#ifndef __UN_H_INCLUDED
#define __UN_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef _STDINT_H_INCLUDED
#include <stdint.h>
#endif

#if defined(__SA_FAMILY_T)
typedef __SA_FAMILY_T sa_family_t;
#undef __SA_FAMILY_T
#endif

#if defined(__PID_T)
typedef __PID_T         pid_t;
#undef __PID_T
#endif

#if defined(__UID_T)
typedef __UID_T         uid_t;
#undef __UID_T
#endif

#if defined(__GID_T)
typedef __GID_T         gid_t;
#undef __GID_T
#endif

/*
 * Definitions for UNIX IPC domain.
 */
struct	sockaddr_un {
	uint8_t		sun_len;	/* total sockaddr length */
	sa_family_t	sun_family;	/* AF_LOCAL */
	char		sun_path[104];	/* path name (gag) */
};

/*
 * Socket options for UNIX IPC domain.
 */
#if defined(__EXT_BSD)
#define	LOCAL_CREDS	0x0001		/* pass credentials to receiver */
#define	LOCAL_CONNWAIT	0x0002		/* connects block until accepted */
#define	LOCAL_PEEREID	0x0003		/* get peer identification */
#endif

/*
 * Data automatically stored inside connect() for use by LOCAL_PEEREID
 */
struct unpcbid {
	pid_t unp_pid;		/* process id */
	uid_t unp_euid;		/* effective user id */
	gid_t unp_egid;		/* effective group id */
};

#ifdef _KERNEL
struct unpcb;
struct socket;

int	uipc_usrreq(struct socket *, int, struct mbuf *,
	    struct mbuf *, struct mbuf *, struct lwp *);
int	uipc_ctloutput(int, struct socket *, int, int, struct mbuf **);

int	unp_attach (struct socket *);
int	unp_bind (struct unpcb *, struct mbuf *, struct lwp *);
int	unp_connect (struct socket *, struct mbuf *, struct lwp *);
int	unp_connect2 (struct socket *, struct socket *, int);
void	unp_detach (struct unpcb *);
void	unp_discard (io_dup_t  *);
void	unp_disconnect (struct unpcb *);
void	unp_drop (struct unpcb *, int);
void	unp_gc (void);
void	unp_mark (struct file *);
void	unp_scan (struct mbuf *, void (*)(io_dup_t *), int);
void	unp_shutdown (struct unpcb *);
int 	unp_externalize (struct mbuf *, struct lwp *, int);
int	unp_internalize (struct mbuf *, struct lwp *);
void 	unp_dispose (struct mbuf *);
int	unp_output (struct mbuf *, struct mbuf *, struct unpcb *,
	    struct lwp *);
void	unp_setsockaddr (struct unpcb *, struct mbuf *);
void	unp_setpeeraddr (struct unpcb *, struct mbuf *);
#ifdef __QNXNTO__
int	uipc_format(struct socket *, int, char *, int *);
int	uipc_path(struct socket *, char *, int);
#endif
#else /* !_KERNEL */

/* actual length of an initialized sockaddr_un */
#if defined(__EXT_BSD)
#define SUN_LEN(su) \
	(sizeof(*(su)) - sizeof((su)->sun_path) + strlen((su)->sun_path))
#endif /* !_XOPEN_SOURCE */
#endif /* _KERNEL */

#endif /* !__UN_H_INCLUDED */

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/socket/public/sys/un.h $ $Rev: 258726 $" )
