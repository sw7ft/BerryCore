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

#ifndef QMEDIARECORDERCONTROL_H
#define QMEDIARECORDERCONTROL_H

#include "qmediacontrol.h"
#include "qmediarecorder.h"

QT_BEGIN_NAMESPACE
class QUrl;
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE

class Q_MULTIMEDIA_EXPORT QMediaRecorderControl : public QMediaControl
{
    Q_OBJECT

public:
    virtual ~QMediaRecorderControl();

    virtual QUrl outputLocation() const = 0;
    virtual bool setOutputLocation(const QUrl &location) = 0;

    virtual QMediaRecorder::State state() const = 0;

    virtual qint64 duration() const = 0;

    virtual bool isMuted() const = 0;

    virtual void applySettings() = 0;

Q_SIGNALS:
    void stateChanged(QMediaRecorder::State state);
    void durationChanged(qint64 position);
    void mutedChanged(bool muted);
    void error(int error, const QString &errorString);

public Q_SLOTS:
    virtual void record() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;
    virtual void setMuted(bool muted) = 0;

protected:
    QMediaRecorderControl(QObject* parent = 0);
};

#define QMediaRecorderControl_iid "com.nokia.Qt.QMediaRecorderControl/1.0"
Q_MEDIA_DECLARE_CONTROL(QMediaRecorderControl, QMediaRecorderControl_iid)

QT_END_NAMESPACE

#endif
