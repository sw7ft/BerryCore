/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
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
 *  cis.h
 *
 *	Card Information Structure defintions.
 *


 *  Referenced PCMCIA Standards Specification
 */

#ifndef __PCMCIA_CIS_H_INCLUDED
#define __PCMCIA_CIS_H_INCLUDED

/* Layer 1 Basic Compatibility Tuples */
#define CISTPL_NULL					0x00
#define CISTPL_DEVICE				0x01
#define CISTPL_CHECKSUM				0x10
#define CISTPL_LONGLINK_A			0x11
#define CISTPL_LONGLINK_C			0x12
#define CISTPL_LINKTARGET			0x13
#define CISTPL_NO_LINK				0x14
#define CISTPL_VERS_1				0x15
#define CISTPL_ALTSTR				0x16
#define CISTPL_DEVICE_A				0x17
#define CISTPL_JEDEC_C				0x18
#define CISTPL_JEDEC_A				0x19
#define CISTPL_CONFIG				0x1A
#define CISTPL_CFTABLE_ENTRY		0x1B
#define CISTPL_DEVICE_OC			0x1C
#define CISTPL_DEVICE_OA			0x1D
#define CISTPL_DEVICE_GEO			0x1E
#define CISTPL_DEVICE_GEO_A			0x1F
/* Layer 2 Data Recording Format Tuples */
#define CISTPL_MANFID				0x20
#define CISTPL_FUNCID				0x21
#define CISTPL_FUNCE				0x22
#define CISTPL_SWIL					0x23
#define CISTPL_VERS_2				0x40
#define CISTPL_FORMAT				0x41
#define CISTPL_GEOMETRY				0x42
#define CISTPL_BYTEORDER			0x43
#define CISTPL_DATE					0x44
#define CISTPL_BATTERY				0x44
/* Layer 3 Data Organization Tuples */
#define CISTPL_ORG					0x46
/* Layer 4 System-Specific Standard Tuples */
#define CISTPL_LAST					0x8F
/* Last valid typle # */
#define CISTPL_END					0xFF

/* Data Organization codes */
#define TPLORGTYPE_FS				0
#define TPLORGTYPE_APP				1
#define TPLORGTYPE_ROMCODE			2

/* Device Type codes */
#define DTYPE_NULL					0x00
#define DTYPE_ROM					0x01
#define DTYPE_OTPROM				0x02
#define DTYPE_EPROM					0x03
#define DTYPE_EEPROM				0x04
#define DTYPE_FLASH					0x05
#define DTYPE_SRAM					0x06
#define DTYPE_DRAM					0x07
#define DTYPE_FUNCSPEC				0x0d

#endif

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/pccard/public/sys/cis.h $ $Rev: 219996 $" )
