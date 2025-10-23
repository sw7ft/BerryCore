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



#ifndef __AOIRESOURCES_H__
#define __AOIRESOURCES_H__

#include <inttypes.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

/* these types have the resource description in the form <min> <max> <incr> */
/* and get/set values as appropriate */
#define AOR_TYPE_LONG   		0x00000001
#define AOR_TYPE_LONGLONG 		0x00000002
#define AOR_TYPE_FLOAT			0x00000003

/* this type has a maximum length in the resource description as an int32 */
#define AOR_TYPE_STRING			0x00000004

/* this type have a int32_t count, followed by count string pointers */
/* and get/set values as int32_t index into array (multiselect has a first */
/* value as the # indexes) */
#define AOR_TYPE_RADIO			0x00000005

/* this type should point to an int32_t, which is 0 or 1, 1 being on. It */
/* requires to resource description. */
#define AOR_TYPE_TOGGLE			0x00000006

#define AOR_TYPE_POINTER		0x00000007

/* readable/writable through resources? */
#define AOR_TYPE_READABLE		0x10000000
#define AOR_TYPE_WRITABLE		0x20000000

/* enabled/visible? */
#define AOR_TYPE_ENABLED		0x01000000
#define AOR_TYPE_VISIBLE		0x02000000

/* suggested structure for your internal resources storage/handling */
typedef struct
{
	char *name;			/* name of resource */
	char *description;	/* description of resource */
	void *value;		/* filled in later with the value */
	void *info;			/* typing info (ie range, list of items, etc) */
	int32_t type;		/* AOR_TYPE_* flags */
} AOResource_t;

/*
 * Interface for resource access.
 */ 
#define AORESOURCEACCESS_VERSION 100
typedef struct
{
	const AOResource_t *(*GetResources)(void *ctx);
	int32_t (*SetResource)(void *ctx,const char *resource,const void *data);
} AOResourceAccess;

__END_DECLS

#endif




#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/aoi/public/aoi/aoi_resources.h $ $Rev: 280224 $" )
#endif
