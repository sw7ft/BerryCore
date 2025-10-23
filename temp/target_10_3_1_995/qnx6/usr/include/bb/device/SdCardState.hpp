/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_DEVICE_SDCARDSTATE_HPP
#define BB_DEVICE_SDCARDSTATE_HPP

#include <bb/device/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace device
{

/*!
 * @headerfile SdCardState.hpp <bb/device/SdCardState>
 *
 * @brief The state of the SD card.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Info"/>
 * <library name="bbdevice"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_DEVICE_EXPORT SdCardState
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The state of the SD card.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*!
         * @brief The media could not be determined.
         *
         * @since BlackBerry 10.0.0
         */
        Unknown = 0,

        /*!
         * @brief The media contains a recognized filesystem format and is available 
         *        for use.
         *
         * @since BlackBerry 10.0.0
         */
        Mounted = 1,

        /*!
         * @brief The media is not mounted (unrecognized  format, un-formatted or
         *        in use by another process).
         *
         * @since BlackBerry 10.0.0
         */
        Unmounted = 2,

//!@cond PRIVATE
        /*!
         * @brief Not used anymore. See @c bb::device::SdCardActivity.
         */
        Busy = 3
//!@endcond

    };

private:
    //!@cond PRIVATE
    SdCardState();
    ~SdCardState();
    //!@endcond
};

} // namespace device
} // namespace bb

QML_DECLARE_TYPE(bb::device::SdCardState)
#endif // BB_DEVICE_SDCARDSTATE_HPP
