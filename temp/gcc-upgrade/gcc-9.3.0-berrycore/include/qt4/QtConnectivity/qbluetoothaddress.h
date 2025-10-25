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

#ifndef QBLUETOOTHADDRESS_H
#define QBLUETOOTHADDRESS_H

#include <qmobilityglobal.h>

#include <QtCore/QByteArray>
#include <QtCore/QString>
#include <QtCore/QMetaType>

QT_BEGIN_HEADER

QTM_BEGIN_NAMESPACE

class QBluetoothAddressPrivate;

class Q_CONNECTIVITY_EXPORT QBluetoothAddress
{
public:
    QBluetoothAddress();
    explicit QBluetoothAddress(quint64 address);
    explicit QBluetoothAddress(const QString &address);
    QBluetoothAddress(const QBluetoothAddress &other);

    /* when compiling with Winscw with VC2008 it still creates 
     * a symbol for the destructor and all sorts of problems
     * could then arrise.  For now, in the emulator, we leak
     * memory, I don't know a better solution
     */
#ifndef __WINS__
    inline ~QBluetoothAddress() {
        if(d_ptr) {
            *this = QBluetoothAddress();
        }
    }
#endif 

    QBluetoothAddress &operator=(const QBluetoothAddress &other);

    bool isNull() const;

    void clear();

    bool operator<(const QBluetoothAddress &other) const;
    bool operator==(const QBluetoothAddress &other) const;
    inline bool operator!=(const QBluetoothAddress &other) const { return !operator==(other); }

    quint64 toUInt64() const;
    QString toString() const;

private:
    Q_DECLARE_PRIVATE(QBluetoothAddress)
    QBluetoothAddressPrivate *d_ptr;
};

QTM_END_NAMESPACE

Q_DECLARE_METATYPE(QtMobility::QBluetoothAddress)

QT_END_HEADER

#endif
