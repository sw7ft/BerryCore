/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_MESSAGE_MESSAGEFILTER_HPP
#define BB_PIM_MESSAGE_MESSAGEFILTER_HPP

#include <bb/pim/Global>

#include <QVariantMap>

namespace bb {
namespace pim {
namespace message {

/*!
 * @headerfile MessageFilter.hpp <bb/pim/message/MessageFilter>
 *
 * @brief The @c MessageFilter class lets you filter lists of messages based on key-value
 * pairs.
 *
 * @details You can use this class to specify a set of criteria for messages, and then apply
 * those criteria when you retrieve messages using the @c MessageService. For example, you
 * can specify that you want to retrieve a list of messages in ascending order, with a
 * particular set of participants and a maximum of 20 results. Then, you can call
 * @c MessageService::messages() and provide the filter as a parameter to retrieve the
 * messages.
 *
 * @see MessageService
 *
 * @xmlonly
 * <apigrouping group="App Integration/Message"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT MessageFilter
{
public:
    /*!
     * @brief Represents the anchor ID key.
     *
     * @details The anchor ID works as a marker ID (@c Message.id()) from which a set of
     * messages are returned from the @c MessageService. You can use this key to retrieve
     * lists of messages in chunks.  This key is valid for non-SMS/MMS accounts that
     * are part of the core PIM APIs.
     *
     * @since BlackBerry 10.0.0
     */
    static const QString AnchorId;
    /*!
     * @brief Represents the conversation ID key.
     *
     * @details This key filters the list of messages based on the conversation
     * that each message belongs to. This key is valid for use for SMS/MMS accounts.
     *
     * @since BlackBerry 10.0.0
     */
    static const QString ConversationId;
    /*!
     * @brief Represents the message ID key.
     *
     * @details This key filters the list of messages based on the message ID of each
     * message. This key is valid for non-SMS/MMS accounts that are part of the core PIM APIs.
     *
     * @since BlackBerry 10.0.0
     */
    static const QString MessageId;
    /*!
     * @brief Represents the quantity key.
     *
     * @details You can use this key to limit the number of messages or conversations that
     * are returned from the @c MessageService.
     *
     * @since BlackBerry 10.0.0
     */
    static const QString Quantity;
    /*!
     * @brief Represents the ascending key.
     *
     * @details This key specifies whether the list of messages returned is in ascending order.
     * This key is valid for use with SMS/MMS accounts.
     *
     * @since BlackBerry 10.0.0
     */
    static const QString Ascending;
    /*!
     * @brief Represents the participants key.
     *
     * @details This key filters the list of messages based on the participants. This key is
     * valid for use with SMS/MMS accounts.
     *
     * @since BlackBerry 10.0.0
     */
    static const QString Participants;
    /*!
     * @brief Represents the broadcast key.
     *
     * @details This key filters the list of messages based on whether the messages have been
     * broadcasted. This key is valid for use with SMS/MMS accounts.
     *
     * @since BlackBerry 10.0.0
     */
    static const QString Broadcast;
    /*!
     * @brief Represents the transmission status key.
     *
     * @details This key filters the list of messages based on their transmission statuses. This
     * key is valid for use with SMS/MMS accounts.
     *
     * @since BlackBerry 10.0.0
     */
    static const QString TransmissionStatus;
    /*!
     * @brief Represents the contact ID key.
     *
     * @details This key filters the list of messages based on the contact ID of the message contact
     * for each message. This key is valid for use with SMS/MMS accounts.
     *
     * @since BlackBerry 10.0.0
     */
    static const QString ContactId;
    /*!
     * @brief Represents the offset key.
     *
     * @details This key filters the list of messages based on an offset value. This key is
     * valid for use with SMS/MMS accounts.
     *
     * @since BlackBerry 10.0.0
     */
    static const QString Offset;
    /*!
     * @brief Represents the messages with IDs key.
     *
     * @details This key filters the list of messages based on the list of message IDs. This
     * key is valid for non-SMS/MMS accounts that are part of the core PIM APIs.
     *
     * @since BlackBerry 10.0.0
     */
    static const QString MessagesWithIds;

    /*!
     * @brief Constructs a new @c MessageFilter.
     *
     * @since BlackBerry 10.0.0
     */
    MessageFilter();

    /*!
     * @brief Destroys this @c MessageFilter.
     *
     * @since BlackBerry 10.0.0
     */
    ~MessageFilter();

    /*!
     * @brief Indicates whether this @c MessageFilter has a value for the provided key.
     *
     * @details The provided key should be one of the constants defined in this class
     * (such as @c MessageFilter::AnchorId, @c MessageFilter::Quantity, and so on).
     *
     * @param key The key to search for.
     *
     * @return @c true if this @c %MessageFilter has a value for the provided key, @c false
     * otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool contains(const QString &key) const;
    /*!
     * @brief Inserts a filter criterion with the provided key and value.
     *
     * @details The provided key should be one of the constants defined in this class
     * (such as @c MessageFilter::AnchorId, @c MessageFilter::Quantity, and so on). The
     * provided value should be a @c QVariant that wraps the desired value for the key.
     * For example, the value for the @c Quantity key could be set as @c %QVariant("10").
     *
     * @param key The key to set the value for.
     * @param value The value to set for the key.
     *
     * @since BlackBerry 10.0.0
     */
    void insert(const QString &key, const QVariant &value);

    /*!
     * @brief Retrieves the value of the provided key.
     *
     * @details The provided key should be one of the constants defined in this class
     * (such as @c MessageFilter::AnchorId, @c MessageFilter::Quantity, and so on). The
     * returned value is a @c QVariant that wraps the value that's associated with the
     * provided key.
     *
     * @param key The key to search for.
     *
     * @return The value of the provided key.
     *
     * @since BlackBerry 10.0.0
     */
    const QVariant value(const QString &key) const;

private:
    QVariantMap _values;
};

} /* namespace message */
} /* namespace pim */
} /* namespace bb */
#endif // BB_PIM_MESSAGE_MESSAGEFILTER_HPP
