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

#ifndef QNDEFMESSAGE_H
#define QNDEFMESSAGE_H

#include "nfc_ndef_global.h"
#include "qndefrecord.h"

#include <QtCore/QList>
#include <QtCore/QVector>
#include <QtCore/QSet>

namespace QtMobilitySubset {

class NFC_NDEFSHARED_EXPORT QNdefMessage : public QList<QNdefRecord>
{
public:
    inline QNdefMessage() { }
    inline explicit QNdefMessage(const QNdefRecord &record) { append(record); }
    inline QNdefMessage(const QNdefMessage &message) : QList<QNdefRecord>(message) { }
    inline QNdefMessage(const QList<QNdefRecord> &records) : QList<QNdefRecord>(records) { }

    bool operator==(const QNdefMessage &other) const;

    QByteArray toByteArray() const;

    static QNdefMessage fromByteArray(const QByteArray &message);
};

} // namespace QtMobilitySubset

#endif // QNDEFMESSAGE_H
