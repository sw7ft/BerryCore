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

#ifndef QBLUETOOTHTRANSFERREPLY_H
#define QBLUETOOTHTRANSFERREPLY_H

#include <QtCore/QIODevice>

#include <qbluetoothtransferrequest.h>
#include <qbluetoothtransfermanager.h>

QT_BEGIN_HEADER

QTM_BEGIN_NAMESPACE

class QBluetoothTransferReplyPrivate;

class Q_CONNECTIVITY_EXPORT QBluetoothTransferReply : public QObject
{
    Q_OBJECT

public:
    enum TransferError {
        NoError = 0,
        UnknownError,
        FileNotFoundError,
        HostNotFoundError,
        UserCanceledTransferError
    };


    ~QBluetoothTransferReply();

    QVariant attribute(QBluetoothTransferRequest::Attribute code) const;
    virtual bool isFinished() const = 0;
    virtual bool isRunning() const = 0;

    QBluetoothTransferManager *manager() const;

    QBluetoothTransferManager::Operation operation() const;

    virtual TransferError error() const = 0;
    virtual QString errorString() const = 0;

public Q_SLOTS:
    void abort();

Q_SIGNALS:
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void finished(QBluetoothTransferReply *);
    void uploadProgress(qint64 bytesSent, qint64 bytesTotal);

protected:
    explicit QBluetoothTransferReply(QObject *parent = 0);
    void setAttribute(QBluetoothTransferRequest::Attribute code, const QVariant &value);
    void setOperation(QBluetoothTransferManager::Operation operation);
    void setManager(QBluetoothTransferManager *manager);
//    void setRequest(QBluetoothTransferRequest *request);

protected:
    QBluetoothTransferReplyPrivate *d_ptr;

private:
    Q_DECLARE_PRIVATE(QBluetoothTransferReply)

};

QTM_END_NAMESPACE

Q_DECLARE_METATYPE(QtMobility::QBluetoothTransferReply *);

QT_END_HEADER

#endif // QBLUETOOTHTRANSFERREPLY_H
