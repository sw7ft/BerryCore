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

#ifndef QACCELEROMETER_H
#define QACCELEROMETER_H

#include <qsensor.h>

#if defined(Q_OS_BLACKBERRY)
# include <qorientablesensorbase.h>
#endif

QTM_BEGIN_NAMESPACE

class QAccelerometerReadingPrivate;

class Q_SENSORS_EXPORT QAccelerometerReading : public QSensorReading
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x)
    Q_PROPERTY(qreal y READ y)
    Q_PROPERTY(qreal z READ z)
    DECLARE_READING(QAccelerometerReading)
public:
    qreal x() const;
    void setX(qreal x);

    qreal y() const;
    void setY(qreal y);

    qreal z() const;
    void setZ(qreal z);
};

class Q_SENSORS_EXPORT QAccelerometerFilter : public QSensorFilter
{
public:
    virtual bool filter(QAccelerometerReading *reading) = 0;
private:
    bool filter(QSensorReading *reading) { return filter(static_cast<QAccelerometerReading*>(reading)); }
};

class QAccelerometerPrivate;

class Q_SENSORS_EXPORT QAccelerometer : public QSensor
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

    Q_ENUMS(AccelerationMode)
    Q_PROPERTY(AccelerationMode accelerationMode READ accelerationMode WRITE setAccelerationMode
               NOTIFY accelerationModeChanged)
public:
    explicit QAccelerometer(QObject *parent = 0);
    virtual ~QAccelerometer();

#if defined(Q_MOC_RUN) && defined(Q_OS_BLACKBERRY)
    // Enums must be replicated in child classes to work in QML
    enum AxesOrientationMode {
        FixedOrientation,
        AutomaticOrientation,
        UserOrientation
    };
    Q_ENUMS(AxesOrientationMode)
#endif
    enum AccelerationMode {
        Gravity,
        User,
        Combined
    };

    AccelerationMode accelerationMode() const;
    void setAccelerationMode(AccelerationMode accelerationMode);

    QAccelerometerReading *reading() const { return static_cast<QAccelerometerReading*>(QSensor::reading()); }
    static char const * const type;

public Q_SLOTS:
    void setUserAcceleration();
    void setGravityAcceleration();
    void setCombinedAcceleration();

Q_SIGNALS:
    void accelerationModeChanged(AccelerationMode accelerationMode);
#if !defined(Q_QDOC) && defined(Q_OS_BLACKBERRY)
    void axesOrientationModeChanged(AxesOrientationMode axesOrientationMode);
    void currentOrientationChanged(int currentOrientation);
    void userOrientationChanged(int userOrientation);
#endif
private:
    friend class QAccelerometerPrivate;
    QAccelerometerPrivate *d_func() const;
    Q_DISABLE_COPY(QAccelerometer)
};

QTM_END_NAMESPACE

#endif

