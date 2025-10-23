/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_WALLPAPERLOCKSTATE_HPP
#define BB_PLATFORM_WALLPAPERLOCKSTATE_HPP

#include <bb/platform/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace platform
{

/*!
 * @headerfile WallpaperLockState.hpp <bb/platform/WallpaperLockState>
 *
 * @brief The set of possible wallpaper lock states on the device.
 *
 * @xmlonly
 * <apigrouping group="Platform/Home screen"/>
 * <library name="bbplatform"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.2.0
 */
class BB_PLATFORM_EXPORT WallpaperLockState
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The set of possible wallpaper lock states on the device.
     *
     * @since BlackBerry 10.2.0
     */
    enum Type {
        /*!
         * @brief The wallpaper lock state could not be determined.
         * 
         * @details This state does not mean that the wallpaper cannot be changed.
         * Since the wallpaper lock state could not be determined, it may on may not
         * be possible to change the wallpaper on the device.
         *
         * @since BlackBerry 10.2.0
         */
        Unknown = 0,

        /*!
         * @brief The wallpaper is locked and cannot be changed by the user.
         *
         * @since BlackBerry 10.2.0
         */
        Locked = 1,

        /*!
         * @brief The wallpaper is unlocked and can be changed by the user.
         * 
         * @since BlackBerry 10.2.0
         */
        Unlocked = 2
    };

private:
//!@cond PRIVATE
    WallpaperLockState();
    ~WallpaperLockState();
//!@endcond
};

} // namespace platform
} // namespace bb

QML_DECLARE_TYPE(bb::platform::WallpaperLockState)
#endif // BB_PLATFORM_WALLPAPERLOCKSTATE_HPP
