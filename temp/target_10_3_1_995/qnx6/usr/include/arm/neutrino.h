/*
 * $QNXLicenseC:
 * Copyright 2007, 2009, QNX Software Systems.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"). You
 * may not reproduce, modify or distribute this software except in
 * compliance with the License. You may obtain a copy of the License
 * at: http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTIES OF ANY KIND, either express or implied.
 *
 * This file may contain contributions from others, either as
 * contributors under the License or as licensors under other terms.
 * Please review this entire file for other proprietary rights or license
 * notices, as well as the QNX Development Suite License Guide at
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */

#ifndef __NEUTRINO_H_INCLUDED
#error arm/neutrino.h should not be included directly.
#endif

__BEGIN_DECLS

#ifndef __KERCPU_H
/*
 * User mode support for interrupt masking is not inlined
 */
extern void	__cpu_InterruptEnable(void);
extern void	__cpu_InterruptDisable(void);
extern void	__cpu_InterruptLock(struct intrspin *__spin);
extern void	__cpu_InterruptUnlock(struct intrspin *__spin);

#define __inline_InterruptEnable	__cpu_InterruptEnable
#define __inline_InterruptDisable	__cpu_InterruptDisable
#define __inline_InterruptLock		__cpu_InterruptLock
#define __inline_InterruptUnlock	__cpu_InterruptUnlock
#endif

static __inline__ unsigned
(__inline_InterruptStatus)(void) {
	unsigned __val;
	__asm__ __volatile__( "mrs %0, cpsr" : "=&r" (__val));
	return (__val & 0x80)^0x80;
}

static __inline__ void __attribute__((__unused__))
	__inline_DebugBreak(void)
{
	/*
	 * WARNING: must match the breakpoint instruction used by gdb.
	 */
	__asm__ __volatile__(
		  "	.word	0xe7ffdefe"
		);
}

static __inline__ void __attribute__((__unused__))
	__inline_DebugKDBreak(void)
{
	__asm__ __volatile__(
		  "	.word	0xe7ffdeff"
		);
}


static __inline__ void __attribute__((__unused__))
	__inline_DebugKDOutput(const char *__text, _CSTD size_t __len)
{
	__asm__ __volatile__(
		  "	mov		r0, %0;"
		  "	mov		r1, %1;"
		  "	.word	0xe7ffffff"
		  :
		  : "r" (__text), "r" (__len)
		  : "r0", "r1"
		);
}

/*
 * ClockCycles must be emulated
 */
_Uint64t ClockCycles(void);

extern unsigned					__clockcycles_incr_bit;
#define CLOCKCYCLES_INCR_BIT	__clockcycles_incr_bit

__END_DECLS


__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/services/system/public/arm/neutrino.h $ $Rev: 717286 $" )
