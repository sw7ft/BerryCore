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






#ifndef	__ARM_PL011_INC__
#define	__ARM_PL011_INC__

#define	PL011_SIZE		0x100

/*
 * --------------------------------------------------------------------------
 * PL011 UART Registers
 * --------------------------------------------------------------------------
 */
#define	PL011_DR		0x00	/* Data register */
#define	PL011_RSR		0x04	/* Receive status register */
#define	PL011_ECR		0x04	/* Error Clear register */
#define	PL011_DMAWM		0x08	/* DMA Water Mark register */
#define	PL011_TIMEOUT	0x0C	/* Timeour register */
#define	PL011_FR		0x18	/* Flag register */
#define	PL011_LCR_R		0x1C	/* Receive Line control register */
#define	PL011_ILPR		0x20	/* IrDA low-power counter register */
#define	PL011_IBRD		0x24	/* Integer baud rate register */
#define	PL011_FBRD		0x28	/* Fractional baud rate register */
#define	PL011_LCR_H		0x2C	/* TX Line control register */
#define	PL011_CR		0x30	/* Control register */
#define	PL011_IFLS		0x34	/* Interrupt FIFO level select register */
#define	PL011_IMSC		0x38	/* Interrupt mask set/clear register */
#define	PL011_RIS		0x3C	/* Raw interrupt status register */
#define	PL011_MIS		0x40	/* Masked interrupt status register */
#define	PL011_ICR		0x44	/* Interrupt clear register */
#define	PL011_DMACR		0x48	/* DMA control register */

/*
 * DR register bits
 */
#define	PL011_DR_OE			(1 << 11)	/* Overrun error */
#define	PL011_DR_BE			(1 << 10)	/* Break error */
#define	PL011_DR_PE			(1 <<  9)	/* Parity error */
#define	PL011_DR_FE			(1 <<  8)	/* Frame error */

/*
 * RSR register bits
 */
#define	PL011_RSR_OE		(1 << 3)	/* Overrun error */
#define	PL011_RSR_BE		(1 << 2)	/* Break error */
#define	PL011_RSR_PE		(1 << 1)	/* Parity error */
#define	PL011_RSR_FE		(1 << 0)	/* Frame error */

/*
 * ECR register bits
 */
#define	PL011_ECR_OE		(1 << 3)	/* Overrun error */
#define	PL011_ECR_BE		(1 << 2)	/* Break error */
#define	PL011_ECR_PE		(1 << 1)	/* Parity error */
#define	PL011_ECR_FE		(1 << 0)	/* Frame error */

/*
 * FR register bits
 */
#define	PL011_FR_TXFE		(1 << 7)	/* Transmit FIFO empty */
#define	PL011_FR_RXFF		(1 << 6)	/* Receive FIFO full */
#define	PL011_FR_TXFF		(1 << 5)	/* Transmit FIFO full */
#define	PL011_FR_RXFE		(1 << 4)	/* Receive FIFO empty */
#define	PL011_FR_BUSY		(1 << 3)	/* UART Busy */
#define	PL011_FR_DCD		(1 << 2)	/* Data carrier detect */
#define	PL011_FR_DSR		(1 << 1)	/* Data set ready */
#define	PL011_FR_CTS		(1 << 0)	/* Clear to send */


/*
 * LCR_H register bits
 */
#define	PL011_LCR_H_SPS		(1 << 7)	/* Stick parity select */
#define	PL011_LCR_H_WLEN8	(3 << 5)	/* 8 bit len */
#define	PL011_LCR_H_WLEN7	(2 << 5)	/* 7 bit len */
#define	PL011_LCR_H_WLEN6	(1 << 5)	/* 6 bit len */
#define	PL011_LCR_H_WLEN5	(0 << 5)	/* 5 bit len */
#define	PL011_LCR_H_FEN		(1 << 4)	/* Enable FIFOs */
#define	PL011_LCR_H_STP2	(1 << 3)	/* 2 Stop bits select */
#define	PL011_LCR_H_EPS		(1 << 2)	/* Even parity select */
#define	PL011_LCR_H_PEN		(1 << 1)	/* Parity enable */
#define	PL011_LCR_H_BRK		(1 << 0)	/* Send break */


/*
 * CR register bits
 */
#define	PL011_CR_CTSEn		(1 << 15)	/* CTS hardware flow control enable */
#define	PL011_CR_RTSEn		(1 << 14)	/* RTS hardware flow control enable */
#define	PL011_CR_RTS		(1 << 11)	/* Request to send */
#define	PL011_CR_DTR		(1 << 10)	/* Data transmit ready */
#define	PL011_CR_RXE		(1 <<  9)	/* Receive enable */
#define	PL011_CR_TXE		(1 <<  8)	/* Transmit enable */
#define	PL011_CR_LBE		(1 <<  7)	/* Loop back enable */
#define	PL011_CR_OVSFACT	(1 <<  3)	/* UART Over Sampling Factor */
#define	PL011_CR_UARTEN		(1 <<  0)	/* UART enable */


/*
 * IMSC register bits
 */
#define	PL011_IMSC_TXFEIM	(1 << 12)	/* Transmit FIFO Empty interrupt */
#define	PL011_IMSC_OEIM		(1 << 10)	/* Overrun error interrupt mask */
#define	PL011_IMSC_RTIM		(1 <<  6)	/* Receive timeout interrupt mask */
#define	PL011_IMSC_TXIM		(1 <<  5)	/* Transmit interrupt mask */
#define	PL011_IMSC_RXIM		(1 <<  4)	/* Receive interrupt mask */
#define PL011_IMSC_CTSRM	(1 <<  1)	/*Clear To Send Modem Masked Interrupt Status */



/*
 * MIS register bits
 */
#define	PL011_MIS_TXFES		(1 << 12)	/* Transmit FIFO Empty interrupt */
#define	PL011_MIS_RTMIS		(1 << 6)	/* Receive timeout masked interrupt status */
#define	PL011_MIS_TXMIS		(1 << 5)	/* Transmit masked interrupt status */
#define	PL011_MIS_RXMIS		(1 << 4)	/* Receive masked interrupt status */
#define PL011_MIS_CTSRMIS	(1 << 1)	/*Clear To Send Modem Interrupt Status */


/*
 * ICR register bits
 */
#define	PL011_ICR_RTIC		(1 << 6)	/* Receive timeout interrupt clear */
#define	PL011_ICR_TXIC		(1 << 5)	/* Transmit interrupt clear */
#define	PL011_ICR_RXIC		(1 << 4)	/* Receive interrupt clear */

/*
 * DMACR register bits
 */
#define	PL011_DMACR_ONERR	(1 << 2)	/* Receive DMA on error */
#define	PL011_DMACR_TXE		(1 << 1)	/* Transmit DMA Enable */
#define	PL011_DMACR_RXE		(1 << 0)	/* Receive DMA Enable */



#endif		/* __ARM_PL011_INC__ */

/* __SRCVERSION("pl011.h $Rev: 323636 $"); */
