/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_IDENTITY_BLACKBERRYPROFILEDELETEDATAFLAG_HPP
#define BB_PLATFORM_IDENTITY_BLACKBERRYPROFILEDELETEDATAFLAG_HPP

#include <bb/platform/Global>
#include <QtDeclarative/QtDeclarative>

namespace bb {
namespace platform {
namespace identity {

/*!
 * @headerfile BlackBerryProfileDeleteDataFlag.hpp <bb/platform/identity/BlackBerryProfileDeleteDataFlag>
 * @brief The flags for deleting profile entries.
 * @details Multiple flags can be combined using bitwise 'OR' unless stated
 * otherwise.
 * @sa deleteData() @c flags parameter
 * @xmlonly
 * <library name="bbplatform" />
 * <apigrouping group="Platform/Identity" />
 * @endxmlonly
 */
class BB_PLATFORM_EXPORT BlackBerryProfileDeleteDataFlag {
    Q_GADGET
    Q_ENUMS( Type )
    Q_FLAGS( Types )
public:
    enum Type {
        /*!<
         * @brief Use the default flags for delete requests.
         * @details If options are not specified, the deletion will follow the
         * default behavior where the specified remote entry is deleted as
         * well as the cached copy if it was cached.
         */
        Default = 0x00000000,

        /*!<
         * @brief Remove the local cached copy of the entry.
         * @details Override the default behavior to remove only the cached copy,
         * but leave the remote copy unchanged.
         * In cases where the application may need data stored locally for quick
         * or repeated access, the value can be cached securely on the device and
         * retrieved on demand, even when not connected to the remote storage copy.
         * The cache is synchronized with the remote copy so that the cache is
         * always up to date while the device has appropriate data coverage.
         */
        CacheOnly = 0x00000001,

        /*!<
         * @brief  Delete all entries under the profile type.
         * @details Removes all the entries for the given type. The @c name
         * specified must be @c NULL when using this flag. To avoid accidental
         * removal of shared entries, use type @c Vendor in
         * @c BlackBerryProfilePropertyType, which does not allow this flag.
         */
        DeleteAll = 0x00000002
    };
    Q_DECLARE_FLAGS( Types, Type )private:
    //!@cond PRIVATE
    BlackBerryProfileDeleteDataFlag();
    ~BlackBerryProfileDeleteDataFlag();
    //!@endcond PRIVATE
};
Q_DECLARE_OPERATORS_FOR_FLAGS( BlackBerryProfileDeleteDataFlag::Types )
} // namespace identity
} // namespace platform
} // namespace bb

QML_DECLARE_TYPE( bb::platform::identity::BlackBerryProfileDeleteDataFlag )

#endif /* BB_PLATFORM_IDENTITY_BLACKBERRYPROFILEDELETEDATAFLAG_HPP */
