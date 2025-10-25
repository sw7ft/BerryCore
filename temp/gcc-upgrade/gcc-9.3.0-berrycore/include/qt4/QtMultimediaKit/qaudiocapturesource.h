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

#ifndef QAUDIOCAPTURESOURCE_H
#define QAUDIOCAPTURESOURCE_H

#include <QtCore/qstringlist.h>
#include <QtCore/qpair.h>
#include <QtCore/qsize.h>

#include <qaudioformat.h>

#include "qmediarecorder.h"
#include "qmediacontrol.h"
#include "qmediaobject.h"
#include "qmediaservice.h"

#include "qmediaserviceprovider.h"

QT_BEGIN_NAMESPACE

class QAudioCaptureSourcePrivate;

class Q_MULTIMEDIA_EXPORT QAudioCaptureSource : public QMediaObject
{
    Q_OBJECT

public:
    QAudioCaptureSource(QObject *parent = 0, QMediaServiceProvider *service = QMediaServiceProvider::defaultServiceProvider());
    ~QAudioCaptureSource();

    bool isAvailable() const;
    QtMultimediaKit::AvailabilityError availabilityError() const;

    QList<QString> audioInputs() const;

    QString audioDescription(const QString& name) const;
    QString defaultAudioInput() const;
    QString activeAudioInput() const;

public Q_SLOTS:
    void setAudioInput(const QString& name);

Q_SIGNALS:
    void activeAudioInputChanged(const QString& name);
    void availableAudioInputsChanged();

private Q_SLOTS:
    void statusChanged();

private:
    Q_DECLARE_PRIVATE(QAudioCaptureSource)
};

QT_END_NAMESPACE

#endif  // QAUDIOCAPTURESOURCE_H
