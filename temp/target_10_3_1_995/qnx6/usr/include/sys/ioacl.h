/*
 * $QNXLicenseC:
 * Copyright 2007, 2009, QNX Software Systems. All Rights Reserved.
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

#ifndef __IOACL_H_INCLUDED
#define __IOACL_H_INCLUDED

#ifndef _ACL_EXT_DATA
#define _ACL_EXT_DATA		struct _acl_header
#endif
_ACL_EXT_DATA;

#ifndef __ACL_H_INCLUDED
#include <sys/acl.h>
#endif

__BEGIN_DECLS
#include <_pack64.h>

struct _acl_header {
	_Uint32t					size;		/* size including header */
	_Int16t						type;		/* ACL_TYPE_* */
	_Uint16t					nents;
};

int iofgetacl(int __fd, _ACL_EXT_DATA *__acl_hdr_data, int __nbytes);
int iofsetacl(int __fd, const _ACL_EXT_DATA *__acl_hdr_data);
int iofchkacl(int __fd, const _ACL_EXT_DATA *__acl_hdr_data);

#include <_packpop.h>
__END_DECLS

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL$ $REV$")
#endif
