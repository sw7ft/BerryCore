/* xtgmath.h internal header */
#ifndef _XTGMATH
#define _XTGMATH
 #ifndef _YVALS
  #include <yvals.h>
 #endif /* _YVALS */

 #if _HAS_C9X

 #if defined(__SUNPRO_CC)	/* compiler test */
  #define _HAS_GENERIC_TEMPLATES	0	/* disable conflicting overloads */
 #endif /* defined(__SUNPRO_CC) */

 #if !defined (_HAS_GENERIC_TEMPLATES) && \
	defined(__cplusplus) && !__embedded_cplusplus	/* DON'T SIMPLIFY! */
  #define _HAS_GENERIC_TEMPLATES	1

 #else /* defined(__cplusplus) && !__embedded_cplusplus */
  #define _HAS_GENERIC_TEMPLATES	0
 #endif /* defined(__cplusplus) && !__embedded_cplusplus */

 #if _HAS_GENERIC_TEMPLATES
_C_STD_BEGIN
		// MACROS (ONE ARGUMENT)
 #define _TGEN_COMTYP(Carg)	typename _Combined_type<Carg, \
	typename _Real_type<_T1>::_Type>::_Type

 #define _TGEN1(fn, Carg, Ret) template<class _T1> inline \
	Ret fn(_T1 _Left) \
	{	/* overload fn(x) returning Ret, real/complex is Carg */ \
	typedef typename _Combined_type<Carg, \
		typename _Real_type<_T1>::_Type>::_Type \
		_Tw; \
	return (fn(_Rc_convert(_Left, (_Tw *)0, \
		(typename _Rc_type<_T1>::_Type *)0, (Carg *)0))); \
	}

 #define _TGEN_C(fn)	_TGEN1(fn, char, \
	_TGEN_COMTYP(char))

 #define _TGEN_C0(fn)	_TGEN1(fn, char, \
	typename _Real_type<_T1>::_Type)

 #define _TGEN_R(fn)	_TGEN1(fn, float, \
	typename _Real_type<_T1>::_Type)

 #define _TGEN_RI(fn, Ret)	_TGEN1(fn, float, Ret)

 #define _TGEN_RC(fn)	_TGEN1(fn, typename _Rc_type<_T1>::_Type, \
	_TGEN_COMTYP(typename _Rc_type<_T1>::_Type))

 #define _TGEN_RC0(fn)	_TGEN1(fn, typename _Rc_type<_T1>::_Type, \
	typename _Real_type<_T1>::_Type)

 #define _TGEN_RX(fn, Xarg) template<class _T1> inline \
	typename _Real_type<_T1>::_Type \
		fn(_T1 _Left, Xarg _Xtra) \
	{	/* overload fn(x, z) returning real, with Xarg z */ \
	typedef typename _Real_type<_T1>::_Type \
		_Tw; \
	return (fn((_Tw)_Left, _Xtra)); \
	}

		// MACROS (TWO ARGUMENTS)
 #define _TGEN2(fn, Carg1, Carg2) template<class _T1, class _T2> inline \
	typename _Combined_type< \
		typename _Rc_widened<Carg1, Carg2>::_Type, \
		typename _Real_widened<typename _Real_type<_T1>::_Type, \
			typename _Real_type<_T2>::_Type>::_Type>::_Type \
		fn(_T1 _Left, _T2 _Right) \
	{	/* overload fn(x, y) returning Ret, real/complex is Carg1/Carg2 */ \
	typedef typename _Rc_widened<Carg1, Carg2>::_Type Carg; \
	typedef typename _Combined_type<Carg, \
		typename _Real_widened<typename _Real_type<_T1>::_Type, \
			typename _Real_type<_T2>::_Type>::_Type>::_Type \
		_Tw; \
	return (fn(_Rc_convert(_Left, (_Tw *)0, (Carg1 *)0, (Carg *)0), \
		_Rc_convert(_Right, (_Tw *)0, (Carg2 *)0, (Carg *)0))); \
	}

 #define _TGEN_RC2(fn)	_TGEN2(fn, typename _Rc_type<_T1>::_Type, \
	typename _Rc_type<_T2>::_Type)

 #define _TGEN_R2(fn)	_TGEN2(fn, float, float)

 #define _TGEN_R2X(fn, Xarg) template<class _T1, class _T2> inline \
	typename _Real_widened<typename _Real_type<_T1>::_Type, \
		typename _Real_type<_T2>::_Type>::_Type \
		fn(_T1 _Left, _T2 _Right, Xarg _Xtra) \
	{	/* overload fn(x, y, z) returning real, with Xarg z */ \
	typedef typename _Real_widened<typename _Real_type<_T1>::_Type, \
			typename _Real_type<_T2>::_Type>::_Type \
		_Tw; \
	return (fn((_Tw)_Left, (_Tw)_Right, _Xtra)); \
	}

		// MACROS (THREE ARGUMENTS)
 #define _TGEN_R3(fn) template<class _T1, class _T2, class _T3> inline \
	typename _Real_widened< \
		typename _Real_widened< \
			typename _Real_type<_T1>::_Type, \
			typename _Real_type<_T2>::_Type>::_Type, \
		typename _Real_type<_T3>::_Type>::_Type \
		fn(_T1 _Left, _T2 _Right, _T3 _Xtra) \
	{	/* overload fn(x, y, z) returning real */ \
	typedef typename _Real_widened< \
		typename _Real_widened< \
			typename _Real_type<_T1>::_Type, \
			typename _Real_type<_T2>::_Type>::_Type, \
		typename _Real_type<_T3>::_Type>::_Type \
		_Tw; \
	return (fn((_Tw)_Left, (_Tw)_Right, (_Tw)_Xtra)); \
	}

		// TEMPLATE FUNCTION _Rc_convert
template<class _From,
	class _To,
	class _From_rc,
	class _To_rc>
	_To _Rc_convert(_From _Val, _To *, _From_rc *, _To_rc *)
	{	// convert _Val to desired type
	return ((_To)_Val);
	}

 #if __GNUC__ == 0
template<class _From,
	class _To>
	_To _Rc_convert(_From _Val, _To *, char *, char *)
	{	// convert _Val to desired type, complex = complex
	_To _Ans;

	_Ans._Val[0] = _Val._Val[0];
	_Ans._Val[1] = _Val._Val[1];
	return (_Ans);
	}

template<class _From,
	class _To>
	_To _Rc_convert(_From _Val, _To *, float *, char *)
	{	// convert _Val to desired type, complex = real
	_To _Ans;

	_Ans._Val[0] = _Val;
	_Ans._Val[1] = 0;
	return (_Ans);
	}
 #endif /* __GNUC__ == 0 */

		// TEMPLATE CLASS _Rc_type
template<class _Ty>
	struct _Rc_type
	{	// determine if type is real or complex
	typedef float _Type;	// default is real
	};

		// TEMPLATE CLASS _Rc_widened
template<class _Ty, class _T2>
	struct _Rc_widened
	{	// determine real/complex type
	typedef char _Type;	// non (real, real) is char (complex)
	};

template<> struct _Rc_widened<float, float>
	{	// determine real/complex
	typedef float _Type;	// (real, real) is real
	};

		// TEMPLATE CLASS _Real_type

 #if defined(__SUNPRO_CC)	/* compiler test */
template<class _Ty>
	struct _Real_type;

template<> struct _Real_type<int>
	{	// determine equivalent real type
	typedef double _Type;
	};

template<> struct _Real_type<unsigned int>
	{	// determine equivalent real type
	typedef double _Type;
	};

template<> struct _Real_type<long>
	{	// determine equivalent real type
	typedef double _Type;
	};

template<> struct _Real_type<unsigned long>
	{	// determine equivalent real type
	typedef double _Type;
	};

template<> struct _Real_type<double>
	{	// determine equivalent real type
	typedef double _Type;
	};

 #else /* defined(__SUNPRO_CC) */
template<class _Ty>
	struct _Real_type
	{	// determine equivalent real type
	typedef double _Type;	// default is double
	};
 #endif /* defined(__SUNPRO_CC) */

template<> struct _Real_type<float>
	{	// determine equivalent real type
	typedef float _Type;
	};

template<> struct _Real_type<long double>
	{	// determine equivalent real type
	typedef long double _Type;
	};

		// TEMPLATE CLASS _Real_widened
template<class _Ty, class _T2>
	struct _Real_widened
	{	// determine widened real type
	typedef long double _Type;	// default is long double
	};

template<> struct _Real_widened<float, float>
	{	// determine widened real type
	typedef float _Type;
	};

template<> struct _Real_widened<float, double>
	{	// determine widened real type
	typedef double _Type;
	};

template<> struct _Real_widened<double, float>
	{	// determine widened real type
	typedef double _Type;
	};

template<> struct _Real_widened<double, double>
	{	// determine widened real type
	typedef double _Type;
	};

		// TEMPLATE CLASS _Combined_type
template<class _Trc, class _Tre>
	struct _Combined_type
	{	// determine combined type
	typedef float _Type;	// (real, float) is float
	};

template<> struct _Combined_type<float, double>
	{	// determine combined type
	typedef double _Type;
	};

template<> struct _Combined_type<float, long double>
	{	// determine combined type
	typedef long double _Type;
	};
_C_STD_END

  #if defined(_STD_USING)
using _CSTD _Rc_type; using _CSTD _Rc_widened;
using _CSTD _Real_type; using _CSTD _Real_widened;
using _CSTD _Combined_type;
  #endif /* defined(_STD_USING) */

 #endif /* _HAS_GENERIC_TEMPLATES */
 #endif /* _IS_C9X */

#endif /* _XTGMATH */

/*
 * Copyright (c) 1992-2006 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V5.00:1296 */

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/m/public/xtgmath.h $ $Rev: 219996 $" )
