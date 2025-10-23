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
 * ARM PrimeCell Peripherals
 *
 */

#ifndef	__ARM_PRIMECELL_H_INCLUDED
#define	__ARM_PRIMECELL_H_INCLUDED

/*
 * --------------------------------------------------------------------------
 * PrimeCell UART Registers
 * --------------------------------------------------------------------------
 */
#define	PRIMECELL_UART_SIZE	0x20
#define	PRIMECELL_UART_DR	0x00	/* data */
#define	PRIMECELL_UART_RSR	0x04	/* receive status */
#define	PRIMECELL_UART_ECR	0x04	/* error clear */
#define	PRIMECELL_UART_LCRH	0x08	/* line control */
#define	PRIMECELL_UART_LCRM	0x0c	/* line control (baud bits 8-15) */
#define	PRIMECELL_UART_LCRL	0x10	/* line control (baud bits 0-7) */
#define	PRIMECELL_UART_CR	0x14	/* control */
#define	PRIMECELL_UART_FR	0x18	/* status flags */
#define	PRIMECELL_UART_IIR	0x1c	/* interrupt identification */
#define	PRIMECELL_UART_ICR	0x1c	/* interrupt clear */

/*
 * RSR register bits
 */
#define	PRIMECELL_UART_RSR_OE	0x08	/* overrun error */
#define	PRIMECELL_UART_RSR_BE	0x04	/* break error */
#define	PRIMECELL_UART_RSR_PE	0x02	/* parity error */
#define	PRIMECELL_UART_RSR_FE	0x01	/* framing error */

/*
 * LCRH register bits
 */
#define	PRIMECELL_UART_LCRH_8BIT	0x60	/* 8 data bits */
#define	PRIMECELL_UART_LCRH_7BIT	0x40	/* 7 data bits */
#define	PRIMECELL_UART_LCRH_6BIT	0x20	/* 6 data bits */
#define	PRIMECELL_UART_LCRH_5BIT	0x00	/* 5 data bits */
#define	PRIMECELL_UART_LCRH_FEN		0x10	/* fifo enable */
#define	PRIMECELL_UART_LCRH_STP2	0x08	/* 2 stop bits */
#define	PRIMECELL_UART_LCRH_EPS		0x04	/* even parity */
#define	PRIMECELL_UART_LCRH_PEN		0x02	/* parity enable */
#define	PRIMECELL_UART_LCRH_BRK		0x01	/* send break */

/*
 * CR register bits
 */
#define	PRIMECELL_UART_CR_LBE		0x80	/* loopback enable */
#define	PRIMECELL_UART_CR_RTIE		0x40	/* rx timeout interrupt enable */
#define	PRIMECELL_UART_CR_TIE		0x20	/* tx interrupt enable */
#define	PRIMECELL_UART_CR_RIE		0x10	/* rx interrupt enable */
#define	PRIMECELL_UART_CR_MSIE		0x08	/* modem status interrupt enable */
#define	PRIMECELL_UART_CR_UARTEN	0x01	/* uart enable */

/*
 * FR register bits
 */
#define	PRIMECELL_UART_FR_TXFE		0x80	/* tx fifo empty */
#define	PRIMECELL_UART_FR_RXFF		0x40	/* rx fifo full */
#define	PRIMECELL_UART_FR_TXFF		0x20	/* tx fifo full */
#define	PRIMECELL_UART_FR_RXFE		0x10	/* rx fifo empty */
#define	PRIMECELL_UART_FR_BUSY		0x08	/* uart busy */
#define	PRIMECELL_UART_FR_DCD		0x04	/* data carrier detect */
#define	PRIMECELL_UART_FR_DSR		0x02	/* data set ready */
#define	PRIMECELL_UART_FR_CTS		0x01	/* clear to send */

/*
 * IIR register bits
 */
#define	PRIMECELL_UART_IIR_RTIS		0x08	/* rx timeout interrupt */
#define	PRIMECELL_UART_IIR_TIS		0x04	/* tx interrupt */
#define	PRIMECELL_UART_IIR_RIS		0x02	/* rx interrupt */
#define	PRIMECELL_UART_IIR_MIS		0x01	/* modem status interrupt */

/*
 * --------------------------------------------------------------------------
 * PrimeCell Keyboard/Mouse Registers
 * --------------------------------------------------------------------------
 */

#define	PRIMECELL_KMI_SIZE			0x14
#define	PRIMECELL_KMI_CR			0x00	/* control register */
#define	PRIMECELL_KMI_STAT			0x04	/* status register */
#define	PRIMECELL_KMI_DATA			0x08	/* data register */
#define	PRIMECELL_KMI_CLKDIV		0x0c	/* clock divisor register */
#define	PRIMECELL_KMI_IR			0x10	/* interrupt identification */

/*
 * CR register bits
 */
#define	PRIMECELL_KMI_CR_TYPE		0x20	/* type (0 = PS2/AT) */
#define	PRIMECELL_KMI_CR_RIEN		0x10	/* rx interrupt enable */
#define	PRIMECELL_KMI_CR_TIEN		0x08	/* tx interrupt enable */
#define	PRIMECELL_KMI_CR_KMIEN		0x04	/* KMI enable */
#define	PRIMECELL_KMI_CR_FKMID		0x02	/* force KMI data low */
#define	PRIMECELL_KMI_CR_FKMIC		0x01	/* force KMI clock low */

/*
 * STAT register bits
 */
#define	PRIMECELL_KMI_STAT_TXEMPTY	0x40	/* tx data status */
#define	PRIMECELL_KMI_STAT_TXBUSY	0x20	/* tx status */
#define	PRIMECELL_KMI_STAT_RXFULL	0x10	/* rx data status */
#define	PRIMECELL_KMI_STAT_RXBUSY	0x08	/* rx status */
#define	PRIMECELL_KMI_STAT_RXPARITY	0x04	/* rx parity bit (odd parity) */
#define	PRIMECELL_KMI_STAT_KMIC		0x02	/* KMI clock input status */
#define	PRIMECELL_KMI_STAT_KMID		0x01	/* KMI data input status */

/*
 * IR register bits
 */
#define	PRIMECELL_KMI_IR_TXINTR		0x02	/* tx interrupt */
#define	PRIMECELL_KMI_IR_RXINTR		0x01	/* rx interrupt */

/*
 * --------------------------------------------------------------------------
 * PrimeCell RTC Registers
 * --------------------------------------------------------------------------
 */

#define	PRIMECELL_RTC_SIZE			0x14
#define	PRIMECELL_RTC_DR			0x00	/* data register */
#define	PRIMECELL_RTC_MR			0x04	/* match register */
#define	PRIMECELL_RTC_STAT			0x08	/* status register */
#define	PRIMECELL_RTC_EOI			0x08	/* interrupt clear register */
#define	PRIMECELL_RTC_LR			0x0c	/* counter load register */
#define	PRIMECELL_RTC_CR			0x10	/* control register */

#endif	/* __ARM_PRIMECELL_H_INCLUDED */


#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/hardware/devc/public/arm/primecell.h $ $Rev: 219612 $" )
