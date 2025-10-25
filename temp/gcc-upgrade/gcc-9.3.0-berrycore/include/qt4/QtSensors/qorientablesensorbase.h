/****************************************************************************
**
** Copyright (C) 2012 Research In Motion <blackberry-qt@qnx.com>
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Mobility Components.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QORIENTABLESENSORBASE_H
#define QORIENTABLESENSORBASE_H

#include <qmobilityglobal.h>

#if defined(Q_OS_BLACKBERRY)

QTM_BEGIN_NAMESPACE

class QOrientableSensorBasePrivate;

class Q_SENSORS_EXPORT QOrientableSensorBase
{
public:
    enum AxesOrientationMode {
        FixedOrientation,
        AutomaticOrientation,
        UserOrientation
    };

#ifdef Q_QDOC
    Q_PROPERTY(AxesOrientationMode axesOrientationMode READ axesOrientationMode WRITE setAxesOrientationMode NOTIFY axesOrientationModeChanged)
    Q_PROPERTY(int currentOrientation READ currentOrientation NOTIFY currentOrientationChanged)
    Q_PROPERTY(int userOrientation READ userOrientation WRITE setUserOrientation NOTIFY userOrientationChanged)
#endif

    QOrientableSensorBase();
    virtual ~QOrientableSensorBase();

    AxesOrientationMode axesOrientationMode() const;
    void setAxesOrientationMode(AxesOrientationMode axesOrientationMode);

    int currentOrientation() const;
    void setCurrentOrientation(int currentOrientation);

    int userOrientation() const;
    void setUserOrientation(int userOrientation);

protected:
    // Signals which will be implemented by moc in the subclass
#ifdef Q_QDOC
Q_SIGNALS:
    void axesOrientationModeChanged(AxesOrientationMode axesOrientationMode);
    void currentOrientationChanged(int currentOrientation);
    void userOrientationChanged(int userOrientation);
#else
    virtual void axesOrientationModeChanged(AxesOrientationMode axesOrientationMode) = 0;
    virtual void currentOrientationChanged(int currentOrientation) = 0;
    virtual void userOrientationChanged(int userOrientation) = 0;
#endif

private:
    QOrientableSensorBasePrivate *d;
    friend class QOrientableSensorBasePrivate;
};

QTM_END_NAMESPACE

#endif // Q_OS_BLACKBERRY

#endif // QORIENTABLESENSORBASE_H
