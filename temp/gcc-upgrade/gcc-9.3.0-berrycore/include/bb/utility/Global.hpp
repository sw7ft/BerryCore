/*!
 * @copyright
 * Copyright Research In Motion Limited, 2011-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_UTILITY_GLOBAL_HPP
#define BB_UTILITY_GLOBAL_HPP

#include <QtGlobal>

// Library specific export macro - do not share across libraries
#if defined(BB_STATIC_UTILITY_LIB)
#   define BB_UTILITY_EXPORT
#else
#   if defined(BB_BUILD_UTILITY_LIB)
#       define BB_UTILITY_EXPORT   Q_DECL_EXPORT
#   else
#       define BB_UTILITY_EXPORT   Q_DECL_IMPORT
#   endif
#endif

#endif // BB_UTILITY_GLOBAL_HPP
