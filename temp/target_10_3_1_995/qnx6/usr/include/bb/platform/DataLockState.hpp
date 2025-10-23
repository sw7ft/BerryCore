/*!
 * @copyright
 * Copyright BlackBerry Limited, 2014
 * BlackBerry Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_DATALOCKSTATE_HPP
#define BB_PLATFORM_DATALOCKSTATE_HPP

#include <bb/platform/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace platform
{

/*!
 * @headerfile DataLockState.hpp <bb/platform/DataLockState>
 *
 * @brief The set of possible datalock states.
 *
 * @xmlonly
 * <apigrouping group="Platform/Security"/>
 * <library name="bbplatform"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.3.1
 */
class BB_PLATFORM_EXPORT DataLockState
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The set of possible datalock states.
     *
     * @since BlackBerry 10.3.1
     */
    enum Type {
        /*!
         * @brief Not locked.
         *
         * @since BlackBerry 10.3.1
         */
        NotLocked     = 0,
        /*!
         * @brief DataLock is pending.
         *
         * @since BlackBerry 10.3.1
         */
        LockPending   = 1,
        /*!
         * @brief DataLocked.
         *
         * @since BlackBerry 10.3.1
         */
        DataLocked    = 2,
        /*!
         * @brief Startup locked.
         *
         * @since BlackBerry 10.3.1
         */
        StartupLocked = 3
    };

private:
//!@cond PRIVATE
    DataLockState();
    ~DataLockState();
//!@endcond
};

} // namespace platform
} // namespace bb

QML_DECLARE_TYPE(bb::platform::DataLockState)
#endif // BB_PLATFORM_DATALOCKSTATE_HPP
