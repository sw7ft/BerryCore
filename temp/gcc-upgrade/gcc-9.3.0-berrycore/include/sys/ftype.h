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
 *  ftype.h    File types.
 *

 */
#ifndef __FTYPE_H_INCLUDED
#define __FTYPE_H_INCLUDED

enum _file_type {
	_FTYPE_MATCHED = -1,
	_FTYPE_ALL = -1,
	_FTYPE_ANY = 0,			/* Path name can be anything */
	_FTYPE_FILE,
	_FTYPE_LINK,			/* Reserved for the Process Manager */
	_FTYPE_SYMLINK,			/* reserved for the Process Manager */
	_FTYPE_PIPE,			/* Reserved for a pipe manager */
	_FTYPE_SHMEM,			/* Reserved for a shared memory object */
	_FTYPE_MQUEUE,			/* Reserved for a message-queue manager */
	_FTYPE_SOCKET,			/* Reserved for a socket manager */
	_FTYPE_SEM,				/* Reserved for a semaphore manager */
	_FTYPE_PHOTON,
	_FTYPE_DUMPER,
	_FTYPE_MOUNT,			/* Receive mount requests on the path */
	_FTYPE_NAME,
	_FTYPE_TYMEM
};

#define _MAJOR_PATHMGR		"pathmgr"	/* Use by path manager only */
#define _MAJOR_DEV			"dev"		/* Devices in /dev with only one instance (/dev/tty) */
#define _MAJOR_BLK_PREFIX	"blk-"		/* All block devices (/dev/hd[0-9]* would be "blk-hd") */
#define _MAJOR_CHAR_PREFIX	"char-"		/* All char devices (/dev/ser[0-9]* would be "char-ser") */
#define _MAJOR_FSYS			"fsys"		/* All filesystems */



#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/c/public/sys/ftype.h $ $REV$")
#endif
