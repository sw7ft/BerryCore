/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_NETWORK_PUSHSERVICE_HPP
#define BB_NETWORK_PUSHSERVICE_HPP

#include <bb/network/Global>
#include <bb/network/PushCommand>

#include <QObject>
#include <QScopedPointer>
#include <QString>
#include <QtDeclarative/QtDeclarative>
#include <QUrl>

namespace bb
{
namespace network
{

class PushStatus;
class PushServicePrivate;

/*!
 * @headerfile PushService.hpp <bb/network/PushService>
 *
 * @brief Manages all interactions with the Push Proxy Gateway (PPG).
 *
 * A @c PushService allows a push-enabled application to send requests to the PPG.
 *
 * The @c PushService supports both sending requests and receiving responses from the PPG.
 * Applications that receive response messages while they are running are notified via the 
 * @c [command]Completed() signal.
 *
 * The following commands are supported by the @c PushService:
 * - @c createSession()
 * - @c createChannel()
 * - @c destroyChannel
 * - @c registerToLaunch()
 * - @c unregisterFromLaunch()
 *
 * The application can send an application level acknowledgement that indicates whether the application accepted
 * or rejected the pushed content ( @c acceptPush() or @c rejectPush() ).
 *
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Push"/>
 * <library name="bbnetwork"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */

class BB_NETWORK_EXPORT PushService: public QObject
{
	Q_OBJECT

	/*!
	 * @brief The provider application ID.
	 *
	 *
	 * @since BlackBerry 10.0.0
	 */
	Q_PROPERTY(QString providerApplicationId READ providerApplicationId WRITE setProviderApplicationId FINAL)

	/*!
	 * @brief The target key.
	 *
	 *
	 * @since BlackBerry 10.0.0
	 */
	Q_PROPERTY(QString targetKey READ targetKey WRITE setTargetKey FINAL)

	/*!
	 * @brief The last command that failed.
     * 
     * The returned value can be either a @c CreateChannel or @c DestroyChannel.
	 *
	 *
	 * @since BlackBerry 10.0.0
	 */
	Q_PROPERTY(bb::network::PushCommand::Type command READ command FINAL)

	/*!
	 * @brief Specifies whether the @c PushService has a connection to the Push Agent.
	 *
	 *
	 * @since BlackBerry 10.0.0
	 */
	Q_PROPERTY(bool hasConnection READ hasConnection CONSTANT FINAL)

public:

	/*!
	 * @brief Creates a new @c PushService object.
	 *
	 * @param parent The @c QObject that will take ownership of this object, or NULL.
	 *
	 *
	 * @since BlackBerry 10.0.0
	 */
	explicit PushService(QObject *parent = 0);

	/*!
	 * @brief Creates a new @c PushService object.
	 *
	 * @param providerApplicationId The unique identifier of the push-enabled application.
	 * @param targetKey The invocation target key.
	 * @param parent The @c QObject that will take ownership of this object, or NULL.
	 *
	 *
	 * @since BlackBerry 10.0.0
	 */
	PushService(const QString &providerApplicationId, const QString &targetKey, QObject *parent = 0);

	/*!
	 * @brief Destroys this @c PushService object.
	 *
	 *
	 * @since BlackBerry 10.0.0
	 */
	virtual ~PushService();

	/*!
	 * @brief Gets the provider application ID.
	 *
	 * @return The provider application ID.
	 *
	 *
	 * @since BlackBerry 10.0.0
	 */
	QString providerApplicationId() const;

	/*!
	 * @brief Gets the target key associated with this @c PushService.
	 *
	 * @return The target key associated with this @c PushService.
	 *
	 *
	 * @since BlackBerry 10.0.0
	 */
	QString targetKey() const;

   /*!
	 * @brief Retrieves the last failed command.
     * 
     * The returned value can be either a @c CreateChannel or @c DestroyChannel.
	 *
	 * @return The last failed command as specified in @c PushCommand.
	 *
    *
    * @since BlackBerry 10.0.0
	 */
	bb::network::PushCommand::Type command() const;

	 /*!
	  * @brief Determines whether the @c PushService has a connection to the Push Agent.
	  *
	  * @return @c true if the @c PushService has a connection to the Push Agent, @c false otherwise.
	  *
	  *
	  * @since BlackBerry 10.0.0
	  */
	Q_INVOKABLE bool hasConnection() const;


	 /*!
	  * @brief Reconnects the @c PushService to the Push Agent.
	  *
	  * @return @c true if the @c PushService was able to reconnect to the Push Agent, @c false otherwise.
	  *
	  * @since BlackBerry 10.2.0
	  */
	Q_INVOKABLE bool reconnect();

public Q_SLOTS:

	/*!
     * @brief Changes the provider application ID represented by this object.
     *
     * @param providerApplicationId The provider application ID
     *
     * @ingroup Slots
	 *
	 * @since BlackBerry 10.0.0
     */
	void setProviderApplicationId(const QString &providerApplicationId);

	/*!
	 * @brief Changes the target key represented by this object.
	 *
	 * @param targetKey The target key
	 *
	 * @ingroup Slots
	 *
	 * @since BlackBerry 10.0.0
	 */
   void setTargetKey(const QString &targetKey);

	/*!
	 * @brief Creates a session between the application and the Push Service Notification agent (PNS agent).
     *
	 * Creating a session sets up inter-process communication between the application and the PNS agent.
	 * This must be called every time the application is launched.
	 *
	 * @ingroup Slots
	 *
	 * @since BlackBerry 10.0.0
	 */
	void createSession();

	/*!
	 * @brief Creates a channel for receiving push messages from the Push Initiator.
     *
	 * Once the channel is successfully established, the application does not have to call this
	 * again. The @c PushService maintains the channel. However, there are some cases where you might have to
     * create the channel again (for example, if the SIM card is removed from the device).
	 *
	 * @param pushProxyGatewayUrl The URL of the Push Proxy Gateway (PPG).
	 *
	 * @ingroup Slots
	 *
	 * @since BlackBerry 10.0.0
	 */
	void createChannel(const QUrl &pushProxyGatewayUrl);

	/*!
	 * @brief Destroys the channel when the application no longer needs it.
	 *
	 * @ingroup Slots
	 *
	 * @since BlackBerry 10.0.0
	 */
	void destroyChannel();

	/*!
	 * @brief Registers the application to be launched in the background upon receiving a push message.
	 *
	 * @ingroup Slots
	 *
	 * @since BlackBerry 10.0.0
	 */
	void registerToLaunch();

	/*!
	 * @brief Cancels a previous @c registerToLaunch() request.
	 *
	 * @ingroup Slots
	 *
	 * @since BlackBerry 10.0.0
	 */
	void unregisterFromLaunch();

	/*!
	 * @brief Accepts a push message.
     * 
     * If the Push Initiator requires an application level acknowledgement for a particular push
	 * message, this function sends an affirmative message back to the PPG to indicate that the application
	 * accepted the pushed content.
	 *
	 * @param payloadId The unique identifier of the push notification which is stored in the @c PushPayload object.
	 *
	 * @ingroup Slots
	 *
	 * @since BlackBerry 10.0.0
	 */
	void acceptPush(const QString &payloadId);

	/*!
	 * @brief Rejects a push message.
     *
     * If the Push Initiator requires an application level acknowledgement for a particular push
	 * message, this function sends a negative message back to the PPG to indicate that the application rejected
	 * the pushed content. This generally means that the Push Initiator should try to resend the push message.
	 * If the Push Initiator did not request an acknowledgement, this function does nothing.
	 *
	 * @param payloadId The unique identifier of the push notification which is stored in the @c PushPayload object.
	 *
	 * @ingroup Slots
	 *
	 * @since BlackBerry 10.0.0
	 */
	void rejectPush(const QString &payloadId);

Q_SIGNALS:

	/*!
	 * @brief Emitted when a response to the @c createSession() request is received.
	 *
	 * @param status The @c PushStatus response for the @c createSession() request call
	 *
	 * @ingroup Signals
	 *
	 * @since BlackBerry 10.0.0
	 */
	void createSessionCompleted(const bb::network::PushStatus &status);

	/*!
	 * @brief Emitted when a response to the @c createChannel() request is received.
	 *
	 *  @param status   A @c PushStatus response for the @c createChannel() request call
	 *  @param token    The token received from the PPG
	 *                  after successfully creating the push channel.
	 *                  This token should be communicated to the Push Initiator.
	 *
	 * @ingroup Signals
	 *
	 * @since BlackBerry 10.0.0
	 */
	void createChannelCompleted(const bb::network::PushStatus &status, const QString &token);

	/*!
	 * @brief Emitted when a response for the @c destroyChannel() request is received.
	 *
	 * @param status A @c PushStatus response for the @c destroyChannel() request call.
	 *
	 * @ingroup Signals
	 *
	 * @since BlackBerry 10.0.0
	 */
	void destroyChannelCompleted(const bb::network::PushStatus &status);

	/*!
	 * @brief Emitted when a response for the @c registerToLaunch() request is received.
	 *
	 * @param status A @c PushStatus response for the @c registerToLaunch() request call.
	 *
	 * @ingroup Signals
	 *
	 * @since BlackBerry 10.0.0
	 */
	void registerToLaunchCompleted(const bb::network::PushStatus &status);

	/*!
	 * @brief Emitted when a response for the @c unregisterFromLaunch() request is received.
	 *
	 * @param status A @c PushStatus response for the @c unregisterFromLaunch() request call.
	 *
	 * @ingroup Signals
	 *
	 * @since BlackBerry 10.0.0
	 */
	void unregisterFromLaunchCompleted(const bb::network::PushStatus &status);

	/*!
	 * @brief Emitted when the SIM card is changed.
     *
	 * When this happens, the PPG stops delivering push messages. To continue receiving content,
	 * you must call @c createChannel() again.
	 *
	 * @ingroup Signals
	 *
	 * @since BlackBerry 10.0.0
	 */
	void simChanged();

	/*!
	 * @brief Emitted when a previous @c createChannel() or @c destroyChannel request
	 * failed with a @c TransportFailure (10103) or SubscriptionContentNotAvailable (10110) status code.
	 *
     * Here's an example of how to initiate the requests again after they fail:
     *
     * @code
	 * if (command == bb::network::PushCommand::CreateChannel) {
	 *     pushService->createChannel(pushProxyGatewayUrl);
	 * }
	 * else if (command == bb::network::PushCommand::DestroyChannel) {
	 *     pushService->destroyChannel();
	 * }
	 * @endcode
     *
	 * @param command The last command that failed (either a @c CreateChannel or @c DestroyChannel).
	 *
	 * @ingroup Signals
	 *
	 * @since BlackBerry 10.0.0
	 */
	void pushTransportReady(bb::network::PushCommand::Type command);

	/*!
	 * @brief Emitted when the connection to the Push Agent has been deleted.
     *
     * When this happens, the application needs to re-establish the connection with
     * the Push Agent by calling @c reconnect() periodically until @c reconnect() returns true.
     * After @c reconnect() returns true, the application must then call @c createSession().
	 *
	 * @ingroup Signals
	 * @since BlackBerry 10.2.0
	 */
	void connectionClosed();

protected:
//!@cond PRIVATE
Q_SIGNALS:
	void createSessionCompleted(int status);
	void createChannelCompleted(int status, const QString &token);
	void destroyChannelCompleted(int status);
	void registerToLaunchCompleted(int status);
	void unregisterFromLaunchCompleted(int status);
//!@endcond PRIVATE


private:
	Q_DISABLE_COPY(PushService)

	Q_DECLARE_PRIVATE(PushService);
	PushServicePrivate * d_ptr;
};

} // namespace network
} // namespace bb

QML_DECLARE_TYPE(bb::network::PushService)

#endif // BB_NETWORK_PUSHSERVICE_HPP
