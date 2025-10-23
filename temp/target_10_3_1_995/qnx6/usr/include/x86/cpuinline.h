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

#ifndef _X86_CPUINLINE_INCLUDED
#define _X86_CPUINLINE_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

__BEGIN_DECLS

#if defined(__GNUC__) || defined(__INTEL_COMPILER)

#if defined(__SLIB_DATA_INDIRECT) && !defined(__SLIB)
extern unsigned __get_cpu_flags(void);
#define __cpu_flags (__get_cpu_flags())
#else
extern unsigned __cpu_flags;
#endif

# define __cpu_membarrier()                                             \
    __extension__ ({                                                    \
            /* check for X86_CPU_SSE2 */                                \
            if (__cpu_flags & (1 << 15)) {                              \
                __asm__ __volatile__ ("mfence" ::: "memory");           \
            } else {                                                    \
                __asm__ __volatile__ ("lock; orb $0,0(%%esp)" ::: "memory"); \
            }                                                           \
        })

# define __cpu_bus_backoff()                                \
    __extension__ ({                                        \
            __asm__ __volatile__ ("pause" ::: "memory");    \
        })

#else
# error compiler not supported
#endif

#if defined(__GNUC__) || defined(__INTEL_COMPILER)

# define __CPU_ENDIAN_RET16
# define __cpu_endian_ret16(__x)                                        \
    (__builtin_constant_p(__x)                                          \
     ? ((((__x) >> 8) & 0xFF) | (((__x) & 0xFF) << 8))                  \
     : __extension__ ({                                                 \
             _Uint16t __reg;                                            \
             __asm__ __volatile__ (                                     \
                   "xchgb %b0, %h0"                                     \
                   : "=q" (__reg)                                       \
                   : "0" (__x));                                        \
             __reg;                                                     \
         }))

# define __CPU_ENDIAN_RET32
# define __cpu_endian_ret32(__x)                                        \
    (__builtin_constant_p(__x)                                          \
     ? ((((__x) >> 24) & 0xFF)                                          \
        | (((__x) >> 8) & 0xFF00)                                       \
        | (((__x) & 0xFF00) << 8)                                       \
        | (((__x) & 0xFF) << 24))                                       \
     : __extension__ ({                                                 \
             _Uint32t __reg = (__x);                                    \
             __asm__ __volatile__ (                                     \
                   "xchgb %b0, %h0;"                                    \
                   "rorl $16, %0;"                                      \
                   "xchgb %b0, %h0;"                                    \
                   : "=q" (__reg)                                       \
                   : "0" (__reg));                                      \
             __reg;                                                     \
         }))

# define __CPU_ENDIAN_RET64
# define __cpu_endian_ret64(__x)                                        \
    (__builtin_constant_p(__x)                                          \
     ? ((((__x) >> 56) & 0xFF)                                          \
        | (((__x) >> 40) & 0xFF00)                                      \
        | (((__x) >> 24) & 0xFF0000)                                    \
        | (((__x) >>  8) & 0xFF000000)                                  \
        | (((__x) & 0xFF000000) <<  8)                                  \
        | (((__x) & 0xFF0000) << 24)                                    \
        | (((__x) & 0xFF00) << 40)                                      \
        | (((__x) & 0xFF) << 56))                                       \
     : __extension__ ({                                                 \
             _Uint64t __reg;                                            \
             __asm__ __volatile__ (                                     \
                   "xchgb %b0, %h0;"                                    \
                   "rorl $16, %0;"                                      \
                   "xchgb %b0, %h0;"                                    \
                   "xchg %%eax, %%edx;"                                 \
                   "xchgb %b0, %h0;"                                    \
                   "rorl $16, %0;"                                      \
                   "xchgb %b0, %h0;"                                    \
                   : "=A" (__reg)                                       \
                   : "0" (__x));                                        \
             __reg;                                                     \
         }))

#endif

#define __CPU_UNALIGNED_RET16
#define __cpu_unaligned_ret16(__p) (*(_Uint16t volatile *)(__p))
#define __CPU_UNALIGNED_RET32
#define __cpu_unaligned_ret32(__p) (*(_Uint32t volatile *)(__p))
#define __CPU_UNALIGNED_RET64
#define __cpu_unaligned_ret64(__p) (*(_Uint64t volatile *)(__p))
#define __CPU_UNALIGNED_PUT16
#define __cpu_unaligned_put16(__p, __x) (*(_Uint16t volatile *)(__p) = (__x))
#define __CPU_UNALIGNED_PUT32
#define __cpu_unaligned_put32(__p, __x) (*(_Uint32t volatile *)(__p) = (__x))
#define __CPU_UNALIGNED_PUT64
#define __cpu_unaligned_put64(__p, __x) (*(_Uint64t volatile *)(__p) = (__x))

__END_DECLS

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/c/public/x86/cpuinline.h $ $REV$")
#endif
