/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */
//! @cond PRIVATE
#ifndef BB_SYSTEM_CONTEXTEVENT_HPP
#define BB_SYSTEM_CONTEXTEVENT_HPP

#include <bb/system/Global>
#include <bb/system/ContextActivityState>
#include <bb/system/ContextClassification>

#include <QString>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace system
{

class ContextEventPrivate;

/*!
 * @headerfile ContextEvent.hpp <bb/system/ContextEvent>
 *
 * @brief A class containing zero or more key-value pairs for use in the Context Collection Library.
 * 
 * @details All values are converted to a @c QString before being stored.  In addition, values are classified
 * using the categories listed in @c ContextClassification, which can be used to
 * anonymize information that can personally identify a user.
 *
 * @xmlonly
 * <apigrouping group="Platform/Context collector"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 */
class BB_SYSTEM_EXPORT ContextEvent : public QObject
{
    Q_OBJECT

public:
    /*!
     * @brief Constructs a @c ContextEvent object.
     *
     * @param parent If not @c 0, the supplied parent will be responsible for deleting this instance.
     */
    explicit ContextEvent(QObject *parent = 0);

    /*!
     * @brief Destroys this @c ContextEvent object.
     */
    virtual ~ContextEvent();

    /*!
     * @brief Inserts a key-value pair to this object.
     *
     * @details If a pair with the supplied key already exists, the value will be overwritten.
     *
     * The value is classified as @c ContextClassification::Public.
     *
     * @param key The key for the pair being added to the collection.  The key should not be empty.
     * @param value A Boolean value for the pair, which will be converted to a @c QString with a value
     * of @c "true" or @c "false".
     */
    Q_INVOKABLE void insert(const QString &key, bool value);

    /*!
     * @brief Inserts a key-value pair to this object.
     *
     * @details If a pair with the supplied key already exists, the value will be overwritten.
     *
     * The value is classified as @c ContextClassification::Public.
     *
     * @param key The key for the pair being added to the collection.  The key should not be empty.
     * @param value An integer value for the pair, which will be converted to a @c QString.
     */
    Q_INVOKABLE void insert(const QString &key, int value);

    /*!
     * @brief Inserts a key-value pair to this object.
     *
     * @details If a pair with the supplied key already exists, the value will be overwritten.
     *
     * The value is classified as @c ContextClassification::Public.
     *
     * @param key The key for the pair being added to the collection.  The key should not be empty.
     * @param value A double value for the pair, which will be converted to a @c QString.
     * @param precision The number of digits after the decimal point to maintain in the @c QString value.
     */
    Q_INVOKABLE void insert(const QString &key, double value, int precision);

    /*!
     * @brief Inserts a key-value pair to this object.
     *
     * @details If a pair with the supplied key already exists, the value will be overwritten.
     *
     * The value is classified as @c ContextClassification::Public.
     *
     * @param key The key for the pair being added to the collection.  The key should not be empty.
     * @param value A @c QString value for the pair.
     */
    Q_INVOKABLE void insert(const QString &key, const QString &value);

    /*!
     * @brief Inserts a key-value pair to this object.
     *
     * @details If a pair with the supplied key already exists, the value will be overwritten.
     *
     * @param key The key for the pair being added to the collection.  The key should not be empty.
     * @param value A @c QString value for the pair.
     * @param classification The classification of the inserted item. See @c ContextClassification
     * for the list of classifications.
     */
    Q_INVOKABLE void insert(const QString &key, const QString &value, bb::system::ContextClassification::Type classification);

    /*!
     * @brief Inserts a corporate liable timestamp in the format "%Y/%m/%d %H:%M:%S"
     *
     * @details If a pair with the supplied key already exists, the value will be overwritten.
     *
     * @param key The key for the pair being added to the collection.  The key should not be empty.
     * @param timestamp A @c QDateTime containing the timestamp.
     */
    Q_INVOKABLE void insertCorporateLiableTimestamp(const QString &key, QDateTime& timestamp);

    /*!
     * @brief Removes a key-value pair from this object.
     *
     * @param key The key of the pair to be removed.
     */
    Q_INVOKABLE void remove(const QString &key);

    /*!
     * @brief Clears all key-value pairs in this object.
     */
    Q_INVOKABLE void clear();

protected:
//! @cond PRIVATE
    Q_INVOKABLE void insert(const QString &key, const QString &value, int classification);
//! @endcond

private:
    //! @cond PRIVATE
    Q_DECLARE_PRIVATE(ContextEvent)
    Q_DISABLE_COPY(ContextEvent)
    QScopedPointer<ContextEventPrivate> const d_ptr;
    //! @endcond
};

} // namespace system
} // namespace bb

QML_DECLARE_TYPE(bb::system::ContextEvent)

#endif // BB_SYSTEM_CONTEXTEVENT_HPP
//! @endcond
