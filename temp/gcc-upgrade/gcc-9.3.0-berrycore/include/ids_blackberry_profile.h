/*
 * Research In Motion Limited. Copyright (C) 2013.
 * Research In Motion Limited. All rights reserved.
 */

/**
 * @file ids_blackberry_profile.h
 *
 * @brief Use BlackBerry profile as an identity provider, and provide
 * off-device data storage.
 *
 * @page BBProfile_Provider BlackBerry profile
 * BlackBerry profile is an identity provider that allows access to
 * off-device, encrypted storage space. The storage space is bound to the
 * BlackBerry ID user that is currently logged in. The storage is accessible
 * remotely from all devices logged in with the same BlackBerry ID user,
 * allowing applications installed on multiple devices access to the same
 * information.
 *
 * @section bbprofile_supported_apis IDS API support
 * BlackBerry profile supports the following Identity Service functions. Using
 * BlackBerry profile with other functions will result in errors.
 * - ids_create_data()
 * - ids_get_data()
 * - ids_set_data()
 * - ids_delete_data()
 * - ids_list_data()
 * - ids_register_notifier()
 *
 * @section  data_storage_sec  Off-device data storage and retrieval APIs
 * Applications can use the APIs to securely store data in, and retrieve data
 * from, the BlackBerry ecosystem. APIs are provided for storing data initially
 * (ids_create_data()), retrieving the data (ids_get_data()), updating the data
 * (ids_set_data()), and removing the data (ids_delete_data()).
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
 * single vendor. For example, if you have multiple apps that require
 * off-device storage, and you have a user who makes use of three of those
 * apps, that user's storage limit applies to the total amount of storage
 * space that those three apps require. Users can have multiple storage
 * allocations, one for each app vendor.
 *
 * @internal For RIM applications that use BlackBerry profile as their
 * identity provider, there is no size restriction on how much data the app
 * can store for each user.
 *
 * @section bbprofile_caching Caching
 * In cases where the application may need data for quick or repeated access,
 * the value can be requested to be cached securely on the device.  When data
 * is cached, retrieving it does not require communication with the remote
 * storage servers, this optimises read operations.  Creating and updating
 * data always requires connectivity with the remote storage servers so a
 * value can not be added/updated while offline.  The cache is synchronised
 * with the remote copy so that the cache is always up to date while the device
 * has appropriate data coverage.  In cases where the device does not have
 * appropriate data coverage, cached values can still be read, but no
 * updates are possible.
 *
 * @section bbprofile_usage Using profile storage
 *
 * @subsection bbprofile_usage_create Create - Store a new entry
 * Call @c ids_create_data() to store new profile entries.  The name of an
 * entry can contain the alphaNumeric characters a-z, A-Z, 1-9, and special
 * characters :_ with no spaces.
 *  - @c type is one of the @c ids_bbprofile_type "profile types".
 *  - @c flags are a combination of @c ids_bbprofile_create_data_flag.
 *
 * @subsection bbprofile_usage_set Set - Update an entry
 * Call @c ids_set_data() to update profile entries.
 *  - @c type is one of the @c ids_bbprofile_type "profile types".
 *  - @c flags are a combination of @c ids_bbprofile_set_data_flag.
 *
 * @subsection bbprofile_usage_get Get - Retrieve an entry
 * Call @c ids_get_data() to retrieve profile entries.
 *  - @c type is one of the @c ids_bbprofile_type "profile types".
 *  - @c flags are a combination of @c ids_bbprofile_get_data_flag.
 *
 * @subsection bbprofile_usage_delete Delete - Remove an entry
 * Call @c ids_delete_data() to remove profile entries.
 *  - @c type is one of the @c ids_bbprofile_type "profile types".
 *  - @c flags are a combination of @c ids_bbprofile_delete_data_flag.
 *
 * @subsection bbprofile_usage_list Get - List available entries
 * Call @c ids_list_data() to list profile entries.
 *  - @c type is one of the @c ids_bbprofile_type "profile types".
 *  - @c flags are a combination of @c ids_bbprofile_list_data_flag.
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
 * @c ids_register_notifier().
 *  - @c type is one of the @c ids_bbprofile_type "profile types".
 *  - @c flags are a combination of @c ids_bbprofile_register_notifier_flag.
 *
 * Each time a registered entry changes, the registered callback function is
 * executed and the corresponding @c ids_bbprofile_notification
 * indicates the kind of change that occurred.
 */

#ifndef IDS_BLACKBERRY_PROFILE_H_
#define IDS_BLACKBERRY_PROFILE_H_

/**
 * @brief The identity provider name for BlackBerry profile
 * @sa ids_register_provider()
 */
#define BLACKBERRY_PROFILE_PROVIDER "ids:rim:profile"

/**
 * @brief The type used to identify the scope that a data entry is stored in
 * within the profile
 * @details The data-profile provider uses the @c type to differentiate
 * between various scopes of data that an application can store. The types
 * available each have their own style of protection. Based on how the
 * application uses the data, the application may choose to store data
 * under one or various types.
 */
enum ids_bbprofile_type {
    /**
     * @brief Application-scoped profile data
     * @details Entries stored with this type are access protected to allow
     * only the creating application access to the data. No other application
     * is able to retrieve, modify, delete or list the values. If the
     * same application is installed on another device with the same user, it
     * will have access to the data. This creates a private-store of data for
     * the application that is accessible only from the specific application
     * on any device with the same BlackBerry ID user logged in.
     */
    IDS_PROFILE_TYPE_APP = 1,
    /**
     * @brief Vendor-scoped profile data
     * @details Entries stored with this type are access protected to allow
     * all applications developed by the same vendor access to the data. No
     * other vendor's applications will be able to retrieve, modify, delete or
     * list the values. If there are several applications installed on a device
     * from the same vendor, they will all have access to these values. If
     * apps from the same vendor are installed on another device, and the same
     * BlackBerry ID user is logged in to that device, all apps from that
     * vendor will have access to the data. This creates a vendor
     * private-store of data that is accessible only from the specific
     * vendor's applications on any device with the same BlackBerry ID user
     * logged in.
     */
    IDS_PROFILE_TYPE_VENDOR = 2
};

/**
 * @brief The flags for creating profile data
 * @details Multiple flags can be combined using bitwise 'OR' unless stated
 * otherwise.
 * See the @c flags parameter in the @c ids_create_data() function for more
 * information.
 */
enum ids_bbprofile_create_data_flag {
    /**
     * @brief Default creation flags
     * @details No options specified, and the creation will follow the default
     * behavior where no caching and no extra encryption will be performed for
     * the new entry.
     */
    IDS_PROFILE_CREATE_DATA_DEFAULT  = 0x00000000,
    /**
     * @brief Device-To-Device encryption, dynamic keys, no user involvement
     * @details To have additional encryption performed on the data prior to
     * being stored remotely. Data is encrypted with dynamically generated keys
     * shared between devices using the same BlackBerry ID user. Only devices
     * with the same user will have the keys to decrypt this data.  The keys
     * are shared between devices and not included in backups or transferred as
     * part of device swap, so if a user only has one device, and it is lost,
     * the keys are not recoverable, and any remote data stored with this
     * encryption will be non-recoverable. Performing a "Security Wipe" will
     * retain the keys and the stored data is recoverable if the same user
     * logs back into the device. If the user has multiple devices,
     * and are data enabled, the devices with the same BlackBerry ID user will
     * exchange the keys securely so that all of them can store and retrieve
     * the data stored with this encryption. Operations will return
     * @c IDS_NOT_READY while the encryption keys are exchanged; the app can
     * repeat the request after a short wait to avoid failures during this one
     * time key exchange window.
     */
    IDS_PROFILE_CREATE_DATA_ENCRYPT_D2D = 0x00000001,
    /**
     * @brief Enable local caching of the entry
     * @details Override the default behavior to enable local data caching for
     * this entry.
     * In cases where the application may need data for quick or repeated
     * access, the value can be requested to be cached securely on the device.
     * When data is cached, retrieving it does not require communication with
     * the remote storage servers, this optimises read operations.  Creating
     * and updating data always requires connectivity with the remote storage
     * servers so a value can not be added/updated while offline.  The cache
     * is synchronised with the remote copy so that the cache is always up to
     * date while the device has appropriate data coverage.  In cases where
     * the device does not have appropriate data coverage, cached values can
     * still be read, but no updates are possible.
     */
    IDS_PROFILE_CREATE_DATA_CACHE    = 0x00000010
};

/**
 * @brief The flags for retrieving profile data
 * @details Multiple flags can be combined using bitwise 'OR' unless stated
 * otherwise.
 * See the @c flags parameter in the ids_get_data() function for more
 * information.
 */
enum ids_bbprofile_get_data_flag {
    /**
     * @brief Use the default flags for get requests
     * @details If options are not specified, the get request will follow the
     * default behavior where the entry is not cached.  If the entry is already
     * being cached, this flag will not disable caching.
     */
    IDS_PROFILE_GET_DATA_DEFAULT  = 0x00000000,
    /**
     * @brief Enable local caching of the entry
     * @details Override the default behavior to enable local data caching for
     * this entry.
     * In cases where the application may need data for quick or repeated
     * access, the value can be requested to be cached securely on the device.
     * When data is cached, retrieving it does not require communication with
     * the remote storage servers, this optimises read operations.  Creating
     * and updating data always requires connectivity with the remote storage
     * servers so a value can not be added/updated while offline.  The cache
     * is synchronised with the remote copy so that the cache is always up to
     * date while the device has appropriate data coverage.  In cases where
     * the device does not have appropriate data coverage, cached values can
     * still be read, but no updates are possible.
     */
    IDS_PROFILE_GET_DATA_CACHE    = 0x00000001
};

/**
 * @brief The flags for modifying profile data
 * @details Multiple flags can be combined using bitwise 'OR' unless stated
 * otherwise.
 * See the @c flags parameter in the @c ids_set_data() function for more
 * information.
 */
enum ids_bbprofile_set_data_flag {
    /**
     * @brief Use the default flags for set requests
     * @details If options are not specified, the update process will follow
     * the default behavior where the entry is not cached.  If the entry is
     * already being cached, this flag will not disable caching.
     */
    IDS_PROFILE_SET_DATA_DEFAULT  = 0x00000000,
    /**
     * @brief Enable local caching of the entry
     * @details Override the default behavior to enable local data caching for
     * this entry.
     * In cases where the application may need data for quick or repeated
     * access, the value can be requested to be cached securely on the device.
     * When data is cached, retrieving it does not require communication with
     * the remote storage servers, this optimises read operations.  Creating
     * and updating data always requires connectivity with the remote storage
     * servers so a value can not be added/updated while offline.  The cache
     * is synchronised with the remote copy so that the cache is always up to
     * date while the device has appropriate data coverage.  In cases where
     * the device does not have appropriate data coverage, cached values can
     * still be read, but no updates are possible.
     */
    IDS_PROFILE_SET_DATA_CACHE    = 0x00000001
} ;

/**
 * @brief The flags for deleting profile entries
 * @details Multiple flags can be combined using bitwise 'OR' unless stated
 * otherwise.
 * See the @c flags parameter in the @c ids_delete_data() function for more
 * information.
 */
enum ids_bbprofile_delete_data_flag {
    /**
     * @brief Use the default flags for delete requests
     * @details If options are not specified, the deletion will follow the
     * default behavior where the specified remote entry is deleted as
     * well as the cached copy if is was cached.
     */
    IDS_PROFILE_DELETE_DATA_DEFAULT     = 0x00000000,
    /**
     * @brief Remove local cached copy of the entry
     * @details Override the default behavior to remove only the cached copy,
     * but leave the remote copy unchanged.
     * In cases where the application may need data for quick or repeated
     * access, the value can be requested to be cached securely on the device.
     * When data is cached, retrieving it does not require communication with
     * the remote storage servers, this optimises read operations.  Creating
     * and updating data always requires connectivity with the remote storage
     * servers so a value can not be added/updated while offline.  The cache
     * is synchronised with the remote copy so that the cache is always up to
     * date while the device has appropriate data coverage.  In cases where
     * the device does not have appropriate data coverage, cached values can
     * still be read, but no updates are possible.
     */
    IDS_PROFILE_DELETE_DATA_CACHE_ONLY  = 0x00000001,
    /**
     * @brief  Delete all entries under profile type
     * @details Removes all the entries for the given type. The @c name
     * specified must be @c NULL when using this flag. To avoid accidental
     * removal of shared entries, use type @c IDS_PROFILE_TYPE_VENDOR in
     * @c ids_bbprofile_type, which does not allow this flag.
     */
    IDS_PROFILE_DELETE_DATA_ALL         = 0x00000002
};

/**
 * @brief The flags for listing profile entries
 * @details Multiple flags can be combined using bitwise 'OR' unless stated
 * otherwise.  Currently there are no other options available, use the default
 * flag for future compatibility.
 * See the @c flags parameter in the @c ids_list_data() function form more
 * information.
 */
enum ids_bbprofile_list_data_flag {
    /**
     * @brief Default list flags
     * @details If options are not specified, the list process will follow the
     * default behavior of listing the remotely available entries.
     */
    IDS_PROFILE_LIST_DATA_DEFAULT = 0x00000000
};

/**
 * @brief The flags for registering/deregistering change notifications of
 * entries within the profile
 * @details Notifications can be registered for entries either before
 * or after they have been created. In cases where the registration is done
 * after creation, the application is notified each time the value changes so
 * that it can perform any necessary operations. If registration is done
 * before an entry is created, the application is notified upon creation of
 * the value as if it were an update. Additionally, registered applications
 * receive a change notification when an entry is deleted.
 * Multiple flags can be combined using bitwise 'OR' unless stated otherwise.
 * See the @c flags parameter for the @c ids_register_notifier() function for
 * more information.
 */
enum ids_bbprofile_register_notifier_flag {
    /**
     * @brief Request to start receiving notifications
     */
    IDS_PROFILE_NOTIFIER_START = 0x00000000,
    /**
     * @brief Request to stop receiving notifications
     */
    IDS_PROFILE_NOTIFIER_STOP  = 0x00000001
};

/**
 * @brief The kinds of notifications that can be generated by this provider
 */
enum ids_bbprofile_notification {
    /**
     * @brief Notifications will now be sent for this entry
     * @details The request to receive notifications was successful. Change
     * notifications will now be sent.
     */
    IDS_PROFILE_NOTIFY_STARTED = 0x00000000,
    /**
     * @brief Notifications will no longer be sent for this entry
     * @details The request to stop receiving notifications was successful, or
     * the request to start receiving has failed. Change notifications will
     * NOT be sent.
     */
    IDS_PROFILE_NOTIFY_STOPPED = 0x00000001,
    /**
     * @brief The entry has changed
     * @details The provider has detected that the entry has changed and is
     * notifying the application. A change can include the entry being created,
     * deleted, or modified.
     */
    IDS_PROFILE_NOTIFY_CHANGED = 0x00000002
};

#endif /* IDS_BLACKBERRY_PROFILE_H_ */
