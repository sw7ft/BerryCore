/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_SCREENSHOTFORMAT_HPP
#define BB_SYSTEM_SCREENSHOTFORMAT_HPP

#include <bb/system/Global>

#include <QObject>

namespace bb
{
namespace system
{

/*!
 * @headerfile ScreenshotFormat.hpp <bb/system/ScreenshotFormat>
 *
 * @brief The list of supported image formats for capturing a @c Screenshot.
 *
 * @xmlonly
 * <apigrouping group="Platform/Utility"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.2.0
 */
class BB_SYSTEM_EXPORT ScreenshotFormat
{
    Q_GADGET
    Q_ENUMS(Type)

public:

    /*!
     *
     * @brief The list of supported image formats for capturing a @c Screenshot.
     *
     * @since BlackBerry 10.2.0
     */
    enum Type {
        /*!
         * @brief PNG image format.
         *
         * @details To specify a PNG format image using the filename, use the "png" extension only.
         *
         * @since BlackBerry 10.2.0
         */
        Png                         = 0,

        /*!
         * @brief JPEG image format.
         *
         * @details To specify a JPEG format image using the filename, use the "jpg" extension only.
         *
         * @since BlackBerry 10.2.0
         */
        Jpeg				        = 1
    };
private:
//!@cond PRIVATE
    ScreenshotFormat();
    ~ScreenshotFormat();
//!@endcond
};
} // namespace system
} // namespace bb

#endif // BB_SYSTEM_SCREENSHOTFORMAT_HPP
