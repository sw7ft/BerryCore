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

#ifndef QMEDIAENCODERSETTINGS_H
#define QMEDIAENCODERSETTINGS_H

#include <QtCore/qsharedpointer.h>
#include <QtCore/qstring.h>
#include <QtCore/qsize.h>
#include <qmobilityglobal.h>
#include "qtmedianamespace.h"

QT_BEGIN_NAMESPACE


class QAudioEncoderSettingsPrivate;
class Q_MULTIMEDIA_EXPORT QAudioEncoderSettings
{
public:
    QAudioEncoderSettings();
    QAudioEncoderSettings(const QAudioEncoderSettings& other);

    ~QAudioEncoderSettings();

    QAudioEncoderSettings& operator=(const QAudioEncoderSettings &other);
    bool operator==(const QAudioEncoderSettings &other) const;
    bool operator!=(const QAudioEncoderSettings &other) const;

    bool isNull() const;

    QtMultimediaKit::EncodingMode encodingMode() const;
    void setEncodingMode(QtMultimediaKit::EncodingMode);

    QString codec() const;
    void setCodec(const QString& codec);

    int bitRate() const;
    void setBitRate(int bitrate);

    int channelCount() const;
    void setChannelCount(int channels);

    int sampleRate() const;
    void setSampleRate(int rate);

    QtMultimediaKit::EncodingQuality quality() const;
    void setQuality(QtMultimediaKit::EncodingQuality quality);

private:
    QSharedDataPointer<QAudioEncoderSettingsPrivate> d;
};

class QVideoEncoderSettingsPrivate;
class Q_MULTIMEDIA_EXPORT QVideoEncoderSettings
{
public:
    QVideoEncoderSettings();
    QVideoEncoderSettings(const QVideoEncoderSettings& other);

    ~QVideoEncoderSettings();

    QVideoEncoderSettings& operator=(const QVideoEncoderSettings &other);
    bool operator==(const QVideoEncoderSettings &other) const;
    bool operator!=(const QVideoEncoderSettings &other) const;

    bool isNull() const;

    QtMultimediaKit::EncodingMode encodingMode() const;
    void setEncodingMode(QtMultimediaKit::EncodingMode);

    QString codec() const;
    void setCodec(const QString &);

    QSize resolution() const;
    void setResolution(const QSize &);
    void setResolution(int width, int height);

    qreal frameRate() const;
    void setFrameRate(qreal rate);

    int bitRate() const;
    void setBitRate(int bitrate);

    QtMultimediaKit::EncodingQuality quality() const;
    void setQuality(QtMultimediaKit::EncodingQuality quality);

private:
    QSharedDataPointer<QVideoEncoderSettingsPrivate> d;
};

class QImageEncoderSettingsPrivate;
class Q_MULTIMEDIA_EXPORT QImageEncoderSettings
{
public:
    QImageEncoderSettings();
    QImageEncoderSettings(const QImageEncoderSettings& other);

    ~QImageEncoderSettings();

    QImageEncoderSettings& operator=(const QImageEncoderSettings &other);
    bool operator==(const QImageEncoderSettings &other) const;
    bool operator!=(const QImageEncoderSettings &other) const;

    bool isNull() const;

    QString codec() const;
    void setCodec(const QString &);

    QSize resolution() const;
    void setResolution(const QSize &);
    void setResolution(int width, int height);

    QtMultimediaKit::EncodingQuality quality() const;
    void setQuality(QtMultimediaKit::EncodingQuality quality);

private:
    QSharedDataPointer<QImageEncoderSettingsPrivate> d;
};

QT_END_NAMESPACE

#endif
