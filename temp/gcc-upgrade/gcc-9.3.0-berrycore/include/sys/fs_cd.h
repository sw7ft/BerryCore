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
 * http://licensing.qnx.com/license-guide/ for other information. $
 */
#ifndef __FS_CD_H_INCLUDED
#define __FS_CD_H_INCLUDED

#include <sys/dcmd_blk.h>
#include <sys/platform.h>

#define CDFS_SECTOR_SIZE		2048
#define CDFS_ISO_NAME_MAX		32
#define CDFS_ISO1_NAME_MAX		12
#define CDFS_RRIP_NAME_MAX		255
#define CDFS_JOLIET_NAME_MAX	309
#ifdef PATH_MAX
#define CDFS_PATHNAME_MAX		PATH_MAX
#else
#define CDFS_PATHNAME_MAX		1024
#endif

#define	CDFS_ISO_IDENT			"CD001"
#define	CDFS_HSF_IDENT			"CDROM"
#define	CDFS_ECMA_IDENT			"CDW01"
#define CDFS_CDXA_IDENT			"CD-XA001"

#define CDFS_DIRENT_EXIST		0x01
#define CDFS_DIRENT_DIR			0x02
#define CDFS_DIRENT_ASSOCIATE	0x04
#define CDFS_DIRENT_RECORD		0x08
#define CDFS_DIRENT_PROTECT		0x10
#define CDFS_DIRENT_EXTENT		0x80

#define CDFS_CDXA_MODE2FORM1	0x0800
#define CDFS_CDXA_MODE2FORM2	0x1000
#define CDFS_CDXA_INTERLEAVED	0x2000
#define CDFS_CDXA_CDDA			0x4000

__BEGIN_DECLS

__END_DECLS

__SRCVERSION("$URL: http://svn.ott.qnx.com/product/trunk/services/blk/fs/cd/public/sys/fs_cd.h $ $Rev: 219613 $")
#endif
