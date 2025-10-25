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

#ifndef QRFCOMMSERVER_H
#define QRFCOMMSERVER_H

#include <qmobilityglobal.h>

#include <QObject>

#include <qbluetoothaddress.h>
#include <qbluetooth.h>
#include <qbluetoothsocket.h>

QT_BEGIN_HEADER

QTM_BEGIN_NAMESPACE

class QRfcommServerPrivate;
class QBluetoothSocket;

class Q_CONNECTIVITY_EXPORT QRfcommServer : public QObject
{
    Q_OBJECT

public:
    QRfcommServer(QObject *parent = 0);
    ~QRfcommServer();

    void close();

    bool listen(const QBluetoothAddress &address = QBluetoothAddress(), quint16 port = 0);
    bool listen(const QBluetoothUuid uuid, QString serviceName);
    bool isListening() const;

    void setMaxPendingConnections(int numConnections);
    int maxPendingConnections() const;

    bool hasPendingConnections() const;
    QBluetoothSocket *nextPendingConnection();

    QBluetoothAddress serverAddress() const;
    quint16 serverPort() const;

    void setSecurityFlags(QBluetooth::SecurityFlags security);
    QBluetooth::SecurityFlags securityFlags() const;

Q_SIGNALS:
    void newConnection();

protected:
    QRfcommServerPrivate *d_ptr;

private:
    Q_DECLARE_PRIVATE(QRfcommServer)

#ifdef QTM_SYMBIAN_BLUETOOTH
    Q_PRIVATE_SLOT(d_func(), void _q_connected())
    Q_PRIVATE_SLOT(d_func(), void _q_socketError(QBluetoothSocket::SocketError err))
    Q_PRIVATE_SLOT(d_func(), void _q_disconnected())
#endif //QTM_SYMBIAN_BLUETOOTH  
    
#ifdef QTM_BLUEZ_BLUETOOTH
    Q_PRIVATE_SLOT(d_func(), void _q_newConnection())
#endif
};



QTM_END_NAMESPACE

QT_END_HEADER

#endif
