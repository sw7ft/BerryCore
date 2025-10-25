/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_MESSAGE_CONVERSATIONBUILDER_HPP
#define BB_PIM_MESSAGE_CONVERSATIONBUILDER_HPP

#include <bb/pim/Global>
#include <bb/pim/account/Account>
#include <bb/pim/message/MessageContact>
#include <bb/pim/message/Conversation>
#include <bb/pim/message/Folder>

#include <QDateTime>
#include <QSharedData>

namespace bb {
namespace pim {
namespace message {

class ConversationBuilderPrivate;

/*!
 * @headerfile ConversationBuilder.hpp <bb/pim/message/ConversationBuilder>
 *
 * @brief The @c ConversationBuilder class lets you create, and specify properties for, a new
 * @c Conversation.
 *
 * @details You can use this class to set properties, such as latest message ID, subject, and
 * participant list, for a @c %Conversation. This class uses the builder pattern to create a
 * @c %Conversation and set its properties. Each of the setter functions returns a self
 * reference to the builder, allowing you to chain function calls together.
 *
 * @code
 * // @brief This sample code shows how to use the ConversationBuilder class to create
 * // TextMessaging Conversation objects.
 * //
 * // @details You can use this function to start the creation of a @c Conversation and
 * // chain additional function calls together to set the properties of the
 * // @c %Conversation.
 * // @param acctKey The account ID.
 * // @param convType pass "G" for group chat, "B" for broadcast
 * // @param participants list of contacts.
 * //
 * // @return A @c %Conversation object.
 * Conversation createTextMessagingConversation(const QString &convType, const QList<MessageContact> &participants)
 * {
 *     QScopedPointer<ConversationBuilder> conversationBuilder(ConversationBuilder::create());
 *     conversationBuilder->accountId(bb::pim::message::TextMessagingAccountId);
 *
 *     bool isGroupChat = convType == "G";
 *     ConversationStatus::Types originalStatus = conversationBuilder->status();
 *     ConversationStatus::Types newStatus = isGroupChat ?
 *                              (originalStatus & ~bb::pim::message::ConversationStatus::Broadcast) :
 *                              (originalStatus | bb::pim::message::ConversationStatus::Broadcast);
 *
 *     // Set the Finalized status bit to indicate the recipients are fixed.
 *     // Leaving this bit cleared allows the recipients to be edited in the UI.
 *     newStatus |= bb::pim::message::ConversationStatus::Finalized;
 *     conversationBuilder->status(newStatus).participants(participants);
 *
 *     return *conversationBuilder;    // use the cast operator to get a Conversation instance to return
 * }
 * @endcode
 *
 * Any changes that you make to a @c %Conversation using this builder are temporary until the changes are persisted by using
 * the @c MessageService.
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
class BB_PIM_EXPORT ConversationBuilder
{
public:
    /*!
     * @brief Creates a new @c ConversationBuilder.
     *
     * @details You can use this function to start the creation of a @c Conversation and
     * chain additional function calls together to set the properties of the
     * @c %Conversation.
     *
     * @return A @c %ConversationBuilder object.
     *
     * @since BlackBerry 10.0.0
     */
    static ConversationBuilder *create();

    /*!
     * @brief Creates a new @c ConversationBuilder using the provided @c %ConversationBuilder.
     *
     * @return A @c %ConversationBuilder object that contains the same values as the
     * provided @c %ConversationBuilder.
     *
     * @since BlackBerry 10.0.0
     */
    static ConversationBuilder *create(const Conversation &conversation);

    /*!
     * @brief Constructs a new @c ConversationBuilder.
     *
     * @since BlackBerry 10.0.0
     */
    ~ConversationBuilder();

    /*!
     * @brief Cast operator.
     *
     * @details This operator casts an object to the @c Conversation type.
     *
     * @since BlackBerry 10.0.0
     */
    operator Conversation();

    /*!
     * @brief Retrieves the ID of the @c Conversation that this @c ConversationBuilder
     * represents.
     *
     * @details This ID is unique per account.
     *
     * @return The conversation's ID.
     *
     * @since BlackBerry 10.0.0
     */
    ConversationKey conversationId() const;

    /*!
     * @brief Sets the ID of the conversation.
     *
     * @param conversationId The conversation's ID.
     *
     * @return A @c ConversationBuilder with the provided conversation ID.
     *
     * @since BlackBerry 10.0.0
     */
    ConversationBuilder &conversationId(ConversationKey conversationId);

    /*!
     * @brief Retrieves the account ID of the @c Conversation that this @c ConversationBuilder
     * represents.
     *
     * @details You can use this ID to determine which account the conversation belongs to.
     *
     * @return The conversation's account ID.
     *
     * @since BlackBerry 10.0.0
     */
    bb::pim::account::AccountKey accountId() const;

    /*!
     * @brief Sets the account ID of the conversation.
     *
     * @param accountId The conversation's account ID.
     *
     * @return A @c ConversationBuilder with the provided account ID.
     *
     * @since BlackBerry 10.0.0
     */
    ConversationBuilder &accountId(bb::pim::account::AccountKey accountId);

    /*!
     * @brief Retrieves the list of folder IDs for the @c Conversation that this
     * @c ConversationBuilder represents.
     *
     * @details The folder IDs are based on the folder ID of each message in the conversation
     * (in no particular order).
     *
     * For example, consider a conversation that consists of messages from the following folders:
     * - inbox
     * - inbox
     * - sent
     * - inbox
     *
     * In this case, this function returns a @c QList with two folder IDs: inbox and sent.
     *
     * @return The conversation's folder IDs.
     *
     * @since BlackBerry 10.0.0
     */
    QList<FolderKey> folderIds() const;

    /*!
     * @brief Sets the folder ID list of the conversation.
     *
     * @param folderIds The list of folder IDs.
     *
     * @return A @c ConversationBuilder with the provided folder ID list.
     *
     * @since BlackBerry 10.0.0
     */
    ConversationBuilder &folderIds(const QList<FolderKey> &folderIds);

    /*!
     * @brief Retrieves the ID of the most recent message in the @c Conversation that
     * this @c ConversationBuilder represents.
     *
     * @return The ID of the most recent message in the conversation.
     *
     * @since BlackBerry 10.0.0
     */
    MessageKey latestMessageId() const;

    /*!
     * @brief Sets the ID of the most recent message in the conversation.
     *
     * @param latestMessageId The ID of the most recent message in the conversation.
     *
     * @return A @c ConversationBuilder with the provided ID of the most recent
     * message.
     *
     * @since BlackBerry 10.0.0
     */
    ConversationBuilder &latestMessageId(MessageKey latestMessageId);

    /*!
     * @brief Retrieves the raw transmission status of the @c Conversation that this
     * @c ConversationBuilder represents.
     *
     * @details Note that this is the status of the latest message in the conversation,
     * coming from the data store.
     *
     * @return The conversation's raw transmission status.
     *
     * @since BlackBerry 10.0.0
     */
    long transmissionStatus() const;

    /*!
     * @brief Sets the raw transmission status of the most recent message in the conversation.
     *
     * @param status The status of the most recent message in the conversation.
     *
     * @return A @c ConversationBuilder with the provided status of the most recent
     * message.
     *
     * @since BlackBerry 10.0.0
     */
    ConversationBuilder &transmissionStatus(long status);

    /*!
     * @brief Retrieves the subject of the @c Conversation that this @c ConversationBuilder
     * represents.
     *
     * @return The conversation's subject.
     *
     * @since BlackBerry 10.0.0
     */
    QString subject() const;

    /*!
     * @brief Sets the subject of the conversation.
     *
     * @param subject The conversation's subject.
     *
     * @return A @c ConversationBuilder with the provided subject.
     *
     * @since BlackBerry 10.0.0
     */
    ConversationBuilder &subject(const QString &subject);

    /*!
     * @brief Retrieves a list of the participants in the @c Conversation that this
     * @c ConversationBuilder represents.
     *
     * @return A list of the conversation's participants.
     *
     * @since BlackBerry 10.0.0
     */
    QList<MessageContact> participants() const;

    /*!
     * @brief Sets the participants of the conversation.
     *
     * @param participants The conversation's participants.
     *
     * @return A @c ConversationBuilder with the provided participants.
     *
     * @since BlackBerry 10.0.0
     */
    ConversationBuilder &participants(QList<MessageContact> participants);

    /*!
     * @brief Retrieves the number of messages in the @c Conversation that this
     * @c ConversationBuilder represents.
     *
     * @return The number of messages in the conversation.
     *
     * @since BlackBerry 10.0.0
     */
    int messageCount() const;

    /*!
     * @brief Sets the number of messages in the conversation.
     *
     * @param messageCount The number of messages in the conversation.
     *
     * @return A @c ConversationBuilder with the provided number of messages.
     *
     * @since BlackBerry 10.0.0
     */
    ConversationBuilder &messageCount(int messageCount);

    /*!
     * @brief Retrieves the number of unread messages in the @c Conversation that this
     * @c ConversationBuilder represents.
     *
     * @return The number of unread messages in the conversation.
     *
     * @since BlackBerry 10.0.0
     */
    int unreadMessageCount() const;

    /*!
     * @brief Sets the number of unread messages in the conversation.
     *
     * @param unreadMessageCount The number of unread messages in the conversation.
     *
     * @return A @c ConversationBuilder with the provided number of unread messages.
     *
     * @since BlackBerry 10.0.0
     */
    ConversationBuilder &unreadMessageCount(int unreadMessageCount);

    /*!
     * @brief Retrieves a bitmask representing the status of the @c Conversation that this
     * @c ConversationBuilder represents.
     *
     * @details The @c ConversationStatus class includes the possible flags for the status
     * of a conversation.
     *
     * @return A bitmask representing the status of the conversation.
     *
     * @since BlackBerry 10.0.0
     */
    ConversationStatus::Types status() const;

    /*!
     * @brief Sets the status of the conversation.
     *
     * @details See @c ConversationStatus for a list of possible flags.
     *
     * @param status The conversation's status.
     *
     * @return A @c ConversationBuilder with the provided status.
     *
     * @since BlackBerry 10.0.0
     */
    ConversationBuilder &status(ConversationStatus::Types status);

    /*!
     * @brief Retrieves the name of the @c Conversation that this @c ConversationBuilder
     * represents.
     *
     * @return The conversation's name.
     *
     * @since BlackBerry 10.0.0
     */
    QString name() const;

    /*!
     * @brief Sets the name of the conversation.
     *
     * @param name The conversation's name.
     *
     * @return A @c ConversationBuilder with the provided name.
     *
     * @since BlackBerry 10.0.0
     */
    ConversationBuilder &name(const QString &name);

    /*!
     * @brief Retrieves the timestamp of the @c Conversation that this
     * @c ConversationBuilder represents.
     *
     * @return The conversation's timestamp.
     *
     * @since BlackBerry 10.0.0
     */
    QDateTime timeStamp() const;

    /*!
     * @brief Sets the timestamp of the conversation.
     *
     * @param timeStamp The conversation's timestamp.
     *
     * @return A @c ConversationBuilder with the provided timestamp.
     *
     * @since BlackBerry 10.0.0
     */
    ConversationBuilder &timeStamp(QDateTime timeStamp);

    /*!
     * @brief Retrieves the summary of the @c Conversation that this
     * @c ConversationBuilder represents.
     *
     * @return The conversation's summary.
     *
     * @since BlackBerry 10.0.0
     */
    QString summary() const;

    /*!
     * @brief Sets the summary of the conversation.
     *
     * @param summary The conversation's summary.
     *
     * @return A @c ConversationBuilder with the provided summary.
     *
     * @since BlackBerry 10.0.0
     */
    ConversationBuilder &summary(const QString &summary);

    /*!
     * @brief Returns the type of the @c Conversation that this @c ConversationBuilder
     * represents.
     *
     * @return The conversation's type.
     *
     * @since BlackBerry 10.0.0
     */
    QString type() const;

private:
    Q_DISABLE_COPY(ConversationBuilder)

    /*! @cond PRIVATE */
    ConversationBuilder();
    explicit ConversationBuilder(const Conversation &conversation);
    /*! @endcond */

    QScopedPointer<ConversationBuilderPrivate> d_ptr;
};

} /* namespace message */
} /* namespace pim */
} /* namespace bb */

#endif // BB_PIM_MESSAGE_CONVERSATIONBUILDER_HPP
