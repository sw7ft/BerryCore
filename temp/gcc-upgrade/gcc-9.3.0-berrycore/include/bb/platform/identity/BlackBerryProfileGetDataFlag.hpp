/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_IDENTITY_BLACKBERRYPROFILEGETDATAFLAG_HPP
#define BB_PLATFORM_IDENTITY_BLACKBERRYPROFILEGETDATAFLAG_HPP

#include <bb/platform/Global>
#include <QtDeclarative/QtDeclarative>

namespace bb {
namespace platform {
namespace identity {

/*!
 * @headerfile BlackBerryProfileGetDataFlag.hpp <bb/platform/identity/BlackBerryProfileGetDataFlag>
 * @brief The flags for Profile data retrieval.
 * @details Multiple flags can be combined using bitwise 'OR' unless stated
 * otherwise.
 * @sa ids_get_data() @c flags parameter
 * @xmlonly
 * <library name="bbplatform" />
 * <apigrouping group="Platform/Identity" />
 * @endxmlonly
 */
class BB_PLATFORM_EXPORT BlackBerryProfileGetDataFlag {
    Q_GADGET
    Q_ENUMS( Type )
    Q_FLAGS( Types )
public:
    enum Type {

        /*!<
         * @brief Use the default flags for get requests.
         * @details If options are not specified, the get request will follow the
         * default behavior where the entry is not cached.  If the entry is already
         * being cached, this flag will not disable caching.
         */
        Default = 0x00000000,

        /*!<
         * @brief Enable local caching of the entry.
         * @details Override the default behavior to enable local data caching for
         * this entry.
         * In cases where the application may need data stored locally for quick or
         * repeated access, the value can be cached securely on the device and
         * retrieved on demand, even when not connected to the remote storage copy.
         * The cache synchronizes with the remote copy so that the cache is
         * always up to date while the device has appropriate data coverage.
         */
        CacheData = 0x00000001
    };
    Q_DECLARE_FLAGS( Types, Type )

private    :
    //!@cond PRIVATE
    BlackBerryProfileGetDataFlag();
    ~BlackBerryProfileGetDataFlag();
    //!@endcond PRIVATE
};
Q_DECLARE_OPERATORS_FOR_FLAGS( BlackBerryProfileGetDataFlag::Types )
} // namespace identity
} // namespace platform
} // namespace bb

QML_DECLARE_TYPE( bb::platform::identity::BlackBerryProfileGetDataFlag )

#endif /* BB_PLATFORM_IDENTITY_BLACKBERRYPROFILEGETDATAFLAG_HPP */
