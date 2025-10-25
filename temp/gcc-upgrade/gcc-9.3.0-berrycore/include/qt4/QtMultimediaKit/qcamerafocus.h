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

#ifndef QCAMERAFOCUS_H
#define QCAMERAFOCUS_H

#include <QtCore/qstringlist.h>
#include <QtCore/qpair.h>
#include <QtCore/qsize.h>
#include <QtCore/qpoint.h>
#include <QtCore/qrect.h>
#include <QtCore/qshareddata.h>

#include <qmediaobject.h>
#include <qmediaenumdebug.h>

QT_BEGIN_NAMESPACE

class QCamera;

class QCameraFocusZoneData;

class Q_MULTIMEDIA_EXPORT QCameraFocusZone {
public:
    enum FocusZoneStatus {
        Invalid,
        Unused,
        Selected,
        Focused
    };

    QCameraFocusZone();
    QCameraFocusZone(const QRectF &area, FocusZoneStatus status = Selected);
    QCameraFocusZone(const QCameraFocusZone &other);

    QCameraFocusZone& operator=(const QCameraFocusZone &other);
    bool operator==(const QCameraFocusZone &other) const;
    bool operator!=(const QCameraFocusZone &other) const;

    ~QCameraFocusZone();

    bool isValid() const;

    QRectF area() const;

    FocusZoneStatus status() const;
    void setStatus(FocusZoneStatus status);

private:
     QSharedDataPointer<QCameraFocusZoneData> d;
};

typedef QList<QCameraFocusZone> QCameraFocusZoneList;


class QCameraFocusPrivate;
class Q_MULTIMEDIA_EXPORT QCameraFocus : public QObject
{
    Q_OBJECT

    Q_PROPERTY(FocusMode focusMode READ focusMode WRITE setFocusMode)
    Q_PROPERTY(FocusPointMode focusPointMode READ focusPointMode WRITE setFocusPointMode)
    Q_PROPERTY(QPointF customFocusPoint READ customFocusPoint WRITE setCustomFocusPoint)
    Q_PROPERTY(QCameraFocusZoneList focusZones READ focusZones NOTIFY focusZonesChanged)
    Q_PROPERTY(qreal opticalZoom READ opticalZoom NOTIFY opticalZoomChanged)
    Q_PROPERTY(qreal digitalZoom READ digitalZoom NOTIFY digitalZoomChanged)

    Q_ENUMS(FocusMode)
    Q_ENUMS(FocusPointMode)
public:
    enum FocusMode {
        ManualFocus = 0x1,
        HyperfocalFocus = 0x02,
        InfinityFocus = 0x04,
        AutoFocus = 0x8,
        ContinuousFocus = 0x10,
        MacroFocus = 0x20
    };
    Q_DECLARE_FLAGS(FocusModes, FocusMode)

    enum FocusPointMode {
        FocusPointAuto,
        FocusPointCenter,
        FocusPointFaceDetection,
        FocusPointCustom
    };

    bool isAvailable() const;

    FocusMode focusMode() const;
    void setFocusMode(FocusMode mode);
    bool isFocusModeSupported(FocusMode mode) const;

    FocusPointMode focusPointMode() const;
    void setFocusPointMode(FocusPointMode mode);
    bool isFocusPointModeSupported(FocusPointMode) const;
    QPointF customFocusPoint() const;
    void setCustomFocusPoint(const QPointF &point);

    QCameraFocusZoneList focusZones() const;

    qreal maximumOpticalZoom() const;
    qreal maximumDigitalZoom() const;
    qreal opticalZoom() const;
    qreal digitalZoom() const;

    void zoomTo(qreal opticalZoom, qreal digitalZoom);

Q_SIGNALS:
    void opticalZoomChanged(qreal);
    void digitalZoomChanged(qreal);

    void focusZonesChanged();

    void maximumOpticalZoomChanged(qreal);
    void maximumDigitalZoomChanged(qreal);

private:
    friend class QCamera;
    QCameraFocus(QCamera *camera);
    ~QCameraFocus();

    Q_DISABLE_COPY(QCameraFocus)
    Q_DECLARE_PRIVATE(QCameraFocus)
    QCameraFocusPrivate *d_ptr;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QCameraFocus::FocusModes)

QT_END_NAMESPACE

Q_DECLARE_METATYPE(QCameraFocus::FocusModes)
Q_DECLARE_METATYPE(QCameraFocus::FocusPointMode)

Q_MEDIA_ENUM_DEBUG(QCameraFocus, FocusMode)
Q_MEDIA_ENUM_DEBUG(QCameraFocus, FocusPointMode)

#endif  // QCAMERAFOCUS_H
