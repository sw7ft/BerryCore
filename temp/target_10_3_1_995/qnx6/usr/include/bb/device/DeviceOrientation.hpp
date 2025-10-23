/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */


#ifndef BB_DEVICE_DEVICEORIENTATION_HPP
#define BB_DEVICE_DEVICEORIENTATION_HPP

#include <bb/device/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb 
{
namespace device 
{

/*!
 *
 * @brief Represents the orientation in which the device is being held relative to 
 * the BlackBerry logo in its natural orientation.
 *
 * The natural orientation of the device is @c DeviceDirection::North (0 degrees).
 *
 * @note It is not appropriate to use this information for responding to device orientation
 * in your UI.  This value will change regardless of how the UI responds.
 * For UI orientation see @c bb::cascades::OrientationSupport.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Info"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_DEVICE_EXPORT DeviceOrientation {
    Q_GADGET
    Q_ENUMS(Type)
public:

    /*!
     * @brief The orientation in which the device is currently being held relative to the
     * BlackBerry logo in its natural orientation.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {

        /*!
         * Device is lying flat on a horizontal surface, such as a desk, with
         * the display visible.
         *
         * @since BlackBerry 10.0.0
         */
        FaceUp = 0,

        /*!
         * Device is lying flat on a horizontal surface, such as a desk, with
         * the display obscured.
         *
         * @since BlackBerry 10.0.0
         */
        FaceDown = 1,

        /*!
         * @brief BlackBerry logo is upright.
         *
         * @since BlackBerry 10.0.0
         */
        TopUp = 2,

        /*!
         * @brief BlackBerry logo is sideways - text runs downwards, display rotated 270 degrees to the left
         *
         * @since BlackBerry 10.0.0
         */
        LeftUp = 3,

        /*!
         * @brief BlackBerry logo is sideways - text runs upwards, display rotated 90 degrees to the left
         *
         * @since BlackBerry 10.0.0
         */
        RightUp = 4,

        /*!
         * @brief BlackBerry logo is upside down, display rotated upside down
         *
         * @since BlackBerry 10.0.0
         */
        BottomUp = 5
    };

private:
//! @cond PRIVATE
    DeviceOrientation();
    ~DeviceOrientation();
//! @endcond
};

}  // namespace device
}  // namespace bb

QML_DECLARE_TYPE(bb::device::DeviceOrientation)
#endif // BB_DEVICE_DEVICEORIENTATION_HPP
