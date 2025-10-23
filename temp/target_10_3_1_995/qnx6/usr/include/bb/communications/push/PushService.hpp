/*
 * (C) 2011-2012 Research In Motion Ltd. All Rights Reserved.
 * RIM, Research In Motion -- Reg. U.S. Patent and Trademark Office
 * The RIM Logo and Inter@ctive are trademarks of Research In Motion, Limited
 * All materials confidential information of Research In Motion, Limited
 *
 * PushService.hpp
 *
 *  Created on: Oct 25, 2011
 *      Author: rtalwalkar
 *
 * @since 10.0.0
 */
#ifndef BB_COMMUNICATIONS_PUSH_PUSHSERVICE_HPP_
#define BB_COMMUNICATIONS_PUSH_PUSHSERVICE_HPP_

#include <string>
#include <map>
#include <bps/navigator_invoke.h>
#include <bb/communications/push/PushListener.hpp>

#define INVALID_PPS_FILE_DESCRIPTOR		-1

namespace bb {
namespace communications {
namespace push {

class PushServicePrivate;

class PushService {
public:
    /** Constructor for the PushService object
     *
     * @param providerApplicationId   Unique identifier of the client application
     * @param targetKey	Invocation target key
     * @return PushService object
     *
     * @since 10.0.0
     */
    PushService(const std::string& providerApplicationId, const std::string& targetKey);

    /** Destructor for the PushService object
     *
     * @return PushService object
     *
     * @since 10.0.0
     */
    ~PushService();

    /**
     * @return Push PPS file descriptor
     *
     * @since 10.0.0
     */
    int getPushFd();

    /**
     * Process the incoming pps message
     *
     * @since 10.0.0
     */
    void processMsg();

    /** The client must first create a session with the PNS agent as a first step.
     *  Creating a session sets up the IPC between the client and the agent.  This needs
     *  to be called every time a the application is launched.
     *
     *  @since 10.0.0
     */
    void createSession();

    /** Create a channel for receiving push messages from the Push Initiator
     * Once the channel is successfully established, the application does not have to call it
     * again. Push Service maintains the channel.
     *
     * @param ppgUrl	This is the URL of the Push Proxy Gateway(PPG)
     *
     * @since 10.0.0
     */
    void createChannel(const std::string& ppgUrl);

    /** Destroy the channel which the application no longer wishes to use
	 */
    void destroyChannel();

    /** If the application wishes to be launched in background upon receiving a push, this API can be called
	 *
	 * @since 10.0.0
	 */
    void registerToLaunch();

    /** If an application no long wishes to be launched when a notification is received,
	 * this API needs to be invoked
	 *
	 * @since 10.0.0
	 */
    void unregisterFromLaunch();

    /** In order to receive notifications, the push-enabled application needs to add a push listener object
     * @param pListener	Instance of an object extending PushListener class
     *
     * @since 10.0.0
     */

    void setListener(PushListener *pListener);

    /** Retrieve the Listener instance
	 * @return pListener    Instance of an object extending PushListener class
	 *
	 * @since 10.0.0
	 */
	PushListener* getListener();

	/** If the push-enabled application wishes to accept a push with the server. This call is required
	 * when the push data indicates that it requires application level acknowledgement for the push.
	 * See @c PushPayload
	 *
	 * @param: payloadId	unique identifier of the push notification which is stored in the payload object.
	 *
	 * @since 10.0.0
	 */
	void acceptPush(const std::string& payloadId);

	/** If the push-enabled application wishes to reject a push with the server. This call is required
	 * when the push data indicates that it requires application level acknowledgement for the push.
	 * See @c PushPayload.
	 *
	 * @param: payloadId	unique identifier of the push notification which is stored in the payload object.
	 *
	 * @since 10.0.0
	 */
	void rejectPush(const std::string& payloadId);

	/*
	 * @return the provider application id
	 *
	 * @since 10.0.0
	 */
	const std::string& getProviderApplicationId() const;

	/*
	 * @return the target key
	 *
	 * @since 10.0.0
	 */
	const std::string& getTargetKey() const;

	/*
	 * @return the dname
	 *
	 * @since 10.0.0
	 */
	const std::string& getDName() const;

private:

	PushServicePrivate *d_ptr;
};
} // namespace push
} // namespace communications
} // namespace bb

#endif /* BB_COMMUNICATIONS_PUSH_PUSHSERVICE_HPP_ */
