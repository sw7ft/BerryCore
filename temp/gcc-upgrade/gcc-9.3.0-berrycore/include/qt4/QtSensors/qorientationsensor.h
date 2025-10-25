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

#ifndef QORIENTATIONSENSOR_H
#define QORIENTATIONSENSOR_H

#include <qsensor.h>

QTM_BEGIN_NAMESPACE

class QOrientationReadingPrivate;

class Q_SENSORS_EXPORT QOrientationReading : public QSensorReading
{
    Q_OBJECT
    Q_ENUMS(Orientation)
    Q_PROPERTY(Orientation orientation READ orientation)
    DECLARE_READING(QOrientationReading)
public:
    enum Orientation {
        Undefined = 0,
        TopUp,
        TopDown,
        LeftUp,
        RightUp,
        FaceUp,
        FaceDown,
    };

    Orientation orientation() const;
    void setOrientation(Orientation orientation);
};

class Q_SENSORS_EXPORT QOrientationFilter : public QSensorFilter
{
public:
    virtual bool filter(QOrientationReading *reading) = 0;
private:
    bool filter(QSensorReading *reading) { return filter(static_cast<QOrientationReading*>(reading)); }
};

class Q_SENSORS_EXPORT QOrientationSensor : public QSensor
{
    Q_OBJECT
public:
    explicit QOrientationSensor(QObject *parent = 0) : QSensor(QOrientationSensor::type, parent) {}
    virtual ~QOrientationSensor() {}
    QOrientationReading *reading() const { return static_cast<QOrientationReading*>(QSensor::reading()); }
    static char const * const type;
};

QTM_END_NAMESPACE

#endif

