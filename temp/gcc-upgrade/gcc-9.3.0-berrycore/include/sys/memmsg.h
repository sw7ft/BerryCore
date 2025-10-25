/*
 * $QNXLicenseC:
 * Copyright 2007, 2009, QNX Software Systems. All Rights Reserved.
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

#ifndef __MEMMSG_H_INCLUDED
#define __MEMMSG_H_INCLUDED

#if defined(__WATCOMC__) && !defined(_ENABLE_AUTODEPEND)
#pragma read_only_file;
#endif

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef __SYSMSG_H_INCLUDED
#include _NTO_HDR_(sys/sysmsg.h)
#endif

#ifndef __MMAN_H_INCLUDED
#include _NTO_HDR_(sys/mman.h)
#endif

#define MEMMGR_COID				SYSMGR_COID

enum {
	_MEM_MAP = _MEMMGR_BASE,
	_MEM_CTRL,
	_MEM_INFO,
	_MEM_OFFSET,
	_MEM_DEBUG_INFO,
	_MEM_SWAP,
	_MEM_PMEM_ADD,
	_MEM_PEER,
	_MEM_DEBUG_CMD,
};

enum {
	_MEM_CTRL_UNMAP,
	_MEM_CTRL_PROTECT,
	_MEM_CTRL_SYNC,
	_MEM_CTRL_LOCKALL,
	_MEM_CTRL_UNLOCKALL,
	_MEM_CTRL_LOCK,
	_MEM_CTRL_UNLOCK,
	_MEM_CTRL_ADVISE
};

enum {
	_MEM_SWAP_ON,
	_MEM_SWAP_OFF,
	_MEM_SWAP_CONFIG,
	_MEM_SWAP_STATS,
	_MEM_SWAP_REGISTER,
	_MEM_SWAP_RUN
};

enum {
	_MEM_OFFSET_PHYS,
	_MEM_OFFSET_FD,
	_MEM_OFFSET_PT
};

enum {
	_MEM_DEBUG_CMD_EXERCISE_DEFRAG,
	_MEM_DEBUG_CMD_GET_FREELIST_INFO,
	_MEM_DEBUG_CMD_GET_PHYS_STATS
};  /* used for subcmd field of mem_debug_cmd_t */

#include _NTO_HDR_(_pack64.h)

/*
 * Message of _MEM_MAP
 */
struct _mem_map {
	_Uint16t						type;
	_Uint16t						zero;
	_Uint32t						reserved1;
	_Uint64t						addr;
	_Uint64t						len;
	_Uint32t						prot;
	_Uint32t						flags;
	_Int32t							fd;
	_Uint32t						preload;
	_Uint64t						align;
	off64_t							offset;
};

struct _mem_map_reply {
	_Uint64t						real_size;
	_Uint64t						real_addr;
	_Uint64t						addr;
};

typedef union {
	struct _mem_map					i;
	struct _mem_map_reply			o;
} mem_map_t;


/*
 * Message of _MEM_CTRL
 */
struct _mem_ctrl {
	_Uint16t						type;
	_Uint16t						subtype;
	_Uint32t						flags;
	_Uint64t						addr;
	_Uint64t						len;
};

typedef union {
	struct _mem_ctrl				i;
} mem_ctrl_t;


#if defined(__EXT_QNX)		/* Approved 1003.1j D10 */
/*
 * Message of _MEM_INFO
 */
struct _mem_info {
	_Uint16t						type;
	_Uint16t						zero;
	_Int32t							fd;
	_Uint32t						flags;
	_Uint32t						reserved;
};

struct _mem_info_reply {
	_Uint32t						zero[2];
	_Uint32t						size;
	_Uint32t						reserved;
	struct __posix_typed_mem_info64	info;
};

typedef union {
	struct _mem_info				i;
	struct _mem_info_reply			o;
} mem_info_t;
#endif

/*
 * Message of _MEM_OFFSET
 */
struct _mem_offset {
	_Uint16t						type;
	_Uint16t						subtype;
	_Int32t							reserved;
	_Uint64t						addr;
	_Uint64t						len;
};

struct _mem_offset_reply {
	_Uint64t						size;
	off64_t							offset;
	_Int32t							fd;
	_Uint32t						reserved;
};

typedef union {
	struct _mem_offset				i;
	struct _mem_offset_reply		o;
} mem_offset_t;

/*
 * Message of _MEM_DEBUG_INFO
 */
struct _mem_debug_info {
	_Uint16t						type;
	_Uint16t						zero;
	_Uint32t						reserved;
	off64_t							offset;
	ino64_t							ino;
	_Uintptrt						vaddr;
	_Uint32t						size;
	_Uint32t						flags;
	dev_t							dev;
	_Uintptrt						old_vaddr;
	__FLEXARY(char, path); /* char path[] */
};


typedef union {
	struct _mem_debug_info			i;
} mem_debug_info_t;



/*
 * Message of _MEM_DEBUG_CMD
 *
 * Note that this command is intended for debug purposes only.  This
 * structure is subject to change at any moment, and should not be
 * depended upon to remain stable.
 */
#define _MEM_DEBUG_FREELIST_PROC		0
#define _MEM_DEBUG_FREELIST_KERNEL		1
#define _MEM_DEBUG_FREELIST_CRIT		2

struct _mem_debug_cmd {
	_Uint16t					type;
	_Uint16t					subtype;
	union {
		struct {
			_Uint32t 	blk_size;
		} exercise_defrag;
		struct {
			int			which_freelist;
		} get_freelist_info;
	} u;
};

#define MEM_DEBUG_CMD_REPLY_VERSION 1


struct _mem_debug_cmd_reply {
	/* If you make a non-backwards-compatible change to this structure, update
	 * the MEM_DEBUG_CMD_REPLY_VERSION definition.
	 */
	int version;
	union {
		struct {
			_Uint64t num_skiplists;
			_Uint64t max;				/* size of largest block on the freelist */
			_Uint64t min;				/* size of smallest block on the freelist */
			_Uint64t total_new;			/* total memory allocated to populate this free list */
			_Uint64t total_alloc;		/* total memory allocated from this heap */
			_Uint64t total_dealloc;		/* total memory deallocated back to this heap */
			_Uint64t num_realloc_bigger;	/* number of reallocs done to allocated grow memory */
			_Uint64t num_realloc_smaller;/* number of reallocs done to shrink allocated memory*/
			struct {
				_Uint64t size;			/* the smallest size block which can be held on this skiplist*/
				_Uint64t block_count;	/* the number of blocks on the skiplist */
				_Uint64t total_size;		/* the sum of the actual sizes of all blocks on this skiplist */
				_Uint64t first;			/* the index in the list of the first occurance of a block on this skiplist */
				_Uint64t max_run_length;	/* the maximum run length */
				_Uint64t num_runs;		/* the number of runs on this skiplist */
				/* A run is a set of blocks on a skiplist not interrupted by a block on a skiplist
				 * with a *larger* size.  A smaller maximum and average run means better performance
				 */
				_Uint64t num_allocs;	/* number of allocations done from this skiplist */
				_Uint64t num_deallocs;	/* number of deallocations done on this skiplist */
				_Uint64t largest;		/* largest block in the free list */
			} skiplist_info[16];
		} get_freelist_info;
		struct {
			/* Statistics from a _MEM_DEBUG_CMD_GET_PHYS_STATS command. All
			 * values are in bytes. */
			_Uint64t free_mem;			/* Free physical memory */
			_Uint64t movable_mem;		/* Allocated but movable memory */
			_Uint64t locked_mem;		/* Locked memory */
			_Uint64t sys_mem;			/* System memory */
			_Uint64t sync_mem;			/* Pages with sync objects */
			_Uint64t max_contig_mem;	/* Size of maximal movable region (free
										 * and allocated) */
		} get_phys_stats;
	} u;
};

struct _mem_debug_cmd_reply_version0 {
	int version;
	union {
		struct {
			_Uint64t num_skiplists;
			_Uint64t max;				/* size of largest block on the freelist */
			_Uint64t min;				/* size of smallest block on the freelist */
			_Uint64t total_new;			/* total memory allocated to populate this free list */
			_Uint64t total_alloc;		/* total memory allocated from this heap */
			_Uint64t total_dealloc;		/* total memory deallocated back to this heap */
			_Uint64t num_realloc_bigger;	/* number of reallocs done to allocated grow memory */
			_Uint64t num_realloc_smaller;/* number of reallocs done to shrink allocated memory */
			struct {
				_Uint64t size;			/* the smallest size block which can be held on this skiplist */
				_Uint64t block_count;	/* the number of blocks on the skiplist */
				_Uint64t total_size;	/* the sum of the actual sizes of all blocks on this skiplist */
				_Uint64t first;			/* the index in the list of the first occurance of a block on this skiplist */
				_Uint64t max_run_length;/* the maximum run length */
				_Uint64t num_runs;		/* the number of runs on this skiplist */
				/* A run is a set of blocks on a skiplist not interrupted by a block on a skiplist
				 * with a *larger* size.  A smaller maximum and average run means better performance
				 */
				_Uint64t num_allocs;	/* number of allocations done from this skiplist */
				_Uint64t num_deallocs;	/* number of deallocations done on this skiplist */
			} skiplist_info[16];
		} get_freelist_info;
	} u;
};

typedef union {
	struct _mem_debug_cmd			i;
	struct _mem_debug_cmd_reply		o;
} mem_debug_cmd_t;


/*
 * Message of _MEM_SWAP
 */
struct _mem_swap {
	_Uint16t						type;
	_Uint16t						subtype;
};

struct _swap_config_data {
	_Uint64t				low_bound;
	_Uint64t				crit_bound;
	_Uint64t				high_bound;
	_Uint8t					priority;
	_Uint8t					spare1[3];
	_Uint32t				spare2;
	_Uint64t				spare3[2];
};


struct _mem_swap_on {
	_Uint16t						type;
	_Uint16t						subtype;
	_Uint32t						spare0[3];
	struct _swap_config_data		config;
	_Uint64t						spare[4];
};

struct _mem_swap_off {
	_Uint16t						type;
	_Uint16t						subtype;
	_Uint32t						spare[3];
};

struct _mem_swap_config {
	_Uint16t						type;
	_Uint16t						subtype;
	_Uint32t						spare[3];
};

struct _mem_swap_config_reply {
	_Uint32t						enabled;
	_Uint32t						spare0[3];
	struct _swap_config_data		config;
	_Uint64t						spare[4];
};

struct _mem_swap_stats {
	_Uint16t						type;
	_Uint16t						subtype;
	_Uint32t						fd;
	_Uint32t						spare[2];
};

struct _mem_swap_stats_reply {
	_Uint32t						fd;
	_Uint32t						faults;
	_Uint64t						resident;
	_Uint64t						pageable;
	_Uint64t						working_set;
	_Uint64t						spare[4];
};

struct _mem_swap_register {
	_Uint16t						type;
	_Uint16t						subtype;
	_Uint64t						size;
	_Int32t							chid;
	_Uint32t						flags;
	_Uint32t						spare[2];
};

struct _mem_swap_run {
	_Uint16t						type;
	_Uint16t						subtype;
	_Uint64t						want;
	_Uint32t						spare[4];
};

typedef union {
	struct _mem_swap				swap;
	struct _mem_swap_on				swap_on;
	struct _mem_swap_off			swap_off;
	struct _mem_swap_config			swap_config;
	struct _mem_swap_config_reply	swap_config_reply;
	struct _mem_swap_stats			swap_stats;
	struct _mem_swap_stats_reply	swap_stats_reply;
	struct _mem_swap_register		swap_register;
	struct _mem_swap_run			swap_run;
} mem_swap_t;


/*
 * Message of _MEM_PMEM_ADD
 */
struct _mem_pmem_add {
	_Uint16t						type;
	_Uint16t						zero1;
	_Uint32t						zero2;
	_Uint64t						addr;
	_Uint64t						len;
};

typedef union {
	struct _mem_pmem_add			i;
} mem_pmem_add_t;


/*
 * Message of _MEM_PEER
 */
struct _mem_peer {
	_Uint16t						type;
	_Uint16t						peer_msg_len;
	_Uint32t						pid;
	_Uint64t						reserved1;
	/* second mem msg follows - keep this structure a multiple of of 64-bits */
};

typedef union {
	struct _mem_peer			i;
} mem_peer_t;

#include _NTO_HDR_(_packpop.h)

#endif


__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/services/system/public/sys/memmsg.h $ $Rev: 756688 $" )
