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
 *  sys/pathmsg.h
 *

 */
#ifndef __PATHMSG_H_INCLUDED
#define __PATHMSG_H_INCLUDED

#if defined(__WATCOMC__) && !defined(_ENABLE_AUTODEPEND)
#pragma read_only_file;
#endif

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef __SYSMSG_H_INCLUDED
#include _NTO_HDR_(sys/sysmsg.h)
#endif

#ifndef __IOMSG_H_INCLUDED
#include _NTO_HDR_(sys/iomsg.h)
#endif

#define PATHMGR_PID				SYSMGR_PID
#define PATHMGR_CHID			SYSMGR_CHID
#define PATHMGR_COID			SYSMGR_COID
#define PATHMGR_HANDLE			SYSMGR_HANDLE
#define PATHMGR_HANDLE_REMOTE	(SYSMGR_HANDLE+1)

enum {
	_PATH_RESOLVE = _PATHMGR_BASE,
	_PATH_CHDIR,
	_PATH_CHROOT,
	_PATH_TRUST,
};


enum {
	_TRUST_ADD,
	_TRUST_LOCK,
	_TRUST_QUERY,
	_TRUST_FILE_FLAG = 0x8000	
};

/*
 * Message of _PATH_TRUST
 */
struct _pathmgr_trust {
	_Uint16t						type;
	_Uint16t						subtype;
	_Uint32t						pid;
	_Uint32t						devno;
	_Uint32t						spare0;
	_Uint64t						inode;
	_Uint32t						spare[4];
};

typedef union {
	struct _pathmgr_trust			i;
} pathmgr_trust_t;


#endif


__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/services/system/public/sys/pathmsg.h $ $Rev: 717286 $" )
