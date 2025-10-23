/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_MESSAGE_SMSTRANSPORTREGISTRATIONRESULT_HPP
#define BB_PIM_MESSAGE_SMSTRANSPORTREGISTRATIONRESULT_HPP

#include <bb/pim/Global>

#include <QObject>

namespace bb
{

namespace pim
{

namespace message
{

/*!
 * @headerfile SmsTransportRegistrationResult.hpp <bb/pim/message/SmsTransportRegistrationResult>
 *
 * @brief The @c SmsTransportRegistrationResult class defines possible statuses for port registration
 * requests for an @c SmsTransport.
 *
 * @details You can use this class to determine the status of a registration request that was made
 * by calling @c SmsTransport::registerPort().
 * 
 * @xmlonly
 * <apigrouping group="App Integration/Message"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */

class BB_PIM_EXPORT SmsTransportRegistrationResult
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief An enumeration of supported statuses for port registration requests.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief Indicates that an unknown registration error occurred.
         *
         * @since BlackBerry 10.0.0
         */
        Unknown = 0,
        /*!
         * @brief Indicates that the registration request was successful.
         *
         * @since BlackBerry 10.0.0
         */
        PortRegistered = 1,

        /*!
         * @brief Indicates that the specified port value is not within the acceptable
         * range for SMS.
         *
         * @since BlackBerry 10.0.0
         */
        InvalidPort = 2,
        /*!
         * @brief Indicates that the specified port currently has another registered
         * listener.
         *
         * @since BlackBerry 10.0.0
         */
        PortInUse = 3,
        /*!
         * @brief Indicates that the target application type is invalid.
         *
         * @since BlackBerry 10.2.2
         */
        TargetTypeInvalid = 4,
        /*!
         * @brief Indicates that the target key is invalid.
         *
         * @since BlackBerry 10.2.2
         */
        TargetKeyInvalid = 5,
    };

private:
    /*! @cond PRIVATE */
    SmsTransportRegistrationResult();
    ~SmsTransportRegistrationResult();
    /*! @endcond */
};

} /* namespace message */
} /* namespace pim */
} /* namespace bb */

#endif // BB_PIM_MESSAGE_SMSTRANSPORTREGISTRATIONRESULT_HPP
