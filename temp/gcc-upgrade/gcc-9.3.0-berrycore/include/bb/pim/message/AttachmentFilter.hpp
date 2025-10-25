/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_MESSAGE_ATTACHMENTFILTER_HPP
#define BB_PIM_MESSAGE_ATTACHMENTFILTER_HPP

#include <bb/pim/Global>

#include <QVariantMap>

namespace bb {
namespace pim {
namespace message {

/*!
 * @headerfile AttachmentFilter.hpp <bb/pim/message/AttachmentFilter>
 *
 * @brief The @c AttachmentFilter class lets you filter lists of attachments based on key-value
 * pairs.
 *
 * @details You can use this class to specify a set of criteria for attachments, and then apply
 * those criteria when you retrieve attachments using the @c MessageService. For example, you
 * can specify that you want to retrieve a list of attachments in ascending order, for a
 * particular account id and a maximum of 20 results. Then, you can call
 * @c MessageService::attachments() and provide the filter as a parameter to retrieve the
 * attachments.
 *
 * @see MessageService
 *
 * @xmlonly
 * <apigrouping group="App Integration/Message"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_PIM_EXPORT AttachmentFilter
{
public:
    /*!
     * @brief Represents the attachment anchor ID key.
     *
     * @details The attachment anchor ID works as a marker ID (@c Attachment.id()) from which
     * a set of attachments are returned from the @c MessageService. You can use this key to
     * retrieve lists of attachments in chunks.
     *
     * @since BlackBerry 10.2.0
     */
    static const char* AnchorAttachmentId;

    /*!
     * @brief Represents the attachment anchor ID's corresponding account ID.
     *
     * @details This key is the account ID of the attachment anchor ID.
     *
     * @since BlackBerry 10.2.0
     */
    static const char* AnchorAccountId;

    /*!
     * @brief Represents the search value for attachment names.
     *
     * @details This search value filters the list of attachments based on whether the
     * attachment name begins with, or contains, the search value.
     *
     * @since BlackBerry 10.2.0
     */
    static const char* SearchValue;

    /*!
     * @brief Represents the quantity key.
     *
     * @details You can use this key to limit the number of attachments or conversations that
     * the @c MessageService returns.
     *
     * @since BlackBerry 10.2.0
     */
    static const char* Quantity;

    /*!
     * @brief Specifies the sort order of the attachments list.
     *
     * @details This value specifies the order by which the list of attachments is sorted.
     * Valid values are "date", "sender", "name" or "type".
	 *
     * If not specified, the default order is "date".
     *
     * @since BlackBerry 10.2.0
     */
    static const char* Order;

    /*!
     * @brief Represents the ascending key.
     *
     * @details This key specifies whether the list of attachments returned is in ascending order.
     *
     * @since BlackBerry 10.2.0
     */
    static const char* Ascending;

    /*!
     * @brief Constructs a new @c AttachmentFilter.
     *
     * @since BlackBerry 10.2.0
     */
    AttachmentFilter();
    
    /*!
     * @brief Destroys this @c AttachmentFilter.
     *
     * @since BlackBerry 10.2.0
     */
    ~AttachmentFilter();

    /*!
     * @brief Indicates whether this @c AttachmentFilter has a value for the provided key.
     *
     * @details The provided key should be one of the constants defined in this class
     * (such as @c AttachmentFilter::AnchorAttachmentId, @c AttachmentFilter::Quantity, and so on).
     *
     * @param key The key to search for.
     *
     * @return @c true if this @c %AttachmentFilter has a value for the provided key, @c false
     * otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool contains(const QString &key) const;
    /*!
     * @brief Inserts a filter criterion with the provided key and value.
     *
     * @details The provided key should be one of the constants defined in this class
     * (such as @c AttachmentFilter::AnchorAttachmentId, @c AttachmentFilter::Quantity, and so on). The
     * provided value should be a @c QVariant that wraps the desired value for the key.
     * For example, the value for the @c Quantity key could be set as @c %QVariant("10").
     *
     * @param key The key to set the value for.
     * @param value The value to set for the key.
     *
     * @since BlackBerry 10.2.0
     */
    void insert(const QString &key, const QVariant &value);

    /*!
     * @brief Retrieves the value of the provided key.
     *
     * @details The provided key should be one of the constants defined in this class
     * (such as @c AttachmentFilter::AnchorAttachmentId, @c AttachmentFilter::Quantity, and so on). The
     * returned value is a @c QVariant that wraps the value that's associated with the
     * provided key.
     *
     * @param key The key to search for.
     *
     * @return The value of the provided key.
     *
     * @since BlackBerry 10.2.0
     */
    const QVariant value(const QString &key) const;

private:
    QVariantMap _values;
};

} /* namespace message */
} /* namespace pim */
} /* namespace bb */

#endif // BB_PIM_MESSAGE_ATTACHMENTFILTER_HPP
