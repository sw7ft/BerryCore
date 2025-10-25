/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_DEVICE_SDCARDACTIVITY_HPP
#define BB_DEVICE_SDCARDACTIVITY_HPP

#include <bb/device/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace device
{

/*!
 * @headerfile SdCardActivity.hpp <bb/device/SdCardActivity>
 *
 * @brief Indicates if the SD card is performing an operation or not.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Info"/>
 * <library name="bbdevice"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_DEVICE_EXPORT SdCardActivity
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief Indicates if the SD card is performing an operation or not.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*!
         * @brief The media state could not be determined.
         *
         * @since BlackBerry 10.0.0
         */
        Unknown = 0,

        /*!
         * @brief The media card filesystem is currently idle.
         *
         * @since BlackBerry 10.0.0
         */
        Idle = 1,

        /*!
         * @brief The media card filesystem is currently executing an operation.
         *
         * @since BlackBerry 10.0.0
         */
        Busy = 2,

    };

private:
    //!@cond PRIVATE
    SdCardActivity();
    ~SdCardActivity();
    //!@endcond
};

} // namespace device
} // namespace bb

QML_DECLARE_TYPE(bb::device::SdCardActivity)
#endif // BB_DEVICE_SDCARDACTIVITY_HPP
