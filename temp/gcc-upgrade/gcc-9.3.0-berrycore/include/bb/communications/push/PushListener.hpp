/*
 * (C) 2011-2013 Research In Motion Ltd. All Rights Reserved.
 * RIM, Research In Motion -- Reg. U.S. Patent and Trademark Office
 * The RIM Logo and Inter@ctive are trademarks of Research In Motion, Limited
 * All materials confidential information of Research In Motion, Limited
 *
 * PushListener.hpp
 *
 *  Created on: Oct 25, 2011
 *      Author: rtalwalkar
 *
 * @since 10.0.0
 */

#ifndef BB_COMMUNICATIONS_PUSH_PUSHLISTENER_HPP_
#define BB_COMMUNICATIONS_PUSH_PUSHLISTENER_HPP_
#include <string>
#include <map>
#include <bb/communications/push/PushCommand.hpp>
#include <bb/communications/push/PushPayload.hpp>
#include <bb/communications/push/PushStatus.hpp>

namespace bb {
namespace communications {
namespace push {
class PushListener {
public:

	/**
	 * Destructor
	 *
	 * @since 10.0.0
	 */
	virtual ~PushListener() {}

	/** Callback in response to createSession call
	 *
	 *  @param status   PushStatus response for the createSession request call
	 *
	 *  @since 10.0.0
	 */
    virtual void onCreateSessionComplete(const PushStatus& status) = 0;

    /** Callback in response to createChannel call
	 *
	 *  @param status   PushStatus response for the createChannel request call
	 *  @param token    The token received from the Push Service
	 *                  after successfully creating the push channel
	 *                  This token should be communicated to the Push Initiator.
	 *
	 * @since 10.0.0
	 */
    virtual void onCreateChannelComplete(const PushStatus& status, const std::string& token) = 0;

    /** Call back in response to destroyChannel call
     *
     *  @param status   PushStatus response for the destroyChannel request call
     *
     */
    virtual void onDestroyChannelComplete(const PushStatus& status)=0;

    /** Callback in response to registerToLaunch call
     *
     *  @param status   PushStatus response for the registerToLaunch call
     *
     *  @since 10.0.0
     *
     */
    virtual void onRegisterToLaunchComplete(const PushStatus& status)=0;

    /** Callback in response to unregisterFromLaunch call
     *
     *  @param status   PushStatus response for the unregisterFromLaunch call
     *
     *  @since 10.0.0
     */
    virtual void onUnregisterFromLaunchComplete(const PushStatus& status)=0;

    /** The callback that is invoked when SIM card is changed.
     *  When this happens, the push is discarded, and a call to
	 *  createChannel() is recommended.
     *
     */
    virtual void onSimChange()=0;

    /**
	 * Sent when a previous @c createChannel() or @c destroyChannel() request
	 * failed with a @c PUSH_ERR_TRANSPORT_FAILURE (10103) or PUSH_ERR_SUBSCRIPTION_CONTENT_NOT_AVAILABLE (10110) status code.
	 *
	 * @param command	to recall the last command that failed (either @c CreateChannel or @c DestroyChannel).
	 *
	 * @code
	 * if (command == CreateChannel) {
	 *	pushService->createChannel(ppgUrl);
	 * }
	 * else if (command == DestroyChannel) {
	 *	pushService->destroyChannel();
	 * }
	 * @endcode
	 *
	 * @since 10.0.0
	 */
    virtual void onPushTransportReady(PushCommand /* command */) {};
};

class PushListener2 : public PushListener  {
public:

	/**
	 * Destructor
	 *
	 * @since 10.1.0
	 */
	virtual ~PushListener2() {}

    /** The callback that is invoked when the connection to the Push Agent has been deleted.
     *  When this happens, the application or service needs to re-establish the connection with
     *  the Push Agent by calling @c getPushFd() periodically until @c getPushFd() returns a valid file descriptor.
     *  After obtaining a valid file descriptor, the application must then call @c createSession().
     *
     * @since 10.1.0
     */
    virtual void onConnectionClose() = 0;
};

} // namespace push
} // namespace communications
} // namespace bb

#endif /* BB_COMMUNICATIONS_PUSH_PUSHLISTENER_HPP_ */
