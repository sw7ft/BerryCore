/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_MESSAGE_MESSAGECONTACT_HPP
#define BB_PIM_MESSAGE_MESSAGECONTACT_HPP

#include <bb/pim/Global>
#include <bb/pim/message/Keys>

#include <QList>
#include <QMetaType>
#include <QString>
#include <QSharedDataPointer>

namespace bb {
namespace pim {
namespace message {

class MessageContactPrivate;

/*!
 * @brief The @c MessageContact class represents a recipient or sender of a message.
 *
 * @details This class includes information about recipients and senders of messages, such as
 * type ("To", "Cc", and so on), name, and email address. You can create @c %MessageContact
 * objects and add them to @c Message objects as recipients or senders.
 *
 * You can use the @c MessageService class to retrieve a specific message or list of
 * messages. Then, you can retrieve the list of recipients by calling
 * @c Message::recipients(), or retrieve the sender by calling @c Message::sender().
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
class BB_PIM_EXPORT MessageContact
{
public:
    /*!
     * @brief An enumeration of supported message contact types.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief Indicates that the message contact is listed in the To field.
         *
         * @since BlackBerry 10.0.0
         */
        To,
        /*!
         * @brief Indicates that the message contact is listed in the Cc field.
         *
         * @since BlackBerry 10.0.0
         */
        Cc = 1,
        /*!
         * @brief Indicates that the message contact is listed in the Bcc field.
         *
         * @since BlackBerry 10.0.0
         */
        Bcc = 2,
        /*!
         * @brief Indicates that the message contact is listed in the From field.
         *
         * @since BlackBerry 10.0.0
         */
        From = 3,
        /*!
         * @brief Indicates that the message contact is listed in the ReplyTo field.
         *
         * @since BlackBerry 10.0.0
         */
        ReplyTo = 4
    };

    /*!
     * @brief Constructs a new @c MessageContact.
     *
     * @since BlackBerry 10.0.0
     */
    MessageContact();

    /*!
     * @brief Constructs a @c MessageContact with the provided private message contact
     * information.
     * 
     * @details This constructor creates a @c %MessageContact by using a @c d_ptr to private
     * message contact information.
     * 
     * @param messageContactPrivate The private message contact information to use.
     *
     * @since BlackBerry 10.0.0
     */
    explicit MessageContact(MessageContactPrivate *messageContactPrivate);

    /*!
     * @brief Constructs a @c MessageContact with the provided type, name, and email
     * address.
     *
     * @param id The ID of the message contact to construct.
     * @param type The type of contact to construct (for example, "To", "Cc", and so on).
     * @param name The name of the contact.
     * @param address The email address of the contact.
     * @param ton The type of network. This parameter is optional, and is used only for
     * alphanumeric addresses in SMS.
     * @param npi The numbering plan identification. This parameter is optional, and is
     * used only for alphanumeric addresses in SMS.
     *
     * @since BlackBerry 10.0.0
     */
    MessageContact(MessageContactKey id, MessageContact::Type type, const QString &name,
            const QString &address, unsigned char ton = 0,
            unsigned char npi = 0);

    /*!
     * @brief Copy constructor.
     * 
     * @details This function constructs a @c MessageContact containing exactly the same values as
     * the provided @c %MessageContact.
     * 
     * @param other The @c %MessageContact to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    MessageContact(const MessageContact &other);

    /*!
     * @brief Assignment operator.
     * 
     * @details This operator copies all values from the provided @c MessageContact into this
     * @c %MessageContact.
     * 
     * @param other The @c %MessageContact from which to copy all values.
     *
     * @return A @c %MessageContact with all copied data.
     *
     * @since BlackBerry 10.0.0
     */
    MessageContact& operator=(const MessageContact &other);

    /*!
     * @brief Equality operator.
     *
     * @details This operator indicates whether this @c MessageContact has the same values
     * as the provided @c %MessageContact.
     * 
     * @param other The @c %MessageContact to compare values with.
     * 
     * @return @c true if the @c %MessageContact objects are considered equal, @c false
     * otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool operator==(const MessageContact &other) const;

    /*!
     * @brief Destroys this @c MessageContact.
     *
     * @since BlackBerry 10.0.0
     */
    ~MessageContact();

    /*!
     * @brief Retrieves the ID of this @c MessageContact.
     * 
     * @return The message contact's ID.
     *
     * @since BlackBerry 10.0.0
     */
    MessageContactKey id() const;

    /*!
     * @brief Retrieves the type of this @c MessageContact.
     *
     * @details This function returns the type as an enumeration value in the
     * @c MessageContact::Type enumeration, and includes values such as "To" and
     * "Cc".
     * 
     * @return The message contact's type.
     *
     * @since BlackBerry 10.0.0
     */
    MessageContact::Type type() const;

    /*!
     * @brief Retrieves the name of this @c MessageContact.
     *
     * @details This function returns the display name that's provided by the service.
     *
     * @return The message contact's name.
     *
     * @since BlackBerry 10.0.0
     */
    QString name() const;

    /*!
     * @brief Retrieves the email address of this @c MessageContact.
     * 
     * @details This function returns the actual email address that's provided by the service.
     *
     * @return The message contact's email address.
     *
     * @since BlackBerry 10.0.0
     */
    QString address() const;

    /*!
     * @brief Retrieves the displayable name of this @c MessageContact.
     * 
     * @details This function returns the displayable name value, which includes the contact
     * name, friendly name, and email address (in that order).
     *
     * @return The message contact's displayable name.
     *
     * @since BlackBerry 10.0.0
     */
    QString displayableName() const;

    /*!
     * @brief Indicates whether this @c MessageContact is valid.
     * 
     * @return @c true if this @c %MessageContact is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

    /*!
     * @brief Retrieves the type of network of this @c MessageContact.
     * 
     * @details This function returns the type of the network (TON). This value is used only
     * for alphanumeric addresses in SMS.
     *
     * @return The type of network.
     *
     * @since BlackBerry 10.0.0
     */

    unsigned char ton() const;

    /*!
     * @brief Retrieves the numbering plan identification of this @c MessageContact.
     * 
     * @details This function returns the numbering plan identification (NPI). This value
     * is used only for alphanumeric addresses in SMS.
     *
     * @return The numbering plan identification.
     *
     * @since BlackBerry 10.0.0
     */

    unsigned char npi() const;

private:
    QSharedDataPointer<MessageContactPrivate> d_ptr;
    friend class MessageContactPrivate;
};

} /* namespace message */
} /* namespace pim */
} /* namespace bb */

Q_DECLARE_METATYPE(bb::pim::message::MessageContact)
Q_DECLARE_METATYPE(QList<bb::pim::message::MessageContact>)

#endif // BB_PIM_MESSAGE_MESSAGECONTACT_HPP
