/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_MESSAGE_MESSAGE_HPP
#define BB_PIM_MESSAGE_MESSAGE_HPP

#include <bb/pim/Global>
#include <bb/pim/account/Account>
#include <bb/pim/message/Attachment>
#include <bb/pim/message/Keys>
#include <bb/pim/message/MessageContact>
#include <bb/pim/message/MessageBody>
#include <bb/pim/message/MessageUpdate>
#include <bb/pim/message/MessagePriority>
#include <bb/pim/message/MessageReplyState>
#include <bb/pim/message/MessageStatus>
#include <bb/pim/message/MessageTransmissionStatus>
#include <bb/pim/message/MessageFolder>
#include <bb/pim/message/MessageClass>
#include <bb/pim/message/MessageFlag>
#include <bb/pim/message/StatusReport>
#include <bb/pim/message/MessageRights>

#include <QList>
#include <QDateTime>
#include <QSharedPointer>
#include <QString>

namespace bb {
namespace pim {
namespace message {

class MessagePrivate;
/*!
 *
 * @brief The @c Message class represents information about a message, such as subject, sender and
 * recipient contacts, and status.
 *
 * @details This class represents data that's commonly associated with a message. You can manipulate
 * @c %Message objects by using the @c MessageService class. For example, you can retrieve a specific
 * message in the messages database by calling @c MessageService::message() and specifying the
 * account ID and message ID of the message you want. Or, you can retrieve a list of messages that
 * fit a set of criteria by calling @c MessageService::messages().
 *
 * You can use the @c %Message class to create a new message in your app and populate it with
 * information. You can then send the message by calling @c MessageService::send().
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
class BB_PIM_EXPORT Message
{
public:

    /*!
     * @brief Constructs an empty @c Message.
     *
     * @since BlackBerry 10.0.0
     */
    Message();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs a @c Message containing exactly the same values as
     * the provided @c %Message.
     *
     * @param other The @c %Message to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    Message(const Message &other);

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c Message into this
     * @c %Message.
     *
     * @param other The @c %Message from which to copy all values.
     *
     * @return A @c %Message with all copied data.
     *
     * @since BlackBerry 10.0.0
     */
    Message& operator=(const Message &other);


    /*!
     * @brief Constructs a @c Message with the provided private message information.
     *
     * @details This constructor creates a @c %Message by using a @c d_ptr to private
     * message information.
     *
     * @param messagePrivate The private message information to use.
     *
     * @since BlackBerry 10.0.0
     */
    explicit Message(MessagePrivate* messagePrivate);


    /*!
     * @brief Destroys this @c Message.
     *
     * @since BlackBerry 10.0.0
     */
    ~Message();

    /*!
    * @brief Retrieves the message ID of this @c Message.
    *
    * @details You can use this ID to retrieve a specific @c %Message using the
    * @c MessageService. This ID is unique per account.
    *
    * @return The message ID as a @c qint64 value.
     *
     * @since BlackBerry 10.0.0
    */
    MessageKey id() const;

    /*!
    * @brief Retrieves the folder ID of this @c Message.
    *
    * @details This ID indicates the folder that this message belongs to. This ID is
    * unique per account.
    *
    * @return The folder ID as a @c qint64 value.
     *
     * @since BlackBerry 10.0.0
    */
    MessageFolderKey folderId() const;

    /*!
    * @brief Retrieves the account ID of this @c Message.
    *
    * @details This ID indicates the account that this message belongs to.
    *
    * @return The account ID as a @c qint64 value.
     *
     * @since BlackBerry 10.0.0
    */
    bb::pim::account::AccountKey accountId() const;

    /*!
    * @brief Retrieves the conversation ID of this @c Message.
    *
    * @details This ID indicates the @c Conversation that this message belongs to. This
    * ID is unique per account.
    *
    * @return The conversation ID as a @c QString.
     *
     * @since BlackBerry 10.0.0
    */
    ConversationKey conversationId() const;

    /*!
     * @brief Retrieves the message preview, if available.
     *
     * @return The preview of the message body.
     *
     * @since BlackBerry 10.3.1
     */
    QString preview() const;

    /*!
    * @brief Retrieves the subject of this @c Message.
    *
    * @return The message subject.
     *
     * @since BlackBerry 10.0.0
    */
    QString subject() const;

    /*!
    * @brief Retrieves the MIME type of this @c Message.
    *
    * @return The MIME type.
     *
     * @since BlackBerry 10.0.0
    */
    QString mimeType() const;

    /*!
    * @brief Retrieves the device timestamp of this @c Message.
    *
    * @details This function returns the time that the message data was created on the device.
    *
    * @return The device timestamp.
     *
     * @since BlackBerry 10.0.0
    */
    QDateTime deviceTimestamp() const;

    /*!
    * @brief Retrieves the server timestamp of this @c Message.
    *
    * @details This function returns the time the message data was sent to the server. This
    * value is not valid for outbound messages.
    *
    * @return The server timestamp.
     *
     * @since BlackBerry 10.0.0
    */
    QDateTime serverTimestamp() const;

    /*!
    * @brief Retrieves the priority of this @c Message.
    *
    * @details The priority of a message is represented by the @c MessagePriority::Type enumeration
    * and includes values such as @c Low and @c High.
    *
    * @return The message priority.
     *
     * @since BlackBerry 10.0.0
    */
    MessagePriority::Type priority() const;

    /*!
    * @brief Retrieves the reply state of this @c Message.
    *
    * @details The reply state of a message is represented by the @c MessageReplyState::Type enumeration
    * and includes values such as @c Replied and @c Forwarded.
    *
    * @return The message reply state.
    *
    * @since BlackBerry 10.2.0
    */
    MessageReplyState::Type replyState() const;

    /*!
    * @brief Retrieves the reply state timestamp of this @c Message.
    *
    * @details The reply state timestamp indicates when the message was last replied to or forwarded.
    *
    * @return The message reply state timestamp.
     *
     * @since BlackBerry 10.2.0
    */
    QDateTime replyStateTimestamp() const;

    /*!
    * @brief Retrieves the status of this @c Message.
    *
    * @details The status of a message is represented by the @c MessageStatus::Type enumeration
    * and includes values such as @c Read and @c Draft. The status can be a bit flag that represents
    * multiple statuses.
    *
    * @return The message status.
     *
     * @since BlackBerry 10.0.0
    */
    MessageStatus::Types status() const;


    /*!
    * @brief Retrieves the transmission status of this @c Message.
    *
    * @details The transmission status of a message is represented by the
    * @c MessageTransmissionStatus::Type enumeration and includes values such as @c Pending and
    * @c Sent.
    *
    * @return The message transmission status.
     *
     * @since BlackBerry 10.0.0
    */
    long transmissionStatus() const;

    /*!
    * @brief Indicates whether this @c Message is an inbound message.
    *
    * @details You can use this information to determine the actions that can be applied to
    * the message (such as @c Reply).
    *
    * @return @c true if the message is an inbound message, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
    */
    bool isInbound() const;

    /*!
    * @brief Indicates whether this @c Message is a draft message.
    *
    * @details You can use this information to determine the actions that can be applied to
    * the message.
    *
    * @return @c true if the message is a draft message, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
    */
    bool isDraft() const;

    /*!
    * @brief Indicates whether this @c Message is filed.
    *
    * @return @c true if the message is filed, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
    */
    bool isFiled() const;

    /*!
    * @brief Indicates whether this @c Message is flagged.
    *
    * @return @c true if the message is flagged, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
    */
    bool isFlagged() const;

    /*!
    * @brief Indicates whether this @c Message has been sent successfully.
    *
    * @return @c true if the message has been sent successfully, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
    */
    bool isSent() const;

    /*!
    * @brief Retrieves the number of recipients in the recipient list for this @c Message.
    *
    * @details You can use this information to determine how to display message recipients in
    * your app (for example, in a message view).
    *
    * @return The number of recipients.
     *
     * @since BlackBerry 10.0.0
    */
    int recipientCount() const;

    /*!
    * @brief Retrieves the number of attachments for this @c Message.
    *
    * @details You can use this information to determine how to display message attachments in
    * your app (for example, in a message view).
    *
    * @return The number of attachments.
     *
     * @since BlackBerry 10.0.0
    */
    int attachmentCount() const;

    /*!
    * @brief Retrieves the sender of this @c Message.
    *
    * @details This function returns the sender as a @c MessageContact. You can use this information
    * to reply to the message.
    *
    * @return The sender of the message.
     *
     * @since BlackBerry 10.0.0
    */
    MessageContact sender() const;

    /*!
    * @brief Retrieves the body of this @c Message.
    *
    * @details This function returns the body as a @c MessageBody. You can use this information to
    * display the contents of the message. You can choose to load the actual content of the body
    * lazily when @c MessageBody::data() is called.
    *
    * @param type The type of message body to return (either plain text or HTML).
    *
    * @return The body of the message.
     *
     * @since BlackBerry 10.0.0
    */
    MessageBody body(MessageBody::Type) const;

    /*!
    * @brief Retrieves the list of recipients of this @c Message.
    *
    * @details This function returns the list of recipients as a @c QList of @c MessageContact objects.
    * You can use this information to implement a "Reply All" action for the message.
    *
    * @return The list of recipients.
     *
     * @since BlackBerry 10.0.0
    */
    QList<MessageContact> recipients() const;

    /*!
     * @brief Retrieves the recipient at the provided index in the recipient list of this @c Message.
     *
     * @param index The index of the recipient to retrieve.
     *
     * @return The recipient at the provided index.
     *
     * @since BlackBerry 10.0.0
     */
    MessageContact recipientAt(int index) const;

    /*!
    * @brief Retrieves the list of attachments of this @c Message.
    *
    * @details This function returns the list of attachments as a @c QList of @c Attachment objects.
    * You can use this information to download or view attachments of the message. You can choose to load
    * the actual content of the attachment lazily when @c Attachment::data() is called
    *
    * @return The list of attachments.
     *
     * @since BlackBerry 10.0.0
    */
    QList<Attachment> attachments() const;

    /*!
     * @brief Retrieves the attachment at the provided index in the attachment list of this @c Message.
     *
     * @param index The index of the attachment to retrieve.
     *
     * @return The attachment at the provided index.
     *
     * @since BlackBerry 10.0.0
     */
    Attachment attachmentAt(int index) const;

    /*!
     * @brief Retrieves the list of status reports for this @c Message.
     *
     * @details This function returns the list of status reports as a @c QList of @c StatusReport
     * objects. You can use this information to check the delivery status for each recipient of the
     * message.
     *
     * @return The list of status reports.
     *
     * @since BlackBerry 10.0.0
     */
    QList<StatusReport> statusReports() const;

    /*!
    * @brief Retrieves the follow-up flag for this @c Message.
    *
    * @return The follow-up flag.
     *
     * @since BlackBerry 10.0.0
    */
    MessageFlag followupFlag() const;

    /*!
    * @brief Applies the specified update to this @c Message.
    *
    * @details You can use this function to keep the copy of a message in your app current with any
    * service-side updates. After you retrieve the message from the message service, you should listen
    * for any updates to the message (for example, by using the @c MessageService::messageUpdated() signal).
    * If any change in message state occurs, you should apply the corresponding message update to your app's
    * copy of the message using this function.
    *
    * @param data The message update to apply.
     *
     * @since BlackBerry 10.0.0
    */
    void apply(MessageUpdate data);

    /*!
    * @brief Retrieves the source ID of this @c Message.
    *
    * @details This ID is a unique ID that might be provided by the server (for example, an email server).
    *
    * @return The source ID.
     *
     * @since BlackBerry 10.0.0
    */
    QString sourceId() const;

    /*!
    * @brief Retrieves the reply-to contact of this @c Message.
    *
    * @return The reply-to contact.
     *
     * @since BlackBerry 10.0.0
    */
    MessageContact replyTo() const;

    /*!
    * @brief Retrieves the class type of this @c Message.
    *
    * @details This function returns the class type as a value in the @c MessageClass::Type
    * enumeration. You can use this information to determine if the message is of a specific
    * class type (for example, a meeting invitation).
    *
    * @return The class type.
     *
     * @since BlackBerry 10.0.0
    */
    MessageClass::Type classType() const;

    /*!
    * @brief Retrieves the error details that are associated with this @c Message.
    *
    * @details This function returns error details that are associated with the message when
    * the message transmission fails. You can use this information to determine what type of
    * error occurred and handle it appropriately.
    *
    * @return The error details.
     *
     * @since BlackBerry 10.0.0
    */
    QString errorDetails() const;

    /*!
    * @brief Retrieves the references sync ID that's associated with this @c Message.
    *
    * @details You can use this information to create a smart reply for the message.
    *
    * @return The references sync ID.
     *
     * @since BlackBerry 10.0.0
    */
    QString referencesSyncId() const;

    /*!
     * @brief Indicates whether this @c Message has attachments.
     *
     * @details You can use this function to determine if a list of messages returned by the
     * @c MessageService has attachments. To retrieve the full list of attachments for a
     * specific message, you can call @c MessageService::message().
     *
     * @return @c true if the message has attachments, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool hasAttachments() const;

    /*!
    * @brief Indicates whether this @c Message is valid.
    *
    * @details You can use this function to determine whether a message that's returned from
    * the message service is valid. A message that doesn't have an ID is considered invalid.
    *
    * @return @c true if this @c %Message is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
    */
    bool isValid() const;

    /*!
     * @brief Retrieves the original message ID of this @c Message.
     *
     * @details This function returns the ID of the message (as a @c MessageKey) that is referenced
     * by this @c %Message object. You can use this ID to refer to the original message that is being
     * replied to.
     *
     * @return The original message ID.
     *
     * @since BlackBerry 10.0.0
     */
    MessageKey origMessageId() const;

    /*!
     * @brief Indicates whether this @c Message should be in the priority inbox.
     *
     * @details You can use this function to determine whether or not a message that's returned
     * from the message service should be in the priority inbox.
     *
     * @return @c true if this @c %Message should be in the priority inbox, @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isPriorityInbox() const;

    /*!
     * @brief Indicates whether this @c Message is flagged as a level one alert.
     *
     * @details You can use this function to determine whether or not a message that's returned
     * from the message service is flagged as level one alert.
     *
     * @return @c True if this @c %Message is flagged as a level one alert, @c false otherwise.
     *
     * @since BlackBerry 10.3.0
     */
    bool isLevelOneAlert() const;

    /*!
     * @brief Retrieves the customized group notification setting of this @c Message.
     *
     * @details This function returns the user notification setting information for messages belonging
     * to a group. This is used to customize notification settings for each group of a given account.
     *
     * @returns The group notification information if this @c %Message belongs to a group and has a user setting;
     *  an empty string otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    QString notificationGroup() const;

    /*!
     * @brief Retrieves the path of an image representing this @c Message.
     *
     * @details This function returns the image path that can be used to display an image with this
     * message.
     *
     * @returns The path of an image representing this @c Message, an empty string if there isn't one.
     *
     * @since BlackBerry 10.2.0
     */
    QString imagePath() const;

    /*!
    * @brief Retrieves the message rights of this @c Message.
    *
    * @details This function returns the message permissions or rights as a @c MessageRights
    *
    * @return The message rights object.
     *
     * @since BlackBerry 10.3.0
    */
    MessageRights messageRights() const;

    /*!
     * @brief Retrieves the size, in bytes, of all attachments for this @c Message.
     *
     * @details This function returns the total size, in bytes, of all attachments. If attachments have
     * not yet been downloaded for this message then this will be the estimated attachment size from the
     * server.
     *
     * @return The total size, in bytes, of all attachments for this @c Message, 0 if there are no attachments.
     *
     * @since BlackBerry 10.3.0
     */
    qint64 totalAttachmentSize() const;

    /*!
     * @brief Indicates whether this @c Message has the hidden flag set.
     *
     * @return @c True if this @c %Message is hidden, @c false otherwise.
     *
     * @since BlackBerry 10.3.0
     */
    bool isHidden() const;

    /*!
    * @brief Indicates whether this @c Message has been classified.
    *
    * @return @c true if the message has been classified, @c false otherwise.
     *
     * @since BlackBerry 10.3.1
    */
    bool isClassified() const;

    /*!
    * @brief Gets the classification for this @c Message.
    *
    * @return the classification id for the Message.
     *
     * @since BlackBerry 10.3.1
    */
    QString classificationId() const;

    /*!
    * @brief Retrieves the estimated size, in bytes, for this @c Message.
    *
    * @details The message size is a combined estimate of message body and its inline attachments.
    * Note that this does not include the size of its external attachments.
    *
    * @return The message size.
    *
    * @since BlackBerry 10.3.1
    */
    qint64 size() const;

private:
    QSharedPointer<MessagePrivate> d_ptr;

    friend class MessagePrivate;
};

} /* namespace message */
} /* namespace pim */
} /* namespace bb */

Q_DECLARE_METATYPE( bb::pim::message::Message )


#endif // MESSAGE_HPP
