/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Mobility Components.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QSENSORMANAGER_H
#define QSENSORMANAGER_H

#include <qsensor.h>

QTM_BEGIN_NAMESPACE

class QSensorBackend;
class QSensorBackendFactory;
class QSensorPluginInterface;

typedef QSensorPluginInterface *(*CreatePluginFunc)();

class Q_SENSORS_EXPORT QSensorManager
{
public:
    // Register a backend (call this from a plugin)
    static void registerBackend(const QByteArray &type, const QByteArray &identifier, QSensorBackendFactory *factory);
    static void unregisterBackend(const QByteArray &type, const QByteArray &identifier);

    static bool isBackendRegistered(const QByteArray &type, const QByteArray &identifier);

    // Create a backend (uses the type and identifier set in the sensor)
    static QSensorBackend *createBackend(QSensor *sensor);

    // For static plugins
    static void registerStaticPlugin(CreatePluginFunc func);
};

class Q_SENSORS_EXPORT QSensorBackendFactory
{
public:
    virtual QSensorBackend *createBackend(QSensor *sensor) = 0;
protected:
    ~QSensorBackendFactory() {}
};

// The default is for legacy static plugins
// This will change to Qt-style static plugins in 1.3
#define REGISTER_STATIC_PLUGIN(pluginname) \
        REGISTER_STATIC_PLUGIN_V1(pluginname)

// Legacy static plugins have their own registration methods.
// They can only register types. They cannot use the changes interface.
#define REGISTER_STATIC_PLUGIN_V1(pluginname) \
    static QSensorPluginInterface *create_static_plugin_ ## pluginname()\
    {\
        return new pluginname;\
    }\
    static bool side_effect_sensor_backend_ ## pluginname ()\
    {\
        QSensorManager::registerStaticPlugin(create_static_plugin_ ## pluginname);\
        return false;\
    }\
    /* This assignment calls the function above */\
    static bool dummy_sensor_backend_ ## pluginname = side_effect_sensor_backend_ ## pluginname();

// Qt-style static plugins use macros from Qt.
// They are handled just like regular plugins.
#define REGISTER_STATIC_PLUGIN_V2(pluginname) \
    QT_PREPEND_NAMESPACE(QObject) *qt_plugin_instance_##pluginname() Q_PLUGIN_INSTANCE(pluginname)\
    Q_IMPORT_PLUGIN(pluginname)

QTM_END_NAMESPACE

#endif

