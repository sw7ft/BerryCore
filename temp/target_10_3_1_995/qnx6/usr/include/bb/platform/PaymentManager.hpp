/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_PAYMENTMANAGER_HPP
#define BB_PLATFORM_PAYMENTMANAGER_HPP

#include <bb/platform/Global>
#include <bb/platform/PaymentConnectionMode>

#include <QObject>
#include <QScopedPointer>
#include <QString>
#include <QUrl>
#include <QVariant>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace platform
{

class CancelSubscriptionReply;
class ExistingPurchasesReply;
class PriceReply;
class PurchaseReply;
class SubscriptionStatusReply;
class SubscriptionTermsReply;

class PaymentManagerPrivate;

/*!
 * @headerfile PaymentManager.hpp <bb/platform/PaymentManager>
 *
 * @brief Allows applications to manage digital good purchases and subscriptions.
 *
 * @details @c PaymentManager allows BlackBerry device users to initiate the purchase of digital goods
 * from within an application. For example, this API can be used to allow users to purchase additional
 * levels in a gaming application, music from a radio application, or any other digital good registered
 * on the Vendor Portal for BlackBerry World. The digital good being purchased must be associated
 * with the calling application in the Vendor Portal for BlackBerry World.
 *
 * The application interacts with the @c PaymentManager by creating a @c PaymentManager instance and calling the appropriate
 * request method, which returns an appropriate @c PaymentReply subclass on success, or 0 on failure. When the request has been processed,
 * the @c PaymentReply::finished() signal will be emitted on the returned reply instance and the appropriate @c *Finished() signal will
 * be emitted on the @c PaymentManager instance.  Results of the request, including success/failure, can be queried from the reply instance.
 * See @c PaymentReply and subclasses for more on this.
 *
 * To give context to the end user during an in-application purchase, a banner is displayed along the top of the purchase
 * and BlackBerry ID login screens, showing the name and icon of the application the purchase is being made from
 * (that is, the purchasing application). The application name and icon can be customized by calling
 * @c setApplicationName(const QString&) and @c setApplicationIconUrl(const QUrl&).
 * If the name and icon are not provided, then they are retrieved from the purchasing application's descriptor.
 * However, this may not work for applications that register with the home screen dynamically;
 * in this case, the purchasing application should explicitly provide a name and icon.
 *
 * The amount of time that elapses before a reply finishes depends on how quickly the user completes the purchase process,
 * which may include steps such as signing in to their BlackBerry ID account, setting up their preferred billing method, etc.
 *
 * Purchases are initiated with the @c requestPurchase() method.
 *
 * A list of already-purchased digital goods can be retrieved with the @c requestExistingPurchases() method.
 *
 * The price of a digital good or subscription can be obtained with the @c requestPrice() method. If the digital good is a subscription,
 * then the additional details pertaining to the subscription can be obtained using @c PaymentManager::requestSubscriptionTerms().
 *
 * The status and terms of subscriptions can be queried with the @c requestSubscriptionStatus and @c requestSubscriptionTerms() methods respectively.
 * Note that subscriptions remain active until the subscription period ends, even if they have been canceled.
 *
 * Subscription can be canceled with the @c requestCancelSubscription() method.
 *
 * @note After the request has finished, it is the responsibility of the user to delete the reply
 * object at an appropriate time. Do not directly delete it inside the slot connected to any of the finished signals. You can
 * use the @c QObject::deleteLater() function.
 *
 * @note The returned reply is a child of the @c PaymentManager to avoid memory leaks if the caller
 * fails to delete it manually.  The reply can be reparented if necessary (e.g., if it needs to
 * live longer than the @c PaymentManager).
 *
 * @xmlonly
 * <apigrouping group="Platform/Payment service"/>
 * <library name="bbplatform"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PLATFORM_EXPORT PaymentManager : public QObject
{
    Q_OBJECT

	/*!
	 * @brief Represents window group id
	 *
	 * @details The window group id for the calling app's main window
	 *
	 * @since BlackBerry 10.2.0
	 */
    Q_PROPERTY(QString windowGroupId READ windowGroupId WRITE setWindowGroupId FINAL)

    //!@cond PRIVATE
	/*!
	 * @brief Represents application name
	 *
	 * @details Application name
	 *
	 * @since BlackBerry 10.2.0
	 */
    Q_PROPERTY(QString applicationName READ applicationName WRITE setApplicationName FINAL)
    //!@endcond

	/*!
	 * @brief Represents application icon url
	 *
	 * @details Application icon url
	 *
	 * @since BlackBerry 10.2.0
	 */
    Q_PROPERTY(QUrl applicationIconUrl READ applicationIconUrl WRITE setApplicationIconUrl FINAL)

public:

    /*!
     * @brief Constructs a new @c PaymentManager instance.
     *
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit PaymentManager(QObject *parent = 0);

    /*!
     * @brief Destroys the instance.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~PaymentManager();

    /*!
     * @brief Used as a parameter to @c requestSubscriptionStatus when checking the status of an
     * app level subscription.
     *
     * @since BlackBerry 10.0.0
     */
    static const QString APP_SUBSCRIPTION;

    /*!
     * @brief Sets the window group id.
     *
     * @details Use this method to set the window group id. The window group
     * id is required by the @c PaymentManager so that it can display dialog
     * windows properly. Depending on the type of application, the window group id
     * can be set and/or retrieved in different ways. For example, a Cascades
     * application will set the window group id upon application start up. This value
     * can then be retrieved using @c bb::cascades::Application::mainWindow()->groupId(),
     * and passed to the @c PaymentManager using this method.
     *
     * @param windowGroupId The window group id to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setWindowGroupId(const QString &windowGroupId);

    /*!
     * @brief Gets the window group id.
     *
     * @details Gets the window group id, as set by calling @c setWindowGroupId().
     *
     * @return The window group id.
     *
     * @since BlackBerry 10.0.0
     */
    QString windowGroupId() const;

    //!@cond PRIVATE
    /*!
     * @brief Sets the application name.
     *
     * @details The application name is displayed on a banner shown to the user
     * during the purchase process. If the name is not provided, then it is retrieved from the purchasing application's descriptor.
     * However, this may not work for applications that register with the home screen dynamically;
     * in these cases, it is highly recommended that the purchasing application explicitly provide a name.
     *
     * @param applicationName The application name to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setApplicationName(const QString &applicationName);
    //!@endcond

    //!@cond PRIVATE
    /*!
     * @brief Gets the application name.
     *
     * @details Gets the application name, as set by calling @c setApplicationName().
     *
     * @return The application name.
     *
     * @since BlackBerry 10.0.0
     */
    QString applicationName() const;
    //!@endcond

    /*!
     * @brief Sets the application icon URL.
     *
     * @details This icon is displayed on a banner shown to the user during the purchase process.
     * The icon must be available through an external website, with a URL of the form @c "http://...".
     * If the icon is not provided, then it is retrieved from the purchasing application's descriptor.
     * However, this may not work for applications that register with the home screen dynamically;
     * in these cases, it is highly recommended that the purchasing application explicitly provide an icon.
     *
     * @param applicationIconUrl The application icon to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setApplicationIconUrl(const QUrl &applicationIconUrl);

    /*!
     * @brief Gets the application icon URL.
     *
     * @details Gets the application icon URL, as set by calling @c setApplicationIconUrl().
     *
     * @return The application icon URL.
     *
     * @since BlackBerry 10.0.0
     */
    QUrl applicationIconUrl() const;

    /*!
     * @brief Requests the purchase of a digital good or subscription.
     *
     * @details Only one of the ID or SKU of the digital good or subscription is required in order to request a
     * purchase. If the ID and SKU are both provided, then the ID is used.
     * To use the SKU, you must pass an empty string for the @c digitalGoodId.
     *
     * A digital good name should be provided in the case where a single ID/SKU represents multiple
     * digital goods on the Payment Service server, and a more specific digital good name should be
     * displayed on the purchase screen.
     * For example, if a game sells additional levels at a single price point,
     * then a generic "My game level" digital good can be used for all such levels. However, at purchase
     * time, the game application should override "My game level" with the name of the level being
     * purchased. This way, the end user is aware of exactly what they are purchasing on the purchase
     * confirmation screen.
     *
     * Purchase metadata offers the application developer a way to store information about each purchase on
     * the Payment server, and to retrieve that data via  @c requestExistingPurchases().
     * For example, assume a book vendor offers many titles at a single price point, and represents
     * them on the vendor portal as a single digital good. In this case, the ISBN of the book can
     * be provided as purchase metadata, which uniquely identifies the digital good that was purchased.
     * The entire list of purchased books can then be retrieved at any time by obtaining previous purchases
     * via the @c requestExistingPurchases() method, filtering on the book's digital good ID, and finally
     * enumerating the ISBNs in the purchase metadata.
     *
     * Extra parameters, in the form of key/value pairs in a @c QVariantMap, can be associated with the purchase request.
     * Any type with a valid @c QVariant::toString() can be used as a value in the map. Output parameters may be present in the
     * @c PurchaseReceipt and can be retrieved via @c PurchaseReceipt::extraParameters(). Input and output parameters may not be
     * directly related (i.e., output parameters may be present in the @c PurchaseReceipt where none were input, or vice versa).
     * Extra parameters are only relevant to the initial purchase (and would not be present, for example, in @c PurchaseReceipt objects
     * returned by @c requestExistingPurchases()).
     *
     * If the request is successfully made, a @c PurchaseReply is returned.  The returned object can
     * be used to obtain information about the request, including when the request has finished.
     * See @c PurchaseReply for more on this.
     *
     * Determining when the request has finished can be done through the @c PurchaseReply::finished() signal or the
     * @c PaymentManager::purchaseFinished() signal.
     *
     * @note After the request has finished, it is the responsibility of the user to delete the @c PurchaseReply
     * object at an appropriate time. Do not directly delete it inside the slot connected to one of the finished signals.
     * You can use the @c QObject::deleteLater() function.
     *
     * @note The returned @c PurchaseReply is a child of the @c PaymentManager to avoid memory leaks if the caller
     * fails to delete it manually.  The @c PurchaseReply can be reparented if necessary (e.g. if it needs to
     * live longer than the @c PaymentManager).
     *
     * @param digitalGoodId The digital good ID.  If empty, the ID is ignored and the SKU is used instead.
     * @param digitalGoodSku The digital good SKU.
     * @param digitalGoodName The digital good name.  If empty, the name will be pulled from the Payment server.
     * @param purchaseMetadata Optional information to associate with a successful purchase.
     * @param extraParameters Set of extra parameters to associate with a purchase request.
     *
     * @return A new @c PurchaseReply if the request was successfully made, or 0 if the request
     * could not be sent due to an internal error.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE bb::platform::PurchaseReply *requestPurchase(const QString &digitalGoodId, const QString &digitalGoodSku = QString(), const QString &digitalGoodName = QString(), const QString &purchaseMetadata = QString(), const QVariantMap &extraParameters = QVariantMap());

    /*!
     * @brief Requests the list of previous purchases.
     *
     * @details If the request is successfully made, an @c ExistingPurchasesReply is returned.  The returned object can
     * be used to obtain information about the request, including when the request has finished.
     * @see @c ExistingPurchasesReply for more on this.
     *
     * Determining when the request has finished can be done through the @c ExistingPurchasesReply::finished() signal or the
     * @c PaymentManager::existingPurchasesFinished() signal.
     *
     * @note After the request has finished, it is the responsibility of the user to delete the @c ExistingPurchasesReply
     * object at an appropriate time. Do not directly delete it inside the slot connected to one of the finished signals. You can
     * use the @c QObject::deleteLater() function.
     *
     * @note The returned @c ExistingPurchasesReply is a child of the @c PaymentManager to avoid memory leaks if the caller
     * fails to delete it manually.  The @c ExistingPurchasesReply can be reparented if necessary (e.g. if it needs to
     * live longer than the @c PaymentManager).
     *
     * @param forceServerRefresh If @c true, the list of purchases is retrieved from the Payment server;
     * otherwise, the current cached list of purchases is returned.
     *
     * @return A new @c ExistingPurchasesReply if the request was successfully made, or 0 if the request
     * could not be sent due to an internal error.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE bb::platform::ExistingPurchasesReply *requestExistingPurchases(bool forceServerRefresh = true);

    /*!
     * @brief Requests the price of a digital good or subscription
     *
     * @details Only one of the ID or SKU of the digital good or subscription is required in order to retrieve
     * the price. If the ID and SKU are both provided, then the ID is used.
     * To use the SKU, you must pass an empty string for the @c digitalGoodId.
     *
     * If the request is successfully made, a @c PriceReply is returned.  The returned object can
     * be used to obtain information about the request, including when the request has finished.
     * @see @c PriceReply for more on this.
     *
     * Determining when the request has finished can be done through the @c PriceReply::finished() signal or the
     * @c PaymentManager::priceFinished() signal.
     *
     * @note After the request has finished, it is the responsibility of the user to delete the @c PriceReply
     * object at an appropriate time. Do not directly delete it inside the slot connected to one of the finished signals. You can
     * use the @c QObject::deleteLater() function.
     *
     * @note The returned @c PriceReply is a child of the @c PaymentManager to avoid memory leaks if the caller
     * fails to delete it manually.  The @c PriceReply can be reparented if necessary (e.g. if it needs to
     * live longer than the @c PaymentManager).
     *
     * @param digitalGoodId The digital good ID.  If empty, the ID is ignored and the SKU is used instead.
     * @param digitalGoodSku The digital good SKU.
     *
     * @return A new @c PriceReply if the request was successfully made, or 0 if the request could not be
     * sent due to an internal error.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE bb::platform::PriceReply *requestPrice(const QString &digitalGoodId, const QString &digitalGoodSku = QString());

    /*!
     * @brief Requests the terms of a subscription.
     *
     * @details The subscription terms include the initial subscription period, renewal price,
     * and renewal period.
     *
     * Only one of the ID or SKU of the digital good or subscription is required in order to retrieve
     * the subscription terms. If the ID and SKU are both provided, then the ID is used.
     * To use the SKU, you must pass an empty string for the @c digitalGoodId.
     *
     * If the request is successfully made, a @c SubscriptionTermsReply is returned.  The returned object can
     * be used to obtain information about the request, including when the request has finished.
     * @see @c SubscriptionTermsReply for more on this.
     *
     * Determining when the request has finished can be done through the @c SubscriptionTermsReply::finished signal() or the
     * @c PaymentManager::subscriptionTermsFinished() signal.
     *
     * @note After the request has finished, it is the responsibility of the user to delete the @c SubscriptionTermsReply
     * object at an appropriate time. Do not directly delete it inside the slot connected to one of the finished signals. You can
     * use the @c QObject::deleteLater() function.
     *
     * @note The returned @c SubscriptionTermsReply is a child of the @c PaymentManager to avoid memory leaks if the caller
     * fails to delete it manually.  The @c SubscriptionTermsReply can be reparented if necessary (e.g. if it needs to
     * live longer than the @c PaymentManager).
     *
     * @param digitalGoodId The digital good ID.  If empty, the ID is ignored and the SKU is used instead.
     * @param digitalGoodSku The digital good SKU.
     *
     * @return A new @c SubscriptionTermsReply if the request was successfully made, or 0 if the request
     * could not be sent due to an internal error.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE bb::platform::SubscriptionTermsReply *requestSubscriptionTerms(const QString &digitalGoodId, const QString &digitalGoodSku = QString());

    /*!
     * @brief Requests whether a subscription is active.
     *
     * @details If the request is successfully made, a @c SubscriptionStatusReply is returned.  The returned object can
     * be used to obtain information about the request, including when the request has finished.
     * @see @c SubscriptionStatusReply for more on this.
     *
     * Determining when the request has finished can be done through the @c SubscriptionStatusReply::finished signal or the
     * @c PaymentManager::subscriptionStatusFinished signal.
     *
     * @note After the request has finished, it is the responsibility of the user to delete the @c SubscriptionStatusReply
     * object at an appropriate time. Do not directly delete it inside the slot connected to one of the finished signals. You can
     * use the @c QObject::deleteLater() function.
     *
     * @note The returned @c SubscriptionStatusReply is a child of the @c PaymentManager to avoid memory leaks if the caller
     * fails to delete it manually.  The @c SubscriptionStatusReply can be reparented if necessary (e.g. if it needs to
     * live longer than the @c PaymentManager).
     *
     * @param digitalGoodId The digital good ID.  If empty, the ID is ignored and the SKU is used instead. To check the status
     * of a subscription app (not a digital good), use @c PaymentManager::APP_SUBSCRIPTION as the digitalGoodId parameter.
     * @param digitalGoodSku The digital good SKU.
     *
     * @return A new @c SubscriptionStatusReply if the request was successfully made, or 0 if the request
     * could not be sent due to an internal error.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE bb::platform::SubscriptionStatusReply* requestSubscriptionStatus(const QString &digitalGoodId, const QString &digitalGoodSku = QString());

    /*!
     * @brief Requests cancellation of a subscription
     *
     * @details To cancel a subscription to a digital good, obtain the purchase id from when the subscription was purchased.
     * This can be obtained from the original purchase or from the list of previous successful purchases (as
     * retrieved using @c requestExistingPurchases()).
     *
     * If the request is successfully made, a @c CancelSubscriptionReply is returned.  The returned object can
     * be used to obtain information about the request, including when the request has finished.
     * @see @c CancelSubscriptionReply for more on this.
     *
     * Determining when the request has finished can be done through the @c CancelSubscriptionReply::finished() signal or the
     * @c PaymentManager::cancelSubscriptionFinished() signal.
     *
     * @note Canceled subscriptions remain active until the subscription period ends.
     *
     * @note After the request has finished, it is the responsibility of the user to delete the @c CancelSubscriptionReply
     * object at an appropriate time. Do not directly delete it inside the slot connected to one of the finished signals. You can
     * use the @c QObject::deleteLater() function.
     *
     * @note The returned @c CancelSubscriptionReply is a child of the @c PaymentManager to avoid memory leaks if the caller
     * fails to delete it manually.  The @c CancelSubscriptionReply can be reparented if necessary (e.g. if it needs to
     * live longer than the @c PaymentManager).
     *
     * @param purchaseId The purchase id from when the subscription was purchased.
     *
     * @return A new @c CancelSubscriptionReply if the request was successfully made, or 0 if the request
     * could not be sent due to an internal error.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE bb::platform::CancelSubscriptionReply* requestCancelSubscription(const QString &purchaseId);

    /*!
     * @brief Sets the global Payment API connection mode.
     *
     * @details The Payment API can be put into a @c PaymentConnectionMode::Test connection mode for easier local testing.
     * @see @c PaymentConnectionMode::Test for more on this.
     *
     * The default connection mode is @c PaymentConnectionMode::Production.
     *
     * @note The connection mode affects the Payment API as a whole, and is not linked to a
     * @c PaymentManager instance.  Changing connections modes while any Payment operations are
     * outstanding is unsupported and will result in undefined behavior.  Ideally, this function
     * will only be called at startup, before any @c PaymentManager instances are created.
     *
     * @note @c PaymentConnectionMode::Test should @b not be used in production code.
     *
     * @param connectionMode The new connection mode for the Payment API.
     *
     * @since BlackBerry 10.0.0
     */
    static void setConnectionMode(bb::platform::PaymentConnectionMode::Type connectionMode);

Q_SIGNALS:
    /*!
     * @brief Emitted when a request initiated by @c requestPurchase() has finished.
     *
     * @note After the request has finished, it is the responsibility of the user to delete the @c PurchaseReply
     * object at an appropriate time.
     *
     * @param reply The @c PurchaseReply that was returned by @c requestPurchase().
     *
     * @since BlackBerry 10.0.0
     */
    void purchaseFinished( bb::platform::PurchaseReply *reply );

    /*!
     * @brief Emitted when a request initiated by @c requestExistingPurchases() has finished.
     *
     * @note After the request has finished, it is the responsibility of the user to delete the @c ExistingPurchasesReply
     * object at an appropriate time.
     *
     * @param reply The @c ExistingPurchasesReply that was returned by @c requestExistingPurchases().
     *
     * @since BlackBerry 10.0.0
     */
    void existingPurchasesFinished(bb::platform::ExistingPurchasesReply *reply);

    /*!
     * @brief Emitted when a request initiated by @c requestPrice() has finished.
     *
     * @note After the request has finished, it is the responsibility of the user to delete the @c PriceReply
     * object at an appropriate time.
     *
     * @param reply The @c PriceReply that was returned by @c requestPrice().
     *
     * @since BlackBerry 10.0.0
     */
    void priceFinished( bb::platform::PriceReply *reply );

    /*!
     * @brief Emitted when a request initiated by @c requestSubscriptionTerms() has finished.
     *
     * @note After the request has finished, it is the responsibility of the user to delete the @c SubscriptionTermsReply
     * object at an appropriate time.
     *
     * @param reply The @c SubscriptionTermsReply that was returned by @c requestSubscriptionTerms().
     *
     * @since BlackBerry 10.0.0
     */
    void subscriptionTermsFinished(bb::platform::SubscriptionTermsReply *reply);

    /*!
     * @brief Emitted when a request initiated by @c requestSubscriptionStatus() has finished.
     *
     * @note After the request has finished, it is the responsibility of the user to delete the @c SubscriptionStatusReply
     * object at an appropriate time.
     *
     * @param reply The @c SubscriptionStatusReply that was returned by @c requestSubscriptionStatus().
     *
     * @since BlackBerry 10.0.0
     */
    void subscriptionStatusFinished(bb::platform::SubscriptionStatusReply *reply);

    /*!
     * @brief Emitted when a request initiated by @c requestCancelSubscription() has finished.
     *
     * @note After the request has finished, it is the responsibility of the user to delete the @c CancelSubscriptionReply
     * object at an appropriate time.
     *
     * @param reply The @c CancelSubscriptionReply that was returned by @c requestCancelSubscription().
     *
     * @since BlackBerry 10.0.0
     */
    void cancelSubscriptionFinished(bb::platform::CancelSubscriptionReply *reply);

protected:
    //!@cond PRIVATE
    Q_INVOKABLE static void setConnectionMode(int connectionMode);
    //!@endcond

private:
//!@cond PRIVATE
    Q_DISABLE_COPY(PaymentManager);
    Q_DECLARE_PRIVATE(PaymentManager);
    QScopedPointer<PaymentManagerPrivate> d_ptr;
//!@endcond
};

} // namespace platform
} // namespace bb

QML_DECLARE_TYPE(bb::platform::PaymentManager)
#endif // BB_PLATFORM_PAYMENTMANAGER_HPP
