/* ymath.h internal header */
#ifndef _YMATH
#define _YMATH
#include <yvals.h>
_C_STD_BEGIN
_C_LIB_DECL

		/* MACROS FOR _FPP_TYPE */
#define _FPP_NONE	0	/* software emulation of FPP */
#define _FPP_X86	1	/* Intel Pentium */
#define _FPP_SPARC	2	/* Sun SPARC */
#define _FPP_MIPS	3	/* SGI MIPS */
#define _FPP_S390	4	/* IBM S/390 */
#define _FPP_PPC	5	/* Motorola PowerPC */
#define _FPP_HPPA	6	/* Hewlett-Packard PA-RISC */
#define _FPP_ALPHA	7	/* Compaq Alpha */
#define _FPP_ARM	8	/* ARM ARM */
#define _FPP_M68K	9	/* Motorola 68xxx */
#define _FPP_SH4	10	/* Hitachi SH4 */
#define _FPP_IA64	11	/* Intel IA64 */
#define _FPP_WCE	12	/* Microsoft Windows CE */

		/* MACROS FOR _Dtest RETURN (0 => ZERO) */
#define _DENORM		(-2)	/* C9X only */
#define _FINITE		(-1)
#define _INFCODE	1
#define _NANCODE	2

		/* MACROS FOR _Feraise ARGUMENT */

 #if _FPP_TYPE == _FPP_X86
  #define _FE_DIVBYZERO	0x04
  #define _FE_INEXACT	0x20
  #define _FE_INVALID	0x01
  #define _FE_OVERFLOW	0x08
  #define _FE_UNDERFLOW	0x10

 #elif _FPP_TYPE == _FPP_SPARC
  #define _FE_DIVBYZERO	0x02
  #define _FE_INEXACT	0x01
  #define _FE_INVALID	0x10
  #define _FE_OVERFLOW	0x08
  #define _FE_UNDERFLOW	0x04

 #elif _FPP_TYPE == _FPP_MIPS
  #define _FE_DIVBYZERO	0x02
  #define _FE_INEXACT	0x01
  #define _FE_INVALID	0x10
  #define _FE_OVERFLOW	0x08
  #define _FE_UNDERFLOW	0x04

 #elif _FPP_TYPE == _FPP_S390
  #define _FE_DIVBYZERO	0x08
  #define _FE_INEXACT	0x01
  #define _FE_INVALID	0x10
  #define _FE_OVERFLOW	0x04
  #define _FE_UNDERFLOW	0x02

 #elif _FPP_TYPE == _FPP_PPC
  #define _FE_DIVBYZERO	0x02
  #define _FE_INEXACT	0x01
  #define _FE_INVALID	0x10
  #define _FE_OVERFLOW	0x08
  #define _FE_UNDERFLOW	0x04

 #elif _FPP_TYPE == _FPP_HPPA
  #define _FE_DIVBYZERO	0x08
  #define _FE_INEXACT	0x01
  #define _FE_INVALID	0x10
  #define _FE_OVERFLOW	0x04
  #define _FE_UNDERFLOW	0x02

 #elif _FPP_TYPE == _FPP_ALPHA
  #define _FE_DIVBYZERO	0x02
  #define _FE_INEXACT	0x10
  #define _FE_INVALID	0x01
  #define _FE_OVERFLOW	0x04
  #define _FE_UNDERFLOW	0x08

 #elif _FPP_TYPE == _FPP_ARM
  #define _FE_DIVBYZERO	0x02
  #define _FE_INEXACT	0x10
  #define _FE_INVALID	0x01
  #define _FE_OVERFLOW	0x04
  #define _FE_UNDERFLOW	0x08

 #elif _FPP_TYPE == _FPP_M68K
  #define _FE_DIVBYZERO	0x02
  #define _FE_INEXACT	0x01
  #define _FE_INVALID	0x10
  #define _FE_OVERFLOW	0x08
  #define _FE_UNDERFLOW	0x04

 #elif _FPP_TYPE == _FPP_SH4
  #define _FE_DIVBYZERO	0x08
  #define _FE_INEXACT	0x01
  #define _FE_INVALID	0x10
  #define _FE_OVERFLOW	0x04
  #define _FE_UNDERFLOW	0x02

 #elif _FPP_TYPE == _FPP_IA64
  #define _FE_DIVBYZERO	0x04
  #define _FE_INEXACT	0x20
  #define _FE_INVALID	0x01
  #define _FE_OVERFLOW	0x08
  #define _FE_UNDERFLOW	0x10

 #elif _FPP_TYPE == _FPP_WCE
  #define _FE_DIVBYZERO	0x08
  #define _FE_INEXACT	0x01
  #define _FE_INVALID	0x10
  #define _FE_OVERFLOW	0x04
  #define _FE_UNDERFLOW	0x02

 #else /* _FPP_TYPE == _FPP_NONE or unknown */
  #undef _FPP_TYPE
  #define _FPP_TYPE	_FPP_NONE

  #define _FE_DIVBYZERO	0x04	/* dummy same as Pentium */
  #define _FE_INEXACT	0x20
  #define _FE_INVALID	0x01
  #define _FE_OVERFLOW	0x08
  #define _FE_UNDERFLOW	0x10
 #endif /* _FPP_TYPE */

		/* TYPE DEFINITIONS */
typedef union
	{	/* pun float types as integer array */
	unsigned short _Word[8];
	float _Float;
	double _Double;
	long double _Long_double;
	} _Dconst;

		/* ERROR REPORTING */
void _Feraise(int);

// These declarations conflict with libstdc++ internals
// workaround by enclosing them in namespace QNX and exporting C-tagged versions
#if defined (__cplusplus)
namespace QNX {
extern "C" {
#endif
		/* double DECLARATIONS */
short _Dtest(double *);
double _Cosh(double, double);
short _Exp(double *, double, long);
double _Log(double, int);
double _Sin(double, unsigned int);
double _Sinh(double, double);
#ifdef _FLOAT_DATA_IS_CONST
extern const _Dconst _Denorm, _Hugeval, _Inf,
	_Nan, _Snan;
#else
extern /* const */ _Dconst _Denorm, _Hugeval, _Inf,
	_Nan, _Snan;
#endif

		/* float DECLARATIONS */
float _FCosh(float, float);
short _FDtest(float *);
short _FExp(float *, float, long);
float _FLog(float, int);
float _FSin(float, unsigned int);
float _FSinh(float, float);
#ifdef _FLOAT_DATA_IS_CONST
extern const _Dconst _FDenorm, _FInf, _FNan, _FSnan;
#else
extern /* const */ _Dconst _FDenorm, _FInf, _FNan, _FSnan;
#endif

		/* long double DECLARATIONS */
long double _LCosh(long double, long double);
short _LDtest(long double *);
short _LExp(long double *, long double, long);
long double _LLog(long double, int);
long double _LSin(long double, unsigned int);
long double _LSinh(long double, long double);
#ifdef _FLOAT_DATA_IS_CONST
extern const _Dconst _LDenorm, _LInf, _LNan, _LSnan;
#else
extern /* const */ _Dconst _LDenorm, _LInf, _LNan, _LSnan;
#endif

 #if defined(__SUNPRO_CC)	/* compiler test */
float fmodf(float, float);
long double fmodl(long double, long double);
 #endif /* defined(__SUNPRO_CC) */

 #if defined(__BORLANDC__)	/* compiler test */
float fmodf(float, float);
float logf(float);
 #endif /* defined(__BORLANDC__) */

#if defined (__cplusplus)
}} /* namespace QNX { extern "C" */
#define _QNX_STD QNX::
#else
#define _QNX_STD
#endif
/* close  QNX namespace and continue with C++ stuff */

/* double DECLARATIONS */
#define QNX_Dtest(a) _QNX_STD _Dtest(a)
#define QNX_Exp(a, b, c) _QNX_STD _Exp(a, b, c)
#define QNX_Cosh(a, b) _QNX_STD _Cosh(a, b)
#define QNX_Log(a, b) _QNX_STD _Log(a, b)
#define QNX_Sin(a, b) _QNX_STD _Sin(a, b)
#define QNX_Sinh(a, b) _QNX_STD _Sinh(a, b)

/* float DECLARATIONS */
#define QNX_FDtest(a) _QNX_STD _FDtest(a)
#define QNX_FExp(a, b, c) _QNX_STD _FExp(a, b, c)
#define QNX_FCosh(a, b) _QNX_STD _FCosh(a, b)
#define QNX_FLog(a, b) _QNX_STD _FLog(a, b)
#define QNX_FSin(a, b) _QNX_STD _FSin(a, b)
#define QNX_FSinh(a, b) _QNX_STD _FSinh(a, b)

/* double DECLARATIONS */
#define QNX_LDtest(a) _QNX_STD _LDtest(a)
#define QNX_LExp(a, b, c) _QNX_STD _LExp(a, b, c)
#define QNX_LCosh(a, b) _QNX_STD _LCosh(a, b)
#define QNX_LLog(a, b) _QNX_STD _LLog(a, b)
#define QNX_LSin(a, b) _QNX_STD _LSin(a, b)
#define QNX_LSinh(a, b) _QNX_STD _LSinh(a, b)

_END_C_LIB_DECL
_C_STD_END
#endif /* _YMATH */

/*
 * Copyright (c) 1992-2006 (c)y P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V5.00:1296 */

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/m/public/ymath.h $ $Rev: 219996 $" )
