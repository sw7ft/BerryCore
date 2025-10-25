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

/*	$NetBSD: util.h,v 1.44 2006/11/20 20:33:33 christos Exp $	*/

/*-
 * Copyright (c) 1995
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
 */

#ifndef _NBUTIL_H_INCLUDED
#define	_NBUTIL_H_INCLUDED

#include <sys/platform.h>
#include <sys/cdefs.h>
#ifndef __QNXNTO__
#include <sys/ttycom.h>
#else
#include <stdarg.h>
#endif
#include <sys/types.h>
#include <stdio.h>
#include <pwd.h>
#include <termios.h>
#include <utmp.h>
#ifndef __QNXNTO__
#include <utmpx.h>
#include <machine/ansi.h>
#else
#include <sys/statvfs.h>
#include <inttypes.h>
#include <time.h>
#include <limits.h>
#endif

#ifndef __QNXNTO__
#define	PIDLOCK_NONBLOCK	1
#define	PIDLOCK_USEHOSTNAME	2
#endif

#define	HN_DECIMAL		0x01
#define	HN_NOSPACE		0x02
#define	HN_B			0x04
#define	HN_DIVISOR_1000		0x08

#define	HN_GETSCALE		0x10
#define	HN_AUTOSCALE		0x20

#ifdef __QNXNTO__
/*
 * From NetBSD's <stdio.h>. fparseln()
 * is in NetBSD's libc proper.
 */
#define	FPARSELN_UNESCESC	0x01
#define	FPARSELN_UNESCCONT	0x02
#define	FPARSELN_UNESCCOMM	0x04
#define	FPARSELN_UNESCREST	0x08
#define	FPARSELN_UNESCALL	0x0f
#endif

__BEGIN_DECLS
#ifndef __QNXNTO__
struct disklabel;
struct iovec;
struct passwd;
struct termios;
struct utmp;
struct winsize;
struct sockaddr;

typedef struct pw_policy *pw_policy_t; 

pid_t		forkpty(int *, char *, struct termios *, struct winsize *);
const char     *getbootfile(void);
off_t		getlabeloffset(void);
int		getlabelsector(void);
int		getmaxpartitions(void);
int		getrawpartition(void);
#endif
int		humanize_number(char *, size_t, int64_t, const char *, int,
		    int);
#ifndef __QNXNTO__
void		login(const struct utmp *);
void		loginx(const struct utmpx *);
#endif
int		login_tty(int);
#ifndef __QNXNTO__
int		logout(const char *);
int		logoutx(const char *, int, int);
void		logwtmp(const char *, const char *, const char *);
void		logwtmpx(const char *, const char *, const char *, int, int);
int		opendisk(const char *, int, char *, size_t, int);
int		openpty(int *, int *, char *, struct termios *,
		    struct winsize *);
time_t		parsedate(const char *, const time_t *, const int *);
#endif
int		pidfile(const char *);
#ifndef __QNXNTO__
int		pidlock(const char *, int, pid_t *, const char *);
int		pw_abort(void);
void		pw_copy(int, int, struct passwd *, struct passwd *);
int		pw_copyx(int, int, struct passwd *, struct passwd *,
			 char *, size_t);
void		pw_edit(int, const char *);
void		pw_error(const char *, int, int);
void		pw_getconf(char *, size_t, const char *, const char *);
void		pw_getpwconf(char *, size_t, const struct passwd *,
			     const char *);
const char     *pw_getprefix(void);
void		pw_init(void);
int		pw_lock(int);
int		pw_mkdb(const char *, int);
pw_policy_t	pw_policy_load(void *, int);
int		pw_policy_test(pw_policy_t, char *);
void		pw_policy_free(pw_policy_t);
void		pw_prompt(void);
int		pw_setprefix(const char *);
int		secure_path(const char *);
#endif
int		snprintb(char *, size_t, const char *, uint64_t);
#ifndef __QNXNTO__
int		sockaddr_snprintf(char *, size_t, const char *,
    const struct sockaddr *);
int		ttyaction(const char *, const char *, const char *);
int		ttylock(const char *, int, pid_t *);
char	       *ttymsg(struct iovec *, int, const char *, int);
int		ttyunlock(const char *);

uint16_t	disklabel_dkcksum(struct disklabel *);
int		disklabel_scan(struct disklabel *, char *, size_t);

/* Error checked functions */
void		(*esetfunc(void (*)(int, const char *, ...)))
    (int, const char *, ...);
#endif
size_t 		estrlcpy(char *, const char *, size_t);
size_t 		estrlcat(char *, const char *, size_t);
#ifndef __QNXNTO__
char 		*estrdup(const char *);
void 		*ecalloc(size_t, size_t);
void 		*emalloc(size_t);
void 		*erealloc(void *, size_t);
struct __sFILE	*efopen(const char *, const char *);
int	 	easprintf(char ** __restrict, const char * __restrict, ...)
    __attribute__((__format__(__printf__, 2, 3)));
int		evasprintf(char ** __restrict, const char * __restrict,
    _BSD_VA_LIST_)
    __attribute__((__format__(__printf__, 2, 0)));
#endif
#ifdef __QNXNTO__
/*
 * fgetln_r is currently specific to QNX
 * fgetln(), fparseln() and asprintf() are
 * in <stdio.h> under NetBSD (their libc
 * proper).
 */
char	*fgetln_r(FILE *, size_t *, char **, size_t *);
char	*fgetln __P((FILE * __restrict, size_t * __restrict));
char	*fparseln(FILE *, size_t *, size_t *, const char[3], int);
int	 asprintf __P((char ** __restrict, const char * __restrict, ...))
	    __attribute__((__format__(__printf__, 2, 3)));
int	 vasprintf __P((char ** __restrict, const char * __restrict,
	    va_list))
	    __attribute__((__format__(__printf__, 2, 0)));

/* In NetBSD's <stdlib.h> (libc proper) */
const char	*getprogname(void);
void		setprogname(const char *);

long long strsuftoll(const char *, const char *, long long, long long);
long long strsuftollx(const char *, const char *, long long, long long,
			char *, size_t);

/* In NetBSD's <unistd.h> (libc proper) */
char	*getusershell __P((void));
void	 endusershell __P((void));
void	 setusershell __P((void));

/* In NetBSD's time.h */
time_t timegm(struct tm *);

/*
 * From NetBSD's fnmatch.h
 * 
 * If both QNX fnmatch.h and this
 * file are included, should get redefinition
 * warnings.
 */
#define FNM_NOMATCH     1       /* Match failed. */
#define FNM_NOSYS       2       /* Function not implemented. */

#define	FNM_NOESCAPE	0x01	/* Disable backslash escaping. */
#define	FNM_PATHNAME	0x02	/* Slash must be matched by slash. */
#define	FNM_PERIOD	0x04	/* Period must be matched by period. */
#if defined(__EXT_BSD)
#define	FNM_CASEFOLD	0x08	/* Pattern is matched case-insensitive */
#define	FNM_LEADING_DIR	0x10	/* Ignore /<tail> after Imatch. */
#endif
int fnmatch_bsd(const char *, const char *, int);


/* NetBSD's string.h */
_CSTD size_t strlcpy(char *, const char *, _CSTD size_t);
_CSTD size_t strlcat(char *, const char *, _CSTD size_t); 

/*
 * Semi portable getfsstat() getmntinfo().
 * 
 * 4.4BSD had getmntinfo() and getfsstat() which
 * worked on struct statfs.  NetBSD 3.0 moved to
 * getmntinfo() and getvfsstat() which worked on
 * struct statvfs ('v' variant).  Since our struct
 * statvfs is already declared without the non-posix
 * f_fstypename, f_mntonname, f_mntfromname we
 * emulate the 4.4BSD variants which may actually
 * be more portable (for now).
 */
#define MFSNAMELEN 32
struct statfs {
	unsigned long	f_bsize;	/* file system block size */
	unsigned long	f_frsize;	/* fundamental filesystem block size */
	fsblkcnt64_t	f_blocks;	/* total number of blocks on file system in units of f_frsize */
	fsblkcnt64_t	f_bfree;	/* total number of free blocks */
	fsblkcnt64_t	f_bavail;	/* number of free blocks available to non-privileged process */
	fsfilcnt64_t	f_files;	/* total number of file serial numbers */
	fsfilcnt64_t	f_ffree;	/* total number of free file serial numbers */
	fsfilcnt64_t	f_favail;	/* number of file serial numbers available to non-privileged process */
	unsigned long	f_fsid;		/* file system id */
	char		f_basetype[16];	/* null terminated name of target file system*/
	unsigned long	f_flag;		/* bit mask of f_flag values */
	unsigned long	f_namemax;	/* maximum filename length */
	unsigned long	f_filler[21];	/* padding */

	/* Above here is the same as statvfs64.  Below is the extra part */

	char	f_fstypename[MFSNAMELEN];	/* fs type name */
	char	f_mntonname[PATH_MAX];	/* directory on which mounted */
	char	f_mntfromname[PATH_MAX];/* mounted file system */
};

#define MNT_RDONLY	ST_RDONLY
#define MNT_NOEXEC	ST_NOEXEC
#define MNT_NOSUID	ST_NOSUID
#define MNT_NOCREAT	ST_NOCREAT
#define MNT_OFF32	ST_OFF32
#define MNT_NOATIME	ST_NOATIME
#define MNT_NOWAIT	0x80
int	getfsstat(struct statfs *, _CSTD size_t, int);
int	getmntinfo(struct statfs **, int);

unsigned int arc4random(void);
void arc4random_stir(void);
void arc4random_buf(void *, size_t);
uint32_t arc4random_uniform(uint32_t);

#endif
__END_DECLS

#endif /* !_NBUTIL_H_INCLUDED */

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/io-pkt/lib/nbutil/public/nbutil.h $ $Rev: 644264 $" )
