/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_GLOBAL_HPP
#define BB_SYSTEM_GLOBAL_HPP

#include <QtGlobal>

// Library specific export macro - do not share across libraries
#if defined(BB_STATIC_SYSTEM_LIB)
#   define BB_SYSTEM_EXPORT
#else
#   if defined(BB_BUILD_SYSTEM_LIB)
#       define BB_SYSTEM_EXPORT Q_DECL_EXPORT
#   else
#       define BB_SYSTEM_EXPORT Q_DECL_IMPORT
#   endif
#endif

// Deprecation warning macro - only supported by GCC
#if defined(__GNUC__)
#   define BB_DEPRECATED    __attribute__ ((deprecated))
#else
#   define BB_DEPRECATED
#endif

#endif // BB_SYSTEM_GLOBAL_HPP
