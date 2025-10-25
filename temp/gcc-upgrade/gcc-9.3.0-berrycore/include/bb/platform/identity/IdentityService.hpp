/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_IDENTITY_IDENTITYSERVICE_HPP
#define BB_PLATFORM_IDENTITY_IDENTITYSERVICE_HPP

#include <bb/platform/identity/IdentityServiceLogVerbosity>
#include <bb/platform/identity/IdentityServiceResult>
#include <bb/platform/Global>

#include <QObject>
#include <QString>

namespace bb {
namespace platform {
namespace identity {

class IdentityServicePrivate;

/*!
 * @headerfile IdentityService.hpp <bb/platform/identity/IdentityService>
 * @brief The Identity Service is used for library level functions that define
 * behavior of the API, and apply to all providers created by an application.
 * @xmlonly
 * <library name="bbplatform" />
 * <apigrouping group="Platform/Identity" />
 * @endxmlonly
 */
class BB_PLATFORM_EXPORT IdentityService: public QObject {
    Q_OBJECT

    /*!
     * @brief The version of the BlackBerry ID APIs that your
     * application is using.  The version of the BlackBerry ID
     * library using the following scheme:
     * 	(Major * 1000000) + (Minor * 1000) + Patch
     */
    Q_PROPERTY( int version READ version CONSTANT FINAL )
public:
    /*!
     * @brief Constructs an empty IdentityService instance and
     * initializes the library for use.
     *
     * @param parent The parent object.  Setting parent to 0
     * constructs an IdentityService instance with no parent.
     */
    explicit IdentityService( QObject *parent = 0 );

    /*!
     * @brief Destroys the IdentityService instance.
     */
    virtual ~IdentityService();

    /*!
     * @brief Retrieves the version of the BlackBerry ID APIs that your
     * application is using.
     * @return The version of the BlackBerry ID library using the
     * following scheme:
     * 	(Major * 1000000) + (Minor * 1000) + Patch
     */
    static int version();

    /*!
     * @brief Allows an application to modify the default behavior of the APIs
     * as well as configure how the library and application are integrated.  By
     * default, GUI Allowed will be true.
     *
     * @param allowed False to suppress GUI interaction that may appear as a
     * result of API calls.
     *
     * @return IdsServiceResult::Success if successful.
     *
     * @b Errors
     * The info field of the resulting IdsResult will contain an errno value of:
     * - @c EFAULT: Library has not been initialized.
     * - @c EINVAL: An invalid parameter was passed to the function.
     * - @c ENOMEM: Not enough memory to store the setting.
     */
#ifndef Q_MOC_RUN
    Q_INVOKABLE
    static bb::platform::identity::IdentityServiceResult::Type setGuiAllowed( bool allowed );
#else
    Q_INVOKABLE static int setGuiAllowed( bool allowed );
#endif
    /*!
     * @brief Allows an application to modify the default behavior of the APIs
     * as well as configure how the library and application are integrated.  By
     * default, the log verbosity will be normal.
     *
     * @param verbosity The desired logging verbosity.
     *
     * @return IdsServiceResult::Success if successful.
     *
     * @b Errors
     * The info field of the resulting IdsResult will contain an errno value of:
     * - @c EFAULT: Library has not been initialized.
     * - @c EINVAL: An invalid parameter was passed to the function.
     * - @c ENOMEM: Not enough memory to store the setting.
     */
#ifndef Q_MOC_RUN
    Q_INVOKABLE
    static bb::platform::identity::IdentityServiceResult::Type setLogVerbosity(
            bb::platform::identity::IdentityServiceLogVerbosity::Type verbosity );
#else
    Q_INVOKABLE static int setLogVerbosity( bb::platform::identity::IdentityServiceLogVerbosity::Type verbosity );
#endif
    /*!
     * @brief Allows application's to modify the default behavior of the APIs
     * as well as configure how the library and application are integrated.
     *
     * @param groupId The calling applications group id.
     *
     * @return IdsServiceResult::Success if successful.
     *
     * @b Errors
     * The info field of the resulting IdsResult will contain an errno value of:
     * - @c EFAULT: Library has not been initialized.
     * - @c EINVAL: An invalid parameter was passed to the function.
     * - @c ENOMEM: Not enough memory to store the setting.
     */
#ifndef Q_MOC_RUN
    Q_INVOKABLE
    static bb::platform::identity::IdentityServiceResult::Type setWindowGroupId( const QString &groupId );
#else
    Q_INVOKABLE static int setWindowGroupId( const QString &groupId );
#endif
private:
    //!@cond PRIVATE
    QScopedPointer<IdentityServicePrivate> d_ptr;Q_DISABLE_COPY( IdentityService )
    Q_DECLARE_PRIVATE( IdentityService )
    //!@endcond PRIVATE
};

} // namespace identity
} // namespace platform
} // namespace bb

QML_DECLARE_TYPE( bb::platform::identity::IdentityService )

#endif /* BB_PLATFORM_IDENTITY_IDENTITYSERVICE_HPP */
