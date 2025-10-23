/*!
 *
 * @copyright
 * Copyright Research In Motion Limited, 2012-2012
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_BBM_APPLICATIONPERMISSIONS_HPP
#define BB_PLATFORM_BBM_APPLICATIONPERMISSIONS_HPP

#include <bb/platform/bbm/Global>
#include <bb/platform/bbm/Permission>
#include <bb/platform/bbm/PermissionValue>

#include <QObject>
#include <QScopedPointer>

namespace bb
{
namespace platform
{
namespace bbm
{

class ApplicationPermissionsPrivate;

class Context;

/*!
 * @headerfile ApplicationPermissions.hpp <bb/platform/bbm/ApplicationPermissions> 
 *
 * @brief Represents a class that provides access to your app's permission settings on the BBM Social Platform.
 *
 * @details @c ApplicationPermissions provides access to the permissions that the current
 * user has set in the global settings for your app. For example, invitations to download your app
 * or updates to their BBM profile.
 *
 * @since BlackBerry 10.0.0
 *
 * @xmlonly
 * <library name="bbplatformbbm"/>
 * <apigrouping group="App Integration/BBM"/>
 * @endxmlonly
 */
class BB_PLATFORM_BBM_EXPORT ApplicationPermissions : public QObject
{
    Q_OBJECT
public:
    /*!
     * @brief Creates a new @c ApplicationPermissions object.
     *
     * @param context The @c Context object that provides the basis for the @c ApplicationPermissions object.
     * A @c Context object with @c RegistrationState::Allowed is necessary for creation of
     * the @c ApplicationPermissions object.
     * @param parent The QObject parent of this @c ApplicationPermissions object.
     *
     * @since BlackBerry 10.0.0
     */
    ApplicationPermissions(Context *context, QObject *parent = 0);

    /*!
     * @brief Destroys this @c ApplicationPermissions object.
     *
     * @since BlackBerry 10.0.0
     */
  virtual ~ApplicationPermissions();


  /*!
   * @brief Retrieves the @c PermissionValue for the specified @c permissionType.
   *
   * @param permissionType The type of permission value to retrieve.
   *
   * @return PermissionValue The value that is set in the global permission settings for your app.
   * @since BlackBerry 10.0.0
   */
  bb::platform::bbm::PermissionValue::Type permissionValue(bb::platform::bbm::Permission::Type permissionType) const;


private:
    Q_DECLARE_PRIVATE(ApplicationPermissions)
    Q_DISABLE_COPY(ApplicationPermissions)
    QScopedPointer<ApplicationPermissionsPrivate> d_ptr;


};

} /* namespace bbm */
} /* namespace platform */
} /* namespace bb */
#endif /* BB_PLATFORM_BBM_APPLICATIONPERMISSIONS_HPP */
