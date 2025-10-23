/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_IDENTITY_BLACKBERRYPROFILELISTDATAFLAG_HPP
#define BB_PLATFORM_IDENTITY_BLACKBERRYPROFILELISTDATAFLAG_HPP

#include <bb/platform/Global>
#include <QtDeclarative/QtDeclarative>

namespace bb {
namespace platform {
namespace identity {

/*!
 * @headerfile BlackBerryProfileListDataFlag.hpp <bb/platform/identity/BlackBerryProfileListDataFlag>
 * @brief The flags for listing profile entries.
 * @details Multiple flags can be combined using bitwise 'OR' unless stated
 * otherwise.
 * @sa IdentityServiceProvider::listData() @c flags parameter
 * @xmlonly
 * <library name="bbplatform" />
 * <apigrouping group="Platform/Identity" />
 * @endxmlonly
 */
class BB_PLATFORM_EXPORT BlackBerryProfileListDataFlag {
    Q_GADGET
    Q_ENUMS( Type )
    Q_FLAGS( Types )
public:
    enum Type {
        /*!<
         * @brief Use the default list flags.
         * @details If options are not specified, the list process follows the
         * default behavior of listing the remotely available entries.
         */
        Default = 0x00000000
    };
    Q_DECLARE_FLAGS( Types, Type )

private    :
    //!@cond PRIVATE
    BlackBerryProfileListDataFlag();
    ~BlackBerryProfileListDataFlag();
    //!@endcond PRIVATE
};
Q_DECLARE_OPERATORS_FOR_FLAGS( BlackBerryProfileListDataFlag::Types )
} // namespace identity
} // namespace platform
} // namespace bb

QML_DECLARE_TYPE( bb::platform::identity::BlackBerryProfileListDataFlag )

#endif /* BB_PLATFORM_IDENTITY_BLACKBERRYPROFILELISTDATAFLAG_HPP */
