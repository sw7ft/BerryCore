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

#ifndef QGRAPHICSVIDEOITEM_H
#define QGRAPHICSVIDEOITEM_H

#include <QtGui/qgraphicsitem.h>

#include <qvideowidget.h>
#include <qmediabindableinterface.h>

QT_BEGIN_NAMESPACE
class QVideoSurfaceFormat;
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE

class QGraphicsVideoItemPrivate;
class Q_MULTIMEDIA_EXPORT QGraphicsVideoItem : public QGraphicsObject, public QMediaBindableInterface
{
    Q_OBJECT
    Q_INTERFACES(QMediaBindableInterface)
    Q_PROPERTY(QMediaObject* mediaObject READ mediaObject WRITE setMediaObject)
    Q_PROPERTY(Qt::AspectRatioMode aspectRatioMode READ aspectRatioMode WRITE setAspectRatioMode)
    Q_PROPERTY(QPointF offset READ offset WRITE setOffset)
    Q_PROPERTY(QSizeF size READ size WRITE setSize)
    Q_PROPERTY(QSizeF nativeSize READ nativeSize NOTIFY nativeSizeChanged)
public:
    QGraphicsVideoItem(QGraphicsItem *parent = 0);
    ~QGraphicsVideoItem();

    QMediaObject *mediaObject() const;    

    Qt::AspectRatioMode aspectRatioMode() const;
    void setAspectRatioMode(Qt::AspectRatioMode mode);

    QPointF offset() const;
    void setOffset(const QPointF &offset);

    QSizeF size() const;
    void setSize(const QSizeF &size);

    QSizeF nativeSize() const;

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

Q_SIGNALS:
    void nativeSizeChanged(const QSizeF &size);

protected:
    void timerEvent(QTimerEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    bool setMediaObject(QMediaObject *object);

    QGraphicsVideoItemPrivate *d_ptr;

private:
    Q_DECLARE_PRIVATE(QGraphicsVideoItem)
    Q_PRIVATE_SLOT(d_func(), void _q_present())
    Q_PRIVATE_SLOT(d_func(), void _q_updateNativeSize())
    Q_PRIVATE_SLOT(d_func(), void _q_serviceDestroyed())
};

QT_END_NAMESPACE

#endif
