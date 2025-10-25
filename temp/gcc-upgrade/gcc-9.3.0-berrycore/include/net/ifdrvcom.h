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
 * Operations to pull out QNX specific / extended driver info
 * which may be common to across drivers or classes of drivers
 * can be defined here.  This is based on the QNX specific
 * ioctl code SIOCGDRVCOM.  Info specific to a particular driver
 * can use SIOCGDRVSPEC with its subcodes defined local to
 * that driver.
 */

#ifndef _NET_IFDRVCOM_H_INCLUDED
#define _NET_IFDRVCOM_H_INCLUDED

#ifndef _NET_IF_H_INCLUDED
#include <net/if.h>
#endif

#ifndef _HW_NICINFO_H_INCLUDED
#include <hw/nicinfo.h>
#endif

/* SIOCGDRVCOM subcodes */
#define DRVCOM_CONFIG	1
#define DRVCOM_STATS	2
/*
 * Note: we don't do one for nic_wifi_dcmd_t as new
 * drivers probably won't use it.
 */

struct drvcom_config {
	struct ifdrv_com	dcom_cmd;
	nic_config_t		dcom_config;
};

struct drvcom_stats {
	struct ifdrv_com	dcom_cmd;
	nic_stats_t		dcom_stats;
};

#endif /* !_NET_IFDRVCOM_H_INCLUDED */

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/socket/public/net/ifdrvcom.h $ $Rev: 233581 $" )
