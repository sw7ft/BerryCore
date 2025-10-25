/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_MESSAGE_MESSAGEUPDATE_HPP
#define BB_PIM_MESSAGE_MESSAGEUPDATE_HPP

#include <bb/pim/Global>
#include <bb/pim/message/MessageFolder>
#include <bb/pim/message/MessageStatus>
#include <bb/pim/message/MessageTransmissionStatus>

#include <QSharedDataPointer>

namespace bb {
namespace pim {
namespace message {

class MessageUpdatePrivate;

/*!
 * @headerfile MessageUpdate.hpp <bb/pim/message/MessageUpdate>
 *
 * @brief The @c MessageUpdate class represents a change or update to a message.
 *
 * @details You can use a @c %MessageUpdate object to apply a change or update to an existing
 * message that your app retrieved from the @c MessageService. You can listen for updates to
 * messages from the @c %MessageService (for example, by listening for the
 * @c MessageService::messageUpdated() signal), and then use the provided
 * @c %MessageUpdate object to update your app's local copy of the message.
 *
 * To update a message, you can call @c Message::apply(). In this way, you can keep your
 * app's local copy of a message in sync with the server's copy.
 *
 * @see Message, MessageService
 *
 * @xmlonly
 * <apigrouping group="App Integration/Message"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT MessageUpdate
{

public:
    /*!
     * @brief An enumeration of supported types of message updates.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        None = 1 ,
        /*!
         * @brief Indicates that the read status of the message has been updated.
         *
         * @since BlackBerry 10.0.0
         */
        Read = 2,
        /*!
         * @brief Indicates that the flagged status of the message has been updated.
         *
         * @since BlackBerry 10.0.0
         */
        Flagged = 3,
        /*!
         * @brief Indicates that the folder that the message is contained in has
         * been updated.
         *
         * @since BlackBerry 10.0.0
         */
        FolderChanged = 4,
        /*!
         * @brief Indicates that the transmission status of the message has been
         * updated.
         *
         * @since BlackBerry 10.0.0
         */
        StatusChanged = 5,
        /*!
         * @brief Indicates that the reply state of the message has been
         * updated.
         *
         * @since BlackBerry 10.2.0
         */
        ReplyStateChanged = 6,
        /*!
         * @brief Indicates that the reply state time of the message has
         * been updated.
         *
         * @since BlackBerry 10.2.0
         */
        ReplyStateTimeChanged = 7,

        /*!
         * @brief Indicates that the priority state of the message has
         * been updated.
         *
         * @since BlackBerry 10.2.0
         */
        PriorityChanged = 8
    };

    /*!
     * @brief Constructs a new @c MessageUpdate.
     *
     * @since BlackBerry 10.0.0
     */
    MessageUpdate();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs a @c MessageUpdate containing exactly the same values as
     * the provided @c %MessageUpdate.
     *
     * @param other The @c %MessageUpdate to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    MessageUpdate(const MessageUpdate &other);

    /*!
     * @brief Constructs a @c MessageUpdate with the provided private message update information.
     *
     * @details This constructor creates a @c %MessageUpdate by using a @c d_ptr to private
     * message update information.
     *
     * @param messageUpdatePrivate The private message update information to use.
     *
     * @since BlackBerry 10.0.0
     */
    explicit MessageUpdate(MessageUpdatePrivate* messageUpdatePrivate);


    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c MessageUpdate into this
     * @c %MessageUpdate.
     *
     * @param other The @c %MessageUpdate from which to copy all values.
     *
     * @return A @c %MessageUpdate with all copied data.
     *
     * @since BlackBerry 10.0.0
     */
    MessageUpdate& operator=(const MessageUpdate &other);

    /*!
     * @brief Destroys this @c MessageUpdate.
     *
     * @since BlackBerry 10.0.0
     */
    ~MessageUpdate();

    /*!
     * @brief Indicates whether this @c MessageUpdate includes the provided type of update.
     *
     * @details For example, you can use this function to determine if this
     * @c %MessageUpdate includes an update to read status by calling the function with
     * @c MessageUpdate::Read as the argument.
     *
     * @param type The type of message update to query for.
     *
     * @return @c true if this @c %MessageUpdate includes the provided type of update,
     * @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool contains(MessageUpdate::Type type) const;

    /*!
     * @brief Inserts an update value for the provided type into this @c MessageUpdate.
     *
     * @param type The type of message update to insert the value for.
     * @param value The value to insert.
     *
     * @since BlackBerry 10.0.0
     */
    void insert(MessageUpdate::Type type, const QVariant &value);

    /*!
     * @brief Indicates whether this @c MessageUpdate is valid.
     *
     * @return @c true if this @c %MessageUpdate is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid();

    /*!
     * @brief Retrieves the value that's associated with the provided update type in this
     * @c MessageUpdate.
     *
     * @param type The type of message update to retrieve the value for.
     *
     * @return The value of the provided type of message update.
     *
     * @since BlackBerry 10.0.0
     */
    const QVariant value(MessageUpdate::Type type) const;


private:
    QSharedDataPointer<MessageUpdatePrivate> d_ptr;
};

} /* namespace message */
} /* namespace pim */
} /* namespace bb */


#endif // BB_PIM_MESSAGE_MESSAGEUPDATE_HPP
