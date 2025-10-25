/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_MESSAGE_MESSAGEFLAG_HPP
#define BB_PIM_MESSAGE_MESSAGEFLAG_HPP

#include <bb/pim/Global>

#include <QSharedDataPointer>

namespace bb {
namespace pim {
namespace message {

class MessageFlagPrivate;

/*!
 * @headerfile MessageFlag.hpp <bb/pim/message/MessageFlag>
 * 
 * @brief The @c MessageFlag class represents the follow-up flag for a message.
 * 
 * @details You can use this class to mark a @c Message for follow-up, and you can choose
 * to display this flag in the UI of your apps. You can set the follow-up flag for a
 * message by calling @c MessageService::setFollowupFlag().
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

class BB_PIM_EXPORT MessageFlag
{
public:
    /*!
     * @brief Constructs a new @c MessageFlag with the provided value.
     * 
     * @param If @c true the follow-up flag is set (enabled), if @c false the follow-up
     * flag is not set (disabled).
     *
     * @since BlackBerry 10.0.0
     */
    explicit MessageFlag(bool flag);

    /*!
     * @brief Copy constructor.
     * 
     * @details This function constructs a @c MessageFlag containing exactly the same values as
     * the provided @c %MessageFlag.
     * 
     * @param other The @c %MessageFlag to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    MessageFlag(const MessageFlag &other);

    /*!
     * @brief Assignment operator.
     * 
     * @details This operator copies all values from the provided @c MessageFlag into this
     * @c %MessageFlag.
     * 
     * @param other The @c %MessageFlag from which to copy all values.
     *
     * @return A @c %MessageFlag with all copied data.
     *
     * @since BlackBerry 10.0.0
     */
    MessageFlag& operator=(const MessageFlag &other);

    /*!
     * @brief Destroys this @c MessageFlag.
     *
     * @since BlackBerry 10.0.0
     */
    ~MessageFlag();

    /*!
     * @brief Indicates whether the follow-up flag is set for this @c MessageFlag.
     *
     * @return @c true if the follow-up flag is set, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isSet() const;
    /*!
     * @brief Sets the follow-up flag for this @c MessageFlag.
     *
     * @param flag If @c true the follow-up flag is set, if @c false the follow-up flag
     * is not set.
     *
     * @since BlackBerry 10.0.0
     */
    void set(bool flag);

private:
    QSharedDataPointer<MessageFlagPrivate> d_ptr;

};


} /* namespace message */
} /* namespace pim */
} /* namespace bb */

#endif // BB_PIM_MESSAGE_MESSAGEFLAG_HPP
