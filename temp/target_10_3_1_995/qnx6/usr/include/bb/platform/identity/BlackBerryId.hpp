/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_IDENTITY_BLACKBERRYID_HPP
#define BB_PLATFORM_IDENTITY_BLACKBERRYID_HPP

#include <bb/platform/Global>

#include <QObject>

namespace bb {
namespace platform {
namespace identity {

class BlackBerryIdPrivate;

/*!
 * @brief Use BlackBerry ID as an identity provider for your application.
 *
 * Using the BlackBerry ID service as an identity provider, you can enhance
 * your app in several ways:
 * - Provide user authentication within your app, without prompting for
 * user credentials.
 * - Provide user authorization to access other BlackBerry apps and off-device
 * services without prompting for user credentials.
 * - Provide access to users' personal information that is stored in the
 * BlackBerry ID account system. User permission to access this information
 * is required.
 *
 * @section   user_auth_sec   User authentication without prompting for credentials
 *
 * Benefits of using BlackBerry ID user authentication:
 * - Eliminate the need to build your own username and password management.
 * - Automatically sign users in to your app after they sign in with their
 * BlackBerry ID account on their devices. This makes your app easier to use.
 * - Eliminate the need for users to create and remember a username and
 * password for your app.
 *
 * @section   off_device_service_sec   User authorization to access other BlackBerry apps and off-device services
 *
 * If your app interacts with an off-device service that requires user
 * authentication (for example, a website that requires the user to sign in
 * with a username and password), you can use BlackBerry ID APIs to perform
 * the off-device authentication/authorization using tokens, instead of
 * prompting the user for credentials. Your app and the off-device service
 * interact seamlessly.
 *
 * @section pii_sec   Access personal information associated with BlackBerry ID accounts
 *
 * You can personalize the user experience of your app by incorporating your
 * users' personal information in your app. Users must allow your app to
 * access the information associated with their BlackBerry ID accounts before
 * you can access it. The application must have the
 * @c read_personally_identifiable_information permission included in their bar
 * descriptor.  The information that is available includes:
 * - first name
 * - last name
 * - screen name
 * - username (an email address)
 *
 * @section Code_sample_sec Sample code for using BlackBerry ID as the identity provider for your app
 *
 * The following sample shows how to retrieve a users first name:
 *
 * @code
 * Make sure to include the following header files in your application
 *
 * #include <bb/platform/identity/IdentityServiceProvide>
 * #include <bb/platform/identity/IdentityServiceResult>
 * #include <bb/platform/identity/IdentityServicePropertyResult>
 * #include <bb/platform/identity/BlackBerryId>
 * #include <bb/platform/identity/BlackBerryIdPropertyType>
 *
 * Step 1 - Create an IdentityServiceProvider instance.
 *
 * IdentityServiceProvider *provider = new IdentityServiceProvider( BlackBerryId::providerName() );
 * if( !provider->isValid() ) {
 * 		qWarning() << "Unable to communicate with BlackBerryId Provider: " << provider->error();
 * }
 *
 * Step 2 - Connect with with success and failure signals.
 *
 *	QObject::connect( provider, SIGNAL( propertiesRetrieved( int, QMap<QString, QString> ) ),
 *						this, SLOT( getPropertiesSucceeded( int, QMap<QString, QString> ) ) );
 *
 *	QObject::connect( provider, SIGNAL( propertyRetrievalFailed( int, bb::platform::identity::IdentityServicePropertyResult::Type, QString ) ),
 *						this, SLOT( getPropertiesFail( int, bb::platform::identity::IdentityServicePropertyResult::Type, QString ) ) );
 *
 * Step 3 - Call API's
 *
 * IdentityServiceResult::Type result = provider->requestProperties( BlackBerryIdPropertyType::Core,
 * 																		BlackBerryId::firstNamePropertyKey() );
 * if( result != IdentityServiceResult::Success ){
 *		qWarning << "Unable to retrieve first name: " << result;
 * }
 *
 * @endcode
 *
 * @headerfile BlackBerryId.hpp <bb/platform/identity/BlackBerryId>
 * @xmlonly
 * <library name="bbplatform" />
 * <apigrouping group="Platform/Identity" />
 * @endxmlonly
 */
class BB_PLATFORM_EXPORT BlackBerryId: public QObject {
    Q_OBJECT

    /**
     * @brief The identity provider name of BlackBerry ID to
     * use with the @sa IdentityServiceProvider class.
     */
    Q_PROPERTY( QString providerName READ providerName CONSTANT FINAL )

    /*!
     * @brief The key used to access a user's UserName.
     */
    Q_PROPERTY( QString userNamePropertyKey READ userNamePropertyKey CONSTANT FINAL )

    /*!
     * @brief The key used to access a user's ScreenName.
     */
    Q_PROPERTY( QString screenNamePropertyKey READ screenNamePropertyKey CONSTANT FINAL )

    /*!
     * @brief The key used to access a user's FirstName.
     */
    Q_PROPERTY( QString firstNamePropertyKey READ firstNamePropertyKey CONSTANT FINAL )

    /*!
     * @brief The key used to access a user's LastName.
     */
    Q_PROPERTY( QString lastNamePropertyKey READ lastNamePropertyKey CONSTANT FINAL )

    /*!
     * @brief The key used to access a user's Unique Id.
     */
    Q_PROPERTY( QString uniqueIdPropertyKey READ uniqueIdPropertyKey CONSTANT FINAL )

    /*!
     * @brief The key used to access a user's Validated email.
     */
    Q_PROPERTY( QString emailPropertyKey READ emailPropertyKey CONSTANT FINAL )

public:
    /*!
     * @brief Constructs an empty BlackBerryId instance.
     * @param parent The parent object.  Setting parent to 0
     * constructs an BlackBerryId instance with no parent.
     */
    explicit BlackBerryId( QObject *parent = 0 );

    /*!
     * @brief Destroys the IdentityBlackBerryId instance.
     */
    virtual ~BlackBerryId();

    /**
     * @brief The identity provider name of BlackBerry ID to
     * use with the @sa IdentityServiceProvider class.
     * @return The string name of the BlackBerry ID provider.
     */
    static QString providerName();

    /**
     * @brief BlackBerry ID core properties.
     * @details These are the core properties that are available to
     * applications using BlackBerry ID as an identity provider.
     * @sa requestProperties() with the BBID_PROPERTY_CORE type.
     */

    /*!
     * @brief The key used to access a user's UserName.
     * @return The key to use in requestProperties when requesting
     * the user's UserName.
     */
    static QString userNamePropertyKey();

    /*!
     * @brief The key used to access a user's ScreenName.
     * @return The key to use in requestProperties when requesting
     * the user's ScreenName.
     */
    static QString screenNamePropertyKey();

    /*!
     * @brief The key used to access a user's FirstName.
     * @return The key to use in requestProperties when requesting
     * the user's FirstName.
     */
    static QString firstNamePropertyKey();

    /*!
     * @brief The key used to access a user's LastName.
     * @return The key to use in requestProperties when requesting
     * the user's LastName.
     */
    static QString lastNamePropertyKey();

    /*!
     * @brief The key used to access a user's Unique Id.
     * @return The key to use in requestProperties when requesting
     * the user's Unique Id.
     */
    static QString uniqueIdPropertyKey();

    /*!
     * @brief The key used to access a user's Confirmed Email.
     * @return The key to use in requestProperties when requesting
     * the user's confirmed email address.
     */
    static QString emailPropertyKey();

private:
    //!@cond PRIVATE
    Q_DISABLE_COPY( BlackBerryId )
    ;
    QScopedPointer<BlackBerryIdPrivate> d_ptr;Q_DECLARE_PRIVATE( BlackBerryId )
    ;
    //!@endcond PRIVATE

};
} // namespace identity
} // namespace platform
} // namespace bb

// TODO:
// QML_DECLARE_TYPE( bb::platform::identity::BlackBerryId )

#endif /* BB_PLATFORM_IDENTITY_BLACKBERRYID_HPP */
