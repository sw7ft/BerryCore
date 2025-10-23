/* math.h standard header */
#ifndef _MATH
#define _MATH
 #include <xtgmath.h>
#ifndef _YMATH
 #include <ymath.h>
#endif /* _YMATH */

#ifdef __QNX__
#include <_pack64.h>
#endif

_C_STD_BEGIN

/*
 * XOPEN/SVID
 */
#if defined(__EXT_XOPEN_EX)

#define M_E         2.7182818284590452354   /* e */
#define M_LOG2E     1.4426950408889634074   /* log 2e */
#define M_LOG10E    0.43429448190325182765  /* log 10e */
#define M_LN2       0.69314718055994530942  /* log e2 */
#define M_LN10      2.30258509299404568402  /* log e10 */
#define M_PI        3.14159265358979323846  /* pi */
#define M_PI_2      1.57079632679489661923  /* pi/2 */
#define M_PI_4      0.78539816339744830962  /* pi/4 */
#define M_1_PI      0.31830988618379067154  /* 1/pi */
#define M_2_PI      0.63661977236758134308  /* 2/pi */
#define M_2_SQRTPI  1.12837916709551257390  /* 2/sqrt(pi) */
#define M_SQRT2     1.41421356237309504880  /* sqrt(2) */
#define M_SQRT1_2   0.70710678118654752440  /* 1/sqrt(2) */

#define MAXFLOAT    ((float)3.40282346638528860e+38)

#endif

		/* CODES FOR is* FUNCTIONS */
#define _FP_LT	1
#define _FP_EQ	2
#define _FP_GT	4

		/* CODES FOR ilogb FUNCTIONS */

 #if _ILONG
  #define _FP_ILOGB0	(-0x7fffffff - _C2)
  #define _FP_ILOGBNAN	0x7fffffff

 #else /* _ILONG */
  #define _FP_ILOGB0	(-0x7fff - _C2)
  #define _FP_ILOGBNAN	0x7fff
 #endif /* _ILONG */

 #if _HAS_C9X
		/* TYPES */

 #if _FEVAL == 1
typedef double float_t;
typedef double double_t;

 #elif _FEVAL == 2
typedef long double float_t;
typedef long double double_t;

 #else /* _FEVAL */
typedef float float_t;
typedef double double_t;
 #endif /* _FEVAL */

		/* MACROS */

 #if 245 < __EDG_VERSION__ && !defined(__cplusplus)
  #define HUGE_VAL	((double)__INFINITY__)
  #define HUGE_VALF	__INFINITY__
  #define HUGE_VALL	((long double)__INFINITY__)
  #define INFINITY	__INFINITY__
  #define NAN		__NAN__

 #elif defined(__EDG__) || 0 < _MSC_VER
  #define HUGE_VAL	_CSTD _Inf._Double
  #define HUGE_VALF	_CSTD _FInf._Float
  #define HUGE_VALL	_CSTD _LInf._Long_double
  #define INFINITY	_CSTD _FInf._Float
  #define NAN		_CSTD _FNan._Float

 #elif defined(__GNUC__) && (__GNUC__ > 3)
  #define HUGE_VAL	(__builtin_huge_val())
  #define HUGE_VALF	(__builtin_huge_valf())
  #define HUGE_VALL	(__builtin_huge_vall())
  #define INFINITY	(__builtin_inff())
  #define NAN		(__builtin_nanf(""))

 #else /* !defined(__EDG__) */
  #ifndef _HUGE_ENUF
   #define _HUGE_ENUF	1e+30F	/* _HUGE_ENUF*_HUGE_ENUF must overflow */
  #endif /* _HUGE_ENUF */

  #define HUGE_VAL	((double)INFINITY)
  #define HUGE_VALF	((float)INFINITY)
  #define HUGE_VALL	((long double)INFINITY)
  #define INFINITY	((float)(_HUGE_ENUF * _HUGE_ENUF))
  #define NAN		((float)(INFINITY * 0.0F))
 #endif /* 245 < __EDG_VERSION__ */

#define FP_INFINITE		_INFCODE
#define FP_NAN			_NANCODE
#define FP_NORMAL		_FINITE
#define FP_SUBNORMAL	_DENORM
#define FP_ZERO			0

 #if _HAS_C9X_FAST_FMA
  #define FP_FAST_FMA	1
  #define FP_FAST_FMAF	1
  #define FP_FAST_FMAL	1
 #endif /* _HAS_C9X_FAST_FMA */

 #define FP_ILOGB0		_FP_ILOGB0
 #define FP_ILOGBNAN	_FP_ILOGBNAN

#define MATH_ERRNO			1
#define MATH_ERREXCEPT		2
#define math_errhandling	(MATH_ERRNO | MATH_ERREXCEPT)	/* do both */

_C_LIB_DECL
int _FFpcomp(float, float);
int _Fpcomp(double, double);
int _LFpcomp(long double, long double);

int _FDclass(float);
int _Dclass(double);
int _LDclass(long double);

int _FDsign(float);
int _Dsign(double);
int _LDsign(long double);
_END_C_LIB_DECL

 #if _HAS_GENERIC_TEMPLATES
		// TEMPLATE FUNCTION _FPCOMP
inline int _FPCOMP(float _Left, float _Right)
	{	// compare _Left and _Right
	return (_FFpcomp(_Left, _Right));
	}

inline int _FPCOMP(double _Left, double _Right)
	{	// compare _Left and _Right
	return (_Fpcomp(_Left, _Right));
	}

inline int _FPCOMP(long double _Left, long double _Right)
	{	// compare _Left and _Right
	return (_LFpcomp(_Left, _Right));
	}

template<class _T1, class _T2> inline
	int _FPCOMP(_T1 _Left, _T2 _Right)
	{	// compare _Left and _Right
	typedef typename _Combined_type<float,
		typename _Real_widened<
			typename _Real_type<_T1>::_Type,
			typename _Real_type<_T2>::_Type>::_Type>::_Type _Tw;
	return (_FPCOMP((_Tw)_Left, (_Tw)_Right));
	}

		// FUNCTION fpclassify
inline int fpclassify(float _Left)
	{	// classify argument
	return (_FDtest(&_Left));
	}

inline int fpclassify(double _Left)
	{	// classify argument
	return (_Dtest(&_Left));
	}

inline int fpclassify(long double _Left)
	{	// classify argument
	return (_LDtest(&_Left));
	}

		// FUNCTION signbit
inline bool signbit(float _Left)
	{	// test sign bit
	return (_FDsign(_Left) != 0);
	}

inline bool signbit(double _Left)
	{	// test sign bit
	return (_Dsign(_Left) != 0);
	}

inline bool signbit(long double _Left)
	{	// test sign bit
	return (_LDsign(_Left) != 0);
	}

template<class _Ty> inline
	bool isfinite(_Ty _Left)
	{	// test for finite
	return (fpclassify(_Left) <= 0);
	}

template<class _Ty> inline
	bool isinf(_Ty _Left)
	{	// test for infinite
	return (fpclassify(_Left) == FP_INFINITE);
	}

template<class _Ty> inline
	bool isnan(_Ty _Left)
	{	// test for NaN
	return (fpclassify(_Left) == FP_NAN);
	}

template<class _Ty> inline
	bool isnormal(_Ty _Left)
	{	// test for normal
	return (fpclassify(_Left) == FP_NORMAL);
	}

template<class _Ty1, class _Ty2> inline
	bool isgreater(_Ty1 _Left, _Ty2 _Right)
	{	// test for _Left > _Right
	return ((_FPCOMP(_Left, _Right) & _FP_GT) != 0);
	}

template<class _Ty1, class _Ty2> inline
	bool isgreaterequal(_Ty1 _Left, _Ty2 _Right)
	{	// test for _Left >= _Right
	return ((_FPCOMP(_Left, _Right) & (_FP_EQ | _FP_GT)) != 0);
	}

template<class _Ty1, class _Ty2> inline
	bool isless(_Ty1 _Left, _Ty2 _Right)
	{	// test for _Left < _Right
	return ((_FPCOMP(_Left, _Right) & _FP_LT) != 0);
	}

template<class _Ty1, class _Ty2> inline
	bool islessequal(_Ty1 _Left, _Ty2 _Right)
	{	// test for _Left <= _Right
	return ((_FPCOMP(_Left, _Right) & (_FP_LT | _FP_EQ)) != 0);
	}

template<class _Ty1, class _Ty2> inline
	bool islessgreater(_Ty1 _Left, _Ty2 _Right)
	{	// test for _Left != _Right
	return ((_FPCOMP(_Left, _Right) & (_FP_LT | _FP_GT)) != 0);
	}

template<class _Ty1, class _Ty2> inline
	bool isunordered(_Ty1 _Left, _Ty2 _Right)
	{	// test for _Left unorderd w.r.t. _Right
	return (_FPCOMP(_Left, _Right) == 0);
	}

  #define fpclassify(x) 		(_CSTD fpclassify(x))
  #define signbit(x)			(_CSTD signbit(x))
  #define isfinite(x)			(_CSTD isfinite(x))
  #define isinf(x)				(_CSTD isinf(x))
  #define isnan(x)				(_CSTD isnan(x))
  #define isnormal(x)			(_CSTD isnormal(x))
  #define isgreater(x, y)		(_CSTD isgreater(x, y))
  #define isgreaterequal(x, y)	(_CSTD isgreaterequal(x, y))
  #define isless(x, y)			(_CSTD isless(x, y))
  #define islessequal(x, y)		(_CSTD islessequal(x, y))
  #define islessgreater(x, y)	(_CSTD islessgreater(x, y))
  #define isunordered(x, y)		(_CSTD isunordered(x, y))

 #else /* _HAS_GENERIC_TEMPLATES */

  #if __EDG__
   #define _CARGI(x, fd, ff, fl) \
	__generic(x,,, fd, ff, fl,,,)(x)
   #define _CARG2I(x, y, fd, ff, fl) \
	__generic(x, y,, fd, ff, fl,,,)(x, y)

  #elif 2 <= __GNUC__
   #define _FLT_TYPE(expression)	_FLT_OR_DBL(__typeof__ (expression))
   #define _FLT_OR_DBL(mytype)	__typeof__ (*(0 \
	? (__typeof__ (0 ? (mytype *)0 : (void *)((mytype)0.5 == 0)))0 \
	: (__typeof__ (0 ? (double *)0 : (void *)((mytype)0.5 != 0)))0))

   #define _CARGI(x, fd, ff, fl) \
	(__extension__({ \
	int _Ans; \
	if (sizeof (_FLT_TYPE(x)) == sizeof (double)) \
		_Ans = fd(x); \
	else if (sizeof (_FLT_TYPE(x)) == sizeof (float)) \
	_Ans = ff(x); \
	else \
		_Ans = fl(x); \
	_Ans; \
	}))
   #define _CARG2I(x, y, fd, ff, fl) \
	(__extension__({ \
	int _Ans; \
	if (sizeof (_FLT_TYPE((x) + (y))) == sizeof (double)) \
		_Ans = fd(x, y); \
	else if (sizeof (_FLT_TYPE((x) + (y))) == sizeof (float)) \
		_Ans = ff(x, y); \
	else \
		_Ans = fl(x, y); \
	_Ans; \
	}))

  #else /* compiler type */
   #define _ARG(x)	(sizeof ((x) + (float)0) == sizeof (float) ? 'f' \
	: sizeof ((x) + (double)0) == sizeof (double) ? 'd' \
	: 'l')
   #define _CARGI(x, fd, ff, fl)	\
	(_ARG(x) == 'f' ? ff((float)(x)) \
	: _ARG(x) == 'd' ? fd((double)(x)) \
	: fl((long double)(x)))
   #define _CARG2I(x, y, fd, ff, fl)	\
	(_ARG((x) + (y)) == 'f' ? ff((float)(x), (float)(y)) \
	: _ARG((x) + (y)) == 'd' ? fd((double)(x), (double)(y)) \
	: fl((long double)(x), (long double)(y)))
  #endif /* compiler type */

  #define _FPCOMP(x, y) \
	_CARG2I(x, y, _Fpcomp, _FFpcomp, _LFpcomp)
  #define fpclassify(x) \
	_CARGI(x, _Dclass, _FDclass, _LDclass)
  #define signbit(x) \
	_CARGI(x, _Dsign, _FDsign, _LDsign)

#define isfinite(x)	(fpclassify(x) <= 0)
#define isinf(x)	(fpclassify(x) == FP_INFINITE)
#define isnan(x)	(fpclassify(x) == FP_NAN)
#define isnormal(x)	(fpclassify(x) == FP_NORMAL)

#define isgreater(x, y)	((_FPCOMP(x, y) & _FP_GT) != 0)
#define isgreaterequal(x, y)	\
	((_FPCOMP(x, y) & (_FP_EQ | _FP_GT)) != 0)
#define isless(x, y)	((_FPCOMP(x, y) & _FP_LT) != 0)
#define islessequal(x, y)	((_FPCOMP(x, y) & (_FP_LT | _FP_EQ)) != 0)
#define islessgreater(x, y)	\
	((_FPCOMP(x, y) & (_FP_LT | _FP_GT)) != 0)
#define isunordered(x, y)	(_FPCOMP(x, y) == 0)
 #endif /* _HAS_GENERIC_TEMPLATES */

 #else /* _IS_C9X */
		/* MACROS */
 #define HUGE_VAL	_CSTD _Hugeval._Double
 #endif /* _IS_C9X */

_C_LIB_DECL
		/* double declarations */
double acos(double);
double asin(double);
double atan(double);
double atan2(double, double);
double ceil(double);
double exp(double);
double fabs(double);
double floor(double);
double fmod(double, double);
double frexp(double, int *);
double ldexp(double, int);
double modf(double, double *);
double pow(double, double);
double sqrt(double);
double tan(double);
double tanh(double);

 #if _HAS_C9X
double acosh(double);
double asinh(double);
double atanh(double);
double cbrt(double);
double copysign(double, double);
double erf(double);
double erfc(double);
double exp2(double);
double expm1(double);
double fdim(double, double);
double fma(double, double, double);
double fmax(double, double);
double fmin(double, double);
double hypot(double, double);
int ilogb(double);
double lgamma(double);
_Longlong llrint(double);
_Longlong llround(double);
double log1p(double);
double logb(double);
long lrint(double);
long lround(double);
double nan(const char *);
double nearbyint(double);
double nextafter(double, double);
double nexttoward(double, long double);
double remainder(double, double);
double remquo(double, double, int *);
double rint(double);
double round(double);
double scalbn(double, int);
double scalbln(double, long);
double tgamma(double);
double trunc(double);
 #endif /* _IS_C9X */

#if defined(__EXT_QNX)
double lgamma_r(double,int*);
float lgammaf_r(float,int*);
long double lgammal_r(long double,int*);
#endif

#if defined(__EXT_UNIX_HIST)
		/* Deprecated functions, use C99 lgamma*() functions instead */
float gammaf(float) __attribute__((__const__,__deprecated__));
float gammaf_r(float,int*) __attribute__((__const__,__deprecated__));
double gamma(double) __attribute__((__const__,__deprecated__));
double gamma_r(double,int*) __attribute__((__const__,__deprecated__));
#endif

#if defined(__EXT_UNIX_MISC)
		/* Compatibility functions */
int finite(double) __attribute__((__const__,__deprecated__)); /* use isfinite macro */
int finitef(float) __attribute__((__const__,__deprecated__)); /* use isfinite macro */
int isinff(float) __attribute__((__const__,__deprecated__)); /* use isinf macro */
int isnanf(float) __attribute__((__const__,__deprecated__)); /* use isnan macro */
double drem(double, double) __attribute__((__const__,__deprecated__)); /* use remainder */
float dremf(float, float) __attribute__((__const__,__deprecated__)); /* use remainder */
float significandf(float) __attribute__((__const__,__deprecated__)); /* use scalbn(x, -ilogb(x) */
double significand(double) __attribute__((__const__,__deprecated__)); /* use scalbnf(x, -ilogbf(x) */
float scalbf(float, float) __attribute__((__const__,__deprecated__)); /* use scalbn */
#endif

		/* Bessel functions */
#if defined(__EXT_XOPEN_EX)
double j0(double);
double j1(double);
double jn(int, double);
double y0(double);
double y1(double);
double yn(int, double);
#endif

#if defined(__EXT_UNIX_MISC)
		/* XSI Obsolete functions */
double scalb(double, double) __attribute__((__const__));
#endif

		/* float declarations */
float acosf(float);
float asinf(float);
float atanf(float);
float atan2f(float, float);
float ceilf(float);
float expf(float);
float fabsf(float);
float floorf(float);
float fmodf(float, float);
float frexpf(float, int *);
float ldexpf(float, int);
float modff(float, float *);
float powf(float, float);
float sqrtf(float);
float tanf(float);
float tanhf(float);

 #if _HAS_C9X
float acoshf(float);
float asinhf(float);
float atanhf(float);
float cbrtf(float);
float copysignf(float, float);
float erff(float);
float erfcf(float);
float expm1f(float);
float exp2f(float);
float fdimf(float, float);
float fmaf(float, float, float);
float fmaxf(float, float);
float fminf(float, float);
float hypotf(float, float);
int ilogbf(float);
float lgammaf(float);
_Longlong llrintf(float);
_Longlong llroundf(float);
float log1pf(float);
float logbf(float);
long lrintf(float);
long lroundf(float);
float nanf(const char *);
float nearbyintf(float);
float nextafterf(float, float);
float nexttowardf(float, long double);
float remainderf(float, float);
float remquof(float, float, int *);
float rintf(float);
float roundf(float);
float scalbnf(float, int);
float scalblnf(float, long);
float tgammaf(float);
float truncf(float);
 #endif /* _IS_C9X */


		/* long double declarations */
long double acosl(long double);
long double asinl(long double);
long double atanl(long double);
long double atan2l(long double, long double);
long double ceill(long double);
long double expl(long double);
long double fabsl(long double);
long double floorl(long double);
long double fmodl(long double, long double);
long double frexpl(long double, int *);
long double ldexpl(long double, int);
long double modfl(long double, long double *);
long double powl(long double, long double);
long double sqrtl(long double);
long double tanl(long double);
long double tanhl(long double);

 #if _HAS_C9X
long double acoshl(long double);
long double asinhl(long double);
long double atanhl(long double);
long double cbrtl(long double);
long double copysignl(long double, long double);
long double erfl(long double);
long double erfcl(long double);
long double exp2l(long double);
long double expm1l(long double);
long double fdiml(long double, long double);
long double fmal(long double, long double, long double);
long double fmaxl(long double, long double);
long double fminl(long double, long double);
long double hypotl(long double, long double);
int ilogbl(long double);
long double lgammal(long double);
_Longlong llrintl(long double);
_Longlong llroundl(long double);
long double log1pl(long double);
long double logbl(long double);
long lrintl(long double);
long lroundl(long double);
long double nanl(const char *);
long double nearbyintl(long double);
long double nextafterl(long double, long double);
long double nexttowardl(long double, long double);
long double remainderl(long double, long double);
long double remquol(long double, long double, int *);
long double rintl(long double);
long double roundl(long double);
long double scalbnl(long double, int);
long double scalblnl(long double, long);
long double tgammal(long double);
long double truncl(long double);
 #endif /* _IS_C9X */

_END_C_LIB_DECL

 #if defined(__cplusplus) && !defined(_NO_CPP_INLINES)

  #if _IS_EMBEDDED

  #else /* _IS_EMBEDDED */
		// TEMPLATE FUNCTION _Pow_int
template<class _Ty> inline
	_Ty _Pow_int(_Ty _Left, int _Right)
	{	// raise to integer power
	unsigned int _Num = _Right;
	if (_Right < 0)
		_Num = 0 - _Num;

	for (_Ty _Ans = 1; ; _Left *= _Left)
		{	// scale and fold in factors
		if ((_Num & 1) != 0)
			_Ans *= _Left;
		if ((_Num >>= 1) == 0)
			return ((_Ty)(0 <= _Right ? _Ans
				: _Ans == _Ty(0) ? HUGE_VAL : _Ty(1) / _Ans));
		}
	}
  #endif /* _IS_EMBEDDED */

		// double INLINES, FOR C++
_C_LIB_DECL
inline double cos(double _Left)
	{	// return cosine
	return (_Sin(_Left, 1));
	}

inline double cosh(double _Left)
	{	// return hyperbolic cosine
	return (_Cosh(_Left, 1));
	}

inline double log(double _Left)
	{	// return natural logarithm
	return (_Log(_Left, 0));
	}

inline double log10(double _Left)
	{	// return base-10 logarithm
	return (_Log(_Left, 1));
	}

inline double sin(double _Left)
	{	// return sine
	return (_Sin(_Left, 0));
	}

inline double sinh(double _Left)
	{	// return hyperbolic sine
	return (_Sinh(_Left, 1));
	}

 #if _HAS_C9X
inline double log2(double _Left)
	{	// return base-2 logarithm
	return (_Log(_Left, -1));
	}
 #endif /* _IS_C9X */

_END_C_LIB_DECL

inline double abs(double _Left)	// OVERLOADS
	{	// return absolute value
	return (fabs(_Left));
	}

 #if _IS_EMBEDDED
inline double pow(double _Left, int _Right)
	{	// raise to integer power
	unsigned int _Num = _Right;
	if (_Right < 0)
		_Num = 0 - _Num;

	for (double _Ans = 1; ; _Left *= _Left)
		{if ((_Num & 1) != 0)
			_Ans *= _Left;
		if ((_Num >>= 1) == 0)
			return (_Right < 0 ? (double)(1) / _Ans : _Ans);
		}
	}

 #else /* _IS_EMBEDDED */
inline double pow(double _Left, int _Right)
	{	// raise to integer power
	return (_Pow_int(_Left, _Right));
	}
 #endif /* _IS_EMBEDDED */

		// float INLINES, FOR C++
_C_LIB_DECL
inline float cosf(float _Left)
	{	// return cosine
	return (_FSin(_Left, 1));
	}

inline float coshf(float _Left)
	{	// return hyperbolic cosine
	return (_FCosh(_Left, 1));
	}

inline float logf(float _Left)
	{	// return natural logarithm
	return (_FLog(_Left, 0));
	}

inline float log10f(float _Left)
	{	// return base-10 logarithm
	return (_FLog(_Left, 1));
	}

inline float sinf(float _Left)
	{	// return sine
	return (_FSin(_Left, 0));
	}

inline float sinhf(float _Left)
	{	// return hyperbolic sine
	return (_FSinh(_Left, 1));
	}

 #if _HAS_C9X
inline float log2f(float _Left)
	{	// return base-2 logarithm
	return (_FLog(_Left, -1));
	}
 #endif /* _IS_C9X */

_END_C_LIB_DECL

inline float abs(float _Left)	// OVERLOADS
	{	// return absolute value
	return (fabsf(_Left));
	}

inline float acos(float _Left)
	{	// return arccosine
	return (acosf(_Left));
	}

inline float asin(float _Left)
	{	// return arcsine
	return (asinf(_Left));
	}

inline float atan(float _Left)
	{	// return arctangent
	return (atanf(_Left));
	}

inline float atan2(float _Left, float _Right)
	{	// return arctangent
	return (atan2f(_Left, _Right));
	}

inline float ceil(float _Left)
	{	// return ceiling
	return (ceilf(_Left));
	}

inline float cos(float _Left)
	{	// return cosine
	return (_FSin(_Left, 1));
	}

inline float cosh(float _Left)
	{	// return hyperbolic cosine
	return (_FCosh(_Left, 1));
	}

inline float exp(float _Left)
	{	// return exponential
	return (expf(_Left));
	}

inline float fabs(float _Left)
	{	// return absolute value
	return (fabsf(_Left));
	}

inline float floor(float _Left)
	{	// return floor
	return (floorf(_Left));
	}

inline float fmod(float _Left, float _Right)
	{	// return modulus
	return (fmodf(_Left, _Right));
	}

inline float frexp(float _Left, int *_Right)
	{	// unpack exponent
	return (frexpf(_Left, _Right));
	}

inline float ldexp(float _Left, int _Right)
	{	// pack exponent
	return (ldexpf(_Left, _Right));
	}

inline float log(float _Left)
	{	// return natural logarithm
	return (_FLog(_Left, 0));
	}

inline float log10(float _Left)
	{	// return base-10 logarithm
	return (_FLog(_Left, 1));
	}

inline float modf(float _Left, float *_Right)
	{	// unpack fraction
	return (modff(_Left, _Right));
	}

inline float pow(float _Left, float _Right)
	{	// raise to power
	return (powf(_Left, _Right));
	}

 #if _IS_EMBEDDED
inline float pow(float _Left, int _Right)
	{	// raise to integer power
	unsigned int _Num = _Right;
	if (_Right < 0)
		_Num = 0 - _Num;

	for (float _Ans = 1; ; _Left *= _Left)
		{if ((_Num & 1) != 0)
			_Ans *= _Left;
		if ((_Num >>= 1) == 0)
			return (_Right < 0 ? (float)(1) / _Ans : _Ans);
		}
	}

 #else /* _IS_EMBEDDED */
inline float pow(float _Left, int _Right)
	{	// raise to integer power
	return (_Pow_int(_Left, _Right));
	}
 #endif /* _IS_EMBEDDED */

inline float sin(float _Left)
	{	// return sine
	return (_FSin(_Left, 0));
	}

inline float sinh(float _Left)
	{	// return hyperbolic sine
	return (_FSinh(_Left, 1));
	}

inline float sqrt(float _Left)
	{	// return square root
	return (sqrtf(_Left));
	}

inline float tan(float _Left)
	{	// return tangent
	return (tanf(_Left));
	}

inline float tanh(float _Left)
	{	// return hyperbolic tangent
	return (tanhf(_Left));
	}

 #if _HAS_C9X
inline float acosh(float _Left)
	{	// return hyperbolic arccosine
	return (acoshf(_Left));
	}

inline float asinh(float _Left)
	{	// return hyperbolic arcsine
	return (asinhf(_Left));
	}

inline float atanh(float _Left)
	{	// return hyperbolic arctangent
	return (atanhf(_Left));
	}

inline float cbrt(float _Left)
	{	// return cube root
	return (cbrtf(_Left));
	}

inline float copysign(float _Left, float _Right)
	{	// return copysign
	return (copysignf(_Left, _Right));
	}

inline float erf(float _Left)
	{	// return erf
 	return (erff(_Left)); }

inline float erfc(float _Left)
	{	// return erfc
	return (erfcf(_Left));
	}

inline float exp2(float _Left)
	{	// return exp2
	return (exp2f(_Left));
	}

inline float expm1(float _Left)
	{	// return expml
	return (expm1f(_Left));
	}

inline float fdim(float _Left, float _Right)
	{	// return fdim
	return (fdimf(_Left, _Right));
	}

inline float fma(float _Left, float _Right, float _Addend)
	{	// return fma
	return (fmaf(_Left, _Right, _Addend));
	}

inline float fmax(float _Left, float _Right)
	{	// return fmax
	return (fmaxf(_Left, _Right));
	}

inline float fmin(float _Left, float _Right)
	{	// return fmin
	return (fminf(_Left, _Right));
	}

inline float hypot(float _Left, float _Right)
	{	// return hypot
	return (hypotf(_Left, _Right));
	}

inline int ilogb(float _Left)
	{	// return ilogb
	return (ilogbf(_Left));
	}

inline float lgamma(float _Left)
	{	// return lgamma
	return (lgammaf(_Left));
	}

inline _Longlong llrint(float _Left)
	{	// return llrint
	return (llrintf(_Left));
	}

inline _Longlong llround(float _Left)
	{	// return llround
	return (llroundf(_Left));
	}

inline float log1p(float _Left)
	{	// return loglp
	return (log1pf(_Left));
	}

inline float log2(float _Left)
	{	// return log2
	return (_FLog(_Left, -1));
	}

inline float logb(float _Left)
	{	// return logb
	return (logbf(_Left));
	}

inline long lrint(float _Left)
	{	// return lrint
	return (lrintf(_Left));
	}

inline long lround(float _Left)
	{	// return lround
	return (lroundf(_Left));
	}

inline float nearbyint(float _Left)
	{	// return nearbyint
	return (nearbyintf(_Left));
	}

inline float nextafter(float _Left, float _Right)
	{	// return nextafter
	return (nextafterf(_Left, _Right));
	}

inline float nexttoward(float _Left, long double _Right)
	{	// return nexttoward
	return (nexttowardf(_Left, _Right));
	}

inline float remainder(float _Left, float _Right)
	{	// return remainder
	return (remainderf(_Left, _Right));
	}

inline float remquo(float _Left, float _Right, int *_Pval)
	{	// return remquo
	return (remquof(_Left, _Right, _Pval));
	}

inline float rint(float _Left)
	{	// return rint
	return (rintf(_Left));
	}

inline float round(float _Left)
	{	// return round
	return (roundf(_Left));
	}

inline float scalbn(float _Left, int _Right)
	{	// return scalbn
	return (scalbnf(_Left, _Right));
	}

inline float scalbln(float _Left, long _Right)
	{	// return scalbln
	return (scalblnf(_Left, _Right));
	}

inline float tgamma(float _Left)
	{	// return tgamma
	return (tgammaf(_Left));
	}

inline float trunc(float _Left)
	{	// return trunc
	return (truncf(_Left));
	}
 #endif /* _IS_C9X */


		// long double INLINES, FOR C++
_C_LIB_DECL
inline long double cosl(long double _Left)
	{	// return cosine
	return (_LSin(_Left, 1));
	}

inline long double coshl(long double _Left)
	{	// return hyperbolic cosine
	return (_LCosh(_Left, 1));
	}

inline long double logl(long double _Left)
	{	// return natural logarithm
	return (_LLog(_Left, 0));
	}

inline long double log10l(long double _Left)
	{	// return base-10 logarithm
	return (_LLog(_Left, 1));
	}

inline long double sinl(long double _Left)
	{	// return sine
	return (_LSin(_Left, 0));
	}

inline long double sinhl(long double _Left)
	{	// return hyperbolic sine
	return (_LSinh(_Left, 1));
	}

 #if _HAS_C9X
inline long double log2l(long double _Left)
	{	// return base-2 logarithm
	return (_LLog(_Left, -1));
	}
 #endif /* _IS_C9X */

_END_C_LIB_DECL

inline long double abs(long double _Left)	// OVERLOADS
	{	// return absolute value
	return (fabsl(_Left));
	}

inline long double acos(long double _Left)
	{	// return arccosine
	return (acosl(_Left));
	}

inline long double asin(long double _Left)
	{	// return arcsine
	return (asinl(_Left));
	}

inline long double atan(long double _Left)
	{	// return arctangent
	return (atanl(_Left));
	}

inline long double atan2(long double _Left, long double _Right)
	{	// return arctangent
	return (atan2l(_Left, _Right));
	}

inline long double ceil(long double _Left)
	{	// return ceiling
	return (ceill(_Left));
	}

inline long double cos(long double _Left)
	{	// return cosine
	return (_LSin(_Left, 1));
	}

inline long double cosh(long double _Left)
	{	// return hyperbolic cosine
	return (_LCosh(_Left, 1));
	}

inline long double exp(long double _Left)
	{	// return exponential
	return (expl(_Left));
	}

inline long double fabs(long double _Left)
	{	// return absolute value
	return (fabsl(_Left));
	}

inline long double floor(long double _Left)
	{	// return floor
	return (floorl(_Left));
	}

inline long double fmod(long double _Left, long double _Right)
	{	// return modulus
	return (fmodl(_Left, _Right));
	}

inline long double frexp(long double _Left, int *_Right)
	{	// unpack exponent
	return (frexpl(_Left, _Right));
	}

inline long double ldexp(long double _Left, int _Right)
	{	// pack exponent
	return (ldexpl(_Left, _Right));
	}

inline long double log(long double _Left)
	{	// return natural logarithm
	return (_LLog(_Left, 0));
	}

inline long double log10(long double _Left)
	{	// return base-10 logarithm
	return (_LLog(_Left, 1));
	}

inline long double modf(long double _Left, long double *_Right)
	{	// unpack fraction
	return (modfl(_Left, _Right));
	}

inline long double pow(long double _Left, long double _Right)
	{	// raise to power
	return (powl(_Left, _Right));
	}

 #if _IS_EMBEDDED
inline long double pow(long double _Left, int _Right)
	{	// raise to integer power
	unsigned int _Num = _Right;
	if (_Right < 0)
		_Num = 0 - _Num;

	for (long double _Ans = 1; ; _Left *= _Left)
		{if ((_Num & 1) != 0)
			_Ans *= _Left;
		if ((_Num >>= 1) == 0)
			return (_Right < 0 ? (long double)(1) / _Ans : _Ans);
		}
	}

 #else /* _IS_EMBEDDED */
inline long double pow(long double _Left, int _Right)
	{	// raise to integer power
	return (_Pow_int(_Left, _Right));
	}
 #endif /* _IS_EMBEDDED */

inline long double sin(long double _Left)
	{	// return sine
	return (_LSin(_Left, 0));
	}

inline long double sinh(long double _Left)
	{	// return hyperbolic sine
	return (_LSinh(_Left, 1));
	}

inline long double sqrt(long double _Left)
	{	// return square root
	return (sqrtl(_Left));
	}

inline long double tan(long double _Left)
	{	// return tangent
	return (tanl(_Left));
	}

inline long double tanh(long double _Left)
	{	// return hyperbolic tangent
	return (tanhl(_Left));
	}

 #if _HAS_C9X
inline long double acosh(long double _Left)
	{	// return acosh
	return (acoshl(_Left));
	}

inline long double asinh(long double _Left)
	{	// return asinh
	return (asinhl(_Left));
	}

inline long double atanh(long double _Left)
	{	// return atanh
	return (atanhl(_Left));
	}

inline long double cbrt(long double _Left)
	{	// return cbrt
	return (cbrtl(_Left));
	}

inline long double copysign(long double _Left, long double _Right)
	{	// return copysign
	return (copysignl(_Left, _Right));
	}

inline long double erf(long double _Left)
	{	// return erf
	return (erfl(_Left));
	}

inline long double erfc(long double _Left)
	{	// return erfc
	return (erfcl(_Left));
	}

inline long double exp2(long double _Left)
	{	// return exp2
	return (exp2l(_Left));
	}

inline long double expm1(long double _Left)
	{	// return expml
	return (expm1l(_Left));
	}

inline long double fdim(long double _Left, long double _Right)
	{	// return fdim
	return (fdiml(_Left, _Right));
	}

inline long double fma(long double _Left, long double _Right,
	long double _Addend)
	{	// return fma
	return (fmal(_Left, _Right, _Addend));
	}

inline long double fmax(long double _Left, long double _Right)
	{	// return fmax
	return (fmaxl(_Left, _Right));
	}

inline long double fmin(long double _Left, long double _Right)
	{	// return fmin
	return (fminl(_Left, _Right));
	}

inline long double hypot(long double _Left, long double _Right)
	{	// return hypot
	return (hypotl(_Left, _Right));
	}

inline int ilogb(long double _Left)
	{	// return ilogb
	return (ilogbl(_Left));
	}

inline long double lgamma(long double _Left)
	{	// return lgamma
	return (lgammal(_Left));
	}

inline _Longlong llrint(long double _Left)
	{	// return llrint
	return (llrintl(_Left));
	}

inline _Longlong llround(long double _Left)
	{	// return llround
	return (llroundl(_Left));
	}

inline long double log1p(long double _Left)
	{	// return loglp
	return (log1pl(_Left));
	}

inline long double log2(long double _Left)
	{	// return log2
	return (_LLog(_Left, -1));
	}

inline long double logb(long double _Left)
	{	// return logb
	return (logbl(_Left));
	}

inline long lrint(long double _Left)
	{	// return lrint
	return (lrintl(_Left));
	}

inline long lround(long double _Left)
	{	// return lround
	return (lroundl(_Left));
	}

inline long double nearbyint(long double _Left)
	{	// return nearbyint
	return (nearbyintl(_Left));
	}

inline long double nextafter(long double _Left, long double _Right)
	{	// return nextafter
	return (nextafterl(_Left, _Right));
	}

inline long double nexttoward(long double _Left, long double _Right)
	{	// return nexttoward
	return (nexttowardl(_Left, _Right));
	}

inline long double remainder(long double _Left, long double _Right)
	{	// return remainder
	return (remainderl(_Left, _Right));
	}

inline long double remquo(long double _Left, long double _Right,
	int *_Pval)
	{	// return remquo
	return (remquol(_Left, _Right, _Pval));
	}

inline long double rint(long double _Left)
	{	// return rint
	return (rintl(_Left));
	}

inline long double round(long double _Left)
	{	// return round
	return (roundl(_Left));
	}

inline long double scalbn(long double _Left, int _Right)
	{	// return scalbn
	return (scalbnl(_Left, _Right));
	}

inline long double scalbln(long double _Left, long _Right)
	{	// return scalbln
	return (scalblnl(_Left, _Right));
	}

inline long double tgamma(long double _Left)
	{	// return tgamma
	return (tgammal(_Left));
	}

inline long double trunc(long double _Left)
	{	// return trunc
	return (truncl(_Left));
	}
 #endif /* _IS_C9X */


 #else /* defined(__cplusplus) && !defined(_NO_CPP_INLINES) */
_C_LIB_DECL
		/* double MACRO OVERRIDES, FOR C */
double cos(double);
double cosh(double);
double log(double);
double log10(double);
double sin(double);
double sinh(double);

#ifdef __QNX__
 #ifdef _FAST_COS
 #define cos(x)	_FAST_COS(x)
 #else
 #define cos(x)	_CSTD _Sin(x, 1)
 #endif
 #ifdef _FAST_COSH
 #define cosh(x)	_FAST_COSH(x)
 #else 
 #define cosh(x)	_CSTD _Cosh(x, 1)
 #endif
 #ifdef _FAST_LOG
 #define log(x)	_FAST_LOG(x)
 #else
 #define log(x)	_CSTD _Log(x, 0)
 #endif
 #ifdef _FAST_LOG10
 #define log10(x)	_FAST_LOG10(x)
 #else
 #define log10(x)	_CSTD _Log(x, 1)
 #endif
 #ifdef _FAST_SIN
 #define sin(x)	_FAST_SIN(x)
 #else
 #define sin(x)	_CSTD _Sin(x,0)
 #endif
 #ifdef _FAST_SINH
 #define sinh(x)	_FAST_SINH(x)
 #else
 #define sinh(x)	_CSTD _Sinh(x, 1)
 #endif
#else
 #define cos(x)		_Sin(x, 1)
 #define cosh(x)	_Cosh(x, 1)
 #define log(x)		_Log(x, 0)
 #define log10(x)	_Log(x, 1)
 #define sin(x)		_Sin(x, 0)
 #define sinh(x)	_Sinh(x, 1)
#endif /* __QNX__ */

 #if _HAS_C9X
double log2(double);

 #define log2(x)	_CSTD _Log(x, -1)
 #endif /* _IS_C9X */

		/* float MACRO OVERRIDES, FOR C */
float cosf(float);
float coshf(float);
float logf(float);
float log10f(float);
float sinf(float);
float sinhf(float);

#ifdef __QNX__
 #ifdef _FAST_COSF
 #define cosf(x)	_FAST_COSF(x)
 #else
 #define cosf(x)	_CSTD _FSin(x, 1)
 #endif
 #ifdef _FAST_COSHF
 #define coshf(x)	_FAST_COSHF(x)
 #else
 #define coshf(x)	_CSTD _FCosh(x, 1)
 #endif
 #ifdef _FAST_LOGF
 #define logf(x)	_FAST_LOGF(x)
 #else
 #define logf(x)	_CSTD _FLog(x, 0)
 #endif
 #ifdef _FAST_LOG10F
 #define log10f(x)	_FAST_LOG10F(x)
 #else
 #define log10f(x)	_CSTD _FLog(x, 1)
 #endif
 #ifdef _FAST_SINF
 #define sinf(x)	_FAST_SINF(x)
 #else
 #define sinf(x)	_CSTD _FSin(x, 0)
 #endif
 #ifdef _FAST_SINHF
 #define sinhf(x)	_FAST_SINHF(x)
 #else
 #define sinhf(x)	_CSTD _FSinh(x, 1)
 #endif
#else
 #define cosf(x)	_FSin(x, 1)
 #define coshf(x)	_FCosh(x, 1)
 #define logf(x)	_FLog(x, 0)
 #define log10f(x)	_FLog(x, 1)
 #define sinf(x)	_FSin(x, 0)
 #define sinhf(x)	_FSinh(x, 1)
#endif /* __QNX__ */

 #if _HAS_C9X
float log2f(float);

 #define log2f(x)	_CSTD _FLog(x, -1)
 #endif /* _IS_C9X */

		/* long double MACRO OVERRIDES, FOR C */
long double cosl(long double);
long double coshl(long double);
long double logl(long double);
long double log10l(long double);
long double sinl(long double);
long double sinhl(long double);

#ifdef __QNX__
 #ifdef _FAST_COSL
 #define cosl(x)	_FAST_COSL(x)
 #else
 #define cosl(x)	_CSTD _LSin(x, 1)
 #endif
 #ifdef _FAST_COSHL
 #define coshl(x)	_FAST_COSHL(x)
 #else
 #define coshl(x)	_CSTD _LCosh(x, 1)
 #endif
 #ifdef _FAST_LOGL
 #define logl(x)	_FAST_LOGL(x)
 #else
 #define logl(x)	_CSTD _LLog(x, 0)
 #endif
 #ifdef _FAST_LOG10L
 #define log10l(x)	_FAST_LOG10L(x)
 #else
 #define log10l(x)	_CSTD _LLog(x, 1)
 #endif
 #ifdef _FAST_SINL
 #define sinl(x)	_FAST_SINL(x)
 #else
 #define sinl(x)	_CSTD _LSin(x, 0)
 #endif
 #ifdef _FAST_SINHL
 #define sinhl(x)	_FAST_SINHL(x)
 #else
 #define sinhl(x)	_CSTD _LSinh(x, 1)
 #endif
#else
 #define sinhl(x)	_LSinh(x, 1)
 #define cosl(x)	_LSin(x, 1)
 #define coshl(x)	_LCosh(x, 1)
 #define logl(x)	_LLog(x, 0)
 #define log10l(x)	_LLog(x, 1)
 #define sinl(x)	_LSin(x, 0)
 #define sinhl(x)	_LSinh(x, 1)
#endif

 #if _HAS_C9X
long double log2l(long double);

 #define log2l(x)	_CSTD _LLog(x, -1)
 #endif /* _IS_C9X */

_END_C_LIB_DECL
 #endif /* defined(__cplusplus) && !defined(_NO_CPP_INLINES) */

_C_STD_END

		/* GENERIC TEMPLATES */

 #if _HAS_GENERIC_TEMPLATES
_C_STD_BEGIN
	_TGEN_RC(acos)	// real or complex generic overloads
	_TGEN_RC(acosh)
	_TGEN_RC(asin)
	_TGEN_RC(asinh)
	_TGEN_RC(atan)
	_TGEN_RC(atanh)
	_TGEN_RC( (cos) ) /* () avoids macro expansion w/ _NO_CPP_INLINES */
	_TGEN_RC( (cosh) )
	_TGEN_RC(exp)
	_TGEN_RC0(fabs)
	_TGEN_RC( (log) )
	_TGEN_RC( (log10) )
	_TGEN_RC2(pow)
	_TGEN_RC( (sin) )
	_TGEN_RC( (sinh) )
	_TGEN_RC(sqrt)
	_TGEN_RC(tan)
	_TGEN_RC(tanh)

	_TGEN_R2(atan2)	// real generic overloads
	_TGEN_R(cbrt)
	_TGEN_R(ceil)
	_TGEN_R2(copysign)
	_TGEN_R(erf)
	_TGEN_R(erfc)
	_TGEN_R(exp2)
	_TGEN_R(expm1)
	_TGEN_R2(fdim)
	_TGEN_R(floor)
	_TGEN_R3(fma)
	_TGEN_R2(fmax)
	_TGEN_R2(fmin)
	_TGEN_R2(fmod)
	_TGEN_RX(frexp, int *)
	_TGEN_R2(hypot)
	_TGEN_RI(ilogb, int)
	_TGEN_RX(ldexp, int)
	_TGEN_R(lgamma)
	_TGEN_RI(llrint, _Longlong)
	_TGEN_RI(llround, _Longlong)
	_TGEN_R(log1p)
	_TGEN_R( (log2) )
	_TGEN_R(logb)
	_TGEN_RI(lrint, long)
	_TGEN_RI(lround, long)
	_TGEN_R(nearbyint)
	_TGEN_R2(nextafter)
	_TGEN_RX(nexttoward, long double)
	_TGEN_R2(remainder)
	_TGEN_R2X(remquo, int *)
	_TGEN_R(rint)
	_TGEN_R(round)
	_TGEN_RX(scalbln, long)
	_TGEN_RX(scalbn, int)
	_TGEN_R(tgamma)
	_TGEN_R(trunc)
_C_STD_END
 #endif /* _HAS_GENERIC_TEMPLATES */

#endif /* _MATH */

 #if defined(_STD_USING)

  #if !defined(_NO_CPP_INLINES)
using _CSTD abs;
  #endif /* !defined(_NO_CPP_INLINES) */

using _CSTD acos; using _CSTD asin;
using _CSTD atan; using _CSTD atan2; using _CSTD ceil;
using _CSTD cos; using _CSTD cosh; using _CSTD exp;
using _CSTD fabs; using _CSTD floor; using _CSTD fmod;
using _CSTD frexp; using _CSTD ldexp; using _CSTD log;
using _CSTD log10; using _CSTD modf; using _CSTD pow;
using _CSTD sin; using _CSTD sinh; using _CSTD sqrt;
using _CSTD tan; using _CSTD tanh;

using _CSTD acosf; using _CSTD asinf;
using _CSTD atanf; using _CSTD atan2f; using _CSTD ceilf;
using _CSTD cosf; using _CSTD coshf; using _CSTD expf;
using _CSTD fabsf; using _CSTD floorf; using _CSTD fmodf;
using _CSTD frexpf; using _CSTD ldexpf; using _CSTD logf;
using _CSTD log10f; using _CSTD modff; using _CSTD powf;
using _CSTD sinf; using _CSTD sinhf; using _CSTD sqrtf;
using _CSTD tanf; using _CSTD tanhf;

using _CSTD acosl; using _CSTD asinl;
using _CSTD atanl; using _CSTD atan2l; using _CSTD ceill;
using _CSTD cosl; using _CSTD coshl; using _CSTD expl;
using _CSTD fabsl; using _CSTD floorl; using _CSTD fmodl;
using _CSTD frexpl; using _CSTD ldexpl; using _CSTD logl;
using _CSTD log10l; using _CSTD modfl; using _CSTD powl;
using _CSTD sinl; using _CSTD sinhl; using _CSTD sqrtl;
using _CSTD tanl; using _CSTD tanhl;

 #if _HAS_C9X

 #if _HAS_GENERIC_TEMPLATES
using _CSTD _FPCOMP; using _CSTD fpclassify;
using _CSTD signbit; using _CSTD isfinite; using _CSTD isinf;
using _CSTD isnan; using _CSTD isnormal;
using _CSTD isgreater; using _CSTD isgreaterequal;
using _CSTD isless; using _CSTD islessequal; using _CSTD islessgreater;
using _CSTD isunordered;
 #endif	/* _HAS_GENERIC_TEMPLATES */

using _CSTD float_t; using _CSTD double_t;

using _CSTD acosh; using _CSTD asinh; using _CSTD atanh;
using _CSTD cbrt; using _CSTD erf; using _CSTD erfc;
using _CSTD expm1; using _CSTD exp2;
using _CSTD hypot; using _CSTD ilogb; using _CSTD lgamma;
using _CSTD log1p; using _CSTD log2; using _CSTD logb;
using _CSTD llrint; using _CSTD lrint; using _CSTD nearbyint;
using _CSTD rint; using _CSTD llround; using _CSTD lround;
using _CSTD fdim; using _CSTD fma; using _CSTD fmax; using _CSTD fmin;
using _CSTD round; using _CSTD trunc;
using _CSTD remainder; using _CSTD remquo;
using _CSTD copysign; using _CSTD nan; using _CSTD nextafter;
using _CSTD scalbn; using _CSTD scalbln;
using _CSTD nexttoward; using _CSTD tgamma;

using _CSTD acoshf; using _CSTD asinhf; using _CSTD atanhf;
using _CSTD cbrtf; using _CSTD erff; using _CSTD erfcf;
using _CSTD expm1f; using _CSTD exp2f;
using _CSTD hypotf; using _CSTD ilogbf; using _CSTD lgammaf;
using _CSTD log1pf; using _CSTD log2f; using _CSTD logbf;
using _CSTD llrintf; using _CSTD lrintf; using _CSTD nearbyintf;
using _CSTD rintf; using _CSTD llroundf; using _CSTD lroundf;
using _CSTD fdimf; using _CSTD fmaf; using _CSTD fmaxf; using _CSTD fminf;
using _CSTD roundf; using _CSTD truncf;
using _CSTD remainderf; using _CSTD remquof;
using _CSTD copysignf; using _CSTD nanf;
using _CSTD nextafterf; using _CSTD scalbnf; using _CSTD scalblnf;
using _CSTD nexttowardf; using _CSTD tgammaf;

using _CSTD acoshl; using _CSTD asinhl; using _CSTD atanhl;
using _CSTD cbrtl; using _CSTD erfl; using _CSTD erfcl;
using _CSTD expm1l; using _CSTD exp2l;
using _CSTD hypotl; using _CSTD ilogbl; using _CSTD lgammal;
using _CSTD log1pl; using _CSTD log2l; using _CSTD logbl;
using _CSTD llrintl; using _CSTD lrintl; using _CSTD nearbyintl;
using _CSTD rintl; using _CSTD llroundl; using _CSTD lroundl;
using _CSTD fdiml; using _CSTD fmal; using _CSTD fmaxl; using _CSTD fminl;
using _CSTD roundl; using _CSTD truncl;
using _CSTD remainderl; using _CSTD remquol;
using _CSTD copysignl; using _CSTD nanl;
using _CSTD nextafterl; using _CSTD scalbnl; using _CSTD scalblnl;
using _CSTD nexttowardl; using _CSTD tgammal;
 #endif /* _IS_C9X */

 #endif /* defined(_STD_USING) */


/*
 * Copyright (c) 1992-2006 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V5.00:1296 */

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/m/public/math.h $ $Rev: 535130 $" )
