/*
 * $QNXtpLicenseC:
 * Copyright 2010, QNX Software Systems. All Rights Reserved.
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

#ifndef _STRING_H_DECLARED
#error <string_chk.h> should not be included directly.
#endif 

#ifndef _STRING_CHK_H
#define _STRING_CHK_H

__BEGIN_DECLS

_C_STD_BEGIN

extern __ALWAYS_INLINE __ARTIFICIAL char * strcpy(char * _Restrict __s1, const char * _Restrict __s2) {
  return __builtin___strcpy_chk(__s1, __s2, __bos(__s1));
}

extern __ALWAYS_INLINE __ARTIFICIAL char * strncpy(char * _Restrict __s1, const char * _Restrict __s2, size_t __n) {
  return __builtin___strncpy_chk(__s1, __s2, __n, __bos(__s1));
}

extern __ALWAYS_INLINE __ARTIFICIAL char * strcat(char * _Restrict __s1, const char * _Restrict __s2) {
  return __builtin___strcat_chk(__s1, __s2, __bos(__s1));
}

extern __ALWAYS_INLINE __ARTIFICIAL char * strncat(char * _Restrict __s1, const char * _Restrict __s2, size_t __n) {
  return __builtin___strncat_chk(__s1, __s2, __n, __bos(__s1));
}

extern __ALWAYS_INLINE __ARTIFICIAL void * memcpy(void * _Restrict __s1, const void * _Restrict __s2, size_t __n) {
  return __builtin___memcpy_chk(__s1, __s2, __n, __bos0(__s1));
}

extern __ALWAYS_INLINE __ARTIFICIAL void * memmove(void * _Restrict __s1, const void * _Restrict __s2, size_t __n) {
  return __builtin___memmove_chk(__s1, __s2, __n, __bos0(__s1));
}

extern __ALWAYS_INLINE __ARTIFICIAL void * memset(void * __s, int __c, size_t __n) {
  return __builtin___memset_chk(__s, __c, __n, __bos0(__s));
}

_C_STD_END

__END_DECLS

#endif 

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL$ $REV$")
#endif
