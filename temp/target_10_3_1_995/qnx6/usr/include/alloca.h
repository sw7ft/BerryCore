/*
 * $QNXLicenseC:
 * Copyright 2007, 2011, 2014, QNX Software Systems. All Rights Reserved.
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
 *  alloca.h: Allocate memory from the stack.
 *
 */

#ifndef _ALLOCA_H_INCLUDED
#define _ALLOCA_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
# include <sys/platform.h>
#endif

__BEGIN_DECLS

extern _Sizet	__stackavail(void);

#undef alloca

/*
 * __builtin_alloca() will align to a value that will be good enough for any
 * intended use on the current platform.  That means the usual 8 or 16 bytes on
 * most platforms, but it can go up to 64 (512 bits) on x86 for instance.
 *
 * __ALLOCA_OVERHEAD will thus prevent an overflow from happening in
 * __builtin_alloca().
 */

#define __ALLOCA_ALIGNMENT (sizeof(_Uint64t) - 1)
#define __ALLOCA_OVERHEAD ((_Sizet)128)
#define __ALLOCA_SIZE_MAX (~(_Sizet)0 - (__ALLOCA_ALIGNMENT + __ALLOCA_OVERHEAD))

#define __alloca_align(__S)                                 \
    (((_Sizet)(__S) + __ALLOCA_ALIGNMENT) & ~__ALLOCA_ALIGNMENT)

#if defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__clang__)
# if !defined(__clang__)
extern void *__builtin_alloca(_Sizet __size);
# endif
# define __alloca(__S) __builtin_alloca(__S)
#else
# error not configured for system
#endif

#define __ALLOCA_ALIGN(__S) __alloca_align(__S)
#define _alloca(__S) __alloca(__S)

#define alloca(__S)                                                     \
    (((((_Sizet)(__S)) <= __ALLOCA_SIZE_MAX)                            \
      && ((__alloca_align(__S) + __ALLOCA_OVERHEAD) < __stackavail()))  \
     ? __alloca(__S)                                                    \
     : NULL)

__END_DECLS

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/c/public/alloca.h $ $REV$")
#endif
