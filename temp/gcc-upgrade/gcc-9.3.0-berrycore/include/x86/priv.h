/*
 * $QNXLicenseC:
 * Copyright 2008, QNX Software Systems. 
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




/*
 * privledged instructions for kernel
 *

 *
 */
#ifndef __PRIV_H_INCLUDED
#define __PRIV_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

__BEGIN_DECLS

#if defined(__WATCOMC__)

	/* return the descriptor for LDT */
_uint16 sldt(void);

	/* store the GDT base address and limit in the pointed to memory */
void sgdt(void *);

	/* store the IDT base address and limit in the pointed to memory */
void sidt(void *);

void lgdt(void *);
void lidt(void *);

void invlpg(_Uintptrt __vaddr);
void ldpgdir(_Paddr32t __addr);
_Paddr32t rdpgdir(void);
int ldcr0(int __flags);
int rdcr0(void);
int ldcr4(unsigned __flags);
unsigned rdcr4(void);
void flushtlb(void);
extern void flushcache(void);

void HALT(void);

char *rddr0(void);
char *rddr1(void);
char *rddr2(void);
char *rddr3(void);
unsigned rddr6(void);
unsigned rddr7(void);
char *wrdr0(unsigned);
char *wrdr1(unsigned);
char *wrdr2(unsigned);
char *wrdr3(unsigned);
unsigned wrdr6(unsigned);
unsigned wrdr7(unsigned);

unsigned wrtr(unsigned);
unsigned rdtr(void);
void clts(void);

void setts(void);

_uint64 rdmsr(int);
void wrmsr(int,_uint64);


#pragma aux HALT = "hlt" parm nomemory [] modify exact nomemory [];

#pragma aux sldt = ".286p" "sldt ax" parm nomemory [] modify nomemory [] value [ax]

#pragma aux setts = \
			".286p" \
			"smsw ax" \
			"or al,8" \
			"lmsw ax"\
			parm nomemory [ ] \
			modify exact nomemory [ax];

#pragma aux lgdt = ".386p" "lgdt pword ptr [esi]" parm [esi] modify exact nomemory [] ;
	
#pragma aux lidt = ".386p" "lidt pword ptr [esi]" parm [esi] modify exact nomemory [] ;

#pragma aux sgdt = ".386p" "sgdt [eax]" parm [eax];

#pragma aux sidt = ".386p" "sidt [eax]" parm [eax];

#pragma aux invlpg = ".486p" "invlpg [eax]" parm nomemory [eax] modify nomemory exact [];

#pragma aux ldpgdir = \
			".386p" \
			"mov cr3,eax" \
			parm nomemory [eax] \
			modify exact [ ];
	
#pragma aux rdpgdir = \
			".386p" \
			"mov eax,cr3" \
			parm nomemory [ ] \
			modify exact nomemory [eax];

#pragma aux ldcr0 = \
			".386p" \
			"mov cr0,eax" \
			parm nomemory [eax] \
			modify exact [ ];
	
#pragma aux rdcr0 = \
			".386p" \
			"mov eax,cr0" \
			parm nomemory [ ] \
			modify exact nomemory [eax];

#pragma aux ldcr4 = \
			".386p" \
			"mov cr4,eax" \
			parm nomemory [eax] \
			modify exact [ ];
	
#pragma aux rdcr4 = \
			".386p" \
			"mov eax,cr4" \
			parm nomemory [ ] \
			modify exact nomemory [eax];

#pragma aux flushtlb = \
			".386p" \
			"cli" \
			"mov eax,cr3" \
			"mov cr3,eax" \
			"sti" \
			parm nomemory [ ] \
			modify exact nomemory [eax];

#pragma aux flushcache = \
			".486p" \
			"wbinvd" \
			modify exact nomemory [];

#pragma aux rddr0 = \
			".386p" \
			"mov eax,dr0" \
			parm nomemory [ ] \
			modify exact nomemory [eax];

#pragma aux rddr1 = \
			".386p" \
			"mov eax,dr1" \
			parm nomemory [ ] \
			modify exact nomemory [eax];

#pragma aux rddr2 = \
			".386p" \
			"mov eax,dr2" \
			parm nomemory [ ] \
			modify exact nomemory [eax];

#pragma aux rddr3 = \
			".386p" \
			"mov eax,dr3" \
			parm nomemory [ ] \
			modify exact nomemory [eax];

#pragma aux rddr6 = \
			".386p" \
			"mov eax,dr6" \
			parm nomemory [ ] \
			modify exact nomemory [eax];

#pragma aux rddr7 = \
			".386p" \
			"mov eax,dr7" \
			parm nomemory [ ] \
			modify exact nomemory [eax];

#pragma aux wrdr0 = \
			".386p" \
			"mov dr0,eax" \
			parm nomemory [eax]\
			modify exact nomemory [ ];

#pragma aux wrdr1 = \
			".386p" \
			"mov dr1,eax" \
			parm nomemory [eax] \
			modify exact nomemory [ ];

#pragma aux wrdr2 = \
			".386p" \
			"mov dr2,eax" \
			parm nomemory [eax] \
			modify exact nomemory [ ];

#pragma aux wrdr3 = \
			".386p" \
			"mov dr3,eax" \
			parm nomemory [eax] \
			modify exact nomemory [ ];

#pragma aux wrdr6 = \
			".386p" \
			"mov dr6,eax" \
			parm nomemory [eax] \
			modify exact nomemory [ ];

#pragma aux wrdr7 = \
			".386p" \
			"mov dr7,eax" \
			parm nomemory [eax] \
			modify exact nomemory [ ];

#pragma aux wrtr = \
			".486p" \
			"ltr ax" \
			parm nomemory [eax] \
			modify exact nomemory [ ];

#pragma aux rdtr = \
			".386p" \
			"xor eax,eax" \
			"str ax" \
			parm nomemory [ ] \
			modify exact nomemory [eax];

#pragma aux clts = \
			".386p" \
			"clts" \
			parm nomemory [ ] \
			modify exact nomemory [ ];

#pragma aux rdmsr = \
			".386p" \
			"db 0fh,32h" \
			parm nomemory [ecx] \
			modify exact nomemory [eax edx];

#pragma aux wrmsr = \
			".386p" \
			"db 0fh,30h" \
			parm nomemory [ecx] [eax edx] \
			modify exact nomemory [ ];

#elif defined(__GNUC__) || defined(__INTEL_COMPILER)

#define HALT() __asm__ __volatile__ ( "hlt": : :"memory")

#define sldt() ({ register _uint16 __ldt; __asm__ ( "sldt %w0": "=q" (__ldt) : : "memory"); __ldt; })

#define setts() ((void)({ register _uint16 __reg; __asm__ __volatile__( "smsw %w0\n\torb $8,%b0\n\tlmsw %w0": "=q" (__reg):); }))

#define lgdt(__gdt) ((void)({__asm__ ( "lgdt (%0)": : "r" (__gdt) : "memory"); }))
#define sgdt(__gdt) __asm__ ( "sgdt (%0)": : "r" (__gdt): "memory" )

#define invlpg(__p) ((void)({__asm__ ("invlpg %0": : "m" (*(char *)__p): "memory"); }))

#define lidt(__idt) ((void)({__asm__ ( "lidt (%0)": : "r" (__idt)); }))
#define sidt(__idt) ((void)({void *__ptr = (__idt); __asm__ ( "sidt (%0)":: "r" (__ptr): "memory"); }))

#define ldpgdir(__dir) ((void)({__asm__ ( "movl %0,%%cr3": :"r" (__dir)); }))
#define rdpgdir() ({register _uint32 __dir; __asm__ ( "movl %%cr3,%0": "=q" (__dir):); __dir; })

#define ldcr0(__flags) ((void)({__asm__ ( "movl %0,%%cr0": :"r" (__flags)); }))
#define rdcr0() ({register _uint32 __flags; __asm__ ( "movl %%cr0,%0": "=q" (__flags):); __flags; })

#define ldcr4(__flags) ((void)({__asm__ ( "movl %0,%%cr4": :"r" (__flags)); }))
#define rdcr4() ({register _uint32 __flags; __asm__ ( "movl %%cr4,%0": "=q" (__flags):); __flags; })

#define flushtlb()	({InterruptDisable();ldpgdir(rdpgdir());InterruptEnable();})

#define flushcache() ((void)({__asm__ __volatile__ ( "wbinvd": : : "memory"); }))

#define wrdr0(__flags) ((void)({__asm__ ( "movl %0,%%db0": :"r" (__flags)); }))
#define wrdr1(__flags) ((void)({__asm__ ( "movl %0,%%db1": :"r" (__flags)); }))
#define wrdr2(__flags) ((void)({__asm__ ( "movl %0,%%db2": :"r" (__flags)); }))
#define wrdr3(__flags) ((void)({__asm__ ( "movl %0,%%db3": :"r" (__flags)); }))
#define wrdr6(__flags) ((void)({__asm__ ( "movl %0,%%db6": :"r" (__flags)); }))
#define wrdr7(__flags) ((void)({__asm__ ( "movl %0,%%db7": :"r" (__flags)); }))

#define rddr0() ({register _uint32 __flags; __asm__ ( "movl %%db0,%0": "=q" (__flags):); __flags; })
#define rddr1() ({register _uint32 __flags; __asm__ ( "movl %%db1,%0": "=q" (__flags):); __flags; })
#define rddr2() ({register _uint32 __flags; __asm__ ( "movl %%db2,%0": "=q" (__flags):); __flags; })
#define rddr3() ({register _uint32 __flags; __asm__ ( "movl %%db3,%0": "=q" (__flags):); __flags; })
#define rddr6() ({register _uint32 __flags; __asm__ ( "movl %%db6,%0": "=q" (__flags):); __flags; })
#define rddr7() ({register _uint32 __flags; __asm__ ( "movl %%db7,%0": "=q" (__flags):); __flags; })

#define wrtr(__tr) ((void)({register _uint16 __tmp = (__tr); __asm__ ( "ltr %w0": : "r" (__tmp)); }))
#define rdtr() ({register _uint16 __tr; __asm__ ( "str %w0": "=q" (__tr):); __tr; })

#define clts() ((void)({__asm__ __volatile__ ( "clts": :); }))

#define rdmsr(__idx)	({ register _uint64 __value; register int __i = (__idx); __asm__( \
						"rdmsr" \
						: "=A" (__value): "c" (__i)); __value; })

#define wrmsr(__idx, __value)	((void)({ register _uint64 __v = (__value); register int __i = (__idx); __asm__( \
						"wrmsr" \
						: : "c" (__i), "A" (__v)); }))

#elif defined(__MWERKS__)

#define __MWINL inline __declspec(naked)

/* MetroWerks inline assembler for x86 doesn't support these properly yet */
#define REGEAX 0
#define REGECX 1
#define REGEDX 2
#define REGEBX 3
#define REGESP 4
#define REGEBP 5
#define REGESI 6
#define REGEDI 7

#define __MW_MOVTOCR(cr, r)        DB 0x0F, 0x22, 0xC0 + (cr * 8) + r
#define __MW_MOVFROMCR(r, cr)      DB 0x0F, 0x20, 0xC0 + (cr * 8) + r
#define __MW_MOVTODR(dr, r)        DB 0x0F, 0x23, 0xC0 + (dr * 8) + r
#define __MW_MOVFROMDR(r, dr)      DB 0x0F, 0x21, 0xC0 + (dr * 8) + r

static __MWINL void HALT(void) {
	asm {
		hlt
	}
}

static __MWINL _uint16 sldt(void) {
	asm {
		/* .286p  GKM */
		sldt ax
	}
}

static __MWINL void setts(void) {
	asm {
		/* .286p  GKM */
		smsw ax
		or al,8
		lmsw ax
	}
}

static __MWINL void lgdt(void *__gdt) {
	asm {
		push esi
		mov esi, __gdt
		lgdt [esi]
		pop esi
	}
}

static __MWINL void lidt(void *__idt) {
	asm {
		push esi
		mov esi, __idt
		lidt [esi]
		pop esi
	}
}

static __MWINL void sgdt(void *__gdt) {
	asm {
		mov eax, __gdt
		sgdt [eax]
	}
}

static __MWINL void sidt(void *__idt) {
	asm {
		mov eax, __idt
		sidt [eax]
	}
}

static __MWINL void invlpg(void *__p) {
	asm {
		mov eax, __p
		invlpg [eax]
	}
}

static __MWINL void ldpgdir(void *__p) {
	asm {
		mov eax, __p
		__MW_MOVTOCR(3, REGEAX) /* mov cr3, eax */
	}
}
	
static __MWINL void *rdpgdir(void) {
	asm {
		__MW_MOVFROMCR(REGEAX, 3) /* mov eax, cr3 */
	}
}

static __MWINL void ldcr0(int __flags) {
	asm {
		mov eax, __flags
		__MW_MOVTOCR(0, REGEAX) /* mov cr0, eax */
	}
}

static __MWINL int rdcr0(void) {
	asm {
		__MW_MOVFROMCR(REGEAX, 0) /* mov eax, cr0 */
	}
}

static __MWINL void flushtlb(void) {
	asm {
		__MW_MOVFROMCR(REGEAX, 3) /* mov eax, cr3 */
		__MW_MOVTOCR(3, REGEAX) /* mov cr3, eax */
	}
}

static __MWINL void flushcache(void) {
	asm {
		wbinvd
	}
}

static __MWINL char *rddr0(void) {
	asm {
		__MW_MOVFROMDR(REGEAX, 0) /* mov eax, dr0 */
	}
}

static __MWINL char *rddr1(void) {
	asm {
		__MW_MOVFROMDR(REGEAX, 1) /* mov eax, dr1 */
	}
}

static __MWINL char *rddr2(void) {
	asm {
		__MW_MOVFROMDR(REGEAX, 2) /* mov eax, dr2 */
	}
}

static __MWINL char *rddr3(void) {
	asm {
		__MW_MOVFROMDR(REGEAX, 3) /* mov eax, dr3 */
	}
}

static __MWINL char *rddr6(void) {
	asm {
		__MW_MOVFROMDR(REGEAX, 6) /* mov eax, dr6 */
	}
}

static __MWINL char *rddr7(void) {
	asm {
		__MW_MOVFROMDR(REGEAX, 7) /* mov eax, dr7 */
	}
}

static __MWINL char *wrdr0(unsigned __r) {
	asm {
		mov eax, __r
		__MW_MOVTODR(0, REGEAX) /* mov dr0, eax */
	}
}

static __MWINL char *wrdr1(unsigned __r) {
	asm {
		mov eax, __r
		__MW_MOVTODR(1, REGEAX) /* mov dr1, eax */
	}
}

static __MWINL char *wrdr2(unsigned __r) {
	asm {
		mov eax, __r
		__MW_MOVTODR(2, REGEAX) /* mov dr2, eax */
	}
}

static __MWINL char *wrdr3(unsigned __r) {
	asm {
		mov eax, __r
		__MW_MOVTODR(3, REGEAX) /* mov dr3, eax */
	}
}

static __MWINL char *wrdr6(unsigned __r) {
	asm {
		mov eax, __r
		__MW_MOVTODR(6, REGEAX) /* mov dr6, eax */
	}
}

static __MWINL char *wrdr7(unsigned __r) {
	asm {
		mov eax, __r
		__MW_MOVTODR(7, REGEAX) /* mov dr7, eax */
	}
}

static __MWINL unsigned wrtr(unsigned __tr) {
	asm {
		mov eax, __tr
		ltr ax
	}
}

static __MWINL unsigned rdtr(void) {
	asm {
		xor eax, eax
		str ax
	}
}

static __MWINL void clts(void) {
	asm {
		clts
	}
}

#else
#error Compiler not defined.
#endif

__END_DECLS

#endif

/* __SRCVERSION("priv.h $Rev: 224746 $"); */
