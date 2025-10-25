/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Mobility Components.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QMOBILITYGLOBAL_H
#define QMOBILITYGLOBAL_H

#define QTM_VERSION_STR   "1.2.2"
/*
   QTM_VERSION is (major << 16) + (minor << 8) + patch.
*/
#define QTM_VERSION 0x010202
/*
   can be used like #if (QTM_VERSION >= QTM_VERSION_CHECK(1, 2, 0))
*/
#define QTM_VERSION_CHECK(major, minor, patch) ((major<<16)|(minor<<8)|(patch))

#define QTM_PACKAGEDATE_STR "YYYY-MM-DD"

#define QTM_PACKAGE_TAG ""

#include <QtCore/qglobal.h>
#if defined(QTM_BUILD_UNITTESTS) && (defined(Q_OS_WIN) || defined(Q_OS_SYMBIAN)) && defined(QT_MAKEDLL)
#    define QM_AUTOTEST_EXPORT Q_DECL_EXPORT
#elif defined(QTM_BUILD_UNITTESTS) && (defined(Q_OS_WIN) || defined(Q_OS_SYMBIAN)) && defined(QT_DLL)
#    define QM_AUTOTEST_EXPORT Q_DECL_IMPORT
#elif defined(QTM_BUILD_UNITTESTS) && !(defined(Q_OS_WIN) || defined(Q_OS_SYMBIAN)) && defined(QT_SHARED)
#    define QM_AUTOTEST_EXPORT Q_DECL_EXPORT
#else
#    define QM_AUTOTEST_EXPORT
#endif


#if defined(Q_OS_WIN) || defined(Q_OS_SYMBIAN)
#  if defined(QT_NODLL)
#    undef QT_MAKEDLL
#    undef QT_DLL
#  elif defined(QT_MAKEDLL)
#    if defined(QT_DLL)
#      undef QT_DLL
#    endif
#    if defined(QT_BUILD_BEARER_LIB)
#      define Q_BEARER_EXPORT Q_DECL_EXPORT
#    else
#      define Q_BEARER_EXPORT Q_DECL_IMPORT
#    endif
#    if defined(QT_BUILD_CFW_LIB)
#      define Q_PUBLISHSUBSCRIBE_EXPORT Q_DECL_EXPORT
#    else
#      define Q_PUBLISHSUBSCRIBE_EXPORT Q_DECL_IMPORT
#    endif
#    if defined(QT_BUILD_CONTACTS_LIB)
#      define Q_CONTACTS_EXPORT Q_DECL_EXPORT
#    else
#      define Q_CONTACTS_EXPORT Q_DECL_IMPORT
#    endif
#    if defined(QT_BUILD_VERSIT_LIB)
#      define Q_VERSIT_EXPORT Q_DECL_EXPORT
#    else
#      define Q_VERSIT_EXPORT Q_DECL_IMPORT
#    endif
#    if defined(QT_BUILD_VERSIT_ORGANIZER_LIB)
#      define Q_VERSIT_ORGANIZER_EXPORT Q_DECL_EXPORT
#    else
#      define Q_VERSIT_ORGANIZER_EXPORT Q_DECL_IMPORT
#    endif
#    if defined(QT_BUILD_LOCATION_LIB)
#      define Q_LOCATION_EXPORT Q_DECL_EXPORT
#    else
#      define Q_LOCATION_EXPORT Q_DECL_IMPORT
#    endif
#    if defined(QT_BUILD_MESSAGING_LIB)
#      define Q_MESSAGING_EXPORT Q_DECL_EXPORT
#    else
#      define Q_MESSAGING_EXPORT Q_DECL_IMPORT
#    endif
#    if defined(QT_BUILD_MULTIMEDIA_LIB)
#        define Q_MULTIMEDIA_EXPORT Q_DECL_EXPORT
#    else
#        define Q_MULTIMEDIA_EXPORT Q_DECL_IMPORT
#    endif
#    if defined(QT_BUILD_SFW_LIB)
#      define Q_SERVICEFW_EXPORT Q_DECL_EXPORT
#    else
#      define Q_SERVICEFW_EXPORT Q_DECL_IMPORT
#    endif
#    if defined(QT_BUILD_SYSINFO_LIB)
#      define Q_SYSINFO_EXPORT Q_DECL_EXPORT
#    else
#      define Q_SYSINFO_EXPORT Q_DECL_IMPORT
#    endif
#    if defined(QT_BUILD_SENSORS_LIB)
#      define Q_SENSORS_EXPORT Q_DECL_EXPORT
#    else
#      define Q_SENSORS_EXPORT Q_DECL_IMPORT
#    endif
#    if defined(QT_BUILD_FEEDBACK_LIB)
#      define Q_FEEDBACK_EXPORT Q_DECL_EXPORT
#    else
#      define Q_FEEDBACK_EXPORT Q_DECL_IMPORT
#    endif
#    if defined(QT_BUILD_GALLERY_LIB)
#      define Q_GALLERY_EXPORT Q_DECL_EXPORT
#    else
#      define Q_GALLERY_EXPORT Q_DECL_IMPORT
#    endif
#    if defined(QT_BUILD_ORGANIZER_LIB)
#      define Q_ORGANIZER_EXPORT Q_DECL_EXPORT
#    else
#      define Q_ORGANIZER_EXPORT Q_DECL_IMPORT
#    endif
#    if defined(QT_BUILD_CONNECTIVITY_LIB)
#      define Q_CONNECTIVITY_EXPORT Q_DECL_EXPORT
#    else
#      define Q_CONNECTIVITY_EXPORT Q_DECL_IMPORT
#    endif
#  elif defined(QT_DLL) /* use a Qt DLL library */
#    define Q_BEARER_EXPORT Q_DECL_IMPORT
#    define Q_PUBLISHSUBSCRIBE_EXPORT Q_DECL_IMPORT
#    define Q_CONTACTS_EXPORT Q_DECL_IMPORT
#    define Q_VERSIT_EXPORT Q_DECL_IMPORT
#    define Q_VERSIT_ORGANIZER_EXPORT Q_DECL_IMPORT
#    define Q_LOCATION_EXPORT Q_DECL_IMPORT
#    define Q_MULTIMEDIA_EXPORT Q_DECL_IMPORT
#    define Q_MESSAGING_EXPORT Q_DECL_IMPORT
#    if QTM_SERVICEFW_SYMBIAN_DATABASEMANAGER_SERVER
#      define Q_SERVICEFW_EXPORT
#    else
#      define Q_SERVICEFW_EXPORT Q_DECL_IMPORT
#    endif
#    define Q_SYSINFO_EXPORT Q_DECL_IMPORT
#    define Q_SENSORS_EXPORT Q_DECL_IMPORT
#    define Q_FEEDBACK_EXPORT Q_DECL_IMPORT
#    define Q_GALLERY_EXPORT Q_DECL_IMPORT
#    define Q_ORGANIZER_EXPORT Q_DECL_IMPORT
#    define Q_CONNECTIVITY_EXPORT Q_DECL_IMPORT
#  endif
#endif

#if !defined(Q_SERVICEFW_EXPORT)
#  if defined(QT_SHARED)
#    define Q_BEARER_EXPORT Q_DECL_EXPORT
#    define Q_PUBLISHSUBSCRIBE_EXPORT Q_DECL_EXPORT
#    define Q_CONTACTS_EXPORT Q_DECL_EXPORT
#    define Q_VERSIT_EXPORT Q_DECL_EXPORT
#    define Q_VERSIT_ORGANIZER_EXPORT Q_DECL_EXPORT
#    define Q_LOCATION_EXPORT Q_DECL_EXPORT
#    define Q_MULTIMEDIA_EXPORT Q_DECL_EXPORT
#    define Q_MESSAGING_EXPORT Q_DECL_EXPORT
#    define Q_SERVICEFW_EXPORT Q_DECL_EXPORT
#    define Q_SYSINFO_EXPORT Q_DECL_EXPORT
#    define Q_SENSORS_EXPORT Q_DECL_EXPORT
#    define Q_FEEDBACK_EXPORT Q_DECL_EXPORT
#    define Q_GALLERY_EXPORT Q_DECL_EXPORT
#    define Q_ORGANIZER_EXPORT Q_DECL_EXPORT
#    define Q_CONNECTIVITY_EXPORT Q_DECL_EXPORT
#  else
#    define Q_BEARER_EXPORT
#    define Q_PUBLISHSUBSCRIBE_EXPORT
#    define Q_CONTACTS_EXPORT
#    define Q_VERSIT_EXPORT
#    define Q_VERSIT_ORGANIZER_EXPORT
#    define Q_LOCATION_EXPORT
#    define Q_MULTIMEDIA_EXPORT
#    define Q_MESSAGING_EXPORT
#    define Q_SERVICEFW_EXPORT
#    define Q_SYSINFO_EXPORT
#    define Q_SENSORS_EXPORT
#    define Q_FEEDBACK_EXPORT
#    define Q_GALLERY_EXPORT
#    define Q_ORGANIZER_EXPORT
#    define Q_CONNECTIVITY_EXPORT
#  endif
#endif


#ifdef QTM_SERVICEFW_SYMBIAN_DATABASEMANAGER_SERVER
#  ifdef Q_SERVICEFW_EXPORT
#    undef Q_SERVICEFW_EXPORT
#  endif
#  define Q_SERVICEFW_EXPORT
#  ifdef QM_AUTOTEST_EXPORT
#    undef QM_AUTOTEST_EXPORT
#  endif
#  define QM_AUTOTEST_EXPORT
#endif

// The namespace is hardcoded as moc has issues resolving
// macros which would be a prerequisite for a dynmamic namespace
#define QTM_NAMESPACE QtMobility

#ifdef QTM_NAMESPACE
# define QTM_PREPEND_NAMESPACE(name) ::QTM_NAMESPACE::name
# define QTM_BEGIN_NAMESPACE namespace QTM_NAMESPACE {
# define QTM_END_NAMESPACE }
# define QTM_USE_NAMESPACE using namespace QTM_NAMESPACE;
#else
# define QTM_PREPEND_NAMESPACE(name) ::name
# define QTM_BEGIN_NAMESPACE
# define QTM_END_NAMESPACE
# define QTM_USE_NAMESPACE
#endif

//in case Qt is in namespace
QT_USE_NAMESPACE

#endif // QMOBILITYGLOBAL_H

