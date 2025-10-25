/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_USER_IDENTITY_IDENTITYSERVICEPROVIDER_HPP
#define BB_USER_IDENTITY_IDENTITYSERVICEPROVIDER_HPP

#include <bb/platform/identity/IdentityServiceResult>
#include <bb/platform/identity/IdentityServiceTokenResult>
#include <bb/platform/identity/IdentityServicePropertyResult>

#include <QObject>
#include <QList>

namespace bb {
namespace platform {
namespace identity {

class IdentityServiceProviderPrivate;
/*!
 * @headerfile IdentityServiceProvider.hpp <bb/platform/identity/IdentityServiceProvider>
 * @brief Use these APIs to provide seamless user authentication/authorization with
 * off-device services.
 *
 * @brief Use the Identity Service provider class to incorporate user authentication
 * and authorization, using one or more external identity providers, in your application.
 *
 * @details Identity Service provider class
 *
 * You can use the APIs in the Identity Service provider class to enable your users to
 * access off-device services and content that require user authentication or authorization.
 * Content and services include data storage and retrieval, and access to services with an
 * external identity provider.  You can also personalize the user experience by integrating
 * users' personal information in your application.
 *
 * An application needs separate instances of the IdentityServiceProvider class for each
 * identity provider that it uses. Using the same instance of IdentityServiceProvider
 * for different providers could lead to undefined behavior.
 *
 * Your users can sign in with their identity provider, using their BlackBerry device, and
 * access content or services that they have with that identity provider from within your
 * application and elsewhere on their device.
 *
 * Any authorization that your application requires can also be done using the login
 * credentials associated with an identity provider.  This approach frees your users from
 * having to remember another login profile, and saves you from having to build user
 * authentication into your application.
 *
 * For example, if you registered your application with BlackBerry ID as your identity
 * provider, your users could access BlackBerry ID controlled resources from within your
 * application, without having to log in again.  BlackBerry ID is one of the supported
 * identity providers, and the list of identity providers is growing.
 *
 * Identity providers can offer different features and levels of access.  It's important
 * to understand the features that are available from your identity provider because
 * those features impact how you design your application.  For example, one identity
 * provider might provide off-device data storage while another might provide on-device
 * data storage.  Similarly, the personal information that you can retrieve with the
 * @c requestProperties() function differ based on the information that each identity
 * provider stores in their account system.
 *
 * You will need to use this documentation in conjunction with the information from
 * your identity provider about how they have implemented the Identity Service provider
 * APIs on thier end.  If you are using BlackBerry ID as the Identity Service provider
 * for your application, you can find information specific to integrating with
 * BlackBerry ID in the IdentityBlackBerryId header files.
 *
 * @section DataStorage_section Data storage and retrieval APIs
 *
 * You can use the APIs in the Identity Service provider class to:
 * - store data initially(createData())
 * - retrieve data (requestData())
 * - update data (setData())
 * - remove data (deleteData())
 * - list stored data (listData())
 *
 * @section UserAuth_Section User authentication without prompting for credentials
 *
 * With the user authentication APIs in this class, you can avoid implementing username
 * and password management in your application.  After your user signs in with the
 * identity provider on their device, that user is automatically signed in to your
 * application as well.  This eliminates the need for users to create and remember a
 * username and password for your application, and it also reduces the number of times
 * that users need to log in, providing a more fluid user experience.
 *
 * @section OffDeviceAuth_Section User authorization for access to off-device services
 *
 * If your application interacts with one of your identity provider's applications or
 * off-device services, and that application or service requires user authentication,
 * you can use the Identity Service provider class to perform that authentication.  User
 * authentication/authorization is done using tokens, and does not require user input.
 * This allows your application and the off-device service to interact seemlessly.
 *
 * @section PII_Section Using personal information in your application
 *
 * Users must first allow your application to access their information.  If allowed
 * access, you can integrate the personal information associated with your users' accounts
 * in your application.  The personal information that is available to your application
 * depends on what information is available from your identity provider's account
 * system.
 *
 * For example, if your application uses BlackBerry ID as an identity provider, your
 * application can access the following pieces of a user's personal information:
 * - first name
 * - last name
 * - screen name
 * - username
 *
 * Check with other identity providers to identify the personal information they make
 * available.
 *
 * @section bbid_modes_sec Registering your application to use the IdentityServiceProvider
 * class.
 *
 * To register your application so that it can use the IdentityServiceProvider class,
 * either pass the name of the provider into the constructor, or call setProvider for
 * an instance of a class.  A separate instance of IdentityServiceProvider should be
 * created for each provider that an application relies on.
 *
 * @xmlonly
 * <library name="bbplatform" />
 * <apigrouping group="Platform/Identity" />
 * @endxmlonly
 */
class BB_PLATFORM_EXPORT IdentityServiceProvider: public QObject {
    Q_OBJECT

    /*!
     * @brief The maximum number of properties that can be included in a single
     * requestProperties() call.
     */
    Q_PROPERTY( int maxPropertyCount READ maxPropertyCount CONSTANT FINAL )
    /*!
     * @brief The maximum string length of a single property name that can be
     * passed in a single @c requestProperties() call, excluding the terminating
     * NULL.
     */
    Q_PROPERTY( int maxPropertyNameLength READ maxPropertyNameLength CONSTANT FINAL )
    /*!
     * @brief The maximum string length of a single data name that can be
     * passed in @c requestData(), @c setData(), @c createData()
     * and @c deleteData() calls, excluding the terminating NULL.
     */
    Q_PROPERTY( int maxDataNameLength READ maxDataNameLength CONSTANT FINAL )

public:
    /*!
     * @brief Constructs an empty IdentityServiceProvider instance.
     * @param parent The parent object.  Setting parent to 0
     * constructs an IdentityServiceProvider instance with no parent.
     */
    explicit IdentityServiceProvider( QObject *parent = 0 );

    /*!
     * @brief Constructs an IdentityServiceProvider instance and registers
     * the provider that was supplied.
     * @param providerName the name of the identityProvider
     * @param parent The parent object.  Setting parent to 0
     * constructs an IdentityServiceProvider instance with no parent.
     */
    explicit IdentityServiceProvider( const QString &providerName, QObject *parent = 0 );

    /*!
     * @brief Destroys the IdentityServiceProvider instance.
     */
    virtual ~IdentityServiceProvider();

    /*!
     * @brief Sets the identity provider for an IdentityServiceProvider
     * instance and registers the provider that was supplied.
     * @detail Changing a provider once one has been set will result in
     * undefined behavior and is discouraged unless registration fails.
     * Typically, the provider should not change during the life of this
     * object (i.e. it is usually set in the constructor in C++, or in the
     * initialization in QML).  In particular, changing the provider when
     * requests are in progress may result in undefined behavior.
     * @param providerName The name of the identity provider.
     * @return @c IdentityServiceResult. Success if successful. See
     * @c IdentityServiceResult for details regarding errors.
     */
#ifndef Q_MOC_RUN
    Q_INVOKABLE
    bb::platform::identity::IdentityServiceResult::Type setProvider( const QString &providerName );
#else
    Q_INVOKABLE int setProvider( const QString &providerName );
#endif
    /*!
     * @brief Issue a request token call.
     *
     * @details Upon completion of a successful requestToken call, the tokenRetrieved
     * signal is emitted and contains an IdentityServiceToken.
     *
     * @param tokenType The token type, which must be between 1 and 32 characters,
     * inclusive.
     * @param appliesTo The name of the application or service that the token
     * applies to. It must be between 1 and 96 characters, inclusive.
     *
     * @return A request Id, which will be 0 if the call fails immediately.  Call error()
     * to get more info on failures.
     * @b Immediate errors @b - See @c error() and @c IdentityServiceResult.
     *
     * @b Asynchronous Error @b Handling - See @c tokenRetrievalFailed and @c IdentityServiceTokenResult.
     */
    Q_INVOKABLE
    int requestToken( const QString &tokenType, const QString &appliesTo ) const;

    /*!
     * @brief Issue a clear token request.
     *
     * @details In cases where the token seems to be invalid
     * or too close to expiry to be deemed useful, an application can clear the
     * currently cached token in order to retrieve a newly generated token in the
     * next requestToken() call.
     * Upon completion of a successful clearToken call, the tokenCleared signal
     * is emitted.
     *
     * @param tokenType The token type which must be between 1 and 32 characters,
     * inclusive.
     * @param appliesTo The name of the application or service that the token
     * applies to. It must be between 1 and 96 characters, inclusive.
     * @return A request Id, which will be 0 if the call fails immediately.  Call error()
     * to get more info on failures.
     *
     * @b Immediate errors @b - See @c error() and @c IdentityServiceResult.
     *
     * @b Asynchronous Error @b Handling - See @c tokenClearFailed and @c IdentityServiceTokenResult.
     */
    Q_INVOKABLE
    int clearToken( const QString &tokenType, const QString &appliesTo );

    /*!
     * @brief Issue a request for user properties.
     *
     * @details Upon completion of a successful getProperties call, the propertiesRetrieved signal
     * is emitted and contains a QList of IdsProperties.
     *
     * @param type The type of properties contained in the @c propertyList
     * parameter. Each provider may have a unique set of types that it is able to
     * handle.  See the documentation for the provider for details on valid values.
     * @param propertyList A list of the requested properties, by property name.
     * @return A request Id, which will be 0 if the call fails immediately.  Call error()
     * to get more info on failures.
     *
     * @b Immediate errors @b - See @c error() and @c IdentityServiceResult.
     *
     * @b Asynchronous Error @b Handling - See @c propertyRetrievalFailed and @c IdentityServicePropertyResult.
     */
    Q_INVOKABLE
    int requestProperties( int type, const QStringList &propertyList ) const;

    /*!
     * @brief Issue a request for data.
     *
     *
     * @details Upon completion of a successful requestData call, the dataRetrieved signal
     * is emitted and contains the requested data.
     *
     * @param type The storage type of the data entry. Each identity provider may
     * have a unique set of types that it supports. See your identity provider's
     * documentation for details on valid types.
     * @param flags Flags related to the request.  Each provider may define specific
     * flags.
     * @param name The name of the data to store.
     * @return A request Id, which will be 0 if the call fails immediately.  Call error()
     * to get more info on failures.
     *
     * @b Immediate errors @b - See @c error() and @c IdentityServiceResult.
     *
     * @b Asynchronous Error @b Handling - See @c dataRetrievalFailed and @c IdentityServicePropertyResult.
     */
    Q_INVOKABLE
    int requestData( int type, int flags, const QString &name ) const;

    /*!
     * @brief Issue a request to set data.
     *
     * @details Upon completion of a successful setData call, the dataSet signal
     * is emitted.
     *
     * @param type The type of properties contained in the @c data parameter. Each
     * identity provider may have a unique set of types that it is able to handle.
     * See the identity provider's documentation for details on valid types.
     * @param flags Flags related to the request.  Each provider may define specific
     * flags.
     * @param name The name of the data to store.
     * @param value The content of the data to store.
     * @return A request Id, which will be 0 if the call fails immediately.  Call error()
     * to get more info on failures.
     *
     * @b Immediate errors @b - See @c error() and @c IdentityServiceResult.
     *
     * @b Asynchronous Error @b Handling - See @c dataSetFailed and @c IdentityServicePropertyResult.
     */
    int setData( int type, int flags, const QString &name, const QByteArray &value );

    //!@cond PRIVATE
    /*!
     * @brief Issue a request to set data.
     *
     * @details Upon completion of a successful setData call, the dataSet signal
     * is emitted.
     *
     * @param type The type of properties contained in the @c data parameter. Each
     * identity provider may have a unique set of types that it is able to handle.
     * See the identity provider's documentation for details on valid types.
     * @param flags Flags related to the request.  Each provider may define specific
     * flags.
     * @param name The name of the data to store.
     * @param value The content of the data to store.
     * @return A request Id, which will be 0 if the call fails immediately.  Call error()
     * to get more info on failures.
     *
     * @b Immediate errors @b - See @c error() and @c IdentityServiceResult.
     *
     * @b Asynchronous Error @b Handling - See @c dataSetFailed and @c IdentityServicePropertyResult.
     */
    Q_INVOKABLE
    int setData( int type, int flags, const QString &name, const QString &value );
    //!@endcond PRIVATE

    /*!
     * @brief Issue a request to create data.
     *
     * @details Upon completion of a successful createData call, the dataCreated
     * signal is emitted.
     *
     * @param type The type of properties contained in the @c data parameter. Each
     * identity provider may have a unique set of types that it is able to handle.
     * See the identity provider's documentation for details on valid types.
     * @param flags Flags related to the request.  Each provider may define specific
     * flags.
     * @param name The name of the data to store.
     * @param value The content of the data to store.
     * @return A request Id, which will be 0 if the call fails immediately.  Call error()
     * to get more info on failures.
     *
     * @b Immediate errors @b - See @c error() and @c IdentityServiceResult.
     *
     * @b Asynchronous Error @b Handling - See @c dataCreateFailed and @c IdentityServicePropertyResult.
     */
    int createData( int type, int flags, const QString &name, const QByteArray &value );

    //!@cond PRIVATE
    /*!
     * @brief Issue a request to create data.
     *
     * @details Upon completion of a successful createData call, the dataCreated
     * signal is emitted.
     *
     * @param type The type of properties contained in the @c data parameter. Each
     * identity provider may have a unique set of types that it is able to handle.
     * See the identity provider's documentation for details on valid types.
     * @param flags Flags related to the request.  Each provider may define specific
     * flags.
     * @param name The name of the data to store.
     * @param value The content of the data to store.
     * @return A request Id, which will be 0 if the call fails immediately.  Call error()
     * to get more info on failures.
     *
     * @b Immediate errors @b - See @c error() and @c IdentityServiceResult.
     *
     * @b Asynchronous Error @b Handling - See @c dataCreateFailed and @c IdentityServicePropertyResult.
     */
    Q_INVOKABLE
    int createData( int type, int flags, const QString &name, const QString &value );
    //!@endcond PRIVATE

    /*!
     * @brief Issue a request to delete data.
     * @details Upon completion of a successful deleteData call, the dataDeleted signal
     * is emitted.
     *
     * @param type The type of data contained in the @c propertyList
     * parameter. Each provider may have a unique set of types that it is able to
     * handle.  See the documentation for the provider for details on valid values.
     * @param name The name of the data to delete
     * @return A request Id, which will be 0 if the call fails immediately.  Call error()
     * to get more info on failures.
     *
     * @b Immediate errors @b - See @c error() and @c IdentityServiceResult.
     *
     * @b Asynchronous Error @b Handling - See @c dataDeleteFailed and @c IdentityServicePropertyResult.
     */
    Q_INVOKABLE
    int deleteData( int type, int flags, const QString &name );

    /*!
     * @brief Issue a request for the list of stored data.
     * @details Upon completion of a successful listData call, the dataListRetrieved signal
     * is emitted.
     *
     * @param type The type of data to list. Each identity provider may have a
     * unique set of types that it is able to handle. See the identity provider's
     * documentation for details on valid data types.
     * @param flags Special flags for the operation. Each provider may have a unique
     * set of flags that it supports.  See the documentation for the provider for
     * details on valid values and their behavior.
     *
     * @return A request Id, which will be 0 if the call fails immediately.  Call error()
     * to get more info on failures.
     *
     * @b Immediate errors @b - See @c error() and @c IdentityServiceResult.
     *
     * @b Asynchronous Error @b Handling - See @c dataListFailed and @c IdentityServicePropertyResult.
     */
    Q_INVOKABLE
    int listData( int type, int flags ) const;

    /*!
     * @brief Issue a request to challenge for identity.
     * @details Upon completion of a successful challenge call, the challengeComplete signal
     * is emitted.
     *
     * @param type The type of challenge requested. Each identity provider may
     * have a unique set of types that it supports. See the identity provider's
     * documentation for details on valid types and their behavior.
     * @param flags Special flags for the operation. Each provider may have a unique
     * set of flags that it supports.  See the documentation for the provider for
     * details on valid values and their behaviour.
     *
     * @return A request Id, which will be 0 if the call fails immediately.  Call error()
     * to get more info on failures.
     *
     * @b Immediate errors @b - See @c error() and @c IdentityServiceResult.
     *
     * @b Asynchronous Error @b Handling - See @c challengeFailed and @c IdentityServicePropertyResult.
     */
    Q_INVOKABLE
    int challenge( int type, int flags ) const;

    /*!
     * @brief Register to be notified when the named entry changes.
     * @param type The type of data referred to by @c name.
     * @param flags Special flags for the operation. Each provider may have a unique
     * set of flags that it supports.  See the documentation for the provider for
     * details on valid values and their behaviour.
     * @param name The name of the entry to receive notifications for.
     *
     * @return @c IdentityServiceResult. Success if successful. See
     * @c IdentityServiceResult for details regarding errors.
     *
     * @b Immediate errors @b - See @c error() and @c IdentityServiceResult.
     */
    Q_INVOKABLE
    int setNotification( int type, int flags, const QString &name );

    /*!
     * @brief Contains the last immediate error from request.
     * @return The result of the last failed API call.
     */
#ifndef Q_MOC_RUN
    Q_INVOKABLE
    bb::platform::identity::IdentityServiceResult::Type error() const;
#else
    Q_INVOKABLE int error() const;
#endif
    /*!
     * @brief Used to determine if the IdentityServiceProvider class is valid.
     * @return true if the IdentityServiceProvider has a valid provider; otherwise
     * returns false.
     */
    Q_INVOKABLE
    bool isValid() const;

    /*!
     * @brief The maximum number of properties that can be included in a single
     * requestProperties() call.
     * @return The maximum number of properties.
     */
    int maxPropertyCount() const;

    /*!
     * @brief The maximum string length of a single property name that can be
     * passed in a single @c requestProperties() call, excluding the terminating
     * NULL.
     * @return The maximum string length.
     */
    int maxPropertyNameLength() const;

    /*!
     * @brief The maximum string length of a single data name that can be
     * passed in @c requestData(), @c setData(), @c createData()
     * and @c deleteData() calls, excluding the terminating NULL.
     * @return The maximum string length.
     */
    int maxDataNameLength() const;Q_SIGNALS:
    /*!
     * @brief Emitted upon successful completion of a requestToken call.
     *
     * @param requestId The request id of the originating requestToken call.
     * @param token The requested token.
     * @param parameters The list of additional token parameters.
     */
    void tokenRetrieved( int requestId, const QByteArray &token, const QMap<QString, QString> &parameters );

    //!@cond PRIVATE
    /*!
     * @brief FOR USE WITH QML - Emitted upon successful completion of a requestToken call.
     *
     * @param requestId The request id of the originating requestToken call.
     * @param token The requested token.
     * @param parameters The list of additional token parameters.
     */
    void tokenRetrieved( int requestId, const QVariant &token, const QVariantMap &parameters );
    //!@endcond PRIVATE

    /*!
     * @brief Emitted upon failure of a requestToken call.
     *
     * @param requestId The request id of the originating requestToken call.
     * @param result Information regarding the failure.
     * @param info Optional information with additional information regarding
     * the request failure.
     */
    void tokenRetrievalFailed( int requestId, bb::platform::identity::IdentityServiceTokenResult::Type result,
            const QString &info );

    //!@cond PRIVATE
    /*!
     * @brief FOR USE WITH QML - Emitted upon failure of a requestToken call.
     *
     * @param requestId The request id of the originating requestToken call.
     * @param result Information regarding the failure.
     * @param info Optional information with additional information regarding
     * the request failure.
     */
    void tokenRetrievalFailed( int requestId, int result, const QString &info );
    //!@endcond PRIVATE

    /*!
     * @brief Emitted upon successful completion of a clearToken call.
     *
     * @param requestId The request id of the originating clearToken call.
     */
    void tokenCleared( int requestId );

    /*!
     * @brief Emitted upon failure of a clearToken call.
     *
     * @param requestId The request id of the originating clearToken call.
     * @param result Information regarding the failure.
     * @param info Optional information with additional information regarding
     * the request failure.
     */
    void tokenClearFailed( int requestId, bb::platform::identity::IdentityServiceTokenResult::Type result,
            const QString &info );

    //!@cond PRIVATE
    /*!
     * @brief FOR USE WITH QML - Emitted upon failure of a clearToken call.
     *
     * @param requestId The request id of the originating clearToken call.
     * @param result Information regarding the failure.
     * @param info Optional information with additional information regarding
     * the request failure.
     */
    void tokenClearFailed( int requestId, int result, const QString &info );
    //!@endcond PRIVATE

    /*!
     * @brief Emitted upon successful completion of a getProperties call.
     *
     * @param requestId The request id of the originating getProperties call.
     * @param userProperties A list containing the requested properties.
     */
    void propertiesRetrieved( int requestId, const QMap<QString, QString> &userProperties );

    //!@cond PRIVATE
    /*!
     * @brief FOR USE WITH QML - Emitted upon successful completion of a getProperties call.
     *
     * @param requestId The request id of the originating getProperties call.
     * @param userProperties A list containing the requested properties.
     */
    void propertiesRetrieved( int requestId, const QVariantMap &userProperties );
    //!@endcond PRIVATE

    /*!
     * @brief Emitted upon failure of a getProperties call.
     *
     * @param requestId The request id of the originating getProperties call.
     * @param result Information regarding the failure.
     * @param info Optional information with additional information regarding
     * the request failure.
     */
    void propertyRetrievalFailed( int requestId, bb::platform::identity::IdentityServicePropertyResult::Type result,
            const QString &info );

    //!@cond PRIVATE
    /*!
     * @brief FOR USE WITH QML - Emitted upon failure of a getProperties call.
     *
     * @param requestId The request id of the originating getProperties call.
     * @param result Information regarding the failure.
     * @param info Optional information with additional information regarding
     * the request failure.
     */
    void propertyRetrievalFailed( int requestId, int result, const QString &info );
    //!@endcond PRIVATE

    /*!
     * @brief Emitted upon successful completion of a requestData call.
     *
     * @param requestId The request id of the originating getProperties call.
     * @param data The requested data.
     */
    void dataRetrieved( int requestId, const QByteArray &data );

    //!@cond PRIVATE
    /*!
     * @brief FOR USE WITH QML - Emitted upon successful completion of a requestData call.
     *
     * @param requestId The request id of the originating getProperties call.
     * @param data The requested data.
     */
    void dataRetrieved( int requestId, const QString &data );
    //!@endcond PRIVATE

    /*!
     * @brief Emitted upon failure of a requestData call.
     *
     * @param requestId The request id of the originating getProperties call.
     * @param result Information regarding the failure.
     * @param info Optional information with additional information regarding
     * the request failure.
     */
    void dataRetrievalFailed( int requestId, bb::platform::identity::IdentityServicePropertyResult::Type result,
            const QString &info );

    //!@cond PRIVATE
    /*!
     * @brief FOR USE WITH QML - Emitted upon failure of a requestData call.
     *
     * @param requestId The request id of the originating getProperties call.
     * @param result Information regarding the failure.
     * @param info Optional information with additional information regarding
     * the request failure.
     */
    void dataRetrievalFailed( int requestId, int result, const QString &info );
    //!@endcond PRIVATE

    /*!
     * @brief Emitted upon successful completion of a setProperty call.
     *
     * @param requestId The request id of the originating setProperty call.
     */
    void dataSet( int requestId );

    /*!
     * @brief Emitted upon failure of a setProperty call.
     *
     * @param requestId The request id of the originating setProperty call.
     * @param result Information regarding the failure.
     * @param info Optional information with additional information regarding
     * the request failure.
     */
    void dataSetFailed( int requestId, bb::platform::identity::IdentityServicePropertyResult::Type result,
            const QString &info );

    //!@cond PRIVATE
    /*!
     * @brief FOR USE WITH QML - Emitted upon failure of a setProperty call.
     *
     * @param requestId The request id of the originating setProperty call.
     * @param result Information regarding the failure.
     * @param info Optional information with additional information regarding
     * the request failure.
     */
    void dataSetFailed( int requestId, int result, const QString &info );
    //!@endcond PRIVATE

    /*!
     * @brief Emitted upon successful completion of a createData call.
     *
     * @param requestId The request id of the originating createProperty call.
     */
    void dataCreated( int requestId );

    /*!
     * @brief Emitted upon failure of a createProperty call.
     *
     * @param requestId The request id of the originating createProperty call.
     * @param result Information regarding the failure.
     * @param info Optional information with additional information regarding
     * the request failure.
     */
    void dataCreateFailed( int requestId, bb::platform::identity::IdentityServicePropertyResult::Type result,
            const QString &info );

    //!@cond PRIVATE
    /*!
     * @brief FOR USE WITH QML - Emitted upon failure of a createProperty call.
     *
     * @param requestId The request id of the originating createProperty call.
     * @param result Information regarding the failure.
     * @param info Optional information with additional information regarding
     * the request failure.
     */
    void dataCreateFailed( int requestId, int result, const QString &info );
    //!@endcond PRIVATE

    /*!
     * @brief Emitted upon successful completion of a deleteProperty call.
     *
     * @param requestId The request id of the originating deleteProperty call.
     */
    void dataDeleted( int requestId );

    /*!
     * @brief Emitted upon failure of a deleteProperty call.
     *
     * @param requestId The request id of the originating deleteProperty call.
     * @param result Information regarding the failure.
     * @param info Optional information with additional information regarding
     * the request failure.
     */
    void dataDeleteFailed( int requestId, bb::platform::identity::IdentityServicePropertyResult::Type result,
            const QString &info );

    //!@cond PRIVATE
    /*!
     * @brief FOR USE WITH QML - Emitted upon failure of a deleteProperty call.
     *
     * @param requestId The request id of the originating deleteProperty call.
     * @param result Information regarding the failure.
     * @param info Optional information with additional information regarding
     * the request failure.
     */
    void dataDeleteFailed( int requestId, int result, const QString &info );
    //!@endcond PRIVATE

    /*!
     * @brief Emitted upon successful completion of a listData call.
     *
     * @param requestId The request id of the originating listData call.
     * @param dataList The requested data.
     */
    void dataListRetrieved( int requestId, const QStringList &dataList );

    /*!
     * @brief Emitted upon failure of a listData call.
     *
     * @param requestId The request id of the originating listData call.
     * @param result Information regarding the failure.
     * @param info Optional information with additional information regarding
     * the request failure.
     */
    void dataListFailed( int requestId, bb::platform::identity::IdentityServicePropertyResult::Type result,
            const QString &info );

    //!@cond PRIVATE
    /*!
     * @brief FOR USE WITH QML - Emitted upon failure of a listData call.
     *
     * @param requestId The request id of the originating listData call.
     * @param result Information regarding the failure.
     * @param info Optional information with additional information regarding
     * the request failure.
     */
    void dataListFailed( int requestId, int result, const QString &info );
    //!@endcond PRIVATE

    /*!
     * @brief Emitted upon successful completion of a challenge call.
     *
     * @param requestId The request id of the originating challenge call.
     * @param level Indicates the level of assurance of the successful challenge
     * completed. See the specific identity provider's documentation for
     * additional information on the values that can be returned.
     */
    void challengeComplete( int requestId, int level );

    /*!
     * @brief Emitted upon failure of a challenge call.
     *
     * @param requestId The request id of the originating challenge call.
     * @param result Information regarding the failure.
     * @param info Optional information with additional information regarding
     * the request failure.
     */
    void challengeFailed( int requestId, bb::platform::identity::IdentityServicePropertyResult::Type result,
            const QString &info );

    //!@cond PRIVATE
    /*!
     * @brief FOR USE WITH QML - Emitted upon failure of a challenge call.
     *
     * @param requestId The request id of the originating challenge call.
     * @param result Information regarding the failure.
     * @param info Optional information with additional information regarding
     * the request failure.
     */
    void challengeFailed( int requestId, int result, const QString &info );
    //!@endcond PRIVATE

    /*!
     * @brief Emitted when a registered notification is received.
     *
     * @param type The type of entry.  Same as value used when registering the
     * notifier.
     * @param notificationName The name of the entry, which is the same as the value that was
     * used when registering the notifier.
     * @param notification Indicates the kind of change that occurred.  See
     * provider's documentation for the values it will return.
     */
    void notificationReceived( int type, const QString &notificationName, int notification );

private:
    //!@cond PRIVATE
    QScopedPointer<IdentityServiceProviderPrivate> const d_ptr;Q_DECLARE_PRIVATE( IdentityServiceProvider )
    Q_DISABLE_COPY( IdentityServiceProvider )
    //!@endcond PRIVATE
};

} // namespace identity
} // namespace platform
} // namespace bb

#endif /* BB_PLATFORM_IDENTITY_IDENTITYSERVICEPROVIDER_HPP */
