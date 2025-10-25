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
 * X86 interrupt classes
 *
 */
#ifndef __X86_INTR_H_INCLUDED
#define __X86_INTR_H_INCLUDED

/*
 * X86 specific interrupt classes
 */
#define	X86_INTR_CLASS_NMI			(0x8000UL << 16)
#define X86_INTR_NMI				(X86_INTR_CLASS_NMI + 0)
#define X86_INTR_CLASS_MSI			(_NTO_INTR_CLASS_EXTERNAL + 256)
#define	X86_INTR_CLASS_APIC			(0x8001UL << 16)
/*
 * the following APIC defined interrupt numbers do not apply to startup-apic.
 * The interrupt number for these devices should be obtained from the HWINFO
 * section of the syspage
*/
#define X86_INTR_APIC_TIMER			(X86_INTR_CLASS_APIC + 0)
#define X86_INTR_APIC_THERMAL		(X86_INTR_CLASS_APIC + 1)
#define X86_INTR_APIC_PERFORMANCE	(X86_INTR_CLASS_APIC + 2)
#define X86_INTR_APIC_LINT0			(X86_INTR_CLASS_APIC + 3)
#define X86_INTR_APIC_LINT1			(X86_INTR_CLASS_APIC + 4)
#define X86_INTR_APIC_ERROR			(X86_INTR_CLASS_APIC + 5)

/*
** Definitions for all i386 GDT and IDT entries. Missing entries are invalid.
**
** GDT - 32 + PROCESSORS_MAX + (PROCESSORS_MAX - 8) entries (88 for PROCESSORS_MAX == 32)
**
** IMPORTANT: This table (and the associated initialization code) currently
**            accommodates 32 CPU's
**
** You will notice that the per CPU segment descriptors are not contiguous.
** Originally, when this table was laid out, it was done for 8 processors.
** The move to 32 CPU's required the table to be expanded however instead of
** moving all of the per CPU segment registers to the entry at 0x200, it was
** decided to leave the existing 8 in their current slot (allowing a mix of
** new and old startups and procnto's to continue to work together for
** <= 8 CPU's).
**
** Also, the additional 24 per CPU segment descriptors are placed *after* the
** existing per CPU TSS descriptors eliminating the need to change the GETCPU
** macro (in services/system/ker/x86/util.ah) with its system wide impact
**
** There are some really ugly calculations in the x86 CPU initialization code.
** Search for "GDT_CALCULATION" for comments related to the interdependency of
** the startup/procnto changes
**
** 00 -               08 - GDT itself     10 - IDT            18 - 
** 20 - sysseg0       28 - sysseg1        30 - sysseg2        38 - sysseg3
** 40 - sysseg4       48 - sysseg5        50 - sysseg6        58 - sysseg7
** 60 -               68 -                70 -                78 - Phys page 1 (V86)
** 80 - Kernel CS(0)  88 - Kernel DS(0)   90 - Proc CS(1)     98 - Proc DS(1)
** A0 - LDT           A8 -                B0 -                B8 -
** C0 - User CS(3)    C8 - User DS(3)     D0 -                D8 -
** E0 -               E8 -                F0 -                F8 -

**100 - TSS cpu0     108 - TSS cpu1      110 - TSS cpu2      118 - TSS cpu3
**120 - TSS cpu4     128 - TSS cpu5      130 - TSS cpu6      138 - TSS cpu7
**140 - TSS cpu8     148 - TSS cpu9      150 - TSS cpu10     158 - TSS cpu11
**160 - TSS cpu12    168 - TSS cpu13     170 - TSS cpu14     178 - TSS cpu15
**180 - TSS cpu16    188 - TSS cpu17     190 - TSS cpu18     198 - TSS cpu19
**1A0 - TSS cpu20    1A8 - TSS cpu21     1B0 - TSS cpu22     1B8 - TSS cpu23
**1C0 - TSS cpu24    1C8 - TSS cpu25     1D0 - TSS cpu26     1D8 - TSS cpu27
**1E0 - TSS cpu28    1E8 - TSS cpu29     1F0 - TSS cpu30     1F8 - TSS cpu31

**200 - sysseg8      208 - sysseg9       210 - sysseg10      218 - sysseg11
**220 - sysseg12     228 - sysseg13      230 - sysseg14      238 - sysseg15
**240 - sysseg16     248 - sysseg17      250 - sysseg18      258 - sysseg19
**260 - sysseg20     268 - sysseg21      270 - sysseg22      278 - sysseg23
**280 - sysseg24     288 - sysseg25      290 - sysseg26      298 - sysseg27
**2A0 - sysseg28     2A8 - sysseg29      2B0 - sysseg30      2B8 - sysseg31
*/

/*
** LDT - 5 entries
** There is only one LDT for the system and it is overlaid ontop of the GDT
** starting at GDT entry A8.
**
** 04 -               0C -                14 -                1C - User CS(3)
** 24 - User DS(3)
*/
/*
** IDT - 48 entries plus whatever is used for hardware interrupts
** vec
** 00  000 - Div 0        008 - Debug       010 - NMI          018 - Brkpoint
** 04  020 - INTO         028 - BOUND       030 - ILL OPCODE   038 - Dev NA
** 08  040 - Double fault 048 - reserved    050 - Inv TSS      058 - Seg NP
** 0c  060 - Stack fault  068 - GP fault    070 - Page fault   078 - reserved
** 10  080 - FPU error    088 - Alignment   090 - Reserved     098 - Reserved
** 14  0A0 - Reserved     0A8 - Reserved    0B0 - Reserved     0B8 - Reserved
** 18  0C0 - Reserved     0C8 - Reserved    0D0 - Reserved     0D8 - Reserved
** 1c  0E0 - Reserved     0E8 - Reserved    0F0 - Reserved     0F8 - Reserved
** 20  100 - Kdebug trap  108 - Kdebug msg  110 -              118 -         
** 24  120 -              128 -             130 - SMP IPI      138 - SMP IPI
** 28  140 - Kernel call  148 -             150 -              158 -
** 2c  160 -              168 -             170 -              178 - APIC spurious
** 30  180 - Hardware vectors....
*/

#endif

/* __SRCVERSION("intr.h $Rev: 278639 $"); */
