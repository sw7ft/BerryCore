/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_IDENTITY_BLACKBERRYPROFILECREATEDATAFLAG_HPP
#define BB_PLATFORM_IDENTITY_BLACKBERRYPROFILECREATEDATAFLAG_HPP

#include <bb/platform/Global>
#include <QtDeclarative/QtDeclarative>

namespace bb {
namespace platform {
namespace identity {

/*!
 * @headerfile BlackBerryProfileCreateDataFlag.hpp <bb/platform/identity/BlackBerryProfileCreateDataFlag>
 * @brief The flags for profile data creation.
 * @details Multiple flags can be combined using bitwise 'OR' unless stated
 * otherwise.
 * @sa createData() @c flags parameter
 * @xmlonly
 * <library name="bbplatform" />
 * <apigrouping group="Platform/Identity" />
 * @endxmlonly
 */
class BB_PLATFORM_EXPORT BlackBerryProfileCreateDataFlag {
    Q_GADGET
    Q_ENUMS( Type )
    Q_FLAGS( Types )

public:
    enum Type {

        /*!<
         * @brief Default creation flag.
         * @details No options specified, and the creation will follow the default
         * behavior where no caching and no extra encryption will be performed for
         * the new entry.
         */
        Default = 0x00000000,

        /*!<
         * @brief Use device-to-device encryption with dynamic keys, where user
         * interaction is not required.
         * @details Additional encryption is performed on the data before that data
         * is stored remotely. Data is encrypted with dynamically generated keys
         * shared between devices using the same BlackBerry ID user. Only devices
         * with the same user will have the keys to decrypt this data.  The keys
         * are shared between devices and not included in backups or transferred as
         * part of a device swap, so if a user only has one device, and it is lost,
         * the keys are not recoverable, and any remote data stored with this
         * encryption will be non-recoverable. Performing a "security wipe" will
         * retain the keys and the stored data is recoverable if the same user
         * logs back in to the device. If the user has multiple data-enabled devices,
         * and are data enabled, the devices with the same BlackBerry ID user will
         * exchange the keys securely so that all of them can store and retrieve
         * the data stored with this encryption. Operations will return
         * @c NotReady while the encryption keys are exchanged; the app can
         * repeat the request after a short wait to avoid failures during this one
         * time key exchange window.
         */
        EncryptDeviceToDevice = 0x00000001,

        /*!<
         * @brief Enable local caching of the entry.
         * @details Override the default behavior to enable local data caching for
         * this entry.
         * In cases where the application may need data stored locally for quick or
         * repeated access, the value can be cached securely on the device and
         * retrieved on demand, even when not connected to the remote storage copy.
         * The cache is synchronized with the remote copy so that the cache is
         * always up to date while the device has appropriate data coverage.
         */
        CacheData = 0x00000010
    };
    Q_DECLARE_FLAGS( Types, Type )

private    :
    //!@cond PRIVATE
    BlackBerryProfileCreateDataFlag();
    ~BlackBerryProfileCreateDataFlag();
    //!@endcond PRIVATE
};
Q_DECLARE_OPERATORS_FOR_FLAGS( BlackBerryProfileCreateDataFlag::Types )
} // namespace identity
} // namespace platform
} // namespace bb

QML_DECLARE_TYPE( bb::platform::identity::BlackBerryProfileCreateDataFlag )

#endif /* BB_PLATFORM_IDENTITY_BLACKBERRYPROFILECREATEDATAFLAG_HPP */
