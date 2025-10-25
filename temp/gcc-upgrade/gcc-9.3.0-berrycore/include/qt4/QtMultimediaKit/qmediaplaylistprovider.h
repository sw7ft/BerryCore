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

#ifndef QMEDIAPLAYLISTPROVIDER_H
#define QMEDIAPLAYLISTPROVIDER_H

#include <QObject>

#include "qmediacontent.h"
#include "qmediaplaylist.h"

QT_BEGIN_NAMESPACE
class QString;
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE

class QMediaPlaylistProviderPrivate;
class Q_MULTIMEDIA_EXPORT QMediaPlaylistProvider : public QObject
{
Q_OBJECT
public:
    QMediaPlaylistProvider(QObject *parent=0);
    virtual ~QMediaPlaylistProvider();

    virtual bool load(const QUrl &location, const char *format = 0);
    virtual bool load(QIODevice * device, const char *format = 0);
    virtual bool save(const QUrl &location, const char *format = 0);
    virtual bool save(QIODevice * device, const char *format);

    virtual int mediaCount() const = 0;
    virtual QMediaContent media(int index) const = 0;

    virtual bool isReadOnly() const;

    virtual bool addMedia(const QMediaContent &content);
    virtual bool addMedia(const QList<QMediaContent> &contentList);
    virtual bool insertMedia(int index, const QMediaContent &content);
    virtual bool insertMedia(int index, const QList<QMediaContent> &content);
    virtual bool removeMedia(int pos);
    virtual bool removeMedia(int start, int end);
    virtual bool clear();

public Q_SLOTS:
    virtual void shuffle();

Q_SIGNALS:
    void mediaAboutToBeInserted(int start, int end);
    void mediaInserted(int start, int end);

    void mediaAboutToBeRemoved(int start, int end);
    void mediaRemoved(int start, int end);

    void mediaChanged(int start, int end);

    void loaded();
    void loadFailed(QMediaPlaylist::Error, const QString& errorMessage);

protected:
    QMediaPlaylistProviderPrivate *d_ptr;
    QMediaPlaylistProvider(QMediaPlaylistProviderPrivate &dd, QObject *parent);

private:
    Q_DECLARE_PRIVATE(QMediaPlaylistProvider)
};

QT_END_NAMESPACE

#endif // QMEDIAPLAYLISTPROVIDER_H
