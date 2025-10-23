/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_MESSAGE_MESSAGERIGHTS_HPP
#define BB_PIM_MESSAGE_MESSAGERIGHTS_HPP

#include <bb/pim/Global>
#include <QString>
#include <QDateTime>
#include <QFlags>
#include <QSharedDataPointer>
#include <QMetaType>

namespace bb {
namespace pim {
namespace message {

class MessageRightsPrivate;

/*!
 * @headerfile MessageRights.hpp <bb/pim/message/MessageRights>
 *
 * @brief The @c MessageRights class represents the rights and permissions for a message.
 *
 * @details A @c Message can have several different permissions, and you can use this
 * class to determine what permissions apply to a particular message. For example, you
 * can determine if a message is allowed for edit, can be forwarded, or can be replied. Here's an
 * example:
 *
 * @code
 * MessageService messageService;
 * Message msg = messageService.message(accountId , messageId);
 * msg.rights().testFlag(bb::pim::message::MessageRights::EditAllowed)
 * @endcode
 *
 * @note The message rights value is a bit mask that represents multiple rights.
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
class BB_PIM_EXPORT MessageRights
{
public:
    /*!
     * @brief An enumeration of supported message rights and permissions.
     *
     * @since BlackBerry 10.3.0
     */
    enum Type {
        /*!
         * @brief Indicates whether the content of the original email
         * can be modified by the user when the user forwards, replies, or
         * replies all to the email message.
         *
         * @since BlackBerry 10.3.0
         */
        EditAllowed      = 1 << 0,
        /*!
         * @brief Specifies whether the information rights management (IRM) protection
         * on the e-mail message can be removed by the user.
         *
         * @since BlackBerry 10.3.0
         */
        ExportAllowed    = 1 << 1,
        /*!
         * @brief Specifies whether the user can copy content out of the
         * e-mail message.
         *
         * @since BlackBerry 10.0.0
         */
        ExtractAllowed   = 1 << 2,
        /*!
         * @brief Specifies whether the user can forward the e-mail message.
         *
         * @since BlackBerry 10.3.0
         */
        ForwardAllowed   = 1 << 3,
        /*!
         * @brief Specifies whether the user can modify the recipient list when
         * the user forwards, or replies to the e-mail message.
         *
         * @since BlackBerry 10.3.0
         */
        ModifyRecipientsAllowed  = 1 << 4,
        /*!
         * @brief Specifies whether the e-mail can be printed by the user.
         *
         * @since BlackBerry 10.3.0
         */
        PrintAllowed     = 1 << 5,
        /*!
         * @brief Specifies whether the contents of the e-mail message can be
         * accessed programmatically by third party applications.
         *
         * @since BlackBerry 10.3.0
         */
        ProgrammaticAccessAllowed = 1 << 6,
        /*!
         * @brief Specifies whether the user can reply to all of the recipients
         * of the original e-mail message.
         *
         * @since BlackBerry 10.3.0
         */
        ReplyAllAllowed  = 1 << 7,
        /*!
         * @brief Specifies whether the user is allowed to reply to the e-mail message.
         *
         * @since BlackBerry 10.3.0
         */
        ReplyAllowed     = 1 << 8
    };

    Q_DECLARE_FLAGS(Types, Type)

    /*!
     * @brief Constructs a new @c MessageRights.
     *
     * @since BlackBerry 10.3.0
     */
    MessageRights();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs a @c MessageRights containing exactly the same values as
     * the provided @c %MessageRights.
     *
     * @param other The @c %MessageRights to be copied.
     *
     * @since BlackBerry 10.3.0
     */

    MessageRights(const MessageRights &other);

    /*!
     * @brief Constructs a @c MessageRights with the provided private message rights
     * information.
     *
     * @details This constructor creates a @c %MessageRights by using a @c d_ptr to private
     * message rights information.
     *
     * @param messageRightsPrivate The private message rights information to use.
     *
     * @since BlackBerry 10.3.0
     */
    explicit MessageRights(MessageRightsPrivate *messageRightsPrivate);

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c MessageRights into this
     * @c %MessageRights.
     *
     * @param other The @c %MessageRights from which to copy all values.
     *
     * @return A @c %MessageRights with all copied data.
     *
     * @since BlackBerry 10.3.0
     */

    MessageRights& operator=(const MessageRights &other);

    /*!
     * @brief Equality operator.
     *
     * @details This operator indicates whether this @c MessageRights has the same values
     * as the provided @c %MessageRights.
     *
     * @param other The @c %MessageRights to compare values with.
     *
     * @return @c True if the @c %MessageRights objects are considered equal, @c false
     * otherwise.
     *
     * @since BlackBerry 10.3.0
     */

    bool operator==(const MessageRights &other) const;

    /*!
     * @brief Destroys this @c MessageRights.
     *
     * @since BlackBerry 10.3.0
     */
    ~MessageRights();

    /*!
     * @brief Indicates whether this @c MessageRights is valid.
     *
     * @return @c True if this @c %MessageRights is valid, @c false otherwise.
     *
     * @since BlackBerry 10.3.0
     */
    bool isValid() const;

    /*!
     * @brief Retrieves the rights policy template ID representing this @c MessageRights.
     *
     * @details This function returns a string that identifies the rights policy template.
     *
     * @return The string that identifies the rights policy template ID for this @c MessageRights, or an empty string
     * if there isn't one.
     *
     * @since BlackBerry 10.3.0
     */
    QString rightsTemplateId() const;

    /*!
     * @brief Retrieves the content expiry date representing this @c MessageRights.
     *
     * @details This function returns the date/time that specifies the expiration date for the license. The client
     * purges the body and attachments of the e-mail message when this date has passed.
     *
     * @return The content expiry timestamp.
     *
     * @since BlackBerry 10.3.0
     */
    QDateTime rightsContentExpiryDate() const;

    /*!
     * @brief Retrieves bit mask of rights permissions representing this @c MessageRights.
     *
     * @details This function returns a bit mask pulling all the rights management permissions together for
     * this message. The bit mask is represented by the @c MessageRights::Types enumeration and
     * includes values such as @c EditAllowed and @c ReplyAllAllowed.
     *
     * @return A bit mask that represents multiple permissions.
     *
     * @since BlackBerry 10.3.0
     */
    MessageRights::Types rights() const;

    /*!
     * @brief Retrieves the name of the rights policy template representing this @c MessageRights.
     *
     * @details This function returns the name of the rights policy template for this @c MessageRights.
     *
     * @return The name of the rights policy template representing this @c MessageRights, an empty string if there isn't one.
     *
     * @since BlackBerry 10.3.0
     */
    QString rightsTemplateInfoName() const;

    /*!
     * @brief Retrieves the description of the rights policy template representing this @c MessageRights.
     *
     * @details This function returns the description of the rights policy template for this @c MessageRights.
     *
     * @returns The description of the rights policy template representing this @c MessageRights, an empty string if there isn't one.
     *
     * @since BlackBerry 10.3.0
     */
    QString rightsTemplateInfoDescription() const;

private:
    /*! @cond PRIVATE */
    QSharedDataPointer<MessageRightsPrivate> d_ptr;
    /*! @endcond */
};

Q_DECLARE_OPERATORS_FOR_FLAGS(MessageRights::Types)

} /* namespace message */
} /* namespace pim */
} /* namespace bb */

#endif // BB_PIM_MESSAGE_MESSAGERIGHTS_HPP
