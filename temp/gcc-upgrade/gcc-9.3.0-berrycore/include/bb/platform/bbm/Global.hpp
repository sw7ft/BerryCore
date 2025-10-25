/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2012
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_BBM_GLOBAL_HPP
#define BB_PLATFORM_BBM_GLOBAL_HPP

#include <QtGlobal>

#if defined(BB_STATIC_PLATFORM_BBM_LIB)
#   define BB_PLATFORM_BBM_EXPORT
#else
#   if defined(BB_BUILD_PLATFORM_BBM_LIB)
#       define BB_PLATFORM_BBM_EXPORT    Q_DECL_EXPORT
#   else
#       define BB_PLATFORM_BBM_EXPORT    Q_DECL_IMPORT
#   endif
#endif

// Deprecation warning macro - only supported by GCC.
#if defined(__GNUC__)
#   define BB_PLATFORM_BBM_DEPRECATED    __attribute__ ((deprecated))
#else
#   define BB_PLATFORM_BBM_DEPRECATED
#endif

#endif // BB_PLATFORM_BBM_GLOBAL_HPP
