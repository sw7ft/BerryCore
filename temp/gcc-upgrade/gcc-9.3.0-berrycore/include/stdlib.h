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

#ifndef _STDLIB_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef _MALLOC_H_INCLUDED
#include <malloc.h>
#endif

#if !defined(__cplusplus) || defined(_STD_USING) || defined(_GLOBAL_USING)
#define _STDLIB_H_INCLUDED
#endif

#ifndef _STDLIB_H_DECLARED
#define _STDLIB_H_DECLARED

/*
 * UNIX98 needs the exit status macros from <sys/wait.h>
 */
#if defined(__EXT_XOPEN_EX) && !defined(__WAIT_H_INCLUDED)
#include <sys/wait.h>
#endif

#include <_pack64.h>

_C_STD_BEGIN

#if defined(__EXT_ANSIC_199012)

#if defined(__SIZE_T)
typedef __SIZE_T	size_t;
#undef __SIZE_T
#endif

#if defined(__WCHAR_T)
typedef __WCHAR_T	wchar_t;
#undef __WCHAR_T
#endif

#ifndef NULL
# define NULL _NULL
#endif

#define RAND_MAX        32767u
#define EXIT_SUCCESS    0
#define EXIT_FAILURE    1
#define MB_CUR_MAX		_CSTD _Mbcurmax

typedef struct  {
        int     quot;
        int     rem;
} div_t;

typedef struct  {
        long    quot;
        long    rem;
} ldiv_t;

typedef struct  {
        _Longlong    quot;
        _Longlong    rem;
} lldiv_t;

typedef lldiv_t _Lldiv_t;

#endif

_C_STD_END

#include <_packpop.h>

__BEGIN_DECLS

_C_STD_BEGIN

extern char _Mbcurmax;

/* library private functions */
#define _STOINT_SIGNED		0x1
#define _STOINT_LLONG		0x2
extern _ULonglong _Stoint(const char *, char **, int, int);
extern float _Stof(const char *, char **, long);
extern double _Stod(const char *, char **, long);
extern long double _Stold(const char *, char **, long);

extern _Longlong _Stoll(const char *, char **, int);
extern _ULonglong _Stoull(const char *, char **, int);

typedef int _Cmpfun(const void *, const void *);

#if defined(__EXT_ANSIC_199012)
extern void abort(void) __attribute__((__noreturn__));
extern int abs(int __j);
extern int atexit(void (*__func)(void));
extern int __cxa_atexit(void (*__func)(void *), void *, void *);
extern double atof(const char *__nptr);
extern int atoi(const char *__nptr);
extern long atol(const char *__nptr);
extern void *bsearch(const void *__key, const void *__base, size_t __nmemb, size_t __size, int (*__compar)(const void *__pkey, const void *__pbase));
extern div_t div(int __numer, int __denom);
extern void exit(int __status) __attribute__((__noreturn__));
extern char *getenv(const char *__name);
extern long labs(long __j);
extern ldiv_t ldiv(long __numer, long __denom);
extern int mblen(const char *__s, size_t __n);
extern size_t mbstowcs(wchar_t *__pwcs, const char *__s, size_t __n);
extern int mbtowc(wchar_t *__pwc, const char *__s, size_t __n);
extern void qsort(void *__base, size_t __nmemb, size_t __size, int (*__compar)(const void *, const void *));
extern int rand(void);
extern void srand(unsigned __seed);
extern double strtod(const char *__nptr, char **__endptr);
extern float strtof(const char *__nptr, char **__endptr);
extern long double strtold(const char *__nptr, char **__endptr);
extern long strtol(const char *__nptr, char **__endptr, int __base);
extern unsigned long strtoul(const char *__nptr, char **__endptr, int __base);
extern size_t wcstombs(char *__s, const wchar_t *__pwcs, size_t __n);
extern int wctomb(char *__s, wchar_t __wchar);
extern int system(const char *__cmd);
# if __GNUC__ >= 4
extern void *__dso_handle __attribute__((__visibility__("hidden")));
# else
extern void *__dso_handle;
# endif
#endif

_C_STD_END

#if defined(__EXT_XOPEN_EX)

# if defined (__NYI)
extern long a64l(const char *__s);
extern char *l64a(long __value);
extern int ttyslot(void);
# endif

extern int getsubopt(char **__optionp, char * const *__tokens, char **__valuep);
extern char *initstate(unsigned __seed, char *__state, _CSTD size_t __size);
extern long jrand48(unsigned short __xsubi[3]);
extern void lcong48(unsigned short __param[7]);
extern long mrand48(void);
extern long random(void);
extern char *realpath(const char *__file_name, char *__resolved_name);
extern unsigned short *seed48(unsigned short __seed16v[3]);
extern void setkey(const char *__key);
extern char *setstate(const char *__state);
extern void srandom(unsigned __seed);
extern int posix_openpt(int __oflag);
extern int grantpt(int __fildes);
extern int unlockpt(int __fildes);
extern char *ptsname(int __fildes);
# if defined(__EXT_QNX)
extern char *ptsname_r(int __fildes, char *__buffer, _CSTD size_t __buflen);
# endif
#endif

#if defined(__EXT_POSIX1_199506)
extern int rand_r(unsigned *__seed);
#endif

#if defined(__EXT_UNIX_MISC) || defined(__EXT_POSIX1_200112)
extern int setenv(const char *__name, const char *__value, int __rewrite);
extern int unsetenv(const char *__name);
#endif

#if defined(__EXT_UNIX_MISC)
extern int daemon(int __nochdir, int __noclose);
#endif

#if defined(__EXT_XOPEN_EX)
extern double drand48(void);
extern double erand48(unsigned short x[3]);
extern long lrand48(void);
extern long nrand48(unsigned short x[3]);
extern void srand48(long seed);
/*
-- Not currently supported --

extern char     *ecvt(double __val, int __ndig, int *__dec, int *__sign);
extern char     *fcvt(double __val, int __ndig, int *__dec, int *__sign);
extern char     *gcvt(double __val, int __ndig, char *__buf);
*/
extern char *mktemp(char *__template);
extern int putenv(char *__string);
#endif

#if defined(__EXT_POSIX1_200809) || defined(__EXT_XOPEN_EX)
extern int mkstemp(char *__template);
extern char * mkdtemp(char *__template);
#endif

#if defined(__EXT_ANSIC_199901) || defined(__EXT_POSIX1_200112)
extern void _Exit(int __status);
extern _Longlong llabs(_Longlong __j);
extern _CSTD lldiv_t lldiv(_Longlong __numer, _Longlong _denom);
#endif

#if defined(__EXT_QNX) || defined(__EXT_ANSIC_199901) || defined(__EXT_POSIX1_200112)
extern _Longlong strtoll(const char *__nptr, char **__endptr, int __base);
extern _ULonglong strtoull(const char *__nptr, char **__endptr, int __base);
extern _Longlong  atoll(const char *__nptr);
#endif

#if defined(__EXT_QNX)

/* long long operations */
extern char *lltoa(_Longlong __value, char *__buf, int __radix);
extern char *ulltoa(_ULonglong __value, char *__buf, int __radix);

int clearenv(void);

/* min and max macros */
# if !defined(__max)
#  define __max(a,b) (((a) > (b)) ? (a) : (b))
# endif
# if !defined(max) && !defined(__cplusplus)
#  define max(a,b) (((a) > (b)) ? (a) : (b))
# endif
# if !defined(__min)
#  define __min(a,b) (((a) < (b)) ? (a) : (b))
# endif
# if !defined(min) && !defined(__cplusplus)
#  define min(a,b) (((a) < (b)) ? (a) : (b))
# endif

#endif

#if defined(__EXT_PCDOS)

#ifndef __cplusplus
# define atof(__p) strtod(__p, (char **) NULL)
#endif

extern unsigned atoh(const char *__nptr);

extern char *itoa(int __value, char *__buf, int __radix);
extern char *ltoa(long __value, char *__buf, int __radix);

extern char *_fullpath(char *__buf, const char *__path, _CSTD size_t __size);
extern void searchenv(const char *__name, const char *__env_var, char *__buf);
extern char *ultoa(unsigned long __value, char *__buf, int __radix);
extern char *utoa(unsigned __value, char *__buf, int __radix);

#if defined(__SLIB_DATA_INDIRECT) && !defined(_amblksiz) && !defined(__SLIB)
  extern unsigned *__get_amblksiz_ptr(void);
  #define _amblksiz *(__get_amblksiz_ptr())
#else
  extern unsigned _amblksiz;  /*  mallocs done in multiples of    */
#endif

#endif

__END_DECLS

#endif

#ifdef __cplusplus
# ifdef _MATH_H_INCLUDED
inline int abs(int __j) { return _CSTD abs(__j); };
inline long abs(long __j) { return _CSTD labs(__j); };
# endif
#endif

#ifdef _STD_USING
# ifndef __GCC_BUILTIN
using _CSTD abort; using _CSTD abs;
using _CSTD exit; using _CSTD labs;
# endif
using _CSTD size_t; using _CSTD div_t; using _CSTD ldiv_t;
using _CSTD atexit; using _CSTD __cxa_atexit; using _CSTD getenv;
using _CSTD atof; using _CSTD atoi; using _CSTD atol;
using _CSTD bsearch; using _CSTD div; using _CSTD ldiv;
using _CSTD mblen; using _CSTD mbstowcs; using _CSTD mbtowc;
using _CSTD qsort; using _CSTD rand; using _CSTD strtof;
using _CSTD srand; using _CSTD strtod; using _CSTD strtol;
using _CSTD strtoul; using _CSTD system;
using _CSTD wcstombs; using _CSTD wctomb;
#endif /* _STD_USING */

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/c/public/stdlib.h $ $REV$")
#endif
