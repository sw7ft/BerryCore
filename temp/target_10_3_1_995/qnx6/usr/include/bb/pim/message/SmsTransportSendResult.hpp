/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_MESSAGE_SMSTRANSPORTSENDRESULT_HPP
#define BB_PIM_MESSAGE_SMSTRANSPORTSENDRESULT_HPP

#include <bb/pim/Global>
#include <QObject>

namespace bb
{

namespace pim
{

namespace message
{

/*!
 * @headerfile SmsTransportSendResult.hpp <bb/pim/message/SmsTransportSendResult>
 *
 * @brief The @c SmsTransportSendResult class defines possible statuses for send requests for
 * an @c SmsTransport.
 *
 * @details You can use this class to determine the status of a send request that was made
 * by calling @c SmsTransport::send().
 *
 * @xmlonly
 * <apigrouping group="App Integration/Message"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */

class BB_PIM_EXPORT SmsTransportSendResult
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief An enumeration of supported statuses for send requests.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief Indicates that the send request was successful.
         *
         * @since BlackBerry 10.0.0
         */
        Success = 0,
        /*!
         * @brief Indicates that the send request was missing the text attachment.
         *
         * @since BlackBerry 10.0.0
         */
        MissingTextAttachment = 1,
        /*!
         * @brief Indicates that the send request included a text attachment of
         * zero length.
         *
         * @since BlackBerry 10.0.0
         */
        EmptyTextAttachment = 2,
        /*!
         * @brief Indicates that the send request recipient list is invalid.
         *
         * @since BlackBerry 10.2.0
         */
        InvalidRecipientList = 3,
    };

private:
    /*! @cond PRIVATE */
    SmsTransportSendResult();
    ~SmsTransportSendResult();
    /*! @endcond */
};

} /* namespace message */
} /* namespace pim */
} /* namespace bb */

#endif // BB_PIM_MESSAGE_SMSTRANSPORTSENDRESULT_HPP
