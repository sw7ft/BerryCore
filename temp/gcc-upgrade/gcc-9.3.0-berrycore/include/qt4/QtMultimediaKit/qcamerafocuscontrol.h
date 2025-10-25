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

#ifndef QCAMERAFOCUSCONTROL_H
#define QCAMERAFOCUSCONTROL_H

#include <qmediacontrol.h>
#include <qmediaobject.h>

#include <qcamerafocus.h>

QT_BEGIN_NAMESPACE

class Q_MULTIMEDIA_EXPORT QCameraFocusControl : public QMediaControl
{
    Q_OBJECT

public:
    ~QCameraFocusControl();

    virtual QCameraFocus::FocusMode focusMode() const = 0;
    virtual void setFocusMode(QCameraFocus::FocusMode mode) = 0;
    virtual bool isFocusModeSupported(QCameraFocus::FocusMode mode) const = 0;

    virtual qreal maximumOpticalZoom() const = 0;
    virtual qreal maximumDigitalZoom() const = 0;
    virtual qreal opticalZoom() const = 0;
    virtual qreal digitalZoom() const = 0;

    virtual void zoomTo(qreal optical, qreal digital) = 0;

    virtual QCameraFocus::FocusPointMode focusPointMode() const = 0;
    virtual void setFocusPointMode(QCameraFocus::FocusPointMode mode) = 0;
    virtual bool isFocusPointModeSupported(QCameraFocus::FocusPointMode mode) const = 0;
    virtual QPointF customFocusPoint() const = 0;
    virtual void setCustomFocusPoint(const QPointF &point) = 0;

    virtual QCameraFocusZoneList focusZones() const = 0;

Q_SIGNALS:
    void opticalZoomChanged(qreal opticalZoom);
    void digitalZoomChanged(qreal digitalZoom);
    void focusZonesChanged();
    void maximumOpticalZoomChanged(qreal);
    void maximumDigitalZoomChanged(qreal);

protected:
    QCameraFocusControl(QObject* parent = 0);
};

#define QCameraFocusControl_iid "com.nokia.Qt.QCameraFocusingControl/1.0"
Q_MEDIA_DECLARE_CONTROL(QCameraFocusControl, QCameraFocusControl_iid)

QT_END_NAMESPACE

#endif  // QCAMERAFOCUSCONTROL_H

