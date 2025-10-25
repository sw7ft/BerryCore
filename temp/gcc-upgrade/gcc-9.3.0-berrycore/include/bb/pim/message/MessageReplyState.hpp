/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_MESSAGE_REPLYSTATE_HPP
#define BB_PIM_MESSAGE_REPLYSTATE_HPP

#include <bb/pim/Global>

#include <QMetaType>

namespace bb {
namespace pim {
namespace message {

/*!
 * @headerfile MessageReplyState.hpp <bb/pim/message/MessageReplyState>
 *
 * @brief The @c MessageReplyState class includes reply state levels for messages.
 *
 * @details You can use this class to determine the reply state of a @c Message. For example,
 * messages can be marked as replied on or forwareded on. This property is not supported by
 * all email protocols.
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
class BB_PIM_EXPORT MessageReplyState
{
public:
    /*!
     * @brief An enumeration of possible reply state levels for messages.
     *
     * @since BlackBerry 10.2.0
     */
    enum Type {
        /*!
         * @brief Indicates no reply state on a message.
         *
         * @since BlackBerry 10.2.0
         */
        None   = 0,
        /*!
         * @brief Indicates a Reply is the most recent action on a message.
         *
         * @since BlackBerry 10.2.0
         */
        Replied = 1,
        /*!
         * @brief Indicates a Reply All is the most recent action on a message.
         *
         * @since BlackBerry 10.2.0
         */
        RepliedToAll = 2,
        /*!
         * @brief Indicates a forward is the most recent action on a message.
         *
         * @since BlackBerry 10.2.0
         */
        Forwarded = 3
    };

private:
    /*! @cond PRIVATE */
    MessageReplyState();
    ~MessageReplyState();
    /*! @endcond */
};

} /* namespace message */
} /* namespace pim */
} /* namespace bb */

Q_DECLARE_METATYPE(bb::pim::message::MessageReplyState::Type)

#endif // BB_PIM_MESSAGE_REPLYSTATE_HPP
