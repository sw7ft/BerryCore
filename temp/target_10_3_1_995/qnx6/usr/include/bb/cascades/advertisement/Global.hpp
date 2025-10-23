/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CASCADES_ADVERTISEMENT_GLOBAL_HPP
#define BB_CASCADES_ADVERTISEMENT_GLOBAL_HPP

#include <QtGlobal>

// Library specific export macro - do not share across libraries
#if defined(BB_STATIC_CASCADES_ADVERTISEMENT_LIB)
#   define BB_CASCADES_ADVERTISEMENT_EXPORT
#else
#   if defined(BB_BUILD_CASCADES_ADVERTISEMENT_LIB)
#       define BB_CASCADES_ADVERTISEMENT_EXPORT Q_DECL_EXPORT
#   else
#       define BB_CASCADES_ADVERTISEMENT_EXPORT Q_DECL_IMPORT
#   endif
#endif

#endif // BB_CASCADES_ADVERTISEMENT_GLOBAL_HPP
