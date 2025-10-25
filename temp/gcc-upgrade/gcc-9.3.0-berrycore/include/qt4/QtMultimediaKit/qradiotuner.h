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

#ifndef QRADIOTUNER_H
#define QRADIOTUNER_H

#include <QtCore/qobject.h>

#include "qmediaobject.h"
#include "qmediaserviceprovider.h"
#include <qmediaenumdebug.h>

#include <QPair>

QT_BEGIN_NAMESPACE

class QRadioTunerPrivate;
class Q_MULTIMEDIA_EXPORT QRadioTuner : public QMediaObject
{
    Q_OBJECT
    Q_PROPERTY(State state READ state NOTIFY stateChanged)
    Q_PROPERTY(Band band READ band WRITE setBand NOTIFY bandChanged)
    Q_PROPERTY(int frequency READ frequency WRITE setFrequency NOTIFY frequencyChanged)
    Q_PROPERTY(bool stereo READ isStereo NOTIFY stereoStatusChanged)
    Q_PROPERTY(StereoMode stereoMode READ stereoMode WRITE setStereoMode)
    Q_PROPERTY(int signalStrength READ signalStrength NOTIFY signalStrengthChanged)
    Q_PROPERTY(int volume READ volume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(bool muted READ isMuted WRITE setMuted NOTIFY mutedChanged)
    Q_PROPERTY(bool searching READ isSearching NOTIFY searchingChanged)
    Q_ENUMS(State)
    Q_ENUMS(Band)
    Q_ENUMS(Error)
    Q_ENUMS(StereoMode)

public:
    enum State { ActiveState, StoppedState };
    enum Band { AM, FM, SW, LW, FM2 };
    enum Error { NoError, ResourceError, OpenError, OutOfRangeError };
    enum StereoMode { ForceStereo, ForceMono, Auto };

    QRadioTuner(QObject *parent = 0, QMediaServiceProvider *provider = QMediaServiceProvider::defaultServiceProvider());
    ~QRadioTuner();

    bool isAvailable() const;
    QtMultimediaKit::AvailabilityError availabilityError() const;

    State state() const;

    Band band() const;

    bool isBandSupported(Band b) const;

    int frequency() const;
    int frequencyStep(Band band) const;
    QPair<int,int> frequencyRange(Band band) const;

    bool isStereo() const;
    void setStereoMode(QRadioTuner::StereoMode mode);
    StereoMode stereoMode() const;

    int signalStrength() const;

    int volume() const;
    bool isMuted() const;

    bool isSearching() const;

    Error error() const;
    QString errorString() const;

public Q_SLOTS:
    void searchForward();
    void searchBackward();
    void cancelSearch();

    void setBand(Band band);
    void setFrequency(int frequency);

    void setVolume(int volume);
    void setMuted(bool muted);

    void start();
    void stop();

Q_SIGNALS:
    void stateChanged(QRadioTuner::State state);
    void bandChanged(QRadioTuner::Band band);
    void frequencyChanged(int frequency);
    void stereoStatusChanged(bool stereo);
    void searchingChanged(bool searching);
    void signalStrengthChanged(int signalStrength);
    void volumeChanged(int volume);
    void mutedChanged(bool muted);
    void error(QRadioTuner::Error error);

private:
    Q_DISABLE_COPY(QRadioTuner)
    Q_DECLARE_PRIVATE(QRadioTuner)
};

QT_END_NAMESPACE

Q_DECLARE_METATYPE(QRadioTuner::State)
Q_DECLARE_METATYPE(QRadioTuner::Band)
Q_DECLARE_METATYPE(QRadioTuner::Error)
Q_DECLARE_METATYPE(QRadioTuner::StereoMode)

Q_MEDIA_ENUM_DEBUG(QRadioTuner, State)
Q_MEDIA_ENUM_DEBUG(QRadioTuner, Band)
Q_MEDIA_ENUM_DEBUG(QRadioTuner, Error)
Q_MEDIA_ENUM_DEBUG(QRadioTuner, StereoMode)

#endif  // QRADIOPLAYER_H
