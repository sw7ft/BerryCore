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
 *  sys/pccard.h
 *

 *
 */
#ifndef __PCCARD_H_INCLUDED
#define __PCCARD_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#ifndef _FCNTL_H_INCLUDED
 #include <fcntl.h>
#endif

#include	<inttypes.h>

#define	PCCARD_NAME				"qnx/pccard"

#define _PCCARD_MAX_WINDOWS		10

typedef	int32_t		mpid_t;
typedef	int32_t		nid_t;

struct _pccard_info {
	int16_t				socket;			/* Socket number (0 based) */
	uint16_t			status;			/* Card status (from socket services spec) */
	uint32_t			flags;			/* Flags (_PCCARD_FLAG_*) */
	uint8_t				vcc;			/* Current Vcc (in tenths of volts) */
	uint8_t				vpp;			/* Current Vpp (in tenths of volts) */
	uint8_t				num_windows;	/* Number of windows described below */
	uint8_t				index;			/* Index for CardBus devices */
	uint16_t			manufacturer;	/* Manufacturer ID from PCCARD */
	uint16_t			card_type;		/* Card Type from PCCARD */
	uint16_t			device_id;		/* CardBus device id */
	uint16_t			vendor_id;		/* CardBus vendor id */
	uint16_t			busnum;			/* PCI bus number */
	uint16_t			devfuncnum;		/* PCI device and function number */
	struct _pccard_window {
		uint16_t				window;		/* Window type (_PCCARD_WINDOW_*) */
		uint16_t				flags;		/* Window flags (_PCCARD_WINFLAG_*) */
		mpid_t					pid;		/* Locking pid */
		uint16_t				device;		/* Device type (_PCCARD_DEV_*) */
		uint16_t				dummy;
		uint32_t				dev_size;	/* Size of memory device */
		uint32_t				reserved3;
		union {
			struct _pccard_irq {
				uint32_t			flags;			/* (_PCCARD_IRQFLAG_*) */
				uint32_t			irq;
			}						irq;
			struct _pccard_memio {
				uint32_t			base;			/* Base address (in host address space) */
				uint32_t			size;			/* Size of window */
				uint32_t			offset;			/* offset of region from base of card */
				uint16_t			flags;			/* (_PCCARD_MEMIOFLAG_*) */
				uint8_t				hw_window;		/* Actual hardware window */
				uint8_t				dummy2;
			}						memio;
		} un;
	} window[_PCCARD_MAX_WINDOWS];
};

typedef int32_t pccard_t;

#define _PCCARD_STATUS_WP			0x0001		/* same as socket services */
#define _PCCARD_STATUS_BVD1			0x0010
#define _PCCARD_STATUS_BVD2			0x0020
#define _PCCARD_STATUS_RDYBSY		0x0040
#define _PCCARD_STATUS_CD			0x0080

#define _PCCARD_FLAG_CARD			0x00000001	/* Card inserted in slot */
#define _PCCARD_FLAG_BATT_LOW		0x00000002	/* Card battery is low */
#define _PCCARD_FLAG_CONFIGURED		0x00000004	/* IO card was detected and configured */
#define _PCCARD_FLAG_NO_RESOURCES	0x00000008	/* Unable to configure due to lack of resources */
#define _PCCARD_FLAG_IOMEM			0x00000010  /* Socket configured as io+memory interface */
#define _PCCARD_FLAG_RECONFIGURE	0x00000020  /* Socket has a configure pending */
#define _PCCARD_FLAG_UNKNOWN		0x00000040  /* Unknown card in socket */
#define	_PCCARD_FLAG_CARDBUS		0x00000080	/* CardBus card in socket */

#define _PCCARD_WINDOW_UNUSED		0x0000		/* Window slot is unused */
#define _PCCARD_WINDOW_MEMORY		0x0001		/* Window describes a memory region */
#define _PCCARD_WINDOW_IO			0x0002		/* Window describes an io region */
#define _PCCARD_WINDOW_IRQ			0x0003		/* Window describes irq usage */
#define _PCCARD_WINDOW_DMA			0x0004		/* Window describes dma usage */
#define _PCCARD_WINDOW_PARTITION	0x0005		/* Window describes a partition */
#define	_PCCARD_WINDOW_ROM			0x0006		/* Window describes ROM area */

#define _PCCARD_WINFLAG_NEXT		0x0001		/* The next window is logically part of this window (ie devices with two i/o port ranges) */
#define _PCCARD_WINFLAG_UNLOCKABLE	0x0002		/* This window cannot be locked */
#define _PCCARD_WINFLAG_TEMPORARY	0x0004		/* This window will go away when unlocked */
#define _PCCARD_WINFLAG_BOOT		0x0008		/* This window was used for boot */
#define _PCCARD_WINFLAG_LOCK_RO		0x0100		/* This window has RO lock(s) */
#define _PCCARD_WINFLAG_LOCK_RW		0x0200		/* This window has a RW lock */
#define _PCCARD_WINFLAG_LOCK_EXCL	0x0400		/* This window has an exclusive lock */

#define _PCCARD_DEV_UNKNOWN			0xFFFF		/* Unknown device */
#define _PCCARD_DEV_ALL				0x0000		/* All devices */
#define _PCCARD_DEV_MEMORY			0x0100		/* Memory type device */
#define _PCCARD_DEV_SERIAL			0x0200		/* 16450 serial device */
#define _PCCARD_DEV_PARALLEL		0x0300		/* PC parallel device */
#define _PCCARD_DEV_FIXED_DISK		0x0400		/* Any hard drive */
#define _PCCARD_DEV_VIDEO			0x0500		/* Any video adapter */
#define _PCCARD_DEV_NETWORK			0x0600		/* Any network adapter */
#define _PCCARD_DEV_AIMS			0x0700		/* Auto Incrementing Mass Storage */
#define _PCCARD_DEV_GPIB			0x1200		/* GPIB card */
#define _PCCARD_DEV_SCSI			0x0800		/* Any SCSI interface */
#define	_PCCARD_DEV_SECURITY		0x0900		/* Security services */
#define	_PCCARD_DEV_INSTRUMENT		0x0A00		/* Instrumentation cards */
#define	_PCCARD_DEV_SERIAL_BUS		0x0B00		/* High speed serial eg. USB */
#define _PCCARD_DEV_SOUND			0x8100		/* Any sound adapter */
#define _PCCARD_DEV_NO_CONSTRAINT	(1 << ((sizeof(int32_t) * 8) - 1)) /* flag: get info on any window even if locked */

#define _PCCARD_IRQFLAG_LEVEL		0x0001		/* The irq is set for level mode */
#define _PCCARD_IRQFLAG_SHARE		0x0002		/* The irq is shared */

#define _PCCARD_MEMIOFLAG_ATTRIBUTE	0x0001		/* The region maps to attribute memory */
#define _PCCARD_MEMIOFLAG_16BIT		0x0002		/* The window is 16-bits wide */
#define	_PCCARD_MEMIOFLAG_32BIT		0x0003		/* The window is 32-bits wide */

#define _PCCARD_ARM_INSERT_REMOVE	0x0001		/* Notify card insertion/removal events */
#define _PCCARD_ARM_BATT_LOW		0x0002		/* Notify on battery low events */
#define _PCCARD_ARM_RECONFIGURE		0x0003		/* Notify on reconfiguration requests */

#define _PCCARD_PARTYPE_UNKNOWN		0x00		/* Unknown or unformatted partition */
#define _PCCARD_PARTYPE_TUPLE		0x01		/* Tuple partition */
#define _PCCARD_PARTYPE_ATTRIBUTE	0x02		/* Attribute partition */
#define _PCCARD_PARTYPE_FREE		0x03		/* Unused partition */
#define _PCCARD_PARTYPE_REGION		0x04		/* Region partition */
#define _PCCARD_PARTYPE_FAT			0x10		/* MS-DOS FAT type */
#define _PCCARD_PARTYPE_QNX2		0x11		/* QNX 2.xx file system */
#define _PCCARD_PARTYPE_QNX4		0x12		/* QNX 4.xx file system */
#define _PCCARD_PARTYPE_FFS1		0x20		/* Microsoft FFS 1.0 */
#define _PCCARD_PARTYPE_FFS2		0x21		/* Microsoft FFS 2.0 */
#define _PCCARD_PARTYPE_QXIP		0x30		/* QNX execute-in-place */
#define _PCCARD_PARTYPE_XIP			0x31		/* PCCARD execute-in-place */
#define _PCCARD_PARTYPE_LFS			0x40		/* Linear File Store */

#define _PCCARD_DEVTYPE_NULL		0x00		/* Null device */
#define _PCCARD_DEVTYPE_ROM			0x01		/* ROM device */
#define _PCCARD_DEVTYPE_OTPROM		0x02		/* One-time programable PROM */
#define _PCCARD_DEVTYPE_EPROM		0x03		/* UV PROM */
#define _PCCARD_DEVTYPE_EEPROM		0x04		/* EEPROM */
#define _PCCARD_DEVTYPE_FLASH		0x05		/* Flash EPROM */
#define _PCCARD_DEVTYPE_SRAM		0x06		/* Static RAM */
#define _PCCARD_DEVTYPE_DRAM		0x07		/* Dynamic RAM */
#define _PCCARD_DEVTYPE_FUNCSPEC	0x0d		/* Function specific area */
#define _PCCARD_DEVTYPE_UNKNOWN		0xff		/* unknown device type */

#define _PCCARD_MEMTYPE_COMMON		0x0000		/* for raw reads */
#define _PCCARD_MEMTYPE_ATTRIBUTE	0x0001		

#define _PCCARD_VPP_0_VOLTS		0		/* voltage setting 0V */
#define _PCCARD_VPP_5_VOLTS		1		/* voltage setting 5V */
#define _PCCARD_VPP_12_VOLTS		2		/* voltage setting 12V */

#ifdef __cplusplus
extern "C" {
#endif

/*
 * General PCCARD functions
 */
 
extern pccard_t pccard_attach(nid_t nid);
extern int32_t pccard_detach(pccard_t handle);
extern int32_t pccard_arm(pccard_t handle, int32_t devtype, uint32_t event, int32_t sig_or_negproxy); /* devtype=_PCCARD_DEV_*, only 1 notification per devtype, 0=disarm */
extern int32_t pccard_info(pccard_t handle, int32_t socket, struct _pccard_info *info, uint32_t size);
extern int32_t pccard_lock(pccard_t handle, int32_t socket, int32_t window, int32_t oflag);
extern int32_t pccard_unlock(pccard_t handle, int32_t socket, int32_t window);
extern int32_t pccard_reconfigure(pccard_t handle, int32_t socket);
extern int32_t pccard_reconfig_socket(pccard_t handle, int32_t socket, int32_t vpp);

/*
 * PCCARD Memory functions
 */
 
extern ssize_t pccard_mem_read(pccard_t handle, int32_t socket, int32_t window, uint32_t offset, ssize_t size, void *data);
extern ssize_t pccard_mem_write(pccard_t handle, int32_t socket, int32_t window, uint32_t offset, ssize_t size, const void *data);
extern long pccard_mem_erase(pccard_t handle, int32_t socket, int32_t window, long block_start, long block_count);
extern int32_t pccard_window_alloc(pccard_t handle, int32_t socket, int32_t window, long *size, paddr_t *phys);
extern int32_t pccard_window_alloc8(pccard_t handle, int32_t socket, int32_t window, long *size, paddr_t *phys);
extern int32_t pccard_window_free(pccard_t handle, int32_t socket, int32_t window);
extern ssize_t pccard_raw_read(pccard_t handle, int32_t socket, int32_t type, uint32_t addr, ssize_t len, void *buf);
extern int32_t pccard_partition_type(pccard_t handle, int32_t socket, int32_t index, int32_t type);
extern int pccard_read_byte_attr (pccard_t handle, int32_t socket, long addr, uint8_t *val);
extern int pccard_write_byte_attr (pccard_t handle, int32_t socket, long addr, uint8_t val);
extern long	pccard_window_map (pccard_t handle, int socket, int index, long offset, long *size);


/*
 * PCCARD IO functions and structures
 */

typedef	struct {
	uint32_t			base;
	uint32_t			size;
	uint32_t			flags;
	} REGS;
 
struct _pccard_io {
	int32_t				type;		/* device type */
	int32_t				socket;		/* Socket number */
	int32_t				index;		/* window within socket (usually zero) */
	uint16_t			manufacturer;	/* card manufacturer */
	uint16_t			card_type;	/* card type */
	uint32_t			flags;		/* event card state (_PCCARD_FLAG_*) */
	REGS				regs [7];	/* IO and memory base addresses */
	uint32_t			irq;		/* irq level */
	uint32_t			irq_flags;	/* irq flags */
	uint16_t			device_id;		/* CardBus device id */
	uint16_t			vendor_id;		/* CardBus vendor id */
	uint16_t			busnum;			/* PCI bus number */
	uint16_t			devfuncnum;		/* PCI device and function number */
	uint8_t				pci_index;		/* PCI index */
	uint8_t				filler [3];
};

#define pccard_io_attach(_n)			pccard_attach(_n)
#define pccard_io_detach(_h)			pccard_detach(_h)
#define pccard_io_arm(_h, _t, _p)		pccard_arm(_h, _t, _PCCARD_ARM_INSERT_REMOVE | _PCCARD_ARM_RECONFIGURE, _p)
#define pccard_io_lock(_h, _s, _w)		pccard_lock(_h, _s, _w, O_RDWR | O_EXCL)
#define pccard_io_unlock(_h, _s, _w)	pccard_unlock(_h, _s, _w)

extern int32_t pccard_io_info(pccard_t handle, int32_t devtype, struct _pccard_io *info);

/*
 * PCCARD resource management defines, functions and structures 
 */
 
struct _pccard_resource {
	uint16_t 			base;
	uint16_t			length;
};
				
#define _PCCARD_RESOURCE_MEMORY			0
#define _PCCARD_RESOURCE_IO				1
#define _PCCARD_RESOURCE_IRQ			2
#define _PCCARD_RESOURCE_DMA			3

#define _PCCARD_RESOURCE_PRIORITIES		2

extern int32_t pccard_resource_clear (pccard_t handle);
extern int32_t pccard_resource_add (pccard_t handle, int32_t type, int32_t priority, int32_t count, const struct _pccard_resource *resources);
extern int32_t pccard_resource_query (pccard_t handle, int32_t type, int32_t subtype, int32_t count, struct _pccard_resource *resources);
extern int32_t pccard_resource_reread (pccard_t handle);

#ifdef __cplusplus
};
#endif

#endif

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/pccard/public/sys/pccard.h $ $Rev: 219996 $" )
