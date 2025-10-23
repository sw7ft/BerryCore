/* Copyright 2009, QNX Software Systems. All Rights Reserved.
 * 
 * You must obtain a written license from and pay applicable license fees to 
 * QNX Software Systems before you may reproduce, modify or distribute this 
 * software, or any work that includes all or part of this software.  Free 
 * development licenses are available for evaluation and non-commercial purposes.  
 * For more information visit http://licensing.qnx.com or email licensing@qnx.com.
 * 
 * This file may contain contributions from others.  Please review this entire 
 * file for other proprietary rights or license notices, as well as the QNX 
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 */
#ifndef _IMG_ERRNO_H_INCLUDED
#define _IMG_ERRNO_H_INCLUDED

#define IMG_ERR_OK			0
#define IMG_ERR_TRUNC		1	/* premature EOF */
#define IMG_ERR_CORRUPT		2	/* unrecoverable error in data stream */
#define IMG_ERR_FORMAT		3	/* file format not recognized */
#define IMG_ERR_NODATA		4	/* no data present */
#define IMG_ERR_NOSUPPORT	5	/* request value/format/conversion not supported */
#define IMG_ERR_MEM			6	/* memory allocation error */
#define IMG_ERR_CFG			7	/* bad or missing config file */
#define IMG_ERR_DLL			8	/* error accessing dll or entrypoint */
#define IMG_ERR_FILE		9	/* file access error */
#define IMG_ERR_INTR		10	/* operation interrupted by application */
#define IMG_ERR_PARM		11	/* invalid parameter */
#define IMG_ERR_NOTIMPL		12	/* operation not implemented */

#endif


#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/img/lib/public/img/img_errno.h $ $Rev: 224588 $" )
#endif
