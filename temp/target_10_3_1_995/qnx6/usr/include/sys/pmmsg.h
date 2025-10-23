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
 *	pmmsg.h
 *

 */

#ifndef	__PMMSG_H_INCLUDED
#define	__PMMSG_H_INCLUDED

#ifndef	__IOMSG_H_INCLUDED
#include <sys/iomsg.h>
#endif

#ifndef	__PM_H_INCLUDED
#include <sys/pm.h>
#endif

enum _pmm_subtypes {
	_PMM_SETMODE_OLD,	/* uses old 8-bit pm_power_mode_t */
	_PMM_GETATTR_OLD,	/* uses old 8-bit pm_power_mode_t */
	_PMM_GETMODES_OLD,	/* uses old 8-bit pm_power_mode_t */
	_PMM_NOTIFY,
	_PMM_PROPERTY_GET,
	_PMM_PROPERTY_SET,
	_PMM_PROPERTY_ADD,
	_PMM_PROPERTY_LIST,
	_PMM_INITMODE_OLD,	/* uses old 8-bit pm_power_mode_t */
	_PMM_SETMODE,
	_PMM_GETATTR,
	_PMM_GETMODES,
	_PMM_INITMODE_OLD1,	/* supplies only pm_power_mode_t values */
	_PMM_MODEINFO,
	_PMM_INITMODE,
	_PMM_MODEATTR,
	_PMM_DEBUG
};


/*
 * _PMM_SETMODE
 */
struct _pmm_setmode_request {
	struct _io_msg	hdr;
	_Uint32t		flags;
	_Int32t			mode;
};

typedef union {
	struct _pmm_setmode_request		i;
} pmm_setmode_msg_t;


/*
 * _PMM_GETATTR
 */
struct _pmm_getattr_request {
	struct _io_msg	hdr;
	_Uint32t		flags;
	_Int32t			mode;
};

typedef union {
	struct _pmm_getattr_request		i;
	pm_power_attr_t					o;
} pmm_getattr_msg_t;


/*
 * _PMM_GETMODES
 */
struct _pmm_getmodes_request {
	struct _io_msg	hdr;
	_Int32t			num_modes;
};

typedef union {
	struct _pmm_getmodes_request	i;
/*	pm_power_mode_t					modes[num_modes];	*/
} pmm_getmodes_msg_t;


/*
 * _PMM_NOTIFY
 */
struct _pmm_notify_request {
	struct _io_msg	hdr;
	_Uint32t		flags;
	struct sigevent	event;
};

typedef union {
	struct _pmm_notify_request		i;
} pmm_notify_msg_t;


/*
 * _PMM_PROPERTY_*
 */
struct _pmm_property_request {
	struct _io_msg	hdr;
	_Uint32t		id;
	_Int32t			size;
/*  char            data[size]; for _PM_PROPERTY_SET/_ADD	*/
};

typedef union {
	struct _pmm_property_request	i;
/*  char							data[size]; for _PM_PROPERTY_GET	*/
/*  pm_property_attr_t              list[size]; for _PM_PROPERTY_LIST	*/
} pmm_property_msg_t;


/*
 * _PMM_INITMODE
 */
struct _pmm_initmode_request {
	struct _io_msg	hdr;
	_Int32t			cur_mode;
	_Int32t			num_modes;
	struct sigevent	event;
	_Int32t			reserved[8];
/*	pmd_mode_attr_t	modes[num_modes];	*/
};

struct _pmm_initmode_reply {
	_Int32t			new_mode;
	_Int32t			pmm_flags;
	_Int32t			mode_flags;
	_Int32t			reserved[5];
};

typedef union {
	struct _pmm_initmode_request	i;
	struct _pmm_initmode_reply		o;
} pmm_initmode_msg_t;


/*
 * _PMM_MODEINFO
 */
enum _pmm_modeinfo_types {
	_PMD_MODE_QUERY,
	_PMD_MODE_REQUEST,
	_PMD_MODE_CONFIRM
};

struct _pmd_mode_request {
	_Int32t		mode;
	_Uint32t	flags;
};

struct _pmd_mode_confirm {
	_Int32t		mode;
	_Int32t		seqno;
};

struct _pmm_modeinfo_request {
	struct _io_msg	hdr;
	_Uint32t		type;
	union {
		struct _pmd_mode_request	request;
		struct _pmd_mode_confirm	confirm;
		_Uint32t		reserved[7];
	} mi;
};

struct _pmm_modeinfo_reply {
	_Int32t			mode;
	_Uint32t		flags;
	_Uint32t		seqno;
	_Uint32t		reserved[5];
};

typedef union {
	struct _pmm_modeinfo_request	i;
	struct _pmm_modeinfo_reply		o;
} pmm_modeinfo_msg_t;


/*
 * _PMM_MODEATTR
 */
struct _pmm_modeattr_request {
	struct _io_msg	hdr;
	_Int32t			num_modes;
	_Uint32t		flags;
	_Uint32t		reserved[4];
};

typedef union {
	struct _pmm_modeattr_request	i;
/*	pmd_mode_attr_t					modes[num_modes];	*/
} pmm_modeattr_msg_t;

/*
 * _PMM_DEBUG
 */
enum {
	_PMM_DEBUG_TRACE_SET = 0
};

struct _pmm_debug_request {
	struct _io_msg	hdr;
	_Uint32t		cmd;
	_Int32t			flags;
	_Uint32t		reserved[6];
};

typedef union {
	struct _pmm_debug_request		i;
} pmm_debug_msg_t;

#endif

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/pm/public/sys/pmmsg.h $ $Rev: 219996 $" )
