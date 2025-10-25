/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable 
 * license fees to QNX Software Systems before you may reproduce, 
 * modify or distribute this software, or any work that includes 
 * all or part of this software.   Free development licenses are 
 * available for evaluation and non-commercial purposes.  For more 
 * information visit http://licensing.qnx.com or email 
 * licensing@qnx.com.
 * 
 * This file may contain contributions from others.  Please review 
 * this entire file for other proprietary rights or license notices, 
 * as well as the QNX Development Suite License Guide at 
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */

/*
 *  sys/disk.h
 *
 */
#ifndef __DISK_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#include _NTO_HDR_(_pack64.h)

__BEGIN_DECLS


__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/hardware/devb/cam/public/sys/disk.h $ $Rev: 219612 $" )

typedef struct partition_entry {
    unsigned char   boot_ind,
                    beg_head,
                    beg_sector,
                    beg_cylinder,
                    os_type,
                    end_head,
                    end_sector,
                    end_cylinder;
    unsigned long   part_offset,
                    part_size;
} partition_entry_t;


__END_DECLS

#include _NTO_HDR_(_packpop.h)

#define __DISK_H_INCLUDED
#endif
