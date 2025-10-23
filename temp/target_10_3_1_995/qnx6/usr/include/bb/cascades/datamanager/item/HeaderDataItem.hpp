/*!
 * @copyright
 * Copyright (C) 2013 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_CASCADES_DATAMANAGER_HEADERDATAITEM_HPP_
#define BB_CASCADES_DATAMANAGER_HEADERDATAITEM_HPP_

#include <bb/cascades/datamanager/Global>
#include <bb/cascades/datamanager/DataItem>
#include <QSharedPointer>

namespace bb
{
namespace cascades
{
namespace datamanager
{

class HeaderDataItemPrivate;

/*!
 * @headerfile HeaderDataItem.hpp <bb/cascades/datamanager/HeaderDataItem>
 *
 * @brief This class represents a single header data item.
 *
 * @xmlonly
 * <apigrouping group="Data Management/Large Data Sets"/>
 * <library name="bbcascadesdatamanager"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_CASCADES_DATAMANAGER_EXPORT HeaderDataItem: public DataItem
{
public:
    /*!
     * @brief Constructs a @c HeaderDataItem given an ID, revision, child count, and payload.
     *
     * @param keyId The ID for this item.
     * @param revision The revision for this item.
     * @param childCount The child count for this item.
     * @param payload The data payload for this item.
     *
     * @since BlackBerry 10.2.0
     */
    HeaderDataItem(const QString &keyId, const DataRevision& revision, int childCount, const QVariant& payload);

    /*!
     * @brief Constructs a @c HeaderDataItem given a @c DataItem and child count.
     *
     * @param data The data item to obtain key, revision, and payload data from.
     * @param childCount The child count for this item.
     *
     * @since BlackBerry 10.2.0
     */
    HeaderDataItem(const DataItem &data, int childCount);

    /*!
     * @brief Constructs a @c HeaderDataItem.
     *
     * @since BlackBerry 10.2.0
     */
    HeaderDataItem();

    /*!
     * @brief Copy constructor.
     *
     * This function constructs a @c HeaderDataItem containing exactly the same values
     * as the provided @c %HeaderDataItem.
     *
     * @param other The @c HeaderDataItem object to copy. This follows the rules of implicit sharing.
     *
     * @since BlackBerry 10.2.0
     */
    HeaderDataItem(const HeaderDataItem& other);

    /*!
     * @brief Assignment operator.
     *
     * This function assigns values from the given @c HeaderDataItem to the returned @c %HeaderDataItem.
     *
     * @param other The @c HeaderDataItem object to assign from. This follows the rules of implicit sharing.
     *
     * @return The revised @c HeaderDataItem instance.
     *
     * @since BlackBerry 10.2.0
     */
    HeaderDataItem& operator=(const HeaderDataItem& other);

    /*!
     * @brief Destructor.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~HeaderDataItem();

    /*!
     * @brief Set the child count for this header item.
     *
     * @param childCount The child count.
     *
     * @since BlackBerry 10.2.0
     */
    void setChildCount(int childCount);

    /*!
     * @brief Get the child count for this header item.
     *
     * @return The child count.
     *
     * @since BlackBerry 10.2.0
     */
    int childCount() const;

    /*!
     * @brief Convert this header item to a string representation.
     *
     * @return The string representation.
     *
     * @since BlackBerry 10.2.0
     */
    virtual QString toString() const;

private:
    /*! @cond PRIVATE */
    QSharedDataPointer<HeaderDataItemPrivate> d;
    /*! @endcond */
};

} // datamanager
} // cascades
} // bb

Q_DECLARE_METATYPE(bb::cascades::datamanager::HeaderDataItem)

#endif /* BB_CASCADES_DATAMANAGER_HEADERDATAITEM_HPP_ */
