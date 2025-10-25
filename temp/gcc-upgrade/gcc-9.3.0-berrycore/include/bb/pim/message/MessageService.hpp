/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_MESSAGE_MESSAGESERVICE_HPP
#define BB_PIM_MESSAGE_MESSAGESERVICE_HPP

#include <bb/Global>
#include <bb/pim/Global>
#include <bb/pim/account/Account>
#include <bb/pim/message/Attachment>
#include <bb/pim/message/AttachmentDownloadStatus>
#include <bb/pim/message/Conversation>
#include <bb/pim/message/ConversationUpdate>
#include <bb/pim/message/FileAttachment>
#include <bb/pim/message/AttachmentFilter>
#include <bb/pim/message/Folder>
#include <bb/pim/message/Message>
#include <bb/pim/message/MessagePriority>
#include <bb/pim/message/MessageUpdate>
#include <bb/pim/message/MessageStatus>
#include <bb/pim/message/MessageTransmissionStatus>
#include <bb/pim/message/MessageServiceFeature>
#include <bb/pim/message/OutOfOfficeSettings>
#include <bb/pim/message/MessageTransaction>
#include <bb/pim/message/MessageUpdateFilter>
#include <bb/pim/message/MarkOrDeletePriorOp>
#include <bb/pim/message/MarkOrDeletePriorFilter>

#include <QObject>

namespace bb {
namespace pim {
namespace message {

class MessageFilter;
class MessageFlag;
class MessageServicePrivate;
class MessageSearchFilter;
class OutOfOfficeSettings;

/*!
 * @headerfile MessageService.hpp <bb/pim/message/MessageService>
 *
 * @brief The @c MessageService class provides access (read, write, and update) to PIM message data.
 *
 * @details This class is an interface to the messaging service. The messaging service manages
 * a database and controls a set of synchronization services. Functions in this class affect this
 * database. The signals in this class are emitted by changes in the messaging database, such as
 * adding or removing messages, or updating existing messages.
 *
 * You can use the signals in this class to listen for several types of messages. You can listen
 * for emails from supported account types (including POP, IMAP, and so on), SMS messages, and
 * MMS messages. However, you can't use these signals to listen for other message types, such as
 * BBM messages, WhatsApp messages, or messages from other non-PIM apps. There are no APIs
 * available to listen for messages from non-PIM apps.
 *
 * You can use this class to perform different operations on messages, such as sending, saving,
 * updating, removing, and retrieving. You can create an instance of this class and use it to
 * manage all of the messaging-related operations in your app. For example, here's how to perform
 * some common operations using the @c %MessageService:
 *
 * @code
 * MessageService messageService;
 * AccountService accountService;
 *
 * // Use MessageBuilder to build a message msg, and the required accountId from
 * // AccountService
 *
 * // Send it using an account
 * messageService.send(accountId , msg ) ;
 *
 * // Save using an account
 * messageService.save(accountId , msg ) ;
 *
 * // Remove a message
 * messageService.remove(accountId , msg.id() ) ;
 * @endcode
 *
 * Folders are containers for messages. The @c %MessageService class implements retrieval and
 * update operations on folders. Here's how you might use folders in your app:
 *
 * @code
 * QList<MessageFolder> folders = messageService.folders(accountId);
 * MessageFolder firstFolder = folders.at(0);
 * messageService.renameMessageFolder( accountId , firstFolder.id(), name )
 * @endcode
 *
 * You can also use the @c %MessageService to retrieve a list of messages and conversations,
 * as follows:
 *
 * @code
 * MessageFilter filter;
 * filter.insert(MessageFilter::Quantity ,QVariant("20") );
 * QList<Message> messageList = messageService.messages(accountId, filter);
 * QList<Conversation> conversationList = messageService.conversations(accountId,
 *                                         filter);
 * @endcode
 *
 * @see Message
 *
 * @xmlonly
 * <apigrouping group="App Integration/Message"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @permissions To use the messaging service, you must set the @c access_pimdomain_messages
 * permission to access email and PIN messages and the @c access_sms_mms permission
 * to access text messages. These permissions are set in the bar-descriptor.xml file
 * of your project.
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT MessageService: public QObject
{
Q_OBJECT

public:
    /*!
     * @brief Constructs a new @c MessageService.
     *
     * @param parent The parent object. This parameter is optional.
     *
     * @since BlackBerry 10.0.0
     */
    explicit MessageService(QObject *parent = 0);

    /*!
     * @brief Constructs a new @c MessageService for the specified account.
     *
     * @details A client that needs either text message service or email service
     * can choose between the services by passing in the appropriate @c accoundId.
     * This avoids listening to an unwanted service and can save some of the
     * client's CPU cycles.
     *
     * @example Passing @c TextMessagingAccountId as @c %accountId creates only a
     * ChatMessageService, not an EmailService.
     *
     * @param accountId The account ID to retrieve the messages from (for example, the unique
     * ID of an existing email account or SMS account).
     * @param parent The parent object. This parameter is optional.
     *
     * @since BlackBerry 10.3.0
     */
    explicit MessageService(bb::pim::account::AccountKey accountId, QObject *parent = 0);

    /*!
     * @brief Destroys this @c MessageService.
     *
     * @since BlackBerry 10.0.0
     */
    ~MessageService();

    /*!
     * @brief Retrieves a list of message IDs that fit the provided criteria.
     *
     * @details You can use this function to retrieve the IDs of messages from a specific account
     * that fit a set of criteria (represented by a @c MessageFilter), and then use this
     * to display the messages in your UI (for example, in a list view).
     *
     * @param accountId The account ID to retrieve the message IDs from (for example, the unique
     * ID of an existing email account).
     * @param filter The criteria to use to retrieve the message IDs.
     *
     * @return A @c QList of message IDs that fit the provided criteria.
     *
     * @since BlackBerry 10.0.0
     */
    QList<MessageKey> messageKeys(bb::pim::account::AccountKey accountId, const MessageFilter &filter) const;

    /*!
     * @brief Retrieves a list of messages that fit the provided criteria.
     *
     * @details You can use this function to retrieve the @c Message objects from a specific account
     * that fit a set of criteria (represented by a @c MessageFilter), and then use this
     * to display the messages in your UI (for example, in a list view).
     *
     * @param accountId The account ID to retrieve the messages from (for example, the unique
     * ID of an existing email account or SMS account).
     * @param filter The criteria to use to retrieve the messages.
     *
     * @return A @c QList of messages that fit the provided criteria.
     *
     * @since BlackBerry 10.0.0
     */
    QList<Message> messages(bb::pim::account::AccountKey accountId, const MessageFilter &filter) const;

    /*!
     * @brief Downloads a single message from the messaging service.
     *
     * @details This function is an asynchronous call to retrieve a message from the messaging service,
     * based on the provided account ID and message ID. You can use this function to download the
     * full message body when your app needs it.
     *
     * At the end of this operation, the @c MessageService emits the @c bodyDownloaded() signal. You can
     * use this signal to get the updated message by calling @c MessageService::message().
     *
     * @param accountId The account ID to download the message from (for example, the unique ID of
     * an existing email account).
     * @param messageId The unique ID of the message to download.
     *
     * @since BlackBerry 10.0.0
     */
    void downloadMessage(bb::pim::account::AccountKey accountId, MessageKey messageId);

    /*!
     * @brief Downloads partial or full contents of a single message from the messaging service.
     *
     * @details This function is an asynchronous call to retrieve the remaining message from the messaging service,
     * based on the provided account ID and message ID. You can use this function to download the partial or
     * full message body when your app needs it.
     *
     * At the end of this operation, the @c MessageService emits the @c bodyDownloaded() signal. You can
     * use this signal to get the updated message by calling @c MessageService::message().
     *
     * @param accountId The account ID to download the message from (for example, the unique ID of
     * an existing email account).
     * @param messageId The unique ID of the message to download.
     * @param partial If @c true and the underlying protocol supports partial bodies, then the partial message contents
     * are requested from the server; if the underlying protocol does not support partial bodies, then the full message
     * is requested. If @c false, the full message is downloaded. Note that partial bodies are not supported by all email protocols.
     *
     * @since BlackBerry 10.3.1
     */
    void downloadMessage(bb::pim::account::AccountKey accountId, MessageKey messageId, bool partial);

    /*!
     * @brief Retrieves a message with the provided account ID and message ID.
     *
     * @details You can use this function to access the full contents of a message (for example,
     * to display the message on a viewer screen in your app).
     *
     * @param accountId The account ID to retrieve the message from (for example, the unique ID of
     * an existing email account).
     * @param messageId The unique ID of the message to retrieve.
     *
     * @return The message with the provided account ID and message ID.
     *
     * @since BlackBerry 10.0.0
     */
    Message message(bb::pim::account::AccountKey accountId, MessageKey messageId) const;

    /*!
     * @brief Retrieves the number of messages with the provided account ID and that fit
     * the provided filter criteria.
     *
     * @details You can use this function to determine the size of the message data before
     * constructing a list of messages in the UI of your app.
     *
     * @param accountId The account ID to retrieve the number of messages from (for example, the
     * unique ID of an existing email account)
     * @param filter The criteria to use to retrieve the number of messages (for example, limiting
     * the results based on conversation ID, and so on).
     *
     * @return The number of messages with the provided account ID and that fit the provided
     * filter criteria.
     *
     * @since BlackBerry 10.0.0
     */
    int messageCount(bb::pim::account::AccountKey accountId, const MessageFilter &filter) const;

    /*!
     * @brief Retrieves a list of conversation IDs that fit the provided criteria.
     *
     * @details You can use this function to retrieve a list of conversation IDs from a specific
     * account that fit a certain set of criteria (represented by a @c MessageFilter), and then use this
     * to display the conversations in your UI (for example, in a conversation view).
     *
     * Obtaining the list of keys allows you to maintain a mapping of UI list index to conversation IDs
     * in your UI.
     *
     * @param accountId The account ID to retrieve the conversation IDs from (for example, the
     * unique ID of an existing email account).
     * @param filter The criteria to use to retrieve the conversation IDs.
     *
     * @return A @c QList of conversation IDs that fit the provided criteria.
     *
     * @since BlackBerry 10.0.0
     */
    QList<ConversationKey> conversationKeys(bb::pim::account::AccountKey accountId,
            const MessageFilter &filter) const;

    /*!
     * @brief Retrieves a list of conversations that fit the provided criteria.
     *
     * @details You can use this function to retrieve the @c Conversation objects from a specific
     * account that fit a set of criteria (represented by a @c MessageFilter), and then use this
     * to display the conversations in your UI (for example, in a conversation view).
     *
     * @param accountId The account ID to retrieve the conversations from (for example, the unique
     * ID of an existing email account or SMS account).
     * @param filter The criteria to use to retrieve the conversations.
     *
     * @return A @c QList of conversations that fit the provided criteria.
     *
     * @since BlackBerry 10.0.0
     */
    QList<Conversation> conversations(bb::pim::account::AccountKey accountId,
            const MessageFilter &filter) const;

    /*!
     * @brief Retrieves a conversation with the provided account ID and conversation ID.
     *
     * @details You can use this function to access the full contents of a conversation (for example,
     * to display the conversation on a viewer screen in your app).
     *
     * @param accountId The account ID to retrieve the conversation from (for example, the unique ID of
     * an existing email account).
     * @param messageId The unique ID of the conversation to retrieve.
     *
     * @return The conversation with the provided account ID and conversation ID.
     *
     * @since BlackBerry 10.0.0
     */
    Conversation conversation(bb::pim::account::AccountKey accountId,
            ConversationKey conversationId) const;

    /*!
     * @brief Retrieves the number of conversations with the provided account ID.
     *
     * @details You can use this function to determine the size of the conversation data before
     * constructing a list of conversations in the UI of your app.
     *
     * @param accountId The account ID to retrieve the number of conversations from (for example, the
     * unique ID of an existing email account)
     *
     * @return The number of conversations with the provided account ID.
     *
     * @since BlackBerry 10.0.0
     */
    int conversationCount(bb::pim::account::AccountKey accountId) const;

    /*!
     * @brief Retrieves a list of messages in a conversation that fit the provided criteria.
     *
     * @param accountId The account ID to retrieve the messages from (for example, the unique
     * ID of an existing email account).
     * @param conversationId The ID of a pre-existing conversation.
     * @param filter The filter criteria to use to retrieve the messages.
     *
     * @return A @c QList of messages with the provided conversation ID and that fit the
     * provided criteria.
     *
     * @since BlackBerry 10.0.0
     */
    QList<Message> messagesInConversation(bb::pim::account::AccountKey accountId,
            ConversationKey conversationId, const MessageFilter &filter) const;

    /*!
     * @brief Retrieves a list of folders in the provided account.
     *
     * @details You can use this function to display a folder view in the UI of your app.
     *
     * @param accountId The account ID to retrieve the folders from (for example, the unique
     * ID of an existing email account).
     *
     * @return A @c QList of folders in the provided account.
     *
     * @since BlackBerry 10.0.0
     */
    QList<MessageFolder> folders(bb::pim::account::AccountKey accountId) const;

    /*!
     * @brief Retrieves a list of folders and a suggested folder for the provided message.
     *
     * @details You can use this function to display a folder view in the UI of your app, as
     * well as suggest a folder in which to file the provided message.
     *
     * @param accountId The account ID to retrieve the folders from (for example, the unique
     * ID of an existing email account).
     * @param messageId The message ID of a message in the account that you want a suggested
     * folder for.
     * @param suggestedFolderId This function returns a folder ID in this parameter, which
     * represents a suggested folder to file the provided message in. This value is invalid
     * if an invalid account ID or message ID is provided.
     *
     * @return A @c QList of folders, or an empty list if an invalid account ID or message ID is
     * provided.
     *
     * @since BlackBerry 10.0.0
     */
    QList<MessageFolder> foldersWithSuggestion(bb::pim::account::AccountKey accountId, MessageKey messageId, MessageFolderKey* suggestedFolderId) const;

    /*!
     * @brief Suggests a possible folder for filing a given message.
     *
     * @param accountId The account ID of an account (for example, the account ID of an existing email account).
     * @param messageId The message ID of a message (for example, the message ID of an existing email message).
     *
     * @return The suggested folder ID for filing a message, or @c UndefinedKey in the case of an invalid account ID or message ID.
     *
     * @since BlackBerry 10.0.0
     */
     MessageFolderKey folderSuggestion(bb::pim::account::AccountKey accountId, MessageKey messageId) const;

    /*!
     * @brief Retrieves a folder with the provided account ID and folder ID.
     *
     * @param accountId The account ID to retrieve the folder from (for example, the unique
     * ID of an existing email account).
     * @param folderId A unique folder ID.
     *
     * @return The folder with the provided account ID and folder ID.
     *
     * @since BlackBerry 10.0.0
     */
    MessageFolder folder(bb::pim::account::AccountKey accountId, MessageFolderKey folderId) const;

    /*!
     * @brief Retrieves a list of messages in the provided folder that fit the provided
     * criteria.
     *
     * @details You can use this function to view messages in a specific folder that fit a set
     * of criteria
     *
     * @param accountId The account ID to retrieve the messages from (for example, the unique
     * ID of an existing email account).
     * @param folderId The ID of the folder to retrieve the messages from.
     * @param filter The set of criteria to use to retrieve the messages.
     *
     * @return A @c QList of messages in the provided folder that fit the provided
     * criteria.
     *
     * @since BlackBerry 10.0.0
     */
    QList<Message> messagesInFolder(bb::pim::account::AccountKey accountId, MessageFolderKey folderId,
            const MessageFilter &filter) const;

    /*!
     * @brief Marks a message as read.
     *
     * @details You can use this function to mark a message with a specific account ID and
     * message ID as read. After the status is changed, the @c messageUpdated() signal is
     * emitted. You can listen for this signal and update the list of messages in your UI
     * accordingly.
     *
     * @param accountId The account ID of the message to update (for example, the unique
     * ID of an existing email account).
     * @param messageId The message ID of the message to update.
     *
     * @since BlackBerry 10.0.0
     */
    void markRead(bb::pim::account::AccountKey accountId, MessageKey messageId);

    /*!
     * @brief Marks a message as unread.
     *
     * @details You can use this function to mark a message with a specific account ID and
     * message ID as unread. After the status is changed, the @c messageUpdated() signal is
     * emitted. You can listen for this signal and update the list of messages in your UI
     * accordingly.
     *
     * @param accountId The account ID of the message to update (for example, the unique
     * ID of an existing email account).
     * @param messageId The message ID of the message to update.
     *
     * @since BlackBerry 10.0.0
     */
    void markUnread(bb::pim::account::AccountKey accountId, MessageKey messageId);

    /*!
     * @brief Marks a conversation as read.
     *
     * @details You can use this function to mark a conversation with a specific account ID and
     * conversation ID as read. This function is used only for SMS accounts.
     *
     * @param accountId The account ID of the conversation to update.
     * @param conversationId The conversation ID of the conversation to update.
     *
     * @since BlackBerry 10.0.0
     */
    void markRead(bb::pim::account::AccountKey accountId, ConversationKey conversationId);

    /*!
     * @brief Marks a conversation as unread.
     *
     * @details You can use this function to mark a conversation with a specific account ID and
     * conversation ID as unread. This function is used only for SMS accounts.
     *
     * @param accountId The account ID of the conversation to update.
     * @param conversationId The conversation ID of the conversation to update.
     *
     * @since BlackBerry 10.0.0
     */
    void markUnread(bb::pim::account::AccountKey accountId, ConversationKey conversationId);

    /*!
     * @brief Mark a message as hidden.
     *
     * @details You can use this function to mark a message with a specific account ID and
     * message ID as hidden. After the status is changed, the @c messageUpdated() signal is
     * emitted. You can listen for this signal and update the list of messages in your UI
     * accordingly.
     *
     * @param accountId The account ID of the message to update (for example, the unique
     * ID of an existing email account).
     * @param messageId The message ID of the message to update.
     *
     * @since BlackBerry 10.3.0
     */
    void hide(bb::pim::account::AccountKey accountId, MessageKey messageId);

    /*!
     * @brief Mark a message as unhidden.
     *
     * @details You can use this function to mark a message with a specific account ID and
     * message ID as unhidden. After the status is changed, the @c messageUpdated() signal is
     * emitted. You can listen for this signal and update the list of messages in your UI
     * accordingly.
     *
     * @param accountId The account ID of the message to update (for example, the unique
     * ID of an existing email account).
     * @param messageId The message ID of the message to update.
     *
     * @since BlackBerry 10.3.0
     */
    void unHide(bb::pim::account::AccountKey accountId, MessageKey messageId);

    /*!
     * @brief Marks a conversation as hidden.
     *
     * @details You can use this function to mark a conversation with a specific account ID and
     * conversation ID as hidden. This function is used only for SMS accounts.
     *
     * @param accountId The account ID of the conversation to update.
     * @param conversationId The conversation ID of the conversation to update.
     *
     * @since BlackBerry 10.3.0
     */
    void hide(bb::pim::account::AccountKey accountId, ConversationKey conversationId);

    /*!
     * @brief Marks a conversation as unhidden.
     *
     * @details You can use this function to mark a conversation with a specific account ID and
     * conversation ID as unhidden. This function is used only for SMS accounts.
     *
     * @param accountId The account ID of the conversation to update.
     * @param conversationId The conversation ID of the conversation to update.
     *
     * @since BlackBerry 10.3.0
     */
    void unHide(bb::pim::account::AccountKey accountId, ConversationKey conversationId);

    /*!
     * @brief Marks messages as hidden prior to the specified date.
     *
     * @param accountIds A list of account IDs for which to mark messages as read or unread, or to delete messages from.
     * @param filter The @c MessageupdateFilter used for specifying options, such as date prior, folder ID, and so on.
     *
     * @since BlackBerry 10.3.0
     */
    void hidePrior(QList<bb::pim::account::AccountKey> accountIds, const MessageUpdateFilter &filter);

    /*!
     * @brief Marks messages as un-hidden prior to the specified date.
     *
     * @param accountIds A list of account IDs for which to mark messages as read or unread, or to delete messages from.
     * @param filter The @c MessageupdateFilter used for specifying options, such as date prior, folder ID, and so on.
     *
     * @since BlackBerry 10.3.0
     */
    void unHidePrior(QList<bb::pim::account::AccountKey> accountIds, const MessageUpdateFilter &filter);

    /*!
     * @brief Sends a message.
     *
     * @details You can use a @c MessageBuilder to create a message, and then call this function
     * to send the message. To reply to a message, you can call @c MessageBuilder::create() and
     * provide the account ID and existing message to create a reply.
     *
     * @param accountId The account ID of the message to send (for example, the unique ID
     * of an existing email account).
     * @param message The message to send, created using a @c %MessageBuilder.
     *
     * @return The message ID of the sent message.
     *
     * @since BlackBerry 10.0.0
     */
    MessageKey send(bb::pim::account::AccountKey accountId, const Message &message);

    /*!
     * @brief Sends a reply to a message if the underlying provider supports SmartReply.
     *
     * @details You can use a @c MessageBuilder to create a message and then call this function
     * to send the message. To reply to a message, you can call @c MessageBuilder::create() and
     * provide the account ID and existing message to create a reply.
     * In order to use @c %smartReply(), you provide either the delta of changes in the body of the message
     * or the entire contents of the body, depending on whether @c %isOrignalMsgEdited is set. Also, a valid @c originalMessageId
     * needs to be set on the @c %message using @c MessageBuilder::origMessageId(). This is usually the unique
     * ID of the message which is being replied to.
     *
     * @param accountId The account ID of the message to send (for example, the unique ID
     * of an existing email account).
     * @param message The message to send, created using a @c %MessageBuilder.
     * @param isOrignalMsgEdited @c True if the provider should treat the contents of @c %message as
     * the delta of changes, @c false if the entire message is provided.
     *
     * @return The message ID of the sent message.
     *
     * @since BlackBerry 10.0.0
     */
    MessageKey smartReply(bb::pim::account::AccountKey accountId, const Message &message, bool isOrignalMsgEdited);

    /*!
     * @brief Forwards a message if the underlying provider supports SmartForward.
     *
     * @details You can use a @c MessageBuilder to create a message and then call this function
     * to send the message. To forward a message, you can call @c MessageBuilder::create() and
     * provide the account ID and existing message to create a forward.
     * In order to use @c %smartForward(), you provide either the delta of changes in the body of the message
     * or the entire contents of the body, depending on whether @c %isOrignalMsgEdited is set. Also, a valid @c originalMessageId
     * needs to be set on the @c %message using @c MessageBuilder::origMessageId(). This is usually the unique
     * ID of the message which is being forwarded.
     *
     * @param accountId The account ID of the message to send (for example, the unique ID
     * of an existing email account).
     * @param message The message to send, created using a @c %MessageBuilder.
     * @param isOrignalMsgEdited @c True if the provider should treat the contents of @c %message as
     * the delta of changes, @c false if the entire message is provided.
     *
     * @return The message ID of the sent message.
     *
     * @since BlackBerry 10.0.0
     */
    MessageKey smartForward(bb::pim::account::AccountKey accountId, const Message &message, bool isOrignalMsgEdited);

    /*!
     * @brief Saves a draft message.
     *
     * @details You can use a @c MessageBuilder to create a message, and then call this function
     * to save the message as a draft.
     *
     * @param accountId The account ID of the message to save (for example, the unique ID
     * of an existing email account).
     * @param message The message to save, created using a @c %MessageBuilder.
     *
     * @return The message ID of the saved message.
     *
     * @since BlackBerry 10.0.0
     */
    MessageKey save(bb::pim::account::AccountKey accountId, const Message &message);

    /*!
     * @brief Saves a conversation.
     *
     * @details You can use a @c ConversationBuilder to create a conversation, and then call this
     * function to save the conversation. This function is used only for SMS accounts.
     *
     * @param accountId The account ID of the conversation to save.
     * @param conversation The conversation to save, created using a @c %ConversationBuilder.
     *
     * @return The conversation ID of the saved conversation.
     *
     * @since BlackBerry 10.0.0
     */
    ConversationKey save(bb::pim::account::AccountKey accountId, const Conversation &conversation);

    /*!
     * @brief Removes a message from an account.
     *
     * @details You can use this function to delete a message from an account.
     *
     * @param accountId The account ID of the message to remove (for example, the unique ID
     * of an existing email account).
     * @param messageId The message ID of the message to delete.
     *
     * @since BlackBerry 10.0.0
     */
    void remove(bb::pim::account::AccountKey accountId, MessageKey messageId);

    /*!
     * @brief Removes a conversation from an account.
     *
     * @details You can use this function to delete a conversation from an account.
     *
     * @param accountId The account ID of the conversation to remove.
     * @param conversationId The conversation ID of the conversation to delete.
     *
     * @since BlackBerry 10.0.0
     */
    void remove(bb::pim::account::AccountKey accountId, ConversationKey conversationId);

    /*!
     * @brief Files a message in a folder.
     *
     * @param accountId The account ID of the message to file (for example, the unique ID
     * of an existing email account).
     * @param messageId The message ID of the message to file.
     * @param folderId The folder ID of the folder to file the message in.
     *
     * @since BlackBerry 10.0.0
     */
    void file(bb::pim::account::AccountKey accountId, MessageKey messageId, MessageFolderKey folderId);

    /*!
     * @brief Files multiple messages from the same account in a folder.
     *
     * @param accountId The account ID of the messages to file (for example, the unique ID
     * of an existing email account).
     * @param messageIds The list of message IDs of the messages to file.
     * @param folderId The folder ID of the folder to file the messages in.
     *
     * @since BlackBerry 10.1.0
     */
    void file(bb::pim::account::AccountKey accountId, QList<MessageKey> messageIds, MessageFolderKey folderId);

    /*!
     * @brief Files a conversation in a folder.
     *
     * @param accountId The account ID of the conversation to file (for example, the unique ID
     * of an existing email account).
     * @param conversationId The conversation ID of the conversation to file.
     * @param folderId The folder ID of the folder to file the conversation in.
     *
     * @since BlackBerry 10.0.0
     */
    void file(bb::pim::account::AccountKey accountId, ConversationKey conversationId, MessageFolderKey folderId);

    /*!
     * @brief Sets the follow-up flag of a message.
     *
     * @details After the follow-up flag is set, the @c messageUpdated() signal is emitted so
     * you can update the message in the UI of your app.
     *
     * @param accountId The account ID of the message to flag (for example, the unique ID
     * of an existing email account).
     * @param messageId The message ID of the message to flag.
     * @param followupFlag The follow-up flag to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setFollowupFlag(bb::pim::account::AccountKey accountId, MessageKey messageId,
            const MessageFlag &followupFlag);

    /*!
     * @brief Resets the follow-up flag of a message.
     *
     * @details After the follow-up flag is reset, the @c messageUpdated() signal is emitted so
     * you can update the message in the UI of your app.
     *
     * @param accountId The account ID of the message to flag (for example, the unique ID
     * of an existing email account).
     * @param messageId The message ID of the message to flag.
     *
     * @since BlackBerry 10.0.0
     */
    void resetFollowupFlag(bb::pim::account::AccountKey accountId, MessageKey messageId);

    /*!
     * @brief Sets the priority of a message.
     *
     * @param accountId The account ID of the message to set the priority of (for example,
     * the unique ID of an existing email account).
     * @param messageId The message ID of the message to set the priority of.
     * @param priority The priority to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setPriority(bb::pim::account::AccountKey accountId, MessageKey messageId,
            MessagePriority::Type priority);

    /*!
     * @brief Sets the status of a message.
     *
     * @details This function is used only for SMS accounts.
     *
     * @param accountId The account ID of the message to set the status of.
     * @param messageId The message ID of the message to set the status of.
     * @param status The status to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setStatus(bb::pim::account::AccountKey accountId, MessageKey messageId,
            MessageStatus::Types status);

    /*!
     * @brief Sets the transmission status of a message.
     *
     * @details This function is used only for SMS accounts.
     *
     * @param accountId The account ID of the message to set the transmission status of.
     * @param messageId The message ID of the message to set the transmission status of.
     * @param transmissionStatus The transmission status to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setTransmissionStatus(bb::pim::account::AccountKey accountId, MessageKey messageId,
            MessageTransmissionStatus::Type transmissionStatus);

    /*!
     * @brief Sets the status of a conversation.
     *
     * @details This function is used only for SMS accounts.
     *
     * @param accountId The account ID of the conversation to set the status of.
     * @param conversationId The conversation ID of the conversation to set the status of.
     * @param status The status to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setStatus(bb::pim::account::AccountKey accountId, ConversationKey conversationId,
            ConversationStatus::Types status);

    /*!
     * @brief Retrieves a list of attachments that fit the provided criteria.
     *
     * @details You can use this function to retrieve the @c Attachment objects from a specific account,
     * or all accounts, that fit a set of criteria (represented by a @c AttachmentFilter), and then use this
     * to display the attachments in your UI (for example, in a list view).
     * Attachments for all accounts are retrieved if the @c accountId is equal to @c bb::pim::account::InvalidKey.
     * If a valid @c accountId is specified along with an empty @c conversationId, then all attachments are
     * retrieved for that account only.  Specifying a valid @c conversationId along with its corresponding
     * @c accountId retrieves the attachments that are contained within that single conversation.
     *
     * @param accountId The account ID to retrieve the attachments from (for example, the unique
     * ID of an existing email account or SMS account).
     * @param conversationId The ID of a pre-existing conversation.
     * @param filter The criteria to use to retrieve the attachments.
     *
     * @return A @c QList of attachments that fit the provided criteria.
     *
     * @since BlackBerry 10.2.0
     */
    QList<FileAttachment> attachments(bb::pim::account::AccountKey accountId,
            ConversationKey conversationId, const AttachmentFilter &filter) const;

    /*!
     * @brief Downloads the attachment of a message.
     *
     * @param accountId The account ID of the message to retrieve the attachment of (for
     * example, the unique ID of an existing email account).
     * @param messageId The ID of the message to retrieve the attachment of.
     * @param attachmentId The ID of the attachment to retrieve.
     *
     * @since BlackBerry 10.0.0
     */
    void downloadAttachment(bb::pim::account::AccountKey accountId, MessageKey messageId,
            AttachmentKey attachmentId);

    /*!
     * @brief Performs a local search for messages that fit the provided criteria.
     *
     * @param accountId The account ID to search (for example, the unique ID of an existing email
     * account). If you pass @c bb::pim::message::UndefinedKey, then the search will be across all
     * accounts.
     * @param filter The criteria to use for the search.
     *
     * @return A @c QList of messages that fit the provided criteria.
     *
     * @since BlackBerry 10.0.0
     */
    QList<Message> searchLocal(bb::pim::account::AccountKey accountId, const MessageSearchFilter &filter);

     /*!
     * @brief Performs a remote search on the messaging server for messages that fit the
     * provided criteria.
     *
     * @param accountId The account ID to search (for example, the unique ID of an existing email
     * account). The account ID must not be @c bb::pim::message::UndefinedKey. Unlike @c searchLocal(),
     * the @c searchRemote() function does not support search in all accounts simultaneously.
     * @param filter The criteria to use for the search.
     *
     * @return A @c QList of messages that fit the provided criteria, or an empty @c QList if the
     * account ID was specified as @c bb::pim::message::UndefinedKey.
     *
     * This method is deprecated. Use searchRemote that takes additional parameter totalItemsOnServer.
     *
     * @since BlackBerry 10.0.0
     */
    QList<Message> searchRemote(bb::pim::account::AccountKey accountId, const MessageSearchFilter &filter) BB_DEPRECATED;

    /*!
     * @brief Performs a remote search on the messaging server for messages that fit the
     * provided criteria.
     *
     * @param accountId The account ID to search (for example, the unique ID of an existing email
     * account). The account ID must not be @c bb::pim::message::UndefinedKey. Unlike @c searchLocal(),
     * the @c searchRemote() function does not support search in all accounts simultaneously.
     * @param filter The criteria to use for the search.
     * @param totalItemsOnServer The number of items in the result set returned by the server. A valid pointer should be passed in
     *                           to get the number of items in a result set back.
     *
     * @return A @c QList of messages that fit the provided criteria, or an empty @c QList if the
     * account ID was specified as @c bb::pim::message::UndefinedKey.
     *
     * @since BlackBerry 10.3.0
     */
    QList<Message> searchRemote(bb::pim::account::AccountKey accountId, const MessageSearchFilter &filter, quint32* totalItemsOnServer);

    /*!
     * @brief Sets the "is typing" status for a conversation.
     *
     * @details This function sets the "is typing" status for conversations in accounts where the underlying
     * protocol supports the idea of presence. This function is not used for SMS or MMS accounts.
     *
     * @param accountId The account ID.
     * @param conversationId The conversation ID.
     * @param typing If @c true the user is typing, if @c false the user is not typing.
     *
     * @since BlackBerry 10.0.0
     */
    void setTypingStatus(bb::pim::account::AccountKey accountId, ConversationKey conversationId,
            bool typing);

    /*!
     * @brief Renames a message folder.
     *
     * @details After the folder is renamed, the @c folderUpdated() signal is emitted, and you can
     * listen for this signal and update the UI of your app accordingly.
     *
     * @param accountId The account ID of the folder to rename (for example, the unique ID of an existing
     * email account).
     * @param folderId The ID of the folder to rename.
     * @param name The new name of the folder.
     *
     * @since BlackBerry 10.0.0
     */
    void renameMessageFolder(bb::pim::account::AccountKey accountId ,MessageFolderKey folderId, const QString &name);

    /*!
     * @brief Adds a message folder.
     *
     * @details After the folder is added, the @c folderAdded() signal is emitted, and you can
     * listen for this signal and update the UI of your app accordingly.
     *
     * @param accountId The account ID of the folder to add (for example, the unique ID of an existing
     * email account).
     * @param folderId The ID of the folder to add.
     * @param name The name of the folder.
     *
     * @since BlackBerry 10.0.0
     */
    void addMessageFolder(bb::pim::account::AccountKey accountId ,MessageFolderKey  folderId, const QString &name);

    /*!
     * @brief Deletes a message folder.
     *
     * @details After the folder is deleted, the @c folderRemoved() signal is emitted, and you can
     * listen for this signal and update the UI of your app accordingly.
     *
     * @param accountId The account ID of the folder to delete (for example, the unique ID of an existing
     * email account).
     * @param folderId The ID of the folder to delete.
     *
     * @since BlackBerry 10.0.0
     */
    void deleteMessageFolder(bb::pim::account::AccountKey accountId ,MessageFolderKey folderId);

    /*!
     * @brief Enables synchronization for a message folder.
     *
     * @param accountId The account ID of an account (for example, the account ID of an existing email account).
     * @param folderId The message folder ID.
     * @param syncConfig If @c true synchronization is enabled for the message folder, if @c false synchronization is
     * disabled for the message folder.
     *
     * @return @c true if synchronization configuration was set successfully, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
     bool setFolderSyncConfig(bb::pim::account::AccountKey accountId ,MessageFolderKey folderId, bool syncConfig);

     /*!
     * @brief Indicates whether the provided feature is supported by an account.
     *
     * @details You can use this function to determine if a specific feature is supported by an
     * account, such as folder management.
     *
     * @param accountId The account ID to query (for example, the unique ID of an existing
     * email account).
     * @param feature The feature to query.
     *
     * @return @c true if the feature is supported by the account, @c false otherwise.
      *
      * @since BlackBerry 10.0.0
     */
    bool isFeatureSupported(bb::pim::account::AccountKey accountId, MessageServiceFeature::Type feature);

    /*!
     * @brief Deletes all messages prior to the provided date and time.
     *
     * @param accountIds A list of account IDs to delete messages from.
     * @param dateTime The date and time, expressed in yyyy-MM-dd hh:mm:ss.zzzzzz format (for
     * example, 2012-07-25 23:59:59.999999).
     *
     * @since BlackBerry 10.0.0
     */
    void deletePrior(QList<bb::pim::account::AccountKey> accountIds,const QString& dateTime);


    /*!
     * @brief Deletes all messages prior to the provided date and time and that meet the given search filter criteria.
     *
     * @param accountIds A list of account IDs to delete messages from.
     * @param filter The criteria to use for the search.
     * @param dateTime The date and time representing the upperbound time limit on the bulk delete action,
     * expressed in yyyy-MM-dd hh:mm:ss.zzzzzz format (for example, 2012-07-25 23:59:59.999999).
     * @param srchExecDateTime The date and time when the search was executed, expressed in
     *  yyyy-MM-dd hh:mm:ss.zzzzzz format (for example, 2012-07-25 23:59:59.999999).
     *
     * @since BlackBerry 10.1.0
     */
    void deletePriorSearchResults(QList<bb::pim::account::AccountKey> accountIds, const MessageSearchFilter &filter,
            const QString& dateTime, const QString& srchExecDateTime);

    /*!
     * @brief Marks all messages prior to the provided date and time as read or unread.
     *
     * @param accountIds A list of account IDs for which to mark messages as read or unread.
     * @param dateTime The date and time, expressed in yyyy-MM-dd hh:mm:ss.zzzzzz format (for
     * example, 2012-07-25 23:59:59.999999).
     * @param markRead If @c true the messages are marked as read, if @c false the messages are
     * marked as unread.
     *
     * @since BlackBerry 10.0.0
     */
    void markPrior(QList<bb::pim::account::AccountKey> accountIds,const QString& dateTime, bool markRead);

    /*!
     * @brief Marks all messages prior to the provided date and time and that meet the given search filter criteria,
     *  as read or unread.
     *
     * @param accountIds A list of account IDs for which to mark messages as read or unread.
     * @param filter The criteria to use for the search.
     * @param dateTime The date and time representing the upperbound time limit on the bulk mark prior action,
     * expressed in yyyy-MM-dd hh:mm:ss.zzzzzz format (for example, 2012-07-25 23:59:59.999999).
     * @param srchExecDateTime The date and time when the search was executed, expressed in
     *  yyyy-MM-dd hh:mm:ss.zzzzzz format (for example, 2012-07-25 23:59:59.999999).
     * @param markRead If @c true the messages are marked as read, if @c false the messages are
     * marked as unread.
     *
     * @since BlackBerry 10.1.0
     */
    void markPriorSearchResults (QList<bb::pim::account::AccountKey> accountIds, const MessageSearchFilter &filter,
            const QString& dateTime, const QString& srchExecDateTime, bool markRead);

    /*!
     * @brief Marks messages as read or unread, or deletes all messages prior to the
     * provided date and time and that meet the given @c MarkOrDeletePriorFilter criteria.
     *
     * @param accountIds A list of account IDs for which to mark messages as read or unread, or to delete messages from.
     * @param filter The @c MarkOrDeletePriorFilter used for specifying options, such as date prior, folder ID, and so on.
     * @param operationType Specifies the type of operation to perform, for example: @c MarkOrDeletePriorOp::MarkPriorRead,
     * @c MarkOrDeletePriorOp::MarkPriorUnread, or @c MarkOrDeletePriorOp::DeletePrior.
     *
     * @since BlackBerry 10.1.0
     */
    void markOrDeletePrior(QList<bb::pim::account::AccountKey> accountIds, const MarkOrDeletePriorFilter &filter, const MarkOrDeletePriorOp::Type &operationType);

    /*!
     * @brief Performs a bulk operation on a list of messages.
     *
     * @details This function supports the following operations: mark messages read, mark messages unread, delete messages and hide messages.
     *          Messages must be supplied in batches of 100 or less per account.
     *          Exceeding 100 messages per account will cause the operation to fail and no message will be processed.
     * @param data A map containing account IDs and corresponding list of messages to be updated.
     * @param operationType Specifies the type of operation to perform (mark read/unread, hide, or delete).
     *
     * @since BlackBerry 10.3.1
     */
    void bulkOperationOnMessages(const QMap<bb::pim::account::AccountKey,QList<MessageKey> > &data, MessageUpdateFilter::UpdateOperation operationType);

    /*!
     * @brief Performs a bulk operation on a list of conversations.
     *
     * @details This operation supports the following operations: mark conversations read, mark conversations unread, delete conversations and hide conversations.
     *          Conversations must be supplied in batches of 100 or less per account.
     *          Exceeding 100 conversations per account will cause the operation to fail and no conversation will be processed.
     * @param data A map containing account IDs and corresponding list of conversations to be updated.
     * @param operationType Specifies the type of operation to perform (mark read/unread, hide or delete).
     *
     * @since BlackBerry 10.3.1
     */
    void bulkOperationOnConversations(const QMap<bb::pim::account::AccountKey,QList<ConversationKey> > &data, MessageUpdateFilter::UpdateOperation operationType);

    /*!
     * @brief Marks messages as read or unread, or deletes all messages prior to the
     * provided date and time and that meet the given search filter criteria.
     *
     * @param accountIds A list of account IDs for which to mark messages as read or unread, or to delete messages from.
     * @param filter The criteria to use for the search.
     * @param dateTime The date and time representing the upperbound time limit on the bulk mark prior action,
     * expressed in yyyy-MM-dd hh:mm:ss.zzzzzz format (for example, 2012-07-25 23:59:59.999999).
     * @param srchExecDateTime The date and time when the search was executed, expressed in
     *  yyyy-MM-dd hh:mm:ss.zzzzzz format (for example, 2012-07-25 23:59:59.999999).
     * @param operationType Specifies the type of operation to perform, for example: @c MarkOrDeletePriorOp::MarkPriorRead,
     * @c MarkOrDeletePriorOp::MarkPriorUnread, or @c MarkOrDeletePriorOp::DeletePrior.
     *
     * @since BlackBerry 10.1.0
     */
    void markOrDeletePriorForSearch(QList<bb::pim::account::AccountKey> accountIds, const MessageSearchFilter &filter,
            const QDateTime& dateTime, const QDateTime& srchExecDateTime, const MarkOrDeletePriorOp::Type &operationType);
    /*!
     * @brief Sets the out-of-office option for an account.
     *
     * @param accountId The account ID to set the out-of-office option for (for example, the
     * unique ID of an existing email account).
     * @param outOfOffice The out-of-office option to set.
     *
     * @since BlackBerry 10.0.0
     */
    void  setOutOfOffice(bb::pim::account::AccountKey accountId, const OutOfOfficeSettings &outOfOffice);

    /*!
     * @brief Retrieves the out-of-office option for an account.
     *
     * @param accountId The account ID to retrieve the out-of-office option for (for example, the
     * unique ID of an existing email account).
     *
     * @return The out-of-office option for the provided account.
     *
     * @since BlackBerry 10.0.0
     */
    OutOfOfficeSettings outOfOffice(bb::pim::account::AccountKey accountId) const;

    /*!
     * @brief Synchronizes all messages in a set of accounts.
     *
     * @param accountIds The list of account IDs to synchronize (for example, the unique IDs
     * of existing email accounts).
     *
     * @since BlackBerry 10.0.0
     */
    void syncAccounts(const QList<bb::pim::account::AccountKey>& accountIds);

    /*!
     * @brief Synchronizes a folder in an account.
     *
     * @param accountId The account ID of the folder to synchronize (for example, the unique ID
     * of an existing email account).
     * @param folderId The folder ID of the folder to synchronize.
     *
     * @since BlackBerry 10.0.0
     */
    void syncFolder(bb::pim::account::AccountKey accountId, MessageFolderKey folderId ) const;


    /*!
     * @brief Pre-fetch a message from the messaging service.
     *
     * @details This function indicates to the messaging service that the provided message should
     * be pre-fetched for faster retrieval. You can use this function to indicate that a message
     * is about to be viewed, which would then improve the retrieval time of a subsequent call to
     * @c MessageService::message().
     *
     * @param accountId The account ID of the message to pre-fetch id of the account (for example,
     * the unique ID of an existing email account).
     * @param messageId The message ID of the message to pre-fetch.
     *
     * @since BlackBerry 10.0.0
     */
    void messagePreFetch(bb::pim::account::AccountKey accountId, MessageKey messageId) const;


    /*!
     * @brief Retrieves a list of message transactions for an account.
     *
     * @details You can use this function to sync any messaging changes from the message service.
     *
     * @param accountId The account ID of the account to retrieve message transactions from.
     *
     * @since BlackBerry 10.0.0
     */
    QList<MessageTransaction> messageTransactions(bb::pim::account::AccountKey accountId)const;

    /*!
     * @brief Retrieves a list of message transactions for an account.
     *
     * @details You can use this function to sync any messaging changes from the message service.
     *
     * @param accountId The account ID of the account to retrieve message transactions from.
     * @param limit The max number of transactions to get, if 0 defaults to 100.
     *
     * @since BlackBerry 10.3.0
     */
    QList<MessageTransaction> messageTransactions(bb::pim::account::AccountKey accountId, unsigned int limit)const;

    /*!
     * @brief Clears the transaction logs up to the specified transaction key for an account.
     *
     * @param accountId The account ID of the account to clear the transaction logs for.
     * @param id The transaction key of the transaction up to which to clear the logs.
     *
     * @return @c true if the logs were cleared successfully, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool clearTransactions(bb::pim::account::AccountKey accountId , TransactionKey id) const;

    /*!
     * @brief Returns the total count of transaction logs entries for an account.
     *
     * @param accountId The account ID of the account to count transaction entries.
     *
     * @return a positive int value matching the total transaction entries, 0 if none exist.
     *
     * @since BlackBerry 10.3.0
     */
    int countTransactions(bb::pim::account::AccountKey accountId) const;

Q_SIGNALS:
    /*!
     * @brief Emitted when an account is added to the message service.
     *
     * @param accountId The account ID of the account that was added (for example, if a new email
     * account was added).
     *
     * @since BlackBerry 10.0.0
     */
    void accountAdded(bb::pim::account::AccountKey accountId);

    /*!
     * @brief Emitted when an account is removed from the message service.
     *
     * @param accountId The account ID of the account that was removed (for example, if an existing
     * email account was removed).
     *
     * @since BlackBerry 10.0.0
     */
    void accountRemoved(bb::pim::account::AccountKey accountId);

    /*!
     * @brief Emitted when an account is updated in the message service.
     *
     * @param accountId The account ID of the account that was updated (for example, if an existing
     * email account was updated with a name change).
     *
     * @since BlackBerry 10.0.0
     */
    void accountUpdated(bb::pim::account::AccountKey accountId);

    /*!
     * @brief Emitted when an account is connected.
     *
     * @param accountId The account ID of the account that is connected.
     *
     * @since BlackBerry 10.2.0
     */
    void accountConnected(bb::pim::account::AccountKey accountId);

    /*!
     * @brief Emitted when an account is marked invalid.
     *
     * @param accountId The account ID of the account that is invalid (for example, if
     * a user password changed).
     *
     * @since BlackBerry 10.2.0
     */
    void accountInvalidated(bb::pim::account::AccountKey accountId);

    /*!
     * @brief Emitted when the default account in the message service is changed.
     *
     * @param accountId The account ID of the new default account.
     *
     * @since BlackBerry 10.0.0
     */
    void accountDefaultChanged(bb::pim::account::AccountKey accountId);

    /*!
     * @brief Emitted when messages are added to the message service.
     *
     * @details This signal is usually emitted on initial sync or if the server has been out of sync
     * for some time.
     *
     * @param accountId The account ID that the messages were added to.
     * @param conversationIds The list of conversation IDs that were added.
     * @param messageIds The list of message IDs that were added.
     *
     * @since BlackBerry 10.0.0
     */
    void messagesAdded(bb::pim::account::AccountKey accountId,
                       QList<bb::pim::message::ConversationKey> conversationIds,
                       QList<bb::pim::message::MessageKey> messageIds);

    /*!
     * @brief Emitted when a single message is added to the message service.
     *
     * @param accountId The account ID of the message that was added.
     * @param conversationId The conversation ID that was added.
     * @param messageId The message ID that was added.
     *
     * @since BlackBerry 10.0.0
     */
    void messageAdded(bb::pim::account::AccountKey accountId,
            bb::pim::message::ConversationKey conversationId,
            bb::pim::message::MessageKey messageId);

    /*!
     * @brief Emitted when a message is updated in the message service.
     *
     * @details The @c MessageUpdate parameter includes the details of the update, which you can
     * use to update the local copy of the message in your app.
     *
     * @param accountId The account ID of the message that was updated.
     * @param conversationId The conversation ID that was updated.
     * @param messageId The message ID that was updated.
     * @param data The data regarding the update.
     *
     * @since BlackBerry 10.0.0
     */
    void messageUpdated(bb::pim::account::AccountKey accountId,
            bb::pim::message::ConversationKey conversationId,
            bb::pim::message::MessageKey messageId, bb::pim::message::MessageUpdate data);

    /*!
     * @brief Emitted when a single message is removed from the message service.
     *
     * @param accountId The account ID of the message that was removed.
     * @param conversationId The conversation ID that was removed.
     * @param messageId The message ID that was removed.
     * @param sourceId The ID of the source.
     *
     * @since BlackBerry 10.0.0
     */
    void messageRemoved(bb::pim::account::AccountKey accountId, bb::pim::message::ConversationKey conversationId,
                        bb::pim::message::MessageKey messageId, QString sourceId);

    /*!
     * @brief Emitted when an account's messages are synchronized.
     *
     * @param accountId The account ID of the messages that were synchronized.
     *
     * @since BlackBerry 10.0.0
     */
    void messageSyncCompleted(bb::pim::account::AccountKey accountId);

    /*!
     * @brief Emitted when a conversation is added to the message service.
     *
     * @details You can respond to this signal by updating your conversation list in your app. This signal is
     * used only for SMS accounts.
     *
     * @param accountId The account ID of the conversation that was added.
     * @param conversationId The conversation ID of the new conversation.
     *
     * @since BlackBerry 10.0.0
     */
    void conversationAdded(bb::pim::account::AccountKey accountId,
            bb::pim::message::ConversationKey conversationId);

    /*!
     * @brief Emitted when a conversation is updated in the message service.
     *
     * @details You can respond to this signal by updating your conversation list in your app. This signal is
     * used only for SMS accounts.
     *
     * @param accountId The account ID of the conversation that was updated.
     * @param conversationId The conversation ID of the conversation that was updated.
     * @param data The data regarding the update, as a @c ConstConversationUpdateSharedPtr. You can apply this
     * update to the corresponding @c Conversation in your app.
     *
     * @since BlackBerry 10.0.0
     */
    void conversationUpdated(bb::pim::account::AccountKey accountId,
            bb::pim::message::ConversationKey conversationId, bb::pim::message::ConversationUpdate data);

    /*!
     * @brief Emitted when a conversation is removed from the message service.
     *
     * @details You can respond to this signal by updating your conversation list in your app.
     *
     * @param accountId The account ID of the conversation that was removed.
     * @param conversationId The conversation ID of the conversation that was removed.
     *
     * @since BlackBerry 10.0.0
     */
    void conversationRemoved(bb::pim::account::AccountKey accountId,
            bb::pim::message::ConversationKey conversationId);

    /*!
     * @brief Emitted when a conversation is removed from the message service.
     *
     * @details You can respond to this signal by updating your conversation list in your app.
     *
     * @param accountId The account ID of the conversation that was removed.
     * @param conversationId The conversation ID of the conversation that was removed.
     * @param messageIds The list message IDs in the conversation that was removed.
     *
     * @since BlackBerry 10.3.1
     */
    void conversationRemoved(bb::pim::account::AccountKey accountId,
            bb::pim::message::ConversationKey conversationId,
            const QList<bb::pim::message::MessageKey> &messageIds);

    /*!
     * @brief Emitted when a folder is added to the message service.
     *
     * @details You can respond to this signal by updating your folder list in your app.
     *
     * @param accountId The account ID of the folder that was added.
     * @param folderId The folder ID of the folder that was added.
     *
     * @since BlackBerry 10.0.0
     */
    void folderAdded(bb::pim::account::AccountKey accountId,
            bb::pim::message::MessageFolderKey folderId);

    /*!
     * @brief Emitted when a folder synchronization starts.
     *
     * @details You can respond to this signal by updating your folder list view and any new
     * messages in the specified folder in your app.
     *
     * @param accountId The account ID of the folder that started synchronizing.
     * @param folderId The folder ID of the folder that started synchronizing.
     * @param count The number of messages being updated in the folder.
     *
     * @since BlackBerry 10.0.0
     */
    void folderSyncStarted(bb::pim::account::AccountKey accountId,
            bb::pim::message::MessageFolderKey folderId, int count);

    /*!
     * @brief Emitted when a folder synchronization finishes.
     *
     * @param accountId The account ID of the folder that finished synchronizing.
     * @param folderId The folder ID of the folder that finished synchronizing.
     *
     * @since BlackBerry 10.0.0
     */
    void folderSyncCompleted(bb::pim::account::AccountKey accountId,
            bb::pim::message::MessageFolderKey folderId);

    /*!
     * @brief Emitted when a folder is updated in the message service.
     *
     * @details For example, this signal is emitted when the name of a folder is changed.
     *
     * @param accountId The account ID of the folder that was updated.
     * @param folderId The folder ID of the folder that was updated.
     *
     * @since BlackBerry 10.0.0
     */
    void folderUpdated(bb::pim::account::AccountKey accountId,
            bb::pim::message::MessageFolderKey folderId);

    /*!
     * @brief Emitted when a folder is removed from the message service.
     *
     * @param accountId The account ID of the folder that was removed.
     * @param folderId The folder ID of the folder that was removed.
     *
     * @since BlackBerry 10.0.0
     */
    void folderRemoved(bb::pim::account::AccountKey accountId,
            bb::pim::message::MessageFolderKey folderId);

    /*!
     * @brief Emitted when a folder becomes out of sync and is updated by the service.
     *
     * @details This signal is emitted in rare cases where the folder becomes out of sync with the server and
     * the service re-synchronizes the folder. This signal is not emitted when all of the messages in
     * a folder are deleted manually.
     *
     * @param accountId The account ID of the folder that was re-synchronized.
     * @param folderId The folder ID of the folder that was re-synchronized.
     *
     * @since BlackBerry 10.0.0
     */
    void folderEmptied(bb::pim::account::AccountKey accountId,
            bb::pim::message::MessageFolderKey folderId);

    /*!
     * @brief Emitted when the folder hierarchy (for example, folder names and structure) for an account is synced.
     * 
     * @details This signal is emitted every time the folder hierarchy for an account is synced. For example,
     * the folder hierarchy might be synced when all of the folders for the account have been added but the
     * folder content and messages are not synced yet.
     * 
     * This signal is emitted for all types of email providers (ActiveSync, IMAP, and POP). Note that this signal
     * is emitted only for email accounts. For non-email accounts, such as LinkedIn, Facebook, and so on, this
     * signal is not emitted.
     *
     * @param accountId The account ID of the account that is being synced.
     *
     * @since BlackBerry 10.3.0
     */
    void folderHierarchySynced(bb::pim::account::AccountKey accountId);

    /*!
     * @brief Emitted when the download status of an attachment changes.
     *
     * @details For example, this signal is emitted when an attachment is being downloaded incrementally.
     *
     * @param accountId The account ID of the account that contains the message.
     * @param messageId The message ID of the message.
     * @param attachmentId The attachment ID of the attachment.
     * @param percentDownloaded The percentage of the attachment that's finished downloading.
     *
     * @since BlackBerry 10.0.0
     */
    void attachmentDownloadStatusChanged(bb::pim::account::AccountKey accountId,
            bb::pim::message::MessageKey messageId,
            bb::pim::message::AttachmentKey attachmentId, int percentDownloaded);

    /*!
     * @brief Emitted when an attachment has finished downloading.
     *
     * @param accountId The account ID of the account that contains the message.
     * @param messageId The messageId of the message.
     * @param attachmentId The attachment ID of the attachment.
     *
     * @since BlackBerry 10.0.0
     */
    void attachmentDownloaded(bb::pim::account::AccountKey accountId,
            bb::pim::message::MessageKey messageId,
            bb::pim::message::AttachmentKey attachmentId);

    /*!
     * @brief Emitted when an attachment isn't downloaded successfully.
     *
     * @param accountId The account ID of the account that contains the message.
     * @param messageId The message ID of the message.
     * @param attachmentId The attachment ID of the attachment.
     * @param attachmentStatus The status code of the attachment, which indicates why
     * the attachment wasn't downloaded successfully.
     *
     * @since BlackBerry 10.0.0
     */
    void attachmentDownloadFailed(bb::pim::account::AccountKey accountId,
            bb::pim::message::MessageKey messageId,
            bb::pim::message::AttachmentKey attachmentId,
            bb::pim::message::AttachmentDownloadStatus::Type  attachmentStatus);

    /*!
     * @brief Emitted when the download status of a message changes.
     *
     * @details For example, this signal is emitted when a message (such as an MMS message)
     * is being downloaded incrementally.
     *
     * @param accountId The account ID of the account that contains the message.
     * @param messageId The message ID of the message.
     * @param percentDownloaded The percentage of the message that's finished downloading.
     *
     * @since BlackBerry 10.0.0
     */
    void messageDownloadStatusChanged(bb::pim::account::AccountKey accountId,
            bb::pim::message::MessageKey messageId, int percentDownloaded);

    /*!
     * @brief Emitted when the body of a message is downloaded.
     *
     * @param accountId The account ID of the account that contains the message.
     * @param messageId The message ID of the message.
     *
     * @since BlackBerry 10.0.0
     */
    void bodyDownloaded(bb::pim::account::AccountKey accountId, bb::pim::message::MessageKey messageId);

    /*!
     * @brief Emitted when a new message is available during a data locked state when Advanced Data at Rest
     * Protection is enabled.
     *
     * @details This signal indicates that a new email is available while the device Advanced Data at Rest
     * Protection enabled and the device is in a data locked state.
     * The user will need to unlock the device before the message can be retrieved. This signal is only an
     * indication that a new email is available, after unlock the messageAdded signal will occur as normal.
     * @see messageAdded()
     *
     * @param accountID the account ID of the account that contains the message.
     * @param mimeType the mime type of the available message.
     * @param count how many messages are available
     *
     * @since BlackBerry 10.3.0
     */
    void datalockedMessageAdded(bb::pim::account::AccountKey accountId, const QString & mimeType, int count);

    /*!
     * @brief Emitted when the typing status in a conversation changes.
     *
     * @details This signal indicates that a participant in a conversation has either started
     * typing or stopped typing. This signal is used only for accounts that support the idea
     * of presence, and it is not used for SMS or MMS accounts.
     *
     * @param accountId The account ID of the account that contains the message.
     * @param conversationId The conversation ID of the conversation.
     * @param typing If @c true the participant has started typing, if @c false the participant
     * has stopped typing.
     *
     * @since BlackBerry 10.0.0
     */
    void typingStatusChanged(bb::pim::account::AccountKey accountId,
            bb::pim::message::ConversationKey conversationId, bool typing);



private:
    Q_DISABLE_COPY(MessageService)
    Q_DECLARE_PRIVATE(MessageService)

    QScopedPointer<MessageServicePrivate> const d_ptr;
};


} /* namespace message */
} /* namespace pim */
} /* namespace bb */

#endif // BB_PIM_MESSAGE_MESSAGESERVICE_HPP
