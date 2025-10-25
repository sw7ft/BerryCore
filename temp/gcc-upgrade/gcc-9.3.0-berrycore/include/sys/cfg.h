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





#ifndef _CFG_H
#define _CFG_H

#include <sys/types.h>

/* Taken from External Plug and Play Interfaces Specification for
   MS-DOS and Windows Run-time Configuration Services Version 1.0 */

typedef struct Config_Info Config_Info_t;

#define ISADEVICE		0x00000001
#define EISADEVICE		0x00000002
#define PCIDEVICE		0x00000004
#define PCMCIADEVICE	0x00000008
#define PNPISADEVICE	0x00000010
#define MCADEVICE		0x00000020

struct Device_ID
{
	ulong_t	BusID;		/* bus type, 0 is undefined */
	ulong_t	DevID;		/* physical device ID, 0xffffffff is undefined */
	ulong_t	CompID;		/* compatibility ID */
	ulong_t	SerialNum;	/* device instance or serial number, 0 is undefined */
	ulong_t	LogicalID;	/* Logical device ID for Plug and Play ISA, Class code for */
						/* PCI, 0xffffffff is undefined */
	ulong_t	Flags;		/* Bit 0: device has been intialized (1) */
						/* Bit 1: device is enabled (1) */
						/* Bit 2: device config has been locked (1) */
						/* Bit 3: device has temporary config resources assigned (1) */
						/* Bit 4: device is re-configurable (1) */
						/* Bit 31: device id is a QNX defined ID */
};


union Bus_Access
{
	struct	PCIAccess {
		uchar_t 	BusNumber;			/* Bus number 0-255 */
		uchar_t 	DevFuncNumber;		/* Device (bits 7:3) and function (in bits 2:0) IDs */
		ushort_t 	PCIreserved;			
	} PCIAccess;
	struct	EISAAccess {
		uchar_t 	SlotNumber;			/* Card slot number */
		uchar_t		FunctionNumber;		/* (E)ISA sub-function number on multi function card */
		ushort_t	EISAreserved;		
	} EISAAccess;
	struct	PnPAccess {
		uchar_t 	CSN;				/* Card slot number determined during ISA isolation */
		uchar_t		LogicalDevNumber;	/* Logical device number */
		ushort_t	Read_data_port;		/* Read data I/O port determined during ISA isolation */
	} PnPAccess;
	struct	PCMCIAAccess {
		ushort_t 	LogicalSocket;		/* Card logical socket # */
		ushort_t 	PCMCIAReserved1;	/* Reserved */
	} PCMCIAAccess;
};

#define	MAX_MEM_REGISTERS		9
#define	MAX_IO_PORTS			20
#define	MAX_IRQS				6
#define	MAX_DMA_CHANNELS		6

struct Config_Info {
	struct Device_ID	Device_ID;			/* Device ID information */
	union Bus_Access	BusAccess;			/* Info to allow config. access */

	ulong_t				NumMemWindows;		/* Num memory windows */
	ulong_t				MemBase[MAX_MEM_REGISTERS];  	/* Memory window base */
	ulong_t				MemLength[MAX_MEM_REGISTERS];	/* Memory window length */
	ulong_t				MemAttrib[MAX_MEM_REGISTERS];	/* Memory window Attrib */

	ulong_t				NumIOPorts;						/* Num IO ports */
	ulong_t				IOPort_Base[MAX_IO_PORTS];		/* I/O port base */
	ulong_t				IOPort_Length[MAX_IO_PORTS];	/* I/O port length */

	ulong_t				NumIRQs;						/* Num IRQ info */
	ulong_t				IRQRegisters[MAX_IRQS];			/* IRQ list */
	ulong_t				IRQAttrib[MAX_IRQS];			/* IRQ Attrib list */

	ulong_t				NumDMAs;						/* Num DMA channels */
	ulong_t				DMALst[MAX_DMA_CHANNELS];	 	/* DMA list */
	ulong_t				DMAAttrib[MAX_DMA_CHANNELS];	/* DMA Attrib list */

	char				Description[33];				/* Device specific desc */
	uchar_t				Reserved1[3];					/* Reserved */
};

struct Query_Info {
	ulong_t		BusID;				/* Input, 0x01 = isadevice, 0x08 = PCMCIA */
	ushort_t	ResourceType;		/* Input, 0x01 = I/O Ports, 0x02 = IRQ */
									/* 0x04 = DMA, 0x08 = Memory */
	ushort_t	ResourceAttrib;		/* Input, attribute of the requested resource */
	ulong_t		ResourceAlign;		/* Input, alignment for base address */
									/* increment in 1-byte blocks */
	ulong_t		ResourceMin;		/* Input, First acceptable value of the resource */
	ulong_t		ResourceMax;		/* Input, Last acceptable value of the resource */
	ulong_t		ResourceActual;		/* Output, Starting value of the resource */
	uchar_t		QIReserved[8];		/* Reserved */
};

/* Resource Types */
#define RESOURCE_IO					0x01	/* I/O ports */
#define RESOURCE_IRQ				0x02	/* IRQ */
#define RESOURCE_DMA				0x04	/* DMA */
#define RESOURCE_MEMORY				0x08	/* Memory */

/* IO attributes */
#define ATTR_IO_EXCL				0x00
#define ATTR_IO_SHARED				0x01

/* Memory Range Attributes */
#define ATTR_MEM_RANGE_DECODE		0x01	/* Use memory range length for decoding */
#define ATTR_MEM_8_BIT				0x00	/* 8-bit memory */
#define ATTR_MEM_16_BIT				0x02	/* 16-bit memory */
#define ATTR_MEM_8_16_BIT			0x04	/* 8 and 16-bit memory */
#define ATTR_MEM_32_BIT				0x00	/* 32-bit memory */
#define ATTR_MEM_16_32_BIT			0x08	/* 16 and 32-bit memory */
#define ATTR_MEM_ROM				0x00	/* Read Only (ROM) */
#define ATTR_MEM_RAM				0x20	/* Read/Write (RAM) */
#define ATTR_MEM_SHARED				0x40	/* Shared Memory */

/* IRQ Attributes */
#define ATTR_IRQ_EDGE_TRIGGERED		0x00	/* Edge Triggered */
#define ATTR_IRQ_LEVEL_TRIGGERED	0x01	/* Level Triggered */
#define ATTR_IRQ_LEVEL_LOW			0x00	/* Level Low */
#define ATTR_IRQ_LEVEL_HIGH			0x02	/* Level High */
#define ATTR_IRQ_SHARED				0x04	/* Shared */

#define ATTR_IRQ_DEFAULT			0x80	/* IRQ default */

/* DMA Attributes */
#define ATTR_DMA_8_BIT				0x0000	/* 8-bit transfers */
#define ATTR_DMA_8_16_BIT			0x0001	/* 8 and 16-bit transfers */
#define ATTR_DMA_16_BIT				0x0002	/* 16-bit transfers */
#define ATTR_DMA_32_BIT				0x0003	/* 32-bit transfers */
#define ATTR_DMA_BUS_MASTER			0x0004	/* logical device is a bus master */
#define ATTR_DMA_COUNT_BYTE_MODE	0x0008	/* DMA may execute in count by byte mode */
#define ATTR_DMA_COUNT_WORD_MODE	0x0010	/* DMA may execute in count by word mode */
/* DMA channel speed support */
#define ATTR_DMA_ISA				0x0000	/* ISA compatible timing */
#define ATTR_DMA_TYPE_A				0x0020	/* type A timing */
#define ATTR_DMA_TYPE_B				0x0040	/* type B timing */
#define ATTR_DMA_TYPE_F				0x0060	/* type F timing */
#define ATTR_DMA_SHARED				0x0100	/* Shared DMA */
#define ATTR_DMA_TYPE_C				0x0200	/* C type timing supported */

#define ATTR_DMA_DEFAULT			0x8000	/* DMA default */

/* Status Values */
#define CM_SUCCESS					0x0000	/* Success */
#define CM_CONFIG_MGR_NOT_PRESENT	0xffff	/* CM driver is not running */
#define CM_DEVICE_NOT_FOUND			0x0001	/* Unknown device/invalid dev index */
#define CM_CONFIG_ERROR				0x0001	/* CM couldn't complete the request */
#define CM_IO_PORT_UNAVAILABLE		0x0002	/* I/O port(s) are in use */
#define CM_IRQ_UNAVAILABLE			0x0004	/* IRQ(s) are in use and not sharable */
#define CM_DMA_CH_UNAVAILABLE		0x0008	/* DMA channel(s) are in use */
#define CM_MEM_WINDOW_UNAVAILABLE	0x0010	/* Memory window(s) are in use */

int CM_GetVersion( ushort_t *__Version, ushort_t *__NumSysDevices );
int CM_GetConfig( ushort_t *__DeviceIndex, struct Config_Info *__ConfigBuffer );
int CM_LockConfig( struct Config_Info *__ConfigBuffer );
int CM_UnLockConfig( struct Config_Info *__ConfigBuffer );
int CME_QueryResources( struct Query_Info *__QueryInfo );
int CME_AllocResources( struct Config_Info *__ConfigBuffer );
int CME_DeallocResources( struct Config_Info *__ConfigBuffer );

#endif

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/drvr/public/sys/cfg.h $ $Rev: 219996 $" )
