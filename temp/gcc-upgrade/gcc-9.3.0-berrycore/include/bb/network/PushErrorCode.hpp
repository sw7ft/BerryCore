/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_NETWORK_PUSHERRORCODE_HPP
#define BB_NETWORK_PUSHERRORCODE_HPP

#include <bb/network/Global>

#include <QMetaObject>

namespace bb
{
namespace network
{

/*!
 * @headerfile PushErrorCode.hpp <bb/network/PushErrorCode>
 *
 * @brief Encapsulates the result codes that occur during a @c PushService operation.
 *
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Push"/>
 * <library name="bbnetwork"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */

class BB_NETWORK_EXPORT PushErrorCode
{
	Q_GADGET
	Q_ENUMS(Type)
	Q_FLAGS(Types)

public:

    /*!
     * @brief The result codes that occur from a @c PushService operation.
     *
     * @since BlackBerry 10.0.0
     */
     enum Type {

        /*!
         * @brief Indicates a success.
         *
         * @since BlackBerry 10.0.0
         */
        NoError = 0,

        /*!
         * @brief Indicates an internal error.
         *
         * This result code can occur from any of the following @c PushService operations: @c createSession(),
         * @c createChannel(), @c destroyChannel(), @c registerToLaunch(), and @c unregisterFromLaunch().
         * 
         * Recommended action: When you receive this code, it's usually recommended that you try the operation again.
         *
         * @since BlackBerry 10.0.0
         */
		InternalError = 500,

		/*!
		 * @brief Indicates the connection to the Push Agent has been closed.
		 *
		 * This result code can occur from any of the following @c PushService operations: @c createSession(),
         * @c createChannel(), @c destroyChannel(), @c registerToLaunch(), and @c unregisterFromLaunch().
         *
         * Recommended action: This result code will trigger the @c connectionClosed signal. After receiving the
         * @c connectionClosed signal, the application should re-establish the connection with the Push Agent, and
         * then retry the operation once the connection has been reestablished.  See @c connectionClosed.
         *
         * @since BlackBerry 10.2.0
		 */
		ConnectionClosed = 501,

		/*!
		 *
		 * @brief Indicates the application does not have the required permission to connect with the Push Agent.
		 *
		 * This result code can occur from any of the following @c PushService operations: @c createSession(),
         * @c createChannel(), @c destroyChannel(), @c registerToLaunch(), and @c unregisterFromLaunch().
		 *
		 * Recommended action: If you are writing a consumer application for the general public,
		 * make sure you specify the following permission tag in your bar-descriptor.xml file:
		 *
		 * @code
		 * 	<permission system="true">_sys_use_consumer_push</permission>
		 * @endcode
		 *
		 * 	If you are writing an enterprise application, make sure your application is installed in the Work perimeter.
		 *
		 * @since BlackBerry 10.2.0
		 */
		NoPermCreateConnection  = 502,


        /*!
         * @brief Indicates an invalid device PIN as determined by the PPG.
         *
         * This result code can occur from any of the following @c PushService operations: @c createChannel() and @c destroyChannel()
         * (only if using public/BIS PPG).
         *
         * Recommended action: When you receive this code, it might be useful to communicate the issue to the user through an alert message.
         * Retrying the operation might not be helpful since it's most likely an unrecoverable error
         * that is beyond the control of the application.
         *
         * @since BlackBerry 10.0.0
         */
		InvalidPin = 10001,

        /*!
         * @brief Indicates an invalid provider application ID.
         *
         * This result code can occur from any of the following @c PushService operations: @c createSession(),
         * @c createChannel(), @c destroyChannel() (only if using public/BIS PPG).
         *
         * Recommended action: When you receive this code, fixing the application ID programmatically and retrying might correct the issue.
         * The provider application ID is passed in to the @c PushService constructor.
         *
         * @since BlackBerry 10.0.0
         */
		InvalidProviderId = 10002,

        /*!
         * @brief Indicates that a successful destroy channel has already been done.
         * 
         * This result code can occur from the following @c PushService operation: @c destroyChannel() (only if using public/BIS PPG).
         * 
         * Recommended action: This result code is for your information only. Most applications can probably ignore this code altogether.
         *
         * @since BlackBerry 10.0.0
         */
		UserAlreadyUnregistered = 10004,

        /*!
         *
         * @brief Indicates that the content provider has already unsubscribed the user.
         * 
         * This result code can occur from any of the following @c PushService operations: @c destroyChannel() (only if using public/BIS PPG).
         * 
         * Recommended action: This result code is for your information only. Most applications can probably ignore this code altogether.
         * 
         *
         * @since BlackBerry 10.0.0
         */
		AlreadyUnsubscribedByProvider = 10005,

        /*!
         * @brief Indicates that the subscriber on the PPG is in an invalid state.
         *
         * This result code can occur from any of the following @c PushService operations: @c createChannel() and
         * @c destroyChannel() (only if using public/BIS PPG). However, this error code should not typically be encountered.
         * It would only occur if a create or destroy channel operation internally causes the state of a subscriber on the PPG to be in an invalid state.
         * 
         * @note Recommended action: If this code occurs, it should be logged and reported to the RIM support team.
         *
         * @since BlackBerry 10.0.0
         */
		InvalidSubscriptionStatus = 10006,

        /*!
         * @brief Indicates that a destroy channel operation failed because the subscriber could not be found on the PPG.
         * 
         * This result code can occur from any of the following @c PushService operations: @c destroyChannel() (only if using public/BIS PPG).
         * 
         * Recommended action: This code can most likely be ignored. If the subscriber could not be found on the PPG, then
         * destroying the channel will have no effect anyway (it is as if they were never registered with the PPG using @c createchannel() ).
         *
         * @since BlackBerry 10.0.0
         */
		PinNotFound = 10007,

        /*!
         * @brief Indicates that a create channel or destroy channel operation passed an expired authentication token to the PPG.
         * 
         * This result code can occur from any of the following @c PushService operations: @c createChannel() and
         * @c destroyChannel() (only if using public/BIS PPG).
         * 
         * Recommended action: If this code occurs, retrying the operation might correct the issue.
         *
         * @since BlackBerry 10.0.0
         */
		SubscriptionRequestTimeOut = 10008,

        /*!
         * @brief Indicates that a create channel or destroy channel operation passed an invalid authentication token to the PPG.
         * 
         * This result code can occur from any of the following @c PushService operations: @c createChannel() and
         * @c destroyChannel() (only if using public/BIS PPG). However, it is very unlikely that you will encounter this result code.
         *
         * @note Recommended action: If this code occurs, it should be logged and reported to the RIM support team.
         *
         * @since BlackBerry 10.0.0
         */
		InvalidAccess = 10009,

        /*!
         * @brief Indicates that too many devices have already performed a create channel request for the provider application ID.
         * 
         * This result code can occur from any of the following @c PushService operations: @c createChannel() (only if using public/BIS PPG).
         *
         * @note Recommended action: This result code should be communicated back to the content provider and then to RIM to try to
         * increase the allowed subscription limit.
         *
         * @since BlackBerry 10.0.0
         */
		SubscriptionLimitExceeded = 10010,

        /*!
         * @brief Indicates that the application attempting to create a channel is sending an invalid operating
         * system version number or an invalid device model number.
         * 
         * This result code can occur from any of the following @c PushService operations: @c createChannel() (only if using public/BIS PPG).
         * 
         * Recommended action: When you receive this code, it might be useful to communicate the issue to the user through an alert message.
         * Retrying the operation is not recommended since this is an unrecoverable error that is beyond the control of the application.
         *
         * @since BlackBerry 10.0.0
         */
		InvalidSubscriptionParameters = 10011,

        /*!
         * @brief Indicates that a content provider has manually suspended a user already.
         *
         * This code is similar to the @c AlreadyUnsubscribedByProvider error.
         * 
         * This result code can occur from any of the following @c PushService operations: @c destroyChannel() (only if using public/BIS PPG).
         * 
         * Recommended action: Most applications can ignore this result code.
         *
         * @since BlackBerry 10.0.0
         */
		SubscriptionAlreadySuspendedByProvider = 10012,

        /*!
         * @brief Indicates that a create session operation must be performed before attempting this operation.
         * 
         * This result code can occur from any of the following @c PushService operations:
         * @c createChannel(), @c destroyChannel(), @c registerToLaunch(), and @c unregisterFromLaunch().
         * 
         * Recommended action: This usually means a programming error in the application.
         *
         * @since BlackBerry 10.0.0
         */
		SessionNotFound = 10100,

        /*!
         * @brief Indicates that a PPG URL was not specified while attempting to perform a create channel operation.
         * 
         * This result code can occur from any of the following @c PushService operations: @c createChannel().
         * 
         * Recommended action: This usually means a programming error in the application. Make sure that a PPG URL is specified
         * when performing a Create Channel operation.
         *
         * @since BlackBerry 10.0.0
         */
		PpgUrlMissing = 10102,

        /**
         * @brief Indicates a failed create channel or destroy channel operation due to a push transport failure.
         * 
         * This result code can occur from any of the following @c PushService operations: @c createChannel() and @c destroyChannel()
         * (only if using public/BIS PPG).
         * 
         * Recommended action: After receiving the @c pushTransportReady() signal, retry the operation.
         * This error can also occur when the user's wireless connection (e.g. Wi-Fi, Mobile Network) is off or temporarily down,
         * so it might make sense to communicate this issue to the user.
         *
         * @since BlackBerry 10.0.0
         */
		TransportFailure = 10103,

        /*!
         * @brief Indicates that an invalid message was written to the push service file descriptor.
         * 
         * This result code can occur from a custom write operation to the push service file descriptor.
         * 
         * Recommended action: This usually means a programming error in the application. Instead of writing to the push service file descriptor directly,
         * it is recommended to use the @c PushService object.
         *
         * @since BlackBerry 10.0.0
         */
		InvalidCommand = 10104,

        /*!
         * @brief Indicates that a certain operation is currently not supported.
         * 
         * Recommended action: This operation/feature might not yet be implemented and so should not be performed.
         *
         * @since BlackBerry 10.0.0
         */
		CommandNotSupported = 10105,

        /*!
         * @brief Indicates that the destroy channel operation is invalid because a create channel operation was not performed before.
         * 
         * This result code can occur from any of the following @c PushService operations: @c destroyChannel()
         * 
         * Recommended action: This might mean a programming error in the application.
         *
         * @since BlackBerry 10.0.0
         */
		UserNotRegistered = 10106,

        /*!
         * @brief Indicates an issue with obtaining a port from the PPG in a create channel operation.
         * 
         * This result code can occur from any of the following @c PushService operations: @c createChannel().
         * 
         * Recommended action: Retrying the operation might correct the issue.
         *
         * @since BlackBerry 10.0.0
         */
		SubscribeMissingPort = 10107,

        /*!
         * @brief Indicates an issue with obtaining a subscription return code from the PPG during a create channel operation.
         * 
         * This result code can occur from any of the following @c PushService operations: @c createChannel() (only if using public/BIS PPG).
         * 
         * Recommended action: Retrying the operation might correct the issue.
         *
         * @since BlackBerry 10.0.0
         */
		SubscribeMissingRc = 10108,

        /*!
         * @brief Indicates that the create channel or destroy channel operation failed due to a failure to communicate with the PPG.
         * 
         * This result code can occur from any of the following @c PushService operations: @c createChannel() and @c destroyChannel()
         * (only if using public/BIS PPG)
         * 
         * Recommended action: After receiving the @c pushTransportReady() signal, retry the operation.
         *
         * @since BlackBerry 10.0.0
         */
		SubscriptionContentNotAvailable = 10110,

        /*!
         * @brief Indicates that the invocation target key is invalid.
         * 
         * This result code can occur from any of the following @c PushService operations: @c createSession().
         * 
         * Recommended action: Fixing the invocation target key programmatically and retrying might correct the issue.
         * The invocation target key is passed in to the @c PushService constructor.
         *
         * @since BlackBerry 10.0.0
         */
		InvalidTargetKey = 10111,

        /*!
        * @brief Indicates that a session already exists.
        * 
        * This result code can occur from any of the following @c PushService operations: @c createSession().
        * 
        * Recommended action: Check the application provider ID and target key to ensure that they are valid and unique.
         *
         * @since BlackBerry 10.0.0
        */
		SessionAlreadyExists = 10112,

//!@cond PRIVATE
        /*!
         * @brief Not used anymore.  See @c InvalidPpgUrl.
         */
		InvalidPpgUrlOrPpgNotAvailable = 10113,
//!@endcond


        /*!
         * @brief Indicates a failed create channel or destroy channel operation due to an invalid PPG URL.
         * 
         * This result code can occur from any of the following @c PushService operations: @c createChannel() and @c destroyChannel()
         * (only if using public/BIS PPG).
         * 
         * Recommended action: Check that the PPG URL is valid.
         *
         * @since BlackBerry 10.0.0
         */
		InvalidPpgUrl = 10114
	};

	Q_DECLARE_FLAGS(Types, Type)

private:
//!@cond PRIVATE
	PushErrorCode();
	~PushErrorCode();
//!@endcond PRIVATE
};

Q_DECLARE_OPERATORS_FOR_FLAGS(PushErrorCode::Types)

} // namespace network
} // namespace bb

#endif /* BB_NETWORK_PUSHERRORCODE_HPP */
