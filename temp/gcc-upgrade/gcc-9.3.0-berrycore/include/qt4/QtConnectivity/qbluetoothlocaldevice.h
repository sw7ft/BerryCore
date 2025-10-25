/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef QBLUETOOTHLOCALDEVICE_H
#define QBLUETOOTHLOCALDEVICE_H

#include <qmobilityglobal.h>

#include <QObject>
#include <QtCore/QList>
#include <QString>

#include "qbluetoothaddress.h"

QT_BEGIN_HEADER

QTM_BEGIN_NAMESPACE

class QBluetoothLocalDevicePrivate;

class Q_CONNECTIVITY_EXPORT QBluetoothHostInfo
{
public:
    QBluetoothHostInfo() { };
    QBluetoothHostInfo(const QBluetoothHostInfo &other) {
        m_address = other.m_address;
        m_name = other.m_name;
    };

    QBluetoothAddress getAddress() const { return m_address; }
    void setAddress(const QBluetoothAddress &address) { m_address = address; }

    QString getName() const { return m_name; }
    void setName(const QString &name){ m_name = name; }

private:
    QBluetoothAddress m_address;
    QString m_name;

};


class Q_CONNECTIVITY_EXPORT QBluetoothLocalDevice : public QObject
{
    Q_OBJECT
    Q_ENUMS(Pairing)
    Q_ENUMS(HostMode)
    Q_ENUMS(Error)
public:
    enum Pairing {
        Unpaired,
        Paired,
        AuthorizedPaired
    };

    enum HostMode {        
        HostPoweredOff,
        HostConnectable,
        HostDiscoverable,
        HostDiscoverableLimitedInquiry
    };

    enum Error {
            NoError,
            PairingError,
            UnknownError = 100
    };
    QBluetoothLocalDevice(QObject *parent = 0);
    explicit QBluetoothLocalDevice(const QBluetoothAddress &address, QObject *parent = 0);
    virtual ~QBluetoothLocalDevice();

    bool isValid() const;

    void requestPairing(const QBluetoothAddress &address, Pairing pairing);
    Pairing pairingStatus(const QBluetoothAddress &address) const;

    void setHostMode(QBluetoothLocalDevice::HostMode mode);
    HostMode hostMode() const;

    void powerOn();

    QString name() const;
    QBluetoothAddress address() const;

    static QList<QBluetoothHostInfo> allDevices();

public Q_SLOTS:
    void pairingConfirmation(bool confirmation);

Q_SIGNALS:
    void hostModeStateChanged(QBluetoothLocalDevice::HostMode state);
    void pairingFinished(const QBluetoothAddress &address, QBluetoothLocalDevice::Pairing pairing);

    void pairingDisplayPinCode(const QBluetoothAddress &address, QString pin);
    void pairingDisplayConfirmation(const QBluetoothAddress &address, QString pin);
    void error(QBluetoothLocalDevice::Error error);

private:
    Q_DECLARE_PRIVATE(QBluetoothLocalDevice)
    QBluetoothLocalDevicePrivate *d_ptr;
#ifdef QTM_SYMBIAN_BLUETOOTH
    Q_PRIVATE_SLOT(d_func(), void _q_pairingFinished(const QBluetoothAddress &, QBluetoothLocalDevice::Pairing))
    Q_PRIVATE_SLOT(d_func(), void _q_registryError(int error))
    Q_PRIVATE_SLOT(d_func(), void _q_pairingError(int error))
#endif //QTM_SYMBIAN_BLUETOOTH
};

QTM_END_NAMESPACE

Q_DECLARE_METATYPE(QtMobility::QBluetoothLocalDevice::HostMode)
Q_DECLARE_METATYPE(QtMobility::QBluetoothLocalDevice::Pairing)
Q_DECLARE_METATYPE(QtMobility::QBluetoothLocalDevice::Error)

QT_END_HEADER

#endif // QBLUETOOTHLOCALDEVICE_H
