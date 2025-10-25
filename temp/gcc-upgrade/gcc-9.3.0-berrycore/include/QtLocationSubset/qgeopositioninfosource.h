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
#ifndef QGEOPOSITIONINFOSOURCE_H
#define QGEOPOSITIONINFOSOURCE_H

#include "qmobilitysubset.h"
#include "qgeopositioninfo.h"

#include <QObject>

QT_BEGIN_HEADER

QTMS_BEGIN_NAMESPACE

class QGeoPositionInfoSourcePrivate;

class Q_LOCATION_EXPORT QGeoPositionInfoSource : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int updateInterval READ updateInterval WRITE setUpdateInterval)
    Q_PROPERTY(int minimumUpdateInterval READ minimumUpdateInterval)

public:
    enum PositioningMethod {
        SatellitePositioningMethods = 0x000000ff,
        NonSatellitePositioningMethods = 0xffffff00,
        AllPositioningMethods = 0xffffffff
    };
    Q_DECLARE_FLAGS(PositioningMethods, PositioningMethod)

    explicit QGeoPositionInfoSource(QObject *parent);
    virtual ~QGeoPositionInfoSource();

    virtual void setUpdateInterval(int msec);
    int updateInterval() const;

    virtual void setPreferredPositioningMethods(PositioningMethods methods);
    PositioningMethods preferredPositioningMethods() const;

    virtual QGeoPositionInfo lastKnownPosition(bool fromSatellitePositioningMethodsOnly = false) const = 0;

    virtual PositioningMethods supportedPositioningMethods() const = 0;
    virtual int minimumUpdateInterval() const = 0;

    static QGeoPositionInfoSource *createDefaultSource(QObject *parent);
    static QGeoPositionInfoSource *createSource(const QString &sourceName, QObject *parent);
    static QStringList availableSources();

public Q_SLOTS:
    virtual void startUpdates() = 0;
    virtual void stopUpdates() = 0;

    virtual void requestUpdate(int timeout = 0) = 0;

Q_SIGNALS:
    void positionUpdated(const QGeoPositionInfo &update);
    void updateTimeout();

private:
    Q_DISABLE_COPY(QGeoPositionInfoSource)
    QGeoPositionInfoSourcePrivate *d;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QGeoPositionInfoSource::PositioningMethods)

QTMS_END_NAMESPACE

QT_END_HEADER

#endif
