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

#ifndef QCAMERA_H
#define QCAMERA_H

#include <QtCore/qstringlist.h>
#include <QtCore/qpair.h>
#include <QtCore/qsize.h>
#include <QtCore/qpoint.h>
#include <QtCore/qrect.h>

#include <qmediacontrol.h>
#include <qmediaobject.h>
#include <qmediaservice.h>

#include <qcameraexposure.h>
#include <qcamerafocus.h>
#include <qcameraimageprocessing.h>

#include <qmediaserviceprovider.h>
#include <qmediaenumdebug.h>

QT_BEGIN_NAMESPACE

class QAbstractVideoSurface;
class QVideoWidget;
class QGraphicsVideoItem;

class QCameraPrivate;
class Q_MULTIMEDIA_EXPORT QCamera : public QMediaObject
{
    Q_OBJECT
    Q_PROPERTY(QCamera::State state READ state NOTIFY stateChanged)
    Q_PROPERTY(QCamera::Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(QCamera::CaptureMode captureMode READ captureMode WRITE setCaptureMode NOTIFY captureModeChanged)
    Q_PROPERTY(QCamera::LockStatus lockStatus READ lockStatus NOTIFY lockStatusChanged)

    Q_ENUMS(Status)
    Q_ENUMS(State)
    Q_ENUMS(CaptureMode)
    Q_ENUMS(Error)
    Q_ENUMS(LockStatus)
    Q_ENUMS(LockChangeReason)
    Q_ENUMS(LockType)
public:
    enum Status {
        UnavailableStatus,
        UnloadedStatus,
        LoadingStatus,
        LoadedStatus,
        StandbyStatus,
        StartingStatus,
        ActiveStatus
    };

    enum State {
        UnloadedState,
        LoadedState,
        ActiveState
    };

    enum CaptureMode
    {
        CaptureStillImage,
        CaptureVideo
    };

    enum Error
    {
        NoError,
        CameraError,
        InvalidRequestError,
        ServiceMissingError,
        NotSupportedFeatureError
    };

    enum LockStatus
    {
        Unlocked,
        Searching,
        Locked
    };

    enum LockChangeReason {
        UserRequest,
        LockAcquired,
        LockFailed,
        LockLost,
        LockTemporaryLost
    };

    enum LockType
    {
        NoLock = 0,
        LockExposure = 0x01,
        LockWhiteBalance = 0x02,
        LockFocus = 0x04
    };
    Q_DECLARE_FLAGS(LockTypes, LockType)

    QCamera(QObject *parent = 0, QMediaServiceProvider *provider = QMediaServiceProvider::defaultServiceProvider());
    QCamera(const QByteArray& device, QObject *parent = 0);
    ~QCamera();

    static QList<QByteArray> availableDevices();
    static QString deviceDescription(const QByteArray &device);

    bool isAvailable() const;
    QtMultimediaKit::AvailabilityError availabilityError() const;

    State state() const;
    Status status() const;

    CaptureMode captureMode() const;
    bool isCaptureModeSupported(CaptureMode mode) const;

    QCameraExposure *exposure() const;
    QCameraFocus *focus() const;
    QCameraImageProcessing *imageProcessing() const;

    void setViewfinder(QVideoWidget *viewfinder);
    void setViewfinder(QGraphicsVideoItem *viewfinder);
    void setViewfinder(QAbstractVideoSurface *surface);

    Error error() const;
    QString errorString() const;

    QCamera::LockTypes supportedLocks() const;
    QCamera::LockTypes requestedLocks() const;

    QCamera::LockStatus lockStatus() const;
    QCamera::LockStatus lockStatus(QCamera::LockType lock) const;

public Q_SLOTS:
    void setCaptureMode(QCamera::CaptureMode mode);

    void load();
    void unload();

    void start();
    void stop();

    void searchAndLock();
    void unlock();

    void searchAndLock(QCamera::LockTypes locks);
    void unlock(QCamera::LockTypes locks);

Q_SIGNALS:
    void stateChanged(QCamera::State);
    void captureModeChanged(QCamera::CaptureMode);
    void statusChanged(QCamera::Status);

    void locked();
    void lockFailed();

    void lockStatusChanged(QCamera::LockStatus, QCamera::LockChangeReason);
    void lockStatusChanged(QCamera::LockType, QCamera::LockStatus, QCamera::LockChangeReason);

    void error(QCamera::Error);

private:
    Q_DISABLE_COPY(QCamera)
    Q_DECLARE_PRIVATE(QCamera)
    Q_PRIVATE_SLOT(d_func(), void _q_preparePropertyChange(int))
    Q_PRIVATE_SLOT(d_func(), void _q_restartCamera())
    Q_PRIVATE_SLOT(d_func(), void _q_error(int, const QString &))
    Q_PRIVATE_SLOT(d_func(), void _q_updateLockStatus(QCamera::LockType, QCamera::LockStatus, QCamera::LockChangeReason))
    Q_PRIVATE_SLOT(d_func(), void _q_updateState(QCamera::State))
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QCamera::LockTypes)

QT_END_NAMESPACE

Q_DECLARE_METATYPE(QCamera::State)
Q_DECLARE_METATYPE(QCamera::Status)
Q_DECLARE_METATYPE(QCamera::Error)
Q_DECLARE_METATYPE(QCamera::CaptureMode)
Q_DECLARE_METATYPE(QCamera::LockType)
Q_DECLARE_METATYPE(QCamera::LockStatus)
Q_DECLARE_METATYPE(QCamera::LockChangeReason)

Q_MEDIA_ENUM_DEBUG(QCamera, State)
Q_MEDIA_ENUM_DEBUG(QCamera, Status)
Q_MEDIA_ENUM_DEBUG(QCamera, Error)
Q_MEDIA_ENUM_DEBUG(QCamera, CaptureMode)
Q_MEDIA_ENUM_DEBUG(QCamera, LockType)
Q_MEDIA_ENUM_DEBUG(QCamera, LockStatus)
Q_MEDIA_ENUM_DEBUG(QCamera, LockChangeReason)

#endif  // QCAMERA_H
