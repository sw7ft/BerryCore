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


#ifndef QMEDIASTREAMSCONTROL_H
#define QMEDIASTREAMSCONTROL_H

#include "qmediacontrol.h"
#include "qtmedianamespace.h"
#include "qmobilityglobal.h"
#include <qmediaenumdebug.h>

QT_BEGIN_NAMESPACE

class Q_MULTIMEDIA_EXPORT QMediaStreamsControl : public QMediaControl
{
    Q_OBJECT
    Q_ENUMS(SteamType)
public:
    enum StreamType { UnknownStream, VideoStream, AudioStream, SubPictureStream, DataStream };

    virtual ~QMediaStreamsControl();

    virtual int streamCount() = 0;
    virtual StreamType streamType(int streamNumber) = 0;

    virtual QVariant metaData(int streamNumber, QtMultimediaKit::MetaData key) = 0;

    virtual bool isActive(int streamNumber) = 0;
    virtual void setActive(int streamNumber, bool state) = 0;

Q_SIGNALS:
    void streamsChanged();
    void activeStreamsChanged();

protected:
    QMediaStreamsControl(QObject *parent = 0);
};

#define QMediaStreamsControl_iid "com.nokia.Qt.QMediaStreamsControl/1.0"
Q_MEDIA_DECLARE_CONTROL(QMediaStreamsControl, QMediaStreamsControl_iid)

QT_END_NAMESPACE

Q_DECLARE_METATYPE(QMediaStreamsControl::StreamType)

Q_MEDIA_ENUM_DEBUG(QMediaStreamsControl, StreamType)

#endif // QMEDIASTREAMSCONTROL_H

