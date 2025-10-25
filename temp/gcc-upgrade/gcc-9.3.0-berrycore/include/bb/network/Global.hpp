/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_NETWORK_GLOBAL_HPP
#define BB_NETWORK_GLOBAL_HPP

#include <QtGlobal>

#if defined(BB_STATIC_NETWORK_LIB)
#   define BB_NETWORK_EXPORT
#else
#   if defined(BB_BUILD_NETWORK_LIB)
#       define BB_NETWORK_EXPORT    Q_DECL_EXPORT
#   else
#       define BB_NETWORK_EXPORT    Q_DECL_IMPORT
#   endif
#endif


#endif /* BB_NETWORK_GLOBAL_HPP */
