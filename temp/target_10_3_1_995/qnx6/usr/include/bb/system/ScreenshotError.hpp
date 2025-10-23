/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_SCREENSHOTERROR_HPP
#define BB_SYSTEM_SCREENSHOTERROR_HPP

#include <bb/system/Global>

#include <QObject>

namespace bb
{
namespace system
{

/*!
 * @headerfile ScreenshotError.hpp <bb/system/ScreenshotError>
 *
 * @brief The list of outcomes for a capture attempt using @c bb::system::Screenshot.
 *
 * @xmlonly
 * <apigrouping group="Platform/Utility"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.2.0
 */
class BB_SYSTEM_EXPORT ScreenshotError
{
    Q_GADGET
    Q_ENUMS(Type)

public:

    /*!
     * @brief The list of outcomes for a capture attempt using @c bb::system::Screenshot.
     *
     * @since BlackBerry 10.2.0
     */
    enum Type {
        /*!
         * @brief No error, operation completed successfully.
         *
         * @since BlackBerry 10.2.0
         */
        None                         = 0,

        /*!
         * @brief An unrecoverable internal error occurred.
         *
         * @since BlackBerry 10.2.0
         */
        InternalError				= 1,

        /*!
         * @brief Insufficient permissions to perform the operation.
         *
         * @details The application should request @c access_shared and @c use_camera_desktop
         * before attempting the capture.
         *
         * @since BlackBerry 10.2.0
         */
        PermissionDenied			= 2,

        /*!
         * @brief The screenshot could not be written to the supplied location.
         *
         * @since BlackBerry 10.2.0
         */
        BadFilePath				= 3,

        /*!
         * @brief The image format specified is not supported.
         *
         * @since BlackBerry 10.2.0
         */
        UnsupportedFileType			= 4,

        /*!
         * @brief The user prevented the screenshot from being captured.
         *
         * @since BlackBerry 10.2.0
         */
        UserDeclined				= 5

    };
private:
//!@cond PRIVATE
    ScreenshotError();
    ~ScreenshotError();
//!@endcond
};
} // namespace system
} // namespace bb

#endif // BB_SYSTEM_SCREENSHOTERROR_HPP
