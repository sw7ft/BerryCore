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
 * QnxWin Interface
 *

 *
 */
#ifndef __X86_QNXWIN_H_INCLUDED
#define __X86_QNXWIN_H_INCLUDED

struct qnxwin_xfer {
	unsigned	tunnel_paddr;
	void		*tunnel_vaddr;
	void		(*rtos_idle)(void);
	void		(*rtos_clock)(unsigned tick); //ZZZ: temp, see main.c
};

#endif

/* __SRCVERSION("qnxwin.h $Rev: 169801 $"); */
