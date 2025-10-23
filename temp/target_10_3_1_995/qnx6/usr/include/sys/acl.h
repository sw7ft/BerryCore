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
#ifndef __ACL_H_INCLUDED
#define __ACL_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

__BEGIN_DECLS

#if defined(__SSIZE_T)
typedef __SSIZE_T       ssize_t;
#undef __SSIZE_T
#endif

#if defined(__ID_T)
typedef __ID_T          id_t;
#undef __ID_T
#endif

typedef enum {
	ACL_EXECUTE,
	ACL_WRITE,
	ACL_READ,
	ACL_PERM_NUM
}							acl_perm_t;

#ifndef _ACL_PERMSET_TYPE
#define _ACL_PERMSET_TYPE	void
#endif
typedef _ACL_PERMSET_TYPE	*acl_permset_t;

typedef enum {
	ACL_UNDEFINED_TAG,
	ACL_USER_OBJ,			/* posix user perms */
	ACL_USER,				/* additional users */
	ACL_GROUP_OBJ,			/* posix group perms */
	ACL_GROUP,				/* additional groups */
	ACL_MASK,				/* highest perms for ACL_USER & all GROUPS */
	ACL_OTHER,				/* posix other perms */
	ACL_TAG_NUM
}							acl_tag_t;

typedef enum {
	ACL_TYPE_ACCESS,		/* access acl minimum is just USER/GROUP/OTHER OBJ's*/
	ACL_TYPE_DEFAULT,		/* default acl applied to new files created in directory */
	ACL_TYPE_NUM
}							acl_type_t;

#ifndef _ACL_ENTRY_TYPE
#define _ACL_ENTRY_TYPE		void
#endif
typedef _ACL_ENTRY_TYPE		*acl_entry_t;
#ifndef _ACL_TYPE
#define _ACL_TYPE			void
#endif
typedef _ACL_TYPE			*acl_t;

#define ACL_UNDEFINED_ID	((id_t)-1)

/* ACL Storage Management */
acl_t acl_dup(acl_t __acl);
int acl_free(void *__obj_p);
acl_t acl_init(int __count);

/* ACL Entry Manipulation */
int acl_copy_entry(acl_entry_t __dest_d, acl_entry_t __src_d);
int acl_create_entry(acl_t *__acl_p, acl_entry_t *__entry_p);
int acl_delete_entry(acl_t __acl, acl_entry_t __entry_d);
int acl_get_entry(acl_t __acl, int __entry_id, acl_entry_t *__entry_p);
#define ACL_FIRST_ENTRY		0
#define ACL_NEXT_ENTRY		1
int acl_valid(acl_t __acl);

int acl_add_perm(acl_permset_t __permset_d, acl_perm_t __perm);
int acl_calc_mask(acl_t *__acl_p);
int acl_clear_perms(acl_permset_t __permset_d);
int acl_delete_perm(acl_permset_t __permset_d, acl_perm_t __perm);
int acl_get_permset(acl_entry_t __entry_d, acl_permset_t *__permset_p);
int acl_set_permset(acl_entry_t __entry_d, acl_permset_t __permset_d);

void *acl_get_qualifier(acl_entry_t __entry_d);
int acl_get_tag_type(acl_entry_t __entry_d, acl_tag_t *__tag_type_p);
int acl_set_qualifier(acl_entry_t __entry_d, const void *__tag_qualifier_p);
int acl_set_tag_type(acl_entry_t __entry_d, acl_tag_t __tag_type);

/* ACL Manipulation on an Object */
int acl_delete_def_file(const char *__path_p);
acl_t acl_get_fd(int __fd);
acl_t acl_get_file(const char *__path_p, acl_type_t __type);
int acl_set_fd(int __fd, acl_t __acl);
int acl_set_file(const char *__path_p, acl_type_t __type, acl_t __acl);

/* ACL Format Translation */
ssize_t acl_copy_ext(void *__buf_p, acl_t __acl, ssize_t __size);
acl_t acl_copy_int(const void *__buf_p);
acl_t acl_from_text(const char *__buf_p);
ssize_t acl_size(acl_t __acl);
char *acl_to_text(acl_t __acl, ssize_t *__len_p);

__END_DECLS

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL$ $REV$")
#endif
