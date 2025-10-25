/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_IDENTITY_BLACKBERRYPROFILEPROPERTYTYPE_HPP
#define BB_PLATFORM_IDENTITY_BLACKBERRYPROFILEPROPERTYTYPE_HPP

#include <bb/platform/Global>
#include <QtDeclarative/QtDeclarative>

namespace bb {
namespace platform {
namespace identity {

/*!
 * @headerfile BlackBerryProfilePropertyType.hpp <bb/platform/identity/BlackBerryProfilePropertyType>
 * @brief The property types for BlackBerry ID @sa getProperties() @c type parameter.
 * @xmlonly
 * <library name="bbplatform" />
 * <apigrouping group="Platform/Identity" />
 * @endxmlonly
 */
class BB_PLATFORM_EXPORT BlackBerryProfilePropertyType {
    Q_GADGET
    Q_ENUMS( Type )
public:
    enum Type {
        /*!< @brief Application-scoped profile data.
         *
         * @details Entries stored with this type are access protected to allow
         * only the creating application access to the data. No other application
         * is able to retrieve, modify, delete or list the values. If the
         * same application is installed on another device with the same user, it
         * will have access to the data. This creates a private-store of data for
         * the application that is accessible only from the specific application
         * on any device with the same BlackBerry ID user logged in.
         */
        Application = 1,

        /*!< @brief Vendor-scoped profile data.
         *
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
        Vendor = 2 /*!< Vendor Scope Profile property type. */
    };

private:
    //!@cond PRIVATE
    BlackBerryProfilePropertyType();
    ~BlackBerryProfilePropertyType();
    //!@endcond PRIVATE
};

} // namespace identity
} // namespace platform
} // namespace bb

QML_DECLARE_TYPE( bb::platform::identity::BlackBerryProfilePropertyType )

#endif /* BB_PLATFORM_IDENTITY_BLACKBERRYPROFILEPROPERTYTYPE_HPP */
