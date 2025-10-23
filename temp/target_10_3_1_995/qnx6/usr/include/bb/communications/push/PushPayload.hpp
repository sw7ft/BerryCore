/*
 * (C) 2012 Research In Motion Ltd. All Rights Reserved.
 * RIM, Research In Motion -- Reg. U.S. Patent and Trademark Office
 * The RIM Logo and Inter@ctive are trademarks of Research In Motion, Limited
 * All materials confidential information of Research In Motion, Limited
 *
 * PushPayload.hpp
 *
 *  Created on: Feb 22, 2012
 *
 * @since 10.0.0
 */

#ifndef BB_COMMUNICATIONS_PUSH_PUSHPAYLOAD_HPP_
#define BB_COMMUNICATIONS_PUSH_PUSHPAYLOAD_HPP_
#include <string>
#include <map>
#include <sys/pps.h>
#include <bps/navigator_invoke.h>

// Invocation action and type
#define PUSH_INVOCATION_ACTION		"bb.action.PUSH"
#define PUSH_INVOCATION_TYPE		"application/vnd.push"
#define PUSH_INVOCATION_FILTER		"actions=bb.action.PUSH; types=application/vnd.push;"

namespace bb {
namespace communications {
namespace push {

class PushPayloadPrivate;

class PushPayload{
public:
	/**
	 *  Creates a new @c PushPayload object.
	 *
	 *  @since 10.0.0
	 */
	PushPayload();

	/**
	 *  Creates a new @c PushPayload object.
	 *
	 *  @param invoke	The payload object within the invoke object contains push id,
	 *  					the raw pushed content,
	 *  					the headers which are the Key-value pairs of metadata sent with the pushed content and
	 *  					a flag to indicate that application level acknowledgement is required
	 *  					for this push.
	 * @since 10.0.0
	 */
	explicit PushPayload(const navigator_invoke_invocation_t *invoke);

	/**
	 *  Creates a new @c PushPayload object.
	 *
	 *  @param invokePushData	The invokePushData object contains push id,
	 *  					the raw pushed content,
	 *  					the headers which are the Key-value pairs of metadata sent with the pushed content and
	 *  					a flag to indicate that application level acknowledgement is required
	 *  					for this push.
	 *	@param invokePushDataLength	length of the push data
	 *
	 *	@since 10.0.0
	 */
	PushPayload(const unsigned char* invokePushData, int invokePushDataLength);

	/**
	 * Creates a copy of of an existing @c PushPayload object.
	 *
	 * @param other The existing @c PushPayload object that will be copied.
	 *
	 * @since 10.0.0
	 */
	PushPayload(const PushPayload &other);
	PushPayload(const std::string& id, const unsigned char* data, const int dataLength, const std::map<std::string, std::string>& headers, bool ackRequired);

	/**
	 * Destroys this @c PushPayload object.
	 *
	 * @since 10.0.0
	 */
	virtual ~PushPayload();

	/**
	 * Copies the data of an existing @c PushPayload object to this object.
	 *
	 * @param rhs The existing @c PushPayload object to copy.
	 *
	 * @since 10.0.0
	 */
	PushPayload& operator=(const PushPayload& rhs);

	/*
	 * @return true if the push payloads are equal, false otherwise
	 *
	 * @since 10.0.0
	 */
	bool operator==(const PushPayload& rhs) const;

	/*
	 * @return true if the push payloads are not equal, false otherwise
	 *
	 * @since 10.0.0
	 */
	bool operator!=(const PushPayload& rhs) const;

	/**
	   * Returns the push notification data
	   *
	   * @return  push notification data
	   *
	   * @since 10.0.0
	   */
	 const unsigned char* getData() const;


	 /**
	   * Returns the push notification headers
	   *
	   * @return  push notification headers
	   *
	   * @since 10.0.0
	   */
	 const std::map<std::string, std::string>& getHeaders() const;

	 /**
	  * Returns the length of the push notification data
	  *
	  * @return length of the push notification data
	  *
	  * @since 10.0.0
	  */
	 int getDataLength() const;

	 /**
	  * @return true if application level acknowledgement is required. false otherwise
	  * Note: The Client application must invoke the accept command if this is true.
	  *
	  * @since 10.0.0
	  */
	 bool isAckRequired() const;

	 /**
	  * @return the Push ID
	  *
	  * @since 10.0.0
	  */
	 const std::string& getId() const;

	 /**
	  * @return true if the push payload is valid. false otherwise
	  *
	  * @since 10.0.0
	  */
	 bool isValid() const;

private:
	 PushPayloadPrivate *d_ptr;
};

} // namespace push
} // namespace communications
} // namespace bb

#endif /* BB_COMMUNICATIONS_PUSH_PUSHPAYLOAD_HPP_ */
