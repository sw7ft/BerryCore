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

#ifndef __ACL_POSIX_H_INCLUDED
#define __ACL_POSIX_H_INCLUDED

#ifdef __ACL_H_INCLUDED
#error sys/acl_posix.h must be included before sys/acl.h and sys/ioacl.h
#endif
#define _ACL_PERMSET_TYPE	_Uint32t
#define _ACL_ENTRY_TYPE		struct _acl_posix_ent
#define _ACL_TYPE			struct _acl
#define _ACL_EXT_DATA		struct _acl_posix
#include <sys/ioacl.h>

/* POSIX types are ACL_TYPE_ACCESS and ACL_TYPE_DEFAULT */
struct _acl_posix_ent {
	_ACL_PERMSET_TYPE			tag_permset;
	id_t						id;
};
#define _ACL_POSIX_PERMSET_MASK	0x00ffffff
#define _ACL_POSIX_TAG_SHIFT	24
#define _ACL_POSIX_TAG_MASK		(0xff << _ACL_POSIX_TAG_SHIFT)

struct _acl_posix {
	struct _acl_header			hdr;
	__FLEXARY(struct _acl_posix_ent, ent);
};

struct _acl {
	int					current;
	int					max;
	struct _acl_posix	posix;
};

/* Some POSIX ACL support functions */
int acl_posix_sort_np(struct _acl_posix *acl);
int acl_posix_check_np(struct _acl_posix const *acl);

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL$ $REV$")
#endif
