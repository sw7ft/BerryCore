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

#ifndef QBLUETOOTHUUID_H
#define QBLUETOOTHUUID_H

#include <qmobilityglobal.h>

#include <QtCore/QtGlobal>
#include <QtCore/QMetaType>
#include <QtCore/QUuid>

#include <QtCore/QDebug>

QT_BEGIN_HEADER

QTM_BEGIN_NAMESPACE

struct quint128
{
    quint8 data[16];
};

class Q_CONNECTIVITY_EXPORT QBluetoothUuid : public QUuid
{
public:
    enum ProtocolUuid {
        Sdp = 0x0001,
        Udp = 0x0002,
        Rfcomm = 0x0003,
        Tcp = 0x0004,
        TcsBin = 0x0005,
        TcsAt = 0x0006,
        Obex = 0x0008,
        Ip = 0x0009,
        Ftp = 0x000A,
        Http = 0x000C,
        Wsp = 0x000E,
        Bnep = 0x000F,
        Upnp = 0x0010,
        Hidp = 0x0011,
        HardcopyControlChannel = 0x0012,
        HardcopyDataChannel = 0x0014,
        HardcopyNotification = 0x0016,
        Avctp = 0x0017,
        Avdtp = 0x0019,
        Cmtp = 0x001B,
        UdiCPlain = 0x001D,
        McapControlChannel = 0x001E,
        McapDataChannel = 0x001F,
        L2cap = 0x0100,
    };

    enum ServiceClassUuid {
        ServiceDiscoveryServer = 0x1000,
        BrowseGroupDescriptor = 0x1001,
        PublicBrowseGroup = 0x1002,
        SerialPort = 0x1101,
        LANAccessUsingPPP = 0x1102,
        DialupNetworking = 0x1103,
        IrMCSync = 0x1104,
        ObexObjectPush = 0x1105,
        OBEXFileTransfer = 0x1106,
        IrMCSyncCommand = 0x1107,
        Headset = 0x1108,
        AudioSource = 0x110a,
        AudioSink = 0x110b,
        AV_RemoteControlTarget = 0x110c,
        AdvancedAudioDistribution = 0x110d,
        AV_RemoteControl = 0x110e,
        AV_RemoteControlController = 0x110f,
        HeadsetAG = 0x1112,
        PANU = 0x1115,
        NAP = 0x1116,
        GN = 0x1117,
        DirectPrinting = 0x1118,
        ReferencePrinting = 0x1119,
        ImagingResponder = 0x111b,
        ImagingAutomaticArchive = 0x111c,
        ImagingReferencedObjects = 0x111d,
        Handsfree = 0x111e,
        HandsfreeAudioGateway = 0x111f,
        DirectPrintingReferenceObjectsService = 0x1120,
        ReflectedUI = 0x1121,
        BasicPrinting = 0x1122,
        PrintingStatus = 0x1123,
        HumanInterfaceDeviceService = 0x1124,
        HardcopyCableReplacement = 0x1125,
        HCRPrint = 0x1126,
        HCRScan = 0x1127,
        SIMAccess = 0x112d,
        PhonebookAccessPCE = 0x112e,
        PhonebookAccessPSE = 0x112f,
        PhonebookAccess = 0x1130,
        HeadsetHS = 0x1131,
        MessageAccessServer = 0x1132,
        MessageNotificationServer = 0x1133,
        MessageAccessProfile = 0x1134,
        PnPInformation = 0x1135,
        GenericNetworking = 0x1201,
        GenericFileTransfer = 0x1202,
        GenericAudio = 0x1203,
        GenericTelephony = 0x1204,
        VideoSource = 0x1303,
        VideoSink = 0x1304,
        VideoDistribution = 0x1305,
        HDP = 0x1400,
        HDPSource = 0x1401,
        HDPSink = 0x1402
    };

    QBluetoothUuid();
    QBluetoothUuid(ProtocolUuid uuid);
    QBluetoothUuid(ServiceClassUuid uuid);
    explicit QBluetoothUuid(quint16 uuid);
    explicit QBluetoothUuid(quint32 uuid);
    explicit QBluetoothUuid(quint128 uuid);
    explicit QBluetoothUuid(const QString &uuid);
    QBluetoothUuid(const QBluetoothUuid &uuid);
    QBluetoothUuid(const QUuid &uuid);
    ~QBluetoothUuid();

    bool operator==(const QBluetoothUuid &other) const;

    int minimumSize() const;

    quint16 toUInt16(bool *ok = 0) const;
    quint32 toUInt32(bool *ok = 0) const;
    quint128 toUInt128() const;
};

inline QDebug operator<<(QDebug debug, const QBluetoothUuid &uuid)
{
    debug << uuid.toString();
    return debug;
}

QTM_END_NAMESPACE

Q_DECLARE_METATYPE(QtMobility::QBluetoothUuid)

QT_END_HEADER

#endif
