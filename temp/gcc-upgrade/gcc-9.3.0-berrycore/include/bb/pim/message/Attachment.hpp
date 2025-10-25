/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_MESSAGE_ATTACHMENT_HPP
#define BB_PIM_MESSAGE_ATTACHMENT_HPP

#include <bb/pim/Global>
#include <bb/pim/message/Keys>

#include <QByteArray>
#include <QMetaType>
#include <QVariantMap>
#include <QSharedPointer>
#include <QString>
#include <QUrl>

namespace bb {
namespace pim {
namespace message {

class AttachmentPrivate;

/**
 * @brief The @c Attachment class represents an attachment to a message.
 *
 * @details This class includes information about an attachment to a @c Message object, such
 * as file path to the attachment on the file system, MIME type, and optional metadata. You
 * can retrieve the list of attachments for a @c %Message by calling
 * @c Message::attachments().
 *
 * You can also use the @c MessageService class to retrieve message attachments. You can
 * download the attachment of a @c %Message by calling @c MessageService::downloadAttachment().
 *
 * Each @c %Attachment object has a key, which is represented by an @c AttachmentKey,
 * and this key uniquely identifies the attachment.
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
class BB_PIM_EXPORT Attachment
{
public:
    /*!
     * @brief Constructs an empty, invalid @c Attachment.
     *
     * @details This constructor may be used when returning an @c %Attachment by value to indicate
     * an error. When you use this constructor to create an @c %Attachment, the @c isValid() will
     * return @c false for the attachment.
     *
     * @since BlackBerry 10.0.0
     */
    Attachment();

    /*!
     * @brief Constructs an @c Attachment with the provided MIME type, name, and file path.
     *
     * @details This constructor creates an attachment object with the provided MIME type and name
     * by using the data that's contained in the file at the provided file path.
     *
     * @param mimeType The MIME type of the attachment to construct.
     * @param name The name of the attachment to construct.
     * @param path The URL that specifies the file path of the data to use to construct the
     *             attachment. The @c file:// schema is the only supported schema for the URL. If
     *             you want the file at this file path to be deleted if and when the associated
     *             message is removed from the messages database, you should listen for storage
     *             deletions and delete file yourself. NOTE: It's important to note that a @c QUrl
     *             is passed and not a @c QString / @c QByteArray. An implicit conversion will not be
     *             performed. Instead, one of the other constructors will be called.
     *
     * @since BlackBerry 10.0.0
     */
    Attachment(const QString &mimeType, const QString &name, const QUrl &path);

    /*!
     * @brief Constructs an @c Attachment with the provided MIME type, name, path, and metadata.
     *
     * @details This constructor creates an attachment object with the provided MIME type, name, and
     * metadata by using the data that's contained in the file at the provided file path.
     *
     * @param mimeType The MIME type of the attachment to construct.
     * @param name The name of the attachment to construct.
     * @param path The URL that specifies the file path of the data to use to construct the
     *             attachment. The @c file:// schema is the only supported schema for the URL. If
     *             you want the file at this file path to be deleted if and when the associated
     *             message is removed from the messages database, you should listen for storage
     *             deletions and delete file yourself. NOTE: It's important to note that a @c QUrl
     *             is passed and not a @c QString / @c QByteArray. An implicit conversion will not be
     *             performed. Instead, one of the other constructors will be called.
     * @param metaData A @c QVariantMap that contains additional metadata associated with this attachment.
     *                 The interpretation and use of its keys and values are implementation-specific.
     *
     * @since BlackBerry 10.0.0
     */
    Attachment(const QString &mimeType, const QString &name, const QUrl &path, const QVariantMap &metaData);

    /*!
     * @brief Constructs an @c Attachment with the provided MIME type, name, and text data.
     *
     * @details This constructor creates an attachment object with the provided MIME type, name, and
     * text data. The text data is assumed to be encoded in UTF-8.
     *
     * @param mimeType The MIME type of the attachment to construct.
     * @param name The name of the attachment to construct.
     * @param textData The UTF-8 text data for the attachment to construct. NOTE: It's important to note
     *                 that a @c QString is passed and not a @c QUrl / @c QByteArray. An implicit
     *                 conversion will not be performed. Instead, one of the other constructors will be
     *                 called.
     *
     * @since BlackBerry 10.0.0
     */
    Attachment(const QString &mimeType, const QString &name, const QString &textData);

    /*!
     * @brief Construct an @c Attachment with the provided MIME type, name, and binary data.
     *
     * @details This constructor creates an attachment object with the provided MIME type, name, and binary
     * data (which is represented by a @c QByteArray).
     *
     * @param mimeType The MIME type of the attachment to construct.
     * @param name The name of the attachment to construct.
     * @param data The data for the attachment to construct. NOTE: It's important to note that a @c %QByteArray
     *             is passed and not a @c QUrl / @c QString. An implicit conversion will not be performed.
     *             Instead, one of the other constructors will be called.
     *
     * @since BlackBerry 10.0.0
     */
    Attachment(const QString &mimeType, const QString &name, const QByteArray &data);

    /*!
     * @brief Construct an @c Attachment with the provided MIME type, name, binary data, and metadata.
     *
     * @details This constructor creates an attachment object with the provided MIME type, name, binary data
     * (which is represented by a @c QByteArray), and metadata.
     *
     * @param mimeType The MIME type of the attachment to construct.
     * @param name The name of the attachment to construct.
     * @param data The data for the attachment to construct. NOTE: It's important to note that a @c %QByteArray
     *             is passed and not a @c QUrl / @c QString. An implicit conversion will not be performed.
     *             Instead, one of the other constructors will be called.
     * @param metaData A @c QVariantMap that contains additional metadata associated with this attachment.
     *                 The interpretation and use of its keys and values are implementation-specific.
     *
     * @since BlackBerry 10.0.0
     */
    Attachment(const QString &mimeType, const QString &name, const QByteArray &data, const QVariantMap &metaData);

    /*!
     * @brief Constructs an @c Attachment from the provided private data.
     *
     * @param attachmentPrivate The private data to construct the attachment from.
     *
     * @since BlackBerry 10.0.0
     */
    Attachment(AttachmentPrivate *attachmentPrivate);

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs an @c Attachment containing exactly the same values as the provided
     * @c %Attachment.
     *
     * @param other The @c %Attachment to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    Attachment(const Attachment &other);

    /*!
     * @brief Destroys this @c Attachment.
     *
     * @details This function cleans up and frees the attachment's data and resources.
     *
     * @since BlackBerry 10.0.0
     */
    ~Attachment();

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c Attachment into this @c %Attachment.
     *
     * @param other The @c %Attachment from which to copy all values.
     *
     * @return An @c %Attachment with all copied data.
     *
     * @since BlackBerry 10.0.0
     */
    Attachment &operator=(const Attachment &other);

    /*!
     * @brief Equality operator.
     *
     * @details This function indicates whether this @c Attachment has exactly the same values as the
     * provided @c %Attachment.
     *
     * @param other The @c %Attachment to compare values with.
     *
     * @return @c true if the attachments are considered equal, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool operator==(const Attachment &other) const;

    /*!
     * @brief Inequality operator.
     *
     * @details This function indicates whether this @c Attachment does not have exactly the same values
     * as the provided @c %Attachment.
     *
     * @param other The @c %Attachment to compare values with.
     *
     * @return @c true if the attachments are not considered equal, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool operator!=(const Attachment &other) const;

    /*!
     * @brief Indicates whether this @c Attachment is valid.
     *
     * @return @c true if this @c %Attachment is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

    /*!
     * @brief Retrieves the attachment ID of this @c Attachment.
     *
     * @details This function returns the ID that's associated with the attachment.
     *
     * @return The attachment's ID.
     *
     * @since BlackBerry 10.0.0
     */
    AttachmentKey id() const;

    /*!
     * @brief Retrieves the MIME type of this @c Attachment.
     *
     * @return The attachment's MIME type.
     *
     * @since BlackBerry 10.0.0
     */
    QString mimeType() const;

    /*!
     * @brief Retrieves the name of this @c Attachment.
     *
     * @return The attachment's name.
     *
     * @since BlackBerry 10.0.0
     */
    QString name() const;

    /*!
     * @brief Retrieves the file path of this @c Attachment on the file system.
     *
     * @details This function returns the path to the attachment's data as a URL using the @c file://
     * schema. If the attachment was constructed with data instead of a path, the internal path used
     * to store the data is returned, if it exists. Otherwise, an empty @c QUrl is returned.
     *
     * @return The attachment's path as a @c file:// URL, if it exists, and an empty @c %QUrl
     * otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    QUrl path() const;

    /*!
     * @brief Retrieves the data of this @c Attachment.
     *
     * @details This function returns the attachment's data. If the attachment was constructed with a
     * path, the data from the file at the path is lazily loaded and then returned. If the data is
     * text data, it is encoded in UTF-8.
     *
     * @return The attachment's data.
     *
     * @since BlackBerry 10.0.0
     */
    QByteArray data() const;

    /*!
     * @brief Retrieves the file path of the icon of this @c Attachment.
     *
     * @details This function returns the path of any icon associated with the attachment, as a URL
     * using the @c file::// schema. If the icon was set using data instead of a path, the internal path
     * used to store the icon data is returned, if it exists. Otherwise, an empty @c QUrl is returned.
     *
     * @return The attachment's icon path as a @c file:// URL, if it exists, and an empty @c %QUrl
     * otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    QUrl iconPath() const;

    /*!
     * @brief Retrieves the icon data of this @c Attachment.
     *
     * @details This function returns the data of any icon associated with the attachment. If the
     * attachment icon was specified using a path, the data from the file at the path is lazily
     * loaded and then returned.
     *
     * @return The attachment's icon data.
     *
     * @since BlackBerry 10.0.0
     */
    QByteArray iconData() const;

    /*!
     * @brief Retrieves the total size (in bytes) of this @c Attachment.
     *
     * @return The attachment's total size (in bytes) as a qint64.
     *
     * @since BlackBerry 10.3.0
     */
    qint64 totalSize64() const;

    /*!
     * @brief Retrieves the total size (in bytes) of this @c Attachment.
     *
     * @return The attachment's total size (in bytes). Returns -1 for size
     * values greater than 2^31-1
     *
     * @since BlackBerry 10.0.0
     */
    int totalSize() const;

    /*!
     * @brief Retrieves the available size (in bytes) of this @c Attachment.
     *
     * @details This function returns, as a uint64, the available size (in bytes) of the attachment. The
     * available size is typically the same as the total size but may be different for some services. For
     * example, the messaging service uses the available size to determine how much of the attachment has
     * actually been downloaded.
     *
     * @return The attachment's available size (in bytes) as a qint64.
     *
     * @since BlackBerry 10.3.0
     */
    qint64 availableSize64() const;

    /*!
     * @brief Retrieves the available size (in bytes) of this @c Attachment.
     *
     * @details This function returns the available size (in bytes) of the attachment. The available
     * size is typically the same as the total size but may be different for some services. For example,
     * the messaging service uses the available size to determine how much of the attachment has actually
     * been downloaded.
     *
     * @return The attachment's available size (in bytes). Returns -1 for size
     * values greater than 2^31-1
     *
     * @since BlackBerry 10.0.0
     */
    int availableSize() const;

    /*!
     * @brief Indicates whether this @c Attachment is an inline attachment.
     *
     * @return @c true if this @c %Attachment is an inline attachment, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isInline() const;

    /*!
     * @brief Retrieves the metadata of this @c Attachment.
     *
     * @details This function returns any metadata that's associated with the attachment. Metadata is
     * returned as a @c QVariantMap. The interpretation and use of its keys and values are
     * implementation-specific.
     *
     * @return The attachment's metadata.
     *
     * @since BlackBerry 10.0.0
     */
    QVariantMap metaData() const;

    /*!
     * @brief Retrieves the content ID for this @c Attachment.
     *
     * @return The attachment's content ID.
     *
     * @since BlackBerry 10.0.0
     */
    QString contentId() const;

private:
    QSharedPointer<AttachmentPrivate> d_ptr;

    friend class AttachmentPrivate;
};

} /* namespace message */
} /* namespace pim */
} /* namespace bb */

Q_DECLARE_METATYPE(bb::pim::message::Attachment)

#endif // BB_PIM_MESSAGE_ATTACHMENT_HPP
