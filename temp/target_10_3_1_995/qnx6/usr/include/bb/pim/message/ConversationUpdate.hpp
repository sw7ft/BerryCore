/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_MESSAGE_CONVERSATIONUPDATE_HPP
#define BB_PIM_MESSAGE_CONVERSATIONUPDATE_HPP

#include <bb/pim/Global>

#include <QMetaType>
#include <QSharedData>

namespace bb {
namespace pim {
namespace message {

class ConversationUpdatePrivate;

/*!
 * @headerfile ConversationUpdate.hpp <bb/pim/message/ConversationUpdate>
 *
 * @brief The @c ConversationUpdate class represents updated information for a conversation.
 * 
 * @details You can use this class to update a conversation in your app when that conversation
 * changes. For example, the @c MessageService::conversationUpdated() signal is emitted when
 * a conversation changes. This signal includes a @c %ConversationUpdate parameter that you
 * can use to update the corresponding @c %Conversation in your app.
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
class BB_PIM_EXPORT ConversationUpdate
{
public:
    /*!
     * @brief Constructs a new @c ConversationUpdate.
     *
     * @since BlackBerry 10.0.0
     */
    ConversationUpdate();

    /*!
     * @brief Destroys this @c ConversationUpdate.
     *
     * @since BlackBerry 10.0.0
     */
    ~ConversationUpdate();

    /*!
     * @brief Copy constructor.
     * 
     * @details This function constructs a @c ConversationUpdate containing exactly the same values as
     * the provided @c %ConversationUpdate.
     * 
     * @param other The @c %ConversationUpdate to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    ConversationUpdate(const ConversationUpdate &other);

    /*!
     * @brief Assignment operator.
     * 
     * @details This operator copies all values from the provided @c ConversationUpdate into this
     * @c %ConversationUpdate.
     * 
     * @param other The @c %ConversationUpdate from which to copy all values.
     *
     * @return A @c %ConversationUpdate with all copied data.
     *
     * @since BlackBerry 10.0.0
     */
    ConversationUpdate &operator=(const ConversationUpdate &other);

private:
    QSharedDataPointer<ConversationUpdatePrivate> d_ptr;
};

} /* namespace message */
} /* namespace pim */
} /* namespace bb */

Q_DECLARE_METATYPE(bb::pim::message::ConversationUpdate);

#endif // BB_PIM_MESSAGE_CONVERSATIONUPDATE_HPP
