/*
 * $QNXLicenseC:
 * Copyright 2007, 2009, QNX Software Systems. All Rights Reserved.
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

#ifndef __STATVFS_H_INCLUDED
#define __STATVFS_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#include <_pack64.h>

#if defined(__FSBLKCNT64_T)
typedef __FSBLKCNT64_T		fsblkcnt64_t;
#undef __FSBLKCNT64_T
#endif

#if defined(__FSFILCNT64_T)
typedef __FSFILCNT64_T		fsfilcnt64_t;
#undef __FSFILCNT64_T
#endif

#if defined(__FSBLKCNT_T)
typedef __FSBLKCNT_T		fsblkcnt_t;
#undef __FSBLKCNT_T
#endif

#if defined(__FSFILCNT_T)
typedef __FSFILCNT_T		fsfilcnt_t;
#undef __FSFILCNT_T
#endif

struct statvfs {
	unsigned long	f_bsize;		/* file system block size */
	unsigned long	f_frsize;		/* fundamental filesystem block size */
#if __OFF_BITS__ == 64
	fsblkcnt_t		f_blocks;		/* total number of blocks on file system in units of f_frsize */
	fsblkcnt_t		f_bfree;		/* total number of free blocks */
	fsblkcnt_t		f_bavail;		/* number of free blocks available to non-privileged process */
	fsfilcnt_t		f_files;		/* total number of file serial numbers */
	fsfilcnt_t		f_ffree;		/* total number of free file serial numbers */
	fsfilcnt_t		f_favail;		/* number of file serial numbers available to non-privileged process */
#elif __OFF_BITS__ == 32
# if defined(__LITTLEENDIAN__)
	fsblkcnt_t		f_blocks;		/* total number of blocks on file system in units of f_frsize */
	fsblkcnt_t		f_blocks_hi;
	fsblkcnt_t		f_bfree;		/* total number of free blocks */
	fsblkcnt_t		f_bfree_hi;
	fsblkcnt_t		f_bavail;		/* number of free blocks available to non-privileged process */
	fsblkcnt_t		f_bavail_hi;
	fsfilcnt_t		f_files;		/* total number of file serial numbers */
	fsfilcnt_t		f_files_hi;
	fsfilcnt_t		f_ffree;		/* total number of free file serial numbers */
	fsfilcnt_t		f_ffree_hi;
	fsfilcnt_t		f_favail;		/* number of file serial numbers available to non-privileged process */
	fsfilcnt_t		f_favail_hi;
# elif defined(__BIGENDIAN__)
	fsblkcnt_t		f_blocks_hi;
	fsblkcnt_t		f_blocks;		/* total number of blocks on file system in units of f_frsize */
	fsblkcnt_t		f_bfree_hi;
	fsblkcnt_t		f_bfree;		/* total number of free blocks */
	fsblkcnt_t		f_bavail_hi;
	fsblkcnt_t		f_bavail;		/* number of free blocks available to non-privileged process */
	fsfilcnt_t		f_files_hi;
	fsfilcnt_t		f_files;		/* total number of file serial numbers */
	fsfilcnt_t		f_ffree_hi;
	fsfilcnt_t		f_ffree;		/* total number of free file serial numbers */
	fsfilcnt_t		f_favail_hi;
	fsfilcnt_t		f_favail;		/* number of file serial numbers available to non-privileged process */
# else
#  error endian not configured for system
# endif
#else
# error __OFF_BITS__ value is unsupported
#endif
	unsigned long	f_fsid;			/* file system id */
	char			f_basetype[16];	/* null terminated name of target file system*/
	unsigned long	f_flag;			/* bit mask of f_flag values */
	unsigned long	f_namemax;		/* maximum filename length */
	unsigned long	f_filler[21];	/* padding */
};

#ifdef __EXT_LF64SRC
struct statvfs64 {
	unsigned long	f_bsize;		/* file system block size */
	unsigned long	f_frsize;		/* fundamental filesystem block size */
	fsblkcnt64_t	f_blocks;		/* total number of blocks on file system in units of f_frsize */
	fsblkcnt64_t	f_bfree;		/* total number of free blocks */
	fsblkcnt64_t	f_bavail;		/* number of free blocks available to non-privileged process */
	fsfilcnt64_t	f_files;		/* total number of file serial numbers */
	fsfilcnt64_t	f_ffree;		/* total number of free file serial numbers */
	fsfilcnt64_t	f_favail;		/* number of file serial numbers available to non-privileged process */
	unsigned long	f_fsid;			/* file system id */
	char			f_basetype[16];	/* null terminated name of target file system*/
	unsigned long	f_flag;			/* bit mask of f_flag values */
	unsigned long	f_namemax;		/* maximum filename length */
	unsigned long	f_filler[21];	/* padding */
};
#endif

#include <_packpop.h>

#define ST_RDONLY        0x01  /* rw read only */
#define ST_NOEXEC        0x02  /* rw can't exec from filesystem */
#define ST_NOSUID        0x04  /* rw don't honor setuid bits on fs */
#define ST_NOCREAT       0x08  /* rw don't allow creat on this fs */
#define ST_OFF32         0x10  /* rw Limit off_t to 32 bits */
#define ST_NOATIME       0x20  /* rw don't update times if only atime is dirty */
#define ST_RMVABLE       0x40  /* media is removeable */

__BEGIN_DECLS

#if defined(__EXT_XOPEN_EX)

#ifdef __EXT_LF64SRC
extern int statvfs64(const char *__path, struct statvfs64 *__buf) __ALIASOFF("statvfs");
extern int fstatvfs64(int __fildes, struct statvfs64 *__buf) __ALIASOFF("fstatvfs");
#if defined(__EXT_LF64ALIAS) && !defined(__ALIAS_ATTRIBUTE)
#error ALIAS not configured for compiler: statvfs,fstatvfs
#endif
#endif

extern int statvfs(const char *__path, struct statvfs *__buf) __ALIAS64("statvfs64");
extern int fstatvfs(int __fildes, struct statvfs *__buf) __ALIAS64("fstatvfs64");

#ifdef __EXT_FUNCALIAS64
# ifdef __ALIAS_ATTRIBUTE
/* Use __ALIAS64 define */
# elif defined(_PRAGMA_REDEFINE_EXTNAME)
#  pragma redefine_extname statvfs statvfs64
#  pragma redefine_extname fstatvfs fstatvfs64
# else
#  define statvfs statvfs64
#  define fstatvfs fstatvfs64
# endif
#endif
#endif

__END_DECLS

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/c/public/sys/statvfs.h $ $REV$")
#endif
