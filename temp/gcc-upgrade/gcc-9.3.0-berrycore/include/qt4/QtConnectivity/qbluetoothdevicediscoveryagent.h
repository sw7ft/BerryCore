/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef QBLUETOOTHDEVICEDISCOVERYAGENT_H
#define QBLUETOOTHDEVICEDISCOVERYAGENT_H

#include <qmobilityglobal.h>

#include <QObject>

#include <qbluetoothdeviceinfo.h>

QT_BEGIN_HEADER

QTM_BEGIN_NAMESPACE

class QBluetoothDeviceDiscoveryAgentPrivate;

class Q_CONNECTIVITY_EXPORT QBluetoothDeviceDiscoveryAgent : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QBluetoothDeviceDiscoveryAgent::InquiryType inquiryType READ inquiryType WRITE setInquiryType)

public:
    // FIXME: add more errors
    // FIXME: add bluez error handling
    enum Error {
        NoError,
        IOFailure,
        PoweredOff,
        UnknownError = 100
    };

    enum InquiryType {
        GeneralUnlimitedInquiry,
        LimitedInquiry,
    };

    QBluetoothDeviceDiscoveryAgent(QObject *parent = 0);
    ~QBluetoothDeviceDiscoveryAgent();

    QBluetoothDeviceDiscoveryAgent::InquiryType inquiryType() const;
    void setInquiryType(QBluetoothDeviceDiscoveryAgent::InquiryType type);

    bool isActive() const;

    Error error() const;
    QString errorString() const;

    QList<QBluetoothDeviceInfo> discoveredDevices() const;

public Q_SLOTS:
    void start();
    void stop();

Q_SIGNALS:
    void deviceDiscovered(const QBluetoothDeviceInfo &info);
    void finished();
    void error(QBluetoothDeviceDiscoveryAgent::Error error);
    void canceled();

private:
    Q_DECLARE_PRIVATE(QBluetoothDeviceDiscoveryAgent)
    QBluetoothDeviceDiscoveryAgentPrivate *d_ptr;

#ifdef QTM_BLUEZ_BLUETOOTH
    Q_PRIVATE_SLOT(d_func(), void _q_deviceFound(const QString &address, const QVariantMap &dict));
    Q_PRIVATE_SLOT(d_func(), void _q_propertyChanged(const QString &name, const QDBusVariant &value));
#endif

#ifdef QTM_SYMBIAN_BLUETOOTH
    Q_PRIVATE_SLOT(d_func(), void _q_newDeviceFound(const QBluetoothDeviceInfo &device))
    Q_PRIVATE_SLOT(d_func(), void _q_setError(QBluetoothDeviceDiscoveryAgent::Error errorCode, QString errorDescription))
#endif // QTM_SYMBIAN_BLUETOOTH
};

QTM_END_NAMESPACE

QT_END_HEADER

#endif
