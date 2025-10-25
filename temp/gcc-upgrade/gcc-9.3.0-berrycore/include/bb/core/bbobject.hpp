/**
 * @copyright
 * Copyright Research In Motion Limited, 2011-2011
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_BBOBJECT_HPP
#define BB_BBOBJECT_HPP

#include <bb/Global>
#include <QtCore/QObject>
#include <QtCore/QScopedPointer>

namespace bb
{
class BbObjectPrivate;
class DLL_PUBLIC BbObject : public QObject
{
    Q_OBJECT
public:
    virtual ~BbObject();
protected:
    explicit BbObject(QObject *parent = 0);
    explicit BbObject(BbObjectPrivate *objectPrivate, QObject *parent = 0);
    QScopedPointer<BbObjectPrivate> d_ptr;
private:
    Q_DISABLE_COPY(BbObject)
    Q_DECLARE_PRIVATE(BbObject)
};

} // namespace bb

#endif // BB_BBOBJECT_HPP
