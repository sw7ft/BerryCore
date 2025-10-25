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


#ifndef QNEARFIELDTARGET_H
#define QNEARFIELDTARGET_H

#include "qmobilityglobal.h"

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QMetaType>
#include <QtCore/QSharedDataPointer>

class QString;
class QUrl;

QT_BEGIN_HEADER

QTM_BEGIN_NAMESPACE

class QNdefMessage;
class QNearFieldTargetPrivate;

class Q_CONNECTIVITY_EXPORT QNearFieldTarget : public QObject
{
    Q_OBJECT

    Q_DECLARE_PRIVATE(QNearFieldTarget)

public:
    enum Type {
        AnyTarget,
        ProprietaryTag,
        NfcTagType1,
        NfcTagType2,
        NfcTagType3,
        NfcTagType4,
        MifareTag,
        NfcForumDevice
    };

    enum AccessMethod {
        NdefAccess,
        TagTypeSpecificAccess,
        LlcpAccess
    };
    Q_DECLARE_FLAGS(AccessMethods, AccessMethod)

    enum Error {
        NoError,
        UnknownError,
        UnsupportedError,
        TargetOutOfRangeError,
        NoResponseError,
        ChecksumMismatchError,
        InvalidParametersError,
        NdefReadError,
        NdefWriteError
    };

    class RequestIdPrivate;
    class Q_CONNECTIVITY_EXPORT RequestId
    {
    public:
        RequestId();
        RequestId(const RequestId &other);
        RequestId(RequestIdPrivate *p);
        ~RequestId();

        bool isValid() const;

        int refCount() const;

        bool operator<(const RequestId &other) const;
        bool operator==(const RequestId &other) const;
        bool operator!=(const RequestId &other) const;
        RequestId &operator=(const RequestId &other);

        QSharedDataPointer<RequestIdPrivate> d;
    };

    explicit QNearFieldTarget(QObject *parent = 0);
    virtual ~QNearFieldTarget();

    virtual QByteArray uid() const = 0;
    virtual QUrl url() const;

    virtual Type type() const = 0;
    virtual AccessMethods accessMethods() const = 0;

    bool isProcessingCommand() const;

    // NdefAccess
    virtual bool hasNdefMessage();
    virtual RequestId readNdefMessages();
    virtual RequestId writeNdefMessages(const QList<QNdefMessage> &messages);

    // TagTypeSpecificAccess
    virtual RequestId sendCommand(const QByteArray &command);
    virtual RequestId sendCommands(const QList<QByteArray> &commands);

    virtual bool waitForRequestCompleted(const RequestId &id, int msecs = 5000);

    QVariant requestResponse(const RequestId &id);
    void setResponseForRequest(const QNearFieldTarget::RequestId &id, const QVariant &response,
                               bool emitRequestCompleted = true);

protected:
    Q_INVOKABLE virtual bool handleResponse(const QNearFieldTarget::RequestId &id,
                                            const QByteArray &response);

Q_SIGNALS:
    void disconnected();

    void ndefMessageRead(const QNdefMessage &message);
    void ndefMessagesWritten();

    void requestCompleted(const QNearFieldTarget::RequestId &id);

    void error(QNearFieldTarget::Error error, const QNearFieldTarget::RequestId &id);

private:
    QNearFieldTargetPrivate *d_ptr;
};

Q_CONNECTIVITY_EXPORT quint16 qNfcChecksum(const char * data, uint len);

Q_DECLARE_OPERATORS_FOR_FLAGS(QNearFieldTarget::AccessMethods)

QTM_END_NAMESPACE

Q_DECLARE_METATYPE(QtMobility::QNearFieldTarget::RequestId)
Q_DECLARE_METATYPE(QtMobility::QNearFieldTarget::Error)

QT_END_HEADER

#endif // QNEARFIELDTARGET_H
