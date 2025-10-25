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

#ifndef QGYROSCOPE_H
#define QGYROSCOPE_H

#include <qsensor.h>

#if defined(Q_OS_BLACKBERRY)
# include <qorientablesensorbase.h>
#endif

QTM_BEGIN_NAMESPACE

class QGyroscopeReadingPrivate;

class Q_SENSORS_EXPORT QGyroscopeReading : public QSensorReading
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x)
    Q_PROPERTY(qreal y READ y)
    Q_PROPERTY(qreal z READ z)
    DECLARE_READING(QGyroscopeReading)
public:
    qreal x() const;
    void setX(qreal x);

    qreal y() const;
    void setY(qreal y);

    qreal z() const;
    void setZ(qreal z);
};

class Q_SENSORS_EXPORT QGyroscopeFilter : public QSensorFilter
{
public:
    virtual bool filter(QGyroscopeReading *reading) = 0;
private:
    bool filter(QSensorReading *reading) { return filter(static_cast<QGyroscopeReading*>(reading)); }
};

class Q_SENSORS_EXPORT QGyroscope : public QSensor
#if defined(Q_OS_BLACKBERRY)
, public QOrientableSensorBase
#endif
{
    Q_OBJECT
#if !defined(Q_QDOC) && defined(Q_OS_BLACKBERRY)
    Q_PROPERTY(AxesOrientationMode axesOrientationMode READ axesOrientationMode WRITE setAxesOrientationMode NOTIFY axesOrientationModeChanged)
    Q_PROPERTY(int currentOrientation READ currentOrientation NOTIFY currentOrientationChanged)
    Q_PROPERTY(int userOrientation READ userOrientation WRITE setUserOrientation NOTIFY userOrientationChanged)
#endif
public:
#if defined(Q_MOC_RUN) && defined(Q_OS_BLACKBERRY)
    // Enums must be replicated in child classes to work in QML
    enum AxesOrientationMode {
        FixedOrientation,
        AutomaticOrientation,
        UserOrientation
    };
    Q_ENUMS(AxesOrientationMode)
#endif
    explicit QGyroscope(QObject *parent = 0) : QSensor(QGyroscope::type, parent) {}
    virtual ~QGyroscope() {}
    QGyroscopeReading *reading() const { return static_cast<QGyroscopeReading*>(QSensor::reading()); }
    static char const * const type;

#if !defined(Q_QDOC) && defined(Q_OS_BLACKBERRY)
Q_SIGNALS:
    void axesOrientationModeChanged(AxesOrientationMode axesOrientationMode);
    void currentOrientationChanged(int currentOrientation);
    void userOrientationChanged(int userOrientation);
#endif
};

QTM_END_NAMESPACE

#endif

