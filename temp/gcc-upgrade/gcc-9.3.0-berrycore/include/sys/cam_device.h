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
 *  sys/cam_device.h
 *
 */

#ifndef __CAM_DEVICE_H_INCLUDED
#define __CAM_DEVICE_H_INCLUDED

#include <_pack64.h>

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

__BEGIN_DECLS

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/hardware/devb/cam/public/sys/cam_device.h $ $Rev: 623848 $" )

#define D_DIR_ACC       0x00    /* Direct Access device            */
#define D_SEQ_ACC       0x01    /* Sequential Access device        */
#define D_PRINTER       0x02    /* Printer device                  */
#define D_PROCESSOR     0x03    /* Processor device                */
#define D_WORM          0x04    /* Write Once Read Multiple device */
#define D_READ_ONLY     0x05    /* Read Only (CD-ROM) device       */
#define D_SCANNER       0x06    /* Scanner device                  */
#define D_OPTICAL       0x07    /* Optical Memory device           */
#define D_MEDIA_CHG     0x08    /* Media Changer device            */
#define D_COMM          0x09    /* Communication device            */
#define D_UNKNOWN       0x1F    /* Unknown device type             */
#define D_MASK          0x1F    /* Mask for device type            */

typedef struct cam_devinfo {
    unsigned int           num_sctrs;      /* Size of disk in sectors         */
    unsigned int           cylinders;      /* Number of tracks                */
    unsigned int           heads;          /* Number of heads                 */
    unsigned int           tracks;         /* Sectors per track               */
    unsigned int           sctr_size;      /* Bytes per sector                */
    unsigned int           flags;          /* Device flags                    */
    unsigned int      	   media_changes;  /* Number of media changes         */
    unsigned int           type;           /* Device type                     */
    _Uint64t               num_sctrs64;
	_Uint32t               ptl;            /* Path/Target/Lun (1 byte for each) */
	unsigned int           rsvd[13];
} cam_devinfo_t;

/* Device flags */
#define DEV_RDONLY              0x000001
#define DEV_NO_MEDIA            0x000002
#define DEV_REMOVABLE           0x000004
#define DEV_RESERVED            0x000008
#define DEV_CDB_10              0x000010
#define DEV_ATAPI               0x000020
#define DEV_RAW                 0x000040
#define DEV_BOUNCE              0x000080
#define DEV_LOCKED              0x000100
#define DEV_BMSTR               0x000200
#define DEV_DMA_NOX64K          0x000400
#define DEV_DMA_LOW             0x000800
#define DEV_DMA_SNOOPING        0x001000
#define DEV_RELEARN_MEDIA       0x002000
#define DEV_DMA_20BIT           0x004000
#define DEV_DMA_24BIT           0x008000
#define DEV_DMA_32BIT           0x010000
#define DEV_DMA_64BIT           0x020000
#define DEV_NO_FLUSH            0x040000
#define DEV_UPSIDE_DOWN_MEDIA	0x080000
#define DEV_NON_ROTATING		0x100000

__END_DECLS

#include <_packpop.h>

#endif
