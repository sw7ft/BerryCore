/*
 * $QNXLicenseC:
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



/*
 *  ftw.h       File tree walk routines
 *

 */

#ifndef _FTW_H_INCLUDED
#define _FTW_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif
#ifndef __STAT_H_INCLUDED
#include <sys/stat.h>
#endif

#define FTW_CHDIR	0x0001		/* chdir() into each directory       */
#define FTW_DEPTH	0x0002		/* report directory after contents   */
#define FTW_MOUNT	0x0004		/* stay within the same mountpoint   */
#define FTW_PHYS	0x0008		/* physical walk (no symlink follow) */

enum {
	FTW_F,						/* object is a file                  */
	FTW_D,						/* object is a directory             */
	FTW_DNR,					/* object is unreadable directory    */
	FTW_DP,						/* object is a directory (FTW_DEPTH) */
	FTW_NS,						/* stat details undefined/invalid    */
	FTW_SL,						/* object is a symlink (FTW_PHYS)    */
	FTW_SLN						/* object is broken symlink          */
};

enum {
	FTW_SKR,					/* skip remainder of directory       */
	FTW_SKD						/* do not enter the directory object */
};

#include <_pack64.h>
struct FTW {
	int				base;		/* offset of object filename in path */
	int				level;		/* depth relative to walk root       */
	int				quit;		/* FTW_SK* action (extension)        */
};
#include <_packpop.h>

__BEGIN_DECLS

#if defined(__EXT_XOPEN_EX)
#ifdef __EXT_LF64SRC
extern int ftw64(const char *__path, int (*__fn)(const char *__fname, const struct stat64 *__sbuf, int __flag), int __ndirs) __ALIASOFF("ftw");
extern int nftw64(const char *__path, int (*__fn)(const char *__fname, const struct stat64 *__sbuf, int __flag, struct FTW *__ftw), int __ndirs, int __flags) __ALIASOFF("nftw");
#if defined(__EXT_LF64ALIAS) && !defined(__ALIAS_ATTRIBUTE)
#error ALIAS not configured for compiler: ftw,nftw
#endif
#endif

extern int ftw(const char *__path, int (*__fn)(const char *__fname, const struct stat *__sbuf, int __flag), int __ndirs) __ALIAS64("ftw64");
extern int nftw(const char *__path, int (*__fn)(const char *__fname, const struct stat *__sbuf, int __flag, struct FTW *__ftw), int __ndirs, int __flags) __ALIAS64("nftw64");

#ifdef __EXT_FUNCALIAS64
#ifdef __ALIAS_ATTRIBUTE
/* Use __ALIAS64 define */
#elif defined(_PRAGMA_REDEFINE_EXTNAME)
#pragma redefine_extname ftw ftw64
#pragma redefine_extname nftw nftw64
#else
#define ftw ftw64
#define nftw nftw64
#endif
#endif
#endif

__END_DECLS

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/c/public/ftw.h $ $REV$")
#endif
