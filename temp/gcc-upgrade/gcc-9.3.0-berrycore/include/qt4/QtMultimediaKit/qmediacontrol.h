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

#ifndef QABSTRACTMEDIACONTROL_H
#define QABSTRACTMEDIACONTROL_H

#include <qmobilityglobal.h>

#include <QtCore/qobject.h>
#include <QtCore/qstring.h>
#include <QtCore/qvariant.h>


QT_BEGIN_NAMESPACE

class QMediaControlPrivate;
class Q_MULTIMEDIA_EXPORT QMediaControl : public QObject
{
    Q_OBJECT

public:
    ~QMediaControl();

protected:
    QMediaControl(QObject *parent = 0);
    QMediaControl(QMediaControlPrivate &dd, QObject *parent = 0);

    QMediaControlPrivate *d_ptr;

private:
    Q_DECLARE_PRIVATE(QMediaControl)
};

template <typename T> const char *qmediacontrol_iid() { return 0; }

#define Q_MEDIA_DECLARE_CONTROL(Class, IId) \
    template <> inline const char *qmediacontrol_iid<Class *>() { return IId; }

QT_END_NAMESPACE

#endif  // QABSTRACTMEDIACONTROL_H
