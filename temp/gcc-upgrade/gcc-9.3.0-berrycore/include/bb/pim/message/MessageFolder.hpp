/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_MESSAGE_MESSAGEFOLDER_HPP
#define BB_PIM_MESSAGE_MESSAGEFOLDER_HPP

#include <bb/pim/Global>
#include <QString>
#include <QSharedDataPointer>

namespace bb {
namespace pim {
namespace message {

/*!
 * @brief Represents a key to identify a folder within an account.
 *
 * @details You can use this key as a unique identifier, along with the account ID, for
 * a message folder.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Message"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
typedef quint64 MessageFolderKey;

class MessageFolderPrivate;

/*!
 * @brief The @c MessageFolder class represents a folder to store messages.
 * 
 * @details This class provides a way to identify a folder within an account (for example,
 * "Inbox", "Sent", and so on). You can create new folders to store specific types of
 * messages.
 * 
 * You can use the @c MessageService to perform operations on message folders. For example,
 * you can add a new message folder by calling @c MessageService::addMessageFolder(), and
 * you can rename an existing folder by calling @c MessageService::renameMessageFolder().
 *
 * @see Message
 * 
 * @xmlonly
 * <apigrouping group="App Integration/Message"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */

class BB_PIM_EXPORT MessageFolder
{

public:

    /*!
     * @brief An enumeration of supported folder types.
     *
     * @details These enumeration values identify folder types, such as "Inbox" and "Sent".
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*!
         * @brief Indicates an unknown folder type.
         *
         * @since BlackBerry 10.0.0
         */
        Unknown=0,
        /*!
         * @brief Indicates the Inbox folder type.
         *
         * @since BlackBerry 10.0.0
         */
        Inbox = 1,
        /*!
         * @brief Indicates the Outbox folder type.
         *
         * @since BlackBerry 10.0.0
         */
        Outbox = 2,
        /*!
         * @brief Indicates the Drafts folder type.
         *
         * @since BlackBerry 10.0.0
         */
        Drafts = 3,
        /*!
         * @brief Indicates the Sent folder type.
         *
         * @since BlackBerry 10.0.0
         */
        Sent = 4,
        /*!
         * @brief Indicates the Trash folder type.
         *
         * @since BlackBerry 10.0.0
         */
        Trash = 5,
        /*!
         * @brief Indicates the Other folder type.
         *
         * @since BlackBerry 10.0.0
         */
        Other = 6
    };

    /*!
     * @brief Constructs a new @c MessageFolder.
     *
     * @since BlackBerry 10.0.0
     */
    MessageFolder();

    /*!
     * @brief Copy constructor.
     * 
     * @details This function constructs a @c MessageFolder containing exactly the same values as
     * the provided @c %MessageFolder.
     * 
     * @param other The @c %MessageFolder to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    MessageFolder(const MessageFolder &other);

    /*!
     * @brief Constructs a folder with the provided parent ID, folder ID, folder name, and type.
     * 
     * @param parentId The ID of the parent folder.
     * @param folderId The ID of the folder to construct.
     * @param folderName The name of the folder.
     * @param type The type of folder (for example, "Inbox", "Drafts", and so on).
     *
     * @since BlackBerry 10.0.0
     */
    MessageFolder(MessageFolderKey parentId,
            MessageFolderKey folderId, const QString &folderName, MessageFolder::Type type);

    /*!
     * @brief Constructs a new @c MessageFolder using the provided @c MessageFolderPrivate object.
     *
     * @param messageFolderPrivate The @c %MessageFolderPrivate object to use to construct the
     * @c %MessageFolder.
     *
     * @since BlackBerry 10.0.0
     */
    explicit MessageFolder(MessageFolderPrivate* messageFolderPrivate);

    /*!
     * @brief Assignment operator.
     * 
     * @details This operator copies all values from the provided @c MessageFolder into this
     * @c %MessageFolder.
     * 
     * @param other The @c %MessageFolder from which to copy all values.
     *
     * @return A @c %MessageFolder with all copied data.
     *
     * @since BlackBerry 10.0.0
     */
    MessageFolder& operator=(const MessageFolder &other);

    /*!
     * @brief Destroys this @c MessageFolder.
     *
     * @since BlackBerry 10.0.0
     */
    ~MessageFolder();

    /*!
     * @brief Retrieves the ID of this @c MessageFolder.
     * 
     * @details You can use this ID to access messages within this message folder. This
     * ID is unique per account.
     * 
     * @return The message folder's ID.
     *
     * @since BlackBerry 10.0.0
     */
    MessageFolderKey id() const;

    /*!
     * @brief Retrieves the name of this @c MessageFolder.
     *
     * @return The message folder's name.
     *
     * @since BlackBerry 10.0.0
     */
    QString name() const;

    /*!
     * @brief Retrieves the type of this @c MessageFolder.
     * 
     * @details This function returns the type as an enumeration value in the
     * @c MessageFolder::Type enumeration, and includes values such as "Inbox" and
     * "Drafts".
     *
     * @return The message folder's type.
     *
     * @since BlackBerry 10.0.0
     */
    MessageFolder::Type type() const;

    /*!
     * @brief Retrieves the ID of the parent folder of this @c MessageFolder.
     * 
     * @details You can use the parent folder ID to set up a tree view of message folders
     * in your app.
     * 
     * @return The message folder's parent folder ID.
     *
     * @since BlackBerry 10.0.0
     */
    MessageFolderKey parentId() const;

    /*!
     * @brief Indicates whether this @c MessageFolder is valid.
     * 
     * @return @c true if this @c %MessageFolder is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

    /*!
     * @brief Indicates the current sync configuration of this @c MessageFolder.
     * 
     * @return @c true if sync is enabled, @c false if sync is disabled.
     *
     * @since BlackBerry 10.0.0
     */
    bool syncConfig() const;

private:
    QSharedDataPointer<MessageFolderPrivate> d_ptr;
};

} /* namespace message */
} /* namespace pim */
} /* namespace bb */

#endif // BB_PIM_MESSAGE_MESSAGEFOLDER_HPP
