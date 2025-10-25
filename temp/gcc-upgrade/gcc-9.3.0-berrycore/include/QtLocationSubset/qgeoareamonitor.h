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
#ifndef QGEOAREAMONITOR_H
#define QGEOAREAMONITOR_H

#include "qmobilitysubset.h"
#include "qgeocoordinate.h"
#include <QMetaType>
#include <QObject>

QT_BEGIN_HEADER
QTMS_BEGIN_NAMESPACE

class QGeoPositionInfo;
class QGeoAreaMonitorPrivate;
class Q_LOCATION_EXPORT QGeoAreaMonitor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QGeoCoordinate center READ center WRITE setCenter)
    Q_PROPERTY(qreal radius READ radius WRITE setRadius)

public:
    explicit QGeoAreaMonitor(QObject *parent);
    virtual ~QGeoAreaMonitor() = 0;

    virtual void setCenter(const QGeoCoordinate &coordinate);
    QGeoCoordinate center() const;

    virtual void setRadius(qreal radius);
    qreal radius() const;

    static QGeoAreaMonitor *createDefaultMonitor(QObject *parent);

Q_SIGNALS:
    void areaEntered(const QGeoPositionInfo &update);
    void areaExited(const QGeoPositionInfo &update);

private:
    Q_DISABLE_COPY(QGeoAreaMonitor)
    Q_DECLARE_PRIVATE(QGeoAreaMonitor)
    QScopedPointer<QGeoAreaMonitorPrivate> d_ptr;
};

QTMS_END_NAMESPACE
QT_END_HEADER

#endif
