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
#ifndef QGEOSATELLITEINFOSOURCE_H
#define QGEOSATELLITEINFOSOURCE_H

#include "qmobilitysubset.h"
#include "qgeosatelliteinfo.h"

#include <QObject>
#include <QList>


QT_BEGIN_HEADER

QTMS_BEGIN_NAMESPACE

class QGeoSatelliteInfoSourcePrivate;

class Q_LOCATION_EXPORT QGeoSatelliteInfoSource : public QObject
{
    Q_OBJECT
public:
    explicit QGeoSatelliteInfoSource(QObject *parent);

    static QGeoSatelliteInfoSource *createDefaultSource(QObject *parent);
    static QGeoSatelliteInfoSource *createSource(const QString &sourceName, QObject *parent);
    static QStringList availableSources();

public Q_SLOTS:
    virtual void startUpdates() = 0;
    virtual void stopUpdates() = 0;

    virtual void requestUpdate(int timeout = 0) = 0;

Q_SIGNALS:
    void satellitesInViewUpdated(const QList<QGeoSatelliteInfo> &satellites);
    void satellitesInUseUpdated(const QList<QGeoSatelliteInfo> &satellites);
    void requestTimeout();

private:
    Q_DISABLE_COPY(QGeoSatelliteInfoSource)
    QGeoSatelliteInfoSourcePrivate *d;
};

QTMS_END_NAMESPACE

QT_END_HEADER

#endif
