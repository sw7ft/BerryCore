/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2012
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_LOCATION_GLOBAL_HPP
#define BB_LOCATION_GLOBAL_HPP

#include <QtGlobal>

// Library specific export macro - do not share across libraries
#if defined(BB_STATIC_LOCATION_LIB)
#   define BB_LOCATION_EXPORT
#else
#   if defined(BB_BUILD_LOCATION_LIB)
#       define BB_LOCATION_EXPORT Q_DECL_EXPORT
#   else
#       define BB_LOCATION_EXPORT Q_DECL_IMPORT
#   endif
#endif

#endif // BB_LOCATION_GLOBAL_HPP
