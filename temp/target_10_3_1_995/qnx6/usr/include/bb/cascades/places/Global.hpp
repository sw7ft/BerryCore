/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CASCADES_PLACES_GLOBAL_HPP
#define BB_CASCADES_PLACES_GLOBAL_HPP

/*!
 * @file bb/cascades/places/Global.hpp
 *
 * @since BlackBerry 10.0.0
 */

#include <qglobal.h>

/*!
 * @brief Library specific export macro - do not share across libraries
 */
#if defined(BB_STATIC_BB_CASCADES_PLACES_LIB)
#   define BB_STATIC_BB_CASCADES_PLACES_LIB
#else
#   if defined(BB_BUILD_BB_CASCADES_PLACES_LIB)
#       define BB_CASCADES_PLACES_EXPORT    Q_DECL_EXPORT
#   else
#       define BB_CASCADES_PLACES_EXPORT    Q_DECL_IMPORT
#   endif
#endif

#endif //BB_CASCADES_PLACES_GLOBAL_HPP
