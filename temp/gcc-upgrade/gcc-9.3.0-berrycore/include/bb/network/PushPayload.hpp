/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_NETWORK_PUSHSPAYLOAD_HPP
#define BB_NETWORK_PUSHSPAYLOAD_HPP

#include <bb/network/Global>
#include <bb/system/InvokeRequest>

#include <QString>
#include <QVariantMap>

// Invocation action
#define BB_PUSH_INVOCATION_ACTION		"bb.action.PUSH"

namespace bb
{
namespace network
{

class PushPayloadPrivate;

/*!
 * @headerfile PushPayload.hpp <bb/network/PushPayload>
 *
 * @brief Encapsulates the push content received from the Push Proxy Gateway (PPG) by way of the Invocation framework.
 *
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Push"/>
 * <library name="bbnetwork"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */

class BB_NETWORK_EXPORT PushPayload {
public:

	/*!
	 * @brief Creates a new @c PushPayload object where the push payload is invalid and the validity flag is set to false.
	 *
	 *
	 * @since BlackBerry 10.0.0
	 */
	PushPayload();

    /*!
     * @brief Creates a new @c PushPayload object based on the invoke request object.
     *
     * The validity flag will be set to @c false when the push data in the @c InvokeRequest object is invalid.
     * You can determine validity of this push payload by calling @c isValid() before you process the data.
     *
     * The payload object within the @c InvokeRequest object contains the following:
     * - A push ID
     * - The raw push content
     * - The headers (key-value pairs of metadata available with the push content)
     * - A flag to indicate that application level acknowledgement is required for this push message.
     *
     * @param invoke    The data used to construct the invoke message.
     *
     *
     * @since BlackBerry 10.0.0
     */
    explicit PushPayload(const bb::system::InvokeRequest &invoke);

    /*!
     * @brief Creates a copy of of an existing @c PushPayload object.
     *
     * @param other The existing @c PushPayload object that will be copied.
     *
     *
     * @since BlackBerry 10.0.0
     */
    PushPayload(const PushPayload &other);

    /*!
     * @brief Destroys this @c PushPayload object.
     *
     *
     * @since BlackBerry 10.0.0
     */
	~PushPayload();

    /*!
     * @brief Copies the data from an existing @c PushPayload object.
     *
     * @param rhs The existing @c PushPayload object that will be copied.
     *
     * @return A @c PushPayload object containing the copied data.
     *
     *
     * @since BlackBerry 10.0.0
     */
	PushPayload& operator=(const PushPayload &rhs);

    /*!
     * @brief Compares push payload objects to see if they are equal.
     *
     * @param rhs The @c PushPayload object that will be compared.
     *
     * @return @c true if the push payload objects are equal (attributes have the same value), @c false otherwise.
     *
     *
     * @since BlackBerry 10.0.0
     */
	bool operator==(const PushPayload &rhs) const;

    /*!
     * @brief Compares the push payload objects to see if they are not equal.
     *
     * @param rhs The @c PushPayload object that will be compared.
     *
     * @return @c true if the push payload objects are not equal, @c false otherwise.
     *
     *
     * @since BlackBerry 10.0.0
     */
	bool operator!=(const PushPayload &rhs) const;

	/*!
	 * @brief Returns the binary data that the push-enabled application received.
	 *
	 * @return The binary data that the push-enabled application received.
	 *
	 *
	 * @since BlackBerry 10.0.0
	 */
	QByteArray data() const;

	 /*!
	   * @brief Returns the push notification headers.
	   *
	   * @return  The push notification headers.
	   *
	  *
	  * @since BlackBerry 10.0.0
	   */
	QVariantMap headers() const;

	/*!
	  * @brief Returns the length of the push notification data.
	  *
	  * @return The length of the push notification data.
	  *
	 *
	 * @since BlackBerry 10.0.0
	  */
	 int dataLength() const;

	 /*!
	  * @brief Returns the push identifier.
	  *
	  * @return The push identifier.
	  *
	  *
	  * @since BlackBerry 10.0.0
	  */
	 QString id() const;

	 /*!
	  * @brief Indicates whether or not data validation is successful.
	  *
	  * @return @c true if the push payload is valid, @c false otherwise
	  *
	  *
	  * @since BlackBerry 10.0.0
	  */
	 bool isValid() const;

	 /*!
	  * @brief Indicates whether an acknowledgement is required for this push message.
	  *
	  * @return @c true if application level acknowledgement is required, @c false otherwise.
	  *         Your application must invoke the @c acceptPush(const QString &payloadId) function if this function returns true.
	  *
	  *
	  * @since BlackBerry 10.0.0
	  */
	 bool isAckRequired() const;

private:
    QScopedPointer<PushPayloadPrivate> const d_ptr;
    Q_DECLARE_PRIVATE(PushPayload)
};

} // namespace network
} // namespace bb

#endif /* BB_NETWORK_PUSHSPAYLOAD_HPP */
