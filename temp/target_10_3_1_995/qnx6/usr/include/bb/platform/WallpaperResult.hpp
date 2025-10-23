/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_WALLPAPERRESULT_HPP
#define BB_PLATFORM_WALLPAPERRESULT_HPP

#include <bb/platform/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace platform
{

/*!
 * @headerfile WallpaperResult.hpp <bb/platform/WallpaperResult>
 *
 * @brief The set of possible results of a request to set the wallpaper on a device.
 *
 * @xmlonly
 * <apigrouping group="Platform/Home screen"/>
 * <library name="bbplatform"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_PLATFORM_EXPORT WallpaperResult
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The set of possible results of a request to set the wallpaper on a device.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief The wallpaper was successfully changed.
         *
         * @since BlackBerry 10.0.0
         */
        Changed = 0,

        /*!
         * @brief The wallpaper is locked and cannot be changed by the user.
         *
         * @since BlackBerry 10.0.0
         */
        Locked = 1,
    };

private:
//!@cond PRIVATE
    WallpaperResult();
    ~WallpaperResult();
//!@endcond
};

} // namespace platform
} // namespace bb

QML_DECLARE_TYPE(bb::platform::WallpaperResult)
#endif // BB_PLATFORM_WALLPAPERRESULT_HPP
