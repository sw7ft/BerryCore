/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_IDENTITY_BLACKBERRYPROFILE_HPP
#define BB_PLATFORM_IDENTITY_BLACKBERRYPROFILE_HPP

#include <bb/platform/Global>

#include <QObject>

namespace bb {
namespace platform {
namespace identity {

class BlackBerryProfilePrivate;
/*!
 * @brief Use BlackBerry profile as an identity provider, and provide
 * off-device data storage.
 *
 * BlackBerry profile is an identity provider that allows access to
 * off-device, encrypted storage space. The storage space is bound to the
 * BlackBerry ID user that is currently logged in. The storage is accessible
 * remotely from all devices logged in with the same BlackBerry ID user,
 * allowing applications installed on multiple devices access to the same
 * information.
 *
 *@section bbprofile_supported_apis IDS API support
 * BlackBerry profile supports the following @c IdentityServiceProvider functions.
 * Using BlackBerry profile with other functions will result in errors.
 * - createData()
 * - requestData()
 * - setData()
 * - deleteData()
 * - listData()
 * - setNotification()
 *
 * @section  data_storage_sec  Off-device data storage and retrieval APIs
 * Applications can use the APIs to securely store data in, and retrieve data
 * from, the BlackBerry ecosystem. APIs are provided for storing data initially
 * (createData()), retrieving the data (requestData()), updating the data
 * (setData()), and removing the data (deleteData()).
 *
 * @section bbprofile_permissions Permissions
 * In order to store and retrieve data off of the device, wireless data is
 * consumed. Applications using storage from BlackBerry profile must have
 * the @c access_internet permission included in their bar descriptor file.
 *
 * @section  data_storage_caps_sec  Limits to storage capacity
 * There's a limit to the amount of off-device storage that is available to
 * each of your users. Storage limits are set according to user and app
 * vendor, and apply to all of the apps that a user might have with a
 * single vendor. As of 1 May 2014, the storage capacity is 10 MB, though
 * BlackBerry may increase or decrease this capacity without notice. For example,
 * if you have multiple apps that require off-device storage, and you have 
 * a user who makes use of three of those apps, that user's storage limit applies
 * to the total amount of storage space that those three apps require. Users 
 * can have multiple storage allocations, one for each app vendor.
 *
 * @section bbprofile_data_usage Data usage
 * In order to store and retrieve data off of the device, wireless data is
 * consumed. Applications using storage from BlackBerry profile must
 * have the "Internet" permission included in their bar descriptor file.
 *
 * @section bbprofile_caching Caching
 * In cases where the application may need data stored locally for quick or
 * repeated access, the value can be cached securely on the device and
 * retrieved on demand, even when not connected to the remote storage copy.
 * The cache is synchronized with the remote copy so that the cache is always
 * up to date while the device has appropriate data coverage.
 *
 * @section bbprofile_usage Using profile storage
 *
 * @subsection bbprofile_usage_create Create - Store a new entry
 * Call @c createData() to store new profile entries.
 *  - @c type is one of the @c BlackBerryProfilePropertyType types.
 *  - @c flags are a combination of @c BlackBerryProfileCreateDataFlags.
 *
 * @subsection bbprofile_usage_set Set - Update an entry
 * Call @c setData() to update profile entries.
 *  - @c type is one of the @c BlackBerryProfilePropertyType types.
 *  - @c flags are a combination of @c BlackBerryProfileSetDataFlags.
 *
 * @subsection bbprofile_usage_get Get - Retrieve an entry
 * Call @c requestData() to retrieve profile entries.
 *  - @c type is one of the @c BlackBerryProfilePropertyType types.
 *  - @c flags are a combination of @c BlackBerryProfileGetDataFlags.
 *
 * @subsection bbprofile_usage_delete Delete - Remove an entry
 * Call @c deleteData() to remove profile entries.
 *  - @c type is one of the @c BlackBerryProfilePropertyType types.
 *  - @c flags are a combination of @c BlackBerryProfileDeleteDataFlags.
 *
 * @subsection bbprofile_usage_list Get - List available entries
 * Call @c listData() to list profile entries.
 *  - @c type is one of the @c BlackBerryProfilePropertyType types.
 *  - @c flags are a combination of @c BlackBerryProfileListDataFlags.
 *
 * @section bbprofile_notifications Notifications
 * Notifications can be registered for entries either before or after they have
 * been created. In cases where the registration is done after creation, the
 * application is notified each time the value changes so that it can
 * perform any necessary operations. If registration is done before an entry
 * is created, the application is notified upon creation of the value as
 * if it were an update. Additionally, registered applications receive a
 * change notification when an entry is deleted.
 *
 * To register for profile entry change notifications, call
 * @c setNotification().
 *  - @c type is one of the @c BlackBerryProfilePropertyType types.
 *  - @c flags are a combination of @c BlackBerryProfileSetNotificationFlag.
 *
 * Each time a registered entry changes, the registered callback function is
 * executed and the corresponding @c ids_bbprofile_notification
 * indicates the kind of change that occurred.
 *
 * @section Code_sample_sec Sample code for using BlackBerryProfile as the identity provider for your app
 *
 * The following sample shows how to a list of user data stored for an application:
 *
 * @code
 * Make sure to include the following header files in your application
 *
 * #include <bb/platform/identity/IdentityServiceProvider>
 * #include <bb/platform/identity/IdentityServiceResult>
 * #include <bb/platform/identity/IdentityServicePropertyResult>
 * #include <bb/platform/identity/BlackBerryProfile>
 * #include <bb/platform/identity/BlackBerryProfilePropertyType>
 * #include <bb/platform/identity/BlackBerryProfileListDataFlag>
 *
 * Step 1 - Create an IdentityServiceProvider instance.
 *
 * IdentityServiceProvider *provider = new IdentityServiceProvider( BlackBerryProfile::providerName(), this );
 * if( !provider->isValid() ) {
 *      qWarning << "Unable to communicate with BlackBerryProfile Provider: " << provider->error();
 * }
 *
 * Step 2 - Connect with with success and failure signals.
 *
 * QObject::connect( provider, SIGNAL( dataListRetrieved( int, QStringList ) ),
 *                      this, SLOT( dataListed( int, QStringList ) ) );
 *
 * QObject::connect( provider, SIGNAL( dataListFailed( int, bb::platform::identity::IdentityServicePropertyResult::Type, QString ) ),
 *                      this, SLOT( listDataFail( int, bb::platform::identity::IdentityServicePropertyResult::Type, QString ) ) );
 *
 * Step 3 - Call API's
 *
 * IdentityServiceResult::Type result = provider->listData( BlackBerryProfilePropertyType::Application,
 *                                                              BlackBerryProfileListDataFlag::Default );
 * if( result != IdentityServiceResult::Success ){
 *      qWarning << "Unable to retrieve data list: " << result;
 * }
 *
 * @endcode
 *
 * @headerfile BlackBerryProfile.hpp <bb/platform/identity/BlackBerryProfile>
 * @xmlonly
 * <library name="bbplatform" />
 * <apigrouping group="Platform/Identity" />
 * @endxmlonly
 */
class BB_PLATFORM_EXPORT BlackBerryProfile: public QObject {
    Q_OBJECT

    /**
     * @brief The identity provider name of BlackBerry ID to
     * use with the @sa IdentityServiceProvider class.
     */
    Q_PROPERTY( QString providerName READ providerName CONSTANT FINAL )

public:
    /*!
     * @brief Constructs an empty BlackBerryProfile instance.
     * @param parent The parent object.  Setting parent to 0
     * constructs an BlackBerryProfile instance with no parent.
     */
    explicit BlackBerryProfile( QObject *parent = 0 );

    /*!
     * @brief Destroys the BlackBerryProfile instance.
     */
    virtual ~BlackBerryProfile();

    /**
     * @brief The identity provider name of BlackBerry Profile to
     * use with the @sa IdentityServiceProvider class.
     * @return The string name of the BlackBerry Profile provider.
     */
    static QString providerName();

private:
    //!@cond PRIVATE
    Q_DISABLE_COPY( BlackBerryProfile )
    ;
    QScopedPointer<BlackBerryProfilePrivate> d_ptr;Q_DECLARE_PRIVATE( BlackBerryProfile )
    ;
    //!@endcond PRIVATE

};
} // namespace identity
} // namespace platform
} // namespace bb

// TODO:
// QML_DECLARE_TYPE( bb::platform::identity::BlackBerryProfile )

#endif /* BB_PLATFORM_IDENTITY_BLACKBERRYPROFILE_HPP */
