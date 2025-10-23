/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_MESSAGE_MESSAGEBUILDER_HPP
#define BB_PIM_MESSAGE_MESSAGEBUILDER_HPP

#include <bb/pim/Global>
#include <bb/pim/account/Account>
#include <bb/pim/message/Attachment>
#include <bb/pim/message/AttachmentEncoding>
#include <bb/pim/message/Conversation>
#include <bb/pim/message/MessageFolder>
#include <bb/pim/message/MessageFlag>
#include <bb/pim/message/Message>
#include <bb/pim/message/MessageBody>
#include <bb/pim/message/MessageContact>
#include <bb/pim/message/MessagePriority>
#include <bb/pim/message/MessageStatus>
#include <bb/pim/message/MessageTransmissionStatus>

#include <QSharedData>

namespace bb {
namespace pim {
namespace message {

class AbstractMessageBuilder;

/*!
 * @headerfile MessageBuilder.hpp <bb/pim/message/MessageBuilder>
 *
 * @brief The @c MessageBuilder class lets you create, and specify properties for, a new @c Message or
 * edit an existing @c %Message.
 *
 * @details You can use this class to set properties, such as status, subject, and body, for a
 * @c %Message. This class uses the builder pattern to create a @c %Message and set its properties.
 * Each of the setter functions returns a self reference to the builder, allowing you to chain function
 * calls together. For example, here's how to create a @c %Message using the builder pattern:
 *
 * @code
 * Message createMessage()
 * {
 *     MessageBuilder *builder = MessageBuilder::create(1);
 *     QString subject = "Test Subject ";
 *     MessageContact rto = MessageContact(-1 ,MessageContact::To,
 *                                         "Test Act1",
 *                                         "TestAct1@gmail.com");
 *     MessageContact rtoCC = MessageContact(-1, MessageContact::Cc,
 *                                           "Test Act2",
 *                                           "TestAct2@yahoo.com");
 *     MessageContact rtoBCC  = MessageContact(-1, MessageContact::Bcc,
 *                                             "Test Act3",
 *                                             "TestAct3@hotmail.com");
 *     QByteArray bodyData = "Testing email body";
 *     builder->subject(subject);
 *     bool added;
 *     builder->addRecipient(rto,&added);
 *     builder->addRecipient(rtoCC,&added);
 *     builder->addRecipient(rtoBCC,&added);
 *     builder->body(MessageBody::Html,bodyData);
 *     Attachment attachment(attachmentType, attachmentName,
 *                           QUrl::fromLocalFile(attachmentPath));
 *     builder->addAttachment(attachment);
 *     Message message = *builder;
 *     delete builder;
 *     return message;
 *
 * }
 * @endcode
 *
 * Any changes that you make to a @c %Message using this builder are temporary until the changes
 * are saved using the @c MessageService.
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

class BB_PIM_EXPORT MessageBuilder
{
public:
    /*!
     * @brief Creates a new @c MessageBuilder for the provided account ID.
     *
     * @details Based on the account ID that's provided (for example, corresponding to a chat or
     * messaging message), the appropriate type of @c %MessageBuilder is returned.
     *
     * @param accountId The account ID to create the message for (for example, an SMS
     * or email account ID).
     *
     * @return A @c %MessageBuilder object.
     *
     * @since BlackBerry 10.0.0
     */
    static MessageBuilder *create(bb::pim::account::AccountKey accountId);

    /*!
     * @brief Creates a new @c MessageBuilder for the provided account ID and message.
     *
     * @details Based on the account ID and message that are provided (for example, corresponding
     * to a chat or messaging message), the appropriate type of @c %MessageBuilder is returned.
     * You can use this function to create a copy @c %MessageBuilder based on an existing message,
     * and then use other functions in this class to edit that message.
     *
     * @param accountId The account ID to create the message for (for example, an SMS
     * or email account ID).
     * @param message The message to be copied and edited.
     *
     * @return A @c %MessageBuilder object.
     *
     * @since BlackBerry 10.0.0
     */
    static MessageBuilder *create(bb::pim::account::AccountKey accountId, const Message &message);

    /*!
     * @brief Destroys this @c MessageBuilder.
     *
     * @since BlackBerry 10.0.0
     */
    ~MessageBuilder();

    /*!
     * @brief Cast operator.
     *
     * @details This operator casts an object to the @c Message type.
     *
     * @since BlackBerry 10.0.0
     */
    operator Message();

    /*!
     * @brief Retrieves the ID of the @c Message that this @c MessageBuilder represents.
     *
     * @return The message's ID.
     *
     * @since BlackBerry 10.0.0
     */
    MessageKey id() const;

    /*!
     * @brief Sets the ID of the message.
     *
     * @param id The message's ID.
     *
     * @return A @c MessageBuilder with the provided message ID.
     *
     * @since BlackBerry 10.0.0
     */
    MessageBuilder &id(MessageKey id);

    /*!
     * @brief Retrieves the coversation ID of the @c Message that this @c MessageBuilder
     * represents.
     *
     * @return The conversation's ID.
     *
     * @since BlackBerry 10.0.0
     */
    ConversationKey conversationId() const;

    /*!
     * @brief Sets the conversation ID of the message.
     *
     * @param conversationId The message's conversation ID.
     *
     * @return A @c MessageBuilder with the provided conversation ID.
     *
     * @since BlackBerry 10.0.0
     */
    MessageBuilder &conversationId(ConversationKey conversationId);

    /*!
     * @brief Retrieves the folder ID of the @c Message that this @c MessageBuilder
     * represents.
     *
     * @return The message's folder ID.
     *
     * @since BlackBerry 10.0.0
     */
    MessageFolderKey folderId() const;

    /*!
     * @brief Sets the folder ID of the message.
     *
     * @param folderId The message's folder ID.
     *
     * @return A @c MessageBuilder with the provided folder ID.
     *
     * @since BlackBerry 10.0.0
     */
    MessageBuilder &folderId(MessageFolderKey folderId);

    /*!
     * @brief Retrieves the device timestamp of the @c Message that this
     * @c MessageBuilder represents.
     *
     * @details The device timestamp represents the time that the message data was created
     * on the device.
     *
     * @return The device timestamp.
     *
     * @since BlackBerry 10.0.0
     */
    QDateTime deviceTimestamp() const;

    /*!
     * @brief Sets the device timestamp for the message.
     *
     * @param deviceTimestamp The device timestamp.
     *
     * @return A @c MessageBuilder with the provided device timestamp.
     *
     * @since BlackBerry 10.0.0
     */
    MessageBuilder &deviceTimestamp(QDateTime deviceTimestamp);

    /*!
     * @brief Retrieves the server timestamp of the @c Message that this
     * @c MessageBuilder represents.
     *
     * @details The server timestamp represents the time the message data was sent to the
     * server. This value is not valid for outbound messages.
     *
     * @return The server timestamp.
     *
     * @since BlackBerry 10.0.0
     */
    QDateTime serverTimestamp() const;

    /*!
     * @brief Sets the server timestamp for the message.
     *
     * @param serverTimestamp The server timestamp.
     *
     * @return A @c MessageBuilder with the provided server timestamp.
     *
     * @since BlackBerry 10.0.0
     */
    MessageBuilder &serverTimestamp(QDateTime serverTimestamp);

    /*!
     * @brief Retrieves the priority of the @c Message that this @c MessageBuilder
     * represents.
     *
     * @return The message's priority.
     *
     * @since BlackBerry 10.0.0
     */
    MessagePriority::Type priority() const;

    /*!
     * @brief Sets the priority of the message.
     *
     * @param priority The message's priority.
     *
     * @return A @c MessageBuilder with the provided priority.
     *
     * @since BlackBerry 10.0.0
     */
    MessageBuilder &priority(MessagePriority::Type priority);

    /*!
     * @brief Retrieves the status of the @c Message that this @c MessageBuilder
     * represents.
     *
     * @return The message's status.
     *
     * @since BlackBerry 10.0.0
     */
    MessageStatus::Types status() const;

    /*!
     * @brief Sets the status of the message.
     *
     * @param status The message's status.
     *
     * @return A @c MessageBuilder with the provided status.
     *
     * @since BlackBerry 10.0.0
     */
    MessageBuilder &status(MessageStatus::Types status);

    /*!
     * @brief Retrieves the transmission status of the @c Message that this
     * @c MessageBuilder represents.
     *
     * @return The message's transmission status.
     *
     * @since BlackBerry 10.0.0
     */
    long transmissionStatus() const;

    /*!
     * @brief Sets the status of the message.
     *
     * @param transmissionStatus The message's status.
     *
     * @return A @c MessageBuilder with the provided status.
     *
     * @since BlackBerry 10.0.0
     */
    MessageBuilder &transmissionStatus(long transmissionStatus);

    /*!
     * @brief Indicates whether the @c Message that this @c MessageBuilder represents
     * is an inbound message.
     *
     * @return @c true if the message is an inbound message, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isInbound() const;

    /*!
     * @brief Sets whether the message is an inbound message.
     *
     * @param If @c true the message is an inbound message, if @c false the message is
     * not an inbound message.
     *
     * @return A @c MessageBuilder with the provided indication of whether the message
     * is an inbound message.
     *
     * @since BlackBerry 10.0.0
     */
     MessageBuilder &inbound(bool inbound);

    /*!
     * @brief Retrieves the sender of the @c Message that this @c MessageBuilder represents.
     *
     * @return The message's sender.
     *
     * @since BlackBerry 10.0.0
     */
     MessageContact sender() const;

    /*!
     * @brief Sets the sender of the message.
     *
     * @param sender The message's sender.
     *
     * @return A @c MessageBuilder with the provided sender.
     *
     * @since BlackBerry 10.0.0
     */
    MessageBuilder &sender(const MessageContact &sender);

    /*!
     * @brief Retrieves the follow-up flag for the @c Message that this @c MessageBuilder
     * represents.
     *
     * @return The message's follow-up flag.
     *
     * @since BlackBerry 10.0.0
     */
    MessageFlag followupFlag() const;

    /*!
     * @brief Sets the follow-up flag of the message.
     *
     * @param followupFlag The message's follow-up flag.
     *
     * @return A @c MessageBuilder with the provided follow-up flag.
     *
     * @since BlackBerry 10.0.0
     */
    MessageBuilder &followupFlag(const MessageFlag &followupFlag);

    /*!
     * @brief Retrieves the body of the @c Message that this @c MessageBuilder
     * represents.
     *
     * @return The message's body.
     *
     * @since BlackBerry 10.0.0
     */
    MessageBody body() const;

    /*!
     * @brief Sets the body of the message.
     *
     * @param type The type of body to set (plain text or HTML).
     * @param data The body data to set.
     *
     * @return A @c MessageBuilder with the provided body type and body data.
     *
     * @since BlackBerry 10.0.0
     */
    MessageBuilder &body(MessageBody::Type type,
                         const QByteArray &data);

    /*!
     * @brief Retrieves the subject of the @c Message that this @c MessageBuilder
     * represents.
     *
     * @return The message's subject.
     *
     * @since BlackBerry 10.0.0
     */
    QString subject() const;

    /*!
     * @brief Sets the subject of the message.
     *
     * @param subject The message's subject.
     *
     * @return A @c MessageBuilder with the provided subject.
     *
     * @since BlackBerry 10.0.0
     */
    MessageBuilder &subject(const QString &subject);

    /*!
     * @brief Retrieves the attachment at the provided index of the @c Message that
     * this @c MessageBuilder represents.
     *
     * @param index The index of the attachment to retrieve.
     *
     * @return The attachment at the provided index.
     *
     * @since BlackBerry 10.0.0
     */
    Attachment attachmentAt(int index) const;

    /*!
     * @brief Retrieves the list of attachments for the @c Message that this
     * @c MessageBuilder represents.
     *
     * @return The list of attachments.
     *
     * @since BlackBerry 10.0.0
     */
    QList<Attachment> attachments() const;

    /*!
     * @brief Retrieves the number of attachments for the @c Message that this
     * @c MessageBuilder represents.
     *
     * @return The number of attachments.
     *
     * @since BlackBerry 10.0.0
     */
    int attachmentCount() const;

    /*!
     * @brief Adds an attachment to the message.
     *
     * @param attachment The attachment to add.
     * @param ok Indicates whether the operation was successful. If @c true the attachment
     * was added successfully, if @c false the attachment was not added successfully.
     *
     * @return A @c MessageBuilder with the provided attachment added.
     *
     * @since BlackBerry 10.0.0
     */
    MessageBuilder &addAttachment(const Attachment &attachment, bool *ok = 0);

    /*!
     * @brief Removes a previously added attachment from the message.
     *
     * @param attachment The attachment to remove.
     * @param ok Indicates whether the operation was successful. If @c true the attachment
     * was removed successfully, if @c false the attachment was not removed successfully.
     *
     * @return A @c MessageBuilder with the provided attachment removed.
     *
     * @since BlackBerry 10.0.0
     */
    MessageBuilder &removeAttachment(const Attachment &attachment, bool *ok = 0);

    /*!
     * @brief Removes all attachments from the message.
     *
     * @return A @c MessageBuilder with all attachments removed.
     *
     * @since BlackBerry 10.0.0
     */
    MessageBuilder &removeAllAttachments();

    /*!
     * @brief Retrieves the recipient at the provided index of the @c Message that this
     * @c MessageBuilder represents.
     *
     * @param index The index of the recipient to remove.
     *
     * @return The recipient at the provided index.
     *
     * @since BlackBerry 10.0.0
     */
    MessageContact recipientAt(int index) const;

    /*!
     * @brief Retrieves the list of recipients for the @c Message that this
     * @c MessageBuilder represents.
     *
     * @return The list of recipients.
     *
     * @since BlackBerry 10.0.0
     */
    QList<MessageContact> recipients() const;

    /*!
     * @brief Retrieves the number of recipients for the @c Message that this
     * @c MessageBuilder represents.
     *
     * @return The number of recipients.
     *
     * @since BlackBerry 10.0.0
     */
    int recipientCount() const;

    /*!
     * @brief Adds a recipient to the message.
     *
     * @param recipient The recipient to add.
     * @param ok Indicates whether the operation was successful. If @c true the recipient
     * was added successfully, if @c false the recipient was not added successfully.
     *
     * @return A @c MessageBuilder with the provided recipient added.
     *
     * @since BlackBerry 10.0.0
     */
    MessageBuilder &addRecipient(const MessageContact &recipient, bool *ok = 0);

    /*!
     * @brief Replaces all recipients of the message with the provided list of recipients.
     *
     * @param recipients The list of recipients to replace the current recipients with.
     *
     * @return A @c MessageBuilder with the provided recipients list.
     *
     * @since BlackBerry 10.0.0
     */
    MessageBuilder &replaceAllRecipients(const QList<MessageContact> &recipients);

    /*!
     * @brief Removes a previously added recipient from the message.
     *
     * @param recipient The recipient to remove.
     * @param ok Indicates whether the operation was successful. If @c true the recipient
     * was removed successfully, if @c false the recipient was not removed successfully.
     *
     * @return A @c MessageBuilder with the provided recipient removed.
     *
     * @since BlackBerry 10.0.0
     */
    MessageBuilder &removeRecipient(const MessageContact &recipient, bool *ok = 0);

    /*!
     * @brief Removes all recipients from the message.
     *
     * @return A @c MessageBuilder with all recipients removed.
     *
     * @since BlackBerry 10.0.0
     */
    MessageBuilder &removeAllRecipients();

    /*!
     * @brief Retrieves the type of the @c Message that this @c MessageBuilder represents.
     *
     * @details For protocols such as text messaging, this value may change based on the
     * contents of the builder.
     *
     * @return The message's type.
     *
     * @since BlackBerry 10.0.0
     */
    QString type() const;

    /*!
     * @brief Retrieves the size (in bytes) of the @c Message that this @c MessageBuilder
     * represents.
     *
     * @return The message's size (in bytes).
     *
     * @since BlackBerry 10.0.0
     */
    int size() const;

    /*!
     * @brief Indicates whether the @c Message that this @c MessageBuilder represents has
     * any recipients.
     *
     * @return @c true if the message has recipients, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool hasRecipients() const;

    /*!
     * @brief Indicates whether the @c Message that this @c MessageBuilder represents has
     * any content (such as recipients, subject, body, or attachments).
     *
     * @return @c true if the message has content, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool hasContent() const;

    /*!
     * @brief Sets the references sync ID for the @c Message that this @c MessageBuilder
     * represents.
     *
     * @details The references sync ID is used for smart replies.
     *
     * @param referencesSyncId The references sync ID to set.
     *
     * @return A @c MessageBuilder with the provided references sync ID.
     *
     * @since BlackBerry 10.0.0
     */
    MessageBuilder &referencesSyncId(QString referencesSyncId);

    /*!
     * @brief Sets the original message ID for this @c Message.
     *
     * @details You can use this ID to to refer to the message that's being replied to.
     *
     * @param origMessageId The original message ID as a @c MessageKey.
     *
     * @return A @c MessageBuilder with the provided original message ID.
     *
     * @since BlackBerry 10.0.0
     */
    MessageBuilder &origMessageId(MessageKey origMessageId);

    /*!
     * @brief Sets the classification ID for this @c Message.
     *
     * @details You can use this to set the classification for the message.
     *
     * @param classificationId The unique message classification ID.
     *
     * @return A @c MessageBuilder with the provided classification ID.
     *
     * @since BlackBerry 10.3.1
     */
    MessageBuilder &classificationId(const QString& classificationId);

private:
    Q_DISABLE_COPY(MessageBuilder)

    /*! @cond PRIVATE */
    explicit MessageBuilder(AbstractMessageBuilder *abstractMessageBuilder);
    /*! @endcond */

    QScopedPointer<AbstractMessageBuilder> d_ptr;
};

} /* namespace message */
} /* namespace pim */
} /* namespace bb */

#endif // BB_PIM_MESSAGE_MESSAGEBUILDER_HPP
