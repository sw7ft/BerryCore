/*
 * $QNXtpLicenseC:
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

/*
 * Copyright (c) 1994-2000 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
 */

#ifndef _WCHAR_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#if !defined(__cplusplus) || defined(_STD_USING) || defined(_GLOBAL_USING)
#define _WCHAR_H_INCLUDED
#endif

#ifndef _WCHAR_H_DECLARED
#define _WCHAR_H_DECLARED

_C_STD_BEGIN

#ifndef NULL
# define NULL _NULL
#endif

#ifndef _Mbstinit
# define _Mbstinit(x)   _Mbstatet x = {0, 0}
#endif /* _Mbstinit */

#ifndef _WCMIN
#error _WCMIN not defined
#endif

#define WCHAR_MIN       _WCMIN
#define WCHAR_MAX       _WCMAX
#ifndef WEOF
#define WEOF            ((_CSTD wint_t)(-1))
#endif

#if defined(__MBSTATE_T)
typedef __MBSTATE_T     mbstate_t;
#undef __MBSTATE_T
#endif

#if defined(__WCHAR_T)
typedef __WCHAR_T       wchar_t;
#undef __WCHAR_T
#endif

#ifndef _WINTT
typedef long            _Wintt;
#define _WINTT
typedef _Wintt          wint_t;
#endif /* _WINTT */

#if defined(__SIZE_T)
typedef __SIZE_T        size_t;
#undef __SIZE_T
#endif

_C_STD_END

#ifdef __FILE_T
typedef __FILE_T        _Filet;
_C_STD_BEGIN
typedef _Filet          FILE;
_C_STD_END
#undef __FILE_T
#endif

_C_STD_BEGIN

struct tm;

_C_LIB_DECL

        /* stdio DECLARATIONS */
wint_t fgetwc(FILE *__stream);
wchar_t *fgetws(wchar_t *_Restrict __ws, int __n, FILE *_Restrict __stream);
wint_t fputwc(wchar_t __wc, FILE *__stream);
int fputws(const wchar_t *_Restrict __ws, FILE *_Restrict __stream);
int fwide(FILE *__stream, int __n);
int fwprintf(FILE *_Restrict __stream, const wchar_t *_Restrict __format, ...);
int fwscanf(FILE *_Restrict __stream, const wchar_t *_Restrict __format, ...);
int vfwscanf(FILE *_Restrict __stream, const wchar_t *_Restrict __format, __NTO_va_list __arg);
int vswscanf(const wchar_t *_Restrict __ws, const wchar_t *_Restrict __format, __NTO_va_list __arg);
int vwscanf(const wchar_t *_Restrict __format, __NTO_va_list __arg);
wint_t getwc(FILE *__stream);
wint_t getwchar(void);
wint_t putwc(wchar_t __wc, FILE *__stream);
wint_t putwchar(wchar_t __wc);
int swprintf(wchar_t *_Restrict __ws, size_t __n, const wchar_t *_Restrict __format, ...);
int swscanf(const wchar_t *_Restrict __ws, const wchar_t *_Restrict __format, ...);
wint_t ungetwc(wint_t __wc, FILE *__stream);
int vfwprintf(FILE *_Restrict __stream, const wchar_t *_Restrict __format, __NTO_va_list __arg);
int vswprintf(wchar_t *_Restrict __ws, size_t __n, const wchar_t *_Restrict __format, __NTO_va_list __arg);
int vwprintf(const wchar_t *_Restrict __format, __NTO_va_list __arg);
int wprintf(const wchar_t *_Restrict __format, ...);
int wscanf(const wchar_t *_Restrict __format, ...);

        /* stdlib DECLARATIONS */
size_t mbrlen(const char *_Restrict __s, size_t __n, mbstate_t *_Restrict __ps);
size_t mbrtowc(wchar_t *_Restrict __pwc, const char *_Restrict __s, size_t __n, mbstate_t *_Restrict __ps);
size_t mbsrtowcs(wchar_t *_Restrict __dst, const char **_Restrict __src, size_t __len, mbstate_t *_Restrict __ps);
int mbsinit(const mbstate_t * __ps);
size_t wcrtomb(char *_Restrict __s, wchar_t __wc, mbstate_t *_Restrict __ps);
size_t wcsrtombs(char *_Restrict __dst, const wchar_t **_Restrict __src, size_t __len, mbstate_t *_Restrict __ps);
long wcstol(const wchar_t *_Restrict __nptr, wchar_t **_Restrict __endptr, int __base);
_Longlong wcstoll(const wchar_t *_Restrict __ntpr, wchar_t **_Restrict __endptr, int __base);

        /* string DECLARATIONS */
wchar_t *wcscat(wchar_t *_Restrict __ws1, const wchar_t *_Restrict __ws2);
int wcscmp(const wchar_t *__ws1, const wchar_t *__ws2);
int wcscoll(const wchar_t *__ws1, const wchar_t *__ws2);
wchar_t *wcscpy(wchar_t *_Restrict __ws1, const wchar_t *_Restrict __ws2);
size_t wcscspn(const wchar_t *__ws1, const wchar_t *__ws2);
size_t wcslen(const wchar_t *__ws);
wchar_t *wcsncat(wchar_t *_Restrict __ws1, const wchar_t *_Restrict __ws2, size_t __n);
int wcsncmp(const wchar_t *__ws1, const wchar_t *__ws2, size_t __n);
wchar_t *wcsncpy(wchar_t *_Restrict __ws1, const wchar_t *_Restrict __ws2, size_t __n);
size_t wcsspn(const wchar_t *__ws1, const wchar_t *__ws2);
wchar_t *wcstok(wchar_t *_Restrict __ws1, const wchar_t *_Restrict __ws2, wchar_t **_Restrict __ptr);
size_t wcsxfrm(wchar_t *_Restrict __ws1, const wchar_t *_Restrict __ws2, size_t __n);
int wmemcmp(const wchar_t *__ws1, const wchar_t *__ws2, size_t __n);
wchar_t *wmemcpy(wchar_t *_Restrict __ws1, const wchar_t *_Restrict __ws2, size_t __n);
wchar_t *wmemmove(wchar_t *__ws1, const wchar_t *__ws2, size_t __n);
wchar_t *wmemset(wchar_t *__ws, wchar_t __wc, size_t __n);

        /* time DECLARATIONS */
size_t wcsftime(wchar_t *_Restrict __ws, size_t __maxsize, const wchar_t *_Restrict __format, const struct tm *_Restrict __timeptr);

wint_t _Btowc(int __c);
int _Wctob(wint_t __wc);
double _WStod(const wchar_t *_Restrict __nptr, wchar_t **_Restrict __endptr, long __base);
float _WStof(const wchar_t *_Restrict __nptr, wchar_t **_Restrict __endptr, long __base);
long double _WStold(const wchar_t *_Restrict __nptr, wchar_t **_Restrict __endptr, long __base);
unsigned long _WStoul(const wchar_t *_Restrict __nptr, wchar_t **_Restrict __endptr, int __base);
_ULonglong _WStoull(const wchar_t *_Restrict __ntpr, wchar_t **_Restrict __endptr, int __base);

_END_C_LIB_DECL

#ifdef __cplusplus
#define _WConst_return const

        /* INLINES AND OVERLOADS, FOR C++ */
_C_LIB_DECL
const wchar_t *wmemchr(const wchar_t *__ws, wchar_t __wc, size_t __n);
const wchar_t *wcschr(const wchar_t *__ws, wchar_t __wc);
const wchar_t *wcspbrk(const wchar_t *__ws1, const wchar_t *__ws2);
const wchar_t *wcsrchr(const wchar_t *__ws, wchar_t __wc);
const wchar_t *wcsstr(const wchar_t *__ws1, const wchar_t *__ws2);
_END_C_LIB_DECL

inline wchar_t *wmemchr(wchar_t *_S, wchar_t _C, size_t _N)
    {   /* call with const first argument */
    union { wchar_t *_Out; const wchar_t * _In; } _Result;
    return (_Result._In = wmemchr((const wchar_t *)_S, _C, _N)), _Result._Out; }

inline wchar_t *wcschr(wchar_t *_S, wchar_t _C)
    {   /* call with const first argument */
    union { wchar_t *_Out; const wchar_t * _In; } _Result;
    return (_Result._In = wcschr((const wchar_t *)_S, _C)), _Result._Out; }

inline wchar_t *wcspbrk(wchar_t *_S, const wchar_t *_P)
    {   /* call with const first argument */
    union { wchar_t *_Out; const wchar_t * _In; } _Result;
    return (_Result._In = wcspbrk((const wchar_t *)_S, _P)), _Result._Out; }

inline wchar_t *wcsrchr(wchar_t *_S, wchar_t _C)
    {   /* call with const first argument */
    union { wchar_t *_Out; const wchar_t * _In; } _Result;
    return (_Result._In = wcsrchr((const wchar_t *)_S, _C)), _Result._Out; }

inline wchar_t *wcsstr(wchar_t *_S, const wchar_t *_P)
    {   /* call with const first argument */
    union { wchar_t *_Out; const wchar_t * _In; } _Result;
    return (_Result._In = wcsstr((const wchar_t *)_S, _P)), _Result._Out; }

inline wint_t btowc(int _C)
    {   /* convert single byte to wide character */
    return (_Btowc(_C)); }

inline double wcstod(const wchar_t *_S,
    wchar_t **_Endptr)
    {   /* convert wide string to double */
    return (_WStod(_S, _Endptr, 0)); }

inline unsigned long wcstoul(const wchar_t *_S,
    wchar_t **_Endptr, int _Base)
    {   /* convert wide string to unsigned long */
    return (_WStoul(_S, _Endptr, _Base)); }

inline _ULonglong wcstoull(const wchar_t *_S,
    wchar_t **_Endptr, int _Base)
    {   /* convert wide string to unsigned long long */
    return (_WStoull(_S, _Endptr, _Base)); }

inline int wctob(wint_t _Wc)
    {   /* convert wide character to single byte */
    return (_Wctob(_Wc)); }

#else /* __cplusplus */
#define _WConst_return

_C_LIB_DECL
wchar_t *wmemchr(const wchar_t *__ws, wchar_t __wc, size_t __n);
wchar_t *wcschr(const wchar_t *__ws, wchar_t __wc);
wchar_t *wcspbrk(const wchar_t *__ws1, const wchar_t *__ws2);
wchar_t *wcsrchr(const wchar_t *__ws, wchar_t __wc);
wchar_t *wcsstr(const wchar_t *__ws1, const wchar_t *__ws2);
wint_t btowc(int __c);
double wcstod(const wchar_t *_Restrict __nptr, wchar_t **_Restrict __endptr);
float wcstof(const wchar_t *_Restrict __ntpr, wchar_t **_Restrict __endptr);
long double wcstold(const wchar_t *_Restrict __ntpr, wchar_t **_Restrict __endptr);
unsigned long wcstoul(const wchar_t *_Restrict __nptr, wchar_t **_Restrict __endptr, int __base);
_ULonglong wcstoull(const wchar_t *_Restrict, wchar_t **_Restrict __endptr, int __base);
int wctob(wint_t __wc);
_END_C_LIB_DECL

#define btowc(c) 					_Btowc(c)
#define wcstod(s, endptr)           _WStod(s, endptr, 0)
#define wcstof(s, endptr)           _WStof(s, endptr, 0)
#define wcstold(s, endptr)          _WStold(s, endptr, 0)
#define wcstoul(s, endptr, base)    _WStoul(s, endptr, base)
#define wcstoull(s, endptr, base)   _WStoull(s, endptr, base)
#define wctob(wc) 					_Wctob(wc)

#endif /* __cplusplus */

_C_STD_END

#if __GNUC__  &&  __USE_FORTIFY_LEVEL > 0
#include <wchar_chk.h>
#endif

#endif /* _WCHAR */

#ifdef _STD_USING
using _CSTD mbstate_t; using _CSTD size_t; using _CSTD tm; using _CSTD wint_t;
using _CSTD btowc; using _CSTD fgetwc; using _CSTD fgetws; using _CSTD fputwc;
using _CSTD fputws; using _CSTD fwide; using _CSTD fwprintf;
using _CSTD fwscanf; using _CSTD getwc; using _CSTD getwchar;
using _CSTD mbrlen; using _CSTD mbrtowc; using _CSTD mbsrtowcs;
using _CSTD mbsinit; using _CSTD putwc; using _CSTD putwchar;
using _CSTD swprintf; using _CSTD swscanf; using _CSTD ungetwc;
using _CSTD vfwprintf; using _CSTD vswprintf; using _CSTD vwprintf;
using _CSTD wcrtomb; using _CSTD wprintf; using _CSTD wscanf;
using _CSTD wcsrtombs; using _CSTD wcstol; using _CSTD wcstoll; using _CSTD wcscat;
using _CSTD wcschr; using _CSTD wcscmp; using _CSTD wcscoll;
using _CSTD wcscpy; using _CSTD wcscspn; using _CSTD wcslen;
using _CSTD wcsncat; using _CSTD wcsncmp; using _CSTD wcsncpy;
using _CSTD wcspbrk; using _CSTD wcsrchr; using _CSTD wcsspn;
using _CSTD wcstod; using _CSTD wcstoul; using _CSTD wcstoull; using _CSTD wcsstr;
using _CSTD wcstok; using _CSTD wcsxfrm; using _CSTD wctob;
using _CSTD wmemchr; using _CSTD wmemcmp; using _CSTD wmemcpy;
using _CSTD wmemmove; using _CSTD wmemset; using _CSTD wcsftime;
#endif /* _STD_USING */

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/c/public/wchar.h $ $REV$")
#endif
