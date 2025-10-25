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

#ifndef QMEDIACONTENT_H
#define QMEDIACONTENT_H

#include <QtCore/qmetatype.h>
#include <QtCore/qshareddata.h>

#include "qmediaresource.h"

#include <qmobilityglobal.h>


QT_BEGIN_NAMESPACE

class QMediaContentPrivate;
class Q_MULTIMEDIA_EXPORT QMediaContent
{
public:
    QMediaContent();
    QMediaContent(const QUrl &contentUrl);
    QMediaContent(const QNetworkRequest &contentRequest);
    QMediaContent(const QMediaResource &contentResource);
    QMediaContent(const QMediaResourceList &resources);
    QMediaContent(const QMediaContent &other);
    ~QMediaContent();

    QMediaContent& operator=(const QMediaContent &other);

    bool operator==(const QMediaContent &other) const;
    bool operator!=(const QMediaContent &other) const;

    bool isNull() const;

    QUrl canonicalUrl() const;
    QNetworkRequest canonicalRequest() const;
    QMediaResource canonicalResource() const;

    QMediaResourceList resources() const;

private:
    QSharedDataPointer<QMediaContentPrivate> d;
};

QT_END_NAMESPACE

Q_DECLARE_METATYPE(QMediaContent)



#endif  // QMEDIACONTENT_H
