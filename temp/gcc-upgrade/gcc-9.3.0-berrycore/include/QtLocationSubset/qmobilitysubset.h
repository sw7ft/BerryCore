/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Mobility Components.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QMOBILITYSUBSET_H
#define QMOBILITYSUBSET_H

#define QTMS_VERSION_STR "1.2.0"
/*
   QTMS_VERSION is (major << 16) + (minor << 8) + patch.
*/
#define QTMS_VERSION 0x010200
/*
   can be used like #if (QTMS_VERSION >= QTMS_VERSION_CHECK(1, 2, 0))
*/
#define QTMS_VERSION_CHECK(major, minor, patch) ((major<<16)|(minor<<8)|(patch))

#define QTMS_PACKAGEDATE_STR "2011-05-10"

#define QTMS_PACKAGE_TAG "fb3e9bc2d941462f1244aaf0ea79425a307f883d"

#include <QtCore/qglobal.h>
#if defined(QTMS_BUILD_UNITTESTS) && (defined(Q_OS_WIN) || defined(Q_OS_SYMBIAN)) && defined(QT_MAKEDLL)
#    define QM_AUTOTEST_EXPORT Q_DECL_EXPORT
#elif defined(QTMS_BUILD_UNITTESTS) && (defined(Q_OS_WIN) || defined(Q_OS_SYMBIAN)) && defined(QT_DLL)
#    define QM_AUTOTEST_EXPORT Q_DECL_IMPORT
#elif defined(QTMS_BUILD_UNITTESTS) && !(defined(Q_OS_WIN) || defined(Q_OS_SYMBIAN)) && defined(QT_SHARED)
#    define QM_AUTOTEST_EXPORT Q_DECL_EXPORT
#else
#    define QM_AUTOTEST_EXPORT
#endif

// For QtMobilitySubset only QT_BUILD_LOCATION_LIB is expected to be defined. However some of the #ifdef logic
// below depends on Q_SERVICEFW_EXPORT being defined. Here, test to see if it is already defined. If not it
// will be undef'd at the end of this file.
#if !defined(Q_SERVICEFW_EXPORT)
#  define QTMS_UNDEFINE_Q_SERVICEFW_EXPORT
#endif

#if defined(Q_OS_WIN) || defined(Q_OS_SYMBIAN)
#  if defined(QT_NODLL)
#    undef QT_MAKEDLL
#    undef QT_DLL
#  elif defined(QT_MAKEDLL)
#    if defined(QT_DLL)
#      undef QT_DLL
#    endif
//#    if defined(QT_BUILD_BEARER_LIB)
//#      define Q_BEARER_EXPORT Q_DECL_EXPORT
//#    else
//#      define Q_BEARER_EXPORT Q_DECL_IMPORT
//#    endif
//#    if defined(QT_BUILD_CFW_LIB)
//#      define Q_PUBLISHSUBSCRIBE_EXPORT Q_DECL_EXPORT
//#    else
//#      define Q_PUBLISHSUBSCRIBE_EXPORT Q_DECL_IMPORT
//#    endif
//#    if defined(QT_BUILD_CONTACTS_LIB)
//#      define Q_CONTACTS_EXPORT Q_DECL_EXPORT
//#    else
//#      define Q_CONTACTS_EXPORT Q_DECL_IMPORT
//#    endif
//#    if defined(QT_BUILD_VERSIT_LIB)
//#      define Q_VERSIT_EXPORT Q_DECL_EXPORT
//#    else
//#      define Q_VERSIT_EXPORT Q_DECL_IMPORT
//#    endif
//#    if defined(QT_BUILD_VERSIT_ORGANIZER_LIB)
//#      define Q_VERSIT_ORGANIZER_EXPORT Q_DECL_EXPORT
//#    else
//#      define Q_VERSIT_ORGANIZER_EXPORT Q_DECL_IMPORT
//#    endif
#    if defined(QT_BUILD_LOCATION_LIB)
#      define Q_LOCATION_EXPORT Q_DECL_EXPORT
#    else
#      define Q_LOCATION_EXPORT Q_DECL_IMPORT
#    endif
//#    if defined(QT_BUILD_MESSAGING_LIB)
//#      define Q_MESSAGING_EXPORT Q_DECL_EXPORT
//#    else
//#      define Q_MESSAGING_EXPORT Q_DECL_IMPORT
//#    endif
//#    if defined(QT_BUILD_MULTIMEDIA_LIB)
//#        define Q_MULTIMEDIA_EXPORT Q_DECL_EXPORT
//#    else
//#        define Q_MULTIMEDIA_EXPORT Q_DECL_IMPORT
//#    endif
// if Q_SERVICEFW_EXPORT is already defined let it pass through
#    if !defined(Q_SERVICEFW_EXPORT)
#      if defined(QT_BUILD_SFW_LIB)
#        define Q_SERVICEFW_EXPORT Q_DECL_EXPORT
#      else
#        define Q_SERVICEFW_EXPORT Q_DECL_IMPORT
#      endif
#    endif
//#    if defined(QT_BUILD_SYSINFO_LIB)
//#      define Q_SYSINFO_EXPORT Q_DECL_EXPORT
//#    else
//#      define Q_SYSINFO_EXPORT Q_DECL_IMPORT
//#    endif
//#    if defined(QT_BUILD_SENSORS_LIB)
//#      define Q_SENSORS_EXPORT Q_DECL_EXPORT
//#    else
//#      define Q_SENSORS_EXPORT Q_DECL_IMPORT
//#    endif
//#    if defined(QT_BUILD_FEEDBACK_LIB)
//#      define Q_FEEDBACK_EXPORT Q_DECL_EXPORT
//#    else
//#      define Q_FEEDBACK_EXPORT Q_DECL_IMPORT
//#    endif
//#    if defined(QT_BUILD_GALLERY_LIB)
//#      define Q_GALLERY_EXPORT Q_DECL_EXPORT
//#    else
//#      define Q_GALLERY_EXPORT Q_DECL_IMPORT
//#    endif
//#    if defined(QT_BUILD_ORGANIZER_LIB)
//#      define Q_ORGANIZER_EXPORT Q_DECL_EXPORT
//#    else
//#      define Q_ORGANIZER_EXPORT Q_DECL_IMPORT
//#    endif
//#    if defined(QT_BUILD_CONNECTIVITY_LIB)
//#      define Q_CONNECTIVITY_EXPORT Q_DECL_EXPORT
//#    else
//#      define Q_CONNECTIVITY_EXPORT Q_DECL_IMPORT
//#    endif
#  elif defined(QT_DLL) /* use a Qt DLL library */
//#    define Q_BEARER_EXPORT Q_DECL_IMPORT
//#    define Q_PUBLISHSUBSCRIBE_EXPORT Q_DECL_IMPORT
//#    define Q_CONTACTS_EXPORT Q_DECL_IMPORT
//#    define Q_VERSIT_EXPORT Q_DECL_IMPORT
//#    define Q_VERSIT_ORGANIZER_EXPORT Q_DECL_IMPORT
#    define Q_LOCATION_EXPORT Q_DECL_IMPORT
//#    define Q_MULTIMEDIA_EXPORT Q_DECL_IMPORT
//#    define Q_MESSAGING_EXPORT Q_DECL_IMPORT
// if Q_SERVICEFW_EXPORT is already defined let it pass through
#    if !defined(Q_SERVICEFW_EXPORT)
#      if QTMS_SERVICEFW_SYMBIAN_DATABASEMANAGER_SERVER
#        define Q_SERVICEFW_EXPORT
#      else
#        define Q_SERVICEFW_EXPORT Q_DECL_IMPORT
#      endif
#    endif
//#    define Q_SYSINFO_EXPORT Q_DECL_IMPORT
//#    define Q_SENSORS_EXPORT Q_DECL_IMPORT
//#    define Q_FEEDBACK_EXPORT Q_DECL_IMPORT
//#    define Q_GALLERY_EXPORT Q_DECL_IMPORT
//#    define Q_ORGANIZER_EXPORT Q_DECL_IMPORT
//#    define Q_CONNECTIVITY_EXPORT Q_DECL_IMPORT
#  endif
#endif

#if !defined(Q_SERVICEFW_EXPORT)
#  if defined(QT_SHARED)
//#    define Q_BEARER_EXPORT Q_DECL_EXPORT
//#    define Q_PUBLISHSUBSCRIBE_EXPORT Q_DECL_EXPORT
//#    define Q_CONTACTS_EXPORT Q_DECL_EXPORT
//#    define Q_VERSIT_EXPORT Q_DECL_EXPORT
//#    define Q_VERSIT_ORGANIZER_EXPORT Q_DECL_EXPORT
#    define Q_LOCATION_EXPORT Q_DECL_EXPORT
//#    define Q_MULTIMEDIA_EXPORT Q_DECL_EXPORT
//#    define Q_MESSAGING_EXPORT Q_DECL_EXPORT
#    define Q_SERVICEFW_EXPORT Q_DECL_EXPORT
//#    define Q_SYSINFO_EXPORT Q_DECL_EXPORT
//#    define Q_SENSORS_EXPORT Q_DECL_EXPORT
//#    define Q_FEEDBACK_EXPORT Q_DECL_EXPORT
//#    define Q_GALLERY_EXPORT Q_DECL_EXPORT
//#    define Q_ORGANIZER_EXPORT Q_DECL_EXPORT
//#    define Q_CONNECTIVITY_EXPORT Q_DECL_EXPORT
#  else
//#    define Q_BEARER_EXPORT
//#    define Q_PUBLISHSUBSCRIBE_EXPORT
//#    define Q_CONTACTS_EXPORT
//#    define Q_VERSIT_EXPORT
//#    define Q_VERSIT_ORGANIZER_EXPORT
#    define Q_LOCATION_EXPORT
//#    define Q_MULTIMEDIA_EXPORT
//#    define Q_MESSAGING_EXPORT
#    define Q_SERVICEFW_EXPORT
//#    define Q_SYSINFO_EXPORT
//#    define Q_SENSORS_EXPORT
//#    define Q_FEEDBACK_EXPORT
//#    define Q_GALLERY_EXPORT
//#    define Q_ORGANIZER_EXPORT
//#    define Q_CONNECTIVITY_EXPORT
#  endif
#endif


#ifdef QTMS_SERVICEFW_SYMBIAN_DATABASEMANAGER_SERVER
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
#define QTMS_NAMESPACE QtMobilitySubset

#ifdef QTMS_NAMESPACE
# define QTMS_PREPEND_NAMESPACE(name) ::QTMS_NAMESPACE::name
# define QTMS_BEGIN_NAMESPACE namespace QTMS_NAMESPACE {
# define QTMS_END_NAMESPACE }
# define QTMS_USE_NAMESPACE using namespace QTMS_NAMESPACE;
#else
# define QTMS_BEGIN_NAMESPACE
# define QTMS_END_NAMESPACE
# define QTMS_USE_NAMESPACE
#endif

// if Q_SERVICEFW_EXPORT wasn't defined before this file was included
// remove any trace of it now.
#if defined(QTMS_UNDEFINE_Q_SERVICEFW_EXPORT)
#  undef Q_SERVICEFW_EXPORT
#endif

//in case Qt is in namespace
QT_USE_NAMESPACE

#endif // QMOBILITYSUBSET_H

