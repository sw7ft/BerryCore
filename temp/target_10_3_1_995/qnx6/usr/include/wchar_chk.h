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

#ifndef _WCHAR_H_DECLARED
#error <wchar_chk.h> should not be included directly.
#endif 

#ifndef _WCHAR_CHK_H
#define _WCHAR_CHK_H

#define __ALIAS(name, args, func) name args  __asm__(func);

__BEGIN_DECLS

_C_STD_BEGIN

extern wchar_t * __wcscpy_chk(wchar_t *_Restrict __ws1, const wchar_t *_Restrict __ws2, size_t __osize);
extern wchar_t * __ALIAS(__wcscpy_alias, (wchar_t * _Restrict __ws1, const wchar_t * _Restrict __ws2), "wcscpy");
extern wchar_t * __wcsncpy_chk(wchar_t * _Restrict __ws1, const wchar_t * _Restrict __ws2, size_t __n, size_t __osize);
extern wchar_t * __ALIAS(__wcsncpy_alias, (wchar_t * _Restrict __ws1, const wchar_t * _Restrict __ws2, size_t __n), "wcsncpy");
extern wchar_t * __wcscat_chk(wchar_t *_Restrict __ws1, const wchar_t *_Restrict __ws2, size_t __osize);
extern wchar_t * __ALIAS(__wcscat_alias, (wchar_t * _Restrict __ws1, const wchar_t * _Restrict __ws2), "wcscat");
extern wchar_t * __wcsncpy_chk(wchar_t * _Restrict __ws1, const wchar_t * _Restrict __ws2, size_t __n, size_t __osize);
extern wchar_t * __ALIAS(__wcsncat_alias, (wchar_t * _Restrict __ws1, const wchar_t * _Restrict __ws2, size_t __n), "wcsncat");
extern wchar_t * __wcsncat_chk(wchar_t * _Restrict __ws1, const wchar_t * _Restrict __ws2, size_t __n, size_t __osize);
extern wchar_t * __wmemcpy_chk(wchar_t *__ws1, const wchar_t *__ws2, size_t __n, size_t __osize);
extern wchar_t * __ALIAS(__wmemcpy_alias, (wchar_t * _Restrict __ws1, const wchar_t * _Restrict __ws2, size_t __n), "wmemcpy");
extern wchar_t * __wmemmove_chk(wchar_t *__ws1, const wchar_t *__ws2, size_t __n, size_t __osize);
extern wchar_t * __ALIAS(__wmemmove_alias, (wchar_t * _Restrict __ws1, const wchar_t * _Restrict __ws2, size_t __n), "wmemmove"); 
extern wchar_t * __wmemset_chk(wchar_t *__ws, wchar_t __c, size_t __n, size_t __osize);
extern wchar_t * __ALIAS(__wmemset_alias, (wchar_t * __s, wchar_t __wc, size_t __n), "wmemset"); 

extern __ALWAYS_INLINE __ARTIFICIAL wchar_t * wcscpy(wchar_t * _Restrict __ws1, const wchar_t * _Restrict __ws2) {
  if (__bos(__ws1) != (size_t) -1)
    return __wcscpy_chk(__ws1, __ws2, __bos(__ws1) / sizeof(wchar_t));
  return __wcscpy_alias(__ws1, __ws2);
}

extern __ALWAYS_INLINE __ARTIFICIAL wchar_t * wcsncpy(wchar_t * _Restrict __ws1, const wchar_t * _Restrict __ws2, size_t __n) {
  if (__bos(__ws1) != (size_t) -1)
    return __wcsncpy_chk (__ws1, __ws2, __n, __bos(__ws1) / sizeof(wchar_t));
  return __wcsncpy_alias(__ws1, __ws2, __n);
}

extern __ALWAYS_INLINE __ARTIFICIAL wchar_t * wcscat(wchar_t * _Restrict __ws1, const wchar_t * _Restrict __ws2) {
  if (__bos(__ws1) != (size_t) -1)
    return __wcscat_chk(__ws1, __ws2, __bos(__ws1) / sizeof(wchar_t));
  return __wcscat_alias(__ws1, __ws2);
}

extern __ALWAYS_INLINE __ARTIFICIAL wchar_t * wcsncat(wchar_t * _Restrict __ws1, const wchar_t * _Restrict __ws2, size_t __n) {
  if (__bos(__ws1) != (size_t) -1)
    return __wcsncat_chk(__ws1, __ws2, __n, __bos(__ws1) / sizeof(wchar_t));
  return __wcsncat_alias(__ws1, __ws2, __n);
}

extern __ALWAYS_INLINE __ARTIFICIAL wchar_t * wmemcpy(wchar_t * _Restrict __ws1, const wchar_t * _Restrict __ws2, size_t __n) {
  if (__bos0(__ws1) != (size_t) -1)
    return __wmemcpy_chk(__ws1, __ws2, __n, __bos0(__ws1) / sizeof(wchar_t));
  return __wmemcpy_alias(__ws1, __ws2, __n);
}

extern __ALWAYS_INLINE __ARTIFICIAL wchar_t * wmemmove(wchar_t * _Restrict __ws1, const wchar_t * _Restrict __ws2, size_t __n) {
  if (__bos0(__ws1) != (size_t) -1)
    return __wmemmove_chk(__ws1, __ws2, __n, __bos0(__ws1) / sizeof(wchar_t));
  return __wmemmove_alias(__ws1, __ws2, __n);
}

extern __ALWAYS_INLINE __ARTIFICIAL wchar_t * wmemset(wchar_t * __ws, wchar_t __wc, size_t __n) {
  if (__bos0(__ws) != (size_t) -1)
    return __wmemset_chk(__ws, __wc, __n, __bos0(__ws) / sizeof(wchar_t));
  return __wmemset_alias(__ws, __wc, __n);
}

_C_STD_END

__END_DECLS

#endif 

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL$ $REV$")
#endif
