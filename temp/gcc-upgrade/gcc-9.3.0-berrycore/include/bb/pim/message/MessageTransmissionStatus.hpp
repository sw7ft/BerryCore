/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_MESSAGE_MESSAGETRANSMISSIONSTATUS_HPP
#define BB_PIM_MESSAGE_MESSAGETRANSMISSIONSTATUS_HPP

#include <bb/pim/Global>

#include <QMetaType>

namespace bb {
namespace pim {
namespace message {

/*!
 * @headerfile MessageTransmissionStatus.hpp <bb/pim/message/MessageTransmissionStatus>
 *
 * @brief The @c MessageTransmissionStatus class includes statuses for message transmission.
 * 
 * @details When a @c Message is sent using the @c MessageService, it can have one of several
 * statuses. For example, the message might be pending, sent, or might indicate that a
 * transmission error occurred. You can use this class to determine the transmission status
 * of a message and detect any errors.
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
class BB_PIM_EXPORT MessageTransmissionStatus
{
public:
    /*!
     * @brief An enumeration of supported message transmission statuses.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        Unknown = 0,
        /*!
         * @brief Indicates that the message is pending after being sent.
         *
         * @since BlackBerry 10.0.0
         */
        Pending = 100,
        /*!
         * @brief Indicates that the message is sending.
         *
         * @since BlackBerry 10.0.0
         */
        Sending = 101,
        /*!
         * @brief Indicates that the message has been sent.
         *
         * @since BlackBerry 10.0.0
         */
        Sent = 102,
        /*!
         * @brief Indicates that the message download failed.
         *
         * @since BlackBerry 10.0.0
         */
        DownloadFailed = 200,
        /*!
         * @brief Indicates that message synchronization failed.
         *
         * @since BlackBerry 10.0.0
         */
        SyncFailed = 201,
        /*!
         * @brief Indicates that the message could not be sent.
         *
         * @since BlackBerry 10.0.0
         */
        FailedToSent = 202,
        /*!
         * @brief Indicates that the message is too large to be sent.
         *
         * @since BlackBerry 10.0.0
         */
        TooLarge = 203,
        /*!
         * @brief Indicates that an attachment size of the message is too large
         * for the message to be sent.
         *
         * @since BlackBerry 10.0.0
         */
        AttachTooLarge = 204,
        /*!
         * @brief AcknowledgmentNotReceived status
         *
         * @details
         * Indicates that acknowledgment for send was not received from server
         *
         * @since BlackBerry 10.0.0
         */
        AcknowledgmentNotReceived = 205,
        /*!
         * @brief BodyDownloadFailedMessageNoLongerExists status
         *
         * @details
         * Indicates that the body download failed because the message no longer exists
         *
         * @since BlackBerry 10.0.0
         */
        BodyDownloadFailedMessageNoLongerExists = 206,
        /*!
         * @brief BodyDownloadFailedGeneral status
         *
         * @details
         * Indicates that the body download failed in general
         *
         * @since BlackBerry 10.0.0
         */
        BodyDownloadFailedGeneral = 207,
        /*!
         * @brief FailedToSentQuotaExceeded status
         *
         * @details
         * Indicates that the message could not be sent due to SendQuota Exceed
         */
        FailedToSentQuotaExceeded = 208,
        /*!
         * @brief ErrorEncryptingMessage status
         *
         * @details
         * Indicates that the message could not be encrypted and sent in general
         */
        ErrorEncryptingMessage = 209,
        /*!
         * @brief ErrorDecryptingMessage status
         *
         * @details
         * Indicates that the message could not be decrypted and shown to the user in general
         */
        ErrorDecryptingMessage = 210,
        /*!
         * @brief ErrorEncryptingMessageIncorrectPassword status
         *
         * @details
         * Indicates that the message could not be encrypted and sent due to the incorrect password
         */
        ErrorEncryptingMessageIncorrectPassword = 211,
        /*!
         * @brief ErrorEncryptingMessageNoPassword status
         *
         * @details
         * Indicates that the message could not be encrypted and sent due to the absence of password
         */
        ErrorEncryptingMessageNoPassword = 212,
        /*!
         * @brief ErrorEncryptingMessageNoIDFile status
         *
         * @details
         * Indicates that the message could not be encrypted and sent due to the absence of ID file on the server
         */
        ErrorEncryptingMessageNoIDFile = 213,
    };

private:
    /*! @cond PRIVATE */
    MessageTransmissionStatus();
    ~MessageTransmissionStatus();
    /*! @endcond */
};

} /* namespace message */
} /* namespace pim */
} /* namespace bb */

Q_DECLARE_METATYPE(bb::pim::message::MessageTransmissionStatus::Type)

#endif // BB_PIM_MESSAGE_MESSAGETRANSMISSIONSTATUS_HPP
