/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_MESSAGE_MESSAGEBODY_HPP
#define BB_PIM_MESSAGE_MESSAGEBODY_HPP

#include <bb/pim/Global>

#include <QSharedDataPointer>
#include <QByteArray>
#include <QString>

namespace bb {
namespace pim {
namespace message {

class MessageBodyPrivate;

/*!
 * @brief The @c MessageBody class represents the body of a message.
 *
 * @details A @c Message typically has a body that includes the actual contents of the message.
 * You can use this class to retrieve information about the message body, such as type (plain
 * text or HTML), available length, and data. You can retrieve a @c %Message by calling
 * @c MessageService::message() and then retrieve the body of that message by calling
 * @c Message::body().
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
class BB_PIM_EXPORT MessageBody
{


public:

    /*!
     * @brief An enumeration of the supported types of body text.
     *
     * @details You can use this information to retrieve plain text or HTML body text from
     * a message.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief Indicates that the body is plain text.
         *
         * @since BlackBerry 10.0.0
         */
        PlainText=0,
        /*!
         * @brief Indicates that the body is HTML.
         *
         * @since BlackBerry 10.0.0
         */
        Html = 1
    };

    /*!
     * @brief Constructs a new @c MessageBody.
     *
     * @since BlackBerry 10.0.0
     */
    MessageBody();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs a @c MessageBody containing exactly the same values as
     * the provided @c %MessageBody.
     *
     * @param other The @c %MessageBody to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    MessageBody(const MessageBody &other);

    /*!
     * @brief Constructs a @c MessageBody with the provided private message body information.
     *
     * @details This constructor creates a @c %MessageBody by using a @c d_ptr to private
     * message body information.
     *
     * @param messageBodyPrivate The private message body information to use.
     *
     * @since BlackBerry 10.0.0
     */
    explicit MessageBody(MessageBodyPrivate* messageBodyPrivate);

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c MessageBody into this
     * @c %MessageBody.
     *
     * @param other The @c %MessageBody from which to copy all values.
     *
     * @return A @c %MessageBody with all copied data.
     *
     * @since BlackBerry 10.0.0
     */
    MessageBody& operator=(const MessageBody &other);

    /*!
     * @brief Destroys this @c MessageBody.
     *
     * @since BlackBerry 10.0.0
     */
    ~MessageBody();

    /*!
    * @brief Retrieves the type of this @c MessageBody.
    *
    * @details This function returns the type as a @c MessageBody object and includes values
    * such as "plain text" or "HTML". You can use this information to render the body content
    * in your app.
    *
    * @return The message body type.
     *
     * @since BlackBerry 10.0.0
    */
    MessageBody::Type type() const;

    /*!
    * @brief Retrieves the content of this @c MessageBody.
    *
    * @details This content is typically loaded lazily when this function is called.
    *
    * @return The message body content.
     *
     * @since BlackBerry 10.0.0
    */
    QByteArray data();


    /*!
    * @brief Retrieves the available length of this @c MessageBody.
    *
    * @return The available length.
     *
     * @since BlackBerry 10.0.0
    */
    int availableLength() const;

    /*!
    * @brief Retrieves the content of this @c MessageBody in plain text.
    *
    * @details This function always returns the plain text version of the content.
    *
    * @return The content in plain text.
     *
     * @since BlackBerry 10.0.0
    */
    QString plainText();

    /*!
    * @brief Retrieves the full content type of this @c MessageBody.
    *
    * @details This function returns the full content type of the message body (for example,
    * "text/html; charset=utf-8").
    *
    * @return The full content type.
     *
     * @since BlackBerry 10.0.0
    */
    QString contentType() const;

    /*!
     * @brief Retrieves the absolute file name of this @c MessageBody.
     *
     * @return The absolute file name.
     *
     * @since BlackBerry 10.0.0
     */
    QString fileName() const;

    /*!
     * @brief Indicates whether this @c MessageBody is partially downloaded.
     *
     * @return @c true if the message body is only partially downloaded, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isPartial() const;

    /*!
     * @brief Indicates whether this @c MessageBody is valid.
     *
     * @return @c true if this @c %MessageBody is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;


private:
    QSharedDataPointer<MessageBodyPrivate> d_ptr;


};

} /* namespace message */
} /* namespace pim */
} /* namespace bb */

#endif // BB_PIM_MESSAGE_MESSAGEBODY_HPP
