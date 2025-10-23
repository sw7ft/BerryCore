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

#ifndef _INTTYPES_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#if !defined(__cplusplus) || defined(_STD_USING) || defined(_GLOBAL_USING)
#define _INTTYPES_H_INCLUDED
#endif

#ifndef _INTTYPES_H_DECLARED
#define _INTTYPES_H_DECLARED

#ifndef _STDINT_H_INCLUDED
#include _NTO_HDR_(stdint.h)
#endif

#define _FMT8           "hh"
#define _FMT16          "h"

#if __INT_BITS__ == 32
#define _FMT32          ""
#if __LONG_BITS__ == 64
#define _FMT64          "l"
#else
#define _FMT64          "ll"
#endif
#elif __INT_BITS__ == 64
#define _FMT32          ""
#define _FMT64          ""
#endif

#define _FMTMAX         "j"     /* intmax_t */
#define _FMTPTR         "t"     /* ptrdiff_t */

#define PRId8			_FMT8 "d"
#define PRId16			_FMT16 "d"
#define PRId32			_FMT32 "d"
#define PRId64			_FMT64 "d"

#define PRIdFAST8		_FMT8 "d"
#define PRIdFAST16		_FMT16 "d"
#define PRIdFAST32		_FMT32 "d"
#define PRIdFAST64		_FMT64 "d"

#define PRIdLEAST8		_FMT8 "d"
#define PRIdLEAST16		_FMT16 "d"
#define PRIdLEAST32		_FMT32 "d"
#define PRIdLEAST64		_FMT64 "d"

#define PRIdMAX			_FMTMAX "d"
#define PRIdPTR			_FMTPTR "d"

#define PRIi8			_FMT8 "i"
#define PRIi16			_FMT16 "i"
#define PRIi32			_FMT32 "i"
#define PRIi64			_FMT64 "i"

#define PRIiFAST8		_FMT8 "i"
#define PRIiFAST16		_FMT16 "i"
#define PRIiFAST32		_FMT32 "i"
#define PRIiFAST64		_FMT64 "i"

#define PRIiLEAST8		_FMT8 "i"
#define PRIiLEAST16		_FMT16 "i"
#define PRIiLEAST32		_FMT32 "i"
#define PRIiLEAST64		_FMT64 "i"

#define PRIiMAX			_FMTMAX "i"
#define PRIiPTR			_FMTPTR "i"

#define PRIo8			_FMT8 "o"
#define PRIo16			_FMT16 "o"
#define PRIo32			_FMT32 "o"
#define PRIo64			_FMT64 "o"

#define PRIoFAST8		_FMT8 "o"
#define PRIoFAST16		_FMT16 "o"
#define PRIoFAST32		_FMT32 "o"
#define PRIoFAST64		_FMT64 "o"

#define PRIoLEAST8		_FMT8 "o"
#define PRIoLEAST16		_FMT16 "o"
#define PRIoLEAST32		_FMT32 "o"
#define PRIoLEAST64		_FMT64 "o"

#define PRIoMAX			_FMTMAX "o"
#define PRIoPTR			_FMTPTR "o"

#define PRIu8			_FMT8 "u"
#define PRIu16			_FMT16 "u"
#define PRIu32			_FMT32 "u"
#define PRIu64			_FMT64 "u"

#define PRIuFAST8		_FMT8 "u"
#define PRIuFAST16		_FMT16 "u"
#define PRIuFAST32		_FMT32 "u"
#define PRIuFAST64		_FMT64 "u"

#define PRIuLEAST8		_FMT8 "u"
#define PRIuLEAST16		_FMT16 "u"
#define PRIuLEAST32		_FMT32 "u"
#define PRIuLEAST64		_FMT64 "u"

#define PRIuMAX			_FMTMAX "u"
#define PRIuPTR			_FMTPTR "u"

#define PRIx8			_FMT8 "x"
#define PRIx16			_FMT16 "x"
#define PRIx32			_FMT32 "x"
#define PRIx64			_FMT64 "x"

#define PRIxFAST8		_FMT8 "x"
#define PRIxFAST16		_FMT16 "x"
#define PRIxFAST32		_FMT32 "x"
#define PRIxFAST64		_FMT64 "x"

#define PRIxLEAST8		_FMT8 "x"
#define PRIxLEAST16		_FMT16 "x"
#define PRIxLEAST32		_FMT32 "x"
#define PRIxLEAST64		_FMT64 "x"

#define PRIxMAX			_FMTMAX "x"
#define PRIxPTR			_FMTPTR "x"

#define PRIX8			_FMT8 "X"
#define PRIX16			_FMT16 "X"
#define PRIX32			_FMT32 "X"
#define PRIX64			_FMT64 "X"

#define PRIXFAST8		_FMT8 "X"
#define PRIXFAST16		_FMT16 "X"
#define PRIXFAST32		_FMT32 "X"
#define PRIXFAST64		_FMT64 "X"

#define PRIXLEAST8		_FMT8 "X"
#define PRIXLEAST16		_FMT16 "X"
#define PRIXLEAST32		_FMT32 "X"
#define PRIXLEAST64		_FMT64 "X"

#define PRIXMAX			_FMTMAX "X"
#define PRIXPTR			_FMTPTR "X"

#define SCNd8			_FMT8 "d"
#define SCNd16			_FMT16 "d"
#define SCNd32			_FMT32 "d"
#define SCNd64			_FMT64 "d"

#define SCNdFAST8		_FMT8 "d"
#define SCNdFAST16		_FMT16 "d"
#define SCNdFAST32		_FMT32 "d"
#define SCNdFAST64		_FMT64 "d"

#define SCNdLEAST8		_FMT8 "d"
#define SCNdLEAST16		_FMT16 "d"
#define SCNdLEAST32		_FMT32 "d"
#define SCNdLEAST64		_FMT64 "d"

#define SCNdMAX			_FMTMAX "d"
#define SCNdPTR			_FMTPTR "d"

#define SCNi8			_FMT8 "i"
#define SCNi16			_FMT16 "i"
#define SCNi32			_FMT32 "i"
#define SCNi64			_FMT64 "i"

#define SCNiFAST8		_FMT8 "i"
#define SCNiFAST16		_FMT16 "i"
#define SCNiFAST32		_FMT32 "i"
#define SCNiFAST64		_FMT64 "i"

#define SCNiLEAST8		_FMT8 "i"
#define SCNiLEAST16		_FMT16 "i"
#define SCNiLEAST32		_FMT32 "i"
#define SCNiLEAST64		_FMT64 "i"

#define SCNiMAX			_FMTMAX "i"
#define SCNiPTR			_FMTPTR "i"

#define SCNo8			_FMT8 "o"
#define SCNo16			_FMT16 "o"
#define SCNo32			_FMT32 "o"
#define SCNo64			_FMT64 "o"

#define SCNoFAST8		_FMT8 "o"
#define SCNoFAST16		_FMT16 "o"
#define SCNoFAST32		_FMT32 "o"
#define SCNoFAST64		_FMT64 "o"

#define SCNoLEAST8		_FMT8 "o"
#define SCNoLEAST16		_FMT16 "o"
#define SCNoLEAST32		_FMT32 "o"
#define SCNoLEAST64		_FMT64 "o"

#define SCNoMAX			_FMTMAX "o"
#define SCNoPTR			_FMTPTR "o"

#define SCNu8			_FMT8 "u"
#define SCNu16			_FMT16 "u"
#define SCNu32			_FMT32 "u"
#define SCNu64			_FMT64 "u"

#define SCNuFAST8		_FMT8 "u"
#define SCNuFAST16		_FMT16 "u"
#define SCNuFAST32		_FMT32 "u"
#define SCNuFAST64		_FMT64 "u"

#define SCNuLEAST8		_FMT8 "u"
#define SCNuLEAST16		_FMT16 "u"
#define SCNuLEAST32		_FMT32 "u"
#define SCNuLEAST64		_FMT64 "u"

#define SCNuMAX			_FMTMAX "u"
#define SCNuPTR			_FMTPTR "u"

#define SCNx8			_FMT8 "x"
#define SCNx16			_FMT16 "x"
#define SCNx32			_FMT32 "x"
#define SCNx64			_FMT64 "x"

#define SCNxFAST8		_FMT8 "x"
#define SCNxFAST16		_FMT16 "x"
#define SCNxFAST32		_FMT32 "x"
#define SCNxFAST64		_FMT64 "x"

#define SCNxLEAST8		_FMT8 "x"
#define SCNxLEAST16		_FMT16 "x"
#define SCNxLEAST32		_FMT32 "x"
#define SCNxLEAST64		_FMT64 "x"

#define SCNxMAX			_FMTMAX "x"
#define SCNxPTR			_FMTPTR "x"

#define SCNX8			_FMT8 "X"
#define SCNX16			_FMT16 "X"
#define SCNX32			_FMT32 "X"
#define SCNX64			_FMT64 "X"

#define SCNXFAST8		_FMT8 "X"
#define SCNXFAST16		_FMT16 "X"
#define SCNXFAST32		_FMT32 "X"
#define SCNXFAST64		_FMT64 "X"

#define SCNXLEAST8		_FMT8 "X"
#define SCNXLEAST16		_FMT16 "X"
#define SCNXLEAST32		_FMT32 "X"
#define SCNXLEAST64		_FMT64 "X"

#define SCNXMAX			_FMTMAX "X"
#define SCNXPTR			_FMTPTR "X"

_C_STD_BEGIN

typedef struct {
	intmax_t quot, rem;
} imaxdiv_t;

__BEGIN_DECLS

intmax_t imaxabs(intmax_t __i);
imaxdiv_t imaxdiv(intmax_t __numer, intmax_t __denom);

intmax_t strtoimax(__const char *__restrict __s, char **__restrict __endptr, int __base);
uintmax_t strtoumax(__const char *__restrict s, char **__restrict __endptr, int __base);
intmax_t wcstoimax(__const _Wchart *__restrict s, _Wchart **__restrict __endptr, int __base);
uintmax_t wcstoumax(__const _Wchart *__restrict s, _Wchart **__restrict __endptr, int __base);

#if defined(__LITTLEENDIAN__)
struct __byte {
	uint8_t		__lo;
	uint8_t		__hi;
};

struct __short {
	uint16_t	__lo;
	uint16_t	__hi;
};

struct __long {
	uint32_t	__lo;
	uint32_t	__hi;
};
#elif defined(__BIGENDIAN__)
struct __byte {
	uint8_t		__hi;
	uint8_t		__lo;
};

struct __short {
	uint16_t	__hi;
	uint16_t	__lo;
};

struct __long {
	uint32_t	__hi;
	uint32_t	__lo;
};
#else
# error endian not configured for system
#endif

__END_DECLS

_C_STD_END

#endif

#ifdef _STD_USING
using _CSTD imaxdiv_t;
using _CSTD imaxabs; using _CSTD imaxdiv;
using _CSTD strtoimax; using _CSTD strtoumax;
using _CSTD wcstoimax; using _CSTD wcstoumax;
#endif /* _STD_USING */

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/c/public/inttypes.h $ $REV$")
#endif
