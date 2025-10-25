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
 *  raid.h
 */

#ifndef _RAID_H_INCLUDED
#define _RAID_H_INCLUDED

#include <_pack64.h>


__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/hardware/devb/cam/public/sys/raid.h $ $Rev: 219612 $" )

#define SIG_SIZE        24

/* DISK FLAGS */
#define VALID_DISK                      0x1
#define WORKING_DISK                    0x2
#define ARRAY_DISK                      0x4
#define REBUILD_DISK                    0x20
#define DISK_HOT_SPARE                  0x40
#define MARKED_FOR_ARRAY                0x80
#define DISK_PRESENT                    0x100

/* ARRAY FLAGS */
#define VALID_ARRAY                     0x1
#define WORKING_ARRAY                   0x2
#define INITIALIZED_ARRAY               0x4
#define READY                           0x8
#define ARRAY_DEGRADED                  0x10
#define REBUILD_ARRAY                   0x20
#define BOUNDARY_ALIGN                  0x80

/* ARRAY IDENTIFIER MASKS */
#define ARRAY_ARRAY_ID_MASK(val)        ((val) & 0xf)
#define ARRAY_RAID_TYPE_MASK(val)       (((val) >> 4) & 0xff)
#define ARRAY_TOTAL_DISKS_MASK(val)     (((val) >> 12) &0xffff)

typedef struct _raid_conf {
    /* any info required to create an array */
    _Uint32t        rsvd[12];
} raid_conf_t;

typedef struct _raid_disk{
    _Uint64t            rebuild_watermark;
    _Uint64t            sync_watermark;
	_Uint64t			total_sectors;
	_Uint16t			channel;
	_Uint16t			device_num;
    _Uint32t            dflags;
    _Uint32t            rsvd[12];
}raid_disk_t;

typedef struct  _raid_array{
    _Uint16t            signature[24];
    _Uint64t            array_identifier;
    _Uint16t            cyls;
    _Uint16t            heads;
    _Uint64t            sectors;
    _Uint16t            StripeBlockSize;
    _Uint16t            StripeSize;
    _Uint16t            pad;
    _Uint32t            aflags;
    _Uint32t            rsvd[12];
}raid_array_t;

typedef struct _raid_array_info{
    raid_array_t    array[4];
    _Uint32t        rsvd[12];
/*  raid_disk_t     disk[]; */
}raid_array_info_t;

typedef struct _raid_array_status {
    _Uint32t            array_state;                    /* array state ie critical */
    _Uint64t            total_sectors;
    _Uint64t            rebuild_count;
    _Uint32t            rsvd[12];
} raid_array_status_t;

typedef struct _raid_status {
    raid_array_status_t status[4];
    _Uint32t            rsvd[12];
} raid_status_t;

#include <_packpop.h>

#endif
