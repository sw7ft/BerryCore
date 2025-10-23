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
#ifndef QMOBILITYPLUGINSEARCH_H
#define QMOBILITYPLUGINSEARCH_H

#include <QCoreApplication>
#include <QStringList>
#include <QDir>
#include <QDebug>

#if defined(Q_OS_SYMBIAN)
# include <f32file.h>
#endif

QTMS_BEGIN_NAMESPACE

#if defined(Q_OS_SYMBIAN)
static inline bool qSymbian_CheckDir(const QDir& dir, RFs& rfs)
{
    bool pathFound = false;
    // In Symbian, going cdUp() in a c:/private/<uid3>/ will result in *platsec* error at fileserver (requires AllFiles capability)
    // Also, trying to cd() to a nonexistent directory causes *platsec* error. This does not cause functional harm, but should
    // nevertheless be changed to use native Symbian methods to avoid unnecessary platsec warnings (as per qpluginloader.cpp).
    // Use native Symbian code to check for directory existence, because checking
    // for files from under non-existent protected dir like E:/private/<uid> using
    // QDir::exists causes platform security violations on most apps.
    QString nativePath = QDir::toNativeSeparators(dir.absolutePath());
    TPtrC ptr = TPtrC16(static_cast<const TUint16*>(nativePath.utf16()), nativePath.length());
    TUint attributes;
    TInt err = rfs.Att(ptr, attributes);
    if (err == KErrNone) {
        // yes, the directory exists.
        pathFound = true;
    }
    return pathFound;
}
#define CHECKDIR(dir) qSymbian_CheckDir(dir, rfs)
#else
#define CHECKDIR(dir) (dir).exists()
#endif

inline QStringList mobilityPlugins(const QString& plugintype)
{
#if !defined QT_NO_DEBUG
    const bool showDebug = qgetenv("QT_DEBUG_PLUGINS").toInt() > 0;
#endif

    QStringList paths = QCoreApplication::libraryPaths();
#ifdef QTMS_PLUGIN_PATH
    paths << QLatin1String(QTMS_PLUGIN_PATH);
#endif
#if !defined QT_NO_DEBUG
    if (showDebug)
        qDebug() << "Plugin paths:" << paths;
#endif

#if defined(Q_OS_SYMBIAN)
    RFs rfs;
    qt_symbian_throwIfError(rfs.Connect());
#endif

    // Temp variable to avoid multiple identical paths
    // (we don't convert the list to set first, because that loses the order)
    QSet<QString> processed;

    /* The list of discovered plugins */
    QStringList plugins;

    /* Enumerate our plugin paths */
    for (int i=0; i < paths.count(); i++) {
        if (processed.contains(paths.at(i)))
            continue;
        processed.insert(paths.at(i));
        QDir pluginsDir(paths.at(i));
        if (!CHECKDIR(pluginsDir))
            continue;

#if defined(Q_OS_WIN)
        if (pluginsDir.dirName().toLower() == QLatin1String("debug") || pluginsDir.dirName().toLower() == QLatin1String("release"))
            pluginsDir.cdUp();
#elif defined(Q_OS_MAC)
        if (pluginsDir.dirName() == QLatin1String("MacOS")) {
            pluginsDir.cdUp();
            pluginsDir.cdUp();
            pluginsDir.cdUp();
        }
#endif

        QString subdir(QLatin1String("plugins/"));
        subdir += plugintype;
        if (pluginsDir.path().endsWith(QLatin1String("/plugins"))
            || pluginsDir.path().endsWith(QLatin1String("/plugins/")))
            subdir = plugintype;

        if (CHECKDIR(QDir(pluginsDir.filePath(subdir)))) {
            pluginsDir.cd(subdir);
            QStringList files = pluginsDir.entryList(QDir::Files);

#if !defined QT_NO_DEBUG
            if (showDebug)
                qDebug() << "Looking for " << plugintype << " plugins in" << pluginsDir.path() << files;
#endif

            for (int j=0; j < files.count(); j++) {
                plugins <<  pluginsDir.absoluteFilePath(files.at(j));
            }
        }
    }

    /* Add application path + plugintype */
    QDir appldir(QCoreApplication::applicationDirPath());
    if(appldir.cd(plugintype)){
        if (!processed.contains(appldir.absolutePath())){
            processed.insert(appldir.absolutePath());
            QStringList files = appldir.entryList(QDir::Files);
#if !defined QT_NO_DEBUG
            if (showDebug)
                qDebug() << "Looking for " << plugintype << " plugins in" << appldir.path() << files;
#endif
            for (int j=0; j < files.count(); j++) {
                plugins <<  appldir.absoluteFilePath(files.at(j));
            }
        }
    }

#if defined(Q_OS_SYMBIAN)
    rfs.Close();
#endif
    return  plugins;
}

QTMS_END_NAMESPACE

#endif
