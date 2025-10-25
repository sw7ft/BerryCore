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

#ifndef QDECLARATIVENDEFRECORD_P_H
#define QDECLARATIVENDEFRECORD_P_H

#include <QtCore/QObject>
#include <QtCore/QMetaType>

#include <qndefrecord.h>

QT_BEGIN_HEADER

QTM_BEGIN_NAMESPACE

class QDeclarativeNdefRecordPrivate;

class Q_CONNECTIVITY_EXPORT QDeclarativeNdefRecord : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QDeclarativeNdefRecord)

    Q_PROPERTY(QString recordType READ recordType WRITE setRecordType NOTIFY recordTypeChanged)

public:
    explicit QDeclarativeNdefRecord(QObject *parent = 0);
    explicit QDeclarativeNdefRecord(const QNdefRecord &record, QObject *parent = 0);

    QString recordType() const;
    void setRecordType(const QString &t);

    QNdefRecord record() const;
    void setRecord(const QNdefRecord &record);

Q_SIGNALS:
    void recordTypeChanged();

private:
    QDeclarativeNdefRecordPrivate *d_ptr;
};

void Q_CONNECTIVITY_EXPORT qRegisterNdefRecordTypeHelper(const QMetaObject *metaObject,
                                                         QNdefRecord::TypeNameFormat typeNameFormat,
                                                         const QByteArray &type);

Q_CONNECTIVITY_EXPORT QDeclarativeNdefRecord *qNewDeclarativeNdefRecordForNdefRecord(const QNdefRecord &record);

template<typename T>
bool qRegisterNdefRecordType(QNdefRecord::TypeNameFormat typeNameFormat, const QByteArray &type)
{
    qRegisterNdefRecordTypeHelper(&T::staticMetaObject, typeNameFormat, type);
    return true;
}

#define Q_DECLARE_NDEFRECORD(className, typeNameFormat, type) \
static bool _q_##className##_registered = qRegisterNdefRecordType<className>(typeNameFormat, type);

QTM_END_NAMESPACE

QT_END_HEADER

#endif // QDECLARATIVENDEFRECORD_P_H
