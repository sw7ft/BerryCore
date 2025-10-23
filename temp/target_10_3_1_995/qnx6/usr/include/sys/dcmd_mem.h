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
 *  dcmd_mem.h   Non-portable low-level devctl definitions
 */
#ifndef __DCMD_MEM_H_INCLUDED
#define __DCMD_MEM_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef _DEVCTL_H_INCLUDED
#include _NTO_HDR_(devctl.h)
#endif

#include _NTO_HDR_(_pack64.h)

struct _mem_partinfo {
	char					type [32];
	unsigned long			offset;
	unsigned long			size;
	unsigned short			block_shift;
	unsigned short			jedec_len;
	unsigned char			jedec_id [8];
};

struct _mem_erase {
	unsigned long			block;
	unsigned long			count;
};

#define DCMD_MEM_PARTINFO			__DIOF(_DCMD_MEM, 1, struct _mem_partinfo)
#define DCMD_MEM_ERASE				__DIOT(_DCMD_MEM, 2, struct _mem_erase)

/*
 * ETFS devctl commands (100-199)
 */

/* 
 * Erasing with an offset and length (specified in bytes).  Specifying -1
 * for length means "go to the end of the partition".
 */
struct etfs_erase_range {
	_Int64t		offset;
	_Int64t		length;
};

struct etfs_info {
	char	name[16];
	int		numblks;
	int		clusters2blk;
	int		clustersize;
	int		erase_cnt;
	int		clean_cnt;
	int		spare_cnt;
	int		filthy_cnt;
	int		inactive_cnt;
	int		xtnts_cnt;
	int		cache_cnt;
	int		devread_cnt;
	int		devwrite_cnt;
	int		cacheread_cnt;
	int		mine_cnt;
	int		copy_cnt;
	int		defrag_cnt;
	int		eccerr_cnt;
	int		chkerr_cnt;
	int		deverr_cnt;
	int		files_cnt;
	int		open_cnt;
	int		badblks_cnt;
	int		blksize;
	int		expansion[15];		/* For future expansion */
} ;

#define DCMD_ETFS_STOP      __DION(_DCMD_MEM, 100)
#define DCMD_ETFS_START     __DION(_DCMD_MEM, 101)
#define DCMD_ETFS_ERASE     __DION(_DCMD_MEM, 102)
#define DCMD_ETFS_FORMAT    __DION(_DCMD_MEM, 103)
#define DCMD_ETFS_DEFRAG    __DION(_DCMD_MEM, 104)
#define DCMD_ETFS_INFO      __DIOF(_DCMD_MEM, 105, struct etfs_info)
#define DCMD_ETFS_ERASE_RANGE     __DIOT(_DCMD_MEM, 106, struct etfs_erase_range)
#define DCMD_ETFS_FLUSH_COUNT     __DION(_DCMD_MEM, 107)

#include _NTO_HDR_(_packpop.h)

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/fs-flash3/public/sys/dcmd_mem.h $ $Rev: 736183 $")
#endif
