/*!
 * @copyright
 * Copyright (C) 2013 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_CASCADES_DATAMANAGER_DATAITEM_HPP_
#define BB_CASCADES_DATAMANAGER_DATAITEM_HPP_

#include <bb/cascades/datamanager/Global>
#include <bb/cascades/datamanager/DataRevision>
#include <QDebug>
#include <QSharedDataPointer>
#include <QString>
#include <QVariant>

namespace bb
{
namespace cascades
{
namespace datamanager
{

class DataItemPrivate;

/*!
 * @headerfile DataItem.hpp <bb/cascades/datamanager/DataItem>
 *
 * @brief This class represents a single item of data in a result set.
 *
 * This is a Qt value object which supports implicit data sharing.
 *
 * @xmlonly
 * <apigrouping group="Data Management/Large Data Sets"/>
 * <library name="bbcascadesdatamanager"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_CASCADES_DATAMANAGER_EXPORT DataItem
{
public:
    /*!
     * @brief Constructs a @c DataItem given an ID, revision, and payload.
     *
     * @param keyId The ID for this item.
     * @param revision The revision for this item.
     * @param payload The data payload for this item.
     *
     * @since BlackBerry 10.2.0
     */
    DataItem(const QString &keyId, const DataRevision& revision, const QVariant& payload);

    /*!
     * @brief Constructs a @c DataItem.
     *
     * @since BlackBerry 10.2.0
     */
    DataItem();

    /*!
     * @brief Copy constructor.
     *
     * This function constructs a @c DataItem containing exactly the same values
     * as the provided @c %DataItem.
     *
     * @param other The @c DataItem object to copy. This follows the rules of implicit sharing.
     *
     * @since BlackBerry 10.2.0
     */
    DataItem(const DataItem& other);

    /*!
     * @brief Assignment operator.
     *
     * This function assigns values from the given @c DataItem to the returned @c %DataItem.
     *
     * @param other The @c DataItem object to assign from. This follows the rules of implicit sharing.
     *
     * @return The revised @c DataItem instance.
     *
     * @since BlackBerry 10.2.0
     */
    DataItem& operator=(const DataItem& other);

    /*!
     * @brief Destructor.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~DataItem();

    /*!
     * @brief Set the ID for this item.
     *
     * This value must uniquely identify this item in the data source across data updates.
     *
     * @param keyId The ID for this item.
     *
     * @since BlackBerry 10.2.0
     */
    void setKeyId(const QString &keyId);

    /*!
     * @brief Get the ID for this item.
     *
     * This value must uniquely identify this item in the data source across data updates.
     *
     * @return The ID for this item.
     *
     * @since BlackBerry 10.2.0
     */
    QString keyId() const;

    /*!
     * @brief Set the revision value for this item.
     *
     * This value must uniquely identify a discrete state of this item in the data source,
     * including the states of all properties of the item.
     *
     * @param revision The revision for this item.
     *
     * @since BlackBerry 10.2.0
     */
    void setRevision(const DataRevision& revision);

    /*!
     * @brief Get the revision value for this item.
     *
     * This value must uniquely identify a discrete state of this item in the data source,
     * including the states of all properties of the item.
     *
     * @return The revision for this item.
     *
     * @since BlackBerry 10.2.0
     */
    DataRevision revision() const;

    /*!
     * @brief Set the data payload for this item.
     *
     * @param payload The data payload for this item.
     *
     * @since BlackBerry 10.2.0
     */
    void setPayload(const QVariant &payload);

    /*!
     * @brief Get the data payload for this item.
     *
     * @return The data payload for this item.
     *
     * @since BlackBerry 10.2.0
     */
    QVariant payload() const;

    /*!
     * @brief Convert this data item to a string representation.
     *
     * @return The string representation.
     *
     * @since BlackBerry 10.2.0
     */
    virtual QString toString() const;

private:
    /*! @cond PRIVATE */
    QSharedDataPointer<DataItemPrivate> d;
    /*! @endcond */
};

QDebug operator<<(QDebug dbg, const DataItem &item);

} // datamanager
} // cascades
} // bb

Q_DECLARE_METATYPE(bb::cascades::datamanager::DataItem)

#endif /* BB_CASCADES_DATAMANAGER_DATAITEM_HPP_ */
