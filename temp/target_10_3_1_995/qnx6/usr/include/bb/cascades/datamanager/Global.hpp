/*!
 * @copyright
 * Copyright (C) 2013 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_CASCADES_DATAMANAGER_GLOBAL_HPP
#define BB_CASCADES_DATAMANAGER_GLOBAL_HPP

#include <QtGlobal>

// Library specific export macro - do not share across libraries
#if defined(BB_STATIC_CASCADES_DATAMANAGER_LIB)
#   define BB_CASCADES_DATAMANAGER_EXPORT
#else
#   if defined(BB_BUILD_CASCADES_DATAMANAGER_LIB)
#       define BB_CASCADES_DATAMANAGER_EXPORT Q_DECL_EXPORT
#   else
#       define BB_CASCADES_DATAMANAGER_EXPORT Q_DECL_IMPORT
#   endif
#endif

#endif // BB_CASCADES_DATAMANAGER_GLOBAL_HPP
