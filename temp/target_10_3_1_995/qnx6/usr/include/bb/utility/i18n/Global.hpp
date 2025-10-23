/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2014
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_UTILITY_I18N_GLOBAL_HPP
#define BB_UTILITY_I18N_GLOBAL_HPP

#include <QtGlobal>

// Library specific export macro - do not share across libraries
#if defined(BB_STATIC_UTILITY_I18N_LIB)
#   define BB_UTILITY_I18N_EXPORT
#else
#   if defined(BB_BUILD_UTILITY_I18N_LIB)
#       define BB_UTILITY_I18N_EXPORT Q_DECL_EXPORT
#   else
#       define BB_UTILITY_I18N_EXPORT Q_DECL_IMPORT
#   endif
#endif

#endif // _HPP
