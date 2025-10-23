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
#ifndef QGEOSATELLITEINFO_H
#define QGEOSATELLITEINFO_H

#include "qmobilitysubset.h"

#include <QMetaType>

QT_BEGIN_NAMESPACE
class QDebug;
class QDataStream;
QT_END_NAMESPACE

QT_BEGIN_HEADER

QTMS_BEGIN_NAMESPACE

class QGeoSatelliteInfoPrivate;

class Q_LOCATION_EXPORT QGeoSatelliteInfo
{
public:
    enum Attribute {
        Elevation,
        Azimuth
    };

    QGeoSatelliteInfo();
    QGeoSatelliteInfo(const QGeoSatelliteInfo &other);
    ~QGeoSatelliteInfo();

    QGeoSatelliteInfo &operator=(const QGeoSatelliteInfo &other);

    bool operator==(const QGeoSatelliteInfo &other) const;
    inline bool operator!=(const QGeoSatelliteInfo &other) const {
        return !operator==(other);
    }

    void setPrnNumber(int prn);
    int prnNumber() const;

    void setSignalStrength(int signalStrength);
    int signalStrength() const;

    void setAttribute(Attribute attribute, qreal value);
    qreal attribute(Attribute attribute) const;
    void removeAttribute(Attribute attribute);

    bool hasAttribute(Attribute attribute) const;

private:
#ifndef QT_NO_DEBUG_STREAM
    friend Q_LOCATION_EXPORT QDebug operator<<(QDebug dbg, const QGeoSatelliteInfo &info);
#endif
#ifndef QT_NO_DATASTREAM
    friend Q_LOCATION_EXPORT QDataStream &operator<<(QDataStream &stream, const QGeoSatelliteInfo &info);
    friend Q_LOCATION_EXPORT QDataStream &operator>>(QDataStream &stream, QGeoSatelliteInfo &info);
#endif
    QGeoSatelliteInfoPrivate *d;
};

#ifndef QT_NO_DEBUG_STREAM
Q_LOCATION_EXPORT QDebug operator<<(QDebug dbg, const QGeoSatelliteInfo &info);
#endif

#ifndef QT_NO_DATASTREAM
Q_LOCATION_EXPORT QDataStream &operator<<(QDataStream &stream, const QGeoSatelliteInfo &info);
Q_LOCATION_EXPORT QDataStream &operator>>(QDataStream &stream, QGeoSatelliteInfo &info);
#endif

QTMS_END_NAMESPACE

Q_DECLARE_METATYPE(QtMobilitySubset::QGeoSatelliteInfo)

QT_END_HEADER

#endif
