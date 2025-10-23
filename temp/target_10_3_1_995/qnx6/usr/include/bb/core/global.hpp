/*!
 * @copyright
 * Copyright Research In Motion Limited, 2011-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CORE_GLOBAL_HPP
#define BB_CORE_GLOBAL_HPP

#include <QtGlobal>

// Library specific export macro - do not share across libraries
#if defined(BB_STATIC_CORE_LIB)
#   define BB_CORE_EXPORT
#else
#   if defined(BB_BUILD_CORE_LIB)
#       define BB_CORE_EXPORT   Q_DECL_EXPORT
#   else
#       define BB_CORE_EXPORT   Q_DECL_IMPORT
#   endif
#endif

// Deprecation warning macro - only supported by GCC
#if defined(__GNUC__)
#   define BB_DEPRECATED    __attribute__ ((deprecated))
#else
#   define BB_DEPRECATED
#endif

// Obsolete macros, soon to be removed
#if defined(__GNUC__)
#   define BB_DLL_PUBLIC  __attribute__ ((visibility ("default")))
#else
#   define BB_DLL_PUBLIC
#endif

#define DLL_PUBLIC          BB_DLL_PUBLIC

#endif // BB_CORE_GLOBAL_HPP
