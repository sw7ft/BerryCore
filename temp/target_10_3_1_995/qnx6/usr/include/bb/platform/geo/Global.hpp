/**
 * @copyright
 * Copyright BlackBerry Limited, 2012-2014
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_PLATFORM_GEO_GLOBAL_HPP
#define BB_PLATFORM_GEO_GLOBAL_HPP

#include <QtGlobal>

#if defined(BB_STATIC_PLATFORM_GEO_LIB)
#   define BB_PLATFORM_GEO_EXPORT
#else
#   if defined(BB_BUILD_PLATFORM_GEO_LIB)
#      define BB_PLATFORM_GEO_EXPORT Q_DECL_EXPORT
#   else
#      define BB_PLATFORM_GEO_EXPORT Q_DECL_IMPORT
#   endif
#endif

#endif /* BB_PLATFORM_GEO_GLOBAL_HPP */
