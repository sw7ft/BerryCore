/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_IDENTITY_BLACKBERRYPROFILESETNOTIFICATIONFLAG_HPP
#define BB_PLATFORM_IDENTITY_BLACKBERRYPROFILESETNOTIFICATIONFLAG_HPP

#include <bb/platform/Global>
#include <QtDeclarative/QtDeclarative>

namespace bb {
namespace platform {
namespace identity {

/*!
 * @headerfile BlackBerryProfileSetNotificationFlag.hpp <bb/platform/identity/BlackBerryProfileSetNotificationFlag>
 * @brief The flags for registering/deregistering change notifications of
 * entries within the profile.
 * @details Notifications can be registered for entries either before
 * or after they have been created. In cases where the registration is done
 * after creation, the application is notified each time the value changes so
 * that it can perform any necessary operations. If registration is done
 * before an entry is created, the application is notified upon creation of
 * the value as if it were an update. Additionally, registered applications
 * receive a change notification when an entry is deleted.
 * @sa registerNotifier() @c flags parameter
 * @xmlonly
 * <library name="bbplatform" />
 * <apigrouping group="Platform/Identity" />
 * @endxmlonly
 */
class BB_PLATFORM_EXPORT BlackBerryProfileSetNotificationFlag {
    Q_GADGET
    Q_ENUMS( Type )
public:
    enum Type {

        Start = 0, /*!< Request to start receiving notifications. */
        Stop = 1 /*!< Request to stop receiving notifications. */
    };

private:
    //!@cond PRIVATE
    BlackBerryProfileSetNotificationFlag();
    ~BlackBerryProfileSetNotificationFlag();
    //!@endcond PRIVATE
};
} // namespace identity
} // namespace platform
} // namespace bb

QML_DECLARE_TYPE( bb::platform::identity::BlackBerryProfileSetNotificationFlag )

#endif /* BB_PLATFORM_IDENTITY_BLACKBERRYPROFILESETNOTIFICATIONFLAG_HPP */
