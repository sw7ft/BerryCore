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

#ifndef _SETJMP_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#if !defined(__cplusplus) || defined(_STD_USING) || defined(_GLOBAL_USING)
#define _SETJMP_H_INCLUDED
#endif

#ifndef _SETJMP_H_DECLARED
#define _SETJMP_H_DECLARED

#include <_pack64.h>

__BEGIN_DECLS

_C_STD_BEGIN

typedef struct _jmp_buf {
	union {
		unsigned int 	__savearea[__JMPBUFSIZE];
		union {
			__jmpbufalign	__alignment__;
			void *		__savearea;
		} __aux;
	}				__jmpbuf_un;
	int				__flg;
	long			__msk[2];
} jmp_buf[1];

_C_STD_END

extern int _setjmp(_CSTD jmp_buf __env);
extern void _longjmp(_CSTD jmp_buf __env, int __val) __attribute__((__noreturn__));

extern void longjmp(_CSTD jmp_buf __env, int __val) __attribute__((__noreturn__));

#if defined(__EXT_POSIX1_200112)
/*
 * POSIX requires a setjmp() function prototype but suppressing the macro
 * definition or defining an external identifier with the name setjmp
 * will cause undefined behaviour
 */
extern int setjmp(_CSTD jmp_buf);
extern int sigsetjmp(_CSTD jmp_buf __env, int __msk);
#endif

typedef _CSTD jmp_buf sigjmp_buf;
extern void __sigjmp_prolog(sigjmp_buf __env, int __msk);
extern void siglongjmp(sigjmp_buf __env, int __val) __attribute__((__noreturn__));

#define sigsetjmp(__env, __msk)	(__sigjmp_prolog((__env), (__msk)), _setjmp(__env))
#define setjmp(__env)			sigsetjmp(__env, 1)
#define longjmp(__env, __val)	siglongjmp((__env), (__val))

#if defined(__PPC__)							\
	|| defined(__MIPS__)						\
	|| defined(__SH__)							\
	|| defined(__ARM__)						\
	|| defined(__X86__)
/*(no-op)*/
#else
# error not configured for system
#endif

#include <_packpop.h>

__END_DECLS

#endif

#ifdef _STD_USING
using _CSTD jmp_buf;
#endif /* _STD_USING */

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/c/public/setjmp.h $ $REV$")
#endif
