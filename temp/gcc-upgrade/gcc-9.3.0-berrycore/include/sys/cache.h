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
 *  sys/cache.h
 *

 */
 
#ifndef __CACHE_H_INCLUDED
#define __CACHE_H_INCLUDED

#ifndef __SYSPAGE_H_INCLUDED
#include <sys/syspage.h>
#endif

#ifndef _STDINT_H_INCLUDED
#include <stdint.h>
#endif

#ifndef _TYPES_H_INCLUDED
#include <sys/types.h>
#endif

struct cache_ctrl;

struct cache_funcs {
	int (* init)(int flags, struct cache_ctrl *cinfo);
	void (* flush)(struct cache_ctrl *cinfo,
			void *vaddr, paddr64_t paddr, size_t len);
	void (* invalidate)(struct cache_ctrl *cinfo,
			void *vaddr, paddr64_t paddr, size_t len);
	int (* fini)(struct cache_ctrl *cinfo);
};

struct cache_ctrl {
	_Uint32t		cache_line_size;
	_Uint32t		cache_flush_rate;
	_Uint32t		cache_invalidate_rate;
	_Uint32t		flags;			/* Internal to library */
	int			fd;
	struct cache_funcs	cf;			/* Internal to library */
	void			*dll;			/* Internal to library */
	struct cacheattr_entry	**cachelist;		/* Internal to library */
	int			ncaches;		/* Internal to library */
	struct syspage_entry	*syspage;		/* Internal to library */
	unsigned		bitmask;		/* Internal to library */
	_Uint32t		reserved[4];
};

#include _NTO_CPU_HDR_(cache.h)

enum {
	CTL_CACHE_DEFAULT 		= (0),
	CTL_CACHE_NOCACHE 		= (1<<0),

	/* write buffering */
	CTL_CACHE_WRITECOMBINE	= (1<<1),

	/* on write hit */
	CTL_CACHE_WRITETHROUGH 	= (1<<2),
	CTL_CACHE_WRITEBACK 	= (1<<3),

	/* on write miss */
	CTL_CACHE_WRITEALLOC	= (1<<4),
	CTL_CACHE_WRITENOALLOC	= (1<<5),
};

#define CTL_CACHE_WC CTL_CACHE_WRITECOMBINE
#define CTL_CACHE_WT CTL_CACHE_WRITETHROUGH
#define CTL_CACHE_WB CTL_CACHE_WRITEBACK
#define CTL_CACHE_WA CTL_CACHE_WRITEALLOC
#define CTL_CACHE_WNA CTL_CACHE_WRITENOALLOC

/* Values for "flags" argument to cache_init() */
#define CACHE_INIT_FLAG_IGNORE_SCAN	0x00000001

#define CACHE_OP_RATE_SNOOP	0
#define CACHE_OP_RATE_INLINE	20
#define CACHE_OP_RATE_CALLOUT	50
#define CACHE_OP_RATE_MSYNC	100

/* The following flags are for the implementation's internal use */
#define	__CACHE_FLUSH_INLINE	0x80000000
#define	__CACHE_INVAL_INLINE	0x40000000
#define	__CACHE_FLUSH_NOP	0x20000000
#define	__CACHE_INVAL_NOP	0x10000000

#ifdef  __CPU_CACHE_FLUSH
	#define CACHE_FLUSH(__cinfo, __vaddr, __paddr, __len) \
		if (!((__cinfo)->flags & __CACHE_FLUSH_NOP)) { \
			if ((__cinfo)->flags & __CACHE_FLUSH_INLINE) { \
				__cpu_cache_flush(__cinfo, __vaddr, __paddr, __len); \
			} else \
				(__cinfo)->cf.flush(__cinfo, __vaddr, __paddr, __len); \
		}
#else
	#define CACHE_FLUSH(__cinfo, __vaddr, __paddr, __len) \
		if (!((__cinfo)->flags & __CACHE_FLUSH_NOP)) \
			(__cinfo)->cf.flush(__cinfo, __vaddr, __paddr, __len)
#endif

#ifdef  __CPU_CACHE_INVAL
#define CACHE_INVAL(__cinfo, __vaddr, __paddr, __len) \
	if (!((__cinfo)->flags & __CACHE_INVAL_NOP)) { \
		if ((__cinfo)->flags & __CACHE_INVAL_INLINE) \
			__cpu_cache_inval(__cinfo, __vaddr, __paddr, __len); \
		else \
			(__cinfo)->cf.invalidate(__cinfo, __vaddr, __paddr, __len); \
	}
#else
	#define CACHE_INVAL(__cinfo, __vaddr, __paddr, __len) \
		if (!((__cinfo)->flags & __CACHE_INVAL_NOP)) \
			(__cinfo)->cf.invalidate(__cinfo, __vaddr, __paddr, __len);
#endif

__BEGIN_DECLS
extern int cache_init(int flags, struct cache_ctrl *cinfo, const char *dllname);
extern int cache_fini(struct cache_ctrl *cinfo);
extern int cache_get_shmctl_flags( int cache_flags, int *prot_flags, int *shmctl_flags, int *special);
__END_DECLS

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/cache/public/sys/cache.h $ $Rev: 307552 $" )
#endif
#endif /* __CACHE_H_INCLUDED */
