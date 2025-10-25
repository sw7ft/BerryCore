/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_DEVICE_DISPLAYASPECTTYPE_HPP
#define BB_DEVICE_DISPLAYASPECTTYPE_HPP

#include <bb/device/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace device
{

/*!
 * @headerfile DisplayAspectType.hpp <bb/device/DisplayAspectType>
 *
 * @brief The aspect of the display describes the shape of the rectangular region that defines the display area.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Info"/>
 * <library name="bbdevice"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_DEVICE_EXPORT DisplayAspectType
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The aspect of the display describes the shape of the rectangular region that defines the display area.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief Display width greater than display height.
         *
         * @since BlackBerry 10.0.0
         */
        Landscape = 0,

        /*!
         * @brief Display width less than display height.
         *
         * @since BlackBerry 10.0.0
         */
        Portrait = 1,

        /*!
         * @brief Display width equal to display height.
         *
         * @since BlackBerry 10.0.0
         */
        Square = 2
    };

private:
//!@cond PRIVATE
    DisplayAspectType();
    ~DisplayAspectType();
//!@endcond
};

} // namespace device
} // namespace bb

QML_DECLARE_TYPE(bb::device::DisplayAspectType)
#endif // BB_DEVICE_DISPLAYASPECTTYPE_HPP
