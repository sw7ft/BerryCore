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
#ifndef __PROXYINFO_H_INCLUDED
#define __PROXYINFO_H_INCLUDED


#include <stdarg.h>
#include <sys/csm.h>

#define		MSG_BUF_SIZE				8192

#define		MAX_URL_LEN				4096
#define		MAX_HOST_LEN				256
#define		PI_MAX_RESULT_LENGTH			262			/* host = 256, colon = 1, port = 5, null = 1*/
#define		PI_IFNAMSIZ				16
#define		MAX_ROUTINGDOMAIN_LEN			256
#define		MAX_EXCL_SIZE           		2048			/* Size of Exclusion list buffer */
#define		MAX_EXCL_ENTRIES			MAX_EXCL_SIZE/4		/* Max number of entries in exclusion list */

#define		PI_CHANNEL_PIP_SET			"pip.set"
#define		PI_CHANNEL_PIP_GET			"pip.get"

#define		PI_PPS_PREFIX				"/pps/services/networking"
#define		EMERALD_SPEC_PATH			"EMERALD_SPECIAL_PATH"

#define		PI_ATTR_PPSPATH				"ppspath"
#define		PI_ATTR_STATICPROXY			"static_proxy"
#define		PI_ATTR_EXCLIST				"exc_list"
#define		PI_ATTR_PACURL				"pac_proxy"
#define		PI_ATTR_HOST				"host"
#define		PI_ATTR_URL				"url"
#define		PI_ATTR_TUNNELPROXY			"tunnel_proxy"
#define		PI_ATTR_MYIPADDRESS			"myipaddress"

#define		PI_RESULT_DIRECT			1
#define		PI_RESULT_PROXY				2
#define		PI_RESULT_ENOSERVER			3
#define		PI_RESULT_ENOMEM			4
#define		PI_RESULT_OK				5			/* For setopt commands only */
#define		PI_RESULT_BADCONFIG			6			/* This would indicate a bug in library (or daemon)*/
#define		PI_RESULT_ENOSERVERORNOPERM		7			/* For commands that require privilegesonly */
#define		PI_RESULT_BADOPTION			8			/* For nonsensical options */
#define		PI_RESULT_BADREQUEST			9			/* For nonsensical requests */


#define		PI_SET_OK				"OK"
#define		PI_SET_BADCONFIG			"BAD CONFIG"
#define		PI_SET_BADREQUEST			"BAD REQUEST"
#define		PI_SET_BADOPTION			"BAD OPTION"


#define		PI_DIRECT_STRING			"DIRECT"

typedef int PI_STATUS;


enum pi_opt_t {
	/*******************************************************/
	/* QUERY OPTIONS: These affect how queries are handled */
	/*******************************************************/
	PI_OPT_AUTOHOST, 					/* ask libproxyinfo to figure out host from 'url' */
	PI_OPT_NOAUTOHOST,					/* disable AUTOHOST (default) */
	PI_OPT_NET_IFACE,					/* Set interface name */
	PI_OPT_ROUTINGDOMAIN,					/* Set routing domain */


	/*******************************************************/
	/* SETTINGS: These affect how the daemon behaves. They */
	/* require privileges (intended mainly for Emerald)    */
	/*******************************************************/
	PI_OPT_NOPROXY,						/* Sets proxy to 'none' */
	PI_OPT_STATICPROXY,					/* Sets a static proxy */
	PI_OPT_TUNNELPROXY,					/* Specifies the proxy to use when downloading PAC file (e.g. Emerald for tunneling) */
	PI_OPT_EXCLIST,						/* Specifies an exclusion list (only for static proxies) */
	PI_OPT_PACPROXY,					/* Sets a PAC proxy */
	PI_OPT_MYIPADDRESS					/* Sets the IP address to be returned by myIpAddress() */
	};
typedef enum pi_opt_t PI_OPT;

typedef struct pi_handle_t {
	char iface_name[PI_IFNAMSIZ];
	char routingdomain[MAX_ROUTINGDOMAIN_LEN];
	msgclient_open_t *mop;					/* For proxy queries (getting)*/
	msgclient_open_t *setmop;				/* For options (setting) requires privileges */
	int autohost;
	char autofigured_host[MAX_HOST_LEN];			/* buffer for when we're auto-figuring host..*/
	char *msgbuf;
} PROXYINFO;

__BEGIN_DECLS
PROXYINFO* pi_init();
PI_STATUS pi_getproxy(PROXYINFO *handle, const char *host, const char *url, char *result, int result_size);
PI_STATUS pi_setopt(PROXYINFO *handle, PI_OPT opt, ...);
void pi_cleanup(PROXYINFO *handle);
__END_DECLS

#endif

#include <sys/srcversion.h>

__SRCVERSION( "$URL$ $Rev$" )
