/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_MESSAGE_SMSTRANSPORT_HPP
#define BB_PIM_MESSAGE_SMSTRANSPORT_HPP

#include <bb/Global>
#include <bb/pim/Global>
#include <bb/pim/message/Message>
#include <bb/pim/message/MessageBuilder>
#include <bb/pim/message/SmsTransportRegistrationResult>
#include <bb/pim/message/SmsTransportSendResult>
#include <QObject>

namespace bb
{

namespace pim
{

namespace message
{

class SmsTransportPrivate;

/*!
 * @headerfile SmsTransport.hpp <bb/pim/message/SmsTransport>
 *
 * @brief The @c SmsTransport class lets you perform operations on SMS messages from your
 * apps.
 * 
 * @details You can use this class to register the port that's used to send SMS messages,
 * send a message, and receive the result of the send operation.
 * 
 * @xmlonly
 * <apigrouping group="App Integration/Message"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT SmsTransport: public QObject
{
    Q_OBJECT

public:

    /*!
     * @brief Constructs a new @c SmsTransport.
     * 
     * @param parent The parent object. This parameter is optional.
     *
     * @since BlackBerry 10.0.0
     */
    explicit SmsTransport(QObject *parent = 0);

    /*!
     * @brief Destroys this @c SmsTransport.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~SmsTransport();

    /*!
     * @brief Obtain a @c MessageBuilder that you can use to create a message.
     * 
     * @details Ownership of the returned object is transferred to the caller, which is
     *          responsible for deleting the object.
     *
     * @return A @c MessageBuilder object.
     *
     * @since BlackBerry 10.0.0
     */

    MessageBuilder *createMessageBuilder();

    /*!
     * @brief Registers the specified port with the SmsTransport service.
     *
     * @details You can make multiple calls to this function, one for each
     *          of the incoming port numbers that you want to listen to. The success
     *          or failure of this registration request will be reported to you via
     *          the @c registerResultReceived() signal.
     *
     * @param port The port number to register.
     *
     * @since BlackBerry 10.0.0
     */

    void registerPort(unsigned int port);

    /*!
     * @brief Registers the specified port and target ID with the SmsTransport service.
     *
     * @details Registers the target to be invoked when an incoming SMS arrives for the specified port.
     *          The success or failure of this registration request will be reported to you via
     *          the @c registerResultReceived() signal.
     *
     * @param port The port number to register.
     * @param targetId The target identifier.
     *
     * @since BlackBerry 10.2.0
     */

    void registerPort(unsigned int port, const QString &targetId);

    /*!
     * @brief Unregisters the specified port with the SmsTransport service.
     *
     * @param port The port number to unregister.
     * @param targetId The target identifier.
     *
     * @since BlackBerry 10.2.0
     */

    void unregisterPort(unsigned int port, const QString &targetId);

    /*!
     * @brief Sends the message to the specified destination port at the recipient
     *        address provided in the message.
     *
     * @details This port does not have to be one registered for incoming
     *          messages. The ID field of the message will be updated, and can
     *          be used to associate a subsequent @c messageSendResultReceived()
     *          signal with this message. Message identifiers are unique within a
     *          single instance of @c SmsTransport.
     *
     * @param port The destination port number associated with this message.
     * @param message The message to send.
     *
     * @return The send response.
     *
     * @since BlackBerry 10.0.0
     */

    SmsTransportSendResult::Type send(unsigned int port, const Message &message);

    /*!
     * @brief Sends the message to the specified destination port at the recipient 
     *        address provided in the message, and the receiver will be passed the
     *        originator port number.
     *
     * @details Neither the originator port or the destination port have to be one
     *          registered for incoming messages. The ID field of the message will 
     *          be updated, and can be used to associate a subsequent 
     *          @c messageSendResultReceived() signal with this message. Message 
     *          identifiers are unique within a single instance of @c SmsTransport.
     *
     * @param originatorPort The originator port number associated with this message.
     * @param destinationPort The destination port number associated with this message.
     * @param message The message to send.
     *
     * @return The send response.
     *
     * @since BlackBerry 10.1.0
     */

    SmsTransportSendResult::Type send(unsigned int originatorPort, unsigned int destinationPort, const bb::pim::message::Message &message);

    /*!
     * @brief Converts the data from an incoming bb.action.PORT_DIRECTED_SMS invoke into a Message.
     *
     * @details 
     *
     * @param data The data from the invoke.
     * @param originatorPort On return, contains the originator port number associated with this message.
     * @param destinationPort On return, contains the destination port number associated with this message.
     *
     * @return The incoming Message
     *
     * @since BlackBerry 10.2
     */

    static const bb::pim::message::Message messageFromData(const QByteArray &data, unsigned int *originatorPort, unsigned int *destinationPort);

Q_SIGNALS:
    /*!
     * @brief Emitted when the requested port registration has completed.
     *
     * @param port The port number specified in the corresponding @c registerPort() call.

     * @param status The status of the registration request.
     *
     * @since BlackBerry 10.0.0
     */

   void registerResultReceived(unsigned int port, bb::pim::message::SmsTransportRegistrationResult::Type status);

    /*!
     * @brief Emitted when a send request for an SMS message has completed either
     *        successfully or with an error.
     *
     * @details The transmission status can be retrieved from the message by calling
     *          @c Message::transmissionStatus().
     *
     * @param msgId The identifier of the outgoing message.
     *
     * @since BlackBerry 10.0.0
     */

   void messageSendResultReceived(bb::pim::message::MessageKey msgId);

//! @cond PRIVATE
    /*!
     * @brief Emitted when an SMS message arrives on the registered port.
     *
     * @details The incoming message contains a single @c Attachment containing the incoming data.
     *
     * @param port The destination port number associated with this message.
     * @param message The received message.
     *
     * @since BlackBerry 10.0.0
     */

    void messageReceived(unsigned int port, const Message &message) BB_DEPRECATED;
//! @endcond

    /*!
     * @brief Emitted when an SMS message arrives on the registered port.
     *
     * @details The incoming message contains a single @c Attachment containing the incoming data.
     *
     * @param originatorPort The originator port number associated with this message.
     * @param destinationPort The destination port number associated with this message.
     * @param message The received message.
     *
     * @since BlackBerry 10.1.0
     */

    void messageReceived(unsigned int originatorPort, unsigned int destinationPort, const bb::pim::message::Message &message);

private:
    Q_DISABLE_COPY(SmsTransport)
    Q_DECLARE_PRIVATE(SmsTransport)

    QScopedPointer<SmsTransportPrivate> const d_ptr;
};

} /* namespace message */
} /* namespace pim */
} /* namespace bb */

#endif /* BB_PIM_MESSAGE_SMSTRANSPORT_HPP */
