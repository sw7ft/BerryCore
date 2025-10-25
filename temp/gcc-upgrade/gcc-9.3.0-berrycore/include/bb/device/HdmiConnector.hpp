/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_DEVICE_HDMICONNECTOR_HPP
#define BB_DEVICE_HDMICONNECTOR_HPP

#include <bb/device/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace device
{

/*!
 * @headerfile HdmiConnector.hpp <bb/device/HdmiConnector>
 *
 * @brief The set of possible HDMI connectors.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Info"/>
 * <library name="bbdevice"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.2.0
 */
class BB_DEVICE_EXPORT HdmiConnector
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The set of possible HDMI connectors.
     *
     * @since BlackBerry 10.2.0
     */
    enum Type
    {
        /*!
         * @brief The type of HDMI connector on the device could not be determined.
         *
         * @since BlackBerry 10.2.0
         */
        Unknown     = 0,

        /*!
         * @brief The device has no HDMI connector.
         *
         * @since BlackBerry 10.2.0
         */
        None         = 1,

        /*!
         * @brief The device has a micro HDMI connector.
         *
         * @since BlackBerry 10.2.0
         */
        Micro        = 2
    };

private:
//!@cond PRIVATE
    HdmiConnector();
    ~HdmiConnector();
//!@endcond
};

} // namespace device
} // namespace bb

QML_DECLARE_TYPE(bb::device::HdmiConnector)
#endif // BB_DEVICE_HDMICONNECTOR_HPP
