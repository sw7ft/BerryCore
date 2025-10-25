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

/**
 * apparently, C++11 introduced changes that mess up stddef.h
 * Solution is to ensure that definitions herein are included before any other
 * sys/platform.h will include this at its bottom, as a workaround
 */

#ifndef _STDDEF_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#if !defined(__cplusplus) || defined(_STD_USING) || defined(_GLOBAL_USING)
#define _STDDEF_H_INCLUDED
#endif

#ifndef _STDDEF_H_DECLARED
#define _STDDEF_H_DECLARED

_STD_BEGIN

#if defined(__SIZE_T)
typedef __SIZE_T	size_t;
#undef __SIZE_T
#endif

#if defined(__RSIZE_T)
typedef __RSIZE_T	rsize_t;
#undef __RSIZE_T
#endif

#if defined(__PTRDIFF_T)
typedef __PTRDIFF_T	ptrdiff_t;
#undef __PTRDIFF_T
#endif

#if defined(__WCHAR_T)
typedef __WCHAR_T	wchar_t;
#undef __WCHAR_T
#endif

#ifndef NULL
# define NULL _NULL
#endif

_STD_END

#if (__GNUC__ >= 4) && !defined(__INTEL_COMPILER)
# define offsetof(__typ,__id) __builtin_offsetof(__typ,__id)
#elif defined(__cplusplus) && (__GNUC__ == 3 && __GNUC_MINOR__ == 4) && !defined(__INTEL_COMPILER)
# define offsetof(__typ,__id)									\
    (__offsetof__(reinterpret_cast <size_t>						\
				  (&reinterpret_cast <const volatile char &>	\
				   (static_cast<__typ *>(0)->__id))))
#else
# define offsetof(__typ,__id) ((_CSTD size_t)&(((__typ*)0)->__id))
#endif

#endif

// max_align_t was added in C11 and seems to be defined by gcc
// Our QNX is max 64-bit alignment but gcc wants 128-bit? so we block?
// really not sure about this...
#if (defined (__STDC_VERSION__) && __STDC_VERSION__+0 >= 201112L) \
	|| (defined(__cplusplus) && __cplusplus+0 >= 201103L)
#if (defined(__clang__) && !defined(__CLANG_MAX_ALIGN_T_DEFINED))
	typedef _Uint64t max_align_t;
	#define __CLANG_MAX_ALIGN_T_DEFINED
#elif (defined(__GNUC__) && !defined(_GCC_MAX_ALIGN_T))
	typedef _GCC_ATTR_ALIGN_u64t max_align_t;
	#define _GCC_MAX_ALIGN_T
#endif
//#ifdef _STD_USING
//using _CSTD max_align_t;
//#endif
#endif

#ifdef _STD_USING
using _CSTD ptrdiff_t; using _CSTD size_t; using _CSTD rsize_t;
#endif /* _STD_USING */

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/c/public/stddef.h $ $REV$")
#endif
