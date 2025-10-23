/*
 * PnsErrno.h
 *
 * (C) 2011-2013 Research In Motion Ltd. All Rights Reserved.
 * RIM, Research In Motion -- Reg. U.S. Patent and Trademark Office
 * The RIM Logo and Inter@ctive are trademarks of Research In Motion, Limited
 * All materials confidential information of Research In Motion, Limited
 *
 *  Created on: 2011-11-17
 *      Author: cpang
 *
 *  Possible return codes from Push Data.
 *
 *  @since 10.0.0
 */

#ifndef BB_COMMUNICATIONS_PUSH_PUSHERRNO_HPP_
#define BB_COMMUNICATIONS_PUSH_PUSHERRNO_HPP_
namespace bb {
namespace communications {
namespace push {

/**
 *	This enumeration defines the error codes that may be returned as a result of a <code>PushService</code> operation
 */
enum PushErrorCode {

	/**
	 * Indicates the operation was successful.
	 */
	PUSH_NO_ERR = 0,

	/**
	 * Error code for an internal error.
	 *
	 * Operations this error can occur on: Create Session, Create Channel, Destroy Channel, Register to Launch, Unregister from Launch
	 *
	 * Recommended action: Retrying the operation might correct the issue.
	 */
	PUSH_ERR_INTERNAL_ERROR = 500,

	/**
	 * Error code when the connection to the Push Agent has been closed.
	 *
	 * Operation this error can occur on: Create Session, Create Channel, Destroy Channel, Register to Launch, Unregister from Launch
	 *
	 * Recommended action: This error will trigger the @c onConnectionClose() callback where the application or service needs to
	 * re-establish the connection with the Push Agent. Retry the operation once the connection has been reestablished. See @c onConnectionClose()
	 */
	PUSH_ERR_CONNECTION_CLOSE = 501,

	/**
	 * Error code when the application does not have the required permission to connect with the Push Agent.
	 *
	 * Operations this error can occur on: Create Session, Create Channel, Destroy Channel, Register to Launch, Unregister from Launch
	 *
	 * Recommended action: If you are writing a consumer application for the general public,
	 * make sure you specify the following permission tag in your bar-descriptor.xml file:
	 *
	 * @code
	 * 	<permission system="true">_sys_use_consumer_push</permission>
	 * @endcode
	 *
	 * 	If you are writing an enterprise application, make sure your application is installed in the Work perimeter.
	 */
	PUSH_ERR_NO_PERM_CREATE_CONNECTION  = 502,

	/**
	 * Error code for an invalid device PIN as determined by the PPG.
	 *
	 * Operations this error can occur on: Create Channel, Destroy Channel (only if using public/BIS PPG)
	 *
	 * Recommended action: Retrying the operation might not be helpful since this is most likely an unrecoverable error
	 * that is out of control of the application.  It might make sense to communicate this issue up to the user.
	 */
	PUSH_ERR_INVALID_PIN = 10001,

	/**
	 * Error code for an invalid provider application ID.
	 *
	 * Operations this error can occur on: Create Session, Create Channel, Destroy Channel (only if using public/BIS PPG)
	 *
	 * Recommended action: Fixing the application ID programmatically and retrying might correct the issue.
	 * The provider application ID is passed in to the <code>PushService</code> constructor.
	 */
	PUSH_ERR_INVALID_PROVIDER_ID = 10002,

	/**
	 * Error code when attempting to call destroy channel again after a successful destroy channel has already been done.
	 *
	 * Operations this error can occur on: Destroy Channel (only if using public/BIS PPG)
	 *
	 * Recommended action: Most applications will typically want to just ignore this error code when it comes back.
	 */
	PUSH_ERR_USER_ALREADY_UNREGISTERED = 10004,

	/**
	 * Error code when attempting to call destroy channel after a content provider has already done the destroying of the channel
	 * by unregistering a user.
	 *
	 * Operations this error can occur on: Destroy Channel (only if using public/BIS PPG)
	 *
	 * Recommended action: Most applications will typically want to just ignore this error code when it comes back.
	 */
	PUSH_ERR_ALREADY_UNSUBSCRIBED_BY_PROVIDER = 10005,

	/**
	 * This error code should not typically be encountered.
	 * It would only occur if a create or destroy channel operation internally causes the state of a subscriber on the PPG to be in an invalid state.
	 *
	 * Operations this error can occur on: Create Channel, Destroy Channel (only if using public/BIS PPG)
	 *
	 * Recommended action: If this error occurs, it should be logged and reported to the RIM support team.
	 */
	PUSH_ERR_INVALID_SUBSCRIPTION_STATUS = 10006,

	/**
	 * Error code for when a destroy channel operation fails because the subscriber could not be found on the PPG's end.
	 *
	 * Operations this error can occur on: Destroy Channel (only if using public/BIS PPG)
	 *
	 * Recommended action: This error can most likely be ignored since if the subscriber could not be found on the PPG's end, then
	 * destroying the channel will have no effect anyway (it is as if they were never registered with the PPG using create channel).
	 */
	PUSH_ERR_PIN_NOT_FOUND = 10007,

	/**
	 * Error code for when a create channel or destroy channel operation internally passes an expired authentication token to the PPG.
	 *
	 * Operations this error can occur on: Create Channel, Destroy Channel (only if using public/BIS PPG)
	 *
	 * Recommended action: Retrying the operation might correct the issue.
	 */
	PUSH_ERR_SUBSCRIPTION_REQUEST_TIME_OUT = 10008,

	/**
	 * This error code should not typically be encountered.
	 * It would only occur if a create channel or destroy channel operation internally passes an invalid authentication token to the PPG.
	 *
	 * Operations this error can occur on: Create Channel, Destroy Channel (only if using public/BIS PPG)
	 *
	 * Recommended action: If this error occurs, it should be logged and reported to the RIM support team.
	 */
	PUSH_ERR_INVALID_ACCESS = 10009,

	/**
	 * Error code for when too many devices have already performed a create channel for the provider application ID.
	 * The create channel is described as still "active" because no destroy channel has been done for it.
	 *
	 * Operations this error can occur on: Create Channel (only if using public/BIS PPG)
	 *
	 * Recommended action: No action can be taken by the application for this error, but it should somehow be communicated
	 * back to the content provider and then to RIM to try to increase the allowed subscription limit.
	 *
	 */
	PUSH_ERR_SUBSCRIPTION_LIMIT_EXCEEDED = 10010,

	/**
	 * Error code for when a device attempting to do a create channel has an invalid operating system version number or an invalid device model number.
	 *
	 * Operations this error can occur on: Create Channel (only if using public/BIS PPG)
	 *
	 * Recommended action: Retrying the operation is not recommended since this is an unrecoverable error that is out of control of the application.
	 * It might make sense to communicate this issue up to the user.
	 */
	PUSH_ERR_INVALID_SUBSCRIPTION_PARAMETERS = 10011,

	/**
	 * Error code when attempting to call destroy channel after a content provider has manually suspended a user.
	 * Similar to the <code>CHANNEL_ALREADY_DESTROYED_BY_PROVIDER</code> error.
	 *
	 * Operations this error can occur on: Destroy Channel (only if using public/BIS PPG)
	 *
	 * Recommended action: Most applications will typically want to just ignore this error code when it comes back.
	 */
	PUSH_ERR_SUBSCRIPTION_ALREADY_SUSPENDED_BY_PROVIDER = 10012,

	/**
	 * Error code when attempting to perform an operation and a create session has not been done beforehand.
	 *
	 * Operations this error can occur on: Create Channel, Destroy Channel, Register to Launch, Unregister from Launch
	 *
	 * Recommended action: This usually means a programming error in the application.
	 */
	PUSH_ERR_SESSION_NOT_FOUND = 10100,

	/**
	 * Error code when attempting to perform a create channel without specifying a PPG URL.
	 *
	 * Operations this error can occur on: Create Channel
	 *
	 * Recommended action: This usually means a programming error in the application. Make sure that a PPG URL is specified
	 * when performing a Create Channel operation.
	 */
	PUSH_ERR_PPGURL_MISSING = 10102,

	/**
     * Error code: Indicates a failed create channel or destroy channel operation due to a push transport failure.
     *
     * Operation: This error can occur on: Create Channel, Destroy Channel (only if using public/BIS PPG).
     *
     * Recommended action: After receiving the onPushTransportReady callback, retry the operation.
     * This error can also occur when the user's wireless connection (e.g. Wi-Fi, Mobile Network) is off or temporarily down,
     * so it might make sense to communicate this issue to the user.
     */
	PUSH_ERR_TRANSPORT_FAILURE = 10103,

	/**
	 * Error code when an invalid message is written to the push service file descriptor
	 *
	 * Operations this error can occur on: custom write operation to the push service file descriptor
	 *
	 * Recommended action: This usually means a programming error in the application. Instead of writing to the push service file descriptor directly,
	 * it is recommended to use the <code>PushService</code> object.
	 */
	PUSH_ERR_INVALID_COMMAND = 10104,

	/**
	 * Error code when a certain operation is currently not supported.
	 *
	 * Recommended action: This operation/feature might not yet be implemented and so should not be performed.
	 */
	PUSH_ERR_COMMAND_NOT_SUPPORTED = 10105,

	/**
	 * Error code when attempting to perform a destroy channel and a create channel has not been done beforehand.
	 *
	 * Operations this error can occur on: Destroy Channel
	 *
	 * Recommended action: This might mean a programming error in the application.
	 */
	PUSH_ERR_USER_NOT_REGISTERED = 10106,

	/**
	 * Error code as a result of an issue on a create channel operation obtaining a port from the PPG.
	 *
	 * Operations this error can occur on: Create Channel
	 *
	 * Recommended action: Retrying the operation might correct the issue.
	 */
	PUSH_ERR_SUBSCRIBE_MISSING_PORT = 10107,

	/**
	 * Error code as a result of an issue on a create channel operation obtaining a subscription return code from the PPG.
	 *
	 * Operations this error can occur on: Create Channel (only if using public/BIS PPG)
	 *
	 * Recommended action: Retrying the operation might correct the issue.
	 */
	PUSH_ERR_SUBSCRIBE_MISSING_RC = 10108,

	/**
	 * Error code when a create channel or destroy channel operation has failed due to a failure to communicate with the PPG.
	 *
	 * Operations this error can occur on: Create Channel, Destroy Channel (only if using public/BIS PPG)
	 *
	 * Recommended action: After receiving the onPushTransportReady callback, retry the operation.
	 */
	PUSH_ERR_SUBSCRIPTION_CONTENT_NOT_AVAILABLE = 10110,

	/**
	 * Error code when a create session operation fails because the invocation target key is invalid
	 *
	 * Operations this error can occur on: Create Session
	 *
	 * Recommended action: Fixing the invocation target key programmatically and retrying might correct the issue.
	 * The invocation target key is passed in to the <code>PushService</code> constructor.
	 */
	PUSH_ERR_INVALID_TARGET_KEY = 10111,

	/**
	* Code that indicates that a session already exists.
	*
	* This result code can occur from any of the following operations: Create Session
	*
	* Recommended action: Check the application provider ID and target key to ensure that they are valid and unique.
	*/
	PUSH_ERR_SESSION_ALREADY_EXISTS = 10112,

//!@cond PRIVATE
	/**
	 *  @brief Not used anymore.  See @c PUSH_ERR_INVALID_PPG_URL.
	 */
	PUSH_ERR_INVALID_PPGURL_OR_PPG_NOT_AVAILABLE	= 10113,
//!@endcond

	/**
	 * Error code: Indicates a failed create channel or destroy channel operation due to an invalid PPG URL.
	 *
	 * Operation: This error can occur on: Create Channel, Destroy Channel (only if using public/BIS PPG).
	 *
	 * Recommended action: Check that the PPG URL is valid.
	 */
	PUSH_ERR_INVALID_PPG_URL = 10114
};
} // namespace push
} // namespace communications
} // namespace bb

#endif /* BB_COMMUNICATIONS_PUSH_PUSHERRNO_HPP_ */
