/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_IDENTITY_BLACKBERRYIDPROPERTYTYPE_HPP
#define BB_PLATFORM_IDENTITY_BLACKBERRYIDPROPERTYTYPE_HPP

#include <bb/platform/Global>
#include <QtDeclarative/QtDeclarative>

namespace bb {
namespace platform {
namespace identity {

/*!
 * @headerfile BlackBerryIdPropertyType.hpp <bb/platform/identity/BlackBerryIdPropertyType>
 * @brief The type used to identify what scope a data entry will be stored in
 * within the profile.
 * @details The data profile provider uses the @c type to differentiate
 * between various scopes of data that an application may store.  The types
 * available each have their own style of protection.  Based on the usage of
 * the data by the application, the application may choose to store data
 * under one or various types.
 * @xmlonly
 * <library name="bbplatform" />
 * <apigrouping group="Platform/Identity" />
 * @endxmlonly
 */
class BB_PLATFORM_EXPORT BlackBerryIdPropertyType {
    Q_GADGET
    Q_ENUMS( Type )
public:
    enum Type {
        Core = 0 /*!< BlackBerry ID core property type. */
    };

private:
    //!@cond PRIVATE
    BlackBerryIdPropertyType();
    ~BlackBerryIdPropertyType();
    //!@endcond PRIVATE
};

} // namespace identity
} // namespace platform
} // namespace bb

QML_DECLARE_TYPE( bb::platform::identity::BlackBerryIdPropertyType )

#endif /* BB_PLATFORM_IDENTITY_BLACKBERRYIDPROPERTYTYPE_HPP */
