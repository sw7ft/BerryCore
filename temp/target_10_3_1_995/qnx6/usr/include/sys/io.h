/*
 * $QNXLicenseC:
 * Copyright 2009, QNX Software Systems. All Rights Reserved.
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
 * http://licensing.qnx.com/license-guide/ for other information. $
 */
#ifndef __NTO_IO_H_INCLUDED
#define __NTO_IO_H_INCLUDED

#include <stddef.h>
#include <sys/iofunc.h>
#include <sys/iomsg.h>
#include <sys/queue.h>
#include <sys/types.h>
#include <sys/resmgr.h>

__BEGIN_DECLS

#define IO_FLAG_WRITE		0x0000	/* Write pseudo-flag               */
#define IO_FLAG_READ		0x0001	/* Read flag                       */
#define IO_FLAG_ASYNC		0x0002	/* IOReq is B_ASYNC                */
#define IO_FLAG_DONE		0x0004	/* IOReq has completed             */
#define IO_FLAG_ACTIVE		0x0008	/* IOReq is active?                */
#define IO_FLAG_ABORT		0x0010	/* IOReq has been aborted?         */
#define IO_FLAG_COMPLETE	0x0020	/* IOReq must not be aborted       */
#define IO_FLAG_IMMEDIATE	0x0040	/* IOReq bypasses normal sort      */
#define IO_FLAG_PHYS		0x0080	/* Must use physical address       */
/* Bits 0x0100, 0x0200, 0x0400, 0x0800 are libcam.so progress tracking */
#define IO_FLAG_CHAINED		0x1000	/* Internal writebehind chaining   */

#define IO_MEDIA_INVALID	0x0001	/* Media is invalid (formatted)       */
#define IO_MEDIA_CHANGED	0x0002	/* Media has been removed/re-inserted */
#define IO_MEDIA_CHGREQ		0x0004	/* User wants to eject (locked) media */
#define IO_DEVICE_RESET		0x0008	/* Device/bus reset (issue lock/rsrv) */

#define IO_FLUSH_FSYNC		0x0001	/* Flush due to user fsync()      */
#define IO_FLUSH_UMOUNT		0x0002	/* Flush due to umount()          */
#define IO_FLUSH_SYNC		0x0004	/* Flush due to non-specific sync */
#define IO_FLUSH_PERIODIC	0x0008	/* Flush due to fsys timer        */
#define IO_FLUSH_MASK		0x00FF	/* Mask/Reasons for flush call    */
#define IO_FLUSH_NONBLOCK	0x1000	/* Flush should be non-blocking   */
#define IO_FLUSH_DETACH		0x2000	/* Device is detaching itself     */
#define IO_FLUSH_MANDATORY	0x4000	/* Device must implement SC_SYNC  */
#define IO_FLUSH_TOPLEVEL	0x8000	/* Internal transaction nesting   */

#define IO_FLUSH_NOBLKNO	(-1U)	/* Device did not report bad blkno */

typedef struct _param param_t;
typedef struct _ioreq ioreq_t;
typedef struct _ioctrl ioctrl_t;
typedef struct _io_entry io_entry_t;
typedef struct _drvr_entry drvr_entry_t;
typedef struct _io_queue ioque_t;
typedef struct _mdl mdl_t;

/* Memory Descriptor List - describes the data buffers to read/write blocks */
struct _mdl {
	caddr_t		vaddr;		/* Virtual address  */
	paddr_t		paddr;		/* Physical address */
};

/* io-blk specific/private data about each IO request */
struct _param {
	daddr_t	lba;			/* Logical block address                      */
	int		length;			/* Number of blocks                           */
	int		blksize;		/* Block size                                 */
	int		resid;			/* Residual xfer length (failed/untried blks) */
	void	*buflist;		/* Block/cache buffer list                    */
};

/* IO Request queue header */
TAILQ_HEAD(_io_queue, _ioreq);

struct _ioreq {
	unsigned			flags;				/* IO_FLAG_READ ...           */
	int					status;				/* Request status/errno       */
	int					priority;			/* Client request priority    */
	int					nmdl;				/* Number of mdl entries      */
	mdl_t				*mdl;				/* Pointer to mdl entries     */
	param_t				parm;				/* io-blk details             */
	void				*user;				/* Opaque user/private data   */
	int					(*notify)(ioreq_t *ioreq);	/* iodone() callback  */
	ioreq_t				*next;				/* Linked-list of related IO  */
	TAILQ_ENTRY(_ioreq)	qlink;				/* Driver-manipulated queue   */
};

/* The callout functions a disk driver must provide to io-blk */
struct _drvr_entry {
	unsigned	nfuncs;
	int			(*open)(void *hdl, int ioflag, int sflag);
	int			(*close)(void *hdl, int ioflag, int sflag);
	int			(*io)(void *hdl, ioreq_t *ioreq);
	int			(*devctl)(void *hdl, resmgr_context_t *ctp, int ioflag, ioreq_t *tag, unsigned dcmd, void *data, size_t size, int *ret);
	int			(*flush)(void *hdl, unsigned flag);
	int			(*abort)(void *hdl, ioreq_t *ioreq, unsigned flag);
	int			(*msg)(void *hdl, resmgr_context_t *ctp, int ioflag, ioreq_t *tag, io_msg_t *msg);
	int			(*sync)(void *hdl, unsigned flag, daddr_t *bad);
};

#define _DRVR_ENTRY_NFUNCS	((sizeof(drvr_entry_t) - offsetof(drvr_entry_t, open)) / sizeof(void *))

/* The callout functions io-blk must provide to a disk driver */
struct _io_entry {
	unsigned	nfuncs;
	int			(*io_init)(int argc, char *argv[]);
	int			(*io_attach)(void *drvr_hdl, drvr_entry_t *drvr_funcs, const char *path, void **reg_hdl);
	int			(*io_detach)(void *reg_hdl, unsigned flags);
	int			(*io_event)(void *reg_hdl, unsigned flags);
	int			(*io_syncfs)(void *reg_hdl, unsigned flags);
};

#define _IO_ENTRY_NFUNCS	((sizeof(io_entry_t) - offsetof(io_entry_t, io_init)) / sizeof(void *))

__END_DECLS

__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/services/blk/io-blk/public/sys/io.h $ $Rev: 745394 $")
#endif
