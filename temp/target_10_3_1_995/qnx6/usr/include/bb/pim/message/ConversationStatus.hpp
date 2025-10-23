/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_MESSAGE_CONVERSATIONSTATUS_HPP
#define BB_PIM_MESSAGE_CONVERSATIONSTATUS_HPP

#include <bb/pim/Global>

#include <QFlags>

namespace bb {
namespace pim {
namespace message {

/*!
 * @headerfile ConversationStatus.hpp <bb/pim/message/ConversationStatus>
 *
 * @brief The @c ConversationStatus class includes possible statuses for conversations.
 * 
 * @details A @c Conversation can have several different statuses. For example, a
 * conversation might be marked as read, flagged, or filed. You can use the enumeration
 * values in this class to determine the status of a @c %Conversation.
 * 
 * @see Conversation
 *
 * @xmlonly
 * <apigrouping group="App Integration/Message"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT ConversationStatus
{
public:
    /*!
     * @brief An enumeration of supported statuses for conversations.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief Indicates that the conversation has been read.
         *
         * @since BlackBerry 10.0.0
         */
        Read      = 1 << 0,
        /*!
         * @brief Indicates that the conversation has a draft version.
         *
         * @since BlackBerry 10.0.0
         */
        HasDraft  = 1 << 1,
        /*!
         * @brief Indicates that the conversation has been finalized.
         *
         * @since BlackBerry 10.0.0
         */
        Finalized = 1 << 2,
        /*!
         * @brief Indicates that the conversation has been broadcast.
         *
         * @since BlackBerry 10.0.0
         */
        Broadcast = 1 << 3,
        /*!
         * @brief Indicates that an error has occurred with the conversation.
         *
         * @since BlackBerry 10.0.0
         */
        HasError  = 1 << 4,
        /*!
         * @brief Indicates that the last message in the conversation is inbound.
         *
         * @since BlackBerry 10.0.0
         */
        LastMessageInbound = 1 << 5,
        /*!
         * @brief Indicates that the conversation has been flagged.
         *
         * @since BlackBerry 10.0.0
         */
        Flagged = 1 << 6,
        /*!
         * @brief Indicates that the conversation has been filed.
         *
         * @since BlackBerry 10.0.0
         */
        Filed = 1 << 7

        // RESERVED = 1 << 8
        // RESERVED = 1 << 9
    };

    Q_DECLARE_FLAGS(Types, Type)

private:
    /*! @cond PRIVATE */
    ConversationStatus();
    ~ConversationStatus();
    /*! @endcond */
};

Q_DECLARE_OPERATORS_FOR_FLAGS(ConversationStatus::Types)

} /* namespace message */
} /* namespace pim */
} /* namespace bb */

#endif /* BB_PIM_MESSAGE_CONVERSATIONSTATUS_HPP */
