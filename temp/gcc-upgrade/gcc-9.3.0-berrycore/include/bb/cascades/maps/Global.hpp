/**
 * @copyright
 * Copyright BlackBerry Limited, 2012-2014
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_CASCADES_MAPS_GLOBAL_HPP
#define BB_CASCADES_MAPS_GLOBAL_HPP

#include <QtGlobal>

#if defined(BB_STATIC_CASCADES_MAPS_LIB)
#   define BB_CASCADES_MAPS_EXPORT
#else
#   if defined(BB_BUILD_CASCADES_MAPS_LIB)
#      define BB_CASCADES_MAPS_EXPORT Q_DECL_EXPORT
#   else
#      define BB_CASCADES_MAPS_EXPORT Q_DECL_IMPORT
#   endif
#endif

#endif /* BB_CASCADES_MAPS_GLOBAL_HPP */
