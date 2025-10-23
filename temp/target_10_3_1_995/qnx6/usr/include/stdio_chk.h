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

#ifndef _STDIO_H_DECLARED
#error <stdio_chk.h> should not be included directly.
#endif 

#ifndef _STDIO_CHK_H
#define _STDIO_CHK_H

__BEGIN_DECLS

_C_STD_BEGIN

#ifdef __bvap
extern __ALWAYS_INLINE __ARTIFICIAL int sprintf(char *__s, const char *__format, ...) {
  return __builtin___sprintf_chk (__s, __USE_FORTIFY_LEVEL - 1, __bos(__s), __format, __bvap);
}

extern __ALWAYS_INLINE __ARTIFICIAL int snprintf(char *__s, size_t __size, const char *__format, ...) {
  return __builtin___snprintf_chk (__s, __size, __USE_FORTIFY_LEVEL - 1, __bos(__s), __format, __bvap);
}
#endif

extern __ALWAYS_INLINE __ARTIFICIAL int vsprintf(char *__s, const char *__format, __NTO_va_list __arg) {
  return __builtin___vsprintf_chk( __s, __USE_FORTIFY_LEVEL - 1, __bos(__s), __format, __arg);
}

extern __ALWAYS_INLINE __ARTIFICIAL int vsnprintf(char *__s, size_t __size, const char *__format, __NTO_va_list __arg) {
  return __builtin___vsnprintf_chk(__s, __size, __USE_FORTIFY_LEVEL - 1, __bos(__s), __format, __arg);
}

_C_STD_END

__END_DECLS

#endif 

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL$ $REV$")
#endif
