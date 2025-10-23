/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
 * 
 * You must obtain a written license from and pay applicable license fees to
 * QNX Software Systems before you may reproduce, modify or distribute this
 * software, or any work that includes all or part of this software.   Free
 * development licenses are available for evaluation and non-commercial
 * purposes.  For more information visit http://licensing.qnx.com or
 * email licensing@qnx.com.
 *  
 * This file may contain contributions from others.  Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.  $
 */
#ifndef __MCD_H_INCLUDED
#define __MCD_H_INCLUDED

/* GENERIC CALLOUT ROUTINE FOR MEDIA NOTIFICATION  */
typedef void mcd_notify(char *iomgr[2], char *device, void *arg);

/* GENERIC CALLOUT ROUTINE FOR CONTENT RECOGNITION */
typedef int mcd_content(char *device, void *arg);

/* RESULT CODES FROM MCD CALLOUT FUNCTIONS         */
#define MCD_RULE_NO_MATCH		(-1)
#define MCD_RULE_MATCHED		(0)
#define MCD_RULE_ABORT(_err)	(_err)

/* MUTLIPLEXED EVENT FOR PATH_MEDIA_PROCMGR        */
#define MCD_PATHMGR_SIGNAL		SIGPHOTON

__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/services/mcd/public/sys/mcd.h $ $Rev: 219613 $")
#endif
