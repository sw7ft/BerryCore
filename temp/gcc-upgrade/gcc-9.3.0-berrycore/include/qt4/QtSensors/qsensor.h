/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
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

#ifndef QSENSOR_H
#define QSENSOR_H

#include <qmobilityglobal.h>
#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QMetaType>
#include <QtCore/QVariant>
#include <QtCore/QPair>

QTM_BEGIN_NAMESPACE

class QSensorPrivate;
class QSensorBackend;
class QSensorReading;
class QSensorReadingPrivate;
class QSensorFilter;

#ifdef Q_QDOC
typedef quint64 qtimestamp;
#else
class qtimestamp
{
public:
    qtimestamp() : value() {}
    qtimestamp(quint64 timestamp) : value(timestamp) {}
    operator quint64() const { return value; }
private:
    quint64 value;
};
#endif

typedef QPair<int,int> qrange;
typedef QList<qrange> qrangelist;
struct qoutputrange
{
    qreal minimum;
    qreal maximum;
    qreal accuracy;
};
typedef QList<qoutputrange> qoutputrangelist;

class Q_SENSORS_EXPORT QSensor : public QObject
{
    friend class QSensorBackend;

    Q_OBJECT
    Q_PROPERTY(QByteArray sensorid READ identifier WRITE setIdentifier)
    Q_PROPERTY(QByteArray type READ type)
    Q_PROPERTY(bool connectedToBackend READ isConnectedToBackend)
    Q_PROPERTY(QtMobility::qrangelist availableDataRates READ availableDataRates)
    Q_PROPERTY(int dataRate READ dataRate WRITE setDataRate NOTIFY dataRateChanged)
    Q_PROPERTY(QSensorReading* reading READ reading NOTIFY readingChanged)
    Q_PROPERTY(bool busy READ isBusy)
    Q_PROPERTY(bool active READ isActive WRITE setActive NOTIFY activeChanged)
    Q_PROPERTY(QtMobility::qoutputrangelist outputRanges READ outputRanges)
    Q_PROPERTY(int outputRange READ outputRange WRITE setOutputRange)
    Q_PROPERTY(QString description READ description)
    Q_PROPERTY(int error READ error NOTIFY sensorError)
    Q_PROPERTY(bool alwaysOn READ isAlwaysOn WRITE setAlwaysOn NOTIFY alwaysOnChanged)
    Q_PROPERTY(bool skipDuplicates READ skipDuplicates WRITE setSkipDuplicates NOTIFY skipDuplicatesChanged)
    Q_PROPERTY(int maxBufferSize READ maxBufferSize NOTIFY maxBufferSizeChanged)
    Q_PROPERTY(int efficientBufferSize READ efficientBufferSize NOTIFY efficientBufferSizeChanged)
    Q_PROPERTY(int bufferSize READ bufferSize WRITE setBufferSize NOTIFY bufferSizeChanged)
public:
    explicit QSensor(const QByteArray &type, QObject *parent = 0);
    virtual ~QSensor();

    QByteArray identifier() const;
    void setIdentifier(const QByteArray &identifier);

    QByteArray type() const;

    Q_INVOKABLE bool connectToBackend();
    bool isConnectedToBackend() const;

    bool isBusy() const;

    void setActive(bool active);
    bool isActive() const;

    bool isAlwaysOn() const;
    void setAlwaysOn(bool alwaysOn);

    bool skipDuplicates() const;
    void setSkipDuplicates(bool skipDuplicates);

    qrangelist availableDataRates() const;
    int dataRate() const;
    void setDataRate(int rate);

    qoutputrangelist outputRanges() const;
    int outputRange() const;
    void setOutputRange(int index);

    QString description() const;
    int error() const;

    // Filters modify the reading
    void addFilter(QSensorFilter *filter);
    void removeFilter(QSensorFilter *filter);
    QList<QSensorFilter*> filters() const;

    // The readings are exposed via this object
    QSensorReading *reading() const;

    // Information about available sensors
    // These functions are implemented in qsensormanager.cpp
    static QList<QByteArray> sensorTypes();
    static QList<QByteArray> sensorsForType(const QByteArray &type);
    static QByteArray defaultSensorForType(const QByteArray &type);

    int maxBufferSize() const;
    void setMaxBufferSize(int maxBufferSize);

    int efficientBufferSize() const;
    void setEfficientBufferSize(int efficientBufferSize);

    int bufferSize() const;
    void setBufferSize(int bufferSize);

public Q_SLOTS:
    // Start receiving values from the sensor
    bool start();

    // Stop receiving values from the sensor
    void stop();

Q_SIGNALS:
    void busyChanged();
    void activeChanged();
    void readingChanged();
    void sensorError(int error);
    void availableSensorsChanged();
    void alwaysOnChanged();
    void skipDuplicatesChanged(bool skipDuplicates);
    void dataRateChanged();
    void maxBufferSizeChanged(int maxBufferSize);
    void efficientBufferSizeChanged(int efficientBufferSize);
    void bufferSizeChanged(int bufferSize);

protected:
    QSensor(const QByteArray &type, QSensorPrivate *dd, QObject* parent = 0);
    // called by the back end
    QSensorPrivate *d_func() const { return d.data(); }

private:
    void registerInstance();

    friend class QSensorPrivate;
    QScopedPointer<QSensorPrivate> d;
    Q_DISABLE_COPY(QSensor)
};

class Q_SENSORS_EXPORT QSensorFilter
{
    friend class QSensor;
public:
    virtual bool filter(QSensorReading *reading) = 0;
protected:
    QSensorFilter();
    ~QSensorFilter();
    virtual void setSensor(QSensor *sensor);
    QSensor *m_sensor;
};

class Q_SENSORS_EXPORT QSensorReading : public QObject
{
    friend class QSensorBackend;

    Q_OBJECT
    Q_PROPERTY(QtMobility::qtimestamp timestamp READ timestamp)
public:
    virtual ~QSensorReading();

    qtimestamp timestamp() const;
    void setTimestamp(qtimestamp timestamp);

    // Access properties of sub-classes by numeric index
    // For name-based access use QObject::property()
    int valueCount() const;
    QVariant value(int index) const;

protected:
    explicit QSensorReading(QObject *parent, QSensorReadingPrivate *d);
    QScopedPointer<QSensorReadingPrivate> *d_ptr() { return &d; }
    virtual void copyValuesFrom(QSensorReading *other);

private:
    QScopedPointer<QSensorReadingPrivate> d;
    Q_DISABLE_COPY(QSensorReading)
};

#define DECLARE_READING(classname)\
        DECLARE_READING_D(classname, classname ## Private)

#define DECLARE_READING_D(classname, pclassname)\
    public:\
        classname(QObject *parent = 0);\
        virtual ~classname();\
        void copyValuesFrom(QSensorReading *other);\
    private:\
        QScopedPointer<pclassname> d;

#define IMPLEMENT_READING(classname)\
        IMPLEMENT_READING_D(classname, classname ## Private)

#define IMPLEMENT_READING_D(classname, pclassname)\
    classname::classname(QObject *parent)\
        : QSensorReading(parent, 0)\
        , d(new pclassname)\
        {}\
    classname::~classname() {}\
    void classname::copyValuesFrom(QSensorReading *_other)\
    {\
        /* No need to verify types, only called by QSensorBackend */\
        classname *other = static_cast<classname *>(_other);\
        pclassname *my_ptr = d.data();\
        pclassname *other_ptr = other->d.data();\
        /* Do a direct copy of the private class */\
        *(my_ptr) = *(other_ptr);\
        /* We need to copy the parent too */\
        QSensorReading::copyValuesFrom(_other);\
    }

QTM_END_NAMESPACE

Q_DECLARE_METATYPE(QtMobility::qtimestamp)
Q_DECLARE_METATYPE(QtMobility::qrange)
Q_DECLARE_METATYPE(QtMobility::qrangelist)
Q_DECLARE_METATYPE(QtMobility::qoutputrangelist)

#endif

