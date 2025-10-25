/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef QCAMERAEXPOSURECONTROL_H
#define QCAMERAEXPOSURECONTROL_H

#include <qmediacontrol.h>
#include <qmediaobject.h>

#include <qcameraexposure.h>
#include <qcamera.h>
#include <qmediaenumdebug.h>

QT_BEGIN_NAMESPACE

class Q_MULTIMEDIA_EXPORT QCameraExposureControl : public QMediaControl
{
    Q_OBJECT
    Q_ENUMS(ExposureParameter)

public:
    ~QCameraExposureControl();

    enum ExposureParameter {
        InvalidParameter = 0,
        ISO = 1,
        Aperture = 2,
        ShutterSpeed = 3,
        ExposureCompensation = 4,
        FlashPower = 5,
        FlashCompensation = 6,
        ExtendedExposureParameter = 1000
    };

    enum ParameterFlag {
        AutomaticValue = 0x01,
        ReadOnly = 0x02,
        ContinuousRange = 0x04
    };
    Q_DECLARE_FLAGS(ParameterFlags, ParameterFlag)

    virtual QCameraExposure::ExposureMode exposureMode() const = 0;
    virtual void setExposureMode(QCameraExposure::ExposureMode mode) = 0;
    virtual bool isExposureModeSupported(QCameraExposure::ExposureMode mode) const = 0;

    virtual QCameraExposure::MeteringMode meteringMode() const = 0;
    virtual void setMeteringMode(QCameraExposure::MeteringMode mode) = 0;
    virtual bool isMeteringModeSupported(QCameraExposure::MeteringMode mode) const = 0;

    virtual bool isParameterSupported(ExposureParameter parameter) const = 0;
    virtual QVariant exposureParameter(ExposureParameter parameter) const = 0;
    virtual ParameterFlags exposureParameterFlags(ExposureParameter parameter) const = 0;
    virtual QVariantList supportedParameterRange(ExposureParameter parameter) const = 0;
    virtual bool setExposureParameter(ExposureParameter parameter, const QVariant& value) = 0;

    virtual QString extendedParameterName(ExposureParameter parameter) = 0;

Q_SIGNALS:
    void flashReady(bool);

    void exposureParameterChanged(int parameter);
    void exposureParameterRangeChanged(int parameter);

protected:
    QCameraExposureControl(QObject* parent = 0);
};

#define QCameraExposureControl_iid "com.nokia.Qt.QCameraExposureControl/1.0"
Q_MEDIA_DECLARE_CONTROL(QCameraExposureControl, QCameraExposureControl_iid)

Q_DECLARE_OPERATORS_FOR_FLAGS(QCameraExposureControl::ParameterFlags)

Q_MEDIA_ENUM_DEBUG(QCameraExposureControl, ExposureParameter)

QT_END_NAMESPACE

#endif  // QCAMERAEXPOSURECONTROL_H

