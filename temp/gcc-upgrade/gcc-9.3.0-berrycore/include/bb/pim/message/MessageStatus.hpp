/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_MESSAGE_MESSAGESTATUS_HPP
#define BB_PIM_MESSAGE_MESSAGESTATUS_HPP

#include <bb/pim/Global>

#include <QFlags>

namespace bb {
namespace pim {
namespace message {

/*!
 * @headerfile MessageStatus.hpp <bb/pim/message/MessageStatus>
 * 
 * @brief The @c MessageStatus class represents the status of a message.
 *
 * @details A @c Message can have several different statuses, and you can use this
 * class to determine what statuses apply to a particular message. For example, you
 * can determine if a message is marked as read, is filed, or is sent. Here's an
 * example:
 *
 * @code
 * MessageService messageService;
 * Message msg = messageService.message(accountId , messageId ) ;
 * msg.status().testFlag(bb::pim::message::MessageStatus::Read)
 * @endcode
 * 
 * Note that the message status can be a bit flag that represents multiple statuses.
 * 
 * @see Message
 *
 * @xmlonly
 * <apigrouping group="App Integration/Message"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT MessageStatus
{
public:
    /*!
     * @brief An enumeration of supported message statuses.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief Indicates that the message is read.
         *
         * @since BlackBerry 10.0.0
         */
        Read      = 1 << 0,
        /*!
         * @brief Indicates that the message is a draft message.
         *
         * @since BlackBerry 10.0.0
         */
        Draft     = 1 << 1,
        /*!
         * @brief Indicates that the message is filed.
         *
         * @since BlackBerry 10.0.0
         */
        Filed     = 1 << 2,
        /*!
         * @brief Indicates that the message is sent.
         *
         * @since BlackBerry 10.0.0
         */
        Sent      = 1 << 4,
        /*!
         * @brief Indicates that the message is deferred.
         *
         * @since BlackBerry 10.0.0
         */
        Deferred  = 1 << 5,
        /*!
         * @brief Indicates that the message has been broadcasted.
         *
         * @since BlackBerry 10.0.0
         */
        Broadcast = 1 << 6,
        /*!
         * @brief Indicates that the message is waiting to be retrieved.
         *
         * @since BlackBerry 10.0.0
         */
        PendingRetrieval = 1 << 7
    };

    Q_DECLARE_FLAGS(Types, Type)

private:
    /*! @cond PRIVATE */
    MessageStatus();
    ~MessageStatus();
    /*! @endcond */
};

Q_DECLARE_OPERATORS_FOR_FLAGS(MessageStatus::Types)

} /* namespace message */
} /* namespace pim */
} /* namespace bb */

#endif // BB_PIM_MESSAGE_MESSAGESTATUS_HPP
