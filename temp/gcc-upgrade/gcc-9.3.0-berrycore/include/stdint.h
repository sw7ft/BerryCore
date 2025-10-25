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

#ifndef _STDINT_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#if !defined(__cplusplus) || defined(_STD_USING) || defined(_GLOBAL_USING)
#define _STDINT_H_INCLUDED
#endif

#ifndef _STDINT_H_DECLARED
#define _STDINT_H_DECLARED

_C_STD_BEGIN

typedef _Int8t                  int8_t;
typedef _Uint8t                 uint8_t;
typedef _Int16t                 int16_t;
typedef _Uint16t                uint16_t;
typedef _Int32t                 int32_t;
typedef _Uint32t                uint32_t;
typedef _Int64t                 int64_t;
typedef _Uint64t                uint64_t;
#if defined(__INTPTR_T)
typedef __INTPTR_T              intptr_t;
#undef __INTPTR_T
#endif
typedef _Uintptrt               uintptr_t;


#if defined(__EXT_QNX)
/*
 * These types are deprecated and applications should use the
 * int_/uint_ types defined below.
 */
typedef _Intleast8t             intleast8_t;
typedef _Uintleast8t            uintleast8_t;
typedef _Intfast8t              intfast8_t;
typedef _Uintfast8t             uintfast8_t;

typedef _Intleast16t            intleast16_t;
typedef _Uintleast16t           uintleast16_t;
typedef _Intfast16t             intfast16_t;
typedef _Uintfast16t            uintfast16_t;

typedef _Intleast32t            intleast32_t;
typedef _Uintleast32t           uintleast32_t;
typedef _Intfast32t             intfast32_t;
typedef _Uintfast32t            uintfast32_t;

typedef _Intleast64t            intleast64_t;
typedef _Uintleast64t           uintleast64_t;
typedef _Intfast64t             intfast64_t;
typedef _Uintfast64t            uintfast64_t;
#endif

typedef _Intleast8t             int_least8_t;
typedef _Uintleast8t            uint_least8_t;
typedef _Intfast8t              int_fast8_t;
typedef _Uintfast8t             uint_fast8_t;

typedef _Intleast16t            int_least16_t;
typedef _Uintleast16t           uint_least16_t;
typedef _Intfast16t             int_fast16_t;
typedef _Uintfast16t            uint_fast16_t;

typedef _Intleast32t            int_least32_t;
typedef _Uintleast32t           uint_least32_t;
typedef _Intfast32t             int_fast32_t;
typedef _Uintfast32t            uint_fast32_t;

typedef _Intleast64t            int_least64_t;
typedef _Uintleast64t           uint_least64_t;
typedef _Intfast64t             int_fast64_t;
typedef _Uintfast64t            uint_fast64_t;

#ifndef _INTMAXT
#define _INTMAXT
typedef _Intmaxt                intmax_t;
typedef _Uintmaxt               uintmax_t;
#endif

// reportedly, C11 and C++11 no longer require macro checks...?

#if (defined __cplusplus && __cplusplus+0 < 201103L) \
	|| (defined __STDC_VERSION__ && __STDC_VERSION__+0 < 201112L)
/* always define the macros? */
#else
#if !defined __cplusplus || defined __STDC_CONSTANT_MACROS
#endif

#define INT8_C(__x)             __x
#define INT16_C(__x)            __x
#define INT32_C(__x)            __x

#define UINT8_C(__x)            __x
#define UINT16_C(__x)           __x
#define UINT32_C(__x)           __x ## U

#if __PTR_BITS__ <= 32
#define INT64_C(__x)            __x ## LL
#define UINT64_C(__x)           __x ## ULL
#define INTMAX_C(__x)           __x ## LL
#define UINTMAX_C(__x)          __x ## ULL
#elif __PTR_BITS__ <= 64
#define INT64_C(__x)            __x ## L
#define UINT64_C(__x)           __x ## UL
#define INTMAX_C(__x)           __x ## L
#define UINTMAX_C(__x)          __x ## UL
#endif

#if (defined __cplusplus && __cplusplus+0 < 201103L) \
	|| (defined __STDC_VERSION__ && __STDC_VERSION__+0 < 201112L)
/* no #if checking */
#else
// combine previous endif with following #if
#endif
#if !defined __cplusplus || defined __STDC_LIMIT_MACROS
#endif

#if __PTR_BITS__ <= 32
#define _INT64_C(__x)           __x ## LL
#define _UINT64_C(__x)          __x ## ULL
#elif __PTR_BITS__ <= 64
#define _INT64_C(__x)           __x ## L
#define _UINT64_C(__x)          __x ## UL
#endif

#define INT8_MIN                (-0x7f-1)
#define INT16_MIN               (-0x7fff-1)
#define INT32_MIN               (-0x7fffffff-1)
#define INT64_MIN               (_INT64_C(-0x7fffffffffffffff)-_INT64_C(1))

#define INT8_MAX                (0x7f)
#define INT16_MAX               (0x7fff)
#define INT32_MAX               (0x7fffffff)
#define INT64_MAX               _INT64_C(0x7fffffffffffffff)

#define UINT8_MAX               (0xff)
#define UINT16_MAX              (0xffff)
#define UINT32_MAX              (0xffffffff)
#define UINT64_MAX              _UINT64_C(0xffffffffffffffff)

#if __PTR_BITS__ <= 16
# define INTPTR_MIN             (-0x7fff-1)
# define INTPTR_MAX             (0x7fff)
# define UINTPTR_MAX            (0xffffU)
#elif __PTR_BITS__ <= 32
# define INTPTR_MIN             (-0x7fffffff-1)
# define INTPTR_MAX             (0x7fffffff)
# define UINTPTR_MAX            (0xffffffffU)
#elif __PTR_BITS__ <= 64
# define INTPTR_MIN             (_INT64_C(-0x7fffffffffffffff)-_INT64_C(1))
# define INTPTR_MAX             _INT64_C(0x7fffffffffffffff)
# define UINTPTR_MAX            _INT64_C(0xffffffffffffffff)
#else
# error Unable to determine pointer limits
#endif

#define PTRDIFF_MIN             INTPTR_MIN
#define PTRDIFF_MAX             INTPTR_MAX

#define INT_LEAST8_MIN          (-0x7f-1)
#define INT_LEAST16_MIN         (-0x7fff-1)
#define INT_LEAST32_MIN         (-0x7fffffff-1)
#define INT_LEAST64_MIN         (_INT64_C(-0x7fffffffffffffff)-_INT64_C(1))

#define INT_LEAST8_MAX          (0x7f)
#define INT_LEAST16_MAX         (0x7fff)
#define INT_LEAST32_MAX         (0x7fffffff)
#define INT_LEAST64_MAX         _INT64_C(0x7fffffffffffffff)

#define UINT_LEAST8_MAX         (0xff)
#define UINT_LEAST16_MAX        (0xffff)
#define UINT_LEAST32_MAX        (0xffffffff)
#define UINT_LEAST64_MAX        _UINT64_C(0xffffffffffffffff)

#define INT_FAST8_MIN           (-0x7f-1)
#define INT_FAST16_MIN          (-0x7fff-1)
#define INT_FAST32_MIN          (-0x7fffffff-1)
#define INT_FAST64_MIN          (_INT64_C(-0x7fffffffffffffff)-_INT64_C(1))

#define INT_FAST8_MAX           (0x7f)
#define INT_FAST16_MAX          (0x7fff)
#define INT_FAST32_MAX          (0x7fffffff)
#define INT_FAST64_MAX          _INT64_C(0x7fffffffffffffff)

#define UINT_FAST8_MAX          (0xff)
#define UINT_FAST16_MAX         (0xffff)
#define UINT_FAST32_MAX         (0xffffffff)
#define UINT_FAST64_MAX         _UINT64_C(0xffffffffffffffff)

#define INTMAX_MIN              (_INT64_C(-0x7fffffffffffffff)-_INT64_C(1))
#define INTMAX_MAX              _INT64_C(0x7fffffffffffffff)
#define UINTMAX_MAX             _UINT64_C(0xffffffffffffffff)

#if __INT_BITS__ <= 16
# define SIG_ATOMIC_MIN         INT16_MIN
# define SIG_ATOMIC_MAX         INT16_MAX
#elif __INT_BITS__ <= 32
# define SIG_ATOMIC_MIN         INT32_MIN
# define SIG_ATOMIC_MAX         INT32_MAX
#elif __INT_BITS__ <= 64
# define SIG_ATOMIC_MIN         INT64_MIN
# define SIG_ATOMIC_MAX         INT64_MAX
#else
# error Unable to determine sigatomic limits
#endif

#define SIZE_MAX                UINT32_MAX

#define WCHAR_MIN               _WCMIN
#define WCHAR_MAX               _WCMAX

#define WINT_MIN                INT32_MIN
#define WINT_MAX                INT32_MAX

#if (defined __cplusplus && __cplusplus+0 < 201103L) \
	|| (defined __STDC_VERSION__ && __STDC_VERSION__+0 < 201112L)
/* no #if checking */
#else
#endif
#endif

_C_STD_END

#endif

#ifdef _STD_USING
using _CSTD int8_t; using _CSTD uint8_t;
using _CSTD int16_t; using _CSTD uint16_t;
using _CSTD int32_t; using _CSTD uint32_t;
using _CSTD int64_t; using _CSTD uint64_t;
using _CSTD intptr_t; using _CSTD uintptr_t;
using _CSTD intmax_t; using _CSTD uintmax_t;
# if defined(__EXT_QNX)
using _CSTD intleast8_t; using _CSTD uintleast8_t;
using _CSTD intleast16_t; using _CSTD uintleast16_t;
using _CSTD intleast32_t; using _CSTD uintleast32_t;
using _CSTD intleast64_t; using _CSTD uintleast64_t;
using _CSTD intfast8_t; using _CSTD uintfast8_t;
using _CSTD intfast16_t; using _CSTD uintfast16_t;
using _CSTD intfast32_t; using _CSTD uintfast32_t;
using _CSTD intfast64_t; using _CSTD uintfast64_t;
# endif
using _CSTD int_least8_t; using _CSTD uint_least8_t;
using _CSTD int_least16_t; using _CSTD uint_least16_t;
using _CSTD int_least32_t; using _CSTD uint_least32_t;
using _CSTD int_least64_t; using _CSTD uint_least64_t;
using _CSTD int_fast8_t; using _CSTD uint_fast8_t;
using _CSTD int_fast16_t; using _CSTD uint_fast16_t;
using _CSTD int_fast32_t; using _CSTD uint_fast32_t;
using _CSTD int_fast64_t; using _CSTD uint_fast64_t;
#endif /* _STD_USING */

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/c/public/stdint.h $ $REV$")
#endif
