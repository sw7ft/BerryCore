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

#ifndef QRADIOTUNERCONTROL_H
#define QRADIOTUNERCONTROL_H

#include "qmediacontrol.h"
#include "qradiotuner.h"

QT_BEGIN_NAMESPACE

class Q_MULTIMEDIA_EXPORT QRadioTunerControl : public QMediaControl
{
    Q_OBJECT

public:
    ~QRadioTunerControl();

    virtual bool isAvailable() const = 0;
    virtual QtMultimediaKit::AvailabilityError availabilityError() const = 0;

    virtual QRadioTuner::State state() const = 0;

    virtual QRadioTuner::Band band() const = 0;
    virtual void setBand(QRadioTuner::Band b) = 0;
    virtual bool isBandSupported(QRadioTuner::Band b) const = 0;

    virtual int frequency() const = 0;
    virtual int frequencyStep(QRadioTuner::Band b) const = 0;
    virtual QPair<int,int> frequencyRange(QRadioTuner::Band b) const = 0;
    virtual void setFrequency(int frequency) = 0;

    virtual bool isStereo() const = 0;
    virtual QRadioTuner::StereoMode stereoMode() const = 0;
    virtual void setStereoMode(QRadioTuner::StereoMode mode) = 0;

    virtual int signalStrength() const = 0;

    virtual int volume() const = 0;
    virtual void setVolume(int volume) = 0;

    virtual bool isMuted() const = 0;
    virtual void setMuted(bool muted) = 0;

    virtual bool isSearching() const = 0;

    virtual void searchForward() = 0;
    virtual void searchBackward() = 0;
    virtual void cancelSearch() = 0;

    virtual void start() = 0;
    virtual void stop() = 0;

    virtual QRadioTuner::Error error() const = 0;
    virtual QString errorString() const = 0;

Q_SIGNALS:
    void stateChanged(QRadioTuner::State state);
    void bandChanged(QRadioTuner::Band band);
    void frequencyChanged(int frequency);
    void stereoStatusChanged(bool stereo);
    void searchingChanged(bool stereo);
    void signalStrengthChanged(int signalStrength);
    void volumeChanged(int volume);
    void mutedChanged(bool muted);
    void error(QRadioTuner::Error err);

protected:
    QRadioTunerControl(QObject *parent = 0);
};

#define QRadioTunerControl_iid "com.nokia.Qt.QRadioTunerControl/1.0"
Q_MEDIA_DECLARE_CONTROL(QRadioTunerControl, QRadioTunerControl_iid)

QT_END_NAMESPACE

#endif  // QRADIOTUNERCONTROL_H
