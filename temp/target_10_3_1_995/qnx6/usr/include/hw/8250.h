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

#include <sys/srcversion.h>







/*
 * Definitions for an 8250 style serial device
 *
 */

/* Offset definitions for registers */
#define REG_RX		0		/*R  Receive*/
#define REG_TX		0		/*W  Transmit*/
#define REG_DL0		0		/*W  Divisor Latch 0*/
#define REG_DL1		1		/*W  Divisor Latch 1*/
#define REG_IE		1		/*RW Interrupt Enable*/
#define REG_II		2		/*R  Interrupt Identification*/
#define REG_FC		2		/*W  Fifo Control*/
#define REG_LC		3		/*RW Line Control*/
#define REG_MC		4		/*RW Modem Control*/
#define REG_LS		5		/*RW Line Status*/
#define REG_MS		6		/*RW Modem Status*/
#define REG_TOTAL	8		/*total number of possible 8250 registers*/

/* Bit definittion for interrupt enable (REG_IE) */
#define IE_RX	0x1
#define IE_TX	0x2
#define IE_LS	0x4
#define IE_MS	0x8

/* Bit definitions for interrupt identification (REG_II) */
#define II_NOINTR	0x01
#define II_MS		0x00
#define II_TX		0x02
#define II_RX		0x04
#define II_LS		0x06
#define II_FIFO		0x80

/* Bit definitions for line control (REG_LC) */
#define LCR_BITS_MASK	0x03
#define LCR_STB2		0x04
#define LCR_PEN			0x08
#define LCR_EPS			0x10
#define LCR_SPS			0x20
#define LCR_BREAK		0x40
#define LCR_DLAB		0x80

/* Bit definitions for modem control (REG_MC) */
#define MCR_DTR			0x01
#define MCR_RTS			0x02
#define MCR_OUT1		0x04
#define MCR_OUT2		0x08
#define MCR_LOOPBACK	0x10

/* Bit definitions for line status (REG_LS) */
#define LSR_RXRDY		0x01
#define LSR_OE			0x02
#define LSR_PE			0x04
#define LSR_FE			0x08
#define LSR_BI			0x10
#define LSR_TXRDY		0x20
#define LSR_TSRE		0x40
#define LSR_RCV_FIFO	0x80

/* Bit definitions for modem status (REG_MS) */
#define MSR_DCTS		0x01
#define MSR_DDSR		0x02
#define MSR_DRING		0x04
#define MSR_DDCD		0x08
#define MSR_CTS			0x10
#define MSR_DSR			0x20
#define MSR_RING		0x40
#define MSR_DCD			0x80

/* Bit definitions for modem status (REG_FC) */
#define FCR_FIFO_ENABLE		0x01
#define FCR_RX_FIFO_RESET	0x02
#define FCR_TX_FIFO_RESET	0x04
#define FCR_RX_TRIG_1		0x00
#define FCR_RX_TRIG_4		0x40
#define FCR_RX_TRIG_8		0x80
#define FCR_RX_TRIG_14		0xC0



__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/hardware/devc/public/hw/8250.h $ $Rev: 238074 $" )
