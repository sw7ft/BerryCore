/*
 * $QNXLicenseC:
 * Copyright 2007, 2008, 2009, QNX Software Systems. All Rights Reserved.
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
 *  The only symbols made visible by this header are
 *  OS/compiler reserved symbols.
 */
#ifndef __COMPILER_GNU_H_INCLUDED
#define __COMPILER_GNU_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#error sys/compiler_gnu.h should not be included directly.
#endif

#undef mips

#ifdef __CHAR_UNSIGNED__
# undef __CHAR_SIGNED__
#else
# ifndef __CHAR_SIGNED__
#  define __CHAR_SIGNED__
# endif
#endif

#ifdef __GNUG__
# undef _NULL
# define _NULL __null
#endif

#if !defined (__cplusplus) && defined(__WCHAR_TYPE__)
# undef __WCHAR_T
# define __WCHAR_T __WCHAR_TYPE__
#endif

#ifdef __WCHAR_MAX__
# undef _WCMAX
# define _WCMAX __WCHAR_MAX__
#endif

#ifdef __WCHAR_MIN__
# undef _WCMIN
# define _WCMIN __WCHAR_MIN__
#endif

#if !defined(__BIGENDIAN__) && !defined(__LITTLEENDIAN__)
# error Endian not defined
#endif

#ifndef _NO_RETURN
# define _NO_RETURN(fun) void fun __attribute__((__noreturn__))
#endif

#ifndef	__CDEFS_H_INCLUDED
# include _NTO_HDR_(sys/cdefs.h)
#endif

#if defined(__CHAR_BIT__) && defined(__SIZEOF_INT__)
# define __INT_BITS__	(__CHAR_BIT__*__SIZEOF_INT__)
#else
# define __INT_BITS__	32
#endif

#if defined(__CHAR_BIT__) && defined(__SIZEOF_POINTER__)
# define __PTR_BITS__	(__CHAR_BIT__*__SIZEOF_POINTER__)
#else
# define __PTR_BITS__	32
#endif

#if defined(__CHAR_BIT__) && defined(__SIZEOF_LONG__)
# define __LONG_BITS__	(__CHAR_BIT__*__SIZEOF_LONG__)
#else
# define __LONG_BITS__	32
#endif

#if defined(__X86__) || defined(__X86_64__)
# define __LONGDOUBLE_BITS__		80
#elif defined(__CHAR_BIT__) && defined(__SIZEOF_LONG_DOUBLE__)
# define __LONGDOUBLE_BITS__		(__CHAR_BIT__*__SIZEOF_LONG_DOUBLE__)
#elif defined(__PPC__) || defined(__MIPS__) || defined(__SH__) || defined(__ARM__) || defined(__SPARC__)
# define __LONGDOUBLE_BITS__		64
#else
# error not configured for CPU
#endif

#if defined(__CHAR_BIT__) && defined(__SIZEOF_SIZE_T__)
# define __SIZE_BITS__		(__CHAR_BIT__*__SIZEOF_SIZE_T__)
#else
# define __SIZE_BITS__		__INT_BITS__
#endif

#if (__GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 7)) && !defined(_lint)
typedef int							_GCC_ATTR_ALIGN_64t __attribute__((__mode__(__DI__)));
typedef unsigned int				_GCC_ATTR_ALIGN_u64t __attribute__((__mode__(__DI__)));
typedef _GCC_ATTR_ALIGN_64t			_Int64t __attribute__((__aligned__(8)));
typedef _GCC_ATTR_ALIGN_u64t		_Uint64t __attribute__((__aligned__(8)));
#else
typedef unsigned long long			_GCC_ATTR_ALIGN_u64t;
typedef signed long long			_GCC_ATTR_ALIGN_64t;
typedef _GCC_ATTR_ALIGN_u64t		_Uint64t __attribute__((__aligned__(8)));
typedef _GCC_ATTR_ALIGN_64t 		_Int64t __attribute__((__aligned__(8)));
#endif

#if __INT_BITS__ == 32
typedef unsigned					_GCC_ATTR_ALIGN_u32t;
typedef int							_GCC_ATTR_ALIGN_32t;
typedef _GCC_ATTR_ALIGN_u32t		_Uint32t __attribute__((__aligned__(4)));
typedef _GCC_ATTR_ALIGN_32t			_Int32t __attribute__((__aligned__(4)));
#elif __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 7)
typedef int                         _GCC_ATTR_ALIGN_32t __attribute__((__mode__(__SI__)));
typedef unsigned int                _GCC_ATTR_ALIGN_u32t __attribute__((__mode__(__SI__)));
typedef _GCC_ATTR_ALIGN_32t			_Int32t __attribute__((__aligned__(4)));
typedef _GCC_ATTR_ALIGN_u32t		_Uint32t  __attribute__((__aligned__(4)));
#else
typedef unsigned long				_GCC_ATTR_ALIGN_u32t;
typedef signed long					_GCC_ATTR_ALIGN_32t;
typedef _GCC_ATTR_ALIGN_u32t		_Uint32t __attribute__((__aligned__(4)));
typedef _GCC_ATTR_ALIGN_32t			_Int32t __attribute__((__aligned__(4)));
#endif

#if __INT_BITS__ == 16
typedef int							_GCC_ATTR_ALIGN_16t;
typedef unsigned					_GCC_ATTR_ALIGN_u16t;
typedef _GCC_ATTR_ALIGN_u16t		_Uint16t __attribute__((__aligned__(2)));
typedef _GCC_ATTR_ALIGN_16t			_Int16t __attribute__((__aligned__(2)));
#elif (__GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 7)) && !defined(_lint)
typedef int							_GCC_ATTR_ALIGN_16t __attribute__((__mode__(__HI__)));
typedef unsigned int				_GCC_ATTR_ALIGN_u16t __attribute__((__mode__(__HI__)));
typedef _GCC_ATTR_ALIGN_16t			_Int16t __attribute__((__aligned__(2)));
typedef _GCC_ATTR_ALIGN_u16t		_Uint16t __attribute__((__aligned__(2)));
#else
typedef signed short				_GCC_ATTR_ALIGN_16t;
typedef unsigned short				_GCC_ATTR_ALIGN_u16t;
typedef _GCC_ATTR_ALIGN_u16t		_Uint16t __attribute__((__aligned__(2)));
typedef _GCC_ATTR_ALIGN_16t			_Int16t __attribute__((__aligned__(2)));
#endif

#if (__GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 7)) && !defined(_lint)
typedef int							_GCC_ATTR_ALIGN_8t __attribute__((__mode__(__QI__)));
typedef unsigned int				_GCC_ATTR_ALIGN_u8t __attribute__((__mode__(__QI__)));
typedef _GCC_ATTR_ALIGN_8t			_Int8t __attribute__((__aligned__(1)));
typedef _GCC_ATTR_ALIGN_u8t			_Uint8t __attribute__((__aligned__(1)));
#else
typedef signed char					_GCC_ATTR_ALIGN_8t;
typedef unsigned char				_GCC_ATTR_ALIGN_u8t;
typedef _GCC_ATTR_ALIGN_u8t			_Uint8t __attribute__((__aligned__(1)));
typedef _GCC_ATTR_ALIGN_8t			_Int8t __attribute__((__aligned__(1)));
#endif

#if defined(__INTPTR_TYPE__) && defined(__UINTPTR_TYPE__)
typedef __UINTPTR_TYPE__			_Uintptrt;
typedef __INTPTR_TYPE__				_Intptrt;
#elif __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 7)
typedef int							_Intptrt __attribute__((__mode__(__pointer__)));
typedef unsigned int				_Uintptrt __attribute__((__mode__(__pointer__)));
#elif __PTR_BITS__ <= 16
typedef _Uint16t					_Uintptrt;
typedef _Int16t						_Intptrt;
#elif __PTR_BITS__ <= 32
typedef _Uint32t					_Uintptrt;
typedef _Int32t						_Intptrt;
#elif __PTR_BITS__ <= 64
typedef _Uint64t					_Uintptrt;
typedef _Int64t						_Intptrt;
#else
#error Unable to declare integral pointer type
#endif

#if defined(__SIZEOF_SIZE_T__) && __SIZEOF_INT__+0 == __SIZEOF_SIZE_T__
typedef unsigned					_Sizet;
typedef int							_Ssizet;
#elif __SIZEOF_SIZE_T__+0 == 8
typedef _Uint64t					_Sizet;
typedef _Int64t						_Ssizet;
#elif !defined(__SIZEOF_SIZE_T__) || __SIZEOF_SIZE_T__+0 == 4 
typedef _Uint32t					_Sizet;
typedef _Int32t						_Ssizet;
#else
#error Unable to declare size_t type
#endif
 
__extension__ typedef long long				_Longlong;
__extension__ typedef unsigned long long	_ULonglong;

/*
 * This is to override the gcc local include files to use
 * our definition of the following types
 */
#define _GCC_PTRDIFF_T
#define _GCC_SIZE_T
#define _GCC_WCHAR_T

/*
 * -ansi			defines __STRICT_ANSI__
 * -traditional		undefines __STDC__ and __STDC_VERSION__
 */

#if defined(__STDC__) && !defined(__STRICT_ANSI__)
# define __EXT
#endif

/*
  For __GNUC__ < 3, we have platform specific implementations of var args
  in the CPU/platform.h headers.  For gcc-3 or newer, we use the builtins
  for the stdarg.h mechanisms, and leave the varargs.h as it is since the
  varargs.h stuff is deprecated in gcc-3.X.
*/

#if (__GNUC__ >= 3)

#ifndef __GNUC_VA_LIST
# define __GNUC_VA_LIST
typedef __builtin_va_list __gnuc_va_list;
#endif

typedef __gnuc_va_list                __NTO_va_list;
#define __NTO_va_start_stdarg(__p1,__p2)  __builtin_va_start(__p1,__p2)
#define __NTO_va_arg(__p1, __p2)          __builtin_va_arg(__p1,__p2)
#define __NTO_va_end(__p1)                __builtin_va_end(__p1)
#define __NTO_va_copy(__d,__s)            __builtin_va_copy(__d,__s)
#endif

#endif

#define __ALIAS_ATTRIBUTE(n)	__asm(n)

#if  __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) \
    && defined _FORTIFY_SOURCE && _FORTIFY_SOURCE > 0 \
    && defined __OPTIMIZE__ && __OPTIMIZE__ > 0
#if _FORTIFY_SOURCE > 1
# define __USE_FORTIFY_LEVEL 2
#else
# define __USE_FORTIFY_LEVEL 1
#endif
# define __bos(ptr) __builtin_object_size (ptr, __USE_FORTIFY_LEVEL > 1)
# define __bos0(ptr) __builtin_object_size (ptr, 0)
#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)
# define __bvap __builtin_va_arg_pack()
#endif
#else
# define __USE_FORTIFY_LEVEL 0
#endif

#ifndef __ARTIFICIAL
# if defined __GNUC_STDC_INLINE__ 
# define  __ARTIFICIAL __attribute__((__gnu_inline__,__artificial__))
#else
# define  __ARTIFICIAL __attribute__((__artificial__))
#endif
#endif

#ifndef __ALWAYS_INLINE
# define __ALWAYS_INLINE __inline  __attribute__((always_inline))
#endif

#ifndef __LINKER_WARNING
# define __LINKER_WARNING(__symbol, __string) \
__asm__(".section .gnu.warning." #__symbol ";.asciz \"" __string "\";.previous");
#endif

#if defined __GNUC__ && ( __GNUC__ >= 4 || (__GNUC__ >= 3 && __GNUC_MINOR__ >= 4))
#if defined __FAST_MATH__
/* use gccs built-ins */

#define _FAST_SIN(val) __builtin_sin(val)
#define _FAST_COS(val) __builtin_cos(val)
#define _FAST_SINL(val) __builtin_sinl(val)
#define _FAST_COSL(val) __builtin_cosl(val)
#define _FAST_SINF(val) __builtin_sinf(val)
#define _FAST_COSF(val) __builtin_cosf(val)
#define _FAST_SINH(val) __builtin_sinh(val)
#define _FAST_COSH(val) __builtin_cosh(val)
#define _FAST_SINHF(val) __builtin_sinhf(val)
#define _FAST_COSHF(val) __builtin_coshf(val)
#define _FAST_COSHL(val) __builtin_coshl(val)
#define _FAST_SINHL(val) __builtin_sinhl(val)
#define _FAST_LOG(val) __builtin_log(val)
#define _FAST_LOGL(val) __builtin_logl(val)
#define _FAST_LOGF(val) __builtin_logf(val)
#define _FAST_LOG10(val) __builtin_log10(val)
#define _FAST_LOG10L(val) __builtin_log10l(val)
#define _FAST_LOG10F(val) __builtin_log10f(val)
#endif
#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/c/public/sys/compiler_gnu.h $ $REV$")
#endif
