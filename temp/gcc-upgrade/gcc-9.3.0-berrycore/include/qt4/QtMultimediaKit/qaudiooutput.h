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


#ifndef QAUDIOOUTPUT_H
#define QAUDIOOUTPUT_H

#include <QtCore/qiodevice.h>

#include <qmobilityglobal.h>
#include <qtmedianamespace.h>

#include <qaudio.h>
#include <qaudioformat.h>
#include <qaudiodeviceinfo.h>


QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE


class QAbstractAudioOutput;

class Q_MULTIMEDIA_EXPORT QAudioOutput : public QObject
{
    Q_OBJECT

public:
    explicit QAudioOutput(const QAudioFormat &format = QAudioFormat(), QObject *parent = 0);
    explicit QAudioOutput(const QAudioDeviceInfo &audioDeviceInfo, const QAudioFormat &format = QAudioFormat(), QObject *parent = 0);
    ~QAudioOutput();

    QAudioFormat format() const;

    void start(QIODevice *device);
    QIODevice* start();

    void stop();
    void reset();
    void suspend();
    void resume();

    void setBufferSize(int bytes);
    int bufferSize() const;

    int bytesFree() const;
    int periodSize() const;

    void setNotifyInterval(int milliSeconds);
    int notifyInterval() const;

    qint64 processedUSecs() const;
    qint64 elapsedUSecs() const;

    QAudio::Error error() const;
    QAudio::State state() const;

Q_SIGNALS:
    void stateChanged(QAudio::State);
    void notify();

private:
    Q_DISABLE_COPY(QAudioOutput)

    QAbstractAudioOutput* d;
};

QT_END_NAMESPACE

QT_END_HEADER

#endif // QAUDIOOUTPUT_H
