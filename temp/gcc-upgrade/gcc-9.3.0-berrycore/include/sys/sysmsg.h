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
 *  sys/sysmsg.h
 *

 */
#ifndef __SYSMSG_H_INCLUDED
#define __SYSMSG_H_INCLUDED

#if defined(__WATCOMC__) && !defined(_ENABLE_AUTODEPEND)
#pragma read_only_file;
#endif

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef __NEUTRINO_H_INCLUDED
#include _NTO_HDR_(sys/neutrino.h)
#endif

enum _sys_bases {
	_SYSMSG_BASE =		0x0000,
	_SYSMGR_BASE =		0x0000,
	_SYSMGR_MAX = 		0x000f,
	_PROCMGR_BASE = 	0x0010,
	_PROCMGR_MAX = 		0x003f,
	_MEMMGR_BASE =		0x0040,
	_MEMMGR_MAX =		0x006f,
	_PATHMGR_BASE =		0x0070,
	_PATHMGR_MAX = 		0x009f,
	_CPUMSG_BASE =		0x00a0,
	_CPUMSG_MAX =		0x00cf,
	_RSRCDBMGR_BASE =	0x00d0,
	_RSRCDBMGR_MAX =	0x00d3,
	_SYSMSG_MAX =		0x00FF
};

enum {
	_SYS_CONF = _SYSMGR_BASE,
	_SYS_CMD,
	_SYS_LOG,
	_SYS_VENDOR,
	_SYS_XCALL,
	_SYS_GETPAGESIZES,
	_SYS_TRACE
};

enum {
	_SYS_SUB_GET,
	_SYS_SUB_SET
};

enum {
	_SYS_CMD_REBOOT,
	_SYS_CMD_CPUMODE,
	_SYS_CMD_RUNSTATE,
};

enum {
	_SYS_TRACE_ALLOCBUF
};

#include _NTO_HDR_(_pack64.h)

/*
 * Message of _SYS_CONF
 */
struct _sys_conf {
	_Uint16t						type;
	_Uint16t						subtype;
	_Int32t							cmd;
	_Int32t							name;
	_Int32t							spare;
	_Int64t							value;
	/* char							set_info[] */
};

struct _sys_conf_reply {
	_Uint32t						zero[3];
	_Int32t							match;
	_Int64t							value;
	/* char							get_info[] */
};

typedef union {
	struct _sys_conf				i;
	struct _sys_conf_reply			o;
} sys_conf_t;


#define _SYS_CMD_RUNSTATE_CPUMASK	0x0000ffffu
#define _SYS_CMD_RUNSTATE_OFF		0x00010000u
#define _SYS_CMD_RUNSTATE_ON		0x00020000u
#define _SYS_CMD_RUNSTATE_DYN_OFF	0x00040000u
#define _SYS_CMD_RUNSTATE_DYN_ON	0x00080000u
#define _SYS_CMD_RUNSTATE_BITMASK	0x00100000u
#define _SYS_CMD_RUNSTATE_BURST		0x80000000u

/*
 * Message of_SYS_CMD
 */
struct _sys_cmd {
	_Uint16t						type;
	_Uint16t						cmd;
	_Uint32t						mode;
};

typedef union {
	struct _sys_cmd					i;
} sys_cmd_t;


/*
 * Message of _SYS_LOG
 *
 * This message matched alignments of "io_write_t" in "sys/iomsg.h".
 */
struct _sys_log {
	_Uint16t						type;
	_Uint16t						reserved;
	_Uint32t						nbytes;
	_Uint32t						zero[2];
	/* unsigned char				log_data[nbytes] */
};

typedef union {
	struct _sys_log					i;
	/*	nbytes is returned with MsgReply */
} sys_log_t;

/*
 * Message of _SYS_VENDOR
 *
 */
struct _sys_vendor {
	_Uint16t						type;
	_Uint16t						vendor_id;
	_Uint32t						reserved;
	/* vendor message follows */
};

typedef union {
	struct _sys_vendor				i;
} sys_vendor_t;

/*
 * Message of _SYS_XCALL
 *
 */
struct _sys_xcall {
	_Uint16t						type;
	_Uint16t						xcall_msg_len;
	_Uint32t						cpu;
	/* followed by _SYS_CMD message */
};

typedef union {
	struct _sys_xcall				i;
} sys_xcall_t;

/*
 * Message of _SYS_GETPAGESIZES
 *
 */
struct _sys_getpagesizes {
	_Uint16t						type;
};

typedef union {
	struct _sys_getpagesizes				i;
} sys_getpagesizes_t;

#define _SYS_GETPAGESIZES_HIGHUSAGE 0x1U /* only available for mappings marked with SHMCTL_HIGHUSAGE */

/*
 * Message of _SYS_TRACE
 *
 */
struct _sys_trace {
	_Uint16t						type;
	_Uint16t						subtype;
	union {
		struct {
			_Uint64t					size;
		} allocbuf;
	} 								u;
};

struct _sys_trace_reply {
	union {
		struct {
			_Paddr64t					paddr;
		} allocbuf;
	}								u;
};

typedef union {
	struct _sys_trace				i;
	struct _sys_trace_reply			o;
} sys_trace_t;

#include _NTO_HDR_(_packpop.h)

#endif


__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/services/system/public/sys/sysmsg.h $ $Rev: 748652 $" )
